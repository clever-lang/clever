/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <map>
#include "core/value.h"
#include "types/map.h"

namespace clever {

void* MapType::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	MapObject* arr = new MapObject();
	std::map<std::string, Value*>& map = arr->getData();

	for (size_t i = 0, j = args->size(); i < j; i += 2) {
		Value* val = new Value();

		val->copy(args->at(i+1));

		map.insert(std::pair<std::string, Value*>(*args->at(i)->getStr(), val));
	}

	return arr;
}

void MapType::deallocData(void* data)
{
	MapObject* arr = static_cast<MapObject*>(data);
	std::map<std::string, Value*>& map = arr->getData();
	std::map<std::string, Value*>::const_iterator it(map.begin()), end(map.end());

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
	std::map<std::string, Value*>& map = arr->getData();
	std::map<std::string, Value*>::const_iterator it(map.begin()), end(map.end());

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

CLEVER_METHOD(MapType::insert)
{
	MapObject* mapobj = CLEVER_GET_OBJECT(MapObject*, CLEVER_THIS());

	mapobj->getData().insert(
		std::pair<std::string, Value*>(*args[0]->getStr(), args[1]));

	args[1]->addRef();
}

CLEVER_TYPE_INIT(MapType::init)
{
	addMethod(CSTRING("insert"), (MethodPtr) &MapType::insert);
}

} // clever
