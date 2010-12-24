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

	if (op1->isConst() && op1->hasSameKind(op2) && op1->hasSameType(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode->get_result()->set_value(new ConstantValue(op1->getInteger() + op2->getInteger()));
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

	if (op1->isConst() && op1->hasSameKind(op2) && op1->hasSameType(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode->get_result()->set_value(new ConstantValue(op1->getInteger() / op2->getInteger()));
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

	if (op1->isConst() && op1->hasSameKind(op2) && op1->hasSameType(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode->get_result()->set_value(new ConstantValue(op1->getInteger() - op2->getInteger()));
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

	if (op1->isConst() && op1->hasSameKind(op2) && op1->hasSameType(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode->get_result()->set_value(new ConstantValue(op1->getInteger() * op2->getInteger()));
				break;
		}
	}
}

void VM::new_scope_handler(CLEVER_VM_HANDLER_ARGS) {
}

void VM::end_scope_handler(CLEVER_VM_HANDLER_ARGS) {
}

void VM::var_decl_handler(CLEVER_VM_HANDLER_ARGS) {
	Value* value = opcode->get_op2();

	value->addRef();

	m_symbols.register_var(opcode->get_op1()->toString(), value);
}

} // clever
