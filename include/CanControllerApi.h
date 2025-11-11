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

class CanControllerApi
{
private:
	Pistache::Rest::Router router;
	Pistache::Address addr;
	std::unique_ptr<Pistache::Http::Endpoint> server;
	CanController controller;
	std::mutex controller_mutex;

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

	void setupRoutes(){
		Pistache::Rest::Routes::Get(router, "/api/connect", Pistache::Rest::Routes::bind(&CanControllerApi::connect, this));
		Pistache::Rest::Routes::Get(router, "/api/debug/on", Pistache::Rest::Routes::bind(&CanControllerApi::debugOn, this));
		Pistache::Rest::Routes::Post(router, "/api/board", Pistache::Rest::Routes::bind(&CanControllerApi::board, this));
		Pistache::Rest::Routes::Post(router, "/api/steps", Pistache::Rest::Routes::bind(&CanControllerApi::steps, this));
		Pistache::Rest::Routes::Post(router, "/api/speed", Pistache::Rest::Routes::bind(&CanControllerApi::speed, this));
		Pistache::Rest::Routes::Post(router, "/api/accel", Pistache::Rest::Routes::bind(&CanControllerApi::accel, this));
		Pistache::Rest::Routes::Post(router, "/api/decel", Pistache::Rest::Routes::bind(&CanControllerApi::decel, this));
		Pistache::Rest::Routes::Get(router, "/api/move/forward", Pistache::Rest::Routes::bind(&CanControllerApi::forward, this));
		Pistache::Rest::Routes::Get(router, "/api/move/backward", Pistache::Rest::Routes::bind(&CanControllerApi::backward, this));
		Pistache::Rest::Routes::Get(router, "/api/homing/zero", Pistache::Rest::Routes::bind(&CanControllerApi::homingZero, this));
		Pistache::Rest::Routes::Get(router, "/api/homing/max", Pistache::Rest::Routes::bind(&CanControllerApi::homingMax, this));
		Pistache::Rest::Routes::Get(router, "/api/reset/driver/error", Pistache::Rest::Routes::bind(&CanControllerApi::resetDRVError, this));
		Pistache::Rest::Routes::Get(router, "/api/brake/off", Pistache::Rest::Routes::bind(&CanControllerApi::brakeOff, this));
		Pistache::Rest::Routes::Get(router, "/api/brake/on", Pistache::Rest::Routes::bind(&CanControllerApi::brakeOn, this));
		Pistache::Rest::Routes::Get(router, "/api/rezerv/off", Pistache::Rest::Routes::bind(&CanControllerApi::rezervOff, this));
		Pistache::Rest::Routes::Get(router, "/api/rezerv/on", Pistache::Rest::Routes::bind(&CanControllerApi::rezervOn, this));

		Pistache::Rest::Routes::Get(router, "/health", Pistache::Rest::Routes::bind(&CanControllerApi::health, this));
	}

	void connect(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonOpenCOM_Click();
			response.send(Pistache::Http::Code::Ok, "Connected");
			BOOST_LOG_TRIVIAL(info) << "buttonOpenCOM_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "Connection failed");
			BOOST_LOG_TRIVIAL(error) << "buttonOpenCOM_Click";
		}
	}

	void debugOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonDebugOn_Click();
			response.send(Pistache::Http::Code::Ok, "Debug ON");
			BOOST_LOG_TRIVIAL(info) << "buttonDebugOn_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "Connection failed");
			BOOST_LOG_TRIVIAL(error) << "buttonDebugOn_Click";
		}
	}

	void board(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numBoard"].as_int64();
			controller.buttonNumBoard_Click(val);
			response.send(Pistache::Http::Code::Ok, "Board Set");
			BOOST_LOG_TRIVIAL(info) << "buttonNumBoard_Click" << " JSON: " << boost::json::serialize(json_data);
		} catch (const std::exception& e){ 
			response.send(Pistache::Http::Code::Internal_Server_Error, "Board Set failed");
			BOOST_LOG_TRIVIAL(error) << "buttonNumBoard_Click" << " JSON: " << boost::json::serialize(json_data);
		}
	}

	void steps(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSteps"].as_int64();
			controller.buttonNumSteps_Click(val);
			response.send(Pistache::Http::Code::Ok, "Steps Set");
			BOOST_LOG_TRIVIAL(info) << "buttonNumSteps_Click" << " JSON: " << boost::json::serialize(json_data);
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "Steps Set failed");
			BOOST_LOG_TRIVIAL(error) << "buttonNumSteps_Click" << " JSON: " << boost::json::serialize(json_data);
		}
	}

	void speed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSpeed"].as_int64();
			controller.buttonSpeed_Click(val);
			response.send(Pistache::Http::Code::Ok, "Speed Set");
			BOOST_LOG_TRIVIAL(info) << "buttonSpeed_Click" << " JSON: " << boost::json::serialize(json_data);
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "Speed Set failed");
			BOOST_LOG_TRIVIAL(error) << "buttonSpeed_Click" << " JSON: " << boost::json::serialize(json_data);
		}
	}

	void accel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numAccel"].as_int64();
			controller.buttonAccel_Click(val);
			response.send(Pistache::Http::Code::Ok, "Acceleration Set");
			BOOST_LOG_TRIVIAL(info) << "buttonAccel_Click" << " JSON: " << boost::json::serialize(json_data);
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "Acceleration Set failed");
			BOOST_LOG_TRIVIAL(error) << "buttonAccel_Click" << " JSON: " << boost::json::serialize(json_data);
		}
	}

	void decel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numDecel"].as_int64();
			controller.buttonDecel_Click(val);
			response.send(Pistache::Http::Code::Ok, "Deceleration Set");
			BOOST_LOG_TRIVIAL(info) << "buttonDecel_Click" << " JSON: " << boost::json::serialize(json_data);
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "Deceleration Set failed");
			BOOST_LOG_TRIVIAL(error) << "buttonDecel_Click" << " JSON: " << boost::json::serialize(json_data);
		}
	}

	void forward(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonMoveForward_Click();
			response.send(Pistache::Http::Code::Ok, "Moving Borward");
			BOOST_LOG_TRIVIAL(info) << "buttonMoveForward_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "Moving Forward failed");
			BOOST_LOG_TRIVIAL(error) << "buttonMoveForward_Click";
		}
	}

	void backward(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonMoveBackward_Click();
			response.send(Pistache::Http::Code::Ok, "Moving Backward");
			BOOST_LOG_TRIVIAL(info) << "buttonMoveBackward_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "Moving Backward failed");
			BOOST_LOG_TRIVIAL(error) << "buttonMoveBackward_Click";
		}
	}

	void homingZero(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonHomingZero_Click();
			response.send(Pistache::Http::Code::Ok, "Homig Zero");
			BOOST_LOG_TRIVIAL(info) << "buttonHomingZero_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "Homig Zero failed");
			BOOST_LOG_TRIVIAL(error) << "buttonHomingZero_Click";
		}
	}

	void homingMax(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonHomingMax_Click();
			response.send(Pistache::Http::Code::Ok, "Homig Max");
			BOOST_LOG_TRIVIAL(info) << "buttonHomingMax_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "Homig Max failed");
			BOOST_LOG_TRIVIAL(error) << "buttonHomingMax_Click";
		}
	}

	void resetDRVError(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonResetDRVError_Click();
			response.send(Pistache::Http::Code::Ok, "ResetDRVError");
			BOOST_LOG_TRIVIAL(info) << "buttonResetDRVError_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "ResetDRVError failed");
			BOOST_LOG_TRIVIAL(error) << "buttonResetDRVError_Click";
		}
	}

	void brakeOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonBrakeOff_Click();
			response.send(Pistache::Http::Code::Ok, "brakeOff");
			BOOST_LOG_TRIVIAL(info) << "buttonBrakeOff_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "brakeOff failed");
			BOOST_LOG_TRIVIAL(error) << "buttonBrakeOff_Click";
		}
	}

	void brakeOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonBrakeOn_Click();
			response.send(Pistache::Http::Code::Ok, "brakeOn");
			BOOST_LOG_TRIVIAL(info) << "buttonBrakeOn_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "brakeOn failed");
			BOOST_LOG_TRIVIAL(error) << "buttonBrakeOn_Click";
		}
	}

	void rezervOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonRezervOff_Click();
			response.send(Pistache::Http::Code::Ok, "rezervOff");
			BOOST_LOG_TRIVIAL(info) << "buttonRezervOff_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "rezervOff failed");
			BOOST_LOG_TRIVIAL(error) << "buttonRezervOff_Click";
		}
	}

	void rezervOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonRezervOn_Click();
			response.send(Pistache::Http::Code::Ok, "rezervOn");
			BOOST_LOG_TRIVIAL(info) << "buttonRezervOn_Click";
		} catch (const std::exception& e){
			response.send(Pistache::Http::Code::Internal_Server_Error, "rezervOn failed");
			BOOST_LOG_TRIVIAL(error) << "buttonRezervOn_Click";
		}
	}

	void health(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		BOOST_LOG_TRIVIAL(info) << "health check";
		response.send(Pistache::Http::Code::Ok, "OK");
	}

public:
	CanControllerApi(const uint16_t numPort=5000, const uint8_t numThread=2, const std::string host="127.0.0.1")
	: addr(host, Pistache::Port(numPort))
	{
		initializeLogger();
		Pistache::Http::Endpoint::Options opts = Pistache::Http::Endpoint::options().threads(numThread);
		server = std::make_unique<Pistache::Http::Endpoint>(addr);
		setupRoutes();
		server->init(opts);
		server->setHandler(router.handler());
	}
	~CanControllerApi(){}
	
	void runServer(){
		std::cout << "Available endpoints:" << std::endl;
		std::cout << "  GET  /api/connect" << std::endl;
		std::cout << "  GET  /api/debug/on" << std::endl;
		std::cout << "  POST /api/steps" << std::endl;
		std::cout << "  POST /api/speed" << std::endl;
		std::cout << "  POST /api/accel" << std::endl;
		std::cout << "  POST /api/decel" << std::endl;
		std::cout << "  GET  /api/move/forward" << std::endl;
		std::cout << "  GET  /api/move/backward" << std::endl;
		std::cout << "  GET  /health" << std::endl;

		server->serve();
	}
};