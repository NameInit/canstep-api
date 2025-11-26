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


class CanController : public std::enable_shared_from_this<CanController> {
public:
	CanController();
	~CanController();

	void buttonOpenCOM_Click(uint16_t vendorId=0x0483, uint16_t productId=0x577f);
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
	void buttonEnPolarity_Click(const std::string& u8Inverting);
	void buttonAl_CLRPolarity_Click(const std::string& u8Inverting);
	void buttonAl_OBrakePolarity_Click(const std::string& u8Inverting);
	void buttonAl_ORezervPolarity_Click(const std::string& u8Inverting);
	void buttonDirPolarity_Click(const std::string& u8Inverting);
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
	void startSceExecutionButton_Click(const std::string& mechFile = "mechs.txt", const std::string& bindingFile = "scenario_bindings.txt");
	void stopSceExecutionButton_Click();
	void resetAllDriversFaultButton_Click();
	void selectMechSetButton_Click();
	void saveSceExecSettings_Click(const std::string& mechFile = "mechs.txt", const std::string& bindingFile = "scenario_bindings.txt");
	void sceExecStopAllMech_Click(const std::string& stopFile = "full_stop.sce");
	void button1_Click_1();
	void sceExecConfigModeCheckbox_CheckedChanged();

	void buttonUpdate_Click();
	void buttonStopUpdate_Click();

	void createMechanismObj0(uint8_t boardId, uint8_t groupId);
	void dataUpdateLoop();

	void myAnswerControlCallback(uint8_t* pNumBoardParse, uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* pCmdInWork, uint8_t* ptmpErrors);
	void myAnswerConfigCallback(uint8_t* pNumBoardParse);
	void myAnswerCallback(uint8_t* pNumBoardParse, uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3);

	void setEncoderActive(bool set) { mechanismObj0->setEncoderActive(set); }

	void executeAllCommandsSilent();
	void executeAllCommandsSilentThread();
	void executeAllCommands();
	void executeAllCommandsThread();

	std::unique_ptr<HidDevice> hidDevice;
	std::unique_ptr<Mechanism> mechanismObj0;
	std::unique_ptr<ScenarioBuilder> scenarioBuilder;

	std::thread updateThread;
	std::atomic<bool> isRunning{false};

	uint16_t vendorId = 1155;
	uint16_t productId = 22399;

	bool runningScenario;

	//getters
	public:
		uint8_t getNumBoard() { return mechanismObj0->getNumBoard(); }
		bool isConnected() { return hidDevice->IsConnected(); }
		bool isRunningMech() { return false; }
		uint32_t getSteps() { return mechanismObj0->getSteps(); }
		float  getSpeed() { return mechanismObj0->getSpeed(0); }
		uint32_t getStartPosition() { return mechanismObj0->getStartPosition(0); }
		uint32_t getEndPosition() { return mechanismObj0->getEndPosition(0); }
		uint32_t getPosition() { return mechanismObj0->GetPosition(0); }
		uint8_t getAccel() { return mechanismObj0->getCurrAccel(0); }
		uint8_t getDecel() { return mechanismObj0->getCurrDecel(0); }
};