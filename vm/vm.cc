/**
 * Clever programming language
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
 */

#include <cstdlib>
#include <iostream>
#include "compiler/compiler.h"
#include "opcode.h"
#include "vm.h"
#include "types/type.h"

namespace clever {

CallStack VM::s_call;

/**
 * Destroy the opcodes data
 */
VM::~VM() {
	OpcodeList::const_iterator it = m_opcodes->begin(), end(m_opcodes->end());

	while (it != end) {
		Value* op1 = (*it)->get_op1();
		Value* op2 = (*it)->get_op2();
		Value* result = (*it)->get_result();

		if (op1) {
			op1->delRef();
		}
		if (op2) {
			op2->delRef();
		}
		if (result) {
			result->delRef();
		}
		delete *it;
		++it;
	}
}

/**
 * Displays an error message and exits
 */
void VM::error(const char* message) throw() {
	std::cerr << "Runtime error: " << message << std::endl;
	exit(1);
}

/**
 * Execute the collected opcodes
 */
void VM::run() throw() {
	long next_op;
	long last_op = m_opcodes->size();

	for (next_op = 0; next_op < last_op && next_op >= 0; ++next_op) {
		Opcode& opcode = *(*m_opcodes)[next_op];

		// opcode.dump();

		/* Invoke the opcode handler */
		opcode.get_handler()(opcode, next_op);
	}
}

/**
 * x + y
 */
CLEVER_VM_HANDLER(VM::plus_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::STRING:
			result->setString(CSTRING(op1->getString() + op2->getString()));
			break;
		case Value::INTEGER:
			result->setInteger(op1->getInteger() + op2->getInteger());
			break;
		case Value::DOUBLE:
			result->setDouble(op1->getDouble() + op2->getDouble());
			break;
	}
}

/**
 * x / y
 */
CLEVER_VM_HANDLER(VM::div_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setInteger(op1->getInteger() / op2->getInteger());
			break;
		case Value::DOUBLE:
			result->setDouble(op1->getDouble() / op2->getDouble());
			break;
	}
}

/**
 * x - y
 */
CLEVER_VM_HANDLER(VM::minus_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setInteger(op1->getInteger() - op2->getInteger());
			break;
		case Value::DOUBLE:
			result->setDouble(op1->getDouble() - op2->getDouble());
			break;
	}
}

/**
 * x * y
 */
CLEVER_VM_HANDLER(VM::mult_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setInteger(op1->getInteger() * op2->getInteger());
			break;
		case Value::DOUBLE:
			result->setDouble(op1->getDouble() * op2->getDouble());
			break;
	}
}

/**
 * x & y
 */
CLEVER_VM_HANDLER(VM::bw_and_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setInteger(op1->getInteger() & op2->getInteger());
			break;
	}
}

/**
 * x ^ y
 */
CLEVER_VM_HANDLER(VM::bw_xor_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setInteger(op1->getInteger() ^ op2->getInteger());
			break;
	}
}

/**
 * x | y
 */
CLEVER_VM_HANDLER(VM::bw_or_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setInteger(op1->getInteger() | op2->getInteger());
			break;
	}
}

/**
 * x % y
 */
CLEVER_VM_HANDLER(VM::mod_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setInteger(op1->getInteger() % op2->getInteger());
			break;
	}
}

/**
 * Type var [= value ]
 */
CLEVER_VM_HANDLER(VM::var_decl_handler) {
	const Value* value = opcode.get_op2();

	if (value) {
		opcode.get_op1()->copy(value);
	}
}

/**
 * ++x
 */
CLEVER_VM_HANDLER(VM::pre_inc_handler) {
	Value* value = opcode.get_op1();
	Value* result = opcode.get_result();

	switch (value->get_type()) {
		case Value::INTEGER:
			value->setInteger(value->getInteger()+1);
			break;
		case Value::DOUBLE:
			value->setDouble(value->getDouble()+1);
			break;
	}
	result->copy(value);
}

/**
 * x++
 */
CLEVER_VM_HANDLER(VM::pos_inc_handler) {
	Value* value = opcode.get_op1();
	Value* result = opcode.get_result();

	result->copy(value);
	switch (value->get_type()) {
		case Value::INTEGER:
			value->setInteger(value->getInteger()+1);
			break;
		case Value::DOUBLE:
			value->setDouble(value->getDouble()+1);
			break;
	}
}

/**
 * --x
 */
CLEVER_VM_HANDLER(VM::pre_dec_handler) {
	Value* value = opcode.get_op1();
	Value* result = opcode.get_result();

	switch (value->get_type()) {
		case Value::INTEGER:
			value->setInteger(value->getInteger()-1);
			break;
		case Value::DOUBLE:
			value->setDouble(value->getDouble()-1);
			break;
	}
	result->copy(value);
}

/**
 * x--
 */
CLEVER_VM_HANDLER(VM::pos_dec_handler) {
	Value* value = opcode.get_op1();
	Value* result = opcode.get_result();

	result->copy(value);
	switch (value->get_type()) {
		case Value::INTEGER:
			value->setInteger(value->getInteger()-1);
			break;
		case Value::DOUBLE:
			value->setDouble(value->getDouble()-1);
			break;
	}
}

/**
 * JMPZ - Jump if zero
 */
CLEVER_VM_HANDLER(VM::jmpz_handler) {
	Value* value = opcode.get_op1();
	Value* result = opcode.get_result();

	switch (value->get_type()) {
		case Value::INTEGER:
			if (!value->getInteger()) {
				if (result) {
					result->setBoolean(false);
				}
				CLEVER_VM_GOTO(opcode.get_jmp_addr1());
			}
			break;
		case Value::DOUBLE:
			if (!value->getDouble()) {
				if (result) {
					result->setBoolean(false);
				}
				CLEVER_VM_GOTO(opcode.get_jmp_addr1());
			}
			break;
		case Value::BOOLEAN:
			if (!value->getBoolean()) {
				if (result) {
					result->setBoolean(false);
				}
				CLEVER_VM_GOTO(opcode.get_jmp_addr1());
			}
			break;
	}
	if (result) {
		result->setBoolean(true);
	}
}

/**
 * JMPNZ - Jump if non zero
 */
CLEVER_VM_HANDLER(VM::jmpnz_handler) {
	Value* value = opcode.get_op1();

	switch (value->get_type()) {
		case Value::INTEGER:
			if (value->getInteger()) {
				opcode.get_result()->setBoolean(true);
				CLEVER_VM_GOTO(opcode.get_jmp_addr1());
			}
			break;
		case Value::DOUBLE:
			if (value->getDouble()) {
				opcode.get_result()->setBoolean(true);
				CLEVER_VM_GOTO(opcode.get_jmp_addr1());
			}
			break;
		case Value::BOOLEAN:
			if (value->getBoolean()) {
				opcode.get_result()->setBoolean(true);
				CLEVER_VM_GOTO(opcode.get_jmp_addr1());
			}
			break;
	}
	opcode.get_result()->setBoolean(false);
}

/**
 * JMP
 */
CLEVER_VM_HANDLER(VM::jmp_handler) {
	CLEVER_VM_GOTO(opcode.get_jmp_addr2());
}

/**
 * x > y
 */
CLEVER_VM_HANDLER(VM::greater_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setBoolean(op1->getInteger() > op2->getInteger());
			break;
		case Value::DOUBLE:
			result->setBoolean(op1->getDouble() > op2->getDouble());
			break;
	}
}

/**
 * x >= y
 */
CLEVER_VM_HANDLER(VM::greater_equal_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setBoolean(op1->getInteger() >= op2->getInteger());
			break;
		case Value::DOUBLE:
			result->setBoolean(op1->getDouble() >= op2->getDouble());
			break;
	}
}

/**
 * x < y
 */
CLEVER_VM_HANDLER(VM::less_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setBoolean(op1->getInteger() < op2->getInteger());
			break;
		case Value::DOUBLE:
			result->setBoolean(op1->getDouble() < op2->getDouble());
			break;
	}
}

/**
 * x <= y
 */
CLEVER_VM_HANDLER(VM::less_equal_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setBoolean(op1->getInteger() <= op2->getInteger());
			break;
		case Value::DOUBLE:
			result->setBoolean(op1->getDouble() <= op2->getDouble());
			break;
	}
}

/**
 * break
 */
CLEVER_VM_HANDLER(VM::break_handler) {
	CLEVER_VM_GOTO(opcode.get_jmp_addr1());
}

/**
 * x == y
 */
CLEVER_VM_HANDLER(VM::equal_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setBoolean(op1->getInteger() == op2->getInteger());
			break;
		case Value::DOUBLE:
			result->setBoolean(op1->getDouble() == op2->getDouble());
			break;
	}
}

/**
 * x != y
 */
CLEVER_VM_HANDLER(VM::not_equal_handler) {
	Value* op1 = opcode.get_op1();
	Value* op2 = opcode.get_op2();
	Value* result = opcode.get_result();

	switch (op1->get_type()) {
		case Value::INTEGER:
			result->setBoolean(op1->getInteger() != op2->getInteger());
			break;
		case Value::DOUBLE:
			result->setBoolean(op1->getDouble() != op2->getDouble());
			break;
	}
}

/**
 * func()
 */
CLEVER_VM_HANDLER(VM::fcall_handler) {
	CallableValue* func = static_cast<CallableValue*>(opcode.get_op1());
	Value* args = opcode.get_op2();
	Value* result = opcode.get_result();
	const ValueVector* func_args = args ? args->getVector() : NULL;

	result->initialize();

	if (func->isNearCall()) {
		s_call.push(&opcode);

		func->call(next_op);
	} else {
		/* Call the function */
		func->call(result, func_args);
	}
}

/**
 * Argument receiver
 */
CLEVER_VM_HANDLER(VM::arg_recv_handler) {
	ValueVector* vars = opcode.get_op1()->getVector();
	ValueVector* func_args = opcode.get_op2()->getVector();

	for (int i = 0, j = vars->size(); i < j; ++i) {
		vars->at(i)->copy(func_args->at(i));
	}
}

/**
 * var.method()
 */
CLEVER_VM_HANDLER(VM::mcall_handler) {
	CallableValue* var = static_cast<CallableValue*>(opcode.get_op1());
	Value* args = opcode.get_op2();
	Value* result = opcode.get_result();
	const ValueVector* func_args = args ? args->getVector() : NULL;

	result->initialize();

	/* Call the method */
	var->call(result, func_args);
}

/**
 * x = y
 */
CLEVER_VM_HANDLER(VM::assign_handler) {
	opcode.get_op1()->copy(opcode.get_op2());
}

/**
 * End function marker
 */
CLEVER_VM_HANDLER(VM::end_func_handler) {
	Opcode* op = s_call.top();

	s_call.pop();

	/**
	 * Go to after the caller command
	 */
	CLEVER_VM_GOTO(op->get_op_num());
}

/**
 * return x
 */
CLEVER_VM_HANDLER(VM::return_handler) {
	if (!s_call.empty()) {
		Value* value = opcode.get_op1();
		Opcode* call = s_call.top();

		if (value) {
			call->get_result()->copy(value);
		}
		s_call.pop();
		/**
		 * Go back to the caller
		 */
		CLEVER_VM_GOTO(call->get_op_num());
	} else {
		/**
		 * Terminates the execution
		 */
		CLEVER_VM_GOTO(-2);
	}
}

} // clever
