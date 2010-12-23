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

#include "config.h"
#include "scanner.h"
#include "parser.hh"
#include "ast.h"

enum YYCONDTYPE {
	yycINITIAL,
	yycST_COMMENT,
	yycST_MULTILINE_COMMENT,
	yycST_END_OF_SCRIPT
};

#define YYGETCONDITION()  s->state
#define YYSETCONDITION(x) s->state = yyc##x

#define YYCTYPE       char
#define YYMARKER     (s->ctx)
#define YYCTXMARKER  (s->ctx)
#define YYCURSOR     cursor
#define YYLIMIT      cursor

#define SET_TYPE(t_ptr) \
	yylval->type = t_ptr; \
	yylval->data = NULL;

#define SKIP() { s->cur = s->yylex + 1; goto next_token; }
#define RET(i) { s->cur = cursor; return i; }

typedef clever::Parser::token token;

clever::Parser::token_type yylex(clever::Parser::semantic_type* yylval,
	clever::Parser::location_type* yylloc, clever::Driver& driver,
	clever::ScannerState* s) {
	const char* cursor = s->cur;
	int yylen;

next_token:
	s->yylex = cursor;

/*!re2c
	re2c:yyfill:enable = 0;

	IDENTIFIER = [a-z][a-zA-Z0-9_]*;
	INTEGER    = [0-9]+;
	DOUBLE     = [0-9]+[.][0-9]+;
	HEXINT     = [0][x][0-9a-zA-Z]+;
	OCTINT     = [0][0-7]+;
	SPACE 	   = [\r\t\v ]+;
	STRING     = (["]([^\\"]*|"\\"["]?)*["]|[']([^\\']*|"\\"[']?)*[']);
	SPECIAL    = [;(),{}&~^|<>=+*/-];
	TYPE       = [A-Z][a-zA-Z0-9_]*;

	<!*> { yylen = cursor - s->yylex; }

	<*>SPACE { yylloc->step(); SKIP(); }
	<*>[\n]+ { yylloc->lines(yylen); yylloc->step(); SKIP(); }

	<INITIAL>SPECIAL { RET(clever::Parser::token_type(s->yylex[0])); }

	<INITIAL>">=" { RET(token::GREATER_EQUAL); }

	<INITIAL>"|=" { RET(token::BW_OR_EQUAL); }

	<INITIAL>"&=" { RET(token::BW_AND_EQUAL); }

	<INITIAL>"^=" { RET(token::XOR_EQUAL); }

	<INITIAL>"<=" { RET(token::LESS_EQUAL); }

	<INITIAL>"++" { RET(token::INCREMENT); }

	<INITIAL>"--" { RET(token::DECREMENT); }

	<INITIAL>"==" { RET(token::EQUAL); }

	<INITIAL>"!=" { RET(token::NOT_EQUAL); }

	<INITIAL>"-=" { RET(token::MINUS_EQUAL); }

	<INITIAL>"+=" { RET(token::PLUS_EQUAL); }

	<INITIAL>"*=" { RET(token::MULT_EQUAL); }

	<INITIAL>"/=" { RET(token::DIV_EQUAL); }

	<INITIAL>"%=" { RET(token::MOD_EQUAL); }

	<INITIAL>"//" {
		YYSETCONDITION(ST_COMMENT);
		SKIP();
	}

	<ST_COMMENT>[^\n]* {
		YYSETCONDITION(INITIAL);
		SKIP();
	}

	<INITIAL>"/*" {
		YYSETCONDITION(ST_MULTILINE_COMMENT);
		SKIP();
	}

	<ST_MULTILINE_COMMENT>[^*]+ { SKIP(); }

	<ST_MULTILINE_COMMENT>"*/" {
		YYSETCONDITION(INITIAL);
		SKIP();
	}

	<ST_MULTILINE_COMMENT>"*" { SKIP(); }

	<INITIAL>"echo" {
		*yylval = new clever::ast::IdentifierAST(std::string(s->yylex, yylen));
		RET(token::ECHO);
	}

	<INITIAL>"for" {
		RET(token::FOR);
	}

	<INITIAL>"in" {
		RET(token::IN);
	}

	<INITIAL>"while" {
		RET(token::WHILE);
	}

	<INITIAL>"if" {
		RET(token::IF);
	}

	<INITIAL>("elseif"|"else if") {
		RET(token::ELSEIF);
	}

	<INITIAL>"else" {
		RET(token::ELSE);
	}

	<INITIAL>IDENTIFIER {
		*yylval = new clever::ast::IdentifierAST(std::string(s->yylex, yylen));
		RET(token::IDENT);
	}

	<INITIAL>TYPE {
		*yylval = new clever::ast::IdentifierAST(std::string(s->yylex, yylen));
		RET(token::TYPE);
	}

	<INITIAL>STRING {
		std::string strtext(s->yylex+1, yylen-2);
		size_t found = 0;

		// Handle sequence char
		while (1) {
			found = strtext.find('\\', found);
			if (found == std::string::npos) {
				break;
			}
			if (s->yylex[0] == '"') {
				switch (strtext[found+1]) {
					case 'n': strtext.replace(int(found), 2, 1, '\n'); break;
					case 'r': strtext.replace(int(found), 2, 1, '\r'); break;
					case 't': strtext.replace(int(found), 2, 1, '\t'); break;
					case 'v': strtext.replace(int(found), 2, 1, '\v'); break;
					case '"': strtext.replace(int(found), 2, 1, '"'); break;
					case '\\': strtext.replace(int(found), 2, 1, '\\'); ++found; break;
					default: ++found; break;
				}
			} else {
				switch (strtext[found+1]) {
					case '\'': strtext.replace(int(found), 2, 1, '\''); break;
					default: ++found; break;
				}
			}
		}

		*yylval = new clever::ast::IdentifierAST(strtext);
		RET(token::STR);
	}

	<INITIAL>INTEGER {
		int64_t n = strtol(std::string(s->yylex, yylen).c_str(), NULL, 10);

		*yylval = new clever::ast::NumberExprAST(n);
		RET(token::NUM_INTEGER);
	}

	<INITIAL>HEXINT {
		int64_t n = 0;

		sscanf(std::string(s->yylex+2, yylen).c_str(), "%x", (unsigned long *)&n);
		*yylval = new clever::ast::NumberExprAST(n);

		RET(token::NUM_INTEGER);
	}

	<INITIAL>OCTINT {
		int64_t n = 0;

		sscanf(std::string(s->yylex+1, yylen), "%o", &n);
		*yylval = new clever::ast::NumberExprAST(n);

		RET(token::NUM_INTEGER);
	}

	<INITIAL>DOUBLE {
		double n = 0;

		n = strtod(std::string(s->yylex, yylen).c_str(), NULL);
		*yylval = new clever::ast::NumberExprAST(n);

		RET(token::NUM_DOUBLE);
	}

	<*>[^] { RET(clever::Parser::token_type(s->yylex[0])); }

	<*>"\000" { RET(token::END); }
*/
}
