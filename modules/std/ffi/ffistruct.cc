/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/value.h"
#include "modules/std/core/function.h"
#include "types/type.h"

#include "core/value.h"
#include "modules/std/ffi/ffistruct.h"

namespace clever { namespace modules { namespace std {

void FFIStructData::setStruct(ExtStructs& structs_map, const CString& struct_type)
{
	this->m_struct_type = structs_map[struct_type];

	if (this->data != 0) {
		::std::free(this->data);
	}

	size_t size = this->m_struct_type->getSize();

	this->data = malloc(size);
}

void FFIStructData::setMember(int i, const Value* const v)
{
	size_t offset = this->m_struct_type->getOffset(i - 1);
	size_t size = this->m_struct_type->getOffset(i) - offset;
	memcpy(static_cast<char*>(data) + offset, v->getData(), size);
}

void FFIStructData::setMember(const CString& member_name, const Value* const v)
{
	setMember(this->m_struct_type->getMember(member_name), v);
}


#define FFI_CONVERT(A, B) (static_cast<A*>(B))

void FFIStructData::getMember(Value* result,  int i)
{
	char type = this->m_struct_type->getType(i);
	size_t offset = this->m_struct_type->getOffset(i - 1);

	void* value = (static_cast<char*>(data) + offset);

	switch (type) {
		case 'i':
			result->setInt(*FFI_CONVERT(int, value));
		break;

		case 'd':
			result->setDouble(*FFI_CONVERT(double, value));
		break;

		case 'b':
			result->setBool(*FFI_CONVERT(bool, value));
		break;

		case 's': case 'c': case 'p':
			result->setData(value);
		break;
	}
}

void FFIStructData::getMember(Value* result, const CString& member_name)
{
	getMember(result, this->m_struct_type->getMember(member_name));
}

void* FFIStruct::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	FFIStructData* data = new FFIStructData;
	const CString* struct_type = args->at(0)->getStr();
	FFIStruct* handler = const_cast<FFIStruct*>(this);

	data->setStruct(handler->m_structs, *struct_type);

	return data;
}

void FFIStruct::deallocData(void* value)
{
	FFIStructData* data = static_cast<FFIStructData*>(value);
	delete data;
}

CLEVER_METHOD(FFIStruct::ctor)
{
	if (!clever_check_args("s")) {
		return;
	}

	result->setObj(this, allocData(&args));
}


CLEVER_METHOD(FFIStruct::addStruct)
{
	if (!clever_check_args("s")) {
		return;
	}

	const CString* s_name = args.at(0)->getStr();
	FFIStruct* handler = const_cast<FFIStruct*>(this);

	handler->m_structs[*s_name] = new ExtStruct;
}

CLEVER_METHOD(FFIStruct::addMember)
{
	if (!clever_check_args("sss")) {
		return;
	}

	const CString* s_name = args.at(0)->getStr();
	const CString* s_member_name = args.at(1)->getStr();
	const CString* s_member_type = args.at(2)->getStr();

	FFIStruct* handler = const_cast<FFIStruct*>(this);

	ExtStruct* ext_struct = handler->m_structs[*s_name];

	ext_struct->addMember(*s_member_name, s_member_type->at(0));
}

CLEVER_METHOD(FFIStruct::getMember)
{
	FFIStructData* data = CLEVER_GET_OBJECT(FFIStructData*, CLEVER_THIS());
	const CString* member_name = args.at(0)->getStr();

	data->getMember(result, *member_name);
}

CLEVER_METHOD(FFIStruct::setMember)
{
	FFIStructData* data = CLEVER_GET_OBJECT(FFIStructData*, CLEVER_THIS());
	const CString* member_name = args.at(0)->getStr();

	data->setMember(*member_name, args.at(1));
}

CLEVER_TYPE_INIT(FFIStruct::init)
{
	Function* ctor = new Function("FFIStruct", (MethodPtr) &FFIStruct::ctor);

	setConstructor(ctor);

	addMethod(ctor);

	addMethod(new Function("addStruct",   (MethodPtr)&FFIStruct::addStruct))
			->setStatic();
	addMethod(new Function("addMember",   (MethodPtr)&FFIStruct::addMember))
			->setStatic();
	addMethod(new Function("getMember",   (MethodPtr)&FFIStruct::getMember));
	addMethod(new Function("setMember",   (MethodPtr)&FFIStruct::setMember));
}
}}}
