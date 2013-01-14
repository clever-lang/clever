/* A Bison parser, made by GNU Bison 2.5.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2011 Free Software Foundation, Inc.
   
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


/* Line 293 of lalr1.cc  */
#line 39 "/usr/src/clever/core/parser.cc"


#include "parser.hh"

/* User implementation prologue.  */


/* Line 299 of lalr1.cc  */
#line 48 "/usr/src/clever/core/parser.cc"
/* Unqualified %code blocks.  */

/* Line 300 of lalr1.cc  */
#line 120 "/usr/src/clever/core/parser.y"

#include "core/driver.h"



/* Line 300 of lalr1.cc  */
#line 59 "/usr/src/clever/core/parser.cc"

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                               \
 do                                                                    \
   if (N)                                                              \
     {                                                                 \
       (Current).begin = YYRHSLOC (Rhs, 1).begin;                      \
       (Current).end   = YYRHSLOC (Rhs, N).end;                        \
     }                                                                 \
   else                                                                \
     {                                                                 \
       (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;        \
     }                                                                 \
 while (false)
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


/* Line 382 of lalr1.cc  */
#line 4 "/usr/src/clever/core/parser.y"
namespace clever {

/* Line 382 of lalr1.cc  */
#line 147 "/usr/src/clever/core/parser.cc"

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


  /// Build a parser object.
  Parser::Parser (Driver& driver_yyarg, ScannerState& state_yyarg, Compiler& c_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg),
      state (state_yyarg),
      c (c_yyarg)
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

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

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
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 565 of lalr1.cc  */
#line 112 "/usr/src/clever/core/parser.y"
{
yylloc.begin.filename = yylloc.end.filename = driver.getFile();
}

/* Line 565 of lalr1.cc  */
#line 342 "/usr/src/clever/core/parser.cc"

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
    if (yy_pact_value_is_default_ (yyn))
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
	if (yy_table_value_is_error_ (yyn))
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

/* Line 690 of lalr1.cc  */
#line 207 "/usr/src/clever/core/parser.y"
    { c.init(); }
    break;

  case 3:

/* Line 690 of lalr1.cc  */
#line 207 "/usr/src/clever/core/parser.y"
    { c.emitAST((yysemantic_stack_[(2) - (2)].block)); }
    break;

  case 4:

/* Line 690 of lalr1.cc  */
#line 211 "/usr/src/clever/core/parser.y"
    { (yyval.block) = new ast::Block(yyloc); }
    break;

  case 5:

/* Line 690 of lalr1.cc  */
#line 212 "/usr/src/clever/core/parser.y"
    { (yysemantic_stack_[(2) - (1)].block)->append((yysemantic_stack_[(2) - (2)].node));       }
    break;

  case 24:

/* Line 690 of lalr1.cc  */
#line 237 "/usr/src/clever/core/parser.y"
    { (yyval.block) = (yysemantic_stack_[(3) - (2)].block); }
    break;

  case 25:

/* Line 690 of lalr1.cc  */
#line 241 "/usr/src/clever/core/parser.y"
    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(3) - (1)].type), NULL, yyloc); }
    break;

  case 26:

/* Line 690 of lalr1.cc  */
#line 242 "/usr/src/clever/core/parser.y"
    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (5)].narray),   yyloc); }
    break;

  case 27:

/* Line 690 of lalr1.cc  */
#line 246 "/usr/src/clever/core/parser.y"
    { (yyval.break_) = new ast::Break(yyloc); }
    break;

  case 28:

/* Line 690 of lalr1.cc  */
#line 250 "/usr/src/clever/core/parser.y"
    { (yyval.continue_) = new ast::Continue(yyloc); }
    break;

  case 29:

/* Line 690 of lalr1.cc  */
#line 254 "/usr/src/clever/core/parser.y"
    { (yyval.wait) = new ast::Wait((yysemantic_stack_[(2) - (2)].ident), yyloc); }
    break;

  case 30:

/* Line 690 of lalr1.cc  */
#line 258 "/usr/src/clever/core/parser.y"
    { (yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(3) - (3)].block), (yysemantic_stack_[(3) - (2)].ident), yyloc); }
    break;

  case 31:

/* Line 690 of lalr1.cc  */
#line 259 "/usr/src/clever/core/parser.y"
    { (yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].node), yyloc); }
    break;

  case 32:

/* Line 690 of lalr1.cc  */
#line 263 "/usr/src/clever/core/parser.y"
    { (yyval.criticalblock) = new ast::CriticalBlock((yysemantic_stack_[(2) - (2)].block), yyloc); }
    break;

  case 53:

/* Line 690 of lalr1.cc  */
#line 287 "/usr/src/clever/core/parser.y"
    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 55:

/* Line 690 of lalr1.cc  */
#line 295 "/usr/src/clever/core/parser.y"
    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 57:

/* Line 690 of lalr1.cc  */
#line 303 "/usr/src/clever/core/parser.y"
    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 58:

/* Line 690 of lalr1.cc  */
#line 304 "/usr/src/clever/core/parser.y"
    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 59:

/* Line 690 of lalr1.cc  */
#line 308 "/usr/src/clever/core/parser.y"
    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 60:

/* Line 690 of lalr1.cc  */
#line 309 "/usr/src/clever/core/parser.y"
    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 61:

/* Line 690 of lalr1.cc  */
#line 313 "/usr/src/clever/core/parser.y"
    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 63:

/* Line 690 of lalr1.cc  */
#line 321 "/usr/src/clever/core/parser.y"
    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 64:

/* Line 690 of lalr1.cc  */
#line 322 "/usr/src/clever/core/parser.y"
    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 65:

/* Line 690 of lalr1.cc  */
#line 326 "/usr/src/clever/core/parser.y"
    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 66:

/* Line 690 of lalr1.cc  */
#line 330 "/usr/src/clever/core/parser.y"
    { (yyval.block) = NULL; }
    break;

  case 67:

/* Line 690 of lalr1.cc  */
#line 331 "/usr/src/clever/core/parser.y"
    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 68:

/* Line 690 of lalr1.cc  */
#line 335 "/usr/src/clever/core/parser.y"
    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 69:

/* Line 690 of lalr1.cc  */
#line 339 "/usr/src/clever/core/parser.y"
    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 70:

/* Line 690 of lalr1.cc  */
#line 343 "/usr/src/clever/core/parser.y"
    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 71:

/* Line 690 of lalr1.cc  */
#line 344 "/usr/src/clever/core/parser.y"
    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 72:

/* Line 690 of lalr1.cc  */
#line 348 "/usr/src/clever/core/parser.y"
    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 73:

/* Line 690 of lalr1.cc  */
#line 349 "/usr/src/clever/core/parser.y"
    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 74:

/* Line 690 of lalr1.cc  */
#line 350 "/usr/src/clever/core/parser.y"
    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 75:

/* Line 690 of lalr1.cc  */
#line 351 "/usr/src/clever/core/parser.y"
    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 76:

/* Line 690 of lalr1.cc  */
#line 355 "/usr/src/clever/core/parser.y"
    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 77:

/* Line 690 of lalr1.cc  */
#line 356 "/usr/src/clever/core/parser.y"
    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 78:

/* Line 690 of lalr1.cc  */
#line 357 "/usr/src/clever/core/parser.y"
    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 79:

/* Line 690 of lalr1.cc  */
#line 358 "/usr/src/clever/core/parser.y"
    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 80:

/* Line 690 of lalr1.cc  */
#line 359 "/usr/src/clever/core/parser.y"
    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 81:

/* Line 690 of lalr1.cc  */
#line 360 "/usr/src/clever/core/parser.y"
    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 82:

/* Line 690 of lalr1.cc  */
#line 364 "/usr/src/clever/core/parser.y"
    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 83:

/* Line 690 of lalr1.cc  */
#line 365 "/usr/src/clever/core/parser.y"
    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 84:

/* Line 690 of lalr1.cc  */
#line 369 "/usr/src/clever/core/parser.y"
    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 85:

/* Line 690 of lalr1.cc  */
#line 370 "/usr/src/clever/core/parser.y"
    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 86:

/* Line 690 of lalr1.cc  */
#line 374 "/usr/src/clever/core/parser.y"
    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 87:

/* Line 690 of lalr1.cc  */
#line 375 "/usr/src/clever/core/parser.y"
    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 88:

/* Line 690 of lalr1.cc  */
#line 376 "/usr/src/clever/core/parser.y"
    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 89:

/* Line 690 of lalr1.cc  */
#line 377 "/usr/src/clever/core/parser.y"
    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 90:

/* Line 690 of lalr1.cc  */
#line 378 "/usr/src/clever/core/parser.y"
    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 91:

/* Line 690 of lalr1.cc  */
#line 382 "/usr/src/clever/core/parser.y"
    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 92:

/* Line 690 of lalr1.cc  */
#line 383 "/usr/src/clever/core/parser.y"
    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 93:

/* Line 690 of lalr1.cc  */
#line 384 "/usr/src/clever/core/parser.y"
    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 94:

/* Line 690 of lalr1.cc  */
#line 385 "/usr/src/clever/core/parser.y"
    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 95:

/* Line 690 of lalr1.cc  */
#line 386 "/usr/src/clever/core/parser.y"
    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 96:

/* Line 690 of lalr1.cc  */
#line 390 "/usr/src/clever/core/parser.y"
    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 97:

/* Line 690 of lalr1.cc  */
#line 391 "/usr/src/clever/core/parser.y"
    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 98:

/* Line 690 of lalr1.cc  */
#line 395 "/usr/src/clever/core/parser.y"
    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 99:

/* Line 690 of lalr1.cc  */
#line 396 "/usr/src/clever/core/parser.y"
    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 100:

/* Line 690 of lalr1.cc  */
#line 400 "/usr/src/clever/core/parser.y"
    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 101:

/* Line 690 of lalr1.cc  */
#line 401 "/usr/src/clever/core/parser.y"
    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 102:

/* Line 690 of lalr1.cc  */
#line 405 "/usr/src/clever/core/parser.y"
    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 103:

/* Line 690 of lalr1.cc  */
#line 406 "/usr/src/clever/core/parser.y"
    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 104:

/* Line 690 of lalr1.cc  */
#line 410 "/usr/src/clever/core/parser.y"
    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 105:

/* Line 690 of lalr1.cc  */
#line 414 "/usr/src/clever/core/parser.y"
    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 106:

/* Line 690 of lalr1.cc  */
#line 418 "/usr/src/clever/core/parser.y"
    { (yyval.import) = new ast::Import((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].ident), yyloc);   }
    break;

  case 107:

/* Line 690 of lalr1.cc  */
#line 419 "/usr/src/clever/core/parser.y"
    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), NULL, yyloc); }
    break;

  case 108:

/* Line 690 of lalr1.cc  */
#line 423 "/usr/src/clever/core/parser.y"
    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 109:

/* Line 690 of lalr1.cc  */
#line 428 "/usr/src/clever/core/parser.y"
    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); }
    break;

  case 110:

/* Line 690 of lalr1.cc  */
#line 430 "/usr/src/clever/core/parser.y"
    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); }
    break;

  case 111:

/* Line 690 of lalr1.cc  */
#line 432 "/usr/src/clever/core/parser.y"
    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); }
    break;

  case 112:

/* Line 690 of lalr1.cc  */
#line 434 "/usr/src/clever/core/parser.y"
    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); }
    break;

  case 113:

/* Line 690 of lalr1.cc  */
#line 439 "/usr/src/clever/core/parser.y"
    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, yyloc); }
    break;

  case 114:

/* Line 690 of lalr1.cc  */
#line 441 "/usr/src/clever/core/parser.y"
    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), yyloc); }
    break;

  case 115:

/* Line 690 of lalr1.cc  */
#line 443 "/usr/src/clever/core/parser.y"
    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); }
    break;

  case 116:

/* Line 690 of lalr1.cc  */
#line 445 "/usr/src/clever/core/parser.y"
    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), yyloc); }
    break;

  case 117:

/* Line 690 of lalr1.cc  */
#line 449 "/usr/src/clever/core/parser.y"
    { (yyval.narray) = NULL; }
    break;

  case 119:

/* Line 690 of lalr1.cc  */
#line 454 "/usr/src/clever/core/parser.y"
    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 120:

/* Line 690 of lalr1.cc  */
#line 455 "/usr/src/clever/core/parser.y"
    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 121:

/* Line 690 of lalr1.cc  */
#line 459 "/usr/src/clever/core/parser.y"
    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 122:

/* Line 690 of lalr1.cc  */
#line 460 "/usr/src/clever/core/parser.y"
    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 123:

/* Line 690 of lalr1.cc  */
#line 464 "/usr/src/clever/core/parser.y"
    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 124:

/* Line 690 of lalr1.cc  */
#line 464 "/usr/src/clever/core/parser.y"
    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 125:

/* Line 690 of lalr1.cc  */
#line 468 "/usr/src/clever/core/parser.y"
    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 126:

/* Line 690 of lalr1.cc  */
#line 469 "/usr/src/clever/core/parser.y"
    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 127:

/* Line 690 of lalr1.cc  */
#line 474 "/usr/src/clever/core/parser.y"
    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 129:

/* Line 690 of lalr1.cc  */
#line 480 "/usr/src/clever/core/parser.y"
    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 130:

/* Line 690 of lalr1.cc  */
#line 484 "/usr/src/clever/core/parser.y"
    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 131:

/* Line 690 of lalr1.cc  */
#line 485 "/usr/src/clever/core/parser.y"
    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 132:

/* Line 690 of lalr1.cc  */
#line 489 "/usr/src/clever/core/parser.y"
    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 133:

/* Line 690 of lalr1.cc  */
#line 490 "/usr/src/clever/core/parser.y"
    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 134:

/* Line 690 of lalr1.cc  */
#line 490 "/usr/src/clever/core/parser.y"
    { (yyval.ifcond) = (yysemantic_stack_[(9) - (9)].ifcond); }
    break;



/* Line 690 of lalr1.cc  */
#line 1091 "/usr/src/clever/core/parser.cc"
	default:
          break;
      }
    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
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
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
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

    yyerror_range[1] = yylocation_stack_[yylen - 1];
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
	if (!yy_pact_value_is_default_ (yyn))
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

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

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
  Parser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = 0;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int Parser::yypact_ninf_ = -131;
  const short int
  Parser::yypact_[] =
  {
      -131,    32,  -131,  -131,   293,    29,   -29,   -20,  -131,  -131,
    -131,   -42,   -28,  -131,    46,     7,  -131,  -131,    48,    13,
      52,    54,   -14,    60,    60,  -131,   -14,     7,  -131,     7,
       9,     7,  -131,  -131,  -131,   -12,   -11,   -10,  -131,  -131,
     497,   -18,  -131,  -131,    -8,  -131,  -131,     1,     8,  -131,
    -131,  -131,  -131,  -131,    18,    42,    43,  -131,  -131,    45,
      49,  -131,  -131,    24,    41,  -131,    19,     7,     7,     7,
      63,    50,     9,   497,    -3,  -131,  -131,  -131,    72,    76,
    -131,    53,     3,   -27,  -131,  -131,  -131,  -131,  -131,  -131,
      82,   497,   497,    55,    79,    77,  -131,   237,    59,    84,
     343,  -131,  -131,  -131,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,   143,     7,     7,     7,  -131,  -131,     7,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,  -131,     7,    29,    75,    87,
      71,   365,   420,    14,     7,    48,     4,   -22,   -14,   -49,
      92,     7,  -131,    94,   105,    82,  -131,  -131,     7,     7,
    -131,  -131,   149,  -131,   480,   480,   480,   480,    10,    10,
     662,   662,   585,   518,   596,   573,   607,   148,   673,   -26,
     -26,    96,  -131,  -131,  -131,   497,   497,  -131,     7,     7,
    -131,   -14,   -14,   112,  -131,   497,  -131,   -14,   -23,    97,
     114,  -131,   175,   -14,   -14,   127,   179,   -14,  -131,  -131,
     497,   497,   137,     7,   116,   117,  -131,  -131,  -131,   120,
    -131,   175,   -14,   -14,   134,   121,  -131,  -131,   -14,   122,
    -131,     7,   123,  -131,  -131,   125,  -131,  -131,   126,  -131,
    -131,  -131,   -14,  -131,   -14,   497,  -131,     7,   195,   -14,
    -131,  -131,   136,   138,   207,  -131,  -131,     7,   -14,  -131,
     442,  -131,   -14,  -131
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    33,    35,    36,
      34,     0,     0,    27,     0,   126,    38,    39,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,    28,   117,
       4,     0,     5,    16,    48,     0,     0,     0,    17,    18,
       0,     0,    51,    52,     0,    23,    49,    50,    45,    44,
      43,    41,    40,    42,     0,     0,     0,    11,    47,    46,
       0,    14,    13,   101,    96,    98,     0,   117,     0,     0,
       0,     0,     0,   125,     0,    50,    45,    46,     0,    97,
     102,     0,     0,     0,    29,     4,    32,    54,    74,    75,
       0,    61,   119,     0,   118,     0,    59,     0,     0,    56,
       0,    21,    22,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    72,    73,     0,    20,    10,
      15,     7,     8,     6,     9,    12,     0,     0,     0,    25,
       0,     0,     0,     0,     0,     0,     0,   101,     0,     0,
       0,     0,    30,     0,    66,    62,    63,    55,     0,     0,
      24,    60,     0,    53,    81,    79,    80,    78,    95,    94,
      76,    77,    82,    84,    83,    85,    92,    93,    91,    87,
      86,    69,    88,    89,    90,   105,   100,    99,   117,   117,
     123,     0,     0,     0,   107,   104,   103,     0,     0,     0,
       0,   113,     0,     0,     0,     0,     0,     0,    68,    64,
     120,    57,     0,   117,     0,     0,   121,   127,   132,     0,
     109,     0,     0,     0,     0,     0,   115,   114,     0,     0,
      67,     0,     0,    71,    26,   124,   128,   106,     0,   111,
     110,   108,     0,    31,     0,    58,    70,   117,   133,     0,
     116,    65,     0,     0,   130,   112,   122,     0,     0,   134,
       0,   131,     0,   129
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -131,  -131,  -131,   220,  -131,   -21,  -131,  -131,  -131,  -131,
    -131,  -131,    -4,    -2,  -131,  -131,  -131,  -131,  -131,  -131,
    -131,    69,  -131,  -131,  -131,    -1,     2,  -131,  -131,  -131,
    -131,  -131,  -131,   -56,  -130,  -131,    80,  -131,  -131,  -129,
    -131,  -131,   -63,  -131,  -131,    20,  -131,  -131,  -131,  -131,
    -131,  -131,  -131,  -131
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,    97,    32,    33,    34,    35,    36,    37,
      38,    39,    92,    74,    42,    98,    99,    43,    44,   154,
     155,   156,   208,    45,    46,    75,    76,    49,    50,    51,
      52,    53,    54,    64,    65,    79,    80,    55,    56,   150,
      57,    58,    93,    94,   235,    77,   216,    60,    61,   248,
     259,    62,   236,   254
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char Parser::yytable_ninf_ = -55;
  const short int
  Parser::yytable_[] =
  {
        40,    86,    41,    47,   140,    90,    48,   187,   202,   147,
     147,    73,     6,     7,     8,     9,    10,   199,    95,    81,
     193,    88,    89,    91,    59,   138,   149,   100,   -54,   -54,
     125,   126,     3,   203,   221,    63,   136,    66,   -54,    68,
     127,   122,   123,   124,   200,   125,   126,    16,    17,   151,
      85,    71,    70,    69,    78,    23,    24,    25,    83,   222,
      84,    67,   152,    85,   141,   142,    87,   101,   102,   103,
     139,   128,   187,   225,   119,   120,   121,   122,   123,   124,
     129,   194,   136,    29,    72,   148,   197,   130,    31,    96,
     198,   187,   238,    40,    82,    41,    47,   131,   137,    48,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,    59,   182,   183,
     184,   132,   133,   185,   134,   214,   215,   201,   135,   143,
     144,    82,   186,   145,   146,   153,   158,   159,   157,   161,
     195,   162,   104,   105,   106,   107,   108,   205,   109,   181,
     232,   110,   111,   190,   210,   211,   188,   207,   212,   112,
     113,   114,   115,   104,   105,   106,   107,   108,   189,   109,
     217,   218,   110,   111,   204,   206,   220,   213,   219,   223,
     224,   147,   226,   227,   252,   229,   230,   237,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   231,   233,   234,
     241,   239,   240,   242,   244,   246,   247,   243,   249,   253,
     228,   118,   119,   120,   121,   122,   123,   124,   256,   257,
     258,   250,     4,   251,   209,   196,     0,   245,   255,     0,
       0,     0,     0,     0,     0,     0,     0,   261,     0,     0,
       5,   263,     6,     7,     8,     9,    10,     0,    11,    12,
       0,     0,     0,   260,     0,     0,     0,     0,     0,     0,
      13,     0,     0,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,    16,    17,    18,
       0,    19,    20,    21,    22,    23,    24,    25,     0,     0,
       0,    26,    27,    28,     0,     0,     5,     0,     6,     7,
       8,     9,    10,     0,    11,    12,     0,     0,     0,     0,
       0,     0,     0,    29,    30,     0,    13,   160,    31,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    15,    16,    17,    18,     0,    19,    20,    21,
      22,    23,    24,    25,     0,     0,     0,    26,    27,    28,
       0,     0,     0,     0,     0,     0,     0,     0,   104,   105,
     106,   107,   108,     0,   109,     0,     0,   110,   111,    29,
      30,     0,     0,     0,    31,   112,   113,   114,   115,     0,
     104,   105,   106,   107,   108,     0,   109,     0,     0,   110,
     111,     0,     0,     0,     0,     0,     0,   112,   113,   114,
     115,     0,     0,     0,   116,   117,   118,   119,   120,   121,
     122,   123,   124,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   163,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   104,   105,   106,   107,   108,
       0,   109,     0,     0,   110,   111,     0,   191,     0,     0,
       0,     0,   112,   113,   114,   115,     0,   104,   105,   106,
     107,   108,     0,   109,     0,     0,   110,   111,     0,     0,
       0,     0,     0,     0,   112,   113,   114,   115,     0,     0,
       0,   116,   117,   118,   119,   120,   121,   122,   123,   124,
       0,     0,     0,     0,     0,   -55,   -55,   -55,   -55,   108,
       0,   109,   192,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   104,   105,   106,   107,   108,     0,   109,     0,
       0,   110,   111,     0,   262,     0,     0,     0,     0,   112,
     113,   114,   115,   104,   105,   106,   107,   108,     0,   109,
       0,     0,   110,   111,   119,   120,   121,   122,   123,   124,
     112,     0,   114,   115,     0,     0,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   104,   105,
     106,   107,   108,     0,   109,     0,     0,   110,   111,     0,
     104,   105,   106,   107,   108,   112,   109,   114,     0,   110,
     111,   104,   105,   106,   107,   108,     0,   109,     0,   114,
     110,   111,   104,   105,   106,   107,   108,     0,   109,     0,
       0,   110,   111,     0,   116,   117,   118,   119,   120,   121,
     122,   123,   124,     0,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,     0,     0,   116,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   104,   105,   106,
     107,   108,     0,   109,     0,     0,   -55,   -55,   104,   105,
     106,   107,   108,     0,   109,     0,     0,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   119,   120,   121,   122,
     123,   124,     0,     0,     0,     0,     0,   119,   120,   121,
     122,   123,   124
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,    22,     4,     4,    67,    26,     4,   137,    57,     6,
       6,    15,     5,     6,     7,     8,     9,   146,     9,     6,
       6,    23,    24,    27,     4,     6,    82,    31,    48,    49,
      48,    49,     0,    82,    57,     6,    58,    66,    58,    81,
      58,    67,    68,    69,    66,    48,    49,    40,    41,    76,
      77,    44,     6,    81,     6,    48,    49,    50,     6,    82,
       6,    81,    83,    77,    68,    69,     6,    79,    79,    79,
      51,    79,   202,   202,    64,    65,    66,    67,    68,    69,
      79,    67,    58,    76,    77,    82,    82,    79,    81,    80,
     146,   221,   221,    97,    81,    97,    97,    79,    57,    97,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,    97,   122,   123,
     124,    79,    79,   127,    79,   188,   189,   148,    79,    66,
      58,    81,   136,    57,    81,    53,    57,    60,    83,    80,
     144,    57,    15,    16,    17,    18,    19,   151,    21,     6,
     213,    24,    25,    82,   158,   159,    81,    52,     9,    32,
      33,    34,    35,    15,    16,    17,    18,    19,    81,    21,
     191,   192,    24,    25,    82,    81,   197,    81,    66,    82,
      66,     6,   203,   204,   247,     6,   207,    67,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    60,    82,    82,
      66,   222,   223,    82,    82,    82,    81,   228,    82,    14,
      83,    63,    64,    65,    66,    67,    68,    69,    82,    81,
      13,   242,     2,   244,   155,   145,    -1,   231,   249,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   258,    -1,    -1,
       3,   262,     5,     6,     7,     8,     9,    -1,    11,    12,
      -1,    -1,    -1,   257,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      -1,    44,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    54,    55,    56,    -1,    -1,     3,    -1,     5,     6,
       7,     8,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    23,    80,    81,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    -1,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,
      17,    18,    19,    -1,    21,    -1,    -1,    24,    25,    76,
      77,    -1,    -1,    -1,    81,    32,    33,    34,    35,    -1,
      15,    16,    17,    18,    19,    -1,    21,    -1,    -1,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    -1,    -1,    -1,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    15,    16,    17,    18,    19,
      -1,    21,    -1,    -1,    24,    25,    -1,    82,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    -1,    15,    16,    17,
      18,    19,    -1,    21,    -1,    -1,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,    19,
      -1,    21,    82,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    15,    16,    17,    18,    19,    -1,    21,    -1,
      -1,    24,    25,    -1,    82,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    15,    16,    17,    18,    19,    -1,    21,
      -1,    -1,    24,    25,    64,    65,    66,    67,    68,    69,
      32,    -1,    34,    35,    -1,    -1,    -1,    -1,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    15,    16,
      17,    18,    19,    -1,    21,    -1,    -1,    24,    25,    -1,
      15,    16,    17,    18,    19,    32,    21,    34,    -1,    24,
      25,    15,    16,    17,    18,    19,    -1,    21,    -1,    34,
      24,    25,    15,    16,    17,    18,    19,    -1,    21,    -1,
      -1,    24,    25,    -1,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    15,    16,    17,
      18,    19,    -1,    21,    -1,    -1,    24,    25,    15,    16,
      17,    18,    19,    -1,    21,    -1,    -1,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    69
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    85,    86,     0,    87,     3,     5,     6,     7,     8,
       9,    11,    12,    23,    26,    39,    40,    41,    42,    44,
      45,    46,    47,    48,    49,    50,    54,    55,    56,    76,
      77,    81,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,   101,   102,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   121,   122,   124,   125,   129,
     131,   132,   135,     6,   117,   118,    66,    81,    81,    81,
       6,    44,    77,    96,    97,   109,   110,   129,     6,   119,
     120,     6,    81,     6,     6,    77,    89,     6,    97,    97,
      89,    96,    96,   126,   127,     9,    80,    87,    99,   100,
      96,    79,    79,    79,    15,    16,    17,    18,    19,    21,
      24,    25,    32,    33,    34,    35,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    48,    49,    58,    79,    79,
      79,    79,    79,    79,    79,    79,    58,    57,     6,    51,
     126,    96,    96,    66,    58,    57,    81,     6,    82,   117,
     123,    76,    89,    53,   103,   104,   105,    83,    57,    60,
      80,    80,    57,    82,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,     6,    96,    96,    96,    96,    96,   118,    81,    81,
      82,    82,    82,     6,    67,    96,   120,    82,   117,   123,
      66,    89,    57,    82,    82,    96,    81,    52,   106,   105,
      96,    96,     9,    81,   126,   126,   130,    89,    89,    66,
      89,    57,    82,    82,    66,   123,    89,    89,    83,     6,
      89,    60,   126,    82,    82,   128,   136,    67,   123,    89,
      89,    66,    82,    89,    82,    96,    82,    81,   133,    82,
      89,    89,   126,    14,   137,    89,    82,    81,    13,   134,
      96,    89,    82,    89
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
     305,   306,   307,   308,   309,   310,   311,    44,    61,   312,
      58,   124,    94,    38,    45,    43,    46,    42,    47,    37,
      33,   126,   313,   314,   315,   316,    91,   123,   317,    59,
     125,    40,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    84,    86,    85,    87,    87,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    89,    90,    90,    91,    92,    93,
      94,    94,    95,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    97,    98,    99,   100,   100,   101,
     101,   102,   103,   104,   104,   105,   106,   106,   107,   108,
     109,   109,   110,   110,   110,   110,   111,   111,   111,   111,
     111,   111,   112,   112,   113,   113,   114,   114,   114,   114,
     114,   115,   115,   115,   115,   115,   116,   116,   117,   117,
     118,   118,   119,   119,   120,   121,   122,   122,   123,   124,
     124,   124,   124,   125,   125,   125,   125,   126,   126,   127,
     127,   128,   128,   130,   129,   131,   131,   132,   133,   133,
     134,   134,   136,   137,   135
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     2,     1,     1,     1,     2,
       2,     2,     2,     1,     3,     3,     6,     1,     1,     2,
       3,     6,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     3,     5,     2,
       3,     2,     1,     1,     2,     5,     0,     2,     4,     3,
       6,     6,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     3,
       3,     1,     1,     3,     3,     3,     6,     4,     4,     5,
       6,     6,     8,     4,     5,     5,     7,     0,     1,     1,
       3,     0,     4,     0,     6,     2,     1,     5,     0,     6,
       0,     2,     0,     0,     9
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"var\"", "\"exit\"",
  "\"type specification\"", "\"identifier\"", "\"number\"",
  "\"float-number\"", "\"string\"", "\"for\"", "\"while\"", "\"if\"",
  "\"else\"", "\"else if\"", "\"<=\"", "\">=\"", "\"<\"", "\">\"",
  "\">>\"", "\">>=\"", "\"<<\"", "\"<<=\"", "\"break\"", "\"==\"",
  "\"!=\"", "\"import\"", "\"+=\"", "\"*=\"", "\"/=\"", "\"-=\"", "\"%=\"",
  "\"||\"", "\"or\"", "\"&&\"", "\"and\"", "\"&=\"", "\"|=\"", "\"^=\"",
  "\"return\"", "\"true\"", "\"false\"", "\"const\"", "\"print\"",
  "\"function\"", "\"spawn\"", "\"wait\"", "\"critical\"", "\"++\"",
  "\"--\"", "\"null\"", "\"new\"", "\"finally\"", "\"catch\"", "\"try\"",
  "\"throw\"", "\"continue\"", "','", "'='", "XOR_EQUAL", "':'", "'|'",
  "'^'", "'&'", "'-'", "'+'", "'.'", "'*'", "'/'", "'%'", "'!'", "'~'",
  "DEEPCOPY", "COPY", "DECREMENT", "INCREMENT", "'['", "'{'", "UMINUS",
  "';'", "'}'", "'('", "')'", "']'", "$accept", "program", "$@1",
  "statement_list", "statement", "block", "instantiation", "break",
  "continue", "wait", "thread_block", "critical_block", "rvalue", "lvalue",
  "array", "key_value_list", "non_empty_key_value_list", "map", "throw",
  "catch", "not_empty_catch", "catch_impl", "finally", "try_catch_finally",
  "property_access", "mcall", "inc_dec", "comparison", "boolean", "logic",
  "arithmetic", "bitwise", "variable_decl", "variable_decl_list",
  "variable_decl_impl", "const_decl_list", "const_decl_impl", "assignment",
  "import", "vararg", "fdecl", "anonymous_fdecl", "call_args",
  "non_empty_call_args", "fcall_chain", "fcall", "@2", "return_stmt",
  "while", "elseif", "else", "if", "@3", "@4", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        85,     0,    -1,    -1,    86,    87,    -1,    -1,    87,    88,
      -1,   122,    79,    -1,   116,    79,    -1,   121,    79,    -1,
     129,    79,    -1,   109,    79,    -1,   124,    -1,   131,    79,
      -1,   135,    -1,   132,    -1,   110,    79,    -1,    89,    -1,
      94,    -1,    95,    -1,    93,    79,    -1,   102,    79,    -1,
      91,    79,    -1,    92,    79,    -1,   107,    -1,    77,    87,
      80,    -1,     5,    66,    51,    -1,     5,    66,    51,    81,
     126,    82,    -1,    23,    -1,    56,    -1,    46,     6,    -1,
      45,     6,    89,    -1,    45,     6,    76,    96,    83,    89,
      -1,    47,    89,    -1,     6,    -1,     9,    -1,     7,    -1,
       8,    -1,    50,    -1,    40,    -1,    41,    -1,   114,    -1,
     113,    -1,   115,    -1,   112,    -1,   111,    -1,   110,    -1,
     129,    -1,   125,    -1,    90,    -1,   108,    -1,   109,    -1,
      98,    -1,   101,    -1,    81,    96,    82,    -1,     6,    -1,
      76,   126,    83,    -1,   100,    -1,     9,    60,    96,    -1,
     100,    57,     9,    60,    96,    -1,    77,    80,    -1,    77,
      99,    80,    -1,    55,    96,    -1,   104,    -1,   105,    -1,
     104,   105,    -1,    53,    81,     6,    82,    89,    -1,    -1,
      52,    89,    -1,    54,    89,   103,   106,    -1,    96,    66,
       6,    -1,    96,    66,     6,    81,   126,    82,    -1,     5,
      66,     6,    81,   126,    82,    -1,    97,    48,    -1,    97,
      49,    -1,    48,    97,    -1,    49,    97,    -1,    96,    24,
      96,    -1,    96,    25,    96,    -1,    96,    18,    96,    -1,
      96,    16,    96,    -1,    96,    17,    96,    -1,    96,    15,
      96,    -1,    96,    32,    96,    -1,    96,    34,    96,    -1,
      96,    33,    96,    -1,    96,    35,    96,    -1,    96,    65,
      96,    -1,    96,    64,    96,    -1,    96,    67,    96,    -1,
      96,    68,    96,    -1,    96,    69,    96,    -1,    96,    63,
      96,    -1,    96,    61,    96,    -1,    96,    62,    96,    -1,
      96,    21,    96,    -1,    96,    19,    96,    -1,     3,   117,
      -1,    42,   119,    -1,   118,    -1,   117,    57,   118,    -1,
       6,    58,    96,    -1,     6,    -1,   120,    -1,   119,    57,
     120,    -1,     6,    58,    96,    -1,    97,    58,    96,    -1,
      26,     6,    66,     6,    66,    67,    -1,    26,     6,    66,
      67,    -1,     6,    66,    66,    66,    -1,    44,     6,    81,
      82,    89,    -1,    44,     6,    81,   123,    82,    89,    -1,
      44,     6,    81,   117,    82,    89,    -1,    44,     6,    81,
     117,    57,   123,    82,    89,    -1,    44,    81,    82,    89,
      -1,    44,    81,   123,    82,    89,    -1,    44,    81,   117,
      82,    89,    -1,    44,    81,   117,    57,   123,    82,    89,
      -1,    -1,   127,    -1,    96,    -1,   127,    57,    96,    -1,
      -1,   128,    81,   126,    82,    -1,    -1,     6,    81,   126,
      82,   130,   128,    -1,    39,    96,    -1,    39,    -1,    11,
      81,    96,    82,    89,    -1,    -1,   133,    14,    81,    96,
      82,    89,    -1,    -1,    13,    89,    -1,    -1,    -1,    12,
      81,    96,    82,    89,   136,   133,   137,   134,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     8,    11,    14,    17,    20,
      23,    26,    28,    31,    33,    35,    38,    40,    42,    44,
      47,    50,    53,    56,    58,    62,    66,    73,    75,    77,
      80,    84,    91,    94,    96,    98,   100,   102,   104,   106,
     108,   110,   112,   114,   116,   118,   120,   122,   124,   126,
     128,   130,   132,   134,   138,   140,   144,   146,   150,   156,
     159,   163,   166,   168,   170,   173,   179,   180,   183,   188,
     192,   199,   206,   209,   212,   215,   218,   222,   226,   230,
     234,   238,   242,   246,   250,   254,   258,   262,   266,   270,
     274,   278,   282,   286,   290,   294,   298,   301,   304,   306,
     310,   314,   316,   318,   322,   326,   330,   337,   342,   347,
     353,   360,   367,   376,   381,   387,   393,   401,   402,   404,
     406,   410,   411,   416,   417,   424,   427,   429,   435,   436,
     443,   444,   447,   448,   449
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   207,   207,   207,   211,   212,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   237,   241,   242,   246,   250,   254,
     258,   259,   263,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   291,   295,   299,   303,   304,   308,
     309,   313,   317,   321,   322,   326,   330,   331,   335,   339,
     343,   344,   348,   349,   350,   351,   355,   356,   357,   358,
     359,   360,   364,   365,   369,   370,   374,   375,   376,   377,
     378,   382,   383,   384,   385,   386,   390,   391,   395,   396,
     400,   401,   405,   406,   410,   414,   418,   419,   423,   427,
     429,   431,   433,   438,   440,   442,   444,   449,   450,   454,
     455,   459,   460,   464,   464,   468,   469,   473,   477,   479,
     484,   485,   489,   490,   489
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
       2,     2,     2,    70,     2,     2,     2,    69,    63,     2,
      81,    82,    67,    65,    57,    64,    66,    68,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,    79,
       2,    58,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    83,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    77,    61,    80,    71,     2,     2,     2,
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
      55,    56,    59,    72,    73,    74,    75,    78
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 742;
  const int Parser::yynnts_ = 54;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 3;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 84;

  const unsigned int Parser::yyuser_token_number_max_ = 317;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1136 of lalr1.cc  */
#line 4 "/usr/src/clever/core/parser.y"
} // clever

/* Line 1136 of lalr1.cc  */
#line 1935 "/usr/src/clever/core/parser.cc"


/* Line 1138 of lalr1.cc  */
#line 492 "/usr/src/clever/core/parser.y"


namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever

