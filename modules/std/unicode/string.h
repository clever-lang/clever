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
#include "core/type.h"
#include "unicode/unistr.h"
#include "unicode/ustream.h"

namespace clever { namespace modules { namespace std {

#define CLEVER_USTR_TYPE UStringObject*
#define CLEVER_USTR_CAST(what) (CLEVER_USTR_TYPE) what
#define CLEVER_USTR_THIS() CLEVER_USTR_CAST(CLEVER_THIS()->getObj())
#define CLEVER_USTR_OBJ(from) UStringObject(from->c_str(), from->size())

struct UStringObject : public TypeObject {
	UStringObject(const char* str, size_t size)
		: intern(new UnicodeString(str, size, US_INV)) {}

	~UStringObject() {
		delete intern;
	}

	UnicodeString* intern;
};

class UString : public Type {
public:
	UString()
		: Type("UString") {}

	~UString() {}

	void init();
	void dump(TypeObject* data, ::std::ostream& out) const;

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(size);
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

}}} // clever::modules::std

#endif // CLEVER_STD_UNICODE_STRING_H
