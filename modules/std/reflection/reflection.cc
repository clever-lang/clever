/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include "core/driver.h"
#include "core/modmanager.h"
#include "modules/std/reflection/reflection.h"
#include "modules/std/reflection/reflect.h"

namespace clever { namespace modules { namespace std {

namespace reflection {

// type(object)
// Returns the type name of the supplied parameter
static CLEVER_FUNCTION(type)
{
	if (!clever_static_check_args(".")) {
		return;
	}

	const Type* type = args[0]->getType();

	result->setStr(new StrObject(type->getName()));
}

// refcount(object)
// Returns the number of reference for the object
static CLEVER_FUNCTION(refcount)
{
	if (!clever_static_check_args(".")) {
		return;
	}

	result->setInt(args[0]->getData()->refCount());
}

// eval(string)
// Executes the supplied string
static CLEVER_FUNCTION(eval)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	Interpreter interp(0, NULL);

	if (!interp.loadStr(*args[0]->getStr(), false)) {
		interp.execute(false);
		// @TODO(Felipe): must fix cstring freeing
		// interp.shutdown();
	}
}

// isconst(Object)
// Returns a boolean indicating if the object is constant
static CLEVER_FUNCTION(isconst)
{
	if (!clever_static_check_args(".")) {
		return;
	}

	result->setBool(args[0]->isConst());
}

} // clever::modules::std::reflection

CLEVER_MODULE_INIT(Reflection)
{
	// Types
	addType(new reflection::ReflectType);

	// Functions
	addFunction(new Function("type",     &CLEVER_NS_FNAME(reflection, type)));
	addFunction(new Function("eval",     &CLEVER_NS_FNAME(reflection, eval)));
	addFunction(new Function("refcount", &CLEVER_NS_FNAME(reflection, refcount)));
	addFunction(new Function("isconst",  &CLEVER_NS_FNAME(reflection, isconst)));
}

}}} // clever::modules::std

