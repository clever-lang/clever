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

// Functions to count and control thread creations
void new_thread();
void delete_thread();
size_t n_threads();
void enable_threads();
void disenable_threads();
bool thread_is_enabled();


class CMutex {
public:
	CMutex();

	~CMutex();

	void lock();
	void unlock();

private:
#ifndef CLEVER_WIN32
	pthread_mutex_t m_mut;
#else
	HANDLE m_mut;
#endif
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
	CThread() {}

	~CThread() {}

	void create(ThreadFunc, void*);

	int wait();

private:
#ifndef CLEVER_WIN32
	pthread_t t_handler;
#else
	HANDLE t_handler;
#endif
	DISALLOW_COPY_AND_ASSIGN(CThread);
};

} // clever

#endif // CLEVER_CTHREAD_H
