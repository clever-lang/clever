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

namespace clever { namespace ast {

#define CLEVER_AST_PURE_VIRTUAL_MEMBERS \
	virtual Value *codeGen();           \
	virtual std::string debug();

class Expression : public RefCounted {
public:
	Expression() : RefCounted(0) { }

	virtual ~Expression() { }

	virtual bool isLiteral() const { return false; }

	virtual bool hasValue() const { return false; }
	virtual Value* get_value() const { return NULL; }

	/*
	 * Method for generating the expression IR
	 */
	virtual Value* codeGen() = 0;
	/*
	 * Method for debug purpose
	 */
	virtual std::string debug() = 0;

	virtual Opcode* opcodeGen() {
		return NULL;
	}
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
	Literal() : Expression() { }
	virtual ~Literal() { }

	bool isLiteral() const { return true; }
	virtual bool hasValue() const { return true; }
	virtual Value* get_value() const { return NULL; }
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
	Value* get_value() const { return m_value; }

	Opcode* opcodeGen();
	DISALLOW_COPY_AND_ASSIGN(BinaryExpression);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	char m_op;
	bool optimized;
	Expression* m_lhs;
	Expression* m_rhs;
	TempValue* m_result;
	ConstantValue* m_value;
};

class NumberLiteral : public Literal {
public:
	explicit NumberLiteral(int64_t val)
		: Literal() {
		m_value = new ConstantValue(val);
	}

	explicit NumberLiteral(double val)
		: Literal() {
		m_value = new ConstantValue(val);
	}

	~NumberLiteral() {
		m_value->delRef();
	}
	
	Value* get_value() { return m_value; };

	DISALLOW_COPY_AND_ASSIGN(NumberLiteral);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	ConstantValue* m_value;
};

class VariableDecl : public Expression {
public:
	VariableDecl(Expression* type, Expression* variable, Expression* rhs)
		: Expression(), m_type(type), m_variable(variable), m_rhs(rhs) {
		m_type->addRef();
		m_variable->addRef();
		m_rhs->addRef();
	}

	~VariableDecl() {
		m_type->delRef();
		m_variable->delRef();
		m_rhs->delRef();
	}

	Opcode* opcodeGen();

	DISALLOW_COPY_AND_ASSIGN(VariableDecl);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	Expression* m_type;
	Expression* m_variable;
	Expression* m_rhs;
};

class Identifier : public Expression {
public:
	explicit Identifier(CString* name)
		: Expression() {
		m_value = new NamedValue(name);
	}

	~Identifier() {
		m_value->delRef();
	}
	
	bool hasValue() const { return true; }
	Value* get_value() const { return m_value; }

	DISALLOW_COPY_AND_ASSIGN(Identifier);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	NamedValue* m_value;
};

class StringLiteral : public Literal {
public:
	explicit StringLiteral(CString* name)
		: Literal() {
		m_value = new ConstantValue(name);
	}

	Value* get_value() { return m_value; };

	~StringLiteral() {
		m_value->delRef();
	}

	DISALLOW_COPY_AND_ASSIGN(StringLiteral);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	ConstantValue* m_value;
};

class TypeCreation : public Expression {
public:
	TypeCreation(Expression* type, Expression* arguments)
		: Expression(), m_type(type), m_arguments(arguments) {
		m_type->addRef();
		m_arguments->addRef();
	}

	~TypeCreation() {
		m_type->delRef();
		m_arguments->delRef();
	}

	DISALLOW_COPY_AND_ASSIGN(TypeCreation);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	Expression* m_type;
	Expression* m_arguments;
};

class NewBlock : public Expression {
public:
	NewBlock() : Expression() { }

	Opcode* opcodeGen();

	DISALLOW_COPY_AND_ASSIGN(NewBlock);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
};

class EndBlock : public Expression {
public:
	EndBlock() : Expression() { }

	Opcode* opcodeGen();

	DISALLOW_COPY_AND_ASSIGN(EndBlock);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
};

class Command : public Expression {
public:
	Command(Expression* value)
		: Expression(), m_value(value) {
		m_value->addRef();
	}

	~Command() {
		m_value->delRef();
	}

	Opcode* opcodeGen();

	DISALLOW_COPY_AND_ASSIGN(Command);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	Expression* m_value;
};

}} // clever::ast

#endif // CLEVER_AST_H
