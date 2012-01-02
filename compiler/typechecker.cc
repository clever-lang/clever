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

namespace clever { namespace ast {

/**
 * Concatenates arg type names with a supplied separator character
 */
std::string TypeChecker::serializeArgType(TypeVector& args_types, const char* sep)
	throw() {
	std::string args_type_name;
	const std::string separator = std::string(sep);

	if (args_types.size() == 0) {
		return std::string("void");
	}

	args_type_name = args_types[0]->getName();

	for (size_t i = 1; i < args_types.size(); ++i) {
		args_type_name += separator + args_types[i]->getName();
	}

	return args_type_name;
}

/**
 * Performs a type compatible checking
 */
bool TypeChecker::checkCompatibleTypes(const Value* const lhs,
		const Value* const rhs) throw() {
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
 * Returns the type resulting of a binary expression of two compatible types
 */
const Type* TypeChecker::checkExprType(const Value* const lhs,
		const Value* const rhs) throw() {
	if (lhs->isPrimitive() && rhs->isPrimitive()
		&& !lhs->isString() && !rhs->isString()) {

		if (lhs->getTypePtr() == CLEVER_DOUBLE
			|| rhs->getTypePtr() == CLEVER_DOUBLE) {
			return CLEVER_DOUBLE;
		}

		if (lhs->getTypePtr() == CLEVER_INT
			|| rhs->getTypePtr() == CLEVER_INT) {
			return CLEVER_INT;
		}

		return CLEVER_BOOL;
	}

	if (lhs->getTypePtr() == CLEVER_STR
		&& rhs->getTypePtr() == CLEVER_STR) {
		return CLEVER_STR;
	}

	/* TODO: check for non-primitive types */
	return lhs->getTypePtr();
}

/**
 * Checks the function return type
 */
void TypeChecker::checkFunctionReturn(const Function* func, const Value* value,
		const Type* rtype, const location& loc) throw() {
	/**
	 * When the rtype is NULL, the return is expected to be Void
	 * When value is NULL, the return statement is empty
	 */
	if (value && rtype == NULL) {
		Compiler::errorf(loc, "Function `%S' cannot return value, it was declared as Void!", &func->getName());
	} else if (value == NULL && rtype) {
		Compiler::errorf(loc, "Function `%S' must return a value of type %s!", &func->getName(), rtype->getName());
	} else if (value && rtype) {
		const Type* vtype = value->getTypePtr();

		if (vtype != rtype) {
			Compiler::errorf(loc, "Function `%S' expects %s value as return, not %s value",
				&func->getName(), rtype->getName(), vtype->getName());
		}
	}
}

/**
 * Checks the number of arguments supplied to the function on call
 */
void TypeChecker::checkFunctionArgs(const Function* func, int num_args,
		const location& loc) throw() {
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
 * Creates a vector with the current value from a Value* pointers
 */
AST_VISITOR(TypeChecker, ArgumentList) {
	ValueVector* values = new ValueVector();
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	values->reserve(nodes.size());

	while (it != end) {
		Value* value;

		(*it)->accept(*this);

		value = (*it)->getValue();
		value->addRef();

		values->push_back(value);
		++it;
	}

	expr->setArgValue(values);
}

AST_VISITOR(TypeChecker, Identifier) {
	Value* ident = g_symtable.getValue(expr->getName());

	if (ident == NULL) {
		Compiler::errorf(expr->getLocation(), "Variable `%S' not found!",
			expr->getName());
	}

	/**
	 * Associate the Value* of the symbol to the identifier
	 */
	expr->setValue(ident);
	ident->addRef();
}

AST_VISITOR(TypeChecker, BinaryExpr) {
	Value* lhs = expr->getLhs()->getValue();
	Value* rhs = expr->getRhs()->getValue();

	if (!checkCompatibleTypes(lhs, rhs)) {
		Compiler::error("Type mismatch!", expr->getLocation());
	}

	if (expr->isAssigned()) {
		expr->setResult(lhs);
		expr->getValue()->setTypePtr(lhs->getTypePtr());
		lhs->addRef();
	} else {
		expr->setResult(new Value(lhs->getTypePtr()));
	}
}

AST_VISITOR(TypeChecker, LogicExpr) {
	const Value* lhs = expr->getLhs()->getValue();
	const Value* rhs = expr->getRhs()->getValue();

	if (!checkCompatibleTypes(lhs, rhs)) {
		Compiler::errorf(expr->getLocation(),
			"Cannot convert `%s' to `%s' in logic expression",
			rhs->getTypePtr()->getName(),
			lhs->getTypePtr()->getName());
	}

	expr->setResult(new Value(CLEVER_BOOL));
}

AST_VISITOR(TypeChecker, VariableDecl) {
	Identifier* variable = expr->getVariable();
	Value* var = new Value();
	ASTNode* rhs = expr->getRhs();
	const Type* type = g_symtable.getType(expr->getType()->getName());

	/**
	 * Check if the type wasn't declarated previously
	 */
	if (type == NULL) {
		Compiler::errorf(expr->getLocation(), "`%S' does not name a type",
			expr->getType()->getName());
	}

	/**
	 * Check if there is already a variable with same name in the current scope
	 */
	if (g_symtable.getValue(variable->getName(), false) != NULL) {
		Compiler::errorf(expr->getLocation(),
			"Already exists a variable named `%S' in the current scope!",
			variable->getName());
	}

	variable->setValue(var);

	/**
	 * Registers a new variable
	 */
	var->setName(variable->getName());
	var->setTypePtr(type);
	var->addRef();

	if (rhs) {
		Value* initval = rhs->getValue();

		if (!checkCompatibleTypes(var, initval)) {
			Compiler::errorf(expr->getLocation(),
				"Cannot convert `%s' to `%s' on assignment",
				initval->getTypePtr()->getName(),
				type->getName());
		}

		expr->setInitialValue(initval);

		if (type != initval->getTypePtr()) {
			if (type == CLEVER_INT) {
				initval->setInteger(initval->getDouble());
			}
			else if (type == CLEVER_DOUBLE) {
				initval->setDouble(initval->getInteger());
			}
		}

		initval->addRef();
	}

	g_symtable.push(var->getName(), var);
}

AST_VISITOR(TypeChecker, PreIncrement) {
	Value* var = expr->getExpr()->getValue();

	expr->setVar(var);
	var->addRef();

	expr->getValue()->addRef();
	expr->getValue()->setTypePtr(var->getTypePtr());
}

AST_VISITOR(TypeChecker, PosIncrement) {
	Value* var = expr->getExpr()->getValue();

	expr->setVar(var);
	var->addRef();

	expr->getValue()->addRef();
	expr->getValue()->setTypePtr(var->getTypePtr());
}

AST_VISITOR(TypeChecker, PreDecrement) {
	Value* var = expr->getExpr()->getValue();

	expr->setVar(var);
	var->addRef();

	expr->getValue()->addRef();
	expr->getValue()->setTypePtr(var->getTypePtr());
}

AST_VISITOR(TypeChecker, PosDecrement) {
	Value* var = expr->getExpr()->getValue();

	expr->setVar(var);
	var->addRef();

	expr->getValue()->addRef();
	expr->getValue()->setTypePtr(var->getTypePtr());
}

AST_VISITOR(TypeChecker, IfExpr) {
	expr->getCondition()->accept(*this);

	if (expr->hasBlock()) {
		expr->getBlock()->accept(*this);
	}

	if (expr->hasElseIf()) {
		const NodeList& elseif_nodes = expr->getNodes();
		NodeList::const_iterator it = elseif_nodes.begin(), end = elseif_nodes.end();

		while (it != end) {
			ElseIfExpr* elseif = static_cast<ElseIfExpr*>(*it);

			elseif->getCondition()->accept(*this);

			if (elseif->hasBlock()) {
				elseif->getBlock()->accept(*this);
			}
			++it;
		}
	}

	if (expr->hasElseBlock()) {
		expr->getElse()->accept(*this);
	}
}

AST_VISITOR(TypeChecker, BlockNode) {
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	/**
	 * Create a new scope
	 */
	expr->setScope(g_symtable.beginScope());

	/**
	 * Iterates statements inside the block
	 */
	while (it != end) {
		(*it)->accept(*this);
		++it;
	}

	/**
	 * Pops the scope
	 */
	g_symtable.endScope();
}

AST_VISITOR(TypeChecker, WhileExpr) {
	expr->getCondition()->accept(*this);

	if (expr->hasBlock()) {
		expr->getBlock()->accept(*this);
	}
}

AST_VISITOR(TypeChecker, ForExpr) {
	if (expr->isIteratorMode()) {
		return;
	}
	if (expr->getVarDecl()) {
		expr->getVarDecl()->accept(*this);
	}

	if (expr->getCondition()) {
		expr->getCondition()->accept(*this);
	}

	if (expr->hasBlock()) {
		expr->getBlock()->accept(*this);
	}

	if (expr->getIncrement()) {
		expr->getIncrement()->accept(*this);
	}
}

AST_VISITOR(TypeChecker, BreakNode) {
}

AST_VISITOR(TypeChecker, FunctionCall) {
	const CString* const name = expr->getFuncName();
	Value* fvalue = g_symtable.getValue(name);
	const Function* func;
	ASTNode* args = expr->getArgs();
	Value* arg_values = NULL;
	int num_args = args ? args->getNodes().size() : 0;

	if (fvalue == NULL) {
		Compiler::errorf(expr->getLocation(), "Function `%S' does not exists!",
			name);
	}

	func = static_cast<CallableValue*>(fvalue)->getFunction();

	checkFunctionArgs(func, num_args, expr->getLocation());

	/**
	 * Set the return type
	 */
	expr->getValue()->setTypePtr(func->getReturn());

	if (num_args) {
		arg_values = new Value;
		arg_values->setType(Value::VECTOR);

		expr->getArgs()->accept(*this);
		arg_values->setVector(expr->getArgs()->getArgValue());

		if (func->isUserDefined()) {
			Value* vars = const_cast<Function*>(func)->getVars();
			vars->addRef();
		}
		arg_values->addRef();
		expr->setArgsValue(arg_values);
	}

	expr->setFuncValue(static_cast<CallableValue*>(fvalue));
	fvalue->addRef();
}

AST_VISITOR(TypeChecker, MethodCall) {
	Value* variable = expr->getVariable()->getValue();
	const CString* const name = expr->getMethodName();
	CallableValue* call = new CallableValue(name);
	ArgumentList* args = expr->getArgs();
	Value* arg_values = NULL;
	TypeVector args_types;

	if (args) {
		expr->getArgs()->accept(*this);
		arg_values = new Value;
		arg_values->setType(Value::VECTOR);
		arg_values->setVector(args->getArgValue());
		arg_values->addRef();
		expr->setArgsValue(arg_values);

		ValueVector* vv = args->getArgValue();

		for (size_t i = 0; i < vv->size(); ++i) {
			args_types.push_back(vv->at(i)->getTypePtr());
		}
	}

	const Method* method = variable->getTypePtr()->getMethod(name, &args_types);

	if (method == NULL) {
		std::string args_type_name = serializeArgType(args_types, ", ");

		Compiler::errorf(expr->getLocation(), "No matching call for %s::%S(%S)",
			variable->getTypePtr()->getName(), call->getName(), &args_type_name);
	}

	call->setTypePtr(variable->getTypePtr());
	call->setHandler(method);
	call->setContext(variable);

	expr->getValue()->setTypePtr(method->getReturn());

	expr->setFuncValue(static_cast<CallableValue*>(call));
}

AST_VISITOR(TypeChecker, AssignExpr) {
	const Value* lhs = expr->getLhs()->getValue();
	const Value* rhs = expr->getRhs()->getValue();

	if (!checkCompatibleTypes(lhs, rhs)) {
		Compiler::errorf(expr->getLocation(),
			"Cannot convert `%s' to `%s' on assignment",
			rhs->getTypePtr()->getName(),
			lhs->getTypePtr()->getName());
	}
}

AST_VISITOR(TypeChecker, ImportStmt) {
	const CString* const package = expr->getPackageName();
	const CString* const module = expr->getModuleName();

	/**
	 * Importing an specific module or an entire package
	 * e.g. import std.io;
	 */
	if (isInteractive() && g_symtable.getScope()->getDepth() == 1) {
		Compiler::import(g_symtable.getScope(0), package, module);
	} else {
		Compiler::import(g_symtable.getScope(), package, module);
	}
}

AST_VISITOR(TypeChecker, FuncDeclaration) {
	const CString* name = expr->getName();
	CallableValue* func = new CallableValue(name);
	Function* user_func = new Function(name->str());
	Identifier* return_type = expr->getReturnValue();
	ArgumentDeclList* args = expr->getArgs();

	/**
	 * We can't have a function declaration without a block
	 */
	if (!expr->hasBlock()) {
		Compiler::error("Cannot declare a function without a block",
			expr->getLocation());
	}
	/**
	 * Mark the function as user function
	 */
	user_func->setUserDefined();

	func->addRef();
	g_symtable.push(func->getName(), func);

	func->setHandler(user_func);

	/**
	 * Set the return type
	 */
	if (return_type) {
		user_func->setReturn(g_symtable.getType(return_type->getName()));
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

	expr->getBlock()->accept(*this);

	m_funcs.pop();

	if (args) {
		g_symtable.endScope();
	}
}

AST_VISITOR(TypeChecker, ReturnStmt) {
	const Value* expr_value = expr->getExprValue();
	const Function* func = m_funcs.empty() ? NULL : m_funcs.top();

	/**
	 * Only for return inside function declaration
	 */
	if (func) {
		checkFunctionReturn(func, expr_value, func->getReturn(),
			expr->getLocation());
	}
}

AST_VISITOR(TypeChecker, ClassDeclaration) {
	Compiler::error("Not implemented yet!");
}

AST_VISITOR(TypeChecker, TypeCreation) {
	Identifier* ident = expr->getIdentifier();
	const Type* type = g_symtable.getType(ident->getName());

	/**
	 * Check if the type wasn't declarated previously
	 */
	if (type == NULL) {
		Compiler::errorf(expr->getLocation(), "`%S' does not name a type",
			ident->getName());
	}

	ArgumentList* args = expr->getArgs();
	TypeVector args_types;
	Value* arg_values = NULL;

	if (args) {
		arg_values = new Value;
		arg_values->setType(Value::VECTOR);
		arg_values->setVector(args->getArgValue());
		expr->setArgsValue(arg_values);

		ValueVector* vv = args->getArgValue();

		for (size_t i = 0; i < vv->size(); ++i) {
			args_types.push_back(vv->at(i)->getTypePtr());
		}
	}

	const Method* ctor = type->getMethod(CSTRING(CLEVER_CTOR_NAME), &args_types);

	if (ctor == NULL) {
		std::string args_type_name = serializeArgType(args_types, ", ");

		Compiler::errorf(expr->getLocation(), "No matching call for constructor %s::%s(%S)",
			type->getName(), type->getName(), &args_type_name);
	}

	Value* value = expr->getValue();
	value->setTypePtr(type);

	CallableValue* call = new CallableValue(CSTRING(CLEVER_CTOR_NAME), type);
	call->setHandler(ctor);
	call->setContext(value);
	value->addRef();

	expr->getValue()->setTypePtr(type);
	expr->setFuncValue(call);
}

}} // clever::ast
