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

#define CLEVER_FUNCTION_ARGS Value* result, const ::std::vector<Value*>& args, const VM* vm
#define CLEVER_FUNC_NAME(name) clv_f_##name
#define CLEVER_NS_FNAME(ns, name) ns::CLEVER_FUNC_NAME(name)
#define CLEVER_FUNCTION(name) void CLEVER_FASTCALL CLEVER_FUNC_NAME(name)(CLEVER_FUNCTION_ARGS)

typedef void (CLEVER_FASTCALL *FunctionPtr)(CLEVER_FUNCTION_ARGS);

class Function: public ValueObject {
public:
	enum FuncKind { UNDEF, USER_FUNC, INTERNAL_FUNC };

	Function()
		: ValueObject(), m_name(), m_type(UNDEF), m_arg_vars(NULL), m_local_vars(NULL), m_environment(NULL) {}

	Function(std::string name, FunctionPtr ptr)
		: ValueObject(), m_name(name), m_type(UNDEF), m_arg_vars(NULL), m_local_vars(NULL), m_environment(NULL)
		{ m_info.ptr = ptr; }

	Function(std::string name, size_t addr)
		: ValueObject(), m_name(name), m_type(UNDEF), m_arg_vars(NULL), m_local_vars(NULL), m_environment(NULL)
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

	bool hasArgs() const { return m_arg_vars != NULL; }

	void setLocalVars(Scope* local_vars) { m_local_vars = local_vars; }
	void setArgVars(Scope* arg_vars) { m_arg_vars = arg_vars; }

	Environment* getEnvironment() { return m_environment; }
	void setEnvironment(Environment* e) {
		m_environment = e;
	}
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

	Environment* m_environment;
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

	void increment(Value* value) const {}

	void decrement(Value* value) const {}
};

} // clever

#endif // CLEVER_TYPES_FUNCTION_H
