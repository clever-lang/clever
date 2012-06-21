/*
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

#ifndef CLEVER_CSOCKET_H
#define CLEVER_CSOCKET_H

#include <string>
#ifndef _WIN32
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#include <winsock.h>
#endif
#include "compiler/clever.h"

#ifndef NO_ERROR
#define NO_ERROR 0
#endif

namespace clever {

class CSocket {
public:
	CSocket();
	~CSocket();

	void setHost(const char *addr);
	void setPort(const int port);
	void setTimeout(const int time);

	bool connect();
	bool close();

	bool receive(const char *buffer, int length);
	bool send(const char *buffer, int length);

	bool isOpen();
	bool poll();

	std::string getErrorString() { return m_error_string; }
	int getError() { return m_error; }

private:
	void resetError();
	void setError();

	// Error
	int m_error;
	std::string m_error_string;

	// Socket and socket-related
	int m_socket;
	struct sockaddr_in m_local;
	std::string m_host;
	std::string m_port;

	// Timeout
	unsigned int m_timeout;

	DISALLOW_COPY_AND_ASSIGN(CSocket);
};

} // clever

#endif // CLEVER_CSOCKET_H
