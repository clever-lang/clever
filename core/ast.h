/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef CLEVER_AST_H
#define CLEVER_AST_H

#include <vector>
#include "core/value.h"
#include "core/location.hh"
#include "core/astvisitor.h"

namespace clever { namespace ast {

class Node {
public:
	Node(const location& location)
		: m_location(location) {}

	virtual ~Node(void) {}
	virtual void accept(Visitor& visitor) {  }

private:
	const location& m_location;
};

class NodeArray: public Node {
public:
	NodeArray(const location& location)
		: Node(location) {}

	virtual ~NodeArray(void) {}

	std::vector<Node*>& getNodes() { return m_nodes; }

	Node* getFirst() {
		if (m_nodes.empty()) {
			return NULL;
		}

		return *(m_nodes.begin());
	}

	Node* append(Node* node) {
		m_nodes.push_back(node);
		return node;
	}

	size_t getSize() const { return m_nodes.size(); }

	virtual void accept(Visitor& visitor) {
		std::vector<Node*>::iterator node(m_nodes.begin()), end(m_nodes.end());
		while (node != end) {
			visitor.visit(*node);
		}
	}


protected:
	std::vector<Node*> m_nodes;
};

class Block: public NodeArray {
public:
	Block(const location& location)
		: NodeArray(location) {}

	using NodeArray::accept;

};

class Assignment: public Node {
public:
	Assignment(Node* lhs, Node* rhs, const location& location)
		: Node(location), m_lhs(lhs), m_rhs(rhs) {}

	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }
private:
	Node* m_lhs;
	Node* m_rhs;
};

class VariableDecl: public Node {
public:
	VariableDecl(const CString* name, Assignment* assignment, const location& location)
		: Node(location), m_name(name), m_assignment(assignment) { }

	const CString* getName() const { return m_name; }
	Assignment* getAssignment() { return m_assignment; }
	bool hasAssignment() const { return m_assignment != NULL; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	const CString* m_name;
	Assignment* m_assignment;
};

class Arithmetic: public Node {
public:
	enum MathOperator {
		MOP_ADD = '+',
		MOP_SUB = '-',
		MOP_MUL = '*',
		MOP_DIV = '/',
		MOP_MOD = '%'
	};

	Arithmetic(MathOperator op, Node* lhs, Node* rhs, const location& location)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(rhs) {}

	MathOperator getOperator() const { return m_op; }
	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	MathOperator m_op;
	Node* m_lhs;
	Node* m_rhs;
};

class FunctionDecl: public Node {
public:
	FunctionDecl(const CString* name, NodeArray* args, Block* block, const location& location)
		: Node(location), m_name(name), m_args(args), m_block(block) {}

	const CString* getName() { return m_name; }

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
	const CString* m_name;
	NodeArray* m_args;
	Block* m_block;
};

class FunctionCall: public Node {
public:
	FunctionCall(Node* callee, NodeArray* args, const location& location)
		: Node(location), m_callee(callee), m_args(args) {}

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

class Ident: public Node {
public:
	Ident(const CString* name, const location& location)
		: Node(location), m_name(name) {}

	const CString* getName() const { return m_name; }

	virtual void accept(Visitor& visitor) { visitor.visit(this); }

private:
	const CString* m_name;
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
