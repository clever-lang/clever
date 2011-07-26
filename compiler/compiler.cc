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

#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <vector>
#include "compiler.h"
#include "interpreter/ast.h"
#include "types/int.h"
#include "types/double.h"
#include "types/string_type.h"
#include "interpreter/astvisitor.h"
#include "typetable.h"

namespace clever {

PackageManager Compiler::s_pkgmanager;
TypeMap TypeTable::s_type_table;

/**
 * Deallocs memory used by compiler data
 */
Compiler::~Compiler() {
	TypeTable::clear();

	s_pkgmanager.shutdown();

	delete m_ast;
}

/**
 * Initializes the compiler data
 */
void Compiler::init() throw() {
	/* Load package list */
	s_pkgmanager.init();

	/* Load the primitive data types */
	loadTypes();
}

/**
 * Loads the class representations of native types
 */
void Compiler::loadTypes() throw() {
	Integer* int_type = new Integer;
	Double* double_type = new Double;
	String* string_type = new String;

	int_type->init();
	double_type->init();
	string_type->init();

	TypeTable::insert(CSTRING("Int"), int_type);
	TypeTable::insert(CSTRING("Double"), double_type);
	TypeTable::insert(CSTRING("String"), string_type);
}

/**
 * Collects all opcode
 */
void Compiler::buildIR() throw() {
	m_cgvisitor.init();

	m_ast->accept(m_cgvisitor);

	m_cgvisitor.shutdown();
	
	m_ast->clear();
}

/**
 * Displays an error message
 */
void Compiler::error(std::string message, const location& loc) throw() {
	if (loc.begin.filename) {
		std::cout << "Compile error: " << message << " on " << *loc.begin.filename << " line " << loc.begin.line << std::endl;
	} else {
		std::cout << "Compile error: " << message << " on line " << loc.begin.line << std::endl;
	}
	exit(1);
}

void Compiler::error(std::string message) {
	std::cout << "Compile error: " << message << std::endl;
	exit(1);
}

/**
 * Performs a type compatible checking
 */
bool Compiler::checkCompatibleTypes(const Value* const lhs, const Value* const rhs) throw() {
	/**
	 * Constants with different type cannot performs operation
	 */
	if (lhs->isPrimitive() && rhs->isPrimitive() && !lhs->hasSameType(rhs)) {
		return false;
	}
	return true;
}

/**
 * Performs a constant folding optimization
 */
Value* Compiler::constantFolding(int op, Value* lhs, Value* rhs) throw() {

#define DO_NUM_OPERATION(_op, type, x, y) \
	if (x->is##type()) return new Value(x->get##type() _op y->get##type());

#define DO_STR_OPERATION(_op, x, y) \
	if (x->isString()) return new Value(CSTRING(x->getString() _op y->getString()));

	/**
	 * Check if the variable value can be predicted
	 */
	if ((lhs->hasName() && lhs->isModified()) || (rhs->hasName() && rhs->isModified())) {
		return NULL;
	}

	switch (op) {
		case ast::PLUS:
			DO_NUM_OPERATION(+, Integer, lhs, rhs);
			DO_STR_OPERATION(+, lhs, rhs);
			DO_NUM_OPERATION(+, Double, lhs, rhs);
			break;
		case ast::MINUS:
			DO_NUM_OPERATION(-, Integer, lhs, rhs);
			DO_NUM_OPERATION(-, Double, lhs, rhs);
			break;
		case ast::DIV:
			DO_NUM_OPERATION(/, Integer, lhs, rhs);
			DO_NUM_OPERATION(/, Double, lhs, rhs);
			break;
		case ast::MULT:
			DO_NUM_OPERATION(*, Integer, lhs, rhs);
			DO_NUM_OPERATION(*, Double, lhs, rhs);
			break;
		case ast::BW_OR:
			DO_NUM_OPERATION(|, Integer, lhs, rhs);
			break;
		case ast::XOR:
			DO_NUM_OPERATION(^, Integer, lhs, rhs);
			break;
		case ast::BW_AND:
			DO_NUM_OPERATION(&, Integer, lhs, rhs);
			break;
		case ast::GREATER:
			DO_NUM_OPERATION(>, Integer, lhs, rhs);
			DO_NUM_OPERATION(>, Double, lhs, rhs);
			break;
		case ast::LESS:
			DO_NUM_OPERATION(<, Integer, lhs, rhs);
			DO_NUM_OPERATION(<, Double, lhs, rhs);
			break;
		case ast::GREATER_EQUAL:
			DO_NUM_OPERATION(>=, Integer, lhs, rhs);
			DO_NUM_OPERATION(>=, Double, lhs, rhs);
			break;
		case ast::LESS_EQUAL:
			DO_NUM_OPERATION(<=, Integer, lhs, rhs);
			DO_NUM_OPERATION(<=, Double, lhs, rhs);
			break;
		case ast::EQUAL:
			DO_NUM_OPERATION(==, Integer, lhs, rhs);
			DO_NUM_OPERATION(==, Double, lhs, rhs);
			break;
		case ast::NOT_EQUAL:
			DO_NUM_OPERATION(!=, Integer, lhs, rhs);
			DO_NUM_OPERATION(!=, Double, lhs, rhs);
			break;
		case ast::MOD:
			DO_NUM_OPERATION(%, Integer, lhs, rhs);
			break;
	}
	return NULL;
}

/**
 * Checks the function return type
 */
void Compiler::checkFunctionReturn(const Function* func, const Value* value, const Type* rtype, const location& loc) throw() {
	/**
	 * When the rtype is NULL, the return is expected to be Void
	 * When value is NULL, the return statement is empty
	 */
	if (value && rtype == NULL) {
		Compiler::errorf(loc, "Function `%S' cannot return value, it was declared as Void!", &func->get_name());
	} else if (value == NULL && rtype) {
		Compiler::errorf(loc, "Function `%S' must return a value of type %s!", &func->get_name(), rtype->get_name());
	} else if (value && rtype) {
		const Type* vtype = value->get_type_ptr();

		if (vtype != rtype) {
			Compiler::errorf(loc, "Function `%S' expects %s value as return, not %s value",
				&func->get_name(), rtype->get_name(), vtype->get_name());
		}
	}
}

/**
 * Checks the number of arguments supplied to the function on call
 */
void Compiler::checkFunctionArgs(const Function* func, int num_args, const location& loc) throw() {
	int expected_args = func->get_num_args();

	if (expected_args != -1 && num_args != expected_args) {
		Compiler::errorf(loc, "Function `%S' expects %l argument%s, %l supplied",
			&func->get_name(), expected_args, (expected_args > 1 ? "s" : ""), num_args);
	}
}

/**
 * Formatter
 */
void Compiler::vsprintf(std::ostringstream& outstr, const char* format, va_list ap) throw() {
	char* chr = const_cast<char*>(format);

	if (!chr) {
		return;
	}

	while (*chr) {
		/* Check for escape %% */
		if (*chr != '%' || *++chr == '%') {
			outstr << *chr++;
			continue;
		}

		switch (*chr) {
			/* double */
			case 'd':
				outstr << va_arg(ap, double);
				break;
			/* long */
			case 'l':
				outstr << va_arg(ap, long);
				break;
			/* std::string* */
			case 'S':
				outstr << *va_arg(ap, std::string*);
				break;
			/* const char* */
			case 's':
				outstr << va_arg(ap, const char*);
				break;
			/* Value* */
			case 'v':
				outstr << va_arg(ap, Value*)->toString();
				break;
		}
		++chr;
	}
}

void Compiler::sprintf(std::ostringstream& outstr, const char* format, ...) throw() {
	va_list args;

	va_start(args, format);

	vsprintf(outstr, format, args);

	va_end(args);
}

void Compiler::printf(const char* format, ...) throw() {
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	std::cout << out;

	va_end(args);
}

void Compiler::errorf(const location& loc, const char* format, ...) throw() {
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	va_end(args);

	error(out.str(), loc);
}

void Compiler::printfln(const char* format, ...) throw() {
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	std::cout << out << std::endl;

	va_end(args);
}

} // clever
