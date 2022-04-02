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

#ifndef __CKCORE_DEBUGGER_SERVER_DEBUG_H__
#define __CKCORE_DEBUGGER_SERVER_DEBUG_H__

#if defined (_WIN32) && !defined (__CYGWIN)
#ifdef UTILS_EXPORTS
#define UTILS_API __declspec(dllexport)
#else
#define UTILS_API __declspec(dllimport)
#endif /* UTILS_EXPORTS */
#else
#define UTILS_API 
#endif /* _WIN32 && !__CYGWIN */

#if defined (_WIN32) && !defined (__CYGWIN)
#include "windows.h"
#include <time.h>
#else
#include "string.h"
#include "unistd.h"
#define Sleep(t) usleep((t)*1000)
#include "time.h"
#include "sys/time.h"
#endif

#include <stdio.h>
#include "verbose.h"
#include "dbg-cfg.h"
#include "dataType.h"

#if defined (_WIN32) && !defined (__CYGWIN) 
#define vsnprintf _vsnprintf
#define vsprintf _vsprintf
#include <stdarg.h>
#else
#include <stdarg.h>
#endif

#if defined (_WIN32) && !defined (__CYGWIN)
// VC6.0, __func__ is not recgonized
#define PARAMS_ASSERT_NO_RETURN(expr)
#define PARAMS_ASSERT_RETURN_NULL(expr)
#define PARAMS_ASSERT_RETURN_NEGATIVE(expr)
#define PARAMS_ASSERT_RETURN_ZERO(expr)

#else /* not _WIN32 */

#define PARAMS_ASSERT_NO_RETURN(expr)                       \
    if (!(expr)) {                                            \
        ERROR_OUT ("[%s:%d]parameters are illegal: %s\n", __func__, __LINE__, #expr);  \
        return;                                             \
    }
#define PARAMS_ASSERT_RETURN_NULL(expr)                     \
    if (!(expr)) {                                            \
        ERROR_OUT ("[%s:%d]parameters are illegal: %s\n", __func__, __LINE__, #expr);  \
        return NULL;                                        \
    };
#define PARAMS_ASSERT_RETURN_NEGATIVE(expr)                 \
    if (!(expr)) {                                            \
        ERROR_OUT ("[%s:%d]parameters are illegal: %s\n", __func__, __LINE__, #expr);  \
        return -1;                                          \
    };
#define PARAMS_ASSERT_RETURN_ZERO(expr)                     \
    if (!(expr)) {                                            \
        ERROR_OUT ("[%s:%d]parameters are illegal: %s\n", __func__, __LINE__, #expr);  \
        return 0;                                          \
    };
#endif /* not _WIN32 */

#ifdef __cplusplus
extern "C" {
#endif

enum utils_config_type
{
	UTILS_CONFIG_IDE_FLAG = 0,
	UTILS_CONFIG_CPU_NUM = 1,
	UTILS_CONFIG_LOG_FILE = 2,
	UTILS_CONFIG_GET_VERBOSE = 3,
};

/* Message out with "WARNING" prompt by dbg_message_out.  */
UTILS_API void WARNING_OUT (const char* fmt, ...);

/* Message out msg via dbg_message_out.  */
UTILS_API void INFO_OUT(const char* fmt, ...);

/* Message out msg via dbg_localsemi_out.  */
UTILS_API void LOCALSEMI_OUT(const char* fmt, ...);

/* Message out with "ERROR:" prompt via dbg_error_out.  */
UTILS_API void ERROR_OUT(const char* fmt, ...);

/* Message out with "VERBOSE:" prompt via dbg_message_out.  */
UTILS_API void VERBOSE_OUT(int verbose, const char* fmt, ...);

/* Init args */
UTILS_API void dbg_debug_channel_init (int (*msgout) (const char *),
									   int (*errout) (const char *),
									   int verbose);

UTILS_API void dbg_debug_channel_config(enum utils_config_type type, void *val);

/* Correspond to init and config, if there are some cases needed to do when DebugServer Close */
UTILS_API void dbg_debug_channel_close();

/* This is a non-used func, just making Utils.dll linking float-lib.  */
UTILS_API volatile double double_func (double args);


UTILS_API int input_read (int type, char *buff, int length);
UTILS_API int input_uninit (dbg_server_cfg_t * cfg);
UTILS_API int input_init (dbg_server_cfg_t * cfg, struct target *target, void *unused);

UTILS_API char *utils_value64_to_str (U64 num);
UTILS_API U64 utils_str_to_value64 (char *nptr, char **endptr, int base);

UTILS_API int init_default_config(dbg_server_cfg_t * cfg);

UTILS_API U64 utils_get_ms_clock();

#ifdef DEBUG
UTILS_API void DEBUG_OUT(const char* fmt, ...);
#endif

#ifdef __cplusplus
}
#endif
#endif // __CKCORE_DEBUGGER_SERVER_DEBUG_H__
