#pragma once

#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <boost/log/trivial.hpp>
#include <memory>
#include <unordered_set>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
#include <cstdint>

#include "WebSocketSession.h"
#include "CanController.h"

namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

class WebSocketServer {
private:
	asio::io_context ioc;
	tcp::acceptor acceptor;
	std::unordered_set<std::shared_ptr<WebSocketSession>> sessions;
	CanController& controller;
	std::mutex& controllerMutex;
	std::atomic<bool> running{false};
	std::atomic<bool> autoUpdateEnabled{false};
	std::thread serverThread;
	std::thread updateThread;
	uint16_t port;
	int32_t updateIntervalMs{1000};

public:
	WebSocketServer(uint16_t port, CanController& controller, std::mutex& controllerMutex);
	~WebSocketServer();

	void run();
	void stop();
	void broadcast(const boost::json::object& message);

	void startAutoUpdates(int32_t intervalMs = 1000);
	void stopAutoUpdates();
	void setUpdateInterval(int32_t intervalMs);
	bool isAutoUpdateEnabled() const { return autoUpdateEnabled; }
	int32_t getUpdateInterval() const { return updateIntervalMs; }
	
	uint16_t getPort() const { return port; }
	size_t getClientCount() const { return sessions.size(); }

private:
	void doAccept();
	void autoUpdateWorker();
	void collectControllerData(boost::json::object& data);
};

WebSocketServer::WebSocketServer(uint16_t port, CanController& controller, std::mutex& controllerMutex)
	: acceptor(ioc, {tcp::v4(), port})
	, controller(controller)
	, controllerMutex(controllerMutex)
	, port(port) {
	
	BOOST_LOG_TRIVIAL(info) << "WebSocket server created on port " << port;
}

WebSocketServer::~WebSocketServer() {
	stop();
	BOOST_LOG_TRIVIAL(info) << "WebSocket server destroyed";
}

void WebSocketServer::run() {
	if (running) {
		BOOST_LOG_TRIVIAL(warning) << "WebSocket server is already running";
		return;
	}
	
	running = true;
	serverThread = std::thread([this]() {
		BOOST_LOG_TRIVIAL(info) << "WebSocket server starting on port " << port;
		doAccept();
		
		try {
			ioc.run();
			BOOST_LOG_TRIVIAL(info) << "WebSocket server stopped";
		} catch (const std::exception& e) {
			BOOST_LOG_TRIVIAL(error) << "WebSocket server error: " << e.what();
		}
	});
}

void WebSocketServer::stop() {
	if (running) {
		running = false;
		stopAutoUpdates();
		
		// Закрываем все соединения
		auto sessionsCopy = sessions;
		for (auto& session : sessionsCopy) {
			// Сессии будут удалены из sessions в своих деструкторах
		}
		sessions.clear();
		
		ioc.stop();
		if (serverThread.joinable()) {
			serverThread.join();
		}
		BOOST_LOG_TRIVIAL(info) << "WebSocket server stopped";
	}
}

void WebSocketServer::startAutoUpdates(int32_t intervalMs) {
	if (autoUpdateEnabled) {
		BOOST_LOG_TRIVIAL(warning) << "Auto updates are already enabled";
		return;
	}
	
	updateIntervalMs = intervalMs;
	autoUpdateEnabled = true;
	
	updateThread = std::thread([this]() {
		autoUpdateWorker();
	});
	
	BOOST_LOG_TRIVIAL(info) << "Started auto updates with interval " << intervalMs << "ms";
}

void WebSocketServer::stopAutoUpdates() {
	if (autoUpdateEnabled) {
		autoUpdateEnabled = false;
		if (updateThread.joinable()) {
			updateThread.join();
		}
		BOOST_LOG_TRIVIAL(info) << "Stopped auto updates";
	}
}

void WebSocketServer::setUpdateInterval(int32_t intervalMs) {
	if (intervalMs < 10) {
		BOOST_LOG_TRIVIAL(warning) << "Update interval too small, setting to minimum 10ms";
		intervalMs = 10;
	}
	
	updateIntervalMs = intervalMs;
	BOOST_LOG_TRIVIAL(info) << "Update interval set to " << intervalMs << "ms";
}

void WebSocketServer::autoUpdateWorker() {
	BOOST_LOG_TRIVIAL(info) << "Auto update worker started";
	
	while (autoUpdateEnabled && running) {
		try {
			// Собираем данные с контроллера
			boost::json::object data;
			collectControllerData(data);
			
			// Отправляем только если есть подключенные клиенты
			if (!sessions.empty()) {
				broadcast(data);
			}
			
			// Ждем следующий интервал
			std::this_thread::sleep_for(std::chrono::milliseconds(updateIntervalMs));
			
		} catch (const std::exception& e) {
			BOOST_LOG_TRIVIAL(error) << "Error in auto update worker: " << e.what();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
	
	BOOST_LOG_TRIVIAL(info) << "Auto update worker stopped";
}

void WebSocketServer::collectControllerData(boost::json::object& data) {
	std::lock_guard<std::mutex> lock(controllerMutex);
	
	try {
		auto now = std::chrono::system_clock::now();
		auto timestamp = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());
		std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
		char timeStr[100];
		std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&timeNow));
		data["server_time"] = timeStr;
		data["timestamp"] = timestamp;
		data["isConnected"] = controller.isConnected() ? "True" : "False";
		data["running"] = controller.isRunningMech() ? "True" : "False";
		data["numBoard"] = std::to_string(controller.getNumBoard());
		data["numSteps"] = std::to_string(controller.getSteps());
		data["numSpeed"] = std::to_string(controller.getSpeed());
		data["numAccel"] = std::to_string(controller.getAccel());
		data["numDecel"] = std::to_string(controller.getDecel());
		data["currentPos"] = std::to_string(controller.getPosition());
		data["startPos"] = std::to_string(controller.getStartPosition());
		data["endPos"] = std::to_string(controller.getEndPosition());
		
	} catch (const std::exception& e) {
		BOOST_LOG_TRIVIAL(error) << "Error collecting controller data: " << e.what();
		data["error"] = "Failed to collect controller data";
	}
}

void WebSocketServer::doAccept() {
	acceptor.async_accept(
		[this](beast::error_code ec, tcp::socket socket) {
			if (!running) {
				return;
			}
			
			if (ec) {
				BOOST_LOG_TRIVIAL(error) << "WebSocket accept error: " << ec.message();
			} else {
				std::make_shared<WebSocketSession>(
					std::move(socket), sessions, controller, controllerMutex)->run();
			}

			if (running) {
				doAccept();
			}
		});
}

void WebSocketServer::broadcast(const boost::json::object& message) {
	if (sessions.empty()) {
		return;
	}
	
	auto jsonStr = boost::json::serialize(message);
	BOOST_LOG_TRIVIAL(debug) << "Broadcasting to " << sessions.size() << " clients: " << jsonStr;
	
	for (auto& session : sessions) {
		session->sendBroadcastMessage(message);
	}
}