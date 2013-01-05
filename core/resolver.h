/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_RESOLVER_H
#define CLEVER_RESOLVER_H

#include "core/astvisitor.h"

namespace clever {
class Compiler;
class Scope;
}

namespace clever { namespace ast {

class Resolver: public Visitor {
public:
	Resolver(Compiler* compiler);

	~Resolver();

	Scope* getSymTable() { return m_symtable; }

	virtual void visit(Block*);
	virtual void visit(VariableDecl*);
	virtual void visit(FunctionDecl*);
	virtual void visit(Ident*);
	virtual void visit(Type*);
	virtual void visit(Import*);
	virtual void visit(Catch*);
private:
	Compiler* m_compiler;
	Scope* m_symtable;
	Scope* m_scope;
};

}} // clever::ast

#endif // CLEVER_RESOLVER_H
