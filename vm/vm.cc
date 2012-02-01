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

#include <iostream>
#include <cstdlib>
#include "compiler/compiler.h"
#include "opcode.h"
#include "vm.h"
#include "types/type.h"
#include "compiler/scope.h"

namespace clever {

CallStack VM::s_call;
ArgStack VM::s_args;
ArgValueStack VM::s_arg_values;

/**
 * Destroy the opcodes data
 */
VM::~VM() {
	OpcodeList::const_iterator it = m_opcodes->begin(), end(m_opcodes->end());

	while (it != end) {
		Value* op1 = (*it)->getOp1();
		Value* op2 = (*it)->getOp2();
		Value* result = (*it)->getResult();

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
 * Pushes the arguments into the call stack
 */
void VM::push_args(ValueVector* vec) {
	ValueVector* vec_copy = new ValueVector;

	s_args.push(vec);

	for (size_t i = 0, j = vec->size(); i < j; ++i) {
		Value* tmp = new Value;

		tmp->copy(vec->at(i));
		vec_copy->push_back(tmp);
	}

	s_arg_values.push(vec_copy);
}

/**
 * Pop arguments onto the call stack
 */
void VM::pop_args(const Opcode* const op) {
	/**
	 * Check if the function has arguments
	 */
	if (op->getOp2() == NULL) {
		return;
	}

	ValueVector* vec_copy = s_arg_values.top();

	for (size_t i = 0, j = vec_copy->size(); i < j; ++i) {
		delete vec_copy->at(i);
	}
	delete vec_copy;

	s_arg_values.pop();

	delete s_args.top();
	s_args.pop();

	if (!s_args.empty()) {
		restore_args();
	}
}

/**
 * Restore the parameter argument values from the previous stack frame
 */
void VM::restore_args() {
	ValueVector* vec = s_args.top();
	ValueVector* vec_copy = s_arg_values.top();

	for (size_t i = 0, j = vec->size(); i < j; ++i) {
		vec->at(i)->copy(vec_copy->at(i));
	}
}

/**
 * Displays an error message and exits
 */
void VM::error(const char* message) {
	std::cerr << "Runtime error: " << message << std::endl;
}

/**
 * Execute the collected opcodes
 */
void VM::run() {
	long last_op = m_opcodes->size();

	for (long next_op = 0; next_op < last_op && next_op >= 0; ++next_op) {
		const Opcode& opcode = *(*m_opcodes)[next_op];

		// opcode.dump();

		/* Invoke the opcode handler */
		opcode.getHandler()(opcode, next_op);
	}
}

/**
 * JMPZ - Jump if zero
 */
CLEVER_VM_HANDLER(VM::jmpz_handler) {
	const Value* const value = opcode.getOp1();
	Value* result = opcode.getResult();

	if (!value->getValueAsBool()) {
		if (result) result->setBoolean(false);
		CLEVER_VM_GOTO(opcode.getJmpAddr1());
	}

	if (result) {
		result->setBoolean(true);
	}
}

/**
 * JMPNZ - Jump if non zero
 */
CLEVER_VM_HANDLER(VM::jmpnz_handler) {
	const Value* const value = opcode.getOp1();

	if (value->getValueAsBool()) {
		opcode.getResult()->setBoolean(true);
		CLEVER_VM_GOTO(opcode.getJmpAddr1());
	}

	opcode.getResult()->setBoolean(false);
}

/**
 * JMP
 */
CLEVER_VM_HANDLER(VM::jmp_handler) {
	CLEVER_VM_GOTO(opcode.getJmpAddr2());
}

/**
 * break
 */
CLEVER_VM_HANDLER(VM::break_handler) {
	CLEVER_VM_GOTO(opcode.getJmpAddr1());
}

void VM::update_vars(Scope* scope, const ValueVector* args) {
	SymbolMap& symbols = scope->getSymbols();
	SymbolMap::const_iterator sym(symbols.begin()), last_sym(symbols.end());
	ValueVector* vec = new ValueVector;
	int i = 0;

	while (sym != last_sym) {
		Symbol* symbol = sym->second;

		if (symbol->isValue()) {
			Value* val = symbol->getValue();
			if (!val->isCallable()) {
				val->copy(args->at(i));
				vec->push_back(val);
				++i;
			}
		}
		++sym;
	}

	push_args(vec);
}

/**
 * func()
 */
CLEVER_VM_HANDLER(VM::fcall_handler) {
	const CallableValue* const func = static_cast<CallableValue*>(opcode.getOp1());
	const Value* const args = opcode.getOp2();
	Value* result = opcode.getResult();
	const ValueVector* const func_args = args ? args->getVector() : NULL;

	if (func->isNearCall()) {
		s_call.push(&opcode);

		if (func_args) {
			update_vars(func->getScope(), func_args);
		}

		func->call(next_op);
	} else {
		/* Call the function */
		func->call(result, func_args);
	}
}

/**
 * var.method()
 */
CLEVER_VM_HANDLER(VM::mcall_handler) {
	const CallableValue* const var = static_cast<CallableValue*>(opcode.getOp1());
	const Value* const args = opcode.getOp2();
	Value* result = opcode.getResult();
	const ValueVector* const func_args = args ? args->getVector() : NULL;

	/* Call the method */
	var->call(result, func_args);
}

/**
 * End function marker
 */
CLEVER_VM_HANDLER(VM::end_func_handler) {
	const Opcode* const op = s_call.top();

	/**
	 * pop + restore arguments from stack
	 */
	pop_args(op);

	s_call.pop();

	/**
	 * Go to after the caller command
	 */
	CLEVER_VM_GOTO(op->getOpNum());
}

/**
 * return x
 */
CLEVER_VM_HANDLER(VM::return_handler) {
	if (!s_call.empty()) {
		const Value* const value = opcode.getOp1();
		const Opcode* call = s_call.top();

		if (value) {
			call->getResult()->copy(value);
		}
		/**
		 * pop + restore arguments from stack
		 */
		pop_args(call);

		s_call.pop();
		/**
		 * Go back to the caller
		 */
		CLEVER_VM_GOTO(call->getOpNum());
	} else {
		/**
		 * Terminates the execution
		 */
		CLEVER_VM_GOTO(-2);
	}
}

} // clever
