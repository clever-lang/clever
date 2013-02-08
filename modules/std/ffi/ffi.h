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


#ifndef CLEVER_STD_FFI_H
#define CLEVER_STD_FFI_H


#include <iostream>

#include "core/cstring.h"
#include "types/type.h"

#include <string>
#include <map>

#ifdef CLEVER_APPLE
# define MACOSX
#endif

namespace clever { namespace packages { namespace std {

typedef void* LibHandler;

struct FFIData {
	CString m_lib_name;
	LibHandler m_lib_handler;

	FFIData()
		: m_lib_name(""), m_lib_handler(NULL) {}
};

class FFI : public Type {
public:
	FFI()
		: Type(CSTRING("FFI")) {}

	~FFI() {}

	void dump(const void* data) const;
	void dump(const void* data, ::std::ostream& out) const;

	virtual void increment(Value*, const VM*, CException*) const {}
	virtual void decrement(Value*, const VM*, CException*) const {}

	void init();

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);

	CLEVER_METHOD(ctor);

	CLEVER_METHOD(call);
	CLEVER_METHOD(load);
	CLEVER_METHOD(unload);
};


}}} // clever::packages::std

#endif // CLEVER_STD_FFI_H
