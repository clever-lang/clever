/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
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

#include "compiler/compiler.h"
#include "compiler/typechecker.h"
#include "compiler/cached_ptrs.h"
#include "types/nativetypes.h"
#include "interpreter/ast.h"
#include "interpreter/driver.h"

namespace clever { namespace ast {

/**
 * Evaluate the Type used in the expression, and the templated type as well
 */
static const Type* _evaluate_type(const location& loc,
	const Identifier* ident, Scope* scope) {
	const Type* type = scope->getType(ident->getName());

	// Check if the type wasn't declarated previously
	if (type == NULL) {
		Compiler::errorf(loc, "`%S' does not name a type",
			ident->getName());
	}

	TemplateArgsVector* template_args = ident->getTemplateArgs();

	if (template_args) {
		if (type->isTemplatedType()) {
			const TemplatedType* temp_type = (const TemplatedType*)type;

			TemplateArgs vec;
			const Type* argt;

			for (size_t i = 0; i < template_args->size(); ++i) {
				argt = g_scope.getType(template_args->at(i)->getName());

				const bool is_void = 
					(template_args->at(i)->getName()->str() == "Void");

				if (argt == NULL && !is_void) {
					Compiler::errorf(loc, "`%S' does not name a type",
						template_args->at(i)->getName());
				}

				if (is_void || !argt->isTemplatedType()) {
					vec.push_back(argt);
				}
				else {
					vec.push_back(_evaluate_type(loc,
						template_args->at(i), scope));
				}
			}

			const std::string* error = temp_type->checkTemplateArgs(vec);
			if (error) {
				Compiler::errorf(loc, error->c_str());
				delete error;
			}

			type = temp_type->getTemplatedType(vec);
		}
		else {
			Compiler::errorf(loc,
				"Type `%S' cannot accept template arguments!",
				type->getName());
		}
	}
	else if (type->isTemplatedType()) {
		// This check below is because alias does not have
		// the template args in their Identifier*, but
		// if the type pointed by an alias has a '>' in its
		// name is because we already checked and it is ok!
		if (((const TemplatedType*)type)->getName()->rfind('>')
			== std::string::npos) {
			Compiler::errorf(loc,
				"Missing template arguments for the type `%S'!",
				type->getName());
		}
	}

	return type;
}

/**
 * Concatenates arg type names with a supplied separator character
 */
static std::string _serialize_arg_type(TypeVector& arg_types, const char* sep) {
	if (arg_types.size() == 0) {
		return std::string("void");
	}

	clever_assert_not_null(arg_types[0]);

	std::string args_type_name = arg_types[0]->getName()->str();
	const std::string separator = std::string(sep);

	for (size_t i = 1, j = arg_types.size(); i < j; ++i) {
		args_type_name += separator;
		args_type_name += arg_types[i]->getName()->str();
	}

	return args_type_name;
}

/**
 * Performs a type compatible checking
 */
static bool _check_compatible_types(const Value* const lhs,
		const Value* const rhs) {

	clever_assert_not_null(lhs);
	clever_assert_not_null(rhs);

	/**
	 * Constants with different type cannot performs operation
	 */
	if (lhs->isPrimitive() && rhs->isPrimitive()
		&& lhs->getTypePtr() != CLEVER_STR
		&& rhs->getTypePtr()  != CLEVER_STR) {
		return true;
	}
	else if (lhs->getTypePtr() == CLEVER_STR
		&& rhs->getTypePtr() == CLEVER_STR) {
		return true;
	}

	return rhs->getTypePtr()->isConvertibleTo(lhs->getTypePtr());
}

static bool _check_compatible_types(const Type* const lhs,
		const Type* const rhs) {
	Value v1(lhs), v2(rhs);

	return _check_compatible_types(&v1, &v2);
}

/**
 * Checks the function return type
 */
static void _check_function_return(const Function* func, const Value* value,
	const location& loc) {
	const Type* rtype = func->getReturnType();
	/**
	 * When the rtype is NULL, the return is expected to be Void
	 * When value is NULL, the return statement is empty
	 */
	if (value && rtype == NULL) {
		Compiler::errorf(loc,
			"Function `%s' cannot return value, it was declared as Void!",
			func->getName().c_str());
	} else if ((value == NULL || value->getTypePtr() == NULL) && rtype) {
		Compiler::errorf(loc, "Function `%s' must return a value of type %S!",
			func->getName().c_str(), rtype->getName());
	} else if (value && rtype) {
		const Type* vtype = value->getTypePtr();

		if (value->isCallable()) {
			Compiler::errorf(loc,
				"Cannot return a function - not implemented yet!");
		} else if (vtype != rtype) {
			Compiler::errorf(loc,
				"Function `%s' expects %S value as return, not %S value",
				func->getName().c_str(), rtype->getName(), vtype->getName());
		}
	}
}

/**
 * Checks the number of arguments supplied to the function on call
 */
static void _check_function_num_args(const Function* func, int num_args,
		const location& loc) {

	clever_assert_not_null(func);

	int n_required_args = func->getNumArgs();
	int n_min_args = func->getMinNumArgs();
	bool is_variadic = func->isVariadic();

	if ((is_variadic && n_min_args > num_args)
		|| (!is_variadic && num_args != n_required_args)) {
		if (n_min_args != n_required_args && n_min_args > num_args) {
			Compiler::errorf(loc,
				"Function `%s' expects at least %i argument%s, %i supplied",
				func->getName().c_str(), n_min_args, 
				(n_min_args > 1 ? "s" : ""), num_args);
		} else {
			Compiler::errorf(loc,
				"Function `%s' expects %i argument%s, %i supplied",
				func->getName().c_str(), n_required_args,
					(n_required_args > 1 ? "s" : ""), num_args);
		}
	}
}

/**
 * Check the argument types
 */
static void _check_function_arg_types(const Function* func,
	ValueVector* arg_values, const location& loc) {
	const FunctionArgs& args = func->getArgs();
	FunctionArgs::const_iterator it(args.begin()), end(args.end());
	size_t i = 0;

	while (it != end) {
		Value* val = arg_values->at(i++);
		const Type* t1 = it->type;
		const Type* t2 = val->getTypePtr();

		if (t1 != t2) {
			if (!_check_compatible_types(t1, t2)) {
				CLEVER_SAFE_DELETE(arg_values);

				Compiler::errorf(loc,
					"Wrong param type #%N: expected `%S', but `%S' supplied",
						i, t1->getName(), t2->getName());
			}
		}

		if (val->isConst() && !it->constness) {
			Compiler::errorf(loc,
				"Cannot pass a const value on parameter `%s' where a "
				"non-const is expected in function `%s'",
				it->name.c_str(), func->getName().c_str());
		}
		++it;
	}
}

/**
 * Prepares the node to generate an opcode which will make a method call
 */
static CallableValue* _prepare_method_call(const Type* type, Value* var,
	const CString* mname, ASTNode* expr, const ValueVector* vv,
	bool is_static = false) {

	clever_assert_not_null(type);
	clever_assert_not_null(mname);
	if (is_static) {
		clever_assert_null(var);
	} else {
		clever_assert_not_null(var);
	}

	TypeVector args_types;

	if (EXPECTED(vv != NULL)) {
		for (size_t i = 0, j = vv->size(); i < j; ++i) {
			args_types.push_back(vv->at(i)->getTypePtr());
		}
	}

	const Method* method = type->getMethod(mname, &args_types);
	const std::string args_type_name = _serialize_arg_type(args_types, ", ");

	if (UNEXPECTED(method == NULL)) {
		if (mname == (CACHE_PTR(CLEVER_CTOR, CLEVER_CTOR_NAME))) {
			Compiler::errorf(expr->getLocation(),
				"No matching call for constructor %S::%S(%s)",
				type->getName(), type->getName(), args_type_name.c_str());
		} else if (is_static) {
			Compiler::errorf(expr->getLocation(), 
				"No matching call for %S::%S(%s)",
				type->getName(), mname, args_type_name.c_str());
		} else {
			Compiler::errorf(expr->getLocation(), 
				"No matching call for %S::%S(%s)",
				var->getTypePtr()->getName(), mname, args_type_name.c_str());
		}
	}

	if (method->isStatic() && !is_static) {
		Compiler::errorf(expr->getLocation(),
			"Cannot call static method %S::%S(%s) as non-static",
			type->getName(), mname, args_type_name.c_str());
	} else if (!method->isStatic() && is_static) {
		Compiler::errorf(expr->getLocation(),
			"Cannot call non-static method %S::%S(%s) as static",
			type->getName(), mname, args_type_name.c_str());
	}

	if (!is_static) {
		var->setTypePtr(type);

		if (UNEXPECTED(var->isConst() && !method->isConst())) {
			const std::string args_type_name = 
				_serialize_arg_type(args_types, ", ");

			Compiler::errorf(expr->getLocation(), "Can't call the non-const "
				"method %S::%S(%s) because variable `%S' is const",
				var->getTypePtr()->getName(), mname, args_type_name.c_str(),
				var->getName());
		}

		var->addRef();
	}

	CallableValue* call = new CallableValue(mname, type);
	call->setHandler(method);
	call->setContext(var);

	// Set the return type as the declared in the method
	Value* result = expr->getValue();

	if (result) {
		result->setTypePtr(method->getReturnType());
	}

	return call;
}

AST_VISITOR(TypeChecker, BreakNode) {
}

/**
 * Creates a vector with the current value from a Value* pointers
 */
AST_VISITOR(TypeChecker, ArgumentList) {
	ValueVector* values = new ValueVector();
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	values->reserve(nodes.size());

	while (EXPECTED(it != end)) {
		(*it)->acceptVisitor(*this);

		Value* value = (*it)->getValue();
		value->addRef();

		values->push_back(value);
		++it;
	}

	expr->setArgValue(values);
}

/**
 * Alias visitor
 */
AST_VISITOR(TypeChecker, AliasStmt) {
	if (expr->isId()) {
		Value* fvalue = m_scope->getValue(expr->getCurrentName());

		if (UNEXPECTED(fvalue == NULL)) {
			Compiler::errorf(expr->getLocation(),
				"Identifier `%S' not found!", expr->getCurrentName());
		}

		if (UNEXPECTED(m_scope->getValue(expr->getNewName()))) {
			Compiler::errorf(expr->getLocation(),
				"Name `%S' already in use!", expr->getNewName());
		}

		m_scope->pushValue(expr->getNewName(), fvalue);
		fvalue->addRef();
	} else {
		const Type* ftype = _evaluate_type(expr->getLocation(),
			expr->getCurrentNameIdentifier(), m_scope);

		if (UNEXPECTED(ftype == NULL)) {
			Compiler::errorf(expr->getLocation(),
				"Type `%S' not found!", expr->getCurrentName());
		}

		if (UNEXPECTED(g_scope.getType(expr->getNewName()))) {
			Compiler::errorf(expr->getLocation(),
				"Name `%S' already in use!", expr->getNewName());
		}

		m_scope->pushType(expr->getNewName(), ftype);
		const_cast<Type*>(ftype)->addRef();
	}
}

/**
 * Constant visitor
 */
AST_VISITOR(TypeChecker, Constant) {
	Value* constant = m_scope->getValue(expr->getName());

	if (UNEXPECTED(constant == NULL)) {
		Compiler::errorf(expr->getLocation(), "Constant `%S' not found!",
			expr->getName());
	}

	Value* value = new Value;
	value->copy(constant);

	expr->setValue(value);
}

/**
 * Regex pattern syntax visitor
 */
AST_VISITOR(TypeChecker, RegexPattern) {
	const Type* type = g_pkgmanager.getTypeByModule(CSTRING("std"),
		CSTRING("regex"), CSTRING("Regex"));

	if (UNEXPECTED(type == NULL)) {
		Compiler::error("Regex module must be loaded to use the regex syntax!");
	}

	// Sets the argument vector for the Pcre constructor
	ValueVector* arg_values = new ValueVector;
	arg_values->push_back(expr->getRegex());

	expr->setArgsValue(arg_values);

	expr->setValue(new Value);

	// The Pcre constructor CallableValue
	expr->setCallValue(_prepare_method_call(type, expr->getValue(),
		CACHE_PTR(CLEVER_CTOR, CLEVER_CTOR_NAME), expr, arg_values));

	expr->getCallValue()->addRef();
}

/**
 * Identifier visitor
 */
AST_VISITOR(TypeChecker, Identifier) {
	Value* ident = m_scope->getValue(expr->getName());

	if (ident == NULL) {
		Compiler::errorf(expr->getLocation(), "Variable `%S' not found!",
			expr->getName());
	}

	if (ident->isCallable()) {
		const Function* func = 
			static_cast<CallableValue*>(ident)->getFunction();
		const FunctionArgs& args = func->getArgs();

		TypeVector tv;
		tv.push_back(func->getReturnType());

		for (size_t i = 0, sz = args.size(); i < sz; ++i) {
			tv.push_back(args[i].type);
		}

		const TemplatedType* const virtual_func =
			static_cast<const TemplatedType*>(CLEVER_TYPE("Function"));

		const Type* func_type = virtual_func->getTemplatedType(tv);

		FunctionValue* fv = 
			static_cast<FunctionValue*>(func_type->allocateValue());
		fv->setFunction(func);

		ident->setTypePtr(func_type);
		ident->setDataValue(fv);
		static_cast<CallableValue*>(ident)
			->setCallableType(CallableValue::FUNCTION);
	}

	// Associate the Value* of the symbol to the identifier
	expr->setValue(ident);
	ident->addRef();
}

/**
 * Unary expression visitor
 */
AST_VISITOR(TypeChecker, UnaryExpr) {
	Value* var = expr->getExpr()->getValue();
	const CString* method_name = NULL;

	switch (expr->getOp()) {
		case ast::NOT:
			method_name = CACHE_PTR(CLEVER_OP_NOT, CLEVER_OPERATOR_NOT);
			break;
		case ast::BW_NOT:
			method_name = CACHE_PTR(CLEVER_OP_BW_NOT, CLEVER_OPERATOR_BW_NOT);
			break;
		case ast::PRE_INC:
			method_name = CACHE_PTR(CLEVER_OP_PRE_INC, CLEVER_OPERATOR_PRE_INC);
			break;
		case ast::PRE_DEC:
			method_name = CACHE_PTR(CLEVER_OP_PRE_DEC, CLEVER_OPERATOR_PRE_DEC);
			break;
		case ast::POS_INC:
			method_name = CACHE_PTR(CLEVER_OP_POS_INC, CLEVER_OPERATOR_POS_INC);
			break;
		case ast::POS_DEC:
			method_name = CACHE_PTR(CLEVER_OP_POS_DEC, CLEVER_OPERATOR_POS_DEC);
			break;
		EMPTY_SWITCH_DEFAULT_CASE();
	}

	clever_assert_not_null(method_name);

	expr->setValue(new Value);

	expr->setCallValue(_prepare_method_call(var->getTypePtr(), var, method_name,
		expr, NULL));

	expr->getCallValue()->addRef();
}

/**
 * Binary expression visitor
 */
AST_VISITOR(TypeChecker, BinaryExpr) {
	const CString* method_name = NULL;

	expr->getLhs()->acceptVisitor(*this);
	expr->getRhs()->acceptVisitor(*this);

	Value* lhs = expr->getLhs()->getValue();
	Value* rhs = expr->getRhs()->getValue();

	bool is_assigned = expr->isAssigned();

	if (UNEXPECTED(is_assigned && lhs->isConst())) {
		Compiler::errorf(expr->getLocation(),
			"Can't assign to variable `%S' because it is const",
			lhs->getName());
	}

	const Type* lhs_type = lhs->getTypePtr();

	// Operator method names
	switch (expr->getOp()) {
		case PLUS:
			method_name = CACHE_PTR(CLEVER_OP_PLUS, CLEVER_OPERATOR_PLUS);
			break;
		case DIV:
			method_name = CACHE_PTR(CLEVER_OP_DIV, CLEVER_OPERATOR_DIV);
			break;
		case MULT:
			method_name = CACHE_PTR(CLEVER_OP_MULT, CLEVER_OPERATOR_MULT);
			break;
		case MINUS:
			method_name = CACHE_PTR(CLEVER_OP_MINUS, CLEVER_OPERATOR_MINUS);
			break;
		case MOD:
			method_name = CACHE_PTR(CLEVER_OP_MOD, CLEVER_OPERATOR_MOD);
			break;
		case XOR:
			method_name = CACHE_PTR(CLEVER_OP_BW_XOR, CLEVER_OPERATOR_BW_XOR);
			break;
		case BW_OR:
			method_name = CACHE_PTR(CLEVER_OP_BW_OR, CLEVER_OPERATOR_BW_OR);
			break;
		case BW_AND:
			method_name = CACHE_PTR(CLEVER_OP_BW_AND, CLEVER_OPERATOR_BW_AND);
			break;
		case GREATER:
			method_name = CACHE_PTR(CLEVER_OP_GREATER, CLEVER_OPERATOR_GREATER);
			break;
		case LESS:
			method_name = CACHE_PTR(CLEVER_OP_LESS, CLEVER_OPERATOR_LESS);
			break;
		case GREATER_EQUAL:
			method_name = CACHE_PTR(CLEVER_OP_GE, CLEVER_OPERATOR_GE);
			break;
		case LESS_EQUAL:
			method_name = CACHE_PTR(CLEVER_OP_LE, CLEVER_OPERATOR_LE);
			break;
		case EQUAL:
			method_name = CACHE_PTR(CLEVER_OP_EQUAL, CLEVER_OPERATOR_EQUAL);
			break;
		case NOT_EQUAL:
			method_name = CACHE_PTR(CLEVER_OP_NE, CLEVER_OPERATOR_NE);
			break;
		case LSHIFT:
			method_name = CACHE_PTR(CLEVER_OP_LSHIFT, CLEVER_OPERATOR_LSHIFT);
			break;
		case RSHIFT:
			method_name = CACHE_PTR(CLEVER_OP_RSHIFT, CLEVER_OPERATOR_RSHIFT);
			break;
		case OR:
		case AND:
			expr->setResult(new Value(CLEVER_BOOL));
			return;
		EMPTY_SWITCH_DEFAULT_CASE();
	}

	clever_assert_not_null(method_name);

	ValueVector* arg_values = new ValueVector;

	arg_values->push_back(lhs);
	arg_values->push_back(rhs);

	expr->setArgsValue(arg_values);

	if (is_assigned) {
		expr->setResult(lhs);
		lhs->addRef();
	} else {
		expr->setResult(new Value);
	}

	expr->setCallValue(_prepare_method_call(lhs->getTypePtr(), lhs,
		method_name, expr, arg_values));

	if (expr->isAssigned()) {
		/**
		 * When using the compound assignment expression (e.g. +=),
		 * we have to restore the original Type ptr, since we aren't in
		 * a temporary expression, but in an assignment to a variable
		 * with its defined type
		 */
		expr->getValue()->setTypePtr(lhs_type);
	}

	expr->getCallValue()->addRef();
}

/**
 * Variable declaration visitor
 */
AST_VISITOR(TypeChecker, VariableDecl) {
	const Type* type = NULL;

	if (EXPECTED(expr->getType() != NULL)) {
		type = _evaluate_type(expr->getLocation(),
			expr->getType(), m_scope);
	}

	Identifier* variable = expr->getVariable();

	// Check if there is already a variable with same name in the current scope
	if (EXPECTED(m_scope->getLocalValue(variable->getName()) != NULL)) {
		Compiler::errorf(expr->getLocation(),
			"Already exists a variable named `%S' in the current scope!",
			variable->getName());
	}

	Value* var = new Value();
	var->setName(variable->getName());
	var->setTypePtr(type);
	var->addRef();

	variable->setValue(var);

	ASTNode* rhs = expr->getRhs();
	ArgumentList* ctor_list = expr->getConstructorArgs();
	bool is_auto = false;
	bool is_const = expr->isConst();

	if (rhs) {
		Value* initval = rhs->getValue();

		if (type) {
			if (!_check_compatible_types(var, initval)) {
				var->delRef();

				Compiler::errorf(expr->getLocation(),
					"Cannot convert `%S' to `%S' on assignment",
					initval->getTypePtr()->getName(),
					type->getName());
			}
		}
		else {
			// `auto' typed, so the variable's type is the type of rhs
			type = initval->getTypePtr();
			var->setTypePtr(type);
			is_auto = true;
			is_const = initval->isConst();
		}

		// Building ValueVector of arguments for __assign__ method call
		ValueVector* arg_values = new ValueVector;
		arg_values->push_back(initval);
		initval->addRef();

		expr->setArgsValue(arg_values);

		expr->setCallValue(_prepare_method_call(type, var,
			CACHE_PTR(CLEVER_OP_ASSIGN, CLEVER_OPERATOR_ASSIGN),
			expr, arg_values));
	}
	else /*if (ctor_list)*/ {
		ValueVector* arg_values = (ctor_list ? ctor_list->getArgValue() : NULL);
		
		if (arg_values) {
			expr->setArgsValue(arg_values);
		}
		
		expr->setCallValue(_prepare_method_call(type, var,
			CACHE_PTR(CLEVER_CTOR, CLEVER_CTOR_NAME), expr, arg_values));
	}
	/*else {
		DataValue* data_value = type->allocateValue();

		if (data_value) {
			var->setDataValue(data_value);
		}
	}*/

	var->setConstness(is_const);

	if (rhs) {
		if (!is_auto && !expr->isConst() && rhs->getValue()->isConst()) {
			Compiler::errorf(expr->getLocation(),
				"Cannot convert const-qualified variable `%S' to a "
				"non-const variable of type `%S' on assignment",
				variable->getName(),
				type->getName());
		}
		else {
			var->setConstness(expr->isConst() || rhs->getValue()->isConst());
		}
	}

	// Registers a new variable
	m_scope->pushValue(var->getName(), var);
}

/**
 * If statement visitor
 */
AST_VISITOR(TypeChecker, IfExpr) {
	expr->getCondition()->acceptVisitor(*this);

	bool if_has_return = false;
	bool else_has_return = false;

	if (EXPECTED(expr->hasBlock())) {
		expr->getBlock()->acceptVisitor(*this);
		if_has_return = expr->getBlock()->hasReturn();
	}

	if (expr->hasElseIf()) {
		const NodeList& elseif_nodes = expr->getNodes();
		NodeList::const_iterator it = elseif_nodes.begin(),
			end = elseif_nodes.end();

		while (it != end) {
			ElseIfExpr* elseif = static_cast<ElseIfExpr*>(*it);

			elseif->getCondition()->acceptVisitor(*this);

			if (elseif->hasBlock()) {
				elseif->getBlock()->acceptVisitor(*this);
			}
			++it;
		}
	}

	if (expr->hasElseBlock()) {
		expr->getElse()->acceptVisitor(*this);
		else_has_return = expr->getElse()->hasReturn();
	}

	// If the IfStmt AND the ElseStmt has return, we
	// are sure that that it inconditionally returns
	if (if_has_return && else_has_return) {
		expr->setReturn();
	}
}

/**
 * Block visitor
 */
AST_VISITOR(TypeChecker, BlockNode) {
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	// Create a new scope
	m_scope = m_scope->newChild();
	expr->setScope(m_scope);

	// Iterates over statements inside the block
	while (EXPECTED(it != end)) {
		(*it)->acceptVisitor(*this);

		if ((*it)->hasReturn()) {
			expr->setReturn();
		}

		++it;
	}

	m_scope = m_scope->getParent();
}

/**
 * Unscoped Block visitor
 */
AST_VISITOR(TypeChecker, UnscopedBlockNode) {
	if (!expr->hasBlock()) {
		return;
	}

	const CString* alias = expr->getAlias();
	const NodeList& nodes = expr->getBlock()->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	// Iterates over statements inside the block
	while (EXPECTED(it != end)) {
		(*it)->acceptVisitor(*this);

		if ((*it)->hasReturn()) {
			expr->setReturn();
		}

		++it;
	}

	if (alias) {
		std::string prefix = alias->str() + "::";
		g_pkgmanager.copyScopeToAlias(m_scope, prefix);
	}
}

/**
 * Variable declaration list visitor
 */
AST_VISITOR(TypeChecker, VarDecls) {
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	// Declare all the variable in the declaration list
	while (EXPECTED(it != end)) {
		(*it)->acceptVisitor(*this);
		++it;
	}
}

/**
 * While statement visitor
 */
AST_VISITOR(TypeChecker, WhileExpr) {
	expr->getCondition()->acceptVisitor(*this);

	if (EXPECTED(expr->hasBlock())) {
		expr->getBlock()->acceptVisitor(*this);

		if (expr->getBlock()->hasReturn()) {
			expr->setReturn();
		}
	}
}

/**
 * For statement visitor
 */
AST_VISITOR(TypeChecker, ForExpr) {
	if (expr->isIteratorMode()) {
		return;
	}

	m_scope = m_scope->newChild();

	if (EXPECTED(expr->getVarDecl())) {
		expr->getVarDecl()->acceptVisitor(*this);
	}

	if (EXPECTED(expr->getCondition())) {
		expr->getCondition()->acceptVisitor(*this);
	}

	if (EXPECTED(expr->hasBlock())) {
		expr->getBlock()->acceptVisitor(*this);

		if (expr->getBlock()->hasReturn()) {
			expr->setReturn();
		}
	}

	if (EXPECTED(expr->getIncrement())) {
		expr->getIncrement()->acceptVisitor(*this);
	}

	m_scope = m_scope->getParent();
}

/**
 * ForEach visitor
 */
AST_VISITOR(TypeChecker, ForEachExpr) {
	if (!expr->hasBlock()) {
		return;
	}

	Value* instance = expr->getVar()->getValue();
	const Type* instancetype = instance->getTypePtr();

	clever_assert_not_null(instancetype);

	/* TODO: Change to Iterable */
	if (!instancetype->implementsInterface(CLEVER_TYPE("Iterator"))) {
		Compiler::error("Variable type doesn't implements Iterator interface");
	}

	/**
	 * for (instance in var):
	 *   => Get the iterator from instance and create the variable using such
	 * value and assign to `var'
	 *   => Emit the opcode to iterator constructor call passing the `instance'
	 *
	 *   Internal view:
	 *      Instance foo;
	 *      InstanceIterator var(foo); // InstanceIterator = foo->getIterator()
	 *
	 *   Loop {
	 *     => Call Iterator valid() method to check if the loop will happens
	 *     Do something if success...
	 *     => Call Iterator next() method
	 *   }
	 */

	Identifier* ident = expr->getIdentifier();

	// Create a new scope
	m_scope = m_scope->newChild();

	// Create the iterator variable
	Value* iterator = instancetype->getIterator();

	if (iterator == NULL) {
		Compiler::errorf(expr->getLocation(),
			"Type `%S' has no iterator!", instancetype->getName());
	}

	const Type* type = iterator->getTypePtr();

	iterator->setName(ident->getName());

	// Register the variable in the new scope
	m_scope->pushValue(ident->getName(), iterator);

	// Building ValueVector of arguments for ctor call
	ValueVector* arg_values = new ValueVector;
	arg_values->push_back(instance);
	instance->addRef();

	expr->setValue(iterator);
	iterator->addRef();

	// Preparing the Iterator ctor call
	expr->setCtorArgsValue(arg_values);
	expr->setCtorCallValue(_prepare_method_call(type, iterator,
		CACHE_PTR(CLEVER_CTOR, CLEVER_CTOR_NAME), expr, arg_values));
	expr->setCtorResult(expr->getValue());

	expr->setValue(new Value);

	// valid method call
	expr->setValidCallValue(_prepare_method_call(type, iterator,
		CSTRING("valid"), expr, NULL));
	expr->setValidResult(expr->getValue());

	expr->setValue(new Value);

	// next method call
	expr->setNextCallValue(_prepare_method_call(type, iterator,
		CSTRING("next"), expr, NULL));
	expr->setNextResult(expr->getValue());

	// Iteration code block
	expr->getBlock()->acceptVisitor(*this);

	m_scope = m_scope->getParent();
}

/**
 * Assignment expression visitor
 */
AST_VISITOR(TypeChecker, AssignExpr) {
	Value* lhs = expr->getLhs()->getValue();
	Value* rhs = expr->getRhs()->getValue();

	if (UNEXPECTED(!_check_compatible_types(lhs, rhs))) {
		Compiler::errorf(expr->getLocation(),
			"Cannot convert `%S' to `%S' on assignment",
			rhs->getTypePtr()->getName(),
			lhs->getTypePtr()->getName());
	}

	if (UNEXPECTED(lhs->isConst())) {
		Compiler::errorf(expr->getLocation(),
			"Can't assign to variable `%S' because it is const",
			lhs->getName());
	}

	ValueVector* arg_values = new ValueVector;
	arg_values->push_back(rhs);
	rhs->addRef();

	expr->setArgsValue(arg_values);

	expr->setCallValue(_prepare_method_call(lhs->getTypePtr(), lhs,
		CACHE_PTR(CLEVER_OP_ASSIGN, CLEVER_OPERATOR_ASSIGN), expr,
			arg_values));

	expr->getCallValue()->addRef();

	expr->setValue(lhs);
}

static inline const char* _find_fcall_rname(const Type* c) {
	if (c == CLEVER_INT)    return "i";
	if (c == CLEVER_DOUBLE) return "d";
	if (c == CLEVER_STR)    return "s";
	if (c == CLEVER_BOOL)   return "b";
	if (c == CLEVER_BYTE)   return "c";
	if (c == CLEVER_VOID)   return "v";
	return "p";
}

/**
 * Function call visitor
 */
AST_VISITOR(TypeChecker, FunctionCall) {
	const CString* const name = expr->getFuncName();

	clever_assert_not_null(name);

	Value* fvalue = m_scope->getValue(name);

	if (UNEXPECTED(fvalue == NULL || !fvalue->isCallable())) {
		Compiler::errorf(expr->getLocation(), "Function `%S' does not exists!",
			name);
	}

	const Function* func = static_cast<CallableValue*>(fvalue)->getFunction();

	int num_args = 
		expr->getArgs() ? int(expr->getArgs()->getNodes().size()) : 0;

	clever_assert_not_null(func);

	_check_function_num_args(func, num_args, expr->getLocation());

	Value* result = new Value;

	if (func->isExternal()) {
		ArgumentList* args = expr->getArgs();

		if (args == NULL) {
			args = new ArgumentList;
			expr->setArgs(args);
			args->addRef();
		}

		std::string rt = _find_fcall_rname(func->getReturnType());

		args->add(new StringLiteral(CSTRING(func->getLibName())));
		args->add(new StringLiteral(CSTRING(rt)));
		args->add(new StringLiteral(CSTRING(func->getLFName())));

		num_args += 3;
	}

	// Set the return type
	result->setTypePtr(func->getReturnType());
	result->setConstness(func->hasReturnConst());

	expr->setValue(result);

	if (num_args) {
		expr->getArgs()->acceptVisitor(*this);

		ValueVector* arg_values = expr->getArgs()->getArgValue();

		_check_function_arg_types(func, arg_values,	expr->getLocation());

		expr->setArgsValue(arg_values);
	}

	expr->getValue()->addRef();
	expr->setFuncValue(static_cast<CallableValue*>(fvalue));
	fvalue->addRef();
}

/**
 * MethodCall visitor
 */
AST_VISITOR(TypeChecker, MethodCall) {
	if (expr->isStaticCall()) {
		Identifier* type_name = static_cast<Identifier*>(expr->getVariable());
		const Type* type = m_scope->getType(type_name->getName());
		const CString* const name = expr->getMethodName();
		ValueVector* arg_values = NULL;

		if (UNEXPECTED(type == NULL)) {
			Compiler::errorf(expr->getLocation(), "Type `%S' not found",
				type_name->getName());
		}

		clever_assert_not_null(type);

		ArgumentList* args = expr->getArgs();

		if (EXPECTED(args != NULL)) {
			arg_values = args->getArgValue();

			expr->setArgsValue(arg_values);
		}

		expr->setValue(new Value);

		expr->setCallValue(_prepare_method_call(type, NULL,
			name, expr, arg_values, true));
	} else {
		Value* variable = expr->getVariable()->getValue();
		const CString* const name = expr->getMethodName();
		ValueVector* arg_values = NULL;

		clever_assert_not_null(variable);
		clever_assert_not_null(name);

		ArgumentList* args = expr->getArgs();

		if (EXPECTED(args != NULL)) {
			arg_values = args->getArgValue();

			expr->setArgsValue(arg_values);
		}

		expr->setValue(new Value);

		expr->setCallValue(_prepare_method_call(variable->getTypePtr(),
			variable, name, expr, arg_values));
	}
}

/**
 * Import statement visitor
 */
AST_VISITOR(TypeChecker, ImportStmt) {
	Scope* scope = m_scope;

	if (UNEXPECTED(isInteractive() && !scope->isGlobal())) {
		scope = &g_scope;
	}

	Compiler::import(scope, expr->getPackageName(), expr->getModuleName(),
		expr->getObjectName(), expr->getAliasName(), expr->isType());
}

/**
 * Function declaration visitor
 */
AST_VISITOR(TypeChecker, FuncPrototype) {
	const CString* name = expr->getName();
	CallableValue* func = new CallableValue(name);
	Function* user_func = new Function(name->str());
	Identifier* return_type = expr->getReturnValue();
	ArgumentDeclList* args = expr->getArgs();

	// Mark the function as user defined function
	user_func->setUserDefined();

	func->addRef();
	m_scope->pushValue(func->getName(), func);

	func->setHandler(user_func);

	// Set the return type
	if (EXPECTED(return_type != NULL)) {
		const Type* rtype = NULL;

		if (return_type->getName() != CACHE_PTR(CLEVER_VOID_STR, "Void")) {
			rtype = _evaluate_type(expr->getLocation(), return_type,
				m_scope);
		}
		user_func->setReturnType(rtype);
	}

	if (args) {
		ArgumentDecls& arg_nodes = args->getArgs();
		ArgumentDecls::iterator it = arg_nodes.begin(),
			end = arg_nodes.end();

		while (EXPECTED(it != end)) {
			const Type* arg_type = _evaluate_type(expr->getLocation(),
				it->type, m_scope);
			const CString* arg_name = it->name->getName();

			user_func->addArg(*arg_name, arg_type, it->constness);

			++it;
		}
	}
}

AST_VISITOR(TypeChecker, FuncDeclaration) {
	// We can't have a function declaration without a block
	if (UNEXPECTED(!expr->hasBlock())) {
		Compiler::error("Cannot declare a function without a block",
			expr->getLocation());
	}

	const CString* name = expr->getName();
	CallableValue* func = NULL;
	Function* user_func = NULL;
	bool has_prototype = false;
	Value* val = m_scope->getValue(name);
	
	if (val) {		
		if (!val->isCallable()) {
			Compiler::errorf(expr->getLocation(),
				"Name `%S' already in use for variable!", name);
		}

		func = static_cast<CallableValue*>(val);
		user_func = const_cast<Function*>(func->getFunction());
		has_prototype = true;
	} else {
		func = new CallableValue(name);
		user_func = new Function(name->str());		
	}

	Identifier* return_type = expr->getReturnValue();
	ArgumentDeclList* args = expr->getArgs();
	const Type* rtype = NULL;

	if (EXPECTED(return_type != NULL)) {
		if (return_type->getName() != CACHE_PTR(CLEVER_VOID_STR, "Void")) {
			rtype = _evaluate_type(expr->getLocation(), return_type,
				m_scope);
		}
	}

	// Check if the prototype fits the function declaration
	if (has_prototype) {
		const Type* rtype2 = user_func->getReturnType();

		if (rtype != rtype2) {
			Compiler::errorf(expr->getLocation(),
				"Function declaration `%S' uses a different return type than "
				"the prototype",
				name);
		}
	} else {
		// Mark the function as user defined function
		user_func->setUserDefined();

		func->addRef();
		func->setHandler(user_func);
		m_scope->pushValue(func->getName(), func);

		// Set the return type
		if (EXPECTED(return_type != NULL)) {
			user_func->setReturnType(rtype);
		}
		// Set the return constness
		user_func->setReturnConst(expr->hasReturnConst());

		func->setConstness(expr->hasReturnConst());
	}

	expr->setValue(func);

	if (args) {
		ArgumentDecls& arg_nodes = args->getArgs();
		ArgumentDecls::iterator it = arg_nodes.begin(),
			end = arg_nodes.end();

		if (func->isMethod()) {
			// TODO: assert whether the child's class is an orphaned scope
			m_scope = m_scope->newChild();
		} else {
			m_scope = m_scope->newOrphanedChild();
		}

		user_func->setScope(m_scope);

		while (EXPECTED(it != end)) {
			Value* var = new Value;

			const Type* arg_type = _evaluate_type(expr->getLocation(),
				it->type, m_scope);
			const CString* arg_name = it->name->getName();

			var->setName(arg_name);
			var->setTypePtr(arg_type);
			var->initialize();
			var->setConstness(it->constness);

			m_scope->pushValue(var->getName(), var);

			if (!has_prototype) {
				user_func->addArg(*arg_name, arg_type, it->constness);
			}

			++it;
		}
	}

	m_funcs.push(user_func);

	expr->getBlock()->acceptVisitor(*this);

	if (user_func->getReturnType() && expr->getBlock()->hasReturn() == false) {
		Compiler::errorf(expr->getLocation(), "Function `%S' must return "
			"a value of type `%S', and it may not return",
			name, user_func->getReturnType()->getName());
	}

	m_funcs.pop();

	if (args) {
		m_scope = m_scope->getParent();
	}
}

/**
 * External Function declaration visitor
 */
AST_VISITOR(TypeChecker, ExtFuncDeclaration) {

	Identifier* return_type = expr->getReturnValue();

	const Type* rtype = CLEVER_VOID;

	if (return_type->getName() != CACHE_PTR(CLEVER_VOID_STR, "Void")) {
		rtype = _evaluate_type(expr->getLocation(), return_type, m_scope);
	}

	const CString* lfname = expr->getLFName();
	const CString* libname = expr->getLibName();
	const CString* name = expr->getName();

	CallableValue* func = new CallableValue(name);
	CallableValue* ext_func = static_cast<CallableValue*>(
		m_scope->getValue(CSTRING("__call_ext_func__")));

	if (ext_func == NULL) {
		Compiler::error("Cannot use extern syntax, FFI module is disabled!");
	}

	Function* m_func;

	if (lfname == NULL) {
		m_func = new Function(libname->c_str(), name->c_str(), rtype,
			ext_func->getFunctionPtr());
	} else {
		m_func = new Function(libname->c_str(), lfname->c_str(), name->c_str(),
			rtype, ext_func->getFunctionPtr());
	}

	ArgumentDeclList* args = expr->getArgs();

	m_scope->pushValue(func->getName(), func);

	func->setHandler(m_func);

	if (args) {
		ArgumentDecls& arg_nodes = args->getArgs();
		ArgumentDecls::iterator it = arg_nodes.begin(), end = arg_nodes.end();

		while (EXPECTED(it != end)) {
			const Type* arg_type = _evaluate_type(expr->getLocation(),
				it->type, m_scope);
			const CString* arg_name = it->name->getName();


			m_func->addArg(*arg_name, arg_type, it->constness);

			++it;
		}
	}
}


/**
 * Return statement visitor
 */
AST_VISITOR(TypeChecker, ReturnStmt) {
	// Only for return statement inside function declaration
	if (UNEXPECTED(m_funcs.empty())) {
		return;
	}

	const Function* func = m_funcs.top();

	_check_function_return(func, expr->getExprValue(), expr->getLocation());
}

/**
 * Type creation visitor
 */
AST_VISITOR(TypeChecker, TypeCreation) {
	Identifier* ident = expr->getIdentifier();
	const Type* type = m_scope->getType(ident->getName());
	ValueVector* arg_values = NULL;

	// Check if the type wasn't declarated previously
	if (UNEXPECTED(type == NULL)) {
		Compiler::errorf(expr->getLocation(), "`%S' does not name a type",
			ident->getName());
	}

	ArgumentList* args = expr->getArgs();

	if (args != NULL) {
		arg_values = args->getArgValue();

		expr->setArgsValue(arg_values);
	}

	expr->setValue(new Value);

	expr->setCallValue(_prepare_method_call(type, expr->getValue(),
		CACHE_PTR(CLEVER_CTOR, CLEVER_CTOR_NAME), expr, arg_values));
}

/**
 * Subscript operator visitor
 */
AST_VISITOR(TypeChecker, Subscript) {
	Value* var = expr->getIdentifier()->getValue();
	Value* expr_val = expr->getExpr()->getValue();

	clever_assert_not_null(expr_val);

	ValueVector* arg_values = new ValueVector;
	arg_values->push_back(expr_val);
	expr_val->addRef();

	expr->setArgsValue(arg_values);

	expr->setValue(new Value);

	expr->setCallValue(_prepare_method_call(var->getTypePtr(), var,
		CACHE_PTR(CLEVER_OP_AT, CLEVER_OPERATOR_AT), expr, arg_values));

	expr->getCallValue()->addRef();
}

/**
 * Class declaration visitor
 */
AST_VISITOR(TypeChecker, ClassDeclaration) {
	Compiler::error("Not implemented yet!");
}

/**
 * ArrayList type visitor
 */
AST_VISITOR(TypeChecker, ArrayList) {
	ValueVector* vv = expr->getArgList()->getArgValue();
	const Type* value_type = vv->at(0)->getTypePtr();

	for (size_t i = 1, sz = vv->size(); i < sz; ++i) {
		if (vv->at(i)->getTypePtr() != value_type) {
			Compiler::errorf(expr->getLocation(),
				"Cannot use Array initializer list with "
				"different value types");
		}
	}

	const Type* const arr_type = CLEVER_TPL_ARRAY(value_type);

	Value* var = new Value(arr_type);
	var->setDataValue(new ArrayValue(vv));
	expr->setValue(var);
}

/**
 * Map visitor
 */
AST_VISITOR(TypeChecker, MapList) {
	ValueVector* vv = expr->getArgList()->getArgValue();
	const Type* key_type = vv->at(0)->getTypePtr();
	const Type* value_type = vv->at(1)->getTypePtr();

	for (size_t i = 2, sz = vv->size(); i < sz; i += 2) {
		if (vv->at(i)->getTypePtr() != key_type) {
			Compiler::errorf(expr->getLocation(),
				"Cannot use Map list with "
				"different key types");
		}
	}

	for (size_t i = 3, sz = vv->size(); i < sz; i += 2) {
		if (vv->at(i)->getTypePtr() != value_type) {
			Compiler::errorf(expr->getLocation(),
				"Cannot use Map list with "
				"different value types");
		}
	}

	const TemplatedType* const virtual_map =
		static_cast<const TemplatedType*>(CLEVER_TYPE("Map"));

	// Checks if the key type meets the requirements
	TypeVector tv(2);
	tv[0] = key_type;
	tv[1] = value_type;

	const std::string* error = virtual_map->checkTemplateArgs(tv);

	if (error) {
		Compiler::errorf(expr->getLocation(),
			error->c_str());
		delete error;
	}

	// Gets the proper Map type
	const Type* map_type = virtual_map->getTemplatedType(key_type,
		value_type);

	MapValue* mv = static_cast<MapValue*>(map_type->allocateValue());
	MapValue::ValueType& map = mv->getMap();

	// Fills the map
	for (size_t i = 0, sz = vv->size(); i < sz; i += 2) {
		map[vv->at(i)] = vv->at(i + 1);
	}

	Value* var = new Value(map_type);
	var->setDataValue(mv);
	expr->setValue(var);

	delete vv;
}

/**
 * Lambda visitor
 */
AST_VISITOR(TypeChecker, LambdaFunction) {
	const TemplatedType* const virtual_func =
		static_cast<const TemplatedType*>(CLEVER_TYPE("Function"));

	const FunctionArgs& args = expr->getArgs();

	TypeVector tv;
	tv.push_back(expr->getReturnType());

	for (size_t i = 0, sz = args.size(); i < sz; ++i) {
		tv.push_back(args[i].type);
	}

	const Type* lambda_type = virtual_func->getTemplatedType(tv);
	
	FunctionValue* fv = 
		static_cast<FunctionValue*>(lambda_type->allocateValue());
	
	fv->setFunction(expr->getFunction());

	Value* var = new Value(lambda_type);
	var->setDataValue(fv);
	expr->setValue(var);
}

/**
 * Copy visitor
 */
AST_VISITOR(TypeChecker, CopyExpr) {
	Value* val = expr->getExpr()->getValue();

	if (val->isPrimitive()) {
		expr->setValue(val);
		return;
	}

	ValueVector* arg_values = new ValueVector;
	arg_values->push_back(val);
	val->addRef();

	expr->setValue(new Value);
	expr->setArgsValue(arg_values);

	if (expr->isDeepCopy()) {
		expr->setCallValue(_prepare_method_call(val->getTypePtr(), val,
			CACHE_PTR(CLEVER_DEEP_COPY, CLEVER_DEEP_COPY_NAME), 
			expr, arg_values));
	} else {
		expr->setCallValue(_prepare_method_call(val->getTypePtr(), val,
			CACHE_PTR(CLEVER_COPY, CLEVER_COPY_NAME), expr, arg_values));
	}

	expr->getCallValue()->addRef();
}

}} // clever::ast
