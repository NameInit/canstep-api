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
#include <thread>
#include <filesystem>

#include "CanController.h"
#include "WebSocketServer.h"
#include "RestApiServer.h"
#include "GrpcApiServer.h"

class CanControllerApi
{
private:
    std::unique_ptr<RestApiServer> restApiServer;
    std::unique_ptr<WebSocketServer> webSocketServer;
    std::unique_ptr<GrpcApiServer> grpcApiServer;
    CanController controller;

	std::thread restApiThread;
    std::thread grpcApiThread;

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
    CanControllerApi(const uint16_t numPortRest=8080, const uint16_t numPortGRGC=50051, const uint16_t numPortWebSocket=8081)
    {
        initializeLogger();
        restApiServer = std::make_unique<RestApiServer>(controller, numPortRest);
        webSocketServer = std::make_unique<WebSocketServer>(controller, numPortWebSocket);
        grpcApiServer = std::make_unique<GrpcApiServer>(controller, numPortGRGC);
    }

    ~CanControllerApi(){
        if(webSocketServer){
            webSocketServer->stopAutoUpdates();
            webSocketServer->shutdownServer();
        }

        if(grpcApiServer){
            grpcApiServer->shutdownServer();
        }

        if(restApiServer){
            restApiServer->shutdownServer();
        }
    }
    
    void runServer(){
		if (webSocketServer) {
			try {
				webSocketServer->runServer();
				webSocketServer->startAutoUpdates(1000);
			} catch (const std::exception& e) {
				BOOST_LOG_TRIVIAL(error) << "Websocket Error: " << e.what();
			}
            
        }

        if(grpcApiServer){
            grpcApiThread = std::thread([this]() { 
                try {
                    grpcApiServer->runServer(); 
                } catch (const std::exception& e) {
                    BOOST_LOG_TRIVIAL(error) << "gRPC Thread Error: " << e.what();
                }
            });
		}

        if(restApiServer){
			restApiThread = std::thread([this]() { 
                try {
                    restApiServer->runServer();
                } catch (const std::exception& e) {
                    BOOST_LOG_TRIVIAL(error) << "Rest Thread Error: " << e.what();
                }
            });
        }

		if(grpcApiThread.joinable()){
            grpcApiThread.join();
        }

		if(restApiThread.joinable()){
            restApiThread.join();
        }
    }
};