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

#include <cstdarg>
#include <cassert>
#include "types/typeutils.h"

namespace clever {

/**
 * Builds the error message related to type mismatch
 */
std::string argsError(const TypeVector* expected, const ValueVector* argv) {
	std::string error = "(";
	int sz = 0;

	if (argv) {
		sz = argv->size();
	}
	
	for (int i = 0; i < sz-1; ++i) {	
		error += argv->at(i)->getTypePtr()->getName();
		error += ", ";
	}
	
	if (sz > 0) {
		error += argv->at(sz-1)->getTypePtr()->getName();
	}
	
	error += "). Expecting (";
	
	sz = expected ? expected->size() : 0;
	for (int i = 0; i < sz-1; ++i) {
		error += expected->at(i)->getName();
		error += ", ";
	}
	
	if (sz > 0) {
		error += expected->at(sz-1)->getName();
	}
	
	error += ")";
	
	return error;
}

/**
 * Checks if the ValueVector matchs the expected types
 */
bool checkArgs(const TypeVector* expected, const ValueVector* args) {
	size_t sz;
	
	if (expected == NULL) {
		if (args == NULL) {
			return true;
		}
		return false;
	}
	
	if (args == NULL) {
		return false;
	}
	
	sz = expected->size();
	
	if (sz != args->size()) {
		return false;
	}
	
	for (size_t i = 0; i < sz; ++i) {
		if (expected->at(i) != args->at(i)->getTypePtr()) {
			return false;
		}
	}
	
	return true;
}

/**
 * Builds a vector of Type pointers
 */
TypeVector* makeArgs(const Type* type1, ...) {
	va_list li;
	TypeVector* tv = NULL;
	const Type* t1 = type1;
	
	if (t1 != NULL) {
		tv = new TypeVector();
	}
	
	va_start(li, type1);
	
	while (t1 != NULL) {
		tv->push_back(t1);
		t1 = va_arg(li, const Type*);
	}
	
	va_end(li);
	
	return tv;
}

} // clever
