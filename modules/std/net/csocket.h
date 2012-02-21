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

#include <string>
#ifndef _WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#include <winsock.h>
#endif

#ifndef CLEVER_CSOCKET_H
#define CLEVER_CSOCKET_H

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

	std::string getErrorString() { return this->errorString; }
	int getError() { return this->error; }

private:
	void resetError();
	void setError();

	// Error
	int error;
	std::string errorString;

	// Socket
	int socket;
	struct sockaddr_in local;
	struct sockaddr_in remote;

	// Timeout
	unsigned int timeout;
};

} // clever

#endif