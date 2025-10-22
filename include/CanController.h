#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include <sstream>

#include <unistd.h>
#include <pthread.h>

#include "Typedefs.h"
#include "ScenarioBuilder.h"
#include "Mechanism.h"
#include "HidDevice.h"
#include "DefsCANStep.h"


class CanController {
public:
    CanController();
    ~CanController();

    void buttonOpenCOM_Click(uint16_t vendorId, uint16_t productId);
    void buttonNumBoard_Click(uint8_t boardId);
    void buttonNumGroup_Click(uint8_t groupId);
    void buttonNumSteps_Click(uint32_t steps);
    void buttonSpeed_Click(float speed);
    void buttonAccel_Click(uint8_t accel);
    void buttonDecel_Click(uint8_t decel);
    void buttonMoveForward_Click();
    void buttonMoveBackward_Click();
    void buttonStop_Click();
    void buttonHomingZero_Click();
    void buttonHomingMax_Click();
    void buttonResetDRVError_Click();
    void buttonBrakeOn_Click();
    void buttonBrakeOff_Click();

    //-----------can откликается, но не знаю как затестить------------------
    void buttonRezervOn_Click();
    void buttonRezervOff_Click();
    void buttonAlarmResetOn_Click();
    void buttonAlarmResetOff_Click();
    void buttonDebugOn_Click();
    void buttonCurrentPositionSet_Click(uint32_t position);
    //------------------------------------------------------

    void buttonNumBoardSave_Click(uint8_t boardId);
    void buttonNumGroupSave_Click(uint8_t groupId);
    void buttonStartPositionSave_Click(uint32_t position);
    void buttonEndPositionSave_Click(uint32_t position);
    void buttonMaxSpeedSave_Click(float speed);
    void buttonDefaultSpeedSave_Click(float speed);
    void buttonAccelSave_Click(uint8_t accel);
    void buttonDecelSave_Click(uint8_t decel);
    void buttonDeltaSave_Click(uint32_t delta);
    // void buttonSensorPolarity_Click(int sensorNum, uint8_t polarity);
    void buttonSensor1Polarity_Click(uint8_t u8Inverting);
    void buttonSensor2Polarity_Click(uint8_t u8Inverting);
    void buttonSensor3Polarity_Click(uint8_t u8Inverting);
    void buttonSensor4Polarity_Click(uint8_t u8Inverting);
    // void buttonSensorDir_Click(int sensorNum, uint8_t direction);
    void buttonSensor1Dir_Click(uint8_t u8Inverting);
    void buttonSensor2Dir_Click(uint8_t u8Inverting);
    void buttonSensor3Dir_Click(uint8_t u8Inverting);
    void buttonSensor4Dir_Click(uint8_t u8Inverting);
    void buttonEnPolarity_Click(uint8_t u8Inverting);
    void buttonAl_CLRPolarity_Click(uint8_t u8Inverting);
    void buttonAl_OBrakePolarity_Click(uint8_t u8Inverting);
    void buttonAl_ORezervPolarity_Click(uint8_t u8Inverting);
    void buttonDirPolarity_Click(uint8_t u8Inverting);
    void buttonSRVRDYPolarity_Click(uint8_t u8Inverting);
    void buttonINPOSPolarity_Click(uint8_t u8Inverting);
    void buttonFAULTPolarity_Click(uint8_t u8Inverting);
    void buttonBrakePolarity_Click(uint8_t u8Inverting);

    void button_OUT_0_OFF_Click();
    void button_OUT_1_OFF_Click();
    void button_OUT_2_OFF_Click();
    void button_OUT_3_OFF_Click();
    void button_OUT_4_OFF_Click();
    void button_OUT_5_OFF_Click();
    void button_OUT_6_OFF_Click();
    void button_OUT_7_OFF_Click();
    void button_OUT_0_TO_VCC_Click();
    void button_OUT_1_TO_VCC_Click();
    void button_OUT_2_TO_VCC_Click();
    void button_OUT_3_TO_VCC_Click();
    void button_OUT_4_TO_VCC_Click();
    void button_OUT_5_TO_VCC_Click();
    void button_OUT_6_TO_VCC_Click();
    void button_OUT_7_TO_VCC_Click();
    void button_OUT_0_TO_GND_Click();
    void button_OUT_1_TO_GND_Click();
    void button_OUT_2_TO_GND_Click();
    void button_OUT_3_TO_GND_Click();
    void button_OUT_4_TO_GND_Click();
    void button_OUT_5_TO_GND_Click();
    void button_OUT_6_TO_GND_Click();
    void button_OUT_7_TO_GND_Click();
    void button_IN_0_TO_VCC_Click();
    void button_IN_1_TO_VCC_Click();
    void button_IN_2_TO_VCC_Click();
    void button_IN_3_TO_VCC_Click();
    void button_IN_4_TO_VCC_Click();
    void button_IN_5_TO_VCC_Click();
    void button_IN_6_TO_VCC_Click();
    void button_IN_7_TO_VCC_Click();
    void button_IN_8_TO_VCC_Click();
    void button_IN_9_TO_VCC_Click();
    void button_IN_10_TO_VCC_Click();
    void button_IN_11_TO_VCC_Click();
    void button_IN_0_TO_GND_Click();
    void button_IN_1_TO_GND_Click();
    void button_IN_2_TO_GND_Click();
    void button_IN_3_TO_GND_Click();
    void button_IN_4_TO_GND_Click();
    void button_IN_5_TO_GND_Click();
    void button_IN_6_TO_GND_Click();
    void button_IN_7_TO_GND_Click();
    void button_IN_8_TO_GND_Click();
    void button_IN_9_TO_GND_Click();
    void button_IN_10_TO_GND_Click();
    void button_IN_11_TO_GND_Click();
    //------------------------------------------------------------------------

    // void buttonOutputPolarity_Click(const std::string& outputName, uint8_t polarity);
    // void buttonInputPolarity_Click(const std::string& inputName, uint8_t polarity);
    void button_MicroSteps_Click(uint32_t microsteps);
    void button_StepsTurn_Click(uint32_t steps);
    // void button_OUT_SetState_Click(int outNum, const std::string& state);
    // void button_IN_SetPull_Click(int inNum, const std::string& state);
    void buttonSaveInPullUps_Click();
    void buttonResetCANStep_Click();
    void buttonDriverOn_Click();
    void buttonDriverOff_Click();
    void buttonIHOLDSet_Click(uint8_t ihold, uint8_t irun, uint8_t iholddelay);
    void buttonSPEEDTHRSSet_Click(uint8_t threshold);
    // void buttonCOOLCONF_Click();
    // void buttonEncoderConfig_Click(uint8_t polarity, uint8_t delta, uint16_t toTurn);
    // void buttonGLOBAL_SCALER_Click(uint8_t scaler);
    void trackBarPositioning_Velocity_Scroll(bool isPositioning);
    void buttonAutosender_Click(uint8_t type, uint8_t delayMs);
    void buttonTestUSBCAN_Click();
    void buttonMotorTorque_Click();
    void buttonMotorSpeed_Click();
    void buttonAbsolutePositionRotorUint_Click();
    void buttonAlarmCode_Click();

    void buttonUpdate_Click();
    void buttonStopUpdate_Click();

    void createMechanismObj0(uint8_t boardId, uint8_t groupId);
    void dataUpdateLoop();

    void myAnswerControlCallback(uint8_t* pNumBoardParse, uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* pCmdInWork, uint8_t* ptmpErrors);
    void myAnswerConfigCallback(uint8_t* pNumBoardParse);
    void myAnswerCallback(uint8_t* pNumBoardParse, uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3);

    std::unique_ptr<HidDevice> hidDevice;
    std::unique_ptr<Mechanism> mechanismObj0;
    std::unique_ptr<ScenarioBuilder> scenarioBuilder;

    std::thread updateThread;
    std::atomic<bool> isRunning{false};

    uint16_t vendorId = 1155;
    uint16_t productId = 22399;
};

CanController::CanController() {
    hidDevice = std::make_unique<HidDevice>();
    scenarioBuilder = std::make_unique<ScenarioBuilder>();
}

CanController::~CanController() {
    buttonStopUpdate_Click();
}

void CanController::createMechanismObj0(uint8_t boardId, uint8_t groupId) {
    if (!mechanismObj0) {
        mechanismObj0 = std::make_unique<Mechanism>(boardId, groupId);

        mechanismObj0->SetCallbackAnswer(std::bind(&CanController::myAnswerCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9));
        mechanismObj0->SetCallbackAnswerConfig(std::bind(&CanController::myAnswerConfigCallback, this, std::placeholders::_1));
        mechanismObj0->SetCallbackAnswerControl(std::bind(&CanController::myAnswerControlCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
        
        mechanismObj0->SetHidDevice(hidDevice.get());
    } else {
        mechanismObj0->changeNumBoard(boardId);
    }
    
    // Отправка запросов на получение начальных данных
    mechanismObj0->ClrAsks();
    usleep(10000); // 10ms
    mechanismObj0->SetAsk(AskPosition);
    mechanismObj0->SetAsk(AskHomings);
    mechanismObj0->SetAsk(AskInputs);
    mechanismObj0->SetAsk(AskCurrOutputs);
    mechanismObj0->SetAsk(AskGroup);
}

void CanController::buttonOpenCOM_Click(uint16_t vendorId=0x0483, uint16_t productId=0x577f) {
    createMechanismObj0(0, 0); // Создаем с ID по умолчанию
    mechanismObj0->SetHidDevice(hidDevice.get());

    if (hidDevice->IsConnected()) {
        hidDevice->Disconnect();
        std::cout << "HID устройство отключено." << std::endl;
    } else if (hidDevice->Connect(vendorId, productId)) {
        std::cout << "HID устройство успешно подключено." << std::endl;
    } else {
        std::cout << "Ошибка: не удалось подключить HID устройство." << std::endl;
    }
}

void CanController::buttonMoveForward_Click() { if(mechanismObj0) mechanismObj0->runForward(); }
void CanController::buttonMoveBackward_Click() { if(mechanismObj0) mechanismObj0->runBackward(); }
void CanController::buttonStop_Click() { if(mechanismObj0) mechanismObj0->stop(); }
void CanController::buttonHomingZero_Click() { if(mechanismObj0) mechanismObj0->HomingZero(); }
void CanController::buttonHomingMax_Click() { if(mechanismObj0) mechanismObj0->HomingMax(); }
void CanController::buttonResetDRVError_Click() { if(mechanismObj0) mechanismObj0->ResetDRVError(); }
void CanController::buttonBrakeOn_Click() { if(mechanismObj0) mechanismObj0->BrakeOn(); }
void CanController::buttonBrakeOff_Click() { if(mechanismObj0) mechanismObj0->BrakeOff(); }
void CanController::buttonRezervOn_Click() { if(mechanismObj0) mechanismObj0->RezervOn(); }
void CanController::buttonRezervOff_Click() { if(mechanismObj0) mechanismObj0->RezervOff(); }
void CanController::buttonAlarmResetOn_Click() { if(mechanismObj0) mechanismObj0->AlarmResetOn(); }
void CanController::buttonAlarmResetOff_Click() { if(mechanismObj0) mechanismObj0->AlarmResetOff(); }
void CanController::buttonDebugOn_Click() { if(mechanismObj0) mechanismObj0->Debug_on(); }
void CanController::buttonResetCANStep_Click() { if(mechanismObj0) mechanismObj0->Reset(); }
void CanController::buttonDriverOn_Click() { if(mechanismObj0) mechanismObj0->Mosfet_On(); }
void CanController::buttonDriverOff_Click() { if(mechanismObj0) mechanismObj0->Mosfet_Off(); }
void CanController::buttonSaveInPullUps_Click() { if(mechanismObj0) mechanismObj0->SaveInPullUps(); }
void CanController::buttonMotorTorque_Click() { if(mechanismObj0) mechanismObj0->SetOneTaskAsk(AskMotorTorque); }
void CanController::buttonMotorSpeed_Click() { if(mechanismObj0) mechanismObj0->SetOneTaskAsk(AskMotorSpeed); }
void CanController::buttonAbsolutePositionRotorUint_Click() { if(mechanismObj0) mechanismObj0->SetOneTaskAsk(AskAbsolutePositionRotorUint); }
void CanController::buttonAlarmCode_Click() { if(mechanismObj0) mechanismObj0->SetOneTaskAsk(AskAlarmCode); }


void CanController::buttonNumBoard_Click(uint8_t boardId) { createMechanismObj0(boardId, 0); }
void CanController::buttonNumGroup_Click(uint8_t groupId) { if(mechanismObj0) mechanismObj0->changeGroup(groupId); }
void CanController::buttonNumSteps_Click(uint32_t steps) { if(mechanismObj0) mechanismObj0->setSteps(steps); }
void CanController::buttonSpeed_Click(float speed) { if(mechanismObj0) mechanismObj0->setSpeed(speed); }
void CanController::buttonAccel_Click(uint8_t accel) { if(mechanismObj0) mechanismObj0->setCurrAccel(accel); }
void CanController::buttonDecel_Click(uint8_t decel) { if(mechanismObj0) mechanismObj0->setCurrDecel(decel); }
void CanController::buttonCurrentPositionSet_Click(uint32_t position) { if(mechanismObj0) mechanismObj0->SetPosition(position); }
void CanController::buttonNumBoardSave_Click(uint8_t boardId) { if(mechanismObj0) mechanismObj0->setNumBoard(boardId); }
void CanController::buttonNumGroupSave_Click(uint8_t groupId) { if(mechanismObj0) mechanismObj0->setGroup(groupId); }
void CanController::buttonStartPositionSave_Click(uint32_t position) { if(mechanismObj0) mechanismObj0->setStartPosition(position); }
void CanController::buttonEndPositionSave_Click(uint32_t position) { if(mechanismObj0) mechanismObj0->setEndPosition(position); }
void CanController::buttonMaxSpeedSave_Click(float speed) { if(mechanismObj0) mechanismObj0->setmaxSpeed(speed); }
void CanController::buttonDefaultSpeedSave_Click(float speed) { if(mechanismObj0) mechanismObj0->setCurrSpeed(speed); }
void CanController::buttonAccelSave_Click(uint8_t accel) { if(mechanismObj0) mechanismObj0->setAccel(accel); }
void CanController::buttonDecelSave_Click(uint8_t decel) { if(mechanismObj0) mechanismObj0->setDecel(decel); }
void CanController::buttonDeltaSave_Click(uint32_t delta) { if(mechanismObj0) mechanismObj0->setDeltaPosition(delta); }
void CanController::button_MicroSteps_Click(uint32_t microsteps) { if(mechanismObj0) mechanismObj0->setMicroSteps(microsteps); }
void CanController::button_StepsTurn_Click(uint32_t steps) { if(mechanismObj0) mechanismObj0->setStepsToTurn(steps); }
void CanController::buttonIHOLDSet_Click(uint8_t ihold, uint8_t irun, uint8_t iholddelay) { if(mechanismObj0) mechanismObj0->SetIHOLD(ihold, irun, iholddelay); }
void CanController::buttonSPEEDTHRSSet_Click(uint8_t threshold) { if(mechanismObj0) mechanismObj0->setTPWMTHRS(threshold); }
void CanController::trackBarPositioning_Velocity_Scroll(bool isPositioning) { if(mechanismObj0) mechanismObj0->setControlPositioning_Velocity(isPositioning); }
void CanController::buttonAutosender_Click(uint8_t type, uint8_t delayMs) { if(mechanismObj0) mechanismObj0->setAutosender(type, delayMs, 0); }
void CanController::buttonTestUSBCAN_Click() { if (mechanismObj0) mechanismObj0->setUpdateType(!mechanismObj0->getUpdateType()); }

void CanController::buttonSensor1Polarity_Click(uint8_t u8Inverting){ mechanismObj0->setHomingAPolarity(u8Inverting); }
void CanController::buttonSensor2Polarity_Click(uint8_t u8Inverting){ mechanismObj0->setHomingBPolarity(u8Inverting); }
void CanController::buttonSensor3Polarity_Click(uint8_t u8Inverting){ mechanismObj0->setHomingCPolarity(u8Inverting); }
void CanController::buttonSensor4Polarity_Click(uint8_t u8Inverting){ mechanismObj0->setHomingDPolarity(u8Inverting); }
void CanController::buttonSensor1Dir_Click(uint8_t u8Inverting){ mechanismObj0->setHomingADirection(u8Inverting); }
void CanController::buttonSensor2Dir_Click(uint8_t u8Inverting){ mechanismObj0->setHomingBDirection(u8Inverting); }
void CanController::buttonSensor3Dir_Click(uint8_t u8Inverting){ mechanismObj0->setHomingCDirection(u8Inverting); }
void CanController::buttonSensor4Dir_Click(uint8_t u8Inverting){ mechanismObj0->setHomingDDirection(u8Inverting); }
void CanController::buttonEnPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setEnPolarity(u8Inverting); }
void CanController::buttonAl_CLRPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setAL_CLRPolarity(u8Inverting); }
void CanController::buttonAl_OBrakePolarity_Click(uint8_t u8Inverting){ mechanismObj0->setOBRAKEPolarity(u8Inverting); }
void CanController::buttonAl_ORezervPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setOReservPolarity(u8Inverting); }
void CanController::buttonDirPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setDIRPolarity(u8Inverting); }
void CanController::buttonSRVRDYPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setSRVRDYPolarity(u8Inverting); }
void CanController::buttonINPOSPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setINPOSPolarity(u8Inverting); }
void CanController::buttonFAULTPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setFAULTPolarity(u8Inverting); }
void CanController::buttonBrakePolarity_Click(uint8_t u8Inverting){ mechanismObj0->setBRAKEPolarity(u8Inverting); }

void CanController::button_OUT_0_OFF_Click() { mechanismObj0->setOutToZ(0); }
void CanController::button_OUT_1_OFF_Click() { mechanismObj0->setOutToZ(1); }
void CanController::button_OUT_2_OFF_Click() { mechanismObj0->setOutToZ(2); }
void CanController::button_OUT_3_OFF_Click() { mechanismObj0->setOutToZ(3); }
void CanController::button_OUT_4_OFF_Click() { mechanismObj0->setOutToZ(4); }
void CanController::button_OUT_5_OFF_Click() { mechanismObj0->setOutToZ(5); }
void CanController::button_OUT_6_OFF_Click() { mechanismObj0->setOutToZ(6); }
void CanController::button_OUT_7_OFF_Click() { mechanismObj0->setOutToZ(7); }
void CanController::button_OUT_0_TO_VCC_Click() { mechanismObj0->setOutToHi(0); }
void CanController::button_OUT_1_TO_VCC_Click() { mechanismObj0->setOutToHi(1); }
void CanController::button_OUT_2_TO_VCC_Click() { mechanismObj0->setOutToHi(2); }
void CanController::button_OUT_3_TO_VCC_Click() { mechanismObj0->setOutToHi(3); }
void CanController::button_OUT_4_TO_VCC_Click() { mechanismObj0->setOutToHi(4); }
void CanController::button_OUT_5_TO_VCC_Click() { mechanismObj0->setOutToHi(5); }
void CanController::button_OUT_6_TO_VCC_Click() { mechanismObj0->setOutToHi(6); }
void CanController::button_OUT_7_TO_VCC_Click() { mechanismObj0->setOutToHi(7); }
void CanController::button_OUT_0_TO_GND_Click() { mechanismObj0->setOutToLo(0); }
void CanController::button_OUT_1_TO_GND_Click() { mechanismObj0->setOutToLo(1); }
void CanController::button_OUT_2_TO_GND_Click() { mechanismObj0->setOutToLo(2); }
void CanController::button_OUT_3_TO_GND_Click() { mechanismObj0->setOutToLo(3); }
void CanController::button_OUT_4_TO_GND_Click() { mechanismObj0->setOutToLo(4); }
void CanController::button_OUT_5_TO_GND_Click() { mechanismObj0->setOutToLo(5); }
void CanController::button_OUT_6_TO_GND_Click() { mechanismObj0->setOutToLo(6); }
void CanController::button_OUT_7_TO_GND_Click() { mechanismObj0->setOutToLo(7); }
void CanController::button_IN_0_TO_VCC_Click() { mechanismObj0->setInPullUp(0); }
void CanController::button_IN_1_TO_VCC_Click() { mechanismObj0->setInPullUp(1); }
void CanController::button_IN_2_TO_VCC_Click() { mechanismObj0->setInPullUp(2); }
void CanController::button_IN_3_TO_VCC_Click() { mechanismObj0->setInPullUp(3); }
void CanController::button_IN_4_TO_VCC_Click() { mechanismObj0->setInPullUp(4); }
void CanController::button_IN_5_TO_VCC_Click() { mechanismObj0->setInPullUp(5); }
void CanController::button_IN_6_TO_VCC_Click() { mechanismObj0->setInPullUp(6); }
void CanController::button_IN_7_TO_VCC_Click() { mechanismObj0->setInPullUp(7); }
void CanController::button_IN_8_TO_VCC_Click() { mechanismObj0->setInPullUp(8); }
void CanController::button_IN_9_TO_VCC_Click() { mechanismObj0->setInPullUp(9); }
void CanController::button_IN_10_TO_VCC_Click() { mechanismObj0->setInPullUp(10); }
void CanController::button_IN_11_TO_VCC_Click() { mechanismObj0->setInPullUp(11); }
void CanController::button_IN_0_TO_GND_Click() { mechanismObj0->setInPullDown(0); }
void CanController::button_IN_1_TO_GND_Click() { mechanismObj0->setInPullDown(1); }
void CanController::button_IN_2_TO_GND_Click() { mechanismObj0->setInPullDown(2); }
void CanController::button_IN_3_TO_GND_Click() { mechanismObj0->setInPullDown(3); }
void CanController::button_IN_4_TO_GND_Click() { mechanismObj0->setInPullDown(4); }
void CanController::button_IN_5_TO_GND_Click() { mechanismObj0->setInPullDown(5); }
void CanController::button_IN_6_TO_GND_Click() { mechanismObj0->setInPullDown(6); }
void CanController::button_IN_7_TO_GND_Click() { mechanismObj0->setInPullDown(7); }
void CanController::button_IN_8_TO_GND_Click() { mechanismObj0->setInPullDown(8); }
void CanController::button_IN_9_TO_GND_Click() { mechanismObj0->setInPullDown(9); }
void CanController::button_IN_10_TO_GND_Click() { mechanismObj0->setInPullDown(10); }
void CanController::button_IN_11_TO_GND_Click() { mechanismObj0->setInPullDown(11); }

void CanController::buttonUpdate_Click() {
    if (!isRunning) {
        isRunning = true;
        updateThread = std::thread(&CanController::dataUpdateLoop, this);
        std::cout << "Поток обновления запущен." << std::endl;
    }
}

void CanController::buttonStopUpdate_Click() {
    if (isRunning) {
        isRunning = false;
        if (updateThread.joinable()) {
            updateThread.join();
        }
        std::cout << "Поток обновления остановлен." << std::endl;
    }
}

void CanController::dataUpdateLoop() {
    while (isRunning) {
        if (mechanismObj0) {
            mechanismObj0->UpdateCode();
        }
        usleep(100000);
    }
}

void CanController::myAnswerControlCallback(uint8_t* pNumBoardParse, uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* pCmdInWork, uint8_t* ptmpErrors) {
    std::cout << "[CONTROL] Board: " << (int)*pNumBoardParse << ", CMD: " << (int)*pNumCMD << ", InWork: " << (int)*pCmdInWork << std::endl;
    if (mechanismObj0 && *pNumBoardParse == mechanismObj0->getNumBoard()) {
        mechanismObj0->loadControl(pRescCMD, pNumCMD, pStartMotor, ptmpErrors);
        mechanismObj0->setCmdFromMechanism(pRescCMD, pNumCMD, pCmdInWork);
    }
}

void CanController::myAnswerConfigCallback(uint8_t* pNumBoardParse) {
    std::cout << "[CONFIG] ACK from Board: " << (int)*pNumBoardParse << std::endl;
    if (mechanismObj0 && *pNumBoardParse == mechanismObj0->getNumBoard()) {
        mechanismObj0->loadParam();
    }
}

void CanController::myAnswerCallback(uint8_t* pNumBoardParse, uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3) {
    if (mechanismObj0 && *pNumBoardParse == mechanismObj0->getNumBoard()) {
        mechanismObj0->loadAnswer(pStatus, pNumAnswer, p8Data, p32Data, pfData, p8Data1, p8Data2, p8Data3);
        
        if(*pNumAnswer == OutPosition) {
            std::cout << "[DATA] Board " << (int)*pNumBoardParse << " Position: " << *p32Data << std::endl;
        }
    }
}