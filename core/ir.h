/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_IR_H
#define CLEVER_IR_H

#include <cstddef>
#include <vector>
#include "core/opcode.h"
#include "core/environment.h"

namespace clever {

class Value;

enum OperandType {
	UNUSED,      // Operand is not used
	FETCH_VAR,   // For fetching a variables
	FETCH_CONST, // For fetching a constant
	FETCH_TMP,   // For fetching a temporary value
	JMP_ADDR     // For instr addr
};

struct Operand {
	OperandType op_type;
	ValueOffset voffset;
	size_t jmp_addr;

	Operand()
		: op_type(UNUSED), voffset(0,0), jmp_addr(0) {}

	Operand(OperandType _op_type)
		: op_type(_op_type), voffset(0,0), jmp_addr(0) {}

	Operand(OperandType op_type_, const ValueOffset& voffset_)
		: op_type(op_type_), voffset(voffset_), jmp_addr(0) {}

	Operand(OperandType op_type_, size_t jmp_addr_)
		: op_type(op_type_), voffset(0,0), jmp_addr(jmp_addr_) {}
};

/// Intermediate representation
struct IR {
	IR(Opcode _op)
		: opcode(_op), op1(), op2(), result() {}

	IR(Opcode _op, Operand _op1)
		: opcode(_op), op1(_op1), op2(), result() {}

	IR(Opcode _op, Operand _op1, Operand _op2)
		: opcode(_op), op1(_op1), op2(_op2), result() {}

	Opcode opcode;
	Operand op1, op2, result;
};

// Vector of VM instructions
typedef std::vector<IR> IRVector;

} // clever

#endif // CLEVER_IR_H
