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

#include <cstdlib>
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/std/file/globvalue.h"
#include "modules/std/file/globiterator.h"
#include "modules/std/file/globiteratorvalue.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std { namespace file {

/**
 * Glob::Glob(String pattern)
 */
CLEVER_METHOD(GlobIterator::constructor) {
	GlobIteratorValue* globit = new GlobIteratorValue;

	GlobValue* glob = static_cast<GlobValue*>(CLEVER_ARG_DATA_VALUE(0));

	globit->data = &glob->paths;

	CLEVER_RETURN_DATA_VALUE(globit);
}

/**
 * GlobIterator::valid()
 */
CLEVER_METHOD(GlobIterator::valid) {
	CLEVER_OBJECT_INIT(globit, GlobIteratorValue*);

	clever_assert_not_null(globit->data);

	CLEVER_RETURN_BOOL(globit->index < globit->data->size());
}

/**
 * GlobIterator::next()
 */
CLEVER_METHOD(GlobIterator::next) {
	CLEVER_OBJECT_INIT(globit, GlobIteratorValue*);

	++globit->index;
}

/**
 * GlobIterator::next()
 */
CLEVER_METHOD(GlobIterator::get) {
	CLEVER_OBJECT_INIT(globit, GlobIteratorValue*);

	CLEVER_RETURN_STR(CSTRINGT(globit->data->at(globit->index)));
}

void GlobIterator::init() {
	const Type* glob = CLEVER_TYPE("Glob");
	const Type* globit = CLEVER_TYPE("GlobIterator");

	/**
	 * Iterator interface methods
	 */
	addInterface(CLEVER_TYPE("Iterator"));

	addMethod(
		(new Method(CLEVER_CTOR_NAME, &GlobIterator::constructor, globit))
			->addArg("instance", glob)
	);
	addMethod(new Method("valid", &GlobIterator::valid, CLEVER_BOOL));
	addMethod(new Method("next", &GlobIterator::next, CLEVER_VOID));
	addMethod(new Method("get", &GlobIterator::get, CLEVER_STR));
}

DataValue* GlobIterator::allocateValue() const {
	return NULL;
}

void GlobIterator::destructor(Value* value) const {
}

}}}} // clever::packages::std::file
