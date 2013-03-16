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
class CriticalBlock;
class Assignment;
class VariableDecl;
class Arithmetic;
class FunctionDecl;
class FunctionCall;
class While;
class For;
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
class Break;
class Continue;
class AttrDecl;

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
	const location m_location;
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

		if (m_nodes.empty()) {
			return NULL;
		}

		return m_nodes.at(index);
	}

	Node* append(Node* node) {
		m_nodes.push_back(node);
		node->addRef();
		return node;
	}

	size_t getSize() const { return m_nodes.size(); }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

	void clearNodes() {
		NodeList::iterator it(m_nodes.begin()), end(m_nodes.end());

		while (it != end) {
			(*it)->delRef();
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
		m_lhs->addRef();
		m_rhs->addRef();
	}

	~Comparison() {
		m_lhs->delRef();
		m_rhs->delRef();
	}

	ComparisonOperator getOperator() const { return m_op; }

	Node* getLhs() const { return m_lhs; }
	Node* getRhs() const { return m_rhs; }

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
		: Node(location), m_conditional(false), m_result(false), m_lhs(lhs), m_rhs(rhs) {
		m_lhs->addRef();
		clever_addref(m_rhs);
	}

	~Assignment() {
		m_lhs->delRef();
		clever_delref(m_rhs);
	}

	void setRhs(Node* rhs) {
		m_rhs = rhs;
		clever_addref(m_rhs);
	}

	Node* getLhs() const { return m_lhs; }
	Node* getRhs() const { return m_rhs; }

	void setConditional(bool conditional) {
		m_conditional = conditional;
	}

	bool isConditional() const {
		return m_conditional;
	}

	void setUseResult() { m_result = true; }
	bool hasResult() const { return m_result; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	bool m_conditional;
	bool m_result;
	Node* m_lhs;
	Node* m_rhs;

	DISALLOW_COPY_AND_ASSIGN(Assignment);
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

	void append(char separator, ast::Type* ident) {
		m_name = CSTRING(*m_name + separator + *ident->getName());
		clever_delete(ident);
	}
private:
	const CString* m_name;
	Symbol* m_sym;

	DISALLOW_COPY_AND_ASSIGN(Type);
};

class Ident: public Node {
public:
	Ident(const CString* name, const location& location)
		: Node(location), m_name(name), m_sym(NULL) {
		clever_assert_not_null(m_name);
	}

	const CString* getName() const { return m_name; }

	void setSymbol(Symbol* sym)	{ m_sym = sym; }
	Symbol* getSymbol() { return m_sym; }

	void append(char separator, Ident* ident) {
		m_name = CSTRING(*m_name + separator + *ident->getName());
		clever_delete(ident);
	}

	void append(char separator, ast::Type* ident) {
		m_name = CSTRING(*m_name + separator + *ident->getName());
		clever_delete(ident);
	}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	const CString* m_name;
	Symbol* m_sym;

	DISALLOW_COPY_AND_ASSIGN(Ident);
};

class CriticalBlock: public NodeArray {
public:
	CriticalBlock(Block* block, const location& location)
		: NodeArray(location), m_block(block) {
		m_block->addRef();
	}

	~CriticalBlock() {
		m_block->delRef();
	}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

	Block* getBlock() { return m_block; }
protected:
	Block* m_block;
private:
	DISALLOW_COPY_AND_ASSIGN(CriticalBlock);
};

class Instantiation: public Node {
public:
	Instantiation(const CString* type, NodeArray* args, const location& location)
		: Node(location), m_type(new Type(type, location)), m_args(args) {
		m_type->addRef();
		clever_addref(m_args);
	}

	Instantiation(Ident* type, NodeArray* args, const location& location)
		: Node(location), m_type(new Type(type->getName(), location)), m_args(args) {
		m_type->addRef();
		clever_delete(type);
		clever_addref(m_args);
	}

	Instantiation(Type* type, NodeArray* args, const location& location)
		: Node(location), m_type(type), m_args(args) {
		m_type->addRef();
		clever_addref(m_args);
	}

	~Instantiation() {
		m_type->delRef();
		clever_delref(m_args);
	}

	Type* getType() const { return m_type; }

	NodeArray* getArgs() const { return m_args; }
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
	Import(Ident* name, const location& location)
		: Node(location), m_module(name), m_func(NULL), m_type(NULL),
			m_namespaced(false) {
		clever_addref(m_module);
	}

	Import(Ident* name, Ident* func, const location& location)
		: Node(location), m_module(name), m_func(func), m_type(NULL),
			m_tree(NULL), m_namespaced(false) {
		clever_addref(m_module);
		m_func->addRef();
	}

	Import(Ident* module, Type* type, const location& location)
		: Node(location), m_module(module), m_func(NULL), m_type(type),
			m_tree(NULL), m_namespaced(false) {
		clever_addref(m_module);
		m_type->addRef();
	}

	~Import() {
		clever_delref(m_module);
		clever_delref(m_func);
		clever_delref(m_type);
		clever_delref(m_tree);
	}

	Type* getType() const { return m_type; }
	Ident* getFunction() const { return m_func; }
	Ident* getModule() const { return m_module; }
	bool hasModule() const { return m_module != NULL; }

	bool hasModuleTree() const { return m_tree != NULL; }
	void setModuleTree(Node* tree) {
		m_tree = tree;
		clever_addref(m_tree);
	}
	Node* getModuleTree() const { return m_tree; }

	void setNamespaced(bool val) { m_namespaced = val; }
	bool isNamespaced() { return m_namespaced; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Ident* m_module;
	Ident* m_func;
	Type* m_type;
	Node* m_tree;
	bool m_namespaced;

	DISALLOW_COPY_AND_ASSIGN(Import);
};

class VariableDecl: public Node {
public:
	VariableDecl(Ident* ident, Assignment* assignment, bool is_const,
				 const location& location)
		: Node(location), m_ident(ident), m_assignment(assignment),
		  m_is_const(is_const) {
		m_ident->addRef();
		clever_addref(m_assignment);
	}

	~VariableDecl() {
		m_ident->delRef();
		clever_delref(m_assignment);
	}

	Ident* getIdent() const { return m_ident; }
	void setAssignment(Assignment* assignment) {
		m_assignment = assignment;
		clever_addref(m_assignment);
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

	Arithmetic(ArithOperator op, Node* lhs, Node* rhs, const location& location, bool is_augmented = false)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(rhs), m_is_augmented(is_augmented) {
		m_lhs->addRef();
		m_rhs->addRef();
	}

	~Arithmetic() {
		m_lhs->delRef();
		m_rhs->delRef();
	}

	ArithOperator getOperator() const { return m_op; }
	Node* getLhs() const { return m_lhs; }
	Node* getRhs() const { return m_rhs; }

	bool isEvaluable() const { return true; }
	bool isAugmented() const { return m_is_augmented; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	ArithOperator m_op;
	Node* m_lhs;
	Node* m_rhs;
	bool m_is_augmented;

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
		m_lhs->addRef();
		m_rhs->addRef();
	}

	~Logic() {
		m_lhs->delRef();
		m_rhs->delRef();
	}

	bool isEvaluable() const { return true; }

	LogicOperator getOperator() const { return m_op; }
	Node* getLhs() const { return m_lhs; }
	Node* getRhs() const { return m_rhs; }

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
		BOP_OR,
		BOP_NOT
	};

	Boolean(BooleanOperator op, Node* lhs, Node* rhs, const location& location)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(rhs) {
		clever_addref(m_lhs);
		clever_addref(m_rhs);
	}

	Boolean(BooleanOperator op, Node* lhs, const location& location)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(NULL) {
		clever_addref(m_lhs);
	}

	~Boolean() {
		clever_delref(m_lhs);
		clever_delref(m_rhs);
	}

	BooleanOperator getOperator() const { return m_op; }
	Node* getLhs() const { return m_lhs; }
	Node* getRhs() const { return m_rhs; }

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
		BOP_NOT,
		BOP_LSHIFT,
		BOP_RSHIFT
	};

	Bitwise(BitwiseOperator op, Node* lhs, Node* rhs, const location& location, bool is_augmented = false)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(rhs), m_is_augmented(is_augmented) {
		m_lhs->addRef();
		m_rhs->addRef();
	}

	Bitwise(BitwiseOperator op, Node* lhs, const location& location)
		: Node(location), m_op(op), m_lhs(lhs), m_rhs(NULL), m_is_augmented(false) {
		m_lhs->addRef();
	}

	~Bitwise() {
		m_lhs->delRef();
		m_rhs->delRef();
	}

	bool isEvaluable() const { return true; }
	bool isAugmented() const { return m_is_augmented; }

	BitwiseOperator getOperator() const { return m_op; }
	Node* getLhs() const { return m_lhs; }
	Node* getRhs() const { return m_rhs; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	BitwiseOperator m_op;
	Node* m_lhs;
	Node* m_rhs;
	bool m_is_augmented;

	DISALLOW_COPY_AND_ASSIGN(Bitwise);
};

enum Visibility {
	PUBLIC,
	PRIVATE
};

class FunctionDecl: public Node {
public:
	FunctionDecl(Ident* ident, NodeArray* args, Block* block,
		VariableDecl* vararg, bool is_anon, const location& location)
		: Node(location), m_ident(ident), m_type(NULL), m_args(args), m_block(block),
			m_vararg(vararg), m_is_anon(is_anon), m_is_ctor(false), m_is_dtor(false),
			m_visibility(0), m_func(NULL) {
		clever_addref(m_ident);
		clever_addref(m_args);
		clever_addref(m_block);
		clever_addref(m_vararg);
	}

	FunctionDecl(Type* type, NodeArray* args, Block* block, VariableDecl* vararg,
		const location& location)
		: Node(location), m_ident(NULL), m_type(type), m_args(args), m_block(block),
			m_vararg(vararg), m_is_anon(false), m_is_ctor(false), m_is_dtor(false),
			m_visibility(0), m_func(NULL) {
		clever_addref(m_type);
		clever_addref(m_args);
		clever_addref(m_block);
		clever_addref(m_vararg);
	}

	~FunctionDecl() {
		clever_delref(m_ident);
		clever_delref(m_type);
		clever_delref(m_args);
		clever_delref(m_block);
		clever_delref(m_vararg);
	}

	void setIdent(Ident* ident) {
		clever_delref(m_ident);
		m_ident = ident;
		clever_addref(m_ident);
	}

	void setType(Type* type) {
		clever_delref(m_type);
		m_type = type;
		clever_addref(m_type);
	}

	void setVisibility(size_t flags) { m_visibility = flags; }
	size_t getVisibility() const { return m_visibility; }

	bool isAnonymous() const { return m_is_anon; }
	bool isCtor() const { return m_is_ctor; }
	bool isDtor() const { return m_is_dtor; }
	bool isMethod() const { return m_func != NULL; }

	void setCtor() { m_is_ctor = true; }
	void setDtor() { m_is_dtor = true; }
	void setMethod(Function* func) { m_func = func; }

	Type* getType() const { return m_type; }
	bool hasType() const { return m_type != NULL; }
	Function* getMethod() const { return m_func; }

	Ident* getIdent() const { return m_ident; }
	bool hasIdent() const { return m_ident != NULL; }

	NodeArray* getArgs() const { return m_args; }
	bool hasArgs() const { return m_args != NULL && m_args->getSize() > 0; }
	size_t numArgs() const { return m_args->getSize(); }

	Node* getArg(size_t index) {
		return m_args->getNode(index);
	}

	bool hasVarArg() const { return m_vararg != NULL; }
	VariableDecl* getVarArg() const { return m_vararg; }

	Block* getBlock() { return m_block; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	Ident* m_ident;
	Type* m_type;
	NodeArray* m_args;
	Block* m_block;
	VariableDecl* m_vararg;
	bool m_is_anon;
	bool m_is_ctor;
	bool m_is_dtor;
	size_t m_visibility;
	Function* m_func;

	DISALLOW_COPY_AND_ASSIGN(FunctionDecl);
};

class MethodCall: public Node {
public:
	MethodCall(Node* callee, Ident* method, NodeArray* args, const location& location)
		: Node(location), m_callee(callee), m_method(method), m_args(args), m_static(false) {
		m_callee->addRef();
		m_method->addRef();
		clever_addref(m_args);
	}

	MethodCall(Type* callee, Ident* method, NodeArray* args, const location& location)
		: Node(location), m_callee(callee), m_method(method), m_args(args), m_static(true) {
		m_callee->addRef();
		m_method->addRef();
		clever_addref(m_args);
	}

	~MethodCall() {
		m_callee->delRef();
		m_method->delRef();
		clever_delref(m_args);
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
		m_callee->addRef();
		clever_addref(m_args);
	}

	~FunctionCall() {
		m_callee->delRef();
		clever_delref(m_args);
	}

	Node* getCallee() const { return m_callee; }

	NodeArray* getArgs() const { return m_args; }
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
		m_condition->addRef();
		clever_addref(m_block);
	}

	~While() {
		m_condition->delRef();
		clever_delref(m_block);
	}

	Node* getCondition() const { return m_condition; }

	Node* getBlock() const { return m_block; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	Node *m_condition;
	Node *m_block;

	DISALLOW_COPY_AND_ASSIGN(While);
};

class For: public Node {
public:
	For(NodeArray* initlist, Node* cond, NodeArray* update, Node* block, const location& location)
		: Node(location),  m_init(initlist), m_condition(cond), m_update(update), m_block(block) {
		clever_addref(m_init);
		clever_addref(m_condition);
		clever_addref(m_update);
		clever_addref(m_block);
	}

	~For() {
		clever_delref(m_init);
		clever_delref(m_condition);
		clever_delref(m_update);
		clever_delref(m_block);
	}

	bool hasInitializer() const { return m_init != NULL; }
	bool hasCondition() const { return m_condition != NULL; }
	bool hasUpdate() const { return m_update != NULL; }

	NodeArray* getInitializer() const { return m_init; }
	Node* getCondition() const { return m_condition; }
	NodeArray* getUpdate() const { return m_update; }

	Node* getBlock() const { return m_block; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	NodeArray* m_init;
	Node* m_condition;
	NodeArray* m_update;
	Node* m_block;

	DISALLOW_COPY_AND_ASSIGN(For);
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
			(*it).first->delRef();
			(*it).second->delRef();
			++it;
		}
		if (m_else_node) {
			m_else_node->delRef();
		}
	}

	void addConditional(Node* cond_node, Node* then_node) {
		clever_assert_not_null(cond_node);

		m_conditionals.push_back(std::pair<Node*,Node*>(cond_node, then_node));

		cond_node->addRef();
		then_node->addRef();
	}

	std::vector<std::pair<Node*, Node*> >& getConditionals() { return m_conditionals; }

	void setElseNode(Node* else_node) {
		m_else_node = else_node;
		m_else_node->addRef();
	}

	Node* getElseNode() const { return m_else_node; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);

private:
	Node* m_else_node;
	std::vector<std::pair<Node*, Node*> > m_conditionals;

	DISALLOW_COPY_AND_ASSIGN(If);
};

class Literal: public Node {
public:
	Literal(const location& location) : Node(location) {}

	virtual ~Literal() {}

	virtual bool isLiteral() const { return true; }
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
		clever_addref(m_value);
	}

	~Return() {
		clever_delref(m_value);
	}

	bool hasValue() const { return m_value != NULL; }
	Node* getValue() const { return m_value; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Node* m_value;

	DISALLOW_COPY_AND_ASSIGN(Return);
};

class Subscript: public Node {
public:
	Subscript(Node* var, Node* index, const location& location)
		: Node(location), m_var(var), m_index(index) {
		clever_addref(m_var);
		clever_addref(m_index);
	}

	~Subscript() {
		clever_delref(m_var);
		clever_delref(m_index);
	}

	Node* getVar() const { return m_var; }
	Node* getIndex() const { return m_index; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Node* m_var;
	Node* m_index;

	DISALLOW_COPY_AND_ASSIGN(Subscript);
};

class Property: public Node {
public:
	enum Flags { WRITE, READ };

	Property(Node* callee, Ident* prop_name, const location& location)
		: Node(location), m_callee(callee), m_prop_name(prop_name),
		  m_static(false), m_mode(READ) {
		m_callee->addRef();
		m_prop_name->addRef();
	}

	Property(Type* callee, Ident* prop_name, const location& location)
		: Node(location), m_callee(callee), m_prop_name(prop_name),
		  m_static(true), m_mode(READ) {
		m_callee->addRef();
		m_prop_name->addRef();
	}

	~Property() {
		m_callee->delRef();
		m_prop_name->delRef();
	}

	Node* getCallee() const { return m_callee; }
	Ident* getProperty() const { return m_prop_name; }

	bool isStatic() const { return m_static; }
	void setStatic() { m_static = true; }

	void setWriteMode() { m_mode = WRITE; }
	void setReadMode() { m_mode = READ; }

	Flags getMode() const { return m_mode; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Node* m_callee;
	Ident* m_prop_name;
	bool m_static;
	Flags m_mode;

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
		m_var->addRef();
	}

	~IncDec() {
		m_var->delRef();
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
		m_try->addRef();
		clever_addref(m_catch);
		clever_addref(m_finally);
	}
	~Try() {
		m_try->delRef();
		clever_delref(m_catch);
		clever_delref(m_finally);
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
		m_var->addRef();
		m_block->addRef();
	}

	~Catch() {
		m_var->delRef();
		m_block->delRef();
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
		m_expr->addRef();
	}

	~Throw() {
		m_expr->delRef();
	}

	Node* getExpr() const { return m_expr; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Node* m_expr;

	DISALLOW_COPY_AND_ASSIGN(Throw);
};

class Break: public Node {
public:
	Break(const location& location)
		: Node(location) {}

	~Break() {}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	DISALLOW_COPY_AND_ASSIGN(Break);
};

class Continue: public Node {
public:
	Continue(const location& location)
		: Node(location) {}

	~Continue() {}

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	DISALLOW_COPY_AND_ASSIGN(Continue);
};

class AttrDecl: public Node {
public:
	AttrDecl(Ident* ident, Node* value, bool is_const, const location& location)
		: Node(location), m_ident(ident), m_value(value), m_const(is_const) {
		m_ident->addRef();
		clever_addref(m_value);
	}

	~AttrDecl() {
		m_ident->delRef();
		clever_delref(m_value);
	}

	Ident* getIdent() const { return m_ident; }

	Node* getValue() const { return m_value; }
	bool hasValue() const { return m_value != NULL; }

	bool isConst() const { return m_const; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Ident* m_ident;
	Node* m_value;
	bool m_const;
};

class ClassDef: public Node {
public:
	ClassDef(Type* name, NodeArray* attrs, NodeArray* methods, const location& location)
		: Node(location), m_type(name), m_attrs(attrs), m_methods(methods) {
		m_type->addRef();
		clever_addref(m_attrs);
		clever_addref(m_methods);
	}

	~ClassDef() {
		m_type->delRef();
		clever_delref(m_attrs);
		clever_delref(m_methods);
	}

	bool hasAttrs() const { return m_attrs != NULL; }
	bool hasMethods() const { return m_methods != NULL; }

	NodeArray* getAttrs() const { return m_attrs; }
	NodeArray* getMethods() const { return m_methods; }

	Type* getType() const { return m_type; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Type* m_type;
	NodeArray* m_attrs;
	NodeArray* m_methods;
};

class Switch: public Node {
public:
	Switch(Node* expr, const location& location)
		: Node(location), m_expr(expr) {
		clever_addref(m_expr);
	}

	~Switch() {
		clever_delref(m_expr);

		std::vector<std::pair<Node*, Node*> >::const_iterator it(m_cases.begin()),
			end(m_cases.end());

		for (; it != end; ++it) {
			clever_delref(it->first);
			clever_delref(it->second);
		}
	}

	void addCase(Node* label, Node* block) {
		m_cases.push_back(std::pair<Node*, Node*>(label, block));
		clever_addref(label);
		clever_addref(block);
	}

	std::vector<std::pair<Node*, Node*> >& getCases() { return m_cases; }

	Node* getExpr() const { return m_expr; }

	virtual void accept(Visitor& visitor);
	virtual Node* accept(Transformer& transformer);
private:
	Node* m_expr;
	std::vector<std::pair<Node*, Node*> > m_cases;
};

}} // clever::ast

#endif // CLEVER_AST_H
