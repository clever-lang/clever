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
class ThreadBlock;
class CriticalBlock;
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
class NullLit;
class MethodCall;
class Property;
class Try;
class TrueLit;
class FalseLit;
class Array;

typedef std::vector<Node*> NodeList;

class Visitor;
class Transformer;

class Node: public RefCounted {
public:
	Node(const location& location)
		: RefCounted(0), m_location(location), m_scope(NULL), m_voffset(0,0) {}

	virtual ~Node() {}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

	virtual bool isLiteral() const { return false; }
	virtual bool isEvaluable() const { return false; }

	const location& getLocation() const { return m_location; }

	virtual IntLit* getIntLit() { return NULL; }
	virtual DoubleLit* getDoubleLit() { return NULL; }
	virtual StringLit* getStrLit() { return NULL; }

	virtual void setScope(const Scope* scope) { m_scope = scope; }
	virtual const Scope* getScope() const { return m_scope; }

	virtual void setVOffset(const ValueOffset& offset) { m_voffset = offset; }
	ValueOffset& getVOffset() { return m_voffset; }

private:
	const location& m_location;
	size_t m_value_id;
	const Scope* m_scope;
	ValueOffset m_voffset;

	DISALLOW_COPY_AND_ASSIGN(Node);
};

class NodeArray: public Node {
public:
	NodeArray(const location& location)
		: Node(location), m_nodes() {}

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



class Comparison: public Node {
public:
	enum ComparisonOperator {
		COP_EQUAL,
		COP_NEQUAL,
		COP_GREATER,
		COP_GEQUAL,
		COP_LESS,
		COP_LEQUAL
	};

	Comparison(ComparisonOperator op, Node* lhs, Node* rhs, const location& location)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(rhs) {
		CLEVER_ADDREF(m_lhs);
		CLEVER_ADDREF(m_rhs);
	}

	~Comparison() {
		CLEVER_DELREF(m_lhs);
		CLEVER_DELREF(m_rhs);
	}

	ComparisonOperator getOperator() const { return m_op; }

	Node* getLhs() { return m_lhs; }
	Node* getRhs() { return m_rhs; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	ComparisonOperator m_op;
	Node* m_lhs;
	Node* m_rhs;

	DISALLOW_COPY_AND_ASSIGN(Comparison);
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

	DISALLOW_COPY_AND_ASSIGN(Assignment);
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

	DISALLOW_COPY_AND_ASSIGN(Ident);
};

class ThreadBlock: public NodeArray {
public:
	ThreadBlock(Block* block, const location& location)
		: NodeArray(location), m_block(block), m_name(NULL), m_size(NULL) {
		CLEVER_ADDREF(m_block);
	}

	ThreadBlock(Block* block, Ident* name, const location& location)
		: NodeArray(location), m_block(block), m_name(name), m_size(NULL) {
		CLEVER_ADDREF(m_block);
		CLEVER_ADDREF(m_name);
	}


	ThreadBlock(Block* block, Ident* name, Node* size, const location& location)
		: NodeArray(location), m_block(block), m_name(name), m_size(size) {
		CLEVER_ADDREF(m_block);
		CLEVER_ADDREF(m_name);
		CLEVER_ADDREF(m_size);
	}

	~ThreadBlock() {
		CLEVER_DELREF(m_block);
		CLEVER_SAFE_DELREF(m_name);
		CLEVER_SAFE_DELREF(m_size);
	}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

	Ident* getName() { return m_name; }

	Block* getBlock() { return m_block; }

	Node* getSize() { return m_size; }

protected:
	Block* m_block;
	Ident* m_name;
	Node* m_size;

private:
	DISALLOW_COPY_AND_ASSIGN(ThreadBlock);
};

class Wait: public NodeArray {
public:
	Wait(Ident* name, const location& location)
		: NodeArray(location), m_name(name) {
		CLEVER_ADDREF(m_name);
	}

	~Wait() {
		CLEVER_DELREF(m_name);
	}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

	Ident* getName() { return m_name; }

protected:
	Ident* m_name;

private:
	DISALLOW_COPY_AND_ASSIGN(Wait);
};

class CriticalBlock: public NodeArray {
public:
	CriticalBlock(Block* block, const location& location)
		: NodeArray(location), m_block(block) {
		CLEVER_ADDREF(m_block);
	}

	~CriticalBlock() {
		CLEVER_DELREF(m_block);
	}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

	Block* getBlock() { return m_block; }
protected:
	Block* m_block;
private:
	DISALLOW_COPY_AND_ASSIGN(CriticalBlock);
};

class Type: public Node {
public:
	Type(const CString* name, const location& location)
		: Node(location), m_name(name), m_sym(NULL) {}
	~Type() {}

	const CString* getName() const { return m_name; }

	void setSymbol(Symbol* sym)	{ m_sym = sym; }
	Symbol* getSymbol() { return m_sym; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	const CString* m_name;
	Symbol* m_sym;

	DISALLOW_COPY_AND_ASSIGN(Type);
};

class Instantiation: public Node {
public:
	Instantiation(const CString* type, NodeArray* args, const location& location)
		: Node(location), m_type(new Type(type, location)), m_args(args) {
		CLEVER_ADDREF(m_type);
		CLEVER_SAFE_ADDREF(m_args);
	}

	Instantiation(Type* type, NodeArray* args, const location& location)
		: Node(location), m_type(type), m_args(args) {
		CLEVER_ADDREF(m_type);
		CLEVER_SAFE_ADDREF(m_args);
	}
	~Instantiation() {
		CLEVER_DELREF(m_type);
		CLEVER_SAFE_DELREF(m_args);
	}

	Type* getType() { return m_type; }

	NodeArray* getArgs() { return m_args; }
	bool hasArgs() const { return m_args != NULL && m_args->getSize() > 0; }

	size_t numArgs() const { return m_args->getSize(); }

	Node* getArg(size_t index) {
		return m_args->getNode(index);
	}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Type* m_type;
	NodeArray* m_args;

	DISALLOW_COPY_AND_ASSIGN(Instantiation);
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

	DISALLOW_COPY_AND_ASSIGN(Import);
};

class VariableDecl: public Node {
public:
	VariableDecl(Ident* ident, Assignment* assignment, bool is_const,
		const location& location)
		: Node(location), m_ident(ident), m_assignment(assignment),
		m_is_const(is_const) {
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

	Assignment* getAssignment() const { return m_assignment; }
	bool hasAssignment() const { return m_assignment != NULL; }

	bool isConst() const { return m_is_const; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	Ident* m_ident;
	Assignment* m_assignment;
	const bool m_is_const;

	DISALLOW_COPY_AND_ASSIGN(VariableDecl);
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

	DISALLOW_COPY_AND_ASSIGN(Arithmetic);
};

class Logic: public Node {
public:
	enum LogicOperator {
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

	DISALLOW_COPY_AND_ASSIGN(Logic);
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

	DISALLOW_COPY_AND_ASSIGN(Boolean);
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

	DISALLOW_COPY_AND_ASSIGN(Bitwise);
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

	DISALLOW_COPY_AND_ASSIGN(FunctionDecl);
};

class MethodCall: public Node {
public:
	MethodCall(Node* callee, Ident* method, NodeArray* args, const location& location)
		: Node(location), m_callee(callee), m_method(method), m_args(args), m_static(false) {
		CLEVER_ADDREF(m_callee);
		CLEVER_ADDREF(m_method);
		CLEVER_SAFE_ADDREF(m_args);
	}

	MethodCall(Type* callee, Ident* method, NodeArray* args, const location& location)
		: Node(location), m_callee(callee), m_method(method), m_args(args), m_static(true) {
		CLEVER_ADDREF(m_callee);
		CLEVER_ADDREF(m_method);
		CLEVER_SAFE_ADDREF(m_args);
	}

	~MethodCall() {
		CLEVER_DELREF(m_callee);
		CLEVER_DELREF(m_method);
		CLEVER_SAFE_DELREF(m_args);
	}

	bool isStaticCall() const { return m_static; }

	bool isEvaluable() const { return true; }

	Node* getCallee() const { return m_callee; }

	Ident* getMethod() const { return m_method; }

	NodeArray* getArgs() const { return m_args; }
	bool hasArgs() const { return m_args != NULL && m_args->getSize() > 0; }

	size_t numArgs() const { return m_args->getSize(); }

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
	Ident* m_method;
	NodeArray* m_args;
	bool m_static;

	DISALLOW_COPY_AND_ASSIGN(MethodCall);
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

	DISALLOW_COPY_AND_ASSIGN(FunctionCall);
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

	DISALLOW_COPY_AND_ASSIGN(While);
};

/// This class can handle both simple and complex (if + ifelse) if statements.
/// If you want to add a new conditional block, use the addConditional method.
class If: public Node {
public:
	If(Node* cond_node, Node* then_node, const location& location)
		: Node(location), m_else_node(NULL), m_conditionals() {

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

	DISALLOW_COPY_AND_ASSIGN(If);
};

class Literal: public Node {
public:
	Literal(const location& location)
		: Node(location), m_const_id(0) {}

	virtual ~Literal() {}

	virtual bool isLiteral() const { return true; }
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

	DISALLOW_COPY_AND_ASSIGN(StringLit);
};

class NullLit: public Literal {
public:
	NullLit(const location& location)
		: Literal(location) {}

	~NullLit() {}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
};

class TrueLit: public Literal {
public:
	TrueLit(const location& location)
		: Literal(location) {}

	~TrueLit() {}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
};

class FalseLit: public Literal {
public:
	FalseLit(const location& location)
		: Literal(location) {}

	~FalseLit() {}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
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

	DISALLOW_COPY_AND_ASSIGN(Return);
};

class Property: public Node {
public:
	Property(Node* obj, Ident* prop_name, const location& location)
		: Node(location), m_obj(obj), m_prop_name(prop_name) {
		CLEVER_ADDREF(m_obj);
		CLEVER_ADDREF(m_prop_name);
	}

	~Property() {
		CLEVER_DELREF(m_obj);
		CLEVER_DELREF(m_prop_name);
	}

	Node* getObject() const { return m_obj; }
	Ident* getProperty() const { return m_prop_name; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Node* m_obj;
	Ident* m_prop_name;

	DISALLOW_COPY_AND_ASSIGN(Property);
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

	DISALLOW_COPY_AND_ASSIGN(IncDec);
};

class Try: public Node {
public:
	Try(Block* try_block, NodeArray* catches, Block* finally, const location& location)
		: Node(location), m_try(try_block), m_catch(catches), m_finally(finally) {
		CLEVER_ADDREF(m_try);
		CLEVER_SAFE_ADDREF(m_catch);
		CLEVER_SAFE_ADDREF(m_finally);
	}
	~Try() {
		CLEVER_DELREF(m_try);
		CLEVER_SAFE_DELREF(m_catch);
		CLEVER_SAFE_DELREF(m_finally);
	}

	Block* getBlock() const { return m_try; }

	NodeArray* getCatches() const { return m_catch; }

	Block* getFinally() const { return m_finally; }
	bool hasFinally() const { return m_finally != NULL; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Block* m_try;
	NodeArray* m_catch;
	Block* m_finally;

	DISALLOW_COPY_AND_ASSIGN(Try);
};

class Catch: public Node {
public:
	Catch(Ident* var, Block* block, const location& location)
		: Node(location), m_var(var), m_block(block) {
		CLEVER_ADDREF(m_var);
		CLEVER_ADDREF(m_block);
	}

	~Catch() {
		CLEVER_DELREF(m_var);
		CLEVER_DELREF(m_block);
	}

	Ident* getVar() const { return m_var; }

	Block* getBlock() const { return m_block; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Ident* m_var;
	Block* m_block;

	DISALLOW_COPY_AND_ASSIGN(Catch);
};

class Throw: public Node {
public:
	Throw(Node* expr, const location& location)
		: Node(location), m_expr(expr) {
		CLEVER_ADDREF(m_expr);
	}

	~Throw() {
		CLEVER_DELREF(m_expr);
	}

	Node* getExpr() const { return m_expr; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Node* m_expr;

	DISALLOW_COPY_AND_ASSIGN(Throw);
};

}} // clever::ast

#endif // CLEVER_AST_H
