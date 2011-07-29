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
#include "cgvisitor.h"
#include "compiler/typetable.h"
#include "compiler/compiler.h"

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
	Value* value = expr->getValue();

	if (value && value->hasName()) {
		Value* var = m_ssa.fetchVar(value);

		/**
		 * If the variable is found, we should use its pointer instead of
		 * fetching on runtime
		 */
		if (EXPECTED(var != NULL)) {
			return var;
		}
		Compiler::error("Inexistent variable!", expr->getLocation());
	}
	return value;
}

/**
 * Generates opcode for binary expression
 */
AST_VISITOR(CodeGenVisitor, BinaryExpr) {
	Value* lhs = getValue(expr->getLhs());
	Value* rhs = getValue(expr->getRhs());
	Value* result = NULL;
	
	if (!Compiler::checkCompatibleTypes(lhs, rhs)) {
		Compiler::error("Type mismatch!", expr->getLocation()); 	
	}
	
	const Type* type = Compiler::checkExprType(lhs, rhs);
	
	if (lhs->isPrimitive() && rhs->isPrimitive() && !expr->isAssigned()) {
		result = Compiler::constantFolding(expr->getOp(), lhs, rhs);
	}
	if (result) {
		/**
		 * Don't generate the opcode, the expression was evaluated in
		 * compile-time
		 */
		result->setTypePtr(type);
		expr->setOptimized(true);
		expr->setResult(result);
		return;
	}
	if (expr->isAssigned()) {
		expr->setResult(lhs);
		lhs->addRef();
		lhs->setModified();
	} else {
		expr->setResult(new Value(lhs->getTypePtr()));
	}

	lhs->addRef();
	rhs->addRef();

	switch (expr->getOp()) {
		case PLUS:  emit(OP_PLUS,   &VM::plus_handler,   lhs, rhs, expr->getValue()); break;
		case DIV:   emit(OP_DIV,    &VM::div_handler,    lhs, rhs, expr->getValue()); break;
		case MULT:  emit(OP_MULT,   &VM::mult_handler,   lhs, rhs, expr->getValue()); break;
		case MINUS: emit(OP_MINUS,  &VM::minus_handler,  lhs, rhs, expr->getValue()); break;
		case XOR:   emit(OP_BW_XOR, &VM::bw_xor_handler, lhs, rhs, expr->getValue()); break;
		case OR:    emit(OP_BW_OR,  &VM::bw_or_handler,  lhs, rhs, expr->getValue()); break;
		case AND:   emit(OP_BW_AND, &VM::bw_and_handler, lhs, rhs, expr->getValue()); break;
		case MOD:   emit(OP_MOD,    &VM::mod_handler,    lhs, rhs, expr->getValue()); break;
	}
	
	expr->getValue()->setTypePtr(type);
}


/**
 * Generates the variable declaration opcode
 */
AST_VISITOR(CodeGenVisitor, VariableDecl) {
	ASTNode* var_type = expr->getType();
	ASTNode* var_expr = expr->getVariable();
	ASTNode* rhs_expr = expr->getInitialValue();
	Value* variable = var_expr->getValue();
	const Type* type = TypeTable::getType(var_type->getValue()->getName());
	
	/* Check if the type wasn't declarated */
	if (type == NULL) {
		Compiler::errorf(expr->getLocation(), "`%s' does not name a type", 
			var_type->getValue()->getName()->c_str());
	}

	variable->setTypePtr(type);

	/* Check if the declaration contains initialization */
	if (rhs_expr) {
		Value* value = getValue(rhs_expr);
		
		if (!Compiler::checkCompatibleTypes(variable, value)) {
			std::string error = std::string("Cannot convert `")
				+ value->getTypePtr()->getName() + "' to `" 
				+ variable->getTypePtr()->getName() + "' on assignment";
			Compiler::error(error, expr->getLocation());	 	
		}

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
			variable->setType(Value::INTEGER);
		}
		else if (type == TypeTable::getType(CSTRING("Double"))) {
			variable->setType(Value::DOUBLE);
		}
		else if (type == TypeTable::getType(CSTRING("String"))) {
			variable->setType(Value::STRING);
		}
		else {
			variable->setType(Value::USER);
			variable->setDataValue(type->allocateValue());	
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
	Value* value = getValue(expr->getExpr());

	value->setModified();
	value->addRef();

	emit(OP_PRE_INC, &VM::pre_inc_handler, value, NULL, expr->getValue());
	expr->getValue()->setTypePtr(value->getTypePtr());
}

/**
 * Generates the pos increment opcode
 */
AST_VISITOR(CodeGenVisitor, PosIncrement) {
	Value* value = getValue(expr->getExpr());

	value->setModified();
	value->addRef();

	emit(OP_POS_INC, &VM::pos_inc_handler, value, NULL, expr->getValue());
	expr->getValue()->setTypePtr(value->getTypePtr());
}

/**
 * Generates the pre decrement opcode
 */
AST_VISITOR(CodeGenVisitor, PreDecrement) {
	Value* value = getValue(expr->getExpr());

	value->setModified();
	value->addRef();

	emit(OP_PRE_DEC, &VM::pre_dec_handler, value, NULL, expr->getValue());
	expr->getValue()->setTypePtr(value->getTypePtr());
}

/**
 * Generates the pos decrement opcode
 */
AST_VISITOR(CodeGenVisitor, PosDecrement) {
	Value* value = getValue(expr->getExpr());

	value->setModified();
	value->addRef();

	emit(OP_POS_DEC, &VM::pos_dec_handler, value, NULL, expr->getValue());
	expr->getValue()->setTypePtr(value->getTypePtr());
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

	expr->getCondition()->accept(*this);

	value = getValue(expr->getCondition());
	value->addRef();

	jmp_if = emit(OP_JMPZ, &VM::jmpz_handler);
	jmp_if->setOp1(value);

	jmp_ops.push_back(jmp_if);

	if (expr->hasBlock()) {
		expr->getBlock()->accept(*this);
	}

	if (expr->hasElseIf()) {
		NodeList& elseif_nodes = expr->getNodes();
		NodeList::const_iterator it = elseif_nodes.begin(), end = elseif_nodes.end();
		Opcode* last_jmp = jmp_if;

		while (it != end) {
			Value* cond;
			ElseIfExpr* elseif = static_cast<ElseIfExpr*>(*it);

			last_jmp->setJmpAddr1(getOpNum());

			elseif->getCondition()->accept(*this);

			cond = getValue(elseif->getCondition());
			cond->addRef();

			jmp_elseif = emit(OP_JMPZ, &VM::jmpz_handler, cond);

			jmp_ops.push_back(jmp_elseif);

			if (elseif->hasBlock()) {
				elseif->getBlock()->accept(*this);
			}

			last_jmp = jmp_elseif;
			++it;
		}
	}

	if (expr->hasElseBlock()) {
		jmp_else = emit(OP_JMP, &VM::jmp_handler);

		if (jmp_ops.size() == 1) {
			jmp_if->setJmpAddr1(getOpNum());
		}

		jmp_ops.push_back(jmp_else);

		expr->getElse()->accept(*this);
	}

	if (jmp_ops.size() == 1) {
		jmp_if->setJmpAddr1(getOpNum());
		jmp_if->setJmpAddr2(getOpNum());
	} else {
		OpcodeList::iterator it = jmp_ops.begin(), end = jmp_ops.end();

		while (it != end) {
			(*it)->setJmpAddr2(getOpNum());
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

	expr->getCondition()->accept(*this);

	value = getValue(expr->getCondition());
	value->addRef();

	jmpz = emit(OP_JMPZ, &VM::jmpz_handler, value);

	if (expr->hasBlock()) {
		m_brks.push(OpcodeStack());

		expr->getBlock()->accept(*this);

		/**
		 * Points break statements to out of WHILE block
		 */
		while (!m_brks.top().empty()) {
			m_brks.top().top()->setJmpAddr1(getOpNum()+1);
			m_brks.top().pop();
		}
		m_brks.pop();
	}

	jmp = emit(OP_JMP, &VM::jmp_handler);
	jmp->setJmpAddr2(start_pos);

	jmpz->setJmpAddr1(getOpNum());
}


/**
 * Generates opcode for logic expression which weren't optimized
 */
AST_VISITOR(CodeGenVisitor, LogicExpr) {
	Opcode* opcode;
	Value* lhs;
	Value* rhs;
	Value* result = NULL;

	expr->getLhs()->accept(*this);
	expr->getRhs()->accept(*this);

	lhs = getValue(expr->getLhs());
	rhs = getValue(expr->getRhs());
	
	if (!Compiler::checkCompatibleTypes(rhs, lhs)) {
		std::string error = std::string("Cannot convert `")
			+ rhs->getTypePtr()->getName() + "' to `" 
			+ lhs->getTypePtr()->getName() + "' in logic expression";
		Compiler::error(error, expr->getLocation());	 	
	}

	if (lhs->isPrimitive()) {
		result = Compiler::constantFolding(expr->getOp(), lhs, rhs);
	}
	if (result) {
		/**
		 * Don't generate the opcode, the expression was evaluated in
		 * compile-time
		 */
		expr->setOptimized(true);
		expr->setResult(result);
		return;
	} else {
		expr->setResult(new Value(lhs->getTypePtr()));
	}

	lhs->addRef();
	rhs->addRef();

	switch (expr->getOp()) {
		case GREATER:       emit(OP_GREATER,       &VM::greater_handler,       lhs, rhs, expr->getValue()); break;
		case LESS:          emit(OP_LESS,          &VM::less_handler,          lhs, rhs, expr->getValue()); break;
		case GREATER_EQUAL: emit(OP_GREATER_EQUAL, &VM::greater_equal_handler, lhs, rhs, expr->getValue()); break;
		case LESS_EQUAL:    emit(OP_LESS_EQUAL,    &VM::less_equal_handler,    lhs, rhs, expr->getValue()); break;
		case EQUAL:         emit(OP_EQUAL,         &VM::equal_handler,         lhs, rhs, expr->getValue()); break;
		case NOT_EQUAL:     emit(OP_NOT_EQUAL,     &VM::not_equal_handler,     lhs, rhs, expr->getValue()); break;
		case AND:
			opcode = emit(OP_JMPNZ, &VM::jmpz_handler, lhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum()+1);
			opcode = emit(OP_JMPZ, &VM::jmpz_handler, rhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum());
			expr->getValue()->addRef();
			break;
		case OR:
			opcode = emit(OP_JMPNZ, &VM::jmpnz_handler, lhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum()+1);
			opcode = emit(OP_JMPNZ, &VM::jmpnz_handler, rhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum());
			expr->getValue()->addRef();
			break;
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
	const CString* const name = expr->getFuncName();
	Value* fvalue = m_ssa.fetchVar(name);
	const Function* func;
	ASTNode* args = expr->getArgs();
	Value* arg_values = NULL;
	int num_args = args ? args->getNodes().size() : 0;

	if (fvalue == NULL) {
		Compiler::error("Function '" + *name + "' does not exists!", expr->getLocation());
	}
	func = static_cast<CallableValue*>(fvalue)->getFunction();

	/* Set the return type */
	expr->getValue()->setTypePtr(func->getReturn());

	Compiler::checkFunctionArgs(func, num_args, expr->getLocation());

	if (args) {
		arg_values = new Value;
		arg_values->setType(Value::VECTOR);
		arg_values->setVector(functionArgs(static_cast<ArgumentList*>(args)));

		if (func->isUserDefined()) {
			Value* vars = const_cast<Function*>(func)->getVars();

			vars->addRef();
			emit(OP_RECV, &VM::arg_recv_handler, vars, arg_values);
			arg_values = NULL;
		}
	}

	fvalue->addRef();
	emit(OP_FCALL, &VM::fcall_handler, fvalue, arg_values, expr->getValue());
}

/**
 * Generates opcode for method call
 */
AST_VISITOR(CodeGenVisitor, MethodCall) {
	Value* variable = getValue(expr->getVariable());
	CallableValue* call = new CallableValue(expr->getMethodName());
	const Method* method = variable->getTypePtr()->getMethod(call->getName());
	ASTNode* args = expr->getArgs();
	Value* arg_values = NULL;

	if (!method) {
		Compiler::error("Method not found!", expr->getLocation());
	}

	call->setTypePtr(variable->getTypePtr());
	call->setHandler(method);
	call->setContext(variable);

	if (args) {
		arg_values = new Value;
		arg_values->setType(Value::VECTOR);
		arg_values->setVector(functionArgs(static_cast<ArgumentList*>(args)));
	}
	emit(OP_MCALL, &VM::mcall_handler, call, arg_values, expr->getValue());
}

/**
 * Generates opcode for variable assignment
 */
AST_VISITOR(CodeGenVisitor, AssignExpr) {
	Value* lhs = getValue(expr->getLhs());
	Value* rhs = getValue(expr->getRhs());
	
	if (!Compiler::checkCompatibleTypes(rhs, lhs)) {
		std::string error = std::string("Cannot convert `")
			+ rhs->getTypePtr()->getName() + "' to `" 
			+ lhs->getTypePtr()->getName() + "' on assignment";
		Compiler::error(error, expr->getLocation());	 	
	}
	
	lhs->setModified();

	lhs->addRef();
	rhs->addRef();

	emit(OP_ASSIGN, &VM::assign_handler, lhs, rhs);
}

/**
 * Import statement
 */
AST_VISITOR(CodeGenVisitor, ImportStmt) {
	const CString* const package = expr->getPackageName();
	const CString* const module = expr->getModuleName();

	if (module) {
		/**
		 * Importing an specific module
		 * e.g. import std.io;
		 */
		if (isInteractive() && m_ssa.currentScope().getNumber() == 1) {
			Compiler::import(m_ssa.fetchScope(0), package, module);
		} else {
			Compiler::import(m_ssa.currentScope(), package, module);
		}
	} else {
		/**
		 * Importing an entire package
		 * e.g. import std;
		 */
		if (isInteractive() && m_ssa.currentScope().getNumber() == 1) {
			Compiler::import(m_ssa.fetchScope(0), package);
		} else {
			Compiler::import(m_ssa.currentScope(), package);
		}
	}
}

/**
 * Function declaration
 */
AST_VISITOR(CodeGenVisitor, FuncDeclaration) {
	const CString* name = expr->getName();
	CallableValue* func = new CallableValue(name);
	Function* user_func = new Function(name->str());
	ast::ArgumentDeclList* args = static_cast<ast::ArgumentDeclList*>(expr->getArgs());
	Value* return_type = expr->getReturn() ? expr->getReturn()->getValue() : NULL;
	Opcode* jmp;

	jmp = emit(OP_JMP, &VM::jmp_handler);

	user_func->setUserDefined();
	user_func->setOffset(getOpNum());

	if (return_type) {
		user_func->setReturn(TypeTable::getType(return_type->getName()));
	}

	func->setHandler(user_func);

	m_ssa.pushVar(func);

	/* we can't have a function declaration without a block. */
	if (!expr->hasBlock()) {
		Compiler::error("Cannot declare a function without a block.", expr->getLocation());
	}

	if (args) {
		ArgumentDecls& arg_nodes = args->getArgs();
		ArgumentDecls::iterator it = arg_nodes.begin(), end = arg_nodes.end();
		Value* vars = new Value;
		ValueVector* vec = new ValueVector;

		vars->setType(Value::VECTOR);
		vars->setReference(0);

		m_ssa.beginScope();

		while (it != end) {
			Value* var = new Value;

			const Type* arg_type = TypeTable::getType(it->first->getValue()->getName());
			const CString* arg_name = it->second->getValue()->getName();

			var->setName(arg_name);
			var->setTypePtr(arg_type);
			var->setType(Value::INTEGER);
			var->initialize();
			var->setModified();

			m_ssa.pushVar(var);
			vec->push_back(var);
			var->addRef();

			user_func->addArg(*arg_name, arg_type);

			++it;
		}

		vars->setVector(vec);
		user_func->setVars(vars);
	}

	m_funcs.push(user_func);

	expr->getBlock()->accept(*this);

	m_funcs.pop();

	if (args) {
		m_ssa.endScope();
	}

	emit(OP_JMP, &VM::end_func_handler);

	jmp->setJmpAddr2(getOpNum());
}

/**
 * Generates opcode for return statement
 */
AST_VISITOR(CodeGenVisitor, ReturnStmt) {
	ASTNode* value = expr->getExpr();
	Value* expr_value = value ? value->getValue() : NULL;
	const Function* func = m_funcs.empty() ? NULL : m_funcs.top();
	const Type* rtype = func ? func->getReturn() : NULL;

	/**
	 * Only for return inside function declaration
	 */
	if (func) {
		Compiler::checkFunctionReturn(func, expr_value, rtype, expr->getLocation());
	}

	if (expr_value) {
		expr_value->addRef();
	}

	emit(OP_RETURN, &VM::return_handler, expr_value);
}

/**
 * Generates opcodes for class declaration
 */
AST_VISITOR(CodeGenVisitor, ClassDeclaration) {
	UserTypeValue* type = new UserTypeValue(expr->getClassName());
	ClassDeclaration::DeclarationError error;	
	bool ok = expr->check(error);
	const CString* const class_name = expr->getClassName();

	if (ok) {
		//@TODO
		
		m_ssa.pushVar(type);
		
		
	}
	else {
		Compiler::errorf(error.getLocation(),
			"Redefinition of %s `%s' in class `%s'",
			(error.getType() == ClassDeclaration::DeclarationError::METHOD_DECLARATION) ?
				"method" : "attribute",
			error.getIdentifier().c_str(),
			class_name->str().c_str()
		);
	}
}

}} // clever::ast
