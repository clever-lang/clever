/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_REFCOUNTED_H
#define CLEVER_REFCOUNTED_H

#include "core/clever.h"

namespace clever {

class NO_INIT_VTABLE RefCounted {
public:
	RefCounted()
		: m_reference(1) { }

	explicit RefCounted(int reference)
		: m_reference(reference) { }

	virtual ~RefCounted() { }

	void setReference(int reference) { m_reference = reference; }

	int refCount() const { return m_reference; }

	void addRef() { ++m_reference; }

	void delRef() {
		clever_assert(m_reference > 0, "This object has been free'd before.");
		if (--m_reference == 0) {
			clever_delete(this);
		}
	}
private:
	int m_reference;

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
