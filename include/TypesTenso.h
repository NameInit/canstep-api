#pragma once

#ifndef __TYPS_TENSO_H_
#define __TYPS_TENSO_H_

#include <iostream>
#include <cstdint>
#include "Typedefs.h"
#include"Types.h"

typedef enum _AskTypeCMDMod {
	eAskNoCMDMod = 0,
	eAskCalibr_V24 = 1,
	eAskCalibr_Photo = 2,
	eAskFilterTensoMedian = 3,
	eAskFilterTensoExp = 4,
	eAskFilterTensoAverage = 5,
	eAskFilterTermoMedian = 6,
	eAskFilterTermoExp = 7,
	eAskFilterTermoAverage = 8,
	eAskCANAutosenderDelay = 9,
	eAskNoiseReset = 10,
	eAskZrtoDriftReset = 11,
}_AskTypeCMDMod;

typedef enum _AskTypeCMDModCh {
	eAskNoCMDCh = 0,
	eAskTensoFreqGain = 1,
	eAskTensoDataType = 2,
	eAskTensoZeroCLR = 3,
	eAskTensoWeightCalibr = 4,
	eAskTermoFreqGain = 5,
	eAskTermoIntExtDataType = 6,
	eAskTermoSet = 7,
	eAskChannelEnable = 8,
}_AskTypeCMDModCh;

typedef enum _AskTypeCMDChTenso {
	eAskNoCMDTenso = 0,
	eAskFreqTenso = 1,
	eAskGainTenso = 2,
	eAskDataTypeTenso = 3,
	eAskZero = 4,
}_AskTypeCMDChTenso;

typedef enum _AskTypeCMDChTermo {
	eAskNoCMDTermo = 0,
	eAskFreqTermo = 1,
	eAskGainTermo = 2,
	eAskDataTypeTermo = 3,
}_AskTypeCMDChTermo;

typedef struct CMD_Mem
{
	uint8_t CMD1;
	uint8_t CMDdata1;
	uint8_t CMDdata2;
}_CMD_Mem;

typedef enum CAN_AskType
{
	CAN_Ask_Off = 0,
	CAN_Ask_Sensor = 1,
	CAN_Ask_Status = 2,
	CAN_Ask_CMD_Mod = 3,
	CAN_Ask_CMD_Ch = 4,
}_CAN_AskType;

typedef enum CAN_Ask_Channel
{
	ChannelAll = 0,
	Channel1_Tenso_0 = 1,
	Channel2_Tenso_1 = 2,
	Channel3_Tenso_2 = 3,
	Channel4_Tenso_3 = 4,
	Channel5_Photo = 5,
	Channel6_V24 = 6,
	Channel7_Termo_0 = 7,
	Channel8_Termo_1 = 8,
	Channel9_Termo_2 = 9,
	Channel10_Termo_3 = 10,
	Channel11_Noise = 11,
	Channel11_ZeroDrift = 12,
	ChannelOff = 0xFF,
}_CAN_Ask_Channel;

typedef struct CAN_Ask
{
	uint8_t AskModuleSystem;
	uint8_t AskModuleType;
	uint8_t AskChannelNumber;
	_CAN_AskType AskType;
	uint8_t AskModuleAddress;
	uint8_t AskCMD1;
	uint8_t AskCMDdata1;
	uint8_t AskCMDdata2;
}_CAN_Ask;

typedef struct CAN_ASK_Output
{
	uint8_t ModuleSystem;
	uint8_t ModuleType;
	uint8_t DataType;
	uint8_t ChannelNumber;
	uint8_t Float0;
	uint8_t Float1;
	uint8_t Float2;
	uint8_t Float3;
}_CAN_ASK_Output;

typedef enum _TensoDataRate
{
	eDR2400Hz = 0,
	eDR1200Hz = 1,
	eDR600Hz = 2,
	eDR300Hz = 3,
	eDR150Hz = 4,
	eDR75Hz = 5,
	eDR37_5Hz = 6,
	eDR18_75Hz = 7,
	eDR10Hz60Notch = 8,
	eDR10Hz50Notch = 9,
	eDR5Hz60Notch = 10,
	eDR5Hz50Notch = 11,
	eDR2_5Hz60Notch = 12,
	eDR2_5Hz50Notch = 13,
	ePADC_Dis = 15
}TensoDataRate;

typedef enum _TensoGain
{
	eGain_1X = 0,
	eGain_2X = 1,
	eGain_4X = 2,
	eGain_6X = 3,
	eGain_8X = 4,
	eGain_12X = 5,
	eGain_16X = 6,
	eGain_24X = 7,
	eGain_32X = 8,
	eGain_48X = 9,
	eGain_64X = 10,
	eGain_96X = 11,
	eGain_128X = 12,
	eGain_192X = 13,
	eGain_256X = 14,
	eGain_1X_WO_Buffer = 15
}TensoGain;

#endif //__TYPS_TENSO_H_