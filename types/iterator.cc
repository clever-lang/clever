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
#include "compiler/compiler.h"
#include "types/iterator.h"

namespace clever {

void ForwardIterator::init() {
	addMethod(new Method(CLEVER_OPERATOR_PRE_INC, NULL, this));
	addMethod(new Method(CLEVER_OPERATOR_POS_INC, NULL, this));

	addMethod((new Method(CLEVER_OPERATOR_EQUAL, NULL, this))
		->addArg("arg1", this)
		->addArg("arg2", this)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_NE, NULL, this))
			->addArg("arg1", this)
			->addArg("arg2", this)
	);

	addMethod((new Method("get", NULL, CLEVER_OBJECT)));
}

DataValue* ForwardIterator::allocateValue() const {
	return NULL;
}

void BidirectionalIterator::init() {
	addMethod(new Method(CLEVER_OPERATOR_PRE_DEC, NULL, this));
	addMethod(new Method(CLEVER_OPERATOR_POS_DEC, NULL, this));
}

DataValue* BidirectionalIterator::allocateValue() const {
	return NULL;
}

void RandomAccessIterator::init() {
	addMethod((new Method(CLEVER_OPERATOR_PLUS, NULL, this))
		->addArg("it", this)
		->addArg("offset", this)
	);
	
	addMethod((new Method(CLEVER_OPERATOR_MINUS, NULL, this))
		->addArg("it", this)
		->addArg("offset", this)
	);
	
	addMethod((new Method(CLEVER_OPERATOR_PLUS, NULL, this))
		->addArg("it", this)
		->addArg("offset", CLEVER_INT)
	);
	
	addMethod((new Method(CLEVER_OPERATOR_MINUS, NULL, this))
		->addArg("it", this)
		->addArg("offset", CLEVER_INT)
	);
	
	addMethod((new Method(CLEVER_OPERATOR_LESS, NULL, this))
		->addArg("arg1", this)
		->addArg("arg2", this)
	);
	
	addMethod((new Method(CLEVER_OPERATOR_GREATER, NULL, this))
		->addArg("arg1", this)
		->addArg("arg2", this)
	);
	
	addMethod((new Method(CLEVER_OPERATOR_LE, NULL, this))
		->addArg("arg1", this)
		->addArg("arg2", this)
	);
	
	addMethod((new Method(CLEVER_OPERATOR_GE, NULL, this))
		->addArg("arg1", this)
		->addArg("arg2", this)
	);
}

DataValue* RandomAccessIterator::allocateValue() const {
	return NULL;
}

} // clever
