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

int test_breakpoint (struct target *target)
{
	int ret = 0;

	printf ("=================== breakpoint test ==================\n\n");
	
	// Software breakpoint
	ret = breakpoint_add (target, 0x0, 2, BKPT_SOFT);
	if (ret < 0) {
		printf ("breakpoint add failed at 0\n");
		return ret;
	}

	// Hardware breakpoint
	ret = breakpoint_add (target, 0x100, 2, BKPT_HARD);
	if (ret < 0) {
		printf ("breakpoint add failed at 0x100\n");
		return ret;
	}

	breakpoint_clear(target);
	printf ("Breakpoint add successfully\n\n");
	
	return 0;
}
