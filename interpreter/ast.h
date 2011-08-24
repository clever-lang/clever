/**
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
 */

#ifndef CLEVER_AST_H
#define CLEVER_AST_H

#include <list>
#include <vector>
#include <set>
#include "compiler/value.h"
#include "compiler/refcounted.h"
#include "astvisitor.h"
#include "build/location.hh"

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
	 * Clear the AST tree
	 */
	void clear() throw() {
		clearNodes();
		m_nodes.resize(0);
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
	void setOptimized(bool value) throw() { m_optimized = value; }
	/**
	 * Method for getting the line where occurs the definition
	 */
	void setLocation(location& locate) throw() { m_location = locate; }
	const location& getLocation() const throw() { return m_location; }

	const std::string* getFileName() const throw() { return m_location.end.filename; }

	unsigned int getBeginLine() const throw() { return m_location.begin.line; }
	unsigned int getEndLine() const throw() { return m_location.end.line; }
	/**
	 * Method for getting the value representation
	 */
	virtual Value* getValue() const throw() { return NULL; }
	/**
	 * Method for generating the expression IR
	 */
	virtual void accept(ASTVisitor& visitor) throw() { }
	virtual void setExpr(ASTNode* expr) throw() { }
	virtual void setBlock(ASTNode* expr) throw() { }
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
	virtual Value* getValue() const throw() = 0;
private:
	DISALLOW_COPY_AND_ASSIGN(Literal);
};

class NumberLiteral : public Literal {
public:
	explicit NumberLiteral(int64_t val) {
		m_value = new Value(val);
		m_value->setTypePtr(CLEVER_TYPE("Int"));
	}

	explicit NumberLiteral(double val) {
		m_value = new Value(val);
		m_value->setTypePtr(CLEVER_TYPE("Double"));
	}

	explicit NumberLiteral(Value* value)
		: m_value(value) { }

	~NumberLiteral() {
		m_value->delRef();
	}

	Value* getValue() const throw() { return m_value; };
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

	Value* getValue() const throw() {
		return m_result;
	}

	ASTNode* getExpr() const {
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

	ASTNode* getLhs() const { return m_lhs; }
	ASTNode* getRhs() const { return m_rhs; }

	int getOp() const { return m_op; }

	Value* getValue() const throw() { return m_result; }

	void setResult(Value* value) { m_result = value; }

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

	ASTNode* getVariable() const {
		return m_variable;
	}

	ASTNode* getInitialValue() const {
		return m_initial_value;
	}

	ASTNode* getType() const {
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
	
	~AttributeDeclaration() {
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
		m_value->setName(name);
		m_name = name;
	}

	~Identifier() {
		m_value->delRef();
	}

	bool hasValue() const { return true; }
	
	Value* getValue() const throw() { return m_value; }
	
	void setValue(Value* value) throw() { m_value = value; }
	
	const CString* getName() const { return m_name; }
	
	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	Value* m_value;
	const CString* m_name;

	DISALLOW_COPY_AND_ASSIGN(Identifier);
};

class StringLiteral : public Literal {
public:
	explicit StringLiteral(const CString* name) {
		m_value = new Value(name);
		m_value->setTypePtr(CLEVER_TYPE("String"));
	}

	~StringLiteral() {
		m_value->delRef();
	}

	Value* getValue() const throw() { return m_value; };
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

	ASTNode* getBlock() throw() { return m_block; }
	ASTNode* getCondition() throw() { return m_condition; }

	ASTNode* getElse() throw() { return m_else; }
	void setElse(ASTNode* expr) {
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

	ASTNode* getCondition() throw() { return m_condition; }
	ASTNode* getBlock() throw() { return m_block; }
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

	ASTNode* getCondition() throw() { return m_condition; }
	ASTNode* getBlock() throw() { return m_block; }

	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
private:
	ASTNode* m_condition;
	ASTNode* m_block;

	DISALLOW_COPY_AND_ASSIGN(WhileExpr);
};

class ForExpr : public ASTNode {
public:
	ForExpr(ASTNode* var_decl, ASTNode* ident, ASTNode* block)
		: m_var_decl(var_decl), m_ident(ident), m_condition(NULL), m_increment(NULL), m_block(block) {
		m_var_decl->addRef();
		m_ident->addRef();
		
		if (m_block) {
			m_block->addRef();
		}
	}
	
	ForExpr(ASTNode* var_decl, ASTNode* condition, ASTNode* increment, ASTNode* block) 
		: m_var_decl(var_decl), m_ident(NULL), m_condition(condition), m_increment(increment), m_block(block) {
		if (m_var_decl) {
			m_var_decl->addRef();
		}
		
		if (m_condition) {
			m_condition->addRef();
		}
		
		if (m_increment) {
			m_increment->addRef();
		}
		
		if (m_block) {
			m_block->addRef();
		}
	}
	
	~ForExpr() {
		if (m_var_decl) {
			m_var_decl->delRef();
		}
		
		if (m_ident) {
			m_ident->delRef();
		}
		
		if (m_condition) {
			m_condition->delRef();
		}
		
		if (m_increment) {
			m_increment->delRef();
		}
		
		if (m_block) {
			m_block->delRef();
		}
	}
	
	bool hasBlock() const { return m_block != NULL; }
	bool isIteratorMode() const { return m_ident != NULL; }
	ASTNode* getVarDecl() throw() { return m_var_decl; }
	ASTNode* getIdentifier() throw() { return m_ident; }
	ASTNode* getCondition() throw() { return m_condition; }
	ASTNode* getIncrement() throw() { return m_increment; }
	ASTNode* getBlock() throw() { return m_block; }
	
	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
	
private:
	ASTNode* m_var_decl;
	ASTNode* m_ident;
	ASTNode* m_condition;
	ASTNode* m_increment;
	ASTNode* m_block;

	DISALLOW_COPY_AND_ASSIGN(ForExpr);
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

	ArgumentDecls& getArgs() throw() { return m_args; }
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

	const CString* const getName() const throw() { return m_name->getValue()->getName(); }
	ASTNode* getArgs() const throw() { return m_args; }
	ASTNode* getReturn() const throw() { return m_return; }
	Value* getReturnValue() const throw() { return m_return ? m_return->getValue() : NULL; }

	ASTNode* getBlock() const throw() { return m_block; }
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

	~MethodDeclaration() {
		m_modifier->delRef();
	}

        ASTNode* getModifier() { return m_modifier; }
protected:
        ASTNode* m_modifier;
};

class FunctionCall : public ASTNode {
public:
	FunctionCall(ASTNode* name)
		: m_name(name), m_args(NULL) {
		m_name->addRef();
		m_result = new CallableValue;
	}
	FunctionCall(ASTNode* name, ASTNode* args)
		: m_name(name), m_args(args) {
		m_name->addRef();
		m_args->addRef();
		m_result = new CallableValue;
	}

	~FunctionCall() {
		m_name->delRef();
		if (m_args) {
			m_args->delRef();
		}
	}

	Value* getValue() const throw() { return m_result; }

	const CString* const getFuncName() const throw() { return m_name->getValue()->getName(); }

	ASTNode* getArgs() throw() { return m_args; }

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
		m_result = new CallableValue;
	}

	MethodCall(ASTNode* var, ASTNode* method, ASTNode* args)
		: m_var(var), m_method(method), m_args(args) {
		m_var->addRef();
		m_method->addRef();
		m_args->addRef();
		m_result = new CallableValue;
	}

	~MethodCall() {
		m_var->delRef();
		m_method->delRef();
		if (m_args) {
			m_args->delRef();
		}
	}

	ASTNode* getVariable() const throw() { return m_var; }
	const CString* const getMethodName() const throw() { return m_method->getValue()->getName(); }
	ASTNode* getArgs() const throw() { return m_args; }

	Value* getValue() const throw() { return m_result; }

	void accept(ASTVisitor& visitor) throw() {
		m_var->accept(visitor);
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
		getRhs()->accept(visitor);
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

	const CString* const getPackageName() throw() {
		return m_package->getValue()->getName();
	}

	const CString* const getModuleName() throw() {
		return m_module ? m_module->getValue()->getName() : NULL;
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

	ASTNode* getExpr() const throw() { return m_expr; }
	
	Value* getExprValue() const throw() {
		return m_expr ? m_expr->getValue() : NULL;
	}

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
	IntegralValue(int value) : m_int_value(value) { }

	~IntegralValue() {
	}

	Value* getValue() const throw() { return m_value; }
	
	int getInt() throw() { return m_int_value; }
private:
	Value* m_value;
	int m_int_value;

	DISALLOW_COPY_AND_ASSIGN(IntegralValue);
};

class ClassStmtList : public ASTNode {
public:
	ClassStmtList() { }

	~ClassStmtList() {
		std::list<MethodDeclaration*>::const_iterator
			it_method = m_methods_decl.begin(), it_method_end = m_methods_decl.end();
		std::list<AttributeDeclaration*>::const_iterator
			it_attrib = m_attrib_decl.begin(), it_attrib_end = m_attrib_decl.end();

		while (it_method != it_method_end) {
			(*it_method)->delRef();
			++it_method;
		}
		while (it_attrib != it_attrib_end) {
			(*it_attrib)->delRef();
			++it_attrib;
		}
	}

	void addMethod(ASTNode* method) throw() {
		MethodDeclaration* m = static_cast<MethodDeclaration*>(method);
		m_methods_decl.push_back(m);
		m->addRef();
	}
	
	void addAttribute(ASTNode* attribute) throw() {
		AttributeDeclaration* attr = static_cast<AttributeDeclaration*>(attribute);
		m_attrib_decl.push_back(attr);
		attr->addRef();
	}

	std::list<MethodDeclaration*>& getMethodsDecl() throw() { 
		return m_methods_decl;
	}

	std::list<AttributeDeclaration*>& getAttribsDecl() throw() { 
		return m_attrib_decl;
	}
private:
	std::list<MethodDeclaration*> m_methods_decl;
	std::list<AttributeDeclaration*> m_attrib_decl;

	DISALLOW_COPY_AND_ASSIGN(ClassStmtList);
};

class ClassDeclaration : public ASTNode {
public:	
	
	class DeclarationError {
	public:
		enum error_type { METHOD_DECLARATION, ATTRIBUTE_DECLARATION };

		DeclarationError() {}

		const std::string& getIdentifier() { return m_identifier; }
		const location& getLocation() { return m_location; }
		error_type getType() { return m_type; }

		void setIdentifier(const std::string& ident) { m_identifier = ident; }
		void setLocation(const location& loc) { m_location = loc; }
		void setErrorType(error_type type) { m_type = type; }

	private:
		std::string m_identifier;
		location m_location;
		error_type m_type;
	};

	ClassDeclaration(ASTNode* name, ASTNode* body)
		: m_name(name), m_body(body) {
		m_name->addRef();
		m_body->addRef();	
	}
		
	~ClassDeclaration() {
		m_name->delRef();
		m_body->delRef();
	}
	
	bool check(DeclarationError& error) {
		ClassStmtList* list = static_cast<ClassStmtList*>(m_body);
		std::list<AttributeDeclaration*>& attribs = list->getAttribsDecl();
		std::list<AttributeDeclaration*>::const_iterator it;

		std::set<std::string> s;

		for (it = attribs.begin(); it != attribs.end(); ++it) {
			const std::string& str = (*it)->getVariable()->getValue()->getName()->str();
			
			if (s.find(str) == s.end()) {
				s.insert(str);
			}
			else {
				error.setErrorType(DeclarationError::ATTRIBUTE_DECLARATION);
				error.setIdentifier(str);
				error.setLocation((*it)->getLocation());
				return false;
			}
		}
		
		s.clear();
		
		std::list<MethodDeclaration*>& methods = list->getMethodsDecl();
		std::list<MethodDeclaration*>::const_iterator it2;
		
		for (it2 = methods.begin(); it2 != methods.end(); ++it2) {
			const std::string& str = (*it2)->getName()->str();
			
			if (s.find(str) == s.end()) {
				s.insert(str);
			}
			else {
				error.setErrorType(DeclarationError::METHOD_DECLARATION);
				error.setIdentifier(str);
				error.setLocation((*it2)->getLocation());
				return false;
			}
		}
		
		return true;
	}
	
	void accept(ASTVisitor& visitor) throw() {
		visitor.visit(this);
	}
	
	const CString* getClassName() const {
		return m_name->getValue()->getName();
	}
	
private:
	ASTNode* m_name;
	ASTNode* m_body;
	DISALLOW_COPY_AND_ASSIGN(ClassDeclaration);
};

}} // clever::ast

#endif // CLEVER_AST_H
