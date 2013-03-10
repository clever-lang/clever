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
#include "core/type.h"
#include "modules/std/core/function.h"

#define CLEVER_MODULE_INIT(x) void x::init()

#define CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION \
	void init()

namespace clever {

class Module;
class Type;

typedef std::tr1::unordered_map<std::string, Type*> TypeMap;
typedef std::tr1::unordered_map<std::string, Module*> ModuleMap;
typedef std::tr1::unordered_map<std::string, Value*> VarMap;
typedef std::tr1::unordered_map<std::string, Function*> FunctionMap;

/// Module representation
class Module {
public:
	enum ModuleStatus { UNLOADED, LOADED };

	Module(const std::string& name)
		: m_name(name), m_flags(UNLOADED) {}

	virtual ~Module() {}

	void addVariable(const std::string& name, Value* value) {
		m_vars.insert(VarMap::value_type(name, value));
	}

	void addModule(Module* mod) {
		m_mods.insert(ModuleMap::value_type(mod->getName(), mod));
	}

	void addType(Type* type) {
		m_types.insert(TypeMap::value_type(type->getName(), type));
	}

	Function* addFunction(Function* func) {
		m_funcs.insert(FunctionMap::value_type(func->getName(), func));
		return func;
	}

	ModuleMap& getModules() { return m_mods; }
	TypeMap& getTypes() { return m_types; }
	VarMap& getVars() { return m_vars; }
	FunctionMap& getFunctions() { return m_funcs; }

	bool hasModules() const { return !m_mods.empty(); }

	const std::string& getName() { return m_name; }

	void setLoaded() { m_flags = LOADED; }
	bool isLoaded() const { return m_flags == LOADED; }

	virtual void init() = 0;
private:
	std::string m_name;
	ModuleMap m_mods;
	VarMap m_vars;
	ModuleStatus m_flags;
	FunctionMap m_funcs;
	TypeMap m_types;
};

} // clever

#endif // CLEVER_MODULE_H
