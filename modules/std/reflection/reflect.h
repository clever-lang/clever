/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_REFLECT_H
#define CLEVER_REFLECT_H

#include <ostream>
#include "types/type.h"

namespace clever { namespace packages { namespace std { namespace reflection {

class ReflectObject {
public:
	ReflectObject()
		: m_data(NULL) {}

	~ReflectObject() {}

	void setData(Value* value) { m_data = value; }

	Value* getData() const { return m_data; }
private:
	Value* m_data;
};

class ReflectType : public Type {
public:
	ReflectType()
		: Type(CSTRING("Reflect")) {}

	~ReflectType() {}

	void init(CLEVER_TYPE_INIT_ARGS);

	virtual void dump(const void*) const {}
	virtual void dump(const void*, ::std::ostream& out) const {}

	void* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	void deallocData(CLEVER_TYPE_DTOR_ARGS) {
		delete static_cast<ReflectObject*>(data);
	}

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(getType);

	CLEVER_METHOD(isFunction);
	CLEVER_METHOD(isInt);
	CLEVER_METHOD(isDouble);
	CLEVER_METHOD(isString);
	CLEVER_METHOD(isBool);
	CLEVER_METHOD(isMap);
	CLEVER_METHOD(isArray);
	CLEVER_METHOD(isThread);

	CLEVER_METHOD(isVariadic);
	CLEVER_METHOD(getNumArgs);
	CLEVER_METHOD(getNumReqArgs);
};

}}}} // clever

#endif // CLEVER_REFLECT_H
