/**
 * Clever programming language
 * Copyright (c) 2012 Clever Team
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

#ifndef CLEVER_TCPSOCKET_H
#define CLEVER_TCPSOCKET_H

#include "types/type.h"
#include "compiler/value.h"
#include "modules/std/net/socketvalue.h"

namespace clever { namespace packages { namespace std { namespace net {

class TcpSocket : public Type {
public:
	TcpSocket() :
		Type(CSTRING("TcpSocket")) { }

	void init();
	DataValue* allocateValue() const;
	void destructor(Value* value) const;

	/**
	 * Type methods
	 */
	static CLEVER_METHOD(constructor);
	static CLEVER_METHOD(setHost);
	static CLEVER_METHOD(setPort);
	static CLEVER_METHOD(setTimeout);
	static CLEVER_METHOD(connect);
	static CLEVER_METHOD(receive);
	static CLEVER_METHOD(send);
	static CLEVER_METHOD(poll);
	static CLEVER_METHOD(toString);
	static CLEVER_METHOD(do_assign);
private:
	DISALLOW_COPY_AND_ASSIGN(TcpSocket);
};

}}}} // clever::packages::std::net

#endif // CLEVER_TCPSOCKET_H
