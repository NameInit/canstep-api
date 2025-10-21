#pragma once

#ifndef __TYPS_CAN_STEP_H_
#define __TYPS_CAN_STEP_H_

#include <iostream>
#include <cstdint>

#include "Types.h"

struct CAN_input_conf
{
	uint8_t devID;
	uint8_t set_param;
	uint8_t reserv1;
	uint8_t reserv2;
	uint8_t Data0;
	uint8_t Data1;
	uint8_t Data2;
	uint8_t Data3;
};

struct CAN_input_contr
{
	uint8_t devID;
	uint8_t setups;
	uint8_t group;
	uint8_t numCommand;
	uint8_t Data0;
	uint8_t Data1;
	uint8_t Data2;
	uint8_t Data3;
};

typedef enum NumOutState
{
	eNumOutZState = 0,
	eNumOutHiState = 1,
	eNumOutLoState = 2,
	eNumOutUnknownState = 255
} _NumOutState;

typedef enum NumInPullUpDown
{
	eNumInNoPullupDown = 0,
	eNumInPullUp = 1,
	eNumInPullDown = 2,
	eNumInUnknownPullupDown = 255
} _NumInPullUpDown;

typedef enum CANUpdater
{
	eCANUpdaterOff = 0,
	eCANUpdaterCentral = 1,
	eCANUpdaterBoardAuto = 2,
} _CANUpdater;

typedef enum eInvertedValue
{
	eUnknownInverted,
	eNotInverted,
	eInverted,
} _eInvertedValue;

typedef enum DirectionEnum {
	DirOff = 0,
	DirFwd = 1,
	DirBwd = 2,
} _DirectionEnum;

typedef enum InvertedValue
{
	NotInverted = 0,
	Inverted = 1,
	UnknownInverted = 255,
} _InvertedValue;

typedef enum AskEnum {
	AskPosition = 0,
	AskHomings = 1,
	AskSrartPoint,
	AskEndPoint,
	AskRange,
	AskInputs,
	AskMotorTorque,
	AskMotorSpeed,
	AskAbsolutePositionRotorUint,
	AskAbsolutePositionRotorGrad,
	AskAlarmCode,
	AskEncoder,
	AskCurrSpeed = 12,
	AskCurrAccel = 13,
	AskCurrDecel = 14,
	AskCurrDir = 15,
	AskCurrOutputs = 16,
	AskHomingAPolarity = 20,
	AskHomingBPolarity,
	AskHomingCPolarity,
	AskHomingDPolarity,
	AskTimeAccel,
	AskAccel,
	AskDecel,
	AskHomingADirection,
	AskHomingBDirection,
	AskHomingCDirection,
	AskHomingDDirection,
	AskmaxSpeed,
	AskSavedSpeed,
	AskDeltaPosition,
	AskSRVRDYPolarity,
	AskINPOSPolarity,
	AskFAULTPolarity,
	AskBRAKEPolarity,
	AskEnPolarity,
	AskAL_CLRPolarity,
	AskOBRAKEPolarity,
	AskOReservPolarity,
	AskDIRPolarity,
	AskGroup,
	AskOuts0_7,
	AskInputs0_11,
	AskTest = 254,
	AskNull = 255
} _AskEnum;

typedef enum OutTypeEnum {
	OutPosition = 0,
	OutLimitSwitchesCondition = 1,
	OutStartPoint,
	OutEndPoint,
	OutRange,
	OutInputs,
	OutMotorTorque,
	OutMotorSpeed,
	OutAbsolutePositionRotorUint,
	OutAbsolutePositionRotorGrad,
	OutAlarmCode,
	OutEncoder,
	OutCurrSpeed = 12,
	OutCurrAccel = 13,
	OutCurrDecel = 14,
	OutCurrDir = 15,
	OutCurrOutputs = 16,
	OutHomingAPolarity = 20,
	OutHomingBPolarity,
	OutHomingCPolarity,
	OutHomingDPolarity,
	OutTimeAccel,
	OutAccel,
	OutDecel,
	OutHomingADirection,
	OutHomingBDirection,
	OutHomingCDirection,
	OutHomingDDirection,
	OutmaxSpeed,
	OutSavedSpeed,
	OutDeltaPosition,
	OutSRVRDYPolarity,
	OutINPOSPolarity,
	OutFAULTPolarity,
	OutBRAKEPolarity,
	OutEnPolarity,
	OutAL_CLRPolarity,
	OutOBRAKEPolarity,
	OutOReservPolarity,
	OutDIRPolarity,
	OutGroup,
	OutOuts0_7,
	OutInputs0_11,
	OutPullUpDwnInputs0_11,
	OutEncoderActive,
	OutIholdIrun,
	OutTPWMTHRS,
	OutSteps,
	OutCOOLCONF,
	OutStallGuard2Result,
	OutEncoderPolarityDeltaTurn,
	OutGLOBAL_SCALER,
	OutEncoderRaw,
	OutVActual,
	OutTest = 254,
	OutNull = 255,
} _OutTypeEnum;

typedef struct CAN_input_control
{
	uint8_t devID;
	uint8_t setups;
	uint8_t group;
	uint8_t numCommand;
	uint8_t Data0;
	uint8_t Data1;
	uint8_t Data2;
	uint8_t Data3;
} _CAN_input_control;

typedef struct CAN_outputControl
{
	uint8_t reserv1;
	uint8_t devID;
	uint8_t reserv2;
	uint8_t CMDType;
	uint8_t CMDNum;
	uint8_t reserv3;
	uint8_t ChannelStart;
	uint8_t NumError;
} _CAN_outputControl;

typedef enum NumCommand {
	cantrol_command = 0,
	homing_zero = 1,
	homing_max = 2,
	reset_drv_err = 3,
	brake_on = 4,
	brake_off = 5,
	rez_on = 6,
	rez_off = 7,
	al_clr_on = 8,
	al_clr_off = 9,
	debug_on = 10,
	curr_position = 11,
	out_to_gnd = 12,
	out_to_vcc = 13,
	out_to_z_state = 14,
	input_to_gnd = 15,
	input_to_vcc = 16,
	input_to_z_state = 17,
	tmc_mosfet_off = 18,
	tmc_positioning_velocity = 19,
	autosender = 20,
} _NumCommand;

typedef struct CAN_input_config
{
	uint8_t devID;
	uint8_t set_param;
	uint8_t reserv1;
	uint8_t reserv2;
	uint8_t Data0;
	uint8_t Data1;
	uint8_t Data2;
	uint8_t Data3;
} _CAN_input_config;

typedef struct ParamFlash {
	uint8_t		NumBoard;
	uint8_t		HomingAPolarity;
	uint8_t		HomingBPolarity;
	uint8_t		HomingCPolarity;
	uint8_t		HomingDPolarity;
	uint32_t	StartPosition;
	uint32_t	EndPosition;
	uint32_t	Range;
	uint8_t		TimeAccel;
	uint8_t		Accel;
	uint8_t		Decel;
	uint8_t 	HomingADirection;
	uint8_t 	HomingBDirection;
	uint8_t 	HomingCDirection;
	uint8_t 	HomingDDirection;
	uint8_t 	FirstStart;
	float 		maxSpeed;
	float 		CurrSpeed;
	uint32_t	DeltaPosition;
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
} _ParamFlash;

typedef enum MenuLVConfig
{
	mNullParam = 0,
	mNumBoard = 1,
	mHomingAPolarity = 2,
	mHomingBPolarity = 3,
	mHomingCPolarity = 4,
	mHomingDPolarity = 5,
	mStartPosition = 6,
	mEndPosition = 7,
	mAccelMem = 8,
	mDecelMem = 9,
	mHomingADirection = 10,
	mHomingBDirection = 11,
	mHomingCDirection = 12,
	mHomingDDirection = 13,
	mMaxSpeed = 14,
	mCurrSpeed = 15,
	mDeltaPosition = 16,
	mEnPolarity = 17,
	mAL_CLRPolarity = 18,
	mOBRAKEPolarity = 19,
	mOReservPolarity = 20,
	mSRVRDYPolarity = 21,
	mINPOSPolarity = 22,
	mFAULTPolarity = 23,
	mBRAKEPolarity = 24,
	mDIRPolarity = 25,
	mSaveGroup = 26,
	mSetMicrostepsToStep = 27,
	mSetStepsToTurn = 28,
	mSetInputsToVccGND = 29,
	mSetEncoderActive = 30,
	mSetTMC_IHOLD = 31,
	mSetTMC_TPWMTHRS = 32,
	mSetTMC_COOLCONF = 33,
	mSetEncoderPolarityDeltaTurn = 34,
	mSetGLOBAL_SCALER = 35,
	mSetFreewheel = 36,
} _MenuLVConfig;

#endif //__TYPS_CAN_STEP_H_