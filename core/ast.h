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
#include "core/clever.h"
#include "core/scope.h"

namespace clever { namespace ast {

class Node;
class NodeArray;
class Block;
class Assignment;
class VariableDecl;
class Arithmetic;
class FunctionDecl;
class FunctionCall;
class While;
class If;
class IntLit;
class DoubleLit;
class StringLit;
class Ident;
class Return;
class Logic;
class Bitwise;
class Import;
class Boolean;

typedef std::vector<Node*> NodeList;

class Visitor;
class Transformer;

class Node: public RefCounted {
public:
	Node(const location& location)
		: RefCounted(0), m_location(location), m_scope(NULL) {}

	virtual ~Node() {}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

	virtual bool isLiteral() const { return false; }
	virtual bool isEvaluable() const { return false; }

	const location& getLocation() const { return m_location; }

	virtual IntLit* getIntLit() { return NULL; }
	virtual DoubleLit* getDoubleLit() { return NULL; }
	virtual StringLit* getStrLit() { return NULL; }

	virtual void setValueId(size_t value_id) { m_value_id = value_id; }
	virtual size_t getValueId() const { return m_value_id; }

	virtual void setScope(Scope* scope) { m_scope = scope; }
	virtual Scope* getScope() { return m_scope; }
private:
	const location& m_location;
	size_t m_value_id;
	Scope* m_scope;
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

	Node* getNode(size_t index) {
		clever_assert(index < m_nodes.size(), "Index %i out of bounds.", index);

		if (m_nodes.empty())
			return NULL;

		return m_nodes.at(index);
	}

	Node* append(Node* node) {
		m_nodes.push_back(node);
		CLEVER_ADDREF(node);
		return node;
	}

	size_t getSize() const { return m_nodes.size(); }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

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

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
};

class Assignment: public Node {
public:
	Assignment(Node* lhs, Node* rhs, const location& location)
		: Node(location), m_conditional(false), m_lhs(lhs), m_rhs(rhs) {
		CLEVER_ADDREF(m_lhs);
		CLEVER_SAFE_ADDREF(m_rhs);
	}

	~Assignment() {
		CLEVER_DELREF(m_lhs);
		CLEVER_SAFE_DELREF(m_rhs);
	}

	void setRhs(Node* rhs) {
		m_rhs = rhs;
		CLEVER_SAFE_ADDREF(m_rhs);
	}

	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	void setConditional(bool conditional) {
		m_conditional = conditional;
	}

	bool isConditional() const {
		return m_conditional;
	}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	bool m_conditional;
	Node* m_lhs;
	Node* m_rhs;
};

class Ident: public Node {
public:
	Ident(const CString* name, const location& location)
		: Node(location), m_name(name), m_sym(NULL) {
		clever_assert_not_null(m_name);
	}

	const CString* getName() const { return m_name; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

	void setSymbol(Symbol* sym)	{ m_sym = sym; }
	Symbol* getSymbol() { return m_sym; }

private:
	const CString* m_name;
	Symbol* m_sym;
};

class Import: public Node {
public:
	Import(Ident* package, Ident* module, const location& location)
		: Node(location), m_package(package), m_module(module) {
		CLEVER_ADDREF(m_package);
		CLEVER_SAFE_ADDREF(m_module);
	}

	~Import() {
		CLEVER_DELREF(m_package);
		CLEVER_SAFE_DELREF(m_module);
	}

	Ident* getPackage() const { return m_package; }
	Ident* getModule() const { return m_module; }
	bool hasModule() const { return m_module != NULL; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Ident* m_package;
	Ident* m_module;
};

class VariableDecl: public Node {
public:
	VariableDecl(Ident* ident, Assignment* assignment, const location& location)
		: Node(location), m_ident(ident), m_assignment(assignment) {
		CLEVER_ADDREF(m_ident);
		CLEVER_SAFE_ADDREF(m_assignment);
	}

	~VariableDecl() {
		CLEVER_DELREF(m_ident);
		CLEVER_SAFE_DELREF(m_assignment);
	}

	Ident* getIdent() const { return m_ident; }
	void setAssignment(Assignment* assignment) {
		m_assignment = assignment;
		CLEVER_SAFE_ADDREF(m_assignment);
	}

	Assignment* getAssignment() { return m_assignment; }
	bool hasAssignment() const { return m_assignment != NULL; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

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

	bool isEvaluable() const { return true; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	ArithOperator m_op;
	Node* m_lhs;
	Node* m_rhs;
};

class Logic: public Node {
public:
	enum LogicOperator {
		LOP_EQUALS,
		LOP_NEQUALS,
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

	bool isEvaluable() const { return true; }

	LogicOperator getOperator() const { return m_op; }
	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	LogicOperator m_op;
	Node* m_lhs;
	Node* m_rhs;
};

class Boolean: public Node {
public:
	enum BooleanOperator {
		BOP_AND,
		BOP_OR
	};

	Boolean(BooleanOperator op, Node* lhs, Node* rhs, const location& location)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(rhs) {
		CLEVER_ADDREF(m_lhs);
		CLEVER_ADDREF(m_rhs);
	}

	~Boolean() {
		CLEVER_DELREF(m_lhs);
		CLEVER_DELREF(m_rhs);
	}

	BooleanOperator getOperator() const { return m_op; }
	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	bool isEvaluable() const { return true; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	BooleanOperator m_op;
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

	bool isEvaluable() const { return true; }

	BitwiseOperator getOperator() const { return m_op; }
	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	BitwiseOperator m_op;
	Node* m_lhs;
	Node* m_rhs;
};

class FunctionDecl: public Node {
public:
	FunctionDecl(Ident* ident, NodeArray* args, Block* block, const location& location)
		: Node(location), m_ident(ident), m_args(args), m_block(block), m_is_anon(false) {
		CLEVER_SAFE_ADDREF(m_ident);
		CLEVER_SAFE_ADDREF(m_args);
		CLEVER_SAFE_ADDREF(m_block);

		if (!ident) {
			m_is_anon = true;
		}
	}

	~FunctionDecl() {
		CLEVER_SAFE_DELREF(m_ident);
		CLEVER_SAFE_DELREF(m_args);
		CLEVER_SAFE_DELREF(m_block);
	}

	void setIdent(Ident* ident) {
		CLEVER_SAFE_DELREF(m_ident);
		m_ident = ident;
		CLEVER_SAFE_ADDREF(m_ident);
	}

	bool isAnonymous() const { return m_is_anon; }

	Ident* getIdent() { return m_ident; }
	bool hasIdent() { return m_ident != NULL; }

	NodeArray* getArgs() { return m_args; }
	bool hasArgs() const { return m_args != NULL && m_args->getSize() > 0; }

	size_t numArgs() const { return m_args->getSize(); }

	Node* getArg(size_t index) {
		return m_args->getNode(index);
	}

	Block* getBlock() { return m_block; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	Ident* m_ident;
	NodeArray* m_args;
	Block* m_block;
	bool m_is_anon;
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

	bool isEvaluable() const { return true; }

	Node* getArg(size_t index) {
		std::vector<Node*> array = m_args->getNodes();

		clever_assert(index > 0 && index < array.size(), "Index %i out of bounds.", index);

		if (array.empty())
			return NULL;

		return array.at(index);
	}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	Node* m_callee;
	NodeArray* m_args;
};

class While: public Node {
public:
	While(Node* condition, Node* block, const location& location)
		: Node(location), m_condition(condition), m_block(block) {
		CLEVER_ADDREF(m_condition);
		CLEVER_SAFE_ADDREF(m_block);
	}

	~While() {
		CLEVER_DELREF(m_condition);
		CLEVER_SAFE_DELREF(m_block);
	}

	Node* getCondition() { return m_condition; }

	Node* getBlock() { return m_block; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	Node *m_condition;
	Node *m_block;
};

/// This class can handle both simple and complex (if + ifelse) if statements.
/// If you want to add a new conditional block, use the addConditional method.
class If: public Node {
public:
	If(Node* cond_node, Node* then_node, const location& location)
		: Node(location), m_else_node(NULL) {

		addConditional(cond_node, then_node);
	}

	~If() {
		std::vector<std::pair<Node*, Node*> >::const_iterator it(m_conditionals.begin()),
			end(m_conditionals.end());

		while (it != end) {
			CLEVER_DELREF((*it).first);
			CLEVER_DELREF((*it).second);
			++it;
		}
		if (m_else_node) {
			CLEVER_DELREF(m_else_node);
		}
	}

	void addConditional(Node* cond_node, Node* then_node) {
		clever_assert_not_null(cond_node);

		m_conditionals.push_back(std::pair<Node*,Node*>(cond_node, then_node));

		CLEVER_ADDREF(cond_node);
		CLEVER_ADDREF(then_node);
	}

	std::vector<std::pair<Node*, Node*> >& getConditionals() { return m_conditionals; }

	void setElseNode(Node* else_node) {
		m_else_node = else_node;
		CLEVER_ADDREF(m_else_node);
	}

	Node* getElseNode() { return m_else_node; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	Node *m_else_node;
	std::vector<std::pair<Node*, Node*> > m_conditionals;
};

class Literal: public Node {
public:
	Literal(const location& location)
		: Node(location), m_const_id(0) {}

	virtual ~Literal() {}

	virtual bool isLiteral() const { return true; }

	virtual void setConstId(size_t const_id) { m_const_id = const_id; }

	virtual size_t getConstId() const { return m_const_id; }
private:
	size_t m_const_id;
};

class IntLit: public Literal {
public:
	IntLit(long value, const location& location)
		: Literal(location), m_value(value) {}

	long getValue() const { return m_value; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

	virtual IntLit* getIntLit() { return this; }

private:
	long m_value;
};

class DoubleLit: public Literal {
public:
	DoubleLit(double value, const location& location)
		: Literal(location), m_value(value) {}

	double getValue() const { return m_value; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

	virtual DoubleLit* getDoubleLit() { return this; }

private:
	double m_value;
};

class StringLit: public Literal {
public:
	StringLit(const CString* value, const location& location)
		: Literal(location), m_value(value) {}

	const CString* getValue() const { return m_value; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	const CString* m_value;
};

class Return: public Node {
public:
	Return(Node* value, const location& location)
		: Node(location), m_value(value) {
		CLEVER_SAFE_ADDREF(m_value);
	}

	~Return() {
		CLEVER_SAFE_DELREF(m_value);
	}

	bool hasValue() const { return m_value != NULL; }
	Node* getValue() const { return m_value; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Node* m_value;
};

class IncDec: public Node {
public:
	enum IncDecOperator {
		PRE_INC,
		PRE_DEC,
		POS_INC,
		POS_DEC
	};

	IncDec(IncDecOperator op, Node* var, const location& location)
		: Node(location), m_op(op), m_var(var) {
		CLEVER_ADDREF(m_var);
	}

	~IncDec() {
		CLEVER_DELREF(m_var);
	}

	bool isEvaluable() const { return true; }

	Node* getVar() const { return m_var; }

	IncDecOperator getOperator() const { return m_op; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	IncDecOperator m_op;
	Node* m_var;
};

}} // clever::ast

#endif // CLEVER_AST_H
