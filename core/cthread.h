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

} // clever

#endif // CLEVER_CTHREAD_H
