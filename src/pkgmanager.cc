#include <iostream>
#include "pkgmanager.h"
#include "cstring.h"
#include "std/package.h"

namespace clever {

void PackageManager::Init(FunctionTable* ftable) throw() {
	m_ftable = ftable;

	addPackage(CSTRING("std"), std_pkg::g_std_package);
}

void PackageManager::loadPackage(const CString* package) throw() {
	PackageMap::iterator it = m_packages.find(package);

	if (it != m_packages.end()) {
		/**
		 * Initializes the package
		 */
		it->second->Init();

		{
			ModuleMap& modules = it->second->get_modules();
			ModuleMap::iterator it = modules.begin(), end = modules.end();

			while (it != end) {
				loadModule(it->second);
				++it;
			}
		}
	} else {
		std::cerr << "package '" << *package << "' not found" << std::endl;
	}
}

void PackageManager::loadModule(Module* module) throw() {
	/**
	 * Initializes the module
	 */
	module->Init();

	{
		FunctionMap& funcs = module->get_functions();
		FunctionMap::iterator it = funcs.begin(), end = funcs.end();


		/**
		 * Inserts the function into the global function table
		 */
		while (it != end) {
			m_ftable->insert(std::pair<const std::string, FunctionPtr>(it->first, it->second));
			++it;
		}
	}
}

void PackageManager::loadModule(const CString* package, const CString* module) throw() {
	PackageMap::iterator it = m_packages.find(package);

	if (it != m_packages.end()) {
		/**
		 * Initializes the package
		 */
		it->second->Init();

		{
			ModuleMap& modules = it->second->get_modules();
			ModuleMap::iterator it_mod = modules.find(module);

			if (it_mod != modules.end()) {
				loadModule(it_mod->second);
			}
		}
	}
}

void PackageManager::shutdown() throw() {
	PackageMap::const_iterator it = m_packages.begin(), end = m_packages.end();

	while (it != end) {
		ModuleMap& modules = it->second->get_modules();
		ModuleMap::const_iterator it2 = modules.begin(), end2 = modules.end();

		while (it2 != end2) {
			delete it2->second;
			++it2;
		}
		delete it->second;
		++it;
	}
}

} // clever