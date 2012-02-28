/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include <fstream>
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/std/ffi/ffi.h"
#include "modules/std/ffi/ffiobject.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std { namespace ffi {

/**
 * FFIObject::constructor()
 */
CLEVER_METHOD(FFIObject::constructor) {
	FFIObjectValue* sv = new FFIObjectValue;

	CLEVER_RETURN_DATA_VALUE(sv);
}

/**
 * Void FFIObject::operator=(FFIObject object)
 */
CLEVER_METHOD(FFIObject::do_assign) {
	FFIObjectValue* lv = CLEVER_GET_VALUE(FFIObjectValue*, CLEVER_THIS());
	const FFIObjectValue* rv = static_cast<FFIObjectValue* >(CLEVER_ARG_DATA_VALUE(0));

	lv->pointer = rv->pointer;
}

void FFIObject::init() {
	const Type* ffiobj = CLEVER_TYPE("FFIObject");

	addMethod(new Method(CLEVER_CTOR_NAME,
		(MethodPtr)&FFIObject::constructor, ffiobj));

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&FFIObject::do_assign,
			ffiobj, false))
			->addArg("rvalue", ffiobj)
	);
}

DataValue* FFIObject::allocateValue() const {
	return new FFIObjectValue;
}

void FFIObject::destructor(Value* value) const {
}

}}}} // clever::packages::std::ffi
