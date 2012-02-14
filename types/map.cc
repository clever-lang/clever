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
	CLEVER_RETURN_INT(map->m_map.size());
}

/**
 * Bool Map<K, V [,C]>::isEmpty()
 */
CLEVER_METHOD(Map::isEmpty) {
	MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
	CLEVER_RETURN_BOOL(map->m_map.empty());
}

/**
 * Void Map<K, V [,C]>::insert(K, V)
 */
CLEVER_METHOD(Map::insert) {
	MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
	map->m_map.insert(std::make_pair(CLEVER_ARG(0), CLEVER_ARG(1)));

	CLEVER_ARG(0)->addRef();
	CLEVER_ARG(1)->addRef();
}

/**
 * Void Map<K, V [,C]>::clear()
 */
CLEVER_METHOD(Map::clear) {
	MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
	MapValue::iterator it = map->m_map.begin(),
		end = map->m_map.end();
		
	while (it != end) {
		it->first->delRef();
		it->second->delRef();
		++it;
	}

	map->m_map.clear();
}

/**
 * String Map<K, V [,C]>::toString()
 */
CLEVER_METHOD(Map::toString) {
	MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
	MapValue::iterator it = map->m_map.begin(),
		end = map->m_map.end();

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
	MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
	MapValue::iterator it = map->m_map.begin(),
		end = map->m_map.end();

	bool ret = false;
	
	if (it != end) {
		if (it->first->toString() == CLEVER_ARG(0)->toString()) {
			ret = true;
		}
		
		while (++it != end && !ret) {
			if (it->first->toString() == CLEVER_ARG(0)->toString()) {
				ret = true;
			}
		}
	}
	
	CLEVER_RETURN_BOOL(ret);
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

	addMethod((new Method("insert", (MethodPtr)&Map::insert, CLEVER_VOID, false))
		->addArg("key", CLEVER_TPL_ARG(0))
		->addArg("value", CLEVER_TPL_ARG(1))
	);

	addMethod(new Method("toString", (MethodPtr)&Map::toString, CLEVER_STR));

	addMethod(new Method("size", (MethodPtr)&Map::size, CLEVER_INT));

	addMethod(new Method("isEmpty", (MethodPtr)&Map::isEmpty, CLEVER_BOOL));

	addMethod(new Method("clear", (MethodPtr)&Map::clear, CLEVER_VOID));
	
	addMethod((new Method("hasKey", (MethodPtr)&Map::hasKey, CLEVER_BOOL))
		->addArg("key", CLEVER_TPL_ARG(0))
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
