/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_PKGMANAGER_H
#define CLEVER_PKGMANAGER_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <vector>
#include "core/module.h"

namespace clever {

class Value;
class Environment;

/// Package manager
class PkgManager {
public:
	enum ImportKind {
		TYPE     = 1<<0,
		FUNCTION = 1<<1,
		ALL      = TYPE | FUNCTION
	};

	PkgManager()
		: m_mods(), m_user(NULL) {}

	~PkgManager() {}

	/// Initialization routine
	void init();

	/// Shutdown routine
	void shutdown();

	Module* getUserModule() const { return m_user; }

	/// Adds a new package to the map
	void addModule(const std::string&, Module*);

	/// Imports the module to the current scope
	void importModule(Scope*, Environment*, const std::string&,
		ImportKind = PkgManager::ALL, const CString* = NULL) const;

	void loadModule(Scope*, Environment*, Module*, ImportKind, const CString*) const;

	void loadFunction(Scope*, Environment*, const CString*, Function*) const;

	void loadType(Scope*, Environment*, const CString*, Type*) const;
private:
	ModuleMap m_mods;
	Module* m_user;
};

} // clever

#endif // CLEVER_PKGMANAGER_H
