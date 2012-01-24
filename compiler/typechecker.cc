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

const Type* clever_evaluate_type(const location& loc, const Identifier* ident)
{
	const Type* type = g_symtable.getType(ident->getName());

	/**
	 * Check if the type wasn't declarated previously
	 */
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

				if (!argt->isTemplatedType()) {
					vec.push_back(argt);
				}
				else {
					vec.push_back(clever_evaluate_type(loc, template_args->at(i)));
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
std::string TypeChecker::serializeArgType(TypeVector& args_types, const char* sep) {
	if (args_types.size() == 0) {
		return std::string("void");
	}

	clever_assert(args_types[0] != NULL, "args_types[0] cannot be NULL!");

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
bool TypeChecker::checkCompatibleTypes(const Value* const lhs,
		const Value* const rhs) {

	clever_assert(lhs != NULL, "lhs cannot be NULL");
	clever_assert(rhs != NULL, "rhs cannot be NULL");

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
		const Value* const rhs) {

	clever_assert(lhs != NULL, "lhs cannot be NULL");
	clever_assert(rhs != NULL, "rhs cannot be NULL");

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
		const Type* rtype, const location& loc) {
	/**
	 * When the rtype is NULL, the return is expected to be Void
	 * When value is NULL, the return statement is empty
	 */
	if (value && rtype == NULL) {
		Compiler::errorf(loc, "Function `%S' cannot return value, it was declared as Void!", &func->getName());
	} else if (value == NULL && rtype) {
		Compiler::errorf(loc, "Function `%S' must return a value of type %S!", &func->getName(), rtype->getName());
	} else if (value && rtype) {
		const Type* vtype = value->getTypePtr();

		if (vtype != rtype) {
			Compiler::errorf(loc, "Function `%S' expects %S value as return, not %S value",
				&func->getName(), rtype->getName(), vtype->getName());
		}
	}
}

/**
 * Checks the number of arguments supplied to the function on call
 */
void TypeChecker::checkFunctionArgs(const Function* func, int num_args,
		const location& loc) {
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

AST_VISITOR(TypeChecker, Constant) {
	Value* constant = g_symtable.getValue(expr->getName());

	if (constant == NULL) {
		Compiler::errorf(expr->getLocation(), "Constant `%S' not found!",
			expr->getName());
	}

	expr->getValue()->copy(constant);
}

AST_VISITOR(TypeChecker, RegexPattern) {
	const Type* type = CLEVER_TYPE("Pcre");

	if (type == NULL) {
		Compiler::error("Regex module must be loaded to use the regex syntax!");
	}

	expr->getRegex()->addRef();

	/**
	 * Sets the argument vector for the Pcre constructor
	 */
	ValueVector* vec = new ValueVector;
	vec->push_back(expr->getRegex());

	Value* arg_values = new Value;
	arg_values->setVector(vec);
	arg_values->addRef();

	expr->setArgsValue(arg_values);

	/**
	 * Finds the Pcre constructor method
	 */
	TypeVector args_types;
	args_types.push_back(CLEVER_STR);

	const CString* method_name = CSTRING(CLEVER_CTOR_NAME);
	const Method* ctor = type->getMethod(method_name, &args_types);
	clever_assert(ctor != NULL, "Pcre's constructor method not found!");

	Value* value = expr->getValue();
	value->setTypePtr(type);

	/**
	 * The Pcre constructor CallableValue
	 */
	CallableValue* mvalue = new CallableValue(method_name);
	mvalue->setTypePtr(type);
	mvalue->setHandler(ctor);
	mvalue->setContext(value);
	mvalue->addRef();

	value->addRef();

	expr->setMethodValue(mvalue);
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

AST_VISITOR(TypeChecker, UnaryExpr) {
	Value* var = expr->getExpr()->getValue();
	const Method* method = NULL;
	const CString* method_name = NULL;

	switch (expr->getOp()) {
		case ast::NOT:     method_name = CSTRING(CLEVER_OPERATOR_NOT);     break;
		case ast::BW_NOT:  method_name = CSTRING(CLEVER_OPERATOR_BW_NOT);  break;
		case ast::PRE_INC: method_name = CSTRING(CLEVER_OPERATOR_PRE_INC); break;
		case ast::POS_INC: method_name = CSTRING(CLEVER_OPERATOR_POS_INC); break;
		case ast::PRE_DEC: method_name = CSTRING(CLEVER_OPERATOR_PRE_DEC); break;
		case ast::POS_DEC: method_name = CSTRING(CLEVER_OPERATOR_POS_DEC); break;
	}

	method = var->getTypePtr()->getMethod(method_name, NULL);

	if (method == NULL) {
		Compiler::errorf(expr->getLocation(),
			"The type %S doesn't support such operation!",
			var->getTypePtr()->getName());
	}

	if (var->isConst() && !method->isConst()) {
		Compiler::errorf(expr->getLocation(), "Can't use the non-const "
			"operator `%S' because variable `%S' is const",
			method_name, var->getName());
	}

	CallableValue* call = new CallableValue(method_name);
	call->setTypePtr(var->getTypePtr());
	call->setHandler(method);
	call->setContext(var);
	var->addRef();

	expr->setMethod(call);
	call->addRef();

	expr->getValue()->setTypePtr(var->getTypePtr());
}

AST_VISITOR(TypeChecker, BinaryExpr) {
	const Method* method = NULL;
	const CString* method_name = NULL;

	expr->getLhs()->acceptVisitor(*this);
	expr->getRhs()->acceptVisitor(*this);

	Value* lhs = expr->getLhs()->getValue();
	Value* rhs = expr->getRhs()->getValue();

	/**
	 * Operator method names
	 */
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

	ValueVector* arg_values = new ValueVector;
	CallableValue* call = new CallableValue(method_name);

	TypeVector arg_types;
	arg_types.push_back(lhs->getTypePtr());
	arg_types.push_back(rhs->getTypePtr());

	arg_values->push_back(lhs);
	arg_values->push_back(rhs);

	Value* args = new Value;
	args->setType(Value::VECTOR);
	args->setVector(arg_values);

	args->addRef();
	call->addRef();

	method = lhs->getTypePtr()->getMethod(method_name, &arg_types);

	if (method == NULL) {
		std::string arg_type_names = serializeArgType(arg_types, ", ");

		Compiler::errorf(expr->getLocation(), "No matching call for operation '%S' in %S using (%S)",
			method_name, lhs->getTypePtr()->getName(), &arg_type_names);
	}

	call->setTypePtr(lhs->getTypePtr());
	call->setHandler(method);
	call->setContext(lhs);
	lhs->addRef();

	expr->setMethod(call);
	expr->setMethodArgs(args);

	if (expr->isAssigned()) {
		if (lhs->isConst()) {
			Compiler::errorf(expr->getLocation(), "Can't assign to "
				"variable `%S' because it is const",
				lhs->getName());
		}

		expr->setResult(lhs);
		expr->getValue()->setTypePtr(lhs->getTypePtr());
		lhs->addRef();
	} else {
		expr->setResult(new Value(method->getReturnType()));
	}
}

AST_VISITOR(TypeChecker, VariableDecl) {
	const Type* type = clever_evaluate_type(expr->getLocation(),
		expr->getType());

	Identifier* variable = expr->getVariable();

	/**
	 * Check if there is already a variable with same name in the current scope
	 */
	if (g_symtable.getValue(variable->getName(), false) != NULL) {
		Compiler::errorf(expr->getLocation(),
			"Already exists a variable named `%S' in the current scope!",
			variable->getName());
	}

	Value* var = new Value();
	variable->setValue(var);
	/**
	 * Registers a new variable
	 */
	var->setName(variable->getName());
	var->setTypePtr(type);
	var->addRef();

	ASTNode* rhs = expr->getRhs();

	if (rhs) {
		Value* initval = rhs->getValue();

		if (!checkCompatibleTypes(var, initval)) {
			Compiler::errorf(expr->getLocation(),
				"Cannot convert `%S' to `%S' on assignment",
				initval->getTypePtr()->getName(),
				type->getName());
		}

		expr->setInitialValue(initval);

		initval->addRef();

		TypeVector arg_types;
		arg_types.push_back(initval->getTypePtr());

		const CString* method_name = CSTRING(CLEVER_OPERATOR_ASSIGN);
		const Method* method = var->getTypePtr()->getMethod(method_name,
			&arg_types);

		if (method == NULL) {
			Compiler::errorf(expr->getLocation(),
				"Method __assign__ not found in %S for assignment with %S",
				var->getTypePtr()->getName(),
				initval->getTypePtr()->getName());
		}

		ValueVector* arg_values = new ValueVector;
		arg_values->push_back(initval);
		initval->addRef();

		Value* args = new Value;
		args->setType(Value::VECTOR);
		args->setVector(arg_values);

		expr->setMethodArgs(args);

		CallableValue* call = new CallableValue(method_name);
		call->setContext(var);
		call->setHandler(method);
		call->setTypePtr(var->getTypePtr());
		var->addRef();
		call->addRef();

		expr->setMethodValue(call);
	}
	else {
		DataValue* data_value = type->allocateValue();

		if (data_value) {
			var->setDataValue(data_value);
		}
	}

	var->setConstness(expr->isConst());
	g_symtable.push(var->getName(), var);
}

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
		(*it)->acceptVisitor(*this);
		++it;
	}

	/**
	 * Pops the scope
	 */
	g_symtable.endScope();
}

AST_VISITOR(TypeChecker, WhileExpr) {
	expr->getCondition()->acceptVisitor(*this);

	if (expr->hasBlock()) {
		expr->getBlock()->acceptVisitor(*this);
	}
}

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

	if (!checkCompatibleTypes(lhs, rhs)) {
		Compiler::errorf(expr->getLocation(),
			"Cannot convert `%S' to `%S' on assignment",
			rhs->getTypePtr()->getName(),
			lhs->getTypePtr()->getName());
	}

	TypeVector arg_types;
	arg_types.push_back(rhs->getTypePtr());

	const CString* method_name = CSTRING(CLEVER_OPERATOR_ASSIGN);
	const Method* method = lhs->getTypePtr()->getMethod(method_name, &arg_types);

	if (method == NULL) {
		Compiler::errorf(expr->getLocation(),
			"Method for assing operation on %S not found to assign %S",
			rhs->getTypePtr()->getName(),
			lhs->getTypePtr()->getName());
	}

	if (lhs->isConst()) {
		Compiler::errorf(expr->getLocation(), "Can't assign to "
			"variable `%S' because it is const",
			lhs->getName());
	}

	ValueVector* arg_values = new ValueVector;
	arg_values->push_back(rhs);
	rhs->addRef();

	Value* args = new Value;
	args->setType(Value::VECTOR);
	args->setVector(arg_values);

	expr->setMethodArgs(args);

	CallableValue* call = new CallableValue(method_name);
	call->setTypePtr(lhs->getTypePtr());
	call->setHandler(method);
	call->setContext(lhs);
	lhs->addRef();

	expr->setMethodValue(call);
	call->addRef();
}

AST_VISITOR(TypeChecker, FunctionCall) {
	const CString* const name = expr->getFuncName();
	Value* fvalue = g_symtable.getValue(name);

	if (fvalue == NULL) {
		Compiler::errorf(expr->getLocation(), "Function `%S' does not exists!",
			name);
	}

	const Function* func = static_cast<CallableValue*>(fvalue)->getFunction();
	size_t num_args = expr->getArgs() ? expr->getArgs()->getNodes().size() : 0;

	checkFunctionArgs(func, num_args, expr->getLocation());

	/**
	 * Set the return type
	 */
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

	expr->setFuncValue(static_cast<CallableValue*>(fvalue));
	fvalue->addRef();
}

AST_VISITOR(TypeChecker, MethodCall) {
	Value* variable = expr->getVariable()->getValue();
	const CString* const name = expr->getMethodName();
	CallableValue* call = new CallableValue(name);
	ArgumentList* args = expr->getArgs();
	TypeVector args_types;

	if (args) {
		expr->getArgs()->acceptVisitor(*this);

		Value* arg_values = new Value;

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

		Compiler::errorf(expr->getLocation(), "No matching call for %S::%S(%S)",
			variable->getTypePtr()->getName(), call->getName(), &args_type_name);
	}

	if (variable->isConst() && !method->isConst()) {
		std::string args_type_name = serializeArgType(args_types, ", ");

		Compiler::errorf(expr->getLocation(), "Can't call the non-const "
			"method %S::%S(%S) because variable `%S' is const",
			variable->getTypePtr()->getName(), call->getName(), &args_type_name,
			variable->getName());
	}

	call->setTypePtr(variable->getTypePtr());
	call->setHandler(method);
	call->setContext(variable);
	variable->addRef();

	expr->getValue()->setTypePtr(method->getReturnType());

	expr->setFuncValue(static_cast<CallableValue*>(call));
}

AST_VISITOR(TypeChecker, ImportStmt) {
	/**
	 * For import with file path we do not handle in the visitor
	 */
	if (expr->hasFilePath()) {
		return;
	}

	Scope* scope = g_symtable.getScope();
	/**
	 * Importing an specific module or an entire package
	 * e.g. import std.io;
	 */
	if (UNEXPECTED(isInteractive() && g_symtable.getScope()->getDepth() == 1)) {
		scope = g_symtable.getScope(0);
	}
	Compiler::import(scope,
		expr->getPackageName(), expr->getModuleName(), expr->getAliasName());
}

AST_VISITOR(TypeChecker, FuncDeclaration) {
	/**
	 * We can't have a function declaration without a block
	 */
	if (!expr->hasBlock()) {
		Compiler::error("Cannot declare a function without a block",
			expr->getLocation());
	}

	const CString* name = expr->getName();
	CallableValue* func = new CallableValue(name);
	Function* user_func = new Function(name->str());
	Identifier* return_type = expr->getReturnValue();
	ArgumentDeclList* args = expr->getArgs();

	/**
	 * Mark the function as user defined function
	 */
	user_func->setUserDefined();

	func->addRef();
	g_symtable.push(func->getName(), func);

	func->setHandler(user_func);

	/**
	 * Set the return type
	 */
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

AST_VISITOR(TypeChecker, ReturnStmt) {
	/**
	 * Only for return statement inside function declaration
	 */
	if (!m_funcs.empty()) {
		const Function* func = m_funcs.top();

		checkFunctionReturn(func, expr->getExprValue(), func->getReturnType(),
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

		Compiler::errorf(expr->getLocation(), "No matching call for constructor %S::%S(%S)",
			type->getName(), type->getName(), &args_type_name);
	}

	Value* value = expr->getValue();
	value->setTypePtr(type);

	CallableValue* call = new CallableValue(CSTRING(CLEVER_CTOR_NAME), type);
	call->setHandler(ctor);
	call->setContext(value);
	value->addRef();

	expr->setFuncValue(call);
}

AST_VISITOR(TypeChecker, Subscript) {
}

}} // clever::ast
