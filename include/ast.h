/*
 * Clever language
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

#include <string>
#include <vector>
#include "types.h"
#include "values.h"
#include "cstring.h"
#include "refcounted.h"
#include "irbuilder.h"

namespace clever {

class Opcode;

} // clever

namespace clever { namespace ast {

/*
 * Operators
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

class Expression;

class NO_INIT_VTABLE Expression : public RefCounted {
public:
	Expression()
		: RefCounted(0), m_optimized(false) { }

	virtual ~Expression() { }

	virtual bool isLiteral() const { return false; }

	virtual bool hasValue() const { return false; }

	inline bool isOptimized() const { return m_optimized; }

	inline void set_optimized(bool value) { m_optimized = value; }
	/*
	 * Method for getting the value representation
	 */
	virtual Value* get_value() const throw() { return NULL; }
	/*
	 * Method for generating the expression IR
	 */
	virtual Opcode* codeGen(IRBuilder& builder) throw() { return NULL; };

	DISALLOW_COPY_AND_ASSIGN(Expression);
private:
	bool m_optimized;
};

class TreeNode {
public:
	typedef std::vector<Expression*> nodeList;

	TreeNode() { }
	~TreeNode() { }

	void clear() throw();
	inline void add(Expression* node) throw() {
		node->addRef();
		nodes.push_back(node);
	}
	inline nodeList& getNodeList() throw() {
		return nodes;
	}

	DISALLOW_COPY_AND_ASSIGN(TreeNode);
private:
	nodeList nodes;
};


class Literal : public Expression {
public:
	Literal() { }
	virtual ~Literal() { }

	bool isLiteral() const { return true; }
	virtual bool hasValue() const { return true; }
	virtual Value* get_value() const throw() = 0;

	DISALLOW_COPY_AND_ASSIGN(Literal);
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

	inline Value* get_value() const throw() { return m_value; };

	DISALLOW_COPY_AND_ASSIGN(NumberLiteral);
private:
	ConstantValue* m_value;
};

class BinaryExpression : public Expression {
public:
	BinaryExpression(int op, Expression* lhs, Expression* rhs)
		: m_op(op), m_lhs(lhs), m_rhs(rhs), m_value(NULL), m_result(NULL) {
		m_lhs->addRef();
		m_rhs->addRef();
	}

	BinaryExpression(int op, Expression* rhs)
		: m_op(op), m_lhs(NULL), m_rhs(rhs), m_value(NULL), m_result(NULL) {
		m_lhs = new NumberLiteral(int64_t(0));
		m_lhs->addRef();
		m_rhs->addRef();
	}

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

	inline Expression* get_lhs() const {
		return m_lhs;
	}

	inline Expression* get_rhs() const {
		return m_rhs;
	}

	inline int get_op() const {
		return m_op;
	}

	inline Value* get_value() const throw() {
		if (isOptimized()) {
			return m_value;
		} else {
			return m_result;
		}
	}

	inline void set_result(ConstantValue* value) {
		m_value = value;
	}

	inline void set_result(TempValue* value) {
		m_result = value;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.binaryExpression(this);
	}

	DISALLOW_COPY_AND_ASSIGN(BinaryExpression);
private:
	int m_op;
	Expression* m_lhs;
	Expression* m_rhs;
	ConstantValue* m_value;
	TempValue* m_result;
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

	Expression* get_variable() const {
		return m_variable;
	}

	Expression* get_initial_value() const {
		return m_initial_value;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.variableDecl(this);
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
		m_name = name;
	}

	~Identifier() {
		m_value->delRef();
	}

	bool hasValue() const { return true; }
	Value* get_value() const throw() { return m_value; }
	CString* get_name() const { return m_name; }

	DISALLOW_COPY_AND_ASSIGN(Identifier);
private:
	NamedValue* m_value;
	CString* m_name;
};

class StringLiteral : public Literal {
public:
	explicit StringLiteral(CString* name) {
		m_value = new ConstantValue(name);
	}

	~StringLiteral() {
		m_value->delRef();
	}

	Value* get_value() const throw() { return m_value; };

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

	DISALLOW_COPY_AND_ASSIGN(TypeCreation);
private:
	Expression* m_type;
	Expression* m_arguments;
};

class NewBlock : public Expression {
public:
	NewBlock() { }

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.newBlock();
	}

	DISALLOW_COPY_AND_ASSIGN(NewBlock);
};

class EndBlock : public Expression {
public:
	EndBlock() { }

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.endBlock();
	}

	DISALLOW_COPY_AND_ASSIGN(EndBlock);
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

	inline Value* get_value() const throw() {
		return m_result;
	}

	inline Expression* get_expr() const {
		return m_expr;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.preIncrement(this);
	}

	DISALLOW_COPY_AND_ASSIGN(PreIncrement);
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

	inline Value* get_value() const throw() {
		return m_result;
	}

	inline Expression* get_expr() const {
		return m_expr;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.posIncrement(this);
	}

	DISALLOW_COPY_AND_ASSIGN(PosIncrement);
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

	inline Expression* get_expr() const {
		return m_expr;
	}

	inline Value* get_value() const throw() {
		return m_result;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.preDecrement(this);
	}

	DISALLOW_COPY_AND_ASSIGN(PreDecrement);
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

	inline Value* get_value() const throw() {
		return m_result;
	}

	inline Expression* get_expr() const {
		return m_expr;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.posDecrement(this);
	}

	DISALLOW_COPY_AND_ASSIGN(PosDecrement);
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

	inline Expression* get_expr() const {
		return m_expr;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.ifExpression(this);
	}

	DISALLOW_COPY_AND_ASSIGN(IfExpression);
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

	inline Expression* get_expr() const {
		return m_expr;
	}

	inline Expression* get_start_expr() const {
		return m_start_expr;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.elseIfExpression(this);
	}

	DISALLOW_COPY_AND_ASSIGN(ElseIfExpression);
private:
	Expression* m_start_expr;
	Expression* m_expr;
};

class ElseExpression : public Expression {
public:
	ElseExpression() { }

	~ElseExpression() { }

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.elseExpression(this);
	}

	DISALLOW_COPY_AND_ASSIGN(ElseExpression);
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

	inline Expression* get_expr() const {
		return m_expr;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.whileExpression(this);
	}

	DISALLOW_COPY_AND_ASSIGN(WhileExpression);
private:
	Expression* m_expr;
};

class EndIfExpression : public Expression {
public:
	EndIfExpression() { }

	~EndIfExpression() { }

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.endIfExpression();
	}

	DISALLOW_COPY_AND_ASSIGN(EndIfExpression);
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

	inline Expression* get_expr() const {
		return m_expr;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.endWhileExpression(this);
	}

	DISALLOW_COPY_AND_ASSIGN(EndWhileExpression);
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

	inline unsigned int get_op_num() const {
		return m_op_num;
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.startExpr(this);
	}

	DISALLOW_COPY_AND_ASSIGN(StartExpr);
private:
	unsigned int m_op_num;
};


class LogicExpression : public Expression {
public:
	LogicExpression(int op, Expression* lhs, Expression* rhs)
		: m_op(op), m_lhs(lhs), m_rhs(rhs), m_result(NULL), m_value(NULL) {
		m_lhs->addRef();
		m_rhs->addRef();
	}

	~LogicExpression() {
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

	inline int get_op() const {
		return m_op;
	}

	inline Expression* get_lhs() const {
		return m_lhs;
	}

	inline Expression* get_rhs() const {
		return m_rhs;
	}

	inline void set_result(ConstantValue* value) {
		m_value = value;
	}

	inline void set_result(TempValue* value) {
		m_result = value;
	}

	inline Value* get_value() const throw() {
		if (isOptimized()) {
			return m_value;
		} else {
			return m_result;
		}
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.logicExpression(this);
	}

	DISALLOW_COPY_AND_ASSIGN(LogicExpression);
private:
	int m_op;
	Expression* m_lhs;
	Expression* m_rhs;
	TempValue* m_result;
	Value* m_value;
};

class BreakExpression : public Expression {
public:
	BreakExpression() { }

	~BreakExpression() { }

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.breakExpression();
	}

	DISALLOW_COPY_AND_ASSIGN(BreakExpression);
};

class ArgumentList : public Expression {
public:
	ArgumentList() { }

	~ArgumentList();

	inline void push(Expression* expr) {
		expr->addRef();
		m_args.push_back(expr);
	}

	inline Arguments* get_args() throw() {
		return &m_args;
	}

	DISALLOW_COPY_AND_ASSIGN(ArgumentList);
private:
	Value* m_value;
	Arguments m_args;
};

class FunctionCall : public Expression {
public:
	FunctionCall(Expression* name)
		: m_name(name), m_args(NULL) {
		m_name->addRef();
	}
	FunctionCall(Expression* name, Expression* args)
		: m_name(name), m_args(args) {
		m_name->addRef();
		m_args->addRef();
	}

	~FunctionCall() {
		m_name->delRef();
		if (m_args) {
			m_args->delRef();
		}
	}

	inline Value* get_value() const throw() {
		return m_name->get_value();
	}

	inline Arguments* get_args() throw() {
		ArgumentList* args;

		if (!m_args) {
			return NULL;
		}
		args = static_cast<ArgumentList*>(m_args);
		return args->get_args();
	}

	inline Opcode* codeGen(IRBuilder& builder) throw() {
		return builder.functionCall(this);
	}

	DISALLOW_COPY_AND_ASSIGN(FunctionCall);
private:
	Expression* m_name;
	Expression* m_args;
};

}} // clever::ast

#endif // CLEVER_AST_H
