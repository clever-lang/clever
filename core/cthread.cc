/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/cthread.h"

namespace clever {

CMutex::CMutex()
{
#ifndef CLEVER_WIN32
	pthread_mutex_init(&m_mut, NULL);
#else
	m_mut = CreateMutex(NULL, FALSE, NULL);
#endif
}

CMutex::~CMutex()
{
#ifndef CLEVER_WIN32
	pthread_mutex_destroy(&m_mut);
#else
	CloseHandle(m_mut);
#endif
}

void CMutex::lock()
{
#ifndef CLEVER_WIN32
	pthread_mutex_lock(&m_mut);
#else
	WaitForSingleObject(m_mut, INFINITE);
#endif
}

void CMutex::unlock()
{
#ifndef CLEVER_WIN32
	pthread_mutex_unlock(&m_mut);
#else
	ReleaseMutex(m_mut);
#endif
}

void CThread::create(ThreadFunc thread_func, void* args)
{
#ifndef CLEVER_WIN32
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&t_handler, &attr, thread_func, args);

	pthread_attr_destroy(&attr);
#else
	t_handler = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_func, args, 0, NULL);
#endif
}

int CThread::wait()
{
	int status;

#ifndef CLEVER_WIN32
	status = pthread_join(t_handler, NULL);
#else
	status = WaitForSingleObject(t_handler, INFINITE);
	status = (status != WAIT_FAILED ? 0x0 : status);
	CloseHandle(t_handler);
#endif

	return status;
}


bool g_thread_is_enabled = false;
size_t g_n_threads = 0;

void new_thread()
{
	++g_n_threads;
}

void delete_thread()
{
	--g_n_threads;
}

size_t n_threads()
{
	return g_n_threads;
}

void enable_threads()
{
	g_thread_is_enabled = true;
}

void disenable_threads()
{
	g_thread_is_enabled = false;
}

bool thread_is_enabled()
{
	return g_thread_is_enabled;
}


} // clever
