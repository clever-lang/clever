/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/value.h"
#include "modules/std/core/function.h"
#include "modules/std/regex/pcre.h"

namespace clever { namespace modules { namespace std { namespace regex {

// Regex.Regex(String pattern)
CLEVER_METHOD(Pcre::constructor)
{
	if (!clever_check_args("s|i")) {
		return;
	}
	PcreObject* self = static_cast<PcreObject*>(allocData(&args));

	if (args.size() == 2) {
		self->re = new pcrecpp::RE(args.at(0)->getStr()->c_str(),
			pcrecpp::RE_Options(args.at(1)->getInt()));
	} else {
		self->re = new pcrecpp::RE(args.at(0)->getStr()->c_str());
	}

	result->setObj(this, self);
}

// Bool Regex::matches(String haystack)
CLEVER_METHOD(Pcre::matches)
{
	if (!clever_check_args("s")) {
		return;
	}

	PcreObject* self = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());
	const CString* haystack = args.at(0)->getStr();
	int n;

	// Check if we are testing another input, if not we just go to the next
	// matching
	if (self->match.last_input != haystack) {
		n = self->re->NumberOfCapturingGroups();

		// Non capturing subpattern uses the partial match method
		if (n == 0) {
			result->setBool(self->re->PartialMatch(haystack->c_str()));
			return;
		} else if (n > 0 && self->match.groups == NULL) {
			self->match.n_groups = n;
			self->match.matches = new ::std::string[n];
			self->match.groups = new pcrecpp::Arg*[n];
			self->match.input = haystack->c_str();
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
	bool res = self->re->DoMatch(self->match.input,
			pcrecpp::RE::UNANCHORED, &consumed, self->match.groups,	n);

	if (res) {
		self->match.input.remove_prefix(consumed);
	}

	result->setBool(res);
}

// String Pcre::group(Int group)
CLEVER_METHOD(Pcre::group)
{
	if (!clever_check_args("i")) {
		return;
	}

	PcreObject* self = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());

	if (args.at(0)->getInt() >= self->match.n_groups) {
		result->setStr(CSTRING(""));
	} else {
		result->setStr(new StrObject(self->match.matches[args.at(0)->getInt()]));
	}
}

// String Regex::replace(String replacement, String haystack)
CLEVER_METHOD(Pcre::replace)
{
	if (!clever_check_args("ss")) {
		return;
	}

	PcreObject* self = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());

	::std::string newstr(*args[1]->getStr());

	self->re->Replace(args[0]->getStr()->c_str(), &newstr);

	result->setStr(new StrObject(newstr));
}

// String Regex::replaceAll(String replacement, String haystack)
CLEVER_METHOD(Pcre::replaceAll)
{
	if (!clever_check_args("ss")) {
		return;
	}

	PcreObject* self = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());
	::std::string newstr(args[1]->getStr()->c_str());

	self->re->GlobalReplace(args[0]->getStr()->c_str(), &newstr);

	result->setStr(new StrObject(newstr));
}

// String Regex::quote(String regex)
CLEVER_METHOD(Pcre::quote)
{
	if (!clever_static_check_args("s")) {
		return;
	}
	result->setStr(new StrObject(pcrecpp::RE::QuoteMeta(args[0]->getStr()->c_str())));
}

CLEVER_TYPE_INIT(Pcre::init)
{
	// Methods
	setConstructor((MethodPtr)&Pcre::constructor);

	addMethod(new Function("matches",    (MethodPtr)&Pcre::matches));
	addMethod(new Function("group",      (MethodPtr)&Pcre::group));
	addMethod(new Function("replace",    (MethodPtr)&Pcre::replace));
	addMethod(new Function("replaceAll", (MethodPtr)&Pcre::replaceAll));

	// Static methods
	addMethod(new Function("quote",      (MethodPtr)&Pcre::quote))->setStatic();

	// Constants
	addProperty(CSTRING("DOTALL"),    new Value(long(PCRE_DOTALL),    true));
	addProperty(CSTRING("MULTILINE"), new Value(long(PCRE_MULTILINE), true));
	addProperty(CSTRING("CASELESS"),  new Value(long(PCRE_CASELESS),  true));
	addProperty(CSTRING("UTF8"),      new Value(long(PCRE_UTF8),      true));
	addProperty(CSTRING("UNGREEDY"),  new Value(long(PCRE_UNGREEDY),  true));
}

}}}} // clever::modules:std::regex
