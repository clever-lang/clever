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

#ifndef CLEVER_TYPEUTILS_H
#define CLEVER_TYPEUTILS_H

#include <string>
#include "type.h"
#include "compiler/value.h"
#include "compiler/method.h"
#include "compiler/compiler.h"

namespace clever {

/**
 * CLEVER_CHECK_ARGS("Class::methodName", CLEVER_TYPE("Type1"), CLEVER_TYPE("Type2"), …, CLEVER_TYPE("TypeN"), NULL) :
 * 	receives the method name string and the argument types **in order** and a NULL constant to mark the end.
 * 	Checks and conveniently initializes the methods arguments.
 *	Use ONLY inside a CLEVER_TYPE_METHOD definition.
 */
#define CLEVER_CHECK_ARGS(name, ...) do { \
	if (!clv_method_->isArgsInitialized()) { \
		addArgs(clv_method_, __VA_ARGS__); \
	}\
	if (!checkArgs(clv_method_->getArgs(), args)) \
		Compiler::error(argsError(name, clv_method_->getArgs(), args)); \
} while (false)

/**
 * addArgs(method, type1, type2, ...), adds the argument types in the method object
 */
void addArgs(Method*, ...);

/**
 * Checks if the Value*s contained in the ValueVector have the same 
 * type as the types in the TypeVector
 */
bool checkArgs(const TypeVector*, const ValueVector*);

/**
 * Prints an error related to wrong arguments and exits the program
 */
std::string argsError(const std::string&, const TypeVector*, const ValueVector*);

} // clever

#endif // CLEVER_TYPEUTILS_H
