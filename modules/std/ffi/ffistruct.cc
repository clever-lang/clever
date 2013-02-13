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
#include "modules/std/ffi/ffistruct.h"
#include "modules/std/ffi/ffitypes.h"

namespace clever { namespace modules { namespace std {

/*
FFISTRUCT
*/

void FFIStructData::setStruct(ExtStructs& structs_map, const CString& struct_type)
{
	m_struct_type = structs_map[struct_type];

	if (data) {
		::std::free(data);
	}

	size_t size = m_struct_type->getSize();
	data = malloc(size);
}

void FFIStructData::setMember(int i, const Value* const v)
{
	size_t offset = m_struct_type->getOffset(i);
	size_t size = m_struct_type->getSize(i);
	FFIType type = m_struct_type->getType(i);

	switch (type) {
		case FFIINT:
			{
				int w = v->getInt();
				memcpy(static_cast<char*>(data) + offset, &w, size);
			}
			break;

		case FFIDOUBLE:
			{
				double w = v->getDouble();
				memcpy(static_cast<char*>(data) + offset, &w, size);
			}
			break;

		default:
			break;
	}
}

void FFIStructData::setMember(const CString& member_name, const Value* const v)
{
	setMember(m_struct_type->getMember(member_name), v);
}

#define FFI_CONVERT(A, B) (static_cast<A*>(B))

void FFIStructData::getMember(Value* result,  int i)
{
	FFIType type = m_struct_type->getType(i);
	size_t offset = m_struct_type->getOffset(i);
	void* value = static_cast<char*>(data) + offset;

	switch (type) {
		case FFIINT:
			result->setInt(*FFI_CONVERT(int, value));
			break;

		case FFIDOUBLE:
			result->setDouble(*FFI_CONVERT(double, value));
			break;

		case FFIBOOL:
			result->setBool(*FFI_CONVERT(bool, value));
			break;

		case FFISTRING:
		case FFIPOINTER:
			//result->setData(value);
			break;

		default:
			break;
	}
}

void FFIStructData::getMember(Value* result, const CString& member_name)
{
	getMember(result, m_struct_type->getMember(member_name));
}

Value* FFIStructData::getMember(const CString* name) const
{
	Value* v = 0;

	v = TypeObject::getMember(name);

	if (v) {
		return v;
	}

	v = const_cast<FFIStructData*>(this)->m_member_map[*name];
	if (v == 0) {
		v = new Value;
		const_cast<FFIStructData*>(this)->m_member_map[*name] = v;
	}
	const_cast<FFIStructData*>(this)->getMember(v, *name);
	return v;
}

TypeObject* FFIStruct::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	FFIStructData* data = new FFIStructData;
	const CString* struct_type = args->at(0)->getStr();

	data->setStruct(FFITypes::m_structs, *struct_type);

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


CLEVER_METHOD(FFIStruct::getMember)
{
	if (!clever_check_args("s")) {
		return;
	}
	FFIStructData* data = CLEVER_GET_OBJECT(FFIStructData*, CLEVER_THIS());
	const CString* member_name = args.at(0)->getStr();

	data->getMember(result, *member_name);
}

CLEVER_METHOD(FFIStruct::setMember)
{
	if (!clever_check_args("s*")) {
		return;
	}
	FFIStructData* data = CLEVER_GET_OBJECT(FFIStructData*, CLEVER_THIS());
	const CString* member_name = args.at(0)->getStr();

	data->setMember(*member_name, args.at(1));
}

CLEVER_TYPE_INIT(FFIStruct::init)
{
	setConstructor((MethodPtr) &FFIStruct::ctor);

	addMethod(new Function("getMember",   (MethodPtr)&FFIStruct::getMember));
	addMethod(new Function("setMember",   (MethodPtr)&FFIStruct::setMember));
}

// FFITYPES

ExtStructs FFITypes::m_structs;

void ExtStruct::addMember(const ::std::string& member_name, FFIType member_type,
	const ::std::string& member_struct_name, const ExtStructs* struct_map)
{
	if (member_type == FFISTRUCT) {
		return;
	}

	size_t n = m_member_offset.size();
	size_t size_type = _get_offset_ext_type(member_type);
	size_t offset = 0;
	size_t padding = 0;

	if (n > 0) {
		size_t align = getSize(n - 1);
		offset = getOffset(n - 1) + align;
		padding = _get_padding_ext(offset, align);
	}

	m_member_offset.push_back(offset + padding);
	m_member_size.push_back(size_type);
	m_member_name.push_back(member_name);
	m_member_type.push_back(member_type);

	if (m_member_map.find(member_name) == m_member_map.end()) {
		m_member_map[member_name] = n;
	}
}

CLEVER_METHOD(FFITypes::ctor)
{
	if (!clever_check_args("s")) {
		return;
	}

	result->setObj(this, allocData(&args));
}

TypeObject* FFITypes::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	const CString* struct_name = args->at(0)->getStr();

	FFITypesBuilder* data = new FFITypesBuilder(*struct_name);

	if (m_structs.find(*struct_name) == m_structs.end()) {
		m_structs[*struct_name] = new ExtStruct;
	}

	return data;
}

void FFITypes::deallocData(void* value)
{
	FFITypesBuilder* data = static_cast<FFITypesBuilder*>(value);
	delete data;
}


CLEVER_METHOD(FFITypes::addMember)
{
	if (!clever_check_args("si")) {
		return;
	}

	FFITypesBuilder* data = CLEVER_GET_OBJECT(FFITypesBuilder*, CLEVER_THIS());

	const CString* s_member_name = args.at(0)->getStr();
	FFIType s_member_type = static_cast<FFIType>(args.at(1)->getInt());


	ExtStruct* ext_struct = m_structs[data->getName()];

	ext_struct->addMember(*s_member_name, s_member_type);
}

CLEVER_METHOD(FFITypes::addFunction)
{
	if (!clever_check_args("s*")) {
		return;
	}

	FFITypesBuilder* data = CLEVER_GET_OBJECT(FFITypesBuilder*, CLEVER_THIS());

	const CString* s_func_name = args.at(0)->getStr();

	ExtStruct* ext_struct = m_structs[data->getName()];
	ExtMemberType ext_func_args;

	for (size_t i = 1, n = args.size(); i < n; ++i) {
		ext_func_args.push_back(static_cast<FFIType>(args.at(i)->getInt()));
	}
	ext_struct->addFunction(*s_func_name, ext_func_args);
}

CLEVER_TYPE_INIT(FFITypes::init)
{
	setConstructor((MethodPtr) &FFITypes::ctor);

	addMethod(new Function("addMember",   (MethodPtr)&FFITypes::addMember));
	addMethod(new Function("addFunction", (MethodPtr)&FFITypes::addFunction));

	addProperty(CSTRING("INT"),		new Value(long(FFIINT),     true));
	addProperty(CSTRING("DOUBLE"),	new Value(long(FFIDOUBLE),  true));
	addProperty(CSTRING("BOOL"),	new Value(long(FFIBOOL),    true));
	addProperty(CSTRING("VOID"),	new Value(long(FFIVOID),    true));
	addProperty(CSTRING("STRING"),	new Value(long(FFISTRING),  true));
	addProperty(CSTRING("POINTER"),	new Value(long(FFIPOINTER), true));
	addProperty(CSTRING("STRUCT"),	new Value(long(FFISTRUCT),  true));
}

}}} // clever::modules::std
