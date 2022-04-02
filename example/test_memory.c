/*
 * Copyright (C) 2020 C-SKY Microsystems Co., Ltd. All rights reserved.
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

#include <stdio.h>
#include <string.h>
#include "dbg-target.h"

int test_memory (struct target *target)
{
	char wbuff[128];
	char rbuff[128];
	int ret = 0;
	memset (wbuff, 'a', sizeof (wbuff));
	printf ("=================== memory access test ==================\n\n");

	//enable ddc function
	ret = target_enable_ddc (target, 1);
	if (ret < 0) {
		return ret;
	}
	//executing write mem operation
	ret = target_write_memory(target, 0x0, wbuff, 128);
	if (ret < 0) {
		return ret;
	}
	//disable ddc function
	ret = target_enable_ddc (target, 0);
	if (ret < 0) {
		return ret;
	}

	ret = target_read_memory(target, 0x0, rbuff, 128);
	if (ret < 0) {
		return ret;
	}

	if (memcmp (wbuff, rbuff, 128) != 0) {
		printf ("memory read/write failed\n\n");
		return -1;
	}
	
	printf ("memory read/write successfully\n\n");
	return 0;
}
