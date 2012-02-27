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

#include <iostream>
#include <fstream>
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/std/net/tcpsocket.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std { namespace net {

CLEVER_METHOD(TcpSocket::constructor) {
	SocketValue* sv = new SocketValue;

	if (args != NULL) {
		if (CLEVER_NUM_ARGS() == 1) {
			// Host only.
			sv->getSocket()->setHost(CLEVER_ARG_STR(0).c_str());
		} else if (CLEVER_NUM_ARGS() == 2) {
			// Host and port.
			sv->getSocket()->setHost(CLEVER_ARG_STR(0).c_str());
			sv->getSocket()->setPort(CLEVER_ARG_INT(1));
		}
	}

	CLEVER_RETURN_DATA_VALUE(sv);
}

CLEVER_METHOD(TcpSocket::setHost) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	sv->getSocket()->setHost(CLEVER_ARG_STR(0).c_str());
}

CLEVER_METHOD(TcpSocket::setPort) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	sv->getSocket()->setPort(CLEVER_ARG_INT(0));
}

CLEVER_METHOD(TcpSocket::setTimeout) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	sv->getSocket()->setTimeout(CLEVER_ARG_INT(0));
}

CLEVER_METHOD(TcpSocket::connect) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	sv->getSocket()->connect();
}

CLEVER_METHOD(TcpSocket::close) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	sv->getSocket()->close();
}

CLEVER_METHOD(TcpSocket::receive) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);
	ValueVector* vv = new ValueVector;
	char *buffer;
	int length;

	length = CLEVER_ARG_INT(0);

	// Allocate the buffer.
	buffer = new char[length];
	memset(buffer, 0, length);

	// Receive the data.
	sv->getSocket()->receive(buffer, length);

	for (int i = 0; i < length; ++i) {
		Value *v = new Value();
		v->setByte(buffer[i]);
		vv->push_back(v);
	}

	// Free the buffer.
	delete buffer;

	retval->setTypePtr(CLEVER_TYPE("Array<Byte>"));
	CLEVER_RETURN_ARRAY(vv);
}

CLEVER_METHOD(TcpSocket::send) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);
	ValueVector *vv = CLEVER_ARG_ARRAY(0);
	char *buffer;
	int bufferSize;

	// Allocate a buffer and fill it with the bytes from the array.
	buffer = new char[vv->size()];
	for (size_t i = 0, j = vv->size(); i < j; ++i) {
		buffer[i] = static_cast<char>(vv->at(i)->getByte());
	}
	bufferSize = vv->size();

	// Send the data.
	sv->getSocket()->send(buffer, bufferSize);

	// Free the buffer.
	delete buffer;
}

CLEVER_METHOD(TcpSocket::isOpen) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	CLEVER_RETURN_BOOL(sv->getSocket()->isOpen());
}

CLEVER_METHOD(TcpSocket::poll) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	CLEVER_RETURN_BOOL(sv->getSocket()->poll());
}

CLEVER_METHOD(TcpSocket::good) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	CLEVER_RETURN_BOOL(sv->getSocket()->getError() == NO_ERROR);
}

CLEVER_METHOD(TcpSocket::getError) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	CLEVER_RETURN_INT(sv->getSocket()->getError());
}

CLEVER_METHOD(TcpSocket::getErrorMessage) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	CLEVER_RETURN_STR(CSTRINGT(sv->getSocket()->getErrorString()));
}

CLEVER_METHOD(TcpSocket::toString) {
	CLEVER_RETURN_STR(CSTRINGT("TcpSocket class"));
}

/**
 * Void TcpSocket::__assign__(TcpSocket)
 */
CLEVER_METHOD(TcpSocket::do_assign) {
	CLEVER_ARG(0)->getDataValue()->addRef();
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

void TcpSocket::init() {
	const Type* tcpsock = CLEVER_TYPE("TcpSocket");
	const Type* arr_byte = CLEVER_GET_ARRAY_TEMPLATE->getTemplatedType(CLEVER_BYTE);

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&TcpSocket::do_assign, tcpsock))
			->addArg("rvalue", tcpsock)
	);

	addMethod(new Method(CLEVER_CTOR_NAME, (MethodPtr)&TcpSocket::constructor, tcpsock));

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&TcpSocket::constructor, tcpsock))
			->addArg("host", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&TcpSocket::constructor, tcpsock))
			->addArg("host", CLEVER_STR)
			->addArg("port", CLEVER_INT)
	);

	addMethod(
		(new Method("setHost", (MethodPtr)&TcpSocket::setHost, CLEVER_VOID))
			->addArg("host", CLEVER_STR)
	);

	addMethod(
		(new Method("setPort", (MethodPtr)&TcpSocket::setPort, CLEVER_VOID))
			->addArg("port", CLEVER_INT)
	);

	addMethod(
		(new Method("setTimeout", (MethodPtr)&TcpSocket::setTimeout, CLEVER_VOID))
			->addArg("timeout", CLEVER_INT)
	);

	addMethod(new Method("connect", (MethodPtr)&TcpSocket::connect, tcpsock));
	addMethod(new Method("close", (MethodPtr)&TcpSocket::close, tcpsock));


	addMethod(
		(new Method("receive", (MethodPtr)&TcpSocket::receive, arr_byte))
			->addArg("length", CLEVER_INT)
	);

	addMethod(
		(new Method("send", (MethodPtr)&TcpSocket::send, CLEVER_VOID))
			->addArg("data", arr_byte)
	);

	addMethod(new Method("isOpen", (MethodPtr)&TcpSocket::isOpen, CLEVER_BOOL));
	addMethod(new Method("poll", (MethodPtr)&TcpSocket::poll, CLEVER_BOOL));

	addMethod(new Method("good", (MethodPtr)&TcpSocket::good, CLEVER_BOOL));
	addMethod(new Method("getError", (MethodPtr)&TcpSocket::getError, CLEVER_INT));
	addMethod(new Method("getErrorMessage", (MethodPtr)&TcpSocket::getErrorMessage, CLEVER_INT));

	addMethod(new Method("toString", (MethodPtr)&TcpSocket::toString, CLEVER_STR));

	// Windows socket initialization.
#ifdef CLEVER_WIN32
	WSADATA wsaData;
	int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != NO_ERROR) {
		::std::cerr << "WSAStartup() failed: " << res << ::std::endl;
	}
#endif
}

DataValue* TcpSocket::allocateValue() const {
	return new SocketValue;
}

void TcpSocket::destructor(Value* value) const {
	//SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	// @TODO: disconnect.
}

}}}} // clever::packages::std::net
