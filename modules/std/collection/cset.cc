/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <ostream>
#include <vector>
#include <algorithm>
#include "core/vm.h"
#include "core/cexception.h"
#include "modules/std/core/function.h"
#include "modules/std/collection/cset.h"

namespace clever { namespace modules { namespace std {

::std::string CSet::toString(TypeObject* value) const
{
	CSetObject* cobj = static_cast<CSetObject*>(value);
	::std::set<CSetValue>::const_iterator it(cobj->set.begin()), end(cobj->set.end());
	::std::ostringstream out;

	out << "Set<";

	while (it != end) {
		it->element->dump(out);

		if (++it != end) {
			out<< ", ";
		}
	}

	out << ">";

	return out.str();
}

bool CSetObjectCompare::operator()(const CSetValue& a, const CSetValue& b) const
{
	::std::vector<Value*> args;

	args.push_back(a.element);
	args.push_back(b.element);

	Value* result = const_cast<VM*>(a.vm)->runFunction(a.comp, args);

	bool ret = result ? result->asBool() : false;

	clever_delref(result);

	return ret;
}

bool operator<(const CSetValue& a, const CSetValue& b)
{
	::std::vector<Value*> args;

	args.push_back(a.element);
	args.push_back(b.element);

	Value* result = const_cast<VM*>(a.vm)->runFunction(a.comp, args);

	bool ret = result ? result->asBool() : false;

	clever_delref(result);

	return ret;
}

CLEVER_TYPE_OPERATOR(CSet::add)
{
	CSetObject* a = clever_get_object(CSetObject*, lhs);
	CSetObject* b = clever_get_object(CSetObject*, rhs);
	CSetObject* c = new CSetObject(a->comp);

	::std::set<CSetValue, CSetObjectCompare>::iterator
			it = a->set.begin(), end = a->set.end();

	while (it != end) {
		c->set.insert(CSetValue(it->element->clone(), it->comp, it->vm));
		++it;
	}

	it = b->set.begin(), end = b->set.end();

	while (it != end) {
		if (c->set.find(CSetValue(it->element, it->comp, it->vm)) == c->set.end()) {
			c->set.insert(CSetValue(it->element->clone(), it->comp, it->vm));
		}
		++it;
	}

	result->setObj(this, c);
}

CLEVER_TYPE_OPERATOR(CSet::mul)
{
	CSetObject* a = clever_get_object(CSetObject*, lhs);
	CSetObject* b = clever_get_object(CSetObject*, rhs);
	CSetObject* c = new CSetObject(a->comp);

	::std::set<CSetValue, CSetObjectCompare>::iterator
			it = a->set.begin(), end = a->set.end();

	while (it != end) {
		if (b->set.find(CSetValue(it->element, it->comp, it->vm)) != b->set.end()) {
			c->set.insert(CSetValue(it->element->clone(), it->comp, it->vm));
		}
		++it;
	}

	result->setObj(this, c);
}

// Set.Set(Function compare)
CLEVER_METHOD(CSet::ctor)
{
	if (!clever_check_args("f")) {
		return;
	}

	const Function* comp = static_cast<Function*>(args[0]->getObj());

	if (comp->getNumRequiredArgs() < 2) {
		clever_throw("Compare function must expect at least two arguments");
		return;
	}

	result->setObj(this,
		new CSetObject(static_cast<Function*>(args[0]->getObj())));
}

// Set.insert(Object element)
CLEVER_METHOD(CSet::insert)
{
	if (!clever_check_args(".")) {
		return;
	}

	CSetObject* cobj = clever_get_this(CSetObject*);

	cobj->set.insert(CSetValue(args[0]->clone(), cobj->comp, vm));
}

// Set.size()
CLEVER_METHOD(CSet::size)
{
	if (!clever_check_no_args()) {
		return;
	}

	const CSetObject* cobj = clever_get_this(CSetObject*);

	result->setInt(cobj->set.size());
}

// Set.empty()
CLEVER_METHOD(CSet::empty)
{
	if (!clever_check_no_args()) {
		return;
	}

	const CSetObject* cobj = clever_get_this(CSetObject*);

	result->setBool(cobj->set.empty());
}

// Set.find(Object value)
CLEVER_METHOD(CSet::find)
{
	if (!clever_check_args(".")) {
		return;
	}

	const CSetObject* cobj = clever_get_this(CSetObject*);

	::std::set<CSetValue, CSetObjectCompare>::const_iterator it(
		cobj->set.find(CSetValue(args[0], cobj->comp, vm)));

	if (it != cobj->set.end()) {
		result->copy(it->element);
	} else {
		result->setBool(false);
	}
}

// Set type initialization
CLEVER_TYPE_INIT(CSet::init)
{
	setConstructor((MethodPtr)&CSet::ctor);

	addMethod(new Function("insert", (MethodPtr)&CSet::insert));
	addMethod(new Function("size",   (MethodPtr)&CSet::size));
	addMethod(new Function("empty",  (MethodPtr)&CSet::empty));
	addMethod(new Function("find",   (MethodPtr)&CSet::find));
}

}}} // clever::modules::std
