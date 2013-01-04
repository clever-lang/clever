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

namespace clever {

typedef std::tr1::unordered_map<const CString*, Function*> FunctionMap;
typedef std::pair<const CString*, Function*> FuncMapEntry;

typedef std::tr1::unordered_map<const CString*, Type*> TypeMap;
typedef std::pair<const CString*, Type*> TypeEntry;

/// Module representation
class Module {
public:
	enum ModuleStatus { UNLOADED, LOADED };

	Module(std::string name)
		: m_name(name), m_flags(UNLOADED), m_funcs() {}

	virtual ~Module() {}

	void addType(const CString* name, Type* type) {
		m_types.insert(TypeEntry(name, type));
	}

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
	TypeMap m_types;
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
