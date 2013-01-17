/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include "core/pkgmanager.h"
#include "modules/std/reflection/reflection.h"
#include "modules/std/reflection/reflect.h"

namespace clever { namespace packages { namespace std {

namespace reflection {

// string type()
// Returns the type name of the supplied parameter
static CLEVER_FUNCTION(type)
{
	if (!clever_static_check_args(".")) {
		return;
	}

	const Type* type = args[0]->getType();

	result->setType(CLEVER_STR_TYPE);
	result->setStr(type ? type->getName() : CSTRING("null"));
}

} // clever::packages::std::reflection

CLEVER_MODULE_INIT(Reflection)
{
	// Types
	addType(CSTRING("Reflect"), new reflection::ReflectType);

	// Functions
	addFunction(new Function("type", &CLEVER_NS_FNAME(reflection, type)));
}

}}} // clever::packages::std

