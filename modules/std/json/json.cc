/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/value.h"
#include "core/type.h"
#include "modules/std/core/array.h"
#include "modules/std/json/json.h"

namespace clever { namespace modules { namespace std {

namespace json {

namespace detail {

::std::string escape(const ::std::string& str) {
	::std::ostringstream oss;

	for (int i = 0, sz = str.size(); i < sz; ++i) {
		switch (str[i]) {
			case '\b': {
				oss << "\\b";
				break;
			}
			case '\f': {
				oss << "\\f";
				break;
			}
			case '\n': {
				oss << "\\n";
				break;
			}
			case '\r': {
				oss << "\\r";
				break;
			}
			case '\t': {
				oss << "\\t";
				break;
			}
			case '\'': {
				oss << "\\'";
				break;
			}
			case '"': {
				oss << "\\\"";
				break;
			}
			case '\\': {
				oss << "\\\\";
				break;
			}
			default: {
				oss << str[i];
			}
		}
	}

	return oss.str();
}

void array_to_json(::std::ostringstream& oss, const Value* array);

void to_json_impl(::std::ostringstream& oss, const Value* object) {
	const MemberMap& members = object->getObj()->getMembers();
	MemberMap::const_iterator it(members.begin()), end(members.end());
	const Value* value;
	const CString* key;
	bool first = true;

	while (it != end) {
		key = it->first;
		value = it->second.value;
		if (!value->isFunction()) {
			if (!first) {
				oss << ", ";
			}
			first = false;

			oss << *key << ": ";
			if (value->isInt() || value->isStr() || value->isDouble()
				|| value->isBool() || value->isMap()) {
				oss << "\"" << detail::escape(value->toString()) << "\"";
			}
			else if (value->isArray()) {
				oss << "[";
				array_to_json(oss, value);
				oss << "]";
			}
			else {
				oss << "{";
				to_json_impl(oss, value);
				oss << "}";
			}
		}
		++it;
	}
}

void array_to_json(::std::ostringstream& oss, const Value* array) {
	ValueVector& arr = clever_get_object(ArrayObject*, array)->getData();
	bool first = true;

	for (int i = 0, sz = arr.size(); i < sz; ++i) {
		if (!arr[i]->isFunction()) {
			if (!first) {
				oss << ", ";
			}
			if (arr[i]->isInt() || arr[i]->isStr() || arr[i]->isDouble()
				|| arr[i]->isBool() || arr[i]->isMap()) {
				oss << "\"" << detail::escape(arr[i]->toString()) << "\"";
			} else if (arr[i]->isArray()) {
				oss << "[";
				array_to_json(oss, arr[i]);
				oss << "]";
			} else {
				oss << "{";
				to_json_impl(oss, arr[i]);
				oss << "}";
			}
			first = false;
		}
	}
}

} // clever::modules::std::json::detail

// to_json(Object object)
static CLEVER_FUNCTION(to_json)
{
	if (!clever_static_check_args(".")) {
		return;
	}

	::std::ostringstream oss;

	oss << "{";
	detail::to_json_impl(oss, args[0]);
	oss << "}";

	result->setStr(new StrObject(oss.str()));
}

} // clever::modules::std::json

/// Initializes Standard Json module
CLEVER_MODULE_INIT(JsonModule)
{
	addFunction(new Function("to_json", &CLEVER_NS_FNAME(json, to_json)));
}

}}} // clever::modules::std
