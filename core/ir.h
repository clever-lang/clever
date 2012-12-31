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
	size_t op_type;
	size_t value_id;
	size_t scope_id;
};

/// Intermediate representation
struct IR {
	IR(Opcode _op)
		: opcode(_op),
			op1_type(UNUSED), op2_type(UNUSED),
			op1(0), op2(0),
			op1_scope(0), op2_scope(0),
			result(NULL) {}

	IR(Opcode _op, OperandType _op1_type, size_t _op1, Value* res = NULL)
		: opcode(_op),
			op1_type(_op1_type), op2_type(UNUSED),
			op1(_op1), op2(0),
			op1_scope(0), op2_scope(0),
			result(res) {}

	IR(Opcode _op, OperandType _op1_type, size_t _op1,
		OperandType _op2_type, size_t _op2, Value* res = NULL)
		: opcode(_op),
			op1_type(_op1_type), op2_type(_op2_type),
			op1(_op1), op2(_op2),
			op1_scope(0), op2_scope(0),
			result(res) {}

	Opcode opcode;
	OperandType op1_type, op2_type;
	size_t op1, op2;
	size_t op1_scope, op2_scope;
	Value* result;
};

// Vector of VM instructions
typedef std::vector<IR> IRVector;

} // clever

#endif // CLEVER_IR_H
