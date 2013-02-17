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
#include "modules/std/core/map.h"
#include "core/vm.h"
#include "core/scope.h"

#include <string>

namespace clever { namespace modules { namespace std { namespace reflection {

// Allocates a Reflect object
TypeObject* ReflectType::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	return new ReflectObject(args->at(0));
}

void ReflectType::dump(TypeObject* data, ::std::ostream& out) const
{
	const ReflectObject* intern = static_cast<ReflectObject*>(data);

	Value* value = intern->getData();

	out << "Reflect(";
	out << value->getType()->getName();
	out << ")";
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
		result->setStr(new StrObject(intern->getData()->getType()->getName()));
	} else {
		result->setNull();
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
// Returns an array containing the type methods
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

// Reflect::getProperties()
// Returns a map containing the type properties
CLEVER_METHOD(ReflectType::getProperties)
{
	if (!clever_check_no_args()) {
		return;
	}

	const ReflectObject* intern = CLEVER_GET_OBJECT(ReflectObject*, CLEVER_THIS());
	const PropertyMap& props = intern->getData()->getType()->getProperties();
	PropertyMap::const_iterator it(props.begin()), end(props.end());

	MapObject* map = new MapObject;

	while (it != end) {
		map->getData().insert(MapObjectPair(*it->first, it->second));
		it->second->addRef();
		++it;
	}

	result->setObj(CLEVER_MAP_TYPE, map);
}

// Reflect::getInternClassSizes()
// Returns the sizes of the Intern classes
CLEVER_METHOD(ReflectType::getInternClassSizes)
{

	printf("_______________________\n");
	printf("Types\n");
	printf("-----------------------\n");

	printf("type bool : %N \n", sizeof(bool));
	printf("type char : %N \n", sizeof(char));
	printf("type size_t : %N \n", sizeof(size_t));
	printf("type int : %N \n", sizeof(int));
	printf("type long : %N \n", sizeof(long));
	printf("type float : %N \n", sizeof(float));
	printf("type double : %N \n", sizeof(double));
	printf("type pointer : %N \n", sizeof(void*));

	printf("_______________________\n");
	printf("Classes\n");
	printf("-----------------------\n");

	printf("class \"RefCounted\" : %N \n", sizeof(RefCounted));
	printf("class \"Value\" : %N \n", sizeof(Value));
	printf("class \"CMutex\" : %N \n", sizeof(CMutex));
	printf("class \"MemberMap\" : %N\n", sizeof(MemberMap));
	printf("class \"TypeFlag\" : %N\n", sizeof(TypeFlag));
	printf("class \"std::string\" : %N\n", sizeof(::std::string));
	printf("class \"Type\" : %N\n", sizeof(Type));
	printf("class \"TypeObject\" : %N\n", sizeof(TypeObject));
	printf("class \"CallStack\" : %N\n", sizeof(CallStack));
	printf("class \"std::vector<Value*>\" : %N\n", sizeof(::std::vector<Value*>));
	printf("class \"std::stack<std::pair<size_t, size_t> >\" : %N\n",
		   sizeof(::std::stack< ::std::pair<size_t, size_t> >));
	printf("class \"std::vector<Value*>\" : %N\n", sizeof(::std::vector<Value*>));
	printf("class \"std::vector<IR>\" : %N\n",
		   sizeof(::std::vector<IR>));
	printf("class \"CException\" : %N\n", sizeof(CException));
	printf("class \"VMThread\" : %N\n", sizeof(VMThread));
	//printf("class \"ValueObject\" : %N\n", sizeof(ValueObject));
	printf("class \"CThread\" : %N\n", sizeof(CThread));
	printf("class \"VM\" : %N\n", sizeof(VM));
	printf("class \"Scope::ScopeVector\" : %N\n", sizeof(Scope::ScopeVector));
}

// Reflect type initialization
CLEVER_TYPE_INIT(ReflectType::init)
{
	setConstructor((MethodPtr) &ReflectType::ctor);
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
	addMethod(new Function("getMethods",    (MethodPtr) &ReflectType::getMethods));
	addMethod(new Function("getProperties", (MethodPtr) &ReflectType::getProperties));

	addMethod(new Function("getInternClassSizes", (MethodPtr) &ReflectType::getInternClassSizes))
			->setStatic();
}

}}}} // clever::modules::std::reflection
