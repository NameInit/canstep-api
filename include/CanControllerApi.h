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
		Pistache::Rest::Routes::Get(router, "/api/alarm/reset/off", Pistache::Rest::Routes::bind(&CanControllerApi::AlarmResetOff, this));
		Pistache::Rest::Routes::Get(router, "/api/alarm/reset/on", Pistache::Rest::Routes::bind(&CanControllerApi::AlarmResetOn, this));
		Pistache::Rest::Routes::Post(router, "/api/current/pos", Pistache::Rest::Routes::bind(&CanControllerApi::currentPos, this));
		Pistache::Rest::Routes::Post(router, "/api/save/board", Pistache::Rest::Routes::bind(&CanControllerApi::saveNumBoard, this));
		Pistache::Rest::Routes::Post(router, "/api/save/group", Pistache::Rest::Routes::bind(&CanControllerApi::saveNumGroup, this));
		Pistache::Rest::Routes::Post(router, "/api/save/start/pos", Pistache::Rest::Routes::bind(&CanControllerApi::saveStartPos, this));
		Pistache::Rest::Routes::Post(router, "/api/save/end/pos", Pistache::Rest::Routes::bind(&CanControllerApi::saveEndPos, this));
		Pistache::Rest::Routes::Post(router, "/api/save/max/speed", Pistache::Rest::Routes::bind(&CanControllerApi::saveMaxSpeed, this));
		Pistache::Rest::Routes::Post(router, "/api/save/default/speed", Pistache::Rest::Routes::bind(&CanControllerApi::saveDefaultSpeed, this));
		Pistache::Rest::Routes::Post(router, "/api/save/accel", Pistache::Rest::Routes::bind(&CanControllerApi::saveAccel, this));
		Pistache::Rest::Routes::Post(router, "/api/save/decel", Pistache::Rest::Routes::bind(&CanControllerApi::saveDecel, this));
		Pistache::Rest::Routes::Post(router, "/api/save/delta", Pistache::Rest::Routes::bind(&CanControllerApi::saveDelta, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/1", Pistache::Rest::Routes::bind(&CanControllerApi::sensor1Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/2", Pistache::Rest::Routes::bind(&CanControllerApi::sensor2Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/3", Pistache::Rest::Routes::bind(&CanControllerApi::sensor3Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/4", Pistache::Rest::Routes::bind(&CanControllerApi::sensor4Polarity, this));
		
		Pistache::Rest::Routes::Get(router, "/health", Pistache::Rest::Routes::bind(&CanControllerApi::health, this));
	}

	void connect(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonOpenCOM_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonOpenCOM_Click";
			response.send(Pistache::Http::Code::Ok, "Connected");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonOpenCOM_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "Connection failed");
		}
	}

	void debugOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonDebugOn_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonDebugOn_Click";
			response.send(Pistache::Http::Code::Ok, "Debug ON");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonDebugOn_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "Connection failed");
		}
	}

	void board(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numBoard"].as_int64();
			controller.buttonNumBoard_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonNumBoard_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Board Set");
		} catch (const std::exception& e){ 
			BOOST_LOG_TRIVIAL(error) << "buttonNumBoard_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Board Set failed");
		}
	}

	void steps(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSteps"].as_int64();
			controller.buttonNumSteps_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonNumSteps_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Steps Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonNumSteps_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Steps Set failed");
		}
	}

	void speed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSpeed"].as_int64();
			controller.buttonSpeed_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonSpeed_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Speed Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSpeed_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Speed Set failed");
		}
	}

	void accel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numAccel"].as_int64();
			controller.buttonAccel_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonAccel_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Acceleration Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonAccel_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Acceleration Set failed");
		}
	}

	void decel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numDecel"].as_int64();
			controller.buttonDecel_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonDecel_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Deceleration Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonDecel_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Deceleration Set failed");
		}
	}

	void forward(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonMoveForward_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonMoveForward_Click";
			response.send(Pistache::Http::Code::Ok, "Moving Borward");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonMoveForward_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "Moving Forward failed");
		}
	}

	void backward(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonMoveBackward_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonMoveBackward_Click";
			response.send(Pistache::Http::Code::Ok, "Moving Backward");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonMoveBackward_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "Moving Backward failed");
		}
	}

	void homingZero(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonHomingZero_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonHomingZero_Click";
			response.send(Pistache::Http::Code::Ok, "Homig Zero");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonHomingZero_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "Homig Zero failed");
		}
	}

	void homingMax(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonHomingMax_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonHomingMax_Click";
			response.send(Pistache::Http::Code::Ok, "Homig Max");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonHomingMax_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "Homig Max failed");
		}
	}

	void resetDRVError(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonResetDRVError_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonResetDRVError_Click";
			response.send(Pistache::Http::Code::Ok, "ResetDRVError");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonResetDRVError_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "ResetDRVError failed");
		}
	}

	void brakeOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonBrakeOff_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonBrakeOff_Click";
			response.send(Pistache::Http::Code::Ok, "brakeOff");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonBrakeOff_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "brakeOff failed");
		}
	}

	void brakeOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonBrakeOn_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonBrakeOn_Click";
			response.send(Pistache::Http::Code::Ok, "brakeOn");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonBrakeOn_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "brakeOn failed");
		}
	}

	void rezervOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonRezervOff_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonRezervOff_Click";
			response.send(Pistache::Http::Code::Ok, "rezervOff");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonRezervOff_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "rezervOff failed");
		}
	}

	void rezervOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonRezervOn_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonRezervOn_Click";
			response.send(Pistache::Http::Code::Ok, "rezervOn");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonRezervOn_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "rezervOn failed");
		}
	}

	void AlarmResetOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonAlarmResetOff_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonAlarmResetOff_Click";
			response.send(Pistache::Http::Code::Ok, "AlarmResetOff");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonAlarmResetOff_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "AlarmResetOff failed");
		}
	}

	void AlarmResetOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonAlarmResetOn_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonAlarmResetOn_Click";
			response.send(Pistache::Http::Code::Ok, "AlarmResetOn");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonAlarmResetOn_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "AlarmResetOn failed");
		}
	}

	void currentPos(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numPos"].as_int64();
			controller.buttonCurrentPositionSet_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonCurrentPositionSet_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "CurrentPosition Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonCurrentPositionSet_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "CurrentPosition Set failed");
		}
	}

	void saveNumBoard(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numBoard"].as_int64();
			controller.buttonNumBoardSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonNumBoardSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveNumBoard Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonNumBoardSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveNumBoard Set failed");
		}
	}

	void saveNumGroup(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numGroup"].as_int64();
			controller.buttonNumGroupSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonNumGroupSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveNumGroup Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonNumGroupSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveNumGroup Set failed");
		}
	}

	void saveStartPos(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numPos"].as_int64();
			controller.buttonStartPositionSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonStartPositionSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveStartPos Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonStartPositionSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveStartPos Set failed");
		}
	}

	void saveEndPos(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numPos"].as_int64();
			controller.buttonEndPositionSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonEndPositionSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveEndPos Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonEndPositionSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveEndPos Set failed");
		}
	}

	void saveMaxSpeed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSpeed"].as_int64();
			controller.buttonMaxSpeedSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonMaxSpeedSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveMaxSpeed Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonMaxSpeedSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveMaxSpeed Set failed");
		}
	}

	void saveDefaultSpeed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSpeed"].as_int64();
			controller.buttonDefaultSpeedSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonDefaultSpeedSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveDefaultSpeed Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonDefaultSpeedSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveDefaultSpeed Set failed");
		}
	}

	void saveAccel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numAccel"].as_int64();
			controller.buttonAccelSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonAccelSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveAccel Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonAccelSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveAccel Set failed");
		}
	}

	void saveDecel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numDecel"].as_int64();
			controller.buttonDecelSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonDecelSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveDecel Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonDecelSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveDecel Set failed");
		}
	}

	void saveDelta(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numDelta"].as_int64();
			controller.buttonDeltaSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonDeltaSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveDelta Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonDeltaSave_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveDelta Set failed");
		}
	}

	void sensor1Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			uint8_t val=static_cast<uint8_t>(obj["numInverting"].as_int64());
			std::cout << static_cast<int>(val) << std::endl;
			// controller.buttonSensor1Polarity_Click(val); segmentation error, need to check with connect
			BOOST_LOG_TRIVIAL(info) << "buttonSensor1Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "sensor1Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor1Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "sensor1Polarity Set failed");
		}
	}

	void sensor2Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			uint8_t val=static_cast<uint8_t>(obj["numInverting"].as_int64());
			std::cout << static_cast<int>(val) << std::endl;
			// controller.buttonSensor2Polarity_Click(val); segmentation error, need to check with connect
			BOOST_LOG_TRIVIAL(info) << "buttonSensor2Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "sensor2Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor2Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "sensor2Polarity Set failed");
		}
	}

	void sensor3Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			uint8_t val=static_cast<uint8_t>(obj["numInverting"].as_int64());
			std::cout << static_cast<int>(val) << std::endl;
			// controller.buttonSensor3Polarity_Click(val); segmentation error, need to check with connect
			BOOST_LOG_TRIVIAL(info) << "buttonSensor3Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "sensor3Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor3Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "sensor3Polarity Set failed");
		}
	}

	void sensor4Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			uint8_t val=static_cast<uint8_t>(obj["numInverting"].as_int64());
			std::cout << static_cast<int>(val) << std::endl;
			// controller.buttonSensor4Polarity_Click(val); segmentation error, need to check with connect
			BOOST_LOG_TRIVIAL(info) << "buttonSensor4Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "sensor4Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor4Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "sensor4Polarity Set failed");
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
		std::cout << "Run Server" << std::endl;

		server->serve();
	}
};