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

namespace clever { namespace packages { namespace std {

class UnicodeString : public Type {
public:
	UnicodeString()
		: Type(CSTRING("UnicodeString")) {}

	~UnicodeString() {}

	virtual void dump(const void*) const {}
	virtual void dump(const void*, ::std::ostream& out) const {}

	virtual void increment(Value*) const {}
	virtual void decrement(Value*) const {}

	void init();

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;
	
	CLEVER_METHOD_D(dbg);
};

}}} // clever::packages::std

#endif // CLEVER_STD_UNICODE_STRING_H
