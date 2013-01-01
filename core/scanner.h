/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_SCANNER_H
#define CLEVER_SCANNER_H

#include "core/clever.h"

namespace clever {

enum YYCONDTYPE {
	yycINITIAL,
	yycST_COMMENT,
	yycST_MULTILINE_COMMENT,
	yycST_END_OF_SCRIPT
};

#define YYGETCONDITION()  s.state
#define YYSETCONDITION(x) s.state = yyc##x

#define YYCTYPE      unsigned char
#define YYMARKER     s.ctx
#define YYCTXMARKER  s.ctx
#define YYCURSOR     cursor
#define YYLIMIT      s.yylimit

#define SET_TYPE(t_ptr) \
	yylval->type = t_ptr; \
	yylval->data = NULL;

#define SKIP() s.cur = s.yylex + 1; goto next_token;
#define RET(i) s.cur = cursor; return i;

class ScannerState {
public:
	ScannerState() : state(0) {}
	~ScannerState() {}

	void set_cursor(const unsigned char* cursor) { cur = cursor; }
	void set_limit(const unsigned char* limit) { yylimit = limit; }

	int state;
	const unsigned char *cur, *yylex, *ctx, *yylimit;

	std::string& getSource() {return m_source; }
private:
	std::string m_source;

	DISALLOW_COPY_AND_ASSIGN(ScannerState);
};

} // clever

#endif // CLEVER_SCANNER_H
