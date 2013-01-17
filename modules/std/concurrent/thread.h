/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CONCURRENT_THREAD_H
#define CLEVER_STD_CONCURRENT_THREAD_H

#include <iostream>

#include "core/cstring.h"
#include "types/type.h"

namespace clever { namespace packages { namespace std {

class Thread : public Type {
public:
	Thread()
		: Type(CSTRING("Thread")) {}

	~Thread() {}

	void dump(const void* data) const;
	void dump(const void* data, ::std::ostream& out) const;

	virtual void increment(Value*) const {}
	virtual void decrement(Value*) const {}

	void init();

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);
	
	CLEVER_METHOD(ctor);

	CLEVER_METHOD(start);
};

}}} // clever::packages::std

#endif // CLEVER_STD_CONCURRENT_THREAD_H
