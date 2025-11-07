#pragma once

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <boost/json.hpp>
#include <memory>
#include <iostream>
#include <cstdint>

#include "CanController.h"

class CanControllerApi
{
private:
    Pistache::Rest::Router router;
    CanController controller;

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

        Pistache::Rest::Routes::Get(router, "/health", Pistache::Rest::Routes::bind(&CanControllerApi::health, this));
    }

    void connect(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
        std::cout << "connect" << std::endl;
        std::cout << "SUCCESS!" << std::endl;
        controller.buttonOpenCOM_Click();
        response.send(Pistache::Http::Code::Ok, "Connected");
    }

    void debugOn(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
        std::cout << "debugOn" << std::endl;
        std::cout << "SUCCESS!" << std::endl;
        controller.buttonDebugOn_Click();
        response.send(Pistache::Http::Code::Ok, "Debug ON");
    }

    void board(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
        std::cout << "board: " << request.body() << std::endl;
        std::cout << "=====JSON BODY=====" << std::endl;
        std::cout << request.body() << std::endl;
        boost::json::value json_data = boost::json::parse(request.body());
        boost::json::object obj=json_data.as_object();
        int64_t val=obj["numBoard"].as_int64(); 
        std::cout << obj["numBoard"].kind() << std::endl;
        std::cout << "Transorm type: " << val << std::endl;
        controller.buttonNumBoard_Click(val);
        std::cout << "SUCCESS!" << std::endl;
        response.send(Pistache::Http::Code::Ok, "Board Set");
    }

    void steps(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
        std::cout << "steps: " << request.body() << std::endl;
        std::cout << "=====JSON BODY=====" << std::endl;
        std::cout << request.body() << std::endl;
        boost::json::value json_data = boost::json::parse(request.body());
        boost::json::object obj=json_data.as_object();
        int64_t val=obj["numSteps"].as_int64();
        std::cout << obj["numSteps"].kind() << std::endl;
        std::cout << "Transorm type: " << val << std::endl;
        controller.buttonNumSteps_Click(val);
        std::cout << "SUCCESS!" << std::endl;
        response.send(Pistache::Http::Code::Ok, "Steps set");
    }

    void speed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
        std::cout << "speed: " << request.body() << std::endl;
        std::cout << "=====JSON BODY=====" << std::endl;
        std::cout << request.body() << std::endl;
        boost::json::value json_data = boost::json::parse(request.body());
        boost::json::object obj=json_data.as_object();
        int64_t val = obj["numSpeed"].as_int64();
        std::cout << obj["numSpeed"].kind() << std::endl;
        std::cout << "Transorm type: " << val << std::endl;
        controller.buttonSpeed_Click(val);
        std::cout << "SUCCESS!" << std::endl;
        response.send(Pistache::Http::Code::Ok, "Speed set");
    }

    void accel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
        std::cout << "accel: " << request.body() << std::endl;
        std::cout << "=====JSON BODY=====" << std::endl;
        std::cout << request.body() << std::endl;
        boost::json::value json_data = boost::json::parse(request.body());
        boost::json::object obj=json_data.as_object();
        int64_t val = obj["numAccel"].as_int64();
        std::cout << obj["numAccel"].kind() << std::endl;
        std::cout << "Transorm type: " << val << std::endl;
        controller.buttonAccel_Click(val);
        std::cout << "SUCCESS!" << std::endl;
        response.send(Pistache::Http::Code::Ok, "Acceleration set");
    }

    void decel(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
        std::cout << "decel: " << request.body() << std::endl;
        std::cout << "=====JSON BODY=====" << std::endl;
        std::cout << request.body() << std::endl;
        boost::json::value json_data = boost::json::parse(request.body());
        boost::json::object obj=json_data.as_object();
        int64_t val = obj["numDecel"].as_int64();
        std::cout << obj["numDecel"].kind() << std::endl;
        std::cout << "Transorm type: " << val << std::endl;
        controller.buttonDecel_Click(val);
        std::cout << "SUCCESS!" << std::endl;
        response.send(Pistache::Http::Code::Ok, "Deceleration set");
    }

    void forward(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
        std::cout << "forward" << std::endl;
        std::cout << "SUCCESS!" << std::endl;
        controller.buttonMoveForward_Click();
        response.send(Pistache::Http::Code::Ok, "Moving forward");
    }

    void backward(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
        std::cout << "backward" << std::endl;
        std::cout << "SUCCESS!" << std::endl;
        controller.buttonMoveBackward_Click();
        response.send(Pistache::Http::Code::Ok, "Moving backward");
    }

    void health(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
        std::cout << "health check" << std::endl;
        response.send(Pistache::Http::Code::Ok, "OK");
    }

public:
    CanControllerApi(){ setupRoutes(); }
    ~CanControllerApi(){}
    
    void runServer(const uint16_t numPort=5000){
        std::cout << "Starting server on port " << numPort << std::endl;
        
        Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(numPort));
        auto server = std::make_shared<Pistache::Http::Endpoint>(addr);
        
        auto opts = Pistache::Http::Endpoint::options().threads(2);
        server->init(opts);
        server->setHandler(router.handler());
        
        std::cout << "Server is running at http://localhost:" << numPort << std::endl;
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