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

#ifndef __DEBUGGER_SERVER_DBG_CFG_H__
#define __DEBUGGER_SERVER_DBG_CFG_H__

#ifdef __cplusplus
extern "C"
{
#endif

//for the max pc sampling operations per second
#define PC_SAMPLING_FREQ_MAX 1000

//for IDLE_DELAY
#define IDLE_DELAY_0 0xf1f1f1f1

//for RISC-V Vector Version
enum riscv_vector_version
{
	RISCV_VECTOR_VER_UNKNOEN,
	RISCV_VECTOR_VER_0_71,
	RISCV_VECTOR_VER_1_0
};

/*------ Service Type ------*/
enum service_type
{
	SERVICE_TYPE_NONE,       ///< Not define
	SERVICE_TYPE_REMOTE,     ///< Remote Server
	SERVICE_TYPE_DJP,        ///< DJP Server
	SERVICE_TYPE_CONSOLE,    ///< Console
};

/* About target Debug Communication(Debug-Print).  */
enum dcomm_type
{
	DCOMM_TYPE_NONE,        ///< None
	DCOMM_TYPE_DCC,         ///< DCC
	DCOMM_TYPE_LDCC,        ///< LDCC
};

/*------ Architecture -------*/
enum debug_arch_type
{
	DEBUG_ARCH_NONE = 0,    ///< Debug Architecture None
	DEBUG_ARCH_CSKY,        ///< C-SKY Debug
	DEBUG_ARCH_RISCV,       ///< RISCV Debug
	DEBUG_ARCH_AUTO,        ///< DebugServer needs to find the debug_arch_type automatically
};

/*------ LINK State -------*/
enum ice_state
{
	ICE_STATE_IDLE = 0,     ///< IDLE
	ICE_STATE_BROKEN,       ///< Broken
	ICE_STATE_BUSY,         ///< Busy
	ICE_STATE_UNKNOWN = 0xf ///< Unknown
};

enum had_reset_type
{
	DO_HAD_TRESET,
	DO_HAD_SRESET,
};

/*------ Link device -------*/
struct link_dev
{
	/* Device point. */
	void *device;
	/* Device Handler, which return from link_open.  */
	void *handler;
	/* The USB VID.  */
	int vid;
	/* The USB PID.  */
	int pid;
	/* The USB bcdDevice.  */
	int bcdDevice;
	/* Device string, it could be a dup string from serial number.  */
	char dev_str[200];
	/* Device serial number.  */
	char sn[200];
	/* Link state.  */
	enum ice_state state;
};

struct dcomm_cfg
{
    enum dcomm_type type;
    int (*on_target_stdout) (char ch);
    int (*on_remote_stdout) (char ch);
};

/* PC Sampling config. */
enum pc_sampling_type
{
	PC_SAMPLING_TYPE_PCFIFO_LINK,    ///< PC Sampling with PCFIFO in link
	PC_SAMPLING_TYPE_PCFIFO_HOST,    ///< PC Sampling with PCFIFO in host
	PC_SAMPLING_TYPE_SNOOP,          ///< PC Sampling with snoop
	PC_SAMPLING_TYPE_DWT,            ///< PC Sampling with DWT
	PC_SAMPLING_TYPE_TRACE,          ///< PC Sampling with trace
};

struct dsampling_cfg
{
	int sampling;
	unsigned int sampling_freq;
	int sampling_port;
	unsigned int sampling_cpu;
	enum pc_sampling_type type;       ///< PC Sampling type
};

struct misc_cfg {
	/* Log Level config.  */
	int verbose;
	/* Print DebugServer Version info . */
	int print_version;
	/* Message output interface.  */
	int (*msgout) (const char *);
	/* Error output interface.  */
	int (*errout) (const char *);
	/* Don't check target while connectint. */
	unsigned char return_after_ice_connection;
};

struct link_cfg
{
	unsigned short vid;
	unsigned short pid;
	char *root_path;
	/* MTCR instruction write delay.
	 * arch.cache_flush_delay will replace this.  */
	int mtcr_delay;
	/* JTAG/SWD select.  */
	int cdi;
	/* NRESET Pin hold time while do nreset.  */
	int nrst_delay;
	/* TRESET pin hold time while do nreset.  */
	int trst_delay;
	/* Do TRESET while do reset. It should be always true.  */
	unsigned char trst_en;
	/* Link TCLK Clock.  */
	unsigned int ice_clk;
	/* Serail number for the target. If set, connect the device with the SN.  */
	char *serial;
	/* The Firmware config path. */
	char *config_path;

};

struct arch_cfg {
	/* Debug architecture.  */
	enum debug_arch_type debug_arch;
	/* Do not check cpuid while connectting.  */
	unsigned int no_cpuid_check;
	/* Initial value is -1, if they are not -1, all the
	 * program should not change it.  */
	/* ISA version for T-HEAD. */
	int isa_version;
	/* HACR length in bits.  */
	int hacr_width;
	/* The register xml file path. */
	char *tdesc_xml_file;
	/* Jtag or GPIO Script file path. Exit after executing script.  */
	char *script;               /* Script path.  */
	/* Jtag or GPIO Script file path.  Continue after executing script.  */
	char *target_init_script;   /* Target init script.  */
	/* Do prerest before connecting. */
	unsigned char pre_reset;
	/* Don't flush cache. */
	unsigned char no_cache_flush;
	/* Delay for doing flush caches.  */
	unsigned int cache_flush_delay;
	/* Wait for target system set-up.  */
	int rst_sleep;
	/* idle_delay for riscv... */
	unsigned int idle_delay;
	/* Set delay time for DMCONTROL.cmdreset signal */
	unsigned int ndmrst_delay;
	/* Set delay time for DMCONTROL.hartreset signal */
	unsigned int hartrst_delay;
};

struct socket_cfg
{
	/* Only start server, not force cpu into debu mode.  */
	unsigned char  onlyserver;
	/* Socket port for remote server.  */
	int  port;                  /* Server port.  */
	/* Only one port for SMP.  */
	unsigned char is_multicore_threads;
};

struct functional_cfg
{
	/* Enale write memory via DDC. */
	unsigned char ddc_flag;

	/* Do semihosting in DebugServer or not.  */
	unsigned char local_semi;

	/* Enable CommandLine. */
	unsigned char cmdline_en;

	/* Command Line initial script path.  */
	char *cmd_script_path;

	/* Operations of accessing memory and register in cklink.  */
	int speeded_up;

	/* Debug Comunications(Debug-Print).  */
	struct dcomm_cfg dcomm;

	/* Debug Sampling(PC, ContextID).  */
	struct dsampling_cfg dsampling;
};

typedef struct debugger_server_cfg
{
	/* Private data.  */
	void *priv;
	/* Global config.  */
	/* Program root path.  */
	char *root_path;
	/* Only for IDE, start with ICE.  */
	unsigned int ide_flag;

	/* Only for IDE, Do cklink upgrade.  */
	unsigned int do_link_upgrade;

	/* ICE config.  */
	struct link_cfg link;

	/* NOTICE: PREVIOUS SHOULD NOT BE MODIFIED. */

	/* Misc config.  */
	struct misc_cfg misc;

	/* architecture config.  */
	struct arch_cfg arch;

	/* socket config.  */
	struct socket_cfg socket;

	/* functional config.  */
	struct functional_cfg function;

	/* A handler for target. */
	struct target *target;

	/* List links.  */
	int list_ice;

	/* list vendor link.  */
	unsigned int list_vendor;

	/* select vendor link.  */
	const char *vendor_name;

	/* log file name. */
	const char *log_file_name;

} dbg_server_cfg_t;

#ifdef __cplusplus
}
#endif

#endif
