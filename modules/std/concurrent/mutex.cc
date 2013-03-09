/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/value.h"
#include "core/type.h"
#include "modules/std/concurrent/mutex.h"
#include "modules/std/core/function.h"

#ifndef CLEVER_THREADS_BEBUG
#undef clever_debug
#define clever_debug(...)
#endif

namespace clever { namespace modules { namespace std {

TypeObject* Mutex::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	MutexObject* mobj = new MutexObject;

	return mobj;
}

CLEVER_METHOD(Mutex::lock)
{
	MutexObject* mutex = clever_get_this(MutexObject*);
	if (!mutex) {
		//CLEVER_THROW(eventually);
		return;
	}

	result->setBool(mutex->mutex.lock());
}

CLEVER_METHOD(Mutex::trylock)
{
	MutexObject* mutex = clever_get_this(MutexObject*);
	if (!mutex) {
		//CLEVER_THROW(eventually);
		return;
	}

	result->setBool(mutex->mutex.trylock());
}

CLEVER_METHOD(Mutex::unlock)
{
	MutexObject* mutex = clever_get_this(MutexObject*);

	if (!mutex) {
		//CLEVER_THROW(eventually);
		return;
	}

	result->setBool(mutex->mutex.unlock());
}

CLEVER_METHOD(Mutex::ctor)
{
	result->setObj(this, allocData(&args));
}

CLEVER_TYPE_INIT(Mutex::init)
{

	setConstructor((MethodPtr) &Mutex::ctor);

	addMethod(new Function("lock",    (MethodPtr) &Mutex::lock));
	addMethod(new Function("trylock", (MethodPtr) &Mutex::trylock));
	addMethod(new Function("unlock",  (MethodPtr) &Mutex::unlock));
}

}}} // clever::modules::std
