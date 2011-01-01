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

/**
 * Opcode handler arguments
 */
#define CLEVER_VM_HANDLER_ARGS unsigned int* next_op, Opcode* opcode
#define CLEVER_VM_HANDLER(name) void name(CLEVER_VM_HANDLER_ARGS)

/**
 * Change the executor flow to run another opcode
 */
#define CLEVER_VM_GOTO(x) *next_op = (x)-1; return

namespace clever {

enum { BLK_UNUSED, BLK_USED };

class SymbolTable;
class Opcode;

class VM {
public:
	typedef void (VM::*opcode_handler)(CLEVER_VM_HANDLER_ARGS);
	typedef std::vector<Opcode*> OpcodeList;

	VM() : m_opcodes(NULL) { }

	explicit VM(OpcodeList* opcodes)
		: m_opcodes(opcodes) { }

	~VM();

	void run(void);
	void error(const char*) const;

	inline void setOpcodes(OpcodeList* opcodes) {
		m_opcodes = opcodes;
	}

	/*
	 * Returns the value from a Value pointer according to Value type
	 */
	inline Value* getValue(Value* op) {
		if (!op) {
			return NULL;
		}
		switch (op->get_kind()) {
			case Value::NAMED:
				return m_symbols.get_var(op);
			case Value::CONST:
				return op;
			case Value::TEMP:
				return op->get_value();
		}
		return NULL;
	}

	/* Opcode handlers */
	CLEVER_VM_HANDLER(plus_handler);
	CLEVER_VM_HANDLER(div_handler);
	CLEVER_VM_HANDLER(mult_handler);
	CLEVER_VM_HANDLER(minus_handler);
	CLEVER_VM_HANDLER(new_scope_handler);
	CLEVER_VM_HANDLER(end_scope_handler);
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

	DISALLOW_COPY_AND_ASSIGN(VM);
private:
	OpcodeList* m_opcodes;
	SymbolTable m_symbols;
};

} // clever

#endif // CLEVER_VM_H