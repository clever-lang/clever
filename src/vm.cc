/*
 * Clever language
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
 *
 * $Id: parser.y 67 2010-12-22 18:55:54Z felipensp $
 */

#include <cstdlib>
#include <iostream>
#include "compiler.h"
#include "opcode.h"
#include "vm.h"

namespace clever {

/*
 * Destroy the opcodes data
 */
VM::~VM(void) {
	OpcodeList::const_iterator it = m_opcodes->begin(), end(m_opcodes->end());

	while (it != end) {
		Value* op1 = (*it)->get_op1();
		Value* op2 = (*it)->get_op2();
		Value* result = (*it)->get_result();

		// (*it)->dump();

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

/*
 * Displays an error message
 */
void VM::error(const char* message) const throw() {
	std::cerr << "Runtime error: " << message << std::endl;
	exit(1);
}

/*
 * Execute the collected opcodes
 */
void VM::run(void) throw() {
	unsigned int next_op, last_op = m_opcodes->size();

	/* Initializes global scope */
	m_symbols.pushVarMap(SymbolTable::var_map());

	for (next_op = 0; next_op < last_op; ++next_op) {
		Opcode& opcode = *(*m_opcodes)[next_op];

		// opcode.dump();

		/* Invoke the opcode handler */
		(this->*(opcode.get_handler()))(next_op, opcode);
	}

	/* Pop global scope */
	m_symbols.popVarMap();
}

/*
 * x + y
 */
CLEVER_VM_HANDLER(VM::plus_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		switch (op1->get_type()) {
			case Value::STRING:
				opcode.set_result(new ConstantValue(CSTRING(op1->getString() + op2->getString())));
				break;
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() + op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode.set_result(new ConstantValue(op1->getDouble() + op2->getDouble()));
				break;
		}
	}
}

/*
 * x / y
 */
CLEVER_VM_HANDLER(VM::div_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() / op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode.set_result(new ConstantValue(op1->getDouble() / op2->getDouble()));
				break;
		}
	}
}

/*
 * x - y
 */
CLEVER_VM_HANDLER(VM::minus_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() - op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode.set_result(new ConstantValue(op1->getDouble() - op2->getDouble()));
				break;
		}
	}
}

/*
 * x * y
 */
CLEVER_VM_HANDLER(VM::mult_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() * op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode.set_result(new ConstantValue(op1->getDouble() * op2->getDouble()));
				break;
		}
	}
}

/*
 * x & y
 */
CLEVER_VM_HANDLER(VM::bw_and_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() & op2->getInteger()));
				break;
		}
	}
}

/*
 * x ^ y
 */
CLEVER_VM_HANDLER(VM::bw_xor_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() ^ op2->getInteger()));
				break;
		}
	}
}

/*
 * x | y
 */
CLEVER_VM_HANDLER(VM::bw_or_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() | op2->getInteger()));
				break;
		}
	}
}

/*
 * x % y
 */
CLEVER_VM_HANDLER(VM::mod_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() % op2->getInteger()));
				break;
		}
	}
}

/*
 * {
 */
CLEVER_VM_HANDLER(VM::new_scope_handler) {
	/*
	 * Just create a new scope if a variable was created in the block
	 * (detected in compile-time)
	 */
	if (opcode.get_flags() == BLK_USED) {
		/* Create a new scope */
		m_symbols.pushVarMap(SymbolTable::var_map());
	}
}

/*
 * }
 */
CLEVER_VM_HANDLER(VM::end_scope_handler) {
	if (opcode.get_flags() == BLK_USED) {
		/* Remove the newest scope */
		m_symbols.popVarMap();
	}
}

/*
 * Type var [= value ]
 */
CLEVER_VM_HANDLER(VM::var_decl_handler) {
	Value* value = getValue(opcode.get_op2());

	/* TODO: Make the type initialization here */
	if (!value) {
		error("Uninitialized variable!");
	}
	value->addRef();

	/* Register the variable in the current scope */
	m_symbols.register_var(opcode.get_op1(), value);
}

/*
 * ++x
 */
CLEVER_VM_HANDLER(VM::pre_inc_handler) {
	Value* value = getValue(opcode.get_op1());
	Value* result = getValue(opcode.get_result());

	if (value->isConst()) {
		switch (value->get_type()) {
			case Value::INTEGER:
				value->setInteger(value->getInteger()+1);
				break;
			case Value::DOUBLE:
				value->setDouble(value->getDouble()+1);
				break;
		}
		opcode.set_result(result, value);
	}
}

/*
 * x++
 */
CLEVER_VM_HANDLER(VM::pos_inc_handler) {
	Value* value = getValue(opcode.get_op1());
	Value* result = getValue(opcode.get_result());

	if (value->isConst()) {
		opcode.set_result(result, value);
		switch (value->get_type()) {
			case Value::INTEGER:
				value->setInteger(value->getInteger()+1);
				break;
			case Value::DOUBLE:
				value->setDouble(value->getDouble()+1);
				break;
		}
	}
}

/*
 * --x
 */
CLEVER_VM_HANDLER(VM::pre_dec_handler) {
	Value* value = getValue(opcode.get_op1());
	Value* result = getValue(opcode.get_result());

	if (value->isConst()) {
		switch (value->get_type()) {
			case Value::INTEGER:
				value->setInteger(value->getInteger()-1);
				break;
			case Value::DOUBLE:
				value->setDouble(value->getDouble()-1);
				break;
		}
		opcode.set_result(result, value);
	}
}

/*
 * x--
 */
CLEVER_VM_HANDLER(VM::pos_dec_handler) {
	Value* value = getValue(opcode.get_op1());
	Value* result = getValue(opcode.get_result());

	if (value->isConst()) {
		opcode.set_result(result, value);
		switch (value->get_type()) {
			case Value::INTEGER:
				value->setInteger(value->getInteger()-1);
				break;
			case Value::DOUBLE:
				value->setDouble(value->getDouble()-1);
				break;
		}
	}
}

/*
 * JMPZ
 */
CLEVER_VM_HANDLER(VM::jmpz_handler) {
	Value* value = getValue(opcode.get_op1());

	if (value->isConst()) {
		switch (value->get_type()) {
			case Value::INTEGER:
				if (!value->getInteger()) {
					CLEVER_VM_GOTO(opcode.get_jmp_addr1());
				}
				break;
			case Value::DOUBLE:
				if (!value->getDouble()) {
					CLEVER_VM_GOTO(opcode.get_jmp_addr1());
				}
				break;
			case Value::BOOLEAN:
				if (!value->getBoolean()) {
					CLEVER_VM_GOTO(opcode.get_jmp_addr1());
				}
				break;
		}
	}
}

/*
 * JMP
 */
CLEVER_VM_HANDLER(VM::jmp_handler) {
	CLEVER_VM_GOTO(opcode.get_jmp_addr2());
}

/*
 * x > y
 */
CLEVER_VM_HANDLER(VM::greater_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2) && op1->hasSameType(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(bool(op1->getInteger() > op2->getInteger())));
				break;
			case Value::DOUBLE:
				opcode.set_result(new ConstantValue(op1->getDouble() > op2->getDouble()));
				break;
		}
	}
}

/*
 * x >= y
 */
CLEVER_VM_HANDLER(VM::greater_equal_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2) && op1->hasSameType(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() >= op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode.set_result(new ConstantValue(op1->getDouble() >= op2->getDouble()));
				break;
		}
	}
}

/*
 * x < y
 */
CLEVER_VM_HANDLER(VM::less_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2) && op1->hasSameType(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() < op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode.set_result(new ConstantValue(op1->getDouble() < op2->getDouble()));
				break;
		}
	}
}

/*
 * x <= y
 */
CLEVER_VM_HANDLER(VM::less_equal_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2) && op1->hasSameType(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() <= op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode.set_result(new ConstantValue(op1->getDouble() <= op2->getDouble()));
				break;
		}
	}
}

/*
 * break
 */
CLEVER_VM_HANDLER(VM::break_handler) {
	CLEVER_VM_GOTO(opcode.get_jmp_addr1());
}

/*
 * x == y
 */
CLEVER_VM_HANDLER(VM::equal_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2) && op1->hasSameType(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() == op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode.set_result(new ConstantValue(op1->getDouble() == op2->getDouble()));
				break;
		}
	}
}

/*
 * x != y
 */
CLEVER_VM_HANDLER(VM::not_equal_handler) {
	Value* op1 = getValue(opcode.get_op1());
	Value* op2 = getValue(opcode.get_op2());

	if (op1->isConst() && op1->hasSameKind(op2) && op1->hasSameType(op2)) {
		switch (op1->get_type()) {
			case Value::INTEGER:
				opcode.set_result(new ConstantValue(op1->getInteger() != op2->getInteger()));
				break;
			case Value::DOUBLE:
				opcode.set_result(new ConstantValue(op1->getDouble() != op2->getDouble()));
				break;
		}
	}
}

/*
 * func()
 */
CLEVER_VM_HANDLER(VM::fcall_handler) {
	const Function& func = Compiler::getFunction(opcode.get_op1()->getString());
	Value* args = opcode.get_op2();
	FunctionArgs func_args;

	if (args) {
		ValueVector* vec_args = args->getVector();
		ValueVector::const_iterator it = vec_args->begin(), end(vec_args->end());

		func_args.reserve(vec_args->size());

		while (it != end) {
			func_args.push_back(getValue(*it));
			++it;
		}
	}

	/* Call the function */
	func.get_func()(func_args);
}

/*
 * var.method()
 */
CLEVER_VM_HANDLER(VM::mcall_handler) {

}

} // clever
