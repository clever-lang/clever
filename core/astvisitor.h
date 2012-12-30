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

#ifndef CLEVER_ASTVISITOR_H
#define CLEVER_ASTVISITOR_H

namespace clever { namespace ast {

class Node;
class NodeArray;
class Block;
class Assignment;
class VariableDecl;
class Arithmetic;
class FunctionDecl;
class FunctionCall;
class While;
class If;
class IntLit;
class DoubleLit;
class StringLit;
class Ident;
class Return;

class Visitor {
public:
	Visitor() {}
	virtual ~Visitor() {}

	virtual void visit(Node* node) {}
	virtual void visit(NodeArray* node) {}
	virtual void visit(Block* node) {}
	virtual void visit(Assignment* node) {}
	virtual void visit(VariableDecl* node) {}
	virtual void visit(Arithmetic* node) {}
	virtual void visit(FunctionDecl* node) {}
	virtual void visit(FunctionCall* node) {}
	virtual void visit(While* node) {}
	virtual void visit(If* node) {}
	virtual void visit(IntLit* node) {}
	virtual void visit(DoubleLit* node) {}
	virtual void visit(StringLit* node) {}
	virtual void visit(Ident* node) {}
	virtual void visit(Return* node) {}
};

}} // clever::ast

#endif // CLEVER_ASTVISITOR_H
