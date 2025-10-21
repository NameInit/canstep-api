#pragma once

#ifndef __DEFS_CAN_STEP_H_
#define __DEFS_CAN_STEP_H_

#include <cstdint>

#define MAX_ASK_SIZE				25

#define USB_CAN_FRAME_Num			16

#define CAN_ID_EMERGENCY_GLOBAL 	10
#define CAN_ID_DRIVER_TRANSCEIVER	82
#define CAN_ID_CENTRAL_CONTROL 		1000
#define CAN_ID_CENTRAL_CONFIG 		1001
#define CAN_ID_ANSWER_CONTROL 		900
#define CAN_ID_ANSWER_CONFIG 		901
#define CAN_ID_ASK					100
#define CAN_ID_ANSWER				101
#define CAN_ID_NET_MASTER			5

#define TMC_FREQ					12000000

#define B_POS_EN		b_0
#define B_POS_AL_CLR	b_1
#define B_POS_OBRAKE	b_2
#define B_POS_ORESERV	b_3

#define	END_OF_ASK			56
#define ONE_STEP_UPDATE
#define DELAY_BEFORE_ASK	30
#define DELAY_AFTER_ASK		20

#define BTMC_sfilt				b_24
#define BTMC_sgt6				b_22
#define BTMC_sgt5				b_21
#define BTMC_sgt4				b_20
#define BTMC_sgt3				b_19
#define BTMC_sgt2				b_18
#define BTMC_sgt1				b_17
#define BTMC_sgt0				b_16
#define BTMC_seimin				b_15
#define BTMC_sedn1				b_14
#define BTMC_sedn0				b_13
#define BTMC_semax3				b_11
#define BTMC_semax2				b_10
#define BTMC_semax1				b_9
#define BTMC_semax0				b_8
#define BTMC_seup1				b_6
#define BTMC_seup0				b_5
#define BTMC_semin3				b_3
#define BTMC_semin2				b_2
#define BTMC_semin1				b_1
#define BTMC_semin0				b_0

#endif //__DEFS_CAN_STEP_H_