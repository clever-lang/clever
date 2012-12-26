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
#include "compiler/cstring.h"
#include "compiler/scope.h"
#include "types/type.h"
#include "vm/vm.h"

namespace clever {

/**
 * Helper macros to be used to change the VM program counter
 * The compiler optimizer is supposed to use tail call optimization here
 */
#define VM_CONT() (this->*m_handlers[m_inst[m_pc].opcode])(m_inst[m_pc])
#define VM_NEXT() ++m_pc; VM_CONT()
#define VM_GOTO(n) m_pc = n; VM_CONT(); return

/**
 * VM initialization phase
 */
inline void VM::init()
{
	/**
	 * Opcode handler mapping
	 */
	m_handlers[OP_VAR_DECL] = &VM::var_decl;
	m_handlers[OP_SCOPE]    = &VM::switch_scope;
	m_handlers[OP_RETURN]   = &VM::ret;
	m_handlers[OP_ASSIGN]   = &VM::assignment;
}

/**
 * Variable declaration execution
 */
VM_HANDLER(var_decl)
{
	Symbol& sym = m_scope_pool[m_current_scope]->at(op.op1);
	Value* value = m_value_pool[sym.getValueId()];

	std::cout << "VAR_DECL: Symbol: " << *sym.getName() << " Value: ";
	if (value) {
		value->getType()->dump();
		std::cout << " (" << *value->getType()->getName() << ")" << std::endl;
	} else {
		std::cout << "null";
	}
	std::cout << std::endl;

	VM_NEXT();
}

/**
 * Scope switching operation
 */
VM_HANDLER(switch_scope)
{
	m_current_scope = op.op1;

	VM_NEXT();
}

/**
 * Return operation
 */
VM_HANDLER(ret)
{
}

/**
 * Assignment operation
 */
VM_HANDLER(assignment)
{
	Value* var = m_value_pool[op.op1];
	Value* value = m_value_pool[op.op2];

	std::cout << "ASSIGN: Changed ";
	var->getType()->dump();
	std::cout << " to ";
	value->getType()->dump();
	std::cout << std::endl;

	VM_NEXT();
}

/**
 * Executes the VM opcodes in a continuation-passing style
 */
void VM::run()
{
	/**
	 * Loads the opcode handlers
	 */
	init();

	/**
	 * Starts the VM by running the first instruction, which keep calling
	 * each other in a tail call way
	 */
	(this->*m_handlers[m_inst[0].opcode])(m_inst[0]);
}

} // clever
