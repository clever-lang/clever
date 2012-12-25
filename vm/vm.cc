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
#include "vm/vm.h"

namespace clever {

#define VM_NEXT() ++i; (this->*m_handlers[m_inst[i].opcode])(i, m_inst[i])

/**
 * VM initialization phase
 */
inline void VM::init()
{
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

	std::cout << "VAR_DECL: Symbol: " << *sym.getName() << " ";

	if (value) {
		std::cout << "Value: " <<
			(value->isInt() ? value->getInt() : value->getDouble()) << std::endl;
	} else {
		std::cout << "Value: null" << std::endl;
	}

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

	var->setInt(value->getInt());

	std::cout << "ASSIGN: " << value->getInt() << std::endl;

	VM_NEXT();
}

/**
 * Executes the VM opcodes in a continuation-passing style
 */
void VM::run()
{
	size_t ip = 0;

	/**
	 * Loads the opcode handlers
	 */
	init();

	(this->*m_handlers[m_inst[ip].opcode])(ip, m_inst[ip]);
}

} // clever
