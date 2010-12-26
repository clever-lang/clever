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
 *
 * $Id$
 */

#include <vector>
#include "scanner.h"
#include "types.h"
#include "ast.h"

#define YYSTYPE clever::ast::Expression*

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
@$.begin.filename = @$.end.filename = &driver.m_file;
};

%debug
%error-verbose

%code {
#include "driver.h"

clever::ast::TreeNode nodes;
}

%token END  0       "end of file"
%token EXIT         "exit"
%token TYPE         "type specification"
%token IDENT        "identifier"
%token NUM_INTEGER  "number"
%token NUM_DOUBLE   "float-number"
%token STR          "string"
%token ECHO         "echo"
%token IN           "in"
%token FOR          "for"
%token WHILE        "while"
%token IF           "if"
%token ELSE         "else"
%token ELSEIF       "else if"

%left ',';
%left '=';
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
%left ELSEIF;
%left ELSE;
%left UMINUS;

%%

%start top_statements;

top_statements:
		statement_list { driver.compiler.Init(nodes.getNodeList()); }
;

statement_list:
		/* empty */
	|	statement_list statements
;

block_stmt:
		'{' { nodes.add(new clever::ast::NewBlock()); } statement_list '}'
				{ nodes.add(new clever::ast::EndBlock()); }
;

statements:
		expr ';'
	|	variable_declaration ';'
	|	echo_stmt ';'
	|	if_stmt
	|	for_stmt
	|	while_stmt
	|	block_stmt
;

variable_declaration_no_init:
		TYPE IDENT	{ nodes.add(new clever::ast::VariableDecl($1, $2, NULL)); }
;

variable_declaration:
		TYPE IDENT '=' type_creation { nodes.add(new clever::ast::VariableDecl($1, $2, $4)); }
	|	TYPE IDENT '=' expr          { nodes.add(new clever::ast::VariableDecl($1, $2, $4)); }
	|	variable_declaration_no_init
;

arguments:
		/* empty */          { $$ = NULL; }
	|	arguments ',' expr   { $$ = $3;   }
	|	expr                 { $$ = $1;   }
;

type_creation:
		TYPE '(' arguments ')' { $$ = new clever::ast::TypeCreation($1, $3); }
;

expr:
		expr '-' expr { $$ = new clever::ast::BinaryExpression('-', $1, $3); nodes.add($$); }
	|	expr '+' expr { $$ = new clever::ast::BinaryExpression('+', $1, $3); nodes.add($$); }
	|	expr '/' expr { $$ = new clever::ast::BinaryExpression('/', $1, $3); nodes.add($$); }
	|	expr '*' expr { $$ = new clever::ast::BinaryExpression('*', $1, $3); nodes.add($$); }
	|	expr '%' expr { $$ = new clever::ast::BinaryExpression('%', $1, $3); nodes.add($$); }
	|	expr '|' expr { $$ = new clever::ast::BinaryExpression('|', $1, $3); nodes.add($$); }
	|	expr '&' expr { $$ = new clever::ast::BinaryExpression('&', $1, $3); nodes.add($$); }
	|	expr '^' expr { $$ = new clever::ast::BinaryExpression('^', $1, $3); nodes.add($$); }
	|	'-' expr %prec UMINUS
	|	'+' expr %prec UMINUS
	|	INCREMENT IDENT { $$ = new clever::ast::PreIncrement($2); nodes.add($$); }
	|	IDENT INCREMENT { $$ = new clever::ast::PosIncrement($1); nodes.add($$); }
	|	DECREMENT IDENT { $$ = new clever::ast::PreDecrement($2); nodes.add($$); }
	|	IDENT DECREMENT { $$ = new clever::ast::PosDecrement($1); nodes.add($$); }
	|	'!' expr
	|	'~' expr
	|	'(' expr ')'  { $$ = $2; }
	|	NUM_INTEGER   { $$ = $1; }
	|	NUM_DOUBLE    { $$ = $1; }
	|	IDENT         { $$ = $1; }
	|	STR           { $$ = $1; }
;

echo_stmt:
		ECHO expr { $$ = new clever::ast::Command($2); nodes.add($$); }
;

for_stmt:
		FOR '(' variable_declaration_no_init IN  IDENT ')' block_stmt
;

while_stmt:
		WHILE '(' expr ')' block_stmt
;

if_stmt:
		IF '(' expr { $2 = new clever::ast::IfExpression($3); nodes.add($2); } ')' block_stmt
		elseif_opt else_opt { nodes.add(new clever::ast::EndIfExpression()); }
;

elseif_opt:
		/* empty */
	|	ELSEIF '(' expr { nodes.add(new clever::ast::ElseIfExpression($3)); } ')' block_stmt
;

else_opt:
		/* empty */
	|	ELSE { nodes.add(new clever::ast::ElseExpression()); } block_stmt
;

%%

void clever::Parser::error(const clever::Parser::location_type& line, const std::string& message)
{
	driver.error(line, message);
}
