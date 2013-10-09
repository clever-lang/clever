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
	switch (opnum) {
	case OP_RET:         return "ret";
	case OP_ASSIGN:      return "assign";
	case OP_ADD:         return "add";
	case OP_SUB:         return "sub";
	case OP_MUL:         return "mult";
	case OP_DIV:         return "div";
	case OP_MOD:         return "mod";
	case OP_JMP:         return "jmp";
	case OP_FCALL:       return "fcall";
	case OP_LEAVE:       return "leave";
	case OP_SEND_VAL:    return "sendval";
	case OP_JMPZ:        return "jmpz";
	case OP_PRE_INC:     return "preinc";
	case OP_PRE_DEC:     return "predec";
	case OP_POS_INC:     return "posinc";
	case OP_POS_DEC:     return "posdec";
	case OP_JMPNZ:       return "jmpnz";
	case OP_AND:         return "and";
	case OP_OR:          return "or";
	case OP_EQUAL:       return "equal";
	case OP_NEQUAL:      return "nequal";
	case OP_LOCK:        return "lock";
	case OP_UNLOCK:      return "unlock";
	case OP_HALT:        return "halt";
	case OP_GREATER:     return "greater";
	case OP_GEQUAL:      return "gequal";
	case OP_LESS:        return "less";
	case OP_LEQUAL:      return "lequal";
	case OP_NEW:         return "new";
	case OP_MCALL:       return "mcall";
	case OP_SMCALL:      return "smcall";
	case OP_PROP_R:      return "propr";
	case OP_SPROP_R:     return "spropr";
	case OP_PROP_W:      return "propw";
	case OP_SPROP_W:     return "spropw";
	case OP_TRY:         return "try";
	case OP_CATCH:       return "catch";
	case OP_THROW:       return "throw";
	case OP_ETRY:        return "etry";
	case OP_NOT:         return "not";
	case OP_BW_AND:      return "bw_and";
	case OP_BW_OR:       return "bw_or";
	case OP_BW_XOR:      return "bw_xor";
	case OP_BW_NOT:      return "bw_not";
	case OP_BW_LS:       return "bw_ls";
	case OP_BW_RS:       return "bw_rs";
	case OP_SUBSCRIPT_W: return "subsw";
	case OP_SUBSCRIPT_R: return "subsr";
	case OP_BIND:        return "bind";
	case OP_BSCOPE:      return "bscope";
	case OP_ESCOPE:      return "escope";
	EMPTY_SWITCH_DEFAULT_CASE();
	}
#undef CASE
	return "UNKNOWN";
}
#endif

} // clever
