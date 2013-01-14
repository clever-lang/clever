/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <map>
#include "core/value.h"
#include "core/vm.h"
#include "types/map.h"
#include "types/function.h"

namespace clever {

void* MapType::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	MapObject* arr = new MapObject();
	ValueMap& map = arr->getData();

	for (size_t i = 0, j = args->size(); i < j; i += 2) {
		Value* val = new Value();

		val->copy(args->at(i+1));

		map.insert(ValuePair(*args->at(i)->getStr(), val));
	}

	return arr;
}

void MapType::deallocData(void* data)
{
	MapObject* arr = static_cast<MapObject*>(data);
	ValueMap& map = arr->getData();
	ValueMap::const_iterator it(map.begin()), end(map.end());

	while (it != end) {
		it->second->delRef();
		++it;
	}

	delete arr;
}

void MapType::dump(const void* value, std::ostream& out) const
{
	Value::DataValue* data = static_cast<Value::DataValue*>(const_cast<void*>(value));
	MapObject* arr = static_cast<MapObject*>(data->obj->getObj());
	ValueMap& map = arr->getData();
	ValueMap::const_iterator it(map.begin()), end(map.end());

	out << "{";

	while (it != end) {
		out << '"' << it->first << '"';
		out << ": ";
		it->second->dump(out);

		++it;

		if (it != end) {
			out << ", ";
		}
	}

	out << "}";
}

// void Map.insert(string key, mixed value)
// Sets the key to value in this map
CLEVER_METHOD(MapType::insert)
{
	if (!clever_check_args("s*")) {
		return;
	}
	
	ValueMap& mapped = (CLEVER_GET_OBJECT(MapObject*, CLEVER_THIS()))->getData();
	mapped.insert(ValuePair(*args[0]->getStr(), args[1]));
	args[1]->addRef();
	result->setNull();
}

// Map.each(function callback)
// Calls the callback with the following prototype: callback(k, v)
// Results returned in a new map
CLEVER_METHOD(MapType::each)
{
	if (!clever_check_args("f")) {
		return;
	}

	Function* func = static_cast<Function*>(args[0]->getObj());
	ValueMap& map = (CLEVER_GET_OBJECT(MapObject*, CLEVER_THIS()))->getData();
	ValueMap::const_iterator it(map.begin()), end(map.end());
	ValueVector results;

	while (it != end) {
		Value* call[3];
		ValueVector fargs;

		call[0] = new Value(CSTRING(it->first));
		call[1] = it->second;

		fargs.push_back(call[0]);
		fargs.push_back(call[1]);

		results.push_back(call[0]);
		results.push_back(call[2] = const_cast<VM*>(vm)->runFunction(func, &fargs));

		++it;
	}

	CLEVER_RETURN_MAP(CLEVER_MAP_TYPE->allocData(&results));

	for (size_t i = 0, j = results.size(); i < j; ++i) {
		results[i]->delRef();
	}
}

// Map.size()
// Returns the number of elements currently mapped
CLEVER_METHOD(MapType::size)
{
	if (!clever_check_no_args()) {
		return;
	}

	CLEVER_RETURN_INT((CLEVER_GET_OBJECT(MapObject*, CLEVER_THIS())->getData()).size());
}

CLEVER_TYPE_INIT(MapType::init)
{
	addMethod(new Function("insert", (MethodPtr) &MapType::insert));
	addMethod(new Function("each",	 (MethodPtr) &MapType::each));
	addMethod(new Function("size",	 (MethodPtr) &MapType::size));
}

} // clever
