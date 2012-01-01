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

#include "vm/vm.h"
#include "compiler/symboltable.h"
#include "vm/opcode.h"

namespace clever { namespace ast {

class Identifier;
class ASTNode;
class BinaryExpr;
class LogicExpr;
class VariableDecl;
class PosIncrement;
class PosDecrement;
class PreIncrement;
class PreDecrement;
class IfExpr;
class WhileExpr;
class ForExpr;
class FunctionCall;
class MethodCall;
class AssignExpr;
class ImportStmt;
class BreakNode;
class BlockNode;
class ArgumentList;
class FuncDeclaration;
class ClassDeclaration;
class ReturnStmt;
class TypeCreation;

#define AST_VISITOR(type, exprtype) void type::visit(exprtype* const expr) throw()
#define AST_VISITOR_DECL_VIRTUAL(type) virtual void visit(type* const expr) throw() = 0
#define AST_VISITOR_DECL(type) void visit(type* const expr) throw()

#define AST_VISITOR_DECLARATION(V) \
	V(BinaryExpr); \
	V(LogicExpr); \
	V(VariableDecl); \
	V(PreIncrement); \
	V(PosIncrement); \
	V(PreDecrement); \
	V(PosDecrement); \
	V(BlockNode); \
	V(IfExpr); \
	V(WhileExpr); \
	V(ForExpr); \
	V(BreakNode); \
	V(FunctionCall); \
	V(MethodCall); \
	V(AssignExpr); \
	V(ImportStmt); \
	V(FuncDeclaration); \
	V(ClassDeclaration); \
	V(ReturnStmt); \
	V(ArgumentList); \
	V(Identifier); \
	V(TypeCreation)

/**
 * AST Visitor
 */
class NO_INIT_VTABLE ASTVisitor {
public:
	ASTVisitor() { }
	virtual ~ASTVisitor() { }
	
	AST_VISITOR_DECLARATION(AST_VISITOR_DECL_VIRTUAL);

	virtual void init() throw() = 0;
	virtual void shutdown() throw() = 0;
private:
	DISALLOW_COPY_AND_ASSIGN(ASTVisitor);
};

}} // clever::ast

#endif // CLEVER_ASTVISITOR_H
