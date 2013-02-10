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

void FFIStructData::setMember(ExtStructs& structs_map, size_t i, const Value* const v)
{

}

void FFIStructData::setMember(ExtStructs& structs_map, const CString& member_name, const Value* const v)
{

}

Value* FFIStructData::getMember(ExtStructs& structs_map, size_t i)
{

}

Value* FFIStructData::getMember(ExtStructs& structs_map, const CString& member_name)
{

}



void* FFIStruct::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
}

void FFIStruct::deallocData(void* value)
{
}

CLEVER_METHOD(FFIStruct::ctor)
{
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
	const CString* s_member_name = args.at(0)->getStr();
	const CString* s_member_type = args.at(0)->getStr();

	FFIStruct* handler = const_cast<FFIStruct*>(this);

	ExtStruct* ext_struct = handler->m_structs[*s_name];

	ext_struct->addMember(*s_member_name, s_member_type->at(0));
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
}
}}}
