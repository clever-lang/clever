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
void PkgManager::init()
{
	addModule("std",   new packages::Std);
	addModule("_user", m_user = new UserModule);
}

/// Performs shutdown operation
void PkgManager::shutdown()
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

	for (size_t i = 0, j = typevec.size(); i < j; ++i) {
		clever_delete(typevec[i]);
	}
}

/// Adds a new module
void PkgManager::addModule(const std::string& name, Module* module)
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
void PkgManager::loadType(Scope* scope, Environment* env, const CString* name,
	Type* type) const
{
	Value* tmp = new Value(type);

	scope->pushValue(name, tmp)->voffset = env->pushValue(tmp);

	type->init();
}

/// Loads an specific module function
void PkgManager::loadFunction(Scope* scope, Environment* env, const CString* name,
	Function* func) const
{
	Value* fval = new Value();

	fval->setObj(CLEVER_FUNC_TYPE, func);

	scope->pushValue(name, fval)->voffset = env->pushValue(fval);
}

/// Loads a module if it is not already loaded
void PkgManager::loadModule(Scope* scope, Environment* env, Module* module,
	ImportKind kind, const CString* name) const
{
	if (kind == PkgManager::ALL && module->hasModules()) {
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

	if (kind & PkgManager::FUNCTION) {
		FunctionMap& funcs = module->getFunctions();
		FunctionMap::const_iterator itf(funcs.begin()),	endf(funcs.end());

		while (EXPECTED(itf != endf)) {
			loadFunction(scope, env, itf->first, itf->second);
			++itf;
		}
	}

	if (kind & PkgManager::TYPE) {
		TypeMap& types = module->getTypes();
		TypeMap::const_iterator itt(types.begin()), ite(types.end());

		while (EXPECTED(itt != ite)) {
			loadType(scope, env, itt->first, itt->second);
			++itt;
		}
	}
}

/// Imports a module
void PkgManager::importModule(Scope* scope, Environment* env,
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
