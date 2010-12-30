/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
#include <list>

namespace clever {

class Module;
struct Function;

typedef std::list<Function*> FunctionList;
typedef std::list<Module*> ModuleList;

/**
 * Module function prototype
 */
typedef void (*module_function)();

/**
 * Function representation
 */
class Function {
public:
	Function(std::string name, module_function func)
		: m_name(name), m_func(func) { }

	~Function() { }

	inline const std::string get_name() { return m_name; }
	inline module_function get_func() { return m_func; }
private:
	const std::string m_name;
	module_function m_func;
};

/**
 * Module representation
 */
class Module {
public:
	Module(std::string name, Function* func)
		: m_name(name) {
		addFunction(func);
	}

	~Module() { }

	inline FunctionList& get_functions() {
		return m_functions;
	}

	inline void addFunction(Function* func) {
		m_functions.push_back(func);
	}
private:
	const std::string m_name;
	FunctionList m_functions;
};

} // clever

#endif // CLEVER_MODULE_H