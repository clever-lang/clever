/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/value.h"
#include "core/type.h"
#include "modules/std/concurrent/sync.h"
#include "modules/std/core/function.h"

#ifndef CLEVER_THREADS_BEBUG
#undef clever_debug
#define clever_debug(...)
#endif

namespace clever { namespace modules { namespace std {

TypeObject* Sync::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	SyncObject* mobj = new SyncObject(args->at(0)->getInt());
	return mobj;
}

CLEVER_METHOD(Sync::status)
{
	if (!clever_check_no_args()) {
		return;
	}
	SyncObject* sync = CLEVER_GET_OBJECT(SyncObject*, CLEVER_THIS());

	result->setBool(sync->status());
}

CLEVER_METHOD(Sync::getID)
{
	if (!clever_check_no_args()) {
		return;
	}
	SyncObject* sync = CLEVER_GET_OBJECT(SyncObject*, CLEVER_THIS());

	result->setInt(sync->getID());
}

CLEVER_METHOD(Sync::getNIDs)
{
	if (!clever_check_no_args()) {
		return;
	}
	SyncObject* sync = CLEVER_GET_OBJECT(SyncObject*, CLEVER_THIS());

	result->setInt(sync->getNIDs());
}

CLEVER_METHOD(Sync::setStatus)
{
	if (!clever_check_args("b")) {
		return;
	}
	SyncObject* sync = CLEVER_GET_OBJECT(SyncObject*, CLEVER_THIS());
	Value* v = args.at(0);
	sync->setStatus(v->getBool());
}

CLEVER_METHOD(Sync::nextID)
{
	if (!clever_check_no_args()) {
		return;
	}
	SyncObject* sync = CLEVER_GET_OBJECT(SyncObject*, CLEVER_THIS());
	result->setInt(sync->nextID());
}

CLEVER_METHOD(Sync::setID)
{
	if (!clever_check_args("i")) {
		return;
	}
	SyncObject* sync = CLEVER_GET_OBJECT(SyncObject*, CLEVER_THIS());
	sync->setID(args.at(0)->getInt());
}


CLEVER_METHOD(Sync::ctor)
{
	if (!clever_check_args("i")) {
		return;
	}
	result->setObj(this, allocData(&args));
}

CLEVER_TYPE_INIT(Sync::init)
{

	setConstructor((MethodPtr) &Sync::ctor);

	addMethod(new Function("getID",      (MethodPtr) &Sync::getID));
	addMethod(new Function("getNIDs",    (MethodPtr) &Sync::getNIDs));
	addMethod(new Function("nextID",     (MethodPtr) &Sync::nextID));
	addMethod(new Function("setID",      (MethodPtr) &Sync::setID));
	addMethod(new Function("status",     (MethodPtr) &Sync::status));
	addMethod(new Function("setStatus",  (MethodPtr) &Sync::setStatus));
}

}}} // clever::modules::std
