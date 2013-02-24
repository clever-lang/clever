#include <ostream>
#include <vector>
#include <utility>
#include "core/cexception.h"
#include "modules/std/core/function.h"
#include "modules/std/io/serializer.h"

namespace clever { namespace modules { namespace std {

void Serializer::dump(TypeObject* obj, ::std::ostream& out) const
{
	SerializerData* sobj = static_cast<SerializerData*>(obj);

	sobj->type->dump(sobj->info.second, out);
}

// Serializer.serialize()
CLEVER_METHOD(Serializer::doSerialize)
{
	if (!clever_static_check_args(".")) {
		return;
	}

	SerializerData* sobj = new SerializerData(args[0]->getType());

	sobj->info = args[0]->getType()->serialize(args[0]);

	clever_addref(args[0]);

	result->setObj(this, sobj);
}

// Serializer.unserialize()
CLEVER_METHOD(Serializer::doUnserialize)
{
	if (!clever_static_check_args(".")) {
		return;
	}

	if (args[0]->getType() != this) {
		clever_throw("Parameter must be of SerializerData type");
		return;
	}
	SerializerData* sobj = CLEVER_GET_OBJECT(SerializerData*, args[0]);
	Value* res = unserialize(sobj->type, sobj->info);

	if (res) {
		result->copy(res);
		clever_delref(res);
	}
}

// Serializer type initialization
CLEVER_TYPE_INIT(Serializer::init)
{
	addMethod(new Function("serialize", (MethodPtr)&Serializer::doSerialize))
		->setStatic();

	addMethod(new Function("unserialize", (MethodPtr)&Serializer::doUnserialize))
		->setStatic();
}

}}} // clever::modules::std
