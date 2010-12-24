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

namespace clever { namespace ast {

TreeNode::~TreeNode(void) {
	TreeNode::nodeList::iterator it = nodes.begin();

	while (it < nodes.end()) {
		(*it)->delRef();
		++it;
	}
}

/*
 * NumberExprAST
 */
Value* NumberExprAST::codeGen(void) {
	return m_value;
}

std::string NumberExprAST::debug(void) {
	return m_value->toString();
}

BinaryExprAST::BinaryExprAST(char op_, ExprAST* lhs, ExprAST* rhs)
		: ExprAST(), m_op(op_), m_lhs(lhs), m_rhs(rhs), m_result(NULL), m_value(NULL), optimized(false) {
	Value* tmp_lhs = lhs->codeGen();
	Value* tmp_rhs = rhs->codeGen();

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

/*
 * BinaryExprAST
 */
Opcode* BinaryExprAST::opcodeGen(void) {
	Value* lhs;
	Value* rhs;

	if (optimized) {
		return NULL;
	}

	lhs = m_lhs->codeGen();
	rhs = m_rhs->codeGen();

	lhs->addRef();
	rhs->addRef();

	switch (m_op) {
		case '+':
			return new Opcode(OP_PLUS, &VM::plus_handler, lhs, rhs, m_result);
		case '/':
			return new Opcode(OP_DIV, &VM::div_handler, lhs, rhs, m_result);
		case '*':
			return new Opcode(OP_MULT, &VM::mult_handler, lhs, rhs, m_result);
		case '-':
			return new Opcode(OP_MINUS, &VM::minus_handler, lhs, rhs, m_result);
	}
}

Value* BinaryExprAST::codeGen(void) {
	if (optimized) {
		return m_value;
	} else {
		return m_result;
	}
}

std::string BinaryExprAST::debug(void) {
	if (optimized) {
		return m_value->toString();
	} else {
		return std::string(m_lhs->debug() + " " + m_op + " " + m_rhs->debug());
	}
}

/*
 * VariableDeclAST
 */
Opcode* VariableDeclAST::opcodeGen(void) {
	/* Check if the declaration contains initialization */
	if (m_rhs) {
		Value* variable = m_variable->codeGen();
		Value* value = m_rhs->codeGen();

		variable->addRef();
		value->addRef();

		return new Opcode(OP_VAR_DECL, &VM::var_decl_handler, variable, value);
	} else {
		return new Opcode(OP_VAR_DECL, &VM::var_decl_handler, m_variable->codeGen());
	}
}

Value* VariableDeclAST::codeGen(void) {
	return NULL;
}

std::string VariableDeclAST::debug(void) {
	return m_type->debug() + " " + m_variable->debug() + " = " + m_rhs->debug();
}

/*
 * IdentifierAST
 */
Value* IdentifierAST::codeGen(void) {
	return m_value;
}

std::string IdentifierAST::debug(void) {
	return m_value->toString();
}

/*
 * StringLiteralAST
 */
Value* StringLiteralAST::codeGen(void) {
	return m_value;
}

std::string StringLiteralAST::debug(void) {
	return m_value->toString();
}

/*
 * TypeCreationAST
 */
Value* TypeCreationAST::codeGen(void) {
	return NULL;
}

std::string TypeCreationAST::debug(void) {
	return m_type->debug();
}

/*
 * NewBlockAST
 */
Opcode* NewBlockAST::opcodeGen(void) {
	return new Opcode(OP_NEW_SCOPE, &VM::new_scope_handler);
}

Value* NewBlockAST::codeGen(void) {
	return NULL;
}

std::string NewBlockAST::debug(void) {
	return std::string("{");
}

/*
 * EndBlockAST
 */
Opcode* EndBlockAST::opcodeGen(void) {
	return new Opcode(OP_END_SCOPE, &VM::end_scope_handler);
}

Value* EndBlockAST::codeGen(void) {
	return NULL;
}

std::string EndBlockAST::debug(void) {
	return std::string("}");
}

/*
 * CommandAST
 */
Value* CommandAST::codeGen(void) {
	return NULL;
}

Opcode* CommandAST::opcodeGen(void) {
	Value* value = m_value->codeGen();
	value->addRef();
	return new Opcode(OP_ECHO, &VM::echo_handler, value);
}

std::string CommandAST::debug(void) {
	return m_command->debug() + " " + m_value->debug();
}

}} // clever::ast
