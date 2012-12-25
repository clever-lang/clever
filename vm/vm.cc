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
#include "vm/vm.h"

namespace clever {

#define VM_HANDLER(name) CLEVER_FORCE_INLINE void VM::name(IR& op)

/**
 * Variable declaration execution
 */
VM_HANDLER(var_decl)
{
	/**
	 * Fetching variable name from scope
	 */
	std::cout << *(m_scope_array[m_current_scope]->at(op.op1)) << std::endl;
}

/**
 * Scope switching operation
 */
VM_HANDLER(switch_scope)
{
	m_current_scope = op.op1;
}

/**
 * Executes the VM opcodes
 */
void VM::run(IRVector& ir)
{
	for (size_t i = 0, j = ir.size(); i < j; ++i) {
		switch (ir[i].opcode) {
			case OP_VAR_DECL:
				var_decl(ir[i]);
				break;
			case OP_SCOPE:
				switch_scope(ir[i]);
				break;
		}
	}
}

} // clever
