/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CONCURRENT_SYNC_H
#define CLEVER_STD_CONCURRENT_SYNC_H

#include <iostream>

#include "core/cstring.h"
#include "core/type.h"
#include "core/cthread.h"

namespace clever { namespace modules { namespace std {

struct SyncObject : public TypeObject {
	SyncObject(size_t n_ids)
		: mutex(), n_ids(n_ids), next_id(0), m_status(true) {}

	~SyncObject() {}

	size_t getID() {
		mutex.lock();
		size_t v = next_id;
		mutex.unlock();
		return v;
	}

	size_t nextID() {
		mutex.lock();
		size_t v = next_id;
		next_id = (next_id + 1) % n_ids;
		mutex.unlock();
		return v;
	}

	void setID(size_t v) {
		mutex.lock();
		next_id = v;
		mutex.unlock();
	}

	size_t getNIDs() {
		return n_ids;
	}

	bool status() {
		mutex.lock();
		bool v = m_status;
		mutex.unlock();
		return v;
	}

	void setStatus(bool v) {
		mutex.lock();
		m_status = v;
		mutex.unlock();
	}

	CMutex mutex;
	size_t n_ids;
	size_t next_id;
	bool m_status;
};

class Sync : public Type {
public:
	Sync()
		: Type("Sync") {}

	~Sync() {}

	virtual void init();

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(status);
	CLEVER_METHOD(nextID);
	CLEVER_METHOD(setID);
	CLEVER_METHOD(setStatus);
	CLEVER_METHOD(getID);
	CLEVER_METHOD(getNIDs);
};

}}} // clever::modules::std

#endif // CLEVER_STD_CONCURRENT_SYNC_H
