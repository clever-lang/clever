%skeleton "lalr1.cc"
%require "2.4.1"
%defines
%define namespace "clever"
%define parser_class_name "Parser"

%code requires {
/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <stack>
#include "core/scanner.h"
#include "core/ast.h"

namespace clever {
class Driver;
class Compiler;
class Value;

} // clever
}

%union {
	ast::Node* node;
	ast::NodeArray* narray;
	ast::Ident* ident;
	ast::StringLit* strlit;
	ast::IntLit* intlit;
	ast::DoubleLit* dbllit;

	ast::Assignment* assignment;
	ast::VariableDecl* vardecl;

}

%type <ident> IDENT
%type <strlit> STR
%type <intlit> NUM_INTEGER
%type <dbllit> NUM_DOUBLE
%type <assignment> assignment
%type <narray> variable_decl variable_decl_list
%type <vardecl> variable_decl_impl


// The parsing context.
%parse-param { Driver& driver }
%parse-param { ScannerState& state }
%parse-param { Compiler& c }
%lex-param   { Driver& driver }
%lex-param   { ScannerState& state }

%locations
%initial-action {
@$.begin.filename = @$.end.filename = driver.getFile();
};

%debug
%error-verbose

%code {
#include "core/driver.h"
}

%token END  0        "end of file"
%token VAR           "var"
%token EXIT          "exit"
%token TYPE          "type specification"
%token IDENT         "identifier"
%token NUM_INTEGER   "number"
%token NUM_DOUBLE    "float-number"
%token STR           "string"
%token FOR           "for"
%token WHILE         "while"
%token IF            "if"
%token ELSE          "else"
%token ELSEIF        "else if"
%token LESS_EQUAL    "<="
%token GREATER_EQUAL ">="
%token LESS          "<"
%token GREATER       ">"
%token RSHIFT        ">>"
%token RSHIFT_EQUAL  ">>="
%token LSHIFT        "<<"
%token LSHIFT_EQUAL  "<<="
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
%token TRUE          "true"
%token FALSE         "false"
%token CONST         "const"
%token PRINT         "print"
%token FUNC          "function"
%token THREAD        "thread"
%token INCREMENT     "++"
%token DECREMENT     "--"

%left ',';
%left LOGICAL_OR;
%left LOGICAL_AND;
%right '=' PLUS_EQUAL MINUS_EQUAL DIV_EQUAL MULT_EQUAL MOD_EQUAL BW_OR_EQUAL XOR_EQUAL BW_AND_EQUAL  RSHIFT_EQUAL LSHIFT_EQUAL;
%left ':';
%left BOOLEAN_OR;
%left BOOLEAN_AND;
%left '|';
%left '^';
%left '&';
%nonassoc EQUAL NOT_EQUAL;
%nonassoc LESS LESS_EQUAL GREATER GREATER_EQUAL;
%left LSHIFT RSHIFT;
%left '-' '+' '.';
%left '*' '/' '%';
%right '!';
%right '~' INCREMENT DECREMENT COPY DEEPCOPY;
%right '[' '{';
%left ELSEIF;
%left ELSE;
%left UMINUS;

%%

%start program;

program:
		{ c.init(); } statement_list { c.end(); }
;

statement_list:
		// empty
	|	statement_list statement
;

statement:
		variable_decl ';'
	|	assignment ';'
;

rvalue:
		IDENT
	|	STR
	|	NUM_INTEGER
	|	NUM_DOUBLE
;

lvalue:
		IDENT
;

variable_decl:
		VAR variable_decl_list { $$ = $2; }
;

variable_decl_list:
		variable_decl_impl                        { $$ = new ast::NodeArray(yyloc); $$->append($1); }
	|	variable_decl_list ',' variable_decl_impl { $1->append($3); }
;

variable_decl_impl:
		IDENT '=' rvalue { $$ = new ast::VariableDecl($1, new ast::Assignment($1, $<node>3, yyloc), yyloc); }
	|	IDENT            { $$ = new ast::VariableDecl($1, NULL, yyloc); }
;

assignment:
		lvalue '=' rvalue { $$ = new ast::Assignment($<node>1, $<node>3, yyloc); }
;

/*
assignment_list:
		// empty
	|	assignment
	|	assignment_list ',' assignment
;
*/


%%

namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever
