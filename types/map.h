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

#ifndef CLEVER_MAP_H
#define CLEVER_MAP_H

#include "types/type.h"
#include "compiler/value.h"
#include "compiler/scope.h"
#include "mapvalue.h"
#include "mapiterator.h"

namespace clever {

class Map : public TemplatedType {
public:
	Map()
		: TemplatedType(CSTRING("Map"), CLEVER_OBJECT) {
		addArg(NULL);
		
		Type* map_iter = new MapIterator;
		g_scope.pushType(CSTRING("MapIterator"), map_iter);
		map_iter->init();
	}

	Map(const CString* name, const Type* key_type, const Type* value_type,
		const Type* comparator_type) : TemplatedType(name, CLEVER_OBJECT) {

			addArg(key_type);
			addArg(value_type);

			if (comparator_type) {
				addArg(comparator_type);
			}
	}

	virtual const std::string* checkTemplateArgs(const TemplateArgs& args) const {
		if (args.size() < 2 || args.size() > 3) {
			std::ostringstream oss;
			sprintf(oss, "Wrong number of template arguments given. "
				"`%S' requires 2 or 3 arguments and %l was given.",
				this->getName(), args.size()
			);

			return new std::string(oss.str());
		}

		TypeVector tv(2, args.at(0));

		if (args.size() == 2) {
			const Method* method = args.at(0)->getMethod(
				CACHE_PTR(CLEVER_OP_LESS, CLEVER_OPERATOR_LESS), &tv);
			if (!method || method->getReturnType() != CLEVER_BOOL) {
				std::ostringstream oss;
				sprintf(oss, "Unable to instantiate the type Map<Key = %S, Value = %S> because"
					" the Key type doesn't have the proper operator < defined.",
					args.at(0)->getName(), args.at(1)->getName()
				);
				return new std::string(oss.str());
			}
			return NULL;
		}

		const Method* method = args.at(2)->getMethod(CSTRING("compare"), &tv);
		if (!method || method->getReturnType() != CLEVER_BOOL) {
			std::ostringstream oss;
			sprintf(oss, "Unable to instantiate the type "
				"Map<Key = %S, Value = %S, Comparator = %S> because"
				" the Comparator type doesn't have the method Bool %S::compare(%S, %S) defined.",
				args.at(0)->getName(), args.at(1)->getName(),
				args.at(2)->getName(), args.at(2)->getName(),
				args.at(0)->getName(), args.at(0)->getName()
			);

			return new std::string(oss.str());
		}

		return NULL;
	}

	virtual const Type* getTemplatedType(const TemplateArgs& args) const {
		std::string name = getName()->str() + "<"
			+ args[0]->getName()->str() + ", "
			+ args[1]->getName()->str();

		if (args.size() == 2) {
			name += ">";
		}
		else {
			name += ", ";
			name += args[2]->getName()->str();
			name += ">";
		}

		const CString* cname = CSTRING(name);
		const Type* type = g_scope.getType(cname);

		if (type == NULL) {
			const Type* comp = (args.size() == 3 ? args[2] : NULL);
			Type* ntype = new Map(cname, args[0], args[1], comp);
			g_scope.pushType(cname, ntype);
			ntype->init();

			return ntype;
		}

		return type;
	}

	virtual const Type* getTemplatedType(const Type* key_type, const Type* value_type) const {
		TemplateArgs tmp;
		tmp.push_back(key_type);
		tmp.push_back(value_type);

		return getTemplatedType(tmp);
	}

	void init();
	DataValue* allocateValue() const;

	void destructor(Value* value) const {
		MapValue* map = CLEVER_GET_VALUE(MapValue*, value);
		MapValue::Iterator it = map->getMap().begin(),
			end = map->getMap().end();

		while (it != end) {
			it->first->delRef();
			it->second->delRef();
			++it;
		}
	}

	/**
	 * Type methods
	 */
	static CLEVER_METHOD(do_assign);
	static CLEVER_METHOD(size);
	static CLEVER_METHOD(insert);
	static CLEVER_METHOD(clear);
	static CLEVER_METHOD(isEmpty);
	static CLEVER_METHOD(toString);
	static CLEVER_METHOD(hasKey);
	static CLEVER_METHOD(getKeys);
	static CLEVER_METHOD(getValues);
	static CLEVER_METHOD(getAll);
	static CLEVER_METHOD(begin);
	static CLEVER_METHOD(end);
	static CLEVER_METHOD(constructor);
	static CLEVER_METHOD(at);
private:
	DISALLOW_COPY_AND_ASSIGN(Map);
};

} // clever

#endif // CLEVER_MAP_H
