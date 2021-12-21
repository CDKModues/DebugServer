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
// File name: rv_gdb_regs.h
// function description: define reg nums for RISCV regs .
//
// ****************************************************************************

#ifndef __RISCV__GDB_REGS_H__
#define __RISCV__GDB_REGS_H__

#define CSR_TSELECT   0x7a0
#define CSR_TDATA1    0x7a1
#define CSR_TDATA2    0x7a2
#define CSR_DCSR      0x7b0
#define CSR_DPC       0x7b1
#define CSR_DSCRATCH  0x7b2

#define CSR_MSTATUS   0x300
#define CSR_MISA      0x301
#define CSR_MIE       0x304
#define CSR_MTVEC     0x305

#define CSR_MSCRATCH  0x340
#define CSR_MEPC      0x341
#define CSR_MCAUSE    0x342
#define CSR_MTVAL     0x343
#define CSR_MIP       0x344

#define CSR_MCYCLE    0xb00
#define CSR_MCYCLEH   0xb80

#define CSR_MARCHID   0xf12
#define CSR_MHARTID   0xf14

//triggers
#define RISCV_CSR_TSELECT_REGNUM   (0x7a0 + 65)
#define RISCV_CSR_TDATA1_REGNUM    (0x7a1 + 65)
#define RISCV_CSR_MCONTROL_REGNUM  (0x7a1 + 65)
#define RISCV_CSR_ICOUNT_REGNUM    (0x7a1 + 65)
#define RISCV_CSR_ITRIGGER_REGNUM  (0x7a1 + 65)
#define RISCV_CSR_ETRIGGER_REGNUM  (0x7a1 + 65)
#define RISCV_CSR_TDATA2_REGNUM    (0x7a2 + 65)
#define RISCV_CSR_TDATA3_REGNUM    (0x7a3 + 65)
#define RISCV_CSR_TEXTRA32_REGNUM  (0x7a3 + 65)
#define RISCV_CSR_TEXTRA64_REGNUM  (0x7a3 + 65)
#define RISCV_CSR_TINFO_REGNUM     (0x7a4 + 65)
#define RISCV_CSR_TCONTROL_REGNUM  (0x7a5 + 65)
#define RISCV_CSR_MCONTEXT_REGNUM  (0x7a8 + 65)
#define RISCV_CSR_SCONTEXT_REGNUM  (0x7aa + 65)

//Core debug
#define RISCV_CSR_MHARTID_REGNUM   (0xf14 + 65)
#define RISCV_CSR_DCSR_REGNUM      (0x7b0 + 65)
#define RISCV_CSR_DPC_REGNUM       (0x7b1 + 65)
#define RISCV_CSR_DSCRATCH0_REGNUM (0xfb2 + 65)
#define RISCV_CSR_DSCRATCH1_REGNUM (0xfb3 + 65)

#define RISCV_CSR_FFLAGS_REGNUM 66
#define RISCV_CSR_FRM_REGNUM    67
#define RISCV_CSR_FCSR_REGNUM   68

/* Some csr reg added by CSKY. */
#define RISCV_CSR_MXSTATUS_REGNUM  (0x7c0 + 65)
#define RISCV_CSR_MHCR_REGNUM      (0x7c1 + 65)
#define RISCV_CSR_MCOR_REGNUM      (0x7c2 + 65)
#define RISCV_CSR_MCCR2_REGNUM     (0x7c3 + 65)
#define RISCV_CSR_MCER2_REGNUM     (0x7c4 + 65)
#define RISCV_CSR_MHINT_REGNUM     (0x7c5 + 65)
#define RISCV_CSR_MRMR_REGNUM      (0x7c6 + 65)
#define RISCV_CSR_MRVBR_REGNUM     (0x7c7 + 65)

#define RISCV_CSR_MCINS_REGNUM     (0x7d2 + 65)
#define RISCV_CSR_MCINDEX_REGNUM   (0x7d3 + 65)
#define RISCV_CSR_MCDATA0_REGNUM   (0x7d4 + 65)
#define RISCV_CSR_MCDATA1_REGNUM   (0x7d5 + 65)

#define RISCV_CSR_CPUID_REGNUM     (0xfc0 + 65)

#define RISCV_CSR_SXSTATUS_REGNUM  (0x5c0 + 65)
#define RISCV_CSR_SHCR_REGNUM      (0x5c1 + 65)
#define RISCV_CSR_SCER2_REGNUM     (0x5c2 + 65)

#define RISCV_CSR_SMIR_REGNUM      (0x9c0 + 65)
#define RISCV_CSR_SMLo0_REGNUM     (0x9c1 + 65)
#define RISCV_CSR_SMHI_REGNUM      (0x9c2 + 65)
#define RISCV_CSR_SMCR_REGNUM      (0x9c3 + 65)

#define RISCV_CSR_FXCR_REGNUM      (0x800 + 65)
/* end... */


/* gdb's register list is defined in riscv_gdb_reg_names gdb/riscv-tdep.c in
 * its source tree. We must interpret the numbers the same here. */
enum rv_gdb_regno {
	RV_GDB_REGNO_ZERO = 0,        /* Read-only register, always 0.  */
	RV_GDB_REGNO_RA = 1,          /* Return Address.  */
	RV_GDB_REGNO_SP = 2,          /* Stack Pointer.  */
	RV_GDB_REGNO_GP = 3,          /* Global Pointer.  */
	RV_GDB_REGNO_TP = 4,          /* Thread Pointer.  */
	RV_GDB_REGNO_T0,
	RV_GDB_REGNO_T1,
	RV_GDB_REGNO_T2,
	RV_GDB_REGNO_S0 = 8,
	RV_GDB_REGNO_FP = 8,          /* Frame Pointer.  */
	RV_GDB_REGNO_S1,
	RV_GDB_REGNO_A0 = 10,         /* First argument.  */
	RV_GDB_REGNO_A1 = 11,         /* Second argument.  */
	RV_GDB_REGNO_A2,
	RV_GDB_REGNO_A3,
	RV_GDB_REGNO_A4,
	RV_GDB_REGNO_A5,
	RV_GDB_REGNO_A6,
	RV_GDB_REGNO_A7,
	RV_GDB_REGNO_S2,
	RV_GDB_REGNO_S3,
	RV_GDB_REGNO_S4,
	RV_GDB_REGNO_S5,
	RV_GDB_REGNO_S6,
	RV_GDB_REGNO_S7,
	RV_GDB_REGNO_S8,
	RV_GDB_REGNO_S9,
	RV_GDB_REGNO_S10,
	RV_GDB_REGNO_S11,
	RV_GDB_REGNO_T3,
	RV_GDB_REGNO_T4,
	RV_GDB_REGNO_T5,
	RV_GDB_REGNO_T6,
	RV_GDB_REGNO_XPR31 = RV_GDB_REGNO_T6,

	RV_GDB_REGNO_PC = 32,
	RV_GDB_REGNO_FPR0 = 33,
	RV_GDB_REGNO_FT0 = RV_GDB_REGNO_FPR0,
	RV_GDB_REGNO_FT1,
	RV_GDB_REGNO_FT2,
	RV_GDB_REGNO_FT3,
	RV_GDB_REGNO_FT4,
	RV_GDB_REGNO_FT5,
	RV_GDB_REGNO_FT6,
	RV_GDB_REGNO_FT7,
	RV_GDB_REGNO_FS0,
	RV_GDB_REGNO_FS1,
	RV_GDB_REGNO_FA0,
	RV_GDB_REGNO_FA1,
	RV_GDB_REGNO_FA2,
	RV_GDB_REGNO_FA3,
	RV_GDB_REGNO_FA4,
	RV_GDB_REGNO_FA5,
	RV_GDB_REGNO_FA6,
	RV_GDB_REGNO_FA7,
	RV_GDB_REGNO_FS2,
	RV_GDB_REGNO_FS3,
	RV_GDB_REGNO_FS4,
	RV_GDB_REGNO_FS5,
	RV_GDB_REGNO_FS6,
	RV_GDB_REGNO_FS7,
	RV_GDB_REGNO_FS8,
	RV_GDB_REGNO_FS9,
	RV_GDB_REGNO_FS10,
	RV_GDB_REGNO_FS11,
	RV_GDB_REGNO_FT8,
	RV_GDB_REGNO_FT9,
	RV_GDB_REGNO_FT10,
	RV_GDB_REGNO_FT11,
	RV_GDB_REGNO_FPR31 = RV_GDB_REGNO_FT11,
	RV_GDB_REGNO_CSR0 = 65,
	RV_GDB_REGNO_MSTATUS = CSR_MSTATUS + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MISA = CSR_MISA + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MIE = CSR_MIE + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MTVEC = CSR_MTVEC + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MSCRATCH = CSR_MSCRATCH + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MEPC = CSR_MEPC + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MCAUSE = CSR_MCAUSE + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MTVAL = CSR_MTVAL + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MIP = CSR_MIP + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MCYCLE = CSR_MCYCLE + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MCYCLEH = CSR_MCYCLEH + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_MARCHID = CSR_MARCHID + RV_GDB_REGNO_CSR0,
//	RV_GDB_REGNO_TSELECT = CSR_TSELECT + RV_GDB_REGNO_CSR0,
//	RV_GDB_REGNO_TDATA1 = CSR_TDATA1 + RV_GDB_REGNO_CSR0,
//	RV_GDB_REGNO_TDATA2 = CSR_TDATA2 + RV_GDB_REGNO_CSR0,
//	RV_GDB_REGNO_MISA = CSR_MISA + RV_GDB_REGNO_CSR0,
//	RV_GDB_REGNO_DPC = CSR_DPC + RV_GDB_REGNO_CSR0,
//	RV_GDB_REGNO_DCSR = CSR_DCSR + RV_GDB_REGNO_CSR0,
//	RV_GDB_REGNO_DSCRATCH = CSR_DSCRATCH + RV_GDB_REGNO_CSR0,
//	RV_GDB_REGNO_MSTATUS = CSR_MSTATUS + RV_GDB_REGNO_CSR0,
	RV_GDB_REGNO_CSR4095 = RV_GDB_REGNO_CSR0 + 4095,
	RV_GDB_REGNO_PRIV = 4161,
	RV_GDB_REGNO_COUNT
};

#endif
