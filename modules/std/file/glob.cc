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

#ifndef CLEVER_MSVC

#include <cstdlib>
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/std/file/glob.h"
#include "modules/std/file/globiteratorvalue.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std { namespace file {

/**
 * Glob::Glob(String pattern)
 */
CLEVER_METHOD(Glob::constructor) {
	GlobValue* gv = new GlobValue;
	glob_t globbuf;

	globbuf.gl_offs = 0;

	glob(CLEVER_ARG_STR(0).c_str(), GLOB_DOOFFS, NULL, &globbuf);

	for (size_t i = 0; i < globbuf.gl_pathc; ++i) {
		gv->paths.push_back(::strdup(globbuf.gl_pathv[i]));
	}

	if (globbuf.gl_pathc) {
		globfree(&globbuf);
	}

	CLEVER_RETURN_DATA_VALUE(gv);
}

/**
 * Glob::current()
 * Returns the current path in the internal cursor
 */
CLEVER_METHOD(Glob::current) {
	CLEVER_OBJECT_INIT(gv, GlobValue*);

	if (gv->paths.size()) {
		CLEVER_RETURN_STR(CSTRINGT(gv->paths.at(0)));
		//CLEVER_RETURN_STR(CSTRINGT(gv->globbuf.gl_pathv[0]));
	} else {
		CLEVER_RETURN_EMPTY_STR();
	}
}

/**
 * Glob::toString()
 * A representation of this class as a string
 */
CLEVER_METHOD(Glob::toString) {
	CLEVER_RETURN_STR(CSTRINGT("Glob class"));
}

void Glob::init() {
	const Type* glob = CLEVER_TYPE("Glob");

	addMethod(
		(new Method(CLEVER_CTOR_NAME, &Glob::constructor, glob))
			->addArg("pattern", CLEVER_STR)
	);

	addMethod(new Method("toString", &Glob::toString, CLEVER_STR));

	/**
	 * Iterator interface methods
	 */
	addInterface(CLEVER_TYPE("Iterator"));

	addMethod(new Method("current", &Glob::current, CLEVER_STR));
}

DataValue* Glob::allocateValue() const {
	return new GlobValue;
}

Value* Glob::getIterator() const {
	Value* it = new Value;
	it->setTypePtr(CLEVER_TYPE("GlobIterator"));
	it->setDataValue(new GlobIteratorValue);

	return it;
}

void Glob::destructor(Value* value) const {
	GlobValue* gv = CLEVER_GET_VALUE(GlobValue*, value);

	for (size_t i = 0; i < gv->paths.size(); ++i) {
		::free(gv->paths.at(i));
	}
}

}}}} // clever::packages::std::file

#endif /* CLEVER_MSVC */
