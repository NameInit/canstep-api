#pragma once

#ifndef __TYPS_H_
#define __TYPS_H_

#include <Typedefs.h>
#include <iostream>
#include <cstdint>

typedef enum TypeID
{
	CAN_11_Bit = 0,
	CAN_29_Bit = 1,
}_TypeID;

typedef enum USB_CAN_CMD
{
	NoCMD = 0,
	SetCAN_IDFilter,
	CAN_Transmit,
	CAN_Rescive
}_USB_CAN_CMD;

typedef struct USB_CAN_Frame
{
	_USB_CAN_CMD CMD;
	uint32_t CAN_DEV_ID;
	uint8_t Size;
	_TypeID TypeID;
	uint8_t FrameData[8];
}_USB_CAN_Frame;

typedef union _USBCANFrame
{
	struct
	{
		uint32_t eCAN_DEV_ID;
		uint8_t eFrameData[8];
		uint8_t eCMD;
		uint8_t eTypeID;
		uint8_t eSize;
		uint8_t LastError;
	}USB_CAN_Frame;
	Byte128BitMask b128USBCANFrame;
}USBCANFrame;

typedef struct _USBHIDFrame
{
	uint32_t eInitData;
	uint8_t eFrameData[16];
	uint32_t eNumUSBTxErrors;
	uint8_t eOtherData[40];
}USBHIDFrame;

typedef struct CAN_input_emergancy
{
	uint8_t Emergancy;
	uint8_t devID;
	uint8_t Reload;
	uint8_t reserv1;
	uint8_t reserv2;
	uint8_t reserv3;
	uint8_t reserv4;
	uint8_t reserv5;
}_CAN_input_emergancy;

#endif //__TYPS_H_