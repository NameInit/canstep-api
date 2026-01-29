#pragma once

#include <mqtt/async_client.h>
#include <boost/json.hpp>
#include <boost/log/trivial.hpp>
#include <memory>
#include <mutex>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <thread>

#include "CanController.h"

namespace json = boost::json;

static const std::string TOPIC_ROOT = "cancontroller";
static const std::string TOPIC_CMD_ROOT = TOPIC_ROOT + "/command/";
static const std::string TOPIC_RESPONSE = TOPIC_ROOT + "/response";

class MqttApiServer final : public virtual mqtt::callback, public virtual mqtt::iaction_listener {
private:
    CanController& controller;
    std::mutex controllerMutex;
    mqtt::async_client client;
    mqtt::connect_options connOpts;

    template<typename T>
    T get_json_value(const json::object& obj, const std::string& key, T default_val) {
        if (obj.contains(key)) {
            try {
                return json::value_to<T>(obj.at(key));
            } catch (const std::exception& e) {
                BOOST_LOG_TRIVIAL(error) << "JSON conversion error for key '" << key << "': " << e.what();
                return default_val;
            }
        }
        return default_val;
    }

    void publishResponse(const std::string& cmd, bool success, const std::string& message, const std::string& error = "") {
        try {
            json::object response;
            response["command"] = cmd;
            response["success"] = success;
            response["message"] = message;
            
            if (!error.empty()) {
                response["error"] = error;
            }
            
            std::string payload = json::serialize(response);

            mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC_RESPONSE, payload);
            pubmsg->set_qos(1);
            client.publish(pubmsg);
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "MQTT Publish Error: " << e.what();
        }
    }

    void on_failure(const mqtt::token& tok) override {
        BOOST_LOG_TRIVIAL(error) << "MQTT Connection failed";
    }

    void on_success(const mqtt::token& tok) override {
        BOOST_LOG_TRIVIAL(info) << "MQTT Connection success";
    }

    void connection_lost(const std::string& cause) override {
        BOOST_LOG_TRIVIAL(warning) << "MQTT Connection lost: " << cause << ". Reconnecting...";
        try {
            client.connect(connOpts, nullptr, *this);
        } catch (const mqtt::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "MQTT Reconnect failed: " << e.what();
        }
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {}

    void message_arrived(mqtt::const_message_ptr msg) override {
        std::string topic = msg->get_topic();
        std::string payload = msg->to_string();
        
        std::string commandName;
        if (topic.rfind(TOPIC_CMD_ROOT, 0) == 0) { 
             commandName = topic.substr(TOPIC_CMD_ROOT.length());
        } else {
            return; 
        }

        BOOST_LOG_TRIVIAL(info) << "MQTT " << topic << ": " << payload;

        std::lock_guard<std::mutex> lock(controllerMutex);
        
        try {
            json::value jv;
            try {
                jv = json::parse(payload);
            } catch(...) {
                jv = json::object(); 
            }
            
            json::object jobj;
            if(jv.is_object()) {
                jobj = jv.as_object();
            }

            if (commandName == "Autosender") {
                int type = get_json_value<int>(jobj, "type", 0);
                int ms = get_json_value<int>(jobj, "ms", 0);
                controller.buttonAutosender_Click(type, ms);
                publishResponse(commandName, true, "Autosender executed");
            }
            else if (commandName == "Connect") {
                controller.buttonOpenCOM_Click();
                publishResponse(commandName, true, "Connected");
            }
            else if (commandName == "DebugOn") {
                controller.buttonDebugOn_Click();
                publishResponse(commandName, true, "Debug ON");
            }
            else if (commandName == "Board") {
                controller.buttonNumBoard_Click(get_json_value<uint64_t>(jobj, "numBoard", 0));
                publishResponse(commandName, true, "Board Set");
            }
            else if (commandName == "Steps") {
                controller.buttonNumSteps_Click(get_json_value<uint64_t>(jobj, "numSteps", 0));
                publishResponse(commandName, true, "Steps Set");
            }
            else if (commandName == "Speed") {
                controller.buttonSpeed_Click(get_json_value<float>(jobj, "numSpeed", 0));
                publishResponse(commandName, true, "Speed Set");
            }
            else if (commandName == "Accel") {
                controller.buttonAccel_Click(get_json_value<uint64_t>(jobj, "numAccel", 0));
                publishResponse(commandName, true, "Accel Set");
            }
            else if (commandName == "Decel") {
                controller.buttonDecel_Click(get_json_value<uint64_t>(jobj, "numDecel", 0));
                publishResponse(commandName, true, "Decel Set");
            }
            else if (commandName == "Forward") {
                controller.buttonMoveForward_Click();
                publishResponse(commandName, true, "Move Forward");
            }
            else if (commandName == "Backward") {
                controller.buttonMoveBackward_Click();
                publishResponse(commandName, true, "Move Backward");
            }
            else if (commandName == "HomingZero") {
                controller.buttonHomingZero_Click();
                publishResponse(commandName, true, "Homing Zero");
            }
            else if (commandName == "HomingMax") {
                controller.buttonHomingMax_Click();
                publishResponse(commandName, true, "Homing Max");
            }
            else if (commandName == "ResetDRVError") {
                controller.buttonResetDRVError_Click();
                publishResponse(commandName, true, "ResetDRVError");
            }
            else if (commandName == "Stop") {
                controller.buttonStop_Click();
                publishResponse(commandName, true, "Moving Stop");
            }
            else if (commandName == "BrakeOff") {
                controller.buttonBrakeOff_Click();
                publishResponse(commandName, true, "brakeOff");
            }
            else if (commandName == "BrakeOn") {
                controller.buttonBrakeOn_Click();
                publishResponse(commandName, true, "brakeOn");
            }
            else if (commandName == "RezervOff") {
                controller.buttonRezervOff_Click();
                publishResponse(commandName, true, "rezervOff");
            }
            else if (commandName == "RezervOn") {
                controller.buttonRezervOn_Click();
                publishResponse(commandName, true, "rezervOn");
            }
            else if (commandName == "AlarmResetOff") {
                controller.buttonAlarmResetOff_Click();
                publishResponse(commandName, true, "AlarmResetOff");
            }
            else if (commandName == "AlarmResetOn") {
                controller.buttonAlarmResetOn_Click();
                publishResponse(commandName, true, "AlarmResetOn");
            }
            else if (commandName == "CurrentPos") {
                controller.buttonCurrentPositionSet_Click(get_json_value<uint64_t>(jobj, "numPos", 0));
                publishResponse(commandName, true, "CurrentPosition Set");
            }
            else if (commandName == "ResetCANStep") {
                controller.buttonResetCANStep_Click();
                publishResponse(commandName, true, "ResetCANStep");
            }
            else if (commandName == "DriverOn") {
                controller.buttonDriverOn_Click();
                publishResponse(commandName, true, "DriverOn");
            }
            else if (commandName == "DriverOff") {
                controller.buttonDriverOff_Click();
                publishResponse(commandName, true, "DriverOff");
            }
            else if (commandName == "ResetLostCounters") {
                controller.resetLostCounters_Click();
                publishResponse(commandName, true, "resetLostCounters");
            }
            else if (commandName == "MotorTorque") {
                controller.buttonMotorTorque_Click();
                publishResponse(commandName, true, "motorTorque");
            }
            else if (commandName == "MotorSpeed") {
                controller.buttonMotorSpeed_Click();
                publishResponse(commandName, true, "motorSpeed");
            }
            else if (commandName == "AbsolutePositionRotorUint") {
                controller.buttonAbsolutePositionRotorUint_Click();
                publishResponse(commandName, true, "absolutePositionRotorUint");
            }
            else if (commandName == "AlarmCode") {
                controller.buttonAlarmCode_Click();
                publishResponse(commandName, true, "alarmCode");
            }
            // // Save Commands
            else if (commandName == "SaveNumBoard") {
                controller.buttonNumBoardSave_Click(get_json_value<int>(jobj, "numBoard", 0));
                publishResponse(commandName, true, "saveNumBoard Set");
            }
            else if (commandName == "SaveNumGroup") {
                controller.buttonNumGroupSave_Click(get_json_value<int>(jobj, "numGroup", 0));
                publishResponse(commandName, true, "saveNumGroup Set");
            }
            else if (commandName == "SaveStartPos") {
                controller.buttonStartPositionSave_Click(get_json_value<uint64_t>(jobj, "numPos", 0));
                publishResponse(commandName, true, "saveStartPos Set");
            }
            else if (commandName == "SaveEndPos") {
                controller.buttonEndPositionSave_Click(get_json_value<uint64_t>(jobj, "numPos", 0));
                publishResponse(commandName, true, "saveEndPos Set");
            }
            else if (commandName == "SaveMaxSpeed") {
                controller.buttonMaxSpeedSave_Click(get_json_value<uint64_t>(jobj, "numSpeed", 0));
                publishResponse(commandName, true, "saveMaxSpeed Set");
            }
            else if (commandName == "SaveDefaultSpeed") {
                controller.buttonDefaultSpeedSave_Click(get_json_value<uint64_t>(jobj, "numSpeed", 0));
                publishResponse(commandName, true, "saveDefaultSpeed Set");
            }
            else if (commandName == "SaveAccel") {
                controller.buttonAccelSave_Click(get_json_value<uint64_t>(jobj, "numAccel", 0));
                publishResponse(commandName, true, "saveAccel Set");
            }
            else if (commandName == "SaveDecel") {
                controller.buttonDecelSave_Click(get_json_value<int>(jobj, "numDecel", 0));
                publishResponse(commandName, true, "saveDecel Set");
            }
            else if (commandName == "SaveDelta") {
                controller.buttonDeltaSave_Click(get_json_value<int>(jobj, "numDelta", 0));
                publishResponse(commandName, true, "saveDelta Set");
            }
            // Configuration Commands
            else if (commandName == "MicroSteps") {
                controller.button_MicroSteps_Click(get_json_value<int>(jobj, "numSteps", 0));
                publishResponse(commandName, true, "MicroSteps Set");
            }
            else if (commandName == "TurnSteps") {
                controller.button_StepsTurn_Click(get_json_value<int>(jobj, "numSteps", 0));
                publishResponse(commandName, true, "StepsTurn Set");
            }
            // Polarity Commands
            else if (commandName == "Sensor1Polarity") {
                controller.buttonSensor1Polarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Sensor1Polarity Set");
            }
            else if (commandName == "Sensor2Polarity") {
                controller.buttonSensor2Polarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Sensor2Polarity Set");
            }
            else if (commandName == "Sensor3Polarity") {
                controller.buttonSensor3Polarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Sensor3Polarity Set");
            }
            else if (commandName == "Sensor4Polarity") {
                controller.buttonSensor4Polarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Sensor4Polarity Set");
            }
            // Direction Commands
            else if (commandName == "Sensor1Dir") {
                controller.buttonSensor1Dir_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Sensor1Dir Set");
            }
            else if (commandName == "Sensor2Dir") {
                controller.buttonSensor2Dir_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Sensor2Dir Set");
            }
            else if (commandName == "Sensor3Dir") {
                controller.buttonSensor3Dir_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Sensor3Dir Set");
            }
            else if (commandName == "Sensor4Dir") {
                controller.buttonSensor4Dir_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Sensor4Dir Set");
            }
            else if (commandName == "SRVRDYPolarity") {
                controller.buttonSRVRDYPolarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "SRVRDYPolarity Set");
            }
            else if (commandName == "INPOSPolarity") {
                controller.buttonINPOSPolarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "INPOSPolarity Set");
            }
            else if (commandName == "FAULTPolarity") {
                controller.buttonFAULTPolarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "FAULTPolarity Set");
            }
            else if (commandName == "BrakePolarity") {
                controller.buttonBrakePolarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "BrakePolarity Set");
            }
            else if (commandName == "DirPolarity") {
                controller.buttonDirPolarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "DirPolarity Set");
            }
            else if (commandName == "EnPolarity") {
                controller.buttonEnPolarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "EnPolarity Set");
            }
            else if (commandName == "Al_CLRPolarity") {
                controller.buttonAl_CLRPolarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Al_CLRPolarity Set");
            }
            else if (commandName == "Al_OBrakePolarity") {
                controller.buttonAl_OBrakePolarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Al_OBrakePolarity Set");
            }
            else if (commandName == "Al_ORezervPolarity") {
                controller.buttonAl_ORezervPolarity_Click(jobj["statusInverting"].as_string().c_str());
                publishResponse(commandName, true, "Al_ORezervPolarity Set");
            }
            else if (commandName == "EncoderActive") {
                controller.setEncoderActive(get_json_value<bool>(jobj, "statusActive", false));
                publishResponse(commandName, true, "setEncoderActive Set");
            }
            else if (commandName == "EncoderConfig") {
                controller.buttonEncoderConfig_Click(
                    get_json_value<int>(jobj, "numPolarity", 0),
                    get_json_value<int>(jobj, "numDelta", 0),
                    get_json_value<int>(jobj, "numTurnData", 0)
                );
                publishResponse(commandName, true, "encoderConfig Set");
            }
            else if (commandName == "FlashBoot") {
                std::string fname = get_json_value<std::string>(jobj, "filename", "");
                controller.buttonBoot_Click(fname);
                publishResponse(commandName, true, "Flash Started");
            }
            else if (commandName == "FlashTypeBootSet") {
                controller.buttonTypeBootSet_Click(jobj["type"].as_string().c_str());
                publishResponse(commandName, true, "flashTypeBootSet");
            }
            else if (commandName == "FlashTypeBootSave") {
                controller.buttonTypeBootSave_Click(jobj["type"].as_string().c_str());
                publishResponse(commandName, true, "flashTypeBootSave");
            }
            else if (commandName == "Health") {
                publishResponse(commandName, true, "OK");
            }
            else {
                BOOST_LOG_TRIVIAL(error) << "Unknown command: " << commandName;
            }

        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "Error processing command " << commandName << ": " << e.what();
            publishResponse(commandName, false, "Execution failed", e.what());
        }
    }

public:
    MqttApiServer(CanController& controller, const uint16_t port=1883, const std::string& host="127.0.0.1", const std::string& clientId = "CanControllerApi")
        : controller(controller), 
          client("tcp://"+host+":"+std::to_string(port), clientId) {
        
        connOpts.set_keep_alive_interval(20);
        connOpts.set_clean_session(true);
        client.set_callback(*this);
        
        BOOST_LOG_TRIVIAL(info) << "MqttApiServer created on port " << port;
    }

    ~MqttApiServer() {
        shutdownServer();
    }

    void runServer() {
        try {
            BOOST_LOG_TRIVIAL(info) << "Connecting to MQTT Broker...";

            client.connect(connOpts, nullptr, *this)->wait();
            BOOST_LOG_TRIVIAL(info) << "Connection Success via wait()";

            BOOST_LOG_TRIVIAL(info) << "Subscribing to " << TOPIC_CMD_ROOT << "# ...";
            client.subscribe(TOPIC_CMD_ROOT + "#", 1)->wait();
            BOOST_LOG_TRIVIAL(info) << "Subscription Active!";

        } catch (const mqtt::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "MQTT Critical Error in runServer: " << e.what();
        }
    }

    void shutdownServer() {
        try {
            if (client.is_connected()) {
                BOOST_LOG_TRIVIAL(info) << "Disconnecting MQTT...";
                client.disconnect()->wait();
            }
        } catch(const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "Disconnecting MQTT failed: " << e.what();
        }
    }
};