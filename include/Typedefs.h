#pragma once

#ifndef __TYPDEFS_H_
#define __TYPDEFS_H_

#include <iostream>
#include <cstdint>

#ifndef ONE_BYTE128_BIT_MASK
#define ONE_BYTE128_BIT_MASK
typedef union _Byte128BitMask
{
	struct {
		bool b_0 : 1;
		bool b_1 : 1;
		bool b_2 : 1;
		bool b_3 : 1;
		bool b_4 : 1;
		bool b_5 : 1;
		bool b_6 : 1;
		bool b_7 : 1;
		bool b_8 : 1;
		bool b_9 : 1;
		bool b_10 : 1;
		bool b_11 : 1;
		bool b_12 : 1;
		bool b_13 : 1;
		bool b_14 : 1;
		bool b_15 : 1;
		bool b_16 : 1;
		bool b_17 : 1;
		bool b_18 : 1;
		bool b_19 : 1;
		bool b_20 : 1;
		bool b_21 : 1;
		bool b_22 : 1;
		bool b_23 : 1;
		bool b_24 : 1;
		bool b_25 : 1;
		bool b_26 : 1;
		bool b_27 : 1;
		bool b_28 : 1;
		bool b_29 : 1;
		bool b_30 : 1;
		bool b_31 : 1;
		bool b_32 : 1;
		bool b_33 : 1;
		bool b_34 : 1;
		bool b_35 : 1;
		bool b_36 : 1;
		bool b_37 : 1;
		bool b_38 : 1;
		bool b_39 : 1;
		bool b_40 : 1;
		bool b_41 : 1;
		bool b_42 : 1;
		bool b_43 : 1;
		bool b_44 : 1;
		bool b_45 : 1;
		bool b_46 : 1;
		bool b_47 : 1;
		bool b_48 : 1;
		bool b_49 : 1;
		bool b_50 : 1;
		bool b_51 : 1;
		bool b_52 : 1;
		bool b_53 : 1;
		bool b_54 : 1;
		bool b_55 : 1;
		bool b_56 : 1;
		bool b_57 : 1;
		bool b_58 : 1;
		bool b_59 : 1;
		bool b_60 : 1;
		bool b_61 : 1;
		bool b_62 : 1;
		bool b_63 : 1;
		bool b_64 : 1;
		bool b_65 : 1;
		bool b_66 : 1;
		bool b_67 : 1;
		bool b_68 : 1;
		bool b_69 : 1;
		bool b_70 : 1;
		bool b_71 : 1;
		bool b_72 : 1;
		bool b_73 : 1;
		bool b_74 : 1;
		bool b_75 : 1;
		bool b_76 : 1;
		bool b_77 : 1;
		bool b_78 : 1;
		bool b_79 : 1;
		bool b_80 : 1;
		bool b_81 : 1;
		bool b_82 : 1;
		bool b_83 : 1;
		bool b_84 : 1;
		bool b_85 : 1;
		bool b_86 : 1;
		bool b_87 : 1;
		bool b_88 : 1;
		bool b_89 : 1;
		bool b_90 : 1;
		bool b_91 : 1;
		bool b_92 : 1;
		bool b_93 : 1;
		bool b_94 : 1;
		bool b_95 : 1;
		bool b_96 : 1;
		bool b_97 : 1;
		bool b_98 : 1;
		bool b_99 : 1;
		bool b_100 : 1;
		bool b_101 : 1;
		bool b_102 : 1;
		bool b_103 : 1;
		bool b_104 : 1;
		bool b_105 : 1;
		bool b_106 : 1;
		bool b_107 : 1;
		bool b_108 : 1;
		bool b_109 : 1;
		bool b_110 : 1;
		bool b_111 : 1;
		bool b_112 : 1;
		bool b_113 : 1;
		bool b_114 : 1;
		bool b_115 : 1;
		bool b_116 : 1;
		bool b_117 : 1;
		bool b_118 : 1;
		bool b_119 : 1;
		bool b_120 : 1;
		bool b_121 : 1;
		bool b_122 : 1;
		bool b_123 : 1;
		bool b_124 : 1;
		bool b_125 : 1;
		bool b_126 : 1;
		bool b_127 : 1;
	} b;
	uint8_t u8Mask[16];
	uint16_t u16Mask[8];
	uint32_t u32Mask[4];
	uint64_t u64Mask[2];
}Byte128BitMask;
#endif

#ifndef ONE_BYTE64_BIT_MASK
#define ONE_BYTE64_BIT_MASK
typedef union _Byte64BitMask
{
	struct {
		bool b_0 :1;
		bool b_1 :1;
		bool b_2 :1;
		bool b_3 :1;
		bool b_4 :1;
		bool b_5 :1;
		bool b_6 :1;
		bool b_7 :1;
		bool b_8 :1;
		bool b_9 :1;
		bool b_10 :1;
		bool b_11 :1;
		bool b_12 :1;
		bool b_13 :1;
		bool b_14 :1;
		bool b_15 :1;
		bool b_16 :1;
		bool b_17 :1;
		bool b_18 :1;
		bool b_19 :1;
		bool b_20 :1;
		bool b_21 :1;
		bool b_22 :1;
		bool b_23 :1;
		bool b_24 :1;
		bool b_25 :1;
		bool b_26 :1;
		bool b_27 :1;
		bool b_28 :1;
		bool b_29 :1;
		bool b_30 :1;
		bool b_31 :1;
		bool b_32 :1;
		bool b_33 :1;
		bool b_34 :1;
		bool b_35 :1;
		bool b_36 :1;
		bool b_37 :1;
		bool b_38 :1;
		bool b_39 :1;
		bool b_40 :1;
		bool b_41 :1;
		bool b_42 :1;
		bool b_43 :1;
		bool b_44 :1;
		bool b_45 :1;
		bool b_46 :1;
		bool b_47 :1;
		bool b_48 :1;
		bool b_49 :1;
		bool b_50 :1;
		bool b_51 :1;
		bool b_52 :1;
		bool b_53 :1;
		bool b_54 :1;
		bool b_55 :1;
		bool b_56 :1;
		bool b_57 :1;
		bool b_58 :1;
		bool b_59 :1;
		bool b_60 :1;
		bool b_61 :1;
		bool b_62 :1;
		bool b_63 :1;
	} b;
	uint8_t u8Mask[8];
	uint16_t u16Mask[4];
	uint32_t u32Mask[2];
	uint64_t raw;

}Byte64BitMask;
#endif

#ifndef ONE_BYTE32_BIT_MASK
#define ONE_BYTE32_BIT_MASK
typedef union _Byte32BitMask
{
	struct {
		bool b_0 :1;
		bool b_1 :1;
		bool b_2 :1;
		bool b_3 :1;
		bool b_4 :1;
		bool b_5 :1;
		bool b_6 :1;
		bool b_7 :1;
		bool b_8 :1;
		bool b_9 :1;
		bool b_10 :1;
		bool b_11 :1;
		bool b_12 :1;
		bool b_13 :1;
		bool b_14 :1;
		bool b_15 :1;
		bool b_16 :1;
		bool b_17 :1;
		bool b_18 :1;
		bool b_19 :1;
		bool b_20 :1;
		bool b_21 :1;
		bool b_22 :1;
		bool b_23 :1;
		bool b_24 :1;
		bool b_25 :1;
		bool b_26 :1;
		bool b_27 :1;
		bool b_28 :1;
		bool b_29 :1;
		bool b_30 :1;
		bool b_31 :1;
	} b;
	uint8_t u8Mask[4];
	uint16_t u16Mask[2];
	uint32_t raw;
	float fraw;
}Byte32BitMask;
#endif

#ifndef ONE_BYTE16_BIT_MASK
#define ONE_BYTE16_BIT_MASK
typedef union _Byte16BitMask
{
	struct {
		bool b_0 :1;
		bool b_1 :1;
		bool b_2 :1;
		bool b_3 :1;
		bool b_4 :1;
		bool b_5 :1;
		bool b_6 :1;
		bool b_7 :1;
		bool b_8 :1;
		bool b_9 :1;
		bool b_10 :1;
		bool b_11 :1;
		bool b_12 :1;
		bool b_13 :1;
		bool b_14 :1;
		bool b_15 :1;
	} b;
	uint8_t u8Mask[2];
	uint16_t raw;
}Byte16BitMask;
#endif

#ifndef ONE_BYTE8_BIT_MASK
#define ONE_BYTE8_BIT_MASK
typedef union _Byte8BitMask
{
	struct {
		bool b_0 :1;
		bool b_1 :1;
		bool b_2 :1;
		bool b_3 :1;
		bool b_4 :1;
		bool b_5 :1;
		bool b_6 :1;
		bool b_7 :1;
	} b;
	uint8_t raw;
}Byte8BitMask;
#endif

#ifndef FLOAT_32_BIT_MASK
#define FLOAT_32_BIT_MASK
typedef union _Float32BitMask
{
	struct {
		bool b_0 :1;
		bool b_1 :1;
		bool b_2 :1;
		bool b_3 :1;
		bool b_4 :1;
		bool b_5 :1;
		bool b_6 :1;
		bool b_7 :1;
		bool b_8 :1;
		bool b_9 :1;
		bool b_10 :1;
		bool b_11 :1;
		bool b_12 :1;
		bool b_13 :1;
		bool b_14 :1;
		bool b_15 :1;
		bool b_16 :1;
		bool b_17 :1;
		bool b_18 :1;
		bool b_19 :1;
		bool b_20 :1;
		bool b_21 :1;
		bool b_22 :1;
		bool b_23 :1;
		bool b_24 :1;
		bool b_25 :1;
		bool b_26 :1;
		bool b_27 :1;
		bool b_28 :1;
		bool b_29 :1;
		bool b_30 :1;
		bool b_31 :1;
	} b;
	uint8_t u8Mask[4];
	uint16_t u16Mask[2];
	uint32_t raw;
	float fraw;
}Float32BitMask;
#endif

#endif //__TYPDEFS_H_