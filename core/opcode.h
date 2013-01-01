/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_OPCODE_H
#define CLEVER_OPCODE_H

namespace clever {

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
	OP_TCALL,      //       Used for thread call
	OP_ETHREAD,    //  10 - Used for end thread marker
	OP_LEAVE,      //       Used for leaving from a function call
	OP_SEND_VAL,   //       Used for send Value* to argument values,
	OP_JMPZ,       //       Used for jumping if zero
	OP_PRE_INC,    //       Used for pre increment variable
	OP_PRE_DEC,    //  15 - Used for pre decrement variable
	OP_POS_INC,    //       Used for pos increment variable
	OP_POS_DEC,    //       Used for pos decrement variable
	OP_JMPNZ,      //       Used for pos decrement variable
	NUM_OPCODES
};

#ifdef CLEVER_DEBUG
const char* get_opcode_name(Opcode);
#endif

} // clever

#endif // CLEVER_OPCODE_H
