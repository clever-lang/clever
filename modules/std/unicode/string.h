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

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;

	CLEVER_METHOD_D(getLength);
	CLEVER_METHOD_D(startsWith);
	CLEVER_METHOD_D(endsWith);
	CLEVER_METHOD_D(indexOf);
	CLEVER_METHOD_D(lastIndexOf);
	CLEVER_METHOD_D(toLower);
	CLEVER_METHOD_D(toUpper);
	CLEVER_METHOD_D(reverse);
	CLEVER_METHOD_D(trim);
	CLEVER_METHOD_D(truncate);
};

}}} // clever::packages::std

#endif // CLEVER_STD_UNICODE_STRING_H
