#pragma once

#ifndef __MECHANISM_H_
#define __MECHANISM_H_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <cerrno>

#include "Typedefs.h"
#include "Defs.h"
#include "DefsCANStep.h"
#include "TypesCANStep.h"
#include "HidDevice.h"

void MechCallback(USBCANFrame* _USBCANFrame);

using CAN_Parsing_Callback_ANSWER_CONTROL_Delegate = std::function<void(uint8_t* pNumBoardParse, uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* pCmdInWork, uint8_t* ptmpErrors)>;
using CAN_Parsing_Callback_ANSWER_CONFIG_Delegate = std::function<void(uint8_t* pNumBoardParse)>;
using CAN_Parsing_Callback_ANSWER_Delegate = std::function<void(uint8_t* pNumBoardParse, uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3)>;

class Mechanism
{
private:
	uint8_t		NumBoard;
	uint8_t		HomingAPolarity;
	uint8_t		HomingBPolarity;
	uint8_t		HomingCPolarity;
	uint8_t		HomingDPolarity;
	uint32_t	StartPosition;
	uint32_t	EndPosition;
	uint32_t	Range;
	uint8_t		Accel;
	uint8_t		Decel;
	uint8_t 	HomingADirection;
	uint8_t 	HomingBDirection;
	uint8_t 	HomingCDirection;
	uint8_t 	HomingDDirection;
	float 		maxSpeed;
	float 		CurrSpeed;
	uint32_t	DeltaPosition;
	uint32_t	u32SetPosition;
	uint8_t 	SRVRDYPolarity;
	uint8_t 	INPOSPolarity;
	uint8_t 	FAULTPolarity;
	uint8_t 	BRAKEPolarity;
	uint8_t 	EnPolarity;
	uint8_t 	AL_CLRPolarity;
	uint8_t 	OBRAKEPolarity;
	uint8_t 	OReservPolarity;
	uint8_t		DIRPolarity;
	uint8_t		Group;
	uint32_t	MicrostepsToStep;
	uint32_t	StepsToTurn;
	uint32_t	InputsToVccGND;
	uint8_t		EncoderActive;
	uint8_t		TMC_IHOLD;
	uint8_t		TMC_IRUN;
	uint8_t		IHOLDDELAY;
	uint8_t		TMC_TPWMTHRS;
	uint8_t		TMC_COOLCONF;
	uint8_t		EncoderPolarityDeltaTurn;
	uint8_t		GLOBAL_SCALER;
	uint8_t		Freewheel;
	uint8_t		run_task;
	uint8_t		stop_task;
	uint8_t		dir_move;
	uint8_t		move_mode;
	uint8_t		rec_step;
	uint8_t		rec_veloc;
	uint8_t		accel_up;
	uint8_t		accel_down;
	uint8_t		channel;
	_NumCommand num_command;
	uint32_t Steps;
	float Speed;
	uint8_t CurrAccel;
	uint8_t CurrDecel;
	bool Emergency;
	bool InWork;
	bool HomingA;
	bool HomingB;
	bool HomingC;
	bool HomingD;
	bool SRVRDY;
	bool INPOS;
	bool FAULT;
	bool BRAKE;
	uint16_t NumInNoPullupDown;
	uint16_t NumInPullUp;
	uint16_t NumInPullDown;
	bool OutEn;
	bool OutDIR;
	bool OutAL_CLR;
	bool OutBRAKE;
	bool OutReserv;
	uint8_t NumOutZState;
	uint8_t NumOutHiState;
	uint8_t NumOutLoState;
	uint32_t	ReadPosition;
	uint8_t		ReadHomeAState;
	uint8_t		ReadHomeBState;
	uint8_t		ReadHomeCState;
	uint8_t		ReadHomeDState;
	uint8_t		ReadOut_Dir;
	uint8_t		ReadOut_EN;
	uint8_t		ReadOut_AL_CLR;
	uint8_t		ReadOut_OBRAKE;
	uint8_t		ReadOut_ORESERV;
	uint8_t		ReadHomingAPolarity;
	uint8_t		ReadHomingBPolarity;
	uint8_t		ReadHomingCPolarity;
	uint8_t		ReadHomingDPolarity;
	uint32_t	ReadStartPosition;
	uint32_t	ReadEndPosition;
	uint32_t	ReadRange;
	uint8_t		ReadCurrAccel;
	uint8_t		ReadCurrDecel;
	uint8_t 	ReadHomingADirection;
	uint8_t 	ReadHomingBDirection;
	uint8_t 	ReadHomingCDirection;
	uint8_t 	ReadHomingDDirection;
	float		ReadSpeed;
	uint8_t		ReadAccel;
	uint8_t		ReadDecel;
	float 		ReadmaxSpeed;
	float 		ReadCurrSpeed;
	uint32_t	ReadDeltaPosition;
	uint8_t 	ReadSRVRDYPolarity;
	uint8_t 	ReadINPOSPolarity;
	uint8_t 	ReadFAULTPolarity;
	uint8_t 	ReadBRAKEPolarity;
	uint8_t 	ReadEnPolarity;
	uint8_t 	ReadAL_CLRPolarity;
	uint8_t 	ReadOBRAKEPolarity;
	uint8_t 	ReadOReservPolarity;
	uint8_t		ReadDIRPolarity;
	uint8_t		ReadGroup;
	uint32_t	ReadMicrostepsToStep;
	uint32_t	ReadStepsToTurn;
	uint32_t	ReadInputsToVccGND;
	uint8_t		ReadEncoderActive;
	uint8_t		ReadTMC_IHOLD;
	uint8_t		ReadTMC_IRUN;
	uint8_t		ReadIHOLDDELAY;
	uint8_t		ReadTMC_TPWMTHRS;
	uint8_t		ReadTMC_COOLCONF;
	uint8_t		ReadEncoderPolarityDeltaTurn;
	uint8_t		ReadGLOBAL_SCALER;
	uint8_t		ReadFreewheel;
	uint16_t	ReadNumInNoPullupDown;
	uint16_t	ReadNumInPullUp;
	uint16_t	ReadNumInPullDown;
	uint8_t		ReadNumOutZState;
	uint8_t		ReadNumOutHiState;
	uint8_t		ReadNumOutLoState;
	uint32_t ServoMotorTorque;
	uint32_t ServoMotorSpeed;
	uint32_t ServoAbsolutePositionRotorUint;
	uint32_t ServoAlarmCode;
	std::unique_ptr<CAN_input_conf> CANInputConfLoc;
	std::unique_ptr<CAN_input_contr> CanInLoc;
	bool		bParamLoaded;
	uint8_t		RescCMD;
	uint8_t		RescNumCMD;
	uint8_t		RescStartMotor;
	uint8_t		RescControlErrors;
	uint8_t		AutosenderType;
	uint8_t		AutosenderDelay;
	uint8_t CmdTransmitted;
	uint8_t NumCmdTransmitted;
	uint8_t CmdRescived;
	uint8_t NumCmdRescived;
	uint8_t u8CmdInWork;
	_CANUpdater Updater;
	uint16_t MaxAskSize;
	uint16_t NumAsks;
	uint16_t NumOneTaskAsks;
	uint16_t u16StageAsk;
	bool UpdateType;
	std::vector<uint8_t> AskNumBoard;
	std::vector<uint8_t> AskNumEnum;
	std::vector<uint8_t> AskOneTaskNumBoard;
	std::vector<uint8_t> AskOneTaskNumEnum;
	pthread_mutex_t hMutex;
	uint8_t u8OverlCreateErr;
	uint32_t DWLastError;
	uint8_t u8NumHIDErr;
	uint32_t u32NumHIDOkRead;
	uint32_t u8NumHIDOkFrame;
	uint32_t u32NumHIDOkAsk;
	uint32_t u32NumHIDOkEmergancy;
	uint32_t u32NumHIDOkParam;
	uint32_t u32NumHIDOkControl;
	uint32_t PossibleLostFrame;

public: HidDevice* pHidDevice;

private:
	CAN_Parsing_Callback_ANSWER_CONTROL_Delegate callbackAnswerControl;
	CAN_Parsing_Callback_ANSWER_CONFIG_Delegate callbackAnswerConfig;
	CAN_Parsing_Callback_ANSWER_Delegate callbackAnswer;

public:
	std::vector<uint8_t> StructToVector(const USBHIDFrame& frame);
	Mechanism(uint8_t _NumBoard, uint8_t _Group);
	~Mechanism();
	void SetMaxAskSize(uint16_t _MaxAskSize);
	void SetHidDevice(HidDevice* hidDevice);
	void SetUpdater(_CANUpdater _Updater);
	uint8_t GetUpdater();
	bool AddAsk(uint8_t _NumBoard, _AskEnum _Ask);
	void SetAsk(_AskEnum _SetAsk);
	void ClrAsks();
	bool AddOneTaskAsk(uint8_t _NumBoard, _AskEnum _Ask);
	bool SetOneTaskAsk(_AskEnum _SetAsk);
	void setUpdateType(bool _UpdateType);
	bool getUpdateType();
	void UpdateCode();

private: 
	void AutosenderSetTest();
	void addPossibleLostFrame();

public: 
	uint32_t getOkFrame();
	uint32_t getPossibleLostFrame();
	void clrPossibleLostFrame();
	void SetCanInputControl(_CAN_input_control* pCan_In, uint8_t* pDevID, uint8_t* pGroup, uint8_t* pNumCMD,
    bool* pbRun, bool* pbStop, bool* pbDir, bool* pbMoveMode, bool* pbSteps, bool* pbVeloc, bool* pbAccel, bool* pbDecel, Byte32BitMask* u32Cmd);
	void SetCANControl(const CAN_input_contr& pCan_In);
	void AskCANStep(uint8_t u8NumBoard, _AskEnum Ask);
	void SetCANParam(const CAN_input_conf& pCANInputConf);
	void CAN_Parsing_Callback_ANSWER_CONTROL(uint8_t* pNumBoardParse, uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* pCmdInWork, uint8_t* ptmpErrors);
	void CAN_Parsing_Callback_ANSWER_CONFIG(uint8_t* pNumBoardParse);
	void CAN_Parsing_Callback_ANSWER(uint8_t* pNumBoardParse, uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3);
	void SetCallbackAnswerControl(const CAN_Parsing_Callback_ANSWER_CONTROL_Delegate& callback);
	void SetCallbackAnswerConfig(const CAN_Parsing_Callback_ANSWER_CONFIG_Delegate& callback);
	void SetCallbackAnswer(const CAN_Parsing_Callback_ANSWER_Delegate& callback);
	

	static uint32_t u32AutosenderTestNum;
	static uint32_t u32AutosenderTestCheck;
	static uint32_t u32AutosenderTestErrNum;
	static bool bTestError;

	void CAN_Parsing_Out(uint8_t* data);
	void saveParam(_MenuLVConfig Param, uint8_t data, uint32_t u32data, float fdata);
	void loadControl(uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* ptmpErrors);
	uint8_t GetRescCMD();
	uint8_t GetRescNumCMD();
	uint8_t GetRescStartMotor();
	uint8_t GetRescControlErrors();
	void loadParam();
	bool GetParamLoaded();
	void ClrParamLoaded();
	void loadAnswer(uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3);
	void changeNumBoard(uint8_t _NumBoard);
	void setNumBoard(uint8_t _NumBoard);

	uint8_t getNumBoard();
	void changeGroup(uint8_t _Group);
	void setGroup(uint8_t _Group);
	uint8_t getGroup(bool R_Wr);
	void setHomingAPolarity(uint8_t _HomingAPolarity);
	uint8_t getHomingAPolarity(bool R_Wr);
	void setHomingBPolarity(uint8_t _HomingBPolarity);
	uint8_t getHomingBPolarity(bool R_Wr);
	void setHomingCPolarity(uint8_t _HomingCPolarity);
	uint8_t getHomingCPolarity(bool R_Wr);
	void setHomingDPolarity(uint8_t _HomingDPolarity);
	uint8_t getHomingDPolarity(bool R_Wr);
	void setStartPosition(uint32_t _StartPosition);
	uint32_t getStartPosition(bool R_Wr);
	void setEndPosition(uint32_t _EndPosition);
	uint32_t getEndPosition(bool R_Wr);
	uint32_t getRange(bool R_Wr);
	uint32_t getServoMotorTorque();
	uint32_t getServoMotorSpeed();
	uint32_t getServoAbsolutePositionRotorUint();
	uint32_t getServoAlarmCode();
	void setAccel(uint8_t _Accel);
	uint8_t getAccel(bool R_Wr);
	void setDecel(uint8_t _Decel);
	uint8_t getDecel(bool R_Wr);
	void setHomingADirection(uint8_t _HomingADirection);
	uint8_t getHomingADirection(bool R_Wr);
	void setHomingBDirection(uint8_t _HomingBDirection);
	uint8_t getHomingBDirection(bool R_Wr);
	void setHomingCDirection(uint8_t _HomingCDirection);
	uint8_t getHomingCDirection(bool R_Wr);
	void setHomingDDirection(uint8_t _HomingDDirection);
	uint8_t getHomingDDirection(bool R_Wr);
	void setmaxSpeed(float _maxSpeed);
	float getmaxSpeed(bool R_Wr);
	void setCurrSpeed(float _CurrSpeed);
	float getCurrSpeed(bool R_Wr);
	void setDeltaPosition(uint32_t _DeltaPosition);
	uint32_t getDeltaPosition(bool R_Wr);
	void setSRVRDYPolarity(uint8_t _SRVRDYPolarity);
	uint8_t getSRVRDYPolarity(bool R_Wr);
	void setINPOSPolarity(uint8_t _INPOSPolarity);
	uint8_t getINPOSPolarity(bool R_Wr);
	void setFAULTPolarity(uint8_t _FAULTPolarity);
	uint8_t getFAULTPolarity(bool R_Wr);
	void setBRAKEPolarity(uint8_t _BRAKEPolarity);
	uint8_t getBRAKEPolarity(bool R_Wr);
	void setEnPolarity(uint8_t _EnPolarity);
	uint8_t getEnPolarity(bool R_Wr);
	void setAL_CLRPolarity(uint8_t _AL_CLRPolarity);
	uint8_t getAL_CLRPolarity(bool R_Wr);
	void setOBRAKEPolarity(uint8_t _OBRAKEPolarity);
	uint8_t getOBRAKEPolarity(bool R_Wr);
	void setOReservPolarity(uint8_t _OReservPolarity);
	uint8_t getOReservPolarity(bool R_Wr);
	void setDIRPolarity(uint8_t _DIRPolarity);
	uint8_t getDIRPolarity(bool R_Wr);
	void runForward();
	void runBackward();
	void stop();
	void HomingZero();
	void HomingMax();
	void ResetDRVError();
	void BrakeOn();
	void BrakeOff();
	void Debug_on();
	void Reset();
	void Mosfet_On();
	void Mosfet_Off();
	uint32_t GetPosition(bool R_Wr);
	void SetPosition(uint32_t _u32Position);
	void RezervOn();
	void RezervOff();
	void AlarmResetOn();
	void AlarmResetOff();
	void setSteps(uint32_t _Steps);
	uint32_t getSteps();
	void setSpeed(float _Speed);
	float getSpeed(bool R_Wr);
	void setCurrAccel(uint8_t _CurrAccel);
	uint8_t getCurrAccel(bool R_Wr);
	void setCurrDecel(uint8_t _CurrDecel);
	uint8_t getCurrDecel(bool R_Wr);
	bool getEmergency();
	bool getInWork();
	bool getHomingA(bool Slow_Fast);
	bool getHomingB(bool Slow_Fast);
	bool getHomingC(bool Slow_Fast);
	bool getHomingD(bool Slow_Fast);
	bool getSRVRDY();
	bool getINPOS();
	bool getFAULT();
	bool getBRAKE();
	bool getOutEn(bool R_Wr);
	bool getOutDIR(bool R_Wr);
	void setOutAL_CLR(bool _OutAL_CLR);
	bool getOutAL_CLR(bool R_Wr);
	void setOutOutBRAKE(bool _OutBRAKE);
	bool getOutBRAKE(bool R_Wr);
	void setOutReserv(bool _OutReserv);
	bool getOutReserv(bool R_Wr);
	void setMicroSteps(uint32_t _MicrostepsToStep);
	uint32_t getMicroSteps(bool R_Wr);
	void setStepsToTurn(uint32_t _StepsToTurn);
	uint32_t getStepsToTurn(bool R_Wr);
	uint8_t setOutToZState(uint8_t _NumOut, bool _TrueFalse);
	uint8_t setOutToHiState(uint8_t _NumOut, bool _TrueFalse);
	uint8_t setOutToLoState(uint8_t _NumOut, bool _TrueFalse);
	void setOutToZ(uint8_t _NumOut);
	void setOutToHi(uint8_t _NumOut);
	void setOutToLo(uint8_t _NumOut);
	_NumOutState getOutState(uint8_t _NumOut, bool R_Wr);
	uint16_t setInToNoPullupDown(uint16_t _NumIn, bool _TrueFalse);
	uint16_t setInPullUp(uint16_t _NumIn, bool _TrueFalse);
	uint16_t setInPullDown(uint16_t _NumIn, bool _TrueFalse);
	void setInToZ(uint16_t _NumIn);
	void setInPullUp(uint16_t _NumIn);
	void setInPullDown(uint16_t _NumIn);
	_NumInPullUpDown getInPullupDown(uint16_t _NumIn, bool R_Wr);
	void SetIHOLD(uint8_t _IHOLD, uint8_t _IRUN, uint8_t _IHOLDDELAY);
	uint8_t GetIHOLD(bool R_Wr);
	uint8_t GetIRUN(bool R_Wr);
	uint8_t GetIHOLDDELAY(bool R_Wr);
	void setTPWMTHRS(uint8_t _TPWMTHRS);
	uint8_t getTPWMTHRS(bool R_Wr);
	void SaveInPullUps();
	void setEncoderActive(bool _set);
	void setCOOLCONF(uint8_t Seup, uint8_t Sedn, bool Seimin, bool SGFilter, uint8_t Semin, uint8_t Semax, uint8_t SGThreshold);
	void setEncoderConfig(uint8_t EncoderPolarity, uint8_t EncoderDelta, uint16_t EncoderToTurnData);
	void setGLOBAL_SCALER(uint8_t _GLOBAL_SCALER);
	void setControlPositioning_Velocity(bool Pos_Vel);
	uint8_t getAutosenderDelay();
	void setAutosender(uint8_t _AutosenderType, uint8_t _AutosenderDelay, uint8_t _AutosenderNum);
	void setCmdToMechanism(uint8_t* Cmd, uint8_t* NumCmd);
	void setCmdFromMechanism(uint8_t* Cmd, uint8_t* NumCmd, uint8_t* CmdInWork);
	bool getCmdInWork();
};

#endif //__MECHANISM_H_