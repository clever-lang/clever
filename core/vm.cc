/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
 *
 * $Id: parser.y 67 2010-12-22 18:55:54Z felipensp $
 */

#include <cstdlib>
#include <iostream>
#include "opcodes.h"
#include "vm.h"

namespace clever {

/*
 * Destroy the opcodes data
 */
VM::~VM(void) {
	OpcodeList::iterator it = m_opcodes->begin();

	while (it < m_opcodes->end()) {
		if ((*it)->get_op1()) {
			(*it)->get_op1()->delRef();
		}
		if ((*it)->get_op2()) {
			(*it)->get_op2()->delRef();
		}
		if ((*it)->get_result()) {
			(*it)->get_result()->delRef();
		}
		delete *it;
		++it;
	}
}

/*
 * Displays an error message
 */
void VM::error(const char* message) const {
	std::cout << "Runtime error: " << message << std::endl;
	exit(1);
}

/*
 * Execute the collected opcodes
 */
void VM::run(void) {
	OpcodeList::iterator it = m_opcodes->begin();

	m_symbols.pushVarMap(SymbolTable::var_map());

	while (it < m_opcodes->end()) {
		Opcode* opcode = *it;

		(this->*((*it)->get_handler()))(*it);
		++it;
	}

	m_symbols.popVarMap();
}

/*
 * echo statemenet
 */
void VM::echo_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* op1 = getValue(opcode->get_op1());

	std::cout << op1->toString() << std::endl;
}

/*
 * x + y
 */
void VM::plus_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* op1 = getValue(opcode->get_op1());
	Value* op2 = getValue(opcode->get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		if (!op1->hasSameType(op2)) {
			error("Type mismatch!");
		}
		switch (op1->get_type()) {
			case Value::STRING:
				opcode->set_result(new ConstantValue(CSTRING(op1->getString() + op2->getString())));
				break;
			case Value::INTEGER:
				opcode->set_result(new ConstantValue(op1->getInteger() + op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode->set_result(new ConstantValue(op1->getDouble() + op2->getDouble()));
				break;
		}
	}
}

/*
 * x / y
 */
void VM::div_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* op1 = getValue(opcode->get_op1());
	Value* op2 = getValue(opcode->get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		if (!op1->hasSameType(op2)) {
			error("Type mismatch!");
		}
		switch (op1->get_type()) {
			case Value::STRING:
				error("Operation not allow in strings!");
				break;
			case Value::INTEGER:
				opcode->set_result(new ConstantValue(op1->getInteger() / op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode->set_result(new ConstantValue(op1->getDouble() / op2->getDouble()));
				break;
		}
	}
}

/*
 * x - y
 */
void VM::minus_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* op1 = getValue(opcode->get_op1());
	Value* op2 = getValue(opcode->get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		if (!op1->hasSameType(op2)) {
			error("Type mismatch!");
		}
		switch (op1->get_type()) {
			case Value::STRING:
				error("Operation not allow in strings!");
				break;
			case Value::INTEGER:
				opcode->set_result(new ConstantValue(op1->getInteger() - op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode->set_result(new ConstantValue(op1->getDouble() - op2->getDouble()));
				break;
		}
	}
}

/*
 * x * y
 */
void VM::mult_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* op1 = getValue(opcode->get_op1());
	Value* op2 = getValue(opcode->get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		if (!op1->hasSameType(op2)) {
			error("Type mismatch!");
		}
		switch (op1->get_type()) {
			case Value::STRING:
				error("Operation not allow in strings!");
				break;
			case Value::INTEGER:
				opcode->set_result(new ConstantValue(op1->getInteger() * op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode->set_result(new ConstantValue(op1->getDouble() * op2->getDouble()));
				break;
		}
	}
}

/*
 * x & y
 */
void VM::bw_and_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* op1 = getValue(opcode->get_op1());
	Value* op2 = getValue(opcode->get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		if (!op1->hasSameType(op2)) {
			error("Type mismatch!");
		}
		switch (op1->get_type()) {
			case Value::STRING:
			case Value::DOUBLE:
				error("Operation not allow for such type!");
				break;
			case Value::INTEGER:
				opcode->set_result(new ConstantValue(op1->getInteger() & op2->getInteger()));
				break;
		}
	}
}

/*
 * x ^ y
 */
void VM::bw_xor_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* op1 = getValue(opcode->get_op1());
	Value* op2 = getValue(opcode->get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		if (!op1->hasSameType(op2)) {
			error("Type mismatch!");
		}
		switch (op1->get_type()) {
			case Value::STRING:
			case Value::DOUBLE:
				error("Operation not allow for such type!");
				break;
			case Value::INTEGER:
				opcode->set_result(new ConstantValue(op1->getInteger() ^ op2->getInteger()));
				break;
		}
	}
}

/*
 * x | y
 */
void VM::bw_or_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* op1 = getValue(opcode->get_op1());
	Value* op2 = getValue(opcode->get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		if (!op1->hasSameType(op2)) {
			error("Type mismatch!");
		}
		switch (op1->get_type()) {
			case Value::STRING:
			case Value::DOUBLE:
				error("Operation not allow for such type!");
				break;
			case Value::INTEGER:
				opcode->set_result(new ConstantValue(op1->getInteger() | op2->getInteger()));
				break;
		}
	}
}

/*
 * {
 */
void VM::new_scope_handler(CLEVER_VM_HANDLER_ARGS) {
	m_symbols.pushVarMap(SymbolTable::var_map());
}

/*
 * }
 */
void VM::end_scope_handler(CLEVER_VM_HANDLER_ARGS) {
	m_symbols.popVarMap();
}

/*
 * Type var
 */
void VM::var_decl_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* value = getValue(opcode->get_op2());

	/* TODO: Make the type initialization here */
	if (!value) {
		error("Uninitialized variable!");
	}
	value->addRef();

	m_symbols.register_var(opcode->get_op1()->toString(), value);
}

/*
 * ++x
 */
void VM::pre_inc_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* value = getValue(opcode->get_op1());

	if (value->isConst()) {
		switch (value->get_type()) {
			case Value::INTEGER:
				value->setInteger(value->getInteger()+1);
				opcode->set_result(new ConstantValue(value->getInteger()));
				break;
			case Value::DOUBLE:
				value->setDouble(value->getDouble()+1);
				opcode->set_result(new ConstantValue(value->getDouble()));
				break;
			default:
				error("Operation unsupported for such type");
				break;
		}
	}
}

/*
 * x++
 */
void VM::pos_inc_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* value = getValue(opcode->get_op1());

	if (value->isConst()) {
		switch (value->get_type()) {
			case Value::INTEGER:
				opcode->set_result(new ConstantValue(value->getInteger()));
				value->setInteger(value->getInteger()+1);
				break;
			case Value::DOUBLE:
				opcode->set_result(new ConstantValue(value->getDouble()));
				value->setDouble(value->getDouble()+1);
				break;
			default:
				error("Operation unsupported for such type");
				break;
		}
	}
}

/*
 * --x
 */
void VM::pre_dec_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* value = getValue(opcode->get_op1());

	if (value->isConst()) {
		switch (value->get_type()) {
			case Value::INTEGER:
				value->setInteger(value->getInteger()-1);
				opcode->set_result(new ConstantValue(value->getInteger()));
				break;
			case Value::DOUBLE:
				value->setDouble(value->getDouble()-1);
				opcode->set_result(new ConstantValue(value->getDouble()));
				break;
			default:
				error("Operation unsupported for such type");
				break;
		}
	}
}

/*
 * x--
 */
void VM::pos_dec_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* value = getValue(opcode->get_op1());

	if (value->isConst()) {
		switch (value->get_type()) {
			case Value::INTEGER:
				opcode->set_result(new ConstantValue(value->getInteger()));
				value->setInteger(value->getInteger()-1);
				break;
			case Value::DOUBLE:
				opcode->set_result(new ConstantValue(value->getDouble()));
				value->setDouble(value->getDouble()-1);
				break;
			default:
				error("Operation unsupported for such type");
				break;
		}
	}
}

} // clever
