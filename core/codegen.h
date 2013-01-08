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

	Codegen(IRVector& ir, Compiler* compiler, Environment* init_glbenv);
	~Codegen() {}

	void sendArgs(NodeArray*);

	Environment* getConstEnv() const { return m_const_env; }
	Environment* getTempEnv() const { return m_temp_env; }

	void visit(Block*);
	void visit(CriticalBlock*);
	void visit(Wait*);
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
	void visit(Ident*);
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
	void visit(Array*);
private:
	IRVector& m_ir;
	Compiler* m_compiler;
	Environment* m_init_glbenv;
	Environment* m_const_env;
	Environment* m_temp_env;
	JmpList m_jmps;

	std::map<CString, size_t> m_thread_ids;
};

}} // clever::ast

#endif // CLEVER_CODEGEN_H
