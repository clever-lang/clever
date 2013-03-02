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

    { c.init(driver.getFile()); }
    break;

  case 3:

    { c.setAST((yysemantic_stack_[(2) - (2)].block)); }
    break;

  case 4:

    { (yyval.block) = new ast::Block(yyloc); }
    break;

  case 5:

    { (yysemantic_stack_[(2) - (1)].block)->append((yysemantic_stack_[(2) - (2)].node));       }
    break;

  case 27:

    { (yyval.block) = (yysemantic_stack_[(3) - (2)].block); }
    break;

  case 28:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(3) - (1)].type), NULL, yyloc); }
    break;

  case 29:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (5)].narray),   yyloc); }
    break;

  case 30:

    { (yyval.break_) = new ast::Break(yyloc); }
    break;

  case 31:

    { (yyval.continue_) = new ast::Continue(yyloc); }
    break;

  case 32:

    {
#ifndef CLEVER_THREADS
		error(yyloc, "Cannot use process block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(3) - (3)].block), (yysemantic_stack_[(3) - (2)].ident), yyloc);
#endif
	}
    break;

  case 33:

    {
#ifndef CLEVER_THREADS
		error(yyloc, "Cannot use process block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].node), yyloc);
#endif
	}
    break;

  case 34:

    {
#ifndef CLEVER_THREADS
		error(yyloc, "Cannot use critical block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.criticalblock) = new ast::CriticalBlock((yysemantic_stack_[(2) - (2)].block), yyloc);
#endif
	}
    break;

  case 45:

    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 56:

    { (yysemantic_stack_[(1) - (1)].assignment)->setUseResult(); }
    break;

  case 63:

    { (yysemantic_stack_[(1) - (1)].property)->setWriteMode(); }
    break;

  case 65:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 66:

    { (yyval.node) = new ast::Switch((yysemantic_stack_[(5) - (3)].node), yyloc); }
    break;

  case 67:

    { (yyval.switch_) = (yysemantic_stack_[(8) - (7)].switch_); }
    break;

  case 73:

    { (yysemantic_stack_[(4) - (0)].switch_)->addCase((yysemantic_stack_[(4) - (2)].node), (yysemantic_stack_[(4) - (4)].block)); (yyval.switch_) = (yysemantic_stack_[(4) - (0)].switch_); }
    break;

  case 74:

    { (yysemantic_stack_[(5) - (0)].switch_)->addCase((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block)); (yyval.switch_) = (yysemantic_stack_[(5) - (0)].switch_); }
    break;

  case 75:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 76:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 77:

    { (yyval.node) = new ast::Boolean(ast::Boolean::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 78:

    { (yyval.node) = new ast::Bitwise(ast::Bitwise::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 79:

    { (yyval.class_) = new ast::ClassDef((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 80:

    { (yyval.narray) = NULL; }
    break;

  case 82:

    { (yyval.narray) = new ast::NodeArray(yyloc); }
    break;

  case 83:

    { (yyval.narray) = (yysemantic_stack_[(3) - (1)].narray); }
    break;

  case 84:

    { (yyval.narray) = (yysemantic_stack_[(1) - (1)].narray); }
    break;

  case 86:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 88:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 98:

    { (yysemantic_stack_[(1) - (0)].narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 99:

    { (yysemantic_stack_[(3) - (0)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 100:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), false, yyloc); }
    break;

  case 101:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(1) - (1)].ident), NULL, false, yyloc);     }
    break;

  case 102:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 103:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 104:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), true, yyloc);   }
    break;

  case 105:

    { (yyval.narray) = NULL; }
    break;

  case 107:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 108:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 109:

    { (yyval.flags) = ast::PRIVATE; }
    break;

  case 110:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(2) - (2)].fdecl)); (yysemantic_stack_[(2) - (2)].fdecl)->setVisibility((yysemantic_stack_[(2) - (1)].flags)); }
    break;

  case 111:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].fdecl)); (yysemantic_stack_[(3) - (3)].fdecl)->setVisibility((yysemantic_stack_[(3) - (2)].flags)); }
    break;

  case 112:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 113:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 114:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 115:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 116:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 117:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 119:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 120:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 121:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 122:

    { (yyval.block) = NULL; }
    break;

  case 123:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 124:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 125:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 126:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 127:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 128:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 129:

    { (yyval.mcall) = (yysemantic_stack_[(0) - (0)].mcall); }
    break;

  case 130:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (0)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 131:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 132:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); (yyval.property)->setStatic(); }
    break;

  case 133:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 134:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 135:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 136:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 137:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 138:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 139:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 140:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 141:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 142:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 143:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 144:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 145:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 146:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 147:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 148:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 149:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 150:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 151:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 152:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 153:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 154:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 155:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 156:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 157:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 158:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 159:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 160:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 161:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 162:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 163:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 164:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 165:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 166:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 167:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 168:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 169:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 170:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 171:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 172:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 173:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 174:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 175:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 176:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 177:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 178:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 179:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 180:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 181:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 182:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 183:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 184:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 185:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 186:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 187:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 188:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 189:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 190:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 191:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 192:

    { (yyval.narray) = NULL; }
    break;

  case 194:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 195:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 196:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 197:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 198:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 200:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 201:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 202:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 203:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 204:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 205:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 206:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 207:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 208:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 209:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 210:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 211:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 212:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 213:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 214:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 216:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 217:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 218:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 219:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 220:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 221:

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
  const short int Parser::yypact_ninf_ = -303;
  const short int
  Parser::yypact_[] =
  {
      -303,    57,  -303,  -303,   419,    54,    50,   234,  -303,  -303,
    -303,    -7,    71,  -303,   102,   286,  -303,  -303,   125,    20,
     189,   119,    24,    24,  -303,   119,   286,  -303,  -303,   217,
     139,   286,     4,   286,  -303,  -303,   146,   150,   185,  -303,
    -303,    56,   -24,   -15,  -303,  -303,  -303,  -303,   192,  -303,
     135,   193,   194,   203,   210,   223,  -303,   241,   226,   227,
     242,  -303,  -303,   218,   253,  -303,    33,   286,   286,   286,
    -303,    79,   239,   286,   286,   286,   286,     4,  -303,    56,
     790,  -303,  -303,  -303,  -303,  -303,  -303,  -303,  -303,  -303,
    -303,  -303,  -303,   259,   267,  -303,   249,   250,   330,   -10,
    -303,  -303,   268,   200,   269,   261,   269,   289,   790,   265,
     286,   790,   273,   296,   295,   288,   201,    58,   571,  -303,
    -303,  -303,  -303,  -303,    28,   286,   286,  -303,  -303,  -303,
    -303,  -303,  -303,    31,  -303,  -303,  -303,   286,    54,   283,
     287,  -303,   290,   630,   651,    16,    10,     3,  -303,  -303,
    -303,  -303,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   125,     8,     9,   292,   286,  -303,    63,
      67,   293,   320,   289,  -303,   144,   710,  -303,   286,   286,
    -303,  -303,   362,  -303,  -303,   294,  -303,   870,   469,   306,
     113,  -303,   790,  -303,   286,   286,  -303,   119,   119,  -303,
    -303,  -303,  -303,  -303,   159,   119,    69,   297,   216,   216,
     216,   216,   240,   240,    38,    38,   882,   811,   116,   870,
     893,    25,   328,   179,   179,  -303,  -303,  -303,   790,  -303,
     119,   117,   298,   119,   137,   299,   300,   490,  -303,  -303,
     371,   119,  -303,  -303,   243,   172,   219,   301,   790,   790,
     319,   286,  -303,    98,   286,   302,   304,  -303,  -303,  -303,
     317,  -303,   382,   119,   119,  -303,   382,   119,   119,  -303,
     382,   119,   119,   119,   119,   307,  -303,  -303,  -303,   312,
     348,   243,   219,  -303,  -303,   313,  -303,   286,   316,   311,
     314,  -303,   333,  -303,  -303,   221,  -303,   346,   337,  -303,
    -303,   338,  -303,  -303,   339,  -303,  -303,  -303,  -303,   119,
    -303,  -303,   348,   349,   426,   427,  -303,   374,   790,  -303,
     286,   286,  -303,  -303,   286,   286,   421,  -303,   119,   119,
     119,  -303,  -303,  -303,   375,   377,  -303,   378,   380,  -303,
     209,   -33,  -303,   354,   357,  -303,   373,   550,   364,   363,
     434,  -303,  -303,  -303,   310,   426,   310,   427,  -303,  -303,
    -303,  -303,  -303,   384,   209,  -303,   373,  -303,  -303,   221,
      83,  -303,  -303,   286,   119,  -303,  -303,  -303,  -303,  -303,
    -303,  -303,  -303,  -303,  -303,  -303,  -303,  -303,  -303,   385,
    -303,   369,  -303,   731,  -303,   419,  -303,   373,   286,   119,
     419,   370,  -303,  -303
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    35,    38,    39,
      37,     0,     0,    30,     0,   213,    41,    42,     0,     0,
       0,     0,     0,     0,    40,     0,     0,    31,    36,     0,
       0,   192,     4,     0,     5,    16,     0,     0,     0,    17,
      18,     0,     0,    46,    26,    23,    44,    43,     0,    22,
      47,     0,     0,     0,     0,     0,    11,     0,     0,    48,
       0,    14,    13,   166,   161,   163,     0,   192,     0,     0,
     171,   177,     0,     0,     0,     0,     0,     0,    59,    49,
     212,    50,    60,    57,    55,    54,    52,    51,    53,    56,
      58,    61,    48,     0,   162,   167,     0,     0,     0,     0,
       4,    34,     0,    35,   139,     0,   140,     0,   117,     0,
       0,   194,     0,   193,     0,     0,     0,     0,     0,    25,
      20,    21,   137,   138,     0,     0,     0,    19,    10,    15,
       7,     8,     6,     0,    24,     9,    12,     0,     0,   126,
      28,   128,     0,     0,     0,     0,     0,     0,    75,    76,
      77,    78,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,     0,
       0,     0,   122,   118,   119,    80,     0,   112,     0,     0,
     115,    27,     0,   116,    45,   125,   127,   170,     0,     0,
     204,   203,   165,   164,   192,   192,   210,     0,     0,   176,
     175,   174,   172,   173,   166,     0,     0,     0,   146,   144,
     145,   143,   160,   159,   141,   142,   147,   149,   148,   150,
     157,   158,   156,   152,   151,   153,   154,   155,   169,   168,
       0,     0,     0,     0,     0,     0,     0,     0,   126,   125,
       0,     0,   124,   120,   105,    81,     0,     0,   195,   113,
       0,   192,    65,     0,   192,     0,     0,   196,   214,   219,
       0,   188,     0,     0,     0,   180,     0,     0,     0,   179,
       0,     0,     0,     0,     0,     0,   123,   108,   109,     0,
       0,   106,     0,    86,    88,     0,    66,     0,     0,     0,
     206,   205,     0,   135,    29,   211,   215,     0,     0,   190,
     189,     0,   185,   183,     0,   184,   182,   181,    33,     0,
      79,   110,     0,     0,     0,     0,    83,     0,   114,   133,
     192,   192,   201,   129,     0,   192,   220,   178,     0,     0,
       0,   121,   111,    85,   101,    87,    98,     0,    89,   102,
       0,     0,   129,     0,     0,   196,   136,     0,     0,     0,
     217,   191,   187,   186,     0,     0,     0,     0,    68,    71,
      72,    70,    69,     0,     0,    67,   134,   208,   207,   202,
       0,   198,   197,     0,     0,   221,    90,    93,    94,    92,
      96,    97,    95,    91,   100,    99,   104,   103,     4,     0,
     129,   131,   132,     0,   218,    73,     4,   209,   192,     0,
      74,     0,   216,   130
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -303,  -303,  -303,    15,  -303,   -16,    -3,  -303,  -303,  -303,
    -303,    -4,     1,   215,  -303,  -303,  -303,    76,  -303,  -303,
    -303,  -303,  -303,  -303,  -303,   160,  -303,  -303,    87,  -303,
      89,  -303,    88,  -303,   165,  -303,  -303,  -303,  -303,  -303,
    -303,  -303,   284,  -303,  -303,  -303,  -302,    -2,  -303,  -303,
      -1,  -303,  -303,  -303,  -303,  -303,  -303,    27,  -131,  -303,
     303,     0,  -303,  -303,  -152,  -243,  -303,   -61,  -303,   114,
    -303,     6,  -303,  -303,     7,  -303,  -303,  -303,  -303,  -303,
    -303,  -303,  -303
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   116,    34,    35,    78,    37,    38,    39,
      40,    79,   111,    42,    43,    44,   327,   373,   351,    81,
      45,   254,   255,   256,   292,   295,   324,   325,   394,   345,
     346,   348,   349,   289,   290,   291,    46,   117,    47,    48,
     182,   183,   184,   252,    49,    50,   356,    82,   352,   333,
      83,    84,    85,    86,    87,    88,    53,    64,    65,    94,
      95,    89,    71,    55,   217,    56,    90,   112,   113,   305,
      57,    91,   355,   400,    92,   267,    60,    61,   336,   385,
      62,   306,   360
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -201;
  const short int
  Parser::yytable_[] =
  {
        41,    36,    51,    52,    54,   101,   142,   203,   214,   107,
      58,    59,   114,   214,   214,   212,    80,     4,   104,   106,
     209,   210,   242,   245,    96,    97,   374,   108,   102,   103,
       8,     9,    10,   195,   118,   199,   200,   125,   139,   152,
     153,   154,   155,   156,   375,   157,   -64,   321,   158,   159,
     376,   126,   152,   153,   154,   155,   156,     3,   157,    63,
     -64,  -201,  -201,    16,    17,   177,   100,   115,   248,   143,
     144,    24,   249,    68,   148,   149,   150,   151,    28,   342,
     213,   140,   196,   178,   215,   201,   211,   141,   401,   240,
     243,   166,   167,   168,    98,   169,   170,   171,   407,    31,
      77,   122,   123,   299,    33,   167,   168,    70,   169,   170,
     171,   186,    41,    36,    51,    52,    54,   141,   192,    66,
     308,   196,    58,    59,   311,   124,   197,   198,   314,   272,
     152,   153,   154,   155,   156,   193,   157,   402,   202,   158,
     159,   203,   145,   265,   266,   203,   300,   -82,   146,   203,
     273,    69,   301,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   216,   -84,  -200,   276,   247,    93,
     164,   165,   166,   167,   168,   -82,   169,   170,   171,   258,
     259,   268,   269,   264,    99,   100,   -63,   280,   277,   271,
     298,   241,   244,   302,     5,     6,     7,     8,     9,    10,
     -63,    11,    12,   -84,   368,   369,   370,   371,   281,   110,
     137,   109,   293,    13,   275,   119,    14,   279,   270,   120,
    -201,  -201,  -201,  -201,   156,   286,   157,   105,   105,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,   169,
     170,   171,    25,    26,    27,    28,    29,   309,   310,    30,
     294,   312,   313,   372,   121,   315,   316,   317,   318,   353,
     354,   127,   128,   129,   358,   -62,    31,    32,   191,   137,
      67,    33,   130,   167,   168,  -107,   169,   170,   171,   131,
       6,     7,     8,     9,    10,   -62,   334,  -199,   328,   287,
     288,   335,   132,   341,   133,   134,   135,   167,   168,   -62,
     169,   170,   171,   138,    67,   386,   387,   388,   389,   147,
     172,   136,   361,   362,   363,    16,    17,   173,    72,   174,
     175,    22,    23,    24,   176,   357,   126,   179,   180,   181,
      28,   185,   152,   153,   154,   155,   156,   411,   157,   390,
     391,   158,   159,    73,    74,   187,   188,   392,   189,    75,
      76,    31,    77,   204,   393,   190,    33,   205,   404,   251,
     260,   206,   246,   250,   261,   263,   285,   296,   274,   278,
     282,   283,   297,   303,   403,   304,   307,   214,   319,   320,
      19,   330,   326,   412,   331,   167,   168,   329,   169,   170,
     171,    41,    36,    51,    52,    54,    41,    36,    51,    52,
      54,    58,    59,   405,   332,   337,    58,    59,   338,   339,
     340,   410,     5,     6,     7,     8,     9,    10,   343,    11,
      12,   344,   347,   350,   359,   377,   364,   365,   378,   366,
     367,    13,   380,   383,    14,   382,   384,   398,   406,   408,
     399,   413,   323,   396,   395,   397,   322,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   253,     0,   379,
      25,    26,    27,    28,    29,     0,   239,    30,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,     0,   157,
       0,     0,   158,   159,    31,    32,     0,     0,     0,    33,
     160,   161,   162,   163,   152,   153,   154,   155,   156,     0,
     157,     0,     0,   158,   159,     0,     0,     0,     0,     0,
       0,   160,   161,   162,   163,     0,     0,     0,     0,     0,
       0,     0,     0,   164,   165,   166,   167,   168,     0,   169,
     170,   171,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   262,     0,     0,   164,   165,   166,   167,   168,     0,
     169,   170,   171,     0,   152,   153,   154,   155,   156,     0,
     157,     0,   284,   158,   159,     0,     0,     0,     0,     0,
       0,   160,   161,   162,   163,   152,   153,   154,   155,   156,
       0,   157,     0,     0,   158,   159,     0,     0,     0,     0,
       0,     0,   160,   161,   162,   163,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,     0,
     169,   170,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   381,     0,     0,   164,   165,   166,   167,   168,
       0,   169,   170,   171,   152,   153,   154,   155,   156,     0,
     157,     0,   194,   158,   159,     0,     0,     0,     0,     0,
       0,   160,   161,   162,   163,   152,   153,   154,   155,   156,
       0,   157,     0,     0,   158,   159,     0,     0,     0,     0,
       0,     0,   160,   161,   162,   163,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,     0,
     169,   170,   171,     0,     0,     0,     0,     0,     0,     0,
       0,   207,     0,     0,     0,   164,   165,   166,   167,   168,
       0,   169,   170,   171,   152,   153,   154,   155,   156,     0,
     157,     0,   208,   158,   159,     0,     0,     0,     0,     0,
       0,   160,   161,   162,   163,   152,   153,   154,   155,   156,
       0,   157,     0,     0,   158,   159,     0,     0,     0,     0,
       0,     0,   160,   161,   162,   163,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,     0,
     169,   170,   171,     0,     0,     0,     0,     0,     0,     0,
       0,   257,     0,     0,     0,   164,   165,   166,   167,   168,
       0,   169,   170,   171,   152,   153,   154,   155,   156,     0,
     157,     0,   409,   158,   159,     0,     0,     0,     0,     0,
       0,   160,   161,   162,   163,   152,   153,   154,   155,   156,
       0,   157,     0,     0,   158,   159,     0,     0,     0,     0,
       0,     0,   160,     0,   162,   163,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,     0,
     169,   170,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   164,   165,   166,   167,   168,
       0,   169,   170,   171,   152,   153,   154,   155,   156,     0,
     157,     0,     0,   158,   159,     0,   152,   153,   154,   155,
     156,   160,   157,   162,     0,   158,   159,   152,   153,   154,
     155,   156,     0,   157,     0,   162,   158,   159,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,     0,
     169,   170,   171,     0,     0,     0,   164,   165,   166,   167,
     168,     0,   169,   170,   171,     0,     0,     0,   165,   166,
     167,   168,     0,   169,   170,   171
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     4,     4,     4,    21,    67,   138,     5,    25,
       4,     4,     8,     5,     5,     5,    15,     2,    22,    23,
       4,     5,   174,   175,     4,     5,    59,    26,     4,     5,
       6,     7,     8,     5,    33,     4,     5,    61,     5,    14,
      15,    16,    17,    18,    77,    20,    61,   290,    23,    24,
     352,    75,    14,    15,    16,    17,    18,     0,    20,     5,
      75,    23,    24,    39,    40,    75,    76,    63,     5,    68,
      69,    47,     5,    80,    73,    74,    75,    76,    54,   322,
      70,    48,    54,    99,    81,    54,    70,    54,     5,    81,
      81,    66,    67,    68,    74,    70,    71,    72,   400,    75,
      76,    45,    46,     5,    80,    67,    68,     5,    70,    71,
      72,   110,   116,   116,   116,   116,   116,    54,    60,    69,
     272,    54,   116,   116,   276,    69,   125,   126,   280,    60,
      14,    15,    16,    17,    18,    77,    20,    54,   137,    23,
      24,   272,    63,   204,   205,   276,    48,     3,    69,   280,
      81,    80,    54,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   147,     3,    63,    60,   177,    54,
      64,    65,    66,    67,    68,    41,    70,    71,    72,   188,
     189,   207,   208,    80,     5,    76,    61,    60,    81,   215,
     261,   174,   175,   264,     3,     4,     5,     6,     7,     8,
      75,    10,    11,    41,     5,     6,     7,     8,    81,    80,
      61,     4,     3,    22,   240,    79,    25,   243,    69,    79,
      14,    15,    16,    17,    18,   251,    20,    22,    23,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    70,
      71,    72,    51,    52,    53,    54,    55,   273,   274,    58,
      41,   277,   278,    54,    79,   281,   282,   283,   284,   330,
     331,    79,    79,    79,   335,    75,    75,    76,    77,    61,
      80,    80,    79,    67,    68,    42,    70,    71,    72,    79,
       4,     5,     6,     7,     8,    61,    75,    63,   297,    56,
      57,    80,    79,   319,    63,    79,    79,    67,    68,    75,
      70,    71,    72,    60,    80,     5,     6,     7,     8,    80,
      61,    79,   338,   339,   340,    39,    40,    60,    42,    80,
      80,    45,    46,    47,     4,   334,    75,    69,    69,    50,
      54,    76,    14,    15,    16,    17,    18,   408,    20,    39,
      40,    23,    24,    67,    68,    82,    60,    47,    63,    73,
      74,    75,    76,    80,    54,    77,    80,    80,   384,    49,
       8,    81,    80,    80,    80,    69,     5,    76,    81,    81,
      81,    81,    63,    81,   383,    81,    69,     5,    81,    77,
      42,    80,    79,   409,    80,    67,    68,    81,    70,    71,
      72,   405,   405,   405,   405,   405,   410,   410,   410,   410,
     410,   405,   405,   398,    81,    69,   410,   410,    81,    81,
      81,   406,     3,     4,     5,     6,     7,     8,    79,    10,
      11,     5,     5,    59,    13,    81,    61,    60,    81,    61,
      60,    22,    69,    80,    25,    81,    12,    63,    63,    80,
     374,    81,   292,   366,   365,   367,   291,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,   183,    -1,   355,
      51,    52,    53,    54,    55,    -1,   173,    58,    -1,    -1,
      -1,    -1,    -1,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    75,    76,    -1,    -1,    -1,    80,
      31,    32,    33,    34,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    64,    65,    66,    67,    68,    -1,
      70,    71,    72,    -1,    14,    15,    16,    17,    18,    -1,
      20,    -1,    82,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    70,    71,    72,    14,    15,    16,    17,    18,    -1,
      20,    -1,    81,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    70,    71,    72,    14,    15,    16,    17,    18,    -1,
      20,    -1,    81,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    70,    71,    72,    14,    15,    16,    17,    18,    -1,
      20,    -1,    81,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    70,    71,    72,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    14,    15,    16,    17,
      18,    31,    20,    33,    -1,    23,    24,    14,    15,    16,
      17,    18,    -1,    20,    -1,    33,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    70,    71,    72,    -1,    -1,    -1,    65,    66,
      67,    68,    -1,    70,    71,    72
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    84,    85,     0,    86,     3,     4,     5,     6,     7,
       8,    10,    11,    22,    25,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    51,    52,    53,    54,    55,
      58,    75,    76,    80,    87,    88,    89,    90,    91,    92,
      93,    94,    96,    97,    98,   103,   119,   121,   122,   127,
     128,   130,   133,   139,   144,   146,   148,   153,   154,   157,
     159,   160,   163,     5,   140,   141,    69,    80,    80,    80,
       5,   145,    42,    67,    68,    73,    74,    76,    89,    94,
      95,   102,   130,   133,   134,   135,   136,   137,   138,   144,
     149,   154,   157,    54,   142,   143,     4,     5,    74,     5,
      76,    88,     4,     5,    94,    96,    94,    88,    95,     4,
      80,    95,   150,   151,     8,    63,    86,   120,    95,    79,
      79,    79,    45,    46,    69,    61,    75,    79,    79,    79,
      79,    79,    79,    63,    79,    79,    79,    61,    60,     5,
      48,    54,   150,    95,    95,    63,    69,    80,    95,    95,
      95,    95,    14,    15,    16,    17,    18,    20,    23,    24,
      31,    32,    33,    34,    64,    65,    66,    67,    68,    70,
      71,    72,    61,    60,    80,    80,     4,    75,    88,    69,
      69,    50,   123,   124,   125,    76,    95,    82,    60,    63,
      77,    77,    60,    77,    81,     5,    54,    95,    95,     4,
       5,    54,    95,   141,    80,    80,    81,    81,    81,     4,
       5,    70,     5,    70,     5,    81,   140,   147,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,   143,
      81,   140,   147,    81,   140,   147,    80,    95,     5,     5,
      80,    49,   126,   125,   104,   105,   106,    81,    95,    95,
       8,    80,    82,    69,    80,   150,   150,   158,    88,    88,
      69,    88,    60,    81,    81,    88,    60,    81,    81,    88,
      60,    81,    81,    81,    82,     5,    88,    56,    57,   116,
     117,   118,   107,     3,    41,   108,    76,    63,   150,     5,
      48,    54,   150,    81,    81,   152,   164,    69,   147,    88,
      88,   147,    88,    88,   147,    88,    88,    88,    88,    81,
      77,   148,   117,   108,   109,   110,    79,    99,    95,    81,
      80,    80,    81,   132,    75,    80,   161,    69,    81,    81,
      81,    88,   148,    79,     5,   112,   113,     5,   114,   115,
      59,   101,   131,   150,   150,   155,   129,    95,   150,    13,
     165,    88,    88,    88,    61,    60,    61,    60,     5,     6,
       7,     8,    54,   100,    59,    77,   129,    81,    81,   152,
      69,    82,    81,    80,    12,   162,     5,     6,     7,     8,
      39,    40,    47,    54,   111,   113,   111,   115,    63,   100,
     156,     5,    54,    95,    88,    86,    63,   129,    80,    81,
      86,   150,    88,    81
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
      44,    61,   315,    58,   124,    94,    38,    45,    43,    46,
      42,    47,    37,    33,   126,    91,   123,   125,   316,    59,
      40,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    83,    85,    84,    86,    86,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    88,    89,    89,
      90,    91,    92,    92,    93,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    96,    96,    96,    97,    99,    98,   100,   100,
     100,   100,   100,   101,   101,   102,   102,   102,   102,   103,
     104,   104,   106,   105,   107,   105,   109,   108,   110,   108,
     111,   111,   111,   111,   111,   111,   111,   111,   112,   112,
     113,   113,   114,   114,   115,   116,   116,   117,   117,   117,
     118,   118,   119,   120,   120,   121,   121,   122,   123,   124,
     124,   125,   126,   126,   127,   128,   128,   128,   128,   129,
     129,   129,   129,   131,   130,   132,   130,   133,   133,   133,
     133,   134,   134,   134,   134,   134,   134,   135,   135,   136,
     136,   137,   137,   137,   137,   137,   138,   138,   138,   138,
     138,   139,   139,   140,   140,   141,   141,   142,   142,   143,
     144,   145,   145,   146,   146,   146,   146,   146,   147,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   149,   149,
     149,   149,   150,   150,   151,   151,   152,   152,   152,   153,
     153,   155,   154,   154,   154,   154,   154,   154,   156,   154,
     158,   157,   159,   159,   160,   161,   161,   162,   162,   164,
     165,   163
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     2,     1,     1,     1,     2,
       2,     2,     1,     1,     2,     2,     1,     3,     3,     6,
       1,     1,     3,     6,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     0,     8,     1,     1,
       1,     1,     1,     4,     5,     2,     2,     2,     2,     6,
       0,     1,     0,     3,     0,     4,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     1,     3,     3,     0,     1,     0,     1,     1,
       2,     3,     3,     3,     5,     3,     3,     2,     1,     1,
       2,     5,     0,     2,     4,     3,     3,     3,     3,     0,
       6,     3,     3,     0,     8,     0,     8,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     3,     3,     1,     1,     3,     3,
       3,     1,     3,     4,     4,     4,     4,     2,     4,     5,
       5,     6,     6,     6,     6,     6,     8,     8,     4,     5,
       5,     7,     0,     1,     1,     3,     0,     4,     4,     1,
       3,     0,     8,     3,     3,     5,     5,     8,     0,    10,
       0,     6,     2,     1,     5,     0,     6,     0,     2,     0,
       0,     9
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"var\"",
  "\"type specification\"", "\"identifier\"", "\"number\"",
  "\"float-number\"", "\"string\"", "\"for\"", "\"while\"", "\"if\"",
  "\"else\"", "\"else if\"", "\"<=\"", "\">=\"", "\"<\"", "\">\"",
  "\">>\"", "\">>=\"", "\"<<\"", "\"<<=\"", "\"break\"", "\"==\"",
  "\"!=\"", "\"import\"", "\"+=\"", "\"*=\"", "\"/=\"", "\"-=\"", "\"%=\"",
  "\"||\"", "\"or\"", "\"&&\"", "\"and\"", "\"&=\"", "\"|=\"", "\"^=\"",
  "\"return\"", "\"true\"", "\"false\"", "\"const\"", "\"function\"",
  "\"spawn\"", "\"critical\"", "\"++\"", "\"--\"", "\"null\"", "\"new\"",
  "\"finally\"", "\"catch\"", "\"try\"", "\"throw\"", "\"continue\"",
  "\"constant identifier\"", "\"class\"", "\"public\"", "\"private\"",
  "\"switch\"", "\"case\"", "','", "'='", "XOR_EQUAL", "':'", "'|'", "'^'",
  "'&'", "'-'", "'+'", "'.'", "'*'", "'/'", "'%'", "'!'", "'~'", "'['",
  "'{'", "'}'", "UMINUS", "';'", "'('", "')'", "']'", "$accept", "program",
  "$@1", "statement_list", "statement", "block", "instantiation", "break",
  "continue", "thread_block", "critical_block", "object", "rvalue",
  "lvalue", "subscript", "switch_expr", "@2", "label", "case_list",
  "unary", "class_def", "class_attr_decl", "class_attr_list", "@3", "@4",
  "non_empty_class_attr_list", "@5", "@6", "attr_rvalue",
  "class_attr_decl_list", "class_attr_decl_impl",
  "class_attr_const_decl_list", "class_attr_const_decl_impl",
  "class_method_decl", "visibility", "class_method_list", "array",
  "key_value_list", "map", "throw", "catch", "not_empty_catch",
  "catch_impl", "finally", "try_catch_finally", "property_access",
  "mcall_chain", "mcall", "@7", "@8", "inc_dec", "comparison", "boolean",
  "logic", "arithmetic", "bitwise", "variable_decl", "variable_decl_list",
  "variable_decl_impl", "const_decl_list", "const_decl_impl", "assignment",
  "import_ident_list", "import", "vararg", "fdecl", "anonymous_fdecl",
  "call_args", "non_empty_call_args", "fcall_chain",
  "fully_qualified_name", "fully_qualified_call", "@9", "@10", "fcall",
  "@11", "return_stmt", "while", "elseif", "else", "if", "@12", "@13", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        84,     0,    -1,    -1,    85,    86,    -1,    -1,    86,    87,
      -1,   146,    79,    -1,   139,    79,    -1,   144,    79,    -1,
     157,    79,    -1,   130,    79,    -1,   148,    -1,   159,    79,
      -1,   163,    -1,   160,    -1,   133,    79,    -1,    88,    -1,
      92,    -1,    93,    -1,   122,    79,    -1,    90,    79,    -1,
      91,    79,    -1,   127,    -1,   103,    -1,   154,    79,    -1,
      89,    79,    -1,    98,    -1,    76,    86,    77,    -1,     4,
      69,    48,    -1,     4,    69,    48,    80,   150,    81,    -1,
      22,    -1,    53,    -1,    43,     5,    88,    -1,    43,     5,
      75,    95,    82,    88,    -1,    44,    88,    -1,     5,    -1,
      54,    -1,     8,    -1,     6,    -1,     7,    -1,    47,    -1,
      39,    -1,    40,    -1,   121,    -1,   119,    -1,    80,    95,
      81,    -1,    97,    -1,   128,    -1,   157,    -1,    94,    -1,
     102,    -1,   137,    -1,   136,    -1,   138,    -1,   135,    -1,
     134,    -1,   144,    -1,   133,    -1,   149,    -1,    89,    -1,
     130,    -1,   154,    -1,     5,    -1,   128,    -1,    97,    -1,
      96,    75,    95,    82,    -1,    -1,    58,    80,    95,    81,
      76,    99,   101,    77,    -1,     5,    -1,    54,    -1,     8,
      -1,     6,    -1,     7,    -1,    59,   100,    63,    86,    -1,
     101,    59,   100,    63,    86,    -1,    67,    95,    -1,    68,
      95,    -1,    73,    95,    -1,    74,    95,    -1,    55,     4,
      76,   104,   116,    77,    -1,    -1,   105,    -1,    -1,   106,
     108,    79,    -1,    -1,   105,   107,   108,    79,    -1,    -1,
       3,   109,   112,    -1,    -1,    41,   110,   114,    -1,     5,
      -1,    54,    -1,     8,    -1,     6,    -1,     7,    -1,    47,
      -1,    39,    -1,    40,    -1,   113,    -1,   112,    60,   113,
      -1,     5,    61,   111,    -1,     5,    -1,   115,    -1,   114,
      60,   115,    -1,     5,    61,   111,    -1,    -1,   118,    -1,
      -1,    56,    -1,    57,    -1,   117,   148,    -1,   118,   117,
     148,    -1,    75,   150,    82,    -1,     8,    63,    95,    -1,
     120,    60,     8,    63,    95,    -1,    76,    63,    77,    -1,
      76,   120,    77,    -1,    52,    95,    -1,   124,    -1,   125,
      -1,   124,   125,    -1,    50,    80,     5,    81,    88,    -1,
      -1,    49,    88,    -1,    51,    88,   123,   126,    -1,    94,
      69,     5,    -1,     4,    69,     5,    -1,    94,    69,    54,
      -1,     4,    69,    54,    -1,    -1,   129,    69,     5,    80,
     150,    81,    -1,   129,    69,     5,    -1,   129,    69,    54,
      -1,    -1,    94,    69,     5,    80,   150,    81,   131,   129,
      -1,    -1,     4,    69,     5,    80,   150,    81,   132,   129,
      -1,    94,    45,    -1,    94,    46,    -1,    45,    94,    -1,
      46,    94,    -1,    95,    23,    95,    -1,    95,    24,    95,
      -1,    95,    17,    95,    -1,    95,    15,    95,    -1,    95,
      16,    95,    -1,    95,    14,    95,    -1,    95,    31,    95,
      -1,    95,    33,    95,    -1,    95,    32,    95,    -1,    95,
      34,    95,    -1,    95,    68,    95,    -1,    95,    67,    95,
      -1,    95,    70,    95,    -1,    95,    71,    95,    -1,    95,
      72,    95,    -1,    95,    66,    95,    -1,    95,    64,    95,
      -1,    95,    65,    95,    -1,    95,    20,    95,    -1,    95,
      18,    95,    -1,     3,   140,    -1,    41,   142,    -1,   141,
      -1,   140,    60,   141,    -1,     5,    61,    95,    -1,     5,
      -1,   143,    -1,   142,    60,   143,    -1,    54,    61,    95,
      -1,    96,    61,    95,    -1,     5,    -1,   145,    69,     5,
      -1,    25,   145,    69,    70,    -1,    25,   145,    63,    70,
      -1,    25,   145,    63,     5,    -1,    25,   145,    63,     4,
      -1,    25,   145,    -1,     5,    69,    69,    69,    -1,    42,
       5,    80,    81,    88,    -1,    42,     4,    80,    81,    88,
      -1,    42,    74,     4,    80,    81,    88,    -1,    42,     5,
      80,   147,    81,    88,    -1,    42,     4,    80,   147,    81,
      88,    -1,    42,     5,    80,   140,    81,    88,    -1,    42,
       4,    80,   140,    81,    88,    -1,    42,     5,    80,   140,
      60,   147,    81,    88,    -1,    42,     4,    80,   140,    60,
     147,    81,    88,    -1,    42,    80,    81,    88,    -1,    42,
      80,   147,    81,    88,    -1,    42,    80,   140,    81,    88,
      -1,    42,    80,   140,    60,   147,    81,    88,    -1,    -1,
     151,    -1,    95,    -1,   151,    60,    95,    -1,    -1,   152,
      80,   150,    81,    -1,   152,    75,    95,    82,    -1,     5,
      -1,   153,    63,     5,    -1,    -1,   153,    63,     5,    80,
     150,    81,   155,   152,    -1,   153,    63,    54,    -1,   153,
      63,     5,    -1,   153,    63,     4,    69,    54,    -1,   153,
      63,     4,    69,    48,    -1,   153,    63,     4,    69,    48,
      80,   150,    81,    -1,    -1,   153,    63,     4,    69,     5,
      80,   150,    81,   156,   129,    -1,    -1,     5,    80,   150,
      81,   158,   152,    -1,    38,    95,    -1,    38,    -1,    10,
      80,    95,    81,    88,    -1,    -1,   161,    13,    80,    95,
      81,    88,    -1,    -1,    12,    88,    -1,    -1,    -1,    11,
      80,    95,    81,    88,   164,   161,   165,   162,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     8,    11,    14,    17,    20,
      23,    26,    28,    31,    33,    35,    38,    40,    42,    44,
      47,    50,    53,    55,    57,    60,    63,    65,    69,    73,
      80,    82,    84,    88,    95,    98,   100,   102,   104,   106,
     108,   110,   112,   114,   116,   118,   122,   124,   126,   128,
     130,   132,   134,   136,   138,   140,   142,   144,   146,   148,
     150,   152,   154,   156,   158,   160,   165,   166,   175,   177,
     179,   181,   183,   185,   190,   196,   199,   202,   205,   208,
     215,   216,   218,   219,   223,   224,   229,   230,   234,   235,
     239,   241,   243,   245,   247,   249,   251,   253,   255,   257,
     261,   265,   267,   269,   273,   277,   278,   280,   281,   283,
     285,   288,   292,   296,   300,   306,   310,   314,   317,   319,
     321,   324,   330,   331,   334,   339,   343,   347,   351,   355,
     356,   363,   367,   371,   372,   381,   382,   391,   394,   397,
     400,   403,   407,   411,   415,   419,   423,   427,   431,   435,
     439,   443,   447,   451,   455,   459,   463,   467,   471,   475,
     479,   483,   486,   489,   491,   495,   499,   501,   503,   507,
     511,   515,   517,   521,   526,   531,   536,   541,   544,   549,
     555,   561,   568,   575,   582,   589,   596,   605,   614,   619,
     625,   631,   639,   640,   642,   644,   648,   649,   654,   659,
     661,   665,   666,   675,   679,   683,   689,   695,   704,   705,
     716,   717,   724,   727,   729,   735,   736,   743,   744,   747,
     748,   749
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   218,   218,   218,   222,   223,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   251,   255,   256,
     260,   264,   268,   275,   285,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   328,   329,   330,   334,   338,   338,   342,   343,
     344,   345,   346,   350,   351,   355,   356,   357,   358,   362,
     366,   367,   371,   371,   372,   372,   376,   376,   377,   377,
     381,   382,   383,   384,   385,   386,   387,   388,   392,   393,
     397,   398,   402,   403,   407,   411,   412,   416,   417,   418,
     422,   423,   427,   431,   432,   436,   437,   441,   445,   449,
     450,   454,   458,   459,   463,   467,   468,   469,   470,   474,
     475,   476,   477,   481,   481,   482,   482,   486,   487,   488,
     489,   493,   494,   495,   496,   497,   498,   502,   503,   507,
     508,   512,   513,   514,   515,   516,   520,   521,   522,   523,
     524,   528,   529,   533,   534,   538,   539,   543,   544,   548,
     552,   556,   557,   561,   562,   563,   564,   565,   569,   573,
     575,   577,   579,   581,   583,   585,   587,   589,   594,   596,
     598,   600,   605,   606,   610,   611,   615,   616,   617,   621,
     622,   626,   626,   627,   628,   629,   630,   631,   632,   632,
     636,   636,   640,   641,   645,   649,   651,   656,   657,   661,
     662,   661
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
       2,     2,     2,    73,     2,     2,     2,    72,    66,     2,
      80,    81,    70,    68,    60,    67,    69,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    79,
       2,    61,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    75,     2,    82,    65,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    76,    64,    77,    74,     2,     2,     2,
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
      55,    56,    57,    58,    59,    62,    78
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 965;
  const int Parser::yynnts_ = 83;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 3;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 83;

  const unsigned int Parser::yyuser_token_number_max_ = 316;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} // clever





namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever

