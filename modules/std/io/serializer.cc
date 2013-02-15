#include "modules/std/core/function.h"
#include "modules/std/io/serializer.h"

namespace clever { namespace modules { namespace std {

CLEVER_METHOD(Serializer::serialize)
{
	if (!clever_static_check_args(".")) {
		return;
	}
}

CLEVER_METHOD(Serializer::unserialize)
{
	if (!clever_static_check_args(".")) {
		return;
	}
}

CLEVER_TYPE_INIT(Serializer::init)
{
	addMethod(new Function("serialize", (MethodPtr)&Serializer::serialize))
		->setStatic();

	addMethod(new Function("unserialize", (MethodPtr)&Serializer::unserialize))
		->setStatic();
}

}}} // clever::modules::std
