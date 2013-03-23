/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/cthread.h"

namespace clever {

CCondition::CCondition()
{
	pthread_cond_init(&condition, NULL);
}

CCondition::~CCondition()
{
	pthread_cond_destroy(&condition);
}

bool CCondition::signal()
{
	return pthread_cond_signal(&condition) == 0;
}

bool CCondition::broadcast()
{
	return pthread_cond_broadcast(&condition) == 0;
}

bool CCondition::wait(CMutex& m)
{
	return pthread_cond_wait(&condition, &m.m_mut) == 0;
}

CMutex::CMutex()
{
#ifdef CLEVER_THREADS
# ifndef CLEVER_WIN32
	pthread_mutex_init(&m_mut, NULL);
# else
	m_mut = CreateMutex(NULL, FALSE, NULL);
# endif
#endif
}

CMutex::~CMutex()
{
#ifdef CLEVER_THREADS
# ifndef CLEVER_WIN32
	pthread_mutex_destroy(&m_mut);
# else
	CloseHandle(m_mut);
# endif
#endif
}

bool CMutex::lock()
{
#ifdef CLEVER_THREADS
# ifndef CLEVER_WIN32
	return pthread_mutex_lock(&m_mut) == 0;
# else
	WaitForSingleObject(m_mut, INFINITE);
# endif
#endif
}

bool CMutex::trylock()
{
	return pthread_mutex_trylock(&m_mut) == 0;
}

bool CMutex::unlock()
{
#ifdef CLEVER_THREADS
# ifndef CLEVER_WIN32
	return pthread_mutex_unlock(&m_mut) == 0;
# else
	ReleaseMutex(m_mut);
# endif
#endif
}

void CThread::create(ThreadFunc thread_func, void* args)
{
#ifdef CLEVER_THREADS
# ifndef CLEVER_WIN32
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&t_handler, &attr, thread_func, args);

	pthread_attr_destroy(&attr);
# else
	t_handler = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_func, args, 0, NULL);
# endif
#endif
	m_is_running = true;
}

int CThread::wait()
{
#ifdef CLEVER_THREADS
	int status;

#ifndef CLEVER_WIN32
	status = pthread_join(t_handler, NULL);
#else
	status = WaitForSingleObject(t_handler, INFINITE);
	status = (status != WAIT_FAILED ? 0x0 : status);
	CloseHandle(t_handler);
#endif
	m_is_running = false;
	return status;
#else
	return 0;
#endif
}

} // clever
