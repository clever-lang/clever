/*
 * Clever programming language
 * Copyright (c) 2011 Clever Team
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
 *
 * $Id$
 */

#ifndef CLEVER_PKGMANAGER_H
#define CLEVER_PKGMANAGER_H

#include <tr1/unordered_map>
#include "module.h"

namespace clever {

class CString;

typedef std::tr1::unordered_map<std::string, FunctionPtr> FunctionTable;
typedef std::tr1::unordered_map<const CString*, Package*> PackageMap;
typedef std::pair<const CString*, Package*> PackagePair;

/**
 * Package manager representation
 */
class PackageManager {
public:
	PackageManager() { }

	~PackageManager() { }

	/**
	 * Load package map
	 */
	void Init(FunctionTable*) throw();
	/**
	 * Free memory
	 */
	void shutdown() throw();
	/**
	 * Add a package to list
	 */
	void addPackage(const CString* name, Package* package) throw() {
		m_packages.insert(PackagePair(name, package));
	}
	/**
	 * Load an specific package
	 */
	void loadPackage(const CString*) throw();
	/**
	 * Load an specific package module
	 */
	void loadModule(const CString*, const CString*) throw();
	void loadModule(Module*) throw();
private:
	PackageMap m_packages;

	FunctionTable* m_ftable;

	DISALLOW_COPY_AND_ASSIGN(PackageManager);
};

} // clever

#endif // CLEVER_PKGMANAGER_H