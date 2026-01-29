# mosquitto mosquitto-clients важный пакет для mqtt, должен быть на образе ubuntu

cmake_minimum_required(VERSION 3.12)
project(CANStepAPI VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(canstep STATIC
    src/HidDevice.cpp
    src/CanController.cpp
    src/Mechanism.cpp
    src/ScenarioBuilder.cpp
    src/Tensometer.cpp
    src/can_controller.grpc.pb.cc
    src/can_controller.pb.cc
)

target_include_directories(canstep PUBLIC include)

target_link_libraries(canstep PUBLIC hidapi-hidraw)
target_link_libraries(canstep PUBLIC pistache)
find_package(Boost REQUIRED COMPONENTS json)
find_package(Boost REQUIRED COMPONENTS log)
target_link_libraries(canstep PUBLIC Boost::json)
target_link_libraries(canstep PUBLIC Boost::log)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
target_link_libraries(canstep PUBLIC gRPC::grpc++)
target_link_libraries(canstep PUBLIC gRPC::grpc)
target_link_libraries(canstep PUBLIC gRPC::grpc++_reflection)
find_package(PahoMqttCpp REQUIRED)
target_link_libraries(canstep PUBLIC PahoMqttCpp::paho-mqttpp3)

add_executable(canstep-test test/main.cpp)
target_link_libraries(canstep-test canstep)