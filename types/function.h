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

#ifndef CLEVER_TYPES_FUNCTION_H
#define CLEVER_TYPES_FUNCTION_H

namespace clever {

class Scope;

enum FuncKind { UNDEF, USER_FUNC, INTERNAL_FUNC };

struct FuncData {
	FuncKind type;
	union {
		size_t addr;   // Instruction address for user function
	} u;
	Scope* arg_vars;   // Argument variables
	Scope* local_vars; // Local variables

	FuncData() : type(UNDEF), arg_vars(NULL), local_vars(NULL) {}
};

/// Function type
class FuncType : public Type {
public:
	FuncType() : Type(CSTRING("Function")) {}
	~FuncType() {}

	void dump(const void* data) const { std::cout << "function() { }"; }

	void* allocData() { return new FuncData; }
	void deallocData(void* data) { if (data) { delete static_cast<FuncData*>(data); } }
};

} // clever

#endif // CLEVER_TYPES_FUNCTION_H
