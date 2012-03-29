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
#include "vm/vm.h"
#include "vm/opcode.h"
#include "compiler/compiler.h"
#include "compiler/scope.h"

namespace clever {

ExecVars VM::s_vars;
VMVars* VM::s_var;
const OpcodeList* VM::s_opcodes;
const Value* VM::s_return_value;

inline void VM::start_new_execution() {
	s_vars.push(VMVars());
	s_var = &s_vars.top();
	s_var->running = true;
}

inline void VM::end_current_execution() {
	s_vars.pop();
	s_var = &s_vars.top();
}

/**
 * Execute the collected opcodes
 */
void VM::run(size_t start, VMMode mode) {
	clever_assert_not_null(s_opcodes);

	start_new_execution();

	size_t last_op = s_opcodes->size();
	s_var->mode = mode;

	for (size_t next_op = start; next_op < last_op && s_var->running; ++next_op) {
		const Opcode& opcode = *(*s_opcodes)[next_op];

		// opcode.dump();

		// Invoke the opcode handler
		opcode.getHandler()(opcode, next_op);
	}

	end_current_execution();
}

/**
 * Runs an specific function with the supplied arguments
 */
void VM::run(const Function* func, const ValueVector* args) {
	clever_assert_not_null(func);

	start_new_execution();

	size_t last_op = s_opcodes->size();
	size_t start = func->getOffset() + 1;

	s_var->mode = INTERNAL;

	s_var->call.push(StackFrame(NULL));

	if (args) {
		push_args(func->getScope(), func->getArgs(), args);
	}

	for (size_t next_op = start; next_op < last_op && s_var->running; ++next_op) {
		const Opcode& opcode = *(*s_opcodes)[next_op];

		// opcode.dump();

		// Invoke the opcode handler
		opcode.getHandler()(opcode, next_op);
	}

	end_current_execution();
}

/**
 * Destroy the opcodes data
 */
void VM::shutdown() {
	clever_assert_not_null(s_opcodes);

	OpcodeList::const_iterator it = s_opcodes->begin(),
		end(s_opcodes->end());

	while (it != end) {
		delete *it;
		++it;
	}

	s_var = NULL;
	s_return_value = NULL;
}

/**
 * Pushes the function call arguments
 */
void VM::push_args(Scope* scope, const FunctionArgs& fargs,
	const ValueVector* args) {

	clever_assert_not_null(args);

	VarVector* vec = new VarVector;
	size_t i = 0;

	FunctionArgs::const_iterator it(fargs.begin()), end(fargs.end());

	vec->reserve(args->size());

	/* TODO: Find a better way to do this */
	while (EXPECTED(it != end)) {
		Value* val = scope->getValue(CSTRING((*it).first));
		Value* tmp = new Value;

		val->copy(args->at(i++));
		tmp->copy(val);

		vec->push_back(VarPair(val, tmp));
		++it;
	}

	s_var->call.top().params = vec;
}

/**
 * Pop arguments onto the call stack
 */
inline void VM::pop_args(const Opcode* const op) {
	// Check if the function has arguments
	if (s_var->mode == NORMAL && op->getOp2Value() == NULL) {
		return;
	}

	VarVector* vec = s_var->call.top().params;

	if (vec == NULL) {
		return;
	}

	for (size_t i = 0, j = vec->size(); i < j; ++i) {
		delete vec->at(i).second;
	}
	delete vec;
}

/**
 * Restore the parameter argument values from the previous stack frame
 */
inline void VM::restore_args() {
	VarVector* vec = s_var->call.top().params;

	if (vec == NULL) {
		return;
	}

	for (size_t i = 0, j = vec->size(); i < j; ++i) {
		vec->at(i).first->copy(vec->at(i).second);
	}
}

/**
 * Pushes local variable into the stack
 */
void VM::push_local_vars(Scope* scope) {
	if (scope == NULL || !scope->hasChildren()) {
		return;
	}

	const SymbolMap& symbols = scope->getChildren()[0]->getSymbols();
	SymbolMap::const_iterator it(symbols.begin()), end(symbols.end());

	VarVector* vec = new VarVector;

	vec->reserve(symbols.size());

	while (it != end) {
		if (it->second->isValue()) {
			Value* val = it->second->getValue();

			if (!val->isCallable()) {
				Value* tmp = new Value;
				tmp->copy(val);
				vec->push_back(VarPair(val, tmp));
			}
		}
		++it;
	}

	s_var->call.top().locals = vec;
}

inline void VM::pop_local_vars() {
	VarVector* vec = s_var->call.top().locals;

	if (!vec) {
		return;
	}

	for (size_t i = 0, j = vec->size(); i < j; ++i) {
		delete vec->at(i).second;
	}
	delete vec;
}

/**
 * Restore local variables value
 */
inline void VM::restore_local_vars() {
	VarVector* vec = s_var->call.top().locals;

	if (vec == NULL) {
		return;
	}

	for (size_t i = 0, j = vec->size(); i < j; ++i) {
		vec->at(i).first->copy(vec->at(i).second);
	}
}

/**
 * Pushes a new context
 */
inline void VM::push_context() {
	if (s_var->context.size()) {
		s_var->context.push(VarVector());
	}
}

/**
 * Pops the current context
 */
void VM::pop_context(const Opcode* opcode) {
	if (opcode == NULL || s_var->context.size() == 0) {
		return;
	}

	for (size_t i = 0, j = s_var->context.top().size(); i < j; ++i) {
		delete s_var->context.top().at(i).second;
	}
	s_var->context.pop();

	if (s_var->context.empty()) {
		return;
	}

	Value* tmp = new Value;
	Value* result = opcode->getResultValue();

	if (result) {
		tmp->copy(result);
	}

	s_var->context.top().push_back(VarPair(result, tmp));

	for (size_t i = 0, j = s_var->context.top().size(); j > 1 && i < j; ++i) {
		s_var->context.top().at(i).first->copy(s_var->context.top().at(i).second);
	}
}

inline void VM::save_context(const Opcode& opcode) {
	if (s_var->context.size()) {
		Value* tmp = new Value;
		tmp->copy(opcode.getResultValue());

		s_var->context.top().push_back(VarPair(opcode.getResultValue(), tmp));
	}
}

/**
 * JMPZ - Jump if zero
 */
CLEVER_VM_HANDLER(VM::jmpz_handler) {
	const Value* const value = opcode.getOp1Value();
	Value* result = opcode.getResultValue();

	if (!value->getValueAsBool()) {
		if (result) {
			result->setBoolean(false);
		}
		CLEVER_VM_GOTO(opcode.getJmpAddr2());
	}

	if (result) {
		result->setBoolean(true);
	}
}

/**
 * JMPNZ - Jump if non-zero
 */
CLEVER_VM_HANDLER(VM::jmpnz_handler) {
	const Value* const value = opcode.getOp1Value();
	Value* result = opcode.getResultValue();

	if (value->getValueAsBool()) {
		if (result) {
			result->setBoolean(true);
		}
		CLEVER_VM_GOTO(opcode.getJmpAddr2());
	}

	if (result) {
		result->setBoolean(false);
	}
}

/**
 * JMP - Performs a jump to another code
 */
CLEVER_VM_HANDLER(VM::jmp_handler) {
	CLEVER_VM_GOTO(opcode.getJmpAddr1());
}

/**
 * Performs a function call
 */
CLEVER_VM_HANDLER(VM::fcall_handler) {
	const CallableValue* const func = opcode.getOp1Callable();
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	// Check if it's an user function
	if (func->isNearCall()) {
		const Function* fptr = func->getFunction();

		// New context
		s_var->context.push(VarVector());

		// New stack frame
		s_var->call.push(StackFrame(&opcode));

		if (EXPECTED(args != NULL)) {
			push_args(fptr->getScope(), fptr->getArgs(), args);
		}
		push_local_vars(fptr->getScope());

		func->call(next_op);
	} else {
		push_context();
		func->call(result, args);
		pop_context(&opcode);
	}
}

/**
 * Performs a method call (directly or via operators)
 */
CLEVER_VM_HANDLER(VM::mcall_handler) {
	const CallableValue* const var = opcode.getOp1Callable();
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();
	bool has_return = var->getMethod()->getReturnType() != NULL;

	if (has_return) {
		push_context();
	}

	var->call(result, args);

	if (has_return) {
		pop_context(&opcode);
	}
}

/**
 * Marks the end of a function
 */
CLEVER_VM_HANDLER(VM::leave_handler) {
	const Opcode* op = NULL;

	// On INTERNAL mode the VM might have an empty stack call
	if (s_var->mode == NORMAL || !s_var->call.empty()) {
		op = s_var->call.top().ret;
	}

	restore_local_vars();

	// pop + restore arguments from stack
	pop_args(op);
	pop_local_vars();

	if (op) {
		s_var->call.pop();
	}

	if (!s_var->call.empty()) {
		restore_args();
	}

	s_return_value = NULL;

	pop_context(op);

	// Go to after the caller command
	if (op) {
		CLEVER_VM_GOTO(op->getOpNum());
	} else {
		// Terminates the execution, go back to the internal caller
		CLEVER_VM_EXIT();
	}
}

/**
 * Returns to the caller or terminates the execution
 */
CLEVER_VM_HANDLER(VM::return_handler) {
	const Value* const value = opcode.getOp1Value();

	if (!s_var->call.empty()) {
		const Opcode* call = s_var->call.top().ret;

		if (EXPECTED(call && value)) {
			call->getResultValue()->copy(value);
		}
		// pop + restore arguments from stack
		pop_args(call);
		restore_local_vars();
		pop_local_vars();

		s_var->call.pop();

		if (!s_var->call.empty()) {
			restore_args();
		}

		s_return_value = value;

		pop_context(call);

		// Go back to the caller
		if (s_var->mode == INTERNAL && s_var->call.empty()) {
			CLEVER_VM_EXIT();
		} else {
			CLEVER_VM_GOTO(call->getOpNum());
		}
	} else {
		s_return_value = value;

		if (s_var->mode == INTERNAL) {
			pop_args(NULL);
		}

		// Terminates the execution
		CLEVER_VM_EXIT();
	}
}

/**
 * Add arithmetic operation
 */
CLEVER_VM_HANDLER(VM::plus_handler) {
	const CallableValue* const var = opcode.getOp1Callable();
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
	save_context(opcode);
}

/**
 * Minus arithmetic operation
 */
CLEVER_VM_HANDLER(VM::minus_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Div arithmetic operation
 */
CLEVER_VM_HANDLER(VM::div_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Mult arithmetic operation
 */
CLEVER_VM_HANDLER(VM::mult_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Mod arithmetic operation
 */
CLEVER_VM_HANDLER(VM::mod_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Inc operation (x++, ++x)
 */
CLEVER_VM_HANDLER(VM::inc_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Dec arithmetic operation (x--, --x)
 */
CLEVER_VM_HANDLER(VM::dec_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Xor bit-wise operation
 */
CLEVER_VM_HANDLER(VM::xor_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * OR bit-wise operation
 */
CLEVER_VM_HANDLER(VM::bw_or_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * AND bit-wise operation
 */
CLEVER_VM_HANDLER(VM::bw_and_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * NOT bit-wise operation
 */
CLEVER_VM_HANDLER(VM::bw_not_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Greater logical operation (x > y)
 */
CLEVER_VM_HANDLER(VM::greater_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Less logical operation (x < y)
 */
CLEVER_VM_HANDLER(VM::less_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Greater or equal logical operation (x >= y)
 */
CLEVER_VM_HANDLER(VM::ge_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Less or equal logical operation (x <= y)
 */
CLEVER_VM_HANDLER(VM::le_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Equal logical operation (x == y)
 */
CLEVER_VM_HANDLER(VM::equal_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Not equal logical operation (x != y)
 */
CLEVER_VM_HANDLER(VM::ne_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Left shift logical operation (x << y)
 */
CLEVER_VM_HANDLER(VM::lshift_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Right shift logical operation (x >> y)
 */
CLEVER_VM_HANDLER(VM::rshift_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * NOT logical operation (x >> y)
 */
CLEVER_VM_HANDLER(VM::not_handler) {
	opcode.getOp1Callable()->call(opcode.getResultValue(), opcode.getOp2Vector());
	save_context(opcode);
}

/**
 * Initialize a variable (Type var;)
 */
CLEVER_VM_HANDLER(VM::init_var_handler) {
	opcode.getOp1Value()->initialize();
}

} // clever
