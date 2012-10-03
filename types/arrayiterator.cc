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

#include "compiler/compiler.h"
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
 * Performs the shallow and deep copy
 */
DataValue* ArrayIterator::copy(const Value* orig, bool deep) const {
	ArrayIteratorValue* miv = new ArrayIteratorValue;
	ArrayIteratorValue* val = CLEVER_GET_VALUE(ArrayIteratorValue*, orig);
	
	miv->setIterator(val->getIterator());
	miv->setArray(val->getArray());
	
	return static_cast<DataValue*>(miv);
}

/**
 * ArrayIterator<T> ArrayIterator<T>::__copy__(ArrayIterator<T> obj)
 * Return a deep copy of the object of same time
 */
CLEVER_METHOD(ArrayIterator::do_copy) {
	CLEVER_RETURN_DATA_VALUE(
		CLEVER_ARG(0)->getTypePtr()->copy(CLEVER_ARG(0), false));
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
	
	if (miv->valid()) {
		Value* val = miv->get();
		retval->copy(val);
		return;
	}
	
	Compiler::warningf("Trying to access an invalid iterator (%S).", 
		CLEVER_THIS()->getName());
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
	ret->setArray(a->getArray());
	
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
	ret->setArray(a->getArray());
	
 	CLEVER_RETURN_DATA_VALUE(ret);
 }
 
/**
 * Int ArrayIterator::minus_it()
 */
 CLEVER_METHOD(ArrayIterator::minus_it) {
 	ArrayIteratorValue* a = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(0));
 	ArrayIteratorValue* b = CLEVER_GET_VALUE(ArrayIteratorValue*,  CLEVER_ARG(1));
	
 	CLEVER_RETURN_INT(a->getIterator() - b->getIterator());
 }

/**
 * Bool ArrayIterator::isValid()
 */
CLEVER_METHOD(ArrayIterator::isValid) {
	ArrayIteratorValue* miv = CLEVER_GET_VALUE(ArrayIteratorValue*, value);
	
	CLEVER_RETURN_BOOL(miv->valid());
}

/**
 * Void ArrayIterator::set(ValueType)
 */
 CLEVER_METHOD(ArrayIterator::set) {
 	ArrayIteratorValue* a = CLEVER_GET_VALUE(ArrayIteratorValue*,  value);
	
	if (a->valid()) {
		a->setValue(CLEVER_ARG(0));
		return;
	}
	
	Compiler::warningf("Trying to access an invalid iterator (%S).", 
		CLEVER_THIS()->getName());
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
	
	addMethod(
		(new Method(CLEVER_OPERATOR_MINUS, &ArrayIterator::minus_it, CLEVER_INT))
			->addArg("arg1", this)
			->addArg("arg2", this)
	);

	addMethod(
		(new Method(CLEVER_COPY_NAME, &ArrayIterator::do_copy, this, false))
			->addArg("orig", this)
	);

	addMethod((new Method("set", &ArrayIterator::set, CLEVER_VOID))
		->addArg("value", value_type)
	);
	
	addMethod(new Method("get", &ArrayIterator::get, value_type));
	addMethod(new Method("isValid", &ArrayIterator::isValid, CLEVER_BOOL));
}

DataValue* ArrayIterator::allocateValue() const {
	return NULL;
}

} // clever
