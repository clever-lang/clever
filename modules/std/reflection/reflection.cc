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

// Bool isnull(Object)
// Returns a boolean indicating if the object is null
static CLEVER_FUNCTION(isnull)
{
	if (!clever_static_check_args("p")) {
		return;
	}

	result->setBool(args[0]->isNull());
}

// Bool isconst(Object)
// Returns a boolean indicating if the object is constant
static CLEVER_FUNCTION(isconst)
{
	if (!clever_static_check_args("p")) {
		return;
	}

	result->setBool(args[0]->isConst());
}

// Bool isint(Object)
// Returns a boolean indicating if the object is an integer
static CLEVER_FUNCTION(isint)
{
	if (!clever_static_check_args("p")) {
		return;
	}

	result->setBool(args[0]->isInt());
}

// Bool isdouble(Object)
// Returns a boolean indicating if the object is a double
static CLEVER_FUNCTION(isdouble)
{
	if (!clever_static_check_args("p")) {
		return;
	}

	result->setBool(args[0]->isDouble());
}

// Bool isnumber(Object)
// Returns a boolean indicating if the object is an number
static CLEVER_FUNCTION(isnumber)
{
	if (!clever_static_check_args("p")) {
		return;
	}

	result->setBool(args[0]->isInt() || args[0]->isDouble());
}

// Bool isstr(Object)
// Returns a boolean indicating if the object is an string
static CLEVER_FUNCTION(isstr)
{
	if (!clever_static_check_args("p")) {
		return;
	}

	result->setBool(args[0]->isStr());
}

// Bool isfunc(Object)
// Returns a boolean indicating if the object is a function
static CLEVER_FUNCTION(isfunc)
{
	if (!clever_static_check_args("p")) {
		return;
	}

	result->setBool(args[0]->isFunction());
}

// Bool isarray(Object)
// Returns a boolean indicating if the object is an array
static CLEVER_FUNCTION(isarray)
{
	if (!clever_static_check_args("p")) {
		return;
	}

	result->setBool(args[0]->isArray());
}

// Bool ismap(Object)
// Returns a boolean indicating if the object is a map
static CLEVER_FUNCTION(ismap)
{
	if (!clever_static_check_args("p")) {
		return;
	}

	result->setBool(args[0]->isMap());
}

// Bool isthread(Object)
// Returns a boolean indicating if the object is a thread
static CLEVER_FUNCTION(isthread)
{
	if (!clever_static_check_args("p")) {
		return;
	}

	result->setBool(args[0]->isThread());
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
	addFunction(new Function("isnull",   &CLEVER_NS_FNAME(reflection, isnull)));
	addFunction(new Function("isconst",  &CLEVER_NS_FNAME(reflection, isconst)));
	addFunction(new Function("isfunct",  &CLEVER_NS_FNAME(reflection, isfunc)));
	addFunction(new Function("isint",    &CLEVER_NS_FNAME(reflection, isint)));
	addFunction(new Function("isnumber", &CLEVER_NS_FNAME(reflection, isnumber)));
	addFunction(new Function("isstr",    &CLEVER_NS_FNAME(reflection, isstr)));
	addFunction(new Function("isdouble", &CLEVER_NS_FNAME(reflection, isdouble)));
	addFunction(new Function("isarray",  &CLEVER_NS_FNAME(reflection, isarray)));
	addFunction(new Function("ismap",    &CLEVER_NS_FNAME(reflection, ismap)));
	addFunction(new Function("isthread", &CLEVER_NS_FNAME(reflection, isthread)));
}

}}} // clever::modules::std

