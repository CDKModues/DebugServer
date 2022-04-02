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
// File name: verbose.h
// function description: define the output level for VERBOSE_OUT .
//
// ****************************************************************************

#ifndef __CKCORE_DEBUGGER_SERVER_VERBOSE_H__
#define __CKCORE_DEBUGGER_SERVER_VERBOSE_H__

#define VERBOSE_USB_FUNC      0x00000001      //USB:     Usb communication packets log
#define VERBOSE_CONNECT_FUNC  0x00000002      //CONNECT: Connect target log
#define VERBOSE_TARGET_FUNC   0x00000004      //TARGET:  Target functions log
#define VERBOSE_REMOTE_FUNC   0x00000008      //REMOTE:  Remote protocol log
#define VERBOSE_DJP_FUNC      0x00000010      //DJP:     Djp protocol log
#define VERBOSE_SYS_FUNC      0x00000020      //SYS:     System log
#define VERBOSE_FLASH_FUNC    0x00000040      //FLASH:   FLASH log, include Libopcode
#define VERBOSE_NO_PREFIX     0x80000000      //Verbose out with no prefix
#define VERBOSE_ALL           0xffffffff      //Output all Verbose message

#endif
