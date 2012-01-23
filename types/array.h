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

#ifndef CLEVER_VECTOR_H
#define CLEVER_VECTOR_H

#include "types/type.h"
#include "compiler/value.h"

namespace clever {

class Array : public TemplatedType {
public:
	Array()
		: TemplatedType(CSTRING("Array"), 1) {
		addArg(NULL);
	}

	Array(const CString* name, const Type* arg_type) :
		TemplatedType(name, 1) {
			addArg(arg_type);
	}

	virtual const Type* getTemplatedType(const Type* type_arg) const {
		::std::string name = getName()->str() + "<"
						   + type_arg->getName()->str() + ">";
		const CString* cname = CSTRING(name);
		const Type* type = g_symtable.getType(cname);

		if (type == NULL) {
			Type* ntype = new Array(cname, type_arg);
			g_symtable.push(cname, ntype);
			ntype->init();

			return ntype;
		}

		return type;
	}

	void init();
	DataValue* allocateValue() const;

	/**
	 * Type methods
	 */
	static CLEVER_METHOD(push);
	static CLEVER_METHOD(pop);
	static CLEVER_METHOD(size);
	static CLEVER_METHOD(isEmpty);
	static CLEVER_METHOD(clear);
	static CLEVER_METHOD(at);
	static CLEVER_METHOD(set);
	static CLEVER_METHOD(resize);
	static CLEVER_METHOD(toString);
	static CLEVER_METHOD(do_assign);
private:
	DISALLOW_COPY_AND_ASSIGN(Array);
};

} // clever

#endif // CLEVER_VECTOR_H
