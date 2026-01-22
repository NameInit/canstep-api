#pragma once

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <memory>
#include <mutex>
#include <iostream>
#include <chrono>


#include "CanController.h"
#include "can_controller.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using cancontroller::CanControllerService;
using cancontroller::AutosenderRequest;
using cancontroller::BoardRequest;
using cancontroller::StepsRequest;
using cancontroller::SpeedRequest;
using cancontroller::AccelRequest;
using cancontroller::DecelRequest;
using cancontroller::PositionRequest;
using cancontroller::GroupRequest;
using cancontroller::DeltaRequest;
using cancontroller::SensorPolarityRequest;
using cancontroller::EncoderActiveRequest;
using cancontroller::EncoderConfigRequest;
using cancontroller::FlashBootRequest;
using cancontroller::FlashTypeRequest;
using cancontroller::CommandResponse;
using cancontroller::HealthResponse;
using cancontroller::Empty;

class GrpcApiServer final : public CanControllerService::Service {
private:
    CanController& controller;
    std::mutex controllerMutex;
    uint16_t port;
    std::unique_ptr<Server> server;
    
public:
    GrpcApiServer(CanController& controller, uint16_t grpcPort = 50051)
        : controller(controller), port(grpcPort) {
        BOOST_LOG_TRIVIAL(info) << "GrpcApiServer created on port " << grpcPort;
    }
    
    ~GrpcApiServer() {
        shutdownServer();
        BOOST_LOG_TRIVIAL(info) << "GrpcApiServer destroyed";
    }
    
    Status Autosender(ServerContext* context, const AutosenderRequest* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonAutosender_Click(request->type(), request->ms());
            BOOST_LOG_TRIVIAL(info) << "gRPC Autosender: type=" << request->type() 
                                   << ", ms=" << request->ms();
            response->set_success(true);
            response->set_message("Autosender executed");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Autosender failed: " << e.what();
            response->set_success(false);
            response->set_message("Autosender failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Connect(ServerContext* context, const Empty* request,
                   CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonOpenCOM_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC Connect";
            response->set_success(true);
            response->set_message("Connected");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Connect failed: " << e.what();
            response->set_success(false);
            response->set_message("Connection failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status DebugOn(ServerContext* context, const Empty* request,
                   CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonDebugOn_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC DebugOn";
            response->set_success(true);
            response->set_message("Debug ON");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC DebugOn failed: " << e.what();
            response->set_success(false);
            response->set_message("Debug ON failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Board(ServerContext* context, const BoardRequest* request,
                 CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonNumBoard_Click(request->numboard());
            BOOST_LOG_TRIVIAL(info) << "gRPC Board: " << request->numboard();
            response->set_success(true);
            response->set_message("Board Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Board failed: " << e.what();
            response->set_success(false);
            response->set_message("Board Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Steps(ServerContext* context, const StepsRequest* request,
                 CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonNumSteps_Click(request->numsteps());
            BOOST_LOG_TRIVIAL(info) << "gRPC Steps: " << request->numsteps();
            response->set_success(true);
            response->set_message("Steps Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Steps failed: " << e.what();
            response->set_success(false);
            response->set_message("Steps Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Speed(ServerContext* context, const SpeedRequest* request,
                 CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonSpeed_Click(request->numspeed());
            BOOST_LOG_TRIVIAL(info) << "gRPC Speed: " << request->numspeed();
            response->set_success(true);
            response->set_message("Speed Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Speed failed: " << e.what();
            response->set_success(false);
            response->set_message("Speed Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Accel(ServerContext* context, const AccelRequest* request,
                 CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonAccel_Click(request->numaccel());
            BOOST_LOG_TRIVIAL(info) << "gRPC Accel: " << request->numaccel();
            response->set_success(true);
            response->set_message("Acceleration Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Accel failed: " << e.what();
            response->set_success(false);
            response->set_message("Acceleration Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Decel(ServerContext* context, const DecelRequest* request,
                 CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonDecel_Click(request->numdecel());
            BOOST_LOG_TRIVIAL(info) << "gRPC Decel: " << request->numdecel();
            response->set_success(true);
            response->set_message("Deceleration Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Decel failed: " << e.what();
            response->set_success(false);
            response->set_message("Deceleration Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Forward(ServerContext* context, const Empty* request,
                   CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonMoveForward_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC Forward";
            response->set_success(true);
            response->set_message("Moving Forward");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Forward failed: " << e.what();
            response->set_success(false);
            response->set_message("Moving Forward failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Backward(ServerContext* context, const Empty* request,
                    CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonMoveBackward_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC Backward";
            response->set_success(true);
            response->set_message("Moving Backward");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Backward failed: " << e.what();
            response->set_success(false);
            response->set_message("Moving Backward failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status HomingZero(ServerContext* context, const Empty* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonHomingZero_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC HomingZero";
            response->set_success(true);
            response->set_message("Homing Zero");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC HomingZero failed: " << e.what();
            response->set_success(false);
            response->set_message("Homing Zero failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status HomingMax(ServerContext* context, const Empty* request,
                     CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonHomingMax_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC HomingMax";
            response->set_success(true);
            response->set_message("Homing Max");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC HomingMax failed: " << e.what();
            response->set_success(false);
            response->set_message("Homing Max failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status ResetDRVError(ServerContext* context, const Empty* request,
                         CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonResetDRVError_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC ResetDRVError";
            response->set_success(true);
            response->set_message("ResetDRVError");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC ResetDRVError failed: " << e.what();
            response->set_success(false);
            response->set_message("ResetDRVError failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Stop(ServerContext* context, const Empty* request,
                CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonStop_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC Stop";
            response->set_success(true);
            response->set_message("Moving Stop");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Stop failed: " << e.what();
            response->set_success(false);
            response->set_message("Moving Stop failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status BrakeOff(ServerContext* context, const Empty* request,
                    CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonBrakeOff_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC BrakeOff";
            response->set_success(true);
            response->set_message("brakeOff");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC BrakeOff failed: " << e.what();
            response->set_success(false);
            response->set_message("brakeOff failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status BrakeOn(ServerContext* context, const Empty* request,
                   CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonBrakeOn_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC BrakeOn";
            response->set_success(true);
            response->set_message("brakeOn");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC BrakeOn failed: " << e.what();
            response->set_success(false);
            response->set_message("brakeOn failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status RezervOff(ServerContext* context, const Empty* request,
                     CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonRezervOff_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC RezervOff";
            response->set_success(true);
            response->set_message("rezervOff");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC RezervOff failed: " << e.what();
            response->set_success(false);
            response->set_message("rezervOff failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status RezervOn(ServerContext* context, const Empty* request,
                    CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonRezervOn_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC RezervOn";
            response->set_success(true);
            response->set_message("rezervOn");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC RezervOn failed: " << e.what();
            response->set_success(false);
            response->set_message("rezervOn failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status AlarmResetOff(ServerContext* context, const Empty* request,
                         CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonAlarmResetOff_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC AlarmResetOff";
            response->set_success(true);
            response->set_message("AlarmResetOff");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC AlarmResetOff failed: " << e.what();
            response->set_success(false);
            response->set_message("AlarmResetOff failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status AlarmResetOn(ServerContext* context, const Empty* request,
                        CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonAlarmResetOn_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC AlarmResetOn";
            response->set_success(true);
            response->set_message("AlarmResetOn");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC AlarmResetOn failed: " << e.what();
            response->set_success(false);
            response->set_message("AlarmResetOn failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status CurrentPos(ServerContext* context, const PositionRequest* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonCurrentPositionSet_Click(request->numpos());
            BOOST_LOG_TRIVIAL(info) << "gRPC CurrentPos: " << request->numpos();
            response->set_success(true);
            response->set_message("CurrentPosition Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC CurrentPos failed: " << e.what();
            response->set_success(false);
            response->set_message("CurrentPosition Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status ResetCANStep(ServerContext* context, const Empty* request,
                        CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonResetCANStep_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC ResetCANStep";
            response->set_success(true);
            response->set_message("ResetCANStep");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC ResetCANStep failed: " << e.what();
            response->set_success(false);
            response->set_message("ResetCANStep failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status DriverOn(ServerContext* context, const Empty* request,
                    CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonDriverOn_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC DriverOn";
            response->set_success(true);
            response->set_message("DriverOn");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC DriverOn failed: " << e.what();
            response->set_success(false);
            response->set_message("DriverOn failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status DriverOff(ServerContext* context, const Empty* request,
                     CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonDriverOff_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC DriverOff";
            response->set_success(true);
            response->set_message("DriverOff");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC DriverOff failed: " << e.what();
            response->set_success(false);
            response->set_message("DriverOff failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status ResetLostCounters(ServerContext* context, const Empty* request,
                             CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.resetLostCounters_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC ResetLostCounters";
            response->set_success(true);
            response->set_message("resetLostCounters");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC ResetLostCounters failed: " << e.what();
            response->set_success(false);
            response->set_message("resetLostCounters failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status MotorTorque(ServerContext* context, const Empty* request,
                       CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonMotorTorque_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC MotorTorque";
            response->set_success(true);
            response->set_message("motorTorque");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC MotorTorque failed: " << e.what();
            response->set_success(false);
            response->set_message("motorTorque failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status MotorSpeed(ServerContext* context, const Empty* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonMotorSpeed_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC MotorSpeed";
            response->set_success(true);
            response->set_message("motorSpeed");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC MotorSpeed failed: " << e.what();
            response->set_success(false);
            response->set_message("motorSpeed failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status AbsolutePositionRotorUint(ServerContext* context, const Empty* request,
                                     CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonAbsolutePositionRotorUint_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC AbsolutePositionRotorUint";
            response->set_success(true);
            response->set_message("absolutePositionRotorUint");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC AbsolutePositionRotorUint failed: " << e.what();
            response->set_success(false);
            response->set_message("absolutePositionRotorUint failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status AlarmCode(ServerContext* context, const Empty* request,
                     CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonAlarmCode_Click();
            BOOST_LOG_TRIVIAL(info) << "gRPC AlarmCode";
            response->set_success(true);
            response->set_message("alarmCode");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC AlarmCode failed: " << e.what();
            response->set_success(false);
            response->set_message("alarmCode failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status SaveNumBoard(ServerContext* context, const BoardRequest* request,
                        CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonNumBoardSave_Click(request->numboard());
            BOOST_LOG_TRIVIAL(info) << "gRPC SaveNumBoard: " << request->numboard();
            response->set_success(true);
            response->set_message("saveNumBoard Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC SaveNumBoard failed: " << e.what();
            response->set_success(false);
            response->set_message("saveNumBoard Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status SaveNumGroup(ServerContext* context, const GroupRequest* request,
                        CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonNumGroupSave_Click(request->numgroup());
            BOOST_LOG_TRIVIAL(info) << "gRPC SaveNumGroup: " << request->numgroup();
            response->set_success(true);
            response->set_message("saveNumGroup Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC SaveNumGroup failed: " << e.what();
            response->set_success(false);
            response->set_message("saveNumGroup Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status SaveStartPos(ServerContext* context, const PositionRequest* request,
                        CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonStartPositionSave_Click(request->numpos());
            BOOST_LOG_TRIVIAL(info) << "gRPC SaveStartPos: " << request->numpos();
            response->set_success(true);
            response->set_message("saveStartPos Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC SaveStartPos failed: " << e.what();
            response->set_success(false);
            response->set_message("saveStartPos Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status SaveEndPos(ServerContext* context, const PositionRequest* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonEndPositionSave_Click(request->numpos());
            BOOST_LOG_TRIVIAL(info) << "gRPC SaveEndPos: " << request->numpos();
            response->set_success(true);
            response->set_message("saveEndPos Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC SaveEndPos failed: " << e.what();
            response->set_success(false);
            response->set_message("saveEndPos Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status SaveMaxSpeed(ServerContext* context, const SpeedRequest* request,
                        CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonMaxSpeedSave_Click(request->numspeed());
            BOOST_LOG_TRIVIAL(info) << "gRPC SaveMaxSpeed: " << request->numspeed();
            response->set_success(true);
            response->set_message("saveMaxSpeed Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC SaveMaxSpeed failed: " << e.what();
            response->set_success(false);
            response->set_message("saveMaxSpeed Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status SaveDefaultSpeed(ServerContext* context, const SpeedRequest* request,
                            CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonDefaultSpeedSave_Click(request->numspeed());
            BOOST_LOG_TRIVIAL(info) << "gRPC SaveDefaultSpeed: " << request->numspeed();
            response->set_success(true);
            response->set_message("saveDefaultSpeed Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC SaveDefaultSpeed failed: " << e.what();
            response->set_success(false);
            response->set_message("saveDefaultSpeed Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status SaveAccel(ServerContext* context, const AccelRequest* request,
                     CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonAccelSave_Click(request->numaccel());
            BOOST_LOG_TRIVIAL(info) << "gRPC SaveAccel: " << request->numaccel();
            response->set_success(true);
            response->set_message("saveAccel Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC SaveAccel failed: " << e.what();
            response->set_success(false);
            response->set_message("saveAccel Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status SaveDecel(ServerContext* context, const DecelRequest* request,
                     CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonDecelSave_Click(request->numdecel());
            BOOST_LOG_TRIVIAL(info) << "gRPC SaveDecel: " << request->numdecel();
            response->set_success(true);
            response->set_message("saveDecel Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC SaveDecel failed: " << e.what();
            response->set_success(false);
            response->set_message("saveDecel Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status SaveDelta(ServerContext* context, const DeltaRequest* request,
                     CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonDeltaSave_Click(request->numdelta());
            BOOST_LOG_TRIVIAL(info) << "gRPC SaveDelta: " << request->numdelta();
            response->set_success(true);
            response->set_message("saveDelta Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC SaveDelta failed: " << e.what();
            response->set_success(false);
            response->set_message("saveDelta Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status MicroSteps(ServerContext* context, const StepsRequest* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.button_MicroSteps_Click(request->numsteps());
            BOOST_LOG_TRIVIAL(info) << "gRPC MicroSteps: " << request->numsteps();
            response->set_success(true);
            response->set_message("MicroSteps Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC MicroSteps failed: " << e.what();
            response->set_success(false);
            response->set_message("MicroSteps Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status TurnSteps(ServerContext* context, const StepsRequest* request,
                     CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.button_StepsTurn_Click(request->numsteps());
            BOOST_LOG_TRIVIAL(info) << "gRPC TurnSteps: " << request->numsteps();
            response->set_success(true);
            response->set_message("StepsTurn Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC TurnSteps failed: " << e.what();
            response->set_success(false);
            response->set_message("StepsTurn Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Sensor1Polarity(ServerContext* context, const SensorPolarityRequest* request,
                           CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonSensor1Polarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Sensor1Polarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Sensor1Polarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Sensor1Polarity failed: " << e.what();
            response->set_success(false);
            response->set_message("Sensor1Polarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Sensor2Polarity(ServerContext* context, const SensorPolarityRequest* request,
                           CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonSensor2Polarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Sensor2Polarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Sensor2Polarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Sensor2Polarity failed: " << e.what();
            response->set_success(false);
            response->set_message("Sensor2Polarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Sensor3Polarity(ServerContext* context, const SensorPolarityRequest* request,
                           CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonSensor3Polarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Sensor3Polarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Sensor3Polarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Sensor3Polarity failed: " << e.what();
            response->set_success(false);
            response->set_message("Sensor3Polarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Sensor4Polarity(ServerContext* context, const SensorPolarityRequest* request,
                           CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonSensor4Polarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Sensor4Polarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Sensor4Polarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Sensor4Polarity failed: " << e.what();
            response->set_success(false);
            response->set_message("Sensor4Polarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Sensor1Dir(ServerContext* context, const SensorPolarityRequest* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonSensor1Dir_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Sensor1Dir: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Sensor1Dir Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Sensor1Dir failed: " << e.what();
            response->set_success(false);
            response->set_message("Sensor1Dir Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Sensor2Dir(ServerContext* context, const SensorPolarityRequest* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonSensor2Dir_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Sensor2Dir: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Sensor2Dir Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Sensor2Dir failed: " << e.what();
            response->set_success(false);
            response->set_message("Sensor2Dir Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Sensor3Dir(ServerContext* context, const SensorPolarityRequest* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonSensor3Dir_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Sensor3Dir: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Sensor3Dir Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Sensor3Dir failed: " << e.what();
            response->set_success(false);
            response->set_message("Sensor3Dir Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Sensor4Dir(ServerContext* context, const SensorPolarityRequest* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonSensor4Dir_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Sensor4Dir: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Sensor4Dir Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Sensor4Dir failed: " << e.what();
            response->set_success(false);
            response->set_message("Sensor4Dir Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status SRVRDYPolarity(ServerContext* context, const SensorPolarityRequest* request,
                          CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonSRVRDYPolarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC SRVRDYPolarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("SRVRDYPolarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC SRVRDYPolarity failed: " << e.what();
            response->set_success(false);
            response->set_message("SRVRDYPolarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status INPOSPolarity(ServerContext* context, const SensorPolarityRequest* request,
                         CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonINPOSPolarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC INPOSPolarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("INPOSPolarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC INPOSPolarity failed: " << e.what();
            response->set_success(false);
            response->set_message("INPOSPolarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status FAULTPolarity(ServerContext* context, const SensorPolarityRequest* request,
                         CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonFAULTPolarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC FAULTPolarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("FAULTPolarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC FAULTPolarity failed: " << e.what();
            response->set_success(false);
            response->set_message("FAULTPolarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status BrakePolarity(ServerContext* context, const SensorPolarityRequest* request,
                         CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonBrakePolarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC BrakePolarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("BrakePolarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC BrakePolarity failed: " << e.what();
            response->set_success(false);
            response->set_message("BrakePolarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status DirPolarity(ServerContext* context, const SensorPolarityRequest* request,
                       CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonDirPolarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC DirPolarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("DirPolarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC DirPolarity failed: " << e.what();
            response->set_success(false);
            response->set_message("DirPolarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status EnPolarity(ServerContext* context, const SensorPolarityRequest* request,
                      CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonEnPolarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC EnPolarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("EnPolarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC EnPolarity failed: " << e.what();
            response->set_success(false);
            response->set_message("EnPolarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Al_CLRPolarity(ServerContext* context, const SensorPolarityRequest* request,
                          CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonAl_CLRPolarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Al_CLRPolarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Al_CLRPolarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Al_CLRPolarity failed: " << e.what();
            response->set_success(false);
            response->set_message("Al_CLRPolarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Al_OBrakePolarity(ServerContext* context, const SensorPolarityRequest* request,
                             CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonAl_OBrakePolarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Al_OBrakePolarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Al_OBrakePolarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Al_OBrakePolarity failed: " << e.what();
            response->set_success(false);
            response->set_message("Al_OBrakePolarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status Al_ORezervPolarity(ServerContext* context, const SensorPolarityRequest* request,
                              CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonAl_ORezervPolarity_Click(request->statusinverting());
            BOOST_LOG_TRIVIAL(info) << "gRPC Al_ORezervPolarity: " << request->statusinverting();
            response->set_success(true);
            response->set_message("Al_ORezervPolarity Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC Al_ORezervPolarity failed: " << e.what();
            response->set_success(false);
            response->set_message("Al_ORezervPolarity Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status EncoderActive(ServerContext* context, const EncoderActiveRequest* request,
                         CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.setEncoderActive(request->statusactive());
            BOOST_LOG_TRIVIAL(info) << "gRPC EncoderActive: " << request->statusactive();
            response->set_success(true);
            response->set_message("setEncoderActive Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC EncoderActive failed: " << e.what();
            response->set_success(false);
            response->set_message("setEncoderActive Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status EncoderConfig(ServerContext* context, const EncoderConfigRequest* request,
                         CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonEncoderConfig_Click(
                request->numpolarity(),
                request->numdelta(),
                request->numturndata()
            );
            BOOST_LOG_TRIVIAL(info) << "gRPC EncoderConfig: polarity=" << request->numpolarity()
                                   << ", delta=" << request->numdelta()
                                   << ", turnData=" << request->numturndata();
            response->set_success(true);
            response->set_message("encoderConfig Set");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC EncoderConfig failed: " << e.what();
            response->set_success(false);
            response->set_message("encoderConfig Set failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status FlashBoot(ServerContext* context, const FlashBootRequest* request,
                     CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonBoot_Click(request->filename());
            BOOST_LOG_TRIVIAL(info) << "gRPC FlashBoot: " << request->filename();
            response->set_success(true);
            response->set_message("Flash");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC FlashBoot failed: " << e.what();
            response->set_success(false);
            response->set_message("Flash failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status FlashTypeBootSet(ServerContext* context, const FlashTypeRequest* request,
                            CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonTypeBootSet_Click(request->type());
            BOOST_LOG_TRIVIAL(info) << "gRPC FlashTypeBootSet: " << request->type();
            response->set_success(true);
            response->set_message("flashTypeBootSet");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC FlashTypeBootSet failed: " << e.what();
            response->set_success(false);
            response->set_message("flashTypeBootSet failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }
    
    Status FlashTypeBootSave(ServerContext* context, const FlashTypeRequest* request,
                             CommandResponse* response) override {
        std::lock_guard<std::mutex> lock(controllerMutex);
        try {
            controller.buttonTypeBootSave_Click(request->type());
            BOOST_LOG_TRIVIAL(info) << "gRPC FlashTypeBootSave: " << request->type();
            response->set_success(true);
            response->set_message("flashTypeBootSave");
            return Status::OK;
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "gRPC FlashTypeBootSave failed: " << e.what();
            response->set_success(false);
            response->set_message("flashTypeBootSave failed");
            response->set_error(e.what());
            return Status::CANCELLED;
        }
    }

    Status Health(ServerContext* context, const Empty* request,
                  HealthResponse* response) override {
        BOOST_LOG_TRIVIAL(info) << "gRPC Health check";
        response->set_healthy(true);
        response->set_status("OK");
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            now.time_since_epoch()).count();
        response->set_timestamp(timestamp);
        return Status::OK;
    }
    
    void runServer() {
        std::string server_address = "0.0.0.0:" + std::to_string(port);
        std::shared_ptr<grpc::ServerCredentials> creds;
        try {
            creds = grpc::InsecureServerCredentials();
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "Crash inside InsecureServerCredentials: " << e.what() << std::endl;
            return;
        }

        if (!creds) {
            BOOST_LOG_TRIVIAL(error) << "InsecureServerCredentials returned NULL!" << std::endl;
            return;
        }

        ServerBuilder builder;
        
        grpc::EnableDefaultHealthCheckService(true);
        grpc::reflection::InitProtoReflectionServerBuilderPlugin();

        int selected_port = 0;        
        try {
            builder.AddListeningPort(server_address, creds, &selected_port);
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "Crash inside AddListeningPort: " << e.what() << std::endl;
            return;
        }

        builder.RegisterService(this);
        server = builder.BuildAndStart();
        
        if (!server) {
            BOOST_LOG_TRIVIAL(error) << "Failed to start gRPC server. Port " << port << " might be busy.";
            return;
        }
        
        if (selected_port == 0) {
            BOOST_LOG_TRIVIAL(error) << "gRPC server failed to bind to port " << port;
            return;
        }

        BOOST_LOG_TRIVIAL(info) << "Run gRPC Server on " << server_address;
        server->Wait();
    }
    
    void shutdownServer() {
        if (server) {
            BOOST_LOG_TRIVIAL(info) << "Shutdown gRPC Server";
            server->Shutdown();
        }
    }
};