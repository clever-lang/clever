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

#include <list>
#include <vector>
#include <set>
#include "compiler/value.h"
#include "compiler/refcounted.h"
#include "compiler/scope.h"
#include "interpreter/astvisitor.h"
#include "interpreter/asttransformer.h"
#include "interpreter/location.hh"

namespace clever {

class Opcode;
class CString;

} // clever

namespace clever { namespace ast {

class ASTNode;
class VariableDecl;
class ExtFuncDeclaration;

typedef std::vector<ASTNode*> NodeList;
typedef std::pair<Identifier*, Identifier*> ArgumentDeclPair;
typedef std::vector<ArgumentDeclPair> ArgumentDecls;
typedef std::vector<Identifier*> TemplateArgsVector;
typedef std::vector<VariableDecl*> VariableDecls;
typedef std::vector<ExtFuncDeclaration*> ExtFuncDecls;

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
	NOT_EQUAL,
	AUTO_EQUAL,
	NOT,
	BW_NOT,
	PRE_INC,
	POS_INC,
	PRE_DEC,
	POS_DEC,
	LSHIFT,
	RSHIFT
};

class NumberLiteral;
class StringLiteral;

/**
 * AST node representation
 */
class NO_INIT_VTABLE ASTNode : public RefCounted {
public:
	ASTNode()
		: RefCounted(0), m_nodes(NULL) {}

	virtual ~ASTNode() {}

	/**
	 * Adds a new child node
	 */
	void add(ASTNode* node) {
		CLEVER_ADDREF(node);
		m_nodes->push_back(node);
	}

	/**
	 *Adds a vector with new child nodes
	 */
	void add(NodeList* nodes){
		NodeList::iterator it = nodes->begin(), end = nodes->end();

		while (it != end) {
			CLEVER_ADDREF((*it));;
			m_nodes->push_back(*it);
			++it;
		}
	}

	/**
	 * Calls delRef() for each child node
	 */
	void clearNodes() const {
		NodeList::const_iterator it = m_nodes->begin(), end = m_nodes->end();

		while (it != end) {
			CLEVER_DELREF((*it));
			++it;
		}
	}
	/**
	 * Clear the AST tree
	 */
	void clear() {
		clearNodes();
		m_nodes->resize(0);
	}
	/**
	 * Checks if the node has child
	 */
	bool hasNodes() const { return m_nodes != NULL && m_nodes->size() != 0; }
	/**
	 * Returns the node vector
	 */
	NodeList& getNodes() { return *m_nodes; }
	/**
	 * Method for getting the line where occurs the definition
	 */
	void setLocation(location& locate) { m_location = locate; }
	const location& getLocation() const { return m_location; }

	const std::string* getFileName() const { return m_location.end.filename; }

	unsigned int getBeginLine() const { return m_location.begin.line; }
	unsigned int getEndLine() const { return m_location.end.line; }
	/**
	 * Method for getting the value representation
	 */
	virtual Value* getValue() const { return NULL; }
	/**
	 * Method for generating the expression IR
	 */
	virtual void acceptVisitor(ASTVisitor& visitor) { }
	virtual ASTNode* acceptTransformer(ASTTransformer& transformer) { return this; }

	virtual NumberLiteral* asNumberLiteral() { return NULL; }
	virtual bool hasBlock() const { return false; }
	virtual bool hasReturn() const { return false; }

protected:
	NodeList* m_nodes;
	location m_location;

	DISALLOW_COPY_AND_ASSIGN(ASTNode);
};

class VarDecls : public ASTNode {
public:
	VarDecls() {}

	VarDecls(NodeList* nodes) {
		m_nodes = nodes;
		NodeList::const_iterator it = m_nodes->begin(), end = m_nodes->end();

		while (it != end) {
			CLEVER_ADDREF((*it));
			++it;
		}
	}

	~VarDecls() {
		if (m_nodes) {
			clearNodes();
			delete m_nodes;
		}
	}

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(VarDecls);
};

class Literal : public ASTNode {
public:
	Literal() { }
	virtual ~Literal() { }

	bool isLiteral() const { return true; }
	virtual bool hasValue() const { return true; }
	virtual Value* getValue() const = 0;
private:
	DISALLOW_COPY_AND_ASSIGN(Literal);
};

class NumberLiteral : public Literal {
public:
	explicit NumberLiteral(int64_t val) {
		m_value = new Value(val);
		m_value->setTypePtr(CLEVER_INT);
	}

	explicit NumberLiteral(double val) {
		m_value = new Value(val);
		m_value->setTypePtr(CLEVER_DOUBLE);
	}

	explicit NumberLiteral(Value* value)
		: m_value(value) { }

	~NumberLiteral() {
		CLEVER_DELREF(m_value);
	}

	Value* getValue() const { return m_value; };

	NumberLiteral* asNumberLiteral() { return this; }
private:
	Value* m_value;

	DISALLOW_COPY_AND_ASSIGN(NumberLiteral);
};

class Identifier : public ASTNode {
public:
	explicit Identifier(const CString* name)
		: m_name(name), m_value(NULL), m_template_args(NULL) {}

	~Identifier() {
		CLEVER_SAFE_DELREF(m_value);

		if (m_template_args) {
			for (size_t i = 0, j = m_template_args->size(); i < j; ++i) {
				CLEVER_DELREF(m_template_args->at(i));
			}

			delete m_template_args;
		}
	}

	void concat(std::string sep, Identifier* ident) {
		m_name = CSTRING(m_name->str() + sep + ident->getName()->str());
	}

	bool hasValue() const { return true; }

	Value* getValue() const { return m_value; }

	void setValue(Value* value) { m_value = value; }

	const CString* getName() const { return m_name; }

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}

	void setTemplateArgs(TemplateArgsVector* template_args) {
		m_template_args = template_args;

		for (size_t i = 0, j = m_template_args->size(); i < j; ++i) {
			CLEVER_ADDREF(m_template_args->at(i));
		}
	}

	TemplateArgsVector* getTemplateArgs() const {
		return m_template_args;
	}
private:
	const CString* m_name;
	Value* m_value;
	TemplateArgsVector* m_template_args;

	DISALLOW_COPY_AND_ASSIGN(Identifier);
};

class Constant : public ASTNode {
public:
	Constant(Identifier* ident)
		: m_ident(ident), m_value(NULL) {
		CLEVER_ADDREF(m_ident);
	}

	~Constant() {
		CLEVER_DELREF(m_ident);
		CLEVER_DELREF(m_value);
	}

	const CString* getName() const { return m_ident->getName(); }

	void setValue(Value* value) { m_value = value; }

	Value* getValue() const { return m_value; }

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}
private:
	Identifier* m_ident;
	Value* m_value;
};

class StringLiteral : public Literal {
public:
	explicit StringLiteral(const CString* name) {
		m_value = new Value(name);
	}

	~StringLiteral() {
		CLEVER_DELREF(m_value);
	}

	Value* getValue() const { return m_value; };

	const CString* getString() const { return m_value->getStringP(); }
private:
	Value* m_value;

	DISALLOW_COPY_AND_ASSIGN(StringLiteral);
};

class BlockNode : public ASTNode {
public:
	BlockNode() :
		m_scope(NULL), m_has_return(false) {
		m_nodes = new NodeList;
	}

	~BlockNode() {
		if (m_nodes) {
			clearNodes();
			delete m_nodes;
		}
	}

	void setScope(Scope* scope) {
		clever_assert_null(m_scope);

		m_scope = scope;
	}

	Scope* getScope() {
		return m_scope;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}

	bool hasReturn() const { return m_has_return; }
	void setReturn() { m_has_return = true; }
private:
	Scope* m_scope;
	bool m_has_return;
	DISALLOW_COPY_AND_ASSIGN(BlockNode);
};

class UnscopedBlockNode : public ASTNode {
public:
	UnscopedBlockNode()
		: m_alias(NULL), m_block(NULL), m_has_return(false) {}

	explicit UnscopedBlockNode(Identifier* alias, BlockNode* block)
		: m_alias(alias), m_block(block), m_has_return(false) {
		CLEVER_SAFE_ADDREF(m_alias);
		CLEVER_ADDREF(m_block);
	}

	~UnscopedBlockNode() {
		CLEVER_SAFE_DELREF(m_alias);
		CLEVER_SAFE_DELREF(m_block);
	}

	const CString* getAlias() const {
		if (m_alias) {
			return m_alias->getName();
		}
		return NULL;
	}

	BlockNode* getBlock() const {
		return m_block;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}

	bool hasBlock() const {
		return m_block != NULL;
	}

	bool hasReturn() const { return m_has_return; }
	void setReturn() { m_has_return = true; }
private:
	Identifier* m_alias;
	BlockNode* m_block;
	bool m_has_return;
	DISALLOW_COPY_AND_ASSIGN(UnscopedBlockNode);
};

class IfExpr : public ASTNode {
public:
	IfExpr(ASTNode* condition, ASTNode* block)
		: m_condition(condition), m_block(block), m_else(NULL), m_has_return(false) {
		CLEVER_ADDREF(m_condition);
		CLEVER_SAFE_ADDREF(m_block);
		m_nodes = new NodeList;
	}

	~IfExpr() {
		CLEVER_DELREF(m_condition);
		CLEVER_SAFE_DELREF(m_block);
		CLEVER_SAFE_DELREF(m_else);
		clearNodes();
		delete m_nodes;
	}

	bool hasBlock() const { return m_block != NULL; }
	bool hasElseBlock() const { return m_else != NULL; }
	bool hasElseIf() const { return m_nodes != NULL && m_nodes->size() != 0; }
	bool hasReturn() const { return m_has_return; }
	void setReturn() { m_has_return = true; }

	ASTNode* getBlock() { return m_block; }
	ASTNode* getCondition() { return m_condition; }

	ASTNode* getElse() { return m_else; }
	void setElse(ASTNode* expr) {
		if (expr) {
			m_else = expr;
			CLEVER_ADDREF(m_else);
		}
	}

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}
private:
	ASTNode* m_condition;
	ASTNode* m_block;
	ASTNode* m_else;
	bool m_has_return;

	DISALLOW_COPY_AND_ASSIGN(IfExpr);
};

class ElseIfExpr : public ASTNode {
public:
	ElseIfExpr(ASTNode* condition, ASTNode* block)
		: m_condition(condition), m_block(block), m_has_return(false) {
		CLEVER_ADDREF(m_condition);
		CLEVER_SAFE_ADDREF(m_block);
	}

	~ElseIfExpr() {
		CLEVER_DELREF(m_condition);
		CLEVER_SAFE_DELREF(m_block);
	}

	bool hasBlock() { return m_block != NULL; }

	ASTNode* getCondition() { return m_condition; }
	ASTNode* getBlock() { return m_block; }
	bool hasReturn() const { return m_has_return; }
	void setReturn() { m_has_return = true; }
private:
	ASTNode* m_condition;
	ASTNode* m_block;
	bool m_has_return;

	DISALLOW_COPY_AND_ASSIGN(ElseIfExpr);
};

class WhileExpr : public ASTNode {
public:
	WhileExpr(ASTNode* condition, ASTNode* block)
		: m_condition(condition), m_block(block), m_has_return(false) {
		CLEVER_ADDREF(m_condition);
		CLEVER_SAFE_ADDREF(m_block);
	}

	~WhileExpr() {
		CLEVER_DELREF(m_condition);
		CLEVER_SAFE_DELREF(m_block);
	}

	bool hasBlock() { return m_block != NULL; }

	ASTNode* getCondition() { return m_condition; }
	ASTNode* getBlock() { return m_block; }

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}

	bool hasReturn() const { return m_has_return; }
	void setReturn() { m_has_return = true; }
private:
	ASTNode* m_condition;
	ASTNode* m_block;
	bool m_has_return;

	DISALLOW_COPY_AND_ASSIGN(WhileExpr);
};

class ForExpr : public ASTNode {
public:
	ForExpr(ASTNode* var_decl, ASTNode* ident, ASTNode* block)
		: m_var_decl(var_decl), m_ident(ident), m_condition(NULL),
		m_increment(NULL), m_block(block), m_has_return(false) {
		CLEVER_ADDREF(m_var_decl);
		CLEVER_ADDREF(m_ident);
		CLEVER_SAFE_ADDREF(m_block);
	}

	ForExpr(ASTNode* var_decl, ASTNode* condition, ASTNode* increment, ASTNode* block)
		: m_var_decl(var_decl), m_ident(NULL), m_condition(condition),
		m_increment(increment), m_block(block), m_has_return(false) {
		CLEVER_SAFE_ADDREF(m_var_decl);
		CLEVER_SAFE_ADDREF(m_condition);
		CLEVER_SAFE_ADDREF(m_increment);
		CLEVER_SAFE_ADDREF(m_block);
	}

	~ForExpr() {
		CLEVER_SAFE_DELREF(m_var_decl);
		CLEVER_SAFE_DELREF(m_ident);
		CLEVER_SAFE_DELREF(m_condition);
		CLEVER_SAFE_DELREF(m_increment);
		CLEVER_SAFE_DELREF(m_block);
	}

	bool hasBlock() const { return m_block != NULL; }
	bool isIteratorMode() const { return m_ident != NULL; }
	ASTNode* getVarDecl() { return m_var_decl; }
	ASTNode* getIdentifier() { return m_ident; }
	ASTNode* getCondition() { return m_condition; }
	ASTNode* getIncrement() { return m_increment; }
	ASTNode* getBlock() { return m_block; }

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}

	bool hasReturn() const { return m_has_return; }
	void setReturn() { m_has_return = true; }
private:
	ASTNode* m_var_decl;
	ASTNode* m_ident;
	ASTNode* m_condition;
	ASTNode* m_increment;
	ASTNode* m_block;
	bool m_has_return;

	DISALLOW_COPY_AND_ASSIGN(ForExpr);
};

class BreakNode : public ASTNode {
public:
	BreakNode() { }

	~BreakNode() { }

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(BreakNode);
};

class ArgumentList : public ASTNode {
public:
	ArgumentList()
		: m_value(NULL) {
		m_nodes = new NodeList;
	}

	~ArgumentList() {
		clearNodes();
		delete m_nodes;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}

	ValueVector* getArgValue() { return m_value; }

	void setArgValue(ValueVector* value) { m_value = value; }
private:
	ValueVector* m_value;
	DISALLOW_COPY_AND_ASSIGN(ArgumentList);
};

class ArgumentDeclList : public ASTNode {
public:
	ArgumentDeclList() { }

	~ArgumentDeclList() {
		ArgumentDecls::const_iterator it = m_args.begin(), end = m_args.end();

		while (it != end) {
			CLEVER_DELREF(it->first);
			CLEVER_DELREF(it->second);
			++it;
		}
	}

	void addArg(Identifier* type, Identifier* name) {
		m_args.push_back(ArgumentDeclPair(type, name));
		CLEVER_ADDREF(type);
		CLEVER_ADDREF(name);
	}

	ArgumentDecls& getArgs() { return m_args; }
private:
	ArgumentDecls m_args;

	DISALLOW_COPY_AND_ASSIGN(ArgumentDeclList);
};

class BinaryExpr : public ASTNode {
public:
	BinaryExpr(int op, ASTNode* lhs, ASTNode* rhs)
		: m_lhs(lhs), m_rhs(rhs), m_op(op), m_result(NULL), m_assign(false),
			m_call_value(NULL), m_args_value(NULL) {
		CLEVER_ADDREF(m_lhs);
		CLEVER_ADDREF(m_rhs);
	}
	BinaryExpr(int op, ASTNode* lhs, ASTNode* rhs, bool assign)
		: m_lhs(lhs), m_rhs(rhs), m_op(op), m_result(NULL), m_assign(assign),
			m_call_value(NULL), m_args_value(NULL) {
		CLEVER_ADDREF(m_lhs);
		CLEVER_ADDREF(m_rhs);
	}

	BinaryExpr(int op, ASTNode* rhs)
		: m_lhs(NULL), m_rhs(rhs), m_op(op), m_result(NULL), m_assign(false),
			m_call_value(NULL), m_args_value(NULL) {
		m_lhs = new NumberLiteral(int64_t(0));
		CLEVER_ADDREF(m_lhs);
		CLEVER_ADDREF(m_rhs);
	}

	virtual ~BinaryExpr() {
		if (m_lhs) {
			CLEVER_DELREF(m_lhs);
		}
		if (m_rhs) {
			CLEVER_DELREF(m_rhs);
		}
		if (m_call_value) {
			CLEVER_DELREF(m_call_value);
		}
	}

	bool hasValue() const { return true; }

	bool isAssigned() const { return m_assign; }

	ASTNode* getLhs() const { return m_lhs; }
	ASTNode* getRhs() const { return m_rhs; }

	int getOp() const { return m_op; }

	Value* getValue() const { return m_result; }

	void setResult(Value* value) { m_result = value; }

	void setCallValue(CallableValue* callable) {
		m_call_value = callable;
	}

	CallableValue* getCallValue() const {
		return m_call_value;
	}

	void setArgsValue(ValueVector* args_value) {
		m_args_value = args_value;
	}

	ValueVector* getArgsValue() const {
		return m_args_value;
	}

	virtual void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}
private:
	ASTNode* m_lhs;
	ASTNode* m_rhs;
	int m_op;
	Value* m_result;
	bool m_assign;
	CallableValue* m_call_value;
	ValueVector* m_args_value;

	DISALLOW_COPY_AND_ASSIGN(BinaryExpr);
};

class Subscript : public ASTNode {
public:
	Subscript(Identifier* ident, ASTNode* expr)
		: m_ident(ident), m_expr(expr), m_result(NULL), m_call_value(NULL),
			m_args_value(NULL) {
		CLEVER_ADDREF(m_ident);
		CLEVER_ADDREF(m_expr);
	}

	~Subscript() {
		CLEVER_DELREF(m_ident);
		CLEVER_DELREF(m_expr);
		CLEVER_SAFE_DELREF(m_call_value);
	}

	Identifier* getIdentifier() const {
		return m_ident;
	}

	ASTNode* getExpr() const {
		return m_expr;
	}

	void setValue(Value* value) {
		m_result = value;
	}

	Value* getValue() const {
		return m_result;
	}

	void setCallValue(CallableValue* callable) {
		m_call_value = callable;
	}

	CallableValue* getCallValue() const {
		return m_call_value;
	}

	void setArgsValue(ValueVector* args_value) {
		m_args_value = args_value;
	}

	ValueVector* getArgsValue() const {
		return m_args_value;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		m_ident->acceptVisitor(visitor);
		m_expr->acceptVisitor(visitor);

		visitor.visit(this);
	}
private:
	Identifier* m_ident;
	ASTNode* m_expr;
	Value* m_result;
	CallableValue* m_call_value;
	ValueVector* m_args_value;

	DISALLOW_COPY_AND_ASSIGN(Subscript);
};

class VariableDecl : public ASTNode {
public:
	VariableDecl(Identifier* type, Identifier* variable)
		: m_type(type), m_variable(variable), m_rhs(NULL), m_const_value(false),
			m_call_value(NULL), m_args_value(NULL), m_ctor_args(NULL) {
		CLEVER_SAFE_ADDREF(m_type);
		CLEVER_ADDREF(m_variable);
	}

	VariableDecl(Identifier* type, Identifier* variable, ASTNode* rhs)
		: m_type(type), m_variable(variable), m_rhs(rhs), m_const_value(false),
			m_call_value(NULL), m_args_value(NULL), m_ctor_args(NULL) {

		// If is not `Auto' typed variable
		CLEVER_SAFE_ADDREF(m_type);
		CLEVER_ADDREF(m_variable);
		CLEVER_ADDREF(m_rhs);
	}

	VariableDecl(Identifier* type, Identifier* variable, ASTNode* rhs,
		bool const_value)
		: m_type(type), m_variable(variable), m_rhs(rhs),
			m_const_value(const_value), m_call_value(NULL),	m_args_value(NULL),
			m_ctor_args(NULL) {

		// If is not `Auto' typed variable
		CLEVER_SAFE_ADDREF(m_type);
		CLEVER_ADDREF(m_variable);
		CLEVER_ADDREF(m_rhs);
	}

	VariableDecl(Identifier* type, Identifier* variable, ArgumentList* arg_list)
		: m_type(type), m_variable(variable), m_rhs(NULL), m_const_value(false),
			m_call_value(NULL),	m_args_value(NULL), m_ctor_args(arg_list) {
		CLEVER_SAFE_ADDREF(m_type);
		CLEVER_SAFE_ADDREF(m_variable);
		CLEVER_SAFE_ADDREF(m_ctor_args);
	}

	virtual ~VariableDecl() {
		CLEVER_SAFE_DELREF(m_type);
		CLEVER_DELREF(m_variable);
		CLEVER_SAFE_DELREF(m_rhs);
		CLEVER_SAFE_DELREF(m_call_value);
		CLEVER_SAFE_DELREF(m_ctor_args);
	}

	Identifier* getVariable() const {
		return m_variable;
	}

	ASTNode* getRhs() {
		return m_rhs;
	}

	void setType(Identifier* type){
		m_type = type;
		CLEVER_ADDREF(m_type);
	}

	Identifier* getType() const {
		return m_type;
	}

	void setCallValue(CallableValue* callable) {
		m_call_value = callable;
	}

	CallableValue* getCallValue() const {
		return m_call_value;
	}

	void setArgsValue(ValueVector* args_value) {
		m_args_value = args_value;
	}

	ValueVector* getArgsValue() const {
		return m_args_value;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		if (m_rhs) {
			m_rhs->acceptVisitor(visitor);
		}
		else if (m_ctor_args) {
			m_ctor_args->acceptVisitor(visitor);
		}

		visitor.visit(this);
	}

	void setConstness(bool constness) {
		m_const_value = constness;
	}

	bool isConst() const {
		return m_const_value;
	}

	ArgumentList* getConstructorArgs() const {
		return m_ctor_args;
	}
private:
	/**
	 * The variable's type. NULL means `Auto' typed variable.
	 */
	Identifier* m_type;
	Identifier* m_variable;
	ASTNode* m_rhs;
	bool m_const_value;
	CallableValue* m_call_value;
	ValueVector* m_args_value;
	ArgumentList* m_ctor_args;

	DISALLOW_COPY_AND_ASSIGN(VariableDecl);
};

class AttributeDeclaration : public VariableDecl {
public:
	AttributeDeclaration(ASTNode* modifier, Identifier* type, Identifier* variable)
		: VariableDecl(type, variable), m_modifier(modifier) {
		CLEVER_ADDREF(m_modifier);
	}

	~AttributeDeclaration() {
		CLEVER_DELREF(m_modifier);
	}
private:
	ASTNode* m_modifier;
	DISALLOW_COPY_AND_ASSIGN(AttributeDeclaration);
};

class UnaryExpr : public ASTNode {
public:
	UnaryExpr(int op, ASTNode* expr)
		: m_op(op), m_expr(expr), m_result(NULL), m_call_value(NULL) {
		CLEVER_ADDREF(m_expr);
	}

	~UnaryExpr() {
		CLEVER_DELREF(m_expr);
		CLEVER_SAFE_DELREF(m_call_value);
	}

	int getOp() const {
		return m_op;
	}

	void setValue(Value* value) {
		m_result = value;
	}

	Value* getValue() const {
		return m_result;
	}

	ASTNode* getExpr() const {
		return m_expr;
	}

	void setCallValue(CallableValue* callable) {
		m_call_value = callable;
	}

	CallableValue* getCallValue() const {
		return m_call_value;
	}

	virtual void acceptVisitor(ASTVisitor& visitor) {
		m_expr->acceptVisitor(visitor);

		visitor.visit(this);
	}
private:
	int m_op;
	ASTNode* m_expr;
	Value* m_result;
	CallableValue* m_call_value;

	DISALLOW_COPY_AND_ASSIGN(UnaryExpr);
};

class RegexPattern : public ASTNode {
public:
	RegexPattern(Value* regex)
		: m_regex(regex), m_value(NULL), m_call_value(NULL), m_args_value(NULL) {
		CLEVER_ADDREF(m_regex);
	}

	~RegexPattern() {
		CLEVER_SAFE_DELREF(m_regex);
		CLEVER_SAFE_DELREF(m_call_value);
	}

	Value* getRegex() const { return m_regex; }

	void setValue(Value* value) { m_value = value; }

	Value* getValue() const { return m_value; }

	void setCallValue(CallableValue* callable) {
		m_call_value = callable;
	}

	CallableValue* getCallValue() const {
		return m_call_value;
	}

	void setArgsValue(ValueVector* args_value) {
		m_args_value = args_value;
	}

	ValueVector* getArgsValue() const {
		return m_args_value;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}
private:
	Value* m_regex;
	Value* m_value;
	CallableValue* m_call_value;
	ValueVector* m_args_value;

	DISALLOW_COPY_AND_ASSIGN(RegexPattern);
};

class TypeCreation : public ASTNode {
public:
	TypeCreation(Identifier* type, ArgumentList* args)
		: m_type(type), m_value(NULL), m_args(args), m_call_value(NULL),
			m_args_value(NULL) {
		CLEVER_SAFE_ADDREF(m_type);
		CLEVER_SAFE_ADDREF(m_args);
	}

	~TypeCreation() {
		CLEVER_DELREF(m_type);
		CLEVER_SAFE_DELREF(m_args);
		CLEVER_SAFE_DELREF(m_call_value);
		CLEVER_SAFE_DELREF(m_value);
	}

	Identifier* getIdentifier() {
		return m_type;
	}

	void setType(Identifier* type){
		m_type = type;
		CLEVER_ADDREF(m_type);
	}

	void setValue(Value* value) {
		m_value = value;
	}

	Value* getValue() const {
		return m_value;
	}

	ArgumentList* getArgs() {
		return m_args;
	}

	void setCallValue(CallableValue* callable) {
		m_call_value = callable;
	}

	CallableValue* getCallValue() const {
		return m_call_value;
	}

	void setArgsValue(ValueVector* args_value) {
		m_args_value = args_value;
	}

	ValueVector* getArgsValue() const {
		return m_args_value;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		ArgumentList* args = getArgs();
		if (args) {
			args->acceptVisitor(visitor);
		}
		visitor.visit(this);
	}
private:
	Identifier* m_type;
	Value* m_value;
	ArgumentList* m_args;
	CallableValue* m_call_value;
	ValueVector* m_args_value;

	DISALLOW_COPY_AND_ASSIGN(TypeCreation);
};

class FuncPrototype : public ASTNode {
public:
	FuncPrototype(Identifier* name, Identifier* rtype, ArgumentDeclList* args)
		: m_name(name), m_return(rtype), m_args(args), m_value(NULL) {
		CLEVER_SAFE_ADDREF(m_name);
		CLEVER_SAFE_ADDREF(m_return);
		CLEVER_SAFE_ADDREF(m_args);
	}

	virtual ~FuncPrototype() {
		CLEVER_SAFE_DELREF(m_name);
		CLEVER_SAFE_DELREF(m_return);
		CLEVER_SAFE_DELREF(m_args);
		CLEVER_SAFE_DELREF(m_value);
	}

	const CString* getName() const { return m_name->getName(); }
	ArgumentDeclList* getArgs() const { return m_args; }

	Identifier* getReturn() const { return m_return; }

	Identifier* getReturnValue() const { return m_return ? m_return : NULL; }


	void setValue(CallableValue* value) { m_value = value; }

	CallableValue* getFunc() { return m_value; }

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}
protected:
	Identifier* m_name;
	Identifier* m_return;
	ArgumentDeclList* m_args;
	CallableValue* m_value;
private:
	DISALLOW_COPY_AND_ASSIGN(FuncPrototype);
};

class FuncDeclaration : public ASTNode {
public:
	FuncDeclaration(Identifier* name, Identifier* rtype,
		ArgumentDeclList* args, BlockNode* block, bool is_const = false)
		: m_name(name), m_return(rtype), m_args(args), m_block(block),
			m_value(NULL), m_is_const(is_const) {
		CLEVER_SAFE_ADDREF(m_name);
		CLEVER_SAFE_ADDREF(m_return);
		CLEVER_SAFE_ADDREF(m_args);
		CLEVER_SAFE_ADDREF(m_block);
	}

	virtual ~FuncDeclaration() {
		CLEVER_SAFE_DELREF(m_name);
		CLEVER_SAFE_DELREF(m_return);
		CLEVER_SAFE_DELREF(m_args);
		CLEVER_SAFE_DELREF(m_block);
		CLEVER_SAFE_DELREF(m_value);
	}

	const CString* getName() const { return m_name->getName(); }
	ArgumentDeclList* getArgs() const { return m_args; }

	Identifier* getReturn() const { return m_return; }

	Identifier* getReturnValue() const { return m_return ? m_return : NULL; }

	BlockNode* getBlock() const { return m_block; }
	bool hasBlock() const { return m_block != NULL; }

	void setValue(CallableValue* value) { m_value = value; }

	CallableValue* getFunc() { return m_value; }

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}
protected:
	Identifier* m_name;
	Identifier* m_return;
	ArgumentDeclList* m_args;
	BlockNode* m_block;
	CallableValue* m_value;
	bool m_is_const;
private:
	DISALLOW_COPY_AND_ASSIGN(FuncDeclaration);
};

class LambdaFunction : public ASTNode {
public:
	LambdaFunction(FuncDeclaration* func)
		: m_function(func), m_value(NULL) {
		CLEVER_ADDREF(m_function);
	}

	virtual ~LambdaFunction() {
		CLEVER_DELREF(m_function);
		CLEVER_SAFE_DELREF(m_value);
	}

	const CString* getName() const { return m_function->getName(); }

	const Function* getFunction() const { return m_function->getFunc()->getFunction(); }

	void acceptVisitor(ASTVisitor& visitor) {
		m_function->acceptVisitor(visitor);
		visitor.visit(this);
	}

	static Identifier* getLambdaId() {
		std::ostringstream oss;
		oss << "$lambda" << (++m_lambda_id) << "$";

		return new Identifier(CSTRING(oss.str()));
	}

	void setValue(Value* value) {
		m_value = value;
	}

	Value* getValue() const {
		return m_value;
	}

	const Type* getReturnType() const {
		return getFunction()->getReturnType();
	}

	const FunctionArgs& getArgs() const {
		return getFunction()->getArgs();
	}
protected:
	FuncDeclaration* m_function;
	Value* m_value;
	static int m_lambda_id;
private:
	DISALLOW_COPY_AND_ASSIGN(LambdaFunction);
};


class ExtFuncDeclaration : public ASTNode {
public:
	ExtFuncDeclaration(StringLiteral* libname, Identifier* name,
		Identifier* rtype, ArgumentDeclList* args )
		: m_libname(libname), m_lfname(NULL), m_name(name), m_return(rtype),
			m_args(args), m_value(NULL) {
		CLEVER_SAFE_ADDREF(m_libname);
		CLEVER_ADDREF(m_name);
		CLEVER_SAFE_ADDREF(m_return);
		CLEVER_SAFE_ADDREF(m_args);
	}

	ExtFuncDeclaration(StringLiteral* libname, Identifier* name,
		Identifier* rtype, ArgumentDeclList* args, StringLiteral* m_lfname )
		: m_libname(libname), m_lfname(m_lfname), m_name(name), m_return(rtype),
			m_args(args), m_value(NULL) {
		CLEVER_SAFE_ADDREF(m_libname);
		CLEVER_SAFE_ADDREF(m_lfname);
		CLEVER_ADDREF(m_name);
		CLEVER_SAFE_ADDREF(m_return);
		CLEVER_SAFE_ADDREF(m_args);
	}

	virtual ~ExtFuncDeclaration() {
		CLEVER_SAFE_DELREF(m_libname);
		CLEVER_SAFE_DELREF(m_lfname);
		CLEVER_DELREF(m_name);
		CLEVER_SAFE_DELREF(m_return);
		CLEVER_SAFE_DELREF(m_args);
		CLEVER_SAFE_DELREF(m_value);
	}

	const CString* getLFName() const {
		if ( m_lfname == NULL ){
			return NULL;
		}
		return m_lfname->getString();
	}
	const CString* getLibName() const { return m_libname->getString(); }
	const CString* getName() const { return m_name->getName(); }
	ArgumentDeclList* getArgs() const { return m_args; }

	Identifier* getReturnValue() const { return m_return; }

	void setLibName(StringLiteral* libname) {
		m_libname = libname;
		CLEVER_ADDREF(m_libname);
	}
	void setValue(CallableValue* value) { m_value = value; }

	CallableValue* getFunc(void) { return m_value; }

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}

protected:
	StringLiteral* m_libname;
	StringLiteral* m_lfname;
	Identifier* m_name;
	Identifier* m_return;
	ArgumentDeclList* m_args;
	CallableValue* m_value;
private:
	DISALLOW_COPY_AND_ASSIGN(ExtFuncDeclaration);
};

inline void _set_libname_ext_func_decl(ExtFuncDecls* v, StringLiteral* libname) {
	ExtFuncDecls::iterator it = v->begin(), end = v->end();

	while (it != end) {
		(*it)->setLibName(libname);
		++it;
	}
}

class MethodDeclaration: public FuncDeclaration {
public:
	MethodDeclaration(ASTNode* modifier, Identifier* rtype, Identifier* name,
                ArgumentDeclList* args, BlockNode* block)
		: FuncDeclaration(name, rtype, args, block), m_modifier(modifier) {
                    CLEVER_ADDREF(m_modifier);
	}

	~MethodDeclaration() {
		CLEVER_DELREF(m_modifier);
	}

	ASTNode* getModifier() { return m_modifier; }

	bool hasBlock() const {
		return true;
	}
protected:
	ASTNode* m_modifier;
};

class FunctionCall : public ASTNode {
public:
	FunctionCall(Identifier* name, ArgumentList* args)
		: m_name(name), m_args(args), m_args_value(NULL),
			m_result(NULL), m_value(NULL) {
		CLEVER_ADDREF(m_name);
		CLEVER_SAFE_ADDREF(m_args);
	}


	~FunctionCall() {
		CLEVER_DELREF(m_name);
		CLEVER_SAFE_DELREF(m_result);
		CLEVER_SAFE_DELREF(m_args);
		CLEVER_SAFE_DELREF(m_value);
	}


	void setFuncValue(CallableValue* value) {
		m_value = value;
	}

	void setValue(Value* value) { m_result = value; }

	Value* getValue() const { return m_result; }

	CallableValue* getFuncValue() {
		return m_value;
	}

	const CString* getFuncName() const { return m_name->getName(); }

	ArgumentList* getArgs() { return m_args; }

	void setArgs(ArgumentList* args){ m_args = args; }

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}

	void setArgsValue(ValueVector* value) {
		m_args_value = value;
	}

	ValueVector* getArgsValue() {
		return m_args_value;
	}
private:
	Identifier* m_name;
	ArgumentList* m_args;
	ValueVector* m_args_value;
	Value* m_result;
	CallableValue* m_value;

	DISALLOW_COPY_AND_ASSIGN(FunctionCall);
};

class MethodCall : public ASTNode {
public:
	MethodCall(ASTNode* var, Identifier* method, ArgumentList* args)
		: m_var(var), m_method(method), m_result(NULL), m_args(args),
			m_call_value(NULL), m_args_value(NULL), m_is_static(false) {
		CLEVER_ADDREF(m_var);
		CLEVER_ADDREF(m_method);
		CLEVER_SAFE_ADDREF(m_args);
	}

	MethodCall(ASTNode* var, Identifier* method, ArgumentList* args,
		bool is_static)
		: m_var(var), m_method(method), m_result(NULL), m_args(args),
			m_call_value(NULL), m_args_value(NULL), m_is_static(is_static) {
		CLEVER_ADDREF(m_var);
		CLEVER_ADDREF(m_method);
		CLEVER_SAFE_ADDREF(m_args);
	}

	MethodCall(Subscript* sub, Identifier* method, ArgumentList* args)
		: m_var(sub), m_method(method), m_result(NULL), m_args(args),
			m_call_value(NULL), m_args_value(NULL), m_is_static(false) {
		CLEVER_ADDREF(m_var);
		CLEVER_ADDREF(m_method);
		CLEVER_SAFE_ADDREF(m_args);
	}

	~MethodCall() {
		CLEVER_DELREF(m_var);
		CLEVER_DELREF(m_method);
		CLEVER_SAFE_DELREF(m_args);
		CLEVER_SAFE_DELREF(m_call_value);
	}

	ASTNode* getVariable() const { return m_var; }
	const CString* getMethodName() const { return m_method->getName(); }

	bool isStaticCall() const { return m_is_static; }

	void setValue(Value* value) { m_result = value; }
	Value* getValue() const { return m_result; }

	ArgumentList* getArgs() {
		return m_args;
	}

	void setCallValue(CallableValue* callable) {
		m_call_value = callable;
	}

	CallableValue* getCallValue() const {
		return m_call_value;
	}

	void setArgsValue(ValueVector* args_value) {
		m_args_value = args_value;
	}

	ValueVector* getArgsValue() const {
		return m_args_value;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		ArgumentList* args = getArgs();

		if (!isStaticCall()) {
			m_var->acceptVisitor(visitor);
		}

		if (args) {
			args->acceptVisitor(visitor);
		}

		visitor.visit(this);
	}
private:
	ASTNode* m_var;
	Identifier* m_method;
	Value* m_result;

	ArgumentList* m_args;
	CallableValue* m_call_value;
	ValueVector* m_args_value;

	bool m_is_static;

	DISALLOW_COPY_AND_ASSIGN(MethodCall);
};

class AssignExpr : public ASTNode {
public:
	AssignExpr(Identifier* lhs, ASTNode* rhs)
		: m_lhs(lhs), m_rhs(rhs), m_call_value(NULL), m_args_value(NULL), m_value(NULL) {
		CLEVER_ADDREF(lhs);
		CLEVER_ADDREF(rhs);
	}

	~AssignExpr() {
		CLEVER_DELREF(m_lhs);
		CLEVER_DELREF(m_rhs);
		CLEVER_SAFE_DELREF(m_call_value);
	}

	ASTNode* getLhs() const { return m_lhs; }
	ASTNode* getRhs() const { return m_rhs; }

	void setCallValue(CallableValue* callable) {
		m_call_value = callable;
	}

	CallableValue* getCallValue() const {
		return m_call_value;
	}

	void setArgsValue(ValueVector* args_value) {
		m_args_value = args_value;
	}

	ValueVector* getArgsValue() const {
		return m_args_value;
	}

	void setValue(Value* value) {
		m_value = value;
	}

	Value* getValue() const {
		return m_value;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		getLhs()->acceptVisitor(visitor);
		getRhs()->acceptVisitor(visitor);
		visitor.visit(this);
	}
private:
	Identifier* m_lhs;
	ASTNode* m_rhs;
	CallableValue* m_call_value;
	ValueVector* m_args_value;
	Value* m_value;

	DISALLOW_COPY_AND_ASSIGN(AssignExpr);
};

class ImportStmt : public ASTNode {
public:
	ImportStmt(Identifier* package)
		: m_package(package), m_module(NULL), m_obj(NULL), m_alias(NULL),
			m_is_type(false) {
		CLEVER_ADDREF(m_package);
	}

	ImportStmt(Identifier* package, Identifier* module, Identifier* obj,
		bool is_type)
		: m_package(package), m_module(module), m_obj(obj), m_alias(NULL),
			m_is_type(is_type) {
		CLEVER_ADDREF(m_package);
		CLEVER_ADDREF(m_module);
		CLEVER_SAFE_ADDREF(m_obj);
	}

	~ImportStmt() {
		CLEVER_SAFE_DELREF(m_package);
		CLEVER_SAFE_DELREF(m_module);
		CLEVER_SAFE_DELREF(m_obj);
		CLEVER_SAFE_DELREF(m_alias);
	}

	void setAlias(Identifier* alias) {
		m_alias = alias;
		CLEVER_ADDREF(alias);
	}

	const CString* getObjectName() {
		return m_obj ? m_obj->getName() : NULL;
	}

	const CString* getPackageName() {
		return m_package->getName();
	}

	const CString* getModuleName() {
		return m_module ? m_module->getName() : NULL;
	}

	const CString* getAliasName() {
		return m_alias ? m_alias->getName() : NULL;
	}

	bool isType() {
		return m_is_type;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}
private:
	Identifier* m_package;
	Identifier* m_module;
	Identifier* m_obj;
	Identifier* m_alias;
	bool m_is_type;

	DISALLOW_COPY_AND_ASSIGN(ImportStmt);
};

class AliasStmt : public ASTNode {
public:
	AliasStmt(Identifier* new_name, Identifier* curr_name, bool is_id = true)
		: m_new_name(new_name), m_curr_name(curr_name), m_is_id(is_id) {
		CLEVER_ADDREF(m_new_name);
		CLEVER_ADDREF(m_curr_name);
	}


	~AliasStmt() {
		CLEVER_DELREF(m_new_name);
		CLEVER_DELREF(m_curr_name);
	}

	bool isId() { return m_is_id; }

	const CString* getNewName() { return m_new_name->getName(); }
	const CString* getCurrentName() { return m_curr_name->getName(); }

	const Identifier* getCurrentNameIdentifier() const { return m_curr_name; }


	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}
private:

	Identifier* m_new_name;
	Identifier* m_curr_name;

	bool m_is_id;

};

class ReturnStmt : public ASTNode {
public:
	ReturnStmt()
		: m_expr(NULL) { }

	explicit ReturnStmt(ASTNode* expr)
		: m_expr(expr) {
		CLEVER_ADDREF(m_expr);
	}

	~ReturnStmt() {
		CLEVER_SAFE_DELREF(m_expr);
	}

	ASTNode* getExpr() const { return m_expr; }

	Value* getExprValue() const {
		return m_expr ? m_expr->getValue() : NULL;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		if (m_expr) {
			m_expr->acceptVisitor(visitor);
		}
		visitor.visit(this);
	}

	virtual bool hasReturn() const { return true; }
private:
	ASTNode* m_expr;

	DISALLOW_COPY_AND_ASSIGN(ReturnStmt);
};

class IntegralValue : public ASTNode {
public:
	IntegralValue(int value) : m_int_value(value) { }

	~IntegralValue() {
	}

	Value* getValue() const { return m_value; }

	int getInt() { return m_int_value; }
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
			CLEVER_DELREF((*it_method));
			++it_method;
		}
		while (it_attrib != it_attrib_end) {
			CLEVER_DELREF((*it_attrib));
			++it_attrib;
		}
	}

	void addMethod(MethodDeclaration* method) {
		m_methods_decl.push_back(method);
		CLEVER_ADDREF(method);
	}

	void addAttribute(AttributeDeclaration* attribute) {
		m_attrib_decl.push_back(attribute);
		CLEVER_ADDREF(attribute);
	}

	std::list<MethodDeclaration*>& getMethodsDecl() {
		return m_methods_decl;
	}

	std::list<AttributeDeclaration*>& getAttribsDecl() {
		return m_attrib_decl;
	}
private:
	std::list<MethodDeclaration*> m_methods_decl;
	std::list<AttributeDeclaration*> m_attrib_decl;

	DISALLOW_COPY_AND_ASSIGN(ClassStmtList);
};

class ClassDeclaration : public ASTNode {
public:
	ClassDeclaration(Identifier* name, ClassStmtList* body)
		: m_name(name), m_body(body) {
		CLEVER_ADDREF(m_name);
		CLEVER_ADDREF(m_body);
	}

	~ClassDeclaration() {
		CLEVER_DELREF(m_name);
		CLEVER_DELREF(m_body);
	}

	void acceptVisitor(ASTVisitor& visitor) {
		visitor.visit(this);
	}

	const CString* getClassName() const {
		return m_name->getName();
	}

private:
	Identifier*    m_name;
	ClassStmtList* m_body;

	DISALLOW_COPY_AND_ASSIGN(ClassDeclaration);
};

class ArrayList : public Literal {
public:
	ArrayList(ArgumentList* args) : m_arg_list(args), m_value(NULL)
	{
		CLEVER_ADDREF(m_arg_list);
	}

	Value* getValue() const {
		return m_value;
	}

	ArgumentList* getArgList() const {
		return m_arg_list;
	}

	void setValue(Value* v) {
		m_value = v;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		m_arg_list->acceptVisitor(visitor);
		visitor.visit(this);
	}

	~ArrayList() {
		CLEVER_DELREF(m_arg_list);
		CLEVER_SAFE_DELREF(m_value);
	}
private:
	ArgumentList* m_arg_list;
	Value* m_value;
	DISALLOW_COPY_AND_ASSIGN(ArrayList);
};

class MapList : public Literal {
public:
	MapList(ArgumentList* args)
		: m_arg_list(args), m_value(NULL) {
		CLEVER_ADDREF(m_arg_list);
	}

	Value* getValue() const {
		return m_value;
	}

	ArgumentList* getArgList() const {
		return m_arg_list;
	}

	void setValue(Value* v) {
		m_value = v;
	}

	void acceptVisitor(ASTVisitor& visitor) {
		m_arg_list->acceptVisitor(visitor);
		visitor.visit(this);
	}

	~MapList() {
		CLEVER_DELREF(m_arg_list);
		CLEVER_SAFE_DELREF(m_value);
	}
private:
	ArgumentList* m_arg_list;
	Value* m_value;
	DISALLOW_COPY_AND_ASSIGN(MapList);
};

inline void setType(VariableDecls* v, Identifier* type){
	VariableDecls::const_iterator it = v->begin(), end = v->end();

	while(it != end){
		(*it)->setType(type);
		if ((*it)->isConst()) {
			(*it)->setConstness(false);
			TypeCreation* tc = static_cast<TypeCreation*>((*it)->getRhs());
			tc->setType(type);
		}
		++it;
	}
}

inline void setConstness(VariableDecls* v, bool c) {
	VariableDecls::const_iterator it = v->begin(), end = v->end();

	while (it != end) {
		(*it)->setConstness(c);
		++it;
	}
}

}} // clever::ast

#endif // CLEVER_AST_H
