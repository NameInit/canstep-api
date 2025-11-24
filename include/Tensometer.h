#pragma once

#ifndef __TENSOMETER_H_
#define __TENSOMETER_H_

#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <cstring>
#include <cstdio>
#include "Typedefs.h"
#include "Defs.h"
#include "TypesTenso.h"
#include "HidDevice.h"

using Tensometer_Callback_ANSWER_Delegate = std::function<void(_CAN_Ask_Channel* pChannel, uint32_t* data)>;

class Tensometer
{
private:
	uint8_t		NumBoard;

	static _AskTypeCMDMod eCMDMod;
	static _CAN_Ask_Channel eNumChannel;
	static _AskTypeCMDModCh eCMDModCh;
	static _AskTypeCMDChTenso eCMDChTenso;
	static _AskTypeCMDChTermo eCMDChTermo;
	static _CAN_AskType eAskType;

	std::unique_ptr<_CAN_input_emergancy> pCan_EmergancyMess;
	std::unique_ptr<_CAN_ASK_Output> pASK_OutputMess;
	std::unique_ptr<_CAN_Ask> pAskMess;
	std::unique_ptr<_CMD_Mem> pCMDMess;

	static _CAN_Ask_Channel RessAsk_Channel;
	static uint32_t u32OUT_COM;

public: 
	HidDevice* pHidDevice;
private: 
	Tensometer_Callback_ANSWER_Delegate callbackTensometerAnswer;
public:
	std::vector<uint8_t> StructToVector(const USBHIDFrame& frame);
	void CallbackTensometerAnswer(_CAN_Ask_Channel* pChannel, uint32_t* pData);
	void SetCallbackTensometerAnswer(const Tensometer_Callback_ANSWER_Delegate& callback);
	Tensometer(uint8_t _NumBoard);
	void SetHidDevice(HidDevice* hidDevice);
	void TensometerParsing(USBCANFrame *pUSBCANFrame);
	void AskTensometerStatus();
	void TensometerCalibrVIn();
	void TensometerCalibrPhoto();
	void TensometerCMDMod(uint16_t* pFTensoMedian, uint16_t* pFTensoExp, uint16_t* pFTensoAverage, 
		uint16_t* pFTermoMedian, uint16_t* pFTermoExp, uint16_t* pFTermoAverage, uint16_t* pFreqAnswer);
	void TensometerCMDTenso(bool* pTensoChannelOk, TensoDataRate* pTensoDataRate, TensoGain* pTensoGain);
	void TensometerCMDTermo(bool* pTensoChannelOk, uint8_t* pTermoDatarate, uint8_t* pTermoGain);
	void TensometerClearZero(bool* pTensoChannelOk);
	void TensometerCalibrWeight(bool* pTensoChannelOk);
	void TensometerShowResult(_CAN_Ask_Channel* pChannel, uint32_t* pData);
	void TensometerStartCh(_CAN_Ask_Channel* pChannel);
	void TensometerNoiseReset();
	void TensometerZeroDriftReset();
	void TensometerAskSensorChannel(_CAN_Ask_Channel* pChannel);
	void SetCANControlTensometer(const _CAN_Ask& pCan_Ask);
};

#endif //__TENSOMETER_H_#pragma once