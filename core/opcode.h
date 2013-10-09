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
	&&OP_SUBSCRIPT_W,\
	&&OP_SUBSCRIPT_R,\
	&&OP_BIND,     \
	&&OP_BSCOPE,   \
	&&OP_ESCOPE
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
	OP_SEND_VAL,   //  10 - Used for send Value* to argument values,
	OP_JMPZ,       //       Used for jumping if zero
	OP_PRE_INC,    //       Used for pre increment variable
	OP_PRE_DEC,    //       Used for pre decrement variable
	OP_POS_INC,    //       Used for pos increment variable
	OP_POS_DEC,    //  15 - Used for pos decrement variable
	OP_JMPNZ,      //       Used for pos decrement variable
	OP_AND,        //       Used for logical and operation
	OP_OR,         //       Used for logical or operation
	OP_EQUAL,      //       Used for logical equal operation
	OP_NEQUAL,     //  20 - Used for logical not equal operation
	OP_LOCK,       //       Used for lock VM
	OP_UNLOCK,     //       Used for unlock VM
	OP_HALT,       //       Used for halting VM
	OP_GREATER,    //       Used for greater than comparison
	OP_GEQUAL,     //  25 - Used for greater than or equal comparison
	OP_LESS,       //       Used for less than comparison
	OP_LEQUAL,     //       Used for less than or equal comparison
	OP_NEW,        //       Used for less than or equal comparison
	OP_MCALL,      //       Used for method call
	OP_SMCALL,     //  30 - Used for static method call
	OP_PROP_R,     //       Used for property access (read mode)
	OP_SPROP_R,    //       Used for static property access (read mode)
	OP_PROP_W,     //       Used for property access (write mode)
	OP_SPROP_W,    //       Used for static property access (write mode)
	OP_TRY,        //  35 - Used for exception block
	OP_CATCH,      //       Used for catching exception
	OP_THROW,      //       Used for throwing exception
	OP_ETRY,       //       Used for end marker exception block
	OP_NOT,        //       Used for NOT boolean operation
	OP_BW_AND,     //  40 - Used for bitwise AND operation
	OP_BW_OR,      //       Used for bitwise OR operation
	OP_BW_XOR,     //       Used for bitwise XOR operation
	OP_BW_NOT,     //       Used for bitwise NOT operation
	OP_BW_LS,      //       Used for bitwise left shift operation
	OP_BW_RS,      //  45 - Used for bitwise right shift operation
	OP_SUBSCRIPT_W,//       Used for subscript operator (write mode)
	OP_SUBSCRIPT_R,//       Used for subscript operator (read mode)
	OP_BIND,       //       Used for runtime binding
	OP_BSCOPE,     //       Used for begin scope marker
	OP_ESCOPE,     //  50 - Used for end scope marker
	NUM_OPCODES
};

#ifdef CLEVER_DEBUG
const char* get_opcode_name(Opcode);
#endif

} // clever

#endif // CLEVER_OPCODE_H
