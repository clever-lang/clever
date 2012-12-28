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

#include <cstdio>
#include "interpreter/scanner.h"
#include "interpreter/parser.hh"
#include "compiler/compiler.h"
#include "compiler/value.h"
#include "types/native_types.h"

namespace clever {

typedef Parser::token token;

Parser::token_type yylex(Parser::semantic_type* yylval,
	Parser::location_type* yylloc, Driver& driver, ScannerState& s) {
	const unsigned char* cursor = s.cur;
	int yylen;

next_token:
	if (YYCURSOR >= YYLIMIT) {
		RET(token::END);
	}

	s.yylex = cursor;

/*!re2c
	re2c:yyfill:enable = 0;

	IDENTIFIER = [a-z][a-zA-Z0-9_]*;
	INTEGER    = [0-9]+;
	DOUBLE     = [-]?([0-9]*"."[0-9]+)|[-]?([0-9]+"."[0-9]+);
	EXP_DOUBLE = ((INTEGER|DOUBLE)[eE][+-]?INTEGER);
	HEXINT     = [0][x][0-9a-zA-Z]+;
	OCTINT     = [0][0-7]+;
	SPACE 	   = [\r\t\v ]+;
	STRING     = (["]([^\\"]*|"\\"["]?)*["]|[']([^\\']*|"\\"[']?)*[']);
	SPECIAL    = [;(),{}&~^|=+*/-][];
	TYPE       = [A-Z][a-zA-Z0-9_]*;
	CONSTANT   = [A-Z][A-Z0-9_]+;
	REGEX      = "/"[^*/]([a-zA-Z0-9]+|SPACE|['"+$^\|{}?)(*:<>.#\]\[-]|"\\"[^])*"/";

	<!*> { yylen = cursor - s.yylex; }

	<*>SPACE { yylloc->step(); SKIP(); }
	<*>[\n]+ {
		if (YYGETCONDITION() == yycST_COMMENT) {
			YYSETCONDITION(INITIAL);
		}
		yylloc->lines(yylen);
		yylloc->step();
		SKIP();
	}

	<INITIAL>"var" { RET(token::VAR); }

	<INITIAL>"or" { RET(token::LOGICAL_OR); }

	<INITIAL>"||" { RET(token::BOOLEAN_OR); }

	<INITIAL>"and" { RET(token::LOGICAL_AND); }

	<INITIAL>"&&" { RET(token::BOOLEAN_AND); }

	<INITIAL>">=" { RET(token::GREATER_EQUAL); }

	<INITIAL>">" { RET(token::GREATER); }

	<INITIAL>"|=" { RET(token::BW_OR_EQUAL); }

	<INITIAL>"&=" { RET(token::BW_AND_EQUAL); }

	<INITIAL>"^=" { RET(token::XOR_EQUAL); }

	<INITIAL>"<=" { RET(token::LESS_EQUAL); }

	<INITIAL>"<" { RET(token::LESS); }

	<INITIAL>"<<=" { RET(token::LSHIFT_EQUAL); }
	<INITIAL>"<<" { RET(token::LSHIFT); }


	<INITIAL>">>=" { RET(token::RSHIFT_EQUAL); }
	<INITIAL>">>" { RET(token::RSHIFT); }


	<INITIAL>"++" { RET(token::INCREMENT); }

	<INITIAL>"--" { RET(token::DECREMENT); }

	<INITIAL>"==" { RET(token::EQUAL); }

	<INITIAL>"!=" { RET(token::NOT_EQUAL); }

	<INITIAL>"-=" { RET(token::MINUS_EQUAL); }

	<INITIAL>"+=" { RET(token::PLUS_EQUAL); }

	<INITIAL>"*=" { RET(token::MULT_EQUAL); }

	<INITIAL>"/=" { RET(token::DIV_EQUAL); }

	<INITIAL>"%=" { RET(token::MOD_EQUAL); }

	<INITIAL>'const' { RET(token::CONST); }

	<INITIAL>"//" {
		YYSETCONDITION(ST_COMMENT);
		SKIP();
	}

	<INITIAL>"#" {
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

	<INITIAL>'function' {
		RET(token::FUNC);
	}

	<INITIAL>'return' {
		RET(token::RETURN);
	}

	<INITIAL>'break' {
		RET(token::BREAK);
	}

	<INITIAL>'for' {
		RET(token::FOR);
	}

	<INITIAL>'while' {
		RET(token::WHILE);
	}

	<INITIAL>'if' {
		RET(token::IF);
	}

	<INITIAL>('elseif'|'else if') {
		RET(token::ELSEIF);
	}

	<INITIAL>'else' {
		RET(token::ELSE);
	}

	<INITIAL>'import' {
		RET(token::IMPORT);
	}


	<INITIAL>'true' {
		RET(token::TRUE);
	}

	<INITIAL>'false' {
		RET(token::FALSE);
	}

	<INITIAL>'print' {
		RET(token::PRINT);
	}

	<INITIAL>IDENTIFIER {
		yylval->node.type = STRCONST;
		yylval->node.data.str = CSTRING(std::string(reinterpret_cast<const char*>(s.yylex), yylen));
		RET(token::IDENT);
	}

	<INITIAL>'Void' {
		RET(token::TYPE);
	}

	<INITIAL>TYPE {
		RET(token::TYPE);
	}

	<INITIAL>SPECIAL { RET(Parser::token_type(s.yylex[0])); }

	<INITIAL>STRING {
		std::string strtext(reinterpret_cast<const char*>(s.yylex+1), yylen-2);
		size_t found = 0;

		// Handle sequence char
		while (1) {
			found = strtext.find('\\', found);
			if (found == std::string::npos) {
				break;
			}
			if (s.yylex[0] == '"') {
				switch (strtext[found+1]) {
					case 'n': strtext.replace(found, 2, 1, '\n'); break;
					case 'r': strtext.replace(found, 2, 1, '\r'); break;
					case 't': strtext.replace(found, 2, 1, '\t'); break;
					case 'v': strtext.replace(found, 2, 1, '\v'); break;
					case '"': strtext.replace(found, 2, 1, '"'); break;
					case '\\': strtext.replace(found, 2, 1, '\\'); ++found; break;
					default: ++found; break;
				}
			} else {
				switch (strtext[found+1]) {
					case '\'': strtext.replace(found, 2, 1, '\''); break;
					default: ++found; break;
				}
			}
		}

		RET(token::STR);
	}

	<INITIAL>INTEGER {
		const char* nstr = reinterpret_cast<const char*>(s.yylex);
		int64_t n = 0;

		for (int i = 0; i < yylen; ++i) {
			n = n * 10 + (nstr[i] - '0');
		}

		yylval->node.type = VALUE;
		yylval->node.data.val = new Value(n);

		RET(token::NUM_INTEGER);
	}

	<INITIAL>HEXINT {
		const char* nstr = reinterpret_cast<const char*>(s.yylex + 2);
		int64_t n = 0;

		for (int i = 0; i < yylen - 2; ++i) {
			n <<= 4;
			if (isdigit(nstr[i])) {
				n += nstr[i] - '0';
			}
			else {
				n += toupper(nstr[i]) - 'A' + 10;
			}
		}

		yylval->node.type = VALUE;
		yylval->node.data.val = new Value(n);

		RET(token::NUM_INTEGER);
	}

	<INITIAL>OCTINT {
		const char* nstr = reinterpret_cast<const char*>(s.yylex + 1);
		int64_t n = 0;

		for (int i = 0; i < yylen - 1; ++i) {
			n = n * 8 + nstr[i] - '0';
		}

		yylval->node.type = VALUE;
		yylval->node.val = new Value(n);

		RET(token::NUM_INTEGER);
	}

	<INITIAL>(DOUBLE|EXP_DOUBLE) {
		double n = 0;
		n = strtod(std::string(reinterpret_cast<const char*>(s.yylex), yylen).c_str(), NULL);

		yylval->node.type = VALUE;
		yylval->node.data.val = new Value(n);

		RET(token::NUM_DOUBLE);
	}

	<*>[^] { RET(Parser::token_type(s.yylex[0])); }

	<*>"\000" { RET(token::END); }
*/
}

} // clever
