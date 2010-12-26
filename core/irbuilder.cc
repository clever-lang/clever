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

#include "irbuilder.h"

namespace clever {

/*
 * Generates the binary expression opcode
 */
Opcode* IRBuilder::binaryExpression(ast::BinaryExpression* expr) {
	Value* lhs;
	Value* rhs;

	if (expr->optimized) {
		return NULL;
	}

	lhs = expr->get_lhs()->get_value();
	rhs = expr->get_rhs()->get_value();

	lhs->addRef();
	rhs->addRef();

	switch (expr->get_op()) {
		case '+': return new Opcode(OP_PLUS, &VM::plus_handler, lhs, rhs, expr->get_value());
		case '/': return new Opcode(OP_DIV, &VM::div_handler, lhs, rhs, expr->get_value());
		case '*': return new Opcode(OP_MULT, &VM::mult_handler, lhs, rhs, expr->get_value());
		case '-': return new Opcode(OP_MINUS, &VM::minus_handler, lhs, rhs, expr->get_value());
		case '^': return new Opcode(OP_BW_XOR, &VM::bw_xor_handler, lhs, rhs, expr->get_value());
		case '|': return new Opcode(OP_BW_OR, &VM::bw_or_handler, lhs, rhs, expr->get_value());
		case '&': return new Opcode(OP_BW_AND, &VM::bw_and_handler, lhs, rhs, expr->get_value());
	}
}

/*
 * Generates the variable declaration opcode
 */
Opcode* IRBuilder::variableDecl(ast::VariableDecl* expr) {
	ast::Expression* var_expr = expr->get_variable();
	ast::Expression* rhs_expr = expr->get_initial_value();
	Value* variable = var_expr->get_value();

	/* Check if the declaration contains initialization */
	if (rhs_expr) {
		Value* value = rhs_expr->get_value();

		variable->addRef();
		value->addRef();

		return new Opcode(OP_VAR_DECL, &VM::var_decl_handler, variable, value);
	} else {
		return new Opcode(OP_VAR_DECL, &VM::var_decl_handler, variable);
	}
}

/*
 * Generates the new block opcode
 */
Opcode* IRBuilder::newBlock() {
	return new Opcode(OP_NEW_SCOPE, &VM::new_scope_handler);
}

/*
 * Generates the end block opcode
 */
Opcode* IRBuilder::endBlock() {
	return new Opcode(OP_END_SCOPE, &VM::end_scope_handler);
}

/*
 * Generates the command opcode
 */
Opcode* IRBuilder::command(ast::Command* expr) {
	Value* value = expr->get_expr()->get_value();

	value->addRef();
	return new Opcode(OP_ECHO, &VM::echo_handler, value);
}

/*
 * Generates the pre increment opcode
 */
Opcode* IRBuilder::preIncrement(ast::PreIncrement* expr) {
	Value* value = expr->get_expr()->get_value();

	value->addRef();
	return new Opcode(OP_PRE_INC, &VM::pre_inc_handler, value, NULL, expr->get_value());
}

/*
 * Generates the pos increment opcode
 */
Opcode* IRBuilder::posIncrement(ast::PosIncrement* expr) {
	Value* value = expr->get_expr()->get_value();

	value->addRef();
	return new Opcode(OP_POS_INC, &VM::pos_inc_handler, value, NULL, expr->get_value());
}

/*
 * Generates the pre decrement opcode
 */
Opcode* IRBuilder::preDecrement(ast::PreDecrement* expr) {
	Value* value = expr->get_expr()->get_value();

	value->addRef();
	return new Opcode(OP_PRE_DEC, &VM::pre_dec_handler, value, NULL, expr->get_value());
}

/*
 * Generates the pos decrement opcode
 */
Opcode* IRBuilder::posDecrement(ast::PosDecrement* expr) {
	Value* value = expr->get_expr()->get_value();

	value->addRef();
	return new Opcode(OP_POS_DEC, &VM::pos_dec_handler, value, NULL, expr->get_value());
}

/*
 * Generates the JMPZ opcode for IF expression
 */
Opcode* IRBuilder::ifExpression(ast::IfExpression* expr) {
	Value* value = expr->get_expr()->get_value();
	Opcode* opcode = new Opcode(OP_JMPZ, &VM::jmpz_handler, value);
	Jmp jmp;

	jmp.push(opcode);
	m_jmps.push(jmp);

	value->addRef();
	return opcode;
}

/*
 * Generates a JMPZ opcode for ELSEIF expression
 */
Opcode* IRBuilder::elseIfExpression(ast::ElseIfExpression* expr) {
	Value* value = expr->get_expr()->get_value();
	Opcode* opcode = new Opcode(OP_JMPZ, &VM::jmpz_handler, value);

	m_jmps.top().top()->set_jmp_addr1(getOpNum()+2);
	m_jmps.top().push(opcode);

	value->addRef();
	return opcode;
}

/*
 * Generates a JMP opcode for ELSE expression
 */
Opcode* IRBuilder::elseExpression(ast::ElseExpression* expr) {
	Opcode* opcode = new Opcode(OP_JMP, &VM::jmp_handler);

	m_jmps.top().top()->set_jmp_addr1(getOpNum()+2);
	m_jmps.top().push(opcode);

	return opcode;
}

/*
 * Just set the jmp address of if-elsif-else to end of control structure
 */
Opcode* IRBuilder::endIfExpression(ast::EndIfExpression* expr) {
	Jmp jmp = m_jmps.top();

	while (!jmp.empty()) {
		Opcode* opcode = jmp.top();

		opcode->set_jmp_addr2(getOpNum()+1);

		jmp.pop();
	}

	m_jmps.pop();

	return NULL;
}

} // clever