/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_AST_H
#define CLEVER_AST_H

#include <vector>
#include "core/value.h"
#include "core/location.hh"
#include "core/astvisitor.h"
#include "core/clever.h"

namespace clever { namespace ast {

class Node;

typedef std::vector<Node*> NodeList;

class Node: public RefCounted {
public:
	Node(const location& location)
		: RefCounted(0), m_location(location) {}

	virtual ~Node() {}

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	const location& m_location;
};

class NodeArray: public Node {
public:
	NodeArray(const location& location)
		: Node(location) {}

	virtual ~NodeArray() { clearNodes(); }

	NodeList& getNodes() { return m_nodes; }

	Node* getFirst() {
		if (m_nodes.empty()) {
			return NULL;
		}

		return *(m_nodes.begin());
	}

	Node* append(Node* node) {
		m_nodes.push_back(node);
		CLEVER_ADDREF(node);
		return node;
	}

	size_t getSize() const { return m_nodes.size(); }

	virtual void accept(Visitor& visitor) {
		NodeList::iterator node(m_nodes.begin()), end(m_nodes.end());
		while (node != end) {
			(*node)->accept(visitor);
			++node;
		}
	}

	void clearNodes() {
		NodeList::iterator it = m_nodes.begin(), end = m_nodes.end();

		while (it != end) {
			CLEVER_DELREF((*it));
			++it;
		}
	}
protected:
	NodeList m_nodes;
};

class Block: public NodeArray {
public:
	Block(const location& location)
		: NodeArray(location) {}

	virtual void accept(Visitor& visitor) {	visitor.visit(this); }
};

class Assignment: public Node {
public:
	Assignment(Node* lhs, Node* rhs, const location& location)
		: Node(location), m_lhs(lhs), m_rhs(rhs) {
		CLEVER_ADDREF(m_lhs);
		CLEVER_ADDREF(m_rhs);
	}

	~Assignment() {
		CLEVER_DELREF(m_lhs);
		CLEVER_DELREF(m_rhs);
	}

	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }
private:
	Node* m_lhs;
	Node* m_rhs;
};

class Ident: public Node {
public:
	Ident(const CString* name, const location& location)
		: Node(location), m_name(name) {}

	const CString* getName() const { return m_name; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	const CString* m_name;
};

class Import: public Node {
public:
	Import(Ident* package, Ident* module, const location& location)
		: Node(location), m_package(package), m_module(module) {
		CLEVER_ADDREF(m_package);
		CLEVER_ADDREF(m_module);
	}

	~Import() {
		CLEVER_DELREF(m_package);
		CLEVER_DELREF(m_module);
	}

	Ident* getPackage() const { return m_package; }
	Ident* getModule() const { return m_module; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }
private:
	Ident* m_package;
	Ident* m_module;
};

class VariableDecl: public Node {
public:
	VariableDecl(Ident* ident, Assignment* assignment, const location& location)
		: Node(location), m_ident(ident), m_assignment(assignment) {
		CLEVER_ADDREF(m_ident);
		if (m_assignment) {
			CLEVER_ADDREF(m_assignment);
		}
	}

	~VariableDecl() {
		CLEVER_DELREF(m_ident);
		if (m_assignment) {
			CLEVER_DELREF(m_assignment);
		}
	}

	Ident* getIdent() const { return m_ident; }
	Assignment* getAssignment() { return m_assignment; }
	bool hasAssignment() const { return m_assignment != NULL; }

	virtual void accept(Visitor& visitor) {	visitor.visit(this); }

private:
	Ident* m_ident;
	Assignment* m_assignment;
};

class Arithmetic: public Node {
public:
	enum ArithOperator {
		MOP_ADD = '+',
		MOP_SUB = '-',
		MOP_MUL = '*',
		MOP_DIV = '/',
		MOP_MOD = '%'
	};

	Arithmetic(ArithOperator op, Node* lhs, Node* rhs, const location& location)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(rhs) {
		CLEVER_ADDREF(m_lhs);
		CLEVER_ADDREF(m_rhs);
	}

	~Arithmetic() {
		CLEVER_DELREF(m_lhs);
		CLEVER_DELREF(m_rhs);
	}

	ArithOperator getOperator() const { return m_op; }
	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	ArithOperator m_op;
	Node* m_lhs;
	Node* m_rhs;
};

class Logic: public Node {
public:
	enum LogicOperator {
		LOP_EQUALS,
		LOP_OR,
		LOP_AND
	};

	Logic(LogicOperator op, Node* lhs, Node* rhs, const location& location)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(rhs) {
		CLEVER_ADDREF(m_lhs);
		CLEVER_ADDREF(m_rhs);
	}

	~Logic() {
		CLEVER_DELREF(m_lhs);
		CLEVER_DELREF(m_rhs);
	}

	LogicOperator getOperator() const { return m_op; }
	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	LogicOperator m_op;
	Node* m_lhs;
	Node* m_rhs;
};

class Bitwise: public Node {
public:
	enum BitwiseOperator {
		BOP_AND,
		BOP_OR,
		BOP_XOR,
		BOP_LSHIFT,
		BOP_RSHIFT
	};

	Bitwise(BitwiseOperator op, Node* lhs, Node* rhs, const location& location)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(rhs) {
		CLEVER_ADDREF(m_lhs);
		CLEVER_ADDREF(m_rhs);
	}

	~Bitwise() {
		CLEVER_DELREF(m_lhs);
		CLEVER_DELREF(m_rhs);
	}

	BitwiseOperator getOperator() const { return m_op; }
	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	BitwiseOperator m_op;
	Node* m_lhs;
	Node* m_rhs;
};

class FunctionDecl: public Node {
public:
	FunctionDecl(Ident* ident, NodeArray* args, Block* block, const location& location)
		: Node(location), m_ident(ident), m_args(args), m_block(block) {}

	Ident* getIdent() { return m_ident; }

	NodeArray* getArgs() { return m_args; }
	bool hasArgs() const { return m_args != NULL && m_args->getSize() > 0; }

	size_t numArgs() const { return m_args->getSize(); }

	Node* getArg(size_t index) {
		std::vector<Node*> array = m_args->getNodes();

		clever_assert(index > 0 && index < array.size(), "Index %i out of bounds.", index);

		if (array.empty())
			return NULL;

		return array.at(index);
	}

	Block* getBlock() { return m_block; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	Ident* m_ident;
	NodeArray* m_args;
	Block* m_block;
};

class FunctionCall: public Node {
public:
	FunctionCall(Node* callee, NodeArray* args, const location& location)
		: Node(location), m_callee(callee), m_args(args) {
		CLEVER_ADDREF(m_callee);
		CLEVER_SAFE_ADDREF(m_args);
	}

	~FunctionCall() {
		CLEVER_DELREF(m_callee);
		CLEVER_SAFE_DELREF(m_args);
	}

	Node* getCallee() { return m_callee; }

	NodeArray* getArgs() { return m_args; }
	bool hasArgs() const { return m_args != NULL && m_args->getSize() > 0; }

	size_t numArgs() const { return m_args->getSize(); }

	Node* getArg(size_t index) {
		std::vector<Node*> array = m_args->getNodes();

		clever_assert(index > 0 && index < array.size(), "Index %i out of bounds.", index);

		if (array.empty())
			return NULL;

		return array.at(index);
	}

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	Node* m_callee;
	NodeArray* m_args;
};

class While: public Node {
public:
	While(Node* condition, Node* block, const location& location)
		: Node(location), m_condition(condition), m_block(block) {}

	Node* getCondition() { return m_condition; }

	Node* getBlock() { return m_block; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	Node *m_condition;
	Node *m_block;
};

/// This class can handle both simple and complex (if + ifelse) if statements.
/// If you want to add a new conditional block, use the addConditional method.
class If: public Node {
public:
	If(Node* cond_node, Node* then_node, Node* else_node, const location& location)
		: Node(location), m_else_node(else_node) {

		addConditional(cond_node, then_node);
	}

	void addConditional(Node* cond_node, Node* then_node) {
		clever_assert_not_null(cond_node);

		m_conditionals.push_back(std::pair<Node*,Node*>(cond_node, then_node));
	}

	std::vector<std::pair<Node*, Node*> > getConditionals() { return m_conditionals; }

	Node* getElseNode() { return m_else_node; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	Node *m_else_node;
	std::vector<std::pair<Node*, Node*> > m_conditionals;
};

class IntLit: public Node {
public:
	IntLit(long value, const location& location)
		: Node(location), m_value(value) {}

	long getValue() const { return m_value; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	long m_value;
};

class DoubleLit: public Node {
public:
	DoubleLit(double value, const location& location)
		: Node(location), m_value(value) {}

	double getValue() const { return m_value; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	double m_value;
};

class StringLit: public Node {
public:
	StringLit(const CString* value, const location& location)
		: Node(location), m_value(value) {}

	const CString* getValue() const { return m_value; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	const CString* m_value;
};

class Return: public Node {
public:
	Return(Node* value, const location& location)
		: Node(location), m_value(value) {}

	Node* getValue() const { return m_value; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }
private:
	Node* m_value;
};

}} // clever::ast

#endif // CLEVER_AST_H
