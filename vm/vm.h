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
#include <pthread.h>
#include "compiler/clever.h"
#include "vm/ir.h"

namespace clever {

#define VM_HANDLER_ARG IR& op
#define VM_HANDLER(name) CLEVER_FASTCALL void VM::name(VM_HANDLER_ARG)
#define VM_HANDLER_D(name) void name(VM_HANDLER_ARG)

class Scope;
class Value;

/**
 * VM representation
 */
class VM {
public:
	typedef void (VM::*OpHandler)(VM_HANDLER_ARG);

	typedef std::vector<pthread_t> ThreadPool;
	typedef std::vector<pthread_mutex_t> MutexPool;

	VM(IRVector& inst)
		: m_pc(0), m_inst(inst), m_scope_pool(NULL), m_value_pool(NULL),
			m_current_scope(0) {}
	~VM() {}
	/**
	 * Sets the symbol table to used by the VM to fetch the symbol names
	 */
	void setSymbolTable(Scope** scope) { m_scope_pool = scope; }
	/**
	 * Sets the Value* pool to be used by VM to fetch the instr values
	 */
	void setValuePool(Value** value) { m_value_pool = value; }
	/**
	 * Start the VM execution
	 */
	void run();

	/**
	 * VM opcode handlers
	 */
	VM_HANDLER_D(var_decl);
	VM_HANDLER_D(switch_scope);
	VM_HANDLER_D(ret);
	VM_HANDLER_D(assignment);
private:
	/**
	 * Initialization phase
	 */
	void init();

	size_t m_pc;
	IRVector& m_inst;
	Scope** m_scope_pool;
	Value** m_value_pool;
	size_t m_current_scope;
    ThreadPool m_thread_pool;
    MutexPool m_mutex_pool;
    OpHandler m_handlers[10];

    DISALLOW_COPY_AND_ASSIGN(VM);
};

} // clever

#endif // CLEVER_VM_H
