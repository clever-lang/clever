/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include <fstream>
#include "core/cstring.h"
#include "core/native_types.h"
#include "modules/std/net/tcpsocket.h"

namespace clever { namespace modules { namespace std { namespace net {

CLEVER_METHOD(TcpSocket::ctor)
{
	if (!clever_check_args("|si")) {
		return;
	}

	SocketObject* sv = new SocketObject;

	if (!args.empty()) {
		switch (args.size()) {
			case 1:
				// Host only.
				sv->getSocket().setHost(args[0]->getStr()->c_str());
				break;
			case 2:
				// Host and port.
				sv->getSocket().setHost(args[0]->getStr()->c_str());
				sv->getSocket().setPort(args[1]->getInt());
				break;
		}
	}

	result->setObj(this, sv);
}

CLEVER_METHOD(TcpSocket::setHost)
{
	if (!clever_check_args("s")) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	sv->getSocket().setHost(args[0]->getStr()->c_str());
}

CLEVER_METHOD(TcpSocket::setPort)
{
	if (!clever_check_args("i")) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	sv->getSocket().setPort(args[0]->getInt());
}

CLEVER_METHOD(TcpSocket::setTimeout)
{
	if (!clever_check_args("i")) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	sv->getSocket().setTimeout(args[0]->getInt());
}

CLEVER_METHOD(TcpSocket::connect)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	sv->getSocket().connect();
}

CLEVER_METHOD(TcpSocket::close)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	sv->getSocket().close();
}

CLEVER_METHOD(TcpSocket::receive)
{
	if (!clever_check_args("i")) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);
	char *buffer;
	long length = args[0]->getInt();

	// Allocate the buffer.
	buffer = new char[length];
	memset(buffer, 0, length);

	// Receive the data.
	sv->getSocket().receive(buffer, length);

	result->setStr(CSTRING(buffer));

	delete[] buffer;
}

CLEVER_METHOD(TcpSocket::send)
{
	if (!clever_check_args("s")) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	const char* buffer = args[0]->getStr()->c_str();
	size_t buffer_len = ::strlen(buffer);

	sv->getSocket().send(buffer, buffer_len);
}

CLEVER_METHOD(TcpSocket::isOpen)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	result->setBool(sv->getSocket().isOpen());
}

CLEVER_METHOD(TcpSocket::poll)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	result->setBool(sv->getSocket().poll());
}

CLEVER_METHOD(TcpSocket::good)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	result->setBool(sv->getSocket().getError() == NO_ERROR);
}

CLEVER_METHOD(TcpSocket::getError)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	result->setInt(sv->getSocket().getError());
}

CLEVER_METHOD(TcpSocket::getErrorMessage)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = clever_get_this(SocketObject*);

	result->setStr(CSTRING(sv->getSocket().getErrorString()));
}

CLEVER_TYPE_INIT(TcpSocket::init)
{
	setConstructor((MethodPtr)&TcpSocket::ctor);

	addMethod(new Function("setHost",         (MethodPtr)&TcpSocket::setHost));
	addMethod(new Function("setPort",         (MethodPtr)&TcpSocket::setPort));
	addMethod(new Function("setTimeout",      (MethodPtr)&TcpSocket::setTimeout));
	addMethod(new Function("connect",         (MethodPtr)&TcpSocket::connect));
	addMethod(new Function("close",           (MethodPtr)&TcpSocket::close));
	addMethod(new Function("receive",         (MethodPtr)&TcpSocket::receive));
	addMethod(new Function("send",            (MethodPtr)&TcpSocket::send));
	addMethod(new Function("isOpen",          (MethodPtr)&TcpSocket::isOpen));
	addMethod(new Function("poll",            (MethodPtr)&TcpSocket::poll));
	addMethod(new Function("good",            (MethodPtr)&TcpSocket::good));
	addMethod(new Function("getError",        (MethodPtr)&TcpSocket::getError));
	addMethod(new Function("toString",        (MethodPtr)&TcpSocket::toString));
	addMethod(new Function("getErrorMessage", (MethodPtr)&TcpSocket::getErrorMessage));

	// Windows socket initialization.
#ifdef CLEVER_WIN32
	WSADATA wsaData;
	int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != NO_ERROR) {
		::std::cerr << "WSAStartup() failed: " << res << ::std::endl;
	}
#endif
}

}}}} // clever::modules::std::net
