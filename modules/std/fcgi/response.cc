/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "types/type.h"
#include "types/native_types.h"
#include "core/value.h"
#include "core/clever.h"
#include "modules/std/fcgi/fcgi.h"
#include "modules/std/fcgi/response.h"
#include "modules/std/fcgi/request.h"

namespace clever { namespace packages { namespace std {

void Response::dump(const void* data) const {
	dump(data, ::std::cout);
}

void Response::dump(const void* data, ::std::ostream& out) const {
	Value::DataValue* dvalue = (Value::DataValue*)data;
	if (dvalue) {
		
	}
}

void* Response::allocData(CLEVER_TYPE_CTOR_ARGS) const {
	return NULL;
}

void Response::deallocData(void* data) {

}

CLEVER_TYPE_INIT(Response::init)
{
	
}

}}} // clever::packages::std
