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

#include "compiler/scope.h"
#include "modules/std/regex/pcre.h"
#include "modules/std/regex/pcrevalue.h"

namespace clever { namespace packages { namespace std { namespace regex {

/**
 * Regex(String pattern)
 */
CLEVER_METHOD(Pcre::constructor) {
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
 * Bool Regex::matches(String haystack)
 */
CLEVER_METHOD(Pcre::matches) {
	PcreValue* self = CLEVER_GET_VALUE(PcreValue*, value);
	const CString* haystack = CLEVER_ARG(0)->getStringP();
	int n;

	// Check if we are testing another input, if not we just go to the next
	// matching
	if (self->match.last_input != haystack) {
		n = self->re->NumberOfCapturingGroups();

		// Non capturing subpattern uses the partial match method
		if (n == 0) {
			CLEVER_RETURN_BOOL(self->re->PartialMatch(haystack->c_str()));
			return;
		} else if (n > 0 && self->match.groups == NULL) {
			self->match.n_groups = n;
			self->match.matches = new ::std::string[n];
			self->match.groups = new pcrecpp::Arg*[n];
			self->match.input = haystack->str();
			self->match.last_input = haystack;

			for (int i = 0; i < n; ++i) {
				self->match.groups[i] = new pcrecpp::Arg;
				*self->match.groups[i] = &self->match.matches[i];
			}
		}
	} else {
		n = self->match.n_groups;
	}

	int consumed;
	bool result = self->re->DoMatch(self->match.input,
			pcrecpp::RE::UNANCHORED, &consumed, self->match.groups,	n);

	if (result) {
		self->match.input.remove_prefix(consumed);
	}

	CLEVER_RETURN_BOOL(result);
}

/**
 * String Pcre::group(Int group)
 */
CLEVER_METHOD(Pcre::group) {
	PcreValue* self = CLEVER_GET_VALUE(PcreValue*, value);

	if (CLEVER_ARG_INT(0) >= self->match.n_groups) {
		CLEVER_RETURN_EMPTY_STR();
	} else {
		CLEVER_RETURN_STR(CSTRINGT(self->match.matches[CLEVER_ARG_INT(0)]));
	}
}

/**
 * String Regex::replace(String replacement, String haystack)
 */
CLEVER_METHOD(Pcre::replace) {
	PcreValue* self = CLEVER_GET_VALUE(PcreValue*, value);
	::std::string newstr(CLEVER_ARG(1)->getStringP()->str());

	self->re->Replace(CLEVER_ARG_STR(0), &newstr);

	CLEVER_RETURN_STR(CSTRINGT(newstr));
}

/**
 * String Regex::replaceAll(String replacement, String haystack)
 */
CLEVER_METHOD(Pcre::replaceAll) {
	PcreValue* self = CLEVER_GET_VALUE(PcreValue*, value);
	::std::string newstr(CLEVER_ARG(1)->getStringP()->str());

	self->re->GlobalReplace(CLEVER_ARG_STR(0), &newstr);

	CLEVER_RETURN_STR(CSTRINGT(newstr));
}

/**
 * Void Regex::operator=(Regex regex)
 */
CLEVER_METHOD(Pcre::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

void Pcre::destructor(Value* value) const {

}

DataValue* Pcre::allocateValue() const {
	return new PcreValue();
}

void Pcre::init() {
	const Type* type = CLEVER_TYPE(REGEX_TYPE_NAME);

	// Regex(String pattern [, Int options])
	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Pcre::constructor, type))
		->addArg("pattern", CLEVER_STR)
		->addArg("options", CLEVER_INT)
		->setMinNumArgs(1)
	);

	// Bool Regex::matches(String haystack)
	addMethod(
		(new Method("matches", (MethodPtr)&Pcre::matches, CLEVER_BOOL))
		->addArg("haystack", CLEVER_STR)
	);

	// String Regex::group(Int group)
	addMethod(
		(new Method("group", (MethodPtr)&Pcre::group, CLEVER_STR))
		->addArg("group", CLEVER_INT)
	);

	// Bool Regex::replace(String replacement, String haystack)
	addMethod(
		(new Method("replace", (MethodPtr)&Pcre::replace, CLEVER_BOOL))
		->addArg("replacement", CLEVER_STR)
		->addArg("haystack", CLEVER_STR)
	);

	// Bool Regex::replaceAll(String replacement, String haystack)
	addMethod(
		(new Method("replaceAll", (MethodPtr)&Pcre::replaceAll, CLEVER_BOOL))
		->addArg("replacement", CLEVER_STR)
		->addArg("haystack", CLEVER_STR)
	);

	// Void Regex::operator= (Regex regex)
	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&Pcre::do_assign, CLEVER_VOID))
		->addArg("rvalue", type)
	);
}

}}}} // clever::packages:std::regex
