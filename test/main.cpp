#include <iostream>
#include <vector>
#include <cstring>
#include <thread>
#include <chrono>
#include "HidDevice.h"
#include "CanController.h"
#include <iostream>

int main() {
    CanController controller;
    controller.initializeDevice(0x0483,0x577f); //ID в парметрах, чтобы найти: lsusb | grep USB-CAN
    // std::this_thread::sleep_for(std::chrono::seconds(1));

    controller.buttonNumBoard_Click(16);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    controller.buttonNumSteps_Click(5000);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    controller.buttonSpeed_Click(10.0f);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    controller.buttonAccel_Click(10);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    controller.buttonDecel_Click(10);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    controller.buttonMoveForward_Click();
    // controller.buttonUpdate_Click();
    return 0;
}