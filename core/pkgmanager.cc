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
	PackageMap::const_iterator it = m_pkgs.begin(), end = m_pkgs.end();

	while (it != end) {
		ModuleMap& mods = it->second->getModules();
		ModuleMap::const_iterator itm = mods.begin(), endm = mods.end();

		while (itm != endm) {
			TypeMap& types = itm->second->getTypes();
			TypeMap::const_iterator itt(types.begin()), ite(types.end());

			while (itt != ite) {
				delete itt->second;
				++itt;
			}

			delete itm->second;
			++itm;
		}

		delete it->second;
		++it;
	}
}

/// Loads a module if it is not already loaded
void PkgManager::loadModule(Scope* scope, Environment* env, Module* module) const
{
	if (module->isLoaded()) {
		return;
	}
	module->init(PKG_INIT_FUNC);
	module->setLoaded();

	FunctionMap& funcs = module->getFunctions();
	FunctionMap::const_iterator itf = funcs.begin(),
		endf = funcs.end();

	while (EXPECTED(itf != endf)) {
		Value* fval = new Value();

		fval->setType(CLEVER_FUNC_TYPE);
		fval->setObj(itf->second);

		scope->pushValue(itf->first, fval);
		env->pushValue(fval);

		++itf;
	}

	module->init(PKG_INIT_TYPE);

	TypeMap& types = module->getTypes();
	TypeMap::const_iterator itt(types.begin()), ite(types.end());

	while (EXPECTED(itt != ite)) {
		Value* tmp = new Value(itt->second);
		scope->pushValue(itt->first, tmp);
		env->pushValue(tmp);
		++itt;
	}
}

/// Imports a module
void PkgManager::importModule(Scope* scope, Environment* env, const CString* package,
	const CString* module) const
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

	loadModule(scope, env, itm->second);
}

/// Imports a package
void PkgManager::importPackage(Scope* scope, Environment* env, const CString* package) const
{
	PackageMap::const_iterator it = m_pkgs.find(package);

	if (it == m_pkgs.end()) {
		std::cerr << "Package not found!" << std::endl;
	}
	if (it->second->isLoaded()) {
		return;
	}
	it->second->init();
	it->second->setLoaded();

	ModuleMap& mods = it->second->getModules();
	ModuleMap::const_iterator itm = mods.begin(), endm = mods.end();

	while (EXPECTED(itm != endm)) {
		loadModule(scope, env, itm->second);
		++itm;
	}
}

} // clever
