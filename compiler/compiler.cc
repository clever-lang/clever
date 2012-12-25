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

#include <cstdlib>
#include "compiler/cstring.h"
#include "compiler/compiler.h"
#include "compiler/scope.h"
#include "compiler/value.h"

namespace clever {

/**
 * Compiler initialization phase
 */
void Compiler::init()
{
	m_scope = new Scope;
	m_scope_pool = (Scope**) calloc(10, sizeof(Scope*));
	m_value_pool = (Value**) calloc(10, sizeof(Value*));

	if (!m_scope_pool || !m_value_pool) {
		error("Out of memory!");
	}
	m_scope_pool[0] = m_scope;
}

/**
 * Compiler termination phase
 */
void Compiler::end()
{
	m_ir.push_back(IR(OP_RETURN, 0));
}

/**
 * Displays an error message and exits
 */
void Compiler::error(const char* msg) const
{
	std::cout << "Compile error: " << msg << std::endl;
	exit(1);
}

/**
 * Frees all resource used by the compiler
 */
void Compiler::shutdown()
{
	CLEVER_SAFE_DELETE(g_cstring_tbl);
	CLEVER_SAFE_DELETE(m_scope);
	free(m_scope_pool);

	for (size_t i = 0; i < m_value_id; ++i) {
		delete m_value_pool[i];
	}
	free(m_value_pool);
}

/**
 * Compiles a variable declaration
 */
void Compiler::varDeclaration(const CString* var, Value* node)
{
	if (!node) {
		node = new Value(0L);
	}
	m_value_pool[m_value_id] = node;

	m_ir.push_back(IR(OP_VAR_DECL, m_scope->push(var, m_value_id)));

	++m_value_id;
}

/**
 * Compiles a variable assignment
 */
void Compiler::assignment(const CString* var, Value* value)
{
	Symbol* sym = m_scope->getSymbol(var);

	if (!sym) {
		error("Variable cannot be found!");
	}

	m_value_pool[m_value_id] = value;

	m_ir.push_back(IR(OP_ASSIGN, sym->getValueId(), m_value_id));

	++m_value_id;
}

/**
 * Creates a new lexical scope
 */
void Compiler::newScope()
{
	m_scope = m_scope->newLexicalScope();
	m_scope->setId(++m_scope_id);

	m_scope_pool[m_scope_id] = m_scope;

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
