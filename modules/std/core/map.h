/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_MAP_H
#define CLEVER_MAP_H

#include <map>
#include <utility>
#include "core/cstring.h"
#include "core/value.h"
#include "core/type.h"

namespace clever {

typedef std::pair<std::string, Value*> MapObjectPair;

class MapObject : public TypeObject{
public:
	MapObject() {}

	MapObject(const ::std::vector<Value*>& args) {
		for (size_t i = 0, j = args.size(); i < j; i += 2) {
			Value* val = new Value();

			val->copy(args[i+1]);

			m_data.insert(ValuePair(*args[i]->getStr(), val));
		}
	}

	~MapObject() {
		ValueMap::const_iterator it(m_data.begin()), end(m_data.end());

		for (; it != end; ++it) {
			clever_delref(it->second);
		}
	}

	std::map<std::string, Value*>& getData() { return m_data; }
private:
	std::map<std::string, Value*> m_data;

	DISALLOW_COPY_AND_ASSIGN(MapObject);
};

class MapType : public Type {
public:
	MapType()
		: Type("Map") {}

	~MapType() {}

	virtual void init();
	virtual std::string toString(TypeObject*) const;

	virtual Value* CLEVER_FASTCALL at_op(CLEVER_TYPE_AT_OPERATOR_ARGS) const;

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(each);
	CLEVER_METHOD(exists);
	CLEVER_METHOD(insert);
	CLEVER_METHOD(size);
private:
	DISALLOW_COPY_AND_ASSIGN(MapType);
};

} // clever

#endif // CLEVER_MAP_H
