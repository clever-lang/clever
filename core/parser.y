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
	ast::Block* block;
	ast::NodeArray* narray;
	ast::Ident* ident;
	ast::StringLit* strlit;
	ast::IntLit* intlit;
	ast::DoubleLit* dbllit;
	ast::Arithmetic* arithmetic;
	ast::Bitwise* bitwise;
	ast::Assignment* assignment;
	ast::VariableDecl* vardecl;
	ast::Logic* logic;
	ast::Import* import;
	ast::FunctionCall* fcall;
	ast::FunctionDecl* fdecl;
	ast::Return* ret;
	ast::While* while_loop;
	ast::IncDec* inc_dec;
	ast::If* ifcond;
	ast::Boolean* boolean;
	ast::NullLit* nillit;
}

%type <ident> IDENT
%type <strlit> STR
%type <intlit> NUM_INTEGER
%type <dbllit> NUM_DOUBLE
%type <assignment> assignment
%type <narray> variable_decl variable_decl_list non_empty_call_args call_args
%type <vardecl> variable_decl_impl
%type <block> statement_list block
%type <arithmetic> arithmetic
%type <bitwise> bitwise
%type <logic> logic
%type <import> import
%type <fcall> fcall
%type <fdecl> fdecl anonymous_fdecl
%type <ret> return_stmt
%type <while_loop> while
%type <inc_dec> inc_dec
%type <ifcond> if else
%type <boolean> boolean
%type <nillit> NIL

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
%token INC           "++"
%token DEC           "--"
%token NIL           "null"

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
		{ c.init(); } statement_list { c.emitAST($2); }
;

statement_list:
		/* empty */                { $$ = new ast::Block(yyloc); }
	|	statement_list statement   { $1->append($<node>2);       }
;

statement:
		import ';'
	|	variable_decl ';'
	|	assignment ';'
	|	fcall ';'
	|	fdecl
	|	return_stmt ';'
	|	if
	|	while
	|	inc_dec ';'
	|	block
;

block:
		'{' statement_list '}'  { $$ = $2; }
;

rvalue:
		IDENT
	|	STR
	|	NUM_INTEGER
	|	NUM_DOUBLE
	|	NIL
	|	arithmetic
	|	logic
	|	bitwise
	|	boolean
	|	inc_dec
	|	fcall
	|	anonymous_fdecl
	|	'(' rvalue ')' { $<node>$ = $<node>2; }
;

lvalue:
		IDENT
;

inc_dec:
		lvalue INC { $$ = new ast::IncDec(ast::IncDec::POS_INC, $<node>1, yyloc); }
	|	lvalue DEC { $$ = new ast::IncDec(ast::IncDec::POS_DEC, $<node>1, yyloc); }
	|	INC lvalue { $$ = new ast::IncDec(ast::IncDec::PRE_INC, $<node>2, yyloc); }
	|	DEC lvalue { $$ = new ast::IncDec(ast::IncDec::PRE_DEC, $<node>2, yyloc); }
;

boolean:
		rvalue BOOLEAN_OR rvalue  { $$ = new ast::Boolean(ast::Boolean::BOP_OR, $<node>1, $<node>3, yyloc);  }
	|	rvalue BOOLEAN_AND rvalue { $$ = new ast::Boolean(ast::Boolean::BOP_AND, $<node>1, $<node>3, yyloc); }
;

logic:
		rvalue EQUAL rvalue       { $$ = new ast::Logic(ast::Logic::LOP_EQUALS, $<node>1, $<node>3, yyloc);  }
	|	rvalue NOT_EQUAL rvalue   { $$ = new ast::Logic(ast::Logic::LOP_NEQUALS, $<node>1, $<node>3, yyloc); }
	|	rvalue LOGICAL_OR rvalue  { $$ = new ast::Logic(ast::Logic::LOP_OR, $<node>1, $<node>3, yyloc);      }
	|	rvalue LOGICAL_AND rvalue { $$ = new ast::Logic(ast::Logic::LOP_AND, $<node>1, $<node>3, yyloc);     }
;

arithmetic:
		rvalue '+' rvalue { $$ = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, $<node>1, $<node>3, yyloc); }
	|	rvalue '-' rvalue { $$ = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, $<node>1, $<node>3, yyloc); }
	|	rvalue '*' rvalue { $$ = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, $<node>1, $<node>3, yyloc); }
	|	rvalue '/' rvalue { $$ = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, $<node>1, $<node>3, yyloc); }
	|	rvalue '%' rvalue { $$ = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, $<node>1, $<node>3, yyloc); }
;

bitwise:
		rvalue '&' rvalue    { $$ = new ast::Bitwise(ast::Bitwise::BOP_AND, $<node>1, $<node>3, yyloc);    }
	|	rvalue '|' rvalue    { $$ = new ast::Bitwise(ast::Bitwise::BOP_OR, $<node>1, $<node>3, yyloc);     }
	|	rvalue '^' rvalue    { $$ = new ast::Bitwise(ast::Bitwise::BOP_XOR, $<node>1, $<node>3, yyloc);    }
	|	rvalue LSHIFT rvalue { $$ = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, $<node>1, $<node>3, yyloc); }
	|	rvalue RSHIFT rvalue { $$ = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, $<node>1, $<node>3, yyloc); }
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
	|	IDENT            { $$ = new ast::VariableDecl($1, new ast::Assignment($1, NULL, yyloc), yyloc); }
;

assignment:
		lvalue '=' rvalue { $$ = new ast::Assignment($<node>1, $<node>3, yyloc); }
;

import:
		IMPORT IDENT '.' IDENT '.' '*' { $$ = new ast::Import($2, $4, yyloc);   }
	|	IMPORT IDENT '.' '*'           { $$ = new ast::Import($2, NULL, yyloc); }
;

fdecl:
		FUNC IDENT '(' ')' block
		{ $$ = new ast::FunctionDecl($2, NULL, $5, yyloc); }
	|	FUNC IDENT '(' variable_decl_list ')' block
		{ $$ = new ast::FunctionDecl($2, $4, $6, yyloc); }
;

anonymous_fdecl:
		FUNC '(' ')' block
		{ $$ = new ast::FunctionDecl(NULL, NULL, $4, yyloc); }
	|	FUNC '(' variable_decl_list ')' block
		{ $$ = new ast::FunctionDecl(NULL, $3, $5, yyloc); }
;

call_args:
		/* empty */          { $$ = NULL; }
	|	non_empty_call_args
;

non_empty_call_args:
		rvalue                         { $$ = new ast::NodeArray(yyloc); $$->append($<node>1); }
	|	non_empty_call_args ',' rvalue { $1->append($<node>3); }
;

fcall:
		IDENT '(' call_args ')' { $$ = new ast::FunctionCall($1, $3, yyloc); }
;

return_stmt:
		RETURN rvalue { $$ = new ast::Return($<node>2, yyloc); }
	|	RETURN        { $$ = new ast::Return(NULL, yyloc); }
;

while:
		WHILE '(' rvalue ')' block
		{ $$ = new ast::While($<node>3, $5, yyloc); }
;

elseif:
		/* empty */
	|	elseif ELSEIF '(' rvalue ')' block
		{ $<ifcond>0->addConditional($<node>4, $6); }
;

else:
		/* empty */ { $$ = $<ifcond>0; }
	|	ELSE block  { $<ifcond>0->setElseNode($<node>2); $$ = $<ifcond>0; }
;

if:
		IF '(' rvalue ')' block { $<ifcond>$ = new ast::If($<node>3, $<node>5, yyloc); }
		elseif { $<ifcond>$ = $<ifcond>6; } else { $$ = $9; }

%%

namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever
