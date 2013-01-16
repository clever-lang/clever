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

  case 24:

    { (yyval.block) = (yysemantic_stack_[(3) - (2)].block); }
    break;

  case 25:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(3) - (1)].type), NULL, yyloc); }
    break;

  case 26:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (5)].narray),   yyloc); }
    break;

  case 27:

    { (yyval.break_) = new ast::Break(yyloc); }
    break;

  case 28:

    { (yyval.continue_) = new ast::Continue(yyloc); }
    break;

  case 29:

    { (yyval.wait) = new ast::Wait((yysemantic_stack_[(2) - (2)].ident), yyloc); }
    break;

  case 30:

    { (yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(3) - (3)].block), (yysemantic_stack_[(3) - (2)].ident), yyloc); }
    break;

  case 31:

    { (yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].node), yyloc); }
    break;

  case 32:

    { (yyval.criticalblock) = new ast::CriticalBlock((yysemantic_stack_[(2) - (2)].block), yyloc); }
    break;

  case 54:

    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 56:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 58:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 59:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 60:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 61:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 62:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 64:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 65:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 66:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 67:

    { (yyval.block) = NULL; }
    break;

  case 68:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 69:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 70:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 71:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 72:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 73:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 74:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 75:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 76:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 77:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 78:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 79:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 80:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 81:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 82:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 83:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 84:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 85:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 86:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 87:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 88:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 89:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 90:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 91:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 92:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 93:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 94:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 95:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 96:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 97:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 98:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 99:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 100:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 101:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 102:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 103:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 104:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 105:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 106:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 107:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 108:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 109:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 110:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].ident), yyloc);   }
    break;

  case 111:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), NULL, yyloc); }
    break;

  case 112:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 113:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); }
    break;

  case 114:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); }
    break;

  case 115:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); }
    break;

  case 116:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); }
    break;

  case 117:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, yyloc); }
    break;

  case 118:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), yyloc); }
    break;

  case 119:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); }
    break;

  case 120:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), yyloc); }
    break;

  case 121:

    { (yyval.narray) = NULL; }
    break;

  case 123:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 124:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 125:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 126:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 127:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 128:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 129:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 130:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 131:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 133:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 134:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 135:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 136:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 137:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 138:

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
  const short int Parser::yypact_ninf_ = -132;
  const short int
  Parser::yypact_[] =
  {
      -132,    22,  -132,  -132,   297,    33,   -22,   -15,  -132,  -132,
    -132,   -30,   -29,  -132,    48,     7,  -132,  -132,     1,    14,
      53,    55,   -16,    62,    62,  -132,   -16,     7,  -132,  -132,
       7,     9,     7,  -132,  -132,  -132,   -11,   -10,    -9,  -132,
    -132,   527,   -18,  -132,  -132,    -5,  -132,  -132,    -3,     8,
    -132,  -132,  -132,  -132,  -132,    12,    19,    42,  -132,  -132,
      43,    47,  -132,  -132,    24,    70,  -132,    21,     7,     7,
       7,    15,    49,     9,   527,    -6,  -132,  -132,  -132,    32,
      72,  -132,    50,     3,   -28,  -132,  -132,  -132,  -132,  -132,
    -132,    28,   527,   527,    56,    83,    82,  -132,   240,    63,
      87,   371,  -132,  -132,  -132,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,    23,     7,     7,     7,  -132,  -132,     7,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,     7,    33,    64,
      65,  -132,    68,   427,   449,    11,     7,     1,     4,   -27,
     -16,   -37,    71,     7,  -132,    66,   100,    28,  -132,  -132,
       7,     7,  -132,  -132,   144,  -132,   410,   410,   410,   410,
      69,    69,   685,   685,   607,   583,   151,   595,   618,   674,
     696,   -32,   -32,    73,  -132,  -132,  -132,  -132,   527,   527,
    -132,     7,     7,  -132,   -16,   -16,    91,  -132,   527,  -132,
     -16,   -23,    76,    93,  -132,   155,   -16,   -16,   348,   156,
     -16,  -132,  -132,   527,   527,   102,     7,    81,    88,  -132,
    -132,  -132,    97,  -132,   155,   -16,   -16,   110,    95,  -132,
    -132,   -16,    98,  -132,     7,    99,  -132,  -132,   101,  -132,
    -132,   104,  -132,  -132,  -132,   -16,  -132,   -16,   527,  -132,
       7,   166,   -16,  -132,  -132,   105,   108,   178,  -132,  -132,
       7,   -16,  -132,   505,  -132,   -16,  -132
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    33,    36,    37,
      35,     0,     0,    27,     0,   130,    39,    40,     0,     0,
       0,     0,     0,     0,     0,    38,     0,     0,    28,    34,
     121,     4,     0,     5,    16,    49,     0,     0,     0,    17,
      18,     0,     0,    52,    53,     0,    23,    50,    51,    46,
      45,    44,    42,    41,    43,     0,     0,     0,    11,    48,
      47,     0,    14,    13,   105,   100,   102,     0,   121,     0,
       0,     0,     0,     0,   129,     0,    51,    46,    47,     0,
     101,   106,     0,     0,     0,    29,     4,    32,    55,    78,
      79,     0,    62,   123,     0,   122,     0,    60,     0,     0,
      57,     0,    21,    22,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,    77,     0,    20,
      10,    15,     7,     8,     6,     9,    12,     0,     0,    71,
      25,    73,     0,     0,     0,     0,     0,     0,     0,   105,
       0,     0,     0,     0,    30,     0,    67,    63,    64,    56,
       0,     0,    24,    61,     0,    54,    85,    83,    84,    82,
      99,    98,    80,    81,    86,    88,    87,    89,    96,    97,
      95,    91,    90,    70,    72,    92,    93,    94,   109,   104,
     103,   121,   121,   127,     0,     0,     0,   111,   108,   107,
       0,     0,     0,     0,   117,     0,     0,     0,     0,     0,
       0,    69,    65,   124,    58,     0,   121,     0,     0,   125,
     131,   136,     0,   113,     0,     0,     0,     0,     0,   119,
     118,     0,     0,    68,     0,     0,    75,    26,   128,   132,
     110,     0,   115,   114,   112,     0,    31,     0,    59,    74,
     121,   137,     0,   120,    66,     0,     0,   134,   116,   126,
       0,     0,   138,     0,   135,     0,   133
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -132,  -132,  -132,   190,  -132,   -21,  -132,  -132,  -132,  -132,
    -132,  -132,    -4,     2,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,    36,  -132,  -132,  -132,    -1,     0,  -132,  -132,  -132,
    -132,  -132,  -132,   -75,  -131,  -132,    51,  -132,  -132,  -129,
    -132,  -132,   -66,  -132,  -132,    20,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,    98,    33,    34,    35,    36,    37,    38,
      39,    40,    93,    75,    43,    99,   100,    44,    45,   156,
     157,   158,   211,    46,    47,    76,    77,    50,    51,    52,
      53,    54,    55,    65,    66,    80,    81,    56,    57,   152,
      58,    59,    94,    95,   238,    78,   219,    61,    62,   251,
     262,    63,   239,   257
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char Parser::yytable_ninf_ = -56;
  const short int
  Parser::yytable_[] =
  {
        41,    87,   142,    48,    49,    91,    42,   190,   151,   149,
     149,    74,     6,     7,     8,     9,    10,   196,    96,   202,
      82,   205,     3,    92,    60,    89,    90,   139,   101,   183,
     126,   127,   137,   -55,   -55,   224,   123,   124,   125,    64,
     203,   128,   126,   127,   -55,    67,   206,    16,    17,   153,
      86,    72,    69,    70,    71,    23,    24,    25,    79,    84,
     225,    85,    86,   154,    29,   143,   144,    68,    88,   102,
     103,   104,   140,   201,   190,   129,   228,   130,   141,   197,
     184,   155,   145,   137,    30,    73,   150,   200,   131,    32,
      97,   146,   132,   190,    41,   241,    83,    48,    49,   133,
      42,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,    60,   185,
     186,   187,   134,   135,   188,   217,   218,   136,   138,   204,
     147,    83,   148,   189,   120,   121,   122,   123,   124,   125,
     159,   160,   198,   161,   163,   164,   191,   192,   209,   208,
     235,   193,   210,   215,   207,   216,   213,   214,   222,   226,
     227,   149,   232,   234,   236,   240,   105,   106,   107,   108,
     109,   237,   110,   220,   221,   111,   112,   244,   245,   223,
     256,   247,   249,   250,   255,   229,   230,   252,   259,   233,
     260,   261,     4,   212,     0,     0,     0,     0,   199,     0,
       0,     0,     0,     0,   242,   243,     0,     0,     0,     0,
     246,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,   253,     0,   254,     0,     0,     0,
     248,   258,     0,     0,     0,     0,     0,     0,     0,     0,
     264,     0,     0,     5,   266,     6,     7,     8,     9,    10,
       0,    11,    12,     0,     0,     0,   263,     0,     0,     0,
       0,     0,     0,    13,     0,     0,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
      16,    17,    18,     0,    19,    20,    21,    22,    23,    24,
      25,     0,     0,     0,    26,    27,    28,    29,     0,     0,
       5,     0,     6,     7,     8,     9,    10,     0,    11,    12,
       0,     0,     0,     0,     0,     0,     0,    30,    31,     0,
      13,   162,    32,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,    16,    17,    18,
       0,    19,    20,    21,    22,    23,    24,    25,     0,     0,
       0,    26,    27,    28,    29,     0,     0,     0,     0,     0,
       0,     0,     0,   105,   106,   107,   108,   109,     0,   110,
       0,     0,   111,   112,    30,    31,     0,     0,     0,    32,
     113,   114,   115,   116,     0,     0,   105,   106,   107,   108,
     109,     0,   110,     0,     0,   111,   112,     0,     0,     0,
       0,     0,     0,   113,   114,   115,   116,     0,     0,     0,
     117,   118,   119,   120,   121,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,   -56,   -56,   -56,   -56,   109,
       0,   110,   231,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   105,   106,   107,   108,   109,     0,   110,     0,
       0,   111,   112,     0,   165,     0,     0,     0,     0,   113,
     114,   115,   116,     0,   105,   106,   107,   108,   109,     0,
     110,     0,     0,   111,   112,   120,   121,   122,   123,   124,
     125,   113,   114,   115,   116,     0,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     194,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     105,   106,   107,   108,   109,     0,   110,     0,     0,   111,
     112,     0,   195,     0,     0,     0,     0,   113,   114,   115,
     116,     0,   105,   106,   107,   108,   109,     0,   110,     0,
       0,   111,   112,     0,     0,     0,     0,     0,     0,   113,
     114,   115,   116,     0,     0,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   265,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   105,   106,
     107,   108,   109,     0,   110,     0,     0,   111,   112,     0,
     105,   106,   107,   108,   109,   113,   110,   115,   116,   111,
     112,     0,   105,   106,   107,   108,   109,   113,   110,   115,
       0,   111,   112,   105,   106,   107,   108,   109,     0,   110,
       0,   115,   111,   112,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,   118,   119,   120,   121,   122,   123,   124,   125,   105,
     106,   107,   108,   109,     0,   110,     0,     0,   111,   112,
     105,   106,   107,   108,   109,     0,   110,     0,     0,   -56,
     -56,   105,   106,   107,   108,   109,     0,   110,     0,     0,
     111,   112,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   120,
     121,   122,   123,   124,   125,     0,     0,     0,     0,     0,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,   120,   121,   122,   123,   124,   125
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,    22,    68,     4,     4,    26,     4,   138,    83,     6,
       6,    15,     5,     6,     7,     8,     9,     6,     9,   148,
       6,    58,     0,    27,     4,    23,    24,     6,    32,     6,
      48,    49,    59,    48,    49,    58,    68,    69,    70,     6,
      67,    59,    48,    49,    59,    67,    83,    40,    41,    77,
      78,    44,    82,    82,     6,    48,    49,    50,    57,     6,
      83,     6,    78,    84,    57,    69,    70,    82,     6,    80,
      80,    80,    51,   148,   205,    80,   205,    80,    57,    68,
      57,    53,    67,    59,    77,    78,    83,    83,    80,    82,
      81,    59,    80,   224,    98,   224,    82,    98,    98,    80,
      98,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,    98,   123,
     124,   125,    80,    80,   128,   191,   192,    80,    58,   150,
      58,    82,    82,   137,    65,    66,    67,    68,    69,    70,
      84,    58,   146,    61,    81,    58,    82,    82,    82,   153,
     216,    83,    52,     9,    83,    82,   160,   161,    67,    83,
      67,     6,     6,    61,    83,    68,    15,    16,    17,    18,
      19,    83,    21,   194,   195,    24,    25,    67,    83,   200,
      14,    83,    83,    82,   250,   206,   207,    83,    83,   210,
      82,    13,     2,   157,    -1,    -1,    -1,    -1,   147,    -1,
      -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,
     231,    -1,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    -1,    -1,   245,    -1,   247,    -1,    -1,    -1,
     234,   252,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     261,    -1,    -1,     3,   265,     5,     6,     7,     8,     9,
      -1,    11,    12,    -1,    -1,    -1,   260,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    41,    42,    -1,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    55,    56,    57,    -1,    -1,
       3,    -1,     5,     6,     7,     8,     9,    -1,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    -1,
      23,    81,    82,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      -1,    44,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    17,    18,    19,    -1,    21,
      -1,    -1,    24,    25,    77,    78,    -1,    -1,    -1,    82,
      32,    33,    34,    35,    -1,    -1,    15,    16,    17,    18,
      19,    -1,    21,    -1,    -1,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    33,    34,    35,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,    19,
      -1,    21,    84,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    15,    16,    17,    18,    19,    -1,    21,    -1,
      -1,    24,    25,    -1,    83,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    -1,    15,    16,    17,    18,    19,    -1,
      21,    -1,    -1,    24,    25,    65,    66,    67,    68,    69,
      70,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      15,    16,    17,    18,    19,    -1,    21,    -1,    -1,    24,
      25,    -1,    83,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    -1,    15,    16,    17,    18,    19,    -1,    21,    -1,
      -1,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    15,    16,
      17,    18,    19,    -1,    21,    -1,    -1,    24,    25,    -1,
      15,    16,    17,    18,    19,    32,    21,    34,    35,    24,
      25,    -1,    15,    16,    17,    18,    19,    32,    21,    34,
      -1,    24,    25,    15,    16,    17,    18,    19,    -1,    21,
      -1,    34,    24,    25,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    15,
      16,    17,    18,    19,    -1,    21,    -1,    -1,    24,    25,
      15,    16,    17,    18,    19,    -1,    21,    -1,    -1,    24,
      25,    15,    16,    17,    18,    19,    -1,    21,    -1,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    70
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    86,    87,     0,    88,     3,     5,     6,     7,     8,
       9,    11,    12,    23,    26,    39,    40,    41,    42,    44,
      45,    46,    47,    48,    49,    50,    54,    55,    56,    57,
      77,    78,    82,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   102,   103,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   122,   123,   125,   126,
     130,   132,   133,   136,     6,   118,   119,    67,    82,    82,
      82,     6,    44,    78,    97,    98,   110,   111,   130,    57,
     120,   121,     6,    82,     6,     6,    78,    90,     6,    98,
      98,    90,    97,    97,   127,   128,     9,    81,    88,   100,
     101,    97,    80,    80,    80,    15,    16,    17,    18,    19,
      21,    24,    25,    32,    33,    34,    35,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    48,    49,    59,    80,
      80,    80,    80,    80,    80,    80,    80,    59,    58,     6,
      51,    57,   127,    97,    97,    67,    59,    58,    82,     6,
      83,   118,   124,    77,    90,    53,   104,   105,   106,    84,
      58,    61,    81,    81,    58,    83,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,     6,    57,    97,    97,    97,    97,    97,
     119,    82,    82,    83,    83,    83,     6,    68,    97,   121,
      83,   118,   124,    67,    90,    58,    83,    83,    97,    82,
      52,   107,   106,    97,    97,     9,    82,   127,   127,   131,
      90,    90,    67,    90,    58,    83,    83,    67,   124,    90,
      90,    84,     6,    90,    61,   127,    83,    83,   129,   137,
      68,   124,    90,    90,    67,    83,    90,    83,    97,    83,
      82,   134,    83,    90,    90,   127,    14,   138,    90,    83,
      82,    13,   135,    97,    90,    83,    90
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
     305,   306,   307,   308,   309,   310,   311,   312,    44,    61,
     313,    58,   124,    94,    38,    45,    43,    46,    42,    47,
      37,    33,   126,   314,   315,   316,   317,    91,   123,   318,
      59,   125,    40,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    85,    87,    86,    88,    88,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    90,    91,    91,    92,    93,    94,
      95,    95,    96,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    98,    99,   100,   101,   101,
     102,   102,   103,   104,   105,   105,   106,   107,   107,   108,
     109,   109,   109,   109,   110,   110,   111,   111,   111,   111,
     112,   112,   112,   112,   112,   112,   113,   113,   114,   114,
     115,   115,   115,   115,   115,   116,   116,   116,   116,   116,
     117,   117,   118,   118,   119,   119,   120,   120,   121,   122,
     123,   123,   124,   125,   125,   125,   125,   126,   126,   126,
     126,   127,   127,   128,   128,   129,   129,   131,   130,   132,
     132,   133,   134,   134,   135,   135,   137,   138,   136
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
       1,     1,     1,     1,     3,     1,     3,     1,     3,     5,
       2,     3,     2,     1,     1,     2,     5,     0,     2,     4,
       3,     3,     3,     3,     6,     6,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     3,     3,     1,     1,     3,     3,     3,
       6,     4,     4,     5,     6,     6,     8,     4,     5,     5,
       7,     0,     1,     1,     3,     0,     4,     0,     6,     2,
       1,     5,     0,     6,     0,     2,     0,     0,     9
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
  "\"throw\"", "\"continue\"", "\"constant identifier\"", "','", "'='",
  "XOR_EQUAL", "':'", "'|'", "'^'", "'&'", "'-'", "'+'", "'.'", "'*'",
  "'/'", "'%'", "'!'", "'~'", "DEEPCOPY", "COPY", "DECREMENT", "INCREMENT",
  "'['", "'{'", "UMINUS", "';'", "'}'", "'('", "')'", "']'", "$accept",
  "program", "$@1", "statement_list", "statement", "block",
  "instantiation", "break", "continue", "wait", "thread_block",
  "critical_block", "rvalue", "lvalue", "array", "key_value_list",
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
        86,     0,    -1,    -1,    87,    88,    -1,    -1,    88,    89,
      -1,   123,    80,    -1,   117,    80,    -1,   122,    80,    -1,
     130,    80,    -1,   110,    80,    -1,   125,    -1,   132,    80,
      -1,   136,    -1,   133,    -1,   111,    80,    -1,    90,    -1,
      95,    -1,    96,    -1,    94,    80,    -1,   103,    80,    -1,
      92,    80,    -1,    93,    80,    -1,   108,    -1,    78,    88,
      81,    -1,     5,    67,    51,    -1,     5,    67,    51,    82,
     127,    83,    -1,    23,    -1,    56,    -1,    46,     6,    -1,
      45,     6,    90,    -1,    45,     6,    77,    97,    84,    90,
      -1,    47,    90,    -1,     6,    -1,    57,    -1,     9,    -1,
       7,    -1,     8,    -1,    50,    -1,    40,    -1,    41,    -1,
     115,    -1,   114,    -1,   116,    -1,   113,    -1,   112,    -1,
     111,    -1,   130,    -1,   126,    -1,    91,    -1,   109,    -1,
     110,    -1,    99,    -1,   102,    -1,    82,    97,    83,    -1,
       6,    -1,    77,   127,    84,    -1,   101,    -1,     9,    61,
      97,    -1,   101,    58,     9,    61,    97,    -1,    78,    81,
      -1,    78,   100,    81,    -1,    55,    97,    -1,   105,    -1,
     106,    -1,   105,   106,    -1,    53,    82,     6,    83,    90,
      -1,    -1,    52,    90,    -1,    54,    90,   104,   107,    -1,
      97,    67,     6,    -1,     5,    67,     6,    -1,    97,    67,
      57,    -1,     5,    67,    57,    -1,    97,    67,     6,    82,
     127,    83,    -1,     5,    67,     6,    82,   127,    83,    -1,
      98,    48,    -1,    98,    49,    -1,    48,    98,    -1,    49,
      98,    -1,    97,    24,    97,    -1,    97,    25,    97,    -1,
      97,    18,    97,    -1,    97,    16,    97,    -1,    97,    17,
      97,    -1,    97,    15,    97,    -1,    97,    32,    97,    -1,
      97,    34,    97,    -1,    97,    33,    97,    -1,    97,    35,
      97,    -1,    97,    66,    97,    -1,    97,    65,    97,    -1,
      97,    68,    97,    -1,    97,    69,    97,    -1,    97,    70,
      97,    -1,    97,    64,    97,    -1,    97,    62,    97,    -1,
      97,    63,    97,    -1,    97,    21,    97,    -1,    97,    19,
      97,    -1,     3,   118,    -1,    42,   120,    -1,   119,    -1,
     118,    58,   119,    -1,     6,    59,    97,    -1,     6,    -1,
     121,    -1,   120,    58,   121,    -1,    57,    59,    97,    -1,
      98,    59,    97,    -1,    26,     6,    67,     6,    67,    68,
      -1,    26,     6,    67,    68,    -1,     6,    67,    67,    67,
      -1,    44,     6,    82,    83,    90,    -1,    44,     6,    82,
     124,    83,    90,    -1,    44,     6,    82,   118,    83,    90,
      -1,    44,     6,    82,   118,    58,   124,    83,    90,    -1,
      44,    82,    83,    90,    -1,    44,    82,   124,    83,    90,
      -1,    44,    82,   118,    83,    90,    -1,    44,    82,   118,
      58,   124,    83,    90,    -1,    -1,   128,    -1,    97,    -1,
     128,    58,    97,    -1,    -1,   129,    82,   127,    83,    -1,
      -1,     6,    82,   127,    83,   131,   129,    -1,    39,    97,
      -1,    39,    -1,    11,    82,    97,    83,    90,    -1,    -1,
     134,    14,    82,    97,    83,    90,    -1,    -1,    13,    90,
      -1,    -1,    -1,    12,    82,    97,    83,    90,   137,   134,
     138,   135,    -1
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
     128,   130,   132,   134,   136,   140,   142,   146,   148,   152,
     158,   161,   165,   168,   170,   172,   175,   181,   182,   185,
     190,   194,   198,   202,   206,   213,   220,   223,   226,   229,
     232,   236,   240,   244,   248,   252,   256,   260,   264,   268,
     272,   276,   280,   284,   288,   292,   296,   300,   304,   308,
     312,   315,   318,   320,   324,   328,   330,   332,   336,   340,
     344,   351,   356,   361,   367,   374,   381,   390,   395,   401,
     407,   415,   416,   418,   420,   424,   425,   430,   431,   438,
     441,   443,   449,   450,   457,   458,   461,   462,   463
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   209,   209,   209,   213,   214,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   239,   243,   244,   248,   252,   256,
     260,   261,   265,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   294,   298,   302,   306,   307,
     311,   312,   316,   320,   324,   325,   329,   333,   334,   338,
     342,   343,   344,   345,   349,   350,   354,   355,   356,   357,
     361,   362,   363,   364,   365,   366,   370,   371,   375,   376,
     380,   381,   382,   383,   384,   388,   389,   390,   391,   392,
     396,   397,   401,   402,   406,   407,   411,   412,   416,   420,
     424,   425,   429,   433,   435,   437,   439,   444,   446,   448,
     450,   455,   456,   460,   461,   465,   466,   470,   470,   474,
     475,   479,   483,   485,   490,   491,   495,   496,   495
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
       2,     2,     2,    71,     2,     2,     2,    70,    64,     2,
      82,    83,    68,    66,    58,    65,    67,    69,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    80,
       2,    59,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    77,     2,    84,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    78,    62,    81,    72,     2,     2,     2,
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
      55,    56,    57,    60,    73,    74,    75,    76,    79
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 766;
  const int Parser::yynnts_ = 54;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 3;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 85;

  const unsigned int Parser::yyuser_token_number_max_ = 318;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} // clever





namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever

