/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
 *
 * $Id$
 */

#ifndef CLEVER_TYPES_H
#define CLEVER_TYPES_H

#include <stdint.h>
#include <iostream>
#include <sstream>
#include <string>
#include "config.h"
#include "refcounted.h"
#include "cstring.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);             \
	void operator=(const TypeName&)

namespace clever {

class Type {
public:
	enum {
		ABSTRACT  = 0,
		CONCRETE  = 1,
		INTERFACE = 2,
		BUILT_IN  = 4
	};

	Type(const std::string& name, int kind)
		: m_name(name), m_kind(kind) {};
	Type(const std::string& package, const std::string& name, int kind)
		: m_package(name), m_name(name), m_kind(kind) {};

	virtual ~Type();

	virtual void Init();

	inline std::string package() const { return m_package; };
	inline std::string name() const { return m_name; };
	inline bool isInterface() const { return m_kind & INTERFACE; };
	inline bool isAbstract() const { return m_kind & ABSTRACT; };
	inline bool isConcrete() const { return m_kind & ABSTRACT; };
	inline bool isBuilt_in() const { return m_kind & BUILT_IN; };

private:
	Type() {};
	DISALLOW_COPY_AND_ASSIGN(Type);

	std::string m_package;
	std::string m_name;
	int m_kind;
};

} // Clever

#endif // CLEVER_TYPES_H
