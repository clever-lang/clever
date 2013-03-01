/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_MOD_IO_SERIALIZER
#define CLEVER_MOD_IO_SERIALIZER

#include "core/type.h"

namespace clever { namespace modules { namespace std {

struct SerializerData : public TypeObject {
	SerializerData(const Type* type_)
		: type(type_) {}

	~SerializerData() {
		if (info.second) {
			clever_delref(info.second);
		}
	}

	const Type* type;
	::std::pair<size_t, TypeObject*> info;
};

class Serializer : public Type {
public:
	Serializer()
		: Type("Serializer") {}

	~Serializer() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual void dump(TypeObject*, ::std::ostream&) const;
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const { return NULL; }

	CLEVER_METHOD(doSerialize);
	CLEVER_METHOD(doUnserialize);

private:
	DISALLOW_COPY_AND_ASSIGN(Serializer);
};

}}} // clever::modules::std

#endif // CLEVER_MOD_IO_SERIALIZER
