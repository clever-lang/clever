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
	/* Pcre(String pattern [, Int options]) */
	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Pcre::constructor, CLEVER_TYPE("Pcre")))
		->addArg("pattern", CLEVER_STR)
		->addArg("options", CLEVER_INT)
		->setMinNumArgs(1)
	);
	/* Pcre.matches(String haystack) */
	addMethod(
		(new Method("matches", (MethodPtr)&Pcre::matches, CLEVER_BOOL))
		->addArg("haystack", CLEVER_STR)
	);
	/* Pcre.replace(String replacement, String haystack) */
	addMethod(
		(new Method("replace", (MethodPtr)&Pcre::replace, CLEVER_BOOL))
		->addArg("replacement", CLEVER_STR)
		->addArg("haystack", CLEVER_STR)
	);
	/* Pcre.replaceAll(String replacement, String haystack) */
	addMethod(
		(new Method("replaceAll", (MethodPtr)&Pcre::replaceAll, CLEVER_BOOL))
		->addArg("replacement", CLEVER_STR)
		->addArg("haystack", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&Pcre::do_assign, CLEVER_VOID))
		->addArg("rvalue", CLEVER_TYPE("Pcre"))
	);
}

void Pcre::destructor(Value* value) const {
	PcreValue* self = CLEVER_GET_VALUE(PcreValue*, value);
	delete self;
}

DataValue* Pcre::allocateValue() const {
	return new PcreValue();
}

/**
 * Pcre Pcre::constructor(String pattern)
 */
CLEVER_TYPE_METHOD(Pcre::constructor) {
	PcreValue* self = new PcreValue();

	if (CLEVER_NUM_ARGS() == 2) {
		self->re = new pcrecpp::RE(CLEVER_ARG_STR(0).c_str(),
			pcrecpp::RE_Options(CLEVER_ARG_INT(1)));
	} else {
		self->re = new pcrecpp::RE(CLEVER_ARG_STR(0).c_str());
	}

	CLEVER_RETURN_DATA_VALUE(self);
}

/**
 * Bool Pcre::matches(String haystack)
 */
CLEVER_TYPE_METHOD(Pcre::matches) {
	PcreValue* self = CLEVER_GET_VALUE(PcreValue*, value);
	const CString* haystack = CLEVER_ARG(0)->getStringP();

	CLEVER_RETURN_BOOL(self->re->PartialMatch(haystack->c_str()));
}

/**
 * String Pcre::replace(String replacement, String haystack)
 */
CLEVER_TYPE_METHOD(Pcre::replace) {
	PcreValue* self = CLEVER_GET_VALUE(PcreValue*, value);
	::std::string newstr(CLEVER_ARG(1)->getStringP()->str());

	self->re->Replace(CLEVER_ARG_STR(0), &newstr);

	CLEVER_RETURN_STR(CSTRING(newstr));
}

/**
 * String Pcre::replaceAll(String replacement, String haystack)
 */
CLEVER_TYPE_METHOD(Pcre::replaceAll) {
	PcreValue* self = CLEVER_GET_VALUE(PcreValue*, value);
	::std::string newstr(CLEVER_ARG(1)->getStringP()->str());

	self->re->GlobalReplace(CLEVER_ARG_STR(0), &newstr);

	CLEVER_RETURN_STR(CSTRING(newstr));
}

CLEVER_TYPE_METHOD(Pcre::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

}}}} // clever::packages:std::regex
