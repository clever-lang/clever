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
 * $Id: parser.y 67 2010-12-22 18:55:54Z felipensp $
 */

#include <iostream>
#include "opcodes.h"
#include "vm.h"

namespace clever {

/*
 * Destroy the opcodes data
 */
VM::~VM(void) {
	OpcodeList::iterator it = m_opcodes->begin();

	while (it < m_opcodes->end()) {
		if ((*it)->get_op1()) {
			// std::cout << (*it)->get_op1() << " (refcount: " << (*it)->get_op1()->refCount() << ")" << std::endl;
			(*it)->get_op1()->delRef();
		}
		if ((*it)->get_op2()) {
			// std::cout << (*it)->get_op2() << " (refcount: " << (*it)->get_op2()->refCount() << ")" << std::endl;
			(*it)->get_op2()->delRef();
		}
		if ((*it)->get_result()) {
			// std::cout << (*it)->get_result() << " (refcount: " << (*it)->get_result()->refCount() << ")" << std::endl;
			(*it)->get_result()->delRef();
		}
		delete *it;
		++it;
	}
}

/*
 * Execute the collected opcodes
 */
void VM::run(void) {
	std::vector<Opcode*>::iterator it = m_opcodes->begin();

	while (it < m_opcodes->end()) {
		Opcode* opcode = *it;

		if (opcode->m_handler) {
			(this->*((*it)->m_handler))(*it);
		}
		++it;
	}
}

/*
 * echo statemenet
 */
void VM::echo_handler(CLEVER_VM_HANDLER_ARGS) {
	std::cout << opcode->get_op1()->toString() << std::endl;
}

/*
 * x + y
 */
void VM::plus_handler(CLEVER_VM_HANDLER_ARGS) {
}

/*
 * x / y
 */
void VM::div_handler(CLEVER_VM_HANDLER_ARGS) {
}

} // clever
