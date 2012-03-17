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
#include "modules/std/rpc/rpcobject.h"
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std { namespace rpc {

/**
 * RPC::constructor()
 */
CLEVER_METHOD(RPC::constructor) {
	RPCValue* sv = new RPCValue;

	CLEVER_RETURN_DATA_VALUE(sv);
}

/**
 * Void RPC::operator=(RPC object)
 */
CLEVER_METHOD(RPC::do_assign) {
	value->setDataValue(CLEVER_ARG_DATA_VALUE(0));
}

CLEVER_METHOD(RPC::client) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	CLEVER_RETURN_BOOL(rv->createClient(CLEVER_ARG_STR(0).c_str(), CLEVER_ARG_INT(1), CLEVER_ARG_INT(2)));
}

CLEVER_METHOD(RPC::server) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	rv->createServer(CLEVER_ARG_INT(0), CLEVER_ARG_INT(1));
}

CLEVER_METHOD(RPC::sendString) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	rv->sendString(CLEVER_ARG_STR(0).c_str(), CLEVER_ARG_STR(0).size());
}

CLEVER_METHOD(RPC::loadLibrary) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	rv->loadLibrary(CLEVER_ARG_STR(0).c_str());
}

CLEVER_METHOD(RPC::addFunction) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	rv->addFunction(CLEVER_ARG_STR(0).c_str(), CLEVER_ARG_STR(1).c_str(), CLEVER_ARG_STR(2).c_str());
}

CLEVER_METHOD(RPC::sendInteger) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	rv->sendInteger(CLEVER_ARG_INT(0));
}

CLEVER_METHOD(RPC::sendKill) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	rv->sendKill();
}

CLEVER_METHOD(RPC::sendInit) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);

	CLEVER_RETURN_BOOL(rv->sendInit());
}

CLEVER_METHOD(RPC::callFunction) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);
	size_t size = CLEVER_NUM_ARGS();
	const char* fname = CLEVER_ARG_STR(0).c_str();
	int len_fname = CLEVER_ARG_STR(0).size();
	int n_args = size-1;
	int len_args = 0;

	for(size_t i=1;i<size;++i){
		len_args+=sizeof(char);
		if (CLEVER_ARG_IS_INT(i)) {
			len_args+=sizeof(int);
		} else if (CLEVER_ARG_IS_BOOL(i)) {
			len_args+=sizeof(char);
		} else if (CLEVER_ARG_IS_STR(i)) {
			len_args+=sizeof(int);
			len_args+=CLEVER_ARG_STR(i).size();
		} else if (CLEVER_ARG_IS_BYTE(i)) {
			len_args+=sizeof(char);
		} else if (CLEVER_ARG_IS_DOUBLE(i)) {
			len_args+=sizeof(double);
		} else if ( CLEVER_ARG_IS_USER(i) ) {
		}
	}

	char* buffer = static_cast<char*>(malloc(len_args+1));

	len_args=0;
	for(size_t i=1;i<size;++i){
		if (CLEVER_ARG_IS_INT(i)) {
			buffer[len_args]='i';
			len_args+=sizeof(char);

			int vi = CLEVER_ARG_INT(i);

			memcpy(buffer+len_args,&vi,sizeof(int));
			len_args+=sizeof(int);

		} else if (CLEVER_ARG_IS_BOOL(i)) {
			buffer[len_args]='b';
			len_args+=sizeof(char);

			char vb = CLEVER_ARG_BOOL(i);

			memcpy(buffer+len_args,&vb,sizeof(char));
			len_args+=sizeof(char);

		} else if (CLEVER_ARG_IS_STR(i)) {
			buffer[len_args]='s';
			len_args+=sizeof(char);

			int len=(int)(CLEVER_ARG_STR(i).size());
			const char* s=CLEVER_ARG_STR(i).c_str();
			
			memcpy(buffer+len_args,&len,sizeof(int));
			
			len_args+=sizeof(int);

			memcpy(buffer+len_args,s,len);
			len_args+=len;

		} else if (CLEVER_ARG_IS_BYTE(i)) {
			buffer[len_args]='c';
			len_args+=sizeof(char);

			char vb = CLEVER_ARG_BOOL(i);

			memcpy(buffer+len_args,&vb,sizeof(char));
			len_args+=sizeof(char);
		} else if (CLEVER_ARG_IS_DOUBLE(i)) {
			buffer[len_args]='d';
			len_args+=sizeof(char);

			double vd = CLEVER_ARG_DOUBLE(i);

			memcpy(buffer+len_args,&vd,sizeof(double));
			len_args+=sizeof(double);
		} else if ( CLEVER_ARG_IS_USER(i) ) {
		}
	}

	rv->sendFunctionCall(fname,buffer,len_fname,n_args,len_args);
	free(buffer);

	CLEVER_RETURN_DATA_VALUE(rv->receiveObject());
}

CLEVER_METHOD(RPC::callProcess) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);
	size_t size = CLEVER_NUM_ARGS();
	int id_process = CLEVER_ARG_INT(0);
	const char* fname = CLEVER_ARG_STR(1).c_str();
	int len_fname = CLEVER_ARG_STR(1).size();
	int n_args = size-2;
	int len_args = 0;

	for(size_t i=2;i<size;++i){
		len_args+=sizeof(char);
		if (CLEVER_ARG_IS_INT(i)) {
			len_args+=sizeof(int);
		} else if (CLEVER_ARG_IS_BOOL(i)) {
			len_args+=sizeof(char);
		} else if (CLEVER_ARG_IS_STR(i)) {
			len_args+=sizeof(int);
			len_args+=CLEVER_ARG_STR(i).size();
		} else if (CLEVER_ARG_IS_BYTE(i)) {
			len_args+=sizeof(char);
		} else if (CLEVER_ARG_IS_DOUBLE(i)) {
			len_args+=sizeof(double);
		} else if ( CLEVER_ARG_IS_USER(i) ) {
		}
	}

	char* buffer = static_cast<char*>(malloc(len_args+1));

	len_args=0;
	for(size_t i=2;i<size;++i){
		if (CLEVER_ARG_IS_INT(i)) {
			buffer[len_args]='i';
			len_args+=sizeof(char);

			int vi = CLEVER_ARG_INT(i);

			memcpy(buffer+len_args,&vi,sizeof(int));
			len_args+=sizeof(int);

		} else if (CLEVER_ARG_IS_BOOL(i)) {
			buffer[len_args]='b';
			len_args+=sizeof(char);

			char vb = CLEVER_ARG_BOOL(i);

			memcpy(buffer+len_args,&vb,sizeof(char));
			len_args+=sizeof(char);

		} else if (CLEVER_ARG_IS_STR(i)) {
			buffer[len_args]='s';
			len_args+=sizeof(char);

			int len=(int)(CLEVER_ARG_STR(i).size());
			const char* s=CLEVER_ARG_STR(i).c_str();
			
			memcpy(buffer+len_args,&len,sizeof(int));
			
			len_args+=sizeof(int);

			memcpy(buffer+len_args,s,len);
			len_args+=len;

		} else if (CLEVER_ARG_IS_BYTE(i)) {
			buffer[len_args]='c';
			len_args+=sizeof(char);

			char vb = CLEVER_ARG_BOOL(i);

			memcpy(buffer+len_args,&vb,sizeof(char));
			len_args+=sizeof(char);
		} else if (CLEVER_ARG_IS_DOUBLE(i)) {
			buffer[len_args]='d';
			len_args+=sizeof(char);

			double vd = CLEVER_ARG_DOUBLE(i);

			memcpy(buffer+len_args,&vd,sizeof(double));
			len_args+=sizeof(double);
		} else if ( CLEVER_ARG_IS_USER(i) ) {
		}
	}

	rv->sendProcessCall(id_process,fname,buffer,len_fname,n_args,len_args);
	free(buffer);
}

CLEVER_METHOD(RPC::waitResult) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);
	int id_process = CLEVER_ARG_INT(0);
	double time_sleep = CLEVER_ARG_DOUBLE(1);

	CLEVER_RETURN_DATA_VALUE(rv->getResultProcess(id_process, time_sleep));
}

CLEVER_METHOD(RPC::sendMsgInt) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);
	int id_message = CLEVER_ARG_INT(0);
	int v = CLEVER_ARG_INT(1);

	rv->sendInteger(id_message, v);
}

CLEVER_METHOD(RPC::recvMsgInt) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);
	int id_message = CLEVER_ARG_INT(0);
	double time_sleep = CLEVER_ARG_DOUBLE(1);

	CLEVER_RETURN_INT(rv->receiveInt(id_message, time_sleep));
}

CLEVER_METHOD(RPC::sendMsgDouble) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);
	int id_message = CLEVER_ARG_INT(0);
	double v = CLEVER_ARG_DOUBLE(1);

	rv->sendDouble(id_message, v);
}

CLEVER_METHOD(RPC::recvMsgDouble) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);
	int id_message = CLEVER_ARG_INT(0);
	double time_sleep = CLEVER_ARG_DOUBLE(1);

	CLEVER_RETURN_DOUBLE(rv->receiveDouble(id_message, time_sleep));
}


CLEVER_METHOD(RPC::sendMsgString) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);
	int id_message = CLEVER_ARG_INT(0);
	::std::string v = CLEVER_ARG_STR(1);

	rv->sendString(id_message, v.c_str(),v.size());
}

CLEVER_METHOD(RPC::recvMsgString) {
	RPCValue* rv = CLEVER_GET_VALUE(RPCValue*, value);
	int id_message = CLEVER_ARG_INT(0);
	double time_sleep = CLEVER_ARG_DOUBLE(1);

	CLEVER_RETURN_STR(CSTRING(rv->receiveString(id_message, time_sleep)));
}


void RPC::init() {
	const Type* rpcobj = CLEVER_TYPE("RPCClass");
	const Type* rpcobjvalue = CLEVER_TYPE("RPCObject");

	addMethod(new Method(CLEVER_CTOR_NAME,
		(MethodPtr)&RPC::constructor, rpcobj));

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&RPC::do_assign,
			rpcobj, false))
			->addArg("rvalue", rpcobj)
	);

	addMethod(
		(new Method("client", (MethodPtr)&RPC::client, CLEVER_BOOL))
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
		(new Method("loadLibrary", (MethodPtr)&RPC::loadLibrary, CLEVER_VOID))
			->addArg("libname", CLEVER_STR)
	);

	addMethod(
		(new Method("addFunction", (MethodPtr)&RPC::addFunction, CLEVER_VOID))
			->addArg("libname", CLEVER_STR)
			->addArg("funcname", CLEVER_STR)
			->addArg("rettype", CLEVER_STR)
	);

	addMethod(
		(new Method("sendString", (MethodPtr)&RPC::sendString, CLEVER_VOID))
			->addArg("value", CLEVER_STR)
	);

	addMethod(
		(new Method("sendInteger", (MethodPtr)&RPC::sendInteger, CLEVER_VOID))
			->addArg("value", CLEVER_INT)
	);

	addMethod(
		(new Method("sendMsgInt", (MethodPtr)&RPC::sendMsgInt, CLEVER_VOID))
			->addArg("id_message", CLEVER_INT)
			->addArg("value", CLEVER_INT)
	);

	addMethod(
		(new Method("recvMsgInt", (MethodPtr)&RPC::recvMsgInt, CLEVER_INT))
			->addArg("id_message", CLEVER_INT)
			->addArg("time_sleep", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method("sendMsgDouble", (MethodPtr)&RPC::sendMsgDouble, CLEVER_VOID))
			->addArg("id_message", CLEVER_INT)
			->addArg("value", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method("recvMsgDouble", (MethodPtr)&RPC::recvMsgDouble, CLEVER_DOUBLE))
			->addArg("id_message", CLEVER_INT)
			->addArg("time_sleep", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method("sendMsgString", (MethodPtr)&RPC::sendMsgString, CLEVER_VOID))
			->addArg("id_message", CLEVER_INT)
			->addArg("value", CLEVER_STR)
	);

	addMethod(
		(new Method("recvMsgString", (MethodPtr)&RPC::recvMsgString, CLEVER_STR))
			->addArg("id_message", CLEVER_INT)
			->addArg("time_sleep", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method("sendKill", (MethodPtr)&RPC::sendKill, CLEVER_VOID))
	);

	addMethod(
		(new Method("sendInit", (MethodPtr)&RPC::sendInit, CLEVER_BOOL))
	);

	addMethod(
		(new Method("callFunction", (MethodPtr)&RPC::callFunction, rpcobjvalue))
			->setVariadic()
			->setMinNumArgs(1)
	);

	addMethod(
		(new Method("callProcess", (MethodPtr)&RPC::callProcess, CLEVER_VOID))
			->setVariadic()
			->setMinNumArgs(2)
	);

	addMethod(
		(new Method("waitResult", (MethodPtr)&RPC::waitResult, rpcobjvalue))
			->addArg("id", CLEVER_INT)
			->addArg("time_sleep", CLEVER_DOUBLE)
	);

}

DataValue* RPC::allocateValue() const {
	return new RPCValue;
}

void RPC::destructor(Value* value) const {
}

}}}} // clever::packages::std::rpc


