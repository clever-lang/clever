%skeleton "lalr1.cc"
%require "2.4.1"
%defines
%define namespace "clever"
%define parser_class_name "Parser"

%code requires {
/*
 * Clever language
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

#include <vector>
#include "scanner.h"
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
@$.begin.filename = @$.end.filename = &driver.get_file();
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
%token LESS_EQUAL   "<="
%token GREATER_EQUAL ">="
%token LESS          "<"
%token GREATER       ">"
%token BREAK         "break"
%token EQUAL         "=="
%token NOT_EQUAL     "!="

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
		statement_list { driver.initCompiler(&nodes); }
;

statement_list:
		/* empty */
	|	statement_list statements
;

statement_list_non_empty:
		statements
	|	statement_list_non_empty statements
;

block_stmt:
		'{' '}'
	|	'{' { nodes.add(new clever::ast::NewBlock()); } statement_list_non_empty '}'
				{ nodes.add(new clever::ast::EndBlock()); }
;

statements:
		expr ';'
	|	variable_declaration ';'
	|	if_stmt
	|	for_stmt
	|	while_stmt
	|	block_stmt
	|	break_stmt ';'
	|	assign_stmt ';'
;

arg_list:
		arg_list ',' expr  { clever::ast::ArgumentList* args = static_cast<clever::ast::ArgumentList*>($1); args->push($3); $$ = args; }
	|	expr               { clever::ast::ArgumentList* args = new clever::ast::ArgumentList(); args->push($1); $$ = args;}
;

func_call:
		IDENT '(' ')'          { $$ = new clever::ast::FunctionCall($1); nodes.add($$); }
	|	IDENT '(' arg_list ')' { $$ = new clever::ast::FunctionCall($1, $3); nodes.add($$); }
;

method_call:
		IDENT '.' IDENT '(' ')'          { $$ = new clever::ast::MethodCall($1, $3); nodes.add($$); }
	|	IDENT '.' IDENT '(' arg_list ')' { $$ = new clever::ast::MethodCall($1, $3, $5); nodes.add($$); }
;

variable_declaration_no_init:
		TYPE IDENT	{ nodes.add(new clever::ast::VariableDecl($1, $2, NULL)); }
;

variable_declaration:
		TYPE IDENT '=' type_creation { nodes.add(new clever::ast::VariableDecl($1, $2, $4)); }
	|	TYPE IDENT '=' expr          { nodes.add(new clever::ast::VariableDecl($1, $2, $4)); }
	|	variable_declaration_no_init
;

assign_stmt:
		IDENT '=' expr { nodes.add(new clever::ast::Assignment($1, $3)); }
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
		expr '-' expr { $$ = new clever::ast::BinaryExpression(ast::MINUS, $1, $3); nodes.add($$); }
	|	expr '+' expr { $$ = new clever::ast::BinaryExpression(ast::PLUS, $1, $3); nodes.add($$); }
	|	expr '/' expr { $$ = new clever::ast::BinaryExpression(ast::DIV, $1, $3); nodes.add($$); }
	|	expr '*' expr { $$ = new clever::ast::BinaryExpression(ast::MULT, $1, $3); nodes.add($$); }
	|	expr '%' expr { $$ = new clever::ast::BinaryExpression(ast::MOD, $1, $3); nodes.add($$); }
	|	expr '|' expr { $$ = new clever::ast::BinaryExpression(ast::OR, $1, $3); nodes.add($$); }
	|	expr '&' expr { $$ = new clever::ast::BinaryExpression(ast::AND, $1, $3); nodes.add($$); }
	|	expr '^' expr { $$ = new clever::ast::BinaryExpression(ast::XOR, $1, $3); nodes.add($$); }
	|	expr ">" expr   { $$ = new clever::ast::LogicExpression(ast::GREATER, $1, $3); nodes.add($$); }
	|	expr ">=" expr  { $$ = new clever::ast::LogicExpression(ast::GREATER_EQUAL, $1, $3); nodes.add($$); }
	|	expr "<" expr   { $$ = new clever::ast::LogicExpression(ast::LESS, $1, $3); nodes.add($$); }
	|	expr "<=" expr  { $$ = new clever::ast::LogicExpression(ast::LESS_EQUAL, $1, $3); nodes.add($$); }
	|	expr "==" expr  { $$ = new clever::ast::LogicExpression(ast::EQUAL, $1, $3); nodes.add($$); }
	|	expr "!=" expr  { $$ = new clever::ast::LogicExpression(ast::NOT_EQUAL, $1, $3); nodes.add($$); }
	|	'-' expr %prec UMINUS { $$ = new clever::ast::BinaryExpression(ast::MINUS, $2); nodes.add($$); }
	|	'+' expr %prec UMINUS { $$ = new clever::ast::BinaryExpression(ast::PLUS, $2); nodes.add($$); }
	|	INCREMENT IDENT { $$ = new clever::ast::PreIncrement($2); nodes.add($$); }
	|	IDENT INCREMENT { $$ = new clever::ast::PosIncrement($1); nodes.add($$); }
	|	DECREMENT IDENT { $$ = new clever::ast::PreDecrement($2); nodes.add($$); }
	|	IDENT DECREMENT { $$ = new clever::ast::PosDecrement($1); nodes.add($$); }
	|	'!' expr
	|	'~' expr
	|	'(' expr ')'  { $$ = $2; }
	|	func_call     { $$ = $1; }
	|	method_call   { $$ = $1; }
	|	NUM_INTEGER   { $$ = $1; }
	|	NUM_DOUBLE    { $$ = $1; }
	|	IDENT         { $$ = $1; }
	|	STR           { $$ = $1; }
;

for_stmt:
		FOR '(' variable_declaration_no_init IN  IDENT ')' block_stmt
;

while_stmt:
		WHILE '(' { $2 = new clever::ast::StartExpr(); nodes.add($2); }
		expr { nodes.add(new clever::ast::WhileExpression($4)); } ')'
		block_stmt { nodes.add(new clever::ast::EndWhileExpression($2)); }
;

if_stmt:
		IF '(' expr { nodes.add(new clever::ast::IfExpression($3)); } ')' block_stmt
		elseif_opt else_opt { nodes.add(new clever::ast::EndIfExpression()); }
;

elseif_opt:
		/* empty */
	|	elseif_opt ELSEIF '(' { $3 = new clever::ast::StartExpr(); nodes.add($3); }
		expr { nodes.add(new clever::ast::ElseIfExpression($3, $5)); } ')' block_stmt
;

else_opt:
		/* empty */
	|	ELSE { nodes.add(new clever::ast::ElseExpression()); } block_stmt
;

break_stmt:
		BREAK { nodes.add(new clever::ast::BreakExpression()); }
;

%%

void clever::Parser::error(const clever::Parser::location_type& line, const std::string& message)
{
	driver.error(line, message);
}
