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
#include "modules/std/net/socketvalue.h"

namespace clever { namespace packages { namespace std { namespace net {

class SocketObject : public ValueObject {
public:
	SocketObject()
		: ValueObject() { socket = new CSocket(); }

	virtual ~SocketObject() { delete socket; }

	bool valid() const { return socket != NULL; }

	CSocket* getSocket() { return this->socket; }
private:
	CSocket* socket;
};

class TcpSocket : public Type {
public:
	TcpSocket() :
		Type(CSTRING("TcpSocket")) { }

	void init();
	void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	void deallocData(void*) const;

	void dump(const void* value) const { dump(value, ::std::cout); }
	void dump(const void* value, ::std::ostream& out) const { out << "TcpSocket"; }

	// Type methods
	CLEVER_METHOD_D(constructor);
	CLEVER_METHOD_D(setHost);
	CLEVER_METHOD_D(setPort);
	CLEVER_METHOD_D(setTimeout);
	CLEVER_METHOD_D(connect);
	CLEVER_METHOD_D(close);
	CLEVER_METHOD_D(receive);
	CLEVER_METHOD_D(send);
	CLEVER_METHOD_D(isOpen);
	CLEVER_METHOD_D(poll);
	CLEVER_METHOD_D(good);
	CLEVER_METHOD_D(getError);
	CLEVER_METHOD_D(getErrorMessage);
	CLEVER_METHOD_D(toString);
	CLEVER_METHOD_D(do_assign);
private:
	DISALLOW_COPY_AND_ASSIGN(TcpSocket);
};

}}}} // clever::packages::std::net

#endif // CLEVER_TCPSOCKET_H
