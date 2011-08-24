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
 
#include "compiler/compiler.h"
#include "compiler/typechecker.h"

namespace clever { namespace ast {

/**
 * Performs a type compatible checking
 */
bool TypeChecker::checkCompatibleTypes(const Value* const lhs, const Value* const rhs) throw() {
	/**
	 * Constants with different type cannot performs operation
	 */
	
	if (lhs->isPrimitive() && rhs->isPrimitive()
		&& lhs->getTypePtr() != CLEVER_TYPE("String") 
		&& rhs->getTypePtr()  != CLEVER_TYPE("String")) {
		return true;
	}
	else if (lhs->getTypePtr() == CLEVER_TYPE("String")
		&& rhs->getTypePtr() == CLEVER_TYPE("String")) {
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
const Type* TypeChecker::checkExprType(const Value* const lhs, const Value* const rhs) throw() {
	if (lhs->isPrimitive() && rhs->isPrimitive()
		&& !lhs->isString() && !rhs->isString()) {
		
		if (lhs->getTypePtr() == CLEVER_TYPE("Double")
			|| rhs->getTypePtr() == CLEVER_TYPE("Double")) {
			return CLEVER_TYPE("Double");
		}
		
		if (lhs->getTypePtr() == CLEVER_TYPE("Int")
			|| rhs->getTypePtr() == CLEVER_TYPE("Int")) {
			return CLEVER_TYPE("Int");
		}
		
		return CLEVER_TYPE("Bool");
	}
	
	if (lhs->getTypePtr() == CLEVER_TYPE("String")
		&& rhs->getTypePtr() == CLEVER_TYPE("String")) {
		return CLEVER_TYPE("String");
	}
	
	/* TODO: check for non-primitive types */
	return lhs->getTypePtr();
}

/**
 * Checks the function return type
 */
void TypeChecker::checkFunctionReturn(const Function* func, const Value* value, const Type* rtype, const location& loc) throw() {
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
void TypeChecker::checkFunctionArgs(const Function* func, int num_args, const location& loc) throw() {
	int expected_args = func->getNumArgs();

	if (expected_args != -1 && num_args != expected_args) {
		Compiler::errorf(loc, "Function `%S' expects %l argument%s, %l supplied",
			&func->getName(), expected_args, (expected_args > 1 ? "s" : ""), num_args);
	}
}


/**
 * Creates a vector with the current value from a Value* pointers
 */
ValueVector* TypeChecker::functionArgs(ArgumentList* args) throw() {
	ValueVector* values = new ValueVector();
	const NodeList& nodes = args->getNodes();
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

	return values;
}

AST_VISITOR(TypeChecker, Identifier) {
	Value* ident = g_symtable.getValue(expr->getName());
	
	if (ident == NULL) {
		Compiler::errorf(expr->getLocation(), "Variable `%s' not found!", expr->getName());
	}
	
	/**
	 * Associate the Value* of the symbol to the identifier
	 */
	 
	expr->setValue(ident);
}

AST_VISITOR(TypeChecker, BinaryExpr) {
}

AST_VISITOR(TypeChecker, VariableDecl) {
	Identifier* variable = expr->getVariable();
	Value* var = new Value();
	const Type* type = g_symtable.getType(expr->getType()->getName());
	
	/**
	 * Check if the type wasn't declarated previously
	 */
	if (type == NULL) {
		Compiler::errorf(expr->getLocation(), "`%s' does not name a type", 
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

	var->setName(variable->getName());
	var->setTypePtr(type);
	
	var->addRef();

	g_symtable.push(var);
}

AST_VISITOR(TypeChecker, PreIncrement) {
	Identifier* ident = expr->getExpr();
	
	expr->setValue(g_symtable.getValue(ident->getName()));
}

AST_VISITOR(TypeChecker, PosIncrement) {
	Identifier* ident = expr->getExpr();
	
	expr->setValue(g_symtable.getValue(ident->getName()));
}

AST_VISITOR(TypeChecker, PreDecrement) {
	Identifier* ident = expr->getExpr();
	
	expr->setValue(g_symtable.getValue(ident->getName()));
}

AST_VISITOR(TypeChecker, PosDecrement) {
	Identifier* ident = expr->getExpr();
	
	expr->setValue(g_symtable.getValue(ident->getName()));
}

AST_VISITOR(TypeChecker, IfExpr) {
}

AST_VISITOR(TypeChecker, BlockNode) {
	NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	/**
	 * Create a new scope
	 */
	g_symtable.beginScope();

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
}

AST_VISITOR(TypeChecker, ForExpr) {
}

AST_VISITOR(TypeChecker, LogicExpr) {
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
		Compiler::errorf(expr->getLocation(), "Function `%S' does not exists!", name);
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
		arg_values->setVector(functionArgs(static_cast<ArgumentList*>(args)));

		if (func->isUserDefined()) {
			Value* vars = const_cast<Function*>(func)->getVars();
			vars->addRef();
		}
		
		expr->setArgsValue(arg_values);
	}
	
	expr->setFuncValue(static_cast<CallableValue*>(fvalue));
	fvalue->addRef();
}

AST_VISITOR(TypeChecker, MethodCall) {
}

AST_VISITOR(TypeChecker, AssignExpr) {
}

AST_VISITOR(TypeChecker, ImportStmt) {
	const CString* const package = expr->getPackageName();
	const CString* const module = expr->getModuleName();

	if (module) {
		/**
		 * Importing an specific module
		 * e.g. import std.io;
		 */
		if (isInteractive() && g_symtable.getScope().getLevel() == 1) {
			Compiler::import(g_symtable.getScope(0), package, module);
		} else {
			Compiler::import(g_symtable.getScope(), package, module);
		}
	} else {
		/**
		 * Importing an entire package
		 * e.g. import std;
		 */
		if (isInteractive() && g_symtable.getScope().getLevel() == 1) {
			Compiler::import(g_symtable.getScope(0), package);
		} else {
			Compiler::import(g_symtable.getScope(), package);
		}
	}
}

AST_VISITOR(TypeChecker, FuncDeclaration) {
}

AST_VISITOR(TypeChecker, ReturnStmt) {
}

AST_VISITOR(TypeChecker, ClassDeclaration) {
}

}} // clever::ast
