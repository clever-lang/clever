/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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

#include <string>
#include <vector>
#include "types.h"
#include "values.h"
#include "cstring.h"
#include "opcodes.h"
#include "refcounted.h"

namespace clever {
class IRBuilder;
}

namespace clever { namespace ast {

enum {
	GREATER,
	GREATER_EQUAL,
	LESS,
	LESS_EQUAL
};

class Expression : public RefCounted {
public:
	Expression() : RefCounted(0) { }

	virtual ~Expression() { }

	virtual bool isLiteral() const { return false; }

	virtual bool hasValue() const { return false; }
	/*
	 * Method for getting the value representation
	 */
	virtual Value* get_value() const { return NULL; }
	/*
	 * Method for generating the expression IR
	 */
	virtual Opcode* codeGen(IRBuilder&) { return NULL; };
	/*
	 * Method for debug purpose
	 */
	virtual std::string debug() { return std::string(); }
};

class TreeNode {
public:
	typedef std::vector<Expression*> nodeList;

	TreeNode() { }
	~TreeNode();

	inline void add(Expression* node) {
		node->addRef();
		nodes.push_back(node);
	}
	inline nodeList& getNodeList() {
		return nodes;
	}
private:
	nodeList nodes;
};


class Literal : public Expression {
public:
	Literal() { }
	virtual ~Literal() { }

	bool isLiteral() const { return true; }
	virtual bool hasValue() const { return true; }
	virtual Value* get_value() const = 0;
};

class BinaryExpression : public Expression {
public:
	BinaryExpression(char, Expression*, Expression*);

	~BinaryExpression() {
		if (m_value) {
			m_value->delRef();
		}
		if (m_lhs) {
			m_lhs->delRef();
		}
		if (m_rhs) {
			m_rhs->delRef();
		}
	}

	bool hasValue() const { return true; }

	inline Expression* get_lhs() {
		return m_lhs;
	}

	inline Expression* get_rhs() {
		return m_rhs;
	}

	inline char get_op() {
		return m_op;
	}

	inline Value* get_value() const {
		if (optimized) {
			return m_value;
		} else {
			return m_result;
		}
	}

	std::string debug();

	Opcode* codeGen(IRBuilder&);

	DISALLOW_COPY_AND_ASSIGN(BinaryExpression);

	bool optimized;
private:
	char m_op;
	Expression* m_lhs;
	Expression* m_rhs;
	TempValue* m_result;
	ConstantValue* m_value;
};

class NumberLiteral : public Literal {
public:
	explicit NumberLiteral(int64_t val) {
		m_value = new ConstantValue(val);
	}

	explicit NumberLiteral(double val) {
		m_value = new ConstantValue(val);
	}

	~NumberLiteral() {
		m_value->delRef();
	}

	Value* get_value() const { return m_value; };

	std::string debug(void) { return m_value->toString(); }

	DISALLOW_COPY_AND_ASSIGN(NumberLiteral);

private:
	ConstantValue* m_value;
};

class VariableDecl : public Expression {
public:
	VariableDecl(Expression* type, Expression* variable, Expression* rhs)
		: Expression(), m_type(type), m_variable(variable), m_initial_value(rhs) {
		m_type->addRef();
		m_variable->addRef();

		if (m_initial_value) {
			m_initial_value->addRef();
		}
	}

	~VariableDecl() {
		m_type->delRef();
		m_variable->delRef();

		if (m_initial_value) {
			m_initial_value->delRef();
		}
	}

	Expression* get_variable() {
		return m_variable;
	}

	Expression* get_initial_value() {
		return m_initial_value;
	}

	Opcode* codeGen(IRBuilder&);

	std::string debug() {
		return m_type->debug() + " " + m_variable->debug() + " = " + m_initial_value->debug();
	}

	DISALLOW_COPY_AND_ASSIGN(VariableDecl);

private:
	Expression* m_type;
	Expression* m_variable;
	Expression* m_initial_value;
};

class Identifier : public Expression {
public:
	explicit Identifier(CString* name) {
		m_value = new NamedValue(name);
	}

	~Identifier() {
		m_value->delRef();
	}

	bool hasValue() const { return true; }
	Value* get_value() const { return m_value; }

	std::string debug(void) {
		return m_value->toString();
	}

	DISALLOW_COPY_AND_ASSIGN(Identifier);
private:
	NamedValue* m_value;
};

class StringLiteral : public Literal {
public:
	explicit StringLiteral(CString* name) {
		m_value = new ConstantValue(name);
	}

	~StringLiteral() {
		m_value->delRef();
	}

	Value* get_value() const { return m_value; };

	std::string debug(void) {
		return m_value->toString();
	}

	DISALLOW_COPY_AND_ASSIGN(StringLiteral);
private:
	ConstantValue* m_value;
};

class TypeCreation : public Expression {
public:
	TypeCreation(Expression* type, Expression* arguments)
		: m_type(type), m_arguments(arguments) {
		m_type->addRef();
		m_arguments->addRef();
	}

	~TypeCreation() {
		m_type->delRef();
		m_arguments->delRef();
	}

	std::string debug(void) {
		return m_type->debug();
	}

	DISALLOW_COPY_AND_ASSIGN(TypeCreation);
private:
	Expression* m_type;
	Expression* m_arguments;
};

class NewBlock : public Expression {
public:
	NewBlock() { }

	Opcode* codeGen(IRBuilder&);

	std::string debug() {
		return std::string("{");
	}

	DISALLOW_COPY_AND_ASSIGN(NewBlock);
};

class EndBlock : public Expression {
public:
	EndBlock() { }

	Opcode* codeGen(IRBuilder&);

	std::string debug() {
		return std::string("}");
	}

	DISALLOW_COPY_AND_ASSIGN(EndBlock);
};

class Command : public Expression {
public:
	Command(Expression* expr)
		: m_expr(expr) {
		m_expr->addRef();
	}

	~Command() {
		m_expr->delRef();
	}

	Expression* get_expr() {
		return m_expr;
	}

	Opcode* codeGen(IRBuilder&);

	std::string debug() {
		return "echo " + m_expr->debug();
	}

	DISALLOW_COPY_AND_ASSIGN(Command);
private:
	Expression* m_expr;
};

class PreIncrement : public Expression {
public:
	PreIncrement(Expression* expr)
		: m_expr(expr) {
		m_expr->addRef();
		m_result = new TempValue();
	}

	~PreIncrement() {
		m_expr->delRef();
	}

	inline Value* get_value() const {
		return m_result;
	}

	inline Expression* get_expr() {
		return m_expr;
	}

	Opcode* codeGen(IRBuilder&);
private:
	Expression* m_expr;
	TempValue* m_result;
};

class PosIncrement : public Expression {
public:
	PosIncrement(Expression* expr)
		: m_expr(expr) {
		m_expr->addRef();
		m_result = new TempValue();
	}

	~PosIncrement() {
		m_expr->delRef();
	}

	inline Value* get_value() const {
		return m_result;
	}

	inline Expression* get_expr() {
		return m_expr;
	}

	Opcode* codeGen(IRBuilder&);
private:
	Expression* m_expr;
	TempValue* m_result;
};

class PreDecrement : public Expression {
public:
	PreDecrement(Expression* expr)
		: m_expr(expr) {
		m_expr->addRef();
		m_result = new TempValue();
	}

	~PreDecrement() {
		m_expr->delRef();
	}

	inline Expression* get_expr() {
		return m_expr;
	}

	inline Value* get_value() const {
		return m_result;
	}

	Opcode* codeGen(IRBuilder&);
private:
	Expression* m_expr;
	TempValue* m_result;
};

class PosDecrement : public Expression {
public:
	PosDecrement(Expression* expr)
		: m_expr(expr) {
		m_expr->addRef();
		m_result = new TempValue();
	}

	~PosDecrement() {
		m_expr->delRef();
	}

	inline Value* get_value() const {
		return m_result;
	}

	inline Expression* get_expr() {
		return m_expr;
	}

	Opcode* codeGen(IRBuilder&);
private:
	Expression* m_expr;
	TempValue* m_result;
};

class IfExpression : public Expression {
public:
	IfExpression(Expression* expr)
		: m_expr(expr) {
		m_expr->addRef();
	}

	~IfExpression() {
		m_expr->delRef();
	}

	inline Expression* get_expr() {
		return m_expr;
	}

	Opcode* codeGen(IRBuilder&);

private:
	Expression* m_expr;
};

class ElseIfExpression : public Expression {
public:
	ElseIfExpression(Expression* start_expr, Expression* expr)
		: m_start_expr(start_expr), m_expr(expr) {
		m_expr->addRef();
		m_start_expr->addRef();
	}

	~ElseIfExpression() {
		m_expr->delRef();
		m_start_expr->delRef();
	}

	inline Expression* get_expr() {
		return m_expr;
	}

	inline Expression* get_start_expr() {
		return m_start_expr;
	}

	Opcode* codeGen(IRBuilder&);
private:
	Expression* m_expr;
	Expression* m_start_expr;
};

class ElseExpression : public Expression {
public:
	ElseExpression() { }

	~ElseExpression() { }

	Opcode* codeGen(IRBuilder&);
};

class WhileExpression : public Expression {
public:
	WhileExpression(Expression* expr)
		: m_expr(expr) {
		m_expr->addRef();
	}

	~WhileExpression() {
		m_expr->delRef();
	}

	inline Expression* get_expr() {
		return m_expr;
	}

	Opcode* codeGen(IRBuilder&);
private:
	Expression* m_expr;
};

class EndIfExpression : public Expression {
public:
	EndIfExpression() { }

	~EndIfExpression() { }

	Opcode* codeGen(IRBuilder&);
};


class EndWhileExpression : public Expression {
public:
	EndWhileExpression(Expression* expr)
		: m_expr(expr) {
		m_expr->addRef();
	}

	~EndWhileExpression() {
		m_expr->delRef();
	}

	inline Expression* get_expr() {
		return m_expr;
	}

	Opcode* codeGen(IRBuilder&);
private:
	Expression* m_expr;
};

class StartExpr : public Expression {
public:
	StartExpr() { }

	~StartExpr() { }

	inline void set_op_num(unsigned int op_num) {
		m_op_num = op_num;
	}

	inline unsigned int get_op_num() {
		return m_op_num;
	}

	Opcode* codeGen(IRBuilder&);
private:
	unsigned int m_op_num;
};


class LogicExpression : public Expression {
public:
	LogicExpression(int op, Expression* lhs, Expression* rhs)
		: m_op(op), m_lhs(lhs), m_rhs(rhs) {
		m_lhs->addRef();
		m_rhs->addRef();
		m_result = new TempValue();
	}

	~LogicExpression() {
		m_lhs->delRef();
		m_rhs->delRef();
	}

	int get_op() {
		return m_op;
	}

	Expression* get_lhs() {
		return m_lhs;
	}

	Expression* get_rhs() {
		return m_rhs;
	}

	inline Value* get_value() const {
		return m_result;
	}

	Opcode* codeGen(IRBuilder&);
private:
	int m_op;
	Expression* m_lhs;
	Expression* m_rhs;
	TempValue* m_result;
};

}} // clever::ast

#endif // CLEVER_AST_H
