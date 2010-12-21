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

#include <iostream>
#include <string>
#include <vector>
#include "types.h"

namespace clever { namespace ast {

#define CLEVER_AST_PURE_VIRTUAL_MEMBERS \
	virtual Value *codeGen();           \
	virtual std::string debug();

class ExprAST {
	int m_reference;
public:
	ExprAST() : m_reference(0) { }
	virtual ~ExprAST() { }

	inline int refCount() { return m_reference; }
	inline void addRef() { ++m_reference; }
	inline int delRef() { return --m_reference; }

	/*
	 * Method for generating the expression IR
	 */
	virtual Value *codeGen() = 0;
	/*
	 * Method for debug purpose
	 */
	virtual std::string debug() = 0;
};


class TreeNode {
public:
	typedef std::vector<ExprAST*> nodeList;

	TreeNode() { }

	inline void add(ExprAST* node) { node->addRef(); nodes.push_back(node); }
	inline nodeList getNodeList() { return nodes; }
private:
	nodeList nodes;
};

class BinaryExprAST : public ExprAST {
public:
	BinaryExprAST(char op_, ExprAST* lhs, ExprAST* rhs)
		: m_op(op_), m_lhs(lhs), m_rhs(rhs) {
		m_lhs->addRef();
		m_rhs->addRef();
	}

	~BinaryExprAST() {
		if (!m_lhs->delRef()) {
			delete m_lhs;
		}
		if (!m_rhs->delRef()) {
			delete m_rhs;
		}
	}

	DISALLOW_COPY_AND_ASSIGN(BinaryExprAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	char m_op;
	ExprAST* m_lhs;
	ExprAST* m_rhs;
};

class NumberExprAST : public ExprAST {
public:
	explicit NumberExprAST(double val)
		: m_value(val) { }

	~NumberExprAST() { }

	DISALLOW_COPY_AND_ASSIGN(NumberExprAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	double m_value;
};

class VariableDeclAST : public ExprAST {
public:
	VariableDeclAST(ExprAST* type, ExprAST* variable, ExprAST* initialization)
		: m_type(type), m_variable(variable), m_initialization(initialization) {
		m_type->addRef();
		m_variable->addRef();
		m_initialization->addRef();
	}

	~VariableDeclAST() {
		if (!m_type->delRef()) {
			delete m_type;
		}
		if (!m_variable->delRef()) {
			delete m_variable;
		}
		if (m_initialization && !m_initialization->delRef()) {
			delete m_initialization;
		}
	}

	DISALLOW_COPY_AND_ASSIGN(VariableDeclAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	ExprAST* m_type;
	ExprAST* m_variable;
	ExprAST* m_initialization;
};

class IdentifierAST : public ExprAST {
public:
	explicit IdentifierAST(const std::string& name)
		: m_name(name) { }

	DISALLOW_COPY_AND_ASSIGN(IdentifierAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	const std::string m_name;
	Value* m_value;
};

class TypeCreationAST : public ExprAST {
public:
	TypeCreationAST(ExprAST* type, ExprAST* arguments)
		: m_type(type), m_arguments(arguments) {
		m_type->addRef();
		m_arguments->addRef();
	}

	~TypeCreationAST() {
		if (!m_type->delRef()) {
			delete m_type;
		}
		if (m_arguments && !m_arguments->delRef()) {
			delete m_arguments;
		}
	}

	DISALLOW_COPY_AND_ASSIGN(TypeCreationAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	ExprAST* m_type;
	ExprAST* m_arguments;
};

class NewBlockAST : public ExprAST {
public:
	NewBlockAST() { }

	DISALLOW_COPY_AND_ASSIGN(NewBlockAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
};

class EndBlockAST : public ExprAST {
public:
	EndBlockAST() { }

	DISALLOW_COPY_AND_ASSIGN(EndBlockAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
};

}} // clever::ast

#endif // CLEVER_AST_H