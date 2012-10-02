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

#include "types/type.h"
#include "types/pair.h"
#include "types/arrayiterator.h"
#include "types/arrayiteratorvalue.h"

namespace clever {

/**
 * Void ArrayIterator::ArrayIterator(Map<>)
 */
CLEVER_METHOD(ArrayIterator::constructor) {
	ArrayIteratorValue* miv = new ArrayIteratorValue(
		CLEVER_GET_VALUE(ArrayValue*, CLEVER_ARG(0))
	);
	
	CLEVER_RETURN_DATA_VALUE(miv);
}

/**
 * Void ArrayIterator::__assign__(ArrayIterator)
 */
CLEVER_METHOD(ArrayIterator::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * ArrayIterator ArrayIterator::__pre_dec__(ArrayIterator)
 */
CLEVER_METHOD(ArrayIterator::pre_dec) {
	ArrayIteratorValue& miv = *CLEVER_GET_VALUE(ArrayIteratorValue*, value);
	--miv;
	miv.addRef();
	CLEVER_RETURN_DATA_VALUE(CLEVER_GET_VALUE(ArrayIteratorValue*, value));
}

/**
 * ArrayIterator ArrayIterator::__pre_inc_(ArrayIterator)
 */
CLEVER_METHOD(ArrayIterator::pre_inc) {
	ArrayIteratorValue& miv = *CLEVER_GET_VALUE(ArrayIteratorValue*, value);
	++miv;
	miv.addRef();
	CLEVER_RETURN_DATA_VALUE(CLEVER_GET_VALUE(ArrayIteratorValue*, value));
}

/**
 * ValueType ArrayIterator::get()
 */
CLEVER_METHOD(ArrayIterator::get) {
	ArrayIteratorValue* miv = CLEVER_GET_VALUE(ArrayIteratorValue*, value);
	Value* val = miv->get();

	retval->copy(val);
}

/**
 * Bool ArrayIterator::equal()
 */
CLEVER_METHOD(ArrayIterator::equal) {
	ArrayIteratorValue* a = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(0));
	ArrayIteratorValue* b = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(1));
	
	CLEVER_RETURN_BOOL(a->getIterator() == b->getIterator());
}

/**
 * Object ArrayIterator::not_equal()
 */
CLEVER_METHOD(ArrayIterator::not_equal) {
	ArrayIteratorValue* a = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(0));
	ArrayIteratorValue* b = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(1));
	
	CLEVER_RETURN_BOOL(a->getIterator() != b->getIterator());
}

/**
 * Bool ArrayIterator::greater()
 */
CLEVER_METHOD(ArrayIterator::greater) {
	ArrayIteratorValue* a = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(0));
	ArrayIteratorValue* b = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(1));
	
	CLEVER_RETURN_BOOL(a->getIterator() > b->getIterator());
}

/**
 * Object ArrayIterator::less()
 */
CLEVER_METHOD(ArrayIterator::less) {
	ArrayIteratorValue* a = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(0));
	ArrayIteratorValue* b = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(1));
	
	CLEVER_RETURN_BOOL(a->getIterator() < b->getIterator());
}

/**
 * Bool ArrayIterator::ge()
 */
CLEVER_METHOD(ArrayIterator::ge) {
	ArrayIteratorValue* a = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(0));
	ArrayIteratorValue* b = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(1));
	
	CLEVER_RETURN_BOOL(a->getIterator() >= b->getIterator());
}

/**
 * Object ArrayIterator::le()
 */
CLEVER_METHOD(ArrayIterator::le) {
	ArrayIteratorValue* a = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(0));
	ArrayIteratorValue* b = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(1));
	
	CLEVER_RETURN_BOOL(a->getIterator() <= b->getIterator());
}

/**
 * ArrayIterator<> ArrayIterator::plus()
 */
CLEVER_METHOD(ArrayIterator::plus) {
	ArrayIteratorValue* a = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(0));
	int64_t offset = CLEVER_ARG(1)->getInteger();
	
	ValueVector::iterator it = a->getIterator() + offset;
	
	ArrayIteratorValue* ret = new ArrayIteratorValue();
	ret->setIterator(it);
	ret->setEnd(a->getEnd());
	
	CLEVER_RETURN_DATA_VALUE(ret);
}

/**
 * ArrayIterator<> ArrayIterator::minus()
 */
 CLEVER_METHOD(ArrayIterator::minus) {
 	ArrayIteratorValue* a = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(0));
 	int64_t offset = CLEVER_ARG(1)->getInteger();
	
 	ValueVector::iterator it = a->getIterator() - offset;
	
 	ArrayIteratorValue* ret = new ArrayIteratorValue();
 	ret->setIterator(it);
 	ret->setEnd(a->getEnd());
	
 	CLEVER_RETURN_DATA_VALUE(ret);
 }



/**
 * Bool ArrayIterator::isValid()
 */
CLEVER_METHOD(ArrayIterator::isValid) {
	ArrayIteratorValue* miv = CLEVER_GET_VALUE(ArrayIteratorValue*, value);
	
	CLEVER_RETURN_BOOL(miv->valid());
}

/**
 * ArrayIterator type initializator
 */
void ArrayIterator::init() {
	/**
	 * Checks if we are in our "virtual" Map type
	 */
	if (CLEVER_TPL_ARG(0) == NULL) {
		return;
	}
	
	const Type* value_type = CLEVER_TPL_ARG(0);
	
	addMethod((new Method(CLEVER_CTOR_NAME, &ArrayIterator::constructor, this))
		->addArg("array", CLEVER_OBJECT)
	);
	
	addMethod(new Method(CLEVER_OPERATOR_PRE_INC, 
		&ArrayIterator::pre_inc, this));
	addMethod(new Method(CLEVER_OPERATOR_POS_INC, 
		&ArrayIterator::pre_inc, this));
	addMethod(new Method(CLEVER_OPERATOR_PRE_DEC, 
		&ArrayIterator::pre_dec, this));
	addMethod(new Method(CLEVER_OPERATOR_POS_DEC, 
		&ArrayIterator::pre_dec, this));

	addMethod(
		(new Method(CLEVER_OPERATOR_EQUAL, &ArrayIterator::equal, CLEVER_BOOL))
			->addArg("arg1", this)
			->addArg("arg2", this)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_NE, &ArrayIterator::not_equal, CLEVER_BOOL))
			->addArg("arg1", this)
			->addArg("arg2", this)
	);
	
	addMethod(
		(new Method(CLEVER_OPERATOR_GREATER, &ArrayIterator::greater, CLEVER_BOOL))
			->addArg("arg1", this)
			->addArg("arg2", this)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LESS, &ArrayIterator::less, CLEVER_BOOL))
			->addArg("arg1", this)
			->addArg("arg2", this)
	);
	
	addMethod(
		(new Method(CLEVER_OPERATOR_GE, &ArrayIterator::ge, CLEVER_BOOL))
			->addArg("arg1", this)
			->addArg("arg2", this)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LE, &ArrayIterator::le, CLEVER_BOOL))
			->addArg("arg1", this)
			->addArg("arg2", this)
	);
	
	addMethod(
		(new Method(CLEVER_OPERATOR_PLUS, &ArrayIterator::plus, this))
			->addArg("arg1", this)
			->addArg("arg2", CLEVER_INT)
	);
	
	addMethod(
		(new Method(CLEVER_OPERATOR_MINUS, &ArrayIterator::minus, this))
			->addArg("arg1", this)
			->addArg("arg2", CLEVER_INT)
	);

	addMethod(new Method("get", &ArrayIterator::get, value_type));
	addMethod(new Method("isValid", &ArrayIterator::isValid, CLEVER_BOOL));
}

DataValue* ArrayIterator::allocateValue() const {
	return NULL;
}

} // clever
