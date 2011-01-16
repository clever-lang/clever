/*
 * Clever language
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

#include <vector>
#include <string>
#include <list>
#include "global.h"
#include "value.h"

namespace clever {

class Module;
class Function;

typedef std::list<Function*> FunctionList;
typedef std::list<Module*> ModuleList;

/**
 * Macros to help on module function declaration
 */
#define CLEVER_FUNCTION_ARGS const CallArgs& args
#define CLEVER_METHOD_ARGS const CallArgs& args
#define CLEVER_FUNC_NAME(name) clv_##name
#define CLEVER_FUNCTION(name) void CLEVER_FASTCALL CLEVER_FUNC_NAME(name)(CLEVER_FUNCTION_ARGS) throw()
#define CLEVER_METHOD(name) void name(CLEVER_METHOD_ARGS) const throw()

/**
 * Function/method arguments vector
 */
typedef std::vector<Value*> CallArgs;

/**
 * Module function prototype
 */
typedef void (CLEVER_FASTCALL *FunctionPtr)(CLEVER_FUNCTION_ARGS);

typedef void (Type::*MethodPtr)(CLEVER_METHOD_ARGS) const;

/**
 * Method representation
 */
class Method {
public:
	Method(const CString* name, MethodPtr method)
		: m_name(name), m_method(method) { }

	~Method() { }

	const CString* get_name() const throw() { return m_name; }
	MethodPtr get_method() const throw() { return m_method; }

	DISALLOW_COPY_AND_ASSIGN(Method);
private:
	const CString* m_name;
	MethodPtr m_method;
};

/**
 * Function representation
 */
class Function {
public:
	Function(std::string name, FunctionPtr func)
		: m_name(name), m_func(func) { }

	~Function() { }

	const std::string get_name() const throw() { return m_name; }
	FunctionPtr get_func() const throw() { return m_func; }

	DISALLOW_COPY_AND_ASSIGN(Function);
private:
	/* Function name */
	const std::string m_name;
	/* Function pointer */
	FunctionPtr m_func;
};

/**
 * Module representation
 */
class Module {
public:
	Module(std::string name)
		: m_name(name) { }

	virtual ~Module() { }

	const std::string& get_name() const throw() {
		return m_name;
	}

	FunctionList& get_functions() throw() {
		return m_functions;
	}

	void addFunction(Function* func) throw() {
		m_functions.push_back(func);
	}

	/* Module initialization */
	virtual void Init() throw() = 0;

	/* Module version */
	virtual const char* getVersion() const { return NULL; }

	DISALLOW_COPY_AND_ASSIGN(Module);
private:
	/* Module name */
	const std::string m_name;
	/* Module function list */
	FunctionList m_functions;
};

} // clever

#endif // CLEVER_MODULE_H