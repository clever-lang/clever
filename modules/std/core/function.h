/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_FUNCTION_H
#define CLEVER_FUNCTION_H

#include <vector>
#include "core/clever.h"
#include "core/value.h"
#include "core/environment.h"
#include "core/type.h"

namespace clever {

class Value;
class VM;
class Scope;

#define CLEVER_FUNCTION_ARGS      Value* result, const ValueVector& args, const VM* vm, CException* exception
#define CLEVER_FUNC_NAME(name)    clv_f_##name
#define CLEVER_NS_FNAME(ns, name) ns::CLEVER_FUNC_NAME(name)
#define CLEVER_FUNCTION(name)     void CLEVER_FASTCALL CLEVER_FUNC_NAME(name)(CLEVER_FUNCTION_ARGS)

typedef void (CLEVER_FASTCALL *FunctionPtr)(CLEVER_FUNCTION_ARGS);

class Function : public TypeObject {
public:
	enum FunctionFlags {
		FF_USER     = 0x00,
		FF_INTERNAL = 1<<0,
		FF_STATIC   = 1<<1,
		FF_VARIADIC = 1<<2,
		FF_CLOSURE  = 1<<3,
		FF_PUBLIC   = 1<<4,
		FF_PRIVATE  = 1<<5,
		FF_INVALID  = 0xFF
	};

	Function()
		: m_name(), m_num_rargs(0), m_num_args(0), m_flags(FF_INVALID),
		  m_environment(NULL), m_context(NULL) {}

	Function(const std::string& name, FunctionPtr ptr)
		: m_name(name), m_num_rargs(0), m_num_args(0), m_flags(FF_INTERNAL|FF_PUBLIC),
		  m_environment(NULL), m_context(NULL)
		{ m_info.fptr = ptr; }

	Function(const std::string& name, size_t addr)
		: m_name(name), m_num_rargs(0), m_num_args(0), m_flags(FF_USER|FF_PUBLIC),
		  m_environment(NULL), m_context(NULL)
		{ m_info.addr = addr; }

	Function(const std::string& name, MethodPtr ptr, const Type* context = NULL)
		: m_name(name), m_num_rargs(0), m_num_args(0), m_flags(FF_INTERNAL|FF_PUBLIC),
		  m_environment(NULL), m_context(context)
		{ m_info.mptr = ptr; }

	~Function() {}

	void setName(const std::string& name) { m_name = name; }
	const std::string& getName() const { return m_name; }

	bool isValid() const { return m_flags < FF_INVALID; }

	void setInternal() {
		if (isValid()) {
			m_flags |= FF_INTERNAL;
		} else {
			m_flags = FF_INTERNAL;
		}
	}
	bool isInternal() const { return m_flags & FF_INTERNAL; }

	void setUserDefined() {
		if (isValid()) {
			m_flags &= ~FF_INTERNAL;
		} else {
			m_flags = FF_USER;
		}
	}
	bool isUserDefined() const { return !isInternal(); }

	bool isPublic() const { return m_flags & FF_PUBLIC; }
	bool isPrivate() const { return m_flags & FF_PRIVATE; }

	void setPublic() { m_flags &= ~FF_PRIVATE; m_flags |= FF_PUBLIC; }
	void setPrivate() { m_flags &= ~FF_PUBLIC; m_flags |= FF_PRIVATE; }

	void setStatic() { m_flags |= FF_STATIC; }
	bool isStatic() const { return m_flags & FF_STATIC; }

	void setVariadic() { m_flags |= FF_VARIADIC; }
	bool isVariadic() const { return m_flags & FF_VARIADIC; }

	MethodPtr getMethodPtr() const { return m_info.mptr; }
	FunctionPtr getFuncPtr() const { return m_info.fptr; }
	size_t getAddr() const { return m_info.addr; }

	void setAddr(size_t addr) { m_info.addr = addr; }
	void setPtr(FunctionPtr ptr) { m_info.fptr = ptr; }
	void setPtr(MethodPtr ptr) { m_info.mptr = ptr; }

	bool hasArgs() const { return m_num_args != 0; }
	size_t getNumArgs() const { return m_num_args; }
	void setNumArgs(size_t n)  { m_num_args = n; }

	size_t getNumRequiredArgs() const { return m_num_rargs; }
	void setNumRequiredArgs(size_t num) { m_num_rargs = num; }

	Environment* getEnvironment() const { return m_environment; }
	void setEnvironment(Environment* env) { m_environment = env; }

	void setClosure() { m_flags |= FF_CLOSURE; }
	bool isClosure() const { return m_flags & FF_CLOSURE; }

	void setContext(const Type* ctx) { m_context = ctx; }
	const Type* getContext() const { return m_context; }
	bool hasContext() const { return m_context != NULL; }

	Function* getClosure() const {
		Function* func = new Function(m_name, m_info.addr);

		func->m_num_rargs = m_num_rargs;
		func->m_num_args = m_num_args;
		func->m_flags = m_flags | FF_CLOSURE;
		func->m_environment = m_environment;

		return func;
	}
private:
	std::string m_name;
	size_t m_num_rargs;
	size_t m_num_args;

	long m_flags;

	union {
		FunctionPtr fptr;
		MethodPtr mptr;
		size_t addr;
	} m_info;

	Environment* m_environment;
	const Type* m_context;

	DISALLOW_COPY_AND_ASSIGN(Function);
};

/// Function type
class FuncType : public Type {
public:
	FuncType()
		: Type("Function") {}

	~FuncType() {}

	virtual void init() {
		setConstructor((MethodPtr)&FuncType::ctor);
	}

	virtual std::string toString(TypeObject* data) const {
		return std::string("function () {}");
	}

	CLEVER_METHOD(ctor) {
		result->setObj(this, new Function);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(FuncType);
};

} // clever

#endif // CLEVER_FUNCTION_H
