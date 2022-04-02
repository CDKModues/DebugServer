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

/*******************************************************************************
* Filename: link.h
*******************************************************************************/

#ifndef __LINK_H__
#define __LINK_H__
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*------ Link return error code ------*/
enum LINK_ERROR {
	LINK_ERROR_NONE = 0,               ///< No error
	LINK_ERROR_NO_DEVICE = 0x80000001, ///< No device
	LINK_ERROR_IO = 0x80000002,        ///< Error IO
	LINK_ERROR_UNSUPPORT = 0x80000003, ///< Unsupport

	LINK_ERROR_UNKNOWN = 0x80000fff,   ///< Unknown error
};

/*----- Config key type -----*/
enum LINK_CONFIG_KEY
{
	LINK_CONFIG_CLK = 0,         ///< Set the jtag clock

	LINK_CONFIG_DDC,             ///< Enable DDC
#define LINK_CONFIG_DCC_VALUE_ENABLE     1
#define LINK_CONFIG_DCC_VALUE_DISABLE    0

	LINK_CONFIG_MTCR_DELAY,      ///< Unused

	LINK_CONFIG_CDI,             ///< Set SWD or JTAG
#define LINK_CONFIG_CDI_VALUE_JTAG       0
#define LINK_CONFIG_CDI_VALUE_SWD        1

	LINK_CONFIG_TRESET,          ///< Do Treset

	LINK_CONFIG_ISA_VER,         ///< Set ISA Version, 2,3: CSKY 8xx; 4: RV32; 5:RV64

	LINK_CONFIG_HACR_LENGTH,     ///< Set HACR(IR) length in bits
#define LINK_CONFIG_HACR_LENGTH_VALUE_8  8
#define LINK_CONFIG_HACR_LENGTH_VALUE_16 16

	LINK_CONFIG_CPU_SEL,         ///< select CPU

	LINK_CONFIG_SET_DM,          ///< For RISCV Setting cklink_csr8

	LINK_CONFIG_GET_DM,          ///< For RISCV Getting cklink_csr8

	LINK_CONFIG_SET_DM_BASE,     ///< For RISCV Setting cklink_csr9

	LINK_CONFIG_TO_RESET_STATE,  ///< Send a request to cklink doing tms is 1 with 100 tclk

	LINK_CONFIG_GET_PC_SAMPLING_SUPPORT,  ///< Send a request to cklink doing tms is 1 with 100 tclk

	LINK_CONFIG_GET_LINK_CLK,     ///< Get link.actclk

/* Define for cklink_csr[8], for riscv config. */
#define CKLINK_REG8_SET_IDLE_DELAY(cklink_reg8, idle_delay)      (((cklink_reg8) & 0xf07ffff8) | (((idle_delay) & 0x7)) | ((((idle_delay) >> 3) & 0x1f) << 23))
#define CKLINK_REG8_SET_ABITS(cklink_reg8, abits)                (((cklink_reg8) & 0xfffffe07) | (((abits) & 0x3f) << 3))
#define CKLINK_REG8_SET_XLEN(cklink_reg8, xlen)                  (((cklink_reg8) & 0xfffff1ff) | (((xlen) & 0x7) << 9))
#define CKLINK_REG8_SET_PROGBUF_SIZE(cklink_reg8, progbuf_size)  (((cklink_reg8) & 0xfffe0fff) | (((progbuf_size) & 0x1f) << 12))
#define CKLINK_REG8_SET_IMPEBREAK(cklink_reg8, impebreak)        (((cklink_reg8) & 0xfffdffff) | (((impebreak) & 0x1) << 17))
#define CKLINK_REG8_SET_MEM_ACCESS_MODE(cklink_reg8, mode)       (((cklink_reg8) & 0xffe3ffff) | (((mode) & 0x7) << 18))
#define CKLINK_REG8_SET_ABSTRACTAUTO(cklink_reg8, abstractauto)  (((cklink_reg8) & 0xffdfffff) | (((abstractauto) & 0x1) << 21))
#define CKLINK_REG8_SET_DMIACC(cklink_reg8, dmiacc)              (((cklink_reg8) & 0xffbfffff) | (((dmiacc) & 0x1) << 22))

#define CKLINK_REG8_GET_MEM_ACCESS_MODE(cklink_reg8)             (((cklink_reg8) >> 18) & 0x7)

	LINK_CONFIG_SET_IDLE_DELAY,          ///< Set TCLK stayed in Run Test/Idle

	LINK_CONFIG_SET_ABITS,               ///< Set abits for RVDM

	LINK_CONFIG_SET_DMIACC,              ///< Set dmiacc for RVDM

	LINK_CONFIG_SET_PB_SIZE,             ///< Set Progbuf size for RVDM

	LINK_CONFIG_SET_IMPEBREAK,           ///< Set ImpEbreak for RVDM

	LINK_CONFIG_SET_ABSTRACTAUTO,        ///< Set AbstractAuto for RVDM

	LINK_CONFIG_SET_XLEN,                ///< Set XLEN for RVDM

	LINK_CONFIG_SET_MEM_ACCESS_MODE,     ///< Set Mem Access Mode for RVDM
};


/*------ Memory Access Mode -------*/
enum MEMORY_ACC_MODE {
	M_BYTE = 1,                 ///< Access memory via byte
	M_HWORD = 2,                ///< Access memory via half-word
	M_WORD = 4,                 ///< Access memory via word
	M_DWORD = 6,                ///< Access memory via double word
};

/*------ PC Sampling Comand -------*/
enum LINK_PC_SAMPLING_CMD
{
	LINK_PC_SAMPLING_NONE,       ///< None
	LINK_PC_SAMPLING_INFO,       ///< Get Buffer size, arg is a integer point
	LINK_PC_SAMPLING_SETUP,      ///< Setup the CPU and time(ms), arg is 
	LINK_PC_SAMPLING_START,      ///< Start PC Sampling
	LINK_PC_SAMPLING_STOP,       ///< Stop PC Sampling
	LINK_PC_SAMPLING_DUMP,       ///< Dump PC from pc buffer
};

/*------ PC Sampling args --------*/
union link_pc_sampling_arg
{
	uint32_t reserved;           ///< no needed for START/STOP
	uint32_t *buffer_size;       ///< arg for INFO
	struct {
		int cpu;                 ///< the CPU
		uint32_t freq;              ///< Sampling frequence @Hz
	} setup_info;                ///< arg for SETUP
	struct {
		uint32_t buff_size;
		uint32_t xlen;
		uint32_t *pc_count;
		uint32_t *pc_buffer;
	}dump_buff;                  ///< arg for DUMP
};

#if 0

/**
\brief        Initilize
\param[in]    cfg
\return       zero for success, negative for error
*/
int  link_init (dbg_server_cfg_t *cfg);

/**
\brief        open the link
\param[in]    cfg, configuations
\param[in]    unique, a unique string, such as serial num
\return       a handle for the link which is open
*/
void * link_open (dbg_server_cfg_t *cfg, void *unique);

/**
\brief        close the link
\param[in]    handle, the return value of link_open
\return       zero for success, negative for error
*/
void link_close (void *handle);

/**
\brief        Config the links
\param[in]    handle, the return value of link_open
\param[in]    key, the config key
\param[in]    value, the config value
\return       zero for success, negative for error
*/
int  link_config (void *handle,  enum LINK_CONFIG_KEY key, unsigned int value);

/**
\brief        Upgrade the firmware of the link
\param[in]    handle, the return value of link_open
\param[in]    path, the path of the program
\return       zero for success, negative for error
*/
int  link_upgrade (void *handle, const char *path);

/**
\brief        Read memory from the target
\param[in]    handle, the return value of link_open
\param[in]    addr, the base address of memory
\param[in]    xlen, 32 or 64
\param[out]   buff, a point which is used to save the memory value
\param[in]    length, the length of the memory which need to be read
\param[in]    mode, byte/half word/word/double word
\return       zero for success, negative for error
*/
int  link_memory_read (void *handle, uint64_t addr, int xlen, uint8_t *buff, int length, int mode);

/**
\brief        Write memory to the target
\param[in]    handle, the return value of link_open
\param[in]    addr, the base address of memory
\param[in]    xlen, 32 or 64
\param[in]    buff, a point which is used to save the memory value
\param[in]    length, the length of the memory which need to be read
\param[in]    mode, byte/half word/word/double word
\return       zero for success, negative for error
*/
int  link_memory_write (void *handle, uint64_t addr, int xlen, uint8_t *buff, int length, int mode);

/**
\brief        Read register to the target
\param[in]    handle, the return value of link_open
\param[in]    regno, the number of register
\param[in]    buff, a point which is used to save the value of the register
\param[in]    nbyte, the length of register in byte
\return       zero for success, negative for error
*/
int  link_register_read (void *handle, int regno, uint8_t *buff, int nbyte);

/**
\brief        Write register to the target
\param[in]    handle, the return value of link_open
\param[in]    regno, the number of register
\param[in]    buff, a point which is used to save the value of the register
\param[in]    nbyte, the length of register in byte
\return       zero for success, negative for error
*/
int  link_register_write (void *, int regno, uint8_t *buff, int nbyte);

/**
\brief        Do a JTAG transfer.
              NOTICE: if read is true, should save the DR output to dr_r.
\param[in]    handle, the return value of link_open
\param[in]    ir_len, the length of IR in bytes
\param[in]    ir, the value of IR
\param[in]    dr_len, the length of DR in bytes
\param[in]    dr_r, the DR output
\param[in]    dr_w, the DR input 
\param[in]    read, a flag indicats need read or not.
\return       zero for success, negative for error
*/
int  link_jtag_operator (void *handle, int ir_len, unsigned char *ir,
                      int dr_len, unsigned char *dr_r, unsigned char *dr_w, int read);

/**
\brief        Do a GPIO transfer.
\param[in]    handle, the return value of link_open
\param[in]    gpio_out, the output value of GPIO
\param[in]    gpio_in, save the GPIO value
\param[in]    gpio_oe, GPIO output enable
\param[in]    gpio_mode, the gpio mode
\return       zero for success, negative for error
*/
int  link_gpio_operator (void *, int gpio_out, int *gpio_in, int gpio_eo, int gpio_mode);

/**
\brief        Show some infomations about link via func
\param[in]    handle, the return value of link_open
\param[in]    cfg, the configurations
\param[in]    func, an output channel
\return       zero for success, negative for error
*/
int  link_show_info (void *, dbg_server_cfg_t *cfg, void (*func)(const char *, ...));

/**
\brief        Reset the target
\param[in]    handle, the return value of link_open
\param[in]    hard, hard reset(nreset) or not
\return       zero for success, negative for error
*/
int  link_reset (void *handle, int hard);

/**
\brief        Get the link device list
\param[in]    handle, the return value of link_open
\param[in]    hard, hard reset(nreset) or not
\return       zero for success, negative for error
*/
int  link_get_device_list (struct link_dev *dev, int *count);

/**
\brief        Get the link device list
\param[in]    vid, the vendor ID of usb devices
\param[in]    pid, the product ID of usb devices
\param[in]    handle, the return value of link_open
\param[in]    hard, hard reset(nreset) or not
\return       zero for success, negative for error
*/
int  link_get_device_list_with_vid_pid (U16 vid, U16 pid, struct link_dev *dev, int *count);

/**
\brief        Get the name of link. It is a special function which indicates
              that the dll is supported to DebugServer.
\return       The name of link.
*/
const char * THE_NAME_OF_LINK (void);

#endif


#ifdef __cplusplus
}
#endif

#endif
