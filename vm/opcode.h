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

#include "vm/vm.h"
#include "vm/operand.h"

namespace clever {

/**
 * Opcodes
 */
enum OpcodeType {
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
	OP_RETURN,
	OP_REGEX,
	OP_NOT,
	OP_BW_NOT,
	OP_PLUS,
	OP_DIV,
	OP_MULT,
	OP_MINUS,
	OP_MOD,
	OP_XOR,
	OP_BW_OR,
	OP_BW_AND,
	OP_GREATER,
	OP_LESS,
	OP_GE,
	OP_LE,
	OP_EQUAL,
	OP_NE,
	OP_LSHIFT,
	OP_RSHIFT,
	OP_ASSIGN,
	OP_AT,
	OP_INIT_VAR,
	OP_LEAVE,
	OP_CLONE
};

/**
 * Opcode representation
 */
class Opcode {
public:
	Opcode(OpcodeType op_type, VM::opcode_handler handler)
		: m_type(op_type), m_handler(handler), m_op1(), m_op2(),
			m_result() {}

	Opcode(OpcodeType op_type, VM::opcode_handler handler, Value* op1)
		: m_type(op_type), m_handler(handler), m_op1(op1), m_op2(),
			m_result() {}

	Opcode(OpcodeType op_type, VM::opcode_handler handler, Value* op1, ValueVector* op2)
		: m_type(op_type), m_handler(handler), m_op1(op1), m_op2(op2),
			m_result() {}

	Opcode(OpcodeType op_type, VM::opcode_handler handler, long op1)
		: m_type(op_type), m_handler(handler), m_op1(op1), m_op2(),
			m_result() {}

	Opcode(OpcodeType op_type, VM::opcode_handler handler, Value* op1,
		Value* op2, Value* result)
		: m_type(op_type), m_handler(handler), m_op1(op1), m_op2(op2),
			m_result(result) {}

	Opcode(OpcodeType op_type, VM::opcode_handler handler, Value* op1,
		ValueVector* op2, Value* result)
		: m_type(op_type), m_handler(handler), m_op1(op1), m_op2(op2),
			m_result(result) {}

	~Opcode() {}

	OpcodeType getType() const { return m_type; }

	VM::opcode_handler getHandler() const { return m_handler; }

	const Operand& getOp1() const { return m_op1; }
	Value* getOp1Value() const { return m_op1.getValue(); }
	CallableValue* getOp1Callable() const { return m_op1.getCallable(); }

	const Operand& getOp2() const { return m_op2; }
	Value* getOp2Value() const { return m_op2.getValue(); }
	ValueVector* getOp2Vector() const { return m_op2.getVector(); }

	const Operand& getResult() const { return m_result; }
	Value* getResultValue() const { return m_result.getValue(); }
	void setResult(Value* result) { m_result.setValue(result); }

	// Methods to set and get the opcode number (its position in the vector)
	size_t getOpNum() const { return m_op_num; }
	void setOpNum(size_t op_num) { m_op_num = op_num; }

	void setJmpAddr1(long addr) { m_op1.setAddr(addr); }
	long getJmpAddr1() const { return m_op1.getAddr(); }

	void setJmpAddr2(long addr) { m_op2.setAddr(addr); }
	long getJmpAddr2() const { return m_op2.getAddr(); }

	/**
	 * Methods for debugging purpose
	 */
	void dump() const;
	const char* getOpName(OpcodeType) const;
	std::string dumpOp(const char* const, const Operand&) const;
	void dumpValue(std::ostringstream&, Value*) const;
	void dumpVector(std::ostringstream&, ValueVector*) const;

	// Returns the opcode handler by supplying its opcode type
	static VM::opcode_handler getHandlerByType(OpcodeType);
private:
	OpcodeType m_type;
	VM::opcode_handler m_handler;
	Operand m_op1, m_op2, m_result;
	size_t m_op_num;

	DISALLOW_COPY_AND_ASSIGN(Opcode);
};

} // clever

#endif // CLEVER_OPCODE_H
