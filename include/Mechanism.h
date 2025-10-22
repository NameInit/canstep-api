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
void MechCallback(USBCANFrame* _USBCANFrame)
{
}

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
	std::vector<uint8_t> StructToVector(const USBHIDFrame& frame)
	{
		std::vector<uint8_t> data(sizeof(USBHIDFrame));
		memcpy(data.data(), &frame, sizeof(USBHIDFrame));
		return data;
	}

	~Mechanism(void) {
		pthread_mutex_destroy(&hMutex);
	}

	Mechanism(uint8_t _NumBoard, uint8_t _Group) {
		NumBoard = _NumBoard;
		Group = _Group;
		CANInputConfLoc = std::make_unique<CAN_input_conf>();
		CanInLoc = std::make_unique<CAN_input_contr>();
		
		pthread_mutex_init(&hMutex, nullptr);
		
		MaxAskSize = MAX_ASK_SIZE;
		AskNumBoard.resize(MaxAskSize, 0);
		AskNumEnum.resize(MaxAskSize, 0);
		NumAsks = 0;
		AskOneTaskNumBoard.resize(MaxAskSize, 0);
		AskOneTaskNumEnum.resize(MaxAskSize, 0);
		NumOneTaskAsks = 0;
		AutosenderDelay = 50;
		u16StageAsk = 0;
		Updater = eCANUpdaterOff;
		u32NumHIDOkParam = 0;
		u32NumHIDOkControl = 0;
		u32NumHIDOkAsk = 0;
	}

	void SetMaxAskSize(uint16_t _MaxAskSize) {
		MaxAskSize = _MaxAskSize;
	}

	void SetHidDevice(HidDevice* hidDevice) { pHidDevice = hidDevice; }

	void SetUpdater(_CANUpdater _Updater) {
		Updater = _Updater;
	}

	uint8_t GetUpdater(void) {
		return static_cast<uint8_t>(Updater);
	}

	bool AddAsk(uint8_t _NumBoard, _AskEnum _Ask) {
		if (NumAsks >= MaxAskSize)
		{
			return false;
		}
		AskNumBoard[NumAsks] = _NumBoard;
		AskNumEnum[NumAsks] = (uint8_t)_Ask;
		NumAsks++;
		return true;
	}

	void SetAsk(_AskEnum _SetAsk)
	{
		AddAsk(NumBoard, _SetAsk);
		setAutosender(254, 20, _SetAsk);
	}

	void ClrAsks()
	{
		std::fill(AskNumBoard.begin(), AskNumBoard.end(), 0);
		std::fill(AskNumEnum.begin(), AskNumEnum.end(), 0);
		NumAsks = 0;
		setAutosender(253, 20, 0);
	}

	bool AddOneTaskAsk(uint8_t _NumBoard, _AskEnum _Ask) {
		if (NumOneTaskAsks >= MaxAskSize)
		{
			return false;
		}
		AskOneTaskNumBoard[NumOneTaskAsks] = _NumBoard;
		AskOneTaskNumEnum[NumOneTaskAsks] = (uint8_t)_Ask;
		NumOneTaskAsks++;
		return true;
	}
	
	bool SetOneTaskAsk(_AskEnum _SetAsk)
	{
		if (NumOneTaskAsks >= MaxAskSize)
		{
			return false;
		}
		AskOneTaskNumBoard[NumOneTaskAsks] = NumBoard;
		AskOneTaskNumEnum[NumOneTaskAsks] = (uint8_t)_SetAsk;
		NumOneTaskAsks++;
		return true;
	}

	void setUpdateType(bool _UpdateType) {
		UpdateType = _UpdateType;
	}

	bool getUpdateType() {
		return UpdateType;
	}
	
	void UpdateCode(void)
	{
		if (UpdateType)
		{
			AutosenderSetTest();
		}
		else
		{
			if (NumAsks)
			{
				AskCANStep(AskNumBoard[u16StageAsk], (_AskEnum)AskNumEnum[u16StageAsk]);
				if (u16StageAsk)
				{
					u16StageAsk--;
				}
				else
				{
					u16StageAsk = NumAsks - 1;
				}
			}
		}
		if (NumOneTaskAsks)
		{
			NumOneTaskAsks--;
			AskCANStep(AskOneTaskNumBoard[NumOneTaskAsks], (_AskEnum)AskOneTaskNumEnum[NumOneTaskAsks]);
			AskOneTaskNumBoard[NumOneTaskAsks] = 0;
			AskOneTaskNumEnum[NumOneTaskAsks] = 0;
		}
	}

private: 
	void AutosenderSetTest(void) {
		USBCANFrame NewUSBCANFrame = { 0 };
		NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
		NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
		NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_ASK;
		NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = this->getNumBoard();
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = (uint8_t)AskTest;

		Byte64BitMask tmpCurrentOUT = { 0 };
		tmpCurrentOUT.raw = u32AutosenderTestNum;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[4] = tmpCurrentOUT.u8Mask[0];
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[5] = tmpCurrentOUT.u8Mask[1];
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[6] = tmpCurrentOUT.u8Mask[2];
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[7] = tmpCurrentOUT.u8Mask[3];
		if (u32AutosenderTestNum < 4294967295) { u32AutosenderTestNum++; }
		else { u32AutosenderTestNum = 0; }
		
		if (pthread_mutex_lock(&hMutex) == 0) {
			USBHIDFrame TmpUSBHIDFrameTS = { 0 };
			pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
			std::vector<uint8_t> data = StructToVector(TmpUSBHIDFrameTS);
			bool iRet = pHidDevice->SendData(data);
			if (iRet) {
				u32NumHIDOkAsk++;
			}
			pthread_mutex_unlock(&hMutex);
		} else {
			perror("pthread_mutex_lock failed");
		}
	}

	void addPossibleLostFrame() {
		if (Updater == eCANUpdaterCentral) {
			PossibleLostFrame = u32NumHIDOkAsk + u32NumHIDOkEmergancy + u32NumHIDOkParam + 
				u32NumHIDOkControl - u32NumHIDOkRead;
		}
		else
		{
			PossibleLostFrame = 0;
		}
		if (UpdateType) {
			PossibleLostFrame = 0;
		}
	}

public: 
	uint32_t getOkFrame() {
		if (UpdateType) {
			return u32NumHIDOkRead;
		}
		else {
			return u32NumHIDOkAsk;
		}
	}

	uint32_t getPossibleLostFrame() {
		return PossibleLostFrame;
	}

	void clrPossibleLostFrame() {
		PossibleLostFrame = 0;
		u32NumHIDOkAsk = 0;
		u32NumHIDOkEmergancy = 0;
		u32NumHIDOkParam = 0;
		u32NumHIDOkControl = 0;
		u32NumHIDOkRead = 0;
	}

	void SetCanInputControl(_CAN_input_control* pCan_In, uint8_t* pDevID, uint8_t* pGroup, uint8_t* pNumCMD,
		bool* pbRun, bool* pbStop, bool* pbDir, bool* pbMoveMode, bool* pbSteps, bool* pbVeloc, bool* pbAccel, bool* pbDecel, Byte32BitMask* u32Cmd)
	{
		pCan_In->devID = *pDevID;
		pCan_In->group = *pGroup;
		pCan_In->numCommand = *pNumCMD;
		pCan_In->setups = 0;
		pCan_In->Data0 = 0;
		pCan_In->Data1 = 0;
		pCan_In->Data2 = 0;
		pCan_In->Data3 = 0;
		if (pCan_In->numCommand == curr_position)
		{
			pCan_In->setups = 0;
			pCan_In->Data0 = u32Cmd->u8Mask[3];
			pCan_In->Data1 = u32Cmd->u8Mask[2];
			pCan_In->Data2 = u32Cmd->u8Mask[1];
			pCan_In->Data3 = u32Cmd->u8Mask[0];
		}
		else if (pCan_In->numCommand == cantrol_command)
		{
			Byte8BitMask b8Tmp;
			b8Tmp.raw = 0;
			b8Tmp.b.b_0 = *pbRun;
			b8Tmp.b.b_1 = *pbStop;
			b8Tmp.b.b_2 = *pbDir;
			b8Tmp.b.b_3 = *pbMoveMode;
			b8Tmp.b.b_4 = *pbSteps;
			b8Tmp.b.b_5 = *pbVeloc;
			b8Tmp.b.b_6 = *pbAccel;
			b8Tmp.b.b_7 = *pbDecel;
			pCan_In->setups = b8Tmp.raw;
			if (*pbSteps)
			{
				pCan_In->Data0 = u32Cmd->u8Mask[3];
				pCan_In->Data1 = u32Cmd->u8Mask[2];
				pCan_In->Data2 = u32Cmd->u8Mask[1];
				pCan_In->Data3 = u32Cmd->u8Mask[0];
			}
			else if (*pbVeloc)
			{
				pCan_In->Data0 = u32Cmd->u8Mask[3];
				pCan_In->Data1 = u32Cmd->u8Mask[2];
				pCan_In->Data2 = u32Cmd->u8Mask[1];
				pCan_In->Data3 = u32Cmd->u8Mask[0];
			}
			else if (*pbAccel)
			{
				pCan_In->Data0 = u32Cmd->u8Mask[3];
				pCan_In->Data1 = u32Cmd->u8Mask[2];
				pCan_In->Data2 = u32Cmd->u8Mask[1];
				pCan_In->Data3 = u32Cmd->u8Mask[0];
			}
			else if (*pbDecel)
			{
				pCan_In->Data0 = u32Cmd->u8Mask[3];
				pCan_In->Data1 = u32Cmd->u8Mask[2];
				pCan_In->Data2 = u32Cmd->u8Mask[1];
				pCan_In->Data3 = u32Cmd->u8Mask[0];
			}
		}
		else
		{
			pCan_In->setups = 0;
		}
	}

	void SetCANControl(const CAN_input_contr& pCan_In)
	{
		USBCANFrame NewUSBCANFrame = { 0 };
		NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
		NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
		NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_CENTRAL_CONTROL;
		NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = pCan_In.devID;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = (uint8_t)pCan_In.setups;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[2] = pCan_In.group;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[3] = pCan_In.numCommand;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[4] = pCan_In.Data0;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[5] = pCan_In.Data1;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[6] = pCan_In.Data2;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[7] = pCan_In.Data3;
		
		if (pthread_mutex_lock(&hMutex) == 0) {
			USBHIDFrame TmpUSBHIDFrameTS = { 0 };
			pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
			std::vector<uint8_t> data = StructToVector(TmpUSBHIDFrameTS);
			bool iRet = pHidDevice->SendData(data);
			if (iRet) {
				u32NumHIDOkControl++;
			}
			pthread_mutex_unlock(&hMutex);
		} else {
			perror("pthread_mutex_lock failed");
		}
	}

	void AskCANStep(uint8_t u8NumBoard, _AskEnum Ask)
	{
		USBCANFrame NewUSBCANFrame = { 0 };
		NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
		NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
		NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_ASK;
		NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = u8NumBoard;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = (uint8_t)Ask;

		if (pthread_mutex_lock(&hMutex) == 0) {
			USBHIDFrame TmpUSBHIDFrameTS = { 0 };
			pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
			std::vector<uint8_t> data = StructToVector(TmpUSBHIDFrameTS);
			bool iRet = pHidDevice->SendData(data);
			if (iRet) {
				u32NumHIDOkAsk++;
			}
			pthread_mutex_unlock(&hMutex);
		} else {
			perror("pthread_mutex_lock failed");
		}
	}

	void SetCANParam(const CAN_input_conf& pCANInputConf)
	{
		USBCANFrame NewUSBCANFrame = { 0 };
		NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
		NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
		NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_CENTRAL_CONFIG;
		NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = pCANInputConf.devID;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = (uint8_t)pCANInputConf.set_param;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[2] = 0;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[3] = 0;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[4] = pCANInputConf.Data0;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[5] = pCANInputConf.Data1;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[6] = pCANInputConf.Data2;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[7] = pCANInputConf.Data3;

		if (pthread_mutex_lock(&hMutex) == 0) {
			USBHIDFrame TmpUSBHIDFrameTS = { 0 };
			pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
			std::vector<uint8_t> data = StructToVector(TmpUSBHIDFrameTS);
			bool iRet = pHidDevice->SendData(data);
			if (iRet) {
				u32NumHIDOkParam++;
			}
			pthread_mutex_unlock(&hMutex);
		} else {
			fprintf(stderr, "pthread_mutex_lock failed\n");
		}
	}
	
	void CAN_Parsing_Callback_ANSWER_CONTROL(uint8_t* pNumBoardParse, uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* pCmdInWork, uint8_t* ptmpErrors) {
		if (callbackAnswerControl) {
			callbackAnswerControl(pNumBoardParse, pRescCMD, pNumCMD, pStartMotor, pCmdInWork, ptmpErrors);
		}
	};
	
	void CAN_Parsing_Callback_ANSWER_CONFIG(uint8_t* pNumBoardParse) {
		if (callbackAnswerConfig) {
			callbackAnswerConfig(pNumBoardParse);
		}
	};
	
	void CAN_Parsing_Callback_ANSWER(uint8_t* pNumBoardParse, uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3) {
		if (callbackAnswer) {
			callbackAnswer(pNumBoardParse, pStatus, pNumAnswer, p8Data, p32Data, pfData, p8Data1, p8Data2, p8Data3);
		}
	};
	
public:
	void SetCallbackAnswerControl(const CAN_Parsing_Callback_ANSWER_CONTROL_Delegate& callback) {
		callbackAnswerControl = callback;
	}

	void SetCallbackAnswerConfig(const CAN_Parsing_Callback_ANSWER_CONFIG_Delegate& callback) {
		callbackAnswerConfig = callback;
	}

	void SetCallbackAnswer(const CAN_Parsing_Callback_ANSWER_Delegate& callback) {
		callbackAnswer = callback;
	}

	static uint32_t u32AutosenderTestNum;
	static uint32_t u32AutosenderTestCheck;
	static uint32_t u32AutosenderTestErrNum;
	static bool bTestError;

	void CAN_Parsing_Out(uint8_t* data)
	{
		static Byte32BitMask tmpCurrentOUT;
		tmpCurrentOUT.raw = 0;
		int32_t tmpInt32 = 0;
		USBCANFrame NewUSBCANFrame = { 0 };
		memcpy(&NewUSBCANFrame.b128USBCANFrame.u8Mask[0], data, USB_CAN_FRAME_Num);
		uint8_t u8NumBoardParse = 0;
		uint8_t u8RescCMD = 0;
		uint8_t u8NumCMD = 0;
		uint8_t u8CmdInWork;
		uint8_t u8StartMotor = 0;
		Byte8BitMask u8tmpErrors = { 0 };
		u8NumBoardParse = NewUSBCANFrame.USB_CAN_Frame.eFrameData[1];

		if (NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID == CAN_ID_ANSWER_CONTROL)
		{
			if (true)
			{
				u8RescCMD = NewUSBCANFrame.USB_CAN_Frame.eFrameData[3];
				u8NumCMD = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				u8CmdInWork = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				u8StartMotor = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				u8tmpErrors.raw = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER_CONTROL(&u8NumBoardParse, &u8RescCMD, &u8NumCMD, &u8StartMotor, &u8CmdInWork, &u8tmpErrors.raw);
			}
		}
		else if (NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID == CAN_ID_ANSWER_CONFIG)
		{
			CAN_Parsing_Callback_ANSWER_CONFIG(&u8NumBoardParse);
		}
		else if (NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID == CAN_ID_ANSWER)
		{
			Byte8BitMask b8TmpStatus = { 0 };
			Byte8BitMask b8TmpData = { 0 };

			b8TmpStatus.raw = NewUSBCANFrame.USB_CAN_Frame.eFrameData[3];
			uint8_t u8NumAnswer = NewUSBCANFrame.USB_CAN_Frame.eFrameData[2];

			Emergency = b8TmpStatus.b.b_0;
			InWork = b8TmpStatus.b.b_1;
			HomingA = b8TmpStatus.b.b_2;
			HomingB = b8TmpStatus.b.b_3;
			HomingC = b8TmpStatus.b.b_4;
			HomingD = b8TmpStatus.b.b_5;

			switch (NewUSBCANFrame.USB_CAN_Frame.eFrameData[2])
			{
			case OutPosition:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutLimitSwitchesCondition:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
				break;
			case OutStartPoint:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutEndPoint:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutRange:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutInputs:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
				break;
			case OutMotorTorque:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutMotorSpeed:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutAbsolutePositionRotorUint:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutAbsolutePositionRotorGrad:
				break;
			case OutAlarmCode:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutEncoder:
				break;
			case OutCurrSpeed:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
				break;
			case OutCurrAccel:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
				break;
			case OutCurrDecel:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
				break;
			case OutCurrDir:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutCurrOutputs:
				Byte8BitMask b8OutputsState;
				b8OutputsState.raw = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutHomingAPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutHomingBPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutHomingCPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutHomingDPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutTimeAccel:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutAccel:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutDecel:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutHomingADirection:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutHomingBDirection:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutHomingCDirection:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutHomingDDirection:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutmaxSpeed:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
				break;
			case OutSavedSpeed:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
				break;
			case OutDeltaPosition:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutSRVRDYPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutINPOSPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutFAULTPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutBRAKEPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutEnPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutAL_CLRPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutOBRAKEPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutOReservPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutDIRPolarity:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutGroup:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutOuts0_7:
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
				break;
			case OutInputs0_11:
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], 0, 0);
				break;
			case OutPullUpDwnInputs0_11:
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
				break;
			case OutEncoderActive:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutIholdIrun:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
				break;
			case OutTPWMTHRS:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutSteps:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutCOOLCONF:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutStallGuard2Result:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutEncoderPolarityDeltaTurn:
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
				break;
			case OutGLOBAL_SCALER:
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
				break;
			case OutEncoderRaw:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				tmpInt32 = (int32_t)tmpCurrentOUT.raw;
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
				break;
			case OutVActual:
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
				break;
			case OutTest:
				tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
				tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
				tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
				tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];

				u32AutosenderTestNum = tmpCurrentOUT.raw;
				if (u32AutosenderTestNum != u32AutosenderTestCheck)
				{
					bTestError = true;
					u32AutosenderTestCheck = u32AutosenderTestNum;
				}
				else
				{
					bTestError = false;
				}
				u32AutosenderTestCheck++;
				if (bTestError)
				{
					u32AutosenderTestErrNum++;
					fprintf(stderr, "Read CAN-USB immediate error: %u (0x%X)\n", u32AutosenderTestErrNum, u32AutosenderTestErrNum);
				}
				else
				{
					if (!(tmpCurrentOUT.raw % 1000))
					{
						fprintf(stdout, "Read CAN-USB Frames: %u (0x%X)\n", tmpCurrentOUT.raw, tmpCurrentOUT.raw);
					}
				}
				tmpCurrentOUT.raw = 0;
				CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
				break;
			default:
				break;
			}
		}
	}

	void saveParam(_MenuLVConfig Param, uint8_t data, uint32_t u32data, float fdata) {
		Byte32BitMask b32TmpParamSave = { 0 };
		switch (Param)
		{
		case mNumBoard:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mNumBoard;
			CANInputConfLoc->Data0 = data;
			SetCANParam(*CANInputConfLoc);
			break;
		case mHomingAPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mHomingAPolarity;
			CANInputConfLoc->Data0 = HomingAPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mHomingBPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mHomingBPolarity;
			CANInputConfLoc->Data0 = HomingBPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mHomingCPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mHomingCPolarity;
			CANInputConfLoc->Data0 = HomingCPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mHomingDPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mHomingDPolarity;
			CANInputConfLoc->Data0 = HomingDPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mStartPosition:
			b32TmpParamSave.raw = StartPosition;
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mStartPosition;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
			SetCANParam(*CANInputConfLoc);
			break;
		case mEndPosition:
			b32TmpParamSave.raw = EndPosition;
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mEndPosition;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
			SetCANParam(*CANInputConfLoc);
			break;
		case mAccelMem:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mAccelMem;
			CANInputConfLoc->Data0 = Accel;
			SetCANParam(*CANInputConfLoc);
			break;
		case mDecelMem:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mDecelMem;
			CANInputConfLoc->Data0 = Decel;
			SetCANParam(*CANInputConfLoc);
			break;
		case mHomingADirection:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mHomingADirection;
			CANInputConfLoc->Data0 = HomingADirection;
			SetCANParam(*CANInputConfLoc);
			break;
		case mHomingBDirection:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mHomingBDirection;
			CANInputConfLoc->Data0 = HomingBDirection;
			SetCANParam(*CANInputConfLoc);
			break;
		case mHomingCDirection:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mHomingCDirection;
			CANInputConfLoc->Data0 = HomingCDirection;
			SetCANParam(*CANInputConfLoc);
			break;
		case mHomingDDirection:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mHomingDDirection;
			CANInputConfLoc->Data0 = HomingDDirection;
			SetCANParam(*CANInputConfLoc);
			break;
		case mMaxSpeed:
			b32TmpParamSave.fraw = maxSpeed;
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mMaxSpeed;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
			SetCANParam(*CANInputConfLoc);
			break;
		case mCurrSpeed:
			b32TmpParamSave.fraw = CurrSpeed;
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mCurrSpeed;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
			SetCANParam(*CANInputConfLoc);
			break;
		case mDeltaPosition:
			b32TmpParamSave.raw = DeltaPosition;
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mDeltaPosition;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
			SetCANParam(*CANInputConfLoc);
			break;
		case mEnPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mEnPolarity;
			CANInputConfLoc->Data0 = EnPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mAL_CLRPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mAL_CLRPolarity;
			CANInputConfLoc->Data0 = AL_CLRPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mOBRAKEPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mOBRAKEPolarity;
			CANInputConfLoc->Data0 = OBRAKEPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mOReservPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mOReservPolarity;
			CANInputConfLoc->Data0 = OReservPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mSRVRDYPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mSRVRDYPolarity;
			CANInputConfLoc->Data0 = SRVRDYPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mINPOSPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mINPOSPolarity;
			CANInputConfLoc->Data0 = INPOSPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mFAULTPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mFAULTPolarity;
			CANInputConfLoc->Data0 = FAULTPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mBRAKEPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mBRAKEPolarity;
			CANInputConfLoc->Data0 = BRAKEPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mDIRPolarity:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mDIRPolarity;
			CANInputConfLoc->Data0 = DIRPolarity;
			SetCANParam(*CANInputConfLoc);
			break;
		case mSaveGroup:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mSaveGroup;
			CANInputConfLoc->Data0 = data;
			SetCANParam(*CANInputConfLoc);
			break;
		case mSetMicrostepsToStep:
			CANInputConfLoc->devID = NumBoard;
			b32TmpParamSave.raw = u32data;
			CANInputConfLoc->set_param = mSetMicrostepsToStep;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
			SetCANParam(*CANInputConfLoc);
			break;
		case mSetStepsToTurn:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mSetStepsToTurn;
			b32TmpParamSave.raw = u32data;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
			SetCANParam(*CANInputConfLoc);
			break;
		case mSetInputsToVccGND:
			b32TmpParamSave.u16Mask[0] = NumInPullDown;
			b32TmpParamSave.u16Mask[1] = NumInPullUp;
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mSetInputsToVccGND;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
			SetCANParam(*CANInputConfLoc);
			break;
		case mSetEncoderActive:
			b32TmpParamSave.u8Mask[0] = data;
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mSetEncoderActive;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
			SetCANParam(*CANInputConfLoc);
			break;
		case mSetTMC_IHOLD:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mSetTMC_IHOLD;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[0];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data3 = 0;
			SetCANParam(*CANInputConfLoc);
			break;
		case mSetTMC_TPWMTHRS:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mSetTMC_TPWMTHRS;
			CANInputConfLoc->Data0 = data;
			CANInputConfLoc->Data1 = 0;
			CANInputConfLoc->Data2 = 0;
			CANInputConfLoc->Data3 = 0;
			SetCANParam(*CANInputConfLoc);
			break;
		case mSetTMC_COOLCONF:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mSetTMC_COOLCONF;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[0];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[3];
			SetCANParam(*CANInputConfLoc);
			break;
		case mSetEncoderPolarityDeltaTurn:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mSetEncoderPolarityDeltaTurn;
			CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[0];
			CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[1];
			CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[2];
			CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[3];
			SetCANParam(*CANInputConfLoc);
			break;
		case mSetGLOBAL_SCALER:
			CANInputConfLoc->devID = NumBoard;
			CANInputConfLoc->set_param = mSetGLOBAL_SCALER;
			CANInputConfLoc->Data0 = data;
			CANInputConfLoc->Data1 = 0;
			CANInputConfLoc->Data2 = 0;
			CANInputConfLoc->Data3 = 0;
			SetCANParam(*CANInputConfLoc);
			break;
		case mSetFreewheel:
			break;
		default:
			break;
		}
	}

	void loadControl(uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* ptmpErrors) {
		RescCMD = *pRescCMD;
		RescNumCMD = *pNumCMD;
		RescStartMotor = *pStartMotor;
		RescControlErrors = *ptmpErrors;
	}
	uint8_t GetRescCMD() { return RescCMD; }
	uint8_t GetRescNumCMD() { return RescNumCMD; }
	uint8_t GetRescStartMotor() { return RescStartMotor; }
	uint8_t GetRescControlErrors() { return RescControlErrors; }
	void loadParam() {
		bParamLoaded = true;
	}
	bool GetParamLoaded() { return bParamLoaded; }
	void ClrParamLoaded() { bParamLoaded = false; }

	void loadAnswer(uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3) {
		Byte8BitMask b8TmpStatus = { 0 };
		b8TmpStatus.raw = *pStatus;
		Emergency = b8TmpStatus.b.b_0;
		InWork = b8TmpStatus.b.b_1;
		HomingA = b8TmpStatus.b.b_2;
		HomingB = b8TmpStatus.b.b_3;
		HomingC = b8TmpStatus.b.b_4;
		HomingD = b8TmpStatus.b.b_5;
		_OutTypeEnum mParam = (_OutTypeEnum)*pNumAnswer;

		Byte8BitMask b8tmpData = { 0 };

		switch (mParam)
		{
		case OutPosition:
			ReadPosition = *p32Data;
			break;
		case OutLimitSwitchesCondition:
			ReadHomeAState = *p8Data;
			ReadHomeBState = *p8Data1;
			ReadHomeCState = *p8Data2;
			ReadHomeDState = *p8Data3;
			break;
		case OutStartPoint:
			ReadStartPosition = *p32Data;
			break;
		case OutEndPoint:
			ReadEndPosition = *p32Data;
			break;
		case OutRange:
			ReadRange = *p32Data;
			break;
		case OutInputs:
			SRVRDY = *p8Data;
			INPOS = *p8Data1;
			FAULT = *p8Data2;
			BRAKE = *p8Data3;
			break;
		case OutMotorTorque:
			ServoMotorTorque = *p32Data;
			break;
		case OutMotorSpeed:
			ServoMotorSpeed = *p32Data;
			break;
		case OutAbsolutePositionRotorUint:
			ServoAbsolutePositionRotorUint = *p32Data;
			break;
		case OutAlarmCode:
			ServoAlarmCode = *p32Data;
			break;
		case OutCurrSpeed:
			ReadSpeed = *pfData;
			break;
		case OutCurrAccel:
			ReadCurrAccel = *pfData;
			break;
		case OutCurrDecel:
			ReadCurrDecel = *pfData;
			break;
		case OutCurrDir:
			ReadOut_Dir = *p8Data;
			break;
		case OutCurrOutputs:
			b8tmpData.raw = *p8Data;
			ReadOut_EN = b8tmpData.b.B_POS_EN;
			ReadOut_AL_CLR = b8tmpData.b.B_POS_AL_CLR;
			ReadOut_OBRAKE = b8tmpData.b.B_POS_OBRAKE;
			ReadOut_ORESERV = b8tmpData.b.B_POS_ORESERV;
			break;
		case OutHomingAPolarity:
			ReadHomingAPolarity = *p8Data;
			break;
		case OutHomingBPolarity:
			ReadHomingBPolarity = *p8Data;
			break;
		case OutHomingCPolarity:
			ReadHomingCPolarity = *p8Data;
			break;
		case OutHomingDPolarity:
			ReadHomingDPolarity = *p8Data;
			break;
		case OutAccel:
			ReadAccel = *p8Data;
			break;
		case OutDecel:
			ReadDecel = *p8Data;
			break;
		case OutHomingADirection:
			ReadHomingADirection = *p8Data;
			break;
		case OutHomingBDirection:
			ReadHomingBDirection = *p8Data;
			break;
		case OutHomingCDirection:
			ReadHomingCDirection = *p8Data;
			break;
		case OutHomingDDirection:
			ReadHomingDDirection = *p8Data;
			break;
		case OutmaxSpeed:
			ReadmaxSpeed = *pfData;
			break;
		case OutSavedSpeed:
			ReadCurrSpeed = *pfData;
			break;
		case OutDeltaPosition:
			ReadDeltaPosition = *p32Data;
			break;
		case OutSRVRDYPolarity:
			ReadSRVRDYPolarity = *p8Data;
			break;
		case OutINPOSPolarity:
			ReadINPOSPolarity = *p8Data;
			break;
		case OutFAULTPolarity:
			ReadFAULTPolarity = *p8Data;
			break;
		case OutBRAKEPolarity:
			ReadBRAKEPolarity = *p8Data;
			break;
		case OutEnPolarity:
			ReadEnPolarity = *p8Data;
			break;
		case OutAL_CLRPolarity:
			ReadAL_CLRPolarity = *p8Data;
			break;
		case OutOBRAKEPolarity:
			ReadOBRAKEPolarity = *p8Data;
			break;
		case OutOReservPolarity:
			ReadOReservPolarity = *p8Data;
			break;
		case OutDIRPolarity:
			ReadDIRPolarity = *p8Data;
			break;
		case OutGroup:
			ReadGroup = *p8Data;
			break;
		case OutOuts0_7:
		case OutInputs0_11:
		case OutPullUpDwnInputs0_11:
		case OutEncoderActive:
		case OutIholdIrun:
		case OutTPWMTHRS:
		case OutSteps:
		case OutCOOLCONF:
		case OutStallGuard2Result:
		case OutEncoderPolarityDeltaTurn:
		case OutGLOBAL_SCALER:
		case OutEncoderRaw:
		case OutVActual:
		case OutTest:
			break;
		default:
			break;
		}
	};

	void changeNumBoard(uint8_t _NumBoard) {
		NumBoard = _NumBoard;
	}
	void setNumBoard(uint8_t _NumBoard) {
		saveParam(mNumBoard, _NumBoard, 0, 0);
		NumBoard = _NumBoard;
	};
public: 
	uint8_t getNumBoard() {
		return NumBoard;
	};
	void changeGroup(uint8_t _Group) {
		Group = _Group;
	}
	void setGroup(uint8_t _Group) {
		Group = _Group;
		saveParam(mSaveGroup, Group, 0, 0);
	};
public: 
	uint8_t getGroup(bool R_Wr) {
		if (R_Wr) return ReadGroup;
		else return Group;
	};
	void setHomingAPolarity(uint8_t _HomingAPolarity) {
		HomingAPolarity = _HomingAPolarity;
		saveParam(mHomingAPolarity, HomingAPolarity, 0, 0);
	};
	uint8_t getHomingAPolarity(bool R_Wr) {
		if (R_Wr) return ReadHomingAPolarity;
		else return HomingAPolarity;
	};
	void setHomingBPolarity(uint8_t _HomingBPolarity) {
		HomingBPolarity = _HomingBPolarity;
		saveParam(mHomingBPolarity, HomingBPolarity, 0, 0);
	};
	uint8_t getHomingBPolarity(bool R_Wr) {
		if (R_Wr) return ReadHomingBPolarity;
		else return HomingBPolarity;
	};
	void setHomingCPolarity(uint8_t _HomingCPolarity) {
		HomingCPolarity = _HomingCPolarity;
		saveParam(mHomingCPolarity, HomingCPolarity, 0, 0);
	};
	uint8_t getHomingCPolarity(bool R_Wr) {
		if (R_Wr) return ReadHomingCPolarity;
		else return HomingCPolarity;
	};
	void setHomingDPolarity(uint8_t _HomingDPolarity) {
		HomingDPolarity = _HomingDPolarity;
		saveParam(mHomingDPolarity, HomingDPolarity, 0, 0);
	};
	uint8_t getHomingDPolarity(bool R_Wr) {
		if (R_Wr) return ReadHomingDPolarity;
		else return HomingDPolarity;
	};
	void setStartPosition(uint32_t _StartPosition) {
		StartPosition = _StartPosition;
		saveParam(mStartPosition, 0, StartPosition, 0);
	};
	uint32_t getStartPosition(bool R_Wr) {
		if (R_Wr) return ReadStartPosition;
		else return StartPosition;
	};
	void setEndPosition(uint32_t _EndPosition) {
		EndPosition = _EndPosition;
		saveParam(mEndPosition, 0, EndPosition, 0);
	};
	uint32_t getEndPosition(bool R_Wr) {
		if (R_Wr) return ReadEndPosition;
		else return EndPosition;
	};
	uint32_t getRange(bool R_Wr) {
		if (R_Wr) return ReadRange;
		else return Range;
	};
	uint32_t getServoMotorTorque() {
		return ServoMotorTorque;
	}
	uint32_t getServoMotorSpeed() {
		return ServoMotorSpeed;
	}
	uint32_t getServoAbsolutePositionRotorUint() {
		return ServoAbsolutePositionRotorUint;
	}
	uint32_t getServoAlarmCode() {
		return ServoAlarmCode;
	}
	void setAccel(uint8_t _Accel) {
		Accel = _Accel;
		saveParam(mAccelMem, Accel, 0, 0);
	};
	uint8_t getAccel(bool R_Wr) {
		if (R_Wr) return ReadAccel;
		else return Accel;
	};
	void setDecel(uint8_t _Decel) {
		Decel = _Decel;
		saveParam(mDecelMem, Decel, 0, 0);
	};
	uint8_t getDecel(bool R_Wr) {
		if (R_Wr) return ReadDecel;
		else return Decel;
	};
	void setHomingADirection(uint8_t _HomingADirection) {
		HomingADirection = _HomingADirection;
		saveParam(mHomingADirection, HomingADirection, 0, 0);
	};
	uint8_t getHomingADirection(bool R_Wr) {
		if (R_Wr) return ReadHomingADirection;
		else return HomingADirection;
	};
	void setHomingBDirection(uint8_t _HomingBDirection) {
		HomingBDirection = _HomingBDirection;
		saveParam(mHomingBDirection, HomingBDirection, 0, 0);
	};
	uint8_t getHomingBDirection(bool R_Wr) {
		if (R_Wr) return ReadHomingBDirection;
		else return HomingBDirection;
	};
	void setHomingCDirection(uint8_t _HomingCDirection) {
		HomingCDirection = _HomingCDirection;
		saveParam(mHomingCDirection, HomingCDirection, 0, 0);
	};
	uint8_t getHomingCDirection(bool R_Wr) {
		if (R_Wr) return ReadHomingCDirection;
		else return HomingCDirection;
	};
	void setHomingDDirection(uint8_t _HomingDDirection) {
		HomingDDirection = _HomingDDirection;
		saveParam(mHomingDDirection, HomingDDirection, 0, 0);
	};
	uint8_t getHomingDDirection(bool R_Wr) {
		if (R_Wr) return ReadHomingDDirection;
		else return HomingDDirection;
	};
	void setmaxSpeed(float _maxSpeed) {
		maxSpeed = _maxSpeed;
		saveParam(mMaxSpeed, 0, 0, maxSpeed);
	};
	float getmaxSpeed(bool R_Wr) {
		if (R_Wr) return ReadmaxSpeed;
		else return maxSpeed;
	};
	void setCurrSpeed(float _CurrSpeed) {
		CurrSpeed = _CurrSpeed;
		saveParam(mCurrSpeed, 0, 0, CurrSpeed);
	};
	float getCurrSpeed(bool R_Wr) {
		if (R_Wr) return ReadCurrSpeed;
		else return CurrSpeed;
	};
	void setDeltaPosition(uint32_t _DeltaPosition) {
		DeltaPosition = _DeltaPosition;
		saveParam(mDeltaPosition, 0, DeltaPosition, 0);
	};
	uint32_t getDeltaPosition(bool R_Wr) {
		if (R_Wr) return ReadDeltaPosition;
		else return DeltaPosition;
	};
	void setSRVRDYPolarity(uint8_t _SRVRDYPolarity) {
		SRVRDYPolarity = _SRVRDYPolarity;
		saveParam(mSRVRDYPolarity, SRVRDYPolarity, 0, 0);
	};
	uint8_t getSRVRDYPolarity(bool R_Wr) {
		if (R_Wr) return ReadSRVRDYPolarity;
		else return SRVRDYPolarity;
	};
	void setINPOSPolarity(uint8_t _INPOSPolarity) {
		INPOSPolarity = _INPOSPolarity;
		saveParam(mINPOSPolarity, INPOSPolarity, 0, 0);
	};
	uint8_t getINPOSPolarity(bool R_Wr) {
		if (R_Wr) return ReadINPOSPolarity;
		else return INPOSPolarity;
	};
	void setFAULTPolarity(uint8_t _FAULTPolarity) {
		FAULTPolarity = _FAULTPolarity;
		saveParam(mFAULTPolarity, FAULTPolarity, 0, 0);
	};
	uint8_t getFAULTPolarity(bool R_Wr) {
		if (R_Wr) return ReadFAULTPolarity;
		else return FAULTPolarity;
	};
	void setBRAKEPolarity(uint8_t _BRAKEPolarity) {
		BRAKEPolarity = _BRAKEPolarity;
		saveParam(mBRAKEPolarity, BRAKEPolarity, 0, 0);
	};
	uint8_t getBRAKEPolarity(bool R_Wr) {
		if (R_Wr) return ReadBRAKEPolarity;
		else return BRAKEPolarity;
	};
	void setEnPolarity(uint8_t _EnPolarity) {
		EnPolarity = _EnPolarity;
		saveParam(mEnPolarity, EnPolarity, 0, 0);
	};
	uint8_t getEnPolarity(bool R_Wr) {
		if (R_Wr) return ReadEnPolarity;
		else return EnPolarity;
	};
	void setAL_CLRPolarity(uint8_t _AL_CLRPolarity) {
		AL_CLRPolarity = _AL_CLRPolarity;
		saveParam(mAL_CLRPolarity, AL_CLRPolarity, 0, 0);
	};
	uint8_t getAL_CLRPolarity(bool R_Wr) {
		if (R_Wr) return ReadAL_CLRPolarity;
		else return AL_CLRPolarity;
	};
	void setOBRAKEPolarity(uint8_t _OBRAKEPolarity) {
		OBRAKEPolarity = _OBRAKEPolarity;
		saveParam(mOBRAKEPolarity, OBRAKEPolarity, 0, 0);
	};
	uint8_t getOBRAKEPolarity(bool R_Wr) {
		if (R_Wr) return ReadOBRAKEPolarity;
		else return OBRAKEPolarity;
	};
	void setOReservPolarity(uint8_t _OReservPolarity) {
		OReservPolarity = _OReservPolarity;
		saveParam(mOReservPolarity, OReservPolarity, 0, 0);
	};
	uint8_t getOReservPolarity(bool R_Wr) {
		if (R_Wr) return ReadOReservPolarity;
		else return OReservPolarity;
	};
	void setDIRPolarity(uint8_t _DIRPolarity) {
		DIRPolarity = _DIRPolarity;
		saveParam(mDIRPolarity, DIRPolarity, 0, 0);
	};
	uint8_t getDIRPolarity(bool R_Wr) {
		if (R_Wr) return ReadDIRPolarity;
		else return DIRPolarity;
	};
	void runForward() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = cantrol_command;
		Byte8BitMask b8Tmp;
		b8Tmp.raw = 0;
		b8Tmp.b.b_0 = true;
		b8Tmp.b.b_2 = true;
		CanInLoc->setups = b8Tmp.raw;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	void runBackward() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = cantrol_command;
		Byte8BitMask b8Tmp;
		b8Tmp.raw = 0;
		b8Tmp.b.b_0 = true;
		b8Tmp.b.b_2 = false;
		CanInLoc->setups = b8Tmp.raw;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	void stop() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = cantrol_command;
		Byte8BitMask b8Tmp;
		b8Tmp.raw = 0;
		b8Tmp.b.b_1 = true;
		CanInLoc->setups = b8Tmp.raw;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	void HomingZero() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = homing_zero;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	void HomingMax() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = homing_max;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	void ResetDRVError() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = reset_drv_err;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	void BrakeOn() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = brake_on;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	void BrakeOff() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = brake_off;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	void Debug_on() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = debug_on;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	void Reset() {
		uint8_t u8Emergancy = 0;
		uint8_t u8Reload = 1;
		uint8_t u8NB = NumBoard;
		pHidDevice->SetEmergancy(&u8NB, &u8Emergancy, &u8Reload);
	}
	void Mosfet_On() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = tmc_mosfet_off;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 1;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	void Mosfet_Off() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = tmc_mosfet_off;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	uint32_t GetPosition(bool R_Wr)
	{
		if (R_Wr) return ReadPosition;
		else return u32SetPosition;
	}
	void SetPosition(uint32_t _u32Position)
	{
		u32SetPosition = _u32Position;
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = curr_position;
		CanInLoc->setups = 0;
		Byte32BitMask u32Cmd;
		u32Cmd.raw = u32SetPosition;
		CanInLoc->Data0 = u32Cmd.u8Mask[3];
		CanInLoc->Data1 = u32Cmd.u8Mask[2];
		CanInLoc->Data2 = u32Cmd.u8Mask[1];
		CanInLoc->Data3 = u32Cmd.u8Mask[0];
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	void RezervOn() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = rez_on;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	void RezervOff() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = rez_off;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	void AlarmResetOn() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = al_clr_on;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	void AlarmResetOff() {
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = al_clr_off;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}
	void setSteps(uint32_t _Steps) {
		Steps = _Steps;
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = cantrol_command;
		Byte8BitMask b8Tmp;
		b8Tmp.raw = 0;
		b8Tmp.b.b_4 = true;
		CanInLoc->setups = b8Tmp.raw;
		Byte32BitMask u32Cmd;
		u32Cmd.raw = Steps;
		CanInLoc->Data0 = u32Cmd.u8Mask[3];
		CanInLoc->Data1 = u32Cmd.u8Mask[2];
		CanInLoc->Data2 = u32Cmd.u8Mask[1];
		CanInLoc->Data3 = u32Cmd.u8Mask[0];
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	uint32_t getSteps() { return Steps; };
	void setSpeed(float _Speed) {
		Speed = _Speed;
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = cantrol_command;
		Byte8BitMask b8Tmp;
		b8Tmp.raw = 0;
		b8Tmp.b.b_5 = true;
		CanInLoc->setups = b8Tmp.raw;
		Byte32BitMask u32Cmd;
		u32Cmd.fraw = Speed;
		CanInLoc->Data0 = u32Cmd.u8Mask[3];
		CanInLoc->Data1 = u32Cmd.u8Mask[2];
		CanInLoc->Data2 = u32Cmd.u8Mask[1];
		CanInLoc->Data3 = u32Cmd.u8Mask[0];
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	float getSpeed(bool R_Wr) {
		if (R_Wr) return ReadSpeed;
		else return Speed;
	};
	void setCurrAccel(uint8_t _CurrAccel) {
		CurrAccel = _CurrAccel;
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = cantrol_command;
		Byte8BitMask b8Tmp;
		b8Tmp.raw = 0;
		b8Tmp.b.b_6 = true;
		CanInLoc->setups = b8Tmp.raw;
		Byte32BitMask u32Cmd;
		u32Cmd.fraw = CurrAccel;
		CanInLoc->Data0 = u32Cmd.u8Mask[3];
		CanInLoc->Data1 = u32Cmd.u8Mask[2];
		CanInLoc->Data2 = u32Cmd.u8Mask[1];
		CanInLoc->Data3 = u32Cmd.u8Mask[0];
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	uint8_t getCurrAccel(bool R_Wr) {
		if (R_Wr) return ReadCurrAccel;
		else return CurrAccel;
	};
	void setCurrDecel(uint8_t _CurrDecel) {
		CurrDecel = _CurrDecel;
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = cantrol_command;
		Byte8BitMask b8Tmp;
		b8Tmp.raw = 0;
		b8Tmp.b.b_7 = true;
		CanInLoc->setups = b8Tmp.raw;
		Byte32BitMask u32Cmd;
		u32Cmd.fraw = CurrDecel;
		CanInLoc->Data0 = u32Cmd.u8Mask[3];
		CanInLoc->Data1 = u32Cmd.u8Mask[2];
		CanInLoc->Data2 = u32Cmd.u8Mask[1];
		CanInLoc->Data3 = u32Cmd.u8Mask[0];
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	uint8_t getCurrDecel(bool R_Wr) {
		if (R_Wr) return ReadCurrDecel;
		else return CurrDecel;
	};

	bool getEmergency() { return Emergency; };
	bool getInWork() { return InWork; };
	bool getHomingA(bool Slow_Fast) {
		if (Slow_Fast) return ReadHomeAState;
		else return HomingA;
	};
	bool getHomingB(bool Slow_Fast) {
		if (Slow_Fast) return ReadHomeBState;
		else return HomingB;
	};
	bool getHomingC(bool Slow_Fast) {
		if (Slow_Fast) return ReadHomeCState;
		else return HomingC;
	};
	bool getHomingD(bool Slow_Fast) {
		if (Slow_Fast) return ReadHomeDState;
		else return HomingD;
	};
	bool getSRVRDY() { return SRVRDY; };
	bool getINPOS() { return INPOS; };
	bool getFAULT() { return FAULT; };
	bool getBRAKE() { return BRAKE; };
	bool getOutEn(bool R_Wr) {
		if (R_Wr) return ReadOut_EN;
		else return OutEn;
	};
	bool getOutDIR(bool R_Wr) {
		if (R_Wr) return ReadOut_Dir;
		else return OutDIR;
	};
	void setOutAL_CLR(bool _OutAL_CLR) {
		OutAL_CLR = _OutAL_CLR;
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		if (OutAL_CLR) CanInLoc->numCommand = al_clr_on;
		else CanInLoc->numCommand = al_clr_off;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	bool getOutAL_CLR(bool R_Wr) {
		if (R_Wr) return ReadOut_AL_CLR;
		else return OutAL_CLR;
	};
	void setOutOutBRAKE(bool _OutBRAKE) {
		OutBRAKE = _OutBRAKE;
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		if (OutBRAKE) CanInLoc->numCommand = brake_on;
		else CanInLoc->numCommand = brake_off;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	bool getOutBRAKE(bool R_Wr) {
		if (R_Wr) return ReadOut_OBRAKE;
		else return OutBRAKE;
	};
	void setOutReserv(bool _OutReserv) {
		OutReserv = _OutReserv;
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		if (OutReserv) CanInLoc->numCommand = rez_on;
		else CanInLoc->numCommand = rez_off;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = 0;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	bool getOutReserv(bool R_Wr) {
		if (R_Wr) return ReadOut_ORESERV;
		else return OutReserv;
	};
	void setMicroSteps(uint32_t _MicrostepsToStep) {
		MicrostepsToStep = _MicrostepsToStep;
		saveParam(mSetMicrostepsToStep, 0, MicrostepsToStep, 0);
	}
	uint32_t getMicroSteps(bool R_Wr) {
		if (R_Wr) return ReadMicrostepsToStep;
		else return MicrostepsToStep;
	}
	void setStepsToTurn(uint32_t _StepsToTurn) {
		StepsToTurn = _StepsToTurn;
		saveParam(mSetStepsToTurn, 0, StepsToTurn, 0);
	}
	uint32_t getStepsToTurn(bool R_Wr) {
		if (R_Wr) return ReadStepsToTurn;
		else return StepsToTurn;
	}
	uint8_t setOutToZState(uint8_t _NumOut, bool _TrueFalse) {
		Byte8BitMask tmpNumOutZState = { 0 };
		tmpNumOutZState.raw = NumOutZState;
		if (_NumOut < 8) {
            if (_TrueFalse) tmpNumOutZState.raw |= (1 << _NumOut);
            else tmpNumOutZState.raw &= ~(1 << _NumOut);
        }
		NumOutZState = tmpNumOutZState.raw;
		return NumOutZState;
	}
	uint8_t setOutToHiState(uint8_t _NumOut, bool _TrueFalse) {
		Byte8BitMask tmpNumOutHiState = { 0 };
		tmpNumOutHiState.raw = NumOutHiState;
		if (_NumOut < 8) {
            if (_TrueFalse) tmpNumOutHiState.raw |= (1 << _NumOut);
            else tmpNumOutHiState.raw &= ~(1 << _NumOut);
        }
		NumOutHiState = tmpNumOutHiState.raw;
		return NumOutHiState;
	}
	uint8_t setOutToLoState(uint8_t _NumOut, bool _TrueFalse) {
		Byte8BitMask tmpNumOutLoState = { 0 };
		tmpNumOutLoState.raw = NumOutLoState;
		if (_NumOut < 8) {
            if (_TrueFalse) tmpNumOutLoState.raw |= (1 << _NumOut);
            else tmpNumOutLoState.raw &= ~(1 << _NumOut);
        }
		NumOutLoState = tmpNumOutLoState.raw;
		return NumOutZState;
	}
	void setOutToZ(uint8_t _NumOut) {
		setOutToZState(_NumOut, true);
		setOutToHiState(_NumOut, false);
		setOutToLoState(_NumOut, false);
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = out_to_z_state;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = _NumOut;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	void setOutToHi(uint8_t _NumOut) {
		setOutToZState(_NumOut, false);
		setOutToHiState(_NumOut, true);
		setOutToLoState(_NumOut, false);
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = out_to_vcc;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = _NumOut;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	void setOutToLo(uint8_t _NumOut) {
		setOutToZState(_NumOut, false);
		setOutToHiState(_NumOut, true);
		setOutToLoState(_NumOut, false);
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = out_to_gnd;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = _NumOut;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	_NumOutState getOutState(uint8_t _NumOut, bool R_Wr) {
		Byte8BitMask tmpNumOutZState = { 0 };
		if (R_Wr) { tmpNumOutZState.raw = ReadNumOutZState; }
		else { tmpNumOutZState.raw = NumOutZState; }
		Byte8BitMask tmpNumOutHiState = { 0 };
		if (R_Wr) { tmpNumOutHiState.raw = ReadNumOutHiState; }
		else { tmpNumOutHiState.raw = NumOutHiState; }
		Byte8BitMask tmpNumOutLoState = { 0 };
		if (R_Wr) { tmpNumOutLoState.raw = ReadNumOutLoState; }
		else { tmpNumOutLoState.raw = NumOutHiState; }
		
		if (_NumOut < 8) {
            if ((tmpNumOutZState.raw >> _NumOut) & 1) return eNumOutZState;
            if ((tmpNumOutHiState.raw >> _NumOut) & 1) return eNumOutHiState;
            if ((tmpNumOutLoState.raw >> _NumOut) & 1) return eNumOutLoState;
        }
		return eNumOutUnknownState;
	}

	uint16_t setInToNoPullupDown(uint16_t _NumIn, bool _TrueFalse) {
		Byte16BitMask tmpNumInNoPullupDown = { 0 };
		tmpNumInNoPullupDown.raw = NumInNoPullupDown;
		if (_NumIn < 12) {
            if (_TrueFalse) tmpNumInNoPullupDown.raw |= (1 << _NumIn);
            else tmpNumInNoPullupDown.raw &= ~(1 << _NumIn);
        }
		NumInNoPullupDown = tmpNumInNoPullupDown.raw;
		return NumInNoPullupDown;
	}

	uint16_t setInPullUp(uint16_t _NumIn, bool _TrueFalse) {
		Byte16BitMask tmpNumInPullUp = { 0 };
		tmpNumInPullUp.raw = NumInPullUp;
		if (_NumIn < 12) {
            if (_TrueFalse) tmpNumInPullUp.raw |= (1 << _NumIn);
            else tmpNumInPullUp.raw &= ~(1 << _NumIn);
        }
		NumInPullUp = tmpNumInPullUp.raw;
		return NumInPullUp;
	}

	uint16_t setInPullDown(uint16_t _NumIn, bool _TrueFalse) {
		Byte16BitMask tmpNumInPullDown = { 0 };
		tmpNumInPullDown.raw = NumInPullDown;
		if (_NumIn < 12) {
            if (_TrueFalse) tmpNumInPullDown.raw |= (1 << _NumIn);
            else tmpNumInPullDown.raw &= ~(1 << _NumIn);
        }
		NumInPullDown = tmpNumInPullDown.raw;
		return NumInPullDown;
	}

	void setInToZ(uint16_t _NumIn) {
		setInToNoPullupDown(_NumIn, true);
		setInPullUp(_NumIn, false);
		setInPullDown(_NumIn, false);
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = input_to_z_state;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = _NumIn;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	void setInPullUp(uint16_t _NumIn) {
		setInToNoPullupDown(_NumIn, true);
		setInPullUp(_NumIn, false);
		setInPullDown(_NumIn, false);
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = input_to_vcc;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = _NumIn;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};
	void setInPullDown(uint16_t _NumIn) {
		setInToNoPullupDown(_NumIn, true);
		setInPullUp(_NumIn, false);
		setInPullDown(_NumIn, false);
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = input_to_gnd;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = _NumIn;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = 0;
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	};

	_NumInPullUpDown getInPullupDown(uint16_t _NumIn, bool R_Wr) {
		Byte16BitMask tmpNumInNoPullupDown = { 0 };
		if (R_Wr) { tmpNumInNoPullupDown.raw = ReadNumInNoPullupDown; }
		else { tmpNumInNoPullupDown.raw = NumInNoPullupDown; }
		Byte16BitMask tmpNumInPullUp = { 0 };
		if (R_Wr) { tmpNumInPullUp.raw = ReadNumInPullUp; }
		else { tmpNumInPullUp.raw = NumInPullUp; }
		Byte16BitMask tmpNumInPullDown = { 0 };
		if (R_Wr) { tmpNumInPullDown.raw = ReadNumInPullDown; }
		else { tmpNumInPullDown.raw = NumInPullDown; }
		
		if (_NumIn < 12) {
            if ((tmpNumInNoPullupDown.raw >> _NumIn) & 1) return eNumInNoPullupDown;
            if ((tmpNumInPullUp.raw >> _NumIn) & 1) return eNumInPullUp;
            if ((tmpNumInPullDown.raw >> _NumIn) & 1) return eNumInPullDown;
        }
		return eNumInUnknownPullupDown;
	}
	void SetIHOLD(uint8_t _IHOLD, uint8_t _IRUN, uint8_t _IHOLDDELAY) {
		TMC_IHOLD = _IHOLD;
		TMC_IRUN = _IRUN;
		IHOLDDELAY = _IHOLDDELAY;
		Byte32BitMask b32TmpParamSave = { 0 };
		b32TmpParamSave.u8Mask[0] = TMC_IHOLD;
		b32TmpParamSave.u8Mask[1] = TMC_IRUN;
		b32TmpParamSave.u8Mask[2] = IHOLDDELAY;
		saveParam(mSetTMC_IHOLD, 0, StepsToTurn, 0);
	}
	uint8_t GetIHOLD(bool R_Wr) {
		if (R_Wr) return ReadTMC_IHOLD;
		else return TMC_IHOLD;
	}
	uint8_t GetIRUN(bool R_Wr) {
		if (R_Wr) return ReadTMC_IRUN;
		else return TMC_IRUN;
	}
	uint8_t GetIHOLDDELAY(bool R_Wr) {
		if (R_Wr) return ReadIHOLDDELAY;
		else return IHOLDDELAY;
	}
	void setTPWMTHRS(uint8_t _TPWMTHRS) {
		TMC_TPWMTHRS = _TPWMTHRS;
		saveParam(mSetTMC_TPWMTHRS, TMC_TPWMTHRS, 0, 0);
	}
	uint8_t getTPWMTHRS(bool R_Wr) {
		if (R_Wr) return ReadTMC_TPWMTHRS;
		else return TMC_TPWMTHRS;
	}
	void SaveInPullUps() {
		saveParam(mSetInputsToVccGND, 0, 0, 0);
	}
	void setEncoderActive(bool _set) {
		saveParam(mSetEncoderActive, _set, 0, 0);
	}
	void setCOOLCONF(uint8_t Seup, uint8_t Sedn, bool Seimin, bool SGFilter, uint8_t Semin, uint8_t Semax, uint8_t SGThreshold) {
		Byte32BitMask b32TmpParamSave = { 0 };
		Byte8BitMask b8TmpData = { 0 };
		b8TmpData.raw = Seup;
		b32TmpParamSave.b.b_0 = b8TmpData.b.b_0;
		b32TmpParamSave.b.b_1 = b8TmpData.b.b_1;
		b8TmpData.raw = Sedn;
		b32TmpParamSave.b.b_2 = b8TmpData.b.b_0;
		b32TmpParamSave.b.b_3 = b8TmpData.b.b_1;
		b32TmpParamSave.b.b_4 = Seimin;
		b32TmpParamSave.b.b_5 = SGFilter;
		b32TmpParamSave.u8Mask[1] = Semin;
		b32TmpParamSave.u8Mask[2] = Semax;
		b32TmpParamSave.u8Mask[3] = SGThreshold;
		saveParam(mSetTMC_COOLCONF, 0, b32TmpParamSave.raw, 0);
	}
	void setEncoderConfig(uint8_t EncoderPolarity, uint8_t EncoderDelta, uint16_t EncoderToTurnData) {
		Byte32BitMask b32TmpParamSave = { 0 };
		Byte16BitMask b16TmpData = { 0 };
		b32TmpParamSave.u8Mask[0] = EncoderPolarity;
		b32TmpParamSave.u8Mask[1] = EncoderDelta;
		b16TmpData.raw = EncoderToTurnData;
		b32TmpParamSave.u8Mask[2] = b16TmpData.u8Mask[0];
		b32TmpParamSave.u8Mask[3] = b16TmpData.u8Mask[1];
		saveParam(mSetEncoderPolarityDeltaTurn, 0, b32TmpParamSave.raw, 0);
	}
	void setGLOBAL_SCALER(uint8_t _GLOBAL_SCALER) {
		saveParam(mSetGLOBAL_SCALER, _GLOBAL_SCALER, 0, 0);
	}
	void setControlPositioning_Velocity(bool Pos_Vel) {
		if (Pos_Vel)
		{
			CanInLoc->devID = NumBoard;
			CanInLoc->group = Group;
			CanInLoc->numCommand = tmc_positioning_velocity;
			CanInLoc->setups = 0;
			CanInLoc->Data0 = 0;
			CanInLoc->Data1 = 0;
			CanInLoc->Data2 = 0;
			CanInLoc->Data3 = 0;
			uint8_t u8tmpCommand = CanInLoc->setups;
			uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
			setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
			SetCANControl(*CanInLoc);
		}
		else
		{
			CanInLoc->devID = NumBoard;
			CanInLoc->group = Group;
			CanInLoc->numCommand = tmc_positioning_velocity;
			CanInLoc->setups = 0;
			CanInLoc->Data0 = 1;
			CanInLoc->Data1 = 0;
			CanInLoc->Data2 = 0;
			CanInLoc->Data3 = 0;
			uint8_t u8tmpCommand = CanInLoc->setups;
			uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
			setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
			SetCANControl(*CanInLoc);
		}
	}
	uint8_t getAutosenderDelay() {
		return AutosenderDelay;
	}
	void setAutosender(uint8_t _AutosenderType, uint8_t _AutosenderDelay, uint8_t _AutosenderNum) {
		AutosenderType = _AutosenderType;
		AutosenderDelay = _AutosenderDelay;
		CanInLoc->devID = NumBoard;
		CanInLoc->group = Group;
		CanInLoc->numCommand = autosender;
		CanInLoc->setups = 0;
		CanInLoc->Data0 = AutosenderType;
		CanInLoc->Data1 = 0;
		CanInLoc->Data2 = 0;
		CanInLoc->Data3 = AutosenderDelay;
		if (_AutosenderType == 254)
		{
			CanInLoc->Data1 = _AutosenderNum;
		}
		uint8_t u8tmpCommand = CanInLoc->setups;
		uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
		setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
		SetCANControl(*CanInLoc);
	}

	void setCmdToMechanism(uint8_t* Cmd, uint8_t* NumCmd) {
		if (*NumCmd)
		{
			NumCmdTransmitted = *NumCmd;
			CmdTransmitted = 0;
		}
		else
		{
			NumCmdTransmitted = 0;
			CmdTransmitted = *Cmd;
		}
	}
	void setCmdFromMechanism(uint8_t* Cmd, uint8_t* NumCmd, uint8_t* CmdInWork) {
		if (*NumCmd)
		{
			NumCmdRescived = *NumCmd;
			CmdRescived = 0;
		}
		else
		{
			NumCmdRescived = 0;
			CmdRescived = *Cmd;
		}
		u8CmdInWork = *CmdInWork;
	}
	bool getCmdInWork() {
		if (NumCmdTransmitted)
		{
			if (NumCmdRescived == NumCmdTransmitted)
			{
				if (u8CmdInWork)
				{
					return true;
				}
			}
		}
		else
		{
			if (CmdTransmitted == CmdRescived)
			{
				if (u8CmdInWork)
				{
					return true;
				}
			}
		}
		return false;
	}
};

uint32_t Mechanism::u32AutosenderTestNum = 0;
uint32_t Mechanism::u32AutosenderTestCheck = 0;
uint32_t Mechanism::u32AutosenderTestErrNum = 0;
bool Mechanism::bTestError = false;

#endif //__MECHANISM_H_