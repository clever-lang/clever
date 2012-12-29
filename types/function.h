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

#include <vector>
#include "compiler/clever.h"
#include "types/type.h"

namespace clever {

class Value;

#define CLEVER_FUNCTION_ARGS ::std::vector<Value*>& args
#define CLEVER_FUNC_NAME(name) clv_f_##name
#define CLEVER_NS_FNAME(ns, name) ns::CLEVER_FUNC_NAME(name)
#define CLEVER_FUNCTION(name) void CLEVER_FASTCALL CLEVER_FUNC_NAME(name)(CLEVER_FUNCTION_ARGS)

class Scope;

typedef void (CLEVER_FASTCALL *FunctionPtr)(CLEVER_FUNCTION_ARGS);

class Function {
public:
	enum FuncKind { UNDEF, USER_FUNC, INTERNAL_FUNC };

	Function()
		: m_name(), m_type(UNDEF), m_arg_vars(NULL), m_local_vars(NULL) {}

	Function(std::string name, FunctionPtr ptr)
		: m_name(name), m_type(UNDEF), m_arg_vars(NULL), m_local_vars(NULL)
		{ m_info.ptr = ptr; }

	Function(std::string name, size_t addr)
		: m_name(name), m_type(UNDEF), m_arg_vars(NULL), m_local_vars(NULL)
		{ m_info.addr = addr; }

	~Function() {}

	void setName(std::string name) { m_name = name; }
	const std::string& getName() const { return m_name; }

	void setInternal() { m_type = INTERNAL_FUNC; }
	void setUserDefined() { m_type = USER_FUNC; }

	bool isUserDefined() const { return m_type == USER_FUNC; }
	bool isInternal() const { return m_type == INTERNAL_FUNC; }

	FunctionPtr getPtr() const { return m_info.ptr; }
	size_t getAddr() const { return m_info.addr; }

	void setAddr(size_t addr) { m_info.addr = addr; }
	void setPtr(FunctionPtr ptr) { m_info.ptr = ptr; }

	Scope* getLocalVars() { return m_local_vars; }
	Scope* getArgVars() { return m_arg_vars; }

	void setLocalVars(Scope* local_vars) { m_local_vars = local_vars; }
	void setArgVars(Scope* arg_vars) { m_arg_vars = arg_vars; }
private:
	std::string m_name;
	FuncKind m_type;
	union {
		FunctionPtr ptr;
		size_t addr;
	} m_info;

	/// Argument variables
	Scope* m_arg_vars;

	/// Local variables
	Scope* m_local_vars;
};


/// Function type
class FuncType : public Type {
public:
	FuncType() : Type(CSTRING("Function")) {}
	~FuncType() {}

	void dump(const void* data) const { std::cout << "function() { }"; }

	void* allocData() { return new Function; }
	void deallocData(void* data) { if (data) { delete static_cast<Function*>(data); } }
};

} // clever

#endif // CLEVER_TYPES_FUNCTION_H
