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
#include "compiler/scope.h"
#include "modules/std/std_pkg.h"

namespace clever {

/// Adds the available packages to be imported
void PkgManager::init(ValuePool* value_pool, size_t* value_id)
{
	m_value_pool = value_pool;
	m_value_id = value_id;

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
			delete itm->second;
			++itm;
		}

		delete it->second;
		++it;
	}
}

/// Loads a module if it is not already loaded
void PkgManager::loadModule(Scope* scope, Module* module)
{
	if (module->isLoaded()) {
		return;
	}
	module->init(PKG_INIT_FUNC);

	FunctionMap& funcs = module->getFunctions();
	FunctionMap::const_iterator itf = funcs.begin(),
		endf = funcs.end();

	while (EXPECTED(itf != endf)) {
		Value* fval = new Value();

		fval->setType(CLEVER_FUNC_TYPE);
		fval->setObj(itf->second);

		scope->push(itf->first, *m_value_id);

		(*m_value_pool)[(*m_value_id)++] = fval;
		++itf;
	}
}

/// Imports a module
void PkgManager::importModule(Scope* scope, const CString* package,
	const CString* module)
{
	PackageMap::const_iterator it = m_pkgs.find(package);

	if (it == m_pkgs.end()) {
		std::cerr << "Package not found!" << std::endl;
		return;
	}

	it->second->init();

	ModuleMap& mods = it->second->getModules();
	ModuleMap::const_iterator itm = mods.find(module);

	if (itm == mods.end()) {
		std::cerr << "Module not found!" << std::endl;
		return;
	}

	loadModule(scope, itm->second);
}

/// Imports a package
void PkgManager::importPackage(Scope* scope, const CString* package)
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
		loadModule(scope, itm->second);
		++itm;
	}
}

} // clever
