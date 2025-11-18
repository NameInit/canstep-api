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
#include <future>

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
    void buttonSensor1Polarity_Click(const std::string& sInverting);
    void buttonSensor2Polarity_Click(const std::string& sInverting);
    void buttonSensor3Polarity_Click(const std::string& sInverting);
    void buttonSensor4Polarity_Click(const std::string& sInverting);
    void buttonSensor1Dir_Click(const std::string& u8Inverting);
    void buttonSensor2Dir_Click(const std::string& u8Inverting);
    void buttonSensor3Dir_Click(const std::string& u8Inverting);
    void buttonSensor4Dir_Click(const std::string& u8Inverting);
    void buttonEnPolarity_Click(uint8_t u8Inverting);
    void buttonAl_CLRPolarity_Click(uint8_t u8Inverting);
    void buttonAl_OBrakePolarity_Click(uint8_t u8Inverting);
    void buttonAl_ORezervPolarity_Click(uint8_t u8Inverting);
    void buttonDirPolarity_Click(uint8_t u8Inverting);
    void buttonSRVRDYPolarity_Click(const std::string& u8Inverting);
    void buttonINPOSPolarity_Click(const std::string& u8Inverting);
    void buttonFAULTPolarity_Click(const std::string& u8Inverting);
    void buttonBrakePolarity_Click(const std::string& u8Inverting);

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
    void button_MicroSteps_Click(uint32_t microsteps);
    void button_StepsTurn_Click(uint32_t steps);
    void buttonSaveInPullUps_Click();
    void buttonResetCANStep_Click();
    void buttonDriverOn_Click();
    void buttonDriverOff_Click();
    void buttonIHOLDSet_Click(uint8_t ihold, uint8_t irun, uint8_t iholddelay);
    void buttonSPEEDTHRSSet_Click(uint8_t threshold);
    void trackBarPositioning_Velocity_Scroll(bool isPositioning);
    void buttonAutosender_Click(uint8_t type, uint8_t delayMs);
    void buttonTestUSBCAN_Click();
    void buttonMotorTorque_Click();
    void buttonMotorSpeed_Click();
    void buttonAbsolutePositionRotorUint_Click();
    void buttonAlarmCode_Click();
    void resetLostCounters_Click();
    void buttonEncoderConfig_Click(uint8_t encoderPolarity, uint8_t encoderDelta, uint16_t encoderToTurn);
    void buttonGLOBAL_SCALER_Click(uint8_t globalScaler);
    void buttonCOOLCONF_Click(uint8_t Seup, uint8_t Sedn, bool Seimen, bool SGFilter, uint8_t Semin, uint8_t Semax, uint8_t SGThreshold);

    void resetMechDriver(const std::string& selectedItem);
    void resetMechController_Click(const std::string& selectedItem);
    void executeSelectedCommandButton_Click(const std::string &selectedCommand);
    void executeAllCommandsButton_Click();
    void buttonFullStop_Click();
    void stopExecutionButton_Click();
    void refrshMechButton_Click();
    void endMechRefresh_Click();
    void removeMechButton_Click(const std::string &selectedItem);
    void addMechButton_Click(const std::string& mechName, uint8_t board, uint8_t group);
    void button1_Click(const std::string& selectedItem);
    void button2_Click(const std::string& mechName, const std::string& action, const std::string& param);
    void saveMechsToFile_Click(const std::string& filename);
    void readMechsFromFile_Click(const std::string& filename);
    void saveCommandsButton_Click(const std::string& filename);
    void loadCommandsButton_Click(const std::string& filename);
    void button3_Click();
    void buttonDebugMode_Click(const std::string &selectedItem);
    void refreshStateButton_Click();
    void autoUpdateTable_CheckedChanged();
    void startSceExecutionButton_Click(const std::string& mechFile, const std::string& bindingFile);
    void stopSceExecutionButton_Click();
    void resetAllDriversFaultButton_Click();
    void selectMechSetButton_Click();
    void saveSceExecSettings_Click(const std::string& mechFile, const std::string& bindingFile);
    void sceExecStopAllMech_Click(const std::string& stopFile);
    void button1_Click_1();
    void sceExecConfigModeCheckbox_CheckedChanged();

    void buttonUpdate_Click();
    void buttonStopUpdate_Click();

    void createMechanismObj0(uint8_t boardId, uint8_t groupId);
    void dataUpdateLoop();

    void myAnswerControlCallback(uint8_t* pNumBoardParse, uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* pCmdInWork, uint8_t* ptmpErrors);
    void myAnswerConfigCallback(uint8_t* pNumBoardParse);
    void myAnswerCallback(uint8_t* pNumBoardParse, uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3);

    void executeAllCommandsSilent() {
        std::thread executionThread([this]() {
            this->executeAllCommandsSilentThread();
        });
        executionThread.detach();
    }

    void executeAllCommandsSilentThread() {
		runningScenario = true;

	// 	// Show "Executing..." in status label
	// 	this->Invoke(gcnew MethodInvoker(this, &MyForm::setStatusExecuting));

		for (int i = 0; i < scenarioBuilder->commandQueue.size(); i++) {
			if (!runningScenario) break;

			std::string &command = scenarioBuilder->commandQueue[i];

	// 		// Parse mech name
	// 		array<String^>^ parts = command->Split(' ');
	// 		String^ mechName = parts->Length > 0 ? parts[0] : "";

	// 		// Store parameters temporarily
	// 		currentCommand = command;
	// 		currentMechName = mechName;

	// 		// Update command and mech labels using MethodInvoker
	// 		this->Invoke(gcnew MethodInvoker(this, &MyForm::UpdateLabelsFromFields));

			scenarioBuilder->executeSingleCommand(command);
		}

	// 	this->Invoke(gcnew MethodInvoker(this, &MyForm::resetExecutionLabels));
		runningScenario = false;
	}

    void executeAllCommands() {
        std::thread executionThread([this]() {
            this->executeAllCommandsThread();
        });
        executionThread.detach();
		// System::Threading::Thread^ executionThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &MyForm::executeAllCommandsThread));
		// executionThread->Start();
	}

    void executeAllCommandsThread() {
		runningScenario = true;
		for (int i = 0; i < scenarioBuilder->commandQueue.size(); i++) {
			if (!runningScenario) break; // ���������, �� ������ �� ������ "����������"

	// 		updateCommandHighlight(i);
			scenarioBuilder->executeSingleCommand(scenarioBuilder->commandQueue[i]);
		}
	// 	resetCommandHighlight();
		runningScenario = false;
	}

    std::unique_ptr<HidDevice> hidDevice;
    std::unique_ptr<Mechanism> mechanismObj0;
    std::unique_ptr<ScenarioBuilder> scenarioBuilder;

    std::thread updateThread;
    std::atomic<bool> isRunning{false};

    uint16_t vendorId = 1155;
    uint16_t productId = 22399;

    bool runningScenario;
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
    
    mechanismObj0->ClrAsks();
    usleep(10000);
    mechanismObj0->SetAsk(AskPosition);
    mechanismObj0->SetAsk(AskHomings);
    mechanismObj0->SetAsk(AskInputs);
    mechanismObj0->SetAsk(AskCurrOutputs);
    mechanismObj0->SetAsk(AskGroup);
}

void CanController::buttonOpenCOM_Click(uint16_t vendorId=0x0483, uint16_t productId=0x577f) {
    createMechanismObj0(0, 0);
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

void CanController::buttonSensor1Polarity_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="Inverted") {u8Inverting=Inverted;} else if(sInverting=="NotInverted") {u8Inverting=NotInverted;} mechanismObj0->setHomingAPolarity(u8Inverting); }
void CanController::buttonSensor2Polarity_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="Inverted") {u8Inverting=Inverted;} else if(sInverting=="NotInverted") {u8Inverting=NotInverted;} mechanismObj0->setHomingBPolarity(u8Inverting); }
void CanController::buttonSensor3Polarity_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="Inverted") {u8Inverting=Inverted;} else if(sInverting=="NotInverted") {u8Inverting=NotInverted;} mechanismObj0->setHomingCPolarity(u8Inverting); }
void CanController::buttonSensor4Polarity_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="Inverted") {u8Inverting=Inverted;} else if(sInverting=="NotInverted") {u8Inverting=NotInverted;} mechanismObj0->setHomingDPolarity(u8Inverting); }
void CanController::buttonSensor1Dir_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="None") {u8Inverting==DirOff;} else if(sInverting=="Forward") {u8Inverting=DirFwd;} else if(sInverting=="Backward") {u8Inverting=DirBwd;} mechanismObj0->setHomingADirection(u8Inverting); }
void CanController::buttonSensor2Dir_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="None") {u8Inverting==DirOff;} else if(sInverting=="Forward") {u8Inverting=DirFwd;} else if(sInverting=="Backward") {u8Inverting=DirBwd;} mechanismObj0->setHomingBDirection(u8Inverting); }
void CanController::buttonSensor3Dir_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="None") {u8Inverting==DirOff;} else if(sInverting=="Forward") {u8Inverting=DirFwd;} else if(sInverting=="Backward") {u8Inverting=DirBwd;} mechanismObj0->setHomingCDirection(u8Inverting); }
void CanController::buttonSensor4Dir_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="None") {u8Inverting==DirOff;} else if(sInverting=="Forward") {u8Inverting=DirFwd;} else if(sInverting=="Backward") {u8Inverting=DirBwd;} mechanismObj0->setHomingDDirection(u8Inverting); }
void CanController::buttonEnPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setEnPolarity(u8Inverting); }
void CanController::buttonAl_CLRPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setAL_CLRPolarity(u8Inverting); }
void CanController::buttonAl_OBrakePolarity_Click(uint8_t u8Inverting){ mechanismObj0->setOBRAKEPolarity(u8Inverting); }
void CanController::buttonAl_ORezervPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setOReservPolarity(u8Inverting); }
void CanController::buttonDirPolarity_Click(uint8_t u8Inverting){ mechanismObj0->setDIRPolarity(u8Inverting); }
void CanController::buttonSRVRDYPolarity_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="Inverted") {u8Inverting=Inverted;} else if(sInverting=="NotInverted") {u8Inverting=NotInverted;} mechanismObj0->setSRVRDYPolarity(u8Inverting); }
void CanController::buttonINPOSPolarity_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="Inverted") {u8Inverting=Inverted;} else if(sInverting=="NotInverted") {u8Inverting=NotInverted;} mechanismObj0->setINPOSPolarity(u8Inverting); }
void CanController::buttonFAULTPolarity_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="Inverted") {u8Inverting=Inverted;} else if(sInverting=="NotInverted") {u8Inverting=NotInverted;} mechanismObj0->setFAULTPolarity(u8Inverting); }
void CanController::buttonBrakePolarity_Click(const std::string& sInverting){ uint8_t u8Inverting=UnknownInverted; if(sInverting=="Inverted") {u8Inverting=Inverted;} else if(sInverting=="NotInverted") {u8Inverting=NotInverted;} mechanismObj0->setBRAKEPolarity(u8Inverting); }

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

void CanController::resetLostCounters_Click() { mechanismObj0->clrPossibleLostFrame(); }
void CanController::buttonEncoderConfig_Click(uint8_t encoderPolarity, uint8_t encoderDelta, uint16_t encoderToTurn) { mechanismObj0->setEncoderConfig(encoderPolarity,encoderDelta,encoderToTurn); }
void CanController::buttonGLOBAL_SCALER_Click(uint8_t globalScaler) { mechanismObj0->setGLOBAL_SCALER(globalScaler); }
void CanController::buttonCOOLCONF_Click(uint8_t Seup, uint8_t Sedn, bool Seimen, bool SGFilter, uint8_t Semin, uint8_t Semax, uint8_t SGThreshold) { mechanismObj0->setCOOLCONF(Seup,Sedn,Seimen,SGFilter,Semin,Semax,SGThreshold); }

void CanController::resetMechDriver(const std::string& selectedItem){
    if(selectedItem.empty()){
        std::cerr << "Empty string in resetMechDriver" << std::endl;
        return ;
    }
    
    size_t pos = selectedItem.find('-');
    std::string key=(pos!=std::string::npos) ? selectedItem.substr(0,pos) : selectedItem;
    if(key.length()==0){
        std::cerr << "Key is zero len" << std::endl;
        return ;
    }
    
    auto it = scenarioBuilder->mechanisms.find(key);
    if(it!=scenarioBuilder->mechanisms.end() && it->second!=nullptr){
        it->second->ResetDRVError();
    }
    else{
        std::cerr << "Not found key in mechanisms";
        return ;
    }

    return ;
}

void CanController::resetMechController_Click(const std::string& selectedItem){
    if(selectedItem.empty()){
        std::cerr << "Empty string in resetMechController_Click" << std::endl;
        return ;
    }

    size_t pos = selectedItem.find('-');
    std::string key=(pos!=std::string::npos) ? selectedItem.substr(0,pos) : selectedItem;
    if(key.length()==0){
        std::cerr << "Key is zero len" << std::endl;
        return ;
    }

    auto it = scenarioBuilder->mechanisms.find(key);
    if(it!=scenarioBuilder->mechanisms.end() && it->second!=nullptr){
        mechanismObj0->SetUpdater(eCANUpdaterOff);
        it->second->Reset();
    }
    else{
        std::cerr << "Not found key in mechanisms";
        return ;
    }
}

void CanController::executeSelectedCommandButton_Click(const std::string &selectedCommand){
    scenarioBuilder->executeSingleCommand(selectedCommand);
    return ;
}

void CanController::executeAllCommandsButton_Click() {
	// scenarioBuilder->executeCommands();
	executeAllCommands();
    return ;
}

void CanController::buttonFullStop_Click(){
    scenarioBuilder->stopAllMechanisms();
    return ;
}

void CanController::stopExecutionButton_Click(){
    runningScenario=false;
    //
    // resetCommandHighlight();
    // if(commandListBox->InvokeRequired) {
    //     commandListBox->Invoke(gcnew Action(this, &MyForm::resetCommandHighlight));
    // }
    // else{
    //     commandListBox->SelectedIndex = -1;
    // }
    return ;
}

void CanController::refrshMechButton_Click(){
    mechanismObj0->SetUpdater(eCANUpdaterCentral);
	// if (backgroundWorker1->IsBusy != true)
	// {
	// 	backgroundWorker1->RunWorkerAsync();
	// }
    return ;
}

void CanController::endMechRefresh_Click(){
    mechanismObj0->SetUpdater(eCANUpdaterOff);
	// if (backgroundWorker1->IsBusy == true)
	// {
	// 	backgroundWorker1->CancelAsync();
	// }
    return ;
}

void CanController::removeMechButton_Click(const std::string &selectedItem){
    if(selectedItem.empty()){
        std::cerr << "Empty string in removeMechButton_Click" << std::endl;
        return ;
    }

    size_t pos = selectedItem.find('-');
    std::string key=(pos!=std::string::npos) ? selectedItem.substr(0,pos) : selectedItem;
    if(key.length()==0){
        std::cerr << "Key is zero len" << std::endl;
        return ;
    }

    auto it = scenarioBuilder->mechanisms.find(key);
    if(it!=scenarioBuilder->mechanisms.end() && it->second!=nullptr){
        scenarioBuilder->mechanisms.erase(it);
        // LoadMechanisms()
    }
    else{
        std::cerr << "Not found key in mechanisms";
        return ;
    }
    // void LoadMechanisms()
	// {
	// 	mechListBox->Items->Clear();
	// 	for each (String ^ key in scenarioBuilder->mechanisms->Keys)
	// 	{
	// 		Mechanism^ mech = scenarioBuilder->mechanisms[key];
	// 		String^ item = String::Format("{0} - �����: {1}, ������: {2}", key, mech->getNumBoard(), mech->getGroup(true));
	// 		mechListBox->Items->Add(item);
	// 	}
	// }

    // if (mechListBox->SelectedItem != nullptr)
	// {
	// 	String^ selectedItem = mechListBox->SelectedItem->ToString();
	// 	array<String^>^ parts = selectedItem->Split('-');
	// 	String^ key = parts[0]->Trim();

	// 	scenarioBuilder->mechanisms->Remove(key);
	// 	LoadMechanisms();
	// }
}

void CanController::addMechButton_Click(const std::string& mechName, uint8_t board, uint8_t group){
    if(mechName.empty() || scenarioBuilder->mechanisms.find(mechName) != scenarioBuilder->mechanisms.end())
    {
        std::cerr << "Incorrect mechName" << std::endl;
        return;
    }

    scenarioBuilder->mechanisms[mechName] = std::make_unique<Mechanism>(board,group);
    scenarioBuilder->mechanisms[mechName]->SetHidDevice(hidDevice.get());
    scenarioBuilder->mechanisms[mechName]->setGroup(group);
    scenarioBuilder->mechanisms[mechName]->SetAsk(_AskEnum::AskPosition);
    scenarioBuilder->mechanisms[mechName]->SetAsk(_AskEnum::AskHomings);
    scenarioBuilder->mechanisms[mechName]->SetAsk(_AskEnum::AskInputs);
    scenarioBuilder->mechanisms[mechName]->SetAsk(_AskEnum::AskCurrOutputs);
    
    // LoadMechanisms();
    return ;
}

void CanController::button1_Click(const std::string& selectedItem) {
    if(selectedItem.empty()){
        std::cerr << "Void selectedItem" << std::endl;
        return ;
    }
    scenarioBuilder->commandQueue.erase(std::remove(
        scenarioBuilder->commandQueue.begin(),scenarioBuilder->commandQueue.end(),selectedItem
    ),scenarioBuilder->commandQueue.end());
    // LoadCommands();
    return ;
	// if (commandListBox->SelectedItem != nullptr)
	// {
	// 	scenarioBuilder->commandQueue->Remove(commandListBox->SelectedItem->ToString());
	// 	LoadCommands();
	// }
}

void CanController::button2_Click(const std::string& mechName, const std::string& action, const std::string& param){
    if(mechName.empty() || action.empty() || param.empty()){
        std::cerr << "Incorrect arguments in button2_Click" << std::endl;
        return ;
    }
    scenarioBuilder->commandQueue.emplace_back(mechName+' '+action+' '+param);
    // LoadCommands();
    return ;

    // if (mechanismComboBox->SelectedItem == nullptr || actionComboBox->SelectedItem == nullptr)
	// 	return;

	// String^ mechName = mechanismComboBox->SelectedItem->ToString();
	// String^ action = actionComboBox->SelectedItem->ToString();
	// String^ param = parameterTextBox->Text;

	// if (action == "SET_STEPS" && String::IsNullOrWhiteSpace(param))
	// {
	// 	MessageBox::Show("�� ������ �������� ��� SET_STEPS", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
	// 	return;
	// }

	// String^ command = mechName + " " + action;
	// if (!String::IsNullOrWhiteSpace(param)) command += " " + param;

	// scenarioBuilder->commandQueue->Add(command);
	// LoadCommands();
	// parameterTextBox->Clear();
}

void CanController::saveMechsToFile_Click(const std::string& filename){
    scenarioBuilder->saveMechanismsToFile(filename);
    // System::Threading::Thread^ staThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &MyForm::ShowSaveMechanismsDialog));
	// staThread->SetApartmentState(System::Threading::ApartmentState::STA);
	// staThread->Start();
    return ;
}

void CanController::readMechsFromFile_Click(const std::string& filename){
    scenarioBuilder->loadMechanismsFromFile(filename);
    // System::Threading::Thread^ staThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &MyForm::ShowOpenMechanismsDialog));
	// staThread->SetApartmentState(System::Threading::ApartmentState::STA);
	// staThread->Start();
    return ;
}

void CanController::saveCommandsButton_Click(const std::string& filename) {
    scenarioBuilder->saveCommandsToFile(filename);
	// System::Threading::Thread^ staThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &MyForm::ShowSaveCommandsDialog));
	// staThread->SetApartmentState(System::Threading::ApartmentState::STA);
	// staThread->Start();
    return ;
}

void CanController::loadCommandsButton_Click(const std::string& filename) {
    scenarioBuilder->loadCommandsFromFile(filename);
	// System::Threading::Thread^ staThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &MyForm::ShowOpenCommandsDialog));
	// staThread->SetApartmentState(System::Threading::ApartmentState::STA);
	// staThread->Start();
    return ;
}

void CanController::button3_Click() {
	// LoadMechanismsList();
    return ;
}

void CanController::buttonDebugMode_Click(const std::string &selectedItem) {
    if(selectedItem.empty()){
        std::cerr << "Error selectedItem in buttonDebugMode_Click" << std::endl;
        return ;
    }
	scenarioBuilder->mechanisms[selectedItem]->Debug_on();
    return ;
}

void CanController::refreshStateButton_Click() {
	// UpdateMechanismStateGrid();
    // void UpdateMechanismStateGrid() {
	// 	mechStateGridView->Rows->Clear();

	// 	mechStateGridView->Rows->Clear();

	// 	List<array<Object^>^>^ stateList = scenarioBuilder->getMechanismsStateList();

	// 	for each (array<Object^> ^ row in stateList) {
	// 		mechStateGridView->Rows->Add(row);


	// 		// �������� ������ ������� FAULT
	// 		int faultColumnIndex = mechStateGridView->Columns["FAULT"]->Index;

	// 		// ��������� ��������� FAULT ��� ���� ������
	// 		bool isFault = Convert::ToBoolean(row[faultColumnIndex]);

	// 		// ��������� ����������� � ����������� �� �������� FAULT
	// 		int rowIndex = mechStateGridView->Rows->Count - 1;  // ������ ������ ��� ����������� ������
	// 		if (isFault) {
	// 			mechStateGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Color::Red;
	// 			mechStateGridView->Rows[rowIndex]->DefaultCellStyle->ForeColor = Color::White;
	// 		}
	// 		else {
	// 			mechStateGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Color::White;
	// 			mechStateGridView->Rows[rowIndex]->DefaultCellStyle->ForeColor = Color::Black;
	// 		}

	// 	}
	// }
    return ;
}

void CanController::autoUpdateTable_CheckedChanged() {
	// if (autoUpdateTable->Checked) {
	// 	autoTableUpdate = true;
	// }
	// else {
	// 	autoTableUpdate = false;
	// }
    return ;
}

void CanController::startSceExecutionButton_Click(const std::string& mechFile = "mechs.txt", const std::string& bindingFile = "scenario_bindings.txt")
{
    // 1. Load Mechs
    std::ifstream mechStream(mechFile);
    if (mechStream.good()) {
        std::string line;
        while (std::getline(mechStream, line)) {
            std::vector<std::string> parts;
            std::istringstream iss(line);
            std::string part;
            
            while (iss >> part) {
                parts.push_back(part);
            }
            
            if (parts.size() >= 3) {
                std::string name = parts[0];
                int board = std::stoi(parts[1]);
                int group = std::stoi(parts[2]);
                
                auto mech = std::make_unique<Mechanism>(static_cast<uint8_t>(board), static_cast<uint8_t>(group));
                mech->SetHidDevice(hidDevice.get());
                usleep(150000);
                mech->setGroup(static_cast<uint8_t>(group));
                usleep(150000);
                mech->ClrAsks();
                usleep(150000);
                mech->SetAsk(_AskEnum::AskPosition);
                usleep(150000);
                mech->SetAsk(_AskEnum::AskGroup);
                usleep(150000);
                mech->SetAsk(_AskEnum::AskHomings);
                usleep(150000);
                mech->SetAsk(_AskEnum::AskInputs);
                usleep(150000);
                mech->SetAsk(_AskEnum::AskCurrOutputs);
                usleep(1500000);
                
                if (mech) {
                    mech->setAutosender(4, 10, 0);
                    usleep(150000);
                }
                if (mech) {
                    mech->setUpdateType(true);
                }
                usleep(50000);
                
                scenarioBuilder->addMechanism(name, std::move(mech));
            }
        }
        mechStream.close();
    }

    usleep(1500000);

    // 2. Load scenario bindings
    auto bindingStream = std::make_unique<std::ifstream>(bindingFile);
    if (!bindingStream->good()) return;

    std::string bindLine;
    while (std::getline(*bindingStream, bindLine)) {
        size_t pos = bindLine.find('=');
        if (pos != std::string::npos) {
            std::string buttonName = bindLine.substr(0, pos);
            std::string filePath = bindLine.substr(pos + 1);
            // ну тут ui было дальше
        }
    }
    return ;
}

void CanController::stopSceExecutionButton_Click() {
	mechanismObj0->SetUpdater(eCANUpdaterOff);
	// if (backgroundWorker1->IsBusy == true)
	// {
		// backgroundWorker1->CancelAsync();
	// }
    return ;
}

void CanController::resetAllDriversFaultButton_Click() {
    for(auto& it : scenarioBuilder->mechanisms){
        it.second->ResetDRVError();
    }
    return ;
}

void CanController::selectMechSetButton_Click() {
	// System::Threading::Thread^ staThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &MyForm::ShowOpenMechanismsDialog));
	// staThread->SetApartmentState(System::Threading::ApartmentState::STA);
	// staThread->Start();
    return ;
}

void CanController::saveSceExecSettings_Click(const std::string& mechFile = "mechs.txt", const std::string& bindingFile = "scenario_bindings.txt") {
	// 1. Save Scenario Bindings
    std::ofstream writer(bindingFile);
    // scenarioBindings - ui
	// StreamWriter^ writer = gcnew StreamWriter("scenario_bindings.txt");
	// for each (auto pair in scenarioBindings) {
	// 	writer->WriteLine(pair.Key->Name + "=" + pair.Value);
	// }
	// writer->Close();

	// 2. Save Mechanisms
	std::ofstream mechWriter(mechFile);
	for(auto& it : scenarioBuilder->mechanisms) {
		Mechanism* mech = it.second.get();
		mechWriter << it.first << " "
                          << static_cast<int>(mech->getNumBoard()) << " "
                          << static_cast<int>(mech->getGroup(false)) << std::endl;
	}
	mechWriter.close();
    return ;
}


void CanController::sceExecStopAllMech_Click(const std::string& stopFile = "full_stop.sce") {
    runningScenario = false;
    
    std::ifstream file(stopFile);
    if (file.good()) {
        file.close();
        scenarioBuilder->loadCommandsFromFile(stopFile);
        executeAllCommandsSilent();
    }
    
    scenarioBuilder->stopAllMechanisms();
    return ;
}

void CanController::button1_Click_1() {
	runningScenario = false;
	// resetExecutionLabels();
    // void resetExecutionLabels() {
	// 	sceExecSceStatusLabel->Text = "��������";
	// 	sceExecCurrCmdLabel->Text = "";
	// 	sceExecCurrMechLabel->Text = "";
	// }
    return ;
}

void CanController::sceExecConfigModeCheckbox_CheckedChanged() {
	// if (sceExecConfigModeCheckbox->Checked)
	// 	for (int i = 3; i <= 41; i += 2) {
	// 		Button^ selectBtn = (Button^)this->Controls->Find("button" + (i + 1).ToString(), true)[0];

	// 		selectBtn->Visible = TRUE;
	// 	}
	// else {
	// 	for (int i = 3; i <= 41; i += 2) {
	// 		Button^ selectBtn = (Button^)this->Controls->Find("button" + (i + 1).ToString(), true)[0];

	// 		selectBtn->Visible = FALSE;
	// 	}

	// }
    return ;
}

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