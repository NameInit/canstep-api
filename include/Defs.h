#pragma once

#ifndef __DEFS_H_
#define __DEFS_H_

#include <cstdint>

#define USB_CAN_FRAME_Num	16

#define CAN_ID_EMERGENCY_GLOBAL 	10

#define CAN_ID_CENTRAL_CONTROL 		1000
#define CAN_ID_CENTRAL_CONFIG 		1001
#define CAN_ID_ANSWER_CONTROL 		900
#define CAN_ID_ANSWER_CONFIG 		901
#define CAN_ID_ASK					100
#define CAN_ID_ANSWER				101
#define CAN_ID_NET_MASTER			5

#define CAN_ID_TRACTOR_ESC_ANSWER	501

#define CAN_ID_TENSO_ASK			510
#define CAN_ID_TENSO_ANSWER			511

#define TMC_FREQ					12000000

#define	END_OF_ASK			56
#define ONE_STEP_UPDATE
#define DELAY_BEFORE_ASK	30
#define DELAY_AFTER_ASK		20

#endif //__DEFS_H_