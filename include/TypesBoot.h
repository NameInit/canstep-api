#pragma once

#ifndef __TYPS_BOOT_H_
#define __TYPS_BOOT_H_

#include <iostream>
#include <cstdint>
#include <string>
#include "Typedefs.h"
#include "Types.h"

//ERROR Bits
#define	B_CRC8_ERROR				b_0
#define	B_CRC32_ERROR				b_1
#define	B_LOST_BYTES_CRC32			b_2//CRC32
#define	B_LOST_BYTES_CRC8			b_3//CRC8
#define	B_TYPE_BOARD_ERROR			b_4//
#define	B_LOAD_STARTED				b_7

//SPI-Flash Page
#define PAGE_NUM_BYTES				256

//Bootloader Protocol CMD types
typedef enum _TypeCMDBootMod {
	eTestCMDBootMod = 0,
	eStartCANStepCMDBootMod = 1,
	eEndCANStepCMDBootMod = 2,
	eStartUSBCANCMDBootMod = 3,
	eEndUSBCANCMDBootMod = 4,
	eStartTractorESCCMDBootMod = 5,
	eEndTractorESCCMDBootMod = 6,
	eStartTensometerCMDBootMod = 7,
	eEndTensometerCMDBootMod = 8,
	eStartCMDBootMod = 9,//Rez
	eEndCMDBootMod = 10,//Rez

	eBoardType = 250,

	eOFFCMDBootMod = 255,//Rez
} TypeCMDBootMod;

typedef enum _TypeBootState {
	eNoBoot = 0,
	eBootLoading = 1,
	eBootLoaded = 2,
	eBootSaving = 3,
	eBootIsOk = 4,
	eBootLostCRC8 = 5,
	eBootLostCRC32 = 6,
	eBootTypeBoard = 7,

	eBootFault = 255
} TypeBootState;

typedef enum _TypeBoard {
	eNoTypeBoard = 0,
	eCAN_STEP = 1,
	eUSB_CAN = 2,
	eTractorESC = 3,
	eTensometer = 4,
} TypeBoard;

// Функция преобразования типа платы в строку
inline std::string TypeBoardToString(TypeBoard type)
{
	switch (type)
	{
	case eNoTypeBoard:  return "Нет платы";
	case eCAN_STEP:     return "CAN_STEP";
	case eUSB_CAN:      return "USB_CAN";
	case eTractorESC:   return "Tractor ESC";
	case eTensometer:   return "Тензометр";
	default:            return "Неизвестно";
	}
}

#pragma pack(push, 1)
typedef struct _CANBootloaderAnswer
{
	uint8_t NumBoard;
	TypeCMDBootMod TypeBootMod;
	uint8_t NumData;
	uint8_t CRCData;
	uint8_t Errors;
} CANBootloaderAnswer;

typedef struct _CANBootloaderSetData
{
	uint8_t NumBoard;
	TypeCMDBootMod TypeBootMod;
	uint8_t NumData;
	uint8_t CRCData;
	uint8_t Data0;
	uint8_t Data1;
	uint8_t Data2;
	uint8_t Data3;
} CANBootloaderSetData;
#pragma pack(pop)

#endif //__TYPS_BOOT_H_