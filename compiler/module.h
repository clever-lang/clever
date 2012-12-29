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

#ifndef CLEVER_MODULE_H
#define CLEVER_MODULE_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <string>
#include "compiler/cstring.h"
#include "types/function.h"

#define CLEVER_MODULE_INIT(x) void x::init(int flags)

#define CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION \
	void init(int flags);

namespace clever {

typedef std::tr1::unordered_map<const CString*, Function*> FunctionMap;
typedef std::pair<const CString*, Function*> FuncMapEntry;

class Module {
public:
	Module(std::string name) : m_name(name) {}
	virtual ~Module() {}

	void addFunction(Function* func) {
		m_funcs.insert(FuncMapEntry(CSTRING(func->getName()), func));
	}

	FunctionMap& getFunctions() { return m_funcs; }

	std::string getName() { return m_name; }

	virtual void init(int) = 0;
private:
	FunctionMap m_funcs;
	std::string m_name;
};

typedef std::tr1::unordered_map<const CString*, Module*> ModuleMap;
typedef std::pair<const CString*, Module*> ModulePair;

/// Package representation
class Package {
public:
	Package(std::string name)
		: m_name(name) {}
	virtual ~Package() {}

	void addModule(Module* module) {
		m_modules.insert(ModulePair(CSTRING(module->getName()), module));
	}

	ModuleMap& getModules() { return m_modules; }


	virtual void init() = 0;
	virtual const char* getVersion() const = 0;
private:
	std::string m_name;
	ModuleMap m_modules;
};

} // clever

#endif // CLEVER_MODULE_H
