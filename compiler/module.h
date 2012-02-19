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

#include <string>
#include <vector>
#include <list>
#include <map>
#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include "compiler/clever.h"
#include "compiler/function.h"
#include "compiler/method.h"

namespace clever {

class CString;
class Module;
class Value;
class Type;

/**
 * Module function and method prototype
 */
typedef std::tr1::unordered_map<const CString*, Module*> ModuleMap;
typedef std::pair<const CString*, Module*> ModulePair;

typedef Type Class;
typedef std::tr1::unordered_map<const CString*, Class*> ClassMap;

typedef std::tr1::unordered_map<const CString*, Value*> ConstMap;
typedef std::pair<const CString*, Value*> ConstPair;

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

	const std::string& getName() const {
		return m_name;
	}

	FunctionMap& getFunctions() {
		return m_functions;
	}

	ConstMap& getConstants() {
		return m_const_table;
	}

	ClassMap& getClassTable() {
		return m_class_table;
	}

	Function* addFunction(Function* func) {
		m_functions.insert(FunctionPair(func->getName(), func));

		return func;
	}

	void addConstant(const CString* name, Value* value) {
		m_const_table.insert(ConstPair(name, value));
	}

	void addClass(Class* klass) {
		m_class_table.insert(std::make_pair(klass->getName(), klass));
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
	virtual void init() = 0;

	/* Module version */
	virtual const char* getVersion() const { return NULL; }
private:
	/* Module state */
	bool m_state;
	/* Module name */
	const std::string m_name;
	/* Module function list */
	FunctionMap m_functions;
	/* Class table */
	ClassMap m_class_table;
	/* Constant table */
	ConstMap m_const_table;

	DISALLOW_COPY_AND_ASSIGN(Module);
};

/**
 * Package representation
 */
class NO_INIT_VTABLE Package {
public:
	enum PackageState { UNLOADED, LOADED, FULLY_LOADED };

	Package(std::string name)
		: m_state(UNLOADED), m_name(name) { }

	virtual ~Package() { }

	/**
	 * Add a new package module
	 */
	void addModule(Module* module) {
		m_modules.insert(ModulePair(CSTRING(module->getName()), module));
	}
	/**
	 * Returns the package modules map
	 */
	ModuleMap& getModules() {
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
	virtual void init() = 0;
	/**
	 * Package version
	 */
	virtual const char* getVersion() const { return NULL; }
private:
	PackageState m_state;
	const std::string& m_name;
	ModuleMap m_modules;

	DISALLOW_COPY_AND_ASSIGN(Package);
};

} // clever

#endif // CLEVER_MODULE_H
