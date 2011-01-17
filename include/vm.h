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
 * $Id$
 */

#ifndef CLEVER_VM_H
#define CLEVER_VM_H

#include <vector>
#include "symboltable.h"
#include "global.h"

/**
 * Opcode handler arguments
 */
#define CLEVER_VM_HANDLER_ARGS unsigned int& next_op, Opcode& opcode
#define CLEVER_VM_HANDLER(name) void name(CLEVER_VM_HANDLER_ARGS) throw()

/**
 * Change the executor flow to run another opcode
 */
#define CLEVER_VM_GOTO(x) next_op = (x)-1; return

namespace clever {

/**
 * OP_NEW_SCOPE flags
 */
enum { BLK_UNUSED, BLK_USED };

class SymbolTable;
class Opcode;

/**
 * Virtual machine representation
 */
class VM {
public:
	/**
	 * Opcode handler prototype
	 */
	typedef void (VM::*opcode_handler)(CLEVER_VM_HANDLER_ARGS);
	typedef std::vector<Opcode*> OpcodeList;

	VM() : m_opcodes(NULL) { }

	~VM();

	/**
	 * Execute the opcode (call the its related handlers)
	 */
	void run() throw();
	/**
	 * Displays an error message and exists
	 */
	void error(const char*) const throw();
	/**
	 * Set the opcode vector
	 */
	void set_opcodes(OpcodeList* opcodes) throw() {
		m_opcodes = opcodes;
	}
	/**
	 * Returns the value from a Value pointer according to its type
	 */
	Value* getValue(Value* op) throw() {
		if (UNEXPECTED(op == NULL)) {
			return NULL;
		}
		switch (op->get_kind()) {
			case Value::TEMP:
				return op->get_value();
			default:
				return op;
		}
	}

	/**
	 * Opcode handlers
	 */
	CLEVER_VM_HANDLER(plus_handler);
	CLEVER_VM_HANDLER(div_handler);
	CLEVER_VM_HANDLER(mult_handler);
	CLEVER_VM_HANDLER(minus_handler);
	CLEVER_VM_HANDLER(mod_handler);
	CLEVER_VM_HANDLER(var_decl_handler);
	CLEVER_VM_HANDLER(bw_and_handler);
	CLEVER_VM_HANDLER(bw_or_handler);
	CLEVER_VM_HANDLER(bw_xor_handler);
	CLEVER_VM_HANDLER(pre_inc_handler);
	CLEVER_VM_HANDLER(pre_dec_handler);
	CLEVER_VM_HANDLER(pos_inc_handler);
	CLEVER_VM_HANDLER(pos_dec_handler);
	CLEVER_VM_HANDLER(jmpz_handler);
	CLEVER_VM_HANDLER(jmp_handler);
	CLEVER_VM_HANDLER(greater_handler);
	CLEVER_VM_HANDLER(greater_equal_handler);
	CLEVER_VM_HANDLER(less_handler);
	CLEVER_VM_HANDLER(less_equal_handler);
	CLEVER_VM_HANDLER(break_handler);
	CLEVER_VM_HANDLER(equal_handler);
	CLEVER_VM_HANDLER(not_equal_handler);
	CLEVER_VM_HANDLER(fcall_handler);
	CLEVER_VM_HANDLER(mcall_handler);
	CLEVER_VM_HANDLER(assign_handler);
private:
	OpcodeList* m_opcodes;
	ScopeManager m_symbols;

	DISALLOW_COPY_AND_ASSIGN(VM);
};

} // clever

#endif // CLEVER_VM_H
