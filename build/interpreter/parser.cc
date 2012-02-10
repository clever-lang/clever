
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */


/* Line 311 of lalr1.cc  */
#line 41 "build/interpreter/parser.cc"


#include "parser.hh"

/* User implementation prologue.  */


/* Line 317 of lalr1.cc  */
#line 50 "build/interpreter/parser.cc"
/* Unqualified %code blocks.  */

/* Line 318 of lalr1.cc  */
#line 58 "interpreter/parser.y"

#include "interpreter/driver.h"

namespace clever {

} // clever



/* Line 318 of lalr1.cc  */
#line 65 "build/interpreter/parser.cc"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 4 "interpreter/parser.y"
namespace clever {

/* Line 380 of lalr1.cc  */
#line 133 "build/interpreter/parser.cc"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  Parser::Parser (Driver& driver_yyarg, ScannerState& state_yyarg, Compiler& compiler_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg),
      state (state_yyarg),
      compiler (compiler_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 553 of lalr1.cc  */
#line 51 "interpreter/parser.y"
{
yylloc.begin.filename = yylloc.end.filename = driver.getFile();
}

/* Line 553 of lalr1.cc  */
#line 318 "build/interpreter/parser.cc"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, driver, state);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 678 of lalr1.cc  */
#line 241 "interpreter/parser.y"
    { driver.initCompiler(); }
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 241 "interpreter/parser.y"
    { driver.emitAST((yysemantic_stack_[(2) - (2)].ast_node)); }
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 245 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BlockNode(); }
    break;

  case 5:

/* Line 678 of lalr1.cc  */
#line 246 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 6:

/* Line 678 of lalr1.cc  */
#line 250 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BlockNode(); (yyval.ast_node)->add((yysemantic_stack_[(1) - (1)].ast_node)); }
    break;

  case 7:

/* Line 678 of lalr1.cc  */
#line 251 "interpreter/parser.y"
    { (yysemantic_stack_[(2) - (1)].ast_node)->add((yysemantic_stack_[(2) - (2)].ast_node)); (yyval.ast_node) = (yysemantic_stack_[(2) - (1)].ast_node); }
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 255 "interpreter/parser.y"
    { (yyval.block_stmt) = new ast::BlockNode(); }
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 256 "interpreter/parser.y"
    { (yyval.block_stmt) = (yysemantic_stack_[(3) - (2)].block_stmt); }
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 260 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(2) - (1)].ast_node); }
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 261 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(2) - (1)].ast_node); }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 262 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::VarDecls();  (yyval.var_decls)->setVarDecls((yysemantic_stack_[(2) - (1)].node_list)); }
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 263 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 264 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 265 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 266 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 267 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 268 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(2) - (1)].ast_node); }
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 269 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(2) - (1)].ast_node); }
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 270 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(2) - (1)].ast_node); }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 271 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(2) - (1)].ast_node); }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 272 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(2) - (1)].ast_node); }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 273 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 274 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(2) - (1)].ast_node); }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 278 "interpreter/parser.y"
    { (yyval.return_stmt) = new ast::ReturnStmt((yysemantic_stack_[(2) - (2)].ast_node)); (yyval.return_stmt)->setLocation(yylloc); }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 279 "interpreter/parser.y"
    { (yyval.return_stmt) = new ast::ReturnStmt();   (yyval.return_stmt)->setLocation(yylloc); }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 283 "interpreter/parser.y"
    { (yyval.arg_decl_list) = new ast::ArgumentDeclList(); (yyval.arg_decl_list)->addArg((yysemantic_stack_[(2) - (1)].identifier), (yysemantic_stack_[(2) - (2)].identifier)); }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 284 "interpreter/parser.y"
    { (yysemantic_stack_[(4) - (1)].arg_decl_list)->addArg((yysemantic_stack_[(4) - (3)].identifier), (yysemantic_stack_[(4) - (4)].identifier)); }
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 288 "interpreter/parser.y"
    { (yyval.arg_decl_list) = NULL; }
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 293 "interpreter/parser.y"
    { (yyval.func_decl) = new ast::FuncDeclaration((yysemantic_stack_[(6) - (2)].identifier), (yysemantic_stack_[(6) - (1)].identifier), (yysemantic_stack_[(6) - (4)].arg_decl_list), (yysemantic_stack_[(6) - (6)].block_stmt)); }
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 297 "interpreter/parser.y"
    { (yyval.class_decl) = new ast::ClassDeclaration((yysemantic_stack_[(5) - (2)].identifier), (yysemantic_stack_[(5) - (4)].class_stmt)); }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 301 "interpreter/parser.y"
    { (yyval.integral_value) = new ast::IntegralValue(0x1); }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 302 "interpreter/parser.y"
    { (yyval.integral_value) = new ast::IntegralValue(0x2); }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 303 "interpreter/parser.y"
    { (yyval.integral_value) = new ast::IntegralValue(0x4); }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 307 "interpreter/parser.y"
    { (yyval.class_stmt) = new ast::ClassStmtList; (yyval.class_stmt)->setLocation(yyloc); }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 308 "interpreter/parser.y"
    { (yyval.class_stmt) = (yysemantic_stack_[(1) - (1)].class_stmt); }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 312 "interpreter/parser.y"
    { (yysemantic_stack_[(2) - (1)].class_stmt)->addAttribute((yysemantic_stack_[(2) - (2)].attr_decl)); (yyval.class_stmt) = (yysemantic_stack_[(2) - (1)].class_stmt); }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 313 "interpreter/parser.y"
    { (yysemantic_stack_[(2) - (1)].class_stmt)->addMethod((yysemantic_stack_[(2) - (2)].method_decl)); (yyval.class_stmt) = (yysemantic_stack_[(2) - (1)].class_stmt); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 317 "interpreter/parser.y"
    { (yyval.method_decl) = new ast::MethodDeclaration((yysemantic_stack_[(7) - (1)].integral_value), (yysemantic_stack_[(7) - (2)].identifier), (yysemantic_stack_[(7) - (3)].identifier), (yysemantic_stack_[(7) - (5)].arg_decl_list), (yysemantic_stack_[(7) - (7)].block_stmt)); (yyval.method_decl)->setLocation(yyloc); }
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 321 "interpreter/parser.y"
    { (yyval.attr_decl) = new ast::AttributeDeclaration((yysemantic_stack_[(4) - (1)].integral_value), (yysemantic_stack_[(4) - (2)].identifier), (yysemantic_stack_[(4) - (3)].identifier)); (yyval.attr_decl)->setLocation(yyloc); }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 325 "interpreter/parser.y"
    { (yysemantic_stack_[(3) - (1)].arg_list)->add((yysemantic_stack_[(3) - (3)].ast_node)); }
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 326 "interpreter/parser.y"
    { (yyval.arg_list) = new ast::ArgumentList; (yyval.arg_list)->add((yysemantic_stack_[(1) - (1)].ast_node)); }
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 330 "interpreter/parser.y"
    { (yyval.arg_list) = NULL; }
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 331 "interpreter/parser.y"
    { (yyval.arg_list) = (yysemantic_stack_[(1) - (1)].arg_list); }
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 335 "interpreter/parser.y"
    { (yysemantic_stack_[(3) - (1)].identifier)->concat(".", (yysemantic_stack_[(3) - (3)].identifier)); delete (yysemantic_stack_[(3) - (3)].identifier); }
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 336 "interpreter/parser.y"
    { (yyval.identifier) = (yysemantic_stack_[(1) - (1)].identifier); }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 340 "interpreter/parser.y"
    { (yysemantic_stack_[(3) - (1)].identifier)->concat("::", (yysemantic_stack_[(3) - (3)].identifier)); delete (yysemantic_stack_[(3) - (3)].identifier); }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 341 "interpreter/parser.y"
    { (yyval.identifier) = (yysemantic_stack_[(1) - (1)].identifier); }
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 346 "interpreter/parser.y"
    { (yyval.func_call) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].identifier), (yysemantic_stack_[(4) - (3)].arg_list)); (yyval.func_call)->setLocation(yylloc); }
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 347 "interpreter/parser.y"
    { (yyval.func_call) = new ast::FunctionCall((yysemantic_stack_[(9) - (2)].identifier),(yysemantic_stack_[(9) - (4)].identifier),(yysemantic_stack_[(9) - (6)].identifier),(yysemantic_stack_[(9) - (8)].arg_list)); (yyval.func_call)->setLocation(yylloc); delete (yysemantic_stack_[(9) - (2)].identifier); delete (yysemantic_stack_[(9) - (4)].identifier); delete (yysemantic_stack_[(9) - (6)].identifier); }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 351 "interpreter/parser.y"
    { (yyval.method_call) = (yysemantic_stack_[(0) - (0)].method_call); }
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 352 "interpreter/parser.y"
    { (yyval.method_call) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].method_call), (yysemantic_stack_[(6) - (3)].identifier), (yysemantic_stack_[(6) - (5)].arg_list)); (yyval.method_call)->setLocation(yylloc); }
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 356 "interpreter/parser.y"
    { (yyval.method_call) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].identifier), (yysemantic_stack_[(6) - (3)].identifier), (yysemantic_stack_[(6) - (5)].arg_list)); (yyval.method_call)->setLocation(yylloc); }
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 357 "interpreter/parser.y"
    { (yyval.method_call) = (yysemantic_stack_[(8) - (8)].method_call); }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 358 "interpreter/parser.y"
    { (yyval.method_call) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].ast_node), (yysemantic_stack_[(6) - (3)].identifier), (yysemantic_stack_[(6) - (5)].arg_list)); (yyval.method_call)->setLocation(yylloc); }
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 359 "interpreter/parser.y"
    { (yyval.method_call) = (yysemantic_stack_[(8) - (8)].method_call); }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 363 "interpreter/parser.y"
    { (yyval.template_args) = new ast::TemplateArgsVector; (yyval.template_args)->push_back((yysemantic_stack_[(1) - (1)].identifier)); }
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 364 "interpreter/parser.y"
    { (yysemantic_stack_[(3) - (1)].template_args)->push_back((yysemantic_stack_[(3) - (3)].identifier)); }
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 365 "interpreter/parser.y"
    { (yysemantic_stack_[(3) - (1)].template_args)->push_back((yysemantic_stack_[(3) - (3)].identifier)); }
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 366 "interpreter/parser.y"
    { (yyval.template_args) = new ast::TemplateArgsVector; (yyval.template_args)->push_back((yysemantic_stack_[(1) - (1)].identifier)); }
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 370 "interpreter/parser.y"
    {   (yyval.template_args) = new ast::TemplateArgsVector;
												ast::TemplateArgsVector* a=new ast::TemplateArgsVector;
												a->push_back((yysemantic_stack_[(3) - (3)].identifier));
												(yysemantic_stack_[(3) - (1)].identifier)->setTemplateArgs(a);
												(yyval.template_args)->push_back((yysemantic_stack_[(3) - (1)].identifier)); 
											}
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 376 "interpreter/parser.y"
    {   ast::TemplateArgsVector* a=new ast::TemplateArgsVector;
												a->push_back((yysemantic_stack_[(5) - (5)].identifier));
												(yysemantic_stack_[(5) - (3)].identifier)->setTemplateArgs(a); 
												(yysemantic_stack_[(5) - (1)].template_args)->push_back((yysemantic_stack_[(5) - (3)].identifier));
											}
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 381 "interpreter/parser.y"
    {   ast::TemplateArgsVector* a=new ast::TemplateArgsVector;
												a->push_back((yysemantic_stack_[(5) - (5)].identifier));
												(yysemantic_stack_[(5) - (3)].identifier)->setTemplateArgs(a); 
												(yysemantic_stack_[(5) - (1)].template_args)->push_back((yysemantic_stack_[(5) - (3)].identifier));
											}
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 386 "interpreter/parser.y"
    {	(yyval.template_args) = new ast::TemplateArgsVector;
												ast::TemplateArgsVector* a=new ast::TemplateArgsVector;
												a->push_back((yysemantic_stack_[(3) - (3)].identifier));
												(yysemantic_stack_[(3) - (1)].identifier)->setTemplateArgs(a);
												(yyval.template_args)->push_back((yysemantic_stack_[(3) - (1)].identifier));
											}
    break;

  case 66:

/* Line 678 of lalr1.cc  */
#line 395 "interpreter/parser.y"
    { (yysemantic_stack_[(4) - (1)].identifier)->setTemplateArgs((yysemantic_stack_[(4) - (3)].template_args)); }
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 396 "interpreter/parser.y"
    { (yysemantic_stack_[(4) - (1)].identifier)->setTemplateArgs((yysemantic_stack_[(4) - (3)].template_args)); }
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 400 "interpreter/parser.y"
    { (yyval.variable_decls) = (yysemantic_stack_[(1) - (1)].variable_decls); }
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 401 "interpreter/parser.y"
    { ast::setConstness((yysemantic_stack_[(2) - (2)].variable_decls),true); (yyval.variable_decls) = (yysemantic_stack_[(2) - (2)].variable_decls); }
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 405 "interpreter/parser.y"
    { ast::setType((yysemantic_stack_[(2) - (2)].variable_decls), (yysemantic_stack_[(2) - (1)].identifier)); (yyval.variable_decls) = (yysemantic_stack_[(2) - (2)].variable_decls); }
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 406 "interpreter/parser.y"
    { ast::setType((yysemantic_stack_[(2) - (2)].variable_decls), (yysemantic_stack_[(2) - (1)].identifier)); (yyval.variable_decls) = (yysemantic_stack_[(2) - (2)].variable_decls); }
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 408 "interpreter/parser.y"
    { (yysemantic_stack_[(4) - (1)].identifier)->concat("::",(yysemantic_stack_[(4) - (3)].identifier)); delete (yysemantic_stack_[(4) - (3)].identifier); ast::setType((yysemantic_stack_[(4) - (4)].variable_decls),(yysemantic_stack_[(4) - (1)].identifier)); (yyval.variable_decls) = (yysemantic_stack_[(4) - (4)].variable_decls); }
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 409 "interpreter/parser.y"
    { (yyval.variable_decls) = (yysemantic_stack_[(2) - (2)].variable_decls); }
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 413 "interpreter/parser.y"
    { (yyval.variable_decls) = new ast::VariableDecls(); (yyval.variable_decls)->push_back((yysemantic_stack_[(3) - (1)].variable_decl)); (yyval.variable_decls)->push_back((yysemantic_stack_[(3) - (3)].variable_decl)); }
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 414 "interpreter/parser.y"
    { (yysemantic_stack_[(3) - (1)].variable_decls)->push_back((yysemantic_stack_[(3) - (3)].variable_decl)); (yyval.variable_decls) = (yysemantic_stack_[(3) - (1)].variable_decls); }
    break;

  case 76:

/* Line 678 of lalr1.cc  */
#line 418 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl(NULL, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 422 "interpreter/parser.y"
    { (yyval.variable_decls) = new ast::VariableDecls(); (yyval.variable_decls)->push_back((yysemantic_stack_[(3) - (1)].variable_decl)); (yyval.variable_decls)->push_back((yysemantic_stack_[(3) - (3)].variable_decl)); }
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 423 "interpreter/parser.y"
    { (yysemantic_stack_[(3) - (1)].variable_decls)->push_back((yysemantic_stack_[(3) - (3)].variable_decl)); (yyval.variable_decls) = (yysemantic_stack_[(3) - (1)].variable_decls); }
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 427 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl(NULL, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].type_creation)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 428 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl(NULL, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 81:

/* Line 678 of lalr1.cc  */
#line 429 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl(NULL, (yysemantic_stack_[(4) - (1)].identifier), new ast::TypeCreation(NULL, (yysemantic_stack_[(4) - (3)].arg_list)), true); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 82:

/* Line 678 of lalr1.cc  */
#line 430 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl(NULL,(yysemantic_stack_[(1) - (1)].identifier));  }
    break;

  case 83:

/* Line 678 of lalr1.cc  */
#line 434 "interpreter/parser.y"
    { (yyval.variable_decl) = (yysemantic_stack_[(1) - (1)].variable_decl); }
    break;

  case 84:

/* Line 678 of lalr1.cc  */
#line 435 "interpreter/parser.y"
    { (yysemantic_stack_[(2) - (2)].variable_decl)->setConstness(true); (yyval.variable_decl) = (yysemantic_stack_[(2) - (2)].variable_decl); }
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 439 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].identifier), (yysemantic_stack_[(4) - (2)].identifier), (yysemantic_stack_[(4) - (4)].type_creation)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 86:

/* Line 678 of lalr1.cc  */
#line 440 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].identifier), (yysemantic_stack_[(4) - (2)].identifier), (yysemantic_stack_[(4) - (4)].type_creation)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 87:

/* Line 678 of lalr1.cc  */
#line 442 "interpreter/parser.y"
    { (yysemantic_stack_[(6) - (1)].identifier)->concat("::", (yysemantic_stack_[(6) - (3)].identifier)); delete (yysemantic_stack_[(6) - (3)].identifier); (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(6) - (1)].identifier), (yysemantic_stack_[(6) - (4)].identifier), (yysemantic_stack_[(6) - (6)].type_creation)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 88:

/* Line 678 of lalr1.cc  */
#line 444 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl(NULL, (yysemantic_stack_[(4) - (2)].identifier), (yysemantic_stack_[(4) - (4)].ast_node)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 89:

/* Line 678 of lalr1.cc  */
#line 445 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl(NULL, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 90:

/* Line 678 of lalr1.cc  */
#line 446 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].identifier), (yysemantic_stack_[(4) - (2)].identifier), (yysemantic_stack_[(4) - (4)].ast_node)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 91:

/* Line 678 of lalr1.cc  */
#line 447 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].identifier), (yysemantic_stack_[(4) - (2)].identifier), (yysemantic_stack_[(4) - (4)].ast_node)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 92:

/* Line 678 of lalr1.cc  */
#line 449 "interpreter/parser.y"
    { (yysemantic_stack_[(6) - (1)].identifier)->concat("::", (yysemantic_stack_[(6) - (3)].identifier)); delete (yysemantic_stack_[(6) - (3)].identifier); (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(6) - (1)].identifier), (yysemantic_stack_[(6) - (4)].identifier), (yysemantic_stack_[(6) - (6)].ast_node)); (yyval.variable_decl)->setLocation(yylloc); }
    break;

  case 93:

/* Line 678 of lalr1.cc  */
#line 451 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(2) - (1)].identifier), (yysemantic_stack_[(2) - (2)].identifier)); }
    break;

  case 94:

/* Line 678 of lalr1.cc  */
#line 452 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(2) - (1)].identifier), (yysemantic_stack_[(2) - (2)].identifier)); }
    break;

  case 95:

/* Line 678 of lalr1.cc  */
#line 453 "interpreter/parser.y"
    { (yysemantic_stack_[(4) - (1)].identifier)->concat("::", (yysemantic_stack_[(4) - (3)].identifier)); delete (yysemantic_stack_[(4) - (3)].identifier); (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].identifier), (yysemantic_stack_[(4) - (4)].identifier)); (yyval.variable_decl)->setLocation(yyloc); }
    break;

  case 96:

/* Line 678 of lalr1.cc  */
#line 455 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(5) - (1)].identifier), (yysemantic_stack_[(5) - (2)].identifier), new ast::TypeCreation((yysemantic_stack_[(5) - (1)].identifier), (yysemantic_stack_[(5) - (4)].arg_list))); (yyval.variable_decl)->setLocation(yyloc);   }
    break;

  case 97:

/* Line 678 of lalr1.cc  */
#line 456 "interpreter/parser.y"
    { (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(5) - (1)].identifier), (yysemantic_stack_[(5) - (2)].identifier), new ast::TypeCreation((yysemantic_stack_[(5) - (1)].identifier), (yysemantic_stack_[(5) - (4)].arg_list))); (yyval.variable_decl)->setLocation(yyloc);   }
    break;

  case 98:

/* Line 678 of lalr1.cc  */
#line 458 "interpreter/parser.y"
    { (yysemantic_stack_[(7) - (1)].identifier)->concat("::", (yysemantic_stack_[(7) - (3)].identifier)); delete (yysemantic_stack_[(7) - (3)].identifier); (yyval.variable_decl) = new ast::VariableDecl((yysemantic_stack_[(7) - (1)].identifier), (yysemantic_stack_[(7) - (4)].identifier), new ast::TypeCreation((yysemantic_stack_[(7) - (1)].identifier), (yysemantic_stack_[(7) - (6)].arg_list))); (yyval.variable_decl)->setLocation(yyloc);  }
    break;

  case 99:

/* Line 678 of lalr1.cc  */
#line 462 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::AssignExpr((yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node));                   (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 100:

/* Line 678 of lalr1.cc  */
#line 463 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::PLUS, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node), true);  (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 101:

/* Line 678 of lalr1.cc  */
#line 464 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::MINUS, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node), true); (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 102:

/* Line 678 of lalr1.cc  */
#line 465 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::DIV, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node), true);   (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 103:

/* Line 678 of lalr1.cc  */
#line 466 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::MULT, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node), true);  (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 104:

/* Line 678 of lalr1.cc  */
#line 467 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::MOD, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node), true);   (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 105:

/* Line 678 of lalr1.cc  */
#line 468 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::AND, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node), true);   (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 106:

/* Line 678 of lalr1.cc  */
#line 469 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::OR, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node), true);    (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 107:

/* Line 678 of lalr1.cc  */
#line 470 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::XOR, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node), true);   (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 108:

/* Line 678 of lalr1.cc  */
#line 471 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::LSHIFT, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node), true);   (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 109:

/* Line 678 of lalr1.cc  */
#line 472 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::RSHIFT, (yysemantic_stack_[(3) - (1)].identifier), (yysemantic_stack_[(3) - (3)].ast_node), true);   (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 110:

/* Line 678 of lalr1.cc  */
#line 476 "interpreter/parser.y"
    { (yyval.type_creation) = new ast::TypeCreation((yysemantic_stack_[(4) - (1)].identifier), (yysemantic_stack_[(4) - (3)].arg_list)); (yyval.type_creation)->setLocation(yylloc); }
    break;

  case 111:

/* Line 678 of lalr1.cc  */
#line 480 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::MINUS, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));         (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 112:

/* Line 678 of lalr1.cc  */
#line 481 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::PLUS, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));          (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 113:

/* Line 678 of lalr1.cc  */
#line 482 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::DIV, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));           (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 114:

/* Line 678 of lalr1.cc  */
#line 483 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::MULT, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));          (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 115:

/* Line 678 of lalr1.cc  */
#line 484 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::MOD, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));           (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 116:

/* Line 678 of lalr1.cc  */
#line 485 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::BW_OR, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));         (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 117:

/* Line 678 of lalr1.cc  */
#line 486 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::BW_AND, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));        (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 118:

/* Line 678 of lalr1.cc  */
#line 487 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::XOR, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));           (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 119:

/* Line 678 of lalr1.cc  */
#line 488 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::GREATER, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));       (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 120:

/* Line 678 of lalr1.cc  */
#line 489 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::GREATER_EQUAL, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node)); (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 121:

/* Line 678 of lalr1.cc  */
#line 490 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::LESS, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));          (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 122:

/* Line 678 of lalr1.cc  */
#line 491 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::LESS_EQUAL, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));    (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 123:

/* Line 678 of lalr1.cc  */
#line 492 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::LSHIFT, (yysemantic_stack_[(3) - (1)].ast_node),(yysemantic_stack_[(3) - (3)].ast_node));         (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 124:

/* Line 678 of lalr1.cc  */
#line 493 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::RSHIFT, (yysemantic_stack_[(3) - (1)].ast_node),(yysemantic_stack_[(3) - (3)].ast_node));         (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 125:

/* Line 678 of lalr1.cc  */
#line 494 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::EQUAL, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));         (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 126:

/* Line 678 of lalr1.cc  */
#line 495 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::NOT_EQUAL, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));     (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 127:

/* Line 678 of lalr1.cc  */
#line 496 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::OR, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));            (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 128:

/* Line 678 of lalr1.cc  */
#line 497 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::AND, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));           (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 129:

/* Line 678 of lalr1.cc  */
#line 498 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::OR, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));            (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 130:

/* Line 678 of lalr1.cc  */
#line 499 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::AND, (yysemantic_stack_[(3) - (1)].ast_node), (yysemantic_stack_[(3) - (3)].ast_node));           (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 131:

/* Line 678 of lalr1.cc  */
#line 500 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::MINUS, (yysemantic_stack_[(2) - (2)].ast_node));             (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 132:

/* Line 678 of lalr1.cc  */
#line 501 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::BinaryExpr(ast::PLUS, (yysemantic_stack_[(2) - (2)].ast_node));              (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 133:

/* Line 678 of lalr1.cc  */
#line 502 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::UnaryExpr(ast::PRE_INC, (yysemantic_stack_[(2) - (2)].identifier));            (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 134:

/* Line 678 of lalr1.cc  */
#line 503 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::UnaryExpr(ast::POS_INC, (yysemantic_stack_[(2) - (1)].identifier));            (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 135:

/* Line 678 of lalr1.cc  */
#line 504 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::UnaryExpr(ast::PRE_DEC, (yysemantic_stack_[(2) - (2)].identifier));            (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 136:

/* Line 678 of lalr1.cc  */
#line 505 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::UnaryExpr(ast::POS_DEC, (yysemantic_stack_[(2) - (1)].identifier));            (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 137:

/* Line 678 of lalr1.cc  */
#line 506 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::UnaryExpr(ast::NOT, (yysemantic_stack_[(2) - (2)].ast_node));                (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 138:

/* Line 678 of lalr1.cc  */
#line 507 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::UnaryExpr(ast::BW_NOT, (yysemantic_stack_[(2) - (2)].ast_node));             (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 139:

/* Line 678 of lalr1.cc  */
#line 508 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(3) - (2)].ast_node); }
    break;

  case 140:

/* Line 678 of lalr1.cc  */
#line 509 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 141:

/* Line 678 of lalr1.cc  */
#line 510 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 142:

/* Line 678 of lalr1.cc  */
#line 511 "interpreter/parser.y"
    { (yyval.ast_node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].identifier), (yysemantic_stack_[(4) - (3)].ast_node)); (yyval.ast_node)->setLocation(yylloc); }
    break;

  case 143:

/* Line 678 of lalr1.cc  */
#line 512 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 144:

/* Line 678 of lalr1.cc  */
#line 513 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 145:

/* Line 678 of lalr1.cc  */
#line 514 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 146:

/* Line 678 of lalr1.cc  */
#line 518 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 147:

/* Line 678 of lalr1.cc  */
#line 519 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 148:

/* Line 678 of lalr1.cc  */
#line 520 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 149:

/* Line 678 of lalr1.cc  */
#line 521 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 150:

/* Line 678 of lalr1.cc  */
#line 522 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 151:

/* Line 678 of lalr1.cc  */
#line 523 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 152:

/* Line 678 of lalr1.cc  */
#line 527 "interpreter/parser.y"
    { (yyval.variable_decl) = NULL; }
    break;

  case 153:

/* Line 678 of lalr1.cc  */
#line 528 "interpreter/parser.y"
    { (yyval.variable_decl) = (yysemantic_stack_[(1) - (1)].variable_decl); }
    break;

  case 154:

/* Line 678 of lalr1.cc  */
#line 532 "interpreter/parser.y"
    { (yyval.ast_node) = NULL; }
    break;

  case 155:

/* Line 678 of lalr1.cc  */
#line 533 "interpreter/parser.y"
    { (yyval.ast_node) = (yysemantic_stack_[(1) - (1)].ast_node); }
    break;

  case 156:

/* Line 678 of lalr1.cc  */
#line 537 "interpreter/parser.y"
    { (yyval.for_expr) = new ast::ForExpr((yysemantic_stack_[(9) - (3)].variable_decl), (yysemantic_stack_[(9) - (5)].ast_node), (yysemantic_stack_[(9) - (7)].ast_node), (yysemantic_stack_[(9) - (9)].block_stmt)); (yyval.for_expr)->setLocation(yylloc); }
    break;

  case 157:

/* Line 678 of lalr1.cc  */
#line 538 "interpreter/parser.y"
    { (yyval.for_expr) = new ast::ForExpr((yysemantic_stack_[(9) - (3)].variable_decl), (yysemantic_stack_[(9) - (5)].ast_node), (yysemantic_stack_[(9) - (7)].ast_node), (yysemantic_stack_[(9) - (9)].block_stmt)); (yyval.for_expr)->setLocation(yylloc); }
    break;

  case 158:

/* Line 678 of lalr1.cc  */
#line 543 "interpreter/parser.y"
    { (yyval.while_expr) = new ast::WhileExpr((yysemantic_stack_[(5) - (3)].ast_node), (yysemantic_stack_[(5) - (5)].block_stmt)); (yyval.while_expr)->setLocation(yylloc); }
    break;

  case 159:

/* Line 678 of lalr1.cc  */
#line 547 "interpreter/parser.y"
    { (yyval.if_expr) = new ast::IfExpr((yysemantic_stack_[(5) - (3)].ast_node), (yysemantic_stack_[(5) - (5)].block_stmt)); (yyval.if_expr)->setLocation(yylloc); }
    break;

  case 160:

/* Line 678 of lalr1.cc  */
#line 548 "interpreter/parser.y"
    { (yysemantic_stack_[(8) - (6)].if_expr)->setElse((yysemantic_stack_[(8) - (8)].block_stmt)); (yyval.if_expr) = (yysemantic_stack_[(8) - (6)].if_expr); (yyval.if_expr)->setLocation(yylloc); }
    break;

  case 161:

/* Line 678 of lalr1.cc  */
#line 552 "interpreter/parser.y"
    { (yyval.elseif_opt) = NULL; }
    break;

  case 162:

/* Line 678 of lalr1.cc  */
#line 553 "interpreter/parser.y"
    { (yyval.elseif_opt) = new ast::ElseIfExpr((yysemantic_stack_[(6) - (4)].ast_node), (yysemantic_stack_[(6) - (6)].block_stmt)); (yysemantic_stack_[(6) - (0)].if_expr)->add((yyval.elseif_opt)); (yyval.elseif_opt)->setLocation(yylloc); }
    break;

  case 163:

/* Line 678 of lalr1.cc  */
#line 557 "interpreter/parser.y"
    { (yyval.block_stmt) = NULL; }
    break;

  case 164:

/* Line 678 of lalr1.cc  */
#line 558 "interpreter/parser.y"
    { (yyval.block_stmt) = (yysemantic_stack_[(2) - (2)].block_stmt);   }
    break;

  case 165:

/* Line 678 of lalr1.cc  */
#line 562 "interpreter/parser.y"
    { (yyval.break_stmt) = new ast::BreakNode(); (yyval.break_stmt)->setLocation(yylloc); }
    break;

  case 166:

/* Line 678 of lalr1.cc  */
#line 566 "interpreter/parser.y"
    { (yyval.import_stmt) = new ast::ImportStmt((yysemantic_stack_[(2) - (2)].identifier));         (yyval.import_stmt)->setLocation(yylloc); }
    break;

  case 167:

/* Line 678 of lalr1.cc  */
#line 567 "interpreter/parser.y"
    { (yyval.import_stmt) = new ast::ImportStmt((yysemantic_stack_[(4) - (2)].identifier), (yysemantic_stack_[(4) - (4)].identifier));     (yyval.import_stmt)->setLocation(yylloc); }
    break;

  case 168:

/* Line 678 of lalr1.cc  */
#line 568 "interpreter/parser.y"
    { (yyval.import_stmt) = new ast::ImportStmt((yysemantic_stack_[(6) - (2)].identifier), (yysemantic_stack_[(6) - (4)].identifier), (yysemantic_stack_[(6) - (6)].identifier)); (yyval.import_stmt)->setLocation(yylloc); }
    break;

  case 169:

/* Line 678 of lalr1.cc  */
#line 572 "interpreter/parser.y"
    { (yyval.block_stmt) = compiler.importFile(driver, (yysemantic_stack_[(2) - (2)].str_literal)->getString(), NULL); delete (yysemantic_stack_[(2) - (2)].str_literal); }
    break;

  case 170:

/* Line 678 of lalr1.cc  */
#line 573 "interpreter/parser.y"
    { (yyval.block_stmt) = compiler.importFile(driver, (yysemantic_stack_[(4) - (2)].str_literal)->getString(), (yysemantic_stack_[(4) - (4)].identifier)->getName()); delete (yysemantic_stack_[(4) - (2)].str_literal); delete (yysemantic_stack_[(4) - (4)].identifier); }
    break;

  case 171:

/* Line 678 of lalr1.cc  */
#line 578 "interpreter/parser.y"
    { (yysemantic_stack_[(6) - (4)].identifier)->concat("::", (yysemantic_stack_[(6) - (6)].identifier)); delete (yysemantic_stack_[(6) - (6)].identifier); (yyval.alias_stmt) = new ast::AliasStmt((yysemantic_stack_[(6) - (2)].identifier), (yysemantic_stack_[(6) - (4)].identifier));  (yyval.alias_stmt)->setLocation(yylloc); }
    break;

  case 172:

/* Line 678 of lalr1.cc  */
#line 582 "interpreter/parser.y"
    { (yysemantic_stack_[(3) - (1)].identifier)->concat("::", (yysemantic_stack_[(3) - (3)].identifier)); delete (yysemantic_stack_[(3) - (3)].identifier); (yyval.constant) = new ast::Constant((yysemantic_stack_[(3) - (1)].identifier)); }
    break;

  case 173:

/* Line 678 of lalr1.cc  */
#line 583 "interpreter/parser.y"
    { (yyval.constant) = new ast::Constant((yysemantic_stack_[(1) - (1)].identifier)); }
    break;



/* Line 678 of lalr1.cc  */
#line 1652 "build/interpreter/parser.cc"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int Parser::yypact_ninf_ = -187;
  const short int
  Parser::yypact_[] =
  {
      -187,    27,   403,  -187,    84,  1072,  -187,  -187,  -187,   -23,
       9,    62,  -187,    11,   155,   104,  -187,  -187,  -187,   136,
    -187,    34,   151,   155,   155,   155,   155,   177,   184,   187,
     251,   155,  -187,   403,  -187,  -187,    72,  -187,  -187,   119,
     121,  -187,  -187,   209,   140,  -187,   145,  -187,   146,   815,
     167,  -187,  -187,  -187,   157,   159,   160,   168,  -187,    24,
     241,   193,   194,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   245,  -187,  -187,   155,    31,
     155,   155,   189,   203,   101,   205,  1163,   188,   212,    94,
      -7,   216,  -187,  -187,   210,   213,   214,  -187,  -187,  -187,
    -187,  -187,  -187,   218,  -187,   329,   599,  -187,  -187,    10,
     155,   127,   193,  -187,  -187,  -187,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,  -187,   266,  -187,  -187,
    -187,  -187,   431,   480,   258,   -15,   257,  -187,   277,   277,
    1163,  1163,  1163,  1163,  1163,  1163,  1163,  1163,  1163,  1163,
    1163,  1163,   208,   547,   175,    37,   285,   246,   289,  -187,
     223,   653,   707,   295,   303,     8,  -187,   310,   132,   311,
     313,   155,   320,   320,   322,  -187,  -187,   324,  -187,  -187,
     263,   252,  1163,   431,   155,   683,   683,   683,   683,   244,
     244,    30,    30,  1280,  1215,   221,  1228,   578,   845,   630,
     163,   163,  -187,  -187,  -187,   254,   261,   267,   867,   334,
    -187,   -48,   -46,   340,  -187,   341,  -187,    78,  -187,  -187,
     155,  -187,    81,   290,   343,    93,   155,   275,   275,   301,
    -187,   100,  -187,   286,   302,   155,  -187,   919,   296,  -187,
    -187,   276,   143,   193,   155,  -187,   278,   971,   -45,   155,
     155,  -187,   353,   275,   282,    25,   339,   342,  -187,   431,
     155,   283,   431,   155,   155,   358,   431,   155,  1163,   288,
    -187,  -187,   360,  -187,  -187,  -187,  -187,   362,  -187,  -187,
     363,   155,   364,   431,   155,  1163,   291,   294,   299,   368,
    -187,   370,  -187,  1163,    20,  -187,  -187,  1163,    58,  1163,
     129,  -187,  1163,    96,   508,  -187,  -187,   373,  -187,  1163,
     133,   335,   308,   312,  1023,    98,  -187,  -187,  -187,    33,
     366,  -187,  -187,  -187,   431,   155,  -187,  1101,   309,   315,
       3,    28,   384,   155,   314,  -187,   330,  -187,  1163,    99,
     275,   275,   275,   318,  -187,  -187,   392,   325,   330,   400,
    -187,  -187,  -187,  -187,   155,   112,  -187,   336,   761,   275,
     155,   275,  -187,   344,  -187,  -187
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     0,   143,   146,   147,   148,     0,
       0,     0,   165,     0,    26,     0,   149,   150,   173,     0,
     151,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     5,    17,     6,     0,    13,    23,     0,
       0,   140,   141,     0,     0,    68,     0,    83,     0,     0,
     144,    15,    16,    14,     0,     0,     0,     0,   145,    82,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   136,   134,     0,   152,
       0,     0,   166,   169,   143,     0,    25,     0,     0,     0,
      47,     0,    69,    84,     0,    73,     0,   131,   132,   137,
     138,   135,   133,     0,     8,     0,     0,     7,    22,     0,
      44,    82,    71,    12,    11,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,     0,    18,    20,
      21,    24,     0,    29,    58,     0,     0,    61,     0,     0,
     109,   108,   100,   103,   102,   101,   104,    89,   105,   106,
     107,    99,    46,     0,     0,     0,     0,     0,     0,   153,
       0,     0,     0,     0,     0,     0,    36,     0,    82,     0,
       0,     0,     0,     0,     0,     9,   139,     0,    48,   172,
      45,     0,    43,     0,     0,   122,   120,   121,   119,   124,
     123,   125,   126,   127,   129,   128,   130,   116,   118,   117,
     111,   112,   114,   113,   115,     0,     0,    79,    80,     0,
      30,     0,     0,     0,    66,     0,    67,    82,    78,    77,
      44,   142,    93,     0,     0,    94,   154,     0,     0,   167,
     170,     0,    37,    47,     0,     0,    46,    76,     0,    75,
      74,     0,    82,    72,     0,    50,    79,    80,     0,    44,
      44,    27,     0,     0,    81,    58,    61,    59,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   155,     0,
     158,   159,     0,    33,    34,    35,    32,     0,    39,    38,
       0,     0,     0,     0,     0,    42,    81,     0,     0,     0,
      31,     0,    79,    80,     0,    54,    85,    90,     0,    88,
      95,    86,    91,     0,   154,   161,   168,     0,   171,    76,
      47,     0,     0,    79,    80,     0,    56,   110,    28,    58,
      61,    81,    52,    96,     0,     0,    97,   143,     0,     0,
     163,     0,     0,    44,    81,    52,    55,    87,    92,     0,
       0,     0,     0,     0,   160,    41,    29,     0,    57,     0,
      98,   157,   156,   164,     0,     0,    51,     0,     0,     0,
      44,     0,    40,     0,   162,    53
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -187,  -187,  -187,  -187,   382,  -156,   -28,  -187,  -187,    61,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -135,  -186,     4,
     126,  -187,    74,  -187,  -187,  -187,  -187,  -187,   -59,  -187,
     399,  -187,    29,   -41,    38,   345,   -18,   107,  -182,    -2,
    -187,  -187,   109,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,    32,    33,    34,    35,    36,   220,   221,
      37,    38,   287,   241,   242,   288,   289,   190,   191,    85,
      40,    41,   346,    42,   332,   345,   145,   146,    43,    44,
      45,    95,    96,    61,    62,    46,    47,    48,   217,   192,
      50,   170,   279,    51,    52,    53,   315,   340,   354,    54,
      55,    56,    57,    58
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -99;
  const short int
  Parser::yytable_[] =
  {
        49,   147,   112,    93,   224,   107,    39,   262,   222,   254,
     254,   256,    86,   188,   187,   188,    82,   352,   353,    83,
     168,    97,    98,    99,   100,    91,    70,     3,    49,   106,
     263,    49,   264,   296,    39,   164,    90,    39,    89,    90,
     225,   164,    90,   223,   271,   -62,   116,   117,   118,   119,
     120,   223,   121,   -63,    79,   -99,   -99,   179,   189,   258,
     189,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   297,   298,   254,   163,   107,   171,   172,
     142,   280,   281,   167,   165,   166,    80,   302,    22,    59,
     306,   166,   131,   132,   311,   133,   134,   135,   331,   178,
     -93,   143,    60,    49,   355,   356,   168,   300,    87,    39,
     222,   323,    60,   254,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   269,   304,   333,   272,   308,    81,
     218,    88,   313,   283,   284,   285,   253,    93,   108,   276,
     -47,   254,   347,   254,   254,   270,    94,   357,   273,   325,
      84,     6,     7,     8,   266,    75,   268,   262,   109,   167,
     277,    76,    77,    78,   336,   286,   344,   360,   -49,   247,
     232,   244,   101,   193,   373,   334,   228,   229,   142,   102,
     369,   257,   103,    60,   361,   362,   363,   179,   110,   293,
     349,    16,    17,   -94,   194,    18,   335,    20,   -93,   245,
     -49,   249,   250,   372,   111,   374,   113,    23,    24,   -95,
     294,   114,   115,    25,    26,    27,    28,    29,   133,   134,
     135,   137,    31,   138,   278,   139,   140,   116,   117,   118,
     119,   120,   330,   121,   141,   144,   122,   123,   148,   149,
     162,   174,   295,   173,   175,     4,     5,     6,     7,     8,
     177,   176,     9,    10,    11,   180,   181,   303,   182,   183,
     307,   215,   309,   184,   312,    12,   223,   226,    13,   128,
     129,   130,   227,   131,   132,   230,   133,   134,   135,   319,
     233,   324,    14,    15,   235,   234,   321,    16,    17,   236,
     239,    18,    19,    20,    21,    22,   131,   132,   240,   133,
     134,   135,   278,    23,    24,   243,   246,   187,   254,    25,
      26,    27,    28,    29,    30,   248,   104,   251,    31,   252,
     255,   259,   348,     4,     5,     6,     7,     8,   260,   261,
       9,    10,    11,   -85,   265,   267,   274,   275,    30,   282,
     179,   290,   291,    12,   -86,   292,    13,   299,   -96,   -65,
     301,   305,   368,   310,   314,   316,   317,   -97,   318,   320,
      14,    15,   326,   328,   329,    16,    17,   327,   341,    18,
      19,    20,    21,    22,   342,   343,   -64,   350,   -87,   188,
     -98,    23,    24,   351,   359,   364,   219,    25,    26,    27,
      28,    29,    30,   366,   185,   367,    31,     4,     5,     6,
       7,     8,   105,   370,     9,    10,    11,   365,   322,   358,
      92,   338,   375,   339,   169,     0,     0,    12,     0,     0,
      13,     0,     0,     0,     0,   216,    84,     6,     7,     8,
       0,     0,     0,     0,    14,    15,     0,     0,     0,    16,
      17,     0,     0,    18,    19,    20,    21,    22,     0,     0,
       0,     0,     0,     0,     0,    23,    24,     0,     0,     0,
       0,    25,    26,    27,    28,    29,    30,    16,    17,     0,
      31,    18,     0,    20,   219,    84,     6,     7,     8,     0,
       0,     0,     0,    23,    24,     0,     0,     0,     0,    25,
      26,    27,    28,    29,     0,     0,     0,     0,    31,     0,
       0,     0,     0,   337,     6,     7,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    17,     0,     0,
      18,     0,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    23,    24,     0,     0,     0,     0,    25,    26,
      27,    28,    29,     0,    16,    17,     0,    31,    18,     0,
      20,     0,     0,   116,   117,   118,   119,   120,     0,   121,
      23,    24,   122,   123,     0,     0,    25,    26,    27,    28,
      29,   124,   125,   126,   127,    31,     0,     0,     0,     0,
       0,     0,     0,     0,   116,   117,   118,   119,   120,     0,
     121,     0,     0,   122,   123,   128,   129,   130,     0,   131,
     132,     0,   133,   134,   135,   116,   117,   118,   119,   120,
       0,   121,     0,     0,   122,   123,   231,     0,     0,     0,
       0,     0,     0,   124,   125,   126,   127,   129,   130,     0,
     131,   132,     0,   133,   134,   135,   116,   117,   118,   119,
     120,     0,   121,     0,     0,   122,   123,   128,   129,   130,
       0,   131,   132,     0,   133,   134,   135,     0,     0,   116,
     117,   118,   119,   120,     0,   121,     0,   186,   122,   123,
       0,     0,     0,     0,     0,     0,     0,   124,   125,   126,
     127,     0,   131,   132,     0,   133,   134,   135,     0,   -99,
     -99,   -99,   -99,   120,     0,   121,     0,     0,     0,     0,
       0,   128,   129,   130,     0,   131,   132,     0,   133,   134,
     135,     0,     0,   116,   117,   118,   119,   120,     0,   121,
       0,   237,   122,   123,     0,     0,     0,     0,     0,     0,
       0,   124,   125,   126,   127,   131,   132,     0,   133,   134,
     135,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,   129,   130,     0,   131,
     132,     0,   133,   134,   135,     0,     0,   116,   117,   118,
     119,   120,     0,   121,     0,   238,   122,   123,     0,     0,
       0,     0,     0,     0,     0,   124,   125,   126,   127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     129,   130,     0,   131,   132,     0,   133,   134,   135,     0,
       0,   116,   117,   118,   119,   120,     0,   121,     0,   371,
     122,   123,     0,     0,     0,     0,     0,     0,     0,   124,
     125,   126,   127,     0,     0,     0,     0,     0,     0,     0,
       0,   116,   117,   118,   119,   120,     0,   121,     0,     0,
     122,   123,     0,   128,   129,   130,     0,   131,   132,     0,
     133,   134,   135,   116,   117,   118,   119,   120,     0,   121,
       0,   136,   122,   123,     0,     0,     0,     0,     0,     0,
       0,   124,   125,   126,   127,   130,     0,   131,   132,     0,
     133,   134,   135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,   129,   130,     0,   131,
     132,     0,   133,   134,   135,   116,   117,   118,   119,   120,
       0,   121,     0,   -90,   122,   123,     0,     0,     0,     0,
       0,     0,     0,   124,   125,   126,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,   129,   130,
       0,   131,   132,     0,   133,   134,   135,   116,   117,   118,
     119,   120,     0,   121,     0,   -88,   122,   123,     0,     0,
       0,     0,     0,     0,     0,   124,   125,   126,   127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     129,   130,     0,   131,   132,     0,   133,   134,   135,   116,
     117,   118,   119,   120,     0,   121,     0,   -91,   122,   123,
       0,     0,     0,     0,     0,     0,     0,   124,   125,   126,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   128,   129,   130,     0,   131,   132,     0,   133,   134,
     135,     0,     0,    63,     0,    64,     0,     0,     0,   -92,
      65,    66,    67,    68,    69,    70,     0,     0,     0,     0,
      71,    72,    73,     0,     0,     0,     0,     0,     0,     0,
       0,   -47,    63,     0,    64,     0,     0,     0,    74,    65,
      66,    67,    68,    69,     0,     0,    75,     0,     0,    71,
      72,    73,    76,    77,    78,     0,     0,     0,     0,   -49,
     -47,     0,     0,     0,     0,     0,     0,    74,     0,     0,
       0,     0,     0,     0,     0,    75,     0,     0,     0,     0,
       0,    76,    77,    78,     0,     0,     0,     0,   -49,   116,
     117,   118,   119,   120,     0,   121,     0,     0,   122,   123,
       0,     0,     0,     0,     0,     0,     0,   124,   125,   126,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   128,   129,   130,     0,   131,   132,     0,   133,   134,
     135,   116,   117,   118,   119,   120,     0,   121,     0,     0,
     122,   123,     0,     0,   116,   117,   118,   119,   120,   124,
     121,   126,   127,   122,   123,     0,     0,     0,     0,     0,
       0,     0,   124,     0,   126,     0,     0,     0,     0,     0,
       0,     0,     0,   128,   129,   130,     0,   131,   132,     0,
     133,   134,   135,     0,     0,     0,   128,   129,   130,     0,
     131,   132,     0,   133,   134,   135,   116,   117,   118,   119,
     120,     0,   121,     0,     0,   122,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   128,   129,
     130,     0,   131,   132,     0,   133,   134,   135
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         2,    60,    43,    21,    19,    33,     2,    55,   143,    55,
      55,   193,    14,     5,     4,     5,     5,    14,    15,     8,
      79,    23,    24,    25,    26,    21,    33,     0,    30,    31,
      78,    33,    78,    78,    30,     4,     5,    33,     4,     5,
      55,     4,     5,    18,   230,    20,    16,    17,    18,    19,
      20,    18,    22,    20,    77,    25,    26,    64,    50,   194,
      50,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   259,   260,    55,    78,   105,    80,    81,
      56,   237,   238,    79,    53,    54,    77,   269,    54,     5,
     272,    54,    62,    63,   276,    65,    66,    67,    78,     5,
      76,    77,    18,   105,    76,    77,   165,   263,     4,   105,
     245,   293,    18,    55,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,    56,   270,    78,    56,   273,    77,
     142,     5,   277,    43,    44,    45,   187,   165,    76,    56,
      49,    55,   334,    55,    55,    77,     5,   343,    77,   294,
       5,     6,     7,     8,   223,    64,   225,    55,    49,   165,
      77,    70,    71,    72,    78,    75,    78,    78,    77,   181,
       5,   177,     5,    56,   370,    56,   148,   149,    56,     5,
      78,   193,     5,    18,   350,   351,   352,    64,    77,    56,
     335,    46,    47,    76,    77,    50,    77,    52,    76,    77,
      77,   182,   183,   369,     5,   371,    76,    62,    63,    76,
      77,    76,    76,    68,    69,    70,    71,    72,    65,    66,
      67,    64,    77,    76,   236,    76,    76,    16,    17,    18,
      19,    20,   301,    22,    76,     4,    25,    26,    55,    55,
       5,    48,   254,    64,    49,     4,     5,     6,     7,     8,
      48,    73,    11,    12,    13,    49,    56,   269,    55,    55,
     272,     5,   274,    55,   276,    24,    18,    20,    27,    58,
      59,    60,     5,    62,    63,    77,    65,    66,    67,   291,
       5,   293,    41,    42,     5,    49,   292,    46,    47,    76,
       5,    50,    51,    52,    53,    54,    62,    63,     5,    65,
      66,    67,   314,    62,    63,     5,     5,     4,    55,    68,
      69,    70,    71,    72,    73,     5,    75,     5,    77,     5,
      78,    77,   334,     4,     5,     6,     7,     8,    77,     5,
      11,    12,    13,    76,     4,     4,    56,     4,    73,    48,
      64,    49,    56,    24,    76,    79,    27,     4,    76,    20,
      18,    78,   364,     5,    76,     5,     4,    76,     5,     5,
      41,    42,    78,     5,     4,    46,    47,    78,     5,    50,
      51,    52,    53,    54,    49,    77,    20,    78,    76,     5,
      76,    62,    63,    78,    64,    77,     4,    68,    69,    70,
      71,    72,    73,    78,    75,     5,    77,     4,     5,     6,
       7,     8,    30,    77,    11,    12,    13,   356,   292,   345,
      21,   314,    78,   314,    79,    -1,    -1,    24,    -1,    -1,
      27,    -1,    -1,    -1,    -1,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    46,
      47,    -1,    -1,    50,    51,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    46,    47,    -1,
      77,    50,    -1,    52,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,
      50,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    -1,    46,    47,    -1,    77,    50,    -1,
      52,    -1,    -1,    16,    17,    18,    19,    20,    -1,    22,
      62,    63,    25,    26,    -1,    -1,    68,    69,    70,    71,
      72,    34,    35,    36,    37,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,    -1,
      22,    -1,    -1,    25,    26,    58,    59,    60,    -1,    62,
      63,    -1,    65,    66,    67,    16,    17,    18,    19,    20,
      -1,    22,    -1,    -1,    25,    26,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    59,    60,    -1,
      62,    63,    -1,    65,    66,    67,    16,    17,    18,    19,
      20,    -1,    22,    -1,    -1,    25,    26,    58,    59,    60,
      -1,    62,    63,    -1,    65,    66,    67,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    22,    -1,    78,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    -1,    62,    63,    -1,    65,    66,    67,    -1,    16,
      17,    18,    19,    20,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    -1,    62,    63,    -1,    65,    66,
      67,    -1,    -1,    16,    17,    18,    19,    20,    -1,    22,
      -1,    78,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    62,    63,    -1,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    -1,    62,
      63,    -1,    65,    66,    67,    -1,    -1,    16,    17,    18,
      19,    20,    -1,    22,    -1,    78,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    -1,    62,    63,    -1,    65,    66,    67,    -1,
      -1,    16,    17,    18,    19,    20,    -1,    22,    -1,    78,
      25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    16,    17,    18,    19,    20,    -1,    22,    -1,    -1,
      25,    26,    -1,    58,    59,    60,    -1,    62,    63,    -1,
      65,    66,    67,    16,    17,    18,    19,    20,    -1,    22,
      -1,    76,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    60,    -1,    62,    63,    -1,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    -1,    62,
      63,    -1,    65,    66,    67,    16,    17,    18,    19,    20,
      -1,    22,    -1,    76,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,
      -1,    62,    63,    -1,    65,    66,    67,    16,    17,    18,
      19,    20,    -1,    22,    -1,    76,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    -1,    62,    63,    -1,    65,    66,    67,    16,
      17,    18,    19,    20,    -1,    22,    -1,    76,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    -1,    62,    63,    -1,    65,    66,
      67,    -1,    -1,    21,    -1,    23,    -1,    -1,    -1,    76,
      28,    29,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    21,    -1,    23,    -1,    -1,    -1,    56,    28,
      29,    30,    31,    32,    -1,    -1,    64,    -1,    -1,    38,
      39,    40,    70,    71,    72,    -1,    -1,    -1,    -1,    77,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    77,    16,
      17,    18,    19,    20,    -1,    22,    -1,    -1,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    -1,    62,    63,    -1,    65,    66,
      67,    16,    17,    18,    19,    20,    -1,    22,    -1,    -1,
      25,    26,    -1,    -1,    16,    17,    18,    19,    20,    34,
      22,    36,    37,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    -1,    62,    63,    -1,
      65,    66,    67,    -1,    -1,    -1,    58,    59,    60,    -1,
      62,    63,    -1,    65,    66,    67,    16,    17,    18,    19,
      20,    -1,    22,    -1,    -1,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    -1,    62,    63,    -1,    65,    66,    67
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    81,    82,     0,     4,     5,     6,     7,     8,    11,
      12,    13,    24,    27,    41,    42,    46,    47,    50,    51,
      52,    53,    54,    62,    63,    68,    69,    70,    71,    72,
      73,    77,    83,    84,    85,    86,    87,    90,    91,    99,
     100,   101,   103,   108,   109,   110,   115,   116,   117,   119,
     120,   123,   124,   125,   129,   130,   131,   132,   133,     5,
      18,   113,   114,    21,    23,    28,    29,    30,    31,    32,
      33,    38,    39,    40,    56,    64,    70,    71,    72,    77,
      77,    77,     5,     8,     5,    99,   119,     4,     5,     4,
       5,    99,   110,   116,     5,   111,   112,   119,   119,   119,
     119,     5,     5,     5,    75,    84,   119,    86,    76,    49,
      77,     5,   113,    76,    76,    76,    16,    17,    18,    19,
      20,    22,    25,    26,    34,    35,    36,    37,    58,    59,
      60,    62,    63,    65,    66,    67,    76,    64,    76,    76,
      76,    76,    56,    77,     4,   106,   107,   108,    55,    55,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,     5,   119,     4,    53,    54,    99,   108,   115,
     121,   119,   119,    64,    48,    49,    73,    48,     5,    64,
      49,    56,    55,    55,    55,    75,    78,     4,     5,    50,
      97,    98,   119,    56,    77,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,     5,     4,   118,   119,     4,
      88,    89,    97,    18,    19,    55,    20,     5,   114,   114,
      77,    79,     5,     5,    49,     5,    76,    78,    78,     5,
       5,    93,    94,     5,    99,    77,     5,   119,     5,   112,
     112,     5,     5,   113,    55,    78,   118,   119,    97,    77,
      77,     5,    55,    78,    78,     4,   108,     4,   108,    56,
      77,    98,    56,    77,    56,     4,    56,    77,   119,   122,
      85,    85,    48,    43,    44,    45,    75,    92,    95,    96,
      49,    56,    79,    56,    77,   119,    78,    98,    98,     4,
      85,    18,   118,   119,    97,    78,   118,   119,    97,   119,
       5,   118,   119,    97,    76,   126,     5,     4,     5,   119,
       5,    99,   100,   118,   119,    97,    78,    78,     5,     4,
     108,    78,   104,    78,    56,    77,    78,     5,   117,   122,
     127,     5,    49,    77,    78,   105,   102,   118,   119,    97,
      78,    78,    14,    15,   128,    76,    77,    98,   102,    64,
      78,    85,    85,    85,    77,    89,    78,     5,   119,    78,
      77,    78,    85,    98,    85,    78
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,    44,    61,    58,   124,    94,
      38,   310,    45,    43,    46,    42,    47,    37,    33,   126,
     311,   312,    91,   123,   313,   125,    59,    40,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    80,    82,    81,    83,    83,    84,    84,    85,    85,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    87,    87,    88,    88,    89,
      89,    90,    91,    92,    92,    92,    93,    93,    94,    94,
      95,    96,    97,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   104,   103,   105,   103,   106,   106,
     106,   106,   107,   107,   107,   107,   108,   108,   109,   109,
     110,   110,   110,   110,   111,   111,   112,   113,   113,   114,
     114,   114,   114,   115,   115,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   120,   120,   120,   120,
     120,   120,   121,   121,   122,   122,   123,   123,   124,   126,
     125,   127,   127,   128,   128,   129,   130,   130,   130,   131,
     131,   132,   133,   133
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     1,     1,     2,     2,     3,
       2,     2,     2,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     2,     1,     2,     2,     1,     2,     4,     0,
       1,     6,     5,     1,     1,     1,     0,     1,     2,     2,
       7,     4,     3,     1,     0,     1,     3,     1,     3,     1,
       4,     9,     0,     6,     0,     8,     0,     8,     1,     3,
       3,     1,     3,     5,     5,     3,     4,     4,     1,     2,
       2,     2,     4,     2,     3,     3,     3,     3,     3,     3,
       3,     4,     1,     1,     2,     4,     4,     6,     4,     3,
       4,     4,     6,     2,     2,     4,     5,     5,     7,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       1,     1,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     0,     1,     9,     9,     5,     0,
       8,     0,     6,     0,     2,     1,     2,     4,     6,     2,
       4,     6,     3,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"exit\"",
  "\"type specification\"", "\"identifier\"", "\"number\"",
  "\"float-number\"", "\"string\"", "\"echo\"", "\"in\"", "\"for\"",
  "\"while\"", "\"if\"", "\"else\"", "\"else if\"", "\"<=\"", "\">=\"",
  "\"<\"", "\">\"", "\">>\"", "\">>=\"", "\"<<\"", "\"<<=\"", "\"break\"",
  "\"==\"", "\"!=\"", "\"import\"", "\"+=\"", "\"*=\"", "\"/=\"", "\"-=\"",
  "\"%=\"", "\":=\"", "\"||\"", "\"or\"", "\"&&\"", "\"and\"", "\"&=\"",
  "\"|=\"", "\"^=\"", "\"return\"", "\"class\"", "\"public\"",
  "\"private\"", "\"protected\"", "\"true\"", "\"false\"", "\"as\"",
  "\"::\"", "\"constant\"", "\"use\"", "\"regex-pattern\"", "\"const\"",
  "\"auto\"", "','", "'='", "':'", "'|'", "'^'", "'&'", "XOR_EQUAL", "'-'",
  "'+'", "'.'", "'*'", "'/'", "'%'", "'!'", "'~'", "DECREMENT",
  "INCREMENT", "'['", "'{'", "UMINUS", "'}'", "';'", "'('", "')'", "']'",
  "$accept", "top_statements", "$@1", "statement_list",
  "statement_list_non_empty", "block_stmt", "statements", "return_stmt",
  "args_declaration_non_empty", "args_declaration", "func_declaration",
  "class_declaration", "access_modifier", "class_stmt",
  "class_stmt_no_empty", "method_declaration", "attribute_declaration",
  "arg_list", "arg_list_opt", "package_module_name", "func_name",
  "func_call", "chaining_method_call", "method_call", "@2", "@3",
  "template_args", "template_args_fix", "template",
  "variable_declaration_list", "variable_declaration_list_impl",
  "auto_variable_declaration_list_creation",
  "auto_variable_declaration_list_creation_aux",
  "variable_declaration_list_creation",
  "variable_declaration_list_creation_aux", "variable_declaration",
  "variable_declaration_impl", "assign_stmt", "type_creation", "expr",
  "literal", "variable_decl_or_empty", "expr_or_empty", "for_expr",
  "while_expr", "if_expr", "@4", "elseif_opt", "else_opt", "break_stmt",
  "import_stmt", "import_file", "alias_stmt", "constant", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        81,     0,    -1,    -1,    82,    83,    -1,    -1,    84,    -1,
      86,    -1,    84,    86,    -1,    73,    75,    -1,    73,    84,
      75,    -1,   119,    76,    -1,   115,    76,    -1,   109,    76,
      -1,    90,    -1,   125,    -1,   123,    -1,   124,    -1,    85,
      -1,   129,    76,    -1,   117,    76,    -1,   130,    76,    -1,
     131,    76,    -1,    87,    76,    -1,    91,    -1,   132,    76,
      -1,    41,   119,    -1,    41,    -1,     4,     5,    -1,    89,
      55,     4,     5,    -1,    -1,    88,    -1,     4,     5,    77,
      89,    78,    85,    -1,    42,     4,    73,    93,    75,    -1,
      43,    -1,    44,    -1,    45,    -1,    -1,    94,    -1,    93,
      96,    -1,    93,    95,    -1,    92,     4,     5,    77,    89,
      78,    85,    -1,    92,     4,     5,    76,    -1,    97,    55,
     119,    -1,   119,    -1,    -1,    97,    -1,     5,    64,     5,
      -1,     5,    -1,    99,    49,     5,    -1,     5,    -1,   100,
      77,    98,    78,    -1,    72,     5,    55,     5,    79,   100,
      77,    98,    78,    -1,    -1,   102,    64,     5,    77,    98,
      78,    -1,    -1,     5,    64,     5,    77,    98,    78,   104,
     102,    -1,    -1,   120,    64,     5,    77,    98,    78,   105,
     102,    -1,     4,    -1,   106,    55,     4,    -1,   106,    55,
     108,    -1,   108,    -1,     4,    18,     4,    -1,   106,    55,
       4,    18,     4,    -1,   106,    55,     4,    18,   108,    -1,
       4,    18,   108,    -1,     4,    18,   106,    19,    -1,     4,
      18,   107,    20,    -1,   110,    -1,    53,   110,    -1,     4,
     113,    -1,   108,   113,    -1,    99,    49,     4,   113,    -1,
      54,   111,    -1,   112,    55,   112,    -1,   111,    55,   112,
      -1,     5,    56,   119,    -1,   114,    55,   114,    -1,   113,
      55,   114,    -1,     5,    56,   118,    -1,     5,    56,   119,
      -1,     5,    77,    97,    78,    -1,     5,    -1,   116,    -1,
      53,   116,    -1,     4,     5,    56,   118,    -1,   108,     5,
      56,   118,    -1,    99,    49,     4,     5,    56,   118,    -1,
      54,     5,    56,   119,    -1,     5,    33,   119,    -1,     4,
       5,    56,   119,    -1,   108,     5,    56,   119,    -1,    99,
      49,     4,     5,    56,   119,    -1,     4,     5,    -1,   108,
       5,    -1,    99,    49,     4,     5,    -1,     4,     5,    77,
      97,    78,    -1,   108,     5,    77,    97,    78,    -1,    99,
      49,     4,     5,    77,    97,    78,    -1,     5,    56,   119,
      -1,     5,    28,   119,    -1,     5,    31,   119,    -1,     5,
      30,   119,    -1,     5,    29,   119,    -1,     5,    32,   119,
      -1,     5,    38,   119,    -1,     5,    39,   119,    -1,     5,
      40,   119,    -1,     5,    23,   119,    -1,     5,    21,   119,
      -1,     4,    77,    98,    78,    -1,   119,    62,   119,    -1,
     119,    63,   119,    -1,   119,    66,   119,    -1,   119,    65,
     119,    -1,   119,    67,   119,    -1,   119,    58,   119,    -1,
     119,    60,   119,    -1,   119,    59,   119,    -1,   119,    19,
     119,    -1,   119,    17,   119,    -1,   119,    18,   119,    -1,
     119,    16,   119,    -1,   119,    22,   119,    -1,   119,    20,
     119,    -1,   119,    25,   119,    -1,   119,    26,   119,    -1,
     119,    34,   119,    -1,   119,    36,   119,    -1,   119,    35,
     119,    -1,   119,    37,   119,    -1,    62,   119,    -1,    63,
     119,    -1,    71,     5,    -1,     5,    71,    -1,    70,     5,
      -1,     5,    70,    -1,    68,   119,    -1,    69,   119,    -1,
      77,   119,    78,    -1,   101,    -1,   103,    -1,     5,    72,
     119,    79,    -1,     5,    -1,   120,    -1,   133,    -1,     6,
      -1,     7,    -1,     8,    -1,    46,    -1,    47,    -1,    52,
      -1,    -1,   115,    -1,    -1,   119,    -1,    11,    77,   121,
      76,   122,    76,   122,    78,    85,    -1,    11,    77,   121,
      76,   122,    76,   117,    78,    85,    -1,    12,    77,   119,
      78,    85,    -1,    -1,    13,    77,   119,    78,    85,   126,
     127,   128,    -1,    -1,   127,    15,    77,   119,    78,    85,
      -1,    -1,    14,    85,    -1,    24,    -1,    27,     5,    -1,
      27,     5,    64,     5,    -1,    27,     5,    64,     5,    48,
       5,    -1,    27,     8,    -1,    27,     8,    48,     5,    -1,
      51,     5,    48,    99,    49,     5,    -1,    99,    49,    50,
      -1,    50,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     8,    10,    12,    15,    18,
      22,    25,    28,    31,    33,    35,    37,    39,    41,    44,
      47,    50,    53,    56,    58,    61,    64,    66,    69,    74,
      75,    77,    84,    90,    92,    94,    96,    97,    99,   102,
     105,   113,   118,   122,   124,   125,   127,   131,   133,   137,
     139,   144,   154,   155,   162,   163,   172,   173,   182,   184,
     188,   192,   194,   198,   204,   210,   214,   219,   224,   226,
     229,   232,   235,   240,   243,   247,   251,   255,   259,   263,
     267,   271,   276,   278,   280,   283,   288,   293,   300,   305,
     309,   314,   319,   326,   329,   332,   337,   343,   349,   357,
     361,   365,   369,   373,   377,   381,   385,   389,   393,   397,
     401,   406,   410,   414,   418,   422,   426,   430,   434,   438,
     442,   446,   450,   454,   458,   462,   466,   470,   474,   478,
     482,   486,   489,   492,   495,   498,   501,   504,   507,   510,
     514,   516,   518,   523,   525,   527,   529,   531,   533,   535,
     537,   539,   541,   542,   544,   545,   547,   557,   567,   573,
     574,   583,   584,   591,   592,   595,   597,   600,   605,   612,
     615,   620,   627,   631
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   241,   241,   241,   245,   246,   250,   251,   255,   256,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   278,   279,   283,   284,   288,
     289,   293,   297,   301,   302,   303,   307,   308,   312,   313,
     317,   321,   325,   326,   330,   331,   335,   336,   340,   341,
     346,   347,   351,   352,   356,   356,   358,   358,   363,   364,
     365,   366,   370,   376,   381,   386,   395,   396,   400,   401,
     405,   406,   407,   409,   413,   414,   418,   422,   423,   427,
     428,   429,   430,   434,   435,   439,   440,   441,   444,   445,
     446,   447,   448,   451,   452,   453,   455,   456,   457,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     476,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   518,   519,   520,   521,
     522,   523,   527,   528,   532,   533,   537,   538,   543,   547,
     547,   552,   553,   557,   558,   562,   566,   567,   568,   572,
     573,   577,   582,   583
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    68,     2,     2,     2,    67,    60,     2,
      77,    78,    65,    63,    55,    62,    64,    66,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,    76,
       2,    56,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    79,    59,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,    58,    75,    69,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      61,    70,    71,    74
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 1347;
  const int Parser::yynnts_ = 54;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 3;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 80;

  const unsigned int Parser::yyuser_token_number_max_ = 313;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 4 "interpreter/parser.y"
} // clever

/* Line 1054 of lalr1.cc  */
#line 2619 "build/interpreter/parser.cc"


/* Line 1056 of lalr1.cc  */
#line 586 "interpreter/parser.y"


namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& message) {
	driver.error(line, message);
}

} // clever

