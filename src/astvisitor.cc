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
 * $Id: vm.h 341 2011-01-22 14:07:26Z felipensp $
 */

#include <iostream>
#include "ast.h"
#include "astvisitor.h"
#include "typetable.h"
#include "compiler.h"

namespace clever { namespace ast {

/**
 * Return the Value pointer related to value type
 */
Value* ASTVisitor::getValue(ast::Node* expr) throw() {
	Value* value = expr->get_value();

	if (value && value->hasName()) {
		Value* var = m_ssa.fetchVar(static_cast<NamedValue*>(value));

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

AST_VISITOR(BinaryNode) {
	Value* lhs = getValue(expr->get_lhs());
	Value* rhs = getValue(expr->get_rhs());
	ConstantValue* result = NULL;

	if (!Compiler::checkCompatibleTypes(lhs, rhs)) {
		Compiler::error("Type mismatch!");
	}
	if (lhs->isPrimitive() && !expr->isAssigned()) {
		result = Compiler::constantFolding(expr->get_op(), lhs, rhs);
	}
	if (result) {
		/**
		 * Don't generate the opcode, the expression was evaluated in
		 * compile-time
		 */
		expr->set_optimized(true);
		expr->set_result(result);
		return;
	}
	if (expr->isAssigned()) {
		expr->set_result(lhs);
		lhs->addRef();
		lhs->setModified();
	} else {
		expr->set_result(new Value);
	}

	lhs->addRef();
	rhs->addRef();

	switch (expr->get_op()) {
		case ast::PLUS:  pushOpcode(new Opcode(OP_PLUS,   &VM::plus_handler,   lhs, rhs, expr->get_value())); break;
		case ast::DIV:   pushOpcode(new Opcode(OP_DIV,    &VM::div_handler,    lhs, rhs, expr->get_value())); break;
		case ast::MULT:  pushOpcode(new Opcode(OP_MULT,   &VM::mult_handler,   lhs, rhs, expr->get_value())); break;
		case ast::MINUS: pushOpcode(new Opcode(OP_MINUS,  &VM::minus_handler,  lhs, rhs, expr->get_value())); break;
		case ast::XOR:   pushOpcode(new Opcode(OP_BW_XOR, &VM::bw_xor_handler, lhs, rhs, expr->get_value())); break;
		case ast::OR:    pushOpcode(new Opcode(OP_BW_OR,  &VM::bw_or_handler,  lhs, rhs, expr->get_value())); break;
		case ast::AND:   pushOpcode(new Opcode(OP_BW_AND, &VM::bw_and_handler, lhs, rhs, expr->get_value())); break;
		case ast::MOD:   pushOpcode(new Opcode(OP_MOD,    &VM::mod_handler,    lhs, rhs, expr->get_value())); break;
	}
}


/**
 * Generates the variable declaration opcode
 */
AST_VISITOR(VariableDecl) {
	ast::Node* var_type = expr->get_type();
	ast::Node* var_expr = expr->get_variable();
	ast::Node* rhs_expr = expr->get_initial_value();
	NamedValue* variable = static_cast<NamedValue*>(var_expr->get_value());
	const Type* type = TypeTable::getType(var_type->get_value()->get_name());

	variable->set_type_ptr(type);

	/* Check if the declaration contains initialization */
	if (rhs_expr) {
		Value* value = getValue(rhs_expr);

		variable->addRef();
		m_ssa.pushVar(variable);

		if (value->isConst()) {
			variable->setInitialized();
			variable->copy(value);
		}

		variable->addRef();
		value->addRef();

		pushOpcode(new Opcode(OP_VAR_DECL, &VM::var_decl_handler, variable, value));
	} else {
		variable->addRef();
		m_ssa.pushVar(variable);

		/* TODO: fix this */
		if (type == TypeTable::getType(CSTRING("Int"))) {
			variable->set_type(Value::INTEGER);
		}

		variable->initialize();
		variable->setInitialized();

		variable->addRef();

		pushOpcode(new Opcode(OP_VAR_DECL, &VM::var_decl_handler, variable));
	}
}

/**
 * Generates the pre increment opcode
 */
AST_VISITOR(PreIncrement) {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();

	pushOpcode(new Opcode(OP_PRE_INC, &VM::pre_inc_handler, value, NULL, expr->get_value()));
}

/**
 * Generates the pos increment opcode
 */
AST_VISITOR(PosIncrement) {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();

	pushOpcode(new Opcode(OP_POS_INC, &VM::pos_inc_handler, value, NULL, expr->get_value()));
}

/**
 * Generates the pre decrement opcode
 */
AST_VISITOR(PreDecrement) {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();

	pushOpcode(new Opcode(OP_PRE_DEC, &VM::pre_dec_handler, value, NULL, expr->get_value()));
}

/**
 * Generates the pos decrement opcode
 */
AST_VISITOR(PosDecrement) {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();

	pushOpcode(new Opcode(OP_POS_DEC, &VM::pos_dec_handler, value, NULL, expr->get_value()));
}

/**
 * Generates the opcode for the IF-ELSEIF-ELSE expression
 */
AST_VISITOR(IfNode) {
	Value* value;
	Opcode* jmp_if = new Opcode(OP_JMPZ, &VM::jmpz_handler);
	Opcode* jmp_else;
	Opcode* jmp_elseif;
	OpcodeList jmp_ops;

	expr->get_condition()->accept(*this);

	value = getValue(expr->get_condition());
	value->addRef();

	jmp_if->set_op1(value);
	pushOpcode(jmp_if);

	jmp_ops.push_back(jmp_if);

	if (expr->hasBlock()) {
		expr->get_block()->accept(*this);
	}

	if (expr->hasElseIf()) {
		NodeList& elseif_nodes = expr->getNodes();
		NodeList::const_iterator it = elseif_nodes.begin(), end = elseif_nodes.end();
		Opcode* last_jmp = jmp_if;

		while (it != end) {
			Value* cond;
			ast::ElseIfNode* elseif = static_cast<ast::ElseIfNode*>(*it);

			last_jmp->set_jmp_addr1(getOpNum());

			elseif->get_condition()->accept(*this);

			cond = getValue(elseif->get_condition());
			cond->addRef();

			jmp_elseif = new Opcode(OP_JMPZ, &VM::jmpz_handler, cond);
			pushOpcode(jmp_elseif);

			jmp_ops.push_back(jmp_elseif);

			if (elseif->hasBlock()) {
				elseif->get_block()->accept(*this);
			}

			last_jmp = jmp_elseif;
			++it;
		}
	}

	if (expr->hasElseBlock()) {
		jmp_else = new Opcode(OP_JMP, &VM::jmp_handler);

		pushOpcode(jmp_else);

		if (jmp_ops.size() == 1) {
			jmp_if->set_jmp_addr1(getOpNum());
		}

		jmp_ops.push_back(jmp_else);

		expr->get_else()->accept(*this);
	}

	if (jmp_ops.size() == 1) {
		jmp_if->set_jmp_addr1(getOpNum());
		jmp_if->set_jmp_addr2(getOpNum());
	} else {
		OpcodeList::iterator it = jmp_ops.begin(), end = jmp_ops.end();

		while (it != end) {
			(*it)->set_jmp_addr2(getOpNum());
			++it;
		}
	}
}

/**
 * Call the accept method of each block node
 */
AST_VISITOR(BlockNode) {
	NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();
	ASTVisitor& visitor = *this;

	/**
	 * Create a new scope
	 */
	m_ssa.beginScope();

	/**
	 * Iterates statements inside the block
	 */
	while (it != end) {
		(*it)->accept(visitor);
		++it;
	}

	/**
	 * Pops the scope
	 */
	m_ssa.endScope();
}

/**
 * Generates the JMPZ opcode for WHILE expression
 */
AST_VISITOR(WhileNode) {
	Value* value;
	Opcode* jmpz;
	Opcode* jmp;
	unsigned int start_pos = 0;

	start_pos = getOpNum();

	expr->get_condition()->accept(*this);

	value = getValue(expr->get_condition());
	value->addRef();

	jmpz = new Opcode(OP_JMPZ, &VM::jmpz_handler, value);
	pushOpcode(jmpz);

	if (expr->hasBlock()) {
		m_brks.push(OpcodeStack());

		expr->get_block()->accept(*this);

		/**
		 * Points break statements to out of WHILE block
		 */
		while (!m_brks.top().empty()) {
			m_brks.top().top()->set_jmp_addr1(getOpNum()+1);
			m_brks.top().pop();
		}
		m_brks.pop();
	}

	jmp = new Opcode(OP_JMP, &VM::jmp_handler);
	jmp->set_jmp_addr2(start_pos);
	pushOpcode(jmp);

	jmpz->set_jmp_addr1(getOpNum());
}


/**
 * Generates opcode for logic expression which weren't optimized
 */
AST_VISITOR(LogicNode) {
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
		return;
	}

	expr->set_result(new Value);

	lhs->addRef();
	rhs->addRef();

	switch (expr->get_op()) {
		case ast::GREATER:       pushOpcode(new Opcode(OP_GREATER,       &VM::greater_handler,       lhs, rhs, expr->get_value())); break;
		case ast::LESS:          pushOpcode(new Opcode(OP_LESS,          &VM::less_handler,          lhs, rhs, expr->get_value())); break;
		case ast::GREATER_EQUAL: pushOpcode(new Opcode(OP_GREATER_EQUAL, &VM::greater_equal_handler, lhs, rhs, expr->get_value())); break;
		case ast::LESS_EQUAL:    pushOpcode(new Opcode(OP_LESS_EQUAL,    &VM::less_equal_handler,    lhs, rhs, expr->get_value())); break;
		case ast::EQUAL:         pushOpcode(new Opcode(OP_EQUAL,         &VM::equal_handler,         lhs, rhs, expr->get_value())); break;
		case ast::NOT_EQUAL:     pushOpcode(new Opcode(OP_NOT_EQUAL,     &VM::not_equal_handler,     lhs, rhs, expr->get_value())); break;
	}
}

/**
 * Generates opcode for break statement
 */
AST_VISITOR(BreakNode) {
	Opcode* opcode = new Opcode(OP_BREAK, &VM::break_handler);

	m_brks.top().push(opcode);

	pushOpcode(opcode);
}

/**
 * Creates a vector with the current value from a Value* pointers
 */
ValueVector* ASTVisitor::functionArgs(ast::ArgumentList* args) throw() {
	ValueVector* values = new ValueVector();
	const NodeList& nodes = args->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	values->reserve(nodes.size());

	while (it != end) {
		Value* value;

		(*it)->accept(*this);

		value = getValue(*it);
		value->addRef();

		values->push_back(value);
		++it;
	}

	return values;
}

/**
 * Generates opcode for function call
 */
AST_VISITOR(FunctionCall) {
	const CString* name = expr->get_func()->get_name();
	const Function* func = Compiler::getFunction(*name);
	CallableValue* call = new CallableValue(name);
	Node* args = expr->get_args();
	Value* arg_values = NULL;

	if (!func) {
		Compiler::error("Function '" + *name + "' does not exists!");
	}

	if (func->isUserDefined()) {
		call->set_addr(func->get_start_pos());
	} else {
		call->set_callback(func->get_ptr());
	}

	if (args) {
		arg_values = new Value;
		arg_values->set_type(Value::VECTOR);
		arg_values->setVector(functionArgs(static_cast<ArgumentList*>(args)));
	}

	pushOpcode(new Opcode(OP_FCALL, &VM::fcall_handler, call, arg_values, expr->get_value()));
}

/**
 * Generates opcode for method call
 */
AST_VISITOR(MethodCall) {
	Value* variable = getValue(expr->get_variable());
	CallableValue* call = new CallableValue(expr->get_method()->get_value()->get_name());
	const MethodPtr method = variable->get_type_ptr()->getMethod(call->get_name());
	Node* args = expr->get_args();
	Value* arg_values = NULL;

	if (!method) {
		Compiler::error("Method not found!");
	}

	call->set_type_ptr(variable->get_type_ptr());
	call->set_callback(method);
	call->set_context(variable);

	if (args) {
		arg_values = new Value;
		arg_values->set_type(Value::VECTOR);
		arg_values->setVector(functionArgs(static_cast<ArgumentList*>(args)));
	}
	pushOpcode(new Opcode(OP_MCALL, &VM::mcall_handler, call, arg_values, expr->get_value()));
}

/**
 * Generates opcode for variable assignment
 */
AST_VISITOR(Assignment) {
	Value* lhs = getValue(expr->get_lhs());
	Value* rhs = getValue(expr->get_rhs());

	lhs->setModified();

	lhs->addRef();
	rhs->addRef();

	pushOpcode(new Opcode(OP_ASSIGN, &VM::assign_handler, lhs, rhs));
}

/**
 * Import statement
 */
AST_VISITOR(Import) {
	const CString* package = expr->get_package()->get_value()->get_name();
	ast::Node* module = expr->get_module();

	if (module) {
		const CString* module_name = module->get_value()->get_name();

		Compiler::import(package, module_name);
	} else {
		Compiler::import(package);
	}
}

/**
 * Function declaration
 */
AST_VISITOR(FuncDeclaration) {
	const CString* name = expr->get_name()->get_value()->get_name();
	CallableValue* func = new CallableValue(name);
	Opcode* jmp = new Opcode(OP_JMP, &VM::jmp_handler);
	Function* user_func = new Function(name->str());

	Compiler::addFunction(name->str(), user_func);

	pushOpcode(jmp);

	func->set_addr(getOpNum());
	user_func->setUserDefined();
	user_func->set_start_pos(getOpNum());

	m_ssa.pushVar(func);

	expr->get_block()->accept(*this);

	pushOpcode(new Opcode(OP_JMP, &VM::end_func_handler));

	jmp->set_jmp_addr2(getOpNum());
}

/**
 * Generates opcode for return statement
 */
AST_VISITOR(ReturnStmt) {
	Node* value = expr->get_expr();

	if (expr) {
		Value* expr_value = value->get_value();

		expr_value->addRef();

		pushOpcode(new Opcode(OP_RETURN, &VM::return_handler, expr_value));
	} else {
		pushOpcode(new Opcode(OP_RETURN, &VM::return_handler));
	}
}

}} // clever::ast
