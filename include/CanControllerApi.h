#pragma once

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <boost/json.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <memory>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <mutex>
#include <filesystem>

#include "CanController.h"
#include "WebSocketServer.h"
#include "RestApiServer.h"

class CanControllerApi
{
private:
	std::unique_ptr<RestApiServer> restApiServer;
	std::unique_ptr<WebSocketServer> webSocketServer;
	CanController controller;

	void initializeLogger() {
		namespace logging = boost::log;
		namespace keywords = boost::log::keywords;
		namespace expr = boost::log::expressions;
		namespace sinks = boost::log::sinks;

		std::filesystem::create_directories("logs");

		auto fmtTimeStamp = expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f");
		auto fmtSeverity = expr::attr<logging::trivial::severity_level>("Severity");
		auto fmtMessage = expr::smessage;

		auto fmt = expr::format("[%1%] [%2%] %3%")
			% fmtTimeStamp
			% fmtSeverity
			% fmtMessage;
		
		logging::add_console_log(
			std::clog,
			keywords::format = fmt,
			keywords::filter = logging::trivial::severity >= logging::trivial::info
		);
		
		auto file_sink = logging::add_file_log(
			keywords::file_name = "logs/can_api_%Y-%m-%d.log",
			keywords::format = fmt,
			keywords::filter = logging::trivial::severity >= logging::trivial::debug,
			keywords::auto_flush = true,
			keywords::open_mode = std::ios_base::app,
			keywords::rotation_size = 10 * 1024 * 1024,
			keywords::max_size = 100 * 1024 * 1024,
			keywords::time_based_rotation = sinks::file::rotation_at_time_interval(boost::posix_time::hours(24))
		);

		logging::add_common_attributes();
	}

public:
	CanControllerApi(const uint16_t numPortRest=8080, const uint16_t numPortWebSocket=8081, const uint8_t numThread=2, const std::string host="127.0.0.1")
	{
		initializeLogger();
		restApiServer = std::make_unique<RestApiServer>(controller, numPortRest);
		webSocketServer = std::make_unique<WebSocketServer>(controller, numPortWebSocket);
	}
	~CanControllerApi(){
		if(restApiServer){
			restApiServer->shutdownServer();
		}

		if(webSocketServer){
			webSocketServer->stopAutoUpdates();
			webSocketServer->shutdownServer();
		}
	}
	
	void runServer(){
		if (webSocketServer) {
			webSocketServer->runServer();
			webSocketServer->startAutoUpdates(1000);
		}

		if(restApiServer){
			restApiServer->runServer();
		}
	}
};