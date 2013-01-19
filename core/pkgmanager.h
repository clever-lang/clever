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

typedef std::tr1::unordered_map<const CString*, Package*> PackageMap;
typedef std::pair<const CString*, Package*> PackagePair;

/// Package manager
class PkgManager {
public:
	enum ImportKind {
		ALL,
		TYPE,
		FUNCTION
	};

	PkgManager()
		: m_pkgs() {}

	~PkgManager() {}

	/// Initialization routine
	void init();

	/// Shutdown routine
	void shutdown();

	/// Adds a new package to the map
	void addPackage(const CString* name, Package* package) {
		m_pkgs.insert(PackagePair(name, package));
	}

	/// Imports the package to the current scope
	void importPackage(Scope*, Environment*, const CString*) const;

	/// Imports the module to the current scope
	void importModule(Scope*, Environment*, const CString*, const CString*,
		ImportKind = PkgManager::ALL, const CString* = NULL) const;

	void loadModule(Scope*, Environment*, Module*, ImportKind, const CString*) const;

	void loadFunction(Scope*, Environment*, const CString*, Function*) const;

	void loadType(Scope*, Environment*, const CString*, Type*) const;
private:
	PackageMap m_pkgs;
};

} // clever

#endif // CLEVER_PKGMANAGER_H
