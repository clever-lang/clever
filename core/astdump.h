#ifndef CLEVER_AST_DUMP_H
#define CLEVER_AST_DUMP_H

#include <iostream>
#include "core/astvisitor.h"

namespace clever { namespace ast {

class DumpVisitor : public Visitor {
public:
	DumpVisitor() {}
	~DumpVisitor() {}

	void visit(Node* node)         { std::cout << "Node" << std::endl; }
	void visit(NodeArray* node)    { std::cout << "NodeArray" << std::endl;}
	void visit(Block* node)        { std::cout << "Block" << std::endl; }
	void visit(Assignment* node)   { std::cout << "Assignment" << std::endl; }
	void visit(VariableDecl* node) {}
	void visit(Arithmetic* node) {}
	void visit(FunctionDecl* node) {}
	void visit(FunctionCall* node) {}
	void visit(While* node) {}
	void visit(If* node) {}
	void visit(IntLit* node) {}
	void visit(DoubleLit* node) {}
	void visit(StringLit* node) {}
	void visit(Ident* node) {}
	void visit(Return* node) {}
};

}} // clever::ast

#endif // CLEVER_AST_DUMP_H
