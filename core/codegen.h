/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_CODEGEN_H
#define CLEVER_CODEGEN_H

#include <cstdlib>
#include "core/astvisitor.h"
#include "core/ir.h"

namespace clever {

class Scope;
typedef std::vector<Scope*> ScopePool;

} // clever

namespace clever { namespace ast {

class Codegen: public Visitor {
public:
	Codegen(IRVector& ir, ScopePool& scope_pool)
		: m_ir(ir), m_scope_pool(scope_pool), m_scope(NULL), m_scope_id(0) {}
	~Codegen() {}

	void init();

	void visit(Block*);
	void visit(VariableDecl*);
	void visit(Assignment*);
private:
	IRVector& m_ir;
	ScopePool& m_scope_pool;
	Scope* m_scope;
	size_t m_scope_id;
};

}} // clever::ast

#endif // CLEVER_CODEGEN_H
