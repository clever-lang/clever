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

/**
 * This class is used by the PQ to perform comparisons its between elements.
 */
struct ComparisonFunctor {
public:
	ComparisonFunctor(Function* function, const VM* vm)
	: m_function(function), m_vm(vm) {
		clever_addref(m_function);
	}

	ComparisonFunctor(const ComparisonFunctor& other)
	: m_function(other.m_function), m_vm(other.m_vm) {
		clever_addref(m_function);
	}

	bool operator()(Value* lhs, Value* rhs) const;

	~ComparisonFunctor() {
		clever_delref(m_function);
	}
private:
	Function* m_function;
	const VM* m_vm;
};

struct CPQObject : public TypeObject {
	typedef ::std::priority_queue<Value*, ::std::vector<Value*>,
		ComparisonFunctor> PQType;

	CPQObject(Function* func, const VM* vm)
	: m_pq(ComparisonFunctor(func, vm)) {}

	~CPQObject() {
		// TODO(muriloadriano): investigate why this causes SIGSEGV
		while (!m_pq.empty()) {
			//clever_delref(m_pq.top());
			m_pq.pop();
		}
	}

	PQType m_pq;
private:
	DISALLOW_COPY_AND_ASSIGN(CPQObject);
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
