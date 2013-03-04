/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/value.h"
#include "modules/std/core/function.h"
#include "modules/std/collection/cqueue.h"

namespace clever { namespace modules { namespace std {

TypeObject* CQueue::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	return new CQueueObject;
}

// Queue.Queue()
CLEVER_METHOD(CQueue::ctor)
{
	if (!clever_check_no_args()) {
		return;
	}

	result->setObj(this, allocData(&args));
}

// Queue.empty()
CLEVER_METHOD(CQueue::empty)
{
	if (!clever_check_no_args()) {
		return;
	}

	const CQueueObject* cobj = CLEVER_GET_OBJECT(CQueueObject*, CLEVER_THIS());

	result->setBool(cobj->queue.empty());
}

// Queue.size()
CLEVER_METHOD(CQueue::size)
{
	if (!clever_check_no_args()) {
		return;
	}

	const CQueueObject* cobj = CLEVER_GET_OBJECT(CQueueObject*, CLEVER_THIS());

	result->setInt(cobj->queue.size());
}

// Queue.push(Object element)
CLEVER_METHOD(CQueue::push)
{
	if (!clever_check_args(".")) {
		return;
	}

	CQueueObject* cobj = CLEVER_GET_OBJECT(CQueueObject*, CLEVER_THIS());

	cobj->queue.push(args[0]);
	clever_addref(args[0]);
}

// Queue.pop()
CLEVER_METHOD(CQueue::pop)
{
	if (!clever_check_no_args()) {
		return;
	}

	CQueueObject* cobj = CLEVER_GET_OBJECT(CQueueObject*, CLEVER_THIS());

	if (!cobj->queue.empty()) {
		clever_delref(cobj->queue.front());
		cobj->queue.pop();
	}
}

// Queue.front()
CLEVER_METHOD(CQueue::front)
{
	if (!clever_check_no_args()) {
		return;
	}

	CQueueObject* cobj = CLEVER_GET_OBJECT(CQueueObject*, CLEVER_THIS());

	result->setNull();

	if (!cobj->queue.empty()) {
		result->copy(cobj->queue.front());
	}
}

// Queue.back()
CLEVER_METHOD(CQueue::back)
{
	if (!clever_check_no_args()) {
		return;
	}

	CQueueObject* cobj = CLEVER_GET_OBJECT(CQueueObject*, CLEVER_THIS());

	result->setNull();

	if (!cobj->queue.empty()) {
		result->copy(cobj->queue.back());
	}
}

// Queue type initialization
CLEVER_TYPE_INIT(CQueue::init)
{
	setConstructor((MethodPtr)&CQueue::ctor);

	addMethod(new Function("empty", (MethodPtr)&CQueue::empty));
	addMethod(new Function("size",  (MethodPtr)&CQueue::size));
	addMethod(new Function("push",  (MethodPtr)&CQueue::push));
	addMethod(new Function("pop",   (MethodPtr)&CQueue::pop));
	addMethod(new Function("front", (MethodPtr)&CQueue::front));
	addMethod(new Function("back",  (MethodPtr)&CQueue::back));
}

}}} // clever::modules::std
