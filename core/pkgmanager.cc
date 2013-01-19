/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include "core/pkgmanager.h"
#include "core/value.h"
#include "core/cstring.h"
#include "core/scope.h"
#include "modules/std/std_pkg.h"

namespace clever {

/// Adds the available packages to be imported
void PkgManager::init()
{
	addPackage(CSTRING("std"), new packages::Std);
}

/// Performs shutdown operation
void PkgManager::shutdown()
{
	std::vector<Type*> typevec;
	PackageMap::const_iterator it = m_pkgs.begin(), end = m_pkgs.end();

	while (it != end) {
		ModuleMap& mods = it->second->getModules();
		ModuleMap::const_iterator itm = mods.begin(), endm = mods.end();

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

		clever_delete(it->second);
		++it;
	}

	for (size_t i = 0, j = typevec.size(); i < j; ++i) {
		clever_delete(typevec[i]);
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
	if (!module->isLoaded()) {
		module->init();
		module->setLoaded();
	}

	if (kind == PkgManager::ALL) {
		FunctionMap& funcs = module->getFunctions();
		FunctionMap::const_iterator itf = funcs.begin(),
			endf = funcs.end();

		while (EXPECTED(itf != endf)) {
			loadFunction(scope, env, itf->first, itf->second);
			++itf;
		}

		TypeMap& types = module->getTypes();
		TypeMap::const_iterator itt(types.begin()), ite(types.end());

		while (EXPECTED(itt != ite)) {
			loadType(scope, env, itt->first, itt->second);
			++itt;
		}
	} else if (kind == PkgManager::FUNCTION) {
		clever_assert_not_null(name);

		FunctionMap& funcs = module->getFunctions();
		FunctionMap::const_iterator itf = funcs.find(name);

		if (itf != funcs.end()) {
			loadFunction(scope, env, itf->first, itf->second);
			++itf;
		}
	} else if (kind == PkgManager::TYPE) {
		clever_assert_not_null(name);

		TypeMap& types = module->getTypes();
		TypeMap::const_iterator itt = types.find(name);

		if (itt != types.end()) {
			loadType(scope, env, itt->first, itt->second);
			++itt;
		}
	}
}

/// Imports a module
void PkgManager::importModule(Scope* scope, Environment* env, const CString* package,
	const CString* module, ImportKind kind, const CString* name) const
{
	PackageMap::const_iterator it = m_pkgs.find(package);

	if (it == m_pkgs.end()) {
		std::cerr << "Package not found!" << std::endl;
		return;
	}

	if (!it->second->isLoaded()) {
		it->second->init();
		it->second->setLoaded();
	}

	ModuleMap& mods = it->second->getModules();
	ModuleMap::const_iterator itm = mods.find(module);

	if (itm == mods.end()) {
		std::cerr << "Module not found!" << std::endl;
		return;
	}

	loadModule(scope, env, itm->second, kind, name);
}

/// Imports a package
void PkgManager::importPackage(Scope* scope, Environment* env, const CString* package) const
{
	PackageMap::const_iterator it = m_pkgs.find(package);

	if (it == m_pkgs.end()) {
		std::cerr << "Package not found!" << std::endl;
	}
	if (it->second->isFullyLoaded()) {
		return;
	}
	if (!it->second->isLoaded()) {
		it->second->init();
	}
	it->second->setFullyLoaded();

	ModuleMap& mods = it->second->getModules();
	ModuleMap::const_iterator itm = mods.begin(), endm = mods.end();

	while (EXPECTED(itm != endm)) {
		loadModule(scope, env, itm->second, PkgManager::ALL, NULL);
		++itm;
	}
}

} // clever
