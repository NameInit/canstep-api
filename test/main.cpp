// #include <iostream>
// #include <vector>
// #include <cstring>
// #include <thread>
// #include <chrono>
// #include "../include/CanController.h"
// #include <iostream>
// -lcanstep -lhidapi-hidraw
#include "../include/CanControllerApi.h"

int main() {
    CanControllerApi api;
    api.runServer();
    // CanController controller;
    // controller.buttonOpenCOM_Click(0x0483,0x577f); //ID в парметрах, чтобы найти: lsusb | grep USB-CAN
    // std::this_thread::sleep_for(std::chrono::seconds(1));

    // controller.buttonDebugOn_Click();

    // controller.buttonNumBoardSave_Click(16);
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    // controller.buttonAl_CLRPolarity_Click(1);

    // controller.buttonNumSteps_Click(3000);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // controller.buttonSpeed_Click(10.0);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // controller.buttonAccel_Click(10);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // controller.buttonDecel_Click(10);
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // controller.buttonDebugOn_Click();

    // controller.buttonMoveForward_Click();
    // controller.buttonHomingZero_Click();
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // controller.buttonStop_Click();
    // controller.buttonUpdate_Click();
    return 0;
}