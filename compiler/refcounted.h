/**
 * Clever programming language
 * Copyright (c) 2011 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef CLEVER_REFCOUNTED_H
#define CLEVER_REFCOUNTED_H

#include "compiler/clever.h"

namespace clever {

class NO_INIT_VTABLE RefCounted {
public:
	RefCounted()
		: m_reference(1) {	}

	explicit RefCounted(int reference)
		: m_reference(reference) {	}

	virtual ~RefCounted() { }

	void setReference(int reference) { m_reference = reference; }

	int refCount() const throw() { return m_reference; }

	void addRef() throw() { ++m_reference; }

	void delRef() throw() {
		clever_assert(m_reference > 0, "This object has been free'd before.");
		if (--m_reference == 0) {
			delete this;
		}
	}
private:
	int m_reference;

	DISALLOW_COPY_AND_ASSIGN(RefCounted);
};

} // clever

#endif /* CLEVER_REFCOUNTED_H */
