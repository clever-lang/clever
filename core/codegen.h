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

	Codegen(IRVector& ir, Scope* symtable, Compiler* compiler)
		: m_ir(ir), m_symtable(symtable), m_compiler(compiler), m_scope(symtable)
	{}
	~Codegen() {}

	void init();

	void visit(Block*);
	void visit(VariableDecl*);
	void visit(Assignment*);
	void visit(FunctionCall*);
	void visit(FunctionDecl*);
	void visit(Return*);
	void visit(While*);
	void visit(IntLit*);
	void visit(DoubleLit*);
	void visit(StringLit*);
	void visit(Ident*);
	void visit(IncDec*);
private:
	IRVector& m_ir;
	Scope* m_symtable;
	Compiler* m_compiler;
	Scope* m_scope;
	JmpList m_jmps;
};

}} // clever::ast

#endif // CLEVER_CODEGEN_H
