%skeleton "lalr1.cc"
%require "2.4.1"
%defines
%define namespace "clever"
%define parser_class_name "Parser"

%code requires {
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

#include <stack>
#include "scanner.h"
#include "ast.h"

#define YYSTYPE ast::ASTNode*

namespace clever {
class Driver;
} // clever
}

// The parsing context.
%parse-param { Driver& driver }
%parse-param { ScannerState& state }
%lex-param   { Driver& driver }
%lex-param   { ScannerState& state }

%locations
%initial-action {
@$.begin.filename = @$.end.filename = driver.get_file();
};

%debug
%error-verbose

%code {
#include "driver.h"

namespace clever {

std::stack<ast::ASTNode*> tree;
ast::ASTNode* nodes = new ast::BlockNode;

} // clever
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
%token IMPORT        "import"
%token PLUS_EQUAL    "+="
%token MULT_EQUAL    "*="
%token DIV_EQUAL     "/="
%token MINUS_EQUAL   "-="
%token MOD_EQUAL     "%="
%token BOOLEAN_OR    "||"
%token LOGICAL_OR    "or"
%token BOOLEAN_AND   "&&"
%token LOGICAL_AND   "and"
%token BW_AND_EQUAL  "&="
%token BW_OR_EQUAL   "|="
%token BW_XOR_EQUAL  "^="
%token RETURN        "return"
%token CLASS 	     "class"
%token PUBLIC	     "public"
%token PRIVATE       "private"
%token PROTECTED     "protected"

%left ',';
%left LOGICAL_OR;
%left LOGICAL_AND;
%left '=';
%left ':';
%left BOOLEAN_OR;
%left BOOLEAN_AND;
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
		{ driver.initCompiler(nodes); tree.push(nodes); } statement_list { tree.pop(); }
;

statement_list:
		/* empty */
	|	statement_list  statements
;

statement_list_non_empty:
		statements
	|	statement_list_non_empty statements { $$ = $2; }
;

block_stmt:
		'{' '}'                      { $$ = NULL; }
	|	'{'                          { $1 = new ast::BlockNode(); tree.push($1); }
		statement_list_non_empty '}' { tree.pop(); }
;

statements:
		expr ';'	             { tree.top()->add($1); }
	|	variable_declaration ';' { tree.top()->add($1); }
	|	func_declaration         { tree.top()->add($1); }
	|	if_expr                  { tree.top()->add($1); }
	|	for_expr
	|	while_expr               { tree.top()->add($1); }
	|	block_stmt               { tree.top()->add($1); }
	|	break_stmt ';'           { tree.top()->add($1); }
	|	assign_stmt ';'          { tree.top()->add($1); }
	|	import_stmt ';'          { tree.top()->add($1); }
	|	return_stmt ';'          { tree.top()->add($1); }
	|	class_declaration	 { tree.top()->add($1); }
;

return_stmt:
		RETURN expr { $$ = new ast::ReturnStmt($2); $$->set_location(yylloc); }
	|	RETURN      { $$ = new ast::ReturnStmt();   $$->set_location(yylloc); }
;

args_declaration_non_empty:
		TYPE IDENT                      { $$ = new ast::ArgumentDeclList(); static_cast<ast::ArgumentDeclList*>($$)->addArg($1, $2); }
	|	args_declaration ',' TYPE IDENT { static_cast<ast::ArgumentDeclList*>($1)->addArg($3, $4); }
;

args_declaration:
		/* empty */ { $$ = NULL; }
	|	args_declaration_non_empty
;

func_declaration:
		TYPE IDENT '(' args_declaration ')' block_stmt { $$ = new ast::FuncDeclaration($2, $1, $4, $6); }
;

class_declaration:	
		CLASS TYPE '{' class_stmt '}' { $$ = $4; }
;

access_modifier:
		PUBLIC          { $$ = new ast::IntegralValue(0x1); }
	| 	PRIVATE         { $$ = new ast::IntegralValue(0x2); }
	| 	PROTECTED       { $$ = new ast::IntegralValue(0x4); }
;

class_stmt:
		/* empty */             { $$ = new ast::ClassStmtList; }
	|	class_stmt_no_empty     { $$ = $1; }
;

class_stmt_no_empty:
		class_stmt attribute_declaration        { static_cast<ast::ClassStmtList*>($1)->addAttribute($2); $$ = $1; }
	|	class_stmt method_declaration           { static_cast<ast::ClassStmtList*>($1)->addMethod($2); $$ = $1; }
;

method_declaration:
		access_modifier TYPE IDENT '(' args_declaration ')' block_stmt { $$ = new ast::MethodDeclaration($1, $2, $3, $5, $7); }
;

attribute_declaration:
                access_modifier TYPE IDENT ';'	{ $$ = new ast::AttributeDeclaration($1, $2, $3); }
;

arg_list:
		arg_list ',' expr  { $1->add($3); }
	|	expr               { $$ = new ast::ArgumentList; $$->add($1); }
;

func_call:
		IDENT '(' ')'          { $$ = new ast::FunctionCall($1); $$->set_location(yylloc); }
	|	IDENT '(' arg_list ')' { $$ = new ast::FunctionCall($1, $3); $$->set_location(yylloc); }
;

method_call:
		IDENT '.' IDENT '(' ')'          { $$ = new ast::MethodCall($1, $3); $$->set_location(yylloc); }
	|	IDENT '.' IDENT '(' arg_list ')' { $$ = new ast::MethodCall($1, $3, $5); $$->set_location(yylloc); }
;

variable_declaration_no_init:
		TYPE IDENT	{ $$ = new ast::VariableDecl($1, $2); }
;

variable_declaration:
		TYPE IDENT '=' type_creation { $$ = new ast::VariableDecl($1, $2, $4); $$->set_location(yylloc); }
	|	TYPE IDENT '=' expr          { $$ = new ast::VariableDecl($1, $2, $4); $$->set_location(yylloc); }
	|	variable_declaration_no_init { $$ = $1; }
;

assign_stmt:
		IDENT '=' expr  { $$ = new ast::AssignExpr($1, $3);                   $$->set_location(yylloc); }
	|	IDENT "+=" expr { $$ = new ast::BinaryExpr(ast::PLUS, $1, $3, true);  $$->set_location(yylloc); }
	|	IDENT "-=" expr { $$ = new ast::BinaryExpr(ast::MINUS, $1, $3, true); $$->set_location(yylloc); }
	|	IDENT "/=" expr { $$ = new ast::BinaryExpr(ast::DIV, $1, $3, true);   $$->set_location(yylloc); }
	|	IDENT "*=" expr { $$ = new ast::BinaryExpr(ast::MULT, $1, $3, true);  $$->set_location(yylloc); }
	|	IDENT "%=" expr { $$ = new ast::BinaryExpr(ast::MOD, $1, $3, true);   $$->set_location(yylloc); }
	|	IDENT "&=" expr { $$ = new ast::BinaryExpr(ast::AND, $1, $3, true);   $$->set_location(yylloc); }
	|	IDENT "|=" expr { $$ = new ast::BinaryExpr(ast::OR, $1, $3, true);    $$->set_location(yylloc); }
	|	IDENT "^=" expr { $$ = new ast::BinaryExpr(ast::XOR, $1, $3, true);   $$->set_location(yylloc); }
;

arguments:
		/* empty */          { $$ = NULL; }
	|	arguments ',' expr   { $$ = $3;   }
	|	expr                 { $$ = $1;   }
;

type_creation:
		TYPE '(' arguments ')' { $$ = new ast::TypeCreation($1, $3); $$->set_location(yylloc); }
;

expr:
		expr '-' expr         { $$ = new ast::BinaryExpr(ast::MINUS, $1, $3);        $$->set_location(yylloc); }
	|	expr '+' expr         { $$ = new ast::BinaryExpr(ast::PLUS, $1, $3);         $$->set_location(yylloc); }
	|	expr '/' expr         { $$ = new ast::BinaryExpr(ast::DIV, $1, $3);          $$->set_location(yylloc); }
	|	expr '*' expr         { $$ = new ast::BinaryExpr(ast::MULT, $1, $3);         $$->set_location(yylloc); }
	|	expr '%' expr         { $$ = new ast::BinaryExpr(ast::MOD, $1, $3);          $$->set_location(yylloc); }
	|	expr '|' expr         { $$ = new ast::BinaryExpr(ast::BW_OR, $1, $3);        $$->set_location(yylloc); }
	|	expr '&' expr         { $$ = new ast::BinaryExpr(ast::BW_AND, $1, $3);       $$->set_location(yylloc); }
	|	expr '^' expr         { $$ = new ast::BinaryExpr(ast::XOR, $1, $3);          $$->set_location(yylloc); }
	|	expr ">" expr         { $$ = new ast::LogicExpr(ast::GREATER, $1, $3);       $$->set_location(yylloc); }
	|	expr ">=" expr        { $$ = new ast::LogicExpr(ast::GREATER_EQUAL, $1, $3); $$->set_location(yylloc); }
	|	expr "<" expr         { $$ = new ast::LogicExpr(ast::LESS, $1, $3);          $$->set_location(yylloc); }
	|	expr "<=" expr        { $$ = new ast::LogicExpr(ast::LESS_EQUAL, $1, $3);    $$->set_location(yylloc); }
	|	expr "==" expr        { $$ = new ast::LogicExpr(ast::EQUAL, $1, $3);         $$->set_location(yylloc); }
	|	expr "!=" expr        { $$ = new ast::LogicExpr(ast::NOT_EQUAL, $1, $3);     $$->set_location(yylloc); }
	|	expr "||" expr
	|	expr "&&" expr
	|	expr "or" expr        { $$ = new ast::LogicExpr(ast::OR, $1, $3);            $$->set_location(yylloc); }
	|	expr "and" expr       { $$ = new ast::LogicExpr(ast::AND, $1, $3);           $$->set_location(yylloc); }
	|	'-' expr %prec UMINUS { $$ = new ast::BinaryExpr(ast::MINUS, $2);            $$->set_location(yylloc); }
	|	'+' expr %prec UMINUS { $$ = new ast::BinaryExpr(ast::PLUS, $2);             $$->set_location(yylloc); }
	|	INCREMENT IDENT       { $$ = new ast::PreIncrement($2);                      $$->set_location(yylloc); }
	|	IDENT INCREMENT       { $$ = new ast::PosIncrement($1);                      $$->set_location(yylloc); }
	|	DECREMENT IDENT       { $$ = new ast::PreDecrement($2);                      $$->set_location(yylloc); }
	|	IDENT DECREMENT       { $$ = new ast::PosDecrement($1);                      $$->set_location(yylloc); }
	|	'!' expr              { $$ = $2; }
	|	'~' expr              { $$ = $2; }
	|	'(' expr ')'          { $$ = $2; }
	|	func_call
	|	method_call
	|	NUM_INTEGER
	|	NUM_DOUBLE
	|	IDENT
	|	STR
;

for_expr:
		FOR '(' variable_declaration_no_init IN  IDENT ')' block_stmt
;

while_expr:
		WHILE '(' expr ')' block_stmt { $$ = new ast::WhileExpr($3, $5); $$->set_location(yylloc); }
;

if_expr:
		IF '(' expr ')' block_stmt { $2 = new ast::IfExpr($3, $5); $$ = $2;                $$->set_location(yylloc); }
		elseif_opt else_opt        { static_cast<ast::IfExpr*>($2)->set_else($8); $$ = $2; $$->set_location(yylloc); }
;

elseif_opt:
		/* empty */
	|	elseif_opt ELSEIF '(' expr ')' block_stmt { $0->add(new ast::ElseIfExpr($4, $6)); $$->set_location(yylloc); }
;

else_opt:
		/* empty */		{ $$ = NULL; }
	|	ELSE block_stmt { $$ = $2;   }
;

break_stmt:
		BREAK { $$ = new ast::BreakNode(); $$->set_location(yylloc); }
;

import_stmt:
		IMPORT IDENT           { $$ = new ast::ImportStmt($2);      $$->set_location(yylloc); }
	|	IMPORT IDENT '.' IDENT { $$ = new ast::ImportStmt($2, $4);  $$->set_location(yylloc); }
;

%%

namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& message) {
	driver.error(line, message);
}

} // clever
