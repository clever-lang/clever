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

#include "compiler/value.h"
#include "modules/std/net/net.h"
#include "modules/std/net/tcpsocket.h"
#include "modules/std/rpc/rpc.h"
#include "modules/std/rpc/rpcclass.h"
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std { namespace rpc {

/**
 * RPC::constructor()
 */
CLEVER_METHOD(RPC::constructor) {
}

/**
 * Void RPC::operator=(RPC object)
 */
CLEVER_METHOD(RPC::do_assign) {

}

CLEVER_METHOD(RPC::client) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	rv->createClient(CLEVER_ARG_STR(0).c_str(), CLEVER_ARG_INT(1), CLEVER_ARG_INT(2));
}

CLEVER_METHOD(RPC::server) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	rv->createServer(CLEVER_ARG_INT(0), CLEVER_ARG_INT(1));
}

CLEVER_METHOD(RPC::sendString) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	rv->sendString(CLEVER_ARG_STR(0).c_str(), CLEVER_ARG_STR(0).size());
}

CLEVER_METHOD(RPC::sendInteger) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	rv->sendInteger(CLEVER_ARG_INT(0));
}

void RPC::init() {
	const Type* rpcobj = CLEVER_TYPE("RPCClass");

	addMethod(new Method(CLEVER_CTOR_NAME,
		(MethodPtr)&RPC::constructor, rpcobj));

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&RPC::do_assign,
			rpcobj, false))
			->addArg("rvalue", rpcobj)
	);

	addMethod(
		(new Method("client", (MethodPtr)&RPC::client, CLEVER_VOID))
			->addArg("host", CLEVER_STR)
			->addArg("port", CLEVER_INT)
			->addArg("time", CLEVER_INT)
	);

	addMethod(
		(new Method("server", (MethodPtr)&RPC::server, CLEVER_VOID))
			->addArg("port", CLEVER_INT)
			->addArg("nconnections", CLEVER_INT)
	);

	addMethod(
		(new Method("sendString", (MethodPtr)&RPC::sendString, CLEVER_VOID))
			->addArg("value", CLEVER_STR)
	);

	addMethod(
		(new Method("sendInteger", (MethodPtr)&RPC::sendInteger, CLEVER_VOID))
			->addArg("value", CLEVER_INT)
	);

}

DataValue* RPC::allocateValue() const {
	return new RPCValue;
}

void RPC::destructor(Value* value) const {
}

}}}} // clever::packages::std::rpc


