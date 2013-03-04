/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <ostream>
#include <vector>
#include "core/vm.h"
#include "core/cexception.h"
#include "modules/std/core/function.h"
#include "modules/std/collection/cset.h"

namespace clever { namespace modules { namespace std {

void CSet::dump(TypeObject* value, ::std::ostream& out) const
{
	CSetObject* cobj = static_cast<CSetObject*>(value);
	::std::set<CSetValue>::const_iterator it(cobj->set.begin()), end(cobj->set.end());

	out << "Set<";

	while (it != end) {
		it->element->dump(out);

		if (++it != end) {
			out<< ", ";
		}
	}

	out << ">";
}

TypeObject* CSet::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	return new CSetObject(static_cast<Function*>(args->at(0)->getObj()));
}

bool CSetObjectCompare::operator()(const CSetValue& a, const CSetValue& b) const
{
	::std::vector<Value*> args;

	args.push_back(a.element);
	args.push_back(b.element);

	Value* result = const_cast<VM*>(a.vm)->runFunction(a.comp, &args);

	bool ret = result ? result->asBool() : false;

	clever_delref(result);

	return ret;
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

	result->setObj(this, allocData(&args));
}

// Set.insert(Object element)
CLEVER_METHOD(CSet::insert)
{
	if (!clever_check_args(".")) {
		return;
	}

	CSetObject* cobj = CLEVER_GET_OBJECT(CSetObject*, CLEVER_THIS());

	cobj->set.insert(CSetValue(args[0], cobj->comp, vm));
	clever_addref(args[0]);
}

// Set.size()
CLEVER_METHOD(CSet::size)
{
	if (!clever_check_no_args()) {
		return;
	}

	const CSetObject* cobj = CLEVER_GET_OBJECT(CSetObject*, CLEVER_THIS());

	result->setInt(cobj->set.size());
}

// Set.empty()
CLEVER_METHOD(CSet::empty)
{
	if (!clever_check_no_args()) {
		return;
	}

	const CSetObject* cobj = CLEVER_GET_OBJECT(CSetObject*, CLEVER_THIS());

	result->setBool(cobj->set.empty());
}

// Set.find(Object value)
CLEVER_METHOD(CSet::find)
{
	if (!clever_check_args(".")) {
		return;
	}

	const CSetObject* cobj = CLEVER_GET_OBJECT(CSetObject*, CLEVER_THIS());

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
