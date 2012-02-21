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
	this->socket = ::socket(AF_INET, SOCK_STREAM, 0);

	// Local socket init.
	this->local.sin_family = AF_INET;
	this->local.sin_addr.s_addr = htonl(INADDR_ANY);
	this->local.sin_port = htons(INADDR_ANY);

	// Remote socket init.
	this->remote.sin_family = AF_INET;
}

CSocket::~CSocket() {
	this->close();
}

void CSocket::setHost(const char *addr) {
	this->remote.sin_addr.s_addr = inet_addr(addr);
}

void CSocket::setPort(const int port) {
	this->remote.sin_port = htons(port);
}

void CSocket::setTimeout(const int time) {
	// Timeout value is in 'ms', and our timeout should be in 'us'.
	this->timeout = time * 1000;
}

bool CSocket::connect() {
	this->resetError();

	if (::connect(this->socket, (struct sockaddr*)&this->remote, sizeof(this->remote)) != 0) {
		this->setError();
		return false;
	}

	return true;
}

bool CSocket::close() {
	int res;

	this->resetError();

#ifdef CLEVER_WIN32
	res = ::closesocket(this->socket);
#else
	res = ::close(this->socket);
#endif

	// If the return was 0, it's ok.
	if (res == 0) {
		return true;
	} else {
		this->setError();
		return false;
	}
}

bool CSocket::receive(const char *buffer, int length) {
	this->resetError();
	
	// Receive data.
	int res = ::recv(this->socket, (char *)buffer, length, 0);

	if (res > 0) {
		return true;
	} else {
		this->setError();
		return false;
	}
}

bool CSocket::send(const char *buffer, int length) {
	int sent = 0;

	this->resetError();

	// Loop the send() because it might happen to not send all data once.
	do {
		int res = ::send(this->socket, (&buffer[sent]), (length - sent), 0);

		if (res >= 0) {
			sent += res;
		} else {
			this->setError();
			return false;
		}
	} while (sent < length);

	return true;
}

bool CSocket::isOpen() {
	char buf;
	fd_set readset;

	this->resetError();

	// @TODO: when the platform supports, use MSG_DONTWAIT.

	// We should perform a select() to make sure our recv() won't block.
	FD_ZERO(&readset);
	FD_SET(this->socket, &readset);

	// Try the select().
	if (::select(this->socket + 1, &readset, NULL, NULL, NULL) > 0) {
		if (!FD_ISSET(this->socket, &readset)) {
			// There's no data, so our recv() will block. This means that our socket is still alive, since
			// when the connection has been closed FD_ISSET returns true.
			return true;
		}
	} else {
		// select() failed, so the socket should be closed.
		return false;
	}

	// If we got here, our select() said that the socket could be read() without blocking. Let's try it.
	int res = ::recv(this->socket, &buf, 1, MSG_PEEK);

	if (res == 0) {
		// Our connection has been closed on the remote end.
		this->close();
		return false;
	} else if (res > 0) {
		// There's data, so the socket is still alive.
		return true;
	} else {
		// We got an error. Let's see if it's an EAGAIN.
		this->setError();
		if (this->error == EAGAIN) {
			// Our socket is still alive.
			return true;
		} else {
			// Some went wrong. Oops.
			this->setError();
			return false;
		}
	}
}

bool CSocket::poll() {
	struct timeval timeout;
	fd_set readset;
	int res;

	this->resetError();

	// Set the minimum interval.
	if (this->timeout > 1000000) {
		timeout.tv_sec = (this->timeout / 1000000);
		timeout.tv_usec = (this->timeout % 1000000);
	} else {
		timeout.tv_sec = 0;
		timeout.tv_usec = this->timeout;
	}

	// Prepare the fd_set.
	FD_ZERO(&readset);
	FD_SET(this->socket, &readset);

	// Try the select().
	res = select(this->socket + 1, &readset, NULL, NULL, &timeout);
	if (res == 0) {
		// Timeout.
		return false;
	} else if (res > 0) {
		// We got our socket back.
		if (FD_ISSET(this->socket, &readset)) {
			return true;
		} else {
			return false;
		}
	} else {
		// Error.
		this->setError();
		return false;
	}
}

void CSocket::resetError() {
	this->error = NO_ERROR;
	this->errorString = std::string("");
}

void CSocket::setError() {
#ifdef CLEVER_WIN32
	this->error = WSAGetLastError();
	this->errorString = GetLastErrorStr(this->error);	
#else
	this->error = errno;
	this->errorString = ::std::string(strerror(errno));
#endif
}

} // clever