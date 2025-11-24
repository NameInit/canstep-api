#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <boost/log/trivial.hpp>
#include <memory>
#include <unordered_set>
#include <mutex>

#include "CanController.h"

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

class WebSocketSession : public std::enable_shared_from_this<WebSocketSession> {
private:
	websocket::stream<beast::tcp_stream> ws_;
	std::unordered_set<std::shared_ptr<WebSocketSession>>& sessions_;
	CanController& controller_;
	std::mutex& controller_mutex_;
	beast::flat_buffer buffer_;

public:
	WebSocketSession(tcp::socket socket, 
					std::unordered_set<std::shared_ptr<WebSocketSession>>& sessions,
					CanController& controller,
					std::mutex& controller_mutex);

	~WebSocketSession();

	void run();
	
	void send_json(const boost::json::object& json_obj);
	void send_broadcast_message(const boost::json::object& json_obj);

private:
	void on_accept(beast::error_code ec);
	void do_read();
	void on_read(beast::error_code ec, std::size_t bytes_transferred);
	void on_write(beast::error_code ec, std::size_t bytes_transferred);
	void process_message(const std::string& message);
	void send_status();
	void send_motor_data();
};

WebSocketSession::WebSocketSession(tcp::socket socket, 
								 std::unordered_set<std::shared_ptr<WebSocketSession>>& sessions,
								 CanController& controller,
								 std::mutex& controller_mutex)
	: ws_(std::move(socket))
	, sessions_(sessions)
	, controller_(controller)
	, controller_mutex_(controller_mutex) {
}

WebSocketSession::~WebSocketSession() {
	sessions_.erase(shared_from_this());
	BOOST_LOG_TRIVIAL(info) << "WebSocket session destroyed";
}

void WebSocketSession::run() {
	ws_.set_option(
		websocket::stream_base::timeout::suggested(
			beast::role_type::server));

	ws_.set_option(websocket::stream_base::decorator(
		[](websocket::response_type& res) {
			res.set(beast::http::field::server,
				"CanController WebSocket Server");
			res.set(beast::http::field::access_control_allow_origin, "*");
		}));

	ws_.async_accept(
		beast::bind_front_handler(
			&WebSocketSession::on_accept,
			shared_from_this()));
}

void WebSocketSession::on_accept(beast::error_code ec) {
	if (ec) {
		BOOST_LOG_TRIVIAL(error) << "WebSocket accept error: " << ec.message();
		return;
	}

	sessions_.insert(shared_from_this());
	BOOST_LOG_TRIVIAL(info) << "WebSocket client connected. Total clients: " << sessions_.size();

	do_read();
}

void WebSocketSession::do_read() {
	ws_.async_read(
		buffer_,
		beast::bind_front_handler(
			&WebSocketSession::on_read,
			shared_from_this()));
}

void WebSocketSession::on_read(beast::error_code ec, std::size_t bytes_transferred) {
	if (ec == websocket::error::closed) {
		BOOST_LOG_TRIVIAL(info) << "WebSocket client disconnected";
		return;
	}

	if (ec) {
		BOOST_LOG_TRIVIAL(error) << "WebSocket read error: " << ec.message();
		return;
	}

	try {
		std::string message = beast::buffers_to_string(buffer_.data());
		BOOST_LOG_TRIVIAL(debug) << "WebSocket received: " << message;
		
		process_message(message);
		
	} catch (const std::exception& e) {
		BOOST_LOG_TRIVIAL(error) << "WebSocket message processing error: " << e.what();
		send_json({{"error", "Message processing failed"}});
	}

	buffer_.consume(buffer_.size());
	do_read();
}

void WebSocketSession::process_message(const std::string& message) {
	try {
		auto json_data = boost::json::parse(message);
		auto obj = json_data.as_object();
		
		if (!obj.contains("command")) {
			send_json({{"error", "Missing command field"}});
			return;
		}
		
		std::string command = static_cast<std::string>(obj["command"].as_string());
		
		if (command == "get_status") {
			send_status();
		} else if (command == "get_motor_data") {
			send_motor_data();
		} else if (command == "subscribe_updates") {
			send_json({{"type", "subscription"}, {"status", "subscribed"}});
		} else if (command == "ping") {
			send_json({{"type", "pong"}, {"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch()).count()}});
		} else {
			send_json({{"error", "Unknown command: " + command}});
		}
		
	} catch (const std::exception& e) {
		BOOST_LOG_TRIVIAL(error) << "WebSocket message parse error: " << e.what();
		send_json({{"error", "Invalid message format"}});
	}
}

void WebSocketSession::send_status() {
	std::lock_guard<std::mutex> lock(controller_mutex_);
	
	try {
		// Здесь можно добавить реальные вызовы методов контроллера для получения статуса
		boost::json::object status = {
			{"type", "status"},
			{"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch()).count()},
			{"connected", true},
			{"driver_on", false},
			{"moving", false},
			{"brake_engaged", false},
			{"alarm_active", false}
		};
		
		send_json(status);
		
	} catch (const std::exception& e) {
		BOOST_LOG_TRIVIAL(error) << "Error getting status: " << e.what();
		send_json({{"error", "Failed to get status"}});
	}
}

void WebSocketSession::send_motor_data() {
	std::lock_guard<std::mutex> lock(controller_mutex_);
	
	try {
		// Здесь можно добавить реальные вызовы методов контроллера
		boost::json::object motor_data = {
			{"type", "motor_data"},
			{"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch()).count()},
			{"torque", 0},
			{"speed", 0},
			{"position", 0},
			{"alarm_code", 0},
			{"temperature", 25}
		};
		
		send_json(motor_data);
		
	} catch (const std::exception& e) {
		BOOST_LOG_TRIVIAL(error) << "Error getting motor data: " << e.what();
		send_json({{"error", "Failed to get motor data"}});
	}
}

void WebSocketSession::send_json(const boost::json::object& json_obj) {
	std::string message = boost::json::serialize(json_obj);
	
	ws_.text(ws_.got_text());
	ws_.async_write(
		asio::buffer(message),
		beast::bind_front_handler(
			&WebSocketSession::on_write,
			shared_from_this()));
}

void WebSocketSession::send_broadcast_message(const boost::json::object& json_obj) {
	std::string message = boost::json::serialize(json_obj);
	
	ws_.text(ws_.got_text());
	ws_.async_write(
		asio::buffer(message),
		[self = shared_from_this()](beast::error_code ec, std::size_t bytes_transferred) {
			if (ec) {
				BOOST_LOG_TRIVIAL(error) << "WebSocket broadcast write error: " << ec.message();
			}
		});
}

void WebSocketSession::on_write(beast::error_code ec, std::size_t bytes_transferred) {
	if (ec) {
		BOOST_LOG_TRIVIAL(error) << "WebSocket write error: " << ec.message();
		return;
	}
}