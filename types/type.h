/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_TYPE_H
#define CLEVER_TYPE_H

#include "core/cstring.h"

namespace clever {

class Value;

class Type {
public:
	Type(const CString* name) : m_name(name) {}
	virtual ~Type() {}

	/// Method for retrieve the type name
	const CString* getName() const { return m_name; }

	/// Virtual method for debug purpose
	virtual void dump(const void*) const = 0;

	virtual void* allocData() { return NULL; }
	virtual void deallocData(void* data) {}

	virtual void increment(Value*) const = 0;
	virtual void decrement(Value*) const = 0;
private:
	const CString* m_name;
};

}

#endif // CLEVER_TYPE_H
