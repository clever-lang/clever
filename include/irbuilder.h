/*
 * Clever language
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

#ifndef CLEVER_IRBUILDER_H
#define CLEVER_IRBUILDER_H
#include <stack>
#include "vm.h"
#include "opcode.h"
#include "ssa.h"

namespace clever { namespace ast {

class Expression;
class BinaryExpression;
class VariableDecl;
class PosIncrement;
class PosDecrement;
class PreIncrement;
class PreDecrement;
class IfExpression;
class ElseIfExpression;
class ElseExpression;
class WhileExpression;
class EndWhileExpression;
class StartExpr;
class LogicExpression;
class FunctionCall;
class MethodCall;
class Assignment;

typedef std::vector<Expression*> Arguments;

}} // clever::ast

namespace clever {

class Opcode;
class Value;

/**
 * Opcode builder
 */
class IRBuilder {
public:
	typedef std::stack<Opcode*> Jmp;
	typedef std::stack<Jmp> JmpStack;

	IRBuilder() { }

	~IRBuilder() { }

	void init() throw();
	void shutdown() throw();

	VM::OpcodeList* get_opcodes() throw() {
		return &m_opcodes;
	}

	void push(Opcode* opcode) throw() {
		m_opcodes.push_back(opcode);
		/* Sets the opcode number, which is used by JMP opcodes */
		opcode->set_op_num(getOpNum());
	}

	unsigned int getOpNum() const throw() {
		return m_opcodes.size()-1;
	}

	Value* getValue(ast::Expression*) throw();
	ValueVector* functionArgs(const ast::Arguments*) throw();

	/* Opcode generators */
	Opcode* binaryExpression(ast::BinaryExpression*) throw();
	Opcode* variableDecl(ast::VariableDecl*) throw();
	Opcode* preIncrement(ast::PreIncrement*) throw();
	Opcode* posIncrement(ast::PosIncrement*) throw();
	Opcode* preDecrement(ast::PreDecrement*) throw();
	Opcode* posDecrement(ast::PosDecrement*) throw();
	Opcode* newBlock() throw();
	Opcode* endBlock() throw();
	Opcode* ifExpression(ast::IfExpression*) throw();
	Opcode* elseIfExpression(ast::ElseIfExpression*) throw();
	Opcode* elseExpression(ast::ElseExpression*) throw();
	Opcode* endIfExpression() throw();
	Opcode* whileExpression(ast::WhileExpression*) throw();
	Opcode* endWhileExpression(ast::EndWhileExpression*) throw();
	Opcode* startExpr(ast::StartExpr*) throw();
	Opcode* logicExpression(ast::LogicExpression*) throw();
	Opcode* breakExpression() throw();
	Opcode* functionCall(ast::FunctionCall*) throw();
	Opcode* methodCall(ast::MethodCall*) throw();
	Opcode* assignment(ast::Assignment*) throw();

	DISALLOW_COPY_AND_ASSIGN(IRBuilder);
private:
	/* Opcode vector */
	VM::OpcodeList m_opcodes;
	/* SSA form */
	SSA m_ssa;
	/* Stack used for control structures */
	JmpStack m_jmps;
	/* Stack used for break in loops */
	JmpStack m_brks;
};

} // clever

#endif // CLEVER_IRBUILDER_H