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
#include "core/irbuilder.h"
#include "types/thread.h"

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

	Codegen(Compiler* compiler, IRBuilder* builder)
		: m_compiler(compiler), m_builder(builder), m_jmps(), m_thread_ids() {}

	~Codegen() {}

	void sendArgs(NodeArray*);

	Environment* getConstEnv() const { return m_builder->getConstEnv(); }
	Environment* getTempEnv() const { return m_builder->getTempEnv(); }

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
	void visit(Import*) {}
	void visit(If*);
	void visit(Logic*);
	void visit(Boolean*);
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
private:
	Compiler* m_compiler;
	IRBuilder* m_builder;
	JmpList m_jmps;
	JmpList m_brks;

	std::map<Thread*, size_t> m_thread_ids;

	DISALLOW_COPY_AND_ASSIGN(Codegen);
};

}} // clever::ast

#endif // CLEVER_CODEGEN_H
