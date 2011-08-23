/**
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
 */

#include <cstdio>
#include "interpreter/scanner.h"
#include "parser.hh"
#include "interpreter/ast.h"
#include "compiler/cstring.h"
#include "compiler/symboltable.h"

namespace clever {

typedef Parser::token token;

Parser::token_type yylex(Parser::semantic_type* yylval, Parser::location_type* yylloc, Driver& driver, ScannerState& s) {
	const char* cursor = s.cur;
	int yylen;

next_token:
	s.yylex = cursor;

/*!re2c
	re2c:yyfill:enable = 0;

	IDENTIFIER = [a-z][a-zA-Z0-9_]*;
	INTEGER    = [0-9]+;
	DOUBLE     = [-]?([0-9]*"."[0-9]+)|[-]?([0-9]+"."[0-9]*);
	EXP_DOUBLE = ((INTEGER|DOUBLE)[eE][+-]?INTEGER);
	HEXINT     = [0][x][0-9a-zA-Z]+;
	OCTINT     = [0][0-7]+;
	SPACE 	   = [\r\t\v ]+;
	STRING     = (["]([^\\"]*|"\\"["]?)*["]|[']([^\\']*|"\\"[']?)*[']);
	SPECIAL    = [;(),{}&~^|=+*/-];
	TYPE       = [A-Z][a-zA-Z0-9_]*;

	<!*> { yylen = cursor - s.yylex; }

	<*>SPACE { yylloc->step(); SKIP(); }
	<*>[\n]+ { yylloc->lines(yylen); yylloc->step(); SKIP(); }

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

	<INITIAL>"return" {
		RET(token::RETURN);
	}

	<INITIAL>"break" {
		RET(token::BREAK);
	}

	<INITIAL>"echo" {
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

	<INITIAL>"import" {
		RET(token::IMPORT);
	}
	
	<INITIAL>"class" {
		RET(token::CLASS);
	}
	
	<INITIAL>"public" {
		RET(token::PUBLIC);
	}

	<INITIAL>"private" {
		RET(token::PRIVATE);
	}

	<INITIAL>"protected" {
		RET(token::PROTECTED);
	}


	<INITIAL>IDENTIFIER {
		*yylval = new ast::Identifier(CSTRING(std::string(s.yylex, yylen)));
		RET(token::IDENT);
	}

	<INITIAL>"Void" {
		*yylval = NULL;
		RET(token::TYPE);
	}

	<INITIAL>TYPE {
		*yylval = new ast::Identifier(CSTRING(std::string(s.yylex, yylen)));
		RET(token::TYPE);
	}

	<INITIAL>SPECIAL { RET(Parser::token_type(s.yylex[0])); }

	<INITIAL>STRING {
		std::string strtext(s.yylex+1, yylen-2);
		size_t found = 0;

		// Handle sequence char
		while (1) {
			found = strtext.find('\\', found);
			if (found == std::string::npos) {
				break;
			}
			if (s.yylex[0] == '"') {
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

		*yylval = new ast::StringLiteral(CSTRING(strtext));
		RET(token::STR);
	}

	<INITIAL>INTEGER {
		Value* newval = new Value(CLEVER_TYPE("Int"));
		int64_t n = strtol(std::string(s.yylex, yylen).c_str(), NULL, 10);

		newval->setType(Value::INTEGER);
		newval->setInteger(n);

		*yylval = new ast::NumberLiteral(newval);

		RET(token::NUM_INTEGER);
	}

	<INITIAL>HEXINT {
		Value* newval = new Value(CLEVER_TYPE("Int"));
		int64_t n = 0;

		std::sscanf(std::string(s.yylex+2, yylen).c_str(), "%X", (unsigned*)&n);

		newval->setType(Value::INTEGER);
		newval->setInteger(n);

		*yylval = new ast::NumberLiteral(newval);

		RET(token::NUM_INTEGER);
	}

	<INITIAL>OCTINT {
		Value* newval = new Value(CLEVER_TYPE("Int"));
		int64_t n = 0;

		sscanf(std::string(s.yylex+1, yylen), "%o", &n);

		newval->setType(Value::INTEGER);
		newval->setInteger(n);

		*yylval = new ast::NumberLiteral(newval);

		RET(token::NUM_INTEGER);
	}

	<INITIAL>(DOUBLE|EXP_DOUBLE) {
		Value* newval = new Value(CLEVER_TYPE("Double"));
		double n = 0;

		n = strtod(std::string(s.yylex, yylen).c_str(), NULL);

		newval->setType(Value::DOUBLE);
		newval->setDouble(n);

		*yylval = new ast::NumberLiteral(newval);

		RET(token::NUM_DOUBLE);
	}

	<*>[^] { RET(Parser::token_type(s.yylex[0])); }

	<*>"\000" { RET(token::END); }
*/
}

} // clever
