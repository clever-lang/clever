/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/value.h"
#include "core/vm.h"
#include "modules/std/core/array.h"
#include "modules/std/core/function.h"

namespace clever {

void* ArrayType::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	ArrayObject* arr = new ArrayObject();
	ValueVector& vec = arr->getData();

	for (size_t i = 0, j = args->size(); i < j; ++i) {
		vec.push_back(args->at(i)->clone());
	}

	return arr;
}

void ArrayType::deallocData(void* data)
{
	ArrayObject* arr = static_cast<ArrayObject*>(data);
	ValueVector& vec = arr->getData();

	for (size_t i = 0, j = vec.size(); i < j; ++i) {
		vec[i]->delRef();
	}

	delete arr;
}

void ArrayType::dump(const void* value, std::ostream& out) const
{
	Value::DataValue* data = static_cast<Value::DataValue*>(const_cast<void*>(value));
	ValueVector& vec = (static_cast<ArrayObject*>(data->obj->getObj()))->getData();

	out << "[";

	for (size_t i = 0, j = vec.size(); i < j; ++i) {
		vec.at(i)->dump(out);
		if (i < j-1) {
			out << ", ";
		}
	}

	out << "]";
}

// Array::Array([arg, ...])
CLEVER_METHOD(ArrayType::ctor)
{
	result->setObj(this, allocData(&args));
}

// void Array::append([arg, ... ])
CLEVER_METHOD(ArrayType::append)
{
	if (args.size()) {
		ValueVector& vec = (CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS()))->getData();

		for (size_t i = 0, j = args.size(); i < j; ++i) {
			vec.push_back(args[i]->clone());
		}
	}
	result->setNull();
}

// int Array::size()
CLEVER_METHOD(ArrayType::size)
{
	if (!clever_check_no_args()) {
		return;
	}

	result->setInt((CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS()))->getData().size());
}

// mixed Array::at(int position)
CLEVER_METHOD(ArrayType::at)
{
	if (!clever_check_args("i")) {
		return;
	}

	ValueVector& arr = (CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS()))->getData();

	if (args[0]->getInt() < 0
		|| arr.size() <= size_t(args[0]->getInt())) {
		result->setNull();
		return;
	}

	result->copy(arr.at(args[0]->getInt()));
}

// void Array::reserve(int size)
CLEVER_METHOD(ArrayType::reserve)
{
	if (!clever_check_args("i")) {
		return;
	}

	ArrayObject* arr = CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS());

	result->setNull();

	if (args[0]->getInt() < 0) {
		return;
	}

	arr->getData().reserve(args[0]->getInt());
}

// Array Array::reverse()
// Returns the reverse of this array
CLEVER_METHOD(ArrayType::reverse)
{
	if (!clever_check_no_args()) {
		return;
	}

	ValueVector& vec = (CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS()))->getData();
	ValueVector::reverse_iterator it(vec.rbegin()), end(vec.rend());
	ValueVector rev;

	while (it != end){
		rev.push_back((*it));
		++it;
	}

	result->setObj(this, allocData(&rev));
}

// mixed Array.shift()
// Removes and returns the first element of the array
CLEVER_METHOD(ArrayType::shift)
{
	if (!clever_check_no_args()) {
		return;
	}

	ValueVector& vec = (CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS()))->getData();

	if (!vec.size()) {
		result->setNull();
		return;
	}

	result->copy(vec[0]);
	vec[0]->delRef();

	vec.erase(vec.begin());
}

// mixed Array.pop()
// Removes and returns the last element of the array
CLEVER_METHOD(ArrayType::pop)
{
	if (!clever_check_no_args()) {
		return;
	}

	ValueVector& vec = (CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS()))->getData();

	if (!vec.size()) {
		result->setNull();
		return;
	}

	result->copy(vec[vec.size()-1]);
	vec[vec.size()-1]->delRef();

	vec.erase(vec.end()-1);
}

// Array Array.range(int start, int end)
// Returns a range as a new array
CLEVER_METHOD(ArrayType::range)
{
	if (!clever_check_args("ii")) {
		return;
	}

	ValueVector& vec = (CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS()))->getData();

	if (vec.empty()){
		result->setNull();
		return;
	}

	ValueVector::size_type start = args[0]->getInt(),
			end = args[1]->getInt(),
			size = vec.size();

	ValueVector ran;
	bool reverse = (start > end);

	while ((reverse ? (end <= start) : (start <= end))) {
		if (start > size || end > size) {
			break;
		}

		ran.push_back(vec[start]);

		if (reverse) {
			--start;
		} else {
			++start;
		}
	}

	result->setObj(this, allocData(&ran));
}

// Array Array::each(function)
// Calls function once for each element in the array, passing the element as the only parameter to function
// The return values from function are returned in the same order as the array
CLEVER_METHOD(ArrayType::each)
{
	if (!clever_check_args("f")) {
		return;
	}

	Function* func = static_cast<Function*>(args[0]->getObj());
	ValueVector& vec = (CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS()))->getData();
	ValueVector results;

	for (size_t i = 0, j = vec.size(); i < j; ++i) {
		ValueVector tmp_args;

		tmp_args.push_back(vec[i]);

		results.push_back(const_cast<VM*>(vm)->runFunction(func, &tmp_args));
	}

	result->setObj(this, allocData(&results));

	for (size_t i = 0, j = results.size(); i < j; ++i) {
		results[i]->delRef();
	}
}

// mixed Array.erase(int position)
// Removes from this array the element at position, returning the value
CLEVER_METHOD(ArrayType::erase)
{
	if (!clever_check_args("i")) {
		return;
	}

	ValueVector& vec = (CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS()))->getData();
	size_t length = vec.size();

	if (!length) {
		return;
	}

	if (args[0]->getInt() >= 0 && size_t(args[0]->getInt()) < length) {
		result->copy(vec[args[0]->getInt()]);

		vec[args[0]->getInt()]->delRef();

		vec.erase(vec.begin()+args[0]->getInt());
	}
}

// Type initialization
CLEVER_TYPE_INIT(ArrayType::init)
{
	Function* ctor = new Function("Array", (MethodPtr) &ArrayType::ctor);

	setConstructor(ctor);

	addMethod(ctor);
	addMethod(new Function("append",  (MethodPtr) &ArrayType::append));
	addMethod(new Function("size",    (MethodPtr) &ArrayType::size));
	addMethod(new Function("at",      (MethodPtr) &ArrayType::at));
	addMethod(new Function("reserve", (MethodPtr) &ArrayType::reserve));
	addMethod(new Function("reverse", (MethodPtr) &ArrayType::reverse));
	addMethod(new Function("each",    (MethodPtr) &ArrayType::each));
	addMethod(new Function("shift",   (MethodPtr) &ArrayType::shift));
	addMethod(new Function("pop",     (MethodPtr) &ArrayType::pop));
	addMethod(new Function("range",   (MethodPtr) &ArrayType::range));
	addMethod(new Function("erase",	  (MethodPtr) &ArrayType::erase));
}

} // clever
