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

#ifndef CLEVER_TYPECHECKER_H
#define CLEVER_TYPECHECKER_H

#include <stack>
#include "compiler/scope.h"
#include "interpreter/astvisitor.h"

namespace clever {
class location;
}

namespace clever { namespace ast {

class TypeChecker : public ASTVisitor {
public:
	typedef std::stack<Function*> FuncDeclStack;

	TypeChecker()
		: m_interactive(false), m_scope(&g_scope) {}

	~TypeChecker() {}

	void init() {}

	void shutdown() {}

	AST_VISITOR_DECLARATION(AST_VISITOR_DECL);

	/**
	 * Set the interactive mode
	 */
	void setInteractive() { m_interactive = true; }

	/**
	 * Returns the interactive mode state
	 */
	bool isInteractive() { return m_interactive; }
private:
	bool m_interactive;
	Scope* m_scope;
	FuncDeclStack m_funcs;
};

}} // clever::ast

#endif // CLEVER_TYPECHECKER_H
