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
#include "modules/std/core/function.h"

#define CLEVER_MODULE_INIT(x) void x::init()

#define CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION \
	void init();

namespace clever {

class Module;
class Type;

typedef std::tr1::unordered_map<const CString*, Type*> TypeMap;
typedef std::pair<const CString*, Type*> TypeMapEntry;

typedef std::tr1::unordered_map<std::string, Module*> ModuleMap;
typedef std::pair<std::string, Module*> ModulePair;

/// Module representation
class Module {
public:
	enum ModuleStatus { UNLOADED, LOADED };

	Module(const std::string& name)
		: m_name(name), m_flags(UNLOADED), m_funcs(), m_types() {}

	virtual ~Module() {}

	void addModule(Module* mod) {
		m_mods.insert(ModulePair(mod->getName(), mod));
	}

	ModuleMap& getModules() { return m_mods; }
	bool hasModules() const { return m_mods.size(); }

	void addType(const CString* name, Type* type) {
		m_types.insert(TypeMapEntry(name, type));
	}

	TypeMap& getTypes() { return m_types; }

	Function* addFunction(Function* func) {
		m_funcs.insert(FunctionMapEntry(CSTRING(func->getName()), func));
		return func;
	}

	FunctionMap& getFunctions() { return m_funcs; }

	const std::string& getName() { return m_name; }

	void setLoaded() { m_flags = LOADED; }
	bool isLoaded() const { return m_flags == LOADED; }

	virtual void init() = 0;
private:
	ModuleMap m_mods;
	std::string m_name;
	ModuleStatus m_flags;
	FunctionMap m_funcs;
	TypeMap m_types;
};

/*

typedef std::tr1::unordered_map<std::string, Module*> ModuleMap;
typedef std::pair<std::string, Module*> ModulePair;

/// Package representation
class Package {
public:
	enum PackageStatus { UNLOADED, LOADED, FULLY_LOADED };

	Package(const std::string& name)
		: m_name(name), m_flags(UNLOADED), m_modules() {}

	virtual ~Package() {}

	void addModule(Module* module) {
		m_modules.insert(ModulePair(module->getName(), module));
	}

	ModuleMap& getModules() { return m_modules; }

	void setLoaded() { m_flags = LOADED; }
	void setFullyLoaded() { m_flags = FULLY_LOADED; }

	bool isLoaded() const { return m_flags == LOADED || m_flags == FULLY_LOADED; }
	bool isFullyLoaded() const { return m_flags == FULLY_LOADED; }

	virtual void init() = 0;
	virtual const char* getVersion() const = 0;
private:
	std::string m_name;
	PackageStatus m_flags;
	ModuleMap m_modules;
};
*/
} // clever

#endif // CLEVER_MODULE_H
