/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
 *
 * $Id$
 */

#ifndef CLEVER_OPCODES_H
#define CLEVER_OPCODES_H

#include "values.h"
#include "types.h"
#include "vm.h"

namespace clever {

enum Opcodes {
	OP_ECHO,
	OP_PLUS,
	OP_DIV,
	OP_MULT,
	OP_MINUS,
	OP_NEW_SCOPE,
	OP_END_SCOPE,
	OP_VAR_DECL,
	OP_BW_OR,
	OP_BW_AND,
	OP_BW_XOR
};

class Opcode {
public:
	Opcode(Opcodes op_type, VM::opcode_handler handler)
		: m_op_type(op_type), m_handler(handler), m_op1(NULL), m_op2(NULL), m_result(NULL) { }

	Opcode(Opcodes op_type, VM::opcode_handler handler, Value* op1)
		: m_op_type(op_type), m_handler(handler), m_op1(op1), m_op2(NULL), m_result(NULL) { }

	Opcode(Opcodes op_type, VM::opcode_handler handler, Value* op1, Value* op2)
		: m_op_type(op_type), m_handler(handler), m_op1(op1), m_op2(op2), m_result(NULL) { }

	Opcode(Opcodes op_type, VM::opcode_handler handler, Value* op1, Value* op2, TempValue* result)
		: m_op_type(op_type), m_handler(handler), m_op1(op1), m_op2(op2), m_result(result) { }

	Value* get_op1() { return m_op1; }
	Value* get_op2() { return m_op2; }
	Value* get_result() { return m_result; }
	inline VM::opcode_handler get_handler() { return m_handler; }

	inline void set_result(Value* value) {
		m_result->set_value(value);
	}

private:
	VM::opcode_handler m_handler;
	Opcodes m_op_type;
	Value* m_op1;
	Value* m_op2;
	TempValue* m_result;
};

} // clever

#endif // CLEVER_OPCODES_H
