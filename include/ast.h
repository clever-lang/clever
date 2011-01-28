/*
 * Clever programming language
 * Copyright (c) 2011 Clever Team
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
 *
 * $Id$
 */

#ifndef CLEVER_AST_H
#define CLEVER_AST_H

#include <iostream>
#include <vector>
#include "value.h"
#include "cstring.h"
#include "refcounted.h"
#include "compiler.h"
#include "astvisitor.h"

namespace clever {

class Opcode;

} // clever

namespace clever { namespace ast {

class Node;

typedef std::vector<Node*> NodeList;

/**
 * Operators (logical and binary)
 */
enum {
	MINUS,
	PLUS,
	MULT,
	DIV,
	MOD,
	OR,
	XOR,
	AND,
	GREATER,
	GREATER_EQUAL,
	LESS,
	LESS_EQUAL,
	EQUAL,
	NOT_EQUAL
};

class NO_INIT_VTABLE Node : public RefCounted {
public:
	Node()
		: RefCounted(0), m_optimized(false) { }

	virtual ~Node() { }

	/**
	 * Adds a new child node
	 */
	void add(Node* node) throw() {
		node->addRef();
		m_nodes.push_back(node);
	}
	/**
	 * Calls delRef() for each child node
	 */
	void clearNodes() const throw() {
		NodeList::const_iterator it = m_nodes.begin(), end = m_nodes.end();

		while (it != end) {
			(*it)->delRef();
			++it;
		}
	}
	/**
	 * Checks if the node has child
	 */
	bool hasNodes() const throw() { return m_nodes.size() != 0; }
	/**
	 * Returns the node vector
	 */
	NodeList& getNodes() throw() { return m_nodes; }
	/**
	 * Indicates if the node is optimized
	 */
	bool isOptimized() const throw() { return m_optimized; }
	/**
	 * Change the node optimize status
	 */
	void set_optimized(bool value) throw() { m_optimized = value; }
	/**
	 * Method for getting the value representation
	 */
	virtual Value* get_value() const throw() { return NULL; }
	/**
	 * Method for generating the expression IR
	 */
	virtual void accept(ASTVisitor& visitor) throw() { }
	virtual void set_expr(Node* expr) throw() { }
	virtual void set_block(Node* expr) throw() { }
protected:
	NodeList m_nodes;
private:
	bool m_optimized;

	DISALLOW_COPY_AND_ASSIGN(Node);
};

class TopNode : public Node {
public:
	TopNode() { }

	~TopNode() { }
};

class Literal : public Node {
public:
	Literal() { }
	virtual ~Literal() { }

	bool isLiteral() const { return true; }
	virtual bool hasValue() const { return true; }
	virtual Value* get_value() const throw() = 0;
private:
	DISALLOW_COPY_AND_ASSIGN(Literal);
};

class NumberLiteral : public Literal {
public:
	explicit NumberLiteral(int64_t val) {
		m_value = new Value(val);
	}

	explicit NumberLiteral(double val) {
		m_value = new Value(val);
	}

	~NumberLiteral() {
		m_value->delRef();
	}

	Value* get_value() const throw() { return m_value; };
private:
	Value* m_value;

	DISALLOW_COPY_AND_ASSIGN(NumberLiteral);
};

class BinaryNode : public Node {
public:
	BinaryNode(int op, Node* lhs, Node* rhs)
		: m_op(op), m_lhs(lhs), m_rhs(rhs), m_result(NULL), m_assign(false) {
		m_lhs->addRef();
		m_rhs->addRef();
	}
	BinaryNode(int op, Node* lhs, Node* rhs, bool assign)
		: m_op(op), m_lhs(lhs), m_rhs(rhs), m_result(NULL), m_assign(assign) {
		m_lhs->addRef();
		m_rhs->addRef();
	}

	BinaryNode(int op, Node* rhs)
		: m_op(op), m_lhs(NULL), m_rhs(rhs), m_result(NULL), m_assign(false) {
		m_lhs = new NumberLiteral(int64_t(0));
		m_lhs->addRef();
		m_rhs->addRef();
	}

	~BinaryNode() {
		if (isOptimized()) {
			m_result->delRef();
		}
		if (m_lhs) {
			m_lhs->delRef();
		}
		if (m_rhs) {
			m_rhs->delRef();
		}
	}

	bool hasValue() const { return true; }

	bool isAssigned() const { return m_assign; }

	Node* get_lhs() const {
		return m_lhs;
	}

	Node* get_rhs() const {
		return m_rhs;
	}

	int get_op() const {
		return m_op;
	}

	Value* get_value() const throw() {
		return m_result;
	}
	void set_result(Value* value) {
		m_result = value;
	}

	void accept(ASTVisitor& visitor) throw() {
		m_lhs->accept(visitor);
		m_rhs->accept(visitor);

		visitor.visit(this);
	}
private:
	int m_op;
	Node* m_lhs;
	Node* m_rhs;
	Value* m_result;
	bool m_assign;

	DISALLOW_COPY_AND_ASSIGN(BinaryNode);
};

class VariableDecl : public Node {
public:
	VariableDecl(Node* type, Node* variable)
		: Node(), m_type(type), m_variable(variable), m_initial_value(NULL) {
		m_type->addRef();
		m_variable->addRef();
	}

	VariableDecl(Node* type, Node* variable, Node* rhs)
		: Node(), m_type(type), m_variable(variable), m_initial_value(rhs) {
		m_type->addRef();
		m_variable->addRef();
		m_initial_value->addRef();
	}

	~VariableDecl() {
		m_type->delRef();
		m_variable->delRef();

		if (m_initial_value) {
			m_initial_value->delRef();
		}
	}

	Node* get_variable() const {
		return m_variable;
	}

	Node* get_initial_value() const {
		return m_initial_value;
	}

	Node* get_type() const {
		return m_type;
	}

	void accept(ASTVisitor& visitor) throw() {
		if (m_initial_value) {
			m_initial_value->accept(visitor);
		}
		visitor.visit(this);
	}
private:
	Node* m_type;
	Node* m_variable;
	Node* m_initial_value;

	DISALLOW_COPY_AND_ASSIGN(VariableDecl);
};

class Identifier : public Node {
public:
	explicit Identifier(const CString* name) {
		m_value = new Value();
		m_value->set_name(name);
		m_name = name;
	}

	~Identifier() {
		m_value->delRef();
	}

	bool hasValue() const { return true; }
	Value* get_value() const throw() { return m_value; }
	const CString* get_name() const { return m_name; }
private:
	Value* m_value;
	const CString* m_name;

	DISALLOW_COPY_AND_ASSIGN(Identifier);
};

class StringLiteral : public Literal {
public:
	explicit StringLiteral(const CString* name) {
		m_value = new Value(name);
	}

	~StringLiteral() {
		m_value->delRef();
	}

	Value* get_value() const throw() { return m_value; };
private:
	Value* m_value;

	DISALLOW_COPY_AND_ASSIGN(StringLiteral);
};

class TypeCreation : public Node {
public:
	TypeCreation(Node* type, Node* arguments)
		: m_type(type), m_arguments(arguments) {
		m_type->addRef();
		m_arguments->addRef();
	}

	~TypeCreation() {
		m_type->delRef();
		m_arguments->delRef();
	}
private:
	Node* m_type;
	Node* m_arguments;

	DISALLOW_COPY_AND_ASSIGN(TypeCreation);
};

class BlockNode : public Node {
public:
	BlockNode() { }

	~BlockNode() {
		clearNodes();
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(BlockNode);
};

class PreIncrement : public Node {
public:
	PreIncrement(Node* expr)
		: m_expr(expr) {
		m_expr->addRef();
		m_result = new Value();
	}

	~PreIncrement() {
		m_expr->delRef();
	}

	Value* get_value() const throw() {
		return m_result;
	}

	Node* get_expr() const {
		return m_expr;
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Node* m_expr;
	Value* m_result;

	DISALLOW_COPY_AND_ASSIGN(PreIncrement);
};

class PosIncrement : public Node {
public:
	PosIncrement(Node* expr)
		: m_expr(expr) {
		m_expr->addRef();
		m_result = new Value();
	}

	~PosIncrement() {
		m_expr->delRef();
	}

	Value* get_value() const throw() {
		return m_result;
	}

	Node* get_expr() const {
		return m_expr;
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Node* m_expr;
	Value* m_result;

	DISALLOW_COPY_AND_ASSIGN(PosIncrement);
};

class PreDecrement : public Node {
public:
	PreDecrement(Node* expr)
		: m_expr(expr) {
		m_expr->addRef();
		m_result = new Value();
	}

	~PreDecrement() {
		m_expr->delRef();
	}

	Node* get_expr() const {
		return m_expr;
	}

	Value* get_value() const throw() {
		return m_result;
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Node* m_expr;
	Value* m_result;

	DISALLOW_COPY_AND_ASSIGN(PreDecrement);
};

class PosDecrement : public Node {
public:
	PosDecrement(Node* expr)
		: m_expr(expr) {
		m_expr->addRef();
		m_result = new Value();
	}

	~PosDecrement() {
		m_expr->delRef();
	}

	Value* get_value() const throw() {
		return m_result;
	}

	Node* get_expr() const {
		return m_expr;
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Node* m_expr;
	Value* m_result;

	DISALLOW_COPY_AND_ASSIGN(PosDecrement);
};

class IfNode : public Node {
public:
	IfNode(Node* condition, Node* block)
		: m_condition(condition), m_block(block), m_else(NULL) {
		m_condition->addRef();
		if (m_block) {
			m_block->addRef();
		}
	}

	~IfNode() {
		m_condition->delRef();
		if (m_block) {
			m_block->delRef();
		}
		if (m_else) {
			m_else->delRef();
		}
		clearNodes();
	}

	bool hasBlock() throw() { return m_block != NULL; }
	bool hasElseBlock() throw() { return m_else != NULL; }
	bool hasElseIf() throw() { return m_nodes.size() != 0; }

	Node* get_block() throw() { return m_block; }
	Node* get_condition() throw() { return m_condition; }

	Node* get_else() throw() { return m_else; }
	void set_else(Node* expr) {
		if (expr) {
			m_else = expr;
			m_else->addRef();
		}
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Node* m_condition;
	Node* m_block;
	Node* m_else;

	DISALLOW_COPY_AND_ASSIGN(IfNode);
};

class ElseIfNode : public Node {
public:
	ElseIfNode(Node* condition, Node* block)
		: m_condition(condition), m_block(block) {
		m_condition->addRef();
		if (m_block) {
			m_block->addRef();
		}
	}

	~ElseIfNode() {
		m_condition->delRef();
		if (m_block) {
			m_block->delRef();
		}
	}

	bool hasBlock() throw() { return m_block != NULL; }

	Node* get_condition() throw() { return m_condition; }
	Node* get_block() throw() { return m_block; }
private:
	Node* m_condition;
	Node* m_block;

	DISALLOW_COPY_AND_ASSIGN(ElseIfNode);
};

class WhileNode : public Node {
public:
	WhileNode(Node* condition, Node* block)
		: m_condition(condition), m_block(block) {
		m_condition->addRef();

		if (m_block) {
			m_block->addRef();
		}
	}

	~WhileNode() {
		m_condition->delRef();

		if (m_block) {
			m_block->delRef();
		}
	}

	bool hasBlock() throw() { return m_block != NULL; }

	Node* get_condition() throw() { return m_condition; }
	Node* get_block() throw() { return m_block; }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Node* m_condition;
	Node* m_block;

	DISALLOW_COPY_AND_ASSIGN(WhileNode);
};

class LogicNode : public Node {
public:
	LogicNode(int op, Node* lhs, Node* rhs)
		: m_op(op), m_lhs(lhs), m_rhs(rhs), m_result(NULL) {
		m_lhs->addRef();
		m_rhs->addRef();
	}

	~LogicNode() {
		if (isOptimized()) {
			m_result->delRef();
		}
		if (m_lhs) {
			m_lhs->delRef();
		}
		if (m_rhs) {
			m_rhs->delRef();
		}
	}

	int get_op() const { return m_op; }
	Node* get_lhs() const { return m_lhs; }
	Node* get_rhs() const { return m_rhs; }

	void set_result(Value* value) { m_result = value; }

	Value* get_value() const throw() { return m_result; }

	void accept(ASTVisitor& visitor) throw() {
		m_lhs->accept(visitor);
		m_rhs->accept(visitor);

		visitor.visit(this);
	}
private:
	int m_op;
	Node* m_lhs;
	Node* m_rhs;
	Value* m_result;

	DISALLOW_COPY_AND_ASSIGN(LogicNode);
};

class BreakNode : public Node {
public:
	BreakNode() { }

	~BreakNode() { }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(BreakNode);
};

class ArgumentList : public Node {
public:
	ArgumentList() { }

	~ArgumentList() {
		clearNodes();
	}
private:
	DISALLOW_COPY_AND_ASSIGN(ArgumentList);
};

class FuncDeclaration : public Node {
public:
	FuncDeclaration(Node* name, Node* type, Node* args, Node* block)
		: m_name(name), m_type(type), m_args(args), m_block(block) {
		m_name->addRef();
		m_type->addRef();
		if (m_args) {
			m_args->addRef();
		}
		if (m_block) {
			m_block->addRef();
		}
	}

	~FuncDeclaration() {
		m_name->delRef();
		m_type->delRef();
		if (m_args) {
			m_args->delRef();
		}
		if (m_block) {
			m_block->delRef();
		}
	}

	Node* get_name() const throw() { return m_name; }
	Node* get_type() const throw() { return m_type; }
	Node* get_args() const throw() { return m_args; }
	Node* get_block() const throw() { return m_block; }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Node* m_name;
	Node* m_type;
	Node* m_args;
	Node* m_block;
};

class FunctionCall : public Node {
public:
	FunctionCall(Node* name)
		: m_name(name), m_args(NULL) {
		m_name->addRef();
		m_result = new Value;
	}
	FunctionCall(Node* name, Node* args)
		: m_name(name), m_args(args) {
		m_name->addRef();
		m_args->addRef();
		m_result = new Value;
	}

	~FunctionCall() {
		m_name->delRef();
		if (m_args) {
			m_args->delRef();
		}
	}

	Value* get_value() const throw() { return m_result; }

	Value* get_func() const throw() { return m_name->get_value(); }

	Node* get_args() throw() { return m_args; }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Node* m_name;
	Node* m_args;
	Value* m_result;

	DISALLOW_COPY_AND_ASSIGN(FunctionCall);
};

class MethodCall : public Node {
public:
	MethodCall(Node* var, Node* method)
		: m_var(var), m_method(method), m_args(NULL) {
		m_var->addRef();
		m_method->addRef();
		m_result = new Value;
	}

	MethodCall(Node* var, Node* method, Node* args)
		: m_var(var), m_method(method), m_args(args) {
		m_var->addRef();
		m_method->addRef();
		m_args->addRef();
		m_result = new Value;
	}

	~MethodCall() {
		m_var->delRef();
		m_method->delRef();
		if (m_args) {
			m_args->delRef();
		}
	}

	Node* get_variable() const throw() { return m_var; }
	Node* get_method() const throw() { return m_method; }
	Node* get_args() const throw() { return m_args; }

	Value* get_value() const throw() { return m_result; }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Node* m_var;
	Node* m_method;
	Node* m_args;
	Value* m_result;

	DISALLOW_COPY_AND_ASSIGN(MethodCall);
};

class Assignment : public Node {
public:
	Assignment(Node* lhs, Node *rhs)
		: m_lhs(lhs), m_rhs(rhs) {
		m_lhs->addRef();
		m_rhs->addRef();
	}
	~Assignment() {
		m_lhs->delRef();
		m_rhs->delRef();
	}

	Node* get_lhs() const throw() { return m_lhs; }
	Node* get_rhs() const throw() { return m_rhs; }

	void accept(ASTVisitor& visitor) throw() {
		m_rhs->accept(visitor);
		visitor.visit(this);
	}
private:
	Node* m_lhs;
	Node* m_rhs;

	DISALLOW_COPY_AND_ASSIGN(Assignment);
};

class Import : public Node {
public:
	Import(Node* package)
		: m_package(package), m_module(NULL) {
		m_package->addRef();
	}
	Import(Node* package, Node* module)
		: m_package(package), m_module(module) {
		m_package->addRef();
		m_module->addRef();
	}
	~Import() {
		m_package->delRef();
		if (m_module) {
			m_module->delRef();
		}
	}

	Node* get_package() throw() {
		return m_package;
	}

	Node* get_module() throw() {
		return m_module;
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Node* m_package;
	Node* m_module;

	DISALLOW_COPY_AND_ASSIGN(Import);
};

class ReturnStmt : public Node {
public:
	ReturnStmt()
		: m_expr(NULL) { }

	explicit ReturnStmt(Node* expr)
		: m_expr(expr) {
		m_expr->addRef();
	}

	~ReturnStmt() {
		if (m_expr) {
			m_expr->delRef();
		}
	}

	Node* get_expr() const throw() { return m_expr; }

	void accept(ASTVisitor& visitor) throw() {
		m_expr->accept(visitor);

		visitor.visit(this);
	}
private:
	Node* m_expr;

	DISALLOW_COPY_AND_ASSIGN(ReturnStmt);
};

}} // clever::ast

#endif // CLEVER_AST_H
