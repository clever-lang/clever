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
#include "core/type.h"

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

	virtual void init();

	virtual std::string toString(TypeObject* data) const {
		return *static_cast<StrObject*>(data)->value;
	}

	virtual void CLEVER_FASTCALL add(CLEVER_TYPE_OPERATOR_ARGS)           const;
	virtual void CLEVER_FASTCALL mul(CLEVER_TYPE_OPERATOR_ARGS)           const;
	virtual void CLEVER_FASTCALL equal(CLEVER_TYPE_OPERATOR_ARGS)         const;
	virtual void CLEVER_FASTCALL not_equal(CLEVER_TYPE_OPERATOR_ARGS)     const;
	virtual void CLEVER_FASTCALL not_op(CLEVER_TYPE_UNARY_OPERATOR_ARGS)  const;
	virtual void CLEVER_FASTCALL greater(CLEVER_TYPE_OPERATOR_ARGS)       const;
	virtual void CLEVER_FASTCALL greater_equal(CLEVER_TYPE_OPERATOR_ARGS) const;
	virtual void CLEVER_FASTCALL less(CLEVER_TYPE_OPERATOR_ARGS)          const;
	virtual void CLEVER_FASTCALL less_equal(CLEVER_TYPE_OPERATOR_ARGS)    const;
	virtual Value* CLEVER_FASTCALL at_op(CLEVER_TYPE_AT_OPERATOR_ARGS)    const;

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
	CLEVER_METHOD(toString);
private:
	DISALLOW_COPY_AND_ASSIGN(StrType);
};

} // clever

#endif // CLEVER_STR_H
