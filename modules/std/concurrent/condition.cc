/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/value.h"
#include "core/type.h"
#include "modules/std/concurrent/condition.h"
#include "modules/std/concurrent/mutex.h"
#include "modules/std/core/function.h"

#ifndef CLEVER_THREADS_BEBUG
#undef clever_debug
#define clever_debug(...)
#endif

namespace clever { namespace modules { namespace std {

TypeObject* Condition::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	ConditionObject* cobj = new ConditionObject;


	return cobj;
}

// bool Condition.signal()
// Will signal to one thread waiting on this Condition
CLEVER_METHOD(Condition::signal)
{
	ConditionObject* cobj =
		clever_get_this(ConditionObject*);

	result->setBool(cobj->condition.signal());
}

// bool Condition.broadcast()
// Will broadcast to every thread waiting on this Condition
CLEVER_METHOD(Condition::broadcast)
{
	ConditionObject* cobj =
		clever_get_this(ConditionObject*);


	result->setBool(cobj->condition.broadcast());
}

// bool Condition.wait(Mutex locked)
// Will wait for another thread to signal or broadcast to this condition
// You should have the Mutex locked at time of the call
// When the call to Condition.wait returns the Mutex owner has not changed
CLEVER_METHOD(Condition::wait)
{
	ConditionObject* cobj =
		clever_get_this(ConditionObject*);


	if (!clever_check_args("*")) {
		return;
	}

	MutexObject* mobj = static_cast<MutexObject*>(args[0]->getObj());


	result->setBool(cobj->condition.wait(mobj->mutex));
}

CLEVER_METHOD(Condition::ctor)
{
	result->setObj(this, allocData(&args));
}

CLEVER_TYPE_INIT(Condition::init)
{
	setConstructor((MethodPtr) &Condition::ctor);

	addMethod(new Function("signal",    (MethodPtr)&Condition::signal));
	addMethod(new Function("broadcast", (MethodPtr)&Condition::broadcast));
	addMethod(new Function("wait",		(MethodPtr)&Condition::wait));
}

}}} // clever::modules::std
