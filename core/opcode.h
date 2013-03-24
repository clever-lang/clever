/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_OPCODE_H
#define CLEVER_OPCODE_H

namespace clever {

#ifndef CLEVER_MSVC
# define OP_LABELS \
	&&OP_RET,      \
	&&OP_ASSIGN,   \
	&&OP_ADD,      \
	&&OP_SUB,      \
	&&OP_MUL,      \
	&&OP_DIV,      \
	&&OP_MOD,      \
	&&OP_JMP,      \
	&&OP_FCALL,    \
	&&OP_LEAVE,    \
	&&OP_SEND_VAL, \
	&&OP_JMPZ,     \
	&&OP_PRE_INC,  \
	&&OP_PRE_DEC,  \
	&&OP_POS_INC,  \
	&&OP_POS_DEC,  \
	&&OP_JMPNZ,    \
	&&OP_AND,      \
	&&OP_OR,       \
	&&OP_EQUAL,    \
	&&OP_NEQUAL,   \
	&&OP_LOCK,     \
	&&OP_UNLOCK,   \
	&&OP_HALT,     \
	&&OP_GREATER,  \
	&&OP_GEQUAL,   \
	&&OP_LESS,     \
	&&OP_LEQUAL,   \
	&&OP_NEW,      \
	&&OP_MCALL,    \
	&&OP_SMCALL,   \
	&&OP_PROP_R,   \
	&&OP_SPROP_R,  \
	&&OP_PROP_W,   \
	&&OP_SPROP_W,  \
	&&OP_TRY,      \
	&&OP_CATCH,    \
	&&OP_THROW,    \
	&&OP_ETRY,     \
	&&OP_NOT,      \
	&&OP_BW_AND,   \
	&&OP_BW_OR,    \
	&&OP_BW_XOR,   \
	&&OP_BW_NOT,   \
	&&OP_BW_LS,    \
	&&OP_BW_RS,    \
	&&OP_SUBSCRIPT,\
	&&OP_GETITER,  \
	&&OP_VALIDITER,\
	&&OP_NEXTITER, \
	&&OP_CURRITER
#endif

/// VM opcodes
enum Opcode {
	OP_RET,        //   0 - Used for returning
	OP_ASSIGN,     //       Used for variable assignment
	OP_ADD,        //       Used for math sum operation
	OP_SUB,        //       Used for math subtraction operation
	OP_MUL,        //       Used for math multiplication operation
	OP_DIV,        //   5 - Used for math division operation
	OP_MOD,        //       Used for math modulus operation
	OP_JMP,        //       Used for jumping to other instructions
	OP_FCALL,      //       Used for function call
	OP_LEAVE,      //       Used for leaving from a function call
	OP_SEND_VAL,   //       Used for send Value* to argument values,
	OP_JMPZ,       //       Used for jumping if zero
	OP_PRE_INC,    //       Used for pre increment variable
	OP_PRE_DEC,    //  15 - Used for pre decrement variable
	OP_POS_INC,    //       Used for pos increment variable
	OP_POS_DEC,    //       Used for pos decrement variable
	OP_JMPNZ,      //       Used for pos decrement variable
	OP_AND,        //       Used for logical and operation
	OP_OR,         //  20 - Used for logical or operation
	OP_EQUAL,      //       Used for logical equal operation
	OP_NEQUAL,     //       Used for logical not equal operation
	OP_LOCK,       //       Used for lock VM
	OP_UNLOCK,     //       Used for unlock VM
	OP_HALT,       //  25 - Used for halting VM
	OP_GREATER,    //       Used for greater than comparison
	OP_GEQUAL,     //       Used for greater than or equal comparison
	OP_LESS,       //       Used for less than comparison
	OP_LEQUAL,     //       Used for less than or equal comparison
	OP_NEW,        //  30 - Used for less than or equal comparison
	OP_MCALL,      //       Used for method call
	OP_SMCALL,     //       Used for static method call
	OP_PROP_R,     //       Used for property access (read mode)
	OP_SPROP_R,    //       Used for static property access (read mode)
	OP_PROP_W,     //  35 - Used for property access (write mode)
	OP_SPROP_W,    //       Used for static property access (write mode)
	OP_TRY,        //       Used for exception block
	OP_CATCH,      //       Used for catching exception
	OP_THROW,      //       Used for throwing exception
	OP_ETRY,       //  40 - Used for end marker exception block
	OP_NOT,        //       Used for NOT boolean operation
	OP_BW_AND,     //       Used for bitwise AND operation
	OP_BW_OR,      //       Used for bitwise OR operation
	OP_BW_XOR,     //       Used for bitwise XOR operation
	OP_BW_NOT,     //  45 - Used for bitwise NOT operation
	OP_BW_LS,      //       Used for bitwise left shift operation
	OP_BW_RS,      //       Used for bitwise right shift operation
	OP_SUBSCRIPT,  //       Used for subscript operator
	OP_GETITER,    //       Used for fetching an iterator
	OP_VALIDITER,
	OP_NEXTITER,
	OP_CURRITER,
	NUM_OPCODES
};

#ifdef CLEVER_DEBUG
const char* get_opcode_name(Opcode);
#endif

} // clever

#endif // CLEVER_OPCODE_H
