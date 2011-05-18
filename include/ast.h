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

#include <vector>
#include <iostream> //debug
#include "value.h"
#include "refcounted.h"
#include "astvisitor.h"
#include "location.hh"

namespace clever {

class Opcode;
class CString;

} // clever

namespace clever { namespace ast {

class ASTNode;

typedef std::vector<ASTNode*> NodeList;
typedef std::pair<ASTNode*, ASTNode*> ArgumentDeclPair;
typedef std::vector<ArgumentDeclPair> ArgumentDecls;

/**
 * Operators (logical and binary)
 */
enum {
	ASSIGN,
	MINUS,
	PLUS,
	MULT,
	DIV,
	MOD,
	OR,
	AND,
	BW_OR,
	BW_AND,
	XOR,
	GREATER,
	GREATER_EQUAL,
	LESS,
	LESS_EQUAL,
	EQUAL,
	NOT_EQUAL
};

/**
 * AST node representation
 */
class NO_INIT_VTABLE ASTNode : public RefCounted {
public:
	ASTNode()
		: RefCounted(0), m_optimized(false) { }

	virtual ~ASTNode() { }

	/**
	 * Adds a new child node
	 */
	void add(ASTNode* node) throw() {
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
	 * Method for getting the line where occurs the definition
	 */
	void set_location(location& locate) throw() { m_location = locate; }
	const location& get_location() const throw() { return m_location; }

	const std::string* getFileName() const throw() { return m_location.end.filename; }

	unsigned int getBeginLine() const throw() { return m_location.begin.line; }
	unsigned int getEndLine() const throw() { return m_location.end.line; }
	/**
	 * Method for getting the value representation
	 */
	virtual Value* get_value() const throw() { return NULL; }
	/**
	 * Method for generating the expression IR
	 */
	virtual void accept(ASTVisitor& visitor) throw() { }
	virtual void set_expr(ASTNode* expr) throw() { }
	virtual void set_block(ASTNode* expr) throw() { }
protected:
	NodeList m_nodes;
	location m_location;
private:
	bool m_optimized;

	DISALLOW_COPY_AND_ASSIGN(ASTNode);
};

class Literal : public ASTNode {
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

	explicit NumberLiteral(Value* value)
		: m_value(value) { }

	~NumberLiteral() {
		m_value->delRef();
	}

	Value* get_value() const throw() { return m_value; };
private:
	Value* m_value;

	DISALLOW_COPY_AND_ASSIGN(NumberLiteral);
};

class NO_INIT_VTABLE UnaryExpr : public ASTNode {
public:
	UnaryExpr(ASTNode* expr)
		: m_expr(expr) {
		m_expr->addRef();
		m_result = new Value();
	}

	~UnaryExpr() {
		m_expr->delRef();
	}

	Value* get_value() const throw() {
		return m_result;
	}

	ASTNode* get_expr() const {
		return m_expr;
	}

	virtual void accept(ASTVisitor& visitor) throw() { }
private:
	ASTNode* m_expr;
	Value* m_result;

	DISALLOW_COPY_AND_ASSIGN(UnaryExpr);
};

/* TODO: turn this into an "abstract" class if possible */
class BinaryExpr : public ASTNode {
public:
	BinaryExpr(int op, ASTNode* lhs, ASTNode* rhs)
		: m_op(op), m_lhs(lhs), m_rhs(rhs), m_result(NULL), m_assign(false) {
		m_lhs->addRef();
		m_rhs->addRef();
	}
	BinaryExpr(int op, ASTNode* lhs, ASTNode* rhs, bool assign)
		: m_op(op), m_lhs(lhs), m_rhs(rhs), m_result(NULL), m_assign(assign) {
		m_lhs->addRef();
		m_rhs->addRef();
	}

	BinaryExpr(int op, ASTNode* rhs)
		: m_op(op), m_lhs(NULL), m_rhs(rhs), m_result(NULL), m_assign(false) {
		m_lhs = new NumberLiteral(int64_t(0));
		m_lhs->addRef();
		m_rhs->addRef();
	}

	virtual ~BinaryExpr() {
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

	ASTNode* get_lhs() const { return m_lhs; }
	ASTNode* get_rhs() const { return m_rhs; }

	int get_op() const { return m_op; }

	Value* get_value() const throw() { return m_result; }

	void set_result(Value* value) { m_result = value; }

	virtual void accept(ASTVisitor& visitor) throw() {
		m_lhs->accept(visitor);
		m_rhs->accept(visitor);

		visitor.visit(this);
	}
private:
	int m_op;
	ASTNode* m_lhs;
	ASTNode* m_rhs;
	Value* m_result;
	bool m_assign;

	DISALLOW_COPY_AND_ASSIGN(BinaryExpr);
};

class VariableDecl : public ASTNode {
public:
	VariableDecl(ASTNode* type, ASTNode* variable)
		: m_type(type), m_variable(variable), m_initial_value(NULL) {
		m_type->addRef();
		m_variable->addRef();
	}

	VariableDecl(ASTNode* type, ASTNode* variable, ASTNode* rhs)
		: m_type(type), m_variable(variable), m_initial_value(rhs) {
		m_type->addRef();
		m_variable->addRef();
		m_initial_value->addRef();
	}

	virtual ~VariableDecl() {
		m_type->delRef();
		m_variable->delRef();

		if (m_initial_value) {
			m_initial_value->delRef();
		}
	}

	ASTNode* get_variable() const {
		return m_variable;
	}

	ASTNode* get_initial_value() const {
		return m_initial_value;
	}

	ASTNode* get_type() const {
		return m_type;
	}

	void accept(ASTVisitor& visitor) throw() {
		if (m_initial_value) {
			m_initial_value->accept(visitor);
		}
		visitor.visit(this);
	}
private:
	ASTNode* m_type;
	ASTNode* m_variable;
	ASTNode* m_initial_value;

	DISALLOW_COPY_AND_ASSIGN(VariableDecl);
};

class AttributeDeclaration : public VariableDecl {
public:
	AttributeDeclaration(ASTNode* modifier, ASTNode* type, ASTNode* variable) 
		: VariableDecl(type, variable), m_modifier(modifier) {
		m_modifier->addRef();
	}
	
	virtual ~AttributeDeclaration() {
		m_modifier->delRef();
	}
private:
	ASTNode* m_modifier;
	DISALLOW_COPY_AND_ASSIGN(AttributeDeclaration);
};

class Identifier : public ASTNode {
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

class TypeCreation : public ASTNode {
public:
	TypeCreation(ASTNode* type, ASTNode* arguments)
		: m_type(type), m_arguments(arguments) {
		m_type->addRef();
		m_arguments->addRef();
	}

	~TypeCreation() {
		m_type->delRef();
		m_arguments->delRef();
	}
private:
	ASTNode* m_type;
	ASTNode* m_arguments;

	DISALLOW_COPY_AND_ASSIGN(TypeCreation);
};

class BlockNode : public ASTNode {
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

class PreIncrement : public UnaryExpr {
public:
	PreIncrement(ASTNode* expr)
		: UnaryExpr(expr) {
	}

	~PreIncrement() {
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:

	DISALLOW_COPY_AND_ASSIGN(PreIncrement);
};

class PosIncrement : public UnaryExpr {
public:
	PosIncrement(ASTNode* expr)
		: UnaryExpr(expr) {
	}

	~PosIncrement() {
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(PosIncrement);
};

class PreDecrement : public UnaryExpr {
public:
	PreDecrement(ASTNode* expr)
		: UnaryExpr(expr) {
	}

	~PreDecrement() {
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(PreDecrement);
};

class PosDecrement : public UnaryExpr {
public:
	PosDecrement(ASTNode* expr)
		: UnaryExpr(expr) {
	}

	~PosDecrement() {
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:

	DISALLOW_COPY_AND_ASSIGN(PosDecrement);
};

class IfExpr : public ASTNode {
public:
	IfExpr(ASTNode* condition, ASTNode* block)
		: m_condition(condition), m_block(block), m_else(NULL) {
		m_condition->addRef();
		if (m_block) {
			m_block->addRef();
		}
	}

	~IfExpr() {
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

	ASTNode* get_block() throw() { return m_block; }
	ASTNode* get_condition() throw() { return m_condition; }

	ASTNode* get_else() throw() { return m_else; }
	void set_else(ASTNode* expr) {
		if (expr) {
			m_else = expr;
			m_else->addRef();
		}
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	ASTNode* m_condition;
	ASTNode* m_block;
	ASTNode* m_else;

	DISALLOW_COPY_AND_ASSIGN(IfExpr);
};

class ElseIfExpr : public ASTNode {
public:
	ElseIfExpr(ASTNode* condition, ASTNode* block)
		: m_condition(condition), m_block(block) {
		m_condition->addRef();
		if (m_block) {
			m_block->addRef();
		}
	}

	~ElseIfExpr() {
		m_condition->delRef();
		if (m_block) {
			m_block->delRef();
		}
	}

	bool hasBlock() throw() { return m_block != NULL; }

	ASTNode* get_condition() throw() { return m_condition; }
	ASTNode* get_block() throw() { return m_block; }
private:
	ASTNode* m_condition;
	ASTNode* m_block;

	DISALLOW_COPY_AND_ASSIGN(ElseIfExpr);
};

class WhileExpr : public ASTNode {
public:
	WhileExpr(ASTNode* condition, ASTNode* block)
		: m_condition(condition), m_block(block) {
		m_condition->addRef();

		if (m_block) {
			m_block->addRef();
		}
	}

	~WhileExpr() {
		m_condition->delRef();

		if (m_block) {
			m_block->delRef();
		}
	}

	bool hasBlock() throw() { return m_block != NULL; }

	ASTNode* get_condition() throw() { return m_condition; }
	ASTNode* get_block() throw() { return m_block; }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	ASTNode* m_condition;
	ASTNode* m_block;

	DISALLOW_COPY_AND_ASSIGN(WhileExpr);
};

class LogicExpr : public BinaryExpr {
public:
	LogicExpr(int op, ASTNode* lhs, ASTNode* rhs)
		: BinaryExpr(op, lhs, rhs) {
	}

	~LogicExpr() { }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(LogicExpr);
};

class BreakNode : public ASTNode {
public:
	BreakNode() { }

	~BreakNode() { }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(BreakNode);
};

class ArgumentList : public ASTNode {
public:
	ArgumentList() { }

	~ArgumentList() {
		clearNodes();
	}
private:
	DISALLOW_COPY_AND_ASSIGN(ArgumentList);
};

class ArgumentDeclList : public ASTNode {
public:
	ArgumentDeclList() { }

	~ArgumentDeclList() {
		ArgumentDecls::const_iterator it = m_args.begin(), end = m_args.end();

		while (it != end) {
			it->first->delRef();
			it->second->delRef();
			++it;
		}
	}

	void addArg(ASTNode* type, ASTNode* name) throw() {
		m_args.push_back(ArgumentDeclPair(type, name));
		type->addRef();
		name->addRef();
	}

	ArgumentDecls& get_args() throw() { return m_args; }
private:
	ArgumentDecls m_args;

	DISALLOW_COPY_AND_ASSIGN(ArgumentDeclList);
};

class FuncDeclaration : public ASTNode {
public:
	FuncDeclaration(ASTNode* name, ASTNode* rtype, ASTNode* args, ASTNode* block)
		: m_name(name), m_return(rtype), m_args(args), m_block(block) {
		m_name->addRef();
		if (m_return) {
			m_return->addRef();
		}
		if (m_args) {
			m_args->addRef();
		}
		if (m_block) {
			m_block->addRef();
		}
	}

	virtual ~FuncDeclaration() {
		m_name->delRef();
		if (m_return) {
			m_return->delRef();
		}
		if (m_args) {
			m_args->delRef();
		}
		if (m_block) {
			m_block->delRef();
		}
	}

	ASTNode* get_name() const throw() { return m_name; }
	ASTNode* get_args() const throw() { return m_args; }
	ASTNode* get_return() const throw() { return m_return; }

	ASTNode* get_block() const throw() { return m_block; }
	bool hasBlock() const throw() { return m_block != NULL; }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
protected:
	ASTNode* m_name;
	ASTNode* m_return;
	ASTNode* m_args;
	ASTNode* m_block;
};

class MethodDeclaration: public FuncDeclaration {
public:
	MethodDeclaration(ASTNode* modifier, ASTNode* rtype, ASTNode* name,
                ASTNode* args, ASTNode* block)
		: FuncDeclaration(name, rtype, args, block), m_modifier(modifier) {
                    m_modifier->addRef();
	}

	virtual ~MethodDeclaration() {
		m_modifier->delRef();
	}

        ASTNode* get_modifier() { return m_modifier; }
protected:
        ASTNode* m_modifier;
};

class FunctionCall : public ASTNode {
public:
	FunctionCall(ASTNode* name)
		: m_name(name), m_args(NULL) {
		m_name->addRef();
		m_result = new Value;
	}
	FunctionCall(ASTNode* name, ASTNode* args)
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

	ASTNode* get_args() throw() { return m_args; }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	ASTNode* m_name;
	ASTNode* m_args;
	Value* m_result;

	DISALLOW_COPY_AND_ASSIGN(FunctionCall);
};

class MethodCall : public ASTNode {
public:
	MethodCall(ASTNode* var, ASTNode* method)
		: m_var(var), m_method(method), m_args(NULL) {
		m_var->addRef();
		m_method->addRef();
		m_result = new Value;
	}

	MethodCall(ASTNode* var, ASTNode* method, ASTNode* args)
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

	ASTNode* get_variable() const throw() { return m_var; }
	ASTNode* get_method() const throw() { return m_method; }
	ASTNode* get_args() const throw() { return m_args; }

	Value* get_value() const throw() { return m_result; }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	ASTNode* m_var;
	ASTNode* m_method;
	ASTNode* m_args;
	Value* m_result;

	DISALLOW_COPY_AND_ASSIGN(MethodCall);
};

class AssignExpr : public BinaryExpr {
public:
	AssignExpr(ASTNode* lhs, ASTNode* rhs)
		: BinaryExpr(ASSIGN, lhs, rhs) {
	}

	~AssignExpr() {
	}

	void accept(ASTVisitor& visitor) throw() {
		get_rhs()->accept(visitor);
		visitor.visit(this);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(AssignExpr);
};

class ImportStmt : public ASTNode {
public:
	ImportStmt(ASTNode* package)
		: m_package(package), m_module(NULL) {
		m_package->addRef();
	}
	ImportStmt(ASTNode* package, ASTNode* module)
		: m_package(package), m_module(module) {
		m_package->addRef();
		m_module->addRef();
	}
	~ImportStmt() {
		m_package->delRef();
		if (m_module) {
			m_module->delRef();
		}
	}

	ASTNode* get_package() throw() {
		return m_package;
	}

	ASTNode* get_module() throw() {
		return m_module;
	}

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	ASTNode* m_package;
	ASTNode* m_module;

	DISALLOW_COPY_AND_ASSIGN(ImportStmt);
};

class ReturnStmt : public ASTNode {
public:
	ReturnStmt()
		: m_expr(NULL) { }

	explicit ReturnStmt(ASTNode* expr)
		: m_expr(expr) {
		m_expr->addRef();
	}

	~ReturnStmt() {
		if (m_expr) {
			m_expr->delRef();
		}
	}

	ASTNode* get_expr() const throw() { return m_expr; }

	void accept(ASTVisitor& visitor) throw() {
		if (m_expr) {
			m_expr->accept(visitor);
		}
		visitor.visit(this);
	}
private:
	ASTNode* m_expr;

	DISALLOW_COPY_AND_ASSIGN(ReturnStmt);
};

class IntegralValue : public ASTNode {
public:
	IntegralValue(int value) : m_value(value) { }

	~IntegralValue() {
	}

	int get_value() throw() { return m_value; }
private:
	int m_value;

	DISALLOW_COPY_AND_ASSIGN(IntegralValue);
};

class ClassStmtList : public ASTNode {
public:
	ClassStmtList() { }

	~ClassStmtList() {
		{
			std::list<MethodDeclaration*>::iterator
	                    it = m_methods_decl.begin(), end = m_methods_decl.end();

			while (it != end) {
	                        (*it)->delRef();
	                        ++it;
			}
		}
		
		{
			std::list<AttributeDeclaration*>::iterator
	                    it = m_attrib_decl.begin(), end = m_attrib_decl.end();

			while (it != end) {
	                        (*it)->delRef();
	                        ++it;
			}
		}
	}

	void addMethod(ASTNode* method) throw() {
                MethodDeclaration* m = static_cast<MethodDeclaration*>(method);
		m_methods_decl.push_back(m);
                m->addRef();
		
                std::cout << "Method: " <<
			m->get_name()->get_value()->get_name()->str() << std::endl;
	}
	
	void addAttribute(ASTNode* attribute) throw() {
		AttributeDeclaration* attr = static_cast<AttributeDeclaration*>(attribute);
		m_attrib_decl.push_back(attr);
		attr->addRef();
		
		std::cout << "Attribute: " <<
			attr->get_variable()->get_value()->get_name()->str() << std::endl;
	}

	std::list<MethodDeclaration*>& get_methods_decl() throw() { 
                return m_methods_decl;
        }

	std::list<AttributeDeclaration*>& get_attrib_decl() throw() { 
                return m_attrib_decl;
        }
private:
	std::list<MethodDeclaration*> m_methods_decl;
	std::list<AttributeDeclaration*> m_attrib_decl;

	DISALLOW_COPY_AND_ASSIGN(ClassStmtList);
};

}} // clever::ast

#endif // CLEVER_AST_H
