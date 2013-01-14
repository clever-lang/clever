/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "types/type.h"
#include "types/function.h"
#include "modules/std/unicode/string.h"
#include "unicode/ustream.h"
#include "unicode/unistr.h"
#include "core/value.h"
#include "core/clever.h"

namespace clever { namespace packages { namespace std {

using namespace icu;

void UString::dump(const void* data) const
{
	dump(data, ::std::cout);
}

void UString::dump(const void* data, ::std::ostream& out) const
{
	Value::DataValue* dvalue = static_cast<Value::DataValue*>(const_cast<void*>(data));
	if (dvalue) {
		UnicodeString* uvalue = static_cast<UnicodeString*>(dvalue->obj->getObj());

		if (uvalue) {
			for(int32_t start=0; start < uvalue->length(); start++) {
				out << static_cast<char>(uvalue->char32At(start));
			}
		}
	}
}

void* UString::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	if (args->size()) {
		Value* from = args->at(0);

		if (from && from->getType() == CLEVER_STR_TYPE) {
			const CString* str = from->getStr();

			if (str) {
				return new CLEVER_USTR_OBJ(str);
			}
		}
	}
	return NULL;
}

void UString::deallocData(void *data)
{
	delete CLEVER_USTR_CAST(data);
}

// UString.getLength()
// Determine the length of this
CLEVER_METHOD(UString::getLength)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (intern) {
		CLEVER_RETURN_INT(intern->length());
	}
}

// UString.startsWith(string match, [int start, int length])
// Determine if this starts with match
CLEVER_METHOD(UString::startsWith)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (!intern) {
		return;
	}

	if (!clever_check_args("s|ii")) {
		return;
	}

	switch (args.size()) {
		case 1:
			CLEVER_RETURN_INT(intern->startsWith(
				UnicodeString(CLEVER_ARG_PSTR(0))));
			break;
		case 3:
			CLEVER_RETURN_INT(intern->startsWith(
				UnicodeString(CLEVER_ARG_PSTR(0)), CLEVER_ARG_INT(1),
					CLEVER_ARG_INT(2)));
			break;
	}
}

// UString.endsWith(string match, [int start, int length])
// Determine if this ends with match
CLEVER_METHOD(UString::endsWith)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (!intern) {
		return;
	}

	if (!clever_check_args("s|ii")) {
		return;
	}

	switch (args.size()) {
		case 1:
			CLEVER_RETURN_INT(intern->endsWith(UnicodeString(CLEVER_ARG_PSTR(0))));
			break;
		case 3:
			CLEVER_RETURN_INT(intern->endsWith(UnicodeString(CLEVER_ARG_PSTR(0)),
					CLEVER_ARG_INT(1), CLEVER_ARG_INT(2)));
			break;
	}
}

// UString.indexOf(string of, [int start, [int length]])
// Locates in this the first occurence of characters in text
CLEVER_METHOD(UString::indexOf)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (!intern) {
		return;
	}

	if (!clever_check_args("s|ii")) {
		return;
	}

	switch(args.size()) {
		case 1:
			CLEVER_RETURN_INT(intern->indexOf(UnicodeString(CLEVER_ARG_PSTR(0))));
			break;
		case 2:
			CLEVER_RETURN_INT(intern->indexOf(UnicodeString(CLEVER_ARG_PSTR(0)),
				CLEVER_ARG_INT(1)));
			break;
		case 3:
			CLEVER_RETURN_INT(intern->indexOf(UnicodeString(CLEVER_ARG_PSTR(0)),
				CLEVER_ARG_INT(1), CLEVER_ARG_INT(2)));
			break;
	}
}

// UString.lastIndexOf(string of, [int start, [int length]])
// Locates in this the last occurence of characters in text
CLEVER_METHOD(UString::lastIndexOf)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (!intern) {
		return;
	}

	if (!clever_check_args("s|ii")) {
		return;
	}

	switch (args.size()) {
		case 1:
			CLEVER_RETURN_INT(intern->lastIndexOf(UnicodeString(CLEVER_ARG_PSTR(0))));
			break;
		case 2:
			CLEVER_RETURN_INT(intern->lastIndexOf(UnicodeString(CLEVER_ARG_PSTR(0)),
				CLEVER_ARG_INT(1)));
			break;
		case 3:
			CLEVER_RETURN_INT(intern->lastIndexOf(UnicodeString(CLEVER_ARG_PSTR(0)),
				CLEVER_ARG_INT(1), CLEVER_ARG_INT(2)));
			break;
	}
}

// UString.toLower()
// Convert this into lowercase characters
CLEVER_METHOD(UString::toLower)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (intern) {
		intern->toLower();
	}
	result->setNull();
}

// UString.toUpper()
// Convert this into uppercase characters
CLEVER_METHOD(UString::toUpper)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (intern) {
		intern->toUpper();
	}
	result->setNull();
}

// UString.reverse()
// Convert this into the reverse of itself
CLEVER_METHOD(UString::reverse)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (intern) {
		intern->reverse();
	}
	result->setNull();
}

// UString.trim()
// Trim this
CLEVER_METHOD(UString::trim)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (intern) {
		intern->trim();
	}
	result->setNull();
}

// UString.truncate(int length)
// Truncates this to length, returning the new truncated length
CLEVER_METHOD(UString::truncate)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (!intern) {
		return;
	}
	if (!clever_check_args("i")) {
		return;
	}
	intern->truncate(CLEVER_ARG_INT(0));
	CLEVER_RETURN_INT(intern->length());
}

// UString.append(string next, [int start, int length])
// Appends next to this, using optional start and length of next, returning the
// length of this
CLEVER_METHOD(UString::append)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (!intern) {
		return;
	}
	if (!clever_check_args("s|ii")) {
		return;
	}

	switch(args.size()) {
		case 1:
			intern->append(UnicodeString(CLEVER_ARG_PSTR(0)));
			break;
		case 3:
			intern->append(UnicodeString(CLEVER_ARG_PSTR(0)),
				CLEVER_ARG_INT(1), CLEVER_ARG_INT(2));
			break;
	}
	CLEVER_RETURN_INT(intern->length());
}

// UString.replace(string match, string replacement)
// Replaces all occurences of match with replacement in this
CLEVER_METHOD(UString::replace)
{
	CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();

	if (!intern) {
		return;
	}
	if (!clever_check_args("ss")) {
		return;
	}
	intern->findAndReplace(UnicodeString(CLEVER_ARG_PSTR(0)),
		UnicodeString(CLEVER_ARG_PSTR(1)));
}

CLEVER_TYPE_INIT(UString::init)
{
	addMethod(new Function("getLength",		(MethodPtr) &UString::getLength));
	addMethod(new Function("startsWith",	(MethodPtr) &UString::startsWith));
	addMethod(new Function("endsWith",		(MethodPtr) &UString::endsWith));
	addMethod(new Function("indexOf",		(MethodPtr) &UString::indexOf));
	addMethod(new Function("lastIndexOf",	(MethodPtr) &UString::lastIndexOf));
	addMethod(new Function("toUpper",		(MethodPtr) &UString::toUpper));
	addMethod(new Function("toLower",		(MethodPtr) &UString::toLower));
	addMethod(new Function("reverse",		(MethodPtr) &UString::reverse));
	addMethod(new Function("trim",			(MethodPtr) &UString::trim));
	addMethod(new Function("truncate",		(MethodPtr) &UString::truncate));
	addMethod(new Function("append",		(MethodPtr) &UString::append));
	addMethod(new Function("replace",		(MethodPtr) &UString::replace));
}

}}} // clever::packages::std
