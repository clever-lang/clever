/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_RESOLVER_H
#define CLEVER_RESOLVER_H

#include "core/astvisitor.h"

#include <stack>

namespace clever {
class Compiler;
class Scope;
class Environment;
}

namespace clever { namespace ast {

class Resolver: public Visitor {
public:
	Resolver(Compiler* compiler);

	~Resolver();

	Scope* getSymTable() { return m_symtable; }

	Environment* getGlobalEnv() {
		clever_assert(m_stack.size() == 1,
					  "There must be only one entry on the stack");

		return m_stack.top();
	}

	virtual void visit(Block*);
	virtual void visit(VariableDecl*);
	virtual void visit(FunctionDecl*);
	virtual void visit(Ident*);
	virtual void visit(Type*);
	virtual void visit(Import*);
private:
	Compiler* m_compiler;
	Scope* m_symtable;
	Scope* m_scope;
	std::stack<Environment*> m_stack;
};

}} // clever::ast

#endif // CLEVER_RESOLVER_H
