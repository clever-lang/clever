/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_UNICODE_STRING_H
#define CLEVER_STD_UNICODE_STRING_H

#include <iostream>
#include "core/cstring.h"
#include "types/type.h"
#include "unicode/unistr.h"
#include "unicode/ustream.h"

namespace clever { namespace packages { namespace std {

#define CLEVER_USTR_TYPE UnicodeString*
#define CLEVER_USTR_CAST(what) (CLEVER_USTR_TYPE) what
#define CLEVER_USTR_THIS() CLEVER_USTR_CAST(CLEVER_THIS()->getObj())
#define CLEVER_USTR_OBJ(from) UnicodeString(from->c_str(), from->size(), US_INV)

class UString : public Type {
public:
	UString()
		: Type(CSTRING("UString")) {}

	~UString() {}

	void dump(const void* data) const;
	void dump(const void* data, ::std::ostream& out) const;

	virtual void increment(Value*) const {}
	virtual void decrement(Value*) const {}

	void init();

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(getLength);
	CLEVER_METHOD(startsWith);
	CLEVER_METHOD(endsWith);
	CLEVER_METHOD(indexOf);
	CLEVER_METHOD(lastIndexOf);
	CLEVER_METHOD(toLower);
	CLEVER_METHOD(toUpper);
	CLEVER_METHOD(reverse);
	CLEVER_METHOD(trim);
	CLEVER_METHOD(truncate);
	CLEVER_METHOD(append);
	CLEVER_METHOD(replace);
};

}}} // clever::packages::std

#endif // CLEVER_STD_UNICODE_STRING_H
