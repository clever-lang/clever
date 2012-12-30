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

	void visit(Node* node)         { std::cout << m_ws << "Node" << std::endl;         }
	void visit(NodeArray* node)    { std::cout << m_ws << "NodeArray" << std::endl;    }
	void visit(Assignment* node)   { std::cout << m_ws << "Assignment" << std::endl;   }
	void visit(Arithmetic* node)   { std::cout << m_ws << "Arithmetic" << std::endl;   }
	void visit(FunctionDecl* node) { std::cout << m_ws << "FunctionDecl" << std::endl; }
	void visit(FunctionCall* node) { std::cout << m_ws << "FunctionCall" << std::endl; }
	void visit(While* node)        { std::cout << m_ws << "While" << std::endl;        }
	void visit(If* node)           { std::cout << m_ws << "If" << std::endl;           }
	void visit(IntLit* node)       { std::cout << m_ws << "IntLit" << std::endl;       }
	void visit(DoubleLit* node)    { std::cout << m_ws << "DoubleLit" << std::endl;    }
	void visit(StringLit* node)    { std::cout << m_ws << "StringLit" << std::endl;    }
	void visit(Ident* node)        { std::cout << m_ws << "Ident" << std::endl;        }
	void visit(Return* node)       { std::cout << m_ws << "Return" << std::endl;       }
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
	void visit(VariableDecl* node) {
		std::cout << m_ws << "VariableDecl" << std::endl;

		m_ws = std::string(++m_level, ' ');

		node->getIdent()->accept(*this);

		if (node->hasAssignment()) {
			node->getAssignment()->accept(*this);
		}

		m_ws = std::string(--m_level, ' ');
	}
private:
	size_t m_level;
	std::string m_ws;
};

}} // clever::ast

#endif // CLEVER_AST_DUMP_H
