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
 
#ifndef CLEVER_TYPECHECKER_H
#define CLEVER_TYPECHECKER_H

#include "compiler/value.h"

namespace clever {
	
class TypeChecker {
public:
	TypeChecker() { }
	~TypeChecker() { }
	
	/**
	 * Checks if the supplied value pointers are compatibles
	 */
	static bool checkCompatibleTypes(const Value* const, const Value* const) throw();
	
	/**
	 * Returns the type resulting of a binary expression of two compatible types
	 */
	static const Type* checkExprType(const Value* const, const Value* const) throw();
	
	static int checkFunctionArgs(Function*, int, const location&) throw();
	
	static void checkFunctionArgs(const Function*, int, const location&) throw();
	
	static void checkFunctionReturn(const Function*, const Value*, const Type*, const location&) throw();
};

} // clever

#endif // CLEVER_TYPECHECKER_H
