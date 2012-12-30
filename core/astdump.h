#ifndef CLEVER_AST_DUMP_H
#define CLEVER_AST_DUMP_H

#include <iostream>
#include "core/astvisitor.h"

namespace clever { namespace ast {

class DumpVisitor : public Visitor {
public:
	DumpVisitor()
		: m_level(0) {}

	~DumpVisitor() {}

	void visit(Node* node)         { std::cout << m_ws << "Node" << std::endl; }
	void visit(NodeArray* node)    { std::cout << m_ws << "NodeArray" << std::endl;}
	void visit(Block* node)        {
		std::cout << std::string(m_level, ' ') << "Block" << std::endl;

		m_ws = std::string(++m_level, ' ');

		std::vector<Node*> nodes = node->getNodes();
		std::vector<Node*>::const_iterator it = nodes.begin(), end = nodes.end();
		while (it != end) {
			(*it)->accept(*this);
			++it;
		}

		m_ws = std::string(--m_level, ' ');
	}
	void visit(Assignment* node)   { std::cout << m_ws << "Assignment" << std::endl;   }
	void visit(VariableDecl* node) { std::cout << m_ws << "VariableDecl" << std::endl; }
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
private:
	size_t m_level;
	std::string m_ws;
};

}} // clever::ast

#endif // CLEVER_AST_DUMP_H
