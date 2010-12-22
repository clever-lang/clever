#ifndef CLEVER_OPCODES_H
#define CLEVER_OPCODES_H

#include "types.h"
#include "vm.h"

namespace clever {

enum Opcodes {
	OP_ECHO
};

struct Opcode {
	Opcode(Opcodes op_type, VM::vm_handler handler, Value* op1)
		: m_op_type(op_type), m_handler(handler), m_op1(op1) { }

	VM::vm_handler m_handler;

	Value* get_op1() { return m_op1; }
	Value* get_op2() { return m_op2; }
	Value* get_result() { return m_result; }

private:
	Opcodes m_op_type;
	Value* m_op1;
	Value* m_op2;
	Value* m_result;
};

} // clever

#endif // CLEVER_OPCODES_H