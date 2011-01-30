/*
 * Clever programming language
 * Copyright (c) 2011 Clever Team
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

#ifndef CLEVER_SCANNER_H
#define CLEVER_SCANNER_H

#include "global.h"

namespace clever {

enum YYCONDTYPE {
	yycINITIAL,
	yycST_COMMENT,
	yycST_MULTILINE_COMMENT,
	yycST_END_OF_SCRIPT
};

#define YYGETCONDITION()  s.state
#define YYSETCONDITION(x) s.state = yyc##x

#define YYCTYPE       char
#define YYMARKER     (s.ctx)
#define YYCTXMARKER  (s.ctx)
#define YYCURSOR     cursor
#define YYLIMIT      cursor

#define SET_TYPE(t_ptr) \
	yylval->type = t_ptr; \
	yylval->data = NULL;

#define SKIP() s.cur = s.yylex + 1; goto next_token;
#define RET(i) s.cur = cursor; return i;

class ScannerState {
public:
	ScannerState() : state(0) { }

	void set_cursor(const char* cursor) throw() { cur = cursor; }

	int state;
	const char *cur, *yylex, *ctx;
private:
	DISALLOW_COPY_AND_ASSIGN(ScannerState);
};

} // clever

#endif // CLEVER_SCANNER_H
