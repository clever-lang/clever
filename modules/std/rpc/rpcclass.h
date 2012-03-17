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

#ifndef CLEVER_RPC_CLASS_H
#define CLEVER_RPC_CLASS_H

#include "types/type.h"
#include "compiler/value.h"
#include "compiler/module.h"
#include "modules/std/rpc/rpcvalue.h"

namespace clever { namespace packages { namespace std { namespace rpc {

//RPC class definition

class RPC : public Type {
public:
	RPC()
		: Type(CSTRING("RPCClass")) { }

	void init();
	DataValue* allocateValue() const;
	void destructor(Value* value) const;

	static CLEVER_METHOD(constructor);
	static CLEVER_METHOD(do_assign);
	static CLEVER_METHOD(client);
	static CLEVER_METHOD(server);
	static CLEVER_METHOD(loadLibrary);
	static CLEVER_METHOD(addFunction);
	static CLEVER_METHOD(sendString);
	static CLEVER_METHOD(sendInteger);
	static CLEVER_METHOD(sendKill);
	static CLEVER_METHOD(sendInit);
	static CLEVER_METHOD(callFunction);
	static CLEVER_METHOD(callProcess);
	static CLEVER_METHOD(waitResult);

	static CLEVER_METHOD(sendMsgInt);
	static CLEVER_METHOD(recvMsgInt);

	static CLEVER_METHOD(sendMsgDouble);
	static CLEVER_METHOD(recvMsgDouble);

	static CLEVER_METHOD(sendMsgString);
	static CLEVER_METHOD(recvMsgString);

	static CLEVER_METHOD(sendMsgObject);
	static CLEVER_METHOD(recvMsgObject);

	~RPC(){}
private:
	DISALLOW_COPY_AND_ASSIGN(RPC);
};

}}}} // clever::packages::std::rpc


#endif //CLEVER_RPC_CLASS_H
