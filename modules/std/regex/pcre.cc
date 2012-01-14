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
 *
 */

#include "modules/std/regex/pcre.h"
#include "modules/std/regex/pcrevalue.h"

namespace clever { namespace packages { namespace std { namespace regex {

void Pcre::init() {
	/* Pcre(String pattern) */
	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Pcre::constructor, CLEVER_TYPE("Pcre")))
		->addArg("pattern", CLEVER_STR)
	);
	/* Pcre.match(String haystack) */
	addMethod(
		(new Method("matches", (MethodPtr)&Pcre::matches, CLEVER_BOOL))
		->addArg("haystack", CLEVER_STR)
	);
}

void Pcre::destructor(Value* value) const {
	PcreValue* self = CLEVER_GET_VALUE(PcreValue*, value);
	delete self;
}

DataValue* Pcre::allocateValue() const {
	return new PcreValue();
}

CLEVER_TYPE_METHOD(Pcre::constructor) {
	PcreValue* self = new PcreValue();

	self->re = new pcrecpp::RE(CLEVER_ARG_STR(0).c_str());

	self->setReference(0);

	retval->setDataValue(self);
}
CLEVER_TYPE_METHOD(Pcre::matches) {
	PcreValue* self = CLEVER_GET_VALUE(PcreValue*, value);
	const CString* haystack = args->at(0)->getStringP();

	retval->setBoolean(self->re->FullMatch(haystack->c_str()));
}

}}}} // clever::packages:std::regex
