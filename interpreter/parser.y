%skeleton "lalr1.cc"
%require "2.4.1"
%defines
%define namespace "clever"
%define parser_class_name "Parser"

%code requires {
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

#include <stack>
#include "interpreter/scanner.h"
#include "interpreter/ast.h"

namespace clever {
class Driver;
class Compiler;
} // clever
}

// The parsing context.
%parse-param { Driver& driver }
%parse-param { ScannerState& state }
%parse-param { Compiler& compiler }
%lex-param   { Driver& driver }
%lex-param   { ScannerState& state }

%locations
%initial-action {
@$.begin.filename = @$.end.filename = driver.getFile();
};

%debug
%error-verbose

%code {
#include "interpreter/driver.h"

namespace clever {

} // clever
}

%token END  0        "end of file"
%token EXIT          "exit"
%token TYPE          "type specification"
%token IDENT         "identifier"
%token NUM_INTEGER   "number"
%token NUM_DOUBLE    "float-number"
%token STR           "string"
%token IN            "in"
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
%token EXTERN        "extern"
%token PLUS_EQUAL    "+="
%token MULT_EQUAL    "*="
%token DIV_EQUAL     "/="
%token MINUS_EQUAL   "-="
%token MOD_EQUAL     "%="
%token AUTO_EQUAL    ":="
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
%token TRUE          "true"
%token FALSE         "false"
%token AS            "as"
%token DOUBLE_COLON  "::"
%token CONSTANT      "constant"
%token USE           "use"
%token REGEX         "regex-pattern"
%token CONST         "const"
%token AUTO          "auto"
%token ANNOTATION    "@@"

%left ',';
%left LOGICAL_OR;
%left LOGICAL_AND;
%right '=' PLUS_EQUAL MINUS_EQUAL DIV_EQUAL MULT_EQUAL MOD_EQUAL BW_OR_EQUAL XOR_EQUAL BW_AND_EQUAL  RSHIFT_EQUAL LSHIFT_EQUAL  ;
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
%right '~' INCREMENT DECREMENT;
%right '[' '{';
%left ELSEIF;
%left ELSE;
%left UMINUS;

%union {
	ast::ASTNode* ast_node;
	ast::Identifier* identifier;
	ast::ArgumentDeclList* arg_decl_list;
	ast::MethodCall* method_call;
	ast::FunctionCall* func_call;
	ast::Constant* constant;
	ast::IfExpr* if_expr;
	ast::NumberLiteral* num_literal;
	ast::StringLiteral* str_literal;
	ast::ClassStmtList* class_stmt;
	ast::ReturnStmt* return_stmt;
	ast::VariableDecl* variable_decl;
	ast::VariableDecls* variable_decls;
	ast::ClassDeclaration* class_decl;
	ast::FuncDeclaration* func_decl;
	ast::FuncPrototype* func_proto;
	ast::ExtFuncDeclaration* ext_func_decl;
	ast::ExtFuncDecls* ext_func_decls;
	ast::MethodDeclaration* method_decl;
	ast::AttributeDeclaration* attr_decl;
	ast::ForExpr* for_expr;
	ast::WhileExpr* while_expr;
	ast::ElseIfExpr* elseif_opt;
	ast::BlockNode* block_stmt;
	ast::UnscopedBlockNode* block_stmt2;
	ast::BreakNode* break_stmt;
	ast::ImportStmt* import_stmt;
	ast::AssignExpr* assign_stmt;
	ast::ArgumentList* arg_list;
	ast::BinaryExpr* binary_expr;
	ast::IntegralValue* integral_value;
	ast::TemplateArgsVector* template_args;
	ast::AliasStmt* alias_stmt;
	ast::RegexPattern* regex_pattern;
	ast::NodeList* node_list;
	ast::VarDecls* var_decls;
	ast::ArrayList* array_list;
	ast::MapList* map_list;
	ast::LambdaFunction* lambda_function;
}

%type <identifier> IDENT
%type <num_literal> NUM_INTEGER
%type <num_literal> NUM_DOUBLE
%type <str_literal> STR

%type <identifier> package_module_name
%type <identifier> func_name
%type <identifier> TYPE
%type <identifier> type_name
%type <regex_pattern> REGEX
%type <identifier> CONSTANT
%type <constant> constant
%type <template_args> template_args
%type <template_args> template_args_fix
%type <ast_node> literal
%type <identifier> template
%type <ast_node> statement_list_non_empty
%type <ast_node> statement_list
%type <block_stmt> block_stmt
%type <ast_node> statements
%type <return_stmt> return_stmt
%type <arg_decl_list> args_declaration_non_empty
%type <arg_decl_list> args_declaration
%type <func_decl> func_declaration
%type <func_proto> func_prototype
%type <ext_func_decl> ext_func_declaration
%type <ext_func_decls> ext_func_declaration_list
%type <ext_func_decls> ext_func_declaration_list_impl
%type <ext_func_decl> ext_func_declaration_list_aux
%type <class_decl> class_declaration
%type <integral_value> access_modifier
%type <class_stmt> class_stmt
%type <class_stmt> class_stmt_no_empty
%type <method_decl> method_declaration
%type <attr_decl> attribute_declaration
%type <arg_list> arg_list
%type <arg_list> arg_list_opt
%type <func_call> func_call
%type <method_call> chaining_method_call
%type <method_call> method_call
%type <variable_decl> variable_decl_or_empty
%type <variable_decl> variable_declaration
%type <variable_decl> variable_declaration_impl
%type <variable_decls> variable_declaration_list
%type <variable_decls> variable_declaration_list_impl
%type <variable_decls> variable_declaration_list_creation
%type <variable_decls> auto_variable_declaration_list_creation
%type <variable_decl> variable_declaration_list_creation_aux
%type <variable_decl> auto_variable_declaration_list_creation_aux
%type <ast_node> assign_stmt
%type <ast_node> expr
%type <ast_node> expr_or_empty
%type <for_expr> for_expr
%type <while_expr> while_expr
%type <if_expr> if_expr
%type <elseif_opt> elseif_opt
%type <block_stmt> else_opt
%type <break_stmt> break_stmt
%type <import_stmt> import_stmt
%type <import_stmt> import_stmt2
%type <block_stmt2> import_file
%type <alias_stmt> alias_stmt
%type <array_list> array_list
%type <arg_list> map_arg_list
%type <map_list> map_list
%type <lambda_function> lambda_function
%type <ast_node> annotation

%%

%start top_statements;

top_statements:
		{ driver.initCompiler(); } statement_list { driver.emitAST($2); }
;

statement_list:
		/* empty */               { $<ast_node>$ = new ast::BlockNode(); }
	|	statement_list_non_empty  { $$ = $<ast_node>1; }
;

statement_list_non_empty:
		statements                          					{ $<ast_node>$ = new ast::BlockNode(); $$->add($1); }
	|	statement_list_non_empty statements 					{ $1->add($2); $$ = $1; }
;

block_stmt:
		'{' '}'                          { $$ = new ast::BlockNode(); }
	|	'{' statement_list_non_empty '}' { $$ = $<block_stmt>2; }
;

statements:
		expr ';'	             		{ $$ = $<ast_node>1; }
	|	variable_declaration ';' 		{ $$ = $<ast_node>1; }
	|	variable_declaration_list ';'		{ $$ = new ast::VarDecls($<node_list>1); }
	|	func_declaration       			{ $$ = $<ast_node>1; }
	|	func_prototype				{ $$ = $<ast_node>1; }
	|	ext_func_declaration ';'    		{ $$ = $<ast_node>1; }
	|	ext_func_declaration_list 		{ $$ = new ast::VarDecls($<node_list>1); }
	|	if_expr                  		{ $$ = $<ast_node>1; }
	|	for_expr                 		{ $$ = $<ast_node>1; }
	|	while_expr               		{ $$ = $<ast_node>1; }
	|	block_stmt               		{ $$ = $<ast_node>1; }
	|	break_stmt ';'           		{ $$ = $<ast_node>1; }
	|	import_stmt ';'          		{ $$ = $<ast_node>1; }
	|	import_file ';'          		{ $$ = $<ast_node>1; }
	|	return_stmt ';'          		{ $$ = $<ast_node>1; }
	|	class_declaration	     		{ $$ = $<ast_node>1; }
	|	alias_stmt ';'           		{ $$ = $<ast_node>1; }
;

return_stmt:
		RETURN expr { $$ = new ast::ReturnStmt($2); $$->setLocation(yylloc); }
	|	RETURN      { $$ = new ast::ReturnStmt();   $$->setLocation(yylloc); }
;

args_declaration_non_empty:
		TYPE IDENT                      	{ $$ = new ast::ArgumentDeclList(); $$->addArg($1, $2); }
	|	template IDENT				{ $$ = new ast::ArgumentDeclList(); $$->addArg($1, $2); }
	|	args_declaration ',' TYPE IDENT 	{ $1->addArg($3, $4); }
	|	args_declaration ',' template IDENT { $1->addArg($3, $4); }
;

args_declaration:
		/* empty */ { $$ = NULL; }
	|	args_declaration_non_empty
;

annotation:
		ANNOTATION            { $$ = NULL; }
	|	annotation ANNOTATION { $$ = NULL; }
;

func_prototype:
		TYPE IDENT '(' args_declaration ')' ';' { $$ = new ast::FuncPrototype($2, $1, $4); }
;

func_declaration:
		TYPE IDENT '(' args_declaration ')' block_stmt { $$ = new ast::FuncDeclaration($2, $1, $4, $6); }
	|	CONST TYPE IDENT '(' args_declaration ')' block_stmt { $$ = new ast::FuncDeclaration($3, $2, $5, $7, true); }
	|	annotation TYPE IDENT '(' args_declaration ')' block_stmt { $$ = new ast::FuncDeclaration($3, $2, $5, $7); }
	|	template IDENT '(' args_declaration ')' block_stmt { $$ = new ast::FuncDeclaration($2, $1, $4, $6); }
	|	annotation template IDENT '(' args_declaration ')' block_stmt { $$ = new ast::FuncDeclaration($3, $2, $5, $7); }
;

lambda_function:
		TYPE '(' args_declaration ')' block_stmt     {
			$$ = new ast::LambdaFunction(new ast::FuncDeclaration(ast::LambdaFunction::getLambdaId(), $1, $3, $5));
		}
	|	template '(' args_declaration ')' block_stmt {
			$$ = new ast::LambdaFunction(new ast::FuncDeclaration(ast::LambdaFunction::getLambdaId(), $1, $3, $5));
		}
;

ext_func_declaration:
		EXTERN STR TYPE IDENT '(' args_declaration ')' { $$ = new ast::ExtFuncDeclaration($2, $4, $3, $6); }
;

ext_func_declaration_list_aux:
		TYPE IDENT '(' args_declaration ')' ';'		{ $$ = new ast::ExtFuncDeclaration(NULL, $2, $1, $4); }
	|	TYPE IDENT '(' args_declaration ')' AS  STR ';'	{ $$ = new ast::ExtFuncDeclaration(NULL, $2, $1, $4, $7); }
;
ext_func_declaration_list_impl:
		ext_func_declaration_list_aux 					{ $$ = new ast::ExtFuncDecls; $$->push_back($1);}
	|	ext_func_declaration_list_impl  ext_func_declaration_list_aux 	{ $$ = $1; $$->push_back($2); }
;

ext_func_declaration_list:
	EXTERN STR '{' ext_func_declaration_list_impl '}' { $$ = $4; ast::_set_libname_ext_func_decl($$,$2); }
;


class_declaration:
		CLASS TYPE '{' class_stmt '}' { $$ = new ast::ClassDeclaration($2, $4); }
;

access_modifier:
		PUBLIC          { $$ = new ast::IntegralValue(0x1); }
	| 	PRIVATE         { $$ = new ast::IntegralValue(0x2); }
	| 	PROTECTED       { $$ = new ast::IntegralValue(0x4); }
;

class_stmt:
		/* empty */             { $$ = new ast::ClassStmtList; $$->setLocation(yyloc); }
	|	class_stmt_no_empty     { $$ = $1; }
;

class_stmt_no_empty:
		class_stmt attribute_declaration        { $1->addAttribute($2); $$ = $1; }
	|	class_stmt method_declaration           { $1->addMethod($2); $$ = $1; }
;

method_declaration:
		access_modifier TYPE IDENT '(' args_declaration ')' block_stmt { $$ = new ast::MethodDeclaration($1, $2, $3, $5, $7); $$->setLocation(yyloc); }
;

attribute_declaration:
		access_modifier TYPE IDENT ';'	{ $$ = new ast::AttributeDeclaration($1, $2, $3); $$->setLocation(yyloc); }
;

arg_list:
		arg_list ',' expr  { $1->add($3); }
	|	expr               { $$ = new ast::ArgumentList; $$->add($1); }
;

arg_list_opt:
		/* empty */  { $$ = NULL; }
	| 	arg_list     { $$ = $1; }
;

array_list:
		'[' arg_list ']'	{ $$ = new ast::ArrayList($2); $$->setLocation(yyloc); }
;

map_arg_list:
		map_arg_list ',' expr ':' expr 	{ $1->add($3); $1->add($5); }
	|	expr ':' expr         			{ $$ = new ast::ArgumentList; $$->add($1); $$->add($3); }
;

map_list:
		'{' map_arg_list '}'		{ $$ = new ast::MapList($2); $$->setLocation(yyloc); }
;

package_module_name:
		IDENT '.' IDENT  { $<identifier>1->concat(".", $3); delete $3; }
	|	IDENT            { $$ = $1; }
;

func_name:
		package_module_name "::" IDENT { $1->concat("::", $3); delete $3; }
	|	IDENT                          { $$ = $1; }
;

type_name:
		package_module_name "::" TYPE { $1->concat("::", $3); delete $3; }
	|	TYPE                          { $$ = $1; }
;

func_call:
		func_name '(' arg_list_opt ')' { $$ = new ast::FunctionCall($1, $3); $$->setLocation(yylloc); }
;

chaining_method_call:
		/* empty */                                         { $$ = $<method_call>0; }
	|	chaining_method_call '.' IDENT '(' arg_list_opt ')' { $$ = new ast::MethodCall($1, $3, $5); $$->setLocation(yylloc); }
;

method_call:
		IDENT '.' IDENT '(' arg_list_opt ')'   { $<method_call>$ = new ast::MethodCall($1, $3, $5); $<method_call>$->setLocation(yylloc); }
			chaining_method_call               { $$ = $8; }
	|	literal '.' IDENT '(' arg_list_opt ')' { $<method_call>$ = new ast::MethodCall($1, $3, $5); $<method_call>$->setLocation(yylloc); }
			chaining_method_call               { $$ = $8; }
	|	func_call '.' IDENT '(' arg_list_opt ')' { $<method_call>$ = new ast::MethodCall($1, $3, $5); $<method_call>$->setLocation(yylloc); }
			chaining_method_call               { $$ = $8; }
	|	IDENT '[' expr ']' '.' IDENT '(' arg_list_opt ')' { $<method_call>$ = new ast::MethodCall(new ast::Subscript($1, $3), $6, $8); $<method_call>$->setLocation(yylloc); }
			chaining_method_call               { $$ = $11; }
	|	'(' expr ')' '.' IDENT '(' arg_list_opt ')'	   { $<method_call>$ = new ast::MethodCall($2, $5, $7); $<method_call>$->setLocation(yylloc); }
			chaining_method_call               { $$ = $10; }
	|	type_name '.' IDENT '(' arg_list_opt ')'    { $<method_call>$ = new ast::MethodCall($1, $3, $5, true); $<method_call>$->setLocation(yylloc); }
			chaining_method_call               { $$ = $8; }
;

template_args:
		type_name      				{ $<template_args>$ = new ast::TemplateArgsVector; $<template_args>$->push_back($1); }
	|	template_args ',' TYPE  	{ $1->push_back($3); }
	|   template_args ',' template	{ $1->push_back($3); }
	|	template					{ $<template_args>$ = new ast::TemplateArgsVector; $<template_args>$->push_back($1); }
;

template_args_fix:
		TYPE "<" template_args				     { $<template_args>$ = new ast::TemplateArgsVector;
											       $1->setTemplateArgs($3);
											       $<template_args>$->push_back($1);
											     }
	|	template_args ',' TYPE "<" template_args { $$ = $1; $3->setTemplateArgs($5); $1->push_back($3); }
;

template:
		TYPE "<" template_args ">"       { $1->setTemplateArgs($3); }
	|	TYPE "<" template_args_fix ">>"	 { $1->setTemplateArgs($3); }
;

variable_declaration_list:
		variable_declaration_list_impl			{ $$ = $1; }
	|	CONST variable_declaration_list_impl	{ ast::setConstness($2,true); $$ = $2; }
;

variable_declaration_list_impl:
		TYPE variable_declaration_list_creation								{ ast::setType($2, $1); $$ = $2; }
	|	template variable_declaration_list_creation							{ ast::setType($2, $1); $$ = $2; }
	|	package_module_name "::" TYPE variable_declaration_list_creation
		{ $1->concat("::", $3); delete $3; ast::setType($4, $1); $$ = $4; }
	|	AUTO auto_variable_declaration_list_creation 						{ $$ = $2; }
;

auto_variable_declaration_list_creation:
		auto_variable_declaration_list_creation_aux	',' auto_variable_declaration_list_creation_aux	{ $<variable_decls>$ = new ast::VariableDecls(); $$->push_back($1); $$->push_back($3); }
	|	auto_variable_declaration_list_creation ',' auto_variable_declaration_list_creation_aux		{ $1->push_back($3); $$ = $1; }
;

auto_variable_declaration_list_creation_aux:
		IDENT '=' expr 				{ $$ = new ast::VariableDecl(NULL, $1, $3); $$->setLocation(yylloc); }
;

variable_declaration_list_creation:
		variable_declaration_list_creation_aux	',' variable_declaration_list_creation_aux	{ $<variable_decls>$ = new ast::VariableDecls(); $$->push_back($1); $$->push_back($3); }
	|	variable_declaration_list_creation ',' variable_declaration_list_creation_aux		{ $1->push_back($3); $$ = $1; }
;

variable_declaration_list_creation_aux:
		IDENT '=' expr 				{ $$ = new ast::VariableDecl(NULL, $1, $3); $$->setLocation(yylloc); }
	|	IDENT '(' arg_list ')'		{ $$ = new ast::VariableDecl(NULL, $1, $<arg_list>3); $$->setLocation(yyloc);   }
	|	IDENT						{ $$ = new ast::VariableDecl(NULL, $1);  }
;

variable_declaration:
		variable_declaration_impl			{ $$ = $1; }
	|	CONST variable_declaration_impl		{ $2->setConstness(true); $$ = $2; }
;

variable_declaration_impl:
		AUTO IDENT '=' expr					{ $$ = new ast::VariableDecl(NULL, $2, $4); $$->setLocation(yylloc); }
	|	IDENT ":=" expr						{ $$ = new ast::VariableDecl(NULL, $1, $3); $$->setLocation(yylloc); }
	|	TYPE IDENT '=' expr                 { $$ = new ast::VariableDecl($1, $2, $4); $$->setLocation(yylloc); }
	|	template IDENT '=' expr             { $$ = new ast::VariableDecl($1, $2, $4); $$->setLocation(yylloc); }
	|	package_module_name "::" TYPE IDENT '=' expr
		{ $1->concat("::", $3); delete $3; $$ = new ast::VariableDecl($1, $4, $6); $$->setLocation(yylloc); }

	|	TYPE IDENT                          { $$ = new ast::VariableDecl($1, $2); }
	|	template IDENT                      { $$ = new ast::VariableDecl($1, $2); }
	|	package_module_name "::" TYPE IDENT { $1->concat("::", $3); delete $3; $$ = new ast::VariableDecl($1, $4); $$->setLocation(yyloc); }

	|   TYPE IDENT '(' arg_list ')'         { $$ = new ast::VariableDecl($1, $2, $<arg_list>4); $$->setLocation(yyloc);   }
	|   template IDENT '(' arg_list ')'     { $$ = new ast::VariableDecl($1, $2, $<arg_list>4); $$->setLocation(yyloc);   }
	|	package_module_name "::" TYPE IDENT '(' arg_list ')'
		{ $1->concat("::", $3); delete $3; $$ = new ast::VariableDecl($1, $4, $<arg_list>6); $$->setLocation(yyloc);  }
;

assign_stmt:
		IDENT '=' expr   %prec '=' { $$ = new ast::AssignExpr($1, $3);                   $$->setLocation(yylloc); }
	|	IDENT "+=" expr  %prec '=' { $$ = new ast::BinaryExpr(ast::PLUS, $1, $3, true);  $$->setLocation(yylloc); }
	|	IDENT "-=" expr  %prec '=' { $$ = new ast::BinaryExpr(ast::MINUS, $1, $3, true); $$->setLocation(yylloc); }
	|	IDENT "/=" expr  %prec '=' { $$ = new ast::BinaryExpr(ast::DIV, $1, $3, true);   $$->setLocation(yylloc); }
	|	IDENT "*=" expr  %prec '=' { $$ = new ast::BinaryExpr(ast::MULT, $1, $3, true);  $$->setLocation(yylloc); }
	|	IDENT "%=" expr  %prec '=' { $$ = new ast::BinaryExpr(ast::MOD, $1, $3, true);   $$->setLocation(yylloc); }
	|	IDENT "&=" expr  %prec '=' { $$ = new ast::BinaryExpr(ast::AND, $1, $3, true);   $$->setLocation(yylloc); }
	|	IDENT "|=" expr  %prec '=' { $$ = new ast::BinaryExpr(ast::OR, $1, $3, true);    $$->setLocation(yylloc); }
	|	IDENT "^=" expr  %prec '=' { $$ = new ast::BinaryExpr(ast::XOR, $1, $3, true);   $$->setLocation(yylloc); }
	|	IDENT "<<=" expr %prec '=' { $$ = new ast::BinaryExpr(ast::LSHIFT, $1, $3, true);   $$->setLocation(yylloc); }
	|	IDENT ">>=" expr %prec '=' { $$ = new ast::BinaryExpr(ast::RSHIFT, $1, $3, true);   $$->setLocation(yylloc); }
;

expr:
		expr '-' expr         { $$ = new ast::BinaryExpr(ast::MINUS, $1, $3);         $$->setLocation(yylloc); }
	|	expr '+' expr         { $$ = new ast::BinaryExpr(ast::PLUS, $1, $3);          $$->setLocation(yylloc); }
	|	expr '/' expr         { $$ = new ast::BinaryExpr(ast::DIV, $1, $3);           $$->setLocation(yylloc); }
	|	expr '*' expr         { $$ = new ast::BinaryExpr(ast::MULT, $1, $3);          $$->setLocation(yylloc); }
	|	expr '%' expr         { $$ = new ast::BinaryExpr(ast::MOD, $1, $3);           $$->setLocation(yylloc); }
	|	expr '|' expr         { $$ = new ast::BinaryExpr(ast::BW_OR, $1, $3);         $$->setLocation(yylloc); }
	|	expr '&' expr         { $$ = new ast::BinaryExpr(ast::BW_AND, $1, $3);        $$->setLocation(yylloc); }
	|	expr '^' expr         { $$ = new ast::BinaryExpr(ast::XOR, $1, $3);           $$->setLocation(yylloc); }
	|	expr ">" expr         { $$ = new ast::BinaryExpr(ast::GREATER, $1, $3);       $$->setLocation(yylloc); }
	|	expr ">=" expr        { $$ = new ast::BinaryExpr(ast::GREATER_EQUAL, $1, $3); $$->setLocation(yylloc); }
	|	expr "<" expr         { $$ = new ast::BinaryExpr(ast::LESS, $1, $3);          $$->setLocation(yylloc); }
	|	expr "<=" expr        { $$ = new ast::BinaryExpr(ast::LESS_EQUAL, $1, $3);    $$->setLocation(yylloc); }
	|	expr "<<" expr        { $$ = new ast::BinaryExpr(ast::LSHIFT, $1,$3);         $$->setLocation(yylloc); }
	|	expr ">>" expr        { $$ = new ast::BinaryExpr(ast::RSHIFT, $1,$3);         $$->setLocation(yylloc); }
	|	expr "==" expr        { $$ = new ast::BinaryExpr(ast::EQUAL, $1, $3);         $$->setLocation(yylloc); }
	|	expr "!=" expr        { $$ = new ast::BinaryExpr(ast::NOT_EQUAL, $1, $3);     $$->setLocation(yylloc); }
	|	expr "||" expr        { $$ = new ast::BinaryExpr(ast::OR, $1, $3);            $$->setLocation(yylloc); }
	|	expr "&&" expr        { $$ = new ast::BinaryExpr(ast::AND, $1, $3);           $$->setLocation(yylloc); }
	|	expr "or" expr        { $$ = new ast::BinaryExpr(ast::OR, $1, $3);            $$->setLocation(yylloc); }
	|	expr "and" expr       { $$ = new ast::BinaryExpr(ast::AND, $1, $3);           $$->setLocation(yylloc); }
	|	'-' expr %prec UMINUS { $$ = new ast::BinaryExpr(ast::MINUS, $2);             $$->setLocation(yylloc); }
	|	'+' expr %prec UMINUS { $$ = new ast::BinaryExpr(ast::PLUS, $2);              $$->setLocation(yylloc); }
	|	INCREMENT IDENT       { $$ = new ast::UnaryExpr(ast::PRE_INC, $2);            $$->setLocation(yylloc); }
	|	IDENT INCREMENT       { $$ = new ast::UnaryExpr(ast::POS_INC, $1);            $$->setLocation(yylloc); }
	|	DECREMENT IDENT       { $$ = new ast::UnaryExpr(ast::PRE_DEC, $2);            $$->setLocation(yylloc); }
	|	IDENT DECREMENT       { $$ = new ast::UnaryExpr(ast::POS_DEC, $1);            $$->setLocation(yylloc); }
	|	'!' expr              { $$ = new ast::UnaryExpr(ast::NOT, $2);                $$->setLocation(yylloc); }
	|	'~' expr              { $$ = new ast::UnaryExpr(ast::BW_NOT, $2);             $$->setLocation(yylloc); }
	|	'(' expr ')'          { $$ = $2; }
	|	func_call             { $$ = $<ast_node>1; }
	|	method_call           { $$ = $<ast_node>1; }
	|	IDENT '[' expr ']'    { $$ = new ast::Subscript($1, $3); $$->setLocation(yylloc); }
	|	IDENT                 { $$ = $<ast_node>1; }
	|	literal               { $$ = $<ast_node>1; }
	|	constant              { $$ = $<ast_node>1; }
	|	assign_stmt           { $$ = $<ast_node>1; }
	|	lambda_function       { $$ = $<ast_node>1; }
;

literal:
		NUM_INTEGER { $$ = $<ast_node>1; }
	|	NUM_DOUBLE  { $$ = $<ast_node>1; }
	|	STR         { $$ = $<ast_node>1; }
	|	TRUE        { $$ = $<ast_node>1; }
	|	FALSE       { $$ = $<ast_node>1; }
	|	REGEX 		{ $$ = $<ast_node>1; }
	|	array_list  { $$ = $<ast_node>1; }
	|	map_list	{ $$ = $<ast_node>1; }
;

variable_decl_or_empty:
		/* empty */          { $$ = NULL; }
	|	variable_declaration { $$ = $1; }
;

expr_or_empty:
		/* empty */ { $$ = NULL; }
	|	expr        { $$ = $1; }
;

for_expr:
		FOR '(' variable_decl_or_empty ';' expr_or_empty ';' expr_or_empty ')' block_stmt { $$ = new ast::ForExpr($3, $5, $7, $9); $$->setLocation(yylloc); }
//	|   FOR '(' variable_declaration_no_init IN  IDENT ')' block_stmt                     { $$ = new ast::ForExpr($3, $5, $7); $$->setLocation(yylloc); }
;

while_expr:
		WHILE '(' expr ')' block_stmt { $$ = new ast::WhileExpr($3, $5); $$->setLocation(yylloc); }
;

if_expr:
		IF '(' expr ')' block_stmt { $<if_expr>$ = new ast::IfExpr($3, $5); $<if_expr>$->setLocation(yylloc); }
		elseif_opt else_opt        { $<if_expr>6->setElse($8); $$ = $<if_expr>6; $$->setLocation(yylloc); }
;

elseif_opt:
		/* empty */ { $$ = NULL; }
	|	elseif_opt ELSEIF '(' expr ')' block_stmt { $$ = new ast::ElseIfExpr($4, $6); $<if_expr>0->add($$); $$->setLocation(yylloc); }
;

else_opt:
		/* empty */		{ $$ = NULL; }
	|	ELSE block_stmt { $$ = $2;   }
;

break_stmt:
		BREAK { $$ = new ast::BreakNode(); $$->setLocation(yylloc); }
;

import_stmt2:
		IMPORT IDENT '.' '*'              { $$ = new ast::ImportStmt($2);                  $$->setLocation(yylloc); }
	|	IMPORT IDENT '.' IDENT '.' IDENT  { $$ = new ast::ImportStmt($2, $4, $6, false);   $$->setLocation(yylloc); }
	|	IMPORT IDENT '.' IDENT '.' TYPE   { $$ = new ast::ImportStmt($2, $4, $6, true);    $$->setLocation(yylloc); }
	|	IMPORT IDENT '.' IDENT '.' '*'    { $$ = new ast::ImportStmt($2, $4, NULL, true);  $$->setLocation(yylloc); }
;

import_stmt:
		import_stmt2           { $$ = $1; }
	|	import_stmt2 AS IDENT  { $$->setAlias($3); }
;

import_file:
		IMPORT STR           { $$ = compiler.importFile(driver, $2->getString(), NULL); delete $2; }
	|	IMPORT STR AS IDENT  { $$ = compiler.importFile(driver, $2->getString(), $4); delete $2; }
;

alias_stmt:
		USE IDENT AS package_module_name "::" IDENT
		{ $4->concat("::", $6); delete $6; $$ = new ast::AliasStmt($2, $4);  $$->setLocation(yylloc); }
	|	USE IDENT AS IDENT
		{ $$ = new ast::AliasStmt($2, $4);  $$->setLocation(yylloc); }
	|	USE TYPE AS package_module_name "::" TYPE
		{ $4->concat("::", $6); delete $6; $$ = new ast::AliasStmt($2, $4, false);  $$->setLocation(yylloc); }
	|	USE TYPE AS package_module_name "::" template
		{ $4->concat("::", $6); delete $6; $$ = new ast::AliasStmt($2, $4, false);  $$->setLocation(yylloc); }
	|	USE TYPE AS TYPE
		{ $$ = new ast::AliasStmt($2, $4, false);  $$->setLocation(yylloc); }
	|	USE TYPE AS template
		{ $$ = new ast::AliasStmt($2, $4, false);  $$->setLocation(yylloc); }
;

constant:
		package_module_name "::" CONSTANT { $1->concat("::", $3); delete $3; $$ = new ast::Constant($1); }
	|	CONSTANT                          { $$ = new ast::Constant($1); }
;

%%

namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& message) {
	driver.error(line, message);
}

} // clever
