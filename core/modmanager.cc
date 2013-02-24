/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include "core/driver.h"
#include "core/modmanager.h"
#include "core/value.h"
#include "core/cstring.h"
#include "core/scope.h"
#include "modules/std/std_pkg.h"
#include "modules/db/db_pkg.h"
#include "core/user.h"

namespace clever {

/// Adds the available packages to be imported
void ModManager::init()
{
	addModule("std",   new modules::Std);
	addModule("db",	   new modules::Db);
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
		//std::cerr << "Module `" << name << "' already added!" << std::endl;
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
void ModManager::loadType(Scope* scope, Environment* env, const std::string& name,
	Type* type) const
{
	Value* tmp = new Value(type);

	scope->pushValue(CSTRING(name), tmp)->voffset = env->pushValue(tmp);

	type->init();
}

/// Loads an specific module function
void ModManager::loadFunction(Scope* scope, Environment* env, const CString* name,
	Function* func) const
{
	Value* fval = new Value();

	fval->setObj(CLEVER_FUNC_TYPE, func);
	fval->setConst(true);

	scope->pushValue(name, fval)->voffset = env->pushValue(fval);
}

void ModManager::loadModuleContent(Scope* scope, Environment* env, Module* module,
	size_t kind, const CString* name, const std::string& ns_prefix) const
{
	if (kind & ModManager::FUNCTION) {
		FunctionMap& funcs = module->getFunctions();

		if (name) {
			FunctionMap::const_iterator it = funcs.find(name);

			if (it == funcs.end()) {
				std::cerr << "Function `" << *name << "' not found!" << std::endl;
			} else {
				loadFunction(scope, env, it->first, it->second);
			}
		} else {
			FunctionMap::const_iterator itf(funcs.begin()),	endf(funcs.end());

			while (EXPECTED(itf != endf)) {
				const CString* fname = ns_prefix.empty() ?
					itf->first : CSTRING(ns_prefix + *itf->first);

				loadFunction(scope, env, fname, itf->second);
				++itf;
			}
		}
	}

	if (kind & ModManager::TYPE) {
		TypeMap& types = module->getTypes();

		if (name) {
			TypeMap::const_iterator it = types.find(*name);

			if (it == types.end()) {
				std::cerr << "Type `" << *name << "' not found!" << std::endl;
			} else {
				loadType(scope, env, it->first, it->second);
			}
		} else {
			TypeMap::const_iterator itt(types.begin()), ite(types.end());

			while (EXPECTED(itt != ite)) {
				const std::string& tname = ns_prefix.empty() ?
					itt->first : ns_prefix + itt->first;

				loadType(scope, env, tname, itt->second);
				++itt;
			}
		}
	}
}

/// Loads a module if it is not already loaded
void ModManager::loadModule(Scope* scope, Environment* env, Module* module,
	size_t kind, const CString* name) const
{
	// Imports the submodule
	// e.g. import std;   => std:<submodule>:<name>
	// e.g. import std.*; => <submodule>:<name>
	if ((kind & ModManager::ALL)
		&& module->hasModules()) {
		ModuleMap& mods = module->getModules();
		ModuleMap::const_iterator it = mods.begin(), end = mods.end();

		while (it != end) {
			if (it->second->isLoaded()) {
				++it;
				continue;
			}
			it->second->init();
			it->second->setLoaded();

			std::string prefix = it->second->getName() + ":";

			if (kind & ModManager::NAMESPACE) {
				std::replace(prefix.begin(), prefix.end(), '.', ':');
			} else {
				prefix = prefix.substr(prefix.find_last_of(".")+1);
			}

			loadModuleContent(scope, env, it->second, kind, NULL,  prefix);
			++it;
		}
	}

	if (module->isLoaded()) {
		return;
	}

	module->init();
	module->setLoaded();

	std::string ns_prefix = "";

	if (kind & ModManager::NAMESPACE) {
		ns_prefix = module->getName();

		size_t found = ns_prefix.find_last_of(".");

		if (found != std::string::npos) {
			ns_prefix = ns_prefix.substr(ns_prefix.find_last_of(".")+1) + ":";
		}
	}

	loadModuleContent(scope, env, module, kind, name, ns_prefix);
}

/// Imports an userland module
ast::Node* ModManager::importFile(Scope* scope, Environment* env,
	const std::string& module, size_t kind, const CString* name) const
{
	std::string mod_name = module;
	std::string ns_name  = kind & ModManager::NAMESPACE ? module : "";

	std::replace(mod_name.begin(), mod_name.end(), '.', '/');

	const std::string& fname = m_include_path + mod_name + ".clv";

	if (!m_driver->loadFile(fname, ns_name)) {
		return m_driver->getCompiler().getAST();
	}

	return NULL;
}

/// Imports a module
ast::Node* ModManager::importModule(Scope* scope, Environment* env,
	const std::string& module, size_t kind, const CString* name) const
{
	ModuleMap::const_iterator it = m_mods.find(module);

	//std::cout << "imp " << module << std::endl;

	if (it == m_mods.end()) {
		ast::Node* tree;

		if ((tree = importFile(scope, env, module, kind, name)) == NULL) {
			std::cerr << "Module `" << module << "' not found!" << std::endl;
			return NULL;
		}
		return tree;
	}

	loadModule(scope, env, it->second, kind, name);

	return NULL;
}

} // clever
