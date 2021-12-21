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
// File name: regNo.h
// function description: reg No. for had and cpu
//
// ****************************************************************************

#ifndef __CKCORE_DEBUGGER_SERVER_REGNO_H__
#define __CKCORE_DEBUGGER_SERVER_REGNO_H__

#include "dataType.h"

enum csky_regnum
{
  CSKY_R0_REGNUM = 0,     /* general regiters.  */
  CSKY_R15_REGNUM = 15,
  CSKY_PC_REGNUM = 72,    /* pc.  */
  CSKY_HI_REGNUM = 20,    /* hi.  */
  CSKY_LO_REGNUM = 21,    /* lo.  */
  CSKY_CR0_REGNUM = 89,   /* control registers.  */
  CSKY_VBR_REGNUM = CSKY_CR0_REGNUM  + 1,    /* vbr.  */
  CSKY_EPSR_REGNUM = CSKY_CR0_REGNUM + 2,    /* epsr.  */
  CSKY_FPSR_REGNUM = CSKY_CR0_REGNUM + 3,    /* fpsr.  */
  CSKY_EPC_REGNUM = CSKY_CR0_REGNUM  + 4,    /* epc.  */
  CSKY_FPC_REGNUM = CSKY_CR0_REGNUM  + 5,    /* fpc.  */
  CSKY_FR0_REGNUMV2 = 40,   /* float register 0.  */
  CSKY_VCR0_REGNUM = 121,
  CSKY_MMU_REGNUM = 128,
  CSKY_PROFCR_REGNUM = 140, /* Profiling only in ABIV2.  */
  CSKY_PROFGR_REGNUM = 144,
  CSKY_NUM_REGS = 253,
  CSKY_FP_REGNUM = 8,

  /* ABIV2 register coding.  */
  CSKYV2_VR0_REGNUM = 56,   /* vector register 0.  */

  /* m32r calling convention.  */
  CSKYV2_SP_REGNUM = CSKY_R0_REGNUM + 14,
  CSKYV2_RET_REGNUM = CSKY_R0_REGNUM,

  /* TODO : other special register names.  */
  /* When call funtion in GDB.  */
  CSKYV2_ABI_A0_REGNUM = 0,
  CSKYV2_ABI_LAST_ARG_REGNUM = 3,

  /* ABIV1 register coding.  */
  CSKYV1_VR0_REGNUM = 24,
  CSKYV1_SP_REGNUM = CSKY_R0_REGNUM,
  CSKYV1_RET_REGNUM = CSKY_R0_REGNUM + 2,   /* R2.  */
  /* TODO : other special register names.  */
  /* When call funtion in GDB.  */
  CSKYV1_ABI_A0_REGNUM = 2,
  CSKYV1_ABI_LAST_ARG_REGNUM = 7,

  CSKY_LR_REGNUM  = CSKY_R15_REGNUM,   /* R15.  */
  CSKY_PSR_REGNUM = CSKY_CR0_REGNUM,

  CSKY_MAX_REGISTER_SIZE = 16   /* per byte.  */
};

/////////////////////////////////////////////////////////////
// CPU Register No:
// GR 0~15
// AR 16~31
// CR 32~63
// PC 64
// HI 79
// LO 80
// GRHi 96~111
/////////////////////////////////////////////////////////////
#define CPUREGNO_GRBASE       0      // 0 ~ 15
#define CPUREGNO_ARBASE       16     // 16 ~ 31
#define CPUREGNO_CRBASE       32     // 32 ~ 63
#define CPUREGNO_PC           64
#define CPUREGNO_HI           79
#define CPUREGNO_LO           80
#define CPUREGNO_GRBASE_hi16  96     // 96 ~ 111


//about cpuid
// common
#define CPID_CPIDVER(cpid)  (((cpid) & 0x0000000f) >> 0)     //bits 03:00

#define CPUIDVER_1         1
#define CPUIDVER_2         2
#define CPUIDVER_3         3
#define CPUIDVER_4         4
#define CPUIDVER_5         5


//--------------------------------------------------------------------------
// CPID VERSION 1
#define CPID_FAMILY(cpid)   (((cpid) & 0xf0000000) >> 28)     //bits 31:28
#define CPID_MODEL(cpid)    (((cpid) & 0x0f000000) >> 24)     //bits 27:24
#define CPID_ICACHE(cpid)   (((cpid) & 0x00f00000) >> 20)     //bits 23:20
#define CPID_DCACHE(cpid)   (((cpid) & 0x000f0000) >> 16)     //bits 19:16
#define CPID_FOUNDRY(cpid)  (((cpid) & 0x0000f000) >> 12)     //bits 15:12
#define CPID_ISPM(cpid)     (((cpid) & 0x00000800) >> 8)     //bits 11:11
#define CPID_DSPM(cpid)     (((cpid) & 0x00000400) >> 8)     //bits 10:10
#define CPID_PROCESS(cpid)  (((cpid) & 0x00000300) >> 8)     //bits 09:08
#define CPID_REVISION(cpid) (((cpid) & 0x000000f0) >> 4)     //bits 07:04

// In CPIDv1, when FAMILY >= 4, CPU is CK6xx series
// These two macro definitions are only valid in CPIDv1
#define FAMILY_5XX        0
#define FAMILY_6XX        4

#define REVERSION_0       0
#define REVERSION_1       1
#define REVERSION_2       2

//for ck802, cpid may has two registers:
//	one is normal value,  the other is sepecial value
//	sepcial values are the followings:
#define	SPECIAL_VAL_0 0
#define	SPECIAL_VAL_1 0x02025a60
#define	SPECIAL_VAL_2 0x00ca52a9
#define SPECIAL_VAL_3 0x55aa00ff
#define IS_SPECIAL_VALUE(cpid)	((cpid == SPECIAL_VAL_0)||(cpid == SPECIAL_VAL_1)||(cpid == SPECIAL_VAL_2)||(cpid == SPECIAL_VAL_3))

#define PROCESS_WITH_E(cpid)   (CPID_MODEL(cpid) & 0x01)
#define PROCESS_WITH_S(cpid)   (CPID_MODEL(cpid) & 0x02)
#define PROCESS_WITH_M(cpid)   (CPID_MODEL(cpid) & 0x08)
#define PROCESS_WITH_2(cpid)   (CPID_MODEL(cpid) & 0x04)


//--------------------------------------------------------------------------
// CPID VERSION 2
#define CPID_FAMILY_V2(cpid)   (((cpid) & 0xf0000000) >> 28)    //bits 31:28
#define CPID_MODEL_V2(cpid)    (((cpid) & 0x0fff0000) >> 16)    //bits 27:16
#define CPID_FOUNDRY_V2(cpid)  (((cpid) & 0x0000f000) >> 12)    //bits 15:12
#define CPID_PROCESS_V2(cpid)  (((cpid) & 0x00000f00) >> 8)     //bits 11:08
#define CPID_REVISION_V2(cpid) (((cpid) & 0x000000f0) >> 4)     //bits 07:04
#define PROCESS_WITH_F_V2(cpid)	(((cpid) & 0x00100000) >> 20)     //bit 20
#define CPIDv2_FAMILY_6XX	1
//--------------------------------------------------------------------------
// CPID VERSOIN 3
// index 0
#define CPID_INDEX_V3(cpid)			(((cpid) & 0xf0000000) >> 28)     //bits 31:28
#define CPID_ARCH_V3(cpid)			(((cpid) & 0x0c000000) >> 26)     //bits 27:26
#define CPID_FAMILY_V3(cpid)		(((cpid) & 0x03c00000) >> 22)     //bits 25:22
#define CPID_CLASS_V3(cpid)			(((cpid) & 0x003c0000) >> 18)     //bits 21:18
#define CPID_MODEL_V3(cpid)			(((cpid) & 0x0003ff00) >> 8)      //bits 17:8
#define CPID_REVER_V3(cpid)			(((cpid) & 0x000000f0) >> 4)      //bits 7:4
#define CPID_VER_V3(cpid)			(((cpid) & 0x0000000f) >> 0)      //bits 3:0

// index 1
#define CPID_BUS_V3(cpid)      (((cpid) & 0x0f000000) >> 24)     //bits 27:24
#define CPID_COPRO_V3(cpid)    (((cpid) & 0x0000ffff) >> 0)      //bits 15:0

// index 2
#define CPID_FOUNDRY_V3(cpid)  (((cpid) & 0x0f000000) >> 24)     //bits 27:24
#define CPID_PROCESS_V3(cpid)  (((cpid) & 0x00f00000) >> 20)     //bits 23:20
#define CPID_SIGNOFF_Y_V3(cpid) \
          (((((cpid) & 0x000000f0) >> 4) * 100) + (((cpid) & 0x0000000f)))
#define CPID_SIGNOFF_M_V3(cpid) (((cpid) & 0x00000f00) >> 8)     //bits 11:8


// index 3
#define CPID_DBUSIF_V3(cpid)   (((cpid) & 0x0c000000) >> 26)     //bits 27:26
#define CPID_IBUSIF_V3(cpid)   (((cpid) & 0x03000000) >> 24)     //bits 25:24
#define CPID_DSRAM_V3(cpid)    (((cpid) & 0x0000f000) >> 12)     //bits 15:12
#define CPID_ISRAM_V3(cpid)    (((cpid) & 0x00000f00) >> 8)      //bits 11:8
#define CPID_DCACHE_V3(cpid)   (((cpid) & 0x000000f0) >> 4)      //bits 7:4
#define CPID_ICACHE_V3(cpid)   (((cpid) & 0x0000000f) >> 0)      //bits 3:0

#define PROCESS_WITH_F_V3(cpid)	((cpid & 0x00000400) >> 10)		 //bit 10
#define PROCESS_WITH_M_V3(cpid)	((cpid & 0x00001000) >> 9)		 //bit 9
#define CPID_V3_IS_CK810(cpid)	((cpid & 0x00040000) >> 18)		 //bit 18

// index 4
#define CPID_L2CACHE_V3(cpid)		(((cpid) & 0x0000000f) >> 0)	  //bits 3:0
#define CPID_L2CACHE_ECC_V3(cpid)	(((cpid) & 0x00000010) >> 4)	  //bits 4:4
#define CPID_ROAD_GROUP(cpid)       (((cpid) & 0xf00) >> 8)           //bits 11:8

// index 5
#define CPID_CORE_COUNT(cpid)		((((cpid) & 0x0000000f) >> 0) + 1)	  //bits 3:0
#define CPID_DEVICE_SLAVE_IF(cpid)	(((cpid) & 0x00000010) >> 0)	  //bits 4:4

// CPID VERSOIN 4
#define CPID_CPIDVER_V4(cpid)  (((cpid) & 0x00000007) >> 0)           //bits 2:0
// index 0
#define CPID_INDEX_V4(cpid)			(((cpid) & 0xf0000000) >> 28)     //bits 31:28
#define CPID_ARCH_V4(cpid)			(((cpid) & 0x0c000000) >> 26)     //bits 27:26
#define CPID_FAMILY_V4(cpid)		(((cpid) & 0x03c00000) >> 22)     //bits 25:22
#define CPID_CLASS_V4(cpid)			(((cpid) & 0x003c0000) >> 18)     //bits 21:18
#define CPID_MODEL_V4(cpid)			(((cpid) & 0x0003ff00) >> 8)      //bits 17:8
#define CPID_ISA_REVERSION_V4(cpid) (((cpid) & 0x000000f8) >> 3)      //bits 7:3
#define CPID_VER_V4(cpid)			(((cpid) & 0x00000007) >> 0)      //bits 2:0

//index 2'
#define CPID_DCACHE_MCU_V4(cpid)          (((cpid) & 0x00000e00) >> 9)      //bits 11:9
#define CPID_ICACHE_MCU_V4(cpid)          (((cpid) & 0x000001c0) >> 6)      //bits 8:6
#define CPID_MGUzone_NUM_MCU_V4(cpid)     (((cpid) & 0x00000038) >> 3)      //bits 5:3
#define CPID_MGUzone_SIZE_MCU_V4(cpid)    (((cpid) & 0x00000007) >> 0)      //bits 2:0

//index 3
#define CPID_DCACHE_AP_V4(cpid)           (((cpid) & 0x000000f0) >> 4)      //bits 7:4
#define CPID_ICACHE_AP_V4(cpid)           (((cpid) & 0x0000000f) >> 0)      //bits 3:0

//index 4
#define CPID_L2CACHE_AP_V4(cpid)          (((cpid) & 0x0000000f) >> 0)      //bits 3:0
#define CPID_L2CACHE_ECC_AP_V5(cpid)      (((cpid) & 0x00000030) >> 4)      //bits 5:4
#define CPID_L2CACHE_LNE_SIZE_AP_V5(cpid) (((cpid) & 0x000000c0) >> 6)      //bits 7:6
#define CPID_L2CACHE_WAY_INFO_V5(cpid)    (((cpid) & 0x00000f00) >> 8)      //bits 11:8
#define CPID_DCACHE_ECC_AP_V5(cpid)       (((cpid) & 0x00030000) >> 16)     //bits 17:16
#define CPID_DCACHE_LINE_SIZE_AP_V5(cpid) (((cpid) & 0x000c0000) >> 18)     //bits 19:18
#define CPID_DCACHE_WAY_INFO_AP_V5(cpid)  (((cpid) & 0x00300000) >> 20)     //bits 21:20
#define CPID_ICACHE_ECC_AP_V5(cpid)       (((cpid) & 0x00c00000) >> 22)     //bits 23:22
#define CPID_ICACHE_LINE_SIZE_AP_V5(cpid) (((cpid) & 0x03000000) >> 24)     //bits 25:24
#define CPID_ICACHE_WAY_INFO_AP_V5(cpid)  (((cpid) & 0x0c000030) >> 26)     //bits 27:26

//index 5
#define CPID_MULTICORE_COUNTS_AP_V4(cpid) (((cpid) & 0x00000007) + 1)       //bits 2:0 + 1

//index 6
#define CPID_TLB_ITEMS_AP_V4(cpid)        (((cpid) & 0x00000f00) >> 8)      //bits 11:8
#define CPID_MGUZone_SIZE_AP_V4(cpid)     (((cpid) & 0x000000f0) >> 4)      //bits 7:4
#define CPID_MGUZone_NUM_AP_V4(cpid)      (((cpid) & 0x0000000f) >> 0)      //bits 3:0

// CPID VERSOIN 5
#define CPID_CPIDVER_V5(cpid)  (((cpid) & 0x00000007) >> 0)           //bits 2:0
// index 0
#define CPID_INDEX_V5(cpid)               CPID_INDEX_V4(cpid)
#define CPID_VER_V5(cpid)                 CPID_VER_V4(cpid)


// Is CK805
#define CPID_V3_IS_CK805(cpid) (((cpid) & 0xfffc000f) == 0x04a40003)        // for CPID_v3 : CK805
#define CPID_V4_IS_X805(cpid)  (((cpid) & 0xfffc0007) == 0x04800004)        // for CPID_v4 : I805

// Is CK804
#define CPID_V3_IS_CK804(cpid) (((cpid) & 0xfffc000f) == 0x04a00003)        // for CPID_v3 : CK804
#define CPID_V4_IS_X804(cpid)  (((cpid) & 0xfffc0007) == 0x040c0003)        // for CPID_v4 : E804

// Is CK860
#define CPID_V3_IS_CK860(cpid) (((cpid) & 0xfffc000f) == 0x049c0003)        // for CPID_v3 : CK860
#define CPID_V4_IS_X860(cpid)  (((cpid) & 0xfffc0007) == 0x05080004)        // for CPID_v4 : C860

// Is CK803S
#define CPID_V3_IS_CK803S(cpid)  (((cpid) & 0xfffc000f) == 0x04900003)      // for CPID_v3 : CK803S

// Is CK803
#define CPID_V3_IS_CK803(cpid)  (((cpid) & 0xfffc000f) == 0x04800003)       // for CPID_v3 : CK803
#define CPID_V4_IS_X803(cpid)   ((((cpid) & 0xfffc0007) == 0x04080004) \
                                 || (((cpid) & 0xfffc0007) == 0x04b40004) ) // for CPID_v4 : E803, S803

// In CPIDv3, CK802 have only one CPID, no index1, 2, 3
#define CPID_V3_IS_CK802(cpid)  (((cpid) & 0xfffc000f) == 0x04880003)       // for CPID_v3 : CK802
#define CPID_V4_IS_X802(cpid)   ((((cpid) & 0xfffc0007) == 0x04040004) \
                                 || (((cpid) & 0xfffc0007) == 0x04b00004) ) // for CPID_v4 : E802, S802

// In CPIDv3, CK801 have only one CPID, no index1, 2, 3
#define CPID_V3_IS_CK801(cpid)  (((cpid) & 0xfffc000f) == 0x04980003)       // for CPID_v3 : CK801
#define CPID_V4_IS_X801(CPID)   (((cpid) & 0xfffc0007) == 0x04000004)       // for CPID_v4 : E801

// get hardware info from cpuid1'
#define GET_CPID_HWINFO(cpid)  ((cpid) & 0x3fffffff)
// thread num to core num
#define THREAD_NUM_TO_MULTICORE_NUM(thread) ((thread) - 1)
// core num to thread num
#define MULTICORE_NUM_TO_THREAD_NUM(core) ((core) + 1)


/*******************************************************************************

  The followings are HAD registers defination.

********************************************************************************/

// for hacr width
#define ICE_CSR_HACR_WIDTH_BIT 12
typedef enum
{
	CK_HACR_8  = 8,
	CK_HACR_16 = 16
} CK_HACR_WIDTH;


/////////////////////////////////////////////////////////////
//For Had Command Register
//For Had Command Register, 10 bits
#define EXBIT       0x20   // EX bit, (1<<5)
#define GOBIT       0x40   // GO bit, (1<<6)
#define HRBIT       0x80   // R/W bit

#define TPEND       0x400  // TPEND bit, (1<<10)
#define FDB         0x80   // FDB bit  , (1<<7)
#define FFY         0x100  // FFY bit  , (1<<8)

#define CSR_R       (TPEND | FDB)
#define CSR_W       (TPEND | FDB | FFY)

#define CK_UNSTALL_MASK_V1	0xffff5fff //the mask of hcr for ck cpu exit debug mode had v1
#define CK_UNSTALL_MASK_V2	0xffdf5fff //the mask of hcr for ck cpu exit debug mode had v2&v3

/////////////////////////////////////////////////////////////
// for hsr
#define DDCBIT      0x100000 // (1<<20)
#define DRBIT       0x8000   // (1<<15)
#define ADR         0x200000 // (1<<21)
#define IS_LOW_POWER(hsr) ((hsr) & 0x1)

// for had BANK SEL
#define BANK_0 0
#define BANK_1 1 //for select bank reg
#define BANK_2 2
#define BANK_3 3

// for HACR 16 EXTENTION
#define BANK1_E16_SEL  (BANK_1 << 5)
#define BANK2_E16_SEL  (BANK_2 << 5)
#define BANK3_E16_SEL  (BANK_3 << 5)

#define EXTEN_16_HACR_WRITE(select)       ((((select) & 0x1f) << 8) | (((select) & 0xE0) >> 1))
#define EXTEN_16_HACR_READ(select)        ((((select) & 0x1f) << 8) | (((select) & 0xE0) >> 1) | (1 << 15))
#define EXTEN_16_HACR_GOBIT(select)       ((((select) & 0x1f) << 8) | (((select) & 0xE0) >> 1) | (1 << 14))
#define EXTEN_16_HACR_GOBIT_EXBIT(select) ((((select) & 0x1f) << 8) | (((select) & 0xE0) >> 1) | (0x3 << 13))

#define HW_ENABLE_C	0x00400000 //enable hw_bkpt_c
#define HW_ENABLE_D	0x00800000 //enable hw_bkpt_d
#define HW_ENABLE_E	0x01000000 //enable hw_bkpt_e
#define HW_ENABLE_F	0x02000000 //enable hw_bkpt_f
#define HW_ENABLE_G	0x04000000 //enable hw_bkpt_g
#define HW_ENABLE_H	0x08000000 //enable hw_bkpt_h
#define HW_ENABLE_I	0x10000000 //enable hw_bkpt_i

#define HW_DISABLE_C	0xffbfffff //disable hw_bkpt_c
#define HW_DISABLE_D	0xff7fffff //disable hw_bkpt_d
#define HW_DISABLE_E	0xfeffffff //disable hw_bkpt_e
#define HW_DISABLE_F	0xfdffffff //disable hw_bkpt_f
#define HW_DISABLE_G	0xfbffffff //disable hw_bkpt_g
#define HW_DISABLE_H	0xf7ffffff //disable hw_bkpt_h
#define HW_DISABLE_I	0xefffffff //disable hw_bkpt_i

//define for HSR
#define HSR_BIT_TO      0x20
#define HSR_BIT_SWO     0x40
#define HSR_BIT_MBO     0x80
#define HSR_BIT_DRO     0x100
#define HSR_BIT_HDRO    0x200
#define HSR_BIT_ADRO    0x400
#define HSR_BIT_EBRO    0x800
#define HSR_BIT_PRO     0x10000

typedef enum {
	HID = 0x02,         // Had ID ???  ?? bits, 'b00010
	HTCR = 0x03,        // Had Trace Counter, 16 bits, 'b00011
	MBCA = 0x04,        // Memory Breakpoint Counter A, 16 bits, 'b00100
	MBCB = 0x05,        // Memory Breakpoint Counter B, 16 bits, 'b00101
	PCFIFO = 0x06,      // PC Fifo for newest 8 jump instructions, 32 bits, depth 8
	BABA = 0x07,        // Break Address Register A
	BABB = 0x08,        // Break Address Register B
	BAMA = 0x09,        // Break Address Mask Register A
	BAMB = 0x0A,        // Break Address Mask Register B
	CPUSCR = 0x0B,      // CPU Scan Chain, 128 bits, 'b01011
	BYPASS = 0x0C,      // Bypass Register
	HCR = 0x0D,         // Had Control Register, 32 bits, 'b01101
	HSR = 0x0E,         // Had Status Register, 16 bits, 'b01110
	HSR2 = 0x0F,        // had status register 32bits, 'b01111,
//	SRAMMODE = 0x10,    // SRAM Mode Register,
	SCRWBBR = 0x11,     // Write Back Bus Register 32 bits, V2 or newer only
	SCRPSR  = 0x12,     // Processor Status Register 32 bits, V2 or newer only
	SCRPC   = 0x13,     // Program Counter 32 bits, V2 or newer only
	SCRIR   = 0x14,     // Instruction Register 32 bits, V2 or newer only
	SCRCSR  = 0x15,     // Control State Register 32 bits, V2 or newer only
	DCCDATA = 0x16,		// Debug Communicate Channel Data register
	ITMDATA = 0x17,		// Lite Debug Communicate Channel Data register
	DDCADDR = 0x18,     // DDC Address Register
	DDCDATA = 0x19,     // DDC Data Register
	// for multicore
	CPUSEL  = 0x1A,		// CPU SELECT
	CPUST   = 0x1B,		// CPU STATE
	BSEL    = 0x1e,	    // BANK select Register
	HCDI    = 0x1f,     // HAD CDI
	HACR    = 0x100     // Special for HACR
}HADREG;

typedef enum{
	BABC = 0x20,		//Break Address Register C
	BAMC = 0x21,		//Break Address Mask Register C
	BABD = 0x22,		//Break Address Register D
	BAMD = 0x23,		//Break Address Mask Register D
	BABE = 0x24,		//Break Address Register E
	BAME = 0x25,		//Break Address Mask Register E
	BABF = 0x26,		//Break Address Register F
	BAMF = 0x27,		//Break Address Mask Register F
	BABG = 0x28,		//Break Address Register G
	BAMG = 0x29,		//Break Address Mask Register G
	BABH = 0x2a,		//Break Address Register H
	BAMH = 0x2b,		//Break Address Mask Register H
	BABI = 0x2c,		//Break Address Register I
	BAMI = 0x2d,		//Break Address Mask Register I
	/* Reserve ... */
	DACSR = 0x38,       //
	DATR  = 0x39,
	DARWR = 0x3a,
	MBIR  = 0x3b,
	MBEE  = 0x3c,
	MBSE  = 0x3d,
}HADREG_B1;

typedef enum{
	EDCR        = 0x40,
	DPCR        = 0x41,
	EVENT_OUTEN = 0x42,
	EVENT_INEN  = 0x43,
	DBG_FIFO    = 0x44,
	PIPE_FIFO   = 0x45,
	PIPE_SEL    = 0x46,

}HADREG_B2;

typedef enum{
	DBG_FIFO2   = 0x60,
	RESET_STATUS = 0x61,
}HADREG_B3;

typedef enum{
	HCDI_8  = 0x1f,
	HCDI_16 = 0xff
}HCDI_NUMBER;

// for EVENT_CTRL type
#define MP_EVENT_OUT_ALL   0x3  // 11B
#define MP_EVENT_OUT_EXIT  0x2  // 10B
#define MP_EVENT_OUT_IN    0x1  // 01B
#define MP_EVENT_OUT_NULL  0x0  // 00B

#define MP_EVENT_IN_ALL    0x3  // 11B
#define MP_EVENT_IN_EXIT   0x2  // 10B
#define MP_EVENT_IN_IN     0x1  // 01B
#define MP_EVENT_IN_NULL   0x0  // 00B

#define _HAD_ID_VERSION(id)   (id & 0xf)
#define _HAD_BKPT_NUM_V2(id)  ((id >> 12) & 0xf) // id_ver_1
#define _HAD_BKPT_NUM_V1(id)  (-1)
#define HAD_ID_V1 0
#define HAD_ID_V2 1

#define _HAD_VERSION(id)     ((id >> 4) & 0xf)
#define HAD_V1               0
#define HAD_V2               1
#define HAD_V3               2
#define HAD_V4               3
#define HAD_V5               4
#define HAD_V6               5
#define HAD_V7               6

#define HAD_REVERSION(id)    ((id >> 8) & 0xf)

#define _ARCH_VERSION(id)     ((id >> 26) & 0x3)
#define ARCH_V1              0
#define ARCH_V2              1

#define _HAD_ID_RESERVED_V2(id)  ((id >> 16) & 0x03ff)  //for id_ver_0
#define _HAD_ID_RESERVED_V1(id)	 ((id >> 12) & 0x03fff) //for id_ver_1

#define HAD_HSR_SRST(hsr)  ((hsr>>11) &0x1)//for SRSR BIT OF HSR

//for multicore(HAD version v4)
#define IS_16_HACR(hid)          ( (hid) & (1 << 18) )
#define GETCPUCOUNT(hid)         ( ((hid)>>8)  & 0x3f )
#define GETMARK(hid)             ( ((hid)>>24) & 0x3  )
#define GETISAVER(hid)           ( ((hid)>>4)  & 0xf  )
#define GETCDITYP(hid)           ( (hid) >>28 )
#define GETIDVER(hid)            ( (hid) & 0xf )
#define HID_MARK_IS_HADTOP(hid)  ( (((hid)>>24) & 0x3) == 1  )

//for System Description
#define HAD_TOP_SD_ADDRESS           0x1C
#define HAD_TOP_SD_DATA              0x1D
#define SD_MAGIC                     0x9
#define SD_T_HEAD_VENDOR_ID          0x5b7
#define SD_ID_CPU_INFO               0x0
#define SD_GET_MAGIC(data)           (((data) >> 28) & 0xf)
#define SD_GET_VENDOR_ID(data)       ( ((data) >> 16) & 0xfff )
#define SD_GET_SD_ID(data)           ( ((data) >> 4) & 0xfff )
#define SD_GET_VERSION(data)         ( (data) & 0xf )
#define SD_GET_CONTENTS_ADDR(data)   ( ((data) & 0xfffffff0) >> 4 )
#define SD_GET_CONTENTS_EXIST(data)  ( ((data) & 0x1) == 1 )
#define SD_GET_CPU_NUM(data)         ( ((data) >> 27) & 0x1f )
#define SD_GET_CORE_ID(data)         ( ((data) >> 23) & 0xf )
#define SD_GET_GROUP(data)           ( ((data) >> 19) & 0xf )
#define SD_GET_CLUSTER(data)         ( ((data) >> 15) & 0xf )
#define SD_GET_POWER_DOMAIN(data)    ( ((data) >> 10) & 0x1f )
#define SD_GET_TEE(data)             ( ((data) >> 9) & 0x1 )
#define SD_GET_JTAG_ENABLE(data)     ( ((data) >> 8) & 0x1 )

inline static int HAD_ID_HACR_LENGTH(U32 hid)
{
  return (IS_16_HACR(hid) ? CK_HACR_16 : CK_HACR_8);
}

inline static int HAD_ID_VERSION (U32 hid)
{
	return _HAD_ID_VERSION(hid);
}

inline static int HAD_VERSION (U32 hid)
{
    if (_HAD_VERSION(hid) == HAD_V1) {
	// [3:0]   HAD_ID_VER = 2
        return HAD_V1;
    }
    else if (_HAD_VERSION(hid) == HAD_V2) {
	// [3:0]   HAD_ID_VER = 1
        return HAD_V2;
    }
    else if (_HAD_VERSION(hid) == HAD_V3) {
		return HAD_V3;
    }
    else if (_HAD_VERSION(hid) == HAD_V4) {
		return HAD_V4;
    }
    else
        return HAD_V5;
}

inline static int ARCH_VERSION (U32 hid)
{
	return _ARCH_VERSION(hid);
}
inline static int BKPT_NUM (U32 hid) //get target bkpt_num
{
	return _HAD_BKPT_NUM_V2(hid);
}

typedef enum {
	BKPTA = 0x00,
	BKPTB = 0x01,
	BKPTC = 0x02,
	BKPTD = 0x03,
	BKPTE = 0x04,
	BKPTF = 0x05,
	BKPTG = 0x06,
	BKPTH = 0x07,
	BKPTI = 0x08
}BKPT;

#define CK_MAX_REG_SIZE			16 // per byte
#define CK_NEW_REG_CODE(regno)  (regno >> 14)
#define CK_NEW_REG_CP(regno)	((regno & 0x2000) >> 13)
#define CK_NEW_REG_SEL(regno)	((regno & 0x1f00) >> 8)
#define CK_NEW_REG_NUM(regno)	(regno & 0xff)

#define CK_NEW_REG_MMU(regno)	((regno & 0x7f00) == 0x4f00)
#define CK_NEW_REG_PROF(regno)	((regno & 0x7f00) == 0x6000)
#define CK_NEW_REG_VR(regno)	((regno & 0x7f00) == 0x4200)

#define CK_NEW_REG_CTRBANK2(regno)	 ((regno & 0x7f00) == 0x4200)
#define CK_NEW_REG_CTRBANK(regno)    ((regno & 0x7000) == 0x4000)
#define CK_NEW_REG_CTRBANKNUM(regno) ((regno & 0xf00) >> 8)

#define CK_NEW_REG_CTRBANK_EXTEN(regno)        ((regno & 0x7000) == 0x5000)
#define CK_NEW_REG_CTRBANKNUM_EXTEN(regno)     ((regno & 0xfff) / 32)
#define CK_NEW_REG_CTRBANK_REGNUM_EXTEN(regno) ((regno & 0xfff) % 32)

#define CK_CPU_HAVE_VECTOR(cpid)  ((CPID_MODEL_V3(cpid) & 0x40) \
                                   || ((CPID_VER_V4(cpid) == CPUIDVER_4) \
                                       && (CPID_MODEL_V4(cpid) & 0x8)) )
#define CK_CPU_HAVE_FLOAT(cpid)   ((CPID_MODEL_V3(cpid) & 0x4) \
                                   || ((CPID_VER_V4(cpid) == CPUIDVER_4) \
                                       && (CPID_MODEL_V4(cpid) & 0x1)) )
#define CK_CPU_HAVE_PROFILING(cpid) ((cpid & 0xffff) & 0x1)

#define IS_32_BITS_INSN(insn)  (((step_insn) & 0xc000) == 0xc000)
#define IS_32_BITS_LRW(insn)  (((insn) >> 10) >= 54 && ((insn) >> 10) <= 55)
#define IS_16_BITS_LRW(insn)  (((insn) >> 10) >= 32 && ((insn) >> 10) <= 47)
#define IS_32_BITS_LD_OR_ST(insn) (((insn) & 0xffe0)== 0xea80)
#define IS_16_BITS_LD_OR_ST(insn) ((((step_insn) & 0xec00) == 0) && ((step_insn) != 0))

#define IS_BPUSH16_INSN(insn) ((((insn) >> 10) == 5) && (((insn) & 0xe0) == 0xe0))
#define IS_BPOP16_INSN(insn)  ((((insn) >> 10) == 5) && (((insn) & 0xa0) == 0xa0))

#endif // __CKCORE_DEBUGGER_SERVER_REGNO_H__
