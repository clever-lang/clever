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

#ifndef CLEVER_PAIR_H
#define CLEVER_PAIR_H

#include "types/type.h"
#include "compiler/value.h"
#include "compiler/scope.h"
#include "pairvalue.h"

namespace clever {

class Pair : public TemplatedType {
public:
	Pair()
		: TemplatedType(CSTRING("Pair"), CLEVER_OBJECT) {
		addArg(NULL);
	}

	Pair(const CString* name, const Type* t1, const Type* t2) 
		: TemplatedType(name, CLEVER_OBJECT) {
			addArg(t1);
			addArg(t2);
	}

	virtual const std::string* checkTemplateArgs(const TemplateArgs& args) const {
		return NULL;
	}

	virtual const Type* getTemplatedType(const TemplateArgs& args) const {
		std::string name = getName()->str() + "<"
			+ args[0]->getName()->str() + ", "
			+ args[1]->getName()->str() + ">";

		const CString* cname = CSTRING(name);
		const Type* type = g_scope.getType(cname);

		if (type == NULL) {
			Type* ntype = new Pair(cname, args[0], args[1]);
			g_scope.pushType(cname, ntype);
			ntype->init();

			return ntype;
		}

		return type;
	}

	virtual const Type* getTemplatedType(const Type* t1, const Type* t2) const {
		TemplateArgs tmp;
		tmp.push_back(t1);
		tmp.push_back(t2);

		return getTemplatedType(tmp);
	}

	void init();
	DataValue* allocateValue() const;

	void destructor(Value* value) const {
	}

	/**
	 * Type methods
	 */
	static CLEVER_METHOD(constructor);
	static CLEVER_METHOD(do_assign);
	static CLEVER_METHOD(first);
	static CLEVER_METHOD(second);
	static CLEVER_METHOD(setFirst);
	static CLEVER_METHOD(setSecond);
	static CLEVER_METHOD(toString);
	static CLEVER_METHOD(equal);
private:
	DISALLOW_COPY_AND_ASSIGN(Pair);
};

} // clever

#endif // CLEVER_PAIR_H
