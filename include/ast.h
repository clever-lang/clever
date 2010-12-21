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

namespace clever { namespace ast {

#define CLEVER_AST_PURE_VIRTUAL_MEMBERS \
	virtual Value *codeGen();           \
	virtual std::string debug();

class ExprAST {
public:
	virtual ~ExprAST() { }

	/*
	 * Method for generating the expression IR
	 */
	virtual Value *codeGen() = 0;
	/*
	 * Method for debug purpose
	 */
	virtual std::string debug() = 0;
};

typedef std::vector<clever::ast::ExprAST*> AstList;

class BinaryExprAST : public ExprAST {
public:
	BinaryExprAST(char op_, ExprAST* lhs, ExprAST* rhs)
		: op(op_), LHS(lhs), RHS(rhs) { }

	~BinaryExprAST() {
		delete LHS;
		delete RHS;
	}

	DISALLOW_COPY_AND_ASSIGN(BinaryExprAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	char op;
	ExprAST* LHS;
	ExprAST* RHS;
	std::string value;
};

class NumberExprAST : public ExprAST {
public:
	explicit NumberExprAST(double val)
		: value(val) { }

	DISALLOW_COPY_AND_ASSIGN(NumberExprAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	double value;
};

class VariableDeclAST : public ExprAST {
public:
	VariableDeclAST(ExprAST* type_, ExprAST* variable_, ExprAST* initialization_)
		: type(type_), variable(variable_), initialization(initialization_) { }

	~VariableDeclAST() {
		delete type;
		delete variable;

		if (initialization) {
			delete initialization;
		}
	}

	DISALLOW_COPY_AND_ASSIGN(VariableDeclAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	ExprAST* type;
	ExprAST* variable;
	ExprAST* initialization;
};

class IdentifierAST : public ExprAST {
public:
	explicit IdentifierAST(const std::string& name_)
		: name(name_) { }

	DISALLOW_COPY_AND_ASSIGN(IdentifierAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	const std::string name;
	Value* value;
};

class TypeCreationAST : public ExprAST {
public:
	TypeCreationAST(ExprAST* type_, ExprAST* arguments_)
		: type(type_), arguments(arguments_) { }

	~TypeCreationAST() {
		delete type;
	}

	DISALLOW_COPY_AND_ASSIGN(TypeCreationAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	ExprAST* type;
	ExprAST* arguments;
};

}} // clever::ast

#endif // CLEVER_AST_H