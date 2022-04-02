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
// File name: riscv-reg.h
// function description: define reg nums for RISCV regs .
//
// ****************************************************************************

#ifndef __INCLUDE_RISCV_REG_H__
#define __INCLUDE_RISCV_REG_H__

#define DECLARE_CSR(name, regno) \
	GDB_CSR_##name = regno + 65,
enum riscv_gdb_csr_regno
{
#include "riscv-opc.h"
};

#define MSTATUS_MIE (1UL << 3)
#define MSTATUS_SIE (1UL << 1)

enum riscv_gdb_gr_fr_regno
{
	GDB_GPR_x0 = 0,
	GDB_GPR_SP = 2,
	GDB_GPR_S0 = 8,
	GDB_GPR_FP = 8,
	GDB_GPR_S1 = 9,
	GDB_GPR_x31 = 31,
	GDB_REG_PC = 32,
	GDB_FR_f0 = 33,
	GDB_FR_f31 = 64,
	GDB_VR_v0 = 4162,
	GDB_VR_v31 = 4193
};
#define GDB_GPR_x1		(GDB_GPR_x0+1)
#define GDB_GPR_x2		(GDB_GPR_x0+2)
#define GDB_GPR_x3		(GDB_GPR_x0+3)
#define GDB_GPR_x4		(GDB_GPR_x0+4)
#define GDB_GPR_x5		(GDB_GPR_x0+5)
#define GDB_GPR_x6		(GDB_GPR_x0+6)
#define GDB_GPR_x7		(GDB_GPR_x0+7)
#define GDB_GPR_x8		(GDB_GPR_x0+8)
#define GDB_GPR_x9		(GDB_GPR_x0+9)
#define GDB_GPR_x10		(GDB_GPR_x0+10)
#define GDB_GPR_x11		(GDB_GPR_x0+11)
#define GDB_GPR_x12		(GDB_GPR_x0+12)
#define GDB_GPR_x13		(GDB_GPR_x0+13)
#define GDB_GPR_x14		(GDB_GPR_x0+14)
#define GDB_GPR_x15		(GDB_GPR_x0+15)
#define GDB_GPR_x16		(GDB_GPR_x0+16)
#define GDB_GPR_x17		(GDB_GPR_x0+17)
#define GDB_GPR_x18		(GDB_GPR_x0+18)
#define GDB_GPR_x19		(GDB_GPR_x0+19)
#define GDB_GPR_x20		(GDB_GPR_x0+20)
#define GDB_GPR_x21		(GDB_GPR_x0+21)
#define GDB_GPR_x22		(GDB_GPR_x0+22)
#define GDB_GPR_x23		(GDB_GPR_x0+23)
#define GDB_GPR_x24		(GDB_GPR_x0+24)
#define GDB_GPR_x25		(GDB_GPR_x0+25)
#define GDB_GPR_x26		(GDB_GPR_x0+26)
#define GDB_GPR_x27		(GDB_GPR_x0+27)
#define GDB_GPR_x28		(GDB_GPR_x0+28)
#define GDB_GPR_x29		(GDB_GPR_x0+29)
#define GDB_GPR_x30		(GDB_GPR_x0+30)
#undef DECLARE_CSR

#define DECLARE_CSR(name, regno) \
	CMD_CSR_##name = regno,
enum riscv_cmd_csr_regno
{
#include "riscv-opc.h"
};
#undef DECLARE_CSR

#define REGNO_IS_GPR(regno) (regno >= GDB_GPR_x0 && regno <= GDB_GPR_x31)
#define REGNO_IS_CSR(regno) ((regno >= 65) && (regno < 4161))
#define REGNO_IS_PRIV(regno) (regno == 4161)
#define REGNO_IS_FR(regno)  (regno >= GDB_FR_f0 && regno <= GDB_FR_f31)
#define REGNO_IS_PC(regno)  (regno == GDB_REG_PC)
#define REGNO_IS_VR(regno)  (regno >= GDB_VR_v0 && regno <= GDB_VR_v31)



/* Register number definations for abstract command. */
enum riscv_cmd_gr_fr_regno
{
	CMD_GPR_x0 = 0x1000,
	CMD_FR_f0 = 0x1020,
	CMD_FR_f63 = 0x103f,
};


#endif
