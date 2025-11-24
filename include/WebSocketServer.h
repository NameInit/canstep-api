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

#include "WebSocketSession.h"
#include "CanController.h"

namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

class WebSocketServer {
private:
	asio::io_context ioc_;
	tcp::acceptor acceptor_;
	std::unordered_set<std::shared_ptr<WebSocketSession>> sessions_;
	CanController& controller_;
	std::mutex& controller_mutex_;
	std::atomic<bool> running_{false};
	std::atomic<bool> auto_update_enabled_{false};
	std::thread server_thread_;
	std::thread update_thread_;
	unsigned short port_;
	int update_interval_ms_{1000};

public:
	WebSocketServer(unsigned short port, CanController& controller, std::mutex& controller_mutex);
	~WebSocketServer();

	void run();
	void stop();
	void broadcast(const boost::json::object& message);
	
	// Вспомогательные методы для отправки специфичных сообщений
	void send_motor_update(int torque, int speed, int position, int alarm_code = 0);
	void send_alarm_update(int alarm_code, const std::string& alarm_message = "");
	void send_connection_status(bool connected);
	void send_movement_status(bool moving, const std::string& direction = "");
	void send_driver_status(bool driver_on);
	void send_system_status();
	
	// Методы для автоматического обновления
	void start_auto_updates(int interval_ms = 1000);
	void stop_auto_updates();
	void set_update_interval(int interval_ms);
	bool is_auto_update_enabled() const { return auto_update_enabled_; }
	int get_update_interval() const { return update_interval_ms_; }
	
	unsigned short get_port() const { return port_; }
	size_t get_client_count() const { return sessions_.size(); }

private:
	void do_accept();
	void auto_update_worker();
	void collect_controller_data(boost::json::object& data);
};

WebSocketServer::WebSocketServer(unsigned short port, CanController& controller, std::mutex& controller_mutex)
	: acceptor_(ioc_, {tcp::v4(), port})
	, controller_(controller)
	, controller_mutex_(controller_mutex)
	, port_(port) {
	
	BOOST_LOG_TRIVIAL(info) << "WebSocket server created on port " << port;
}

WebSocketServer::~WebSocketServer() {
	stop();
	BOOST_LOG_TRIVIAL(info) << "WebSocket server destroyed";
}

void WebSocketServer::run() {
	if (running_) {
		BOOST_LOG_TRIVIAL(warning) << "WebSocket server is already running";
		return;
	}
	
	running_ = true;
	server_thread_ = std::thread([this]() {
		BOOST_LOG_TRIVIAL(info) << "WebSocket server starting on port " << port_;
		do_accept();
		
		try {
			ioc_.run();
			BOOST_LOG_TRIVIAL(info) << "WebSocket server stopped";
		} catch (const std::exception& e) {
			BOOST_LOG_TRIVIAL(error) << "WebSocket server error: " << e.what();
		}
	});
}

void WebSocketServer::stop() {
	if (running_) {
		running_ = false;
		stop_auto_updates();
		
		// Закрываем все соединения
		auto sessions_copy = sessions_;
		for (auto& session : sessions_copy) {
			// Сессии будут удалены из sessions_ в своих деструкторах
		}
		sessions_.clear();
		
		ioc_.stop();
		if (server_thread_.joinable()) {
			server_thread_.join();
		}
		BOOST_LOG_TRIVIAL(info) << "WebSocket server stopped";
	}
}

void WebSocketServer::start_auto_updates(int interval_ms) {
	if (auto_update_enabled_) {
		BOOST_LOG_TRIVIAL(warning) << "Auto updates are already enabled";
		return;
	}
	
	update_interval_ms_ = interval_ms;
	auto_update_enabled_ = true;
	
	update_thread_ = std::thread([this]() {
		auto_update_worker();
	});
	
	BOOST_LOG_TRIVIAL(info) << "Started auto updates with interval " << interval_ms << "ms";
}

void WebSocketServer::stop_auto_updates() {
	if (auto_update_enabled_) {
		auto_update_enabled_ = false;
		if (update_thread_.joinable()) {
			update_thread_.join();
		}
		BOOST_LOG_TRIVIAL(info) << "Stopped auto updates";
	}
}

void WebSocketServer::set_update_interval(int interval_ms) {
	if (interval_ms < 10) {
		BOOST_LOG_TRIVIAL(warning) << "Update interval too small, setting to minimum 10ms";
		interval_ms = 10;
	}
	
	update_interval_ms_ = interval_ms;
	BOOST_LOG_TRIVIAL(info) << "Update interval set to " << interval_ms << "ms";
}

void WebSocketServer::auto_update_worker() {
	BOOST_LOG_TRIVIAL(info) << "Auto update worker started";
	
	while (auto_update_enabled_ && running_) {
		try {
			// Собираем данные с контроллера
			boost::json::object data;
			collect_controller_data(data);
			
			// Отправляем только если есть подключенные клиенты
			if (!sessions_.empty()) {
				broadcast(data);
			}
			
			// Ждем следующий интервал
			std::this_thread::sleep_for(std::chrono::milliseconds(update_interval_ms_));
			
		} catch (const std::exception& e) {
			BOOST_LOG_TRIVIAL(error) << "Error in auto update worker: " << e.what();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
	
	BOOST_LOG_TRIVIAL(info) << "Auto update worker stopped";
}

void WebSocketServer::collect_controller_data(boost::json::object& data) {
	std::lock_guard<std::mutex> lock(controller_mutex_);
	
	try {
		auto now = std::chrono::system_clock::now();
		auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
			now.time_since_epoch()).count();
		
		// Базовые данные, которые всегда отправляем
		data = {
			{"type", "auto_update"},
			{"timestamp", timestamp},
			{"clients_connected", static_cast<int64_t>(sessions_.size())}
		};
		
		// Здесь можно добавить вызовы реальных методов контроллера
		// Для примера добавляем заглушки - в реальном коде замените на вызовы методов CanController
		
		// // Статус подключения (заглушка)
		// data["connected"] = true;
		
		// // Данные мотора (заглушки)
		// data["motor_torque"] = 0;
		// data["motor_speed"] = 0;
		// data["motor_position"] = 0;
		// data["motor_temperature"] = 25;
		
		// // Статусы системы (заглушки)
		// data["driver_enabled"] = false;
		// data["moving"] = false;
		// data["brake_engaged"] = true;
		// data["alarm_active"] = false;
		// data["alarm_code"] = 0;
		
		// // Информация о сервере
		// data["update_interval_ms"] = update_interval_ms_;
		// data["server_uptime_ms"] = timestamp; // В реальности нужно вычислять uptime
		
		// Добавляем системное время для отладки
		std::time_t time_now = std::chrono::system_clock::to_time_t(now);
		char time_str[100];
		std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", std::localtime(&time_now));
		data["server_time"] = time_str;
		
	} catch (const std::exception& e) {
		BOOST_LOG_TRIVIAL(error) << "Error collecting controller data: " << e.what();
		data["error"] = "Failed to collect controller data";
	}
}

void WebSocketServer::do_accept() {
	acceptor_.async_accept(
		[this](beast::error_code ec, tcp::socket socket) {
			if (!running_) {
				return;
			}
			
			if (ec) {
				BOOST_LOG_TRIVIAL(error) << "WebSocket accept error: " << ec.message();
			} else {
				std::make_shared<WebSocketSession>(
					std::move(socket), sessions_, controller_, controller_mutex_)->run();
			}

			if (running_) {
				do_accept();
			}
		});
}

void WebSocketServer::broadcast(const boost::json::object& message) {
	if (sessions_.empty()) {
		return;
	}
	
	auto json_str = boost::json::serialize(message);
	BOOST_LOG_TRIVIAL(debug) << "Broadcasting to " << sessions_.size() << " clients: " << json_str;
	
	for (auto& session : sessions_) {
		session->send_broadcast_message(message);
	}
}

void WebSocketServer::send_motor_update(int torque, int speed, int position, int alarm_code) {
	boost::json::object update = {
		{"type", "motor_update"},
		{"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count()},
		{"torque", torque},
		{"speed", speed},
		{"position", position},
		{"alarm_code", alarm_code}
	};
	
	broadcast(update);
}

void WebSocketServer::send_alarm_update(int alarm_code, const std::string& alarm_message) {
	boost::json::object update = {
		{"type", "alarm_update"},
		{"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count()},
		{"alarm_code", alarm_code},
		{"alarm_message", alarm_message}
	};
	
	broadcast(update);
}

void WebSocketServer::send_connection_status(bool connected) {
	boost::json::object update = {
		{"type", "connection_status"},
		{"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count()},
		{"connected", connected}
	};
	
	broadcast(update);
}

void WebSocketServer::send_movement_status(bool moving, const std::string& direction) {
	boost::json::object update = {
		{"type", "movement_status"},
		{"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count()},
		{"moving", moving},
		{"direction", direction}
	};
	
	broadcast(update);
}

void WebSocketServer::send_driver_status(bool driver_on) {
	boost::json::object update = {
		{"type", "driver_status"},
		{"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count()},
		{"driver_on", driver_on}
	};
	
	broadcast(update);
}

void WebSocketServer::send_system_status() {
	boost::json::object status;
	collect_controller_data(status);
	status["type"] = "system_status"; // Переопределяем тип
	broadcast(status);
}