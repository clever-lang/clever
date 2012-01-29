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
#include "types/nativetypes.h"
#include "interpreter/ast.h"
#include "interpreter/driver.h"

namespace clever { namespace ast {

/**
 * Evaluate the Type used in the expression, and the templated type as well
 */
static const Type* _evaluate_type(const location& loc,
	const Identifier* ident) {
	const Type* type = g_symtable.getType(ident->getName());

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
				argt = g_symtable.getType(template_args->at(i)->getName());

				if (argt == NULL) {
					Compiler::errorf(loc, "`%S' does not name a type",
						template_args->at(i)->getName());
				}

				if (!argt->isTemplatedType()) {
					vec.push_back(argt);
				}
				else {
					vec.push_back(_evaluate_type(loc, template_args->at(i)));
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
		Compiler::errorf(loc,
			"Missing template arguments for the type `%S'!",
			type->getName());
	}

	return type;
}

/**
 * Concatenates arg type names with a supplied separator character
 */
static std::string _serialize_arg_type(TypeVector& args_types, const char* sep) {
	if (args_types.size() == 0) {
		return std::string("void");
	}

	clever_assert_not_null(args_types[0]);

	std::string args_type_name = args_types[0]->getName()->str();
	const std::string separator = std::string(sep);

	for (size_t i = 1, j = args_types.size(); i < j; ++i) {
		args_type_name += separator;
		args_type_name += args_types[i]->getName()->str();
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

	/**
	 * @TODO: check if a class is base of another
	 * if (lhs->isPrimitive() && rhs->isPrimitive() && !lhs->hasSameType(rhs))
	 */
	return lhs->hasSameType(rhs);
}

/**
 * Checks the function return type
 */
static void _check_function_return(const Function* func,
	const Value* value, const Type* rtype, const location& loc) {
	/**
	 * When the rtype is NULL, the return is expected to be Void
	 * When value is NULL, the return statement is empty
	 */
	if (value && rtype == NULL) {
		Compiler::errorf(loc,
			"Function `%S' cannot return value, it was declared as Void!",
			&func->getName());
	} else if (value == NULL && rtype) {
		Compiler::errorf(loc, "Function `%S' must return a value of type %S!",
			&func->getName(), rtype->getName());
	} else if (value && rtype) {
		const Type* vtype = value->getTypePtr();

		if (vtype != rtype) {
			Compiler::errorf(loc,
				"Function `%S' expects %S value as return, not %S value",
				&func->getName(), rtype->getName(), vtype->getName());
		}
	}
}

/**
 * Checks the number of arguments supplied to the function on call
 */
static void _check_function_args(const Function* func, int num_args,
		const location& loc) {

	clever_assert_not_null(func);

	int n_required_args = func->getNumArgs();
	int n_min_args = func->getMinNumArgs();
	bool is_variadic = func->isVariadic();

	if ((is_variadic && n_min_args > num_args)
		|| (!is_variadic && num_args != n_required_args)) {
		if (n_min_args != n_required_args && n_min_args > num_args) {
			Compiler::errorf(loc, "Function `%S' expects at least %l argument%s, %l supplied",
				&func->getName(), n_min_args, (n_min_args > 1 ? "s" : ""),
				num_args);
		} else {
			Compiler::errorf(loc, "Function `%S' expects %l argument%s, %l supplied",
				&func->getName(), n_required_args, (n_required_args > 1 ? "s" : ""),
				num_args);
		}
	}
}

/**
 * Prepares the node to generate an opcode which will make a method call
 */
static void _make_method_call(const Type* type, Value* var,
	const CString* mname, CallExpr* expr, Value* arg_values) {

	clever_assert_not_null(var);

	ArgumentList* args = expr->getArgs();
	TypeVector args_types;

	if (arg_values != NULL || args != NULL) {
		// Building the ValueVector of arguments

		if (arg_values == NULL) {
			arg_values = new Value;
			arg_values->setType(Value::VECTOR);
			arg_values->setVector(args->getArgValue());
			expr->setArgsValue(arg_values);
		}

		ValueVector* vv = args ? args->getArgValue() : arg_values->getVector();

		for (size_t i = 0; i < vv->size(); ++i) {
			args_types.push_back(vv->at(i)->getTypePtr());
		}
	}

	const Method* method = type->getMethod(mname, &args_types);

	if (UNEXPECTED(method == NULL)) {
		std::string args_type_name = _serialize_arg_type(args_types, ", ");

		if (mname == CSTRING(CLEVER_CTOR_NAME)) {
			Compiler::errorf(expr->getLocation(),
				"No matching call for constructor %S::%S(%S)",
				type->getName(), type->getName(), &args_type_name);
		} else {
			std::string args_type_name = _serialize_arg_type(args_types, ", ");

			Compiler::errorf(expr->getLocation(), "No matching call for %S::%S(%S)",
				var->getTypePtr()->getName(), mname, &args_type_name);
		}
	}
	var->setTypePtr(type);

	if (var->isConst() && !method->isConst()) {
		std::string args_type_name = _serialize_arg_type(args_types, ", ");

		Compiler::errorf(expr->getLocation(), "Can't call the non-const "
			"method %S::%S(%S) because variable `%S' is const",
			var->getTypePtr()->getName(), mname, &args_type_name,
			var->getName());
	}

	CallableValue* call = new CallableValue(mname, type);
	call->setHandler(method);
	call->setContext(var);
	var->addRef();

	expr->setCallValue(call);

	// Set the return type as the declared in the method
	Value* result = expr->getValue();

	if (result) {
		result->setTypePtr(method->getReturnType());
	}
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

	while (it != end) {
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
	Value* fvalue = g_symtable.getValue(expr->getCurrentName());

	if (fvalue == NULL) {
		Compiler::errorf(expr->getLocation(), "Identifier `%S' not found!",
			expr->getCurrentName());
	}

	if (g_symtable.getValue(expr->getNewName())) {
		Compiler::errorf(expr->getLocation(), "Name `%S' already in use!",
			expr->getNewName());
	}

	g_symtable.push(expr->getNewName(), fvalue);
	fvalue->addRef();
}

/**
 * Constant visitor
 */
AST_VISITOR(TypeChecker, Constant) {
	Value* constant = g_symtable.getValue(expr->getName());

	if (constant == NULL) {
		Compiler::errorf(expr->getLocation(), "Constant `%S' not found!",
			expr->getName());
	}

	expr->getValue()->copy(constant);
}

/**
 * Regex pattern syntax visitor
 */
AST_VISITOR(TypeChecker, RegexPattern) {
	const Type* type = CLEVER_TYPE("Pcre");

	if (type == NULL) {
		Compiler::error("Regex module must be loaded to use the regex syntax!");
	}

	// Sets the argument vector for the Pcre constructor
	ValueVector* vec = new ValueVector;
	vec->push_back(expr->getRegex());

	Value* arg_values = new Value;
	arg_values->setVector(vec);

	expr->setArgsValue(arg_values);

	// The Pcre constructor CallableValue
	_make_method_call(type, expr->getValue(), CSTRING(CLEVER_CTOR_NAME),
		expr, arg_values);

	expr->getCallValue()->addRef();
}

/**
 * Identifier visitor
 */
AST_VISITOR(TypeChecker, Identifier) {
	Value* ident = g_symtable.getValue(expr->getName());

	if (ident == NULL) {
		Compiler::errorf(expr->getLocation(), "Variable `%S' not found!",
			expr->getName());
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
		case ast::NOT:     method_name = CSTRING(CLEVER_OPERATOR_NOT);     break;
		case ast::BW_NOT:  method_name = CSTRING(CLEVER_OPERATOR_BW_NOT);  break;
		case ast::PRE_INC: method_name = CSTRING(CLEVER_OPERATOR_PRE_INC); break;
		case ast::POS_INC: method_name = CSTRING(CLEVER_OPERATOR_POS_INC); break;
		case ast::PRE_DEC: method_name = CSTRING(CLEVER_OPERATOR_PRE_DEC); break;
		case ast::POS_DEC: method_name = CSTRING(CLEVER_OPERATOR_POS_DEC); break;
	}

	clever_assert_not_null(method_name);

	_make_method_call(var->getTypePtr(), var, method_name, expr, NULL);

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

	const Type* lhs_type = lhs->getTypePtr();

	// Operator method names
	switch (expr->getOp()) {
		case PLUS:          method_name = CSTRING(CLEVER_OPERATOR_PLUS);    break;
		case DIV:           method_name = CSTRING(CLEVER_OPERATOR_DIV);     break;
		case MULT:          method_name = CSTRING(CLEVER_OPERATOR_MULT);    break;
		case MINUS:         method_name = CSTRING(CLEVER_OPERATOR_MINUS);   break;
		case MOD:           method_name = CSTRING(CLEVER_OPERATOR_MOD);     break;
		case XOR:           method_name = CSTRING(CLEVER_OPERATOR_BW_XOR);  break;
		case BW_OR:         method_name = CSTRING(CLEVER_OPERATOR_BW_OR);   break;
		case BW_AND:        method_name = CSTRING(CLEVER_OPERATOR_BW_AND);  break;
		case GREATER:       method_name = CSTRING(CLEVER_OPERATOR_GREATER); break;
		case LESS:          method_name = CSTRING(CLEVER_OPERATOR_LESS);    break;
		case GREATER_EQUAL: method_name = CSTRING(CLEVER_OPERATOR_GE);      break;
		case LESS_EQUAL:    method_name = CSTRING(CLEVER_OPERATOR_LE);      break;
		case EQUAL:         method_name = CSTRING(CLEVER_OPERATOR_EQUAL);   break;
		case NOT_EQUAL:     method_name = CSTRING(CLEVER_OPERATOR_NE);      break;
		case LSHIFT:        method_name = CSTRING(CLEVER_OPERATOR_LSHIFT);  break;
		case RSHIFT:        method_name = CSTRING(CLEVER_OPERATOR_RSHIFT);  break;
		case OR:
		case AND:
			expr->setResult(new Value(CLEVER_BOOL));
			return;
	}

	clever_assert_not_null(method_name);

	ValueVector* arg_values = new ValueVector;

	arg_values->push_back(lhs);
	arg_values->push_back(rhs);

	Value* args = new Value;
	args->setType(Value::VECTOR);
	args->setVector(arg_values);

	expr->setArgsValue(args);

	if (expr->isAssigned()) {
		if (lhs->isConst()) {
			Compiler::errorf(expr->getLocation(),
				"Can't assign to variable `%S' because it is const",
				lhs->getName());
		}

		expr->setResult(lhs);
		lhs->addRef();
	} else {
		expr->setResult(new Value);
	}

	_make_method_call(lhs->getTypePtr(), lhs, method_name, expr, args);

	if (expr->isAssigned()) {
		/**
		 * When using the compound assignment expression (e.g. +=),
		 * we have to restore the original Type ptr, since we aren't in a
		 * temporary expression, but in an assignment to a variable with its
		 * defined type
		 */
		expr->getValue()->setTypePtr(lhs_type);
	}

	expr->getCallValue()->addRef();
}

/**
 * Variable declaration visitor
 */
AST_VISITOR(TypeChecker, VariableDecl) {
	const Type* type = _evaluate_type(expr->getLocation(),
		expr->getType());

	Identifier* variable = expr->getVariable();

	// Check if there is already a variable with same name in the current scope
	if (g_symtable.getValue(variable->getName(), false) != NULL) {
		Compiler::errorf(expr->getLocation(),
			"Already exists a variable named `%S' in the current scope!",
			variable->getName());
	}

	Value* var = new Value();
	variable->setValue(var);
	var->setName(variable->getName());
	var->setTypePtr(type);
	var->addRef();

	ASTNode* rhs = expr->getRhs();

	if (rhs) {
		Value* initval = rhs->getValue();

		if (!_check_compatible_types(var, initval)) {
			Compiler::errorf(expr->getLocation(),
				"Cannot convert `%S' to `%S' on assignment",
				initval->getTypePtr()->getName(),
				type->getName());
		}
		initval->addRef();
		expr->setInitialValue(initval);

		// Building ValueVector of arguments for __assign__ method call
		ValueVector* arg_values = new ValueVector;
		arg_values->push_back(initval);
		initval->addRef();

		Value* args = new Value;
		args->setType(Value::VECTOR);
		args->setVector(arg_values);

		expr->setArgsValue(args);

		_make_method_call(type, var, CSTRING(CLEVER_OPERATOR_ASSIGN),
			expr, args);

		expr->getCallValue()->addRef();
	} else {
		DataValue* data_value = type->allocateValue();

		if (data_value) {
			var->setDataValue(data_value);
		}
	}

	var->setConstness(expr->isConst());

	// Registers a new variable
	g_symtable.push(var->getName(), var);
}

/**
 * If statement visitor
 */
AST_VISITOR(TypeChecker, IfExpr) {
	expr->getCondition()->acceptVisitor(*this);

	if (expr->hasBlock()) {
		expr->getBlock()->acceptVisitor(*this);
	}

	if (expr->hasElseIf()) {
		const NodeList& elseif_nodes = expr->getNodes();
		NodeList::const_iterator it = elseif_nodes.begin(), end = elseif_nodes.end();

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
	}
}

/**
 * Block visitor
 */
AST_VISITOR(TypeChecker, BlockNode) {
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	// Create a new scope
	expr->setScope(g_symtable.beginScope());

	// Iterates over statements inside the block
	while (it != end) {
		(*it)->acceptVisitor(*this);
		++it;
	}

	// Pops from current scope
	g_symtable.endScope();
}

/**
 * While statement visitor
 */
AST_VISITOR(TypeChecker, WhileExpr) {
	expr->getCondition()->acceptVisitor(*this);

	if (expr->hasBlock()) {
		expr->getBlock()->acceptVisitor(*this);
	}
}

/**
 * For statement visitor
 */
AST_VISITOR(TypeChecker, ForExpr) {
	if (expr->isIteratorMode()) {
		return;
	}

	g_symtable.beginScope();

	if (expr->getVarDecl()) {
		expr->getVarDecl()->acceptVisitor(*this);
	}

	if (expr->getCondition()) {
		expr->getCondition()->acceptVisitor(*this);
	}

	if (expr->hasBlock()) {
		expr->getBlock()->acceptVisitor(*this);
	}

	if (expr->getIncrement()) {
		expr->getIncrement()->acceptVisitor(*this);
	}

	g_symtable.endScope();
}

/**
 * Assignment expression visitor
 */
AST_VISITOR(TypeChecker, AssignExpr) {
	Value* lhs = expr->getLhs()->getValue();
	Value* rhs = expr->getRhs()->getValue();

	if (!_check_compatible_types(lhs, rhs)) {
		Compiler::errorf(expr->getLocation(),
			"Cannot convert `%S' to `%S' on assignment",
			rhs->getTypePtr()->getName(),
			lhs->getTypePtr()->getName());
	}

	if (lhs->isConst()) {
		Compiler::errorf(expr->getLocation(),
			"Can't assign to variable `%S' because it is const",
			lhs->getName());
	}

	ValueVector* arg_values = new ValueVector;
	arg_values->push_back(rhs);
	rhs->addRef();

	Value* args = new Value;
	args->setType(Value::VECTOR);
	args->setVector(arg_values);

	expr->setArgsValue(args);

	_make_method_call(lhs->getTypePtr(), lhs,
		CSTRING(CLEVER_OPERATOR_ASSIGN), expr, args);

	expr->getCallValue()->addRef();
}

/**
 * Function call visitor
 */
AST_VISITOR(TypeChecker, FunctionCall) {
	const CString* const name = expr->getFuncName();

	clever_assert_not_null(name);

	Value* fvalue = g_symtable.getValue(name);

	if (fvalue == NULL) {
		Compiler::errorf(expr->getLocation(), "Function `%S' does not exists!",
			name);
	}

	const Function* func = static_cast<CallableValue*>(fvalue)->getFunction();
	size_t num_args = expr->getArgs() ? expr->getArgs()->getNodes().size() : 0;

	clever_assert_not_null(func);

	_check_function_args(func, num_args, expr->getLocation());

	// Set the return type
	expr->getValue()->setTypePtr(func->getReturnType());

	if (num_args) {
		Value* arg_values = new Value;
		arg_values->setType(Value::VECTOR);

		expr->getArgs()->acceptVisitor(*this);
		arg_values->setVector(expr->getArgs()->getArgValue());

		if (func->isUserDefined()) {
			Value* vars = const_cast<Function*>(func)->getVars();
			vars->addRef();
		}
		arg_values->addRef();
		expr->setArgsValue(arg_values);
	}
	expr->getValue()->addRef();
	expr->setFuncValue(static_cast<CallableValue*>(fvalue));
	fvalue->addRef();
}

AST_VISITOR(TypeChecker, MethodCall) {
	Value* variable = expr->getVariable()->getValue();
	const CString* const name = expr->getMethodName();

	clever_assert_not_null(variable);
	clever_assert_not_null(name);

	_make_method_call(variable->getTypePtr(), variable,
		name, expr, NULL);
}

/**
 * Import statement visitor
 */
AST_VISITOR(TypeChecker, ImportStmt) {
	// For import with file path we do not handle in the visitor
	if (expr->hasFilePath()) {
		return;
	}

	Scope* scope = g_symtable.getScope();

	if (UNEXPECTED(isInteractive() && g_symtable.getScope()->getDepth() == 1)) {
		scope = g_symtable.getScope(0);
	}

	/**
	 * Importing an specific module or an entire package
	 * e.g. import std.io;
	 */
	Compiler::import(scope,
		expr->getPackageName(), expr->getModuleName(), expr->getAliasName());
}

/**
 * Function declaration visitor
 */
AST_VISITOR(TypeChecker, FuncDeclaration) {
	// We can't have a function declaration without a block
	if (!expr->hasBlock()) {
		Compiler::error("Cannot declare a function without a block",
			expr->getLocation());
	}

	const CString* name = expr->getName();
	CallableValue* func = new CallableValue(name);
	Function* user_func = new Function(name->str());
	Identifier* return_type = expr->getReturnValue();
	ArgumentDeclList* args = expr->getArgs();

	// Mark the function as user defined function
	user_func->setUserDefined();

	func->addRef();
	g_symtable.push(func->getName(), func);

	func->setHandler(user_func);

	// Set the return type
	if (return_type) {
		user_func->setReturnType(g_symtable.getType(return_type->getName()));
	}

	expr->setValue(func);

	if (args) {
		ArgumentDecls& arg_nodes = args->getArgs();
		ArgumentDecls::iterator it = arg_nodes.begin(), end = arg_nodes.end();
		Value* vars = new Value;
		ValueVector* vec = new ValueVector;

		vars->setType(Value::VECTOR);
		vars->setReference(0);

		g_symtable.beginScope();

		while (it != end) {
			Value* var = new Value;

			const Type* arg_type = g_symtable.getType(it->first->getName());
			const CString* arg_name = it->second->getName();

			var->setName(arg_name);
			var->setTypePtr(arg_type);
			var->initialize();

			g_symtable.push(var->getName(), var);
			vec->push_back(var);
			var->addRef();

			user_func->addArg(*arg_name, arg_type);

			++it;
		}

		vars->setVector(vec);
		user_func->setVars(vars);
	}

	m_funcs.push(user_func);

	expr->getBlock()->acceptVisitor(*this);

	m_funcs.pop();

	if (args) {
		g_symtable.endScope();
	}
}

/**
 * Return statement visitor
 */
AST_VISITOR(TypeChecker, ReturnStmt) {
	// Only for return statement inside function declaration
	if (!m_funcs.empty()) {
		const Function* func = m_funcs.top();

		_check_function_return(func, expr->getExprValue(), func->getReturnType(),
			expr->getLocation());
	}
}

/**
 * Type creation visitor
 */
AST_VISITOR(TypeChecker, TypeCreation) {
	Identifier* ident = expr->getIdentifier();
	const Type* type = g_symtable.getType(ident->getName());

	// Check if the type wasn't declarated previously
	if (type == NULL) {
		Compiler::errorf(expr->getLocation(), "`%S' does not name a type",
			ident->getName());
	}

	_make_method_call(type, expr->getValue(),
		CSTRING(CLEVER_CTOR_NAME), expr, NULL);
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

	Value* args = new Value;
	args->setType(Value::VECTOR);
	args->setVector(arg_values);

	expr->setArgsValue(args);

	_make_method_call(var->getTypePtr(), var, CSTRING(CLEVER_OPERATOR_AT),
		expr, args);

	expr->getCallValue()->addRef();
}

/**
 * Class declaration visitor
 */
AST_VISITOR(TypeChecker, ClassDeclaration) {
	Compiler::error("Not implemented yet!");
}

}} // clever::ast
