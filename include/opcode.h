/*
 * Clever language
 * Copyright (c) 2011 Clever Team
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

#include "vm.h"

namespace clever {
/**
 * Opcodes
 */
enum Opcodes {
	OP_PLUS,
	OP_DIV,
	OP_MULT,
	OP_MINUS,
	OP_MOD,
	OP_VAR_DECL,
	OP_BW_OR,
	OP_BW_AND,
	OP_BW_XOR,
	OP_PRE_INC,
	OP_PRE_DEC,
	OP_POS_INC,
	OP_POS_DEC,
	OP_JMPZ,
	OP_JMP,
	OP_GREATER,
	OP_GREATER_EQUAL,
	OP_LESS,
	OP_LESS_EQUAL,
	OP_EQUAL,
	OP_NOT_EQUAL,
	OP_BREAK,
	OP_FCALL,
	OP_MCALL,
	OP_ASSIGN
};

/**
 * Opcode representation
 */
class Opcode {
public:
	Opcode(Opcodes op_type, VM::opcode_handler handler)
		: m_op_type(op_type), m_handler(handler), m_op1(NULL), m_op2(NULL), m_result(NULL) { }

	Opcode(Opcodes op_type, VM::opcode_handler handler, Value* op1)
		: m_op_type(op_type), m_handler(handler), m_op1(op1), m_op2(NULL), m_result(NULL) { }

	Opcode(Opcodes op_type, VM::opcode_handler handler, Value* op1, Value* op2)
		: m_op_type(op_type), m_handler(handler), m_op1(op1), m_op2(op2), m_result(NULL) { }

	Opcode(Opcodes op_type, VM::opcode_handler handler, Value* op1, Value* op2, Value* result)
		: m_op_type(op_type), m_handler(handler), m_op1(op1), m_op2(op2), m_result(result) { }

	~Opcode() { }

	int get_op_type() const { return m_op_type; }

	VM::opcode_handler get_handler() const { return m_handler; }

	Value* get_op1() const { return m_op1; }
	void set_op1(Value* op1) { m_op1 = op1; }

	Value* get_op2() const { return m_op2; }
	void set_op2(Value* op2) { m_op2 = op2; }

	Value* get_result() const { return m_result; }
	void set_result(Value* value) { m_result->set_value(value); }
	void set_result(Value* result, Value* value) const throw();

	int64_t get_op_num() const { return m_op_num; }
	void set_op_num(unsigned int op_num) { m_op_num = op_num; }

	void set_jmp_addr1(unsigned int jmp_addr) { m_extra.jmp1 = jmp_addr; }
	unsigned int get_jmp_addr1() const { return m_extra.jmp1; }

	void set_jmp_addr2(unsigned int jmp_addr) { m_extra.jmp2 = jmp_addr; }
	unsigned int get_jmp_addr2() const { return m_extra.jmp2; }

	void set_flags(unsigned int flags) {	m_extra.flags = flags; }
	unsigned int get_flags() const { return m_extra.flags; }

	/* Debug */
	void dump() const throw();
	const char* getOpName(Opcodes) const throw();
	std::string dumpOp(const char*, Value*) const throw();
private:
	Opcodes m_op_type;
	VM::opcode_handler m_handler;
	Value* m_op1;
	Value* m_op2;
	Value* m_result;
	unsigned int m_op_num;
	struct { unsigned int jmp1, jmp2, flags; } m_extra;

	DISALLOW_COPY_AND_ASSIGN(Opcode);
};

} // clever

#endif // CLEVER_OPCODES_H
