/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_TCPSOCKET_H
#define CLEVER_TCPSOCKET_H

#include <ostream>
#include "types/type.h"
#include "core/value.h"
#include "modules/std/net/csocket.h"

namespace clever { namespace packages { namespace std { namespace net {

class SocketObject : public ValueObject {
public:
	SocketObject()
		: ValueObject() {}

	virtual ~SocketObject() {}

	CSocket& getSocket() { return m_socket; }
private:
	CSocket m_socket;
};

class TcpSocket : public Type {
public:
	TcpSocket() :
		Type(CSTRING("TcpSocket")) { }

	void init();
	void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	void deallocData(void*);

	void dump(const void* value) const { dump(value, ::std::cout); }
	void dump(const void* value, ::std::ostream& out) const { out << "TcpSocket"; }

	// Type methods
	CLEVER_METHOD(setHost);
	CLEVER_METHOD(setPort);
	CLEVER_METHOD(setTimeout);
	CLEVER_METHOD(connect);
	CLEVER_METHOD(close);
	CLEVER_METHOD(receive);
	CLEVER_METHOD(send);
	CLEVER_METHOD(isOpen);
	CLEVER_METHOD(poll);
	CLEVER_METHOD(good);
	CLEVER_METHOD(getError);
	CLEVER_METHOD(getErrorMessage);
	CLEVER_METHOD(toString);
	CLEVER_METHOD(do_assign);
private:
	DISALLOW_COPY_AND_ASSIGN(TcpSocket);
};

}}}} // clever::packages::std::net

#endif // CLEVER_TCPSOCKET_H
