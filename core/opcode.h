/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef CLEVER_OPCODE_H
#define CLEVER_OPCODE_H

namespace clever {

/// VM opcodes
enum Opcode {
	OP_RET,      //   0 - Used for returning
	OP_ASSIGN,   //       Used for variable assignment
	OP_ADD,      //       Used for math sum operation
	OP_SUB,      //       Used for math subtraction operation
	OP_MUL,      //       Used for math multiplication operation
	OP_DIV,      //   5 - Used for math division operation
	OP_MOD,      //       Used for math modulus operation
	OP_JMP,      //       Used for jumping to other instructions
	OP_FCALL,    //       Used for function call
    OP_TCALL,    //       Used for thread call
    OP_END_THREAD, //     End thread marker
	OP_LEAVE,    //       Used for leaving from a function call
	OP_SEND_VAL, //  10 - Used for send Value* to argument values,
	OP_JMPZ,     //       Used for jumping if zero
	OP_PRE_INC,  //       Used for pre increment variable
	OP_PRE_DEC,  //       Used for pre decrement variable
	OP_POS_INC,  //       Used for pos increment variable
	OP_POS_DEC,  //  15 - Used for pos decrement variable
	NUM_OPCODES
};

#ifdef CLEVER_DEBUG
const char* get_opcode_name(Opcode);
#endif

} // clever

#endif // CLEVER_OPCODE_H
