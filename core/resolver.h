/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_RESOLVER_H
#define CLEVER_RESOLVER_H

#include "core/astvisitor.h"
#include "core/scope.h"

namespace clever { namespace ast {

class Resolver: public Visitor {
public:
	Resolver();

	~Resolver() {}

	Scope* getSymTable() { return m_symtable; }

	virtual void visit(Block* node);
	virtual void visit(VariableDecl* node);
	virtual void visit(FunctionDecl* node);
	virtual void visit(Ident* node);
private:
	Scope* m_symtable;
	Scope* m_curscope;
	size_t m_scope_id;

};

}}

#endif // CLEVER_RESOLVER_H
