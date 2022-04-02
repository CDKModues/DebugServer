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
// File name: arch.h
// function description: define the parameter about Hardware configuration
//
// ****************************************************************************


#ifndef __CKCORE_DEBUGGER_SERVER_ARCH_H__
#define __CKCORE_DEBUGGER_SERVER_ARCH_H__

#define CKCORE_DDC      1
#define CKCORE_NODDC   0

#define CKCORE_ICE      "USBICE"
#define CKCORE_ECP      "EASYJTAG"
#define CKCORE_SIM      "SIMULATOR"

#define CKCORE_BIG_ENDIAN_NEW		2	// csky new big endian for CK800s
#define CKCORE_BIG_ENDIAN			1	
#define CKCORE_LITTLE_ENDIAN		0

// define for ice idproduct
#define CKLINK_LEGENCY_PID		0xB000 // OLD ICE upto 0xB100
#define CKLINK_LOW_COST_PID		0xB002 // OLD LOST COST ICE upto 0xB110
#define CKLINK_VID			      0xC510 // ALL VID
#define CKLINK_V2_PID			    0xB200
#define CKLINK_V1_PID			    0xB100
#define CKLINK_LITE_V1_PID		0xB110
#define CKLINK_LITE_V2_PID		0xB210

/* VID define. */
#define CSKY_iVID			CKLINK_VID
/* According to the USB-IF, new vendor id is 0x32BF.  */
#define T_HEAD_iVID			0x32BF


/**
 * Litev2's transient PID, when upgrade litev2, this PID appear temporarily.
 */
#define CKLINK_LITE_V2_PID_update	0xB211

//For riscv dm spec
enum RISCV_DM_SPEC_VERSION
{
	DM_SPEC_011 = 1,
	DM_SPEC_013 = 2,
	DM_SPEC_Unknown,
};

/* T-HEAD IDCODE.  */
#define T_HEAD_JEP106 0x5b7
#define RISCV_DTM_IDCODE_VALID(idcode)     ((idcode) & 1)
#define IS_T_HEAD_JEP106(idcode)           ((((idcode) >> 1) & 0x7ff) == T_HEAD_JEP106)
#define RISCV_IDCODE_GET_MANUFID(idcode)   (((idcode) >> 1) & 0x7ff)

#endif // __CKCORE_DEBUGGER_SERVER_ARCH_H__
