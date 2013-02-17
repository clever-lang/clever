/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_MODMANAGER_H
#define CLEVER_MODMANAGER_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <vector>
#include "core/module.h"
#include "core/ast.h"

namespace clever {

class Value;
class Environment;
class Driver;

/// Package manager
class ModManager {
public:
	enum ImportKind {
		NONE      = 0,
		TYPE      = 1<<0,
		FUNCTION  = 1<<1,
		ALL       = TYPE | FUNCTION,
		NAMESPACE = 1<<2
	};

	ModManager(Driver* driver)
		: m_driver(driver), m_user(NULL) {}

	~ModManager() {}

	/// Initialization routine
	void init();

	/// Shutdown routine
	void shutdown();

	void setIncludePath(const std::string& path) { m_include_path = path; }

	Module* getUserModule() const { return m_user; }

	/// Adds a new package to the map
	void addModule(const std::string&, Module*);

	/// Imports the module to the current scope
	ast::Node* importModule(Scope*, Environment*, const std::string&,
		size_t = ModManager::ALL, const CString* = NULL) const;

	ast::Node* importFile(Scope*, Environment*, const std::string&,
		size_t = ModManager::ALL, const CString* = NULL) const;

	void loadModule(Scope*, Environment*, Module*, size_t, const CString*) const;
	void loadFunction(Scope*, Environment*, const CString*, Function*) const;
	void loadType(Scope*, Environment*, const std::string&, Type*) const;
private:
	Driver* m_driver;
	ModuleMap m_mods;
	Module* m_user;
	std::string m_include_path;
};

} // clever

#endif // CLEVER_MODMANAGER_H
