/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/type.h"
#include "modules/std/core/function.h"
#include "modules/std/collection/cstack.h"

namespace clever { namespace modules { namespace std {

TypeObject* CStack::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	return new CStackObject;
}

// Stack.Stack()
CLEVER_METHOD(CStack::ctor)
{
	if (!clever_check_no_args()) {
		return;
	}

	result->setObj(this, allocData(&args));
}

// Stack.push()
CLEVER_METHOD(CStack::push)
{
	if (!clever_check_args(".")) {
		return;
	}

	CStackObject* sobj = CLEVER_GET_OBJECT(CStackObject*, CLEVER_THIS());

	sobj->stack.push(args[0]);
}

// Stack.pop()
CLEVER_METHOD(CStack::pop)
{
	if (!clever_check_no_args()) {
		return;
	}

	CStackObject* sobj = CLEVER_GET_OBJECT(CStackObject*, CLEVER_THIS());

	sobj->stack.pop();
}

// Stack.top()
CLEVER_METHOD(CStack::top)
{
	if (!clever_check_no_args()) {
		return;
	}

	CStackObject* sobj = CLEVER_GET_OBJECT(CStackObject*, CLEVER_THIS());

	result->copy(sobj->stack.top());
}

// Stack type initialization
CLEVER_TYPE_INIT(CStack::init)
{
	setConstructor((MethodPtr)&CStack::ctor);

	addMethod(new Function("push", (MethodPtr)&CStack::push));
	addMethod(new Function("pop",  (MethodPtr)&CStack::pop));
	addMethod(new Function("top",  (MethodPtr)&CStack::top));
}

}}} // clever::modules::std
