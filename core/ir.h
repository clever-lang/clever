/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_IR_H
#define CLEVER_IR_H

#include <vector>
#include "core/opcode.h"

namespace clever {

class Value;

enum OperandType {
	UNUSED,      // Operand is not used
	FETCH_VAL,   // For Value* fetchs
	FETCH_CONST, // For constant Values
	JMP_ADDR     // For instr addr
};

struct Operand {
	OperandType op_type;
	size_t value_id;
	size_t scope_id;

	Operand() : op_type(UNUSED), value_id(0), scope_id(0) {}

	Operand(OperandType _op_type, size_t id)
		: op_type(_op_type), value_id(id), scope_id(0) {}

	Operand(OperandType _op_type, size_t id, size_t scope_id)
		: op_type(_op_type), value_id(id), scope_id(scope_id) {}

};

/// Intermediate representation
struct IR {
	IR(Opcode _op)
		: opcode(_op), op1(), op2(), result(NULL) {}

	IR(Opcode _op, Operand _op1)
		: opcode(_op), op1(_op1), op2(), result(NULL) {}

	IR(Opcode _op, Operand _op1, Operand _op2)
		: opcode(_op), op1(_op1), op2(_op2), result(NULL) {}

	Opcode opcode;
	Operand op1, op2;
	Value* result;
};

// Vector of VM instructions
typedef std::vector<IR> IRVector;

} // clever

#endif // CLEVER_IR_H
