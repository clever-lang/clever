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
	size_t flags;
	ast::Node* node;
	ast::Block* block;
	ast::CriticalBlock* criticalblock;
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
	ast::For* for_loop;
	ast::IncDec* inc_dec;
	ast::If* ifcond;
	ast::Boolean* boolean;
	ast::NullLit* nillit;
	ast::Comparison* comp;
	ast::Type* type;
	ast::Instantiation* inst;
	ast::MethodCall* mcall;
	ast::Property* property;
	ast::Try* except;
	ast::Catch* catch_;
	ast::Throw* throw_;
	ast::TrueLit* true_;
	ast::FalseLit* false_;
	ast::Break* break_;
	ast::Continue* continue_;
	ast::AttrDecl* attr;
	ast::ClassDef* class_;
	ast::Switch* switch_;
}

%type <type> TYPE
%type <ident> IDENT CONSTANT import_ident_list fully_qualified_name
%type <strlit> STR
%type <intlit> NUM_INTEGER
%type <dbllit> NUM_DOUBLE
%type <true_> TRUE
%type <false_> FALSE
%type <inst> instantiation array map
%type <assignment> assignment
%type <narray> variable_decl variable_decl_list non_empty_call_args call_args
%type <narray> const_decl_list not_empty_catch catch key_value_list
%type <narray> class_attr_decl_list class_attr_const_decl_list class_attr_list class_attr_decl
%type <narray> class_method_decl class_method_list
%type <vardecl> variable_decl_impl vararg
%type <vardecl> const_decl_impl
%type <block> statement_list block finally
%type <criticalblock> critical_block
%type <arithmetic> arithmetic
%type <bitwise> bitwise
%type <logic> logic
%type <import> import
%type <fcall> fcall fcall_chain
%type <fdecl> fdecl anonymous_fdecl
%type <ret> return_stmt
%type <while_loop> while
%type <for_loop> for
%type <narray> for_expr_1 for_expr_3
%type <node> for_expr_2
%type <inc_dec> inc_dec
%type <ifcond> if else
%type <boolean> boolean
%type <nillit> NIL
%type <comp> comparison
%type <property> property_access
%type <except> try_catch_finally
%type <catch_> catch_impl
%type <throw_> throw
%type <break_> break
%type <continue_> continue
%type <class_> class_def
%type <attr> class_attr_decl_impl class_attr_const_decl_impl
%type <flags> visibility
%type <switch_> switch_expr case_list

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
%expect 1   /* map */

%code {
#include "core/driver.h"
}

%token END  0        "end of file"
%token VAR           "var"
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
%token FUNC          "function"
%token CRITICAL      "critical"
%token INC           "++"
%token DEC           "--"
%token NIL           "null"
%token NEW           "new"
%token FINALLY       "finally"
%token CATCH         "catch"
%token TRY           "try"
%token THROW         "throw"
%token CONTINUE      "continue"
%token CONSTANT      "constant identifier"
%token CLASS         "class"
%token PUBLIC        "public"
%token PRIVATE       "private"
%token SWITCH        "switch"
%token CASE          "case"
%token DEFAULT       "default"

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
%right '~' INC DEC;
%right '[' '{' '}';
%left ELSEIF;
%left ELSE;
%left UMINUS;

%%

%start program;

program:
		{ c.init(driver.getFile()); } statement_list { c.setAST($2); }
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
	|	mcall ';'
	|	fdecl
	|	return_stmt ';'
	|	if
	|	while
	|   for
	|	inc_dec ';'
	|	block
	|   critical_block
	|	throw ';'
	|	break ';'
	|	continue ';'
	|	try_catch_finally
	|	class_def
	|	fully_qualified_call ';'
	|	instantiation ';'
	|	switch_expr
;

block:
		'{' statement_list '}'  { $$ = $2; }
;

instantiation:
		TYPE '.' NEW                   { $$ = new ast::Instantiation($1, NULL, yyloc); }
	|	TYPE '.' NEW '(' call_args ')' { $$ = new ast::Instantiation($1, $5,   yyloc); }
;

break:
		BREAK { $$ = new ast::Break(yyloc); }
;

continue:
		CONTINUE { $$ = new ast::Continue(yyloc); }
;


critical_block:
		CRITICAL block {
#ifndef CLEVER_THREADS
		error(yyloc, "Cannot use critical block syntax, threads is disabled!"); YYABORT;
#else
		$$ = new ast::CriticalBlock($2, yyloc);
#endif
	}
;

object:
		IDENT
	|	CONSTANT
	|	STR
	|	NUM_INTEGER
	|	NUM_DOUBLE
	|	NIL
	|	TRUE
	|	FALSE
	|	map
	|	array
	|	'(' rvalue ')' { $<node>$ = $<node>2; }
	|	subscript
	|	fcall
;

rvalue:
		object
	|	unary
	|	arithmetic
	|	logic
	|	bitwise
	|	boolean
	|	comparison
	|	assignment    { $<assignment>1->setUseResult(); }
	|	inc_dec
	|	anonymous_fdecl
	|	instantiation
	|	mcall
	|	fully_qualified_call
	|	property_access
;

lvalue:
		IDENT
	|	property_access         { $1->setWriteMode(); }
	|	subscript
;

subscript:
		lvalue '[' rvalue ']'   { $<node>$ = new ast::Subscript($<node>1, $<node>3, yyloc); }
;

switch_expr:
		SWITCH '(' rvalue ')' '{' { $<node>$ = new ast::Switch($<node>3, yyloc); } case_list '}' { $$ = $7; }
;

label:
		IDENT
	|	CONSTANT
	|	STR
	|	NUM_INTEGER
	|	NUM_DOUBLE
	|	property_access
;

case_list:
		CASE label ':' statement_list           { $<switch_>0->addCase($<node>2, $4); $$ = $<switch_>0; }
	|	DEFAULT ':' statement_list              { $<switch_>0->addCase(NULL, $3); $$ = $<switch_>0;     }
	|	case_list CASE label ':' statement_list { $<switch_>0->addCase($<node>3, $5); $$ = $<switch_>0; }
	|	case_list DEFAULT ':' statement_list    { $<switch_>0->addCase(NULL, $4); $$ = $<switch_>0;     }
;

unary:
		'-' rvalue %prec UMINUS { $<node>$ = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, new ast::IntLit(0, yyloc), $<node>2, yyloc); }
	|	'+' rvalue %prec UMINUS { $<node>$ = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, new ast::IntLit(0, yyloc), $<node>2, yyloc); }
	|	'!' rvalue              { $<node>$ = new ast::Boolean(ast::Boolean::BOP_NOT, $<node>2, yyloc);                                  }
	|	'~' rvalue              { $<node>$ = new ast::Bitwise(ast::Bitwise::BOP_NOT, $<node>2, yyloc);                                  }
;

class_def:
		CLASS TYPE '{' class_attr_decl class_method_decl '}' { $$ = new ast::ClassDef($2, $4, $5, yyloc); }
;

class_attr_decl:
		/* empty */      { $$ = NULL; }
	|	class_attr_list
;

class_attr_list:
		{ $<narray>$ = new ast::NodeArray(yyloc); } non_empty_class_attr_list ';' { $$ = $<narray>1; }
	|	class_attr_list { $<narray>$ = $1; } non_empty_class_attr_list ';'
;

non_empty_class_attr_list:
		VAR   { $<narray>$ = $<narray>0; } class_attr_decl_list
	|	CONST { $<narray>$ = $<narray>0; } class_attr_const_decl_list
;

attr_rvalue:
		IDENT
	|	CONSTANT
	|	STR
	|	NUM_INTEGER
	|	NUM_DOUBLE
	|	NIL
	|	TRUE
	|	FALSE
;

class_attr_decl_list:
		class_attr_decl_impl  { $<narray>0->append($1); }
	|	class_attr_decl_list ',' class_attr_decl_impl { $<narray>0->append($3); }
;

class_attr_decl_impl:
		IDENT '=' attr_rvalue { $$ = new ast::AttrDecl($1, $<node>3, false, yyloc); }
	|	IDENT                 { $$ = new ast::AttrDecl($1, NULL, false, yyloc);     }
;

class_attr_const_decl_list:
		class_attr_const_decl_impl { $$ = new ast::NodeArray(yyloc); $$->append($1); }
	|	class_attr_const_decl_list ',' class_attr_const_decl_impl { $1->append($3); }
;

class_attr_const_decl_impl:
		IDENT '=' attr_rvalue { $$ = new ast::AttrDecl($1, $<node>3, true, yyloc);   }
;

class_method_decl:
		/* empty */  { $$ = NULL; }
	|	class_method_list
;

visibility:
		/* empty */ { $$ = ast::PUBLIC;  }
	|	PUBLIC      { $$ = ast::PUBLIC;  }
	|	PRIVATE     { $$ = ast::PRIVATE; }
;

class_method_list:
		visibility fdecl                   { $$ = new ast::NodeArray(yyloc); $$->append($2); $2->setVisibility($1); }
	|	class_method_list visibility fdecl { $1->append($3); $3->setVisibility($2); }
;

array:
		'[' call_args ']'  { $$ = new ast::Instantiation(CSTRING("Array"), $2, yyloc); }
;

key_value_list:
		STR ':' rvalue                    { $$ = new ast::NodeArray(yyloc); $$->append($1); $$->append($<node>3); }
	|	key_value_list ',' STR ':' rvalue { $1->append($3); $1->append($<node>5);                                 }
;

map:
		'{' ':' '}'             { $$ = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
	|	'{' key_value_list '}'  { $$ = new ast::Instantiation(CSTRING("Map"), $2, yyloc);   }
;

throw:
		THROW rvalue { $$ = new ast::Throw($<node>2, yyloc); }
;

catch:
		not_empty_catch
;

not_empty_catch:
		catch_impl                 { $$ = new ast::NodeArray(yyloc); $$->append($1); }
	|	not_empty_catch catch_impl { $1->append($2);                                 }
;

catch_impl:
		CATCH '(' IDENT ')' block { $$ = new ast::Catch($3, $5, yyloc); }
;

finally:
		/* empty */   { $$ = NULL; }
	|	FINALLY block { $$ = $2;   }
;

try_catch_finally:
		TRY block catch finally { $$ = new ast::Try($2, $3, $4, yyloc); }
;

property_access:
		object '.' IDENT    { $$ = new ast::Property($<node>1, $3, yyloc); }
	|	TYPE '.' IDENT      { $$ = new ast::Property($1, $3, yyloc); }
	|	object '.' CONSTANT { $$ = new ast::Property($<node>1, $3, yyloc); }
	|	TYPE '.' CONSTANT   { $$ = new ast::Property($1, $3, yyloc); }
	|	property_access '.' IDENT    { $$ = new ast::Property($<node>1, $3, yyloc); }
	|	property_access '.' CONSTANT { $$ = new ast::Property($<node>1, $3, yyloc); }
;

mcall_chain:
		/* empty */                             { $<mcall>$ = $<mcall>0; }
	|	mcall_chain '.' IDENT '(' call_args ')' { $<mcall>$ = new ast::MethodCall($<node>0, $3, $5, yyloc); }
	|	mcall_chain '.' IDENT                   { $<property>$ = new ast::Property($<node>1, $3, yyloc); }
	|	mcall_chain '.' CONSTANT                { $<property>$ = new ast::Property($<node>1, $3, yyloc); $<property>$->setStatic(); }
;

mcall:
		object '.' IDENT '(' call_args ')'          { $<node>$ = new ast::MethodCall($<node>1, $3, $5, yyloc); } mcall_chain { $<node>$ = $<node>8; }
	|	property_access '.' IDENT '(' call_args ')' { $<node>$ = new ast::MethodCall($<node>1, $3, $5, yyloc); } mcall_chain { $<node>$ = $<node>8; }
	|	TYPE '.' IDENT '(' call_args ')'            { $<node>$ = new ast::MethodCall($1, $3, $5, yyloc); }       mcall_chain { $<node>$ = $<node>8; }
;

inc_dec:
		object INC { $$ = new ast::IncDec(ast::IncDec::POS_INC, $<node>1, yyloc); }
	|	object DEC { $$ = new ast::IncDec(ast::IncDec::POS_DEC, $<node>1, yyloc); }
	|	INC object { $$ = new ast::IncDec(ast::IncDec::PRE_INC, $<node>2, yyloc); }
	|	DEC object { $$ = new ast::IncDec(ast::IncDec::PRE_DEC, $<node>2, yyloc); }
	|	property_access INC { $$ = new ast::IncDec(ast::IncDec::POS_INC, $<node>1, yyloc); $1->setWriteMode(); }
	|	property_access DEC { $$ = new ast::IncDec(ast::IncDec::POS_DEC, $<node>1, yyloc); $1->setWriteMode(); }
	|	INC property_access { $$ = new ast::IncDec(ast::IncDec::PRE_INC, $<node>2, yyloc); $2->setWriteMode(); }
	|	DEC property_access { $$ = new ast::IncDec(ast::IncDec::PRE_DEC, $<node>2, yyloc); $2->setWriteMode(); }
;

comparison:
		rvalue EQUAL rvalue         { $$ = new ast::Comparison(ast::Comparison::COP_EQUAL,   $<node>1, $<node>3, yyloc); }
	|	rvalue NOT_EQUAL rvalue     { $$ = new ast::Comparison(ast::Comparison::COP_NEQUAL,  $<node>1, $<node>3, yyloc); }
	|	rvalue GREATER rvalue       { $$ = new ast::Comparison(ast::Comparison::COP_GREATER, $<node>1, $<node>3, yyloc); }
	|	rvalue GREATER_EQUAL rvalue { $$ = new ast::Comparison(ast::Comparison::COP_GEQUAL,  $<node>1, $<node>3, yyloc); }
	|	rvalue LESS rvalue          { $$ = new ast::Comparison(ast::Comparison::COP_LESS,    $<node>1, $<node>3, yyloc); }
	|	rvalue LESS_EQUAL rvalue    { $$ = new ast::Comparison(ast::Comparison::COP_LEQUAL,  $<node>1, $<node>3, yyloc); }
;

boolean:
		rvalue BOOLEAN_OR rvalue  { $$ = new ast::Boolean(ast::Boolean::BOP_OR, $<node>1, $<node>3, yyloc);  }
	|	rvalue BOOLEAN_AND rvalue { $$ = new ast::Boolean(ast::Boolean::BOP_AND, $<node>1, $<node>3, yyloc); }
;

logic:
		rvalue LOGICAL_OR rvalue  { $$ = new ast::Logic(ast::Logic::LOP_OR, $<node>1, $<node>3, yyloc);      }
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
	|	CONST const_decl_list  { $$ = $2; }
;

variable_decl_list:
		variable_decl_impl                        { $$ = new ast::NodeArray(yyloc); $$->append($1); }
	|	variable_decl_list ',' variable_decl_impl { $1->append($3); }
;

variable_decl_impl:
		IDENT '=' rvalue { $$ = new ast::VariableDecl($1, new ast::Assignment($1, $<node>3, yyloc), false, yyloc); }
	|	IDENT            { $$ = new ast::VariableDecl($1, new ast::Assignment($1, NULL, yyloc), false, yyloc); }
;

const_decl_list:
		const_decl_impl                     { $$ = new ast::NodeArray(yyloc); $$->append($1); }
	|	const_decl_list ',' const_decl_impl { $1->append($3); }
;

const_decl_impl:
		CONSTANT '=' rvalue { $$ = new ast::VariableDecl($1, new ast::Assignment($1, $<node>3, yyloc), true, yyloc); }
;

assignment:
		lvalue '=' rvalue { $$ = new ast::Assignment($<node>1, $<node>3, yyloc); }
;

import_ident_list:
		IDENT                        { $$ = $1; }
	|	import_ident_list '.' IDENT  { $1->append('.', $3); $$ = $1; }
;

import:
		IMPORT import_ident_list '.' '*'   { $$ = new ast::Import($2, yyloc);     }
	|	IMPORT import_ident_list ':' '*'   { $$ = new ast::Import($2, yyloc);     }
	|	IMPORT import_ident_list ':' IDENT { $$ = new ast::Import($2, $4, yyloc); }
	|	IMPORT import_ident_list ':' TYPE  { $$ = new ast::Import($2, $4, yyloc); }
	|	IMPORT import_ident_list           { $$ = new ast::Import($2, yyloc); $$->setNamespaced(true); }
;

vararg:
		IDENT '.' '.' '.' { $$ = new ast::VariableDecl($1, new ast::Assignment($1, NULL, yyloc), false, yyloc); }
;

fdecl:
		FUNC IDENT '(' ')' block
		{ $$ = new ast::FunctionDecl($2, NULL, $5, NULL, false, yyloc); }
	|	FUNC TYPE '(' ')' block
		{ $$ = new ast::FunctionDecl($2, NULL, $5, NULL, yyloc); $$->setCtor(); }
	|	FUNC '~' TYPE '(' ')' block
		{ $$ = new ast::FunctionDecl($3, NULL, $6, NULL, yyloc); $$->setDtor(); }
	|	FUNC IDENT '(' vararg ')' block
		{ $$ = new ast::FunctionDecl($2, NULL, $6, $4, false, yyloc); }
	|	FUNC TYPE '(' vararg ')' block
		{ $$ = new ast::FunctionDecl($2, NULL, $6, $4, yyloc); $$->setCtor(); }
	|	FUNC IDENT '(' variable_decl_list ')' block
		{ $$ = new ast::FunctionDecl($2, $4, $6, NULL, false, yyloc); }
	|	FUNC TYPE '(' variable_decl_list ')' block
		{ $$ = new ast::FunctionDecl($2, $4, $6, NULL, yyloc); $$->setCtor(); }
	|	FUNC IDENT '(' variable_decl_list ',' vararg ')' block
		{ $$ = new ast::FunctionDecl($2, $4, $8, $6, false, yyloc); }
	|	FUNC TYPE '(' variable_decl_list ',' vararg ')' block
		{ $$ = new ast::FunctionDecl($2, $4, $8, $6, yyloc); $$->setCtor(); }
;

anonymous_fdecl:
		FUNC '(' ')' block
		{ $$ = new ast::FunctionDecl(NULL, NULL, $4, NULL, true, yyloc); }
	|	FUNC '(' vararg ')' block
		{ $$ = new ast::FunctionDecl(NULL, NULL, $5, $3, true, yyloc); }
	|	FUNC '(' variable_decl_list ')' block
		{ $$ = new ast::FunctionDecl(NULL, $3, $5, NULL, true, yyloc); }
	|	FUNC '(' variable_decl_list ',' vararg ')' block
		{ $$ = new ast::FunctionDecl(NULL, $3, $7, $5, true, yyloc); }
;

call_args:
		/* empty */          { $$ = NULL; }
	|	non_empty_call_args
;

non_empty_call_args:
		rvalue                         { $$ = new ast::NodeArray(yyloc); $$->append($<node>1); }
	|	non_empty_call_args ',' rvalue { $1->append($<node>3); }
;

fcall_chain:
		/* empty */                   { $$ = $<fcall>0; }
	|	fcall_chain '(' call_args ')' { $$ = new ast::FunctionCall($<node>1, $3, yyloc); }
	|	fcall_chain '[' rvalue ']'    { $<node>$ = new ast::Subscript($<node>1, $<node>3, yyloc); }
;

fully_qualified_name:
		IDENT
	|	fully_qualified_name ':' IDENT { $1->append(':', $3); $<ident>$ = $1; }
;

fully_qualified_call:
		fully_qualified_name ':' IDENT '(' call_args ')'          { $1->append(':', $3); $<fcall>$ = new ast::FunctionCall($1, $5, yyloc); } fcall_chain { $<fcall>$ = $8; }
	|	fully_qualified_name ':' CONSTANT                         { $1->append(':', $3); }
	|	fully_qualified_name ':' IDENT                            { $1->append(':', $3); }
	|	fully_qualified_name ':' TYPE '.' CONSTANT                { $1->append(':', $3); $<property>$ = new ast::Property(new ast::Type($1->getName(), yyloc), $5, yyloc); clever_delete($1); }
	|	fully_qualified_name ':' TYPE '.' NEW                     { $1->append(':', $3); $<inst>$ = new ast::Instantiation($1, NULL, yyloc); }
	|	fully_qualified_name ':' TYPE '.' NEW '(' call_args ')'   { $1->append(':', $3); $<inst>$ = new ast::Instantiation($1, $7,   yyloc); }
	|	fully_qualified_name ':' TYPE '.' IDENT '(' call_args ')' { $1->append(':', $3); $<mcall>$ = new ast::MethodCall(new ast::Type($1->getName(), yyloc), $5, $7, yyloc); clever_delete($1); } mcall_chain { $<node>$ = $<node>10; }
;

fcall:
		IDENT '(' call_args ')' { $<fcall>$ = new ast::FunctionCall($1, $3, yyloc); } fcall_chain { $$ = $6; }
;

return_stmt:
		RETURN rvalue { $$ = new ast::Return($<node>2, yyloc); }
	|	RETURN        { $$ = new ast::Return(NULL, yyloc); }
;

while:
		WHILE '(' rvalue ')' block { $$ = new ast::While($<node>3, $5, yyloc); }
;

for_expr_1:
		/* empty */         { $$ = NULL; }
	|	variable_decl
	|	non_empty_call_args
;

for_expr_2:
		/* empty */     { $$ = NULL;     }
	|	rvalue          { $$ = $<node>1; }
;

for_expr_3:
		call_args
;

for:
		FOR '(' for_expr_1 ';' for_expr_2 ';' for_expr_3 ')' block { $$ = new ast::For($3, $5, $7, $9, yyloc); }
;

elseif:
		/* empty */
	|	elseif ELSEIF '(' rvalue ')' block { $<ifcond>0->addConditional($<node>4, $6); }
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
