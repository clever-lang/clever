/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */


#include "core/vm.h"
#include "core/value.h"
#include "modules/std/core/function.h"
#include "modules/std/collection/cqueue.h"

namespace clever { namespace modules { namespace std {

// Queue.Queue()
CLEVER_METHOD(CQueue::ctor)
{
	if (!clever_check_no_args()) {
		return;
	}

	result->setObj(this, new CQueueObject);
}

// Queue.empty()
CLEVER_METHOD(CQueue::empty)
{
	if (!clever_check_no_args()) {
		return;
	}

	const CQueueObject* cobj = clever_get_this(CQueueObject*);

	result->setBool(cobj->queue.empty());
}

// Queue.size()
CLEVER_METHOD(CQueue::size)
{
	if (!clever_check_no_args()) {
		return;
	}

	const CQueueObject* cobj = clever_get_this(CQueueObject*);

	result->setInt(cobj->queue.size());
}

// Queue.push(Object element)
CLEVER_METHOD(CQueue::push)
{
	if (!clever_check_args(".")) {
		return;
	}

	CQueueObject* cobj = clever_get_this(CQueueObject*);

	cobj->queue.push(args[0]);
	clever_addref(args[0]);
}

// Queue.pop()
CLEVER_METHOD(CQueue::pop)
{
	if (!clever_check_no_args()) {
		return;
	}

	CQueueObject* cobj = clever_get_this(CQueueObject*);

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

	CQueueObject* cobj = clever_get_this(CQueueObject*);

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

	CQueueObject* cobj = clever_get_this(CQueueObject*);

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

/*PriorityQueue*/
bool operator<(const CPQValue& a, const CPQValue& b)
{
	::std::vector<Value*> args;

	args.push_back(a.element);
	args.push_back(b.element);

	Value* result = const_cast<VM*>(a.vm)->runFunction(a.comp, args);

	bool ret = result ? result->asBool() : false;

	clever_delref(result);

	return ret;
}

// PriorityQueue.PriorityQueue()
CLEVER_METHOD(CPQueue::ctor)
{
	if (!clever_check_args("f")) {
		return;
	}

	const Function* comp = static_cast<Function*>(args[0]->getObj());

	if (comp->getNumRequiredArgs() < 2) {
		clever_throw("Compare function must expect at least two arguments");
		return;
	}

	result->setObj(this,
		new CPQObject(static_cast<Function*>(args[0]->getObj())));
}

// PriorityQueue.empty()
CLEVER_METHOD(CPQueue::empty)
{
	if (!clever_check_no_args()) {
		return;
	}

	const CPQObject* cobj = clever_get_this(CPQObject*);

	result->setBool(cobj->pq.empty());
}

// PriorityQueue.push(Object element)
CLEVER_METHOD(CPQueue::push)
{
	if (!clever_check_args(".")) {
		return;
	}

	CPQObject* cobj = clever_get_this(CPQObject*);

	cobj->pq.push(CPQValue(args[0]->clone(), cobj->comp, vm));
}

// PriorityQueue.pop()
CLEVER_METHOD(CPQueue::pop)
{
	if (!clever_check_no_args()) {
		return;
	}

	CPQObject* cobj = clever_get_this(CPQObject*);

	if (!cobj->pq.empty()) {
		clever_delref(cobj->pq.top().element);
		cobj->pq.pop();
	}
}

// Priority.top()
CLEVER_METHOD(CPQueue::top)
{
	if (!clever_check_no_args()) {
		return;
	}

	CPQObject* cobj = clever_get_this(CPQObject*);

	result->setNull();

	if (!cobj->pq.empty()) {
		result->copy(cobj->pq.top().element);
	}
}


// PriorityQueue type initialization

CLEVER_TYPE_INIT(CPQueue::init)
{
	setConstructor((MethodPtr)&CPQueue::ctor);

	addMethod(new Function("empty", (MethodPtr)&CPQueue::empty));
	addMethod(new Function("push",  (MethodPtr)&CPQueue::push));
	addMethod(new Function("pop",   (MethodPtr)&CPQueue::pop));
	addMethod(new Function("top",   (MethodPtr)&CPQueue::top));
}

}}} // clever::modules::std
