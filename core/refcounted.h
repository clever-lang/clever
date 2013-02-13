/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_REFCOUNTED_H
#define CLEVER_REFCOUNTED_H

#include "core/clever.h"
#include "core/cthread.h"

namespace clever {

class NO_INIT_VTABLE RefCounted {
public:
	RefCounted()
		: m_reference(1) {}

	explicit RefCounted(size_t reference)
		: m_reference(reference) {}

	virtual ~RefCounted() {}

	void setReference(size_t reference) {
#ifdef CLEVER_THREADS
		m_mutex.lock();
		m_reference = reference;
		m_mutex.unlock();
#else
		m_reference = reference;
#endif
	}

	size_t refCount() const { return m_reference; }

	void addRef() {
#if CLEVER_GCC_VERSION >= 4010 || defined(__clang__)
		__sync_add_and_fetch(&m_reference, 1);
#else
# ifdef CLEVER_THREADS
		m_mutex.lock();
		++m_reference;
		m_mutex.unlock();
# else
		++m_reference;
# endif
#endif
	}

	void delRef() {
		clever_assert(m_reference > 0, "This object has been free'd before.");
#if CLEVER_GCC_VERSION >= 4010
		if (__sync_sub_and_fetch(&m_reference, 1) == 0) {
			clever_delete(this);
		}
#else
# ifdef CLEVER_THREADS
		m_mutex.lock();
		if (--m_reference == 0) {
			m_mutex.unlock();
			clever_delete(this);
		} else {
			m_mutex.unlock();
		}
# else
		if (--m_reference == 0) {
			clever_delete(this);
		}
# endif
#endif
	}
private:
	size_t m_reference;
#ifdef CLEVER_THREADS
	CMutex m_mutex;
#endif
	DISALLOW_COPY_AND_ASSIGN(RefCounted);
};

/**
 * @brief safely increases the reference count on ptr
 * @param ptr a RefCounted instance
 */
inline void clever_addref(RefCounted* ptr) {
	if (ptr) {
		ptr->addRef();
	}
}

/**
 * @brief safely decreases the reference count on ptr.
 * @param ptr a RefCounted instance
 */
inline void clever_delref(RefCounted* ptr) {
	if (ptr) {
		ptr->delRef();
	}
}

/**
 * @brief safely decreases the reference count on ptr and sets it to NULL.
 * @param ptr a RefCounted instance
 */
inline void clever_delref_var(RefCounted*& ptr) {
	if (ptr) {
		bool set_null = ptr->refCount() == 1;
		ptr->delRef();

		if (set_null) {
			ptr = NULL;
		}
	}
}

} // clever

#endif /* CLEVER_REFCOUNTED_H */
