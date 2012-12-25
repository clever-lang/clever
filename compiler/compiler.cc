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

#include "compiler/cstring.h"
#include "compiler/compiler.h"
#include "compiler/scope.h"

namespace clever {

void Compiler::init()
{
	m_scope = new Scope;
	m_scope_array[0] = m_scope;
}

/**
 * Frees all resource used by the compiler
 */
void Compiler::shutdown()
{
	if (g_cstring_tbl) {
		delete g_cstring_tbl;
	}
	if (m_scope) {
		delete m_scope; /* FIXME: memleak on child scopes */
	}
}

/**
 * Compiles a variable declaration
 */
void Compiler::varDeclaration(const CString* var)
{
	m_ir.push_back(IR(OP_VAR_DECL, m_scope->push(var)));
}

/**
 * Creates a new lexical scope
 */
void Compiler::newScope()
{
	m_scope = m_scope->newLexicalScope();
	m_scope->setId(++m_scope_id);

	m_scope_array[m_scope_id] = m_scope;

	m_ir.push_back(IR(OP_SCOPE, m_scope_id));
}

/**
 * Scope end marker to switch to parent scope
 */
void Compiler::endScope()
{
	m_scope = m_scope->getParent();

	m_ir.push_back(IR(OP_SCOPE, m_scope->getId()));
}

} // clever
