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

namespace clever {

void PkgManager::init()
{
	addPackage(CSTRING("std"), new packages::Std);
}

void PkgManager::shutdown()
{
}

/// Imports a module
void PkgManager::importModule(Scope* scope, const CString* package,
	const CString* module)
{
	PackageMap::const_iterator it = m_pkgs.find(package);

	if (it == m_pkgs.end()) {
		std::cerr << "Package not found!" << std::endl;
	}

	it->second->init();

	ModuleMap& mods = it->second->getModules();
	ModuleMap::const_iterator itm = mods.begin(), endm = mods.end();

	while (itm != endm) {
		itm->second->init(0);
		++itm;
	}
}

/// Imports a package
void PkgManager::importPackage(Scope* scope, const CString* package)
{
	PackageMap::const_iterator it = m_pkgs.find(package);

	if (it == m_pkgs.end()) {
		std::cerr << "Package not found!" << std::endl;
	}

	it->second->init();
}

} // clever
