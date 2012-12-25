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

#ifndef CLEVER_COMPILER_H
#define CLEVER_COMPILER_H

#include <vector>
#include "compiler/clever.h"
#include "compiler/scope.h"
#include "vm/opcode.h"

namespace clever {

class CString;

/**
 * Intermediate representation
 */
struct IR {
	IR(Opcode _op, int _op1)
		: opcode(_op), op1(_op1), op2(0), result(NULL) {}

	IR(Opcode _op, int _op1, int _op2)
		: opcode(_op), op1(_op1), op2(_op2), result(NULL) {}

	int opcode, op1, op2;
	void* result;
};

typedef std::vector<IR> IRVector;

/**
 * Compiler representation
 */
class Compiler {
public:
	Compiler() : m_ir(), m_scope(NULL), m_scope_id(0) {}

	~Compiler() {}
	/**
	 * Starts the compilation phase
	 */
	void init();
	/**
	 * Ends the compilation phase
	 */
	void end() const {}
	/**
	 * Shutdown the compiler freeing all resources
	 */
	void shutdown();

	IRVector& getIR() { return m_ir; }

	Scope** getScopeTable() { return m_scope_array; }

	/**
	 * Compilation methods
	 */
	void varDeclaration(const CString*);
	void newScope();
	void endScope();
private:
	IRVector m_ir;
	Scope* m_scope;
	Scope* m_scope_array[10];
	size_t m_scope_id;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
