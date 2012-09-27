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

#ifndef CLEVER_MAPITERATOR_H
#define CLEVER_MAPITERATOR_H

#include "types/type.h"
#include "compiler/value.h"
#include "compiler/scope.h"

namespace clever {

class MapIterator : public TemplatedType {
public:
	MapIterator()
		: TemplatedType(CSTRING("MapIterator"), CLEVER_OBJECT) {
		addInterface(g_scope.getType(CSTRING("BidirectionalIterator")));
		addArg(NULL);
	}
	
	MapIterator(const CString* name, const Type* key_type, const Type* value_type)
		: TemplatedType(name, CLEVER_OBJECT) {
		addInterface(g_scope.getType(CSTRING("BidirectionalIterator")));
		addArg(key_type);
		addArg(value_type);
	}
	
 	const std::string* checkTemplateArgs(const TemplateArgs& args) const {
		// @TODO: support for 3 arguments (MapIterator<K, T, Comparator>)
		if (args.size() != 2) {
			std::ostringstream oss;
			sprintf(oss, "Wrong number of template arguments given. "
				"`%S' requires 2 argument and %l was given.",
				this->getName(), args.size()
			);

			return new std::string(oss.str());
		}
		
		return NULL;
	}

	virtual const Type* getTemplatedType(const Type* key_arg, const Type* value_arg) const {
		std::string name = getName()->str() + "<"
						   	+ key_arg->getName()->str() + ", "
							+ value_arg->getName()->str() + ">";

		const CString* cname = CSTRING(name);
		const Type* type = g_scope.getType(cname);

		if (type == NULL) {
			Type* ntype = new MapIterator(cname, key_arg, value_arg);
			g_scope.pushType(cname, ntype);
			ntype->init();

			return ntype;
		}

		return type;
	}
	
	virtual const Type* getTemplatedType(const TemplateArgs& args) const {
		// @TODO: support for 3 arguments (MapIterator<K, T, Comparator>)
		std::string name = getName()->str() + "<"
			+ args[0]->getName()->str() + ", "
			+ args[1]->getName()->str() + ">";

		const CString* cname = CSTRING(name);
		const Type* type = g_scope.getType(cname);

		if (type == NULL) {
			Type* ntype = new MapIterator(cname, args[0], args[1]);
			g_scope.pushType(cname, ntype);
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
	static CLEVER_METHOD(do_assign);
	static CLEVER_METHOD(constructor);
	static CLEVER_METHOD(pre_dec);
	static CLEVER_METHOD(pos_dec);
	static CLEVER_METHOD(pre_inc);
	static CLEVER_METHOD(pos_inc);
	static CLEVER_METHOD(equal);
	static CLEVER_METHOD(not_equal);
	static CLEVER_METHOD(isValid);
	static CLEVER_METHOD(get);
private:
	DISALLOW_COPY_AND_ASSIGN(MapIterator);
};

} // clever

#endif // CLEVER_MAPITERATOR_H
