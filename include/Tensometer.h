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
	std::vector<uint8_t> StructToVector(const USBHIDFrame& frame)
	{
		std::vector<uint8_t> data(sizeof(USBHIDFrame));
		memcpy(data.data(), &frame, sizeof(USBHIDFrame));
		return data;
	}
	void CallbackTensometerAnswer(_CAN_Ask_Channel* pChannel, uint32_t* pData) {
		if (callbackTensometerAnswer) {
			callbackTensometerAnswer(pChannel, pData);
		}
	};
	void SetCallbackTensometerAnswer(const Tensometer_Callback_ANSWER_Delegate& callback) {
		callbackTensometerAnswer = callback;
	}

public:
	Tensometer(uint8_t _NumBoard) {
		NumBoard = _NumBoard;
		pCan_EmergancyMess = std::make_unique<_CAN_input_emergancy>();
		pASK_OutputMess = std::make_unique<_CAN_ASK_Output>();
		pAskMess = std::make_unique<_CAN_Ask>();
		pCMDMess = std::make_unique<_CMD_Mem>();
	}

	void SetHidDevice(HidDevice* hidDevice) { pHidDevice = hidDevice; }

	void TensometerParsing(USBCANFrame *pUSBCANFrame) {
		static _CAN_Ask_Channel TmpAsk_Channel;
		
		USBCANFrame NewUSBCANFrame = { 0 };
		memcpy(&NewUSBCANFrame.b128USBCANFrame.u8Mask[0], pUSBCANFrame, USB_CAN_FRAME_Num);

		static Byte32BitMask tmpCurrentOUT = { 0 };
		if (NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID == CAN_ID_TENSO_ANSWER)
		{
			tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
			tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
			tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
			tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
			RessAsk_Channel = (_CAN_Ask_Channel)NewUSBCANFrame.USB_CAN_Frame.eFrameData[3];
			TmpAsk_Channel = (_CAN_Ask_Channel)NewUSBCANFrame.USB_CAN_Frame.eFrameData[3];
			u32OUT_COM = tmpCurrentOUT.raw;

			CallbackTensometerAnswer(&TmpAsk_Channel, &tmpCurrentOUT.raw);
		}
	}

	void AskTensometerStatus() {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = 0;
		eAskType = CAN_Ask_Status;
		eNumChannel = ChannelOff;
		pAskMess->AskType = CAN_Ask_Status;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = 0;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;

		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCalibrVIn() {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = 0;
		pAskMess->AskType = CAN_Ask_CMD_Mod;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskCalibr_V24;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;

		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCalibrPhoto() {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = 0;
		pAskMess->AskType = CAN_Ask_CMD_Mod;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskCalibr_Photo;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCMDMod(uint16_t* pFTensoMedian, uint16_t* pFTensoExp, uint16_t* pFTensoAverage, 
		uint16_t* pFTermoMedian, uint16_t* pFTermoExp, uint16_t* pFTermoAverage, uint16_t* pFreqAnswer) {
		Byte16BitMask b16TmpData = { 0 };
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = 0;
		pAskMess->AskType = CAN_Ask_CMD_Mod;
		pAskMess->AskModuleAddress = 0;

		b16TmpData.raw = *pFTensoMedian;
		pAskMess->AskCMD1 = eAskFilterTensoMedian;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFTensoExp;
		pAskMess->AskCMD1 = eAskFilterTensoExp;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFTensoAverage;
		pAskMess->AskCMD1 = eAskFilterTensoAverage;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFTermoMedian;
		pAskMess->AskCMD1 = eAskFilterTermoMedian;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFTermoExp;
		pAskMess->AskCMD1 = eAskFilterTermoExp;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFTermoAverage;
		pAskMess->AskCMD1 = eAskFilterTermoAverage;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFreqAnswer;
		pAskMess->AskCMD1 = eAskCANAutosenderDelay;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCMDTenso(bool* pTensoChannelOk, TensoDataRate* pTensoDataRate, TensoGain* pTensoGain) {
		Byte8BitMask b8TmpData = { 0 };
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		if ((eNumChannel == Channel1_Tenso_0) || (eNumChannel == Channel2_Tenso_1) || (eNumChannel == Channel3_Tenso_2) || (eNumChannel == Channel4_Tenso_3))
		{
			pAskMess->AskChannelNumber = eNumChannel;
			*pTensoChannelOk = true;
		}
		else
		{
			*pTensoChannelOk = false;
			return;
		}

		pAskMess->AskType = CAN_Ask_CMD_Ch;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskTensoFreqGain;
		b8TmpData.raw = (uint8_t) *pTensoDataRate;
		pAskMess->AskCMDdata1 = b8TmpData.raw;
		b8TmpData.raw = (uint8_t)*pTensoGain;
		pAskMess->AskCMDdata2 = b8TmpData.raw;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCMDTermo(bool* pTensoChannelOk, uint8_t* pTermoDatarate, uint8_t* pTermoGain) {
		Byte8BitMask b8TmpData = { 0 };
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		if ((eNumChannel == Channel7_Termo_0) || (eNumChannel == Channel8_Termo_1) || (eNumChannel == Channel9_Termo_2) || (eNumChannel == Channel10_Termo_3))
		{
			pAskMess->AskChannelNumber = eNumChannel;
			*pTensoChannelOk = true;
		}
		else
		{
			*pTensoChannelOk = false;
			return;
		}
		pAskMess->AskType = CAN_Ask_CMD_Ch;
		pAskMess->AskModuleAddress = 0;

		pAskMess->AskCMD1 = eAskTermoFreqGain;
		b8TmpData.raw = *pTermoDatarate;
		pAskMess->AskCMDdata1 = b8TmpData.raw;
		b8TmpData.raw = *pTermoGain;
		pAskMess->AskCMDdata2 = b8TmpData.raw;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerClearZero(bool* pTensoChannelOk) {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		if ((eNumChannel == Channel1_Tenso_0) || (eNumChannel == Channel2_Tenso_1) || (eNumChannel == Channel3_Tenso_2) || (eNumChannel == Channel4_Tenso_3))
		{
			pAskMess->AskChannelNumber = eNumChannel;
			*pTensoChannelOk = true;
		}
		else
		{
			*pTensoChannelOk = false;
			return;
		}
		pAskMess->AskType = CAN_Ask_CMD_Ch;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskTensoZeroCLR;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCalibrWeight(bool* pTensoChannelOk) {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		if ((eNumChannel == Channel1_Tenso_0) || (eNumChannel == Channel2_Tenso_1) || (eNumChannel == Channel3_Tenso_2) || (eNumChannel == Channel4_Tenso_3))
		{
			pAskMess->AskChannelNumber = eNumChannel;
			*pTensoChannelOk = true;
		}
		else
		{
			*pTensoChannelOk = false;
			return;
		}
		pAskMess->AskType = CAN_Ask_CMD_Ch;
		pAskMess->AskModuleAddress = 0;

		pAskMess->AskCMD1 = eAskTensoWeightCalibr;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerShowResult(_CAN_Ask_Channel* pChannel, uint32_t* pData) {
		*pData = u32OUT_COM;		
		*pChannel = RessAsk_Channel;
	}

	void TensometerStartCh(_CAN_Ask_Channel* pChannel) {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = *pChannel;
		pAskMess->AskType = CAN_Ask_CMD_Ch;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskChannelEnable;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerNoiseReset() {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = ChannelOff;
		pAskMess->AskType = CAN_Ask_CMD_Mod;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskNoiseReset;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerZeroDriftReset() {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = ChannelOff;
		pAskMess->AskType = CAN_Ask_CMD_Mod;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskZrtoDriftReset;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerAskSensorChannel(_CAN_Ask_Channel* pChannel) {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		eAskType = CAN_Ask_Sensor;
		pAskMess->AskChannelNumber = *pChannel;
		pAskMess->AskType = eAskType;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = 0;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void SetCANControlTensometer(const _CAN_Ask& pCan_Ask)
	{
		USBCANFrame NewUSBCANFrame = { 0 };
		NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
		NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
		NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_TENSO_ASK;
		NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = pCan_Ask.AskModuleSystem;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = pCan_Ask.AskModuleType;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[2] = pCan_Ask.AskChannelNumber;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[3] = pCan_Ask.AskType;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[4] = pCan_Ask.AskModuleAddress;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[5] = pCan_Ask.AskCMD1;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[6] = pCan_Ask.AskCMDdata1;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[7] = pCan_Ask.AskCMDdata2;

		USBHIDFrame TmpUSBHIDFrameTS = { 0 };
		pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
		std::vector<uint8_t> data = StructToVector(TmpUSBHIDFrameTS);
		if (!pHidDevice->SendData(data))
		{
			fprintf(stderr, "Error when SetEmergancy transmit\n");
		}
	}
};

_AskTypeCMDMod Tensometer::eCMDMod = eAskNoCMDMod;
_CAN_Ask_Channel Tensometer::eNumChannel = ChannelOff;
_AskTypeCMDModCh Tensometer::eCMDModCh = eAskNoCMDCh;
_AskTypeCMDChTenso Tensometer::eCMDChTenso = eAskNoCMDTenso;
_AskTypeCMDChTermo Tensometer::eCMDChTermo = eAskNoCMDTermo;
_CAN_AskType Tensometer::eAskType = CAN_Ask_Off;
_CAN_Ask_Channel Tensometer::RessAsk_Channel;
uint32_t Tensometer::u32OUT_COM = 0;

#endif //__TENSOMETER_H_#pragma once

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
	std::vector<uint8_t> StructToVector(const USBHIDFrame& frame)
	{
		std::vector<uint8_t> data(sizeof(USBHIDFrame));
		memcpy(data.data(), &frame, sizeof(USBHIDFrame));
		return data;
	}
	void CallbackTensometerAnswer(_CAN_Ask_Channel* pChannel, uint32_t* pData) {
		if (callbackTensometerAnswer) {
			callbackTensometerAnswer(pChannel, pData);
		}
	};
	void SetCallbackTensometerAnswer(const Tensometer_Callback_ANSWER_Delegate& callback) {
		callbackTensometerAnswer = callback;
	}

public:
	Tensometer(uint8_t _NumBoard) {
		NumBoard = _NumBoard;
		pCan_EmergancyMess = std::make_unique<_CAN_input_emergancy>();
		pASK_OutputMess = std::make_unique<_CAN_ASK_Output>();
		pAskMess = std::make_unique<_CAN_Ask>();
		pCMDMess = std::make_unique<_CMD_Mem>();
	}

	void SetHidDevice(HidDevice* hidDevice) { pHidDevice = hidDevice; }

	void TensometerParsing(USBCANFrame *pUSBCANFrame) {
		static _CAN_Ask_Channel TmpAsk_Channel;
		
		USBCANFrame NewUSBCANFrame = { 0 };
		memcpy(&NewUSBCANFrame.b128USBCANFrame.u8Mask[0], pUSBCANFrame, USB_CAN_FRAME_Num);

		static Byte32BitMask tmpCurrentOUT = { 0 };
		if (NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID == CAN_ID_TENSO_ANSWER)
		{
			tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
			tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
			tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
			tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
			RessAsk_Channel = (_CAN_Ask_Channel)NewUSBCANFrame.USB_CAN_Frame.eFrameData[3];
			TmpAsk_Channel = (_CAN_Ask_Channel)NewUSBCANFrame.USB_CAN_Frame.eFrameData[3];
			u32OUT_COM = tmpCurrentOUT.raw;

			CallbackTensometerAnswer(&TmpAsk_Channel, &tmpCurrentOUT.raw);
		}
	}

	void AskTensometerStatus() {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = 0;
		eAskType = CAN_Ask_Status;
		eNumChannel = ChannelOff;
		pAskMess->AskType = CAN_Ask_Status;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = 0;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;

		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCalibrVIn() {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = 0;
		pAskMess->AskType = CAN_Ask_CMD_Mod;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskCalibr_V24;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;

		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCalibrPhoto() {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = 0;
		pAskMess->AskType = CAN_Ask_CMD_Mod;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskCalibr_Photo;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCMDMod(uint16_t* pFTensoMedian, uint16_t* pFTensoExp, uint16_t* pFTensoAverage, 
		uint16_t* pFTermoMedian, uint16_t* pFTermoExp, uint16_t* pFTermoAverage, uint16_t* pFreqAnswer) {
		Byte16BitMask b16TmpData = { 0 };
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = 0;
		pAskMess->AskType = CAN_Ask_CMD_Mod;
		pAskMess->AskModuleAddress = 0;

		b16TmpData.raw = *pFTensoMedian;
		pAskMess->AskCMD1 = eAskFilterTensoMedian;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFTensoExp;
		pAskMess->AskCMD1 = eAskFilterTensoExp;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFTensoAverage;
		pAskMess->AskCMD1 = eAskFilterTensoAverage;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFTermoMedian;
		pAskMess->AskCMD1 = eAskFilterTermoMedian;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFTermoExp;
		pAskMess->AskCMD1 = eAskFilterTermoExp;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFTermoAverage;
		pAskMess->AskCMD1 = eAskFilterTermoAverage;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);

		b16TmpData.raw = *pFreqAnswer;
		pAskMess->AskCMD1 = eAskCANAutosenderDelay;
		pAskMess->AskCMDdata1 = b16TmpData.u8Mask[0];
		pAskMess->AskCMDdata2 = b16TmpData.u8Mask[1];
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCMDTenso(bool* pTensoChannelOk, TensoDataRate* pTensoDataRate, TensoGain* pTensoGain) {
		Byte8BitMask b8TmpData = { 0 };
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		if ((eNumChannel == Channel1_Tenso_0) || (eNumChannel == Channel2_Tenso_1) || (eNumChannel == Channel3_Tenso_2) || (eNumChannel == Channel4_Tenso_3))
		{
			pAskMess->AskChannelNumber = eNumChannel;
			*pTensoChannelOk = true;
		}
		else
		{
			*pTensoChannelOk = false;
			return;
		}

		pAskMess->AskType = CAN_Ask_CMD_Ch;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskTensoFreqGain;
		b8TmpData.raw = (uint8_t) *pTensoDataRate;
		pAskMess->AskCMDdata1 = b8TmpData.raw;
		b8TmpData.raw = (uint8_t)*pTensoGain;
		pAskMess->AskCMDdata2 = b8TmpData.raw;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCMDTermo(bool* pTensoChannelOk, uint8_t* pTermoDatarate, uint8_t* pTermoGain) {
		Byte8BitMask b8TmpData = { 0 };
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		if ((eNumChannel == Channel7_Termo_0) || (eNumChannel == Channel8_Termo_1) || (eNumChannel == Channel9_Termo_2) || (eNumChannel == Channel10_Termo_3))
		{
			pAskMess->AskChannelNumber = eNumChannel;
			*pTensoChannelOk = true;
		}
		else
		{
			*pTensoChannelOk = false;
			return;
		}
		pAskMess->AskType = CAN_Ask_CMD_Ch;
		pAskMess->AskModuleAddress = 0;

		pAskMess->AskCMD1 = eAskTermoFreqGain;
		b8TmpData.raw = *pTermoDatarate;
		pAskMess->AskCMDdata1 = b8TmpData.raw;
		b8TmpData.raw = *pTermoGain;
		pAskMess->AskCMDdata2 = b8TmpData.raw;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerClearZero(bool* pTensoChannelOk) {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		if ((eNumChannel == Channel1_Tenso_0) || (eNumChannel == Channel2_Tenso_1) || (eNumChannel == Channel3_Tenso_2) || (eNumChannel == Channel4_Tenso_3))
		{
			pAskMess->AskChannelNumber = eNumChannel;
			*pTensoChannelOk = true;
		}
		else
		{
			*pTensoChannelOk = false;
			return;
		}
		pAskMess->AskType = CAN_Ask_CMD_Ch;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskTensoZeroCLR;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerCalibrWeight(bool* pTensoChannelOk) {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		if ((eNumChannel == Channel1_Tenso_0) || (eNumChannel == Channel2_Tenso_1) || (eNumChannel == Channel3_Tenso_2) || (eNumChannel == Channel4_Tenso_3))
		{
			pAskMess->AskChannelNumber = eNumChannel;
			*pTensoChannelOk = true;
		}
		else
		{
			*pTensoChannelOk = false;
			return;
		}
		pAskMess->AskType = CAN_Ask_CMD_Ch;
		pAskMess->AskModuleAddress = 0;

		pAskMess->AskCMD1 = eAskTensoWeightCalibr;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerShowResult(_CAN_Ask_Channel* pChannel, uint32_t* pData) {
		*pData = u32OUT_COM;		
		*pChannel = RessAsk_Channel;
	}

	void TensometerStartCh(_CAN_Ask_Channel* pChannel) {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = *pChannel;
		pAskMess->AskType = CAN_Ask_CMD_Ch;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskChannelEnable;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerNoiseReset() {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = ChannelOff;
		pAskMess->AskType = CAN_Ask_CMD_Mod;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskNoiseReset;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerZeroDriftReset() {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		pAskMess->AskChannelNumber = ChannelOff;
		pAskMess->AskType = CAN_Ask_CMD_Mod;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = eAskZrtoDriftReset;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void TensometerAskSensorChannel(_CAN_Ask_Channel* pChannel) {
		pAskMess->AskModuleSystem = 10;
		pAskMess->AskModuleType = 51;
		eAskType = CAN_Ask_Sensor;
		pAskMess->AskChannelNumber = *pChannel;
		pAskMess->AskType = eAskType;
		pAskMess->AskModuleAddress = 0;
		pAskMess->AskCMD1 = 0;
		pAskMess->AskCMDdata1 = 0;
		pAskMess->AskCMDdata2 = 0;
		SetCANControlTensometer(*pAskMess);
	}

	void SetCANControlTensometer(const _CAN_Ask& pCan_Ask)
	{
		USBCANFrame NewUSBCANFrame = { 0 };
		NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
		NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
		NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_TENSO_ASK;
		NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = pCan_Ask.AskModuleSystem;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = pCan_Ask.AskModuleType;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[2] = pCan_Ask.AskChannelNumber;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[3] = pCan_Ask.AskType;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[4] = pCan_Ask.AskModuleAddress;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[5] = pCan_Ask.AskCMD1;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[6] = pCan_Ask.AskCMDdata1;
		NewUSBCANFrame.USB_CAN_Frame.eFrameData[7] = pCan_Ask.AskCMDdata2;

		USBHIDFrame TmpUSBHIDFrameTS = { 0 };
		pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
		std::vector<uint8_t> data = StructToVector(TmpUSBHIDFrameTS);
		if (!pHidDevice->SendData(data))
		{
			fprintf(stderr, "Error when SetEmergancy transmit\n");
		}
	}
};

_AskTypeCMDMod Tensometer::eCMDMod = eAskNoCMDMod;
_CAN_Ask_Channel Tensometer::eNumChannel = ChannelOff;
_AskTypeCMDModCh Tensometer::eCMDModCh = eAskNoCMDCh;
_AskTypeCMDChTenso Tensometer::eCMDChTenso = eAskNoCMDTenso;
_AskTypeCMDChTermo Tensometer::eCMDChTermo = eAskNoCMDTermo;
_CAN_AskType Tensometer::eAskType = CAN_Ask_Off;
_CAN_Ask_Channel Tensometer::RessAsk_Channel;
uint32_t Tensometer::u32OUT_COM = 0;

#endif //__TENSOMETER_H_