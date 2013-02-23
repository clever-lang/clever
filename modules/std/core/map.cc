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

TypeObject* MapType::allocData(CLEVER_TYPE_CTOR_ARGS) const
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

void MapType::dump(TypeObject* value, std::ostream& out) const
{
	MapObject* arr = static_cast<MapObject*>(value);
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

// Map::Map([arg, ...])
CLEVER_METHOD(MapType::ctor)
{
	result->setObj(this, allocData(&args));
}

// Subscript operator
CLEVER_TYPE_AT_OPERATOR(MapType::at_op)
{
	MapObject* mobj = CLEVER_GET_OBJECT(MapObject*, CLEVER_THIS());
	std::map<std::string, Value*>& data = mobj->getData();

	if (!index->isStr()) {
		clever_throw("Invalid map index type");
		return NULL;
	}

	std::map<std::string, Value*>::const_iterator it = data.find(*index->getStr());

	if (it == data.end()) {
		clever_throw("Map index not found!");
		return NULL;
	}
	return it->second;
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

	result->setObj(this, allocData(&results));

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

	result->setInt((CLEVER_GET_OBJECT(MapObject*, CLEVER_THIS())->getData()).size());
}

CLEVER_TYPE_INIT(MapType::init)
{
	setConstructor((MethodPtr) &MapType::ctor);

	addMethod(new Function("insert", (MethodPtr) &MapType::insert));
	addMethod(new Function("each",	 (MethodPtr) &MapType::each));
	addMethod(new Function("size",	 (MethodPtr) &MapType::size));
}

} // clever
