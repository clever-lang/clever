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
#include "types/nativetypes.h"
#include "interpreter/astvisitor.h"
#include "interpreter/api.h"
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

	/**
	 * Registers all native types
	 */
	TypeTable::insert(CSTRING("Int"), int_type);
	TypeTable::insert(CSTRING("Double"), double_type);
	TypeTable::insert(CSTRING("String"), string_type);
	
	int_type->init();
	double_type->init();
	string_type->init();
}

/**
 * Collects all opcode
 */
void Compiler::buildIR() throw() {
	m_cgvisitor.init();

	m_ast->accept(m_tcvisitor);
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


void Compiler::errorf(const location& loc, const char* format, ...) throw() {
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	va_end(args);

	error(out.str(), loc);
}

} // clever
