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
	::printf("%-15s | ", getOpName(getType()));
	::printf("%-30s | ", dumpOp("op1", getOp1()).c_str());
	::printf("%-40s | ", dumpOp("op2", getOp2()).c_str());
	::printf("%-20s\n", dumpOp("result", getResult()).c_str());
}

/**
 * Returns the opcode name
 */
const char* Opcode::getOpName(OpcodeType op) const {
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
		CASE(OP_INIT_VAR);
		CASE(OP_LEAVE);
		default:
			return "UNKNOWN";
	}
}

/**
 * Dumps an operand
 */
std::string Opcode::dumpOp(const char* const label, const Operand& op) const {
	std::ostringstream str;

	str << label;
	str << ": ";

	switch (op.getType()) {
		case UNUSED:
			str << "UNUSED";
			break;
		case ADDR:
			str << op.getAddr();
			break;
		case VALUE:
			str << "(" << op.getValue() << ") ";
			dumpValue(str, op.getValue());
			break;
		case VECTOR:
			if (op.getVector()) {
				str << "vector (";
				dumpVector(str, op.getVector());
				str << ")";
			} else {
				str << "UNUSED";
			}
			break;
	}
	return str.str();
}

/**
 * Dumps a Value* pointer
 */
void Opcode::dumpValue(std::ostringstream& str, Value* value) const {
	if (value == NULL) {
		str << "NULL";
	} else if (value->isCallable()) {
		str << value->getName()->str();
	} else if (value->getType() == Value::NONE) {
		str << "UNKNOWN";
	} else {
		if (value->getTypePtr()) {
			str << value->toString();
		}
	}
}

/**
 * Dumps a ValueVector pointer
 */
void Opcode::dumpVector(std::ostringstream& str, ValueVector* vec) const {
	if (vec->size() == 0) {
		return;
	}
	for (size_t i = 0, j = vec->size(); i < j; ++i) {
		str << vec->at(i);

		if (i == 1 && j > i+1) {
			str << ", ...";
			break;
		}

		if (i+1 < j) {
			str << ", ";
		}
	}
}

/**
 * Returns the opcode handler by supplying its opcode type
 */
VM::opcode_handler Opcode::getHandlerByType(OpcodeType op_type) {
	switch (op_type) {
		case OP_PLUS:    return &VM_H(plus);
		case OP_MINUS:   return &VM_H(minus);
		case OP_DIV:     return &VM_H(div);
		case OP_MULT:    return &VM_H(mult);
		case OP_MOD:     return &VM_H(mod);
		case OP_XOR:     return &VM_H(xor);
		case OP_BW_OR:   return &VM_H(bw_or);
		case OP_BW_AND:  return &VM_H(bw_and);
		case OP_GREATER: return &VM_H(greater);
		case OP_LESS:    return &VM_H(less);
		case OP_GE:      return &VM_H(ge);
		case OP_LE:      return &VM_H(le);
		case OP_EQUAL:   return &VM_H(equal);
		case OP_NE:      return &VM_H(ne);
		case OP_LSHIFT:  return &VM_H(lshift);
		case OP_RSHIFT:  return &VM_H(rshift);
		case OP_PRE_INC: return &VM_H(inc);
		case OP_POS_INC: return &VM_H(inc);
		case OP_PRE_DEC: return &VM_H(dec);
		case OP_POS_DEC: return &VM_H(dec);
		case OP_NOT:     return &VM_H(not);
		case OP_BW_NOT:  return &VM_H(bw_not);
		case OP_INIT_VAR:return &VM_H(init_var);
		default:	     return &VM_H(mcall);
	}
}

} // clever
