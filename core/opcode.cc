/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/opcode.h"

namespace clever {

#ifdef CLEVER_DEBUG
const char* get_opcode_name(Opcode opnum)
{
#define CASE(s) case s: return #s
	switch (opnum) {
		CASE(OP_RET);
		CASE(OP_ASSIGN);
		CASE(OP_ADD);
		CASE(OP_SUB);
		CASE(OP_MUL);
		CASE(OP_DIV);
		CASE(OP_MOD);
		CASE(OP_JMP);
		CASE(OP_FCALL);
		CASE(OP_TCALL);
		CASE(OP_ETHREAD);
		CASE(OP_LEAVE);
		CASE(OP_SEND_VAL);
		CASE(OP_JMPZ);
		CASE(OP_PRE_INC);
		CASE(OP_PRE_DEC);
		CASE(OP_POS_INC);
		CASE(OP_POS_DEC);
		CASE(OP_JMPNZ);
		EMPTY_SWITCH_DEFAULT_CASE();
	}
#undef CASE
	return "UNKNOWN";
}
#endif

} // clever
