/**
 * Clever programming language
 * Copyright (c) 2012 Clever Team
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

#include <iostream>
#include <errno.h>
#include "modules/std/net/csocket.h"
#ifdef CLEVER_WIN32
#include "win32/win32.h"
#else
#include <cstring>
#endif

namespace clever {

CSocket::CSocket() {
	// Socket init.
	// @TODO: check for errors on this.
	m_socket = ::socket(AF_INET, SOCK_STREAM, 0);

	// Local socket init.
	m_local.sin_family = AF_INET;
	m_local.sin_addr.s_addr = htonl(INADDR_ANY);
	m_local.sin_port = htons(INADDR_ANY);

	// Remote socket init.
	m_remote.sin_family = AF_INET;
}

CSocket::~CSocket() {
	close();
}

void CSocket::setHost(const char *addr) {
	m_remote.sin_addr.s_addr = inet_addr(addr);
}

void CSocket::setPort(const int port) {
	m_remote.sin_port = htons(port);
}

void CSocket::setTimeout(const int time) {
	// Timeout value is in 'ms', and our timeout should be in 'us'.
	m_timeout = time * 1000;
}

bool CSocket::connect() {
	resetError();

	if (::connect(m_socket, (struct sockaddr*)&m_remote, sizeof(m_remote)) != 0) {
		setError();
		return false;
	}

	return true;
}

bool CSocket::close() {
	int res;

	resetError();

#ifdef CLEVER_WIN32
	res = ::closesocket(m_socket);
#else
	res = ::close(m_socket);
#endif

	// If the return was 0, it's ok.
	if (res == 0) {
		return true;
	} else {
		setError();
		return false;
	}
}

bool CSocket::receive(const char *buffer, int length) {
	resetError();

	// Receive data.
	int res = ::recv(m_socket, (char *)buffer, length, 0);

	if (res > 0) {
		return true;
	} else {
		setError();
		return false;
	}
}

bool CSocket::send(const char *buffer, int length) {
	int sent = 0;

	resetError();

	// Loop the send() because it might happen to not send all data once.
	do {
		int res = ::send(m_socket, (&buffer[sent]), (length - sent), 0);

		if (res >= 0) {
			sent += res;
		} else {
			setError();
			return false;
		}
	} while (sent < length);

	return true;
}

bool CSocket::isOpen() {
	struct timeval timeout;
	char buf;
	fd_set readset;

	resetError();

	// @TODO: when the platform supports, use MSG_DONTWAIT.
	
	// Set the minimum interval.
	if (m_timeout > 1000000) {
		timeout.tv_sec = (m_timeout / 1000000);
		timeout.tv_usec = (m_timeout % 1000000);
	} else {
		timeout.tv_sec = 0;
		timeout.tv_usec = m_timeout;
	}


	// We should perform a select() to make sure our recv() won't block.
	FD_ZERO(&readset);
	FD_SET(m_socket, &readset);

	// Try the select().
	if (::select(m_socket + 1, &readset, NULL, NULL, &timeout) >= 0) {
		if (!FD_ISSET(m_socket, &readset)) {
			// There's no data, so our recv() will block. This means that our socket is still alive, since
			// when the connection has been closed FD_ISSET returns true.
			return true;
		}
	} else {
		// select() failed, so the socket should be closed.
		return false;
	}

	// If we got here, our select() said that the socket could be read() without blocking. Let's try it.
	int res = ::recv(m_socket, &buf, 1, MSG_PEEK);

	if (res == 0) {
		// Our connection has been closed on the remote end.
		close();
		return false;
	} else if (res > 0) {
		// There's data, so the socket is still alive.
		return true;
	} else {
		// We got an error. Let's see if it's an EAGAIN.
		setError();
		if (m_error == EAGAIN) {
			// Our socket is still alive.
			return true;
		} else {
			// Some went wrong. Oops.
			setError();
			return false;
		}
	}
}

bool CSocket::poll() {
	struct timeval timeout;
	fd_set readset;
	int res;

	resetError();

	// Set the minimum interval.
	if (m_timeout > 1000000) {
		timeout.tv_sec = (m_timeout / 1000000);
		timeout.tv_usec = (m_timeout % 1000000);
	} else {
		timeout.tv_sec = 0;
		timeout.tv_usec = m_timeout;
	}

	// Prepare the fd_set.
	FD_ZERO(&readset);
	FD_SET(m_socket, &readset);

	// Try the select().
	res = select(m_socket + 1, &readset, NULL, NULL, &timeout);
	if (res == 0) {
		// Timeout.
		return false;
	} else if (res > 0) {
		// We got our socket back.
		if (FD_ISSET(m_socket, &readset)) {
			return true;
		} else {
			return false;
		}
	} else {
		// Error.
		setError();
		return false;
	}
}

void CSocket::resetError() {
	m_error = NO_ERROR;
	m_error_string = std::string("");
}

void CSocket::setError() {
#ifdef CLEVER_WIN32
	m_error = WSAGetLastError();
	m_error_string = GetLastErrorStr(m_error);
#else
	m_error = errno;
	m_error_string = ::std::string(strerror(errno));
#endif
}

} // clever
