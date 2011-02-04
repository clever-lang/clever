/*
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
 *
 * $Id$
 */

#ifndef CLEVER_VM_H
#define CLEVER_VM_H

#include <vector>
#include <stack>
#include "global.h"

/**
 * Opcode handler arguments
 */
#define CLEVER_VM_HANDLER_ARGS Opcode& opcode, long& next_op
#define CLEVER_VM_HANDLER(name) void CLEVER_FASTCALL name(CLEVER_VM_HANDLER_ARGS) throw()

/**
 * Change the executor flow to run another opcode
 */
#define CLEVER_VM_GOTO(x) next_op = (x); return

namespace clever {

class Opcode;

typedef std::vector<Opcode*> OpcodeList;
typedef std::stack<Opcode*> CallStack;

/**
 * Virtual machine representation
 */
class VM {
public:
	/**
	 * Opcode handler prototype
	 */
	typedef void (CLEVER_FASTCALL *opcode_handler)(CLEVER_VM_HANDLER_ARGS);

	VM() : m_opcodes(NULL) { }

	~VM();

	/**
	 * Execute the opcode (call the its related handlers)
	 */
	void run() throw();
	/**
	 * Displays an error message and exists
	 */
	static void error(const char*) throw();
	/**
	 * Set the opcode vector
	 */
	void set_opcodes(OpcodeList& opcodes) throw() { m_opcodes = &opcodes; }
	/**
	 * Opcode handlers
	 */
	static CLEVER_VM_HANDLER(plus_handler);
	static CLEVER_VM_HANDLER(div_handler);
	static CLEVER_VM_HANDLER(mult_handler);
	static CLEVER_VM_HANDLER(minus_handler);
	static CLEVER_VM_HANDLER(mod_handler);
	static CLEVER_VM_HANDLER(var_decl_handler);
	static CLEVER_VM_HANDLER(bw_and_handler);
	static CLEVER_VM_HANDLER(bw_or_handler);
	static CLEVER_VM_HANDLER(bw_xor_handler);
	static CLEVER_VM_HANDLER(pre_inc_handler);
	static CLEVER_VM_HANDLER(pre_dec_handler);
	static CLEVER_VM_HANDLER(pos_inc_handler);
	static CLEVER_VM_HANDLER(pos_dec_handler);
	static CLEVER_VM_HANDLER(jmpz_handler);
	static CLEVER_VM_HANDLER(jmp_handler);
	static CLEVER_VM_HANDLER(greater_handler);
	static CLEVER_VM_HANDLER(greater_equal_handler);
	static CLEVER_VM_HANDLER(less_handler);
	static CLEVER_VM_HANDLER(less_equal_handler);
	static CLEVER_VM_HANDLER(break_handler);
	static CLEVER_VM_HANDLER(equal_handler);
	static CLEVER_VM_HANDLER(not_equal_handler);
	static CLEVER_VM_HANDLER(fcall_handler);
	static CLEVER_VM_HANDLER(mcall_handler);
	static CLEVER_VM_HANDLER(assign_handler);
	static CLEVER_VM_HANDLER(end_func_handler);
	static CLEVER_VM_HANDLER(return_handler);
	static CLEVER_VM_HANDLER(arg_recv_handler);
private:
	OpcodeList* m_opcodes;

	static CallStack s_call;

	DISALLOW_COPY_AND_ASSIGN(VM);
};

} // clever

#endif // CLEVER_VM_H
