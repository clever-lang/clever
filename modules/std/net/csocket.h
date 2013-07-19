/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_CSOCKET_H
#define CLEVER_CSOCKET_H

#include <string>
#ifndef _WIN32
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#include <ws2tcpip.h>
#include <winsock.h>
#endif
#include "core/clever.h"

#ifndef NO_ERROR
#define NO_ERROR 0
#endif

namespace clever {

class CSocket {
public:
	CSocket()
		: m_timeout(0) {}
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
