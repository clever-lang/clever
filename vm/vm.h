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

/**
 * Change the executor flow to run another opcode
 */
#define CLEVER_VM_GOTO(x) next_op = (x); return

#define CLEVER_VM_EXIT() s_var->running = false; return

namespace clever {

class Opcode;
class Scope;
class Value;

typedef std::vector<Opcode*> OpcodeList;
typedef std::stack<const Opcode*> CallStack;
typedef std::stack<ValueVector*> ValueVStack;

enum VMMode { NORMAL, INTERNAL };

/**
 * VM variables
 */
struct VMVars {
	VMMode mode;

	bool running;

	// Call stack - store the caller opcode
	CallStack call;

	// Store the scoped variables
	ValueVStack arg_vars, arg_values;
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

	~VM();

	static void setOpcodes(OpcodeList* opcodes) {
		s_opcodes = opcodes;
	}

	/**
	 * Execute the opcode (call the its related handlers)
	 */
	static void run(size_t offset = 0, VMMode mode = NORMAL);
	static void run(const Function*, const ValueVector*);

	static void start_new_execution();
	static void end_current_execution();
	/**
	 * Function/method argument handling
	 */
	static void pop_args(const Opcode* const);
	static void restore_args();
	static void update_vars(Scope*, const FunctionArgs&, const ValueVector*);
	/**
	 * Opcode handlers
	 */
	static CLEVER_VM_HANDLER(var_decl_handler);
	static CLEVER_VM_HANDLER(jmpnz_handler);
	static CLEVER_VM_HANDLER(jmpz_handler);
	static CLEVER_VM_HANDLER(jmp_handler);
	static CLEVER_VM_HANDLER(fcall_handler);
	static CLEVER_VM_HANDLER(mcall_handler);
	static CLEVER_VM_HANDLER(assign_handler);
	static CLEVER_VM_HANDLER(end_func_handler);
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

	static const Value* getLastReturnValue() {
		return s_return_value;
	}
private:
	static const OpcodeList* s_opcodes;

	static ExecVars s_vars;
	static VMVars* s_var;

	static const Value* s_return_value;

	DISALLOW_COPY_AND_ASSIGN(VM);
};

} // clever

#endif // CLEVER_VM_H
