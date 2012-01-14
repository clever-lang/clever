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

#ifndef CLEVER_OPCODES_H
#define CLEVER_OPCODES_H

#include "vm.h"
#include "types/type.h"
#include "compiler/value.h"

namespace clever {

/**
 * Opcodes
 */
enum Opcodes {
	OP_VAR_DECL,
	OP_PRE_INC,
	OP_PRE_DEC,
	OP_POS_INC,
	OP_POS_DEC,
	OP_JMPNZ,
	OP_JMPZ,
	OP_JMP,
	OP_BREAK,
	OP_FCALL,
	OP_MCALL,
	OP_ASSIGN,
	OP_RETURN,
	OP_RECV
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

	int getOpType() const throw() { return m_op_type; }

	VM::opcode_handler getHandler() const throw() { return m_handler; }

	Value* getOp1() const throw() { return m_op1; }
	const Type* getOp1Type() const throw() { return m_op1->getTypePtr(); }
	void setOp1(Value* op1) throw() { m_op1 = op1; }

	Value* getOp2() const throw() { return m_op2; }
	const Type* getOp2Type() const throw() { return m_op2->getTypePtr(); }
	void setOp2(Value* op2) throw() { m_op2 = op2; }

	Value* getResult() const throw() { return m_result; }
	void setResult(Value* result) throw() { m_result = result; }

	long getOpNum() const throw() { return m_op_num; }
	void setOpNum(long op_num) throw() { m_op_num = op_num; }

	void setJmpAddr1(long jmp_addr) throw() { m_extra.jmp1 = jmp_addr; }
	long getJmpAddr1() const throw() { return m_extra.jmp1; }

	void setJmpAddr2(long jmp_addr) throw() { m_extra.jmp2 = jmp_addr; }
	long getJmpAddr2() const throw() { return m_extra.jmp2; }

	void setFlags(long flags) throw() { m_extra.flags = flags; }
	long getFlags() const throw() { return m_extra.flags; }

	/**
	 * Methods for debug
	 */
	void dump() const throw();
	const char* getOpName(Opcodes) const throw();
	std::string dumpOp(const char* const, Value* const) const throw();
private:
	Opcodes m_op_type;
	VM::opcode_handler m_handler;
	Value* m_op1;
	Value* m_op2;
	Value* m_result;
	long m_op_num;
	struct { long jmp1, jmp2, flags; } m_extra;

	DISALLOW_COPY_AND_ASSIGN(Opcode);
};

} // clever

#endif // CLEVER_OPCODES_H
