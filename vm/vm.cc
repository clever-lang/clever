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

VM::VM(Scope** scope_pool, Value** value_pool)
	: m_scope_pool(scope_pool), m_value_pool(value_pool), m_current_scope(0)
{
	m_handlers[OP_VAR_DECL] = &VM::var_decl;
	m_handlers[OP_SCOPE] = &VM::switch_scope;
}

/**
 * Variable declaration execution
 */
VM_HANDLER(var_decl)
{
	Symbol& sym = m_scope_pool[m_current_scope]->at(op.op1);
	Value* value = m_value_pool[sym.getValueId()];

	std::cout << "Symbol: " << *sym.getName() << std::endl;
	std::cout << "Value: " <<
		((value->isInt()) ? value->getInt() : value->getDouble()) << std::endl;
}

/**
 * Scope switching operation
 */
VM_HANDLER(switch_scope)
{
	m_current_scope = op.op1;
}

/**
 * Executes the VM opcodes in a call threading way
 */
void VM::run(IRVector& ir)
{
	for (size_t i = 0, j = ir.size(); i < j; ++i) {
		(this->*m_handlers[ir[i].opcode])(i, ir[i]);
	}
}

} // clever
