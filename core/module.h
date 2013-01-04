/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_MODULE_H
#define CLEVER_MODULE_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <string>
#include "types/function.h"

#define CLEVER_MODULE_INIT(x) void x::init(int flags)

#define CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION \
	void init(int flags);

/* {{{ Accessor Macros for Function Arguments */
#define CLV_ARG_COUNT		 args.size
/* {{{ CString */
#define CLV_ARG_CSTR(index) args[index]->getStr() /* }}} */
/* {{{ String Pointer */
#define CLV_ARG_PSTR(index) ((char*) (args[index]->getStr())->c_str()) /* }}} */
#define CLV_ARG_DBL(index)	 args[index]->getDouble()
#define CLV_ARG_LONG(index) args[index]->getLong()
#define CLV_ARG_OBJ(index)	 args[index]->getObj()
#define CLV_ARG_DATA(index) args[index]->getData()
#define CLV_ARG_DUMP(index) args[index]->dump()
/* }}} */

#define CLV_RETURN_STR(r)	
#define CLV_RETURN_DBL(d)
#define CLV_RETURN_LONG(l)
#define CLV_RETURN_OBJ(o)

namespace clever {

typedef std::tr1::unordered_map<const CString*, Function*> FunctionMap;
typedef std::pair<const CString*, Function*> FuncMapEntry;

/// Module representation
class Module {
public:
	enum ModuleStatus { UNLOADED, LOADED };

	Module(std::string name)
		: m_name(name), m_flags(UNLOADED), m_funcs() {}

	virtual ~Module() {}

	void addFunction(Function* func) {
		m_funcs.insert(FuncMapEntry(CSTRING(func->getName()), func));
	}

	FunctionMap& getFunctions() { return m_funcs; }

	std::string getName() { return m_name; }

	void setLoaded() { m_flags = LOADED; }
	bool isLoaded() const { return m_flags == LOADED; }

	virtual void init(int) = 0;
private:
	std::string m_name;
	ModuleStatus m_flags;
	FunctionMap m_funcs;
};

typedef std::tr1::unordered_map<const CString*, Module*> ModuleMap;
typedef std::pair<const CString*, Module*> ModulePair;

/// Package representation
class Package {
public:
	enum PackageStatus { UNLOADED, LOADED };

	Package(std::string name)
		: m_name(name), m_flags(UNLOADED) {}

	virtual ~Package() {}

	void addModule(Module* module) {
		m_modules.insert(ModulePair(CSTRING(module->getName()), module));
	}

	ModuleMap& getModules() { return m_modules; }

	void setLoaded() { m_flags = LOADED; }
	bool isLoaded() const { return m_flags == LOADED; }

	virtual void init() = 0;
	virtual const char* getVersion() const = 0;
private:
	std::string m_name;
	PackageStatus m_flags;
	ModuleMap m_modules;
};

} // clever

#endif // CLEVER_MODULE_H
