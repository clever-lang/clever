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
	Mutex() { pthread_mutex_init(&m_mut, NULL); }

	~Mutex() { pthread_mutex_destroy(&m_mut); }

	void lock() { pthread_mutex_lock(&m_mut); }

	void unlock() {	pthread_mutex_unlock(&m_mut); }
private:
	pthread_mutex_t m_mut;
};


typedef void* (*ThreadFunc)(void*);

class CThread {
public:
	CThread() {}

	void create(ThreadFunc thread_func, void* args) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

		pthread_create(&t_handler, &attr,
			thread_func, args);

		pthread_attr_destroy(&attr);
	}

	void* wait() {
		void* status;

		pthread_join(t_handler, &status);

		return status;
	}

private:
	pthread_t t_handler;
};

} // clever

#endif // CLEVER_CTHREAD_H
