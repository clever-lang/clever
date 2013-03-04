/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_SET_H
#define CLEVER_STD_SET_H

#include <set>
#include "core/type.h"

namespace clever { namespace modules { namespace std {

struct CSetValue {
	CSetValue(Value* elem, const Function* func_, const VM* vm_)
		: element(elem), comp(func_), vm(vm_) {}

	~CSetValue() {}

	Value* element;
	const Function* comp;
	const VM* vm;
};

struct CSetObjectCompare {
	bool operator()(const CSetValue& a, const CSetValue& b) const;
};

struct CSetObject : public TypeObject {
	CSetObject(const Function* func)
		: comp(func) {}

	~CSetObject() {
		::std::set<CSetValue, CSetObjectCompare>::const_iterator it(set.begin()),
			end(set.end());

		for (; it != end; ++it) {
			clever_delref(it->element);
		}
	}

	::std::set<CSetValue, CSetObjectCompare> set;
	const Function* comp;
};

class CSet : public Type {
public:
	CSet()
		: Type("Set") {}

	~CSet() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void dump(TypeObject*, ::std::ostream&) const;

	// Methods
	CLEVER_METHOD(ctor);
	CLEVER_METHOD(insert);
	CLEVER_METHOD(size);
	CLEVER_METHOD(empty);
	CLEVER_METHOD(find);
private:
	DISALLOW_COPY_AND_ASSIGN(CSet);
};

}}} // clever::modules::std

#endif // CLEVER_STD_SET_H
