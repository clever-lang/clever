/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
 *
 * $Id$
 */

// If this is not a Windows host, don't compile this file.

#ifdef _WIN32

#include <iostream>
#include <string>
#include "win32.h"

void GetLastErrorStr(LPTSTR pszFunction, std::string &err)
{ 
    LPTSTR pszMessage;
    DWORD dwLastError = GetLastError(); 
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dwLastError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&pszMessage,
        0, NULL );
	err = std::string(pszMessage);
    LocalFree(pszMessage);
}

void CreateBackgroundProcess(std::string cline) {
	PROCESS_INFORMATION ProcInfo;
	STARTUPINFO StartupInfo;
	std::string err;
	
	memset(&StartupInfo, 0, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(STARTUPINFO);
	StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	StartupInfo.wShowWindow = SW_HIDE;
	
	if (CreateProcess(NULL, LPSTR(cline.c_str()), NULL, NULL, false, CREATE_NO_WINDOW, NULL, NULL, &StartupInfo, &ProcInfo)) {
		std::cout << "Background process created (PID: " << ProcInfo.dwProcessId << ")";
	} else {
		GetLastErrorStr("CreateProcess",err);
		std::cout << "Background process creation failed: " << err;
	}
}

#endif