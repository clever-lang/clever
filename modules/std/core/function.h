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

#define CLEVER_FUNCTION_ARGS      Value* result, const ::std::vector<Value*>& args, const VM* vm, CException* exception
#define CLEVER_FUNC_NAME(name)    clv_f_##name
#define CLEVER_NS_FNAME(ns, name) ns::CLEVER_FUNC_NAME(name)
#define CLEVER_FUNCTION(name)     void CLEVER_FASTCALL CLEVER_FUNC_NAME(name)(CLEVER_FUNCTION_ARGS)

typedef void (CLEVER_FASTCALL *FunctionPtr)(CLEVER_FUNCTION_ARGS);

typedef std::tr1::unordered_map<const CString*, Function*> FunctionMap;
typedef std::pair<const CString*, Function*> FunctionMapEntry;

class Function {
public:
	enum FunctionFlags {
		FF_USER     = 0x00,
		FF_INTERNAL = 0x01,
		FF_STATIC   = 0x02,
		FF_VARIADIC = 0x04,

		FF_INVALID  = 0xFF
	};

	Function()
		: m_name(), m_num_rargs(0), m_num_args(0), m_flags(FF_INVALID),
		  m_environment(NULL) {}

	Function(std::string name, FunctionPtr ptr)
		: m_name(name), m_num_rargs(0), m_num_args(0), m_flags(FF_INTERNAL),
		  m_environment(NULL)
		{ m_info.fptr = ptr; }

	Function(std::string name, size_t addr)
		: m_name(name), m_num_rargs(0), m_num_args(0), m_flags(FF_USER),
		  m_environment(NULL)
		{ m_info.addr = addr; }

	Function(std::string name, MethodPtr ptr)
		: m_name(name), m_num_rargs(0), m_num_args(0), m_flags(FF_INTERNAL),
		  m_environment(NULL)
		{ m_info.mptr = ptr; }

	~Function() {}

	void setName(std::string name) { m_name = name; }
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

	Environment* getEnvironment() { return m_environment; }
	void setEnvironment(Environment* e) {
		m_environment = e;
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

	DISALLOW_COPY_AND_ASSIGN(Function);
};

/// Function type
class FuncType : public Type {
public:
	FuncType()
		: Type(CSTRING("Function")) {}

	~FuncType() {}

	void init(CLEVER_TYPE_INIT_ARGS) {
		Function* ctor = new Function("Function", (MethodPtr) &FuncType::ctor);

		setConstructor(ctor);
		addMethod(ctor);
	}

	void dump(const void* data) const { dump(data, std::cout); }
	void dump(const void* data, std::ostream& out) const { out << "function() {}"; }

	void* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new Function;  }

	CLEVER_METHOD(ctor) {
		result->setObj(this, allocData(NULL));
	}

	void deallocData(void* data) { delete static_cast<Function*>(data); }
};

} // clever

#endif // CLEVER_TYPES_FUNCTION_H
