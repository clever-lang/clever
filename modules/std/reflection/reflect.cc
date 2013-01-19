/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "modules/std/core/function.h"
#include "modules/std/reflection/reflect.h"
#include "modules/std/core/array.h"

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

	result->setObj(this, allocData(&args));
}

// Reflect::getType()
// Returns the type name of the object
CLEVER_METHOD(ReflectType::getType)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	if (intern->getData()->getType()) {
		result->setStr(intern->getData()->getType()->getName());
	}
}

// Reflect::isFunction()
// Check if the object is of function type
CLEVER_METHOD(ReflectType::isFunction)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isFunction());
}

// Reflect::isBool()
// Check if the object is of bool type
CLEVER_METHOD(ReflectType::isBool)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isBool());
}

// Reflect::isString()
// Check if the object is of string type
CLEVER_METHOD(ReflectType::isString)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isStr());
}

// Reflect::isInt()
// Check if the object is of int type
CLEVER_METHOD(ReflectType::isInt)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isInt());
}

// Reflect::isDouble()
// Check if the object is of double type
CLEVER_METHOD(ReflectType::isDouble)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isDouble());
}


// Reflect::isArray()
// Check if the object is of double type
CLEVER_METHOD(ReflectType::isArray)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isArray());
}

// Reflect::isMap()
// Check if the object is of map type
CLEVER_METHOD(ReflectType::isMap)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isMap());
}

// Reflect::isThread()
// Check if the object is of thread type
CLEVER_METHOD(ReflectType::isThread)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());

	result->setBool(intern->getData()->isThread());
}

// Reflect::getName()
// Returns the name of the type or function
CLEVER_METHOD(ReflectType::getName)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());
	const Value* data = intern->getData();

	if (!data->isFunction()) {
		return;
	}

	const Function* func = static_cast<Function*>(data->getObj());

	result->setStr(CSTRING(func->getName()));
}

// Reflect::isStatic()
// Check if the object is an static function
CLEVER_METHOD(ReflectType::isStatic)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());
	const Value* data = intern->getData();

	if (!data->isFunction()) {
		return;
	}

	const Function* func = static_cast<Function*>(data->getObj());

	result->setBool(func->isStatic());
}

// Reflect::isVariadic()
// Check if the object is a variadic function
CLEVER_METHOD(ReflectType::isVariadic)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());
	const Value* data = intern->getData();

	if (!data->isFunction()) {
		return;
	}

	const Function* func = static_cast<Function*>(data->getObj());

	result->setBool(func->isVariadic());
}

// Reflect::isUserDefined()
// Check if the object is an user-defined function
CLEVER_METHOD(ReflectType::isUserDefined)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());
	const Value* data = intern->getData();

	if (!data->isFunction()) {
		return;
	}

	const Function* func = static_cast<Function*>(data->getObj());

	result->setBool(func->isUserDefined());
}

// Reflect::isInternal()
// Check if the object is an internal function
CLEVER_METHOD(ReflectType::isInternal)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());
	const Value* data = intern->getData();

	if (!data->isFunction()) {
		return;
	}

	const Function* func = static_cast<Function*>(data->getObj());

	result->setBool(func->isInternal());
}

// Reflect::getNumArgs()
// Returns the number of arguments (variadic is not in the count)
CLEVER_METHOD(ReflectType::getNumArgs)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());
	const Value* data = intern->getData();

	if (!data->isFunction()) {
		return;
	}

	const Function* func = static_cast<Function*>(data->getObj());

	result->setInt(func->getNumArgs());
}

// Reflect::getNumRegArgs()
// Returns the number of required arguments (variadic is not in the count)
CLEVER_METHOD(ReflectType::getNumReqArgs)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());
	const Value* data = intern->getData();

	if (!data->isFunction()) {
		return;
	}

	const Function* func = static_cast<Function*>(data->getObj());

	result->setInt(func->getNumRequiredArgs());
}

// Reflect::getMethods()
// Returns an array with the type methods
CLEVER_METHOD(ReflectType::getMethods)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());
	const MethodMap& methods = intern->getData()->getType()->getMethods();
	MethodMap::const_iterator it(methods.begin()), end(methods.end());

	ArrayObject* arr = new ArrayObject;

	while (it != end) {
		Value* val = new Value;
		val->setStr(CSTRING(it->second->getName()));
		arr->getData().push_back(val);
		++it;
	}

	result->setObj(CLEVER_ARRAY_TYPE, arr);
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
	addMethod(new Function("getName",       (MethodPtr) &ReflectType::getName));
	addMethod(new Function("isStatic",      (MethodPtr) &ReflectType::isStatic));
	addMethod(new Function("isVariadic",    (MethodPtr) &ReflectType::isVariadic));
	addMethod(new Function("isUserDefined", (MethodPtr) &ReflectType::isUserDefined));
	addMethod(new Function("isInternal",    (MethodPtr) &ReflectType::isInternal));
	addMethod(new Function("getNumArgs",    (MethodPtr) &ReflectType::getNumArgs));
	addMethod(new Function("getNumReqArgs", (MethodPtr) &ReflectType::getNumReqArgs));

	// Type specific methods
	addMethod(new Function("getMethods", (MethodPtr) &ReflectType::getMethods));
}

}}}} // clever::packages::std::reflection
