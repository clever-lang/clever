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

#include <sstream>
#include "ast.h"
#include "compiler.h"
#include "opcodes.h"
#include "vm.h"
#include "irbuilder.h"

namespace clever { namespace ast {

TreeNode::~TreeNode(void) {
	TreeNode::nodeList::iterator it = nodes.begin();

	/* Remove the AST nodes */
	while (it < nodes.end()) {
		(*it)->delRef();
		++it;
	}
}

/*
 * BinaryExpression
 */
BinaryExpression::BinaryExpression(char op_, Expression* lhs, Expression* rhs)
		: m_op(op_), m_lhs(lhs), m_rhs(rhs), m_result(NULL), m_value(NULL), optimized(false) {
	Value* tmp_lhs = lhs->get_value();
	Value* tmp_rhs = rhs->get_value();

	m_rhs->addRef();
	m_lhs->addRef();

	if (!Compiler::checkCompatibleTypes(tmp_lhs, tmp_rhs)) {
		Compiler::error("Type mismatch!");
	}

	/* Checking if we can perform constant folding optimization */
	if (tmp_lhs->isConst() && tmp_rhs->isConst()) {
		m_value = Compiler::constantFolding(m_op, tmp_lhs, tmp_rhs);
	}
	if (m_value) {
		/* No opcode must be generated */
		optimized = true;

		m_rhs->delRef();
		m_lhs->delRef();
		m_rhs = m_lhs = NULL;
	} else {
		m_result = new TempValue();
	}
}

Opcode* BinaryExpression::codeGen(IRBuilder& builder) {
	return builder.binaryExpression(this);
}

std::string BinaryExpression::debug(void) {
	if (optimized) {
		return m_value->toString();
	} else {
		return std::string(m_lhs->debug() + " " + m_op + " " + m_rhs->debug());
	}
}

/*
 * VariableDecl
 */
Opcode* VariableDecl::codeGen(IRBuilder& builder) {
	return builder.variableDecl(this);
}

/*
 * NewBlock
 */
Opcode* NewBlock::codeGen(IRBuilder& builder) {
	return builder.newBlock();
}

/*
 * EndBlock
 */
Opcode* EndBlock::codeGen(IRBuilder& builder) {
	return builder.endBlock();
}

/*
 * Command
 */
Opcode* Command::codeGen(IRBuilder& builder) {
	return builder.command(this);
}

/*
 * PreIncrement
 */
Opcode* PreIncrement::codeGen(IRBuilder& builder) {
	return builder.preIncrement(this);
}

/*
 * PosIncrement
 */
Opcode* PosIncrement::codeGen(IRBuilder& builder) {
	return builder.posIncrement(this);
}

/*
 * PosDecrement
 */
Opcode* PreDecrement::codeGen(IRBuilder& builder) {
	return builder.preDecrement(this);
}

/*
 * PosDecrement
 */
Opcode* PosDecrement::codeGen(IRBuilder& builder) {
	return builder.posDecrement(this);
}

/*
 * IfExpression
 */
Opcode* IfExpression::codeGen(IRBuilder& builder) {
	return builder.ifExpression(this);
}

/*
 * ElseIfExpression
 */
Opcode* ElseIfExpression::codeGen(IRBuilder& builder) {
	return builder.elseIfExpression(this);
}

/*
 * ElseExpression
 */
Opcode* ElseExpression::codeGen(IRBuilder& builder) {
	return builder.elseExpression(this);
}

/*
 * EndIfExpression
 */
Opcode* EndIfExpression::codeGen(IRBuilder& builder) {
	return builder.endIfExpression();
}

/*
 * StartLoop
 */
Opcode* StartLoop::codeGen(IRBuilder& builder) {
	return builder.startLoop(this);
}

/*
 * WhileExpression
 */
Opcode* WhileExpression::codeGen(IRBuilder& builder) {
	return builder.whileExpression(this);
}

/*
 * EndWhileExpression
 */
Opcode* EndWhileExpression::codeGen(IRBuilder& builder) {
	return builder.endWhileExpression(this);
}

Opcode* LogicExpression::codeGen(IRBuilder& builder) {
	return builder.logicExpression(this);
}

}} // clever::ast
