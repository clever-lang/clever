/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_DATE_DATE_H
#define CLEVER_STD_DATE_DATE_H

#include "core/cstring.h"
#include "types/type.h"

namespace clever { namespace modules { namespace std {

struct DateObject : public TypeObject {
	DateObject()
		: intern(new time_t) {}

	~DateObject() {
		delete intern;
	}

	time_t* intern;
};

class Date : public Type {
public:
	Date()
		: Type("Date") {}

	~Date() {}

	void init();
	void dump(TypeObject* data, ::std::ostream& out) const;

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(format);
	CLEVER_METHOD(uformat);
	CLEVER_METHOD(getTime);
};

}}} // clever::modules::std

#endif // CLEVER_STD_DATE_DATE_H
