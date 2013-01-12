/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/value.h"
#include "core/vm.h"
#include "types/array.h"
#include "types/function.h"

namespace clever {

void* ArrayType::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	ArrayObject* arr = new ArrayObject();
	std::vector<Value*>& vec = arr->getData();

	for (size_t i = 0, j = args->size(); i < j; ++i) {
		vec.push_back(args->at(i)->clone());
	}

	return arr;
}

void ArrayType::deallocData(void* data)
{
	ArrayObject* arr = static_cast<ArrayObject*>(data);
	std::vector<Value*>& vec = arr->getData();

	for (size_t i = 0, j = vec.size(); i < j; ++i) {
		vec[i]->delRef();
	}

	delete arr;
}

void ArrayType::dump(const void* value, std::ostream& out) const
{
	Value::DataValue* data = static_cast<Value::DataValue*>(const_cast<void*>(value));
	ArrayObject* arr = static_cast<ArrayObject*>(data->obj->getObj());
	std::vector<Value*>& vec = arr->getData();

	out << "[";

	for (size_t i = 0, j = vec.size(); i < j; ++i) {
		vec.at(i)->dump(out);
		if (i < j-1) {
			out << ", ";
		}
	}

	out << "]";
}

// void Array::append([arg, ... ])
CLEVER_METHOD(ArrayType::append)
{
	ArrayObject* arr = CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS());

	for (size_t i = 0, j = args.size(); i < j; ++i) {
		arr->getData().push_back(args[i]->clone());
	}
}

// int Array::size()
CLEVER_METHOD(ArrayType::size)
{
	if (!clever_check_no_args()) {
		return;
	}

	ArrayObject* arr = CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS());

	result->setInt(arr->getData().size());
}

// mixed Array::at(int position)
CLEVER_METHOD(ArrayType::at)
{
	if (!clever_check_args("i")) {
		return;
	}

	ArrayObject* arr = CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS());

	if (args[0]->getInt() < 0
		|| arr->getData().size() <= size_t(args[0]->getInt())) {
		result->setNull();
		return;
	}

	result->copy(arr->getData().at(args[0]->getInt()));
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

// void Array::each(function)
CLEVER_METHOD(ArrayType::each)
{
	if (!clever_check_args("f")) {
		return;
	}

	ArrayObject* arr = CLEVER_GET_OBJECT(ArrayObject*, CLEVER_THIS());
	Function* func = static_cast<Function*>(args[0]->getObj());
	std::vector<Value*>& vec = arr->getData();

	for (size_t i = 0, j = arr->getData().size(); i < j; ++i) {
		std::vector<Value*> tmp_args;

		tmp_args.push_back(vec[i]);

		Value* res = const_cast<VM*>(vm)->runFunction(func, &tmp_args);

		res->delRef();
	}
}

// Type initialization
CLEVER_TYPE_INIT(ArrayType::init)
{
	addMethod(CSTRING("append"),  (MethodPtr) &ArrayType::append);
	addMethod(CSTRING("size"),    (MethodPtr) &ArrayType::size);
	addMethod(CSTRING("at"),      (MethodPtr) &ArrayType::at);
	addMethod(CSTRING("reserve"), (MethodPtr) &ArrayType::reserve);
	addMethod(CSTRING("each"),    (MethodPtr) &ArrayType::each);
}

} // clever
