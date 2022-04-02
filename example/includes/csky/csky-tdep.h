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
// File name: csky-tdep.h
// function description: defination for CSKY Target Description .
//
// ****************************************************************************

#ifndef __CSKY_TDEP_H__
#define __CSKY_TDEP_H__

#include "dbg-target.h"

#undef DIRECTORY_SEPARATOR
#ifdef _WIN32
#define DIRECTORY_SEPARATOR '\\'
#else
#define DIRECTORY_SEPARATOR '/'
#endif

#define DEFAULT_REGISTER_LIST_SIZE    16

enum csky_arch
{
	/* Here, macros for CSKY Arch are not equals to
	   bits domain of class in CPUID0 in CPU ID SPEC
	   as they are different in three versions.
	   They are flags for getting the right tdesc_xml files.*/
    CSKY_ARCH_UNKNOWN = 0,
    CSKY_ARCH_CK510 = 1,
    CSKY_ARCH_CK610,
    CSKY_ARCH_CK803 = 0x11,
    CSKY_ARCH_CK810,
    CSKY_ARCH_CK802,
    CSKY_ARCH_CK807,
    CSKY_ARCH_CK803S,
    CSKY_ARCH_CK820,
    CSKY_ARCH_CK801,
    CSKY_ARCH_CK860,
    CSKY_ARCH_CK804,
    CSKY_ARCH_CK805,
};

enum csky_series
{
	CSKY_E_SERIES = 0,
	CSKY_R_SERIES,
	CSKY_I_SERIES,
	CSKY_S_SERIES,
	CSKY_C_SERIES,
	CSKY_UNKNOWN_SERIES,
};

struct ddc_destroyed_regs
{
	int rd01_saved;
	unsigned int saved_rd0;
	unsigned int saved_rd1;
};

struct cpu_csky
{
	enum csky_arch arch;
	enum csky_series series;
	unsigned int id_version;
	unsigned int revision;
    char *cpu_info;
	char cpu_name[16];
    unsigned int cpid[10];
    enum  target_endian endian; /* Target endian. */
    enum target_state state;    /* Target state.  */
    int had_ver;                /* Had version.  */
	int cpu_state;              /* For onlyserver */
/* CPUID ver 3 */
#define CPU_FEATURE_DSP_MEDIA     (1 << 0)
#define CPU_FEATURE_MMU           (1 << 1)
#define CPU_FEATURE_FPU           (1 << 2)
#define CPU_FEATURE_SPM           (1 << 3)
#define CPU_FEATURE_MGU           (1 << 4)
#define CPU_FEATURE_BCTM          (1 << 5)
#define CPU_FEATURE_VDSP          (1 << 6)
#define CPU_FEATURE_SET           (1 << 7)
#define CPU_FEATURE_TEE           (1 << 8)

/* CPUID ver 4 */
#define CPU_FEATURE_FPU_V4       (1 << 0)
#define CPU_FEATURE_TEE_V4       (1 << 1)
#define CPU_FEATURE_DSP_V4       (1 << 2)
#define CPU_FEATURE_VDSP_V4      (1 << 3)
    unsigned int flags;         /* CPU feature flags.  */
    int is_normal;
    unsigned int max_hw_breakpoint;      /* The quantity of hw breakpoint.  */
    unsigned int max_watchpoint;         /* The quantity of watchpoint.  */
	int reg_count;
    struct reg * reg_list;
    unsigned int tdesc_xml_length; /* xml file length.  */
    char *tdesc_xml_contents; /* xml file contents.  */
    struct halt_info halt;
	struct ddc_destroyed_regs destroyed_regs;
	int hacr_width;
};

struct csky_arch_info
{
	int had_top_ver;
	int cdi_type;
	int hacr_width;
	int cpu_cur;
	int cpu_cnt;
	int current_had_ver;
	int mtcrDelay;
	int cache_en;
	int ddc_en_flag;
	unsigned int cache_flush_delay;

	int local_semi;
	int onlyserver;
	int resume_bkpt_exception;

	int is_mcpu;
	int is_multicore;
	int is_multicore_threads;

	int is_in_hadtop;

	enum pc_sampling_type sampling_type;

	/* the max mode when mem-access. */
	enum TARGET_MEM_ACCESS_MAX_MODE mem_access_max_mode;

	unsigned int enter_debug_time;

	struct cpu_csky *cpus;
	void *link;
	void *target;
};

struct csky_ld_st_info
{
	unsigned int st_ld_addr[8];
	unsigned int is_st_ld[8];
	unsigned int st_ld_len[8];
	unsigned int addr_count;
};

struct csky_arch_info * get_csky_arch_info ();

int csky_ops_read_memory (U64 addr, unsigned char *buff, int size);
int csky_ops_write_memory (U64 addr, unsigned char *buff, int size);

int csky_ops_resume (void);



/* Instruction macros used for analyzing the prologue.  */
#define V1_IS_SUBI0(x)   (((x) & 0xfe0f) == 0x2400)   /* subi r0,oimm5.     */
#define V1_IS_STWx0(x)   (((x) & 0xf00f) == 0x9000)   /* stw rz,(r0,disp).  */
#define V1_IS_STWxy(x)   (((x) & 0xf000) == 0x9000)   /* stw rx,(ry,disp).  */
#define V1_IS_MOVx0(x)   (((x) & 0xfff0) == 0x1200)   /* mov rn,r0.         */
#define V1_IS_MOV80(x)   (((x) & 0xfff0) == 0x1208)   /* mov r8,r0.         */
#define V1_IS_LRW1(x)    (((x) & 0xff00) == 0x7100)   /* lrw r1,literal.    */
#define V1_IS_MOVI1(x)   (((x) & 0xf80f) == 0x6001)   /* movi r1,imm7.      */
#define V1_IS_BGENI1(x)  (((x) & 0xfe0f) == 0x3201)   /* bgeni r1,imm5.     */
#define V1_IS_BMASKI1(x) (((x) & 0xfe0f) == 0x2C01)   /* bmaski r1,imm5.    */
#define V1_IS_ADDI1(x)   (((x) & 0xfe0f) == 0x2001)   /* addi r1,oimm5.     */
#define V1_IS_SUBI1(x)   (((x) & 0xfe0f) == 0x2401)   /* subi r1,oimm5.     */
#define V1_IS_RSUBI1(x)  (((x) & 0xfe0f) == 0x2801)   /* rsubi r1,imm5.     */
#define V1_IS_NOT1(x)    (((x) & 0xffff) == 0x01f1)   /* not r1.            */
#define V1_IS_ROTLI1(x)  (((x) & 0xfe0f) == 0x3801)   /* rotli r1,imm5.     */
#define V1_IS_LSLI1(x)   (((x) & 0xfe0f) == 0x3c01)   /* lsli r1, imm5.     */
#define V1_IS_BSETI1(x)  (((x) & 0xfe0f) == 0x3401)   /* bseti r1,imm5.     */
#define V1_IS_BCLRI1(x)  (((x) & 0xfe0f) == 0x3001)   /* bclri r1,imm5.     */
#define V1_IS_STWSP(x)   (x == 0x9000)                /* st r0, (r0, 0).    */
#define V1_IS_IXH1(x)    (((x) & 0xffff) == 0x1d11)   /* ixh r1,r1.         */
#define V1_IS_IXW1(x)    (((x) & 0xffff) == 0x1511)   /* ixw r1,r1.         */
#define V1_IS_SUB01(x)   (((x) & 0xffff) == 0x0510)   /* subu r0,r1.        */
#define V1_IS_RTS(x)     (((x) & 0xffff) == 0x00cf)   /* jmp r15.           */

#define V1_IS_R1_ADJUSTER(x) \
    (V1_IS_ADDI1(x) || V1_IS_SUBI1(x) || V1_IS_ROTLI1(x) || V1_IS_BSETI1(x) \
     || V1_IS_BCLRI1(x) || V1_IS_RSUBI1(x) || V1_IS_NOT1(x)\
     || V1_IS_MOVI1(x)  || V1_IS_IXH1(x) || V1_IS_IXW1(x))\
     || V1_IS_LSLI1(x) || V1_IS_STWSP(x) || V1_IS_SUB01(x)


/* st.b/h/w.  */
#define V1_IS_ST(insn)            ((insn & 0x9000) == 0x9000)
/* size: 0(w)~4   1(b)~1  2(h)~2.  */
#define V1_ST_SIZE(insn)          ((insn & 0x6000) ?\
                                   ((insn & 0x6000) >> 13 == 1 ? 1 : 2) : 4)
/* rx.  */
#define V1_ST_ADDR_REGNUM(insn)   (insn & 0x000f)
/* disp.  */
#define V1_ST_OFFSET(insn)        ((insn & 0x00f0) >> 4)

/* stm rf-r15, r0.  */
#define V1_IS_STM(insn)           ((insn & 0xfff0) == 0x0070)
/* Count of registers.  */
#define V1_STM_SIZE(insn)         (15 - (insn & 0x000f) + 1)

#define V1_IS_STQ(insn)           ((insn & 0xfff0) == 0x0050)
/* rx.  */
#define V1_STQ_ADDR_REGNUM(insn)  (insn & 0x000f)

/* ld.b/h/w.  */
#define V1_IS_LD(insn)            ((insn & 0x9000) == 0x8000)
/* size.  */
#define V1_LD_SIZE(insn)          V1_ST_SIZE(insn)
/* rx.  */
#define V1_LD_ADDR_REGNUM(insn)   V1_ST_ADDR_REGNUM(insn)
/* disp.  */
#define V1_LD_OFFSET(insn)        V1_ST_OFFSET(insn)

#define V1_IS_LDM(insn)           ((insn & 0xfff0) == 0x0060)

/* Count of registers.  */
#define V1_LDM_SIZE(insn)         V1_STM_SIZE(insn)
#define V1_IS_LDQ(insn)           ((insn & 0xfff0) == 0x0040)
/* rx.  */
#define V1_LDQ_ADDR_REGNUM(insn)  (insn & 0x000f)

/* For jmp/branch insn.  */
#define V1_IS_BR(insn)            ((insn & 0xf800) == 0xf000)    /*  */
#define V1_IS_BT(insn)            ((insn & 0xf800) == 0xe000)    /*  */
#define V1_IS_BF(insn)            ((insn & 0xf800) == 0xe800)    /*  */
#define V1_IS_BSR(insn)           ((insn & 0xf800) == 0xf800)    /*  */
#define V1_IS_BTBF(insn)          ((insn & 0xf000) == 0xe000)    /*  */
#define V1_IS_JMP(insn)           ((insn & 0xfff0) == 0x00c0)    /*  */
#define V1_IS_JMPI(insn)          ((insn & 0xff00) == 0x7000)    /*  */
#define V1_IS_JSR(insn)           ((insn & 0xfff0) == 0x00d0)    /*  */
#define V1_IS_JSRI(insn)          ((insn & 0xff00) == 0x7f00)    /*  */

#define V1_BR_OFFSET(insn)        ((insn & 0x400) ? \
                                  (0 - (2 + ((0x3ff & insn) << 1))) : \
                                  (2 + ((0x3ff & insn) << 1)))
#define V1_BSR_OFFSET(insn)       V1_BR_OFFSET(insn)
#define V1_BTBF_OFFSET(insn)      V1_BR_OFFSET(insn)

#define V1_JMP_REGNUM(insn)       (insn & 0xf)

#define V1_JSR_REGNUM(insn)       (insn & 0xf)

#define V1_JSRI_OFFSET(insn)      ((((insn & 0xff) << 2) + 2) & 0xfffffffc)
#define V1_JMPI_OFFSET(insn)      V1_JSRI_OFFSET(insn)

#define V1_IS_MFCR_EPSR(insn)     ((insn & 0xfff0) == 0x1020)
#define V1_IS_MFCR_FPSR(insn)     ((insn & 0xfff0) == 0x1030)
#define V1_IS_MFCR_EPC(insn)      ((insn & 0xfff0) == 0x1040)
#define V1_IS_MFCR_FPC(insn)      ((insn & 0xfff0) == 0x1050)
#define V1_IS_RFI(insn)           (insn == 0x0003)
#define V1_IS_RTE(insn)           (insn == 0x0002)
#define V1_IS_MOV_FP_SP(insn)     (insn == 0x1208)  /* mov r8, r0.  */

/* Define three insn as follows for *.elf or *.so built with fPIC
   We call it "fPIC insns"
              bsr label            --------- insn1
   label :    lrw r14, imm         --------- insn2
              addu r14, r15        --------- insn3
              ld   r15, (r0, imm)  --------- insn4.  */

#define V1_IS_BSR_NEXT(insn)       (insn == 0xf800)              /* insn1.  */
#define V1_IS_LRW_R14(insn)        ((insn & 0xff00) == 0x7e00)   /* insn2.  */
#define V1_IS_ADDU_R14_R15(insn)   (insn == 0x1cfe)              /* insn3.  */
#define V1_IS_LD_R15(insn)         ((insn & 0xff0f) == 0x8f00)   /* insn4.  */

/* ----------------------V2P insn ------------------------  */

/* For insn v2p.  */
/* st.b/h/w, the buttom half 0x0c00 is stm.  */
#define V2P_16_IS_ST(insn)            (((insn & 0xf000) == 0x5000)\
                                        && ((insn & 0x0c00) != 0x0c00))
/* size.  */
#define V2P_16_ST_SIZE(insn)          (1 << ((insn & 0x0c00) >> 10))
/* rx.  */
#define V2P_16_ST_ADDR_REGNUM(insn)   ((insn & 0x003c) >> 2)
/* disp.  */
#define V2P_16_ST_OFFSET(insn)        (insn & 0x3)
/* ry.  */
#define V2P_16_ST_VAL_REGNUM(insn)    ((insn & 0x03c0) >> 6)

/* stw ry, (r0, disp).  */
#define V2P_16_IS_STWx0(insn)         ((insn & 0xfc3c) == 0x5800)
#define V2P_16_IS_STM(insn)           ((insn & 0xfc00) == 0x5c00)
/* rx.  */
#define V2P_16_STM_ADDR_REGNUM(insn)  V2P_16_ST_ADDR_REGNUM(insn)
/* Count of registers.  */
#define V2P_16_STM_SIZE(insn)         ((insn & 0x3) + 1)

/* ld.b/h/w, the buttom half 0x0c00 is ldm.  */
#define V2P_16_IS_LD(insn)            (((insn & 0xf000) == 0x4000)\
                                       && ((insn & 0x0c00) != 0x0c00))
/* size.  */
#define V2P_16_LD_SIZE(insn)          V2P_16_ST_SIZE(insn)
/* rx.  */
#define V2P_16_LD_ADDR_REGNUM(insn)   V2P_16_ST_ADDR_REGNUM(insn)
/* disp.  */
#define V2P_16_LD_OFFSET(insn)        V2P_16_ST_OFFSET(insn)

#define V2P_16_IS_LDM(insn)           ((insn & 0xfc00) == 0x4c00)
/* rx.  */
#define V2P_16_LDM_ADDR_REGNUM(insn)  V2P_16_STM_ADDR_REGNUM(insn)
/* Count of registers.  */
#define V2P_16_LDM_SIZE(insn)         V2P_16_STM_SIZE(insn)
/* ry.  */
#define V2P_16_STM_VAL_REGNUM(insn)   ((insn & 0x03c0) >> 6)

/* stm  ry-rz, (r0).  */
#define V2P_16_IS_STMx0(insn)         ((insn & 0xfc3c) == 0x5c00)

/* st.b/h/w.  */
#define V2P_32_IS_ST(insn)            ((insn & 0xfc00c000) == 0xdc000000)

/* size: b/h/w.  */
#define V2P_32_ST_SIZE(insn)          (1 << ((insn & 0x3000) >> 12))
/* rx.  */
#define V2P_32_ST_ADDR_REGNUM(insn)   ((insn & 0x001f0000) >> 16)
/* disp.  */
#define V2P_32_ST_OFFSET(insn)        (insn & 0x00000fff)
/* ry.  */
#define V2P_32_ST_VAL_REGNUM(insn)    ((insn & 0x03e00000) >> 21)

/* stw ry, (r0, disp).  */
#define V2P_32_IS_STWx0(insn)         ((insn & 0xfc1ff000) == 0xdc002000)
#define V2P_32_IS_STM(insn)           ((insn & 0xfc00ffe0) == 0xd4001c20)
/* rx.  */
#define V2P_32_STM_ADDR_REGNUM(insn)  V2P_32_ST_ADDR_REGNUM(insn)
/* Count of registers.  */
#define V2P_32_STM_SIZE(insn)         ((insn & 0x1f) + 1)
/* ry.  */
#define V2P_32_STM_VAL_REGNUM(insn)   ((insn & 0x03e00000) >> 21)

/* stm ry-rz, (r0).  */
#define V2P_32_IS_STMx0(insn)         ((insn & 0xfc1fffe0) == 0xd4001c20)
#define V2P_32_IS_STR(insn)           (((insn & 0xfc000000) == 0xd4000000)\
                                        && !(V2P_32_IS_STM(insn)))
/* rx.  */
#define V2P_32_STR_X_REGNUM(insn)     V2P_32_ST_ADDR_REGNUM(insn)
/* ry.  */
#define V2P_32_STR_Y_REGNUM(insn)     ((insn >> 21) & 0x1f)

/* size: b/h/w.  */
#define V2P_32_STR_SIZE(insn)         (1 << ((insn & 0x0c00) >> 10))
/* imm (for rx + ry * imm).  */
#define V2P_32_STR_OFFSET(insn)       ((insn & 0x000003e0) >> 5)
#define V2P_32_IS_STEX(insn)          ((insn & 0xfc00f000) == 0xdc007000)
/* rx.  */
#define V2P_32_STEX_ADDR_REGNUM(insn) ((insn & 0xf0000) >> 16)
/* disp.  */
#define V2P_32_STEX_OFFSET(insn)      (insn & 0x0fff)
/* ld.b/h/w.  */
#define V2P_32_IS_LD(insn)            ((insn & 0xfc008000) == 0xd8000000)
/* size.  */
#define V2P_32_LD_SIZE(insn)          V2P_32_ST_SIZE(insn)
/* rx.  */
#define V2P_32_LD_ADDR_REGNUM(insn)   V2P_32_ST_ADDR_REGNUM(insn)
/* disp.  */
#define V2P_32_LD_OFFSET(insn)        V2P_32_ST_OFFSET(insn)

#define V2P_32_IS_LDM(insn)           ((insn & 0xfc00ffe0) == 0xd0001c20)
/* rx.  */
#define V2P_32_LDM_ADDR_REGNUM(insn)  V2P_32_STM_ADDR_REGNUM(insn)
/* Count of registers.  */
#define V2P_32_LDM_SIZE(insn)         V2P_32_STM_SIZE(insn)

#define V2P_32_IS_LDR(insn)           (((insn & 0xfc00fe00) == 0xd0000000)\
                                       && !(V2P_32_IS_LDM(insn)))
/* rx.  */
#define V2P_32_LDR_X_REGNUM(insn)     V2P_32_STR_X_REGNUM(insn)
/* ry.  */
#define V2P_32_LDR_Y_REGNUM(insn)     V2P_32_STR_Y_REGNUM(insn)

/* size: b/h/w.  */
#define V2P_32_LDR_SIZE(insn)         V2P_32_STR_SIZE(insn)

/* imm (for rx + ry * imm).  */
#define V2P_32_LDR_OFFSET(insn)       V2P_32_STR_OFFSET(insn)
#define V2P_32_IS_LDEX(insn)          ((insn & 0xfc00f000) == 0xd8007000)
/* rx.  */
#define V2P_32_LDEX_ADDR_REGNUM(insn) V2P_32_STEX_ADDR_REGNUM(insn)
/* disp.  */
#define V2P_32_LDEX_OFFSET(insn)      V2P_32_STEX_OFFSET(insn)


/* subi r0, imm.  */
#define V2P_16_IS_SUBI0(insn)         ((insn & 0xffc1) == 0x2001)
#define V2P_16_SUBI_IMM(insn)         (((insn & 0x003e) >> 1) + 1)


/* subi r0, imm.  */
#define V2P_32_IS_SUBI0(insn)         ((insn & 0xffff0000) == 0xa4000000)
#define V2P_32_SUBI_IMM(insn)         ((insn & 0xffff) + 1)

/* mov r8, r0.  */
#define V2P_16_IS_MOV_FP_SP(insn)     (insn == 0x1e00)

/* mov r8, r0.  */
#define V2P_32_IS_MOV_FP_SP(insn)     (insn == 0xc4004828)


/* Check st16 but except st16 sp.  */
#define V2_16_IS_ST(insn)            (((insn & 0xe000)==0xa000)\
                                      && ((insn & 0x1800) != 0x1800))
/* size.  */
#define V2_16_ST_SIZE(insn)          (1 << ((insn & 0x1800) >> 11))
/* rx.  */
#define V2_16_ST_ADDR_REGNUM(insn)   ((insn & 0x700) >> 8)
/* disp.  */
#define V2_16_ST_OFFSET(insn)        ((insn & 0x1f) << ((insn & 0x1800) >> 11))
/* ry.  */
#define V2_16_ST_VAL_REGNUM(insn)    ((insn &0xe0) >> 5)

/* st16.w rz, (sp, disp).  */
#define V2_16_IS_STWx0(insn)         ((insn & 0xf800) == 0xb800)
#define V2_16_STWx0_VAL_REGNUM(insn) V2_16_ST_ADDR_REGNUM(insn)

/* disp.  */
#define V2_16_STWx0_OFFSET(insn)     ((((insn & 0x700) >> 3)\
                                      + (insn &0x1f)) <<2)

/* "stm" only exists in 32_bit insn now.  */
/* #define V2_16_IS_STM(insn)           ((insn & 0xfc00) == 0x5c00)  */
/* rx  */
/* #define V2_16_STM_ADDR_REGNUM(insn)  V2_16_ST_ADDR_REGNUM(insn)  */
/* count of registers  */
/* #define V2_16_STM_SIZE(insn)         ((insn & 0x3) + 1)  */

/* Check ld16 but except ld16 sp.  */
#define V2_16_IS_LD(insn)            (((insn & 0xe000)==0x8000)\
                                       && (insn & 0x1800) != 0x1800)
/* size.  */
#define V2_16_LD_SIZE(insn)          V2_16_ST_SIZE(insn)
/* rx.  */
#define V2_16_LD_ADDR_REGNUM(insn)   V2_16_ST_ADDR_REGNUM(insn)
/* disp.  */
#define V2_16_LD_OFFSET(insn)        V2_16_ST_OFFSET(insn)

/* ld16.w rz,(sp,disp).  */
#define V2_16_IS_LDWx0(insn)         ((insn & 0xf800) == 0x9800)
/*disp.  */
#define V2_16_LDWx0_OFFSET(insn)     V2_16_STWx0_OFFSET(insn)

/* "ldm" only exists in 32_bit insn now.  */
/* #define V2_16_IS_LDM(insn)           ((insn & 0xfc00) == 0x4c00)  */
/* rx  */
/* #define V2_16_LDM_ADDR_REGNUM(insn)  V2_16_STM_ADDR_REGNUM(insn)  */
/* count of registers  */
/* #define V2_16_LDM_SIZE(insn)         V2_16_STM_SIZE(insn)  */
/* ry  */
/* #define V2_16_STM_VAL_REGNUM(insn)   ((insn & 0x03c0) >> 6)  */
/* stm  ry-rz,(r0)  */
/* #define V2_16_IS_STMx0(insn)         ((insn & 0xfc3c) == 0x5c00)  */

/* st32.b/h/w/d.  */
#define V2_32_IS_ST(insn)            ((insn & 0xfc00c000) == 0xdc000000)

/* size: b/h/w/d.  */
#define V2_32_ST_SIZE(insn)          (1 << ((insn & 0x3000) >> 12))
/* rx.  */
#define V2_32_ST_ADDR_REGNUM(insn)   ((insn & 0x001f0000) >> 16)
/* disp.  */
#define V2_32_ST_OFFSET(insn)        ((insn & 0xfff) << ((insn & 0x3000) >> 12))
/* ry.  */
#define V2_32_ST_VAL_REGNUM(insn)    ((insn & 0x03e00000) >> 21)

/* stw ry, (sp, disp).  */
#define V2_32_IS_STWx0(insn)         ((insn & 0xfc1ff000) == 0xdc0e2000)


/* stm32 ry-rz, (rx).  */
#define V2_32_IS_STM(insn)           ((insn & 0xfc00ffe0) == 0xd4001c20)
/* rx.  */
#define V2_32_STM_ADDR_REGNUM(insn)  V2_32_ST_ADDR_REGNUM(insn)
/* Count of registers.  */
#define V2_32_STM_SIZE(insn)         ((insn & 0x1f) + 1)
/* ry.  */
#define V2_32_STM_VAL_REGNUM(insn)   ((insn & 0x03e00000) >> 21)
/* stm32 ry-rz, (sp).  */
#define V2_32_IS_STMx0(insn)         ((insn & 0xfc1fffe0) == 0xd40e1c20)

/* str32.b/h/w rz, (rx, ry << offset).  */
#define V2_32_IS_STR(insn)           (((insn & 0xfc000000) == 0xd4000000)\
                                      && !(V2_32_IS_STM(insn)))
/* rx.  */
#define V2_32_STR_X_REGNUM(insn)     V2_32_ST_ADDR_REGNUM(insn)
/* ry.  */
#define V2_32_STR_Y_REGNUM(insn)     ((insn >> 21) & 0x1f)
/* size: b/h/w.  */
#define V2_32_STR_SIZE(insn)         (1 << ((insn & 0x0c00) >> 10))
/* imm (for rx + ry * imm).  */
#define V2_32_STR_OFFSET(insn)       ((insn & 0x000003e0) >> 5)

/* stex32.w rz, (rx, disp).  */
#define V2_32_IS_STEX(insn)          ((insn & 0xfc00f000) == 0xdc007000)
/* rx.  */
#define V2_32_STEX_ADDR_REGNUM(insn) ((insn & 0x1f0000) >> 16)
/* disp.  */
#define V2_32_STEX_OFFSET(insn)      ((insn & 0x0fff) << 2)

/* ld.b/h/w.  */
#define V2_32_IS_LD(insn)            ((insn & 0xfc00c000) == 0xd8000000)
/* size.  */
#define V2_32_LD_SIZE(insn)          V2_32_ST_SIZE(insn)
/* rx.  */
#define V2_32_LD_ADDR_REGNUM(insn)   V2_32_ST_ADDR_REGNUM(insn)
/* disp.  */
#define V2_32_LD_OFFSET(insn)        V2_32_ST_OFFSET(insn)
#define V2_32_IS_LDM(insn)           ((insn & 0xfc00ffe0) == 0xd0001c20)
/* rx.  */
#define V2_32_LDM_ADDR_REGNUM(insn)  V2_32_STM_ADDR_REGNUM(insn)
/* Count of registers.  */
#define V2_32_LDM_SIZE(insn)         V2_32_STM_SIZE(insn)

/* ldr32.b/h/w rz, (rx, ry << offset).  */
#define V2_32_IS_LDR(insn)           (((insn & 0xfc00fe00) == 0xd0000000)\
                                      && !(V2_32_IS_LDM(insn)))
/* rx.  */
#define V2_32_LDR_X_REGNUM(insn)     V2_32_STR_X_REGNUM(insn)
/* ry.  */
#define V2_32_LDR_Y_REGNUM(insn)     V2_32_STR_Y_REGNUM(insn)
/* size: b/h/w.  */
#define V2_32_LDR_SIZE(insn)         V2_32_STR_SIZE(insn)
/* imm (for rx + ry*imm).  */
#define V2_32_LDR_OFFSET(insn)       V2_32_STR_OFFSET(insn)

#define V2_32_IS_LDEX(insn)          ((insn & 0xfc00f000) == 0xd8007000)
/* rx.  */
#define V2_32_LDEX_ADDR_REGNUM(insn) V2_32_STEX_ADDR_REGNUM(insn)
/* disp.  */
#define V2_32_LDEX_OFFSET(insn)      V2_32_STEX_OFFSET(insn)


/* subi.sp sp, disp.  */
#define V2_16_IS_SUBI0(insn)         ((insn & 0xfce0) == 0x1420)
/* disp.  */
#define V2_16_SUBI_IMM(insn)         ((((insn & 0x300) >> 3)\
                                       + (insn & 0x1f)) << 2)


/* subi32 sp,sp,oimm12.  */
#define V2_32_IS_SUBI0(insn)         ((insn & 0xfffff000) == 0xe5ce1000)
/* oimm12.  */
#define V2_32_SUBI_IMM(insn)         ((insn & 0xfff) + 1)

/* For new instrctions in V2: push.  */
/* push16.  */
#define V2_16_IS_PUSH(insn)          ((insn & 0xffe0) == 0x14c0)
#define V2_16_IS_PUSH_R15(insn)      ((insn & 0x10) == 0x10)
#define V2_16_PUSH_LIST1(insn)       ( insn & 0xf)           /* r4 - r11.  */

/* pop16.  */
#define V2_16_IS_POP(insn)           ((insn & 0xffe0) == 0x1480)
#define V2_16_IS_POP_R15(insn)       V2_16_IS_PUSH_R15(insn)
#define V2_16_POP_LIST1(insn)        V2_16_PUSH_LIST1(insn)  /* r4 - r11.  */


/* push32.  */
#define V2_32_IS_PUSH(insn)          ((insn & 0xfffffe00) == 0xebe00000)
#define V2_32_IS_PUSH_R29(insn)      ((insn & 0x100) == 0x100)
#define V2_32_IS_PUSH_R15(insn)      ((insn & 0x10) == 0x10)
#define V2_32_PUSH_LIST1(insn)       ( insn & 0xf)         /* r4 - r11.  */
#define V2_32_PUSH_LIST2(insn)       ((insn & 0xe0) >> 5)  /* r16 - r17.  */

/* pop32.  */
#define V2_32_IS_POP(insn)          ((insn & 0xfffffe00) == 0xebc00000)
#define V2_32_IS_POP_R29(insn)      V2_32_IS_PUSH_R29(insn)
#define V2_32_IS_POP_R15(insn)      V2_32_IS_PUSH_R15(insn)
#define V2_32_POP_LIST1(insn)       V2_32_PUSH_LIST1(insn)  /* r4 - r11.  */
#define V2_32_POP_LIST2(insn)       V2_32_PUSH_LIST2(insn)  /* r16 - r17.  */

/* Adjust sp by r4(l0).  */
/* lrw r4, literal.  */
#define V2_16_IS_LRW4(x)    (((x) & 0xfce0) == 0x1080)
/* movi r4, imm8.  */
#define V2_16_IS_MOVI4(x)   (((x) & 0xff00) == 0x3400)

/* Insn: bgeni,bmaski only exist in 32_insn now.  */
/* bgeni r4,imm5.  */
/* #define V2_16_IS_BGENI4(x)  (((x) & 0xfe0f) == 0x3201)  */
/* bmaski r4,imm5.  */
/* #define V2_16_IS_BMASKI4(x) (((x) & 0xfe0f) == 0x2C01)  */

/* addi r4, oimm8.  */
#define V2_16_IS_ADDI4(x)   (((x) & 0xff00) == 0x2400)
/* subi r4, oimm8.  */
#define V2_16_IS_SUBI4(x)   (((x) & 0xff00) == 0x2c00)

/* Insn: rsubi not exist in v2_insn.  */
/* nor16 r4, r4  */
#define V2_16_IS_NOR4(x)    ((x) == 0x6d12)

/* Insn: rotli not exist in v2_16_insn.  */
/* lsli r4, r4, imm5.  */
#define V2_16_IS_LSLI4(x)   (((x) & 0xffe0) == 0x4480)
/* bseti r4, imm5.  */
#define V2_16_IS_BSETI4(x)  (((x) & 0xffe0) == 0x3ca0)
/* bclri r4, imm5.  */
#define V2_16_IS_BCLRI4(x)  (((x) & 0xffe0) == 0x3c80)

/* Insn: ixh, ixw only exist in 32_insn now.  */
/* subu sp, r4.  */
#define V2_16_IS_SUBU4(x)   ((x) == 0x6392)

#define V2_16_IS_R4_ADJUSTER(x)   (V2_16_IS_ADDI4(x) || V2_16_IS_SUBI4(x) \
            || V2_16_IS_BSETI4(x) || V2_16_IS_BCLRI4(x) || V2_16_IS_NOR4(x)\
            || V2_16_IS_LSLI4(x))

/* lrw r4, literal.  */
#define V2_32_IS_LRW4(x)    (((x) & 0xffff0000) == 0xea840000)
/* movi r4, imm16.  */
#define V2_32_IS_MOVI4(x)   (((x) & 0xffff0000) == 0xea040000)
/* movih r4, imm16.  */
#define V2_32_IS_MOVIH4(x)  (((x) & 0xffff0000) == 0xea240000)
/* bmaski r4, oimm5.  */
#define V2_32_IS_BMASKI4(x) (((x) & 0xfc1fffff) == 0xc4005024)
/* addi r4, r4, oimm12.  */
#define V2_32_IS_ADDI4(x)   (((x) & 0xfffff000) == 0xe4840000)
/* subi r4, r4, oimm12.  */
#define V2_32_IS_SUBI4(x)   (((x) & 0xfffff000) == 0xe4810000)

/* Insn: rsubi not exist in v2_insn.  */
/* nor32 r4, r4, r4.  */
#define V2_32_IS_NOR4(x)    ((x) == 0xc4842484)
/* rotli r4, r4, imm5.  */
#define V2_32_IS_ROTLI4(x)  (((x) & 0xfc1fffff) == 0xc4044904)
/* lsli r4, r4, imm5.  */
#define V2_32_IS_LISI4(x)   (((x) & 0xfc1fffff) == 0xc4044824)
/* bseti32 r4, r4, imm5.  */
#define V2_32_IS_BSETI4(x)  (((x) & 0xfc1fffff) == 0xc4042844)
/* bclri32 r4, r4, imm5.  */
#define V2_32_IS_BCLRI4(x)  (((x) & 0xfc1fffff) == 0xc4042824)
/* ixh r4, r4, r4.  */
#define V2_32_IS_IXH4(x)    ((x) == 0xc4840824)
/* ixw r4, r4, r4.  */
#define V2_32_IS_IXW4(x)    ((x) == 0xc4840844)
/* subu32 sp, sp, r4.  */
#define V2_32_IS_SUBU4(x)   ((x) == 0xc48e008e)

#define V2_32_IS_R4_ADJUSTER(x)   (V2_32_IS_ADDI4(x) || V2_32_IS_SUBI4(x) \
           || V2_32_IS_ROTLI4(x)  || V2_32_IS_IXH4(x) || V2_32_IS_IXW4(x) \
        || V2_32_IS_NOR4(x)  || V2_32_IS_BSETI4(x) || V2_32_IS_BCLRI4(x)\
        || V2_32_IS_LISI4(x))

#define V2_IS_R4_ADJUSTER(x)  ( V2_32_IS_R4_ADJUSTER(x)\
                                || V2_16_IS_R4_ADJUSTER(x) )
#define V2_IS_SUBU4(x)  ( V2_32_IS_SUBU4(x) || V2_16_IS_SUBU4(x) )

/* Insn: mfcr only exist in v2_32.  */
/* mfcr rz, epsr.  */
#define V2_32_IS_MFCR_EPSR(insn)    ((insn & 0xffffffe0) == 0xc0026020)
/* mfcr rz, fpsr.  */
#define V2_32_IS_MFCR_FPSR(insn)    ((insn & 0xffffffe0) == 0xc0036020)
/* mfcr rz, epc.  */
#define V2_32_IS_MFCR_EPC(insn)     ((insn & 0xffffffe0) == 0xc0046020)
/* mfcr rz, fpc.  */
#define V2_32_IS_MFCR_FPC(insn)     ((insn & 0xffffffe0) == 0xc0056020)

/* Insn: rte, rfi only exit in v2_32.  */
#define V2_32_IS_RTE(insn)    (insn == 0xc0004020)
#define V2_32_IS_RFI(insn)    (insn == 0xc0004420)
#define V2_32_IS_JMP(insn)    ((insn & 0xffe0ffff) == 0xe8c00000)
#define V2_16_IS_JMP(insn)    ((insn & 0xffc3) == 0x7800)
#define V2_32_IS_JMPI(insn)   ((insn & 0xffff0000) == 0xeac00000)
#define V2_32_IS_JMPIX(insn)  ((insn & 0xffe0fffc) == 0xe9e00000)
#define V2_16_IS_JMPIX(insn)  ((insn & 0xf8fc) == 0x38e0)

#define V2_16_IS_BR(insn)     ((insn & 0xfc00) == 0x0400)
#define V2_32_IS_BR(insn)     ((insn & 0xffff0000) == 0xe8000000)
#define V2_16_IS_MOV_FP_SP(insn)     (insn == 0x6e3b)     /* mov r8, r14.  */
#define V2_32_IS_MOV_FP_SP(insn)     (insn == 0xc40e4828) /* mov r8, r14.  */

/*********************************
* FLDS
*********************************/
#define V2_32_IS_FLDS(insn)            (((insn) & 0xfe00ff00) == 0xf4002000)
#define V2_32_FLDS_ADDR_REGNUM(insn)   (((insn) >> 16) & 0x1f)
#define V2_32_FLDS_OFFSET(insn)        (((((insn) >> 4) & 0xf) << 2) + ((((insn) >> 21) & 0xf) << 6))

/*********************************
* FLDD
*********************************/
#define V2_32_IS_FLDD(insn)            (((insn) & 0xfe00ff00) == 0xf4002100)
#define V2_32_FLDD_ADDR_REGNUM(insn)   (((insn) >> 16) & 0x1f)
#define V2_32_FLDD_OFFSET(insn)        (((((insn) >> 4) & 0xf) << 2) + ((((insn) >> 21) & 0xf) << 6))

/*********************************
* FLDM
*********************************/
#define V2_32_IS_FLDM(insn)            (((insn) & 0xfe00ff00) == 0xf4002200)
#define V2_32_FLDM_ADDR_REGNUM(insn)   (((insn) >> 16) & 0x1f)
#define V2_32_FLDM_OFFSET(insn)        (((((insn) >> 4) & 0xf) << 3) + ((((insn) >> 21) & 0xf) << 7))

/*********************************
* FLDRS
*********************************/
#define V2_32_IS_FLDRS0(insn)           (((insn) & 0xfc00fff0) == 0xf4002800)
#define V2_32_IS_FLDRS1(insn)           (((insn) & 0xfc00fff0) == 0xf4002820)
#define V2_32_IS_FLDRS2(insn)           (((insn) & 0xfc00fff0) == 0xf4002840)
#define V2_32_IS_FLDRS3(insn)           (((insn) & 0xfc00fff0) == 0xf4002860)
#define V2_32_FLDRS_RX(insn)            (((insn) >> 16) & 0x1f)
#define V2_32_FLDRS_RY(insn)            (((insn) >> 21) & 0x1f)

/*********************************
 * FLDRD
 *********************************/
#define V2_32_IS_FLDRD0(insn)           (((insn) & 0xfc00fff0) == 0xf4002900)
#define V2_32_IS_FLDRD1(insn)           (((insn) & 0xfc00fff0) == 0xf4002920)
#define V2_32_IS_FLDRD2(insn)           (((insn) & 0xfc00fff0) == 0xf4002940)
#define V2_32_IS_FLDRD3(insn)           (((insn) & 0xfc00fff0) == 0xf4002960)
#define V2_32_FLDRD_RX(insn)            (((insn) >> 16) & 0x1f)
#define V2_32_FLDRD_RY(insn)            (((insn) >> 21) & 0x1f)

/*********************************
 * FLDRM
 *********************************/
#define V2_32_IS_FLDRM0(insn)           (((insn) & 0xfc00fff0) == 0xf4002a00)
#define V2_32_IS_FLDRM1(insn)           (((insn) & 0xfc00fff0) == 0xf4002a20)
#define V2_32_IS_FLDRM2(insn)           (((insn) & 0xfc00fff0) == 0xf4002a40)
#define V2_32_IS_FLDRM3(insn)           (((insn) & 0xfc00fff0) == 0xf4002a60)
#define V2_32_FLDRM_RX(insn)            (((insn) >> 16) & 0x1f)
#define V2_32_FLDRM_RY(insn)            (((insn) >> 21) & 0x1f)

/*********************************
 * FLDMS
 *********************************/
#define V2_32_IS_FLDMS(insn)           (((insn) & 0xfe00fff0) == 0xf4003000)
#define V2_32_IS_FLDMD(insn)           (((insn) & 0xfe00fff0) == 0xf4003100)
#define V2_32_IS_FLDMM(insn)           (((insn) & 0xfe00fff0) == 0xf4003200)
#define V2_32_FLDMSDM_REGNUM(insn)     (((insn) >> 16) & 0x1f)
#define V2_32_FLDMSDM_COUNT(insn)      ((((insn) >> 21) & 0xf) + 1)

/*********************************
 * FLRWS
 *********************************/
#define V2_32_IS_FLRWS(insn)           (((insn) & 0xfe00ff00) == 0xf4003800)
#define V2_32_IS_FLRWD(insn)           (((insn) & 0xfe00ff00) == 0xf4003900)
#define V2_32_FLRWSD_REGNUM(insn)      (((insn) >> 16) & 0x1f)
#define V2_32_FLRWSD_OFFSET(insn)      (((((insn) >> 4) & 0xf) << 2) + ((((insn) >> 21) & 0xf) << 6))


/*********************************
 * FSTS
 *********************************/
#define V2_32_IS_FSTS(insn)           (((insn) & 0xfe00ff00) == 0xf4002400)
#define V2_32_IS_FSTD(insn)           (((insn) & 0xfe00ff00) == 0xf4002500)
#define V2_32_IS_FSTM(insn)           (((insn) & 0xfe00ff00) == 0xf4002600)
#define V2_32_FSTSDM_REGNUM(insn)     (((insn) >> 16) & 0x1f)
#define V2_32_FST_SD_OFFSET(insn)     (((((insn) >> 4) & 0xf) << 2) + ((((insn) >> 21) & 0xf) << 6))
#define V2_32_FST_M_OFFSET(insn)      (((((insn) >> 4) & 0xf) << 3) + ((((insn) >> 21) & 0xf) << 7))


/*********************************
 * FSTRS
 *********************************/
#define V2_32_IS_FSTRS0(insn)           (((insn) & 0xfc00fff0) == 0xf4002c00)
#define V2_32_IS_FSTRS1(insn)           (((insn) & 0xfc00fff0) == 0xf4002c20)
#define V2_32_IS_FSTRS2(insn)           (((insn) & 0xfc00fff0) == 0xf4002c40)
#define V2_32_IS_FSTRS3(insn)           (((insn) & 0xfc00fff0) == 0xf4002c60)
#define V2_32_FSTRS_RX(insn)            (((insn) >> 16) & 0x1f)
#define V2_32_FSTRS_RY(insn)            (((insn) >> 21) & 0x1f)

/*********************************
 * FSTRD
 *********************************/
#define V2_32_IS_FSTRD0(insn)           (((insn) & 0xfc00fff0) == 0xf4002d00)
#define V2_32_IS_FSTRD1(insn)           (((insn) & 0xfc00fff0) == 0xf4002d20)
#define V2_32_IS_FSTRD2(insn)           (((insn) & 0xfc00fff0) == 0xf4002d40)
#define V2_32_IS_FSTRD3(insn)           (((insn) & 0xfc00fff0) == 0xf4002d60)
#define V2_32_FSTRD_RX(insn)            (((insn) >> 16) & 0x1f)
#define V2_32_FSTRD_RY(insn)            (((insn) >> 21) & 0x1f)

/*********************************
 * FSTRM
 *********************************/
#define V2_32_IS_FSTRM0(insn)           (((insn) & 0xfc00fff0) == 0xf4002e00)
#define V2_32_IS_FSTRM1(insn)           (((insn) & 0xfc00fff0) == 0xf4002e20)
#define V2_32_IS_FSTRM2(insn)           (((insn) & 0xfc00fff0) == 0xf4002e40)
#define V2_32_IS_FSTRM3(insn)           (((insn) & 0xfc00fff0) == 0xf4002e60)
#define V2_32_FSTRM_RX(insn)            (((insn) >> 16) & 0x1f)
#define V2_32_FSTRM_RY(insn)            (((insn) >> 21) & 0x1f)

/*********************************
 * FSTMS
 *********************************/
#define V2_32_IS_FSTMS(insn)           (((insn) & 0xfe00fff0) == 0xf4003400)
#define V2_32_IS_FSTMD(insn)           (((insn) & 0xfe00fff0) == 0xf4003500)
#define V2_32_IS_FSTMM(insn)           (((insn) & 0xfe00fff0) == 0xf4003600)
#define V2_32_FSTMSDM_REGNUM(insn)     (((insn) >> 16) & 0x1f)
#define V2_32_FSTMSDM_COUNT(insn)      ((((insn) >> 21) & 0xf) + 1)


/*********************************
 * 860 FLRW.T FLD.T  FST.T FLDR.T
 * FSTR.T FLDM.T FSTM.T
 *********************************/

/*********************************
 * FLRW.T
 *********************************/
#define V2_32_IS_FLRW_16(insn)            (((insn) & 0xfc00ff00) == 0xf4003b00)
#define V2_32_IS_FLRW_32(insn)            (((insn) & 0xfc00ff00) == 0xf4003800)
#define V2_32_IS_FLRW_64(insn)            (((insn) & 0xfc00ff00) == 0xf4003900)
#define V2_32_FLRW_T_REGNUM(insn)         (((insn) >> 16) & 0x1f)
#define V2_32_FLRW_T_OFFSET(insn)         (((((insn) >> 4) & 0xf) << 2) + ((((insn) >> 21) & 0xf) << 6))

/*********************************
 * FLD.T
 *********************************/
#define V2_32_IS_FLD_16(insn)            (((insn) & 0xfc00ff00) == 0xf4002300)
#define V2_32_IS_FLD_32(insn)            (((insn) & 0xfc00ff00) == 0xf4002000)
#define V2_32_IS_FLD_64(insn)            (((insn) & 0xfc00ff00) == 0xf4002100)
#define V2_32_FLD_T_REGNUM(insn)         (((insn) >> 16) & 0x1f)
#define V2_32_FLD_T_OFFSET(insn)         (((((insn) >> 4) & 0xf) << 2) + ((((insn) >> 21) & 0xf) << 6))

/*********************************
 * FLDR.T
 *********************************/
#define V2_32_IS_FLDR_32_0(insn)         (((insn) & 0xfc00ffe0) == 0xf4002800)
#define V2_32_IS_FLDR_32_1(insn)         (((insn) & 0xfc00ffe0) == 0xf4002820)
#define V2_32_IS_FLDR_32_2(insn)         (((insn) & 0xfc00ffe0) == 0xf4002840)
#define V2_32_IS_FLDR_32_3(insn)         (((insn) & 0xfc00ffe0) == 0xf4002860)
#define V2_32_IS_FLDR_64_0(insn)         (((insn) & 0xfc00ffe0) == 0xf4002900)
#define V2_32_IS_FLDR_64_1(insn)         (((insn) & 0xfc00ffe0) == 0xf4002920)
#define V2_32_IS_FLDR_64_2(insn)         (((insn) & 0xfc00ffe0) == 0xf4002940)
#define V2_32_IS_FLDR_64_3(insn)         (((insn) & 0xfc00ffe0) == 0xf4002960)
#define V2_32_FLDR_T_RX(insn)            (((insn) >> 16) & 0x1f)
#define V2_32_FLDR_T_RY(insn)            (((insn) >> 21) & 0x1f)

/*********************************
 * FLDMU.T
 *********************************/
#define V2_32_IS_FLDMU_16(insn)          (((insn) & 0xfc00ffe0) == 0xf4003380)
#define V2_32_IS_FLDMU_32(insn)          (((insn) & 0xfc00ffe0) == 0xf4003080)
#define V2_32_IS_FLDMU_64(insn)          (((insn) & 0xfe00ffe0) == 0xf4003180)
#define V2_32_FLDMU_T_REGNUM(insn)       (((insn) >> 16) & 0x1f)
#define V2_32_FLDMU_T_COUNT(insn)        ((((insn) >> 21) & 0xf) + 1)

/*********************************
 * FLDM.T
 *********************************/
#define V2_32_IS_FLDM_16(insn)           (((insn) & 0xfc00ffe0) == 0xf4003300)
#define V2_32_IS_FLDM_32(insn)           (((insn) & 0xfc00ffe0) == 0xf4003000)
#define V2_32_IS_FLDM_64(insn)           (((insn) & 0xfe00ffe0) == 0xf4003100)
#define V2_32_FLDM_T_REGNUM(insn)        (((insn) >> 16) & 0x1f)
#define V2_32_FLDM_T_COUNT(insn)         ((((insn) >> 21) & 0x1f) + 1)

/*********************************
 * FST.T
 *********************************/
#define V2_32_IS_FST_16(insn)            (((insn) & 0xfc00ff00) == 0xf4002700)
#define V2_32_IS_FST_32(insn)            (((insn) & 0xfc00ff00) == 0xf4002400)
#define V2_32_IS_FST_64(insn)            (((insn) & 0xfe00ff00) == 0xf4002500)
#define V2_32_FST_T_REGNUM(insn)         (((insn) >> 16) & 0x1f)
#define V2_32_FST_T_OFFSET(insn)         (((((insn) >> 4) & 0xf) << 2) + ((((insn) >> 21) & 0xf) << 6))

/*********************************
 * FSTR.T
 *********************************/
#define V2_32_IS_FSTR_32_0(insn)         (((insn) & 0xfc00ffe0) == 0xf4002c00)
#define V2_32_IS_FSTR_32_1(insn)         (((insn) & 0xfc00ffe0) == 0xf4002c20)
#define V2_32_IS_FSTR_32_2(insn)         (((insn) & 0xfc00ffe0) == 0xf4002c40)
#define V2_32_IS_FSTR_32_3(insn)         (((insn) & 0xfc00ffe0) == 0xf4002c60)
#define V2_32_IS_FSTR_64_0(insn)         (((insn) & 0xfc00ffe0) == 0xf4002d00)
#define V2_32_IS_FSTR_64_1(insn)         (((insn) & 0xfc00ffe0) == 0xf4002d20)
#define V2_32_IS_FSTR_64_2(insn)         (((insn) & 0xfc00ffe0) == 0xf4002d40)
#define V2_32_IS_FSTR_64_3(insn)         (((insn) & 0xfc00ffe0) == 0xf4002d60)
#define V2_32_FSTR_T_RX(insn)            (((insn) >> 16) & 0x1f)
#define V2_32_FSTR_T_RY(insn)            (((insn) >> 21) & 0x1f)

/*********************************
 * FSTMU.T
 *********************************/
#define V2_32_IS_FSTMU_16(insn)          (((insn) & 0xfc00ffe0) == 0xf4003780)
#define V2_32_IS_FSTMU_32(insn)          (((insn) & 0xfc00ffe0) == 0xf4003480)
#define V2_32_IS_FSTMU_64(insn)          (((insn) & 0xfe00ffe0) == 0xf4003580)
#define V2_32_FSTMU_T_REGNUM(insn)       (((insn) >> 16) & 0x1f)
#define V2_32_FSTMU_T_COUNT(insn)        ((((insn) >> 21) & 0x1f) + 1)

/*********************************
 * FSTM.T
 *********************************/
#define V2_32_IS_FSTM_16(insn)           (((insn) & 0xfc00ffe0) == 0xf4003700)
#define V2_32_IS_FSTM_32(insn)           (((insn) & 0xfe00ffe0) == 0xf4003400)
#define V2_32_IS_FSTM_64(insn)           (((insn) & 0xfc00ffe0) == 0xf4003500)
#define V2_32_FSTM_T_REGNUM(insn)        (((insn) >> 16) & 0x1f)
#define V2_32_FSTM_T_COUNT(insn)         ((((insn) >> 21) & 0x1f) + 1)


/*********************************
 * 860 805 Vector
 ********************************/

/*********************************
 * VLDRU.T.N
 *********************************/
#define V2_32_IS_VLDRU_T_N(insn)      (((insn) & 0xfc00ff00) == 0xf8002400)
#define V2_32_VLDRU_T_N_RX(insn)      (((insn) >> 16) & 0x1f)
#define V2_32_VLDRU_T_N_RY(insn)      (((insn) >> 21) & 0x1f)
#define V2_32_VLDRU_T_N_NUM(insn)     ((((insn) >> 6) & 0x3) + 1)
#define V2_32_VLDRU_T_N_SIZE(insn)    (1 << (((insn) >> 4) & 0x3))

/*********************************
 * VLDU.T.N
 ********************************/
#define V2_32_IS_VLDU_T_N(insn)      (((insn) & 0xffe0ff00) == 0xf8002000)
#define V2_32_VLDU_T_N_REGNUM(insn)  (((insn) >> 16) & 0x1f)
#define V2_32_VLDU_T_N_NUM(insn)     ((((insn) >> 6) & 0x3) + 1)
#define V2_32_VLDU_T_N_SIZE(insn)    (1 << (((insn) >> 4) & 0x3))

/*********************************
 * VLD.T.N
 ********************************/
#define V2_32_IS_VLD_T_N(insn)       (((insn) & 0xfc00fc00) == 0xf8003000)
#define V2_32_VLD_T_N_REGNUM(insn)   (((insn) >> 16) & 0x1f)
#define V2_32_VLD_T_N_NUM(insn)      ((((insn) >> 6) & 0x3) + 1)
#define V2_32_VLD_T_N_SIZE(insn)     (1 << (((insn) >> 4) & 0x3))
#define V2_32_VLD_T_N_OFFSET(insn)   (((((insn) >> 21) & 0x1f) << 2) + (((insn) >> 8) & 0x3))

/*********************************
  * VLDX.T
  ********************************/
#define V2_32_IS_VLDX_T_N(insn)      (((insn) & 0xfc00ffc0) == 0xf8002500)
#define V2_32_VLDX_T_N_RX(insn)      (((insn) >> 16) & 0x1f)
#define V2_32_VLDX_T_N_RY(insn)      (((insn) >> 21) & 0x1f)
#define V2_32_VLDX_T_N_SIZE(insn)    (1 << (((insn) >> 4) & 0x3))

/*********************************
 * VLRW.T.N
 ********************************/
#define V2_32_IS_VLRW_32_N(insn)      (((insn) & 0xfc00fc30) == 0xf8003420)
#define V2_32_VLRW_32_N_NUM(insn)     ((((insn) >> 6) & 0x3) + 1)
#define V2_32_VLRW_32_N_IMM(insn)     (((((insn) >> 8) & 0x3) << 2) + ((((insn) >> 16) & 0x1f) << 4))

/*********************************
 * VLDMU.T
 ********************************/
#define V2_32_IS_VLDMU_T(insn)        (((insn) & 0xffe0ff00) == 0xf8002200)
#define V2_32_VLDMU_T_REGNUM(insn)    (((insn) >> 16) & 0x1f)
#define V2_32_VLDMU_T_SIZE(insn)      (1 << (((insn) >> 4) & 0x3))
#define V2_32_VLDMU_T_COUNT(insn)     ((((insn) >> 6) & 0x3) + 1)

/*********************************
 * VLDMRU.T
 ********************************/
#define V2_32_IS_VLDMRU_T(insn)        (((insn) & 0xffe0ff00) == 0xf8002600)
#define V2_32_VLDMRU_T_RX(insn)        (((insn) >> 16) & 0x1f)
#define V2_32_VLDMRU_T_RY(insn)        (((insn) >> 21) & 0x1f)
#define V2_32_VLDMRU_T_SIZE(insn)      (1 << (((insn) >> 4) & 0x3))
#define V2_32_VLDMRU_T_COUNT(insn)     ((((insn) >> 6) & 0x3) + 1)

/*********************************
 * VLDM.T
 ********************************/
#define V2_32_IS_VLDM_T(insn)        (((insn) & 0xffe0ff00) == 0xf8002300)
#define V2_32_VLDM_T_REGNUM(insn)    (((insn) >> 16) & 0x1f)
#define V2_32_VLDM_T_SIZE(insn)      (1 << (((insn) >> 4) & 0x3))
#define V2_32_VLDM_T_COUNT(insn)     ((((insn) >> 6) & 0x3) + 1)

/*********************************
 * VSTRU.T.N
 ********************************/
#define V2_32_IS_VSTRU_T_N(insn)     (((insn) & 0xfe00ff00) == 0xf8002c00)
#define V2_32_VSTRU_T_N_RX(insn)     (((insn) >> 16) & 0x1f)
#define V2_32_VSTRU_T_N_RY(insn)     (((insn) >> 21) & 0x1f)
#define V2_32_VSTRU_T_N_SIZE(insn)   (1 << (((insn) >> 4) & 0x3))
#define V2_32_VSTRU_T_N_NUM(insn)    ((((insn) >> 6) & 0x3) + 1)

/*********************************
 * VSTU.T.N
 ********************************/
#define V2_32_IS_VSTU_T_N(insn)      (((insn) & 0xffe0ff00) == 0xf8002800)
#define V2_32_VSTU_T_REGNUM(insn)    (((insn) >> 16) & 0x1f)
#define V2_32_VSTU_T_SIZE(insn)      (1 << (((insn) >> 4) & 0x3))
#define V2_32_VSTU_T_COUNT(insn)     ((((insn) >> 6) & 0x3) + 1)

/*********************************
 * VST.T.N
 ********************************/
#define V2_32_IS_VST_T_N(insn)      (((insn) & 0xfc00fc00) == 0xf8003800)
#define V2_32_VST_T_REGNUM(insn)    (((insn) >> 16) & 0x1f)
#define V2_32_VST_T_SIZE(insn)      (1 << (((insn) >> 4) & 0x3))
#define V2_32_VST_T_COUNT(insn)     ((((insn) >> 6) & 0x3) + 1)
#define V2_32_VST_T_IMM(insn)       ((((insn) >> 8) & 0x3) + ((((insn) >> 21) & 0x1f) << 2))

/*********************************
 * VSTX.T
 ********************************/
#define V2_32_IS_VSTX_T(insn)        (((insn) & 0xfc00ffc0) == 0xf8002d00)
#define V2_32_VSTX_T_RX(insn)        (((insn) >> 16) & 0x1f)
#define V2_32_VSTX_T_RY(insn)        (((insn) >> 21) & 0x1f)
#define V2_32_VSTX_T_SIZE(insn)      (1 << (((insn) >> 4) & 0x3))

/*********************************
 * VSTMU.T
 ********************************/
#define V2_32_IS_VSTMU_T_N(insn)      (((insn) & 0xffe0ff00) == 0xf8002a00)
#define V2_32_VSTMU_T_REGNUM(insn)    (((insn) >> 16) & 0x1f)
#define V2_32_VSTMU_T_SIZE(insn)      (1 << (((insn) >> 4) & 0x3))
#define V2_32_VSTMU_T_IMM(insn)       ((((insn) >> 6) & 0x3) + 1)

/*********************************
 * VSTMRU.T
 ********************************/
#define V2_32_IS_VSTMRU_T_N(insn)      (((insn) & 0xffe0ff00) == 0xf8002e00)
#define V2_32_VSTMRU_T_RX(insn)        (((insn) >> 16) & 0x1f)
#define V2_32_VSTMRU_T_RY(insn)        (((insn) >> 21) & 0x1f)
#define V2_32_VSTMRU_T_SIZE(insn)      (1 << (((insn) >> 4) & 0x3))
#define V2_32_VSTMRU_T_IMM(insn)       ((((insn) >> 6) & 0x3) + 1)

/*********************************
 * VSTM.T
 ********************************/
#define V2_32_IS_VSTM_T_N(insn)      (((insn) & 0xffe0ff00) == 0xf8002b00)
#define V2_32_VSTM_T_REGNUM(insn)    (((insn) >> 16) & 0x1f)
#define V2_32_VSTM_T_SIZE(insn)      (1 << (((insn) >> 4) & 0x3))
#define V2_32_VSTM_T_IMM(insn)       ((((insn) >> 6) & 0x3) + 1)

 /*********************************
 * 810
 ********************************/

/*********************************
 * VLDD
 ********************************/
#define V2_32_IS_VLDD_T(insn)         (((insn) & 0xfe00fc00) == 0xf8002000)
#define V2_32_VLDD_T_REGNUM(insn)     (((insn) >> 16) & 0x1f)
#define V2_32_VLDD_T_SIZE(insn)       (((insn) >> 8) & 0x3)
#define V2_32_VLDD_T_OFFSET(insn)     (((((insn) >> 4) & 0xf) << 3) + ((((insn) >> 21) & 0xf) << 7))

/*********************************
 * VLDQ
 *********************************/
#define V2_32_IS_VLDQ_T(insn)         (((insn) & 0xfe00fc00) == 0xf8002400)
#define V2_32_VLDQ_T_REGNUM(insn)     (((insn) >> 16) & 0x1f)
#define V2_32_VLDQ_T_SIZE(insn)       (((insn) >> 8) & 0x3)
#define V2_32_VLDQ_T_OFFSET(insn)     (((((insn) >> 4) & 0xf) << 4) + ((((insn) >> 21) & 0xf) << 8))

/*********************************
 * VLDRD
 *********************************/
#define V2_32_IS_VLDRD0_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003000)
#define V2_32_IS_VLDRD1_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003020)
#define V2_32_IS_VLDRD2_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003040)
#define V2_32_IS_VLDRD3_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003060)
#define V2_32_VLDRD_T_RX(insn)        (((insn) >> 16) & 0x1f)
#define V2_32_VLDRD_T_RY(insn)        (((insn) >> 21) & 0x1f)
#define V2_32_VLDRD_T_SIZE(insn)      (((insn) >> 8) & 0x3)

/*********************************
 * VLDRQ
 *********************************/
#define V2_32_IS_VLDRQ0_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003400)
#define V2_32_IS_VLDRQ1_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003420)
#define V2_32_IS_VLDRQ2_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003440)
#define V2_32_IS_VLDRQ3_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003460)
#define V2_32_VLDRQ_T_RX(insn)        (((insn) >> 16) & 0x1f)
#define V2_32_VLDRQ_T_RY(insn)        (((insn) >> 21) & 0x1f)
#define V2_32_VLDRQ_T_SIZE(insn)      (((insn) >> 8) & 0x3)

/*********************************
 * VSTD
 *********************************/
#define V2_32_IS_VSTD_T(insn)         (((insn) & 0xfe00fc00) == 0xf8002800)
#define V2_32_VSTD_T_REGNUM(insn)     (((insn) >> 16) & 0x1f)
#define V2_32_VSTD_T_SIZE(insn)       (((insn) >> 8) & 0x3)
#define V2_32_VSTD_T_OFFSET(insn)     (((((insn) >> 4) & 0xf) << 3) + ((((insn) >> 21) & 0xf) << 7))

/*********************************
 * VSTQ
 *********************************/
#define V2_32_IS_VSTQ_T(insn)         (((insn) & 0xfe00fc00) == 0xf8002c00)
#define V2_32_VSTQ_T_REGNUM(insn)     (((insn) >> 16) & 0x1f)
#define V2_32_VSTQ_T_SIZE(insn)       (((insn) >> 8) & 0x3)
#define V2_32_VSTQ_T_OFFSET(insn)     (((((insn) >> 4) & 0xf) << 4) + ((((insn) >> 21) & 0xf) << 8))

/*********************************
 * VSTRD
 *********************************/
#define V2_32_IS_VSTRD0_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003800)
#define V2_32_IS_VSTRD1_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003820)
#define V2_32_IS_VSTRD2_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003840)
#define V2_32_IS_VSTRD3_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003860)
#define V2_32_VSTRD_T_RX(insn)        (((insn) >> 16) & 0x1f)
#define V2_32_VSTRD_T_RY(insn)        (((insn) >> 21) & 0x1f)
#define V2_32_VSTRD_T_SIZE(insn)      (((insn) >> 8) & 0x3)

/*********************************
 * VSTRQ
 *********************************/
#define V2_32_IS_VSTRQ0_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003c00)
#define V2_32_IS_VSTRQ1_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003c20)
#define V2_32_IS_VSTRQ2_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003c40)
#define V2_32_IS_VSTRQ3_T(insn)       (((insn) & 0xfe00fcf0) == 0xf8003c60)
#define V2_32_VSTRQ_T_RX(insn)        (((insn) >> 16) & 0x1f)
#define V2_32_VSTRQ_T_RY(insn)        (((insn) >> 21) & 0x1f)
#define V2_32_VSTRQ_T_SIZE(insn)      (((insn) >> 8) & 0x3)

/* For spilt hardware_version.  */
#define HW_PROXY_MAIN_VER(hardware_version) (((hardware_version) >> 24) & 0xff)
#define HW_PROXY_SUB VER(hardware_version)  (((hardware_version) >> 16) & 0xff)
#define HW_ICE_MAIN_VER(hardware_version)   (((hardware_version) >> 8)  & 0x3f)
#define HW_ICE_SUB_VER(hardware_version)    ((hardware_version) & 0xff)

/* For csky tdesc xml.  */
#define CSKY_PSEUDO_FEATURE_NAME        "org.gnu.csky.pseudo"
#define CSKY_ABIV1_FEATURE_NAME_PREFIX  "org.gnu.csky.abiv1"
#define CSKY_ABIV2_FEATURE_NAME_PREFIX  "org.gnu.csky.abiv2"
#define CSKY_FEATURE_NAME_PREFIX_LENGTH  18

#define CSKY_CRBANK_NUM_REGS 32
#define CSKY_ABIV1_NUM_REGS 159
#define CSKY_ABIV2_XML10_NUM_REGS 1171

/*  Macro for abiv2.  */
#define CSKY_SP_REGNUM_V2 14

/*  Macro for abiv1.  */
#define CSKY_SP_REGNUM_V1 0

/* TEE debug */
#define CSKY_REE 0
#define CSKY_TEE 1

#define TEE_MASK 0x40000000
#define REE_MASK 0xbfffffff

#define TEE_DEBUG_EN(dcr)  ((dcr) & 0x2)
#define REE_DEBUG_EN(dcr)  ((dcr) & 0x1)

#define EXEC_ENV_IS_TEE(psr)  ((psr) & 0x40000000)

#endif 
