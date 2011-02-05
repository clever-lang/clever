/*
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
 *
 * $Id$
 */

#ifndef CLEVER_MODULE_H
#define CLEVER_MODULE_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <tr1/unordered_map>
#include "global.h"

namespace clever {

class CString;
class Module;
class Value;
class Type;
class Function;

typedef std::vector<Value*> ValueVector;

/**
 * Macros to help on module function declaration
 */
#define CLEVER_FUNCTION_ARGS const ValueVector* args, Value* retval
#define CLEVER_METHOD_ARGS const ValueVector* args, Value* retval, Value* value
#define CLEVER_FUNC_NAME(name) clv_##name
#define CLEVER_FUNCTION(name) void CLEVER_FASTCALL CLEVER_FUNC_NAME(name)(CLEVER_FUNCTION_ARGS) throw()
#define CLEVER_METHOD(name) void CLEVER_FASTCALL name(CLEVER_METHOD_ARGS) throw()

/**
 * Module function and method prototype
 */
typedef void (CLEVER_FASTCALL *FunctionPtr)(CLEVER_FUNCTION_ARGS);
typedef void (CLEVER_FASTCALL *MethodPtr)(CLEVER_METHOD_ARGS);

typedef std::tr1::unordered_map<std::string, Function*> FunctionMap;
typedef std::pair<std::string, Function*> FunctionPair;

typedef std::tr1::unordered_map<const CString*, Module*> ModuleMap;
typedef std::pair<const CString*, Module*> ModulePair;

typedef std::tr1::unordered_map<std::string, const Type*> FunctionArgs;
typedef std::pair<std::string, const Type*> FunctionArgsPair;

/**
 * Function representation
 */
class Function {
public:
	enum FunctionType { INTERNAL, USER };

	explicit Function(std::string name)
		: m_name(name), m_type(INTERNAL), m_num_args(0), m_return(NULL) { }

	Function(std::string name, FunctionPtr ptr)
		: m_name(name), m_type(INTERNAL), m_num_args(0), m_return(NULL) { m_info.ptr = ptr; }

	Function(std::string name, FunctionPtr ptr, const Type* rtype)
		: m_name(name), m_type(INTERNAL), m_num_args(0), m_return(rtype) { m_info.ptr = ptr; }

	Function(std::string name, FunctionPtr ptr, int numargs)
		: m_name(name), m_type(INTERNAL), m_num_args(numargs), m_return(NULL) { m_info.ptr = ptr; }

	Function(std::string name, FunctionPtr ptr, int numargs, const Type* rtype)
		: m_name(name), m_type(INTERNAL), m_num_args(numargs), m_return(rtype) { m_info.ptr = ptr; }

	Function(std::string& name, unsigned int offset)
		: m_name(name), m_type(USER), m_num_args(0), m_return(NULL) { m_info.offset = offset; }

	Function(std::string& name, unsigned int offset, int numargs)
		: m_name(name), m_type(USER), m_num_args(numargs), m_return(NULL) { m_info.offset = offset; }

	virtual ~Function() { }

	Function* addArg(std::string name, const Type* type) throw() {
		m_args.insert(FunctionArgsPair(name, type));
		++m_num_args;

		return this;
	}

	FunctionArgs& getArgs() throw() { return m_args; }

	void set_vars(Value* vars) { m_vars = vars; }
	Value* get_vars() throw() { return m_vars; }

	int get_num_args() const { return m_num_args; }
	void setVariadicArgs() throw() { m_num_args = -1; }

	void setInternal() throw() { m_type = INTERNAL; }
	void setUserDefined() throw() { m_type = USER; }

	bool isUserDefined() const throw() { return m_type == USER; }
	bool isInternal() const throw() { return m_type == INTERNAL; }

	void set_offset(unsigned int num) { m_info.offset = num; }
	unsigned int get_offset() const throw() { return m_info.offset; }

	void set_return(const Type* type) { m_return = type; }
	const Type* get_return() const throw() { return m_return; }

	FunctionPtr get_ptr() const throw() { return m_info.ptr; }

	const std::string& get_name() const throw() { return m_name; }

	void call (const ValueVector* args, Value* result) {
		m_info.ptr(args, result);
	}

	unsigned int call() {
		return m_info.offset;
	}

private:
	union {
		FunctionPtr  ptr;
		unsigned int offset;
	} m_info;

	const Type* m_return;
	FunctionType m_type;
	FunctionArgs m_args;

	Value* m_vars;
	std::string m_name;
	int m_num_args;
};

/**
 * Package representation
 */
class NO_INIT_VTABLE Package {
public:
	enum { UNLOADED, LOADED, FULLY_LOADED };

	Package(std::string name)
		: m_state(UNLOADED), m_name(name) { }

	virtual ~Package() { }

	/**
	 * Add a new package module
	 */
	void addModule(const CString* name, Module* module) throw() {
		m_modules.insert(ModulePair(name, module));
	}
	/**
	 * Returns the package modules map
	 */
	ModuleMap& get_modules() {
		return m_modules;
	}
	/**
	 * Check if the package is loaded
	 */
	bool isLoaded() const {	return m_state == LOADED || m_state == FULLY_LOADED; }
	/**
	 * Check if the package is unloaded
	 */
	bool isUnloaded() const { return m_state == UNLOADED; }
	/**
	 * Check if the package was fully loaded
	 */
	bool isFullyLoaded() const { return m_state == FULLY_LOADED; }
	/**
	 * Set the package state to loaded
	 */
	void setLoaded() { m_state = LOADED; }
	/**
	 * Set the package state to fully loaded
	 */
	void setFullyLoaded() { m_state = FULLY_LOADED; }
	/**
	 * Initializes package data
	 */
	virtual void Init() throw() = 0;
	/**
	 * Package version
	 */
	virtual const char* getVersion() const { return NULL; }
private:
	bool m_state;
	const std::string& m_name;
	ModuleMap m_modules;

	DISALLOW_COPY_AND_ASSIGN(Package);
};

/**
 * Module representation
 */
class NO_INIT_VTABLE Module {
public:
	enum { UNLOADED, LOADED };

	Module(std::string name)
		: m_state(UNLOADED), m_name(name) { }

	virtual ~Module() {
		FunctionMap::const_iterator it = m_functions.begin(), end = m_functions.end();

		while (it != end) {
			delete it->second;
			++it;
		}
	}

	const std::string& get_name() const throw() {
		return m_name;
	}

	FunctionMap& get_functions() throw() {
		return m_functions;
	}

	Function* addFunction(Function* func) throw() {
		m_functions.insert(FunctionPair(func->get_name(), func));

		return func;
	}
	/**
	 * Check if the module is loaded
	 */
	bool isLoaded() const {	return m_state == LOADED; }
	/**
	 * Check if the package is unloaded
	 */
	bool isUnloaded() const { return m_state == UNLOADED; }
	/**
	 * Set the module state to loaded
	 */
	void setLoaded() { m_state = LOADED; }

	/* Module initialization */
	virtual void Init() throw() = 0;

	/* Module version */
	virtual const char* getVersion() const { return NULL; }
private:
	/* Module state */
	bool m_state;
	/* Module name */
	const std::string m_name;
	/* Module function list */
	FunctionMap m_functions;

	DISALLOW_COPY_AND_ASSIGN(Module);
};

} // clever

#endif // CLEVER_MODULE_H
