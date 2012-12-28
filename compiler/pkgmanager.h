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

#ifndef CLEVER_PKGMANAGER_H
#define CLEVER_PKGMANAGER_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include "compiler/cstring.h"
#include "compiler/module.h"

namespace clever {

class Scope;

typedef std::tr1::unordered_map<const CString*, Package*> PackageMap;
typedef std::pair<const CString*, Package*> PackagePair;

class PkgManager {
public:
	PkgManager() {}
	~PkgManager() {}

	void init();
	void shutdown();

	void addPackage(const CString* name, Package* package) {
		m_pkgs.insert(PackagePair(name, package));
	}

	void importPackage(Scope*, const CString*);
private:
	PackageMap m_pkgs;
};

} // clever

#endif // CLEVER_PKGMANAGER_H
