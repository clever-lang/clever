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
#include <map>
#include "core/astvisitor.h"

namespace clever {

class Thread;
class Compiler;
class IRBuilder;

} // clever

namespace clever { namespace ast {

class Codegen: public Visitor {
public:
	typedef std::vector<size_t> AddrVector;
	typedef std::stack<AddrVector> JmpList;

	Codegen(IRBuilder* builder)
		: m_builder(builder) {}

	~Codegen() {}

	void sendArgs(NodeArray*);

	void visit(Block*);
	void visit(CriticalBlock*);
	void visit(ThreadBlock*);
	void visit(VariableDecl*);
	void visit(Assignment*);
	void visit(FunctionCall*);
	void visit(MethodCall*);
	void visit(FunctionDecl*);
	void visit(Return*);
	void visit(While*);
	void visit(IntLit*);
	void visit(DoubleLit*);
	void visit(StringLit*);
	void visit(Ident*) {}
	void visit(IncDec*);
	void visit(Arithmetic*);
	void visit(Comparison*);
	void visit(Import*);
	void visit(If*);
	void visit(Logic*);
	void visit(Boolean*);
	void visit(Bitwise*);
	void visit(NullLit*);
	void visit(TrueLit*);
	void visit(FalseLit*);
	void visit(Instantiation*);
	void visit(Property*);
	void visit(Try*);
	void visit(Throw*);
	void visit(Continue*);
	void visit(Break*);
	void visit(ClassDef*);
	void visit(Subscript*);
	void visit(Switch*);
private:
	IRBuilder* m_builder;
	JmpList m_jmps;
	JmpList m_brks;

	DISALLOW_COPY_AND_ASSIGN(Codegen);
};

}} // clever::ast

#endif // CLEVER_CODEGEN_H
