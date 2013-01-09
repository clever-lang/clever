
#ifndef CLEVER_STD_REFLECTION_FUNCTION_H
#define CLEVER_STD_REFLECTION_FUNCTION_H

#include <iostream>
#include "core/cstring.h"
#include "types/type.h"

namespace clever { namespace packages { namespace std {

class ReflectionFunction : public Type {
public:
	ReflectionFunction()
		: Type(CSTRING("ReflectionFunction")) {}

	~ReflectionFunction() {}

	virtual void dump(const void*) const {}
	virtual void dump(const void*, ::std::ostream& out) const {}

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const { return NULL; }
	virtual void deallocData(void* data) {}
};

}}} // clever::packages::std

#endif // CLEVER_STD_REFLECTION_FUNCTION_H
