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

#include <iostream>
#include "compiler/pkgmanager.h"
#include "compiler/value.h"
#include "compiler/cstring.h"
#include "modules/std/std_pkg.h"
#include "modules/web/web_pkg.h"

namespace clever {

/**
 * Loads native packages
 */
void PackageManager::init() {
	addPackage(CSTRING("std"), new packages::Std());
	addPackage(CSTRING("web"), new packages::Web());
}

/**
 * Load an entire package
 */
void PackageManager::loadPackage(Scope* scope, const CString* const package) {
	PackageMap::const_iterator it = m_packages.find(package);

	if (it == m_packages.end()) {
		std::cerr << "package '" << *package << "' not found" << std::endl;
		return;
	}

	/**
	 * Check if the package already has been loaded
	 */
	if (it->second->isLoaded()) {
		return;
	}
	/**
	 * Initializes the package
	 */
	it->second->init();

	ModuleMap& modules = it->second->getModules();
	ModuleMap::const_iterator mit = modules.begin(), end = modules.end();

	while (mit != end) {
		loadModule(scope, package, mit->second, NULL);
		++mit;
	}
	/**
	 * Sets the package state to fully loaded
	 */
	it->second->setFullyLoaded();
}

static void _load_module_functions(const CString* alias, Scope* scope,
	Module* module, const CString* obj) {

	FunctionMap& funcs = module->getFunctions();

	/**
	 * Finds an specific module function
	 */
	if (obj) {
		FunctionMap::const_iterator it = funcs.find(obj->str());

		if (it == funcs.end()) {
			std::cerr << "function '" << obj->str() << "' not found" << std::endl;
			return;
		}
		CallableValue* fvalue = new CallableValue(CSTRING(it->first));

		fvalue->setHandler(it->second);

		scope->pushValue(alias ? alias : fvalue->getName(), fvalue);
		return;
	}

	const std::string prefix = alias ? alias->str() + "::" : "";
	FunctionMap::const_iterator it = funcs.begin(), end = funcs.end();

	/**
	 * Inserts the function into the symbol table
	 */
	while (it != end) {
		CallableValue* fvalue = new CallableValue(CSTRING(it->first));

		fvalue->setHandler(it->second);

		scope->pushValue(CSTRING(prefix + *fvalue->getName()), fvalue);
		++it;
	}
}

/**
 * Loads the module classes
 */
static void _load_module_classes(const CString* alias, Scope* scope,
	Module* module, const CString* obj) {

	ClassMap& classes = module->getClassTable();

	if (obj) {
		ClassMap::const_iterator it = classes.find(obj);

		if (it == classes.end()) {
			std::cerr << "class '" << obj->str() << "' not found" << std::endl;
			return;
		}

		g_scope.pushType(alias ? alias : CSTRING(*it->first), it->second);
		it->second->addRef();
		it->second->init();
		return;
	}

	ClassMap::iterator itc = classes.begin(), endc = classes.end();

	const std::string prefix = alias ? alias->str() + "::" : "";

	/**
	 * Inserts all classes into the symbol table
	 */
	while (itc != endc) {
		g_scope.pushType(CSTRING(prefix + *itc->first), itc->second);
		itc->second->addRef();
		itc->second->init();
		++itc;
	}
}

/**
 * Loads the module constants
 */
static void _load_module_constants(const CString* alias, Scope* scope,
	Module* module, const CString* obj) {

	ConstMap& constants = module->getConstants();
	ConstMap::iterator itcs = constants.begin(), endcs = constants.end();

	const std::string prefix = alias ? alias->str() + "::" : "";

	/**
	 * Inserts all constants into the symbol table
	 */
	while (itcs != endcs) {
		g_scope.pushValue(CSTRING(prefix + itcs->first->str()), itcs->second);
		++itcs;
	}
}

/**
 * Imports an specific object to the scope
 */
void PackageManager::loadObject(Scope* scope, const CString* const package,
	const CString* const module, const CString* const obj,
	const CString* const alias, bool is_type) {

	PackageMap::const_iterator it = m_packages.find(package);

	if (it == m_packages.end()) {
		std::cerr << "package '" << *package << "' not found" << std::endl;
		return;
	}

	/**
	 * Checks if the package is unloaded, in this case initialize it
	 */
	if (it->second->isUnloaded()) {
		it->second->init();
		it->second->setLoaded();
	}

	ModuleMap& modules = it->second->getModules();
	ModuleMap::const_iterator it_mod = modules.find(module);

	if (it_mod == modules.end()) {
		std::cerr << "module '" << *module << "' not found" << std::endl;
		return;
	}

	short int flags = is_type ? PKG_INIT_CLASS : PKG_INIT_FUNC;

	/**
	 * Checks if the module already has been loaded
	 */
	if (!it_mod->second->isLoaded(flags)) {
		it_mod->second->init(flags);
		it_mod->second->setLoaded(flags);
	}

	if (is_type) {
		_load_module_classes(alias, scope, it_mod->second, obj);
	} else {
		_load_module_functions(alias, scope, it_mod->second, obj);
	}

	/**
	 * Always initialize the constants when initializing some class/function
	 */
	if (!it_mod->second->isLoaded(PKG_INIT_CONST)) {
		it_mod->second->init(PKG_INIT_CONST);
		it_mod->second->setLoaded(PKG_INIT_CONST);

		_load_module_constants(alias, scope, it_mod->second, NULL);
	}
}

/**
 * Loads an specific module
 */
void PackageManager::loadModule(Scope* scope, const CString* const package,
	Module* const module, const CString* const alias) {
	/**
	 * Checks if the module already has been loaded
	 */
	if (!module->isLoaded(PKG_INIT_ALL)) {
		/**
		 * Initializes the module
		 */
		module->init(PKG_INIT_ALL);
		module->setLoaded(PKG_INIT_ALL);
	}

	_load_module_functions(alias, scope, module, NULL);

	_load_module_classes(alias, scope, module, NULL);

	_load_module_constants(alias, scope, module, NULL);
}

/**
 * Checks if an specific module is currently loaded
 */
bool PackageManager::checkModuleLoaded(const CString* const package,
	const CString* const module) {
	PackageMap::const_iterator it = m_packages.find(package);

	if (it == m_packages.end()) {
		return false;
	}

	if (it->second->isFullyLoaded()) {
		return true;
	}

	ModuleMap& modules = it->second->getModules();
	ModuleMap::const_iterator it_mod = modules.find(module);

	if (it_mod == modules.end()) {
		return false;
	}

	return it_mod->second->isLoaded(PKG_INIT_ALL);
}

/**
 * Get the Type pointer by its real name
 */
const Type* PackageManager::getTypeByModule(const CString* const package,
	const CString* const module, const CString* const type) {
	PackageMap::const_iterator it = m_packages.find(package);

	if (it == m_packages.end()) {
		return NULL;
	}

	ModuleMap& modules = it->second->getModules();
	ModuleMap::const_iterator it_mod = modules.find(module);

	if (it_mod == modules.end()) {
		return NULL;
	}

	ClassMap& classes = it_mod->second->getClassTable();
	ClassMap::const_iterator it_class = classes.find(type);

	if (it_class == classes.end()) {
		return NULL;
	}

	return it_class->second;
}

/**
 * Loads an specific module package by supplying the package and module names
 */
void PackageManager::loadModule(Scope* scope, const CString* const package,
	const CString* const module, const CString* const alias) {

	PackageMap::const_iterator it = m_packages.find(package);

	if (it == m_packages.end()) {
		std::cerr << "package '" << *package << "' not found" << std::endl;
		return;
	}

	/**
	 * Checks if the package is unloaded, in this case initialize it
	 */
	if (it->second->isUnloaded()) {
		it->second->init();
	}
	/**
	 * Check if the package already has been fully loaded
	 */
	if (!it->second->isFullyLoaded()) {
		ModuleMap& modules = it->second->getModules();
		ModuleMap::const_iterator it_mod = modules.find(module);

		if (it_mod == modules.end()) {
			std::cerr << "module '" << *module << "' not found" << std::endl;
			return;
		}

		/**
		 * Loads the module if it has been found
		 */
		loadModule(scope, package, it_mod->second, alias);
	}
	/**
	 * Change the package state to loaded
	 */
	it->second->setLoaded();
}

/**
 * Copy user-defined function in a scope to another supplied alias
 */
void PackageManager::copyScopeToAlias(Scope* scope, const std::string& alias) {
	SymbolMap& symbols = scope->getSymbols();
	SymbolMap::const_iterator it2(symbols.begin()), end2(symbols.end());
	std::vector<ValuePair> callables;
	std::vector<TypePair> type_alias;

	while (it2 != end2) {
		Symbol* sym = it2->second;

		if (sym->isValue()) {
			Value* val = sym->getValue();

			if (val->isCallable()) {
				CallableValue* fvalue = static_cast<CallableValue*>(val);

				if (fvalue->isNearCall()) {
					callables.push_back(ValuePair(
						CSTRING(alias + val->getName()->str()),
						fvalue));
				}
			}
		} else if (sym->isType()) {
			type_alias.push_back(TypePair(
				CSTRING(alias + sym->getSymbolName()->str()), sym->getType()));
		}
		++it2;
	}

	std::vector<ValuePair>::const_iterator it_call(callables.begin()),
		it_end(callables.end());

	while (it_call != it_end) {
		scope->pushValue(it_call->first, it_call->second);
		it_call->second->addRef();
		++it_call;
	}

	std::vector<TypePair>::const_iterator it_alias(type_alias.begin()),
		it_end2(type_alias.end());

	while (it_alias != it_end2) {
		scope->pushType(it_alias->first, it_alias->second);
		const_cast<Type*>(it_alias->second)->addRef();
		++it_alias;
	}

}

/**
 * Removes the packages and its modules
 */
void PackageManager::shutdown() {
	PackageMap::const_iterator it = m_packages.begin(), end = m_packages.end();

	while (it != end) {
		ModuleMap& modules = it->second->getModules();
		ModuleMap::const_iterator it_m(modules.begin()), end_m(modules.end());

		/**
		 * Deletes the module entries
		 */
		while (it_m != end_m) {
			delete it_m->second;
			++it_m;
		}
		/**
		 * Deletes the package
		 */
		delete it->second;
		++it;
	}
}

} // clever
