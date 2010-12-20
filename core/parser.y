%skeleton "lalr1.cc"
%require "2.4.1"
%defines
%define namespace "clever"
%define parser_class_name "Parser"

%code requires {
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
 */

#include <vector>
#include "scanner.h"
#include "types.h"
#include "ast.h"

#define YYSTYPE clever::ast::ExprAST*

namespace clever {
class Driver;
}
}

// The parsing context.
%parse-param { clever::Driver& driver }
%parse-param { clever::ScannerState* state }
%lex-param   { clever::Driver& driver }
%lex-param   { clever::ScannerState* state }
     
%locations
%initial-action {
// Initialize the initial location.
@$.begin.filename = @$.end.filename = &driver.file;
};

%debug
%error-verbose

%code {
#include "driver.h"
#include "compiler.h"

clever::ast::AstList nodes;
clever::Compiler compiler;
}

%token END  0       "end of file"
%token EXIT         "exit"
%token TYPE         "type specification"
%token IDENT        "identifier"
%token NUM_INTEGER  "number"
%token NUM_DOUBLE   "float-number"
%token STR          "string"
%token ASSIGN       "="


%left ',';
%left BW_OR BW_AND BW_XOR;
%left ASSIGN;
%left ':';
%left '|';
%left '^';
%left '&';
%nonassoc EQUAL NOT_EQUAL;
%nonassoc LESS LESS_EQUAL GREATER GREATER_EQUAL;
%left PLUS_EQUAL MINUS_EQUAL DIV_EQUAL MULT_EQUAL MOD_EQUAL BW_OR_EQUAL XOR_EQUAL BW_AND_EQUAL;
%left SHIFT_LEFT SHIFT_RIGHT;
%left '-' '+' '.';
%left '*' '/' '%';
%right '!';
%right '~' INCREMENT DECREMENT;
%right '[' '{';
%left ELSIF;
%left ELSE;
%left UMINUS;

%%

%start top_statements;

top_statements:
		statement_list { compiler.Init(nodes); }
;

statement_list:
		/* empty */
	|	statement_list statements	
;

statements:
		expr ';'
	|	variable_declaration ';'
;

variable_declaration:
		TYPE IDENT "=" type_creation { nodes.push_back(new clever::ast::VariableDeclAST($1, $2, $4)); }
;

arguments:
		/* empty */
	|	arguments ',' expr
	|	expr
;

type_creation:
		TYPE '(' arguments ')' { nodes.push_back(new clever::ast::TypeCreationAST($1, $3)); }
;

expr:	expr '-' expr { nodes.push_back(new clever::ast::BinaryExprAST('-', $1, $3)); }
	|	expr '+' expr { nodes.push_back(new clever::ast::BinaryExprAST('+', $1, $3)); }
	|	expr '/' expr { nodes.push_back(new clever::ast::BinaryExprAST('/', $1, $3)); }
	|	expr '*' expr { nodes.push_back(new clever::ast::BinaryExprAST('*', $1, $3)); }
	|	expr '%' expr { nodes.push_back(new clever::ast::BinaryExprAST('%', $1, $3)); }
	|	NUM_INTEGER   { $$ = $1; }
	|	NUM_DOUBLE    { $$ = $1; }
;

%%

void clever::Parser::error(const clever::Parser::location_type& line, const std::string& message)
{
	driver.error(line, message);
}
