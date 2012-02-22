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

#ifndef CLEVER_MAPVALUE_H
#define CLEVER_MAPVALUE_H

#include <map>
#include "compiler/value.h"

namespace clever {

struct Comparator {
	Comparator(const Method* method, Value* value = NULL)
		: m_comp(method), m_value(value) {
		if (m_value) {
			m_value->addRef();
		}
	}

	~Comparator() {
		if (m_value) {
			m_value->delRef();
		}
	}

	bool operator()(Value* a, Value* b) const {
		ValueVector vv(2);
		vv[0] = a;
		vv[1] = b;

		Value result;

		if (!m_value) {
			m_comp->call(&vv, &result, a);
		}
		else {
			m_comp->call(&vv, &result, m_value);
		}

		return result.getBoolean();
	}

private:
	const Method* m_comp;
	Value* m_value;
};

struct MapValue : public DataValue {
	typedef std::map<Value*, Value*, Comparator> MapInternal;
	typedef MapInternal::iterator Iterator;
	typedef MapInternal ValueType;

	MapValue(const Method* method, Value* value = NULL)
		: m_map(Comparator(method, value)) {
	}

	MapInternal& getMap() {
		return m_map;
	}

	~MapValue() {}
private:
	MapInternal m_map;

	DISALLOW_COPY_AND_ASSIGN(MapValue);
};

} // clever

#endif

