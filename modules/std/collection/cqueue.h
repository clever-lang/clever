/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_QUEUE_H
#define CLEVER_STD_QUEUE_H

#include <queue>
#include "core/type.h"

namespace clever { namespace modules { namespace std {

/*PriorityQueue*/
struct CPQValue {
	CPQValue(Value* elem, const Function* func_, const VM* vm_)
		: element(elem), comp(func_), vm(vm_) {}

	~CPQValue() {}

	Value* element;
	const Function* comp;
	const VM* vm;
};


bool operator<(const CPQValue& a, const CPQValue& b);

struct CPQObject : public TypeObject {
	CPQObject(const Function* func)
		: comp(func) {}

	~CPQObject() {
		while (!pq.empty()) {
			delete pq.top().element;
			pq.pop();
		}

	}

	::std::priority_queue<CPQValue> pq;
	const Function* comp;
};


class CPQueue : public Type {
public:
	CPQueue()
		: Type("PriorityQueue") {}

	~CPQueue() {}

	virtual void init();

	// Methods
	CLEVER_METHOD(ctor);
	CLEVER_METHOD(empty);
	CLEVER_METHOD(push);
	CLEVER_METHOD(pop);
	CLEVER_METHOD(top);

private:
	DISALLOW_COPY_AND_ASSIGN(CPQueue);
};

/* Queue */

struct CQueueObject : public TypeObject {
	CQueueObject() {}

	~CQueueObject() {
		while (!queue.empty()) {
			clever_delref(queue.front());
			queue.pop();
		}
	}

	::std::queue<Value*> queue;
};

class CQueue : public Type {
public:
	CQueue()
		: Type("Queue") {}

	~CQueue() {}

	virtual void init();

	// Methods
	CLEVER_METHOD(ctor);
	CLEVER_METHOD(empty);
	CLEVER_METHOD(size);
	CLEVER_METHOD(push);
	CLEVER_METHOD(pop);
	CLEVER_METHOD(front);
	CLEVER_METHOD(back);
private:
	DISALLOW_COPY_AND_ASSIGN(CQueue);
};

}}} // clever::modules::std

#endif // CLEVER_STD_QUEUE_H
