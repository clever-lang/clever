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

#include <vector>

namespace clever {

class Opcode;

class VM {
public:
	typedef void (VM::*vm_handler)(Opcode* opcode);
	typedef std::vector<Opcode*> OpcodeList;

	VM() : m_opcodes(NULL) { }
	~VM();
	explicit VM(OpcodeList* opcodes)
		: m_opcodes(opcodes) { }

	void run(void);

	inline void setOpcodes(std::vector<Opcode*>* opcodes) {
		m_opcodes = opcodes;
	}

	/* Opcode handlers */
	void echo_stmt(Opcode* opcode);
	void plus_stmt(Opcode* opcode);
private:
	OpcodeList* m_opcodes;
};

} // clever

#endif // CLEVER_VM_H