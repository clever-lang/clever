/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cstdio>
#include "core/scanner.h"
#include "core/parser.hh"
#include "core/ast.h"
#include "core/value.h"
#include "types/native_types.h"

namespace clever {

typedef Parser::token token;

Parser::token_type yylex(Parser::semantic_type* yylval,
	Parser::location_type* yyloc, Driver& driver, ScannerState& s) {
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

	<*>SPACE { yyloc->step(); SKIP(); }
	<*>[\n]+ {
		if (YYGETCONDITION() == yycST_COMMENT) {
			YYSETCONDITION(INITIAL);
		}
		yyloc->lines(yylen);
		yyloc->step();
		SKIP();
	}

	<INITIAL>'null' {
		yylval->nillit = new ast::NullLit(*yyloc);
		RET(token::NIL);
	}

	<INITIAL>'var' { RET(token::VAR); }

	<INITIAL>'catch' { RET(token::CATCH); }

	<INITIAL>'try' { RET(token::TRY); }

	<INITIAL>'finally' { RET(token::FINALLY); }

	<INITIAL>'throw' { RET(token::THROW); }

	<INITIAL>'or' { RET(token::LOGICAL_OR); }

	<INITIAL>"||" { RET(token::BOOLEAN_OR); }

	<INITIAL>'and' { RET(token::LOGICAL_AND); }

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


	<INITIAL>"++" { RET(token::INC); }

	<INITIAL>"--" { RET(token::DEC); }

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

	<INITIAL>'new' {
		RET(token::NEW);
	}

	<INITIAL>'function' {
		RET(token::FUNC);
	}

	<INITIAL>'wait' {
		RET(token::WAIT);
	}

	<INITIAL>'spawn' {
		RET(token::THREAD);
	}

	<INITIAL>'critical' {
		RET(token::CRITICAL);
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

	<INITIAL>IDENTIFIER {
		yylval->ident = new ast::Ident(
			CSTRING(std::string(reinterpret_cast<const char*>(s.yylex), yylen)), *yyloc);

		RET(token::IDENT);
	}

	<INITIAL>TYPE {
		yylval->type = new ast::Type(
			CSTRING(std::string(reinterpret_cast<const char*>(s.yylex), yylen)), *yyloc);
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

        yylval->strlit = new ast::StringLit(CSTRING(strtext), *yyloc);

		RET(token::STR);
	}

	<INITIAL>INTEGER {
		const char* nstr = reinterpret_cast<const char*>(s.yylex);
		int64_t n = 0;

		for (int i = 0; i < yylen; ++i) {
			n = n * 10 + (nstr[i] - '0');
		}

        yylval->intlit = new ast::IntLit(n, *yyloc);

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

        yylval->intlit = new ast::IntLit(n, *yyloc);

		RET(token::NUM_INTEGER);
	}

	<INITIAL>OCTINT {
		const char* nstr = reinterpret_cast<const char*>(s.yylex + 1);
		int64_t n = 0;

		for (int i = 0; i < yylen - 1; ++i) {
			n = n * 8 + nstr[i] - '0';
		}

        yylval->intlit = new ast::IntLit(n, *yyloc);

		RET(token::NUM_INTEGER);
	}

	<INITIAL>(DOUBLE|EXP_DOUBLE) {
		double n = strtod(
			std::string(reinterpret_cast<const char*>(s.yylex), yylen).c_str(), NULL);

        yylval->dbllit = new ast::DoubleLit(n, *yyloc);

		RET(token::NUM_DOUBLE);
	}

	<*>[^] { RET(Parser::token_type(s.yylex[0])); }

	<*>"\000" { RET(token::END); }
*/
}

} // clever
