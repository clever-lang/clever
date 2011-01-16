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

#include "irbuilder.h"
#include "compiler.h"
#include "ssa.h"
#include "value.h"
#include "typetable.h"

namespace clever {

void IRBuilder::init() throw() {
	/* Initializes global scope */
	m_ssa.newBlock();

	/* Reserve space for 10 opcodes */
	m_opcodes.reserve(10);
}

void IRBuilder::shutdown() throw() {
	/* Pop global scope */
	m_ssa.endBlock();
}

/**
 * Return the Value pointer related to value type
 */
Value* IRBuilder::getValue(ast::Expression* expr) throw() {
	Value* value = expr->get_value();

	if (value && value->hasName()) {
		Value* var = m_ssa.fetchVar(value);

		/**
		 * If the variable is found, we should use its pointer instead of
		 * fetching on runtime
		 */
		if (EXPECTED(var != NULL)) {
			return var;
		}
		Compiler::error("Inexistent variable!");
	}
	return value;
}

/**
 * Generates the binary expression opcode
 */
Opcode* IRBuilder::binaryExpression(ast::BinaryExpression* expr) throw() {
	Value* lhs = getValue(expr->get_lhs());
	Value* rhs = getValue(expr->get_rhs());
	ConstantValue* result = NULL;

	if (!Compiler::checkCompatibleTypes(lhs, rhs)) {
		Compiler::error("Type mismatch!");
	}
	if (lhs->isPrimitive()) {
		result = Compiler::constantFolding(expr->get_op(), lhs, rhs);
	}
	if (result) {
		/**
		 * Don't generate the opcode, the expression was evaluated in
		 * compile-time
		 */
		expr->set_optimized(true);
		expr->set_result(result);
		return NULL;
	}
	expr->set_result(new TempValue);

	lhs->addRef();
	rhs->addRef();

	switch (expr->get_op()) {
		case ast::PLUS:  return new Opcode(OP_PLUS,   &VM::plus_handler,   lhs, rhs, expr->get_value());
		case ast::DIV:   return new Opcode(OP_DIV,    &VM::div_handler,    lhs, rhs, expr->get_value());
		case ast::MULT:  return new Opcode(OP_MULT,   &VM::mult_handler,   lhs, rhs, expr->get_value());
		case ast::MINUS: return new Opcode(OP_MINUS,  &VM::minus_handler,  lhs, rhs, expr->get_value());
		case ast::XOR:   return new Opcode(OP_BW_XOR, &VM::bw_xor_handler, lhs, rhs, expr->get_value());
		case ast::OR:    return new Opcode(OP_BW_OR,  &VM::bw_or_handler,  lhs, rhs, expr->get_value());
		case ast::AND:   return new Opcode(OP_BW_AND, &VM::bw_and_handler, lhs, rhs, expr->get_value());
		case ast::MOD:   return new Opcode(OP_MOD,    &VM::bw_and_handler, lhs, rhs, expr->get_value());
	}
	return NULL;
}

/**
 * Generates the variable declaration opcode
 */
Opcode* IRBuilder::variableDecl(ast::VariableDecl* expr) throw() {
	ast::Expression* var_type = expr->get_type();
	ast::Expression* var_expr = expr->get_variable();
	ast::Expression* rhs_expr = expr->get_initial_value();
	NamedValue* variable = static_cast<NamedValue*>(var_expr->get_value());
	const Type* type = TypeTable::getType(var_type->get_value()->get_name());

	variable->set_type_ptr(type);

	/* Check if the declaration contains initialization */
	if (rhs_expr) {
		Value* value = getValue(rhs_expr);

		m_ssa.pushVar(variable);

		variable->setInitialized();
		variable->copy(value);

		variable->addRef();
		value->addRef();

		return new Opcode(OP_VAR_DECL, &VM::var_decl_handler, variable, value);
	} else {
		return new Opcode(OP_VAR_DECL, &VM::var_decl_handler, variable);
	}
}

/**
 * Generates the new block opcode
 */
Opcode* IRBuilder::newBlock() throw() {
	Opcode* opcode = new Opcode(OP_NEW_SCOPE, &VM::new_scope_handler);
	Jmp jmp;

	/* Initializes new scope */
	m_ssa.newBlock();

	jmp.push(opcode);
	m_jmps.push(jmp);

	return opcode;
}

/**
 * Generates the end block opcode
 */
Opcode* IRBuilder::endBlock() throw() {
	Opcode* opcode = new Opcode(OP_END_SCOPE, &VM::end_scope_handler);
	Opcode* start_block = m_jmps.top().top();

	/**
	 * No variable was defined in the scope, so let to set a flag
	 * to do not push-pop scope in runtime
	 */
	if (m_ssa.topBlock().size() == 0) {
		start_block->set_flags(BLK_UNUSED);
		opcode->set_flags(BLK_UNUSED);
	} else {
		start_block->set_flags(BLK_USED);
		opcode->set_flags(BLK_USED);
	}

	m_jmps.top().pop();
	m_jmps.pop();

	/* Pop current scope */
	m_ssa.endBlock();

	return opcode;
}

/**
 * Generates the pre increment opcode
 */
Opcode* IRBuilder::preIncrement(ast::PreIncrement* expr) throw() {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();
	return new Opcode(OP_PRE_INC, &VM::pre_inc_handler, value, NULL, expr->get_value());
}

/**
 * Generates the pos increment opcode
 */
Opcode* IRBuilder::posIncrement(ast::PosIncrement* expr) throw() {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();
	return new Opcode(OP_POS_INC, &VM::pos_inc_handler, value, NULL, expr->get_value());
}

/**
 * Generates the pre decrement opcode
 */
Opcode* IRBuilder::preDecrement(ast::PreDecrement* expr) throw() {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();

	return new Opcode(OP_PRE_DEC, &VM::pre_dec_handler, value, NULL, expr->get_value());
}

/**
 * Generates the pos decrement opcode
 */
Opcode* IRBuilder::posDecrement(ast::PosDecrement* expr) throw(){
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();
	return new Opcode(OP_POS_DEC, &VM::pos_dec_handler, value, NULL, expr->get_value());
}

/**
 * Generates the JMPZ opcode for IF expression
 */
Opcode* IRBuilder::ifExpression(ast::IfExpression* expr) throw() {
	Value* value = getValue(expr->get_expr());
	Opcode* opcode = new Opcode(OP_JMPZ, &VM::jmpz_handler, value);
	Jmp jmp;

	jmp.push(opcode);
	m_jmps.push(jmp);

	value->addRef();
	return opcode;
}

/**
 * Generates a JMPZ opcode for ELSEIF expression
 */
Opcode* IRBuilder::elseIfExpression(ast::ElseIfExpression* expr) throw() {
	Value* value = getValue(expr->get_expr());
	Opcode* opcode = new Opcode(OP_JMPZ, &VM::jmpz_handler, value);
	ast::StartExpr* start_expr = static_cast<ast::StartExpr*>(expr->get_start_expr());

	/* Sets the if jmp to start of the ELSEIF expr */
	m_jmps.top().top()->set_jmp_addr1(start_expr->get_op_num());
	m_jmps.top().push(opcode);

	value->addRef();
	return opcode;
}

/**
 * Generates a JMP opcode for ELSE expression
 */
Opcode* IRBuilder::elseExpression(ast::ElseExpression* expr) throw() {
	Opcode* opcode = new Opcode(OP_JMP, &VM::jmp_handler);

	m_jmps.top().top()->set_jmp_addr1(getOpNum()+2);
	m_jmps.top().push(opcode);

	return opcode;
}

/**
 * Just set the jmp address of if-elsif-else to end of control structure
 */
Opcode* IRBuilder::endIfExpression() throw() {
	Jmp jmp = m_jmps.top();

	/* Sets the jmp addr for the IF when there is no ELSE */
	if (m_jmps.top().size() == 1) {
		m_jmps.top().top()->set_jmp_addr1(getOpNum()+1);
	}

	while (!jmp.empty()) {
		Opcode* opcode = jmp.top();

		/* Points to out of if-elsif-else block */
		opcode->set_jmp_addr2(getOpNum()+1);

		jmp.pop();
	}

	m_jmps.pop();

	return NULL;
}

/**
 * Generates the JMPZ opcode for WHILE expression
 */
Opcode* IRBuilder::whileExpression(ast::WhileExpression* expr) throw() {
	Value* value = getValue(expr->get_expr());
	Opcode* opcode = new Opcode(OP_JMPZ, &VM::jmpz_handler, value);
	Jmp jmp;

	jmp.push(opcode);
	m_jmps.push(jmp);
	m_brks.push(Jmp());

	value->addRef();
	return opcode;
}

/**
 * Just set the end jmp addr of WHILE expression
 */
Opcode* IRBuilder::endWhileExpression(ast::EndWhileExpression* expr) throw() {
	Opcode* opcode = new Opcode(OP_JMP, &VM::jmp_handler);
	ast::StartExpr* start_loop = static_cast<ast::StartExpr*>(expr->get_expr());
	unsigned int scope_out = getOpNum()+2;

	/* Points to out of WHILE block */
	while (!m_brks.top().empty()) {
		m_brks.top().top()->set_jmp_addr1(scope_out);
		m_brks.top().pop();
	}
	m_jmps.top().top()->set_jmp_addr1(scope_out);
	m_jmps.top().pop();
	m_jmps.pop();
	m_brks.pop();

	/* Points to start of WHILE expression */
	opcode->set_jmp_addr2(start_loop->get_op_num());

	return opcode;
}

/**
 * Just hold the current op number before the WHILE expression
 */
Opcode* IRBuilder::startExpr(ast::StartExpr* expr) throw() {
	expr->set_op_num(getOpNum()+1);

	return NULL;
}

/**
 * Generates opcode for logic expression which weren't optimized
 */
Opcode* IRBuilder::logicExpression(ast::LogicExpression* expr) throw() {
	Value* lhs = getValue(expr->get_lhs());
	Value* rhs = getValue(expr->get_rhs());
	ConstantValue* result = NULL;

	if (!Compiler::checkCompatibleTypes(lhs, rhs)) {
		Compiler::error("Type mismatch!");
	}

	if (lhs->isPrimitive()) {
		result = Compiler::constantFolding(expr->get_op(), lhs, rhs);
	}
	if (result) {
		/**
		 * Don't generate the opcode, the expression was evaluated in
		 * compile-time
		 */
		expr->set_optimized(true);
		expr->set_result(result);
		return NULL;
	}

	expr->set_result(new TempValue);

	lhs->addRef();
	rhs->addRef();

	switch (expr->get_op()) {
		case ast::GREATER:       return new Opcode(OP_GREATER,       &VM::greater_handler,       lhs, rhs, expr->get_value());
		case ast::LESS:          return new Opcode(OP_LESS,          &VM::less_handler,          lhs, rhs, expr->get_value());
		case ast::GREATER_EQUAL: return new Opcode(OP_GREATER_EQUAL, &VM::greater_equal_handler, lhs, rhs, expr->get_value());
		case ast::LESS_EQUAL:    return new Opcode(OP_LESS_EQUAL,    &VM::less_equal_handler,    lhs, rhs, expr->get_value());
		case ast::EQUAL:         return new Opcode(OP_EQUAL,         &VM::equal_handler,         lhs, rhs, expr->get_value());
		case ast::NOT_EQUAL:     return new Opcode(OP_NOT_EQUAL,     &VM::not_equal_handler,     lhs, rhs, expr->get_value());
	}
	return NULL;
}

/**
 * Generates opcode for break statement
 */
Opcode* IRBuilder::breakExpression() throw() {
	Opcode* opcode = new Opcode(OP_BREAK, &VM::break_handler);

	m_brks.top().push(opcode);

	return opcode;
}

ValueVector* IRBuilder::functionArgs(const ast::Arguments* args) throw() {
	ValueVector* values = new ValueVector();
	ast::Arguments::const_iterator it = args->begin(), end(args->end());

	values->reserve(args->size());

	while (it != end) {
		Value* value = getValue(*it);

		if (value) {
			value->addRef();
		}
		values->push_back(value);
		++it;
	}

	return values;
}

/**
 * Generates opcode for function call
 */
Opcode* IRBuilder::functionCall(ast::FunctionCall* expr) throw() {
	const CString* name = expr->get_value()->get_name();
	const Function* func = Compiler::getFunction(*name);
	CallableValue* call = new CallableValue(name);
	const ast::Arguments* args = expr->get_args();
	Value* arg_values = NULL;

	if (!func) {
		Compiler::error("Function does not exists!");
	}

	call->set_callback(func);

	if (args) {
		arg_values = new Value;
		arg_values->set_type(Value::VECTOR);
		arg_values->setVector(functionArgs(args));
	}

	return new Opcode(OP_FCALL, &VM::fcall_handler, call, arg_values);
}

Opcode* IRBuilder::methodCall(ast::MethodCall* expr) throw() {
	Value* variable = getValue(expr->get_variable());
	CallableValue* call = new CallableValue(expr->get_method()->get_value()->get_name());
	const Method* method = variable->get_type_ptr()->getMethod(call->get_name());
	const ast::Arguments* args = expr->get_args();
	Value* arg_values = NULL;

	if (!method) {
		Compiler::error("Method not found!");
	}

	call->set_type_ptr(variable->get_type_ptr());
	call->set_callback(method);

	if (args) {
		arg_values = new Value;
		arg_values->set_type(Value::VECTOR);
		arg_values->setVector(functionArgs(args));
	}
	return new Opcode(OP_MCALL, &VM::mcall_handler, call, arg_values);
}

} // clever
