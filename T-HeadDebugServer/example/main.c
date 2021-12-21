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
#include <debug.h>
#include <dbg-cfg.h>
#include <dbg-target.h>

extern  int test_memory (struct target *target);
extern  int test_register (struct target *target);
extern  int test_breakpoint (struct target *target);

/* Try to avoid exiting right now in windows */
void
prepare_exit_from_main ()
{
#if defined (_WIN32) && !defined (__CYGWIN)
    int a;
    printf ("Input enter to exit...\n");
    a = getchar ();
#endif
    return;
}

int main(int argc, char **argv)
{
	dbg_server_cfg_t cfg;
	struct halt_info info;

	init_default_config(&cfg);

	/* Init verbose output channel. */
	dbg_debug_channel_init (cfg.misc.msgout, cfg.misc.errout, cfg.misc.verbose);

	/* Create target.  */
    if (target_init (&cfg)) {
        prepare_exit_from_main ();
        return -1;
    }

	/* Print target version. */
    target_print_version (printf);
    if (cfg.misc.print_version) {
        prepare_exit_from_main ();
        return -1;
    }

    /* Open device. */
    cfg.target = target_open (&cfg);
    if (!(cfg.target && target_is_connected (cfg.target))) {
        prepare_exit_from_main ();
        return -1;
    }

	/* Memory access test.  */
	test_memory(cfg.target);

	/* Register access test.  */
	test_register(cfg.target);

	/* Breakpoint test.  */
	test_breakpoint(cfg.target);

	/* Resume. */
	target_resume (cfg.target);

	/* Halt CPU */
	target_halt (cfg.target);

	/* Check debug. */
	target_check_debug (cfg.target, &info);

	target_close (cfg.target);

	return 0;
}
