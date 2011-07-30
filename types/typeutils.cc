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
#include "types/typeutils.h"

namespace clever {

void addArgs(Method* method, ...)
{
	using namespace std;
	va_list li;
	
	TypeVector* tv = NULL;
	
	const Type* t1;
	va_start(li, method);
	
	t1 = va_arg(li, const Type*);
	
	if (t1 != NULL) tv = new TypeVector();
	
	while (t1 != NULL) {
		tv->push_back(t1);
		t1 = va_arg(li, const Type*);
	}
	
	method->setArgs(tv);
	va_end(li);
}

std::string argsError(const std::string& name, const TypeVector* expected, const ValueVector* args)
{
	std::string error = "No matching call for " + name + "(";
	size_t size = args->size();
	
	for (size_t i = 0; i < size-1; ++i) {
		error += args->at(i)->getTypePtr()->getName();
		error += ", ";
	}
	
	if (size > 0) {
		error += args->at(size-1)->getTypePtr()->getName();
	}
	
	error += ")";
	
	return error;
}

bool checkArgs(const TypeVector* expected, const ValueVector* args) {
	
	if (expected == NULL) {
		if (args == NULL) return true;
		return false;
	}
	
	if (args == NULL) return false;
	
	size_t sz = expected->size();
	
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

} // clever