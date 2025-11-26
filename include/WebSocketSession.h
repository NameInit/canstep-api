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
    websocket::stream<beast::tcp_stream> ws;
    std::unordered_set<std::shared_ptr<WebSocketSession>>& sessions;
    CanController& controller;
    std::mutex& controllerMutex;
    beast::flat_buffer buffer;

public:
    WebSocketSession(tcp::socket socket, 
                    std::unordered_set<std::shared_ptr<WebSocketSession>>& sessions,
                    CanController& controller,
                    std::mutex& controllerMutex);

    ~WebSocketSession();

    void run();
    
    void sendJson(const boost::json::object& jsonObj);
    void sendBroadcastMessage(const boost::json::object& jsonObj);

private:
    void onAccept(beast::error_code ec);
    void doRead();
    void onRead(beast::error_code ec, std::size_t bytesTransferred);
    void onWrite(beast::error_code ec, std::size_t bytesTransferred);
    void processMessage(const std::string& message);
    void sendStatus();
    void sendMotorData();
};

WebSocketSession::WebSocketSession(tcp::socket socket, 
                                 std::unordered_set<std::shared_ptr<WebSocketSession>>& sessions,
                                 CanController& controller,
                                 std::mutex& controllerMutex)
    : ws(std::move(socket))
    , sessions(sessions)
    , controller(controller)
    , controllerMutex(controllerMutex) {
}

WebSocketSession::~WebSocketSession() {
    sessions.erase(shared_from_this());
    BOOST_LOG_TRIVIAL(info) << "WebSocket session destroyed";
}

void WebSocketSession::run() {
    ws.set_option(
        websocket::stream_base::timeout::suggested(
            beast::role_type::server));

    ws.set_option(websocket::stream_base::decorator(
        [](websocket::response_type& res) {
            res.set(beast::http::field::server,
                "CanController WebSocket Server");
            res.set(beast::http::field::access_control_allow_origin, "*");
        }));

    ws.async_accept(
        beast::bind_front_handler(
            &WebSocketSession::onAccept,
            shared_from_this()));
}

void WebSocketSession::onAccept(beast::error_code ec) {
    if (ec) {
        BOOST_LOG_TRIVIAL(error) << "WebSocket accept error: " << ec.message();
        return;
    }

    sessions.insert(shared_from_this());
    BOOST_LOG_TRIVIAL(info) << "WebSocket client connected. Total clients: " << sessions.size();

    doRead();
}

void WebSocketSession::doRead() {
    ws.async_read(
        buffer,
        beast::bind_front_handler(
            &WebSocketSession::onRead,
            shared_from_this()));
}

void WebSocketSession::onRead(beast::error_code ec, std::size_t bytesTransferred) {
    if (ec == websocket::error::closed) {
        BOOST_LOG_TRIVIAL(info) << "WebSocket client disconnected";
        return;
    }

    if (ec) {
        BOOST_LOG_TRIVIAL(error) << "WebSocket read error: " << ec.message();
        return;
    }

    try {
        std::string message = beast::buffers_to_string(buffer.data());
        BOOST_LOG_TRIVIAL(debug) << "WebSocket received: " << message;
        
        processMessage(message);
        
    } catch (const std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << "WebSocket message processing error: " << e.what();
        sendJson({{"error", "Message processing failed"}});
    }

    buffer.consume(buffer.size());
    doRead();
}

void WebSocketSession::processMessage(const std::string& message) {
    try {
        auto jsonData = boost::json::parse(message);
        auto obj = jsonData.as_object();
        
        if (!obj.contains("command")) {
            sendJson({{"error", "Missing command field"}});
            return;
        }
        
        std::string command = static_cast<std::string>(obj["command"].as_string());
        
        if (command == "get_status") {
            sendStatus();
        } else if (command == "get_motor_data") {
            sendMotorData();
        } else if (command == "subscribe_updates") {
            sendJson({{"type", "subscription"}, {"status", "subscribed"}});
        } else if (command == "ping") {
            sendJson({{"type", "pong"}, {"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count()}});
        } else {
            sendJson({{"error", "Unknown command: " + command}});
        }
        
    } catch (const std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << "WebSocket message parse error: " << e.what();
        sendJson({{"error", "Invalid message format"}});
    }
}

void WebSocketSession::sendStatus() {
    std::lock_guard<std::mutex> lock(controllerMutex);
    
    try {
        // Здесь можно добавить реальные вызовы методов контроллера для получения статуса
        boost::json::object status = {
            // {"type", "status"},
            // {"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
            //     std::chrono::system_clock::now().time_since_epoch()).count()},
            // {"connected", true},
            // {"driver_on", false},
            // {"moving", false},
            // {"brake_engaged", false},
            // {"alarm_active", false}
        };
        
        sendJson(status);
        
    } catch (const std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << "Error getting status: " << e.what();
        sendJson({{"error", "Failed to get status"}});
    }
}

void WebSocketSession::sendMotorData() {
    std::lock_guard<std::mutex> lock(controllerMutex);
    
    try {
        // Здесь можно добавить реальные вызовы методов контроллера
        boost::json::object motorData = {
            // {"type", "motor_data"},
            // {"timestamp", std::chrono::duration_cast<std::chrono::milliseconds>(
            //     std::chrono::system_clock::now().time_since_epoch()).count()},
            // {"torque", 0},
            // {"speed", 0},
            // {"position", 0},
            // {"alarm_code", 0},
            // {"temperature", 25}
        };
        
        sendJson(motorData);
        
    } catch (const std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << "Error getting motor data: " << e.what();
        sendJson({{"error", "Failed to get motor data"}});
    }
}

void WebSocketSession::sendJson(const boost::json::object& jsonObj) {
    std::string message = boost::json::serialize(jsonObj);
    
    ws.text(ws.got_text());
    ws.async_write(
        asio::buffer(message),
        beast::bind_front_handler(
            &WebSocketSession::onWrite,
            shared_from_this()));
}

void WebSocketSession::sendBroadcastMessage(const boost::json::object& jsonObj) {
    std::string message = boost::json::serialize(jsonObj);
    
    ws.text(ws.got_text());
    ws.async_write(
        asio::buffer(message),
        [self = shared_from_this()](beast::error_code ec, std::size_t bytesTransferred) {
            if (ec) {
                BOOST_LOG_TRIVIAL(error) << "WebSocket broadcast write error: " << ec.message();
            }
        });
}

void WebSocketSession::onWrite(beast::error_code ec, std::size_t bytesTransferred) {
    if (ec) {
        BOOST_LOG_TRIVIAL(error) << "WebSocket write error: " << ec.message();
        return;
    }
}