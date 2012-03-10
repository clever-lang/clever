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

#ifndef CLEVER_RPCVALUE_H
#define CLEVER_RPCVALUE_H

#include <cstdlib>
#include <string>
#include <pthread.h>
#include <map>
#include "compiler/datavalue.h"

#include "modules/std/net/csocket.h"

namespace clever { namespace packages { namespace std { namespace rpc {


typedef ::std::map< ::std::string, void*> ExtMap;
typedef ::std::map< ::std::string, ::std::string> FuncMap;

class RPCValue : public DataValue {

public:

	RPCValue() { socket = 0; }

	void createServer(int port, int connections);

	void createClient(const char* host, const int port, const int time);

	void loadLibrary(const char* libname);
	void addFunction(const char* libname, const char* funcname, const char* rettype);

	void sendString(const char* s, int len);

	void sendInteger(int v);

	CSocket* getSocket() { return this->socket; }

	virtual ~RPCValue() { if(socket) delete socket; }

private:

	CSocket* socket;
	int createConnection(int client_socket_id);
};

}}}} // clever::packages::std::rpc

#endif // CLEVER_RPCVALUE_H

