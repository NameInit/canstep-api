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
		Pistache::Rest::Routes::Post(router, "/api/autosender", Pistache::Rest::Routes::bind(&CanControllerApi::autosender, this));
		Pistache::Rest::Routes::Get(router, "/api/connect", Pistache::Rest::Routes::bind(&CanControllerApi::connect, this));
		Pistache::Rest::Routes::Get(router, "/api/debug/on", Pistache::Rest::Routes::bind(&CanControllerApi::debugOn, this));
		Pistache::Rest::Routes::Post(router, "/api/board/set", Pistache::Rest::Routes::bind(&CanControllerApi::board, this));
		Pistache::Rest::Routes::Post(router, "/api/steps/set", Pistache::Rest::Routes::bind(&CanControllerApi::steps, this));
		Pistache::Rest::Routes::Post(router, "/api/speed/set", Pistache::Rest::Routes::bind(&CanControllerApi::speed, this));
		Pistache::Rest::Routes::Post(router, "/api/accel/set", Pistache::Rest::Routes::bind(&CanControllerApi::accel, this));
		Pistache::Rest::Routes::Post(router, "/api/decel/set", Pistache::Rest::Routes::bind(&CanControllerApi::decel, this));
		Pistache::Rest::Routes::Get(router, "/api/move/forward", Pistache::Rest::Routes::bind(&CanControllerApi::forward, this));
		Pistache::Rest::Routes::Get(router, "/api/move/backward", Pistache::Rest::Routes::bind(&CanControllerApi::backward, this));
		Pistache::Rest::Routes::Get(router, "/api/homing/zero", Pistache::Rest::Routes::bind(&CanControllerApi::homingZero, this));
		Pistache::Rest::Routes::Get(router, "/api/homing/max", Pistache::Rest::Routes::bind(&CanControllerApi::homingMax, this));
		Pistache::Rest::Routes::Get(router, "/api/reset/driver/error", Pistache::Rest::Routes::bind(&CanControllerApi::resetDRVError, this));
		Pistache::Rest::Routes::Get(router, "/api/move/stop", Pistache::Rest::Routes::bind(&CanControllerApi::stop, this));
		Pistache::Rest::Routes::Get(router, "/api/brake/off", Pistache::Rest::Routes::bind(&CanControllerApi::brakeOff, this));
		Pistache::Rest::Routes::Get(router, "/api/brake/on", Pistache::Rest::Routes::bind(&CanControllerApi::brakeOn, this));
		Pistache::Rest::Routes::Get(router, "/api/rezerv/off", Pistache::Rest::Routes::bind(&CanControllerApi::rezervOff, this));
		Pistache::Rest::Routes::Get(router, "/api/rezerv/on", Pistache::Rest::Routes::bind(&CanControllerApi::rezervOn, this));
		Pistache::Rest::Routes::Get(router, "/api/alarm/reset/off", Pistache::Rest::Routes::bind(&CanControllerApi::alarmResetOff, this));
		Pistache::Rest::Routes::Get(router, "/api/alarm/reset/on", Pistache::Rest::Routes::bind(&CanControllerApi::alarmResetOn, this));
		Pistache::Rest::Routes::Post(router, "/api/current/pos", Pistache::Rest::Routes::bind(&CanControllerApi::currentPos, this));
		Pistache::Rest::Routes::Get(router, "/api/reset/canstep", Pistache::Rest::Routes::bind(&CanControllerApi::resetCANStep, this));
		Pistache::Rest::Routes::Get(router, "/api/driver/on", Pistache::Rest::Routes::bind(&CanControllerApi::driverOn, this));
		Pistache::Rest::Routes::Get(router, "/api/driver/off", Pistache::Rest::Routes::bind(&CanControllerApi::driverOff, this));
		Pistache::Rest::Routes::Get(router, "/api/lostcounters/reset", Pistache::Rest::Routes::bind(&CanControllerApi::resetLostCounters, this));
		Pistache::Rest::Routes::Get(router, "/api/motor/torque", Pistache::Rest::Routes::bind(&CanControllerApi::motorTorque, this));
		Pistache::Rest::Routes::Get(router, "/api/motor/speed", Pistache::Rest::Routes::bind(&CanControllerApi::motorSpeed, this));
		Pistache::Rest::Routes::Get(router, "/api/pos/absolute", Pistache::Rest::Routes::bind(&CanControllerApi::absolutePositionRotorUint, this));
		Pistache::Rest::Routes::Get(router, "/api/alarm/code", Pistache::Rest::Routes::bind(&CanControllerApi::alarmCode, this));
		Pistache::Rest::Routes::Post(router, "/api/save/board", Pistache::Rest::Routes::bind(&CanControllerApi::saveNumBoard, this));
		Pistache::Rest::Routes::Post(router, "/api/save/group", Pistache::Rest::Routes::bind(&CanControllerApi::saveNumGroup, this));
		Pistache::Rest::Routes::Post(router, "/api/save/start/pos", Pistache::Rest::Routes::bind(&CanControllerApi::saveStartPos, this));
		Pistache::Rest::Routes::Post(router, "/api/save/end/pos", Pistache::Rest::Routes::bind(&CanControllerApi::saveEndPos, this));
		Pistache::Rest::Routes::Post(router, "/api/save/max/speed", Pistache::Rest::Routes::bind(&CanControllerApi::saveMaxSpeed, this));
		Pistache::Rest::Routes::Post(router, "/api/save/default/speed", Pistache::Rest::Routes::bind(&CanControllerApi::saveDefaultSpeed, this));
		Pistache::Rest::Routes::Post(router, "/api/save/accel", Pistache::Rest::Routes::bind(&CanControllerApi::saveAccel, this));
		Pistache::Rest::Routes::Post(router, "/api/save/decel", Pistache::Rest::Routes::bind(&CanControllerApi::saveDecel, this));
		Pistache::Rest::Routes::Post(router, "/api/save/delta", Pistache::Rest::Routes::bind(&CanControllerApi::saveDelta, this));
		Pistache::Rest::Routes::Post(router, "/api/steps/micro/set", Pistache::Rest::Routes::bind(&CanControllerApi::microSteps, this));
		Pistache::Rest::Routes::Post(router, "/api/steps/turn/set", Pistache::Rest::Routes::bind(&CanControllerApi::turnSteps, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/1", Pistache::Rest::Routes::bind(&CanControllerApi::sensor1Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/2", Pistache::Rest::Routes::bind(&CanControllerApi::sensor2Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/3", Pistache::Rest::Routes::bind(&CanControllerApi::sensor3Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/4", Pistache::Rest::Routes::bind(&CanControllerApi::sensor4Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/direction/1", Pistache::Rest::Routes::bind(&CanControllerApi::sensor1Dir, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/direction/2", Pistache::Rest::Routes::bind(&CanControllerApi::sensor2Dir, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/direction/3", Pistache::Rest::Routes::bind(&CanControllerApi::sensor3Dir, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/direction/4", Pistache::Rest::Routes::bind(&CanControllerApi::sensor4Dir, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/srvrdy", Pistache::Rest::Routes::bind(&CanControllerApi::SRVRDYPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/inpos", Pistache::Rest::Routes::bind(&CanControllerApi::INPOSPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/fault", Pistache::Rest::Routes::bind(&CanControllerApi::FAULTPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/brake", Pistache::Rest::Routes::bind(&CanControllerApi::BrakePolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/direction", Pistache::Rest::Routes::bind(&CanControllerApi::DirPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/en", Pistache::Rest::Routes::bind(&CanControllerApi::EnPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/al_clr", Pistache::Rest::Routes::bind(&CanControllerApi::Al_CLRPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/al_obrake", Pistache::Rest::Routes::bind(&CanControllerApi::Al_OBrakePolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/al_orezerv", Pistache::Rest::Routes::bind(&CanControllerApi::Al_ORezervPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/encoder/active", Pistache::Rest::Routes::bind(&CanControllerApi::EncoderActive, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/encoder/config", Pistache::Rest::Routes::bind(&CanControllerApi::encoderConfig, this));

		Pistache::Rest::Routes::Get(router, "/health", Pistache::Rest::Routes::bind(&CanControllerApi::health, this));
	}

	void autosender(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t type=obj["numType"].as_int64();
			int64_t ms=obj["numMs"].as_int64();
			controller.buttonAutosender_Click(type,ms);
			BOOST_LOG_TRIVIAL(info) << "buttonAutosender_Click";
			response.send(Pistache::Http::Code::Ok, "Autosender");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonAutosender_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "Autosender failed");
		}
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

	void stop(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonStop_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonStop_Click";
			response.send(Pistache::Http::Code::Ok, "Moving Stop");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonStop_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "Moving Stop failed");
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

	void alarmResetOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
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

	void alarmResetOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
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

	void resetCANStep(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonResetCANStep_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonResetCANStep_Click";
			response.send(Pistache::Http::Code::Ok, "ResetCANStep");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonResetCANStep_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "ResetCANStep failed");
		}
	}

	void driverOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonDriverOn_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonDriverOn_Click";
			response.send(Pistache::Http::Code::Ok, "DriverOn");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonDriverOn_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "DriverOn failed");
		}
	}

	void driverOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonDriverOff_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonDriverOff_Click";
			response.send(Pistache::Http::Code::Ok, "DriverOff");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonDriverOff_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "DriverOff failed");
		}
	}

	void resetLostCounters(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.resetLostCounters_Click();
			BOOST_LOG_TRIVIAL(info) << "resetLostCounters_Click";
			response.send(Pistache::Http::Code::Ok, "resetLostCounters");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "resetLostCounters_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "resetLostCounters failed");
		}
	}
	
	void motorTorque(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonMotorTorque_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonMotorTorque_Click";
			response.send(Pistache::Http::Code::Ok, "motorTorque");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonMotorTorque_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "motorTorque failed");
		}
	}

	void motorSpeed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonMotorSpeed_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonMotorSpeed_Click";
			response.send(Pistache::Http::Code::Ok, "motorSpeed");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonMotorSpeed_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "motorSpeed failed");
		}
	}

	void absolutePositionRotorUint(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonAbsolutePositionRotorUint_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonAbsolutePositionRotorUint_Click";
			response.send(Pistache::Http::Code::Ok, "absolutePositionRotorUint");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonAbsolutePositionRotorUint_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "absolutePositionRotorUint failed");
		}
	}

	void alarmCode(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		try{
			controller.buttonAlarmCode_Click();
			BOOST_LOG_TRIVIAL(info) << "buttonAlarmCode_Click";
			response.send(Pistache::Http::Code::Ok, "alarmCode");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonAlarmCode_Click";
			response.send(Pistache::Http::Code::Internal_Server_Error, "alarmCode failed");
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

	void microSteps(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSteps"].as_int64();
			controller.button_MicroSteps_Click(val);
			BOOST_LOG_TRIVIAL(info) << "button_MicroSteps_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "MicroSteps Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "button_MicroSteps_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "MicroSteps Set failed");
		}
	}

	void turnSteps(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSteps"].as_int64();
			controller.button_StepsTurn_Click(val);
			BOOST_LOG_TRIVIAL(info) << "button_StepsTurn_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "StepsTurn Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "button_StepsTurn_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "StepsTurn Set failed");
		}
	}

	void sensor1Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor1Polarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonSensor1Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor1Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor1Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor1Polarity Set failed");
		}
	}

	void sensor2Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor2Polarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonSensor2Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor2Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor2Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor2Polarity Set failed");
		}
	}

	void sensor3Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor3Polarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonSensor3Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor3Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor3Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor3Polarity Set failed");
		}
	}

	void sensor4Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor4Polarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonSensor4Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor4Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor4Polarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor4Polarity Set failed");
		}
	}

	void sensor1Dir(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor1Dir_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonSensor1Dir_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor1Dir Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor1Dir_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor1Dir Set failed");
		}
	}

	void sensor2Dir(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor2Dir_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonSensor2Dir_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor2Dir Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor2Dir_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor2Dir Set failed");
		}
	}

	void sensor3Dir(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor3Dir_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonSensor3Dir_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor3Dir Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor3Dir_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor3Dir Set failed");
		}
	}

	void sensor4Dir(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor4Dir_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonSensor4Dir_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor4Dir Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSensor4Dir_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor4Dir Set failed");
		}
	}

	void SRVRDYPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSRVRDYPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonSRVRDYPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "SRVRDYPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonSRVRDYPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "SRVRDYPolarity Set failed");
		}
	}

	void INPOSPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonINPOSPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonINPOSPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "INPOSPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonINPOSPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "INPOSPolarity Set failed");
		}
	}
	
	void FAULTPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonFAULTPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonFAULTPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "FAULTPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonFAULTPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "FAULTPolarity Set failed");
		}
	}
	
	void BrakePolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonBrakePolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonBrakePolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "BrakePolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonBrakePolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "BrakePolarity Set failed");
		}
	}

	void DirPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonDirPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonDirPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "DirPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonDirPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "DirPolarity Set failed");
		}
	}

	void EnPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonEnPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonEnPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "EnPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonEnPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "EnPolarity Set failed");
		}
	}

	void Al_CLRPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonAl_CLRPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonAl_CLRPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Al_CLRPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonAl_CLRPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Al_CLRPolarity Set failed");
		}
	}

	void Al_OBrakePolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonAl_OBrakePolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonAl_OBrakePolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Al_OBrakePolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonAl_OBrakePolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Al_OBrakePolarity Set failed");
		}
	}

	void Al_ORezervPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonAl_ORezervPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << "buttonAl_ORezervPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Al_ORezervPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonAl_ORezervPolarity_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Al_ORezervPolarity Set failed");
		}
	}

	void EncoderActive(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			bool val = static_cast<bool>(obj["statusActive"].as_bool());
			controller.setEncoderActive(val);
			BOOST_LOG_TRIVIAL(info) << "setEncoderActive" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "setEncoderActive Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "setEncoderActive" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "setEncoderActive Set failed");
		}
	}

	void encoderConfig(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controller_mutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t polarity = obj["numPolarity"].as_int64();
			int64_t delta = obj["numDelta"].as_int64();
			int64_t turnData = obj["numTurnData"].as_int64();
			controller.buttonEncoderConfig_Click(polarity,delta,turnData);
			BOOST_LOG_TRIVIAL(info) << "buttonEncoderConfig_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "encoderConfig Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << "buttonEncoderConfig_Click" << " JSON: " << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "encoderConfig Set failed");
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