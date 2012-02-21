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
#include <errno.h>
#include <fcntl.h>
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/std/net/tcpsocket.h"
#include "types/nativetypes.h"

// Win32 workarounds.
#ifdef CLEVER_WIN32
#define errno WSAGetLastError()
#endif

namespace clever { namespace packages { namespace std { namespace net {

CLEVER_METHOD(TcpSocket::constructor) {
	SocketValue* sv = new SocketValue;

	// Socket init.
	// @TODO: check for errors on this.
	sv->socket = socket(AF_INET, SOCK_STREAM, 0);

	// Local socket init.
	sv->local.sin_family = AF_INET;
	sv->local.sin_addr.s_addr = htonl(INADDR_ANY);
	sv->local.sin_port = htons(INADDR_ANY);

	// Remote socket init.
	sv->remote.sin_family = AF_INET;

	if (args != NULL) {
		if (CLEVER_NUM_ARGS() == 1) {
			// Host only.
			sv->remote.sin_addr.s_addr = inet_addr(CLEVER_ARG_STR(0).c_str());
		} else if (CLEVER_NUM_ARGS() == 2) {
			// Host and port.
			sv->remote.sin_addr.s_addr = inet_addr(CLEVER_ARG_STR(0).c_str());
			sv->remote.sin_port = CLEVER_ARG_INT(1);
		}
	}

	/* Assignment on type creation will increase the ref */
	sv->setReference(0);

	CLEVER_RETURN_DATA_VALUE(sv);
}

CLEVER_METHOD(TcpSocket::setHost) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	sv->remote.sin_addr.s_addr = inet_addr(CLEVER_ARG_STR(0).c_str());
}

CLEVER_METHOD(TcpSocket::setPort) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	sv->remote.sin_port = htons(CLEVER_ARG_INT(0));
}

CLEVER_METHOD(TcpSocket::setTimeout) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	sv->timeout = (CLEVER_ARG_INT(0) * 1000);
}

CLEVER_METHOD(TcpSocket::connect) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	if (::connect(sv->socket, (struct sockaddr*)&sv->remote, sizeof(sv->remote)) != 0) {
		// @TODO: change this.

		::std::cerr << "connect() failed: " << (errno) << " - " << ::std::string(strerror(errno)) << ::std::endl;
	}
}

CLEVER_METHOD(TcpSocket::close) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

#ifdef CLEVER_WIN32
	if (::closesocket(sv->socket) != 0) {
#else
	if (::close(sv->socket) != 0) {
#endif
		// @TODO: change this.

		::std::cerr << "close() failed: " << (errno) << " - " << ::std::string(strerror(errno)) << ::std::endl;
	}
}

CLEVER_METHOD(TcpSocket::receive) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);
	ValueVector* vv = new ValueVector;
	char *buffer;
	unsigned int length;
	
	length = CLEVER_ARG_INT(0);

	// Allocate the buffer.
	buffer = new char[length];

	// Receive data.
	int res = ::recv(sv->socket, (char *)buffer, length, 0);

	if (res <= 0) {
		// @TODO: change this.

		::std::cerr << "recv() failed: " << (errno) << " - " << ::std::string(strerror(errno)) << ::std::endl;
		//::std::cerr << "recv() failed: connection has been gracefully closed." << ::std::endl;
	} else {
		for (int i = 0; i < length; i++) {
			Value *v = new Value();
			v->setByte(buffer[i]);
			vv->push_back(v);
		}

		retval->setTypePtr(CLEVER_TYPE("Array<Byte>"));
		CLEVER_RETURN_ARRAY(vv);
	}

	// Free the buffer.
	delete buffer;
}

CLEVER_METHOD(TcpSocket::send) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);
	ValueVector *vv = CLEVER_ARG_ARRAY(0);
	char *buffer;
	int bufferSize;
	int bytesSent = 0;

	// Allocate a buffer and fill it with the bytes from the array.
	buffer = new char[vv->size()];
	for (int i = 0; i < vv->size(); i++) {
		buffer[i] = static_cast<char>(vv->at(i)->getByte());
	}
	bufferSize = vv->size();

	// Loop the send() because it might happen to not send all data once.
	do {
		int res = ::send(sv->socket, (&buffer[bytesSent]), (bufferSize - bytesSent), 0);

		if (res >= 0) {
			bytesSent += res;
		} else {
			// @TODO: change this.
			::std::cerr << "send() failed: " << (errno) << " - " << ::std::string(strerror(errno)) << ::std::endl;
		}
	} while (bytesSent < bufferSize);

	// Free the buffer.
	delete buffer;
}

CLEVER_METHOD(TcpSocket::isOpen) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);

	/*
	fd_set writeset;

	FD_ZERO(&writeset);
	FD_SET(sv->socket, &writeset);

	// Try the select().
	int res = select(sv->socket + 1, NULL, &writeset, NULL, NULL);

	::std::cout << "[DEBUG] select() returned " << res << ::std::endl;

	if (res > 0) {
		if (FD_ISSET(sv->socket, &writeset)) {
			::std::cout << "[DEBUG] FD_ISSET returned true" << ::std::endl;
		} else {
			::std::cout << "[DEBUG] FD_ISSET returned false" << ::std::endl;
		}
	}
	*/
	::std::cerr << "isOpen(): not implemented" << ::std::endl;
	CLEVER_RETURN_BOOL(true);
}

CLEVER_METHOD(TcpSocket::poll) {
	SocketValue* sv = CLEVER_GET_VALUE(SocketValue*, value);
	struct timeval timeout;
	fd_set readset;
	int res;

	// Set the minimum interval.
	if (sv->timeout > 1000000) {
		timeout.tv_sec = (sv->timeout / 1000000);
		timeout.tv_usec = (sv->timeout % 1000000);
	} else {
		timeout.tv_sec = 0;
		timeout.tv_usec = sv->timeout;
	}

	// Prepare the fd_set.
	FD_ZERO(&readset);
	FD_SET(sv->socket, &readset);

	// Try the select().
	res = select(sv->socket + 1, &readset, NULL, NULL, &timeout);
	if (res == 0) {
		// Timeout.
		CLEVER_RETURN_BOOL(false);
	} else if (res > 0) {
		// We got our socket back.
		if (FD_ISSET(sv->socket, &readset)) {
			CLEVER_RETURN_BOOL(true);
		} else {
			CLEVER_RETURN_BOOL(false);
		}
	} else {
		// @TODO: change this.
		::std::cerr << "select() failed: " << (errno) << " - " << ::std::string(strerror(errno)) << ::std::endl;
	}
}

CLEVER_METHOD(TcpSocket::toString) {
	CLEVER_RETURN_STR(CSTRING("TcpSocket class"));
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

	addMethod(new Method("connect", (MethodPtr)&TcpSocket::connect, tcpsock));
	addMethod(new Method("close", (MethodPtr)&TcpSocket::close, tcpsock));

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
