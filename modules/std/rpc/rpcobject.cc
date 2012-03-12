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
#include <string>
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/std/rpc/rpc.h"
#include "modules/std/rpc/rpcobject.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std { namespace rpc {

/**
 * RPCObject::constructor()
 */
CLEVER_METHOD(RPCObject::constructor) {
	RPCObjectValue* sv = new RPCObjectValue;

	CLEVER_RETURN_DATA_VALUE(sv);
}

/**
 * Void RPCObject::operator=(FFIObject object)
 */
CLEVER_METHOD(RPCObject::do_assign) {

	RPCObjectValue* lv = CLEVER_GET_VALUE(RPCObjectValue*, CLEVER_THIS());
	const RPCObjectValue* rv = static_cast<RPCObjectValue* >(CLEVER_ARG_DATA_VALUE(0));

	lv->type = rv->type;
	if(lv->pointer){
		free(lv->pointer);
		lv->pointer=0;
	}
	lv->pointer = rv->pointer;
}

CLEVER_METHOD(RPCObject::toInteger) {
	RPCObjectValue* lv = CLEVER_GET_VALUE(RPCObjectValue*, CLEVER_THIS());
	int* vi = static_cast<int*> (lv->pointer);

	CLEVER_RETURN_INT(*vi);
}

CLEVER_METHOD(RPCObject::toDouble) {
	RPCObjectValue* lv = CLEVER_GET_VALUE(RPCObjectValue*, CLEVER_THIS());
	double* vd = static_cast<double*> (lv->pointer);

	CLEVER_RETURN_DOUBLE(*vd);
}

CLEVER_METHOD(RPCObject::toString) {
	RPCObjectValue* lv = CLEVER_GET_VALUE(RPCObjectValue*, CLEVER_THIS());
	char* vs = static_cast<char*> (lv->pointer);

	CLEVER_RETURN_STR(CSTRING(::std::string(vs)));
}

CLEVER_METHOD(RPCObject::clear) {
	RPCObjectValue* lv = CLEVER_GET_VALUE(RPCObjectValue*, CLEVER_THIS());

	if(lv->pointer){
		free(lv->pointer);
		lv->pointer=0;
	}
}

void RPCObject::init() {
	const Type* rpcobj = CLEVER_TYPE("RPCObject");

	addMethod(new Method(CLEVER_CTOR_NAME,
		(MethodPtr)&RPCObject::constructor, rpcobj));

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&RPCObject::do_assign,
			rpcobj, false))
			->addArg("rvalue", rpcobj)
	);

	addMethod(
		(new Method("toInteger", (MethodPtr)&RPCObject::toInteger, CLEVER_INT))
	);

	addMethod(
		(new Method("toDouble", (MethodPtr)&RPCObject::toDouble, CLEVER_DOUBLE))
	);

	addMethod(
		(new Method("toString", (MethodPtr)&RPCObject::toString, CLEVER_STR))
	);

	addMethod(
		(new Method("clear", (MethodPtr)&RPCObject::clear, CLEVER_VOID))
	);
}

DataValue* RPCObject::allocateValue() const {
	return new RPCObjectValue;
}

void RPCObject::destructor(Value* value) const{
}

}}}} // clever::packages::std::rpcobject
