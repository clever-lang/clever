/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/value.h"
#include "modules/std/concurrent/mutex.h"
#include "modules/std/core/function.h"
#include "types/type.h"

namespace clever { namespace modules { namespace std {

void Mutex::dump(TypeObject* data) const
{
	dump(data, ::std::cout);
}

void Mutex::dump(TypeObject* data, ::std::ostream& out) const
{
}

TypeObject* Mutex::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	MutexObject* mobj = new MutexObject;

	if (mobj->mutex) {
		// @TODO(krakjoe) mutex attributes
		pthread_mutex_init(mobj->mutex, NULL);
	}
	return mobj;
}

void Mutex::deallocData(void* data)
{
	MutexObject* mobj = static_cast<MutexObject*>(data);

	if (mobj->mutex) {
		pthread_mutex_destroy(mobj->mutex);
		delete mobj;
	}
}

CLEVER_METHOD(Mutex::lock)
{
	MutexObject* mutex = CLEVER_GET_OBJECT(MutexObject*, CLEVER_THIS());
	if (!mutex) {
		//CLEVER_THROW(eventually);
		return;
	}

	result->setBool((
		pthread_mutex_lock(
			CLEVER_GET_OBJECT(MutexObject*, CLEVER_THIS())->mutex) == 0)
	);
}

CLEVER_METHOD(Mutex::trylock)
{
	MutexObject* mutex = CLEVER_GET_OBJECT(MutexObject*, CLEVER_THIS());
	if (!mutex) {
		//CLEVER_THROW(eventually);
		return;
	}

	result->setBool((
		pthread_mutex_trylock(
			CLEVER_GET_OBJECT(MutexObject*, CLEVER_THIS())->mutex) == 0)
	);
}

CLEVER_METHOD(Mutex::unlock)
{
	MutexObject* mutex = CLEVER_GET_OBJECT(MutexObject*, CLEVER_THIS());

	if (!mutex) {
		//CLEVER_THROW(eventually);
		return;
	}

	result->setBool((
		pthread_mutex_unlock(
			CLEVER_GET_OBJECT(MutexObject*, CLEVER_THIS())->mutex) == 0));
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
