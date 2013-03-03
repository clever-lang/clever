/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_CTHREAD_H
#define CLEVER_CTHREAD_H

#ifndef CLEVER_WIN32
# include <pthread.h>
#else
# include <win32/win32.h>
#endif
#include "core/clever.h"

namespace clever {

class CMutex {
public:
	CMutex();

	~CMutex();

	bool lock();
	bool unlock();
	bool trylock();


#ifndef CLEVER_WIN32
	pthread_mutex_t m_mut;
#else
	HANDLE m_mut;
#endif

private:
	DISALLOW_COPY_AND_ASSIGN(CMutex);
};

#ifndef CLEVER_WIN32
# define CLEVER_THREAD_FUNC(name) void* name(void *arg)
typedef void* (*ThreadFunc)(void*);
#else
typedef DWORD (*ThreadFunc)(LPVOID);
# define CLEVER_THREAD_FUNC(name) DWORD name(void *arg)
#endif

class CThread {
public:
	CThread()
		: m_is_running(false) {}

	~CThread() {
		if (m_is_running) {
			wait();
		}
	}

	void create(ThreadFunc, void*);

	bool isRunning() { return m_is_running; }

	int wait();

private:
	bool m_is_running;
#ifndef CLEVER_WIN32
	pthread_t t_handler;
#else
	HANDLE t_handler;
#endif
	DISALLOW_COPY_AND_ASSIGN(CThread);
};

class CCondition {
public:
	CCondition();

	~CCondition();

	bool signal();
	bool broadcast();
	bool wait(CMutex&);

private:
	pthread_cond_t condition;
};

} // clever

#endif // CLEVER_CTHREAD_H
