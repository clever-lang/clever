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

#include <cstdio>
#include <sstream>
#include "vm/opcode.h"
#include "compiler/value.h"

namespace clever {

/**
 * Dumps an opcode
 */
void Opcode::dump() const {
	::printf("(%04zu) | ", getOpNum());
	::printf("%-15s | ", getOpName(m_op_type));
	::printf("%-20s | ", dumpOp("op1", m_op1).c_str());
	::printf("%-20s | ", dumpOp("op2", m_op2).c_str());
	::printf("%-20s | ", dumpOp("result", m_result).c_str());
	::printf("Addr1: %04ld | ", getJmpAddr1());
	::printf("Addr2: %04ld\n", getJmpAddr2());
}

/**
 * Returns the opcode name
 */
const char* Opcode::getOpName(Opcodes op) const {
#define CASE(x) case x: return #x

	switch (op) {
		CASE(OP_PRE_INC);
		CASE(OP_PRE_DEC);
		CASE(OP_POS_INC);
		CASE(OP_POS_DEC);
		CASE(OP_JMPNZ);
		CASE(OP_JMPZ);
		CASE(OP_JMP);
		CASE(OP_BREAK);
		CASE(OP_MCALL);
		CASE(OP_FCALL);
		CASE(OP_RETURN);
		CASE(OP_REGEX);
		CASE(OP_NOT);
		CASE(OP_BW_NOT);
		CASE(OP_PLUS);
		CASE(OP_DIV);
		CASE(OP_MULT);
		CASE(OP_MINUS);
		CASE(OP_MOD);
		CASE(OP_XOR);
		CASE(OP_BW_OR);
		CASE(OP_BW_AND);
		CASE(OP_GREATER);
		CASE(OP_LESS);
		CASE(OP_GE);
		CASE(OP_LE);
		CASE(OP_EQUAL);
		CASE(OP_NE);
		CASE(OP_LSHIFT);
		CASE(OP_RSHIFT);
		CASE(OP_ASSIGN);
		CASE(OP_AT);
		default:
			return "UNKNOWN";
	}
}

/**
 * Dumps an operand
 */
std::string Opcode::dumpOp(const char* const label, Value* const op) const {
	if (op) {
		std::ostringstream str;
		std::string name = op->getName() && op->isCallable() ?
			op->getName()->str() : op->toString();

		if (op->isVector()) {
			name = "vector";
		}

		str << op->refCount();

		return std::string(std::string(label) + ": " + name + " (#" + str.str() + ")");
	} else {
		return std::string(std::string(label) + ": UNUSED");
	}
}

} // clever
