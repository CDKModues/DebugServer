/*
 * Copyright (C) 2021 T-HEAD Semiconductor Co.,Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// ****************************************************************************
// File name: regType.h
// function description: reg type for had and cpu.
//
// ****************************************************************************                       

#ifndef __CKCORE_DEBUGGER_SERVER_REGTYPE_H__
#define __CKCORE_DEBUGGER_SERVER_REGTYPE_H__

typedef struct
{
    unsigned int WBBR;
    unsigned int PSR;
    unsigned int PC;
    unsigned short IR;
    unsigned short CTL;
} CTLREGS, *PCTLREGS;

typedef enum {
	HB_NONE = 0,
	HB_ALL_ALL_LS   = 0x01,   // `b00001
	HB_ALL_INST_LS  = 0x02,   // `b00010
	HB_ALL_DATA_LS  = 0x03,   // `b00011 
	HB_ALL_INST_JMP = 0x04,   // `b00100
	HB_ALL_DATA_S   = 0x05,   // `b00101
	HB_ALL_DATA_L   = 0x06,   // `b00110

	HB_USR_ALL_LS   = 0x11,   // `b10001
	HB_USR_INST_LS  = 0x12,   // `b10010
	HB_USR_DATA_LS  = 0x13,   // `b10011 
	HB_USR_INST_JMP = 0x14,   // `b10100
	HB_USR_DATA_S   = 0x15,   // `b10101
	HB_USR_DATA_L   = 0x16,   // `b10110

	HB_SUP_ALL_LS   = 0x19,   // `b11001
	HB_SUP_INST_LS  = 0x1A,   // `b11010
	HB_SUP_DATA_LS  = 0x1B,   // `b11011 
	HB_SUP_INST_JMP = 0x1C,   // `b11100
	HB_SUP_DATA_S   = 0x1D,   // `b11101
	HB_SUP_DATA_L   = 0x1E,   // `b11110
}HB_MODE;

#endif //__CKCORE_DEBUGGER_SERVER_REGTYPE_H__
