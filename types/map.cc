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
#include "types/map.h"
#include "compiler/compiler.h"

namespace clever {

/**
 * Void Map::__assign__(Map)
 */
CLEVER_METHOD(Map::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * Int Map<K, V [,C]>::size()
 */
CLEVER_METHOD(Map::size) {
	MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
	CLEVER_RETURN_INT(map->getMap().size());
}

/**
 * Bool Map<K, V [,C]>::isEmpty()
 */
CLEVER_METHOD(Map::isEmpty) {
	MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
	CLEVER_RETURN_BOOL(map->getMap().empty());
}

/**
 * Void Map<K, V [,C]>::insert(K, V)
 */
CLEVER_METHOD(Map::insert) {
	MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
	map->getMap().insert(std::make_pair(CLEVER_ARG(0), CLEVER_ARG(1)));

	CLEVER_ARG(0)->addRef();
	CLEVER_ARG(1)->addRef();
}

/**
 * Void Map<K, V [,C]>::clear()
 */
CLEVER_METHOD(Map::clear) {
	MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
	MapValue::Iterator it = map->getMap().begin(),
		end = map->getMap().end();
		
	while (it != end) {
		it->first->delRef();
		it->second->delRef();
		++it;
	}

	map->getMap().clear();
}

/**
 * String Map<K, V [,C]>::toString()
 */
CLEVER_METHOD(Map::toString) {
	MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
	MapValue::Iterator it = map->getMap().begin(),
		end = map->getMap().end();

	std::string ret = "[", sep = ", ";	

	if (it != end) {
		ret += it->first->toString() + " => "
			+ it->second->toString();
		
		while (++it != end) {
			ret += sep + it->first->toString() + " => "
				+ it->second->toString();
		}
	}

	ret += "]";

	CLEVER_RETURN_STR(CSTRING(ret));
}

/**
 * Bool Map<K, V [, C]>::hasKey(K)
 */
CLEVER_METHOD(Map::hasKey) {
	MapValue::ValueType& map = CLEVER_GET_VALUE(MapValue*, value)->getMap();
	Value* search = CLEVER_ARG(0);
	
	MapValue::Iterator it = map.find(search);
	
	CLEVER_RETURN_BOOL(it != map.end());
}

/**
 * Array<K> Map<K, V [, C]>::getKeys()
 * Returns an Array<K> with all keys present in this Map
 */
CLEVER_METHOD(Map::getKeys) {
	MapValue::ValueType& map = CLEVER_GET_VALUE(MapValue*, value)->getMap();
	MapValue::Iterator it = map.begin(), end = map.end();
	
	ValueVector* vv = new ValueVector();
	Value* v;
	
	while (it != end) {
		v = new Value();
		v->copy(it->first);
		vv->push_back(v);
		++it;
	}
	
	retval->setTypePtr(CLEVER_TPL_ARRAY(CLEVER_TYPE_ARG(value->getTypePtr(), 0)));
	CLEVER_RETURN_ARRAY(vv);
}

/**
 * Array<V> Map<K, V [, C]>::getValues()
 * Returns an Array<V> with all values present in this Map
 */
CLEVER_METHOD(Map::getValues) {
	MapValue::ValueType& map = CLEVER_GET_VALUE(MapValue*, value)->getMap();
	MapValue::Iterator it = map.begin(), end = map.end();
	
	ValueVector* vv = new ValueVector();
	Value* v;
	
	while (it != end) {
		v = new Value();
		v->copy(it->second);
		vv->push_back(v);
		++it;
	}
	
	retval->setTypePtr(CLEVER_TPL_ARRAY(CLEVER_TYPE_ARG(value->getTypePtr(), 1)));
	CLEVER_RETURN_ARRAY(vv);
}


/**
 * Map type initializator
 */
void Map::init() {
	/**
	 * Check if we are in our "virtual" Map type
	 */
	if (CLEVER_TPL_ARG(0) == NULL) {
		return;
	}
	
	const Type* const key_type = CLEVER_TPL_ARG(0);
	const Type* const value_type = CLEVER_TPL_ARG(1);
	const Type* const arr_key = CLEVER_TPL_ARRAY(key_type);
	const Type* const arr_val = CLEVER_TPL_ARRAY(value_type);

	addMethod((new Method("insert", (MethodPtr)&Map::insert, CLEVER_VOID, false))
		->addArg("key", key_type)
		->addArg("value", value_type)
	);

	addMethod(new Method("toString", (MethodPtr)&Map::toString, CLEVER_STR));

	addMethod(new Method("size", (MethodPtr)&Map::size, CLEVER_INT));

	addMethod(new Method("isEmpty", (MethodPtr)&Map::isEmpty, CLEVER_BOOL));

	addMethod(new Method("clear", (MethodPtr)&Map::clear, CLEVER_VOID));
	
	addMethod(new Method("getKeys", (MethodPtr)&Map::getKeys, arr_key));
	
	addMethod(new Method("getValues", (MethodPtr)&Map::getValues, arr_val));
	
	addMethod((new Method("hasKey", (MethodPtr)&Map::hasKey, CLEVER_BOOL))
		->addArg("key", key_type)
	);
}

DataValue* Map::allocateValue() const {
	if (this->getNumArgs() == 2) {
		TypeVector tv(2, getTypeArg(0));
		return new MapValue(getTypeArg(0)
			->getMethod(CSTRING(CLEVER_OPERATOR_LESS), &tv));
	}
	
	TypeVector tv(2, getTypeArg(0));
	return new MapValue(getTypeArg(2)
		->getMethod(CSTRING("compare"), &tv), new Value(getTypeArg(2)));
}

} // clever
