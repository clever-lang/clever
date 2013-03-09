/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/value.h"
#include "core/cexception.h"
#include "modules/std/core/function.h"
#include "modules/std/regex/pcre.h"

namespace clever { namespace modules { namespace std { namespace regex {

// Regex.Regex(String pattern [, Int flags])
CLEVER_METHOD(Pcre::constructor)
{
	if (!clever_check_args("s|i")) {
		return;
	}

	PcreObject* reobj = static_cast<PcreObject*>(allocData(&args));

	const ::std::string pattern = "(" + *args.at(0)->getStr() + ")";

	if (args.size() == 2) {
		reobj->re = new pcrecpp::RE(pattern.c_str(),
			pcrecpp::RE_Options(args.at(1)->getInt()));
	} else {
		reobj->re = new pcrecpp::RE(pattern.c_str());
	}

	const ::std::string& errormsg = reobj->re->error();

	if (!errormsg.empty()) {
		clever_throw(errormsg.c_str());
		delete reobj;
		return;
	}

	result->setObj(this, reobj);
}

// Bool Regex::test(String haystack)
CLEVER_METHOD(Pcre::test)
{
	if (!clever_check_args("s")) {
		return;
	}

	PcreObject* reobj = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());

	result->setBool(reobj->re->PartialMatch(args.at(0)->getStr()->c_str()));
}

// Bool Regex::match(String haystack)
CLEVER_METHOD(Pcre::match)
{
	if (!clever_check_args("s")) {
		return;
	}

	PcreObject* reobj = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());
	const CString* haystack = args.at(0)->getStr();
	int ngroups;

	if (reobj->match.last_input != haystack) {
		ngroups = reobj->re->NumberOfCapturingGroups();

		reobj->match.groups     = NULL;
		reobj->match.input      = haystack->c_str();
		reobj->match.last_input = haystack;
		reobj->match.n_groups   = ngroups;

		if (ngroups != 0) {
			reobj->match.matches = new ::std::string[ngroups];
			reobj->match.groups  = new pcrecpp::Arg*[ngroups];

			for (int i = 0; i < ngroups; ++i) {
				reobj->match.groups[i]  = new pcrecpp::Arg;
				*reobj->match.groups[i] = &reobj->match.matches[i];
			}
		}
	} else {
		ngroups = reobj->match.n_groups;
	}

	int consumed;
	bool res = reobj->re->DoMatch(reobj->match.input, pcrecpp::RE::UNANCHORED,
		&consumed, reobj->match.groups, ngroups);

	if (res) {
		reobj->match.input.remove_prefix(consumed);
	}

	result->setBool(res);
}

// String Pcre::group(Int group)
CLEVER_METHOD(Pcre::group)
{
	if (!clever_check_args("i")) {
		return;
	}

	const PcreObject* reobj = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());

	if (args.at(0)->getInt() >= reobj->match.n_groups) {
		result->setStr(CSTRING(""));
	} else {
		result->setStr(new StrObject(reobj->match.matches[args.at(0)->getInt()]));
	}
}

// String Regex::replace(String replacement, String haystack)
CLEVER_METHOD(Pcre::replace)
{
	if (!clever_check_args("ss")) {
		return;
	}

	const PcreObject* reobj = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());

	::std::string newstr(*args[1]->getStr());

	reobj->re->Replace(args[0]->getStr()->c_str(), &newstr);

	result->setStr(new StrObject(newstr));
}

// String Regex::replaceAll(String replacement, String haystack)
CLEVER_METHOD(Pcre::replaceAll)
{
	if (!clever_check_args("ss")) {
		return;
	}

	const PcreObject* reobj = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());
	::std::string newstr(args[1]->getStr()->c_str());

	reobj->re->GlobalReplace(args[0]->getStr()->c_str(), &newstr);

	result->setStr(new StrObject(newstr));
}

// String Regex::getPattern()
CLEVER_METHOD(Pcre::getPattern)
{
	if (!clever_check_no_args()) {
		return;
	}

	const PcreObject* reobj = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());

	result->setStr(new StrObject(reobj->re->pattern()));
}

// String Regex::getError()
CLEVER_METHOD(Pcre::getError)
{
	if (!clever_check_no_args()) {
		return;
	}

	const PcreObject* reobj = CLEVER_GET_OBJECT(PcreObject*, CLEVER_THIS());

	result->setStr(new StrObject(reobj->re->error()));
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

	addMethod(new Function("test",       (MethodPtr)&Pcre::test));
	addMethod(new Function("match",      (MethodPtr)&Pcre::match));
	addMethod(new Function("group",      (MethodPtr)&Pcre::group));
	addMethod(new Function("replace",    (MethodPtr)&Pcre::replace));
	addMethod(new Function("replaceAll", (MethodPtr)&Pcre::replaceAll));
	addMethod(new Function("getPattern", (MethodPtr)&Pcre::getPattern));
	addMethod(new Function("getError",   (MethodPtr)&Pcre::getError));

	// Static methods
	addMethod(new Function("quote",      (MethodPtr)&Pcre::quote))->setStatic();

	// Constants
	addProperty("DOTALL",    new Value(long(PCRE_DOTALL),    true));
	addProperty("MULTILINE", new Value(long(PCRE_MULTILINE), true));
	addProperty("CASELESS",  new Value(long(PCRE_CASELESS),  true));
	addProperty("UTF8",      new Value(long(PCRE_UTF8),      true));
	addProperty("UNGREEDY",  new Value(long(PCRE_UNGREEDY),  true));
	addProperty("EXTENDED",  new Value(long(PCRE_EXTENDED),  true));
}

}}}} // clever::modules:std::regex
