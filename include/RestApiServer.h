#pragma once

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <boost/json.hpp>
#include <boost/log/trivial.hpp>
#include <memory>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <mutex>
#include <filesystem>

#include "CanController.h"

class RestApiServer
{
private:
	Pistache::Rest::Router router;
	Pistache::Address addr;
	std::unique_ptr<Pistache::Http::Endpoint> endpoint;
	CanController& controller;
	std::mutex controllerMutex;
	uint16_t port;

	void setupRoutes(){
		Pistache::Rest::Routes::Post(router, "/api/autosender", Pistache::Rest::Routes::bind(&RestApiServer::autosender, this));
		Pistache::Rest::Routes::Get(router, "/api/connect", Pistache::Rest::Routes::bind(&RestApiServer::connect, this));
		Pistache::Rest::Routes::Get(router, "/api/debug/on", Pistache::Rest::Routes::bind(&RestApiServer::debugOn, this));
		Pistache::Rest::Routes::Post(router, "/api/board/set", Pistache::Rest::Routes::bind(&RestApiServer::board, this));
		Pistache::Rest::Routes::Post(router, "/api/steps/set", Pistache::Rest::Routes::bind(&RestApiServer::steps, this));
		Pistache::Rest::Routes::Post(router, "/api/speed/set", Pistache::Rest::Routes::bind(&RestApiServer::speed, this));
		Pistache::Rest::Routes::Post(router, "/api/accel/set", Pistache::Rest::Routes::bind(&RestApiServer::accel, this));
		Pistache::Rest::Routes::Post(router, "/api/decel/set", Pistache::Rest::Routes::bind(&RestApiServer::decel, this));
		Pistache::Rest::Routes::Get(router, "/api/move/forward", Pistache::Rest::Routes::bind(&RestApiServer::forward, this));
		Pistache::Rest::Routes::Get(router, "/api/move/backward", Pistache::Rest::Routes::bind(&RestApiServer::backward, this));
		Pistache::Rest::Routes::Get(router, "/api/homing/zero", Pistache::Rest::Routes::bind(&RestApiServer::homingZero, this));
		Pistache::Rest::Routes::Get(router, "/api/homing/max", Pistache::Rest::Routes::bind(&RestApiServer::homingMax, this));
		Pistache::Rest::Routes::Get(router, "/api/reset/driver/error", Pistache::Rest::Routes::bind(&RestApiServer::resetDRVError, this));
		Pistache::Rest::Routes::Get(router, "/api/move/stop", Pistache::Rest::Routes::bind(&RestApiServer::stop, this));
		Pistache::Rest::Routes::Get(router, "/api/brake/off", Pistache::Rest::Routes::bind(&RestApiServer::brakeOff, this));
		Pistache::Rest::Routes::Get(router, "/api/brake/on", Pistache::Rest::Routes::bind(&RestApiServer::brakeOn, this));
		Pistache::Rest::Routes::Get(router, "/api/rezerv/off", Pistache::Rest::Routes::bind(&RestApiServer::rezervOff, this));
		Pistache::Rest::Routes::Get(router, "/api/rezerv/on", Pistache::Rest::Routes::bind(&RestApiServer::rezervOn, this));
		Pistache::Rest::Routes::Get(router, "/api/alarm/reset/off", Pistache::Rest::Routes::bind(&RestApiServer::alarmResetOff, this));
		Pistache::Rest::Routes::Get(router, "/api/alarm/reset/on", Pistache::Rest::Routes::bind(&RestApiServer::alarmResetOn, this));
		Pistache::Rest::Routes::Post(router, "/api/current/pos", Pistache::Rest::Routes::bind(&RestApiServer::currentPos, this));
		Pistache::Rest::Routes::Get(router, "/api/reset/canstep", Pistache::Rest::Routes::bind(&RestApiServer::resetCANStep, this));
		Pistache::Rest::Routes::Get(router, "/api/driver/on", Pistache::Rest::Routes::bind(&RestApiServer::driverOn, this));
		Pistache::Rest::Routes::Get(router, "/api/driver/off", Pistache::Rest::Routes::bind(&RestApiServer::driverOff, this));
		Pistache::Rest::Routes::Get(router, "/api/lostcounters/reset", Pistache::Rest::Routes::bind(&RestApiServer::resetLostCounters, this));
		Pistache::Rest::Routes::Get(router, "/api/motor/torque", Pistache::Rest::Routes::bind(&RestApiServer::motorTorque, this));
		Pistache::Rest::Routes::Get(router, "/api/motor/speed", Pistache::Rest::Routes::bind(&RestApiServer::motorSpeed, this));
		Pistache::Rest::Routes::Get(router, "/api/pos/absolute", Pistache::Rest::Routes::bind(&RestApiServer::absolutePositionRotorUint, this));
		Pistache::Rest::Routes::Get(router, "/api/alarm/code", Pistache::Rest::Routes::bind(&RestApiServer::alarmCode, this));
		Pistache::Rest::Routes::Post(router, "/api/save/board", Pistache::Rest::Routes::bind(&RestApiServer::saveNumBoard, this));
		Pistache::Rest::Routes::Post(router, "/api/save/group", Pistache::Rest::Routes::bind(&RestApiServer::saveNumGroup, this));
		Pistache::Rest::Routes::Post(router, "/api/save/start/pos", Pistache::Rest::Routes::bind(&RestApiServer::saveStartPos, this));
		Pistache::Rest::Routes::Post(router, "/api/save/end/pos", Pistache::Rest::Routes::bind(&RestApiServer::saveEndPos, this));
		Pistache::Rest::Routes::Post(router, "/api/save/max/speed", Pistache::Rest::Routes::bind(&RestApiServer::saveMaxSpeed, this));
		Pistache::Rest::Routes::Post(router, "/api/save/default/speed", Pistache::Rest::Routes::bind(&RestApiServer::saveDefaultSpeed, this));
		Pistache::Rest::Routes::Post(router, "/api/save/accel", Pistache::Rest::Routes::bind(&RestApiServer::saveAccel, this));
		Pistache::Rest::Routes::Post(router, "/api/save/decel", Pistache::Rest::Routes::bind(&RestApiServer::saveDecel, this));
		Pistache::Rest::Routes::Post(router, "/api/save/delta", Pistache::Rest::Routes::bind(&RestApiServer::saveDelta, this));
		Pistache::Rest::Routes::Post(router, "/api/steps/micro/set", Pistache::Rest::Routes::bind(&RestApiServer::microSteps, this));
		Pistache::Rest::Routes::Post(router, "/api/steps/turn/set", Pistache::Rest::Routes::bind(&RestApiServer::turnSteps, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/1", Pistache::Rest::Routes::bind(&RestApiServer::sensor1Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/2", Pistache::Rest::Routes::bind(&RestApiServer::sensor2Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/3", Pistache::Rest::Routes::bind(&RestApiServer::sensor3Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/4", Pistache::Rest::Routes::bind(&RestApiServer::sensor4Polarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/direction/1", Pistache::Rest::Routes::bind(&RestApiServer::sensor1Dir, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/direction/2", Pistache::Rest::Routes::bind(&RestApiServer::sensor2Dir, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/direction/3", Pistache::Rest::Routes::bind(&RestApiServer::sensor3Dir, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/direction/4", Pistache::Rest::Routes::bind(&RestApiServer::sensor4Dir, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/srvrdy", Pistache::Rest::Routes::bind(&RestApiServer::SRVRDYPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/inpos", Pistache::Rest::Routes::bind(&RestApiServer::INPOSPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/fault", Pistache::Rest::Routes::bind(&RestApiServer::FAULTPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/brake", Pistache::Rest::Routes::bind(&RestApiServer::BrakePolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/direction", Pistache::Rest::Routes::bind(&RestApiServer::DirPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/en", Pistache::Rest::Routes::bind(&RestApiServer::EnPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/al_clr", Pistache::Rest::Routes::bind(&RestApiServer::Al_CLRPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/al_obrake", Pistache::Rest::Routes::bind(&RestApiServer::Al_OBrakePolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/polarity/al_orezerv", Pistache::Rest::Routes::bind(&RestApiServer::Al_ORezervPolarity, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/encoder/active", Pistache::Rest::Routes::bind(&RestApiServer::EncoderActive, this));
		Pistache::Rest::Routes::Post(router, "/api/sensor/encoder/config", Pistache::Rest::Routes::bind(&RestApiServer::encoderConfig, this));
		Pistache::Rest::Routes::Post(router, "/api/flash/run", Pistache::Rest::Routes::bind(&RestApiServer::flashBoot, this));
		Pistache::Rest::Routes::Post(router, "/api/flash/type/set", Pistache::Rest::Routes::bind(&RestApiServer::flashTypeBootSet, this));
		Pistache::Rest::Routes::Post(router, "/api/flash/type/save", Pistache::Rest::Routes::bind(&RestApiServer::flashTypeBootSave, this));

		Pistache::Rest::Routes::Get(router, "/health", Pistache::Rest::Routes::bind(&RestApiServer::health, this));
	}

	void autosender(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t type=obj["numType"].as_int64();
			int64_t ms=obj["numMs"].as_int64();
			controller.buttonAutosender_Click(type,ms);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Autosender");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Autosender failed");
		}
	}

	void connect(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonOpenCOM_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "Connected");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "Connection failed");
		}
	}

	void debugOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonDebugOn_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "Debug ON");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "Connection failed");
		}
	}

	void board(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numBoard"].as_int64();
			controller.buttonNumBoard_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Board Set");
		} catch (const std::exception& e){ 
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Board Set failed");
		}
	}

	void steps(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSteps"].as_int64();
			controller.buttonNumSteps_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Steps Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Steps Set failed");
		}
	}

	void speed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSpeed"].as_int64();
			controller.buttonSpeed_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Speed Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Speed Set failed");
		}
	}

	void accel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numAccel"].as_int64();
			controller.buttonAccel_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Acceleration Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Acceleration Set failed");
		}
	}

	void decel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numDecel"].as_int64();
			controller.buttonDecel_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Deceleration Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Deceleration Set failed");
		}
	}

	void forward(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonMoveForward_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "Moving Borward");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "Moving Forward failed");
		}
	}

	void backward(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonMoveBackward_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "Moving Backward");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "Moving Backward failed");
		}
	}

	void homingZero(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonHomingZero_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "Homig Zero");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "Homig Zero failed");
		}
	}

	void homingMax(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonHomingMax_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "Homig Max");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "Homig Max failed");
		}
	}

	void resetDRVError(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonResetDRVError_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "ResetDRVError");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "ResetDRVError failed");
		}
	}

	void stop(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonStop_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "Moving Stop");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "Moving Stop failed");
		}
	}

	void brakeOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonBrakeOff_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "brakeOff");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "brakeOff failed");
		}
	}

	void brakeOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonBrakeOn_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "brakeOn");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "brakeOn failed");
		}
	}

	void rezervOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonRezervOff_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "rezervOff");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "rezervOff failed");
		}
	}

	void rezervOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonRezervOn_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "rezervOn");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "rezervOn failed");
		}
	}

	void alarmResetOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonAlarmResetOff_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "AlarmResetOff");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "AlarmResetOff failed");
		}
	}

	void alarmResetOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonAlarmResetOn_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "AlarmResetOn");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "AlarmResetOn failed");
		}
	}

	void currentPos(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numPos"].as_int64();
			controller.buttonCurrentPositionSet_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "CurrentPosition Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "CurrentPosition Set failed");
		}
	}

	void resetCANStep(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonResetCANStep_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "ResetCANStep");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "ResetCANStep failed");
		}
	}

	void driverOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonDriverOn_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "DriverOn");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "DriverOn failed");
		}
	}

	void driverOff(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonDriverOff_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "DriverOff");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "DriverOff failed");
		}
	}

	void resetLostCounters(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.resetLostCounters_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "resetLostCounters");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "resetLostCounters failed");
		}
	}
	
	void motorTorque(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonMotorTorque_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "motorTorque");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "motorTorque failed");
		}
	}

	void motorSpeed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonMotorSpeed_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "motorSpeed");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "motorSpeed failed");
		}
	}

	void absolutePositionRotorUint(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonAbsolutePositionRotorUint_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "absolutePositionRotorUint");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "absolutePositionRotorUint failed");
		}
	}

	void alarmCode(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		try{
			controller.buttonAlarmCode_Click();
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Ok, "alarmCode");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource();
			response.send(Pistache::Http::Code::Internal_Server_Error, "alarmCode failed");
		}
	}

	void saveNumBoard(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numBoard"].as_int64();
			controller.buttonNumBoardSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveNumBoard Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveNumBoard Set failed");
		}
	}

	void saveNumGroup(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numGroup"].as_int64();
			controller.buttonNumGroupSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveNumGroup Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveNumGroup Set failed");
		}
	}

	void saveStartPos(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numPos"].as_int64();
			controller.buttonStartPositionSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveStartPos Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveStartPos Set failed");
		}
	}

	void saveEndPos(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numPos"].as_int64();
			controller.buttonEndPositionSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveEndPos Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveEndPos Set failed");
		}
	}

	void saveMaxSpeed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSpeed"].as_int64();
			controller.buttonMaxSpeedSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveMaxSpeed Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveMaxSpeed Set failed");
		}
	}

	void saveDefaultSpeed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSpeed"].as_int64();
			controller.buttonDefaultSpeedSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveDefaultSpeed Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveDefaultSpeed Set failed");
		}
	}

	void saveAccel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numAccel"].as_int64();
			controller.buttonAccelSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveAccel Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveAccel Set failed");
		}
	}

	void saveDecel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numDecel"].as_int64();
			controller.buttonDecelSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveDecel Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveDecel Set failed");
		}
	}

	void saveDelta(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numDelta"].as_int64();
			controller.buttonDeltaSave_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "saveDelta Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "saveDelta Set failed");
		}
	}

	void microSteps(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSteps"].as_int64();
			controller.button_MicroSteps_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "MicroSteps Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "MicroSteps Set failed");
		}
	}

	void turnSteps(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t val=obj["numSteps"].as_int64();
			controller.button_StepsTurn_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "StepsTurn Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "StepsTurn Set failed");
		}
	}

	void sensor1Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor1Polarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor1Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor1Polarity Set failed");
		}
	}

	void sensor2Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor2Polarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor2Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor2Polarity Set failed");
		}
	}

	void sensor3Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor3Polarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor3Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor3Polarity Set failed");
		}
	}

	void sensor4Polarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor4Polarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor4Polarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor4Polarity Set failed");
		}
	}

	void sensor1Dir(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor1Dir_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor1Dir Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor1Dir Set failed");
		}
	}

	void sensor2Dir(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor2Dir_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor2Dir Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor2Dir Set failed");
		}
	}

	void sensor3Dir(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor3Dir_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor3Dir Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor3Dir Set failed");
		}
	}

	void sensor4Dir(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSensor4Dir_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Sensor4Dir Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Sensor4Dir Set failed");
		}
	}

	void SRVRDYPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonSRVRDYPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "SRVRDYPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "SRVRDYPolarity Set failed");
		}
	}

	void INPOSPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonINPOSPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "INPOSPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "INPOSPolarity Set failed");
		}
	}
	
	void FAULTPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonFAULTPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "FAULTPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "FAULTPolarity Set failed");
		}
	}
	
	void BrakePolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonBrakePolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "BrakePolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "BrakePolarity Set failed");
		}
	}

	void DirPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonDirPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "DirPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "DirPolarity Set failed");
		}
	}

	void EnPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonEnPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "EnPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "EnPolarity Set failed");
		}
	}

	void Al_CLRPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonAl_CLRPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Al_CLRPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Al_CLRPolarity Set failed");
		}
	}

	void Al_OBrakePolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonAl_OBrakePolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Al_OBrakePolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Al_OBrakePolarity Set failed");
		}
	}

	void Al_ORezervPolarity(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string val = static_cast<std::string>(obj["statusInverting"].as_string());
			controller.buttonAl_ORezervPolarity_Click(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Al_ORezervPolarity Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Al_ORezervPolarity Set failed");
		}
	}

	void EncoderActive(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			bool val = static_cast<bool>(obj["statusActive"].as_bool());
			controller.setEncoderActive(val);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "setEncoderActive Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "setEncoderActive Set failed");
		}
	}

	void encoderConfig(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			int64_t polarity = obj["numPolarity"].as_int64();
			int64_t delta = obj["numDelta"].as_int64();
			int64_t turnData = obj["numTurnData"].as_int64();
			controller.buttonEncoderConfig_Click(polarity,delta,turnData);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "encoderConfig Set");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "encoderConfig Set failed");
		}
	}

	void flashBoot(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string filename = static_cast<std::string>(obj["filename"].as_string());
			controller.buttonBoot_Click(filename);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "Flash");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "Flash failed");
		}
	}

	void flashTypeBootSet(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string type = static_cast<std::string>(obj["type"].as_string());
			controller.buttonTypeBootSet_Click(type);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "flashTypeBootSet");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "flashTypeBootSet failed");
		}
	}

	void flashTypeBootSave(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		std::lock_guard<std::mutex> lock(controllerMutex);
		boost::json::value json_data = boost::json::parse(request.body());
		try{
			boost::json::object obj=json_data.as_object();
			std::string type = static_cast<std::string>(obj["type"].as_string());
			controller.buttonTypeBootSave_Click(type);
			BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Ok, "flashTypeBootSave");
		} catch (const std::exception& e){
			BOOST_LOG_TRIVIAL(error) << request.method() << ' ' << request.resource() << ' ' << boost::json::serialize(json_data);
			response.send(Pistache::Http::Code::Internal_Server_Error, "flashTypeBootSave failed");
		}
	}

	void health(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
		BOOST_LOG_TRIVIAL(info) << request.method() << ' ' << request.resource();
		response.send(Pistache::Http::Code::Ok, "OK");
	}

public:
	RestApiServer(CanController& controller, const uint16_t numPort=8080, const uint8_t numThread=2, const std::string host="127.0.0.1")
	: addr(host, Pistache::Port(numPort))
	, controller(controller)
	, port(numPort)
	{
		Pistache::Http::Endpoint::Options opts = Pistache::Http::Endpoint::options().threads(numThread);
		endpoint = std::make_unique<Pistache::Http::Endpoint>(addr);
		setupRoutes();
		endpoint->init(opts);
		endpoint->setHandler(router.handler());
		BOOST_LOG_TRIVIAL(info) << "RestApiServer created on port " << numPort;
		return ;
	}
	~RestApiServer(){
		BOOST_LOG_TRIVIAL(info) << "RestApiServer destroyed";
		return ;
	}
	
	void runServer(){
		BOOST_LOG_TRIVIAL(info) << "Run RestApiServer on port " << port;
		endpoint->serve();
	}

	void shutdownServer(){
		BOOST_LOG_TRIVIAL(info) << "Shutdown RestApiServer";
		endpoint->shutdown();
	}
};