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
 
#ifndef CLEVER_CGVISITOR_H
#define CLEVER_CGVISITOR_H

#include "compiler/symboltable.h"
#include "vm/opcode.h"
#include "interpreter/astvisitor.h"

namespace clever { namespace ast {

/**
 * CodeGen Visitor
 */
class CodeGenVisitor : public ASTVisitor {
public:
	typedef std::stack<Opcode*> OpcodeStack;
	typedef std::stack<OpcodeStack> JmpStack;
	typedef std::stack<Function*> FuncDeclStack;

	CodeGenVisitor()
		: m_interactive(false) {
		//g_symtable.beginScope();		
	}
	~CodeGenVisitor() {
		//g_symtable.endScope();	
	}

	void init() throw() {
		m_opcodes.clear();
		m_opcodes.reserve(10);
	}

	void shutdown() throw() { }
	
	/**
	 * Set the interactive mode
	 */
	void setInteractive() throw() { m_interactive = true; }
	/**
	 * Returns the interactive mode state
	 */
	bool isInteractive() throw() { return m_interactive; }

	/**
	 * Returns the opcode list
	 */
	OpcodeList& getOpcodes() throw() { return m_opcodes; }

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
	AST_VISITOR_DECL(ForExpr);
	AST_VISITOR_DECL(BreakNode);
	AST_VISITOR_DECL(FunctionCall);
	AST_VISITOR_DECL(MethodCall);
	AST_VISITOR_DECL(AssignExpr);
	AST_VISITOR_DECL(ImportStmt);
	AST_VISITOR_DECL(FuncDeclaration);
	AST_VISITOR_DECL(ClassDeclaration);
	AST_VISITOR_DECL(ReturnStmt);

private:
	bool m_interactive;
	OpcodeList m_opcodes;
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
		opcode->setOpNum(getOpNum());

		return opcode;
	}

	/**
	 * Returns the opcode number
	 */
	unsigned int getOpNum() const throw() {	return m_opcodes.size()-1; }

	DISALLOW_COPY_AND_ASSIGN(CodeGenVisitor);
};

}} // clever::ast

#endif /* CLEVER_CGVSITIOR_H */
