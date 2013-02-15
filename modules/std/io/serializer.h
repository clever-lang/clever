#ifndef CLEVER_MOD_IO_SERIALIZER
#define CLEVER_MOD_IO_SERIALIZER

#include "types/type.h"

namespace clever { namespace modules { namespace std {

struct SerializerData : public TypeObject {
	size_t size;
	void* data;
};

class Serializer : public Type {
public:
	Serializer()
		: Type("Serializer") {}

	~Serializer() {}

	void init(CLEVER_TYPE_INIT_ARGS);

	TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const {
		return new SerializerData;
	}

	void deallocData(CLEVER_TYPE_DTOR_ARGS) {
		delete static_cast<SerializerData*>(data);
	}

	CLEVER_METHOD(serialize);
	CLEVER_METHOD(unserialize);

private:
	DISALLOW_COPY_AND_ASSIGN(Serializer);
};

}}} // clever::modules::std

#endif // CLEVER_MOD_IO_SERIALIZER
