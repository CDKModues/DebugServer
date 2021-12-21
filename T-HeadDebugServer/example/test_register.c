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
#include <stdlib.h>
#include "dbg-target.h"
#include "dataType.h"
#include "regNo.h"


int test_register (struct target *target)
{
	struct reg rn;
	int ret = 0;
	int i = CSKY_R0_REGNUM;

	printf ("=================== register access test ==================\n\n");

	printf ("CPU generate register:\n");
	for (i; i <= CSKY_R15_REGNUM; i++) {
		rn.num = i;
		rn.value.val32 = 0x12345678;
		ret = target_write_cpu_reg (target, &rn);
		if (ret < 0)
			printf ("failed to write 0x%x to r%d\n", rn.value.val32, i);

		memset (&rn.value.val32, 0, sizeof (rn.value));
		ret = target_read_cpu_reg (target, &rn);
		if (ret < 0)
			printf ("failed to read r%d\n", i);

		printf ("r%d: write 0x123456789, read 0x%x\n", i, rn.value.val32);
	}

	printf ("CPU PC register:\n");
	rn.num = CSKY_PC_REGNUM;
	rn.value.val32 = 0x12345678;
	ret = target_write_cpu_reg (target, &rn);
	if (ret < 0)
		printf ("failed to write 0x%x to r%d\n", rn.value.val32, i);

	memset (&rn.value.val32, 0, sizeof (rn.value));
	ret = target_read_cpu_reg (target, &rn);
	if (ret < 0)
		printf ("failed to read r%d\n", i);
	printf ("PC: write 0x123456789, read 0x%x\n", rn.value.val32);
	
	printf ("\n\n");
	
	return 0;
}
