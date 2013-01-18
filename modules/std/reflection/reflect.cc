/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "modules/std/core/function.h"
#include "modules/std/reflection/reflect.h"

namespace clever { namespace packages { namespace std { namespace reflection {

void* ReflectType::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	ReflectObject* obj = new ReflectObject;

	obj->setData(args->at(0));

	return obj;
}

// Reflect::Reflect(object)
// Returns an instance of Reflect object
CLEVER_METHOD(ReflectType::ctor)
{
	if (!clever_check_args(".")) {
		return;
	}

	result->setType(this);
	result->setObj(allocData(&args));
}

// Reflect::getType()
// Returns the type name of the object
CLEVER_METHOD(ReflectType::getType)
{
	if (!clever_check_args(".")) {
		return;
	}

	const Type* type = args[0]->getType();

	result->setStr(type ? type->getName() : CSTRING("null"));
}

// Reflect::isFunction()
// Check if the object is of function type
CLEVER_METHOD(ReflectType::isFunction)
{
	if (!clever_check_no_args()) {
		return;
	}

	ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isFunction());
}

// Reflect::isBool()
// Check if the object is of bool type
CLEVER_METHOD(ReflectType::isBool)
{
	if (!clever_check_no_args()) {
		return;
	}

	ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isBool());
}

// Reflect::isString()
// Check if the object is of string type
CLEVER_METHOD(ReflectType::isString)
{
	if (!clever_check_no_args()) {
		return;
	}

	ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isString());
}

// Reflect::isInt()
// Check if the object is of int type
CLEVER_METHOD(ReflectType::isInt)
{
	if (!clever_check_no_args()) {
		return;
	}

	ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isInt());
}

// Reflect::isDouble()
// Check if the object is of double type
CLEVER_METHOD(ReflectType::isDouble)
{
	if (!clever_check_no_args()) {
		return;
	}

	ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isDouble());
}


// Reflect::isArray()
// Check if the object is of double type
CLEVER_METHOD(ReflectType::isArray)
{
	if (!clever_check_no_args()) {
		return;
	}

	ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isArray());
}

// Reflect::isMap()
// Check if the object is of map type
CLEVER_METHOD(ReflectType::isMap)
{
	if (!clever_check_no_args()) {
		return;
	}

	ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isMap());
}

// Reflect::isThread()
// Check if the object is of thread type
CLEVER_METHOD(ReflectType::isThread)
{
	if (!clever_check_no_args()) {
		return;
	}

	ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isThread());
}

// Reflect::isVariadic()
// Check if the object is a variadic function
CLEVER_METHOD(ReflectType::isVariadic)
{
	if (!clever_check_no_args()) {
		return;
	}

	ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());
	const Value* data = intern->getData();

	if (!data->isFunction()) {
		return;
	}

	const Function* func = static_cast<Function*>(data->getObj());

	result->setBool(func->isVariadic());
}

// Reflect type initialization
CLEVER_TYPE_INIT(ReflectType::init)
{
	Function* ctor = new Function("Reflect", (MethodPtr) &ReflectType::ctor);

	setConstructor(ctor);
	addMethod(ctor);
	addMethod(new Function("getType",    (MethodPtr) &ReflectType::getType));

	// Type checking
	addMethod(new Function("isFunction", (MethodPtr) &ReflectType::isFunction));
	addMethod(new Function("isBool",     (MethodPtr) &ReflectType::isBool));
	addMethod(new Function("isString",   (MethodPtr) &ReflectType::isString));
	addMethod(new Function("isInt",      (MethodPtr) &ReflectType::isInt));
	addMethod(new Function("isDouble",   (MethodPtr) &ReflectType::isDouble));
	addMethod(new Function("isArray",    (MethodPtr) &ReflectType::isArray));
	addMethod(new Function("isMap",      (MethodPtr) &ReflectType::isMap));
	addMethod(new Function("isThread",   (MethodPtr) &ReflectType::isThread));

	// Function specific methods
	addMethod(new Function("isVariadic", (MethodPtr) &ReflectType::isVariadic));
}

}}}} // clever::packages::std::reflection
