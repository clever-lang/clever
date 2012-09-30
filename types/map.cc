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
#include "types/mapiterator.h"
#include "types/mapiteratorvalue.h"
#include "types/map.h"
#include "compiler/compiler.h"

namespace clever {

/**
 * Void Map::Map()
 */
CLEVER_METHOD(Map::constructor) {
	CLEVER_RETURN_DATA_VALUE(CLEVER_THIS()->getTypePtr()->allocateValue());
}

/**
 * Void Map::__assign__(Map)
 */
CLEVER_METHOD(Map::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * Array<K> Map<K, V [, C]>::_at_(K key)
 * Access the element whose key is equal `key'
 */
CLEVER_METHOD(Map::at) {
	MapValue::ValueType& map = CLEVER_GET_VALUE(MapValue*, value)->getMap();
	MapValue::Iterator it = map.find(CLEVER_ARG(0));

	if (it != map.end()) {
		retval->copy(it->second);
	}
	else {
		const Type* value_type = ((const TemplatedType*)CLEVER_THIS()
			->getTypePtr())->getTypeArg(1);
		
		Compiler::warningf("Map %S does not contains the key %S. "
				"Returning default value of type %S.",
			value->getName(), CLEVER_ARG(0)->getTypePtr()->getName(), value_type->getName());
		
		retval->setTypePtr(value_type);
		retval->initialize();
	}
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
	Value* key = new Value();
	Value* val = new Value();

	key->deepCopy(CLEVER_ARG(0));
	val->deepCopy(CLEVER_ARG(1));

	map->getMap().insert(std::make_pair(key, val));
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
 * Array<Pair<K,V>> Map<K, V [, C]>::getAll()
 * Returns an Array<> with all pair (key, value) present in this Map
 */
CLEVER_METHOD(Map::getAll) {
	MapValue::ValueType& map = CLEVER_GET_VALUE(MapValue*, value)->getMap();
	MapValue::Iterator it = map.begin(), end = map.end();

	const Type* const pair_type =
		static_cast<const TemplatedType*>(CLEVER_TYPE("Pair"))
		->getTemplatedType(CLEVER_THIS_ARG(0), CLEVER_THIS_ARG(1));

	ValueVector* vv = new ValueVector();
	Value* v;

	while (it != end) {
		PairValue* pv = new PairValue(it->first, it->second);

		v = new Value();
		v->setDataValue(pv);
		v->setTypePtr(pair_type);

		vv->push_back(v);
		++it;
	}

	retval->setTypePtr(CLEVER_TPL_ARRAY(pair_type));
	CLEVER_RETURN_ARRAY(vv);
}

/**
 * MapIterator Map<K, V [, C]>::begin()
 * Returns an iterator to the begin of this Map
 */
CLEVER_METHOD(Map::begin) {
	MapIteratorValue* miv = new MapIteratorValue(
		CLEVER_GET_VALUE(MapValue*, CLEVER_THIS())
	);
	
	MapValue::ValueType& map = CLEVER_GET_VALUE(MapValue*, value)->getMap();
	miv->getIterator() = map.begin();
	
	CLEVER_RETURN_DATA_VALUE(miv);
}

/**
 * MapIterator Map<K, V [, C]>::begin()
 * Returns an iterator to the end of this Map
 */
CLEVER_METHOD(Map::end) {
	MapIteratorValue* miv = new MapIteratorValue(
		CLEVER_GET_VALUE(MapValue*, CLEVER_THIS())
	);
	
	MapValue::ValueType& map = CLEVER_GET_VALUE(MapValue*, value)->getMap();
	miv->getIterator() = map.end();
	
	CLEVER_RETURN_DATA_VALUE(miv);
}


/**
 * Map type initializator
 */
void Map::init() {
	/**
	 * Checks if we are in our "virtual" Map type
	 */
	if (CLEVER_TPL_ARG(0) == NULL) {
		return;
	}

	/** Type pointers */
	const Type* const key_type   = CLEVER_TPL_ARG(0);
	const Type* const value_type = CLEVER_TPL_ARG(1);
	const Type* const arr_key = CLEVER_TPL_ARRAY(key_type);
	const Type* const arr_val = CLEVER_TPL_ARRAY(value_type);

	const Type* const pair_type =
		static_cast<const TemplatedType*>(CLEVER_TYPE("Pair"))
		->getTemplatedType(key_type, value_type);

	const Type* const arr_pair = CLEVER_TPL_ARRAY(pair_type);
	const Type* const map_type = 
		static_cast<const TemplatedType*>(CLEVER_TYPE("Map"))
		->getTemplatedType(key_type, value_type);
	
	const Type* const iter_type = 
		static_cast<const TemplatedType*>(CLEVER_TYPE("MapIterator"))
		->getTemplatedType(key_type, value_type);

	/**
	 * Beginning of methods definitions
	 */
	addMethod(new Method(CLEVER_CTOR_NAME, &Map::constructor, map_type));
	 
 	addMethod((new Method(CLEVER_OPERATOR_AT, &Map::at, CLEVER_TPL_ARG(1)))
 		->addArg("key", CLEVER_TPL_ARG(0))
 	);
	
	addMethod((new Method("insert", &Map::insert, CLEVER_VOID, false))
		->addArg("key", key_type)
		->addArg("value", value_type)
	);

	addMethod(new Method("toString", &Map::toString, CLEVER_STR));

	addMethod(new Method("size", &Map::size, CLEVER_INT));

	addMethod(new Method("isEmpty", &Map::isEmpty, CLEVER_BOOL));

	addMethod(new Method("clear", &Map::clear, CLEVER_VOID));

	addMethod(new Method("getKeys", &Map::getKeys, arr_key));

	addMethod(new Method("getValues", &Map::getValues, arr_val));

	addMethod(new Method("getAll", &Map::getAll, arr_pair));

	addMethod((new Method("hasKey", &Map::hasKey, CLEVER_BOOL))
		->addArg("key", key_type)
	);
	
	addMethod(new Method("begin", &Map::begin, iter_type));
	addMethod(new Method("end", &Map::end, iter_type));
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
