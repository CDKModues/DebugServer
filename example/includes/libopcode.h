#ifndef __LIBOPCODE_H__
#define __LIBOPCODE_H__

#include "dataType.h"

#define LIBOPCODE_ERROR_NONE   0
#define LIBOPCODE_ERROR_FATAL  -1
#define LIBOPCODE_ERROR_SP 	   -1001
#define LIBOPCODE_ERROR_TARGET -1002


/* Can the opcode be executed.  */
int opcode_can_be_executed (void *target, insn_t opcode);

/* The opcode will be executed,
 * if is_flashbp is true, the PC will be updated.  */
int opcode_execute (void * target, insn_t opcode, int is_flashbp);


#endif
