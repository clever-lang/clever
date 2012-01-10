/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "types/type.h"
#include "types/array.h"
#include "compiler/compiler.h"

namespace clever {

CLEVER_TYPE_METHOD(Array::push) {
	ValueVector* vec = CLEVER_THIS()->getVector();

	Value* val = new Value();
	val->copy(CLEVER_ARG(0));

	vec->push_back(val);
}

CLEVER_TYPE_METHOD(Array::pop) {
	ValueVector* vec = CLEVER_THIS()->getVector();

	if (vec->size() > 0) {
		retval->copy(vec->back());
		vec->pop_back();
	}
	else {
		const Type* value_type = ((TemplatedType*)CLEVER_THIS()
			->getTypePtr())->getTypeArg(0);
			
		Compiler::warningf("Popping from a empty Array<%s>! Returning"
			" default value of type %s.",
			value_type->getName(), value_type->getName());
		
		retval->setTypePtr(value_type);
		retval->initialize();
	}
}

CLEVER_TYPE_METHOD(Array::size) {
	ValueVector* vec = CLEVER_THIS()->getVector();

	CLEVER_RETURN_INT(vec->size());
}

CLEVER_TYPE_METHOD(Array::isEmpty) {
	ValueVector* vec = CLEVER_THIS()->getVector();

	CLEVER_RETURN_BOOL(vec->empty());
}

CLEVER_TYPE_METHOD(Array::clear) {
	ValueVector* vec = CLEVER_THIS()->getVector();

	size_t sz = vec->size();
	for (size_t i = 0; i < sz; ++i) {
		vec->at(i)->delRef();
	}

	vec->clear();
}

CLEVER_TYPE_METHOD(Array::at) {
	ValueVector* vec = CLEVER_THIS()->getVector();
	int64_t idx = CLEVER_ARG(0)->getInteger();
	
	if (size_t(idx) < vec->size() && idx >= 0) {
		retval->copy(vec->at(idx));
	}
	else {
		const Type* value_type = ((TemplatedType*)CLEVER_THIS()
			->getTypePtr())->getTypeArg(0);
		
		if (idx >= 0) {	
			Compiler::warningf("Indexing position %l an Array<%s>"
				" with %l elements. Returning default value of type %s.",
				idx, value_type->getName(), vec->size(), 
				value_type->getName());
		}
		else {
			Compiler::warningf("Indexing negative position %l an Array<%s>!"
				" Returning default value of type %s.",
				idx, value_type->getName(), value_type->getName());
		}
		
		retval->setTypePtr(value_type);
		retval->initialize();
	}
}

CLEVER_TYPE_METHOD(Array::set) {
	ValueVector* vec = CLEVER_THIS()->getVector();
	int64_t idx = CLEVER_ARG(0)->getInteger();

	if (size_t(idx) < vec->size() && idx >= 0) {
		Value* val = new Value();
		val->copy(CLEVER_ARG(1));

		vec->at(idx)->delRef();
		vec->at(idx) = val;
	}
	else {
		const Type* value_type = ((TemplatedType*)CLEVER_THIS()
			->getTypePtr())->getTypeArg(0);
		
		if (idx >= 0) {	
			Compiler::warningf("Setting position %l an Array<%s> with %l elements.",
				idx, value_type->getName(), vec->size(), 
				value_type->getName());
		}
		else {
			Compiler::warningf("Setting negative position %l an Array<%s>!",
				idx, value_type->getName(), value_type->getName());
		}
	}
}

CLEVER_TYPE_METHOD(Array::resize) {
	ValueVector* vec = CLEVER_THIS()->getVector();
	int nsz = CLEVER_ARG(0)->getInteger();

	size_t sz = vec->size();
	for (size_t i = 0; i < sz; ++i) {
		vec->at(i)->delRef();
	}

	vec->resize(nsz);

	for (int i = 0; i < nsz; ++i) {
		vec->at(i) = new Value();
		vec->at(i)->copy(CLEVER_ARG(1));
	}
}

CLEVER_TYPE_METHOD(Array::toString) {
	ValueVector* vec = CLEVER_THIS()->getVector();
	std::string ret = "[", sep = ", ";

	for (unsigned int i = 0, j = vec->size(); i < j; ++i) {
		ret += vec->at(i)->toString();
		if (i+1 < j) {
			ret += sep;
		}
	}
	ret += "]";

	CLEVER_RETURN_STR(CSTRING(ret));
}

void Array::init() {
	/* If we are in our "virtual" Array type */
	if (CLEVER_TPL_ARG(0) == NULL) {
		return;
	}

	addMethod(new Method("toString", (MethodPtr)&Array::toString, CLEVER_STR));

	addMethod(
		(new Method("push", (MethodPtr)&Array::push, CLEVER_VOID))
			->addArg("arg1", CLEVER_TPL_ARG(0))
	);

	addMethod(
		new Method("pop", (MethodPtr)&Array::pop, CLEVER_TPL_ARG(0))
	);

	addMethod(new Method("size", (MethodPtr)&Array::size, CLEVER_INT));

	addMethod(new Method("isEmpty", (MethodPtr)&Array::isEmpty, CLEVER_BOOL));

	addMethod(new Method("clear", (MethodPtr)&Array::clear, CLEVER_VOID));

	addMethod((new Method("at", (MethodPtr)&Array::at, CLEVER_TPL_ARG(0)))
		->addArg("index", CLEVER_INT)
	);

	addMethod((new Method("set", (MethodPtr)&Array::set, CLEVER_VOID))
		->addArg("index", CLEVER_INT)
		->addArg("element", CLEVER_TPL_ARG(0))
	);

	addMethod((new Method("resize", (MethodPtr)&Array::resize, CLEVER_VOID))
		->addArg("new_size", CLEVER_INT)
		->addArg("value", CLEVER_TPL_ARG(0))
	);
}

DataValue* Array::allocateValue() const {
	return NULL;
}

} // clever
