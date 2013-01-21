/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CONCURRENT_MUTEX_H
#define CLEVER_STD_CONCURRENT_MUTEX_H

#include <iostream>

#include "core/cstring.h"
#include "types/type.h"

namespace clever { namespace packages { namespace std {

class Mutex : public Type {
public:
	Mutex()
		: Type(CSTRING("Mutex")) {}

	~Mutex() {}

	void dump(const void* data) const;
	void dump(const void* data, ::std::ostream& out) const;

	virtual void increment(Value*, const VM*, CException*) const {}
	virtual void decrement(Value*, const VM*, CException*) const {}

	void init();

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);

	CLEVER_METHOD(ctor);

	CLEVER_METHOD(lock);
	CLEVER_METHOD(unlock);
	CLEVER_METHOD(trylock);
};

}}} // clever::packages::std

#endif // CLEVER_STD_CONCURRENT_MUTEX_H
