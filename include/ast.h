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
#include "types.h"

namespace Clever { namespace Ast {

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

class BinaryExprAST : public ExprAST {
	char op;
	ExprAST *LHS, *RHS;
	std::string value;
public:
	BinaryExprAST(char op_, ExprAST *lhs, ExprAST *rhs)
		: op(op_), LHS(lhs), RHS(rhs) { }
		
	~BinaryExprAST() {
		delete LHS;
		delete RHS;
	}

	virtual Value *codeGen();
	virtual std::string debug();
};

class NumberExprAST : public ExprAST {
	double value;
public:
	NumberExprAST(double val)
		: value(val) { }
		
	virtual Value *codeGen();
	virtual std::string debug();
};

}} // Clever::Ast

#endif // CLEVER_AST_H