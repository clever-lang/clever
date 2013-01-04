#include "types/type.h"
#include "modules/std/reflection/reflectionfunction.h"

namespace clever { namespace packages { namespace std {

void* ReflectionFunction::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	return NULL;
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::add)
{
	// TODO: what we will do here?
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::sub)
{
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::mul)
{
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::div)
{
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::mod)
{
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::greater)
{
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::greater_equal)
{
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::less)
{
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::less_equal)
{
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::equal)
{
}

CLEVER_TYPE_OPERATOR(ReflectionFunction::not_equal)
{
}

}}} // clever::packages::std
