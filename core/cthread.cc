#include "core/cthread.h"

namespace clever {

Mutex::Mutex()
{
	pthread_mutex_init(&m_mut, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_mut);
}

void Mutex::lock()
{
	pthread_mutex_lock(&m_mut);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&m_mut);
}


CThread::CThread()
{
}

void CThread::create(ThreadFunc thread_func, void* args)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&t_handler, &attr,
		thread_func, args);

	pthread_attr_destroy(&attr);
}

void* CThread::wait()
{
	void* status;

	pthread_join(t_handler, &status);

	return status;
}

}
