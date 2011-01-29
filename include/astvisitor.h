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
#include "compiler.h"

namespace clever { namespace ast {

class ASTNode;
class BinaryExpr;
class LogicExpr;
class VariableDecl;
class PosIncrement;
class PosDecrement;
class PreIncrement;
class PreDecrement;
class IfNode;
class ElseIfNode;
class WhileNode;
class FunctionCall;
class MethodCall;
class AssignStmt;
class Import;
class BreakNode;
class BlockNode;
class ArgumentList;
class FuncDeclaration;
class ReturnStmt;

#define AST_VISITOR(type) void ASTVisitor::visit(type* expr) throw()
#define AST_VISITOR_DECL(type) void visit(type* expr) throw()

/**
 * AST Visitor
 */
class ASTVisitor {
public:
	typedef std::stack<Opcode*> OpcodeStack;
	typedef std::stack<OpcodeStack> JmpStack;

	ASTVisitor() { }

	void init() throw() {
		m_ssa.beginScope();
		m_opcodes.reserve(10);
	}

	void shutdown() throw() {
		m_ssa.endScope();
	}

	~ASTVisitor() { }
	/**
	 * Builds the function arguments vector
	 */
	ValueVector* functionArgs(ast::ArgumentList*) throw();
	/**
	 * Returns the Value pointer according with value type.
	 */
	Value* getValue(ast::ASTNode*) throw();

	/**
	 * Displays the error message and exits the program
	 */
	void error(std::string) throw();
	/**
	 * Checks if two operands has compatible types to perform some operation
	 */
	bool checkCompatibleTypes(Value*, Value*) throw();
	/**
	 * Performs the constant folding and constant propagation optimization
	 */
	Value* constantFolding(int, Value*, Value*) throw();
	/**
	 * Returns the opcode list
	 */
	OpcodeList& get_opcodes() throw() {	return m_opcodes; }
	/**
	 * Returns the opcode number
	 */
	unsigned int getOpNum() const throw() {	return m_opcodes.size()-1; }
	/**
	 * Pushes the opcode to list
	 */
	void pushOpcode(Opcode* opcode) throw() {
		m_opcodes.push_back(opcode);
		/**
		 * Sets the opcode number, which is used by JMP opcodes
		 */
		opcode->set_op_num(getOpNum());
	}

	AST_VISITOR_DECL(BinaryExpr);
	AST_VISITOR_DECL(LogicExpr);
	AST_VISITOR_DECL(VariableDecl);
	AST_VISITOR_DECL(PreIncrement);
	AST_VISITOR_DECL(PosIncrement);
	AST_VISITOR_DECL(PreDecrement);
	AST_VISITOR_DECL(PosDecrement);
	AST_VISITOR_DECL(BlockNode);
	AST_VISITOR_DECL(IfNode);
	AST_VISITOR_DECL(WhileNode);
	AST_VISITOR_DECL(BreakNode);
	AST_VISITOR_DECL(FunctionCall);
	AST_VISITOR_DECL(MethodCall);
	AST_VISITOR_DECL(AssignStmt);
	AST_VISITOR_DECL(Import);
	AST_VISITOR_DECL(FuncDeclaration);
	AST_VISITOR_DECL(ReturnStmt);
private:
	OpcodeList m_opcodes;
	SSA m_ssa;
	JmpStack m_brks;

	DISALLOW_COPY_AND_ASSIGN(ASTVisitor);
};

}} // clever::ast

#endif // CLEVER_ASTVISITOR_H
