/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_CTHREAD_H
#define CLEVER_CTHREAD_H

#include <pthread.h>

namespace clever {

class Mutex {
public:
	Mutex();

	~Mutex();

	void lock();
	void unlock();

private:
	pthread_mutex_t m_mut;
};


typedef void* (*ThreadFunc)(void*);

class CThread {
public:
	CThread() {}

	~CThread() {}

	void create(ThreadFunc thread_func, void* args);

	void* wait();

private:
	pthread_t t_handler;
};

} // clever

#endif // CLEVER_CTHREAD_H
