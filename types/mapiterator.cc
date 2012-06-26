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
#include "compiler/compiler.h"
#include "types/pair.h"
#include "types/mapiterator.h"
#include "types/mapiteratorvalue.h"

namespace clever {

/**
 * Void MapIterator::MapIterator(Map<>)
 */
CLEVER_METHOD(MapIterator::constructor) {
	MapIteratorValue* miv = new MapIteratorValue(
		CLEVER_GET_VALUE(MapValue*, CLEVER_ARG(0))
	);
	
	CLEVER_RETURN_DATA_VALUE(miv);
}

/**
 * Void MapIterator::__assign__(MapIterator)
 */
CLEVER_METHOD(MapIterator::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * MapIterator MapIterator::__pre_dec__(MapIterator)
 */
CLEVER_METHOD(MapIterator::pre_dec) {
	MapIteratorValue& miv = *CLEVER_GET_VALUE(MapIteratorValue*, value);
	--miv;
	CLEVER_RETURN_DATA_VALUE(CLEVER_GET_VALUE(MapIteratorValue*, value));
}

/**
 * MapIterator MapIterator::__pre_inc_(MapIterator)
 */
CLEVER_METHOD(MapIterator::pre_inc) {
	MapIteratorValue& miv = *CLEVER_GET_VALUE(MapIteratorValue*, value);
	++miv;
	CLEVER_RETURN_DATA_VALUE(CLEVER_GET_VALUE(MapIteratorValue*, value));
}

/**
 * Object MapIterator::get()
 */
CLEVER_METHOD(MapIterator::get) {
	MapIteratorValue* miv = CLEVER_GET_VALUE(MapIteratorValue*, value);
	
	std::pair<Value*, Value*> pair = miv->get();
	
	const Type* const pair_type =
		static_cast<const TemplatedType*>(CLEVER_TYPE("Pair"))
		->getTemplatedType(pair.first->getTypePtr(), pair.second->getTypePtr());
		
	PairValue* pv = new PairValue(pair.first, pair.second);
	retval->setTypePtr(pair_type);
	
	CLEVER_RETURN_DATA_VALUE(pv);
}

/**
 * Bool MapIterator::equal()
 */
CLEVER_METHOD(MapIterator::equal) {
	MapIteratorValue* a = CLEVER_GET_VALUE(MapIteratorValue*,  CLEVER_ARG(0));
	MapIteratorValue* b = CLEVER_GET_VALUE(MapIteratorValue*,  CLEVER_ARG(1));
	
	CLEVER_RETURN_BOOL(a->getIterator() == b->getIterator());
}

/**
 * Object MapIterator::not_equal()
 */
CLEVER_METHOD(MapIterator::not_equal) {
	MapIteratorValue* a = CLEVER_GET_VALUE(MapIteratorValue*,  CLEVER_ARG(0));
	MapIteratorValue* b = CLEVER_GET_VALUE(MapIteratorValue*,  CLEVER_ARG(1));
	
	CLEVER_RETURN_BOOL(a->getIterator() != b->getIterator());
}

/**
 * Object MapIterator::isValid()
 */
CLEVER_METHOD(MapIterator::isValid) {
	MapIteratorValue* miv = CLEVER_GET_VALUE(MapIteratorValue*, value);
	
	CLEVER_RETURN_BOOL(miv->valid());
}

/**
 * MapIterator type initializator
 */
void MapIterator::init() {
	addMethod((new Method(CLEVER_CTOR_NAME, &MapIterator::constructor, this))
		->addArg("map", CLEVER_OBJECT)
	);
	
	addMethod(new Method(CLEVER_OPERATOR_PRE_INC, &MapIterator::pre_inc, this));
	addMethod(new Method(CLEVER_OPERATOR_POS_INC, &MapIterator::pre_inc, this));
	addMethod(new Method(CLEVER_OPERATOR_PRE_DEC, &MapIterator::pre_dec, this));
	addMethod(new Method(CLEVER_OPERATOR_POS_DEC, &MapIterator::pre_dec, this));

	addMethod(
	(new Method(CLEVER_OPERATOR_EQUAL, &MapIterator::equal, CLEVER_BOOL))
		->addArg("arg1", this)
		->addArg("arg2", this)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_NE, &MapIterator::not_equal, CLEVER_BOOL))
			->addArg("arg1", this)
			->addArg("arg2", this)
	);

	addMethod(new Method("get", &MapIterator::get, CLEVER_OBJECT));
	addMethod(new Method("isValid", &MapIterator::isValid, CLEVER_BOOL));
}

DataValue* MapIterator::allocateValue() const {
	return NULL;
}

} // clever
