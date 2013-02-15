#include <vector>
#include <utility>
#include "core/cexception.h"
#include "modules/std/core/function.h"
#include "modules/std/io/serializer.h"

namespace clever { namespace modules { namespace std {

// Serializer.serialize()
CLEVER_METHOD(Serializer::serialize)
{
	if (!clever_static_check_args(".")) {
		return;
	}

	SerializerData* sobj = new SerializerData(args[0]->getData());

	sobj->info = args[0]->getType()->serialize(args[0]);

	result->setObj(this, sobj);
}

// Serializer.unserialize()
CLEVER_METHOD(Serializer::unserialize)
{
	if (!clever_static_check_args(".")) {
		return;
	}

	if (args[0]->getType() != this) {
		clever_throw("Parameter must be of SerializerData type");
		return;
	}
	SerializerData* sobj = CLEVER_GET_OBJECT(SerializerData*, args[0]);
	Value* res = args[0]->getType()->unserialize(sobj->obj->getType(), sobj->info);

	if (res) {
		result->copy(res);
		clever_delref(res);
	}
}

// Serializer type initialization
CLEVER_TYPE_INIT(Serializer::init)
{
	addMethod(new Function("serialize", (MethodPtr)&Serializer::serialize))
		->setStatic();

	addMethod(new Function("unserialize", (MethodPtr)&Serializer::unserialize))
		->setStatic();
}

}}} // clever::modules::std
