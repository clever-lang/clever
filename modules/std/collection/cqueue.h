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

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

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
