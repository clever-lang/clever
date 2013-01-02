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
	Mutex(){ pthread_mutex_init(&mut, &mattr); }
	~Mutex() { pthread_mutex_destroy(&mut); }

	void lock() { pthread_mutex_lock(&mut); }

	void unlock() {	pthread_mutex_unlock(&mut); }
private:
	pthread_mutex_t mut;
	pthread_mutexattr_t mattr;
};



} // clever

#endif // CLEVER_CTHREAD_H
