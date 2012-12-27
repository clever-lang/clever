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

#ifdef CLEVER_DEBUG
#include <stdio.h>
#include "vm/opcode.h"
#endif
#include "compiler/cstring.h"
#include "compiler/scope.h"
#include "compiler/value.h"
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
	m_handlers[OP_RETURN]   = &VM::ret;
	m_handlers[OP_ASSIGN]   = &VM::assignment;
	m_handlers[OP_PLUS]     = &VM::plus;
	m_handlers[OP_PRINT]    = &VM::print;
	m_handlers[OP_HALT]     = &VM::halt;
	m_handlers[OP_JMP]      = &VM::jmp;
}

#ifdef CLEVER_DEBUG
void VM::dumpOpcodes() const
{
	const char *op_type[] = {
		"UNUSED", "FETCH_VAL", "FETCH_SCOPE", "JMP_ADDR"
	};

	for (size_t i = 0, j = m_inst.size(); i < j; ++i) {
		IR& ir = m_inst[i];
		::printf("[%03ld] %-10s | %3ld (%-9s) | %3ld (%-9s)\n",
			i,
			get_opcode_name(ir.opcode),
			ir.op1, op_type[ir.op1_type],
			ir.op2, op_type[ir.op2_type]);
	}
}
#endif

/**
 * Return operation
 */
VM_HANDLER(ret)
{
}

/**
 * Halt operation
 */
VM_HANDLER(halt)
{
}

/**
 * JMP operation
 */
VM_HANDLER(jmp)
{
	VM_GOTO(op.op1);
}

/**
 * Assignment operation
 */
VM_HANDLER(assignment)
{
	Value* var = getValue(op.op1);
	Value* value = getValue(op.op2);

	var->copy(value);

	VM_NEXT();
}

/**
 * Math sum operation
 */
VM_HANDLER(plus)
{
	Value* lhs = getValue(op.op1);
	Value* rhs = getValue(op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() + rhs->getInt());
	}

	VM_NEXT();
}

/**
 * Temporary handler for print command
 */
VM_HANDLER(print)
{
	getValue(op.op1)->dump();
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
