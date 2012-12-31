/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_CODEGEN_H
#define CLEVER_CODEGEN_H

#include <vector>
#include <stack>
#include "core/astvisitor.h"
#include "core/ir.h"

namespace clever {

class Scope;
class Compiler;
typedef std::vector<Scope*> ScopePool;

} // clever

namespace clever { namespace ast {

class Codegen: public Visitor {
public:
	typedef std::vector<size_t> AddrVector;
	typedef std::stack<AddrVector> JmpList;

	Codegen(IRVector& ir, ScopePool& scope_pool, const Compiler* compiler)
		: m_ir(ir), m_scope_pool(scope_pool), m_compiler(compiler), m_scope(NULL),
			m_scope_id(0) {}
	~Codegen() {}

	void init();

	void visit(Block*);
	void visit(VariableDecl*);
	void visit(Assignment*);
	void visit(Import*);
	void visit(FunctionCall*);
	void visit(FunctionDecl*);
	void visit(Return*);
	void visit(While*);
private:
	IRVector& m_ir;
	ScopePool& m_scope_pool;
	const Compiler* m_compiler;
	Scope* m_scope;
	size_t m_scope_id;
	JmpList m_jmps;
};

}} // clever::ast

#endif // CLEVER_CODEGEN_H
