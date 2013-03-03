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
#include "core/type.h"
#include "core/cthread.h"

namespace clever { namespace modules { namespace std {

struct MutexObject : public TypeObject {
	MutexObject()
		: mutex() {}

	~MutexObject() {
	}

	CMutex mutex;
};

class Mutex : public Type {
public:
	Mutex()
		: Type("Mutex") {}

	~Mutex() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(lock);
	CLEVER_METHOD(unlock);
	CLEVER_METHOD(trylock);
};

}}} // clever::modules::std

#endif // CLEVER_STD_CONCURRENT_MUTEX_H
