/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
 * $Id$
 */

#include "ast.h"
#include <sstream>

namespace clever { namespace ast {

/*
 * NumberExprAST
 */
Value* NumberExprAST::codeGen(void) {
	return NULL;
}

std::string NumberExprAST::debug(void) {
	std::stringstream str;

	str << m_value;

	return str.str();
}

/*
 * BinaryExprAST
 */
Value* BinaryExprAST::codeGen(void) {
	return NULL;
}

std::string BinaryExprAST::debug(void) {
	return std::string(m_lhs->debug() + " " + m_op + " " + m_rhs->debug());
}


/*
 * VariableDeclAST
 */
Value* VariableDeclAST::codeGen(void) {

}

std::string VariableDeclAST::debug(void) {
	return m_type->debug() + " " + m_variable->debug() + " = " + m_initialization->debug();
}

/*
 * IdentifierAST
 */
Value* IdentifierAST::codeGen(void) {

}

std::string IdentifierAST::debug(void) {
	return m_name;
}

/*
 * TypeCreationAST
 */
Value* TypeCreationAST::codeGen(void) {
	return NULL;
}

std::string TypeCreationAST::debug(void) {
	return m_type->debug();
}

/*
 * NewBlockAST
 */
Value* NewBlockAST::codeGen(void) {
	return NULL;
}

std::string NewBlockAST::debug(void) {
	return std::string("{");
}

/*
 * EndBlockAST
 */
Value* EndBlockAST::codeGen(void) {
	return NULL;
}

std::string EndBlockAST::debug(void) {
	return std::string("}");
}

}} // clever::ast