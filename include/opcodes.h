#ifndef CLEVER_OPCODES_H
#define CLEVER_OPCODES_H

#include "types.h"
#include "vm.h"

namespace clever {

enum Opcodes {
	OP_ECHO,
	OP_PLUS
};

struct Opcode {
	Opcode(Opcodes op_type, VM::vm_handler handler, Value* op1)
		: m_op_type(op_type), m_handler(handler), m_op1(op1), m_op2(NULL), m_result(NULL) { }

	Opcode(Opcodes op_type, VM::vm_handler handler, Value* op1, Value* op2)
		: m_op_type(op_type), m_handler(handler), m_op1(op1), m_op2(op2), m_result(NULL) { }

	Opcode(Opcodes op_type, VM::vm_handler handler, Value* op1, Value* op2, Value* result)
		: m_op_type(op_type), m_handler(handler), m_op1(op1), m_op2(op2), m_result(result) { }

	VM::vm_handler m_handler;

	Value* get_op1() { return m_op1; }
	Value* get_op2() { return m_op2; }
	Value* get_result() { return m_result; }
	void set_result(Value* value) { m_result = value; }

private:
	Opcodes m_op_type;
	Value* m_op1;
	Value* m_op2;
	Value* m_result;
};

} // clever

#endif // CLEVER_OPCODES_H