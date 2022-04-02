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

#ifndef __CKCORE_DEBUGGER_SERVER_DATATYPE_H__
#define __CKCORE_DEBUGGER_SERVER_DATATYPE_H__

// #ifdef _WIN32
// #define inline __inline
// #endif

typedef int BOOL;
#if defined (_WIN32) && !defined(__CYGWIN__)
typedef int socklen_t;
#endif

#if !defined (bool) && !defined (__cplusplus)
#define bool int
#endif

#if !defined (false) && !defined (__cplusplus)
#define false 0
#define true  1
#endif

#if defined (_WIN32) && !defined(__CYGWIN__)
typedef unsigned __int64 U64;
typedef __int64          S64;
#else
typedef unsigned long long  U64;
//typedef uint64_t         U64;
typedef double           S64;

typedef unsigned long    DWORD;

#ifndef UINT64
#define UINT64 unsigned __int64
#endif

#ifndef UINT31
#define UINT31 unsigned int
#define UINT15 unsigned short
#define UINT7 unsigned char
#endif

#ifndef BOOL
#define BOOL             int
#define TRUE               1
#define FALSE              0
#endif
#endif


#if !defined( __int64) && !defined(_WIN32)
#if defined (M32)
#define __int64 long long
#else
#define __int64 long
#endif
#endif

#ifndef _MAX_PATH
#define _MAX_PATH 1024
#endif

#ifndef U32
#define __CKDATATYPE__
typedef unsigned int     U32;
typedef unsigned short   U16;
typedef unsigned char    U8;
typedef int              S32;
typedef short            S16;
typedef char             S8;
#endif

typedef unsigned long long insn_t;

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)    ((sizeof (x))/(sizeof (x[0])))
#endif

#endif // __CKCORE_DEBUGGER_SERVER_DATATYPE_H__
