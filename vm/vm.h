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

#ifndef CLEVER_VM_H
#define CLEVER_VM_H

#include <vector>
#include <stack>
#include "compiler/clever.h"
#include "compiler/function.h"

/**
 * Opcode handler arguments
 */
#define CLEVER_VM_HANDLER_ARGS const Opcode& opcode, size_t& next_op
#define CLEVER_VM_HANDLER(name) void CLEVER_FASTCALL name(CLEVER_VM_HANDLER_ARGS)
#define VM_H(name) VM::name##_handler

/**
 * Change the executor flow to run another opcode
 */
#define CLEVER_VM_GOTO(x) next_op = (x); return

#define CLEVER_VM_EXIT() s_var->running = false; return

namespace clever {

class Opcode;
class Scope;
class Value;

typedef std::pair<Value*, Value*> VarPair;
typedef std::vector<VarPair> VarVector;

/**
 * Stack frame representation
 */
struct StackFrame {
	StackFrame(const Opcode* opcode)
		: ret(opcode), params(NULL), locals(NULL) {}

	// Return address as an opcode pointer
	const Opcode* ret;

	// Local and parameter variables
	VarVector* params;
	VarVector* locals;
};

typedef std::vector<Opcode*> OpcodeList;
typedef std::stack<StackFrame> CallStack;
typedef std::stack<VarVector> ContextStack;

/**
 * VM execution modes
 */
enum VMMode {
	NORMAL,  // Executing by the interpreter
	INTERNAL // VM Executor being called internally by a function/method
};

/**
 * VM Executor variables
 */
struct VMVars {
	VMMode mode;
	bool running;
	CallStack call;
	ContextStack context;
};
typedef std::stack<VMVars> ExecVars;

/**
 * Virtual machine representation
 */
class VM {
public:
	/**
	 * Opcode handler prototype
	 */
	typedef void (CLEVER_FASTCALL *opcode_handler)(CLEVER_VM_HANDLER_ARGS);

	VM() {}

	~VM() {}

	static void setOpcodes(OpcodeList* opcodes) {
		s_opcodes = opcodes;
	}

	/**
	 * Execute the opcode (call the its related handlers)
	 */
	static void run(size_t offset = 0, VMMode mode = NORMAL);
	static void run(const Function*, const ValueVector*);

	static void shutdown();

	static void start_new_execution();
	static void end_current_execution();
	/**
	 * Function/method argument handling
	 */
	static void pop_args(const Opcode* const);
	static void restore_args();
	static void push_args(Scope*, const FunctionArgs&, const ValueVector*);

	/**
	 * Function/method local variable handling
	 */
	static void push_local_vars(Scope*);
	static void pop_local_vars();
	static void restore_local_vars();

	/**
	 * Context handling
	 */
	static void push_context();
	static void save_context(const Opcode&);
	static void pop_context(const Opcode*);

	/**
	 * Opcode handlers
	 */
	static CLEVER_VM_HANDLER(init_var_handler);
	static CLEVER_VM_HANDLER(jmpnz_handler);
	static CLEVER_VM_HANDLER(jmpz_handler);
	static CLEVER_VM_HANDLER(jmp_handler);
	static CLEVER_VM_HANDLER(fcall_handler);
	static CLEVER_VM_HANDLER(mcall_handler);
	static CLEVER_VM_HANDLER(assign_handler);
	static CLEVER_VM_HANDLER(leave_handler);
	static CLEVER_VM_HANDLER(return_handler);

	/**
	 * Arithmetic operation
	 */
	static CLEVER_VM_HANDLER(plus_handler);
	static CLEVER_VM_HANDLER(minus_handler);
	static CLEVER_VM_HANDLER(div_handler);
	static CLEVER_VM_HANDLER(mult_handler);
	static CLEVER_VM_HANDLER(mod_handler);
	static CLEVER_VM_HANDLER(inc_handler);
	static CLEVER_VM_HANDLER(dec_handler);

	/**
	 * Bit-wise operation
	 */
	static CLEVER_VM_HANDLER(bw_not_handler);
	static CLEVER_VM_HANDLER(xor_handler);
	static CLEVER_VM_HANDLER(bw_or_handler);
	static CLEVER_VM_HANDLER(bw_and_handler);
	static CLEVER_VM_HANDLER(lshift_handler);
	static CLEVER_VM_HANDLER(rshift_handler);

	/**
	 * Logical operation
	 */
	static CLEVER_VM_HANDLER(greater_handler);
	static CLEVER_VM_HANDLER(less_handler);
	static CLEVER_VM_HANDLER(ge_handler);
	static CLEVER_VM_HANDLER(le_handler);
	static CLEVER_VM_HANDLER(equal_handler);
	static CLEVER_VM_HANDLER(ne_handler);
	static CLEVER_VM_HANDLER(not_handler);

	/**
	 * Returns the last value returned by a return instruction
	 */
	static const Value* getLastReturnValue() {
		return s_return_value;
	}
private:
	// Opcodes to be executed
	static const OpcodeList* s_opcodes;

	// VM executor variables
	static ExecVars s_vars;

	// Current variable
	static VMVars* s_var;

	// Last returned value by a return instruction
	static const Value* s_return_value;

	DISALLOW_COPY_AND_ASSIGN(VM);
};

} // clever

#endif // CLEVER_VM_H
