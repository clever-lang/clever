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

#ifndef CLEVER_IRBUILDER_H
#define CLEVER_IRBUILDER_H
#include <stack>
#include "ast.h"

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

	void init();
	void shutdown();

	inline VM::OpcodeList* get_opcodes() {
		return &m_opcodes;
	}

	inline void push(Opcode* opcode) {
		m_opcodes.push_back(opcode);
		/* Sets the opcode number, which is used by JMP opcodes */
		opcode->set_op_num(getOpNum());
	}

	inline unsigned int getOpNum() {
		return m_opcodes.size()-1;
	}

	inline Value* getValue(ast::Expression* expr) {
		Value* value = expr->get_value();

		if (value && value->isNamedValue()) {
			return m_symbols.get_var(value);
		}
		return value;
	}

	/* Opcode generators */
	Opcode* binaryExpression(ast::BinaryExpression*);
	Opcode* variableDecl(ast::VariableDecl*);
	Opcode* command(ast::Command*);
	Opcode* preIncrement(ast::PreIncrement*);
	Opcode* posIncrement(ast::PosIncrement*);
	Opcode* preDecrement(ast::PreDecrement*);
	Opcode* posDecrement(ast::PosDecrement*);
	Opcode* newBlock();
	Opcode* endBlock();
	Opcode* ifExpression(ast::IfExpression*);
	Opcode* elseIfExpression(ast::ElseIfExpression*);
	Opcode* elseExpression(ast::ElseExpression*);
	Opcode* endIfExpression();
	Opcode* whileExpression(ast::WhileExpression*);
	Opcode* endWhileExpression(ast::EndWhileExpression*);
	Opcode* startExpr(ast::StartExpr*);
	Opcode* logicExpression(ast::LogicExpression*);
	Opcode* breakExpression();

	DISALLOW_COPY_AND_ASSIGN(IRBuilder);
private:
	/* Opcode vector */
	VM::OpcodeList m_opcodes;
	/* Symbol table map */
	SymbolTable m_symbols;
	/* Stack used for control structures */
	JmpStack m_jmps;
};

} // clever

#endif // CLEVER_IRBUILDER_H