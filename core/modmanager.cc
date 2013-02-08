/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include "core/modmanager.h"
#include "core/value.h"
#include "core/cstring.h"
#include "core/scope.h"
#include "modules/std/std_pkg.h"
#include "core/user.h"

namespace clever {

/// Adds the available packages to be imported
void ModManager::init()
{
	addModule("std",   new modules::Std);
	addModule("_user", m_user = new UserModule);
}

/// Performs shutdown operation
void ModManager::shutdown()
{
	std::vector<Type*> typevec;
	ModuleMap::const_iterator itm = m_mods.begin(), endm = m_mods.end();

	while (itm != endm) {
		TypeMap& types = itm->second->getTypes();
		TypeMap::const_iterator itt(types.begin()), ite(types.end());

		while (itt != ite) {
			itt->second->deallocMembers();
			typevec.push_back(itt->second);
			++itt;
		}

		clever_delete(itm->second);
		++itm;
	}

	std::for_each(typevec.begin(), typevec.end(), clever_delete<Type>);
}

/// Adds a new module
void ModManager::addModule(const std::string& name, Module* module)
{
	if (m_mods.find(name) != m_mods.end()) {
		std::cerr << "Module `" << name << "' already added!" << std::endl;
		return;
	}

	m_mods.insert(ModulePair(name, module));
	module->init();
	module->setLoaded();

	//std::cout << "init " << module->getName() << std::endl;

	if (module->hasModules()) {
		ModuleMap& mods = module->getModules();
		ModuleMap::const_iterator it = mods.begin(), end = mods.end();

		while (it != end) {
			// @TODO(Felipe): recursivity
			m_mods.insert(ModulePair(it->first, it->second));
			++it;
		}
	}
}

/// Loads an specific module type
void ModManager::loadType(Scope* scope, Environment* env, const CString* name,
	Type* type) const
{
	Value* tmp = new Value(type);

	scope->pushValue(name, tmp)->voffset = env->pushValue(tmp);

	type->init();
}

/// Loads an specific module function
void ModManager::loadFunction(Scope* scope, Environment* env, const CString* name,
	Function* func) const
{
	Value* fval = new Value();

	fval->setObj(CLEVER_FUNC_TYPE, func);

	scope->pushValue(name, fval)->voffset = env->pushValue(fval);
}

/// Loads a module if it is not already loaded
void ModManager::loadModule(Scope* scope, Environment* env, Module* module,
	ImportKind kind, const CString* name) const
{
	if (kind == ModManager::ALL && module->hasModules()) {
		ModuleMap& mods = module->getModules();
		ModuleMap::const_iterator it = mods.begin(), end = mods.end();

		while (it != end) {
			loadModule(scope, env, it->second, kind, NULL);
			++it;
		}
	}

	if (module->isLoaded()) {
		return;
	}

	module->init();
	module->setLoaded();

	//std::cout << "load " << module->getName() << std::endl;

	if (kind & ModManager::FUNCTION) {
		FunctionMap& funcs = module->getFunctions();
		FunctionMap::const_iterator itf(funcs.begin()),	endf(funcs.end());

		while (EXPECTED(itf != endf)) {
			loadFunction(scope, env, itf->first, itf->second);
			++itf;
		}
	}

	if (kind & ModManager::TYPE) {
		TypeMap& types = module->getTypes();
		TypeMap::const_iterator itt(types.begin()), ite(types.end());

		while (EXPECTED(itt != ite)) {
			loadType(scope, env, itt->first, itt->second);
			++itt;
		}
	}
}

/// Imports a module
void ModManager::importModule(Scope* scope, Environment* env,
	const std::string& module, ImportKind kind, const CString* name) const
{
	ModuleMap::const_iterator it = m_mods.find(module);

	//std::cout << "imp " << module << std::endl;

	if (it == m_mods.end()) {
		std::cerr << "Module `" << module << "` not found!" << std::endl;
		return;
	}

	loadModule(scope, env, it->second, kind, name);
}

} // clever
