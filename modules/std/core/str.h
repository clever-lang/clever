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

struct StrObject : public TypeObject {
public:
	StrObject(const CString* str)
		: value(str), interned(true) {}

	StrObject(const CString* str, bool is_interned)
		: value(str), interned(is_interned) {}

	StrObject(const std::string& str)
		: value(new CString(str)), interned(false) {}

	~StrObject() {
		if (!interned) {
			delete value;
		}
	}

	const CString* value;
	bool interned;

	DISALLOW_COPY_AND_ASSIGN(StrObject);
};

class StrType : public Type {
public:
	StrType()
		: Type("String") {}

	~StrType() {}

	void init(CLEVER_TYPE_INIT_ARGS);
	void dump(TypeObject*, std::ostream&) const;

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const { return NULL; }

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;

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
	CLEVER_METHOD(toUpper);
	CLEVER_METHOD(toLower);
	CLEVER_METHOD(replace);
private:
	DISALLOW_COPY_AND_ASSIGN(StrType);
};

} // clever

#endif // CLEVER_STR_H
