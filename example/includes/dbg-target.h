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

#ifndef __DEBUGGER_SERVER_INCLUDE_TARGET_H__
#define __DEBUGGER_SERVER_INCLUDE_TARGET_H__

#if defined (_WIN32) && !defined (__CYGWIN)
#ifdef TARGET_EXPORTS
#define TARGET_API __declspec(dllexport)
#else
#define TARGET_API __declspec(dllimport)
#endif /* TARGET_EXPORTS */
#else
#define TARGET_API
#endif /* _WIN32 && !__CYGWIN */

/* TODO: linux/windows may be different.  */
#ifndef _WIN32
#include <semaphore.h>
#else    /* _WIN32 */
#include <windows.h>
#endif   /* _WIN32 */

#include "dbg-cfg.h"
#include "regType.h"
#include "dataType.h"
#include "link.h"

#if defined _WIN32 && !defined (__CYGWIN) 
#define SLEEP_S(count) Sleep((count)*1000)

#define LOCK    EnterCriticalSection
#define UNLOCK  LeaveCriticalSection

#define WAITFOR_UNTIL(sema)		      WaitForSingleObject(sema, INFINITE)
#define WAITFOR_TIMM(sema)		      WaitForSingleObject(sema, 0)
#define WAITFOR_TWOSEC(sema, tsec)    WaitForSingleObject(sema, 2000)
#define WAKEUP(sema)			      !ReleaseSemaphore(sema,1,0)

#define semVar HANDLE

#else

#define SLEEP_S(count)  sleep(count)

#define LOCK    pthread_mutex_lock
#define UNLOCK  pthread_mutex_unlock

#define WAITFOR_UNTIL(sema)		    sem_wait(&(sema))
#define WAITFOR_TIMM(sema)		    sem_trywait(&(sema))
#define WAITFOR_TWOSEC(sema, tsec)	sem_timedwait(&(sema), &(tsec))
#define WAKEUP(sema)			    sem_post(&(sema))

#define semVar  sem_t

#endif /* _WIN32 & !__CYGWIN */

//CLK
#define HAD_READ_HSR16_CLK     37
#define HAD_READ_HSR32_CLK     53
#define HAD_READ_PCFIFO32_CLK  53
#define HAD_READ_PCFIFO64_CLK  93

#define DM_READ_DMSTATUS_CLK   174
#define DM_PCSAMPLING_32_CLK   174
#define DM_PCSAMPLING_64_CLK   282

#define HAD_CDI_J5_V  0xFFFFFFFF
#define HAD_CDI_J5    0
#define HAD_CDI_J2    1
#define HAD_CDI_NULL  0xff

#define MAX_CPU_COUNT 32

#ifdef __cplusplus
extern "C" {
#endif

/// definition for debug operations.
typedef struct debug_operation debug_operation_t;

/*----- Breakpoint types ------*/
enum bkpt_type
{
    BKPT_SOFT = 0,      ///< Soft-Breakpoint
    BKPT_HARD,          ///< Hard-Breakpoint
	BKPT_FLASH,         ///< Flash-Breakpoint
	BKPT_SIM,           ///< Simulater-Breakpoint
	BKPT_DEL,           ///< Delete-Breakpoint
};

/*----- Watchpoint types ------*/
enum watchpoint_type
{
    WPT_WRITE = 2,      ///< Write-Watchpoint
    WPT_READ,           ///< Read-Watchpoint
    WPT_ACCESS          ///< Access-Watchpoint
};

/*----- Target message type -----*/
enum target_message_type
{
  TARGET_MSG_ARCH_NAME = 1, ///< Name of architecture
  TARGET_MSG_CPU_NAME,      ///< Name of CPU
  TARGET_MSG_PIPE_INFO,     ///< Pipe informations, Only in C960
  TARGET_MSG_DEBUG_INFO,    ///< Debug informations, Only in C960
};

/* NOTICE: It is not used yet.  */
/*----- Target state -----*/
enum target_state
{
    TARGET_UNKNOWN = 0,     ///< Unknown state
    TARGET_RUNNING = 1,     ///< Target is running
    TARGET_HALTED = 2,      ///< Target is halted
    TARGET_RESET = 3,       ///< Target is reset
    TARGET_DEBUG_RUNNING = 4, ///< Target is debug-running
};

/*----- The reason of debug -----*/
enum target_debug_reason
{
    DBG_REASON_DBGRQ = 0,   ///< Debug request, Such as CTRL-C in gdb
    DBG_REASON_BREAKPOINT,  ///< Caused by breakpoint
    DBG_REASON_WATCHPOINT,  ///< Caused by watchpoint
    DBG_REASON_SINGLESTEP,  ///< Caused by singleStep
    DBG_REASON_RUNNING,     ///< Target is Running, not in debug mode
    DBG_REASON_FILEIO,      ///< Caused by semihosting
    DBG_REASON_PRO,         ///< Caused by other cores
	DBG_REASON_SIMBP,       ///< Caused by a flash simulate bp
    DBG_REASON_UNDEFINED,   ///< Undefined
};

/*----- The status of debug communication -----*/
enum target_dcomm_status
{
    TARGET_DCOMM_CAN_READ = 1,  ///< Debug communication can be read
    TARGET_DCOMM_CAN_WRITE,     ///< Debug communication can be written
    TARGET_DCOMM_CAN_RDWR,      ///< Debug communication can be read or written
};

/*----- The endian of target -----*/
enum target_endian
{
    ENDIAN_LITTLE = 0,      ///< Little endian
    ENDIAN_BIG    = 1,      ///< Big endian
    ENDIAN_BIG_V1 = 1,      ///< CSKY big endian v1
    ENDIAN_BIG_V2 = 2,      ///< CSKY big endian v2
};

/*---- The type for TARGET_CONFIG_CONTINUOUS_MEM_OPERATION ----*/
enum target_continuous_mem_op_state
{
	TARGET_CONTINUOUS_MEM_OPERATION_START,
	TARGET_CONTINUOUS_MEM_OPERATION_END,
};

/*----- The type for TARGET_CONFIG_MEM_MAX_MODE -----*/
enum TARGET_MEM_ACCESS_MAX_MODE {
	MEM_ACCESS_MODE_DWORD = 0,
	MEM_ACCESS_MODE_WORD,
	MEM_ACCESS_MODE_HWORD,
	MEM_ACCESS_MODE_BYTE
};

/*----- The type for config the target -----*/
enum target_config_type
{
	TARGET_CONFIG_BKPT_EXCEPTION = 0,          ///<control whether set FDB when resuming the target
	TARGET_CONFIG_MEM_ACCESS_MODE,             ///<config mem-access mode  progbuf,abstract cmd/sysbus (only riscv dm)
	TARGET_CONFIG_DM_BASE,                     ///<config dm base
	TARGET_CONFIG_CONTINUOUS_MEM_OPERATION,    ///<set the start and end for continuous mem operations
	TARGET_CONFIG_PC_SAMPLING,                 ///<the PC sampling frequence/start/stop
	TARGET_CONFIG_VIRTUAL_MEM_ACCESS_MODE,     ///<config virtual mem access mode, riscv
	TARGET_CONFIG_PC_SAMPLING_MODE,            ///<config virtual mem access mode, riscv
	TARGET_CONFIG_MEM_MAX_MODE,                ///<config the max mode for mem access
	TARGET_CONFIG_HACR_WIDTH,                  ///<config the hacr width for HAD
	TARGET_CONFIG_SELECT_TO_HADTOP,            ///<config current module to HAD TOP
};

/*----- The type for config the target -----*/
enum target_riscv_mem_access_mode
{
	RV_MEM_ACCESS_PROGBUF = 0,  ///< DEBUG_ARCH_RISCV access mem via PB
	RV_MEM_ACCESS_ABSCMD,  ///< DEBUG_ARCH_RISCV access mem via ABSCDM
	RV_MEM_ACCESS_SYSBUS   ///< DEBUG_ARCH_RISCV access mem via SYSBUS
};

/*----- The type for TARGET_CPU_ARCH -----*/
enum taret_cpu_arch_type
{
	CPU_ARCH_UNKNOWN = 0,
	CPU_ARCH_TH5XX,
	CPU_ARCH_TH8XX,
	CPU_ARCH_RV32,
	CPU_ARCH_RV64
};

/*----- The type for get the target configuration -----*/
enum target_get_config_type
{
	TARGET_GET_PCFIFO_SUPPORT = 0,   ///<get whether the target supports PCFIFO
	TARGET_GET_DBGINFO_SUPPORT,      ///<get whether the target supports DBGINFO
	TAREGT_GET_THEAD_RVDM,           ///<get whether the target is rvdm with thead implementation
	TARGET_GET_GROUP_COUNT,          ///<get group count
	TARGET_GET_GROUP_CPU_COUNT,      ///<get group cpu count
	TARGET_GET_GROUP_ELEMENTS,       ///<get group elements
	TARGET_GET_GROUP_CPU_CUR,        ///<get group cpu_cur
	TARGET_GET_GROUP_CUR,            ///<get group cur
	TAREGT_GET_RVDM_BASE,            ///<get dm base
	TARGET_GET_SAMMPLING_SUPPORT,    ///<get sampling supported
	//feature: one-hot decoded: bit[0], PC Sampling supported by host
	//                          bit[1], ConetextID Sampling supported by host
	//                          bit[2], PC Sampling supported by link
	//                          bit[3], ConetextID Sampling supported by link
	TARGET_GET_CPUID,                ///<get cpuid of the current cpu
	TARGET_GET_CPUNAME,              ///<get cpuname of the current cpu
	TARGET_GET_PC_SAMPLING,          ///<get pc sampling
	TARGET_GET_CONTEXTID_SAMPLING,   ///<get context id sampling
	TARGET_GET_CPU_N_STATE,          ///<get state of cpu_n(enum target_state)
	TARGET_GET_XLEN,                 ///<get xlen of the current cpu
	TARGET_GET_VIRTUAL_MEM_ACCESS_MODE, ///<get virtual mem access mode, riscv
	TARGET_GET_IS_ASYNC_ENTER_DEBUG,    ///<get whether the current cpu entered debug mode by async mode
	TARGET_GET_CPU_ARCH,                ///<get cpu architecture
	TARGET_GET_INSN_LEN,                ///<get an insn length, 2-bytes or 4-bytes
	TARGET_GET_BKPT_INSN,               ///<get 16-bits or 32-bits software breakpoint instruction
};

/*----- The type for sampling feature -----*/
enum target_sampling_featue_one_hot_decode
{
	TARGET_PC_SAMPLING_FEATURE = 1,
	TARGET_CONTEXTID_SAMPLING_FEATURE = 2,
	TARGET_PC_SAMPLING_FEATURE_LINK = 4,
	TARGET_CONTEXTID_SAMPLING_FEATURE_LINK = 8,
};

/*--------- Reset type ----------*/
enum target_reset_type
{
	RESET_TYPE_SOFT = 0,
	RESET_TYPE_HARD = 1,
	RESET_TYPE_NRESET = 2,
	RESET_TYPE_SOFT_HALT = 3,
	RESET_TYPE_HARD_HALT = 4,
};

/**
\brief The struct of breakpoint
*/
struct breakpoint
{
    U64 address;                ///< The address of breakpoint
    unsigned int length;        ///< The length of breakpoint, it shoud be 2 or 4
    enum bkpt_type type;        ///< The type of breakpoint, Hard or Soft
    unsigned int orig_instr;    ///< Origin instruction opcode.
    int index;                  ///< Hard bkpt index.
	int set;                    ///< Set or not, whether this bkpt is in the target
	int gdb_set;                ///< Whether gdb keep this bkpt's state is inserted or not

	/// add for flash-breakpoint
	int type_adjusted;          ///< For FlashBp, HB or FlashBp
	int is_new;                 ///< For FlashBp, a new FlashBp
	U64 sector_id;              ///< For FlashBp, the sector id for address
	int sim_type;               ///< For FlashBp, a insn simulate FlashBp

    struct breakpoint *next;    ///< Next breakpoint
};

/**
\brief The struct of watchpoint
*/
struct watchpoint
{
    U64 address;                ///< The address of watchpoint
    unsigned int length;        ///< The length of watchpoint
    unsigned int mask;          ///< The mask of the watchpoint
    unsigned int value;         ///< The value of watchpoint(NOTICE: unused)
    enum watchpoint_type rw;    ///< The type of the watchpoint
    int set;                    ///< Set or not, it is a status of the watchpoint
    int index;                  ///< Hard bkpt index.
    struct watchpoint *next;    ///< Next watchpoint
};

/**
\brief The information of file-io(Semihosting)
*/
struct gdb_fileio_info
{
    char *identifier;       ///< A string means the operations
    U64 param_1;            ///< Parameter 1
    U64 param_2;            ///< Parameter 2
    U64 param_3;            ///< Parameter 3
    U64 param_4;            ///< Parameter 4
};

/**
\brief The informations of halt
*/
struct halt_info
{
    enum target_debug_reason reason;    ///< Debug reason
    U64 addr;                           ///< Current PC
	int addr_len;                       ///< Address length
    unsigned int current_cpu;           ///< Current cpu
    unsigned int status;                ///< The value of HSR/DCSR
	unsigned int status2;               ///< The value of MHaltcause
    union {
        struct gdb_fileio_info fileio;  ///< File-I/O information for host to do syscall
        /* TODO: add watchpoint info. */
    } data;
};

/*----- The type of register -----*/
enum register_type {
    REGISTER_TYPE_GR = 1,   ///< General register
    REGISTER_TYPE_CR,       ///< CPU control and status register
    REGISTER_TYPE_FR,       ///< Floating register
    REGISTER_TYPE_VR,       ///< Vector register
    REGISTER_TYPE_HAD,      ///< HAD register
    REGISTER_TYPE_RV,       ///< RISCV control and status register
    REGISTER_TYPE_DM,       ///< RISCV DM register
};

/**
\brief register define
*/
struct reg
{
    char name[32];              ///< Name of register
    int num;                    ///< Register number
    enum register_type type;    ///< Register type.
    int length;                 ///< Register length
    union {
        unsigned char val8;
        unsigned short val16;
        unsigned int val32;
        U64 val64;
        float valf;
        double vald;
        unsigned char raw[128];
    }value;                     ///< Value of register
};

/**
\brief Target interface version
*/
struct target_version
{
	int target_main_version;    ///< main version
	int target_sub_version;     ///< sub version
	char *op_type;              ///< the type of op intefaces
	int op_main_version;        ///< the main version of op intefaces
	int op_sub_version;         ///< the sub version of op intefaces
};

/**
\brief Args for TARGET_GET_PC_SAMPLING
*/
enum pc_sampling_cmd
{
	PC_SAMPLING_NONE,       ///< None
	PC_SAMPLING_INFO,       ///< Get Buffer size, arg is a integer point
	PC_SAMPLING_SETUP,      ///< Setup the CPU and time(ms), arg is
	PC_SAMPLING_START,      ///< Start PC Sampling
	PC_SAMPLING_STOP,       ///< Stop PC Sampling
	PC_SAMPLING_DUMP,       ///< Dump PC from pc buffer
};

union pc_sampling_arg
{
	uint32_t reserved;           ///< no needed for START/STOP
	uint32_t *buffer_size;       ///< arg for INFO
	struct {
		int cpu;                 ///< the CPU
		uint32_t freq;              ///< Sampling frequence @Hz
	} setup_info;                ///< arg for SETUP
	struct {
		uint32_t buff_size;
		uint32_t *pc_count;
		uint32_t *pc_buffer;
	}dump_buff;                  ///< arg for DUMP
};

struct target_pc_sampling_arg
{
	enum pc_sampling_cmd cmd;
	union pc_sampling_arg arg;
};

#ifndef __CDK_DBUGGER_INTERFACE_H__

/* The interface of target connections.  */
/**
  \brief        Initialize target interfaces
  \param[in]    cfg,debug server config
  \return       awaly return 0
*/
TARGET_API int target_init (dbg_server_cfg_t *cfg);

/**
  \brief        Open target
                1. Connect to cklink
                2. Connect to HAD or DM
                3. Connect to CPU
                4. Do some pre-operations
  \param[in]    debug server config
  \return       A handle(an address comes from malloc) for success, otherwise return NULL
*/
TARGET_API struct target *target_open (dbg_server_cfg_t *cfg);

/**
  \brief        Close target
                1. Clear to breakpoints and watchpoints
                2. Disconnect cklink
                3. free target
  \param[in]    tgt the handle of target
  \return       0 for seccuss, negative for error
*/
TARGET_API int target_close (struct target *tgt);

/**
  \brief        De-initialize target interfaces (NOTICE: Do nothing yet)
  \return       For now, do nothing, always return 0
*/
TARGET_API int target_uninit (void);

/* Target Infomations.  */
/**
  \brief        Get arch informations as a string (NOTICE: It not is implemented)
  \param[in]    tgt, the handle of target
  \return       a string contains the arch informations
*/
TARGET_API const char *target_get_arch_info (struct target *tgt);

/**
  \brief        Check whether CKLINK is connected or not
  \param[in]    tgt, the handle of target
  \return       non-zero if CKLINK has been connected, otherwise return 0
*/
TARGET_API int target_is_ice_connected (struct target *tgt);

/**
  \brief        Check whether target is connected or not
  \param[in]    tgt, the handle of target
  \return       non-zero if target has been connected, otherwise return 0
*/
TARGET_API int target_is_connected (struct target *tgt);

/**
  \brief        Check whether target is (multi-cpus or multi-cores) or not
  \param[in]    tgt, the handle of target
  \return       non-zero if target is (multi-cpus or multi-cores), otherwise return 0
*/
TARGET_API int target_is_multi_cpu (struct target *tgt);

/**
  \brief        Get HAD version
  \param[in]    tgt, the handle of target
  \return       verison of had,
                HAD_V1 -------- 0
                HAD_V2 -------- 1
                HAD_V3 -------- 2
                HAD_V4 -------- 3
                HAD_V5 -------- 4
                HAD_V6 -------- 5
*/
TARGET_API int target_get_had_version(struct target *tgt);

/**
  \brief        Get CPU count
  \param[in]    tgt, the handle of target
  \return       the count of cpus
*/
TARGET_API int target_get_cpu_count (struct target *tgt);

/**
  \brief        Check whether the cpu is available
  \param[in]    tgt, the handle of target
  \param[in]    cpu, the index of cpu
  \return       non-zero if cpu available, otherwise 0
*/
TARGET_API int target_is_cpu_available (struct target *tgt, int cpu);

/**
  \brief        Get index of current CPU
  \param[in]    tgt the handle of target
  \return       The index of current CPU
*/
TARGET_API int target_get_current_cpu (struct target *tgt);

/**
  \brief        Get CPU name which specified by cpu
  \param[in]    tgt, the handle of target
  \param[in]    cpu, the index of cpu
  \return       a point which contains the cpu name, if the cpu does't existed, return NULL.
*/
TARGET_API const char *target_get_cpu_name (struct target *tgt, int cpu);

/**
  \brief        Get contents of target description file
  \param[in]    tgt, the handle of target
  \return       a point which contains the contents of target description,
                if target does't have tdesc file, return NULL
*/
TARGET_API const char *target_get_cpu_tdesc_content (struct target *tgt);

/**
  \brief        Get length of target description file
  \param[in]    tgt, the handle of target
  \return       The length of target description file,
                if target does't have tdesc file, return 0
*/
TARGET_API int target_get_cpu_tdesc_length (struct target *tgt);

/**
  \brief        Get endian of target
  \param[in]    tgt, the handle of target
  \return       The endian of target
*/
TARGET_API int target_get_endian (struct target *tgt);

/**
  \brief        Get count of hardware breakpoints
  \param[in]    tgt, the handle of target
  \return       The count of hardware breakpoints
*/
TARGET_API int target_get_max_hw_breakpoint (struct target *tgt);

/**
  \brief        Get count of watchpoints
  \param[in]    tgt, the handle of target
  \return       The count of watchpoints
*/
TARGET_API int target_get_max_watchpoint (struct target *tgt);

/* Debug operations.  */
/**
  \brief        check target is multi cores
  \param[in]    tgt, the handle of target
  \return       non-zero for target is multi cores. Return zero while target is not multi-cores
*/
TARGET_API int target_is_multi_cores_and_threads(struct target *tgt);

/**
  \brief        Enable or disable cachce flush while doing single-step or resuming
  \param[in]    tgt, the handle of target
  \param[in]    en, bool type, enable(1) or disable(0)
  \return       zero for success, negative for error
*/
TARGET_API int target_enable_cache_flush (struct target *tgt, int en);

/**
  \brief        Resume the target
  \param[in]    tgt, the handle of target
  \return       zero for success, negative for error
*/
TARGET_API int target_resume (struct target *tgt);

/**
  \brief        Halt the target
  \param[in]    tgt, the handle of target
  \return       zero for success, negative for error
*/
TARGET_API int target_halt (struct target *tgt);

/**
  \brief        Do Single step
  \param[in]    tgt, the handle of target
  \return       zero for success, negative for error
*/
TARGET_API int target_single_step (struct target *tgt);

/**
  \brief        Get the state of target
  \param[in]    tgt, the handle of target
  \param[in]    state, HSR for HAD; DCSR for RVDM
  \return       zero for success, negative for error
*/
TARGET_API int target_get_state (struct target *tgt, int *state);

/**
  \brief        Reset target
  \param[in]    tgt, the handle of target
  \param[in]    type, 2, nreset, 1 hard, 0, software
  \param[in]    data, unused
  \return       zero for success, negative for error
*/
TARGET_API int target_reset (struct target *tgt, int type, void *data);

/**
  \brief        Select the cpu which specified with cpu
  \param[in]    tgt, the handle of target
  \param[in]    cpu, the index of cpu which need to be selected
  \return       zero for success, negative for error
*/
TARGET_API int target_select_cpu (struct target *tgt, int cpu);

/**
  \brief        Get pctrace of the target (NOTICE: not implemented)
  \param[in]    tgt, the handle of target
  \return       zero for success, negative for error
*/
TARGET_API int target_pctrace (struct target *tgt);


/* Get all Register ot list. It will malloc memory.  */
/**
  \brief        Get register number from name
  \param[in]    tgt, the handle of target
  \param[in]    str, the string contains register name
  \param[out]   end, save the end of register name in the str
  \param[out]   reg, save the register number, name, length, type
  \return       zero for success, negative for error
*/
TARGET_API int target_get_regno_from_name (struct target *tgt, char *str, char **end, struct reg *reg);

/**
  \brief        Get register list
  \param[in]    tgt, the handle of target
  \param[out]   reg_list, a point contains a point which will be pointed to the reg list
  \param[out]   psize, a point which will be saved to reg list count
  \return       zero for success, negative for error
*/
TARGET_API int target_get_register_list (struct target *tgt,
                                                 struct reg ** reg_list,
                                                 int *psize);
/**
  \brief        Read cpu register
  \param[in]    tgt, the handle of target
  \param[out]   reg, save the register number, name, length, type, value,
                the number must set before calling the function
  \return       zero for success, negative for error
*/
TARGET_API int target_read_cpu_reg (struct target *tgt, struct reg *reg);

/**
  \brief        write cpu register
  \param[in]    tgt, the handle of target
  \param[out]   reg, reigster to be written,
                the number and value must set before calling the function
  \return       zero for success, negative for error
*/
TARGET_API int target_write_cpu_reg (struct target *tgt, struct reg const *reg);

/**
  \brief        Read ICE(CKLINK) register
  \param[in]    tgt, the handle of target
  \param[out]   reg, save the register number, name, length, type, value,
                the number must set before calling the function
  \return       zero for success, negative for error
*/
TARGET_API int target_read_ice_reg (struct target *tgt, struct reg *reg);

/**
  \brief        Write ICE(CKLINK) register
  \param[in]    tgt, the handle of target
  \param[out]   reg, reigster to be written,
                the number and value must set before calling the function
  \return       zero for success, negative for error
*/
TARGET_API int target_write_ice_reg (struct target *tgt, struct reg const *reg);

/**
  \brief        Read HAD register
  \param[in]    tgt, the handle of target
  \param[out]   reg, save the register number, name, length, type, value,
                the number must set before calling the function
  \return       zero for success, negative for error
*/
TARGET_API int target_read_had_reg (struct target *tgt, struct reg *reg);

/**
  \brief        Write HAD register
  \param[in]    tgt, the handle of target
  \param[out]   reg, reigster to be written,
                the number and value must set before calling the function
  \return       zero for success, negative for error
*/
TARGET_API int target_write_had_reg (struct target *tgt, struct reg const *reg);

/**
  \brief        Read HAD CPU SCR register(NOTICE: only for csky ABI V1)
  \param[in]    tgt, the handle of target
  \param[out]   ctrlregs, save the scr register value
  \return       zero for success, negative for error
*/
TARGET_API int target_read_had_cpuscr(struct target *tgt, CTLREGS * ctlregs);

/**
  \brief        Write HAD CPU SCR register(NOTICE: only for csky ABI V1)
  \param[in]    tgt, the handle of target
  \param[out]   ctrlregs, to be writtein
  \return       zero for success, negative for error
*/
TARGET_API int target_write_had_cpuscr(struct target *tgt, CTLREGS * ctlregs);

/* Memory read/write.  */
/**
  \brief        Read memory from target
  \param[in]    tgt, the handle of target
  \param[in]    addr, the memory address to be read
  \param[out]   buff, an address which used to to save the memory data
  \param[in]    size, size to be read
  \return       zero, for success, negative for error
*/
TARGET_API int target_read_memory (struct target *tgt, U64 addr, unsigned char *buff, unsigned int size);

/**
  \brief        Write memory from target
  \note         if you try to download a lot of data and cfg.ddc_flag is on, please call
                target_enable_ddc (target, 1) before the first target_write_memory and
				call target_enable_ddc (target, 1) after the last target_write_memory
  \param[in]    tgt, the handle of target
  \param[in]    addr, the memory address to be written
  \param[out]   buff, the data which will be written to the target
  \param[in]    size, size to be written
  \return       zero for success, negative for error
*/
TARGET_API int target_write_memory (struct target *tgt, U64 addr, unsigned char *buff, unsigned int size);

/* Check debug-mode.  */
/**
  \brief        Check debug target
  \param[in]    tgt, the handle of target
  \param[out]   info, the halt informations, you should malloc first
  \return       zero for success, negative for error
*/
TARGET_API int target_check_debug (struct target *tgt, struct halt_info *info);

/* Semihosting.  */
/**
  \brief        Fileio end, set reponse while finishing semihosting
  \param[in]    tgt, the handle of target
  \param[in]    retcode, return value of semihosting
  \param[in]    fileio_errno, errno of semihosting
  \param[in]    ctrl_c, if gdb press CTRL-C or not
  \return       zero for success, negative for error
*/
TARGET_API int target_fileio_end (struct target *tgt, int retcode, int fileio_errno, int ctrl_c);

/* Interfaces of breakpoint.  */
/**
\brief        Get current left count of the hardwarw breakpoint
\param[in]    tgt, the handle of target
\return       hw left count
*/
TARGET_API int breakpoint_get_left_hw_count(struct target *tgt);

/* Interfaces of breakpoint.  */
/**
  \brief        Clear breapoints in breakpoint manager
  \param[in]    tgt, the handle of target
  \return       zero for success, negative for error
*/
TARGET_API int breakpoint_clear (struct target *tgt);

/**
  \brief        find breapoint in breakpoint manager
  \param[in]    tgt, the handle of target
  \param[in]    address, the address of breakpoint
  \return       a breakpoint found, NULL for not found
*/
TARGET_API struct breakpoint * breakpoint_find (struct target *tgt, U64 address);

/**
  \brief        Add breapoint in breakpoint manager
  \param[in]    tgt, the handle of target
  \param[in]    address, the address of breakpoint
  \param[in]    length, the breakpoint length, it could be 2 or 4
  \param[in]    type, the breakpoint type, BKPT_SOFT or BKPT_HARD, other value will generate error
  \return       zero for success, negative for error
*/
TARGET_API int breakpoint_add (struct target *tgt, U64 address,
                               unsigned int length, enum bkpt_type type);

/**
  \brief        Remove breapoint in breakpoint manager
  \param[in]    tgt, the handle of target
  \param[in]    address, the address of breakpoint which will be removed
  \return       zero for success, negative for error
*/
TARGET_API int breakpoint_remove (struct target *tgt, U64 address);

/**
  \brief        Clear watchpoints in watchpoint manager
  \param[in]    tgt, the handle of target
  \return       zero for success, negative for error
*/
TARGET_API int watchpoint_clear (struct target *tgt);

/**
  \brief        Add watchpoints in watchpoint manager
  \param[in]    tgt, the handle of target
  \param[in]    address, the address of breakpoint
  \param[in]    length, the watchpoint length, it could be 2 or 4
  \param[in]    type, the watchpoint type, WPT_ACCESS, WPT_WRITE or WPT_READ
  \return       zero for success, negative for error
*/
TARGET_API int watchpoint_add (struct target *tgt, U64 address,
                                    unsigned int length, int value,
                                    enum watchpoint_type rw);

/**
  \brief        Remove watchpoint in watchpoints manager
  \param[in]    tgt, the handle of target
  \param[in]    address, the address of the watchpoint which will be removed
  \return       zero for success, negative for error
*/
TARGET_API int watchpoint_remove (struct target *tgt, U64 address);

/**
  \brief        find watchpoint in watchpoints manager
  \param[in]    tgt, the handle of target
  \param[in]    address,, the address of the watchpoint
  \return       a watchpoint found, NULL for not found
*/
TARGET_API struct watchpoint * watchpoint_find (struct target *tgt, U64 address,
													 int st_ld_len, int is_st_ld);

/**
  \brief        Check memory has breakpoint or not (NOTICE: it will be in low level)
  \param[in]    tgt, the handle of target
  \param[in]    address, the address of the watchpoint
  \param[in]    data, the data of the memory
  \param[in]    length, the length of data
  \return       None
*/
TARGET_API void ck_check_mem_read (struct target *tgt, U64 address,
										unsigned char *data, unsigned int length);
/**
  \brief        Find the watchpoint which may be ld rx, rx, offset
  \param[in]    tgt, the handle of target
  \return       a watchpoint found, NULL for not found
*/
TARGET_API struct watchpoint * watchpoint_unique_find (struct target *target);

/* Debug communication interface, . */
/**
  \brief        the data from target will be output with cfg->dcomm.on_target_stdio
  \param[in]    tgt, the handle of target
  \return       zero for success, negative for error
*/
TARGET_API int target_do_dcomm (struct target *tgt);

/* Execute script */
/**
  \brief        Execute the script, GPIO script or JTAG script
  \param[in]    tgt, the handle of target
  \param[in]    scrfilepath, file path of the script
  \param[in]    MsgOut, message output interface
  \return       zero for success, negative for error
*/
TARGET_API int target_execute_script(struct target *tgt, char *scrfilepath,
									 int (*MsgOut) (const char *));

/* Print Version. */
/**
  \brief        Show version informations to the message out
  \return       None
*/
TARGET_API void target_print_version(void(*output) (const char *, ...));

/**
  \brief        Get the version of target interface
  \param[in]    tgt, the handle of target
  \param[out]   version, save the version of target interface
  \return       zero for success, negative for error
*/
TARGET_API int target_get_target_version(struct target *tgt, struct target_version *version);

/**
  \brief        Update firmware
  \param[in]    tgt, the handle of target
  \param[in]    firmware_path, the path of firmware
  \return       zero for success, negative for error
*/
TARGET_API int target_upgrade_firmware(struct target *tgt, char * firmware_path);

/**
  \brief        Setup the contact between multi-cores
  \param[in]    tgt, the handle of target
  \param[in]    flag_out, the singals output to others
  \param[in]    flag_in, the singals input from others
  \return       zero for success, negative for error
*/
TARGET_API int target_set_contact_mp(struct target *tgt, unsigned int flag_out, unsigned int flag_in);

/**
  \brief        Enable/disable downloading memory with DDC
  \param[in]    tgt, the handle of target
  \param[in]    enable, bool value, enable(1) or disable (0)
  \return       zero for success, negative for error
*/
TARGET_API int target_enable_ddc (struct target *tgt, unsigned int enable);

/**
  \brief        Get the regno of pc, sp, fp(NOTICE: It should be replaced with get regno from name)
  \param[in]    tgt, the handle of target
  \param[out]   pc_regno, save the regno of PC
  \param[out]   sp_regno, save the regno of SP
  \param[out]   fp_regno, save the regno of FP
  \return       zero for success, negative for error
*/
TARGET_API int target_get_pc_sp_fp_regno (struct target *target, int *pc_regno,
                                          int *sp_regno, int * fp_regno);

/**
  \brief        Setup the debug communication output to remote output
  \param[in]    tgt, the handle of target
  \param[in]    dcomm_remote_output, the remote output function
  \return       None
*/
TARGET_API void target_set_remote_dcomm_output (struct target *target, int (*dcomm_remote_output)(char ch));

/**
  \brief        trget switch trust environment (NOTICE: not used)
  \param[in]    tgt, the handle of target
  \param[in]    env, 1, TEE, 0, REE
  \return       zero for success, negative for error
*/
TARGET_API int target_switch_exec_environment (struct target *tgt, int env);

/* Breakpoints & watchpoint.  */
/**
  \brief        Insert a breakpoint which specified with the bp(NOTICE: using breakpoint_add usually)
  \param[in]    tgt, the handle of target
  \param[in]    bp, a breakpoint informations which will be inserted
  \return       zero for success, negative for error
*/
TARGET_API int target_insert_breakpoint (struct target *tgt, struct breakpoint *bp);

/**
  \brief        Remote a breakpoint which specified with the bp(NOTICE: using breakpoint_remove usually)
  \param[in]    tgt, the handle of target
  \param[in]    bp, a breakpoint informations which will be removed
  \return       zero for success, negative for error
*/
TARGET_API int target_remove_breakpoint (struct target *tgt, struct breakpoint *bp);

/**
  \brief        Insert a watchpoint which specified with the wp(NOTICE: using watchpoint_add usually)
  \param[in]    tgt, the handle of target
  \param[in]    wp, a watchpoint informations which will be inserted
  \return       zero for success, negative for error
*/
TARGET_API int target_insert_watchpoint (struct target *tgt, struct watchpoint *wp);

/**
  \brief        Remove a watchpoint which specified with the wp(NOTICE: using watchpoint_remove usually)
  \param[in]    tgt, the handle of target
  \param[in]    wp, a watchpoint informations which will be removed
  \return       zero for success, negative for error
*/
TARGET_API int target_remove_watchpoint (struct target *tgt, struct watchpoint *wp);

/* Execution environment Read/Write.  */
/**
  \brief        Read exec environment register(NOTICE:unused, may be deleted)
  \param[in]    tgt, the handle of target
  \param[out]   reg, save the register number, name, length, type, value,
                the number must set before calling the function
  \param[in]    exec_env, 1TEE, 0 REE
  \return       zero for success, negative for error
*/
TARGET_API int target_read_exec_env_register (struct target *tgt, struct reg *reg, int exec_env);

/**
  \brief        write exec environment register(NOTICE:unused, may be deleted)
  \param[in]    tgt, the handle of target
  \param[out]   reg, reigster to be written,
                the number and value must set before calling the function
  \param[in]    exec_env, 1 TEE, 0, REE
  \return       zero for success, negative for error
*/
TARGET_API int target_write_exec_env_register (struct target *tgt, const struct reg *reg, int exec_env);

/* Get HAD Registers List */
/**
  \brief        Get had register list (NOTICE: for UI)
  \note         No need to malloc space for reg_list, reg_list will return all supported HAD Regisetrs as a point
  \param[in]    tgt, the handle of target
  \param[out]   reg_list, a point contains a point which will be pointed to the reg list
  \return       zero for success, negative for error
*/
TARGET_API void target_get_had_registers_list (struct target *tgt, struct reg **reg_list);

/**
  \brief        Get target message
  \param[in]    tgt, the handle of target
  \param[in]    type, message type
  \param[in]    arg, the argument in the type, it could be the index of the cpu with type TARGET_MSG_CPU_NAME,
                others will be ignored
  \param[in]    msg, save the message informations, if type is TARGET_MSG_PIPE_INFO and TARGET_MSG_DEBUG_INFO,
                the size of message shoud be more than 2K bytes, otherwise size shoud more the 128 bytes
  \return       zero for success, negative for error
*/
TARGET_API int target_get_message (struct target *tgt,
                                   enum target_message_type type,
                                   int arg, char *msg);

/* Get RISCV Debug Module Registers List */
/**
  \brief        Get DM register list (NOTICE: for UI)
  \param[in]    tgt, the handle of target
  \param[out]   spec_ver, save the version of dm
  \param[out]   count, save the register count
  \param[out]   reg_list, a point contains a point which will be pointed to the reg list
  \return       zero for success, negative for error
*/
TARGET_API void target_get_dm_registers_list (struct target *tgt, int *spec_ver, int *count, struct reg **reg_list);

/**
  \brief        Read cpu register
  \param[in]    tgt, the handle of target
  \param[out]   reg, reigster to be red,
                the number must set before calling the function
  \param[in]    spec_ver, the version of dm
  \return       zero for success, negative for error
*/
TARGET_API int target_read_dm_reg (struct target *tgt, struct reg *reg, int spec_ver);

/**
  \brief        Write cpu register
  \param[in]    tgt, the handle of target
  \param[out]   reg, reigster to be written,
                the number and value must set before calling the function
  \param[in]    spec_ver, the version of dm
  \return       zero for success, negative for error
*/
TARGET_API int target_write_dm_reg (struct target *tgt, const struct reg *reg, int spec_ver);

/**
  \brief        Get debug architecture
  \param[in]    tgt, the handle of target
  \return       the type of target debug architecture
*/
TARGET_API enum debug_arch_type target_get_debug_arch_type (struct target *tgt);

/**
  \brief        Print architecture informations
  \param[in]    tgt, the handle of target
  \return       None
*/
TARGET_API void target_print_arch_info (struct target *tgt, void(*output) (const char *, ...));

/**
\brief        Get cklink device list
\param[in]    cfg
\param[in]    dev, point of list, the list should malloc space before calling the function
\param[in]    dev_count, point of list count
\return       zero for success, negative for error
*/
TARGET_API int target_get_link_list (dbg_server_cfg_t * cfg,
	                                   struct link_dev *dev,
	                                   unsigned int *dev_count);
/**
\brief        Get Vendor link list
\param[in]    cfg
\param[out]    str, a string for output.
\return       number of vendor
*/
TARGET_API int target_get_vendor_list (dbg_server_cfg_t *cfg, char *str);

/**
\brief        Config the links
\param[in]    target
\param[in]    config type
\param[in]    config value
\return       zero for success, negative for error
*/

TARGET_API int target_config_link (struct target *tgt, enum LINK_CONFIG_KEY key, unsigned int value);

/**
\brief        Config the Target
\param[in]    target
\param[in]    config type
\param[in]    config value
\return       zero for success, negative for error
*/

TARGET_API int target_config_target(struct target *tgt, enum target_config_type key, void *value);

/**
\brief        Get the Target configuration
\param[in]    target
\param[in]    config type
\param[in]    config value, space is malloced by caller
\return       zero for success, negative for error
*/

TARGET_API int target_get_target_config(struct target *tgt, enum target_get_config_type type, void *value);

/**
\brief        Execute the opcode with the debug module
\param[in]    target
\param[in]    opcode, the opcode of the instruction which is executed
\return       zero for success, negative for error
*/

TARGET_API int target_execute_opcode (struct target *tgt, insn_t opcode);

#ifdef __cplusplus
}
#endif
#endif //__CDK_DBUGGER_INTERFACE_H__
#endif
