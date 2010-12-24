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
 * $Id$
 */

#ifndef CLEVER_VM_H
#define CLEVER_VM_H

#include <stack>
#include <map>
#include <vector>
#include "types.h"

#define CLEVER_VM_HANDLER_ARGS Opcode* opcode

namespace clever {

class Opcode;

struct SymbolTable {
public:
	typedef std::map<std::string, Value*> var_map;

	inline void register_var(std::string name, Value* value) {
		m_variables.top().insert(std::pair<std::string, Value*>(name, value));
	}

	inline Value* get_var(std::string name) {
		var_map::iterator it = m_variables.top().find(name);

		return it->second;
	}

	inline void pushVarMap(var_map map) {
		m_variables.push(map);
	}

	inline void popVarMap() {
		var_map::iterator it = m_variables.top().begin();

		while (it != m_variables.top().end()) {
			it->second->delRef();
			++it;
		}
		m_variables.pop();
	}

private:
	std::stack<var_map> m_variables;
};

class VM {
public:
	typedef void (VM::*opcode_handler)(CLEVER_VM_HANDLER_ARGS);
	typedef std::vector<Opcode*> OpcodeList;

	VM() : m_opcodes(NULL) { }
	~VM();
	explicit VM(OpcodeList* opcodes)
		: m_opcodes(opcodes) { }

	void run(void);

	inline void setOpcodes(OpcodeList* opcodes) {
		m_opcodes = opcodes;
	}

	/* Opcode handlers */
	void echo_handler(CLEVER_VM_HANDLER_ARGS);
	void plus_handler(CLEVER_VM_HANDLER_ARGS);
	void div_handler(CLEVER_VM_HANDLER_ARGS);
	void mult_handler(CLEVER_VM_HANDLER_ARGS);
	void minus_handler(CLEVER_VM_HANDLER_ARGS);
	void new_scope_handler(CLEVER_VM_HANDLER_ARGS);
	void end_scope_handler(CLEVER_VM_HANDLER_ARGS);
	void var_decl_handler(CLEVER_VM_HANDLER_ARGS);
private:
	OpcodeList* m_opcodes;
	SymbolTable m_symbols;
};

} // clever

#endif // CLEVER_VM_H