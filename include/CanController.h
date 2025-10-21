#pragma once

// --- Includes ---
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include <sstream>

// POSIX/Linux headers
#include <unistd.h> // для usleep
#include <pthread.h>

// Ваши проектные заголовочные файлы
#include "Typedefs.h"
#include "ScenarioBuilder.h"
#include "Mechanism.h"
#include "HidDevice.h"
#include "DefsCANStep.h"

// --- Объявление класса CanController ---

class CanController {
public:
    // Конструктор и деструктор
    CanController();
    ~CanController();

    // Запуск интерактивной консоли
    void runTerminal();

public:
    void initializeDevice(uint16_t vendorId, uint16_t productId);

    // --- Реализация логики кнопок ---
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
    void buttonRezervOn_Click();
    void buttonRezervOff_Click();
    void buttonAlarmResetOn_Click();
    void buttonAlarmResetOff_Click();
    void buttonDebugOn_Click();
    void buttonCurrentPositionSet_Click(uint32_t position);
    void buttonNumBoardSave_Click(uint8_t boardId);
    void buttonNumGroupSave_Click(uint8_t groupId);
    void buttonStartPositionSave_Click(uint32_t position);
    void buttonEndPositionSave_Click(uint32_t position);
    void buttonMaxSpeedSave_Click(float speed);
    void buttonDefaultSpeedSave_Click(float speed);
    void buttonAccelSave_Click(uint8_t accel);
    void buttonDecelSave_Click(uint8_t decel);
    void buttonDeltaSave_Click(uint32_t delta);
    void buttonSensorPolarity_Click(int sensorNum, uint8_t polarity);
    void buttonSensorDir_Click(int sensorNum, uint8_t direction);
    void buttonOutputPolarity_Click(const std::string& outputName, uint8_t polarity);
    void buttonInputPolarity_Click(const std::string& inputName, uint8_t polarity);
    void button_MicroSteps_Click(uint32_t microsteps);
    void button_StepsTurn_Click(uint32_t steps);
    void button_OUT_SetState_Click(int outNum, const std::string& state);
    void button_IN_SetPull_Click(int inNum, const std::string& state);
    void buttonSaveInPullUps_Click();
    void buttonResetCANStep_Click();
    void buttonDriverOn_Click();
    void buttonDriverOff_Click();
    void buttonIHOLDSet_Click(uint8_t ihold, uint8_t irun, uint8_t iholddelay);
    void buttonSPEEDTHRSSet_Click(uint8_t threshold);
    void buttonCOOLCONF_Click();
    void buttonEncoderConfig_Click(uint8_t polarity, uint8_t delta, uint16_t toTurn);
    void buttonGLOBAL_SCALER_Click(uint8_t scaler);
    void trackBarPositioning_Velocity_Scroll(bool isPositioning);
    void buttonAutosender_Click(uint8_t type, uint8_t delayMs);
    void buttonTestUSBCAN_Click();
    void buttonMotorTorque_Click();
    void buttonMotorSpeed_Click();
    void buttonAbsolutePositionRotorUint_Click();
    void buttonAlarmCode_Click();

    void buttonUpdate_Click();
    void buttonStopUpdate_Click();

    // --- Внутренние методы и переменные ---
    void createMechanismObj0(uint8_t boardId, uint8_t groupId);
    void dataUpdateLoop();

    // --- Обработчики обратных вызовов ---
    void myAnswerControlCallback(uint8_t* pNumBoardParse, uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* pCmdInWork, uint8_t* ptmpErrors);
    void myAnswerConfigCallback(uint8_t* pNumBoardParse);
    void myAnswerCallback(uint8_t* pNumBoardParse, uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3);

    std::unique_ptr<HidDevice> hidDevice;
    std::unique_ptr<Mechanism> mechanismObj0;
    std::unique_ptr<ScenarioBuilder> scenarioBuilder;

    // Для потока обновления
    std::thread updateThread;
    std::atomic<bool> isRunning{false};
    
    // Данные для HID
    uint16_t vendorId = 1155;
    uint16_t productId = 22399;
};

// --- Реализация методов класса CanController ---

CanController::CanController() {
    hidDevice = std::make_unique<HidDevice>();
    scenarioBuilder = std::make_unique<ScenarioBuilder>();
}

CanController::~CanController() {
    buttonStopUpdate_Click(); // Останавливаем поток, если он работает
}

void CanController::createMechanismObj0(uint8_t boardId, uint8_t groupId) {
    if (!mechanismObj0) {
        mechanismObj0 = std::make_unique<Mechanism>(boardId, groupId);
        
        // Настройка обратных вызовов с использованием std::bind
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

void CanController::initializeDevice(uint16_t vendorId, uint16_t productId) {
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

// --- Простые команды ---
void CanController::buttonMoveForward_Click() { if(mechanismObj0) mechanismObj0->runForavrd(); }
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


// --- Команды с параметрами ---
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

// --- Потоковая логика ---
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
        usleep(100000); // 100ms задержка, чтобы не загружать процессор
    }
}

// --- Обработчики обратных вызовов ---
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

// --- Интерактивный терминал ---
void CanController::runTerminal() {
    std::cout << "Консоль управления CAN-Step. Введите 'help' для списка команд." << std::endl;
    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "exit") {
            break;
        } else if (command == "help") {
            std::cout << "Доступные команды:\n"
                      << "  init\n"
                      << "  forward\n"
                      << "  backward\n"
                      << "  stop\n"
                      << "  homing_zero\n"
                      << "  homing_max\n"
                      << "  set_pos <position>\n"
                      << "  set_board <id>\n"
                      << "  set_group <id>\n"
                      << "  update_start\n"
                      << "  update_stop\n"
                      << "  exit\n"
                      << "..." << std::endl;
        } else if (command == "init") {
            initializeDevice(0,0);
        } else if (command == "forward") {
            buttonMoveForward_Click();
        } else if (command == "backward") {
            buttonMoveBackward_Click();
        } else if (command == "stop") {
            buttonStop_Click();
        } else if (command == "homing_zero") {
            buttonHomingZero_Click();
        } else if (command == "homing_max") {
            buttonHomingMax_Click();
        } else if (command == "set_pos") {
            uint32_t pos;
            ss >> pos;
            buttonCurrentPositionSet_Click(pos);
        } else if (command == "set_board") {
            int id;
            ss >> id;
            buttonNumBoard_Click(static_cast<uint8_t>(id));
        } else if (command == "set_group") {
            int id;
            ss >> id;
            buttonNumGroup_Click(static_cast<uint8_t>(id));
        } else if (command == "update_start") {
            buttonUpdate_Click();
        } else if (command == "update_stop") {
            buttonStopUpdate_Click();
        } else {
            std::cout << "Неизвестная команда: " << command << std::endl;
        }
    }
}