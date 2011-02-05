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

#include "ast.h"
#include "astvisitor.h"
#include "typetable.h"
#include "compiler.h"

namespace clever { namespace ast {

/**
 * Creates a vector with the current value from a Value* pointers
 */
ValueVector* CodeGenVisitor::functionArgs(ArgumentList* args) throw() {
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
 * Return the Value pointer related to value type
 */
Value* CodeGenVisitor::getValue(ASTNode* expr) throw() {
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
		Compiler::error("Inexistent variable!", expr->get_location());
	}
	return value;
}

/**
 * Generates opcode for binary expression
 */
AST_VISITOR(CodeGenVisitor, BinaryExpr) {
	Value* lhs = getValue(expr->get_lhs());
	Value* rhs = getValue(expr->get_rhs());
	Value* result = NULL;

	if (!Compiler::checkCompatibleTypes(lhs, rhs)) {
		Compiler::error("Type mismatch!", expr->get_location());
	}
	if (lhs->isPrimitive() && rhs->isPrimitive() && !expr->isAssigned()) {
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
		case PLUS:  emit(OP_PLUS,   &VM::plus_handler,   lhs, rhs, expr->get_value()); break;
		case DIV:   emit(OP_DIV,    &VM::div_handler,    lhs, rhs, expr->get_value()); break;
		case MULT:  emit(OP_MULT,   &VM::mult_handler,   lhs, rhs, expr->get_value()); break;
		case MINUS: emit(OP_MINUS,  &VM::minus_handler,  lhs, rhs, expr->get_value()); break;
		case XOR:   emit(OP_BW_XOR, &VM::bw_xor_handler, lhs, rhs, expr->get_value()); break;
		case OR:    emit(OP_BW_OR,  &VM::bw_or_handler,  lhs, rhs, expr->get_value()); break;
		case AND:   emit(OP_BW_AND, &VM::bw_and_handler, lhs, rhs, expr->get_value()); break;
		case MOD:   emit(OP_MOD,    &VM::mod_handler,    lhs, rhs, expr->get_value()); break;
	}
}


/**
 * Generates the variable declaration opcode
 */
AST_VISITOR(CodeGenVisitor, VariableDecl) {
	ASTNode* var_type = expr->get_type();
	ASTNode* var_expr = expr->get_variable();
	ASTNode* rhs_expr = expr->get_initial_value();
	Value* variable = var_expr->get_value();
	const Type* type = TypeTable::getType(var_type->get_value()->get_name());

	variable->set_type_ptr(type);

	/* Check if the declaration contains initialization */
	if (rhs_expr) {
		Value* value = getValue(rhs_expr);

		variable->addRef();
		m_ssa.pushVar(variable);

		if (value->isPrimitive()) {
			variable->setInitialized();
			variable->copy(value);
		}

		variable->addRef();
		value->addRef();

		emit(OP_VAR_DECL, &VM::var_decl_handler, variable, value);
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

		emit(OP_VAR_DECL, &VM::var_decl_handler, variable);
	}
}

/**
 * Generates the pre increment opcode
 */
AST_VISITOR(CodeGenVisitor, PreIncrement) {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();

	emit(OP_PRE_INC, &VM::pre_inc_handler, value, NULL, expr->get_value());
}

/**
 * Generates the pos increment opcode
 */
AST_VISITOR(CodeGenVisitor, PosIncrement) {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();

	emit(OP_POS_INC, &VM::pos_inc_handler, value, NULL, expr->get_value());
}

/**
 * Generates the pre decrement opcode
 */
AST_VISITOR(CodeGenVisitor, PreDecrement) {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();

	emit(OP_PRE_DEC, &VM::pre_dec_handler, value, NULL, expr->get_value());
}

/**
 * Generates the pos decrement opcode
 */
AST_VISITOR(CodeGenVisitor, PosDecrement) {
	Value* value = getValue(expr->get_expr());

	value->setModified();
	value->addRef();

	emit(OP_POS_DEC, &VM::pos_dec_handler, value, NULL, expr->get_value());
}

/**
 * Generates the opcode for the IF-ELSEIF-ELSE expression
 */
AST_VISITOR(CodeGenVisitor, IfExpr) {
	Value* value;
	Opcode* jmp_if;
	Opcode* jmp_else;
	Opcode* jmp_elseif;
	OpcodeList jmp_ops;

	expr->get_condition()->accept(*this);

	value = getValue(expr->get_condition());
	value->addRef();

	jmp_if = emit(OP_JMPZ, &VM::jmpz_handler);
	jmp_if->set_op1(value);

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
			ElseIfExpr* elseif = static_cast<ElseIfExpr*>(*it);

			last_jmp->set_jmp_addr1(getOpNum());

			elseif->get_condition()->accept(*this);

			cond = getValue(elseif->get_condition());
			cond->addRef();

			jmp_elseif = emit(OP_JMPZ, &VM::jmpz_handler, cond);

			jmp_ops.push_back(jmp_elseif);

			if (elseif->hasBlock()) {
				elseif->get_block()->accept(*this);
			}

			last_jmp = jmp_elseif;
			++it;
		}
	}

	if (expr->hasElseBlock()) {
		jmp_else = emit(OP_JMP, &VM::jmp_handler);

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
AST_VISITOR(CodeGenVisitor, BlockNode) {
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
AST_VISITOR(CodeGenVisitor, WhileExpr) {
	Value* value;
	Opcode* jmpz;
	Opcode* jmp;
	unsigned int start_pos = 0;

	start_pos = getOpNum();

	expr->get_condition()->accept(*this);

	value = getValue(expr->get_condition());
	value->addRef();

	jmpz = emit(OP_JMPZ, &VM::jmpz_handler, value);

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

	jmp = emit(OP_JMP, &VM::jmp_handler);
	jmp->set_jmp_addr2(start_pos);

	jmpz->set_jmp_addr1(getOpNum());
}


/**
 * Generates opcode for logic expression which weren't optimized
 */
AST_VISITOR(CodeGenVisitor, LogicExpr) {
	Value* lhs = getValue(expr->get_lhs());
	Value* rhs = getValue(expr->get_rhs());
	Value* result = NULL;

	if (!Compiler::checkCompatibleTypes(lhs, rhs)) {
		Compiler::error("Type mismatch!", expr->get_location());
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
		case GREATER:       emit(OP_GREATER,       &VM::greater_handler,       lhs, rhs, expr->get_value()); break;
		case LESS:          emit(OP_LESS,          &VM::less_handler,          lhs, rhs, expr->get_value()); break;
		case GREATER_EQUAL: emit(OP_GREATER_EQUAL, &VM::greater_equal_handler, lhs, rhs, expr->get_value()); break;
		case LESS_EQUAL:    emit(OP_LESS_EQUAL,    &VM::less_equal_handler,    lhs, rhs, expr->get_value()); break;
		case EQUAL:         emit(OP_EQUAL,         &VM::equal_handler,         lhs, rhs, expr->get_value()); break;
		case NOT_EQUAL:     emit(OP_NOT_EQUAL,     &VM::not_equal_handler,     lhs, rhs, expr->get_value()); break;
	}
}

/**
 * Generates opcode for break statement
 */
AST_VISITOR(CodeGenVisitor, BreakNode) {
	Opcode* opcode = emit(OP_BREAK, &VM::break_handler);

	m_brks.top().push(opcode);
}

/**
 * Generates opcode for function call
 */
AST_VISITOR(CodeGenVisitor, FunctionCall) {
	const CString* name = expr->get_func()->get_name();
	Value* fvalue = m_ssa.fetchVar(name);
	const Function* func;
	ASTNode* args = expr->get_args();
	Value* arg_values = NULL;
	int num_args = args ? args->getNodes().size() : 0;

	if (fvalue == NULL) {
		Compiler::error("Function '" + *name + "' does not exists!", expr->get_location());
	}
	func = static_cast<CallableValue*>(fvalue)->get_function();

	Compiler::checkFunctionArgs(func, num_args, expr->get_location());

	if (args) {
		arg_values = new Value;
		arg_values->set_type(Value::VECTOR);
		arg_values->setVector(functionArgs(static_cast<ArgumentList*>(args)));

		if (func->isUserDefined()) {
			Value* vars = const_cast<Function*>(func)->get_vars();

			vars->addRef();
			emit(OP_RECV, &VM::arg_recv_handler, vars, arg_values);
			arg_values = NULL;
		}
	}

	fvalue->addRef();
	emit(OP_FCALL, &VM::fcall_handler, fvalue, arg_values, expr->get_value());
}

/**
 * Generates opcode for method call
 */
AST_VISITOR(CodeGenVisitor, MethodCall) {
	Value* variable = getValue(expr->get_variable());
	CallableValue* call = new CallableValue(expr->get_method()->get_value()->get_name());
	const MethodPtr method = variable->get_type_ptr()->getMethod(call->get_name());
	ASTNode* args = expr->get_args();
	Value* arg_values = NULL;

	if (!method) {
		Compiler::error("Method not found!", expr->get_location());
	}

	call->set_type_ptr(variable->get_type_ptr());
	call->set_handler(method);
	call->set_context(variable);

	if (args) {
		arg_values = new Value;
		arg_values->set_type(Value::VECTOR);
		arg_values->setVector(functionArgs(static_cast<ArgumentList*>(args)));
	}
	emit(OP_MCALL, &VM::mcall_handler, call, arg_values, expr->get_value());
}

/**
 * Generates opcode for variable assignment
 */
AST_VISITOR(CodeGenVisitor, AssignStmt) {
	Value* lhs = getValue(expr->get_lhs());
	Value* rhs = getValue(expr->get_rhs());

	lhs->setModified();

	lhs->addRef();
	rhs->addRef();

	emit(OP_ASSIGN, &VM::assign_handler, lhs, rhs);
}

/**
 * Import statement
 */
AST_VISITOR(CodeGenVisitor, ImportStmt) {
	const CString* package = expr->get_package()->get_value()->get_name();
	ASTNode* module = expr->get_module();

	if (module) {
		const CString* module_name = module->get_value()->get_name();

		Compiler::import(m_ssa.currentScope(), package, module_name);
	} else {
		Compiler::import(m_ssa.currentScope(), package);
	}
}

/**
 * Function declaration
 */
AST_VISITOR(CodeGenVisitor, FuncDeclaration) {
	const CString* name = expr->get_name()->get_value()->get_name();
	CallableValue* func = new CallableValue(name);
	Function* user_func = new Function(name->str());
	ast::ArgumentDeclList* args = static_cast<ast::ArgumentDeclList*>(expr->get_args());
	Value* return_type = expr->get_return() ? expr->get_return()->get_value() : NULL;
	Opcode* jmp;

	jmp = emit(OP_JMP, &VM::jmp_handler);

	user_func->setUserDefined();
	user_func->set_offset(getOpNum());

	if (return_type) {
		user_func->set_return(TypeTable::getType(return_type->get_name()));
	}

	func->set_handler(user_func);

	m_ssa.pushVar(func);

	if (expr->hasBlock()) {
		if (args) {
			ArgumentDecls& arg_nodes = args->get_args();
			ArgumentDecls::iterator it = arg_nodes.begin(), end = arg_nodes.end();
			Value* vars = new Value;
			ValueVector* vec = new ValueVector;

			vars->set_type(Value::VECTOR);
			vars->set_reference(0);

			m_ssa.beginScope();

			while (it != end) {
				Value* var = new Value;

				var->set_name(it->second->get_value()->get_name());
				var->set_type_ptr(TypeTable::getType(it->first->get_value()->get_name()));
				var->set_type(Value::INTEGER);
				var->initialize();
				var->setModified();

				m_ssa.pushVar(var);
				vec->push_back(var);
				var->addRef();

				user_func->addArg(*it->second->get_value()->get_name(), TypeTable::getType(it->first->get_value()->get_name()));

				++it;
			}

			vars->setVector(vec);
			user_func->set_vars(vars);
		}

		m_funcs.push(user_func);

		expr->get_block()->accept(*this);

		m_funcs.pop();

		if (args) {
			m_ssa.endScope();
		}
	}

	emit(OP_JMP, &VM::end_func_handler);

	jmp->set_jmp_addr2(getOpNum());
}

/**
 * Generates opcode for return statement
 */
AST_VISITOR(CodeGenVisitor, ReturnStmt) {
	ASTNode* value = expr->get_expr();
	const Function* func = m_funcs.empty() ? NULL : m_funcs.top();
	const Type* rtype = func ? func->get_return() : NULL;

	/**
	 * Only for return inside function declaration
	 */
	if (func) {
		if (value && rtype == NULL) {
			Compiler::errorf(expr->get_location(), "Function `%S' cannot return value, it was declared as Void!",
				&func->get_name());
		} else if (value == NULL && rtype) {
			Compiler::errorf(expr->get_location(), "Function `%S' must return a value of type %s!",
				&func->get_name(), rtype->get_name());
		}
	}

	if (value) {
		Value* expr_value = value->get_value();

		expr_value->addRef();

		emit(OP_RETURN, &VM::return_handler, expr_value);
	} else {
		emit(OP_RETURN, &VM::return_handler);
	}
}

}} // clever::ast
