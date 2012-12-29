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
#include <vector>
#include "compiler/cstring.h"
#include "compiler/module.h"

namespace clever {

class Value;
typedef std::vector<Value*> ValuePool;

const short int PKG_INIT_FUNC  = 1 << 0;
const short int PKG_INIT_CLASS = 1 << 1;
const short int PKG_INIT_CONST = 1 << 2;
const short int PKG_INIT_ALL   = PKG_INIT_FUNC | PKG_INIT_CLASS | PKG_INIT_CONST;

#define BEGIN_DECLARE_FUNCTION() if (flags & PKG_INIT_FUNC) {
#define BEGIN_DECLARE_CLASS()    if (flags & PKG_INIT_CLASS) {
#define BEGIN_DECLARE_CONSTANT() if (flags & PKG_INIT_CONST) {
#define END_DECLARE() }

class Scope;

typedef std::tr1::unordered_map<const CString*, Package*> PackageMap;
typedef std::pair<const CString*, Package*> PackagePair;

class PkgManager {
public:
	PkgManager() {}
	~PkgManager() {}

	void init(std::vector<Value*>*, size_t*);
	void shutdown();

	void addPackage(const CString* name, Package* package) {
		m_pkgs.insert(PackagePair(name, package));
	}

	void importPackage(Scope*, const CString*);
	void importModule(Scope*, const CString*, const CString*);
private:
	PackageMap m_pkgs;
	ValuePool* m_value_pool;
	size_t* m_value_id;
};

} // clever

#endif // CLEVER_PKGMANAGER_H
