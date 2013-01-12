/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include <fstream>
#include "core/compiler.h"
#include "core/cstring.h"
#include "modules/std/net/tcpsocket.h"
#include "types/native_types.h"

namespace clever { namespace packages { namespace std { namespace net {

void* TcpSocket::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	SocketObject* sv = new SocketObject;

	if (args != NULL) {
		switch (args->size()) {
			case 1:
				// Host only.
				sv->getSocket().setHost(args->at(0)->getStr()->c_str());
				break;
			case 2:
				// Host and port.
				sv->getSocket().setHost(args->at(0)->getStr()->c_str());
				sv->getSocket().setPort(args->at(1)->getInt());
				break;
		}
	}
	return sv;
}

void TcpSocket::deallocData(void* obj)
{
	SocketObject* sv = static_cast<SocketObject*>(obj);

	delete sv;
}

CLEVER_METHOD(TcpSocket::setHost)
{
	if (!clever_check_args("s")) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	sv->getSocket().setHost(args[0]->getStr()->c_str());
}

CLEVER_METHOD(TcpSocket::setPort)
{
	if (!clever_check_args("i")) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	sv->getSocket().setPort(args[0]->getInt());
}

CLEVER_METHOD(TcpSocket::setTimeout)
{
	if (!clever_check_args("i")) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	sv->getSocket().setTimeout(args[0]->getInt());
}

CLEVER_METHOD(TcpSocket::connect)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	sv->getSocket().connect();
}

CLEVER_METHOD(TcpSocket::close)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	sv->getSocket().close();
}

CLEVER_METHOD(TcpSocket::receive)
{
	/*
	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());
	ValueVector* vv = new ValueVector;
	char *buffer;
	int length;

	length = CLEVER_ARG_INT(0);

	// Allocate the buffer.
	buffer = new char[length];
	memset(buffer, 0, length);

	// Receive the data.
	sv->getSocket().receive(buffer, length);

	for (int i = 0; i < length; ++i) {
		Value *v = new Value();
		v->setByte(buffer[i]);
		vv->push_back(v);
	}

	// Free the buffer.
	delete buffer;

	retval->setTypePtr(CLEVER_TYPE("Array<Byte>"));
	CLEVER_RETURN_ARRAY(vv);*/
}

CLEVER_METHOD(TcpSocket::send)
{
	if (!clever_check_args("s")) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	const char* buffer = args[0]->getStr()->c_str();
	size_t buffer_len = ::strlen(buffer);

	sv->getSocket().send(buffer, buffer_len);
}

CLEVER_METHOD(TcpSocket::isOpen)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	CLEVER_RETURN_BOOL(sv->getSocket().isOpen());
}

CLEVER_METHOD(TcpSocket::poll)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	CLEVER_RETURN_BOOL(sv->getSocket().poll());
}

CLEVER_METHOD(TcpSocket::good)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	CLEVER_RETURN_BOOL(sv->getSocket().getError() == NO_ERROR);
}

CLEVER_METHOD(TcpSocket::getError)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	result->setInt(sv->getSocket().getError());
}

CLEVER_METHOD(TcpSocket::getErrorMessage)
{
	if (!clever_check_no_args()) {
		return;
	}

	SocketObject* sv = CLEVER_GET_OBJECT(SocketObject*, CLEVER_THIS());

	result->setStr(CSTRING(sv->getSocket().getErrorString()));
}

CLEVER_METHOD(TcpSocket::toString)
{
	result->setStr(CSTRING("TcpSocket class"));
}

CLEVER_TYPE_INIT(TcpSocket::init)
{
	addMethod(CSTRING("setHost"),         (MethodPtr)&TcpSocket::setHost);
	addMethod(CSTRING("setPort"),         (MethodPtr)&TcpSocket::setPort);
	addMethod(CSTRING("setTimeout"),      (MethodPtr)&TcpSocket::setTimeout);
	addMethod(CSTRING("connect"),         (MethodPtr)&TcpSocket::connect);
	addMethod(CSTRING("close"),           (MethodPtr)&TcpSocket::close);
	addMethod(CSTRING("receive"),         (MethodPtr)&TcpSocket::receive);
	addMethod(CSTRING("send"),            (MethodPtr)&TcpSocket::send);
	addMethod(CSTRING("isOpen"),          (MethodPtr)&TcpSocket::isOpen);
	addMethod(CSTRING("poll"),            (MethodPtr)&TcpSocket::poll);
	addMethod(CSTRING("good"),            (MethodPtr)&TcpSocket::good);
	addMethod(CSTRING("getError"),        (MethodPtr)&TcpSocket::getError);
	addMethod(CSTRING("toString"),        (MethodPtr)&TcpSocket::toString);
	addMethod(CSTRING("getErrorMessage"), (MethodPtr)&TcpSocket::getErrorMessage);

	// Windows socket initialization.
#ifdef CLEVER_WIN32
	WSADATA wsaData;
	int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != NO_ERROR) {
		::std::cerr << "WSAStartup() failed: " << res << ::std::endl;
	}
#endif
}

}}}} // clever::packages::std::net
