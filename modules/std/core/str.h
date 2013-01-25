/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STR_H
#define CLEVER_STR_H

#include <iostream>
#include "core/cstring.h"
#include "types/type.h"

namespace clever {

class StrObject {
public:
	StrObject(const CString* str)
		: m_str(str), m_interned(true) {}

	StrObject(const CString* str, bool interned)
		: m_str(str), m_interned(interned) {}

	StrObject(const std::string& str)
		: m_str(new CString(str)), m_interned(false) {}

	~StrObject() {
		if (!m_interned) {
			delete m_str;
		}
	}

	const CString* getStr() const { return m_str; }
private:
	const CString* m_str;
	bool m_interned;

	DISALLOW_COPY_AND_ASSIGN(StrObject);
};

class StrType : public Type {
public:
	StrType()
		: Type(CSTRING("String")) {}

	~StrType() {}

	void init();

	void dump(const void*, std::ostream&) const;

	void* allocData(CLEVER_TYPE_CTOR_ARGS) const { return NULL; }
	void deallocData(CLEVER_TYPE_DTOR_ARGS) { delete static_cast<StrObject*>(data); }

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;

	void increment(Value*, const VM*, CException*) const {}

	void decrement(Value*, const VM*, CException*) const {}

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(subString);
	CLEVER_METHOD(find);
	CLEVER_METHOD(findFirst);
	CLEVER_METHOD(findLast);
	CLEVER_METHOD(size);
	CLEVER_METHOD(format);
	CLEVER_METHOD(startsWith);
	CLEVER_METHOD(endsWith);
	CLEVER_METHOD(charAt);
	CLEVER_METHOD(split);
private:
	DISALLOW_COPY_AND_ASSIGN(StrType);
};

} // clever

#endif // CLEVER_STR_H
