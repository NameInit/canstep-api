cmake_minimum_required(VERSION 3.12)
project(CANStepAPI VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(canstep STATIC
    src/HidDevice.cpp
)

target_include_directories(canstep PUBLIC include)

target_link_libraries(canstep PUBLIC hidapi-hidraw)
find_package(Boost REQUIRED COMPONENTS json)
find_package(Boost REQUIRED COMPONENTS log)
target_link_libraries(canstep PUBLIC pistache)
target_link_libraries(canstep PUBLIC Boost::json)
target_link_libraries(canstep PUBLIC Boost::log)

add_executable(canstep-test test/main.cpp)
target_link_libraries(canstep-test canstep)