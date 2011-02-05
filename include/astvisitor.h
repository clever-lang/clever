/*
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
 *
 * $Id$
 */

#ifndef CLEVER_ASTVISITOR_H
#define CLEVER_ASTVISITOR_H

#include "vm.h"
#include "ssa.h"
#include "opcode.h"

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
class AssignStmt;
class ImportStmt;
class BreakNode;
class BlockNode;
class ArgumentList;
class FuncDeclaration;
class ReturnStmt;

#define AST_VISITOR(type, exprtype) void type::visit(exprtype* expr) throw()
#define AST_VISITOR_DECL_VIRTUAL(type) virtual void visit(type* expr) throw() = 0
#define AST_VISITOR_DECL(type) void visit(type* expr) throw()

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
	AST_VISITOR_DECL_VIRTUAL(AssignStmt);
	AST_VISITOR_DECL_VIRTUAL(ImportStmt);
	AST_VISITOR_DECL_VIRTUAL(FuncDeclaration);
	AST_VISITOR_DECL_VIRTUAL(ReturnStmt);
private:
	DISALLOW_COPY_AND_ASSIGN(ASTVisitor);
};

/**
 * CodeGen Visitor
 */
class CodeGenVisitor : public ASTVisitor {
public:
	typedef std::stack<Opcode*> OpcodeStack;
	typedef std::stack<OpcodeStack> JmpStack;
	typedef std::stack<Function*> FuncDeclStack;

	CodeGenVisitor() {}
	~CodeGenVisitor() {}

	void init() throw() {
		m_ssa.beginScope();
		m_opcodes.reserve(10);
	}

	void shutdown() throw() {
		m_ssa.endScope();
	}

	/**
	 * Returns the opcode list
	 */
	OpcodeList& get_opcodes() throw() {	return m_opcodes; }

	/**
	 * Builds the function arguments vector
	 */
	ValueVector* functionArgs(ArgumentList*) throw();

	/**
	 * Returns the Value pointer according with value type.
	 */
	Value* getValue(ASTNode*) throw();

	AST_VISITOR_DECL(BinaryExpr);
	AST_VISITOR_DECL(LogicExpr);
	AST_VISITOR_DECL(VariableDecl);
	AST_VISITOR_DECL(PreIncrement);
	AST_VISITOR_DECL(PosIncrement);
	AST_VISITOR_DECL(PreDecrement);
	AST_VISITOR_DECL(PosDecrement);
	AST_VISITOR_DECL(BlockNode);
	AST_VISITOR_DECL(IfExpr);
	AST_VISITOR_DECL(WhileExpr);
	AST_VISITOR_DECL(BreakNode);
	AST_VISITOR_DECL(FunctionCall);
	AST_VISITOR_DECL(MethodCall);
	AST_VISITOR_DECL(AssignStmt);
	AST_VISITOR_DECL(ImportStmt);
	AST_VISITOR_DECL(FuncDeclaration);
	AST_VISITOR_DECL(ReturnStmt);

private:
	OpcodeList m_opcodes;
	SSA m_ssa;
	JmpStack m_brks;
	FuncDeclStack m_funcs;

	/**
	 * Output an opcode.
	 */
	Opcode* emit(Opcodes type, VM::opcode_handler handler, Value* op1 = NULL, Value* op2 = NULL, Value* result = NULL) throw() {
		Opcode* opcode = new Opcode(type, handler, op1, op2, result);
		m_opcodes.push_back(opcode);
		/**
		 * Sets the opcode number, which is used by JMP opcodes
		 */
		opcode->set_op_num(getOpNum());

		return opcode;
	}

	/**
	 * Returns the opcode number
	 */
	unsigned int getOpNum() const throw() {	return m_opcodes.size()-1; }

	DISALLOW_COPY_AND_ASSIGN(CodeGenVisitor);
};

}} // clever::ast

#endif // CLEVER_ASTVISITOR_H
