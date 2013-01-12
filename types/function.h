/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_TYPES_FUNCTION_H
#define CLEVER_TYPES_FUNCTION_H

#include <vector>
#include "core/clever.h"
#include "core/value.h"
#include "core/environment.h"
#include "types/type.h"

namespace clever {

class Value;
class VM;
class Scope;

#define CLEVER_FUNCTION_ARGS      Value* result, const ::std::vector<Value*>& args, const VM* vm
#define CLEVER_FUNC_NAME(name)    clv_f_##name
#define CLEVER_NS_FNAME(ns, name) ns::CLEVER_FUNC_NAME(name)
#define CLEVER_FUNCTION(name)     void CLEVER_FASTCALL CLEVER_FUNC_NAME(name)(CLEVER_FUNCTION_ARGS)

typedef void (CLEVER_FASTCALL *FunctionPtr)(CLEVER_FUNCTION_ARGS);

class Function: public ValueObject {
public:
	enum FuncKind { UNDEF, USER_FUNC, INTERNAL_FUNC };

	Function()
		: ValueObject(), m_name(), m_type(UNDEF), m_num_args(0),
		m_variadic(false), m_environment(NULL) {}

	Function(std::string name, FunctionPtr ptr)
		: ValueObject(), m_name(name), m_type(INTERNAL_FUNC), m_num_args(0),
		m_variadic(false), m_environment(NULL)
		{ m_info.ptr = ptr; }

	Function(std::string name, size_t addr)
		: ValueObject(), m_name(name), m_type(USER_FUNC), m_num_args(0),
		m_variadic(false), m_environment(NULL)
		{ m_info.addr = addr; }

	~Function() {}

	void setName(std::string name) { m_name = name; }
	const std::string& getName() const { return m_name; }

	void setInternal() { m_type = INTERNAL_FUNC; }
	void setUserDefined() { m_type = USER_FUNC; }

	void setVariadic() { m_variadic = true; }
	bool isVariadic() const { return m_variadic; }

	bool isUserDefined() const { return m_type == USER_FUNC; }
	bool isInternal() const { return m_type == INTERNAL_FUNC; }

	FunctionPtr getPtr() const { return m_info.ptr; }
	size_t getAddr() const { return m_info.addr; }

	void setAddr(size_t addr) { m_info.addr = addr; }
	void setPtr(FunctionPtr ptr) { m_info.ptr = ptr; }

	bool hasArgs() const { return m_num_args != 0; }
	size_t getNumArgs() const { return m_num_args; }
	void setNumArgs(size_t n)  { m_num_args = n; }

	Environment* getEnvironment() { return m_environment; }
	void setEnvironment(Environment* e) {
		m_environment = e;
	}
private:
	std::string m_name;
	FuncKind m_type;
	size_t m_num_args;
	bool m_variadic;

	union {
		FunctionPtr ptr;
		size_t addr;
	} m_info;

	Environment* m_environment;

	DISALLOW_COPY_AND_ASSIGN(Function);
};

/// Function type
class FuncType : public Type {
public:
	FuncType() : Type(CSTRING("Function")) {}
	~FuncType() {}

	void dump(const void* data) const { dump(data, std::cout); }
	void dump(const void* data, std::ostream& out) const { out << "function() { }"; }

	void* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new Function; }

	void deallocData(void* data) { if (data) { delete static_cast<Function*>(data); } }
};

} // clever

#endif // CLEVER_TYPES_FUNCTION_H
