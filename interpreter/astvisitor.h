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

#ifndef CLEVER_ASTVISITOR_H
#define CLEVER_ASTVISITOR_H

#include "vm/vm.h"
#include "compiler/ssa.h"
#include "vm/opcode.h"

namespace clever { namespace ast {

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

#define AST_VISITOR(type, exprtype) void type::visit(exprtype* const expr) throw()
#define AST_VISITOR_DECL_VIRTUAL(type) virtual void visit(type* const expr) throw() = 0
#define AST_VISITOR_DECL(type) void visit(type* const expr) throw()

/**
 * AST Visitor
 */
class NO_INIT_VTABLE ASTVisitor {
public:
	ASTVisitor() { }
	virtual ~ASTVisitor() { }

	virtual void init() throw() = 0;
	virtual void shutdown() throw() = 0;

	AST_VISITOR_DECL_VIRTUAL(BinaryExpr);
	AST_VISITOR_DECL_VIRTUAL(LogicExpr);
	AST_VISITOR_DECL_VIRTUAL(VariableDecl);
	AST_VISITOR_DECL_VIRTUAL(PreIncrement);
	AST_VISITOR_DECL_VIRTUAL(PosIncrement);
	AST_VISITOR_DECL_VIRTUAL(PreDecrement);
	AST_VISITOR_DECL_VIRTUAL(PosDecrement);
	AST_VISITOR_DECL_VIRTUAL(BlockNode);
	AST_VISITOR_DECL_VIRTUAL(IfExpr);
	AST_VISITOR_DECL_VIRTUAL(WhileExpr);
	AST_VISITOR_DECL_VIRTUAL(BreakNode);
	AST_VISITOR_DECL_VIRTUAL(FunctionCall);
	AST_VISITOR_DECL_VIRTUAL(MethodCall);
	AST_VISITOR_DECL_VIRTUAL(AssignExpr);
	AST_VISITOR_DECL_VIRTUAL(ImportStmt);
	AST_VISITOR_DECL_VIRTUAL(FuncDeclaration);
	AST_VISITOR_DECL_VIRTUAL(ClassDeclaration);
	AST_VISITOR_DECL_VIRTUAL(ReturnStmt);
private:
	DISALLOW_COPY_AND_ASSIGN(ASTVisitor);
};

}} // clever::ast

#endif // CLEVER_ASTVISITOR_H
