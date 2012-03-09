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


int process(int client_socket_id) {
	while (true) {
		int length;
		char* text;

		/* First, read the length of the text message from the socket. If
		read returns zero, the client closed the connection. */

		if (recv (client_socket_id, &length, sizeof (length), 0) == 0)
			return 0;

		/* Allocate a buffer to hold the text. */
		text = (char*) calloc (length,sizeof(char));
		/* Read the text itself, and print it. */
		recv (client_socket_id, text, length, 0);
		printf ("<%s>\n", text);
		/* Free the buffer. */
		free (text);
		/* If the client sent the message “quit,” we’re all done.  */
		if (!strcmp (text, "quit"))
			return 1;
	}

	close (client_socket_id);
	return 0;
}

int RPCValue::createConnection(int client_socket_id){
	//Create thread to manage connection
	return process (client_socket_id);
}


void RPCValue::createServer(int port, int connections){
	sockaddr_in sa;

	memset(&sa, 0, sizeof(sa));

	sa.sin_family = PF_INET;
	sa.sin_port = ::htons(port);
	int m_socket = ::socket(AF_INET, SOCK_STREAM, 0);

	bind(m_socket, (sockaddr *)&sa, sizeof(sockaddr_in));
	
	listen(m_socket, connections);

	int kill_me;

	do {
		struct sockaddr client_name;
		socklen_t client_name_len;
		int client_socket_id;
		
		client_socket_id = accept (m_socket, &client_name, &client_name_len);
		
		kill_me=createConnection(client_socket_id);
		
	} while (!kill_me);

	close (m_socket);

}

void RPCValue::createClient(const char* host, const int port, const int time) {
	socket = new CSocket;

	socket->setHost(host);
	socket->setPort(port);
	socket->setTimeout(time);
}

void RPCValue::sendString(const char* s, int len) {
	socket->send(s,len);
}

void RPCValue::sendInteger(int v) {
	socket->send( (char*)(&v),sizeof(int));
}


}}}} // clever::packages::std::rpc


