cmake_minimum_required(VERSION 3.12)
project(CANStepAPI VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем библиотеку
add_library(canstep STATIC
    src/HidDevice.cpp
)

# Подключаем заголовочные файлы
target_include_directories(canstep PUBLIC include)

# ДОБАВЛЕНО: Подключаем hidapi библиотеку к нашей библиотеке
target_link_libraries(canstep PUBLIC hidapi-hidraw)

# Добавляем исполняемый файл для тестирования
add_executable(canstep-test test/main.cpp)
target_link_libraries(canstep-test canstep)