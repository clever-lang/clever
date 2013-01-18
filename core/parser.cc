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




#include "parser.hh"

/* User implementation prologue.  */


/* Unqualified %code blocks.  */


#include "core/driver.h"




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


namespace clever {


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
    
{
yylloc.begin.filename = yylloc.end.filename = driver.getFile();
}


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

    { c.init(); }
    break;

  case 3:

    { c.emitAST((yysemantic_stack_[(2) - (2)].block)); }
    break;

  case 4:

    { (yyval.block) = new ast::Block(yyloc); }
    break;

  case 5:

    { (yysemantic_stack_[(2) - (1)].block)->append((yysemantic_stack_[(2) - (2)].node));       }
    break;

  case 23:

    { (yyval.block) = (yysemantic_stack_[(3) - (2)].block); }
    break;

  case 24:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(3) - (1)].type), NULL, yyloc); }
    break;

  case 25:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (5)].narray),   yyloc); }
    break;

  case 26:

    { (yyval.break_) = new ast::Break(yyloc); }
    break;

  case 27:

    { (yyval.continue_) = new ast::Continue(yyloc); }
    break;

  case 28:

    { (yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(3) - (3)].block), (yysemantic_stack_[(3) - (2)].ident), yyloc); }
    break;

  case 29:

    { (yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].node), yyloc); }
    break;

  case 30:

    { (yyval.criticalblock) = new ast::CriticalBlock((yysemantic_stack_[(2) - (2)].block), yyloc); }
    break;

  case 52:

    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 54:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 56:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 57:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 58:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 59:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 60:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 62:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 63:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 64:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 65:

    { (yyval.block) = NULL; }
    break;

  case 66:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 67:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 68:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 69:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 70:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 71:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 72:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 73:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 74:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 75:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 76:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 77:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 78:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 79:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 80:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 81:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 82:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 83:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 84:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 85:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 86:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 87:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 88:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 89:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 90:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 91:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 92:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 93:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 94:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 95:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 96:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 97:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 98:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 99:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 100:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 101:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 102:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 103:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 104:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 105:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 106:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 107:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 108:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].ident), yyloc);   }
    break;

  case 109:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), NULL, yyloc); }
    break;

  case 110:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 111:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); }
    break;

  case 112:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); }
    break;

  case 113:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); }
    break;

  case 114:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); }
    break;

  case 115:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, yyloc); }
    break;

  case 116:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), yyloc); }
    break;

  case 117:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); }
    break;

  case 118:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), yyloc); }
    break;

  case 119:

    { (yyval.narray) = NULL; }
    break;

  case 121:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 122:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 123:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 124:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 125:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 126:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 127:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 128:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 129:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 131:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 132:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 133:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 134:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 135:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 136:

    { (yyval.ifcond) = (yysemantic_stack_[(9) - (9)].ifcond); }
    break;



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
  const short int Parser::yypact_ninf_ = -133;
  const short int
  Parser::yypact_[] =
  {
      -133,    45,  -133,  -133,   280,    27,   -19,    -6,  -133,  -133,
    -133,   -11,    -9,  -133,    81,     9,  -133,  -133,    63,    37,
     115,    46,   116,   116,  -133,    46,     9,  -133,  -133,     9,
      16,     9,  -133,  -133,  -133,    48,    49,  -133,  -133,   507,
     -12,  -133,  -133,    60,  -133,  -133,    61,    62,  -133,  -133,
    -133,  -133,  -133,    64,    65,    67,  -133,  -133,    69,    70,
    -133,  -133,    66,    85,  -133,    18,     9,     9,     9,    59,
      73,    16,   507,     7,  -133,  -133,  -133,    89,    93,  -133,
      75,     1,   -10,  -133,  -133,  -133,  -133,  -133,    99,   507,
     507,    74,   101,   100,  -133,   224,    79,   104,   353,  -133,
    -133,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,    33,     9,
       9,     9,  -133,  -133,     9,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,     9,    27,    87,    94,  -133,    80,   408,
     430,     4,     9,    63,     2,   -18,    46,   -38,    92,     9,
    -133,    96,   127,    99,  -133,  -133,     9,     9,  -133,  -133,
     170,  -133,   674,   674,   674,   674,    68,    68,    13,    13,
     586,   562,   148,   574,   597,   652,   663,    -8,    -8,   103,
    -133,  -133,  -133,  -133,   507,   507,  -133,     9,     9,  -133,
      46,    46,   114,  -133,   507,  -133,    46,   -31,   105,   119,
    -133,   175,    46,    46,   330,   182,    46,  -133,  -133,   507,
     507,   130,     9,   109,   110,  -133,  -133,  -133,   126,  -133,
     175,    46,    46,   128,   113,  -133,  -133,    46,   117,  -133,
       9,   118,  -133,  -133,   122,  -133,  -133,   123,  -133,  -133,
    -133,    46,  -133,    46,   507,  -133,     9,   183,    46,  -133,
    -133,   124,   137,   185,  -133,  -133,     9,    46,  -133,   485,
    -133,    46,  -133
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    31,    34,    35,
      33,     0,     0,    26,     0,   128,    37,    38,     0,     0,
       0,     0,     0,     0,    36,     0,     0,    27,    32,   119,
       4,     0,     5,    16,    47,     0,     0,    17,    18,     0,
       0,    50,    51,     0,    22,    48,    49,    44,    43,    42,
      40,    39,    41,     0,     0,     0,    11,    46,    45,     0,
      14,    13,   103,    98,   100,     0,   119,     0,     0,     0,
       0,     0,   127,     0,    49,    44,    45,     0,    99,   104,
       0,     0,     0,     4,    30,    53,    76,    77,     0,    60,
     121,     0,   120,     0,    58,     0,     0,    55,     0,    20,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    74,    75,     0,    19,    10,    15,     7,     8,
       6,     9,    12,     0,     0,    69,    24,    71,     0,     0,
       0,     0,     0,     0,     0,   103,     0,     0,     0,     0,
      28,     0,    65,    61,    62,    54,     0,     0,    23,    59,
       0,    52,    83,    81,    82,    80,    97,    96,    78,    79,
      84,    86,    85,    87,    94,    95,    93,    89,    88,    68,
      70,    90,    91,    92,   107,   102,   101,   119,   119,   125,
       0,     0,     0,   109,   106,   105,     0,     0,     0,     0,
     115,     0,     0,     0,     0,     0,     0,    67,    63,   122,
      56,     0,   119,     0,     0,   123,   129,   134,     0,   111,
       0,     0,     0,     0,     0,   117,   116,     0,     0,    66,
       0,     0,    73,    25,   126,   130,   108,     0,   113,   112,
     110,     0,    29,     0,    57,    72,   119,   135,     0,   118,
      64,     0,     0,   132,   114,   124,     0,     0,   136,     0,
     133,     0,   131
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -133,  -133,  -133,   194,  -133,   -20,  -133,  -133,  -133,  -133,
    -133,    -4,    -2,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
      51,  -133,  -133,  -133,    -1,     0,  -133,  -133,  -133,  -133,
    -133,  -133,   -68,  -128,  -133,    76,  -133,  -133,  -132,  -133,
    -133,   -57,  -133,  -133,    19,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,    95,    32,    33,    34,    35,    36,    37,
      38,    90,    73,    41,    96,    97,    42,    43,   152,   153,
     154,   207,    44,    45,    74,    75,    48,    49,    50,    51,
      52,    53,    63,    64,    78,    79,    54,    55,   148,    56,
      57,    91,    92,   234,    76,   215,    59,    60,   247,   258,
      61,   235,   253
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char Parser::yytable_ninf_ = -54;
  const short int
  Parser::yytable_[] =
  {
        39,    84,    40,    46,    47,    88,   186,   145,   145,   138,
     192,    72,   198,   147,     6,     7,     8,     9,    10,   201,
      86,    87,    89,    58,   135,    93,   220,    98,   101,   102,
     103,   104,   105,    62,   106,   122,   123,   -54,   -54,   179,
     133,   -53,   -53,    80,   202,     3,   124,    65,   199,    16,
      17,   221,   -53,    70,   122,   123,    22,    23,    24,   119,
     120,   121,   150,   139,   140,    28,   149,    83,   136,   224,
      67,   193,    68,   186,   137,    66,   197,   116,   117,   118,
     119,   120,   121,   146,   196,    29,    71,    69,   237,   180,
      31,    39,   186,    40,    46,    47,    94,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,    58,   181,   182,   183,    81,    77,
     184,    82,    85,    83,   133,   141,   200,    99,   100,   185,
     213,   214,   116,   117,   118,   119,   120,   121,   194,   125,
     126,   127,   134,   128,   129,   204,   130,   142,   131,   132,
     143,   151,   209,   210,    81,   231,   144,   155,   156,   159,
     157,   160,   189,   101,   102,   103,   104,   105,   187,   106,
     216,   217,   107,   108,   203,   188,   219,   205,   206,   211,
     218,   145,   225,   226,   212,   223,   229,   222,   228,   251,
     230,   232,   233,   236,   240,   241,     4,   252,   257,   243,
     245,   238,   239,   246,   208,   248,   255,   242,     0,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   256,   195,
       0,   249,     0,   250,     0,     0,   244,     5,   254,     6,
       7,     8,     9,    10,     0,    11,    12,   260,     0,     0,
       0,   262,     0,     0,     0,     0,     0,    13,     0,     0,
      14,     0,   259,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,     0,    19,    20,
      21,    22,    23,    24,     0,     0,     0,    25,    26,    27,
      28,     0,     0,     5,     0,     6,     7,     8,     9,    10,
       0,    11,    12,     0,     0,     0,     0,     0,     0,     0,
      29,    30,     0,    13,   158,    31,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
      16,    17,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,     0,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,   101,   102,   103,   104,   105,
       0,   106,     0,     0,   107,   108,    29,    30,     0,     0,
       0,    31,   109,   110,   111,   112,     0,     0,   101,   102,
     103,   104,   105,     0,   106,     0,     0,   107,   108,     0,
       0,     0,     0,     0,     0,   109,   110,   111,   112,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,   121,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   227,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   101,   102,   103,   104,   105,     0,   106,
       0,     0,   107,   108,     0,   161,     0,     0,     0,     0,
     109,   110,   111,   112,     0,   101,   102,   103,   104,   105,
       0,   106,     0,     0,   107,   108,     0,     0,     0,     0,
       0,     0,   109,   110,   111,   112,     0,     0,     0,   113,
     114,   115,   116,   117,   118,   119,   120,   121,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     190,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     101,   102,   103,   104,   105,     0,   106,     0,     0,   107,
     108,     0,   191,     0,     0,     0,     0,   109,   110,   111,
     112,     0,   101,   102,   103,   104,   105,     0,   106,     0,
       0,   107,   108,     0,     0,     0,     0,     0,     0,   109,
     110,   111,   112,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,   121,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   261,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   101,   102,   103,
     104,   105,     0,   106,     0,     0,   107,   108,     0,   101,
     102,   103,   104,   105,   109,   106,   111,   112,   107,   108,
       0,   101,   102,   103,   104,   105,   109,   106,   111,     0,
     107,   108,   101,   102,   103,   104,   105,     0,   106,     0,
     111,   107,   108,   113,   114,   115,   116,   117,   118,   119,
     120,   121,     0,     0,     0,   113,   114,   115,   116,   117,
     118,   119,   120,   121,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,   121,     0,     0,     0,   114,
     115,   116,   117,   118,   119,   120,   121,   101,   102,   103,
     104,   105,     0,   106,     0,     0,   107,   108,   101,   102,
     103,   104,   105,     0,   106,     0,     0,   107,   108,   -54,
     -54,   -54,   -54,   105,     0,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     120,   121,     0,     0,     0,     0,     0,   116,   117,   118,
     119,   120,   121,     0,     0,     0,     0,     0,   116,   117,
     118,   119,   120,   121
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,    21,     4,     4,     4,    25,   134,     6,     6,    66,
       6,    15,   144,    81,     5,     6,     7,     8,     9,    57,
      22,    23,    26,     4,     6,     9,    57,    31,    15,    16,
      17,    18,    19,     6,    21,    47,    48,    24,    25,     6,
      58,    47,    48,     6,    82,     0,    58,    66,    66,    40,
      41,    82,    58,    44,    47,    48,    47,    48,    49,    67,
      68,    69,    82,    67,    68,    56,    76,    77,    50,   201,
      81,    67,    81,   201,    56,    81,   144,    64,    65,    66,
      67,    68,    69,    82,    82,    76,    77,     6,   220,    56,
      81,    95,   220,    95,    95,    95,    80,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    95,   119,   120,   121,    81,    56,
     124,     6,     6,    77,    58,    66,   146,    79,    79,   133,
     187,   188,    64,    65,    66,    67,    68,    69,   142,    79,
      79,    79,    57,    79,    79,   149,    79,    58,    79,    79,
      57,    52,   156,   157,    81,   212,    81,    83,    57,    80,
      60,    57,    82,    15,    16,    17,    18,    19,    81,    21,
     190,   191,    24,    25,    82,    81,   196,    81,    51,     9,
      66,     6,   202,   203,    81,    66,   206,    82,     6,   246,
      60,    82,    82,    67,    66,    82,     2,    14,    13,    82,
      82,   221,   222,    81,   153,    82,    82,   227,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    81,   143,
      -1,   241,    -1,   243,    -1,    -1,   230,     3,   248,     5,
       6,     7,     8,     9,    -1,    11,    12,   257,    -1,    -1,
      -1,   261,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      26,    -1,   256,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,    45,
      46,    47,    48,    49,    -1,    -1,    -1,    53,    54,    55,
      56,    -1,    -1,     3,    -1,     5,     6,     7,     8,     9,
      -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    -1,    23,    80,    81,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    41,    42,    -1,    44,    45,    46,    47,    48,    49,
      -1,    -1,    -1,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,    19,
      -1,    21,    -1,    -1,    24,    25,    76,    77,    -1,    -1,
      -1,    81,    32,    33,    34,    35,    -1,    -1,    15,    16,
      17,    18,    19,    -1,    21,    -1,    -1,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    15,    16,    17,    18,    19,    -1,    21,
      -1,    -1,    24,    25,    -1,    82,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    -1,    15,    16,    17,    18,    19,
      -1,    21,    -1,    -1,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      15,    16,    17,    18,    19,    -1,    21,    -1,    -1,    24,
      25,    -1,    82,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    -1,    15,    16,    17,    18,    19,    -1,    21,    -1,
      -1,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    -1,    -1,    -1,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    15,    16,    17,
      18,    19,    -1,    21,    -1,    -1,    24,    25,    -1,    15,
      16,    17,    18,    19,    32,    21,    34,    35,    24,    25,
      -1,    15,    16,    17,    18,    19,    32,    21,    34,    -1,
      24,    25,    15,    16,    17,    18,    19,    -1,    21,    -1,
      34,    24,    25,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    15,    16,    17,
      18,    19,    -1,    21,    -1,    -1,    24,    25,    15,    16,
      17,    18,    19,    -1,    21,    -1,    -1,    24,    25,    15,
      16,    17,    18,    19,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    85,    86,     0,    87,     3,     5,     6,     7,     8,
       9,    11,    12,    23,    26,    39,    40,    41,    42,    44,
      45,    46,    47,    48,    49,    53,    54,    55,    56,    76,
      77,    81,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,   100,   101,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   120,   121,   123,   124,   128,   130,
     131,   134,     6,   116,   117,    66,    81,    81,    81,     6,
      44,    77,    95,    96,   108,   109,   128,    56,   118,   119,
       6,    81,     6,    77,    89,     6,    96,    96,    89,    95,
      95,   125,   126,     9,    80,    87,    98,    99,    95,    79,
      79,    15,    16,    17,    18,    19,    21,    24,    25,    32,
      33,    34,    35,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    47,    48,    58,    79,    79,    79,    79,    79,
      79,    79,    79,    58,    57,     6,    50,    56,   125,    95,
      95,    66,    58,    57,    81,     6,    82,   116,   122,    76,
      89,    52,   102,   103,   104,    83,    57,    60,    80,    80,
      57,    82,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,     6,
      56,    95,    95,    95,    95,    95,   117,    81,    81,    82,
      82,    82,     6,    67,    95,   119,    82,   116,   122,    66,
      89,    57,    82,    82,    95,    81,    51,   105,   104,    95,
      95,     9,    81,   125,   125,   129,    89,    89,    66,    89,
      57,    82,    82,    66,   122,    89,    89,    83,     6,    89,
      60,   125,    82,    82,   127,   135,    67,   122,    89,    89,
      66,    82,    89,    82,    95,    82,    81,   132,    82,    89,
      89,   125,    14,   136,    89,    82,    81,    13,   133,    95,
      89,    82,    89
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
      88,    88,    88,    89,    90,    90,    91,    92,    93,    93,
      94,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    97,    98,    99,    99,   100,   100,
     101,   102,   103,   103,   104,   105,   105,   106,   107,   107,
     107,   107,   108,   108,   109,   109,   109,   109,   110,   110,
     110,   110,   110,   110,   111,   111,   112,   112,   113,   113,
     113,   113,   113,   114,   114,   114,   114,   114,   115,   115,
     116,   116,   117,   117,   118,   118,   119,   120,   121,   121,
     122,   123,   123,   123,   123,   124,   124,   124,   124,   125,
     125,   126,   126,   127,   127,   129,   128,   130,   130,   131,
     132,   132,   133,   133,   135,   136,   134
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     2,     1,     1,     1,     2,
       2,     2,     1,     3,     3,     6,     1,     1,     3,     6,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     3,     5,     2,     3,
       2,     1,     1,     2,     5,     0,     2,     4,     3,     3,
       3,     3,     6,     6,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     3,     3,     1,     1,     3,     3,     3,     6,     4,
       4,     5,     6,     6,     8,     4,     5,     5,     7,     0,
       1,     1,     3,     0,     4,     0,     6,     2,     1,     5,
       0,     6,     0,     2,     0,     0,     9
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
  "\"function\"", "\"spawn\"", "\"critical\"", "\"++\"", "\"--\"",
  "\"null\"", "\"new\"", "\"finally\"", "\"catch\"", "\"try\"",
  "\"throw\"", "\"continue\"", "\"constant identifier\"", "','", "'='",
  "XOR_EQUAL", "':'", "'|'", "'^'", "'&'", "'-'", "'+'", "'.'", "'*'",
  "'/'", "'%'", "'!'", "'~'", "DEEPCOPY", "COPY", "DECREMENT", "INCREMENT",
  "'['", "'{'", "UMINUS", "';'", "'}'", "'('", "')'", "']'", "$accept",
  "program", "$@1", "statement_list", "statement", "block",
  "instantiation", "break", "continue", "thread_block", "critical_block",
  "rvalue", "lvalue", "array", "key_value_list",
  "non_empty_key_value_list", "map", "throw", "catch", "not_empty_catch",
  "catch_impl", "finally", "try_catch_finally", "property_access", "mcall",
  "inc_dec", "comparison", "boolean", "logic", "arithmetic", "bitwise",
  "variable_decl", "variable_decl_list", "variable_decl_impl",
  "const_decl_list", "const_decl_impl", "assignment", "import", "vararg",
  "fdecl", "anonymous_fdecl", "call_args", "non_empty_call_args",
  "fcall_chain", "fcall", "@2", "return_stmt", "while", "elseif", "else",
  "if", "@3", "@4", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        85,     0,    -1,    -1,    86,    87,    -1,    -1,    87,    88,
      -1,   121,    79,    -1,   115,    79,    -1,   120,    79,    -1,
     128,    79,    -1,   108,    79,    -1,   123,    -1,   130,    79,
      -1,   134,    -1,   131,    -1,   109,    79,    -1,    89,    -1,
      93,    -1,    94,    -1,   101,    79,    -1,    91,    79,    -1,
      92,    79,    -1,   106,    -1,    77,    87,    80,    -1,     5,
      66,    50,    -1,     5,    66,    50,    81,   125,    82,    -1,
      23,    -1,    55,    -1,    45,     6,    89,    -1,    45,     6,
      76,    95,    83,    89,    -1,    46,    89,    -1,     6,    -1,
      56,    -1,     9,    -1,     7,    -1,     8,    -1,    49,    -1,
      40,    -1,    41,    -1,   113,    -1,   112,    -1,   114,    -1,
     111,    -1,   110,    -1,   109,    -1,   128,    -1,   124,    -1,
      90,    -1,   107,    -1,   108,    -1,    97,    -1,   100,    -1,
      81,    95,    82,    -1,     6,    -1,    76,   125,    83,    -1,
      99,    -1,     9,    60,    95,    -1,    99,    57,     9,    60,
      95,    -1,    77,    80,    -1,    77,    98,    80,    -1,    54,
      95,    -1,   103,    -1,   104,    -1,   103,   104,    -1,    52,
      81,     6,    82,    89,    -1,    -1,    51,    89,    -1,    53,
      89,   102,   105,    -1,    95,    66,     6,    -1,     5,    66,
       6,    -1,    95,    66,    56,    -1,     5,    66,    56,    -1,
      95,    66,     6,    81,   125,    82,    -1,     5,    66,     6,
      81,   125,    82,    -1,    96,    47,    -1,    96,    48,    -1,
      47,    96,    -1,    48,    96,    -1,    95,    24,    95,    -1,
      95,    25,    95,    -1,    95,    18,    95,    -1,    95,    16,
      95,    -1,    95,    17,    95,    -1,    95,    15,    95,    -1,
      95,    32,    95,    -1,    95,    34,    95,    -1,    95,    33,
      95,    -1,    95,    35,    95,    -1,    95,    65,    95,    -1,
      95,    64,    95,    -1,    95,    67,    95,    -1,    95,    68,
      95,    -1,    95,    69,    95,    -1,    95,    63,    95,    -1,
      95,    61,    95,    -1,    95,    62,    95,    -1,    95,    21,
      95,    -1,    95,    19,    95,    -1,     3,   116,    -1,    42,
     118,    -1,   117,    -1,   116,    57,   117,    -1,     6,    58,
      95,    -1,     6,    -1,   119,    -1,   118,    57,   119,    -1,
      56,    58,    95,    -1,    96,    58,    95,    -1,    26,     6,
      66,     6,    66,    67,    -1,    26,     6,    66,    67,    -1,
       6,    66,    66,    66,    -1,    44,     6,    81,    82,    89,
      -1,    44,     6,    81,   122,    82,    89,    -1,    44,     6,
      81,   116,    82,    89,    -1,    44,     6,    81,   116,    57,
     122,    82,    89,    -1,    44,    81,    82,    89,    -1,    44,
      81,   122,    82,    89,    -1,    44,    81,   116,    82,    89,
      -1,    44,    81,   116,    57,   122,    82,    89,    -1,    -1,
     126,    -1,    95,    -1,   126,    57,    95,    -1,    -1,   127,
      81,   125,    82,    -1,    -1,     6,    81,   125,    82,   129,
     127,    -1,    39,    95,    -1,    39,    -1,    11,    81,    95,
      82,    89,    -1,    -1,   132,    14,    81,    95,    82,    89,
      -1,    -1,    13,    89,    -1,    -1,    -1,    12,    81,    95,
      82,    89,   135,   132,   136,   133,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     8,    11,    14,    17,    20,
      23,    26,    28,    31,    33,    35,    38,    40,    42,    44,
      47,    50,    53,    55,    59,    63,    70,    72,    74,    78,
      85,    88,    90,    92,    94,    96,    98,   100,   102,   104,
     106,   108,   110,   112,   114,   116,   118,   120,   122,   124,
     126,   128,   130,   134,   136,   140,   142,   146,   152,   155,
     159,   162,   164,   166,   169,   175,   176,   179,   184,   188,
     192,   196,   200,   207,   214,   217,   220,   223,   226,   230,
     234,   238,   242,   246,   250,   254,   258,   262,   266,   270,
     274,   278,   282,   286,   290,   294,   298,   302,   306,   309,
     312,   314,   318,   322,   324,   326,   330,   334,   338,   345,
     350,   355,   361,   368,   375,   384,   389,   395,   401,   409,
     410,   412,   414,   418,   419,   424,   425,   432,   435,   437,
     443,   444,   451,   452,   455,   456,   457
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   207,   207,   207,   211,   212,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   236,   240,   241,   245,   249,   254,   255,
     259,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   288,   292,   296,   300,   301,   305,   306,
     310,   314,   318,   319,   323,   327,   328,   332,   336,   337,
     338,   339,   343,   344,   348,   349,   350,   351,   355,   356,
     357,   358,   359,   360,   364,   365,   369,   370,   374,   375,
     376,   377,   378,   382,   383,   384,   385,   386,   390,   391,
     395,   396,   400,   401,   405,   406,   410,   414,   418,   419,
     423,   427,   429,   431,   433,   438,   440,   442,   444,   449,
     450,   454,   455,   459,   460,   464,   464,   468,   469,   473,
     477,   479,   484,   485,   489,   490,   489
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
  const int Parser::yylast_ = 743;
  const int Parser::yynnts_ = 53;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 3;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 84;

  const unsigned int Parser::yyuser_token_number_max_ = 317;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} // clever





namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever

