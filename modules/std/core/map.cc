/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <map>
#include "core/value.h"
#include "core/vm.h"
#include "modules/std/core/map.h"
#include "modules/std/core/function.h"

namespace clever {

std::string MapType::toString(TypeObject* value) const
{
	MapObject* arr = static_cast<MapObject*>(value);
	ValueMap& map = arr->getData();
	ValueMap::const_iterator it(map.begin()), end(map.end());
	std::ostringstream out;

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

	return out.str();
}

// Map::Map([arg, ...])
CLEVER_METHOD(MapType::ctor)
{
	result->setObj(this, new MapObject(args));
}

// Subscript operator
CLEVER_TYPE_AT_OPERATOR(MapType::at_op)
{
	MapObject* mobj = clever_get_this(MapObject*);
	std::map<std::string, Value*>& data = mobj->getData();

	if (!index->isStr()) {
		clever_throw("Invalid map index type");
		return NULL;
	}

	std::map<std::string, Value*>::const_iterator it = data.find(*index->getStr());
	Value* item = NULL;

	if (is_write) {
		if (it == data.end()) {
			item = data[*index->getStr()] = new Value;
		} else {
			item = it->second;
		}
	} else {
		if (it == data.end()) {
			clever_throw("Map index not found!");
			return NULL;
		}
		item = it->second;
	}

	clever_addref(item);

	return item;
}

// void Map.insert(string key, mixed value)
// Sets the key to value in this map
CLEVER_METHOD(MapType::insert)
{
	if (!clever_check_args("s*")) {
		return;
	}

	ValueMap& mapped = clever_get_this(MapObject*)->getData();
	mapped.insert(ValuePair(*args[0]->getStr(), args[1]->clone()));
	result->setNull();
}

// void Map.exists(string key)
// Checks if a key exists in this map
CLEVER_METHOD(MapType::exists)
{
	if (!clever_check_args("s")) {
		return;
	}

	ValueMap& mapped = clever_get_this(MapObject*)->getData();
	result->setBool(mapped.find(*args[0]->getStr()) != mapped.end());
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
	ValueMap& map = clever_get_this(MapObject*)->getData();
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
		results.push_back(call[2] = const_cast<VM*>(clever->vm)->runFunction(func, fargs));

		++it;
	}

	result->setObj(this, new MapObject(results));

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

	result->setInt(clever_get_this(MapObject*)->getData().size());
}

CLEVER_TYPE_INIT(MapType::init)
{
	setConstructor((MethodPtr)&MapType::ctor);

	addMethod(new Function("each",   (MethodPtr)&MapType::each));
	addMethod(new Function("insert", (MethodPtr)&MapType::insert));
	addMethod(new Function("exists", (MethodPtr)&MapType::exists));
	addMethod(new Function("size",   (MethodPtr)&MapType::size));
}

} // clever
