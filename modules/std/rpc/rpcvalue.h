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
#include "modules/std/rpc/rpcobjectvalue.h"

//Function call
#define CLEVER_RPC_FC 0x1
//Process call
#define CLEVER_RPC_PC 0x2
//Send String
#define CLEVER_RPC_PS 0x3
//Send Integer
#define CLEVER_RPC_PI 0x4
//Get process return
#define CLEVER_RPC_GR 0x5
//Kill command
#define CLEVER_RPC_KILL 0x6
//Init command
#define CLEVER_RPC_INIT 0x7
//Connection accepted 
#define CLEVER_RPC_OK 0x8
//Receive Int
#define CLEVER_RPC_RI 0x9
//Send Int
#define CLEVER_RPC_SI 0x10
//Receive Double
#define CLEVER_RPC_RD 0x11
//Send Double
#define CLEVER_RPC_SD 0x12
//Receive String
#define CLEVER_RPC_RS 0x13
//Send String
#define CLEVER_RPC_SS 0x14

namespace clever { namespace packages { namespace std { namespace rpc {


typedef ::std::map< ::std::string, void*> ExtMap;
typedef ::std::map< ::std::string, ::std::string> FuncMap;

class RPCValue : public DataValue {

public:

	RPCValue() { socket = 0; }

	void createServer(int port, int connections);

	bool createClient(const char* host, const int port, const int time);

	void loadLibrary(const char* libname);
	void addFunction(const char* libname, const char* funcname, const char* rettype);

	/* Send objects to server*/
	void sendInteger(int v);
	void sendString(const char* s, int len);
	void sendFunctionCall(const char* fname, const char* args, int len_fname, int n_args, int len_args);
	void sendProcessCall(int id_process, const char* fname, const char* args, int len_fname, int n_args, int len_args);

	/* Send objects to another clients */
	void sendObject(int id_message, const char* s, int len);
	void sendInteger(int id_message, int v);
	void sendDouble(int id_message, double v);
	void sendString(int id_message, const char* s, int len);


	void sendKill();
	bool sendInit();

	RPCObjectValue* getResultProcess(int id_process, double time_sleep);
	RPCObjectValue* receiveObject();

	/* Receive objects from another clients */
	RPCObjectValue* receiveObject(int id_message);
	int receiveInt(int id_message, double time_sleep);
	double receiveDouble(int id_message, double time_sleep);
	::std::string receiveString(int id_message, double time_sleep);

	CSocket* getSocket() { return this->socket; }

	~RPCValue();

private:

	CSocket* socket;
	void createConnection(int client_socket_id);
};

}}}} // clever::packages::std::rpc

#endif // CLEVER_RPCVALUE_H

