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

class Identifier;
class Constant;
class ASTNode;
class BinaryExpr;
class VariableDecl;
class IfExpr;
class WhileExpr;
class ForExpr;
class FunctionCall;
class MethodCall;
class AssignExpr;
class ImportStmt;
class BreakNode;
class BlockNode;
class ASTNodes;
class ArgumentList;
class FuncDeclaration;
class ClassDeclaration;
class ReturnStmt;
class TypeCreation;
class UnaryExpr;
class AliasStmt;
class RegexPattern;
class Subscript;

#define AST_VISITOR(type, exprtype) void type::visit(exprtype* const expr)
#define AST_VISITOR_DECL_VIRTUAL(type) virtual void visit(type* const expr) = 0
#define AST_VISITOR_DECL(type) void visit(type* const expr)

#define AST_VISITOR_DECLARATION(V) \
	V(BinaryExpr); \
	V(RegexPattern); \
	V(Subscript); \
	V(Constant); \
	V(AliasStmt); \
	V(UnaryExpr); \
	V(VariableDecl); \
	V(BlockNode); \
	V(ASTNodes); \
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

	virtual void init() = 0;
	virtual void shutdown() = 0;
private:
	DISALLOW_COPY_AND_ASSIGN(ASTVisitor);
};

}} // clever::ast

#endif // CLEVER_ASTVISITOR_H
