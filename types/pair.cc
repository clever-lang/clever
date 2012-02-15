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

#include <utility>
#include "types/type.h"
#include "types/array.h"
#include "types/pair.h"
#include "types/pairvalue.h"
#include "compiler/compiler.h"

namespace clever {

/**
 * Void Pair::Pair(T1 a, T1 b)
 */
CLEVER_METHOD(Pair::constructor) {
	PairValue* pv = new PairValue(CLEVER_ARG(0), CLEVER_ARG(1));
	retval->setTypePtr(CLEVER_THIS()->getTypePtr());
	CLEVER_RETURN_DATA_VALUE(pv);
}

/**
 * Void Pair::__assign__(Pair)
 */
CLEVER_METHOD(Pair::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * T1 Pair::first()
 */
CLEVER_METHOD(Pair::first) {
	PairValue* pair = CLEVER_GET_VALUE(PairValue*, value);
	retval->copy(pair->first());
}

/**
 * Void Pair::setFirst(T1)
 */
CLEVER_METHOD(Pair::setFirst) {
	PairValue* pair = CLEVER_GET_VALUE(PairValue*, value);
	pair->first()->delRef();
	pair->setFirst(CLEVER_ARG(0));
	CLEVER_ARG(0)->addRef();
}

/**
 * T2 Pair::second()
 */
CLEVER_METHOD(Pair::second) {
	PairValue* pair = CLEVER_GET_VALUE(PairValue*, value);
	retval->copy(pair->second());
}

/**
 * Void Pair::setSecond(T2)
 */
CLEVER_METHOD(Pair::setSecond) {
	PairValue* pair = CLEVER_GET_VALUE(PairValue*, value);
	pair->second()->delRef();
	pair->setSecond(CLEVER_ARG(0));
	CLEVER_ARG(0)->addRef();
}


/**
 * String Pair<T1, T2>::toString()
 */
CLEVER_METHOD(Pair::toString) {
	PairValue* pair = CLEVER_GET_VALUE(PairValue*, value);
	std::string ret = "(";
	ret += pair->first()->toString();
	ret += ", ";
	ret += pair->second()->toString();
	ret += ")";

	CLEVER_RETURN_STR(CSTRING(ret));
}

/**
 * Pair type initializator
 */
void Pair::init() {
	/**
	 * Check if we are in our "virtual" Pair type
	 */
	if (CLEVER_TPL_ARG(0) == NULL) {
		return;
	}
	
	const Type* const t1 = CLEVER_TPL_ARG(0);
	const Type* const t2 = CLEVER_TPL_ARG(1);
	
	addMethod((new Method(CLEVER_CTOR_NAME, (MethodPtr)&Pair::constructor, this))
		->addArg("first", t1)
		->addArg("second", t2)
	);
	
	addMethod((new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&Pair::do_assign, CLEVER_VOID))
		->addArg("rhs", this)
	);
	
	addMethod(new Method("first", (MethodPtr)&Pair::first, t1));
	
	addMethod((new Method("setFirst", (MethodPtr)&Pair::setFirst, CLEVER_VOID))
		->addArg("newFirst", t1)
	);
	
	addMethod(new Method("second", (MethodPtr)&Pair::second, t2));
	
	addMethod((new Method("setSecond", (MethodPtr)&Pair::setSecond, CLEVER_VOID))
		->addArg("newSecond", t2)
	);
	
	addMethod(new Method("toString", (MethodPtr)&Pair::toString, CLEVER_STR));
}

DataValue* Pair::allocateValue() const {
	return new PairValue(getTypeArg(0), getTypeArg(1));
}

} // clever
