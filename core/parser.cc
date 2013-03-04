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

  case 26:

    { (yyval.block) = (yysemantic_stack_[(3) - (2)].block); }
    break;

  case 27:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(3) - (1)].type), NULL, yyloc); }
    break;

  case 28:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (5)].narray),   yyloc); }
    break;

  case 29:

    { (yyval.break_) = new ast::Break(yyloc); }
    break;

  case 30:

    { (yyval.continue_) = new ast::Continue(yyloc); }
    break;

  case 31:

    {
#ifndef CLEVER_THREADS
		error(yyloc, "Cannot use critical block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.criticalblock) = new ast::CriticalBlock((yysemantic_stack_[(2) - (2)].block), yyloc);
#endif
	}
    break;

  case 42:

    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 52:

    { (yysemantic_stack_[(1) - (1)].assignment)->setUseResult(); }
    break;

  case 60:

    { (yysemantic_stack_[(1) - (1)].property)->setWriteMode(); }
    break;

  case 62:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 63:

    { (yyval.node) = new ast::Switch((yysemantic_stack_[(5) - (3)].node), yyloc); }
    break;

  case 64:

    { (yyval.switch_) = (yysemantic_stack_[(8) - (7)].switch_); }
    break;

  case 71:

    { (yysemantic_stack_[(4) - (0)].switch_)->addCase((yysemantic_stack_[(4) - (2)].node), (yysemantic_stack_[(4) - (4)].block)); (yyval.switch_) = (yysemantic_stack_[(4) - (0)].switch_); }
    break;

  case 72:

    { (yysemantic_stack_[(3) - (0)].switch_)->addCase(NULL, (yysemantic_stack_[(3) - (3)].block)); (yyval.switch_) = (yysemantic_stack_[(3) - (0)].switch_);     }
    break;

  case 73:

    { (yysemantic_stack_[(5) - (0)].switch_)->addCase((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block)); (yyval.switch_) = (yysemantic_stack_[(5) - (0)].switch_); }
    break;

  case 74:

    { (yysemantic_stack_[(4) - (0)].switch_)->addCase(NULL, (yysemantic_stack_[(4) - (4)].block)); (yyval.switch_) = (yysemantic_stack_[(4) - (0)].switch_);     }
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

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 130:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 131:

    { (yyval.mcall) = (yysemantic_stack_[(0) - (0)].mcall); }
    break;

  case 132:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (0)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 133:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 134:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); (yyval.property)->setStatic(); }
    break;

  case 135:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 136:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 137:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 138:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 139:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 140:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 141:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 142:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 143:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 144:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 145:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].property)->setWriteMode(); }
    break;

  case 146:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].property)->setWriteMode(); }
    break;

  case 147:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].property)->setWriteMode(); }
    break;

  case 148:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].property)->setWriteMode(); }
    break;

  case 149:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 150:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 151:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 152:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 153:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 154:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 155:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 156:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 157:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 158:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 159:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 160:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 161:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 162:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 163:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 164:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 165:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 166:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 167:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 168:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 169:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 170:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 171:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 172:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 173:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 174:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 175:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 176:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 177:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 178:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 179:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 180:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 181:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 182:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 183:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 184:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 185:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 186:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 187:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 188:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 189:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 190:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 191:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 192:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 193:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 194:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 195:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 196:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 197:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 198:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 199:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 200:

    { (yyval.narray) = NULL; }
    break;

  case 202:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 203:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 204:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 205:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 206:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 208:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 209:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 210:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 211:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 212:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 213:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 214:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 215:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 216:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 217:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 218:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 219:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 220:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 221:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 222:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 224:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 225:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 226:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 227:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 228:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 229:

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
  const short int Parser::yypact_ninf_ = -331;
  const short int
  Parser::yypact_[] =
  {
      -331,    43,  -331,  -331,   293,    25,   -68,   179,  -331,  -331,
    -331,   -30,    45,  -331,    57,   457,  -331,  -331,    79,    40,
      47,   159,   159,  -331,    47,   457,  -331,  -331,   154,    81,
     457,    14,   457,  -331,  -331,    89,    90,    91,  -331,    93,
      -6,    70,  -331,  -331,  -331,  -331,   121,  -331,   186,   129,
     157,   166,   167,   168,  -331,   185,   192,   195,   199,  -331,
    -331,   220,   222,  -331,    18,   457,   457,   457,  -331,   133,
     203,   457,   457,   457,   457,    14,  -331,    93,   786,  -331,
     183,  -331,  -331,  -331,  -331,  -331,  -331,  -331,  -331,  -331,
    -331,  -331,   226,   234,  -331,   215,   227,   298,  -331,  -331,
     237,   163,   239,   235,   128,   239,   128,   260,   786,   236,
     457,   786,   229,   253,   251,   242,    53,   -11,   605,  -331,
    -331,  -331,  -331,  -331,    48,   457,   457,  -331,  -331,  -331,
      65,  -331,  -331,  -331,  -331,  -331,    33,  -331,  -331,  -331,
     457,    25,   240,   241,  -331,   243,   626,   685,    30,     6,
      21,  -331,  -331,  -331,  -331,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,    79,    27,    28,   248,
      67,   106,   139,   249,   268,   260,  -331,     1,   706,  -331,
     457,   457,  -331,  -331,   314,  -331,  -331,   250,  -331,   857,
     524,   262,  -331,   254,   161,  -331,   786,  -331,   457,   457,
    -331,    47,    47,  -331,  -331,  -331,  -331,  -331,    88,    47,
     -35,   259,   205,   205,   205,   205,   221,   221,   503,   503,
     869,   845,   880,   857,   939,   950,   584,     9,     9,  -331,
    -331,  -331,   786,  -331,    47,    -8,   267,    47,    59,   271,
     272,  -331,  -331,  -331,   344,    47,  -331,  -331,   211,    13,
      44,   284,   786,   786,   299,   457,  -331,   457,    69,   457,
     280,   282,  -331,  -331,  -331,   295,  -331,   360,    47,    47,
    -331,   360,    47,    47,  -331,   360,    47,    47,    47,   285,
    -331,  -331,  -331,   294,   330,   211,    44,  -331,  -331,   296,
    -331,   457,   300,   301,   297,   304,  -331,   306,  -331,  -331,
     182,  -331,   305,   307,  -331,  -331,   308,  -331,  -331,   311,
    -331,  -331,  -331,    47,  -331,  -331,   330,   315,   371,   374,
    -331,    76,   786,  -331,  -331,   457,   457,  -331,  -331,   457,
     457,   372,  -331,    47,    47,    47,  -331,  -331,  -331,   332,
     335,  -331,   337,   336,  -331,   210,   338,   174,  -331,  -331,
     318,   319,  -331,   333,   545,   322,   325,   396,  -331,  -331,
    -331,   351,   371,   351,   374,    80,   346,   349,   362,   363,
     239,   365,   141,  -331,   210,   375,  -331,   333,   333,  -331,
    -331,   182,   142,  -331,  -331,   457,    47,  -331,  -331,  -331,
    -331,  -331,  -331,  -331,  -331,  -331,  -331,  -331,  -331,  -331,
    -331,   293,   377,  -331,  -331,   334,  -331,   765,  -331,   293,
    -331,   293,   333,   457,    47,   293,   354,  -331,  -331
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    32,    35,    36,
      34,     0,     0,    29,     0,   221,    38,    39,     0,     0,
       0,     0,     0,    37,     0,     0,    30,    33,     0,     0,
     200,     4,     0,     5,    16,     0,     0,     0,    17,     0,
       0,    43,    25,    22,    41,    40,     0,    21,    60,     0,
       0,     0,     0,     0,    11,     0,     0,    44,     0,    14,
      13,   174,   169,   171,     0,   200,     0,     0,   179,   185,
       0,     0,     0,     0,     0,     0,    55,    45,   220,    46,
      58,    56,    53,    51,    50,    48,    47,    49,    52,    54,
      57,    44,     0,   170,   175,     0,     0,     0,     4,    31,
       0,    32,   143,     0,   147,   144,   148,     0,   117,     0,
       0,   202,     0,   201,     0,     0,     0,     0,     0,    24,
      19,    20,   141,   142,     0,     0,     0,    18,   145,   146,
       0,    10,    15,     7,     8,     6,     0,    23,     9,    12,
       0,     0,   126,    27,   128,     0,     0,     0,     0,     0,
       0,    75,    76,    77,    78,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   122,   118,   119,    80,     0,   112,
       0,     0,   115,    26,     0,   116,    42,   125,   127,   178,
       0,   129,   130,     0,   212,   211,   173,   172,   200,   200,
     218,     0,     0,   184,   183,   182,   180,   181,   174,     0,
       0,     0,   154,   152,   153,   151,   168,   167,   149,   150,
     155,   157,   156,   158,   165,   166,   164,   160,   159,   161,
     162,   163,   177,   176,     0,     0,     0,     0,     0,     0,
       0,   126,   125,   129,     0,     0,   124,   120,   105,    81,
       0,     0,   203,   113,     0,   200,    62,   200,     0,   200,
       0,     0,   204,   222,   227,     0,   196,     0,     0,     0,
     188,     0,     0,     0,   187,     0,     0,     0,     0,     0,
     123,   108,   109,     0,     0,   106,     0,    86,    88,     0,
      63,     0,     0,     0,     0,   214,   213,     0,   139,    28,
     219,   223,     0,     0,   198,   197,     0,   193,   191,     0,
     192,   190,   189,     0,    79,   110,     0,     0,     0,     0,
      83,     0,   114,   135,   137,   200,   200,   209,   131,     0,
     200,   228,   186,     0,     0,     0,   121,   111,    85,   101,
      87,    98,     0,    89,   102,     0,     0,     0,   131,   131,
       0,     0,   204,   140,     0,     0,     0,   225,   199,   195,
     194,     0,     0,     0,     0,    32,    35,    36,    34,    33,
       0,     0,    60,     4,     0,     0,    64,   136,   138,   216,
     215,   210,     0,   206,   205,     0,     0,   229,    90,    93,
      94,    92,    96,    97,    95,    91,   100,    99,   104,   103,
       4,    72,     0,     4,   131,   133,   134,     0,   226,    71,
       4,    74,   217,   200,     0,    73,     0,   224,   132
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -331,  -331,  -331,     3,  -331,   -18,     8,  -331,  -331,  -331,
      -4,    16,   -14,  -331,  -331,  -331,    63,  -331,  -331,  -331,
    -331,  -331,  -331,  -331,   153,  -331,  -331,    64,  -331,    78,
    -331,    84,  -331,   160,  -331,  -331,  -331,  -331,  -331,  -331,
    -331,   274,  -331,  -331,    -1,  -330,    11,  -331,  -331,  -331,
      20,  -331,  -331,  -331,  -331,  -331,  -331,  -110,  -131,  -331,
     276,    23,  -331,  -331,  -164,  -275,  -331,   -56,  -331,   104,
    -331,    32,  -331,  -331,    35,  -331,  -331,  -331,  -331,  -331,
    -331,  -331,  -331
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   116,    33,    34,    76,    36,    37,    38,
      77,   111,    40,    41,    42,   331,   381,   357,    79,    43,
     258,   259,   260,   296,   299,   328,   329,   406,   350,   351,
     353,   354,   293,   294,   295,    44,   117,    45,    46,   184,
     185,   186,   256,    47,    80,   363,    81,   358,   359,   338,
      82,    83,    84,    85,    86,    87,    51,    62,    63,    93,
      94,    88,    69,    53,   221,    54,    89,   112,   113,   310,
      55,    90,   362,   414,    91,   272,    58,    59,   341,   397,
      60,   311,   367
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -209;
  const short int
  Parser::yytable_[] =
  {
        39,    64,    99,    48,   -82,     4,   107,   103,   103,   145,
     207,   216,    35,   246,   249,    49,   -84,   102,   105,   325,
     104,   106,   114,   142,    50,   277,   218,    52,   387,   388,
      61,    78,   218,   218,   213,   214,    56,   203,   204,    57,
     220,   108,   -82,     3,    95,    96,   278,   297,   118,   194,
      66,   347,   281,   197,   -84,   125,     5,     6,     7,     8,
       9,    10,    68,    11,    12,   143,   195,   245,   248,   126,
     201,   144,   251,   282,   304,    13,   217,   115,    14,   172,
     173,   174,   146,   147,   422,   298,   205,   151,   152,   153,
     154,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     215,   198,   219,    24,    25,    26,    27,    28,   244,   247,
      29,   252,    39,   313,    97,    48,   305,   316,   202,   285,
     144,   319,   306,    98,    35,    67,   188,    49,    30,    31,
     193,   -61,    92,    32,   355,   356,    50,   122,   123,    52,
     286,   199,   200,   -65,   253,   -61,   207,   415,    56,   140,
     207,    57,   270,   271,   207,   -59,   206,   275,   109,   198,
      65,   110,   124,   100,   101,     8,     9,    10,   119,   120,
     121,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   202,   273,   274,   416,   148,   182,    16,    17,
     127,   276,   149,   -60,   -70,    23,   262,   263,   131,   302,
     182,   303,    27,   307,   100,   375,   376,   377,   378,  -209,
    -209,  -209,  -209,   159,  -208,   160,   280,   128,   129,   284,
     128,   129,   384,   385,    30,    75,   132,   290,   -59,    32,
     -59,   269,  -207,    65,   -60,   133,   134,   135,   136,    16,
      17,   386,   130,  -107,   -59,   130,    23,   339,   -60,    65,
     314,   315,   340,   379,   317,   318,   291,   292,   320,   321,
     322,   137,   170,   171,   138,   172,   173,   174,   139,   360,
     361,   140,   141,   150,   365,    30,    75,   175,   170,   171,
      32,   172,   173,   174,   176,   177,     5,     6,     7,     8,
       9,    10,   179,    11,    12,   346,   180,   178,   181,   183,
     126,   189,   187,   190,   191,    13,   255,   332,    14,   192,
     208,   209,   264,   268,   210,   368,   369,   370,   250,   254,
     265,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     279,   103,   267,    24,    25,    26,    27,    28,   283,   289,
      29,   380,   287,   288,   382,   364,   398,   399,   400,   401,
     300,   308,   301,   309,   312,   218,   323,   426,    30,    31,
     103,   324,    19,    32,   342,   330,   349,   335,   418,   352,
     380,   333,   334,   382,   336,   366,   411,   337,   343,   344,
     402,   403,   345,   371,   348,   372,   374,   404,   373,   389,
     390,   383,   392,   394,   405,   395,   427,    39,   396,   -68,
      48,   417,   -69,   419,   423,    39,   421,    39,    48,    35,
      48,    39,    49,   425,    48,   -67,   -66,    35,   410,    35,
      49,    50,    49,    35,    52,   428,    49,   408,   413,    50,
     420,    50,    52,    56,    52,    50,    57,   412,    52,   327,
     407,    56,   243,    56,    57,   326,    57,    56,   409,   257,
      57,     6,     7,     8,     9,    10,   391,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    17,     0,    70,
       0,    21,    22,    23,     0,     0,     0,     0,     0,     0,
      27,     0,     0,     0,     0,     0,     0,   155,   156,   157,
     158,   159,     0,   160,    71,    72,  -209,  -209,     0,     0,
      73,    74,    30,    75,     0,     0,     0,    32,   155,   156,
     157,   158,   159,     0,   160,     0,     0,   161,   162,     0,
       0,     0,     0,     0,     0,   163,   164,   165,   166,   155,
     156,   157,   158,   159,     0,   160,     0,     0,   161,   162,
     170,   171,     0,   172,   173,   174,   163,   164,   165,   166,
       0,     0,     0,     0,     0,     0,     0,     0,   167,   168,
     169,   170,   171,     0,   172,   173,   174,     0,   155,   156,
     157,   158,   159,     0,   160,     0,   266,   161,   162,   167,
     168,   169,   170,   171,     0,   172,   173,   174,     0,   155,
     156,   157,   158,   159,     0,   160,     0,   393,   161,   162,
       0,     0,     0,     0,     0,     0,   163,   164,   165,   166,
     155,   156,   157,   158,   159,     0,   160,     0,     0,   161,
     162,   170,   171,     0,   172,   173,   174,   163,   164,   165,
     166,     0,     0,     0,     0,     0,     0,     0,     0,   167,
     168,   169,   170,   171,     0,   172,   173,   174,     0,     0,
       0,     0,     0,     0,     0,     0,   196,     0,     0,     0,
     167,   168,   169,   170,   171,     0,   172,   173,   174,   155,
     156,   157,   158,   159,     0,   160,     0,   211,   161,   162,
       0,     0,     0,     0,     0,     0,   163,   164,   165,   166,
     155,   156,   157,   158,   159,     0,   160,     0,     0,   161,
     162,     0,     0,     0,     0,     0,     0,   163,   164,   165,
     166,     0,     0,     0,     0,     0,     0,     0,     0,   167,
     168,   169,   170,   171,     0,   172,   173,   174,     0,     0,
       0,     0,     0,     0,     0,     0,   212,     0,     0,     0,
     167,   168,   169,   170,   171,     0,   172,   173,   174,   155,
     156,   157,   158,   159,     0,   160,     0,   261,   161,   162,
       0,     0,     0,     0,     0,     0,   163,   164,   165,   166,
     155,   156,   157,   158,   159,     0,   160,     0,     0,   161,
     162,     0,     0,     0,     0,     0,     0,   163,   164,   165,
     166,     0,     0,     0,     0,     0,     0,     0,     0,   167,
     168,   169,   170,   171,     0,   172,   173,   174,     0,     0,
       0,     0,     0,     0,     0,     0,   424,     0,     0,     0,
     167,   168,   169,   170,   171,     0,   172,   173,   174,   155,
     156,   157,   158,   159,     0,   160,     0,     0,   161,   162,
       0,   155,   156,   157,   158,   159,   163,   160,   165,   166,
     161,   162,     0,   155,   156,   157,   158,   159,   163,   160,
     165,     0,   161,   162,   155,   156,   157,   158,   159,     0,
     160,     0,   165,   161,   162,     0,     0,     0,     0,   167,
     168,   169,   170,   171,     0,   172,   173,   174,     0,     0,
       0,   167,   168,   169,   170,   171,     0,   172,   173,   174,
       0,     0,     0,   167,   168,   169,   170,   171,     0,   172,
     173,   174,     0,     0,   167,   168,   169,   170,   171,     0,
     172,   173,   174,   155,   156,   157,   158,   159,     0,   160,
       0,     0,   161,   162,   155,   156,   157,   158,   159,     0,
     160,     0,     0,   161,   162,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   168,   169,   170,   171,     0,   172,
     173,   174,     0,     0,     0,     0,   169,   170,   171,     0,
     172,   173,   174
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,    69,    20,     4,     3,     2,    24,    21,    22,    65,
     141,     5,     4,   177,   178,     4,     3,    21,    22,   294,
      21,    22,     8,     5,     4,    60,     5,     4,   358,   359,
       5,    15,     5,     5,     4,     5,     4,     4,     5,     4,
     150,    25,    41,     0,     4,     5,    81,     3,    32,    60,
      80,   326,    60,     5,    41,    61,     3,     4,     5,     6,
       7,     8,     5,    10,    11,    47,    77,   177,   178,    75,
       5,    53,     5,    81,     5,    22,    70,    63,    25,    70,
      71,    72,    66,    67,   414,    41,    53,    71,    72,    73,
      74,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      70,    53,    81,    50,    51,    52,    53,    54,    81,    81,
      57,     5,   116,   277,    74,   116,    47,   281,    53,    60,
      53,   285,    53,    76,   116,    80,   110,   116,    75,    76,
      77,    61,    53,    80,    58,    59,   116,    44,    45,   116,
      81,   125,   126,    63,     5,    75,   277,     5,   116,    61,
     281,   116,   208,   209,   285,    75,   140,    69,     4,    53,
      80,    80,    69,     4,     5,     6,     7,     8,    79,    79,
      79,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,    53,   211,   212,    53,    63,    69,    39,    40,
      79,   219,    69,    75,    63,    46,   190,   191,    79,   265,
      69,   267,    53,   269,     4,     5,     6,     7,     8,    14,
      15,    16,    17,    18,    63,    20,   244,    44,    45,   247,
      44,    45,    58,    59,    75,    76,    79,   255,    75,    80,
      61,    80,    63,    80,    61,    79,    79,    79,    63,    39,
      40,    77,    69,    42,    75,    69,    46,    75,    75,    80,
     278,   279,    80,    53,   282,   283,    55,    56,   286,   287,
     288,    79,    67,    68,    79,    70,    71,    72,    79,   335,
     336,    61,    60,    80,   340,    75,    76,    61,    67,    68,
      80,    70,    71,    72,    60,    80,     3,     4,     5,     6,
       7,     8,     4,    10,    11,   323,    69,    80,    69,    49,
      75,    82,    76,    60,    63,    22,    48,   301,    25,    77,
      80,    80,     8,    69,    81,   343,   344,   345,    80,    80,
      80,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      81,   355,    80,    50,    51,    52,    53,    54,    81,     5,
      57,   355,    81,    81,   355,   339,     5,     6,     7,     8,
      76,    81,    63,    81,    69,     5,    81,   423,    75,    76,
     384,    77,    42,    80,    69,    79,     5,    80,   396,     5,
     384,    81,    81,   384,    80,    13,   383,    81,    81,    81,
      39,    40,    81,    61,    79,    60,    60,    46,    61,    81,
      81,    63,    69,    81,    53,    80,   424,   411,    12,    63,
     411,   395,    63,   410,    80,   419,   413,   421,   419,   411,
     421,   425,   411,   420,   425,    63,    63,   419,    63,   421,
     419,   411,   421,   425,   411,    81,   425,   373,    63,   419,
      63,   421,   419,   411,   421,   425,   411,   384,   425,   296,
     372,   419,   176,   421,   419,   295,   421,   425,   374,   185,
     425,     4,     5,     6,     7,     8,   362,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    42,
      -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,
      17,    18,    -1,    20,    67,    68,    23,    24,    -1,    -1,
      73,    74,    75,    76,    -1,    -1,    -1,    80,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      67,    68,    -1,    70,    71,    72,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    -1,    70,    71,    72,    -1,    14,    15,
      16,    17,    18,    -1,    20,    -1,    82,    23,    24,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    -1,    14,
      15,    16,    17,    18,    -1,    20,    -1,    82,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    67,    68,    -1,    70,    71,    72,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    -1,    70,    71,    72,    14,
      15,    16,    17,    18,    -1,    20,    -1,    81,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    -1,    70,    71,    72,    14,
      15,    16,    17,    18,    -1,    20,    -1,    81,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    -1,    70,    71,    72,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    14,    15,    16,    17,    18,    31,    20,    33,    34,
      23,    24,    -1,    14,    15,    16,    17,    18,    31,    20,
      33,    -1,    23,    24,    14,    15,    16,    17,    18,    -1,
      20,    -1,    33,    23,    24,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,    70,
      71,    72,    -1,    -1,    64,    65,    66,    67,    68,    -1,
      70,    71,    72,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,    70,
      71,    72,    -1,    -1,    -1,    -1,    66,    67,    68,    -1,
      70,    71,    72
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    84,    85,     0,    86,     3,     4,     5,     6,     7,
       8,    10,    11,    22,    25,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    50,    51,    52,    53,    54,    57,
      75,    76,    80,    87,    88,    89,    90,    91,    92,    93,
      95,    96,    97,   102,   118,   120,   121,   126,   127,   129,
     133,   139,   144,   146,   148,   153,   154,   157,   159,   160,
     163,     5,   140,   141,    69,    80,    80,    80,     5,   145,
      42,    67,    68,    73,    74,    76,    89,    93,    94,   101,
     127,   129,   133,   134,   135,   136,   137,   138,   144,   149,
     154,   157,    53,   142,   143,     4,     5,    74,    76,    88,
       4,     5,    93,    95,   127,    93,   127,    88,    94,     4,
      80,    94,   150,   151,     8,    63,    86,   119,    94,    79,
      79,    79,    44,    45,    69,    61,    75,    79,    44,    45,
      69,    79,    79,    79,    79,    79,    63,    79,    79,    79,
      61,    60,     5,    47,    53,   150,    94,    94,    63,    69,
      80,    94,    94,    94,    94,    14,    15,    16,    17,    18,
      20,    23,    24,    31,    32,    33,    34,    64,    65,    66,
      67,    68,    70,    71,    72,    61,    60,    80,    80,     4,
      69,    69,    69,    49,   122,   123,   124,    76,    94,    82,
      60,    63,    77,    77,    60,    77,    81,     5,    53,    94,
      94,     5,    53,     4,     5,    53,    94,   141,    80,    80,
      81,    81,    81,     4,     5,    70,     5,    70,     5,    81,
     140,   147,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,   143,    81,   140,   147,    81,   140,   147,
      80,     5,     5,     5,    80,    48,   125,   124,   103,   104,
     105,    81,    94,    94,     8,    80,    82,    80,    69,    80,
     150,   150,   158,    88,    88,    69,    88,    60,    81,    81,
      88,    60,    81,    81,    88,    60,    81,    81,    81,     5,
      88,    55,    56,   115,   116,   117,   106,     3,    41,   107,
      76,    63,   150,   150,     5,    47,    53,   150,    81,    81,
     152,   164,    69,   147,    88,    88,   147,    88,    88,   147,
      88,    88,    88,    81,    77,   148,   116,   107,   108,   109,
      79,    98,    94,    81,    81,    80,    80,    81,   132,    75,
      80,   161,    69,    81,    81,    81,    88,   148,    79,     5,
     111,   112,     5,   113,   114,    58,    59,   100,   130,   131,
     150,   150,   155,   128,    94,   150,    13,   165,    88,    88,
      88,    61,    60,    61,    60,     5,     6,     7,     8,    53,
      93,    99,   127,    63,    58,    59,    77,   128,   128,    81,
      81,   152,    69,    82,    81,    80,    12,   162,     5,     6,
       7,     8,    39,    40,    46,    53,   110,   112,   110,   114,
      63,    86,    99,    63,   156,     5,    53,    94,    88,    86,
      63,    86,   128,    80,    81,    86,   150,    88,    81
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
      87,    87,    87,    87,    87,    87,    88,    89,    89,    90,
      91,    92,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    95,
      95,    95,    96,    98,    97,    99,    99,    99,    99,    99,
      99,   100,   100,   100,   100,   101,   101,   101,   101,   102,
     103,   103,   105,   104,   106,   104,   108,   107,   109,   107,
     110,   110,   110,   110,   110,   110,   110,   110,   111,   111,
     112,   112,   113,   113,   114,   115,   115,   116,   116,   116,
     117,   117,   118,   119,   119,   120,   120,   121,   122,   123,
     123,   124,   125,   125,   126,   127,   127,   127,   127,   127,
     127,   128,   128,   128,   128,   130,   129,   131,   129,   132,
     129,   133,   133,   133,   133,   133,   133,   133,   133,   134,
     134,   134,   134,   134,   134,   135,   135,   136,   136,   137,
     137,   137,   137,   137,   138,   138,   138,   138,   138,   139,
     139,   140,   140,   141,   141,   142,   142,   143,   144,   145,
     145,   146,   146,   146,   146,   146,   147,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   149,   149,   149,   149,
     150,   150,   151,   151,   152,   152,   152,   153,   153,   155,
     154,   154,   154,   154,   154,   154,   156,   154,   158,   157,
     159,   159,   160,   161,   161,   162,   162,   164,   165,   163
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     2,     1,     1,     2,     2,
       2,     1,     1,     2,     2,     1,     3,     3,     6,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     0,     8,     1,     1,     1,     1,     1,
       1,     4,     3,     5,     4,     2,     2,     2,     2,     6,
       0,     1,     0,     3,     0,     4,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     1,     3,     3,     0,     1,     0,     1,     1,
       2,     3,     3,     3,     5,     3,     3,     2,     1,     1,
       2,     5,     0,     2,     4,     3,     3,     3,     3,     3,
       3,     0,     6,     3,     3,     0,     8,     0,     8,     0,
       8,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     3,     3,     1,     1,     3,     3,     3,     1,
       3,     4,     4,     4,     4,     2,     4,     5,     5,     6,
       6,     6,     6,     6,     8,     8,     4,     5,     5,     7,
       0,     1,     1,     3,     0,     4,     4,     1,     3,     0,
       8,     3,     3,     5,     5,     8,     0,    10,     0,     6,
       2,     1,     5,     0,     6,     0,     2,     0,     0,     9
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
  "\"critical\"", "\"++\"", "\"--\"", "\"null\"", "\"new\"", "\"finally\"",
  "\"catch\"", "\"try\"", "\"throw\"", "\"continue\"",
  "\"constant identifier\"", "\"class\"", "\"public\"", "\"private\"",
  "\"switch\"", "\"case\"", "\"default\"", "','", "'='", "XOR_EQUAL",
  "':'", "'|'", "'^'", "'&'", "'-'", "'+'", "'.'", "'*'", "'/'", "'%'",
  "'!'", "'~'", "'['", "'{'", "'}'", "UMINUS", "';'", "'('", "')'", "']'",
  "$accept", "program", "$@1", "statement_list", "statement", "block",
  "instantiation", "break", "continue", "critical_block", "object",
  "rvalue", "lvalue", "subscript", "switch_expr", "@2", "label",
  "case_list", "unary", "class_def", "class_attr_decl", "class_attr_list",
  "@3", "@4", "non_empty_class_attr_list", "@5", "@6", "attr_rvalue",
  "class_attr_decl_list", "class_attr_decl_impl",
  "class_attr_const_decl_list", "class_attr_const_decl_impl",
  "class_method_decl", "visibility", "class_method_list", "array",
  "key_value_list", "map", "throw", "catch", "not_empty_catch",
  "catch_impl", "finally", "try_catch_finally", "property_access",
  "mcall_chain", "mcall", "@7", "@8", "@9", "inc_dec", "comparison",
  "boolean", "logic", "arithmetic", "bitwise", "variable_decl",
  "variable_decl_list", "variable_decl_impl", "const_decl_list",
  "const_decl_impl", "assignment", "import_ident_list", "import", "vararg",
  "fdecl", "anonymous_fdecl", "call_args", "non_empty_call_args",
  "fcall_chain", "fully_qualified_name", "fully_qualified_call", "@10",
  "@11", "fcall", "@12", "return_stmt", "while", "elseif", "else", "if",
  "@13", "@14", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        84,     0,    -1,    -1,    85,    86,    -1,    -1,    86,    87,
      -1,   146,    79,    -1,   139,    79,    -1,   144,    79,    -1,
     157,    79,    -1,   129,    79,    -1,   148,    -1,   159,    79,
      -1,   163,    -1,   160,    -1,   133,    79,    -1,    88,    -1,
      92,    -1,   121,    79,    -1,    90,    79,    -1,    91,    79,
      -1,   126,    -1,   102,    -1,   154,    79,    -1,    89,    79,
      -1,    97,    -1,    76,    86,    77,    -1,     4,    69,    47,
      -1,     4,    69,    47,    80,   150,    81,    -1,    22,    -1,
      52,    -1,    43,    88,    -1,     5,    -1,    53,    -1,     8,
      -1,     6,    -1,     7,    -1,    46,    -1,    39,    -1,    40,
      -1,   120,    -1,   118,    -1,    80,    94,    81,    -1,    96,
      -1,   157,    -1,    93,    -1,   101,    -1,   137,    -1,   136,
      -1,   138,    -1,   135,    -1,   134,    -1,   144,    -1,   133,
      -1,   149,    -1,    89,    -1,   129,    -1,   154,    -1,   127,
      -1,     5,    -1,   127,    -1,    96,    -1,    95,    75,    94,
      82,    -1,    -1,    57,    80,    94,    81,    76,    98,   100,
      77,    -1,     5,    -1,    53,    -1,     8,    -1,     6,    -1,
       7,    -1,   127,    -1,    58,    99,    63,    86,    -1,    59,
      63,    86,    -1,   100,    58,    99,    63,    86,    -1,   100,
      59,    63,    86,    -1,    67,    94,    -1,    68,    94,    -1,
      73,    94,    -1,    74,    94,    -1,    54,     4,    76,   103,
     115,    77,    -1,    -1,   104,    -1,    -1,   105,   107,    79,
      -1,    -1,   104,   106,   107,    79,    -1,    -1,     3,   108,
     111,    -1,    -1,    41,   109,   113,    -1,     5,    -1,    53,
      -1,     8,    -1,     6,    -1,     7,    -1,    46,    -1,    39,
      -1,    40,    -1,   112,    -1,   111,    60,   112,    -1,     5,
      61,   110,    -1,     5,    -1,   114,    -1,   113,    60,   114,
      -1,     5,    61,   110,    -1,    -1,   117,    -1,    -1,    55,
      -1,    56,    -1,   116,   148,    -1,   117,   116,   148,    -1,
      75,   150,    82,    -1,     8,    63,    94,    -1,   119,    60,
       8,    63,    94,    -1,    76,    63,    77,    -1,    76,   119,
      77,    -1,    51,    94,    -1,   123,    -1,   124,    -1,   123,
     124,    -1,    49,    80,     5,    81,    88,    -1,    -1,    48,
      88,    -1,    50,    88,   122,   125,    -1,    93,    69,     5,
      -1,     4,    69,     5,    -1,    93,    69,    53,    -1,     4,
      69,    53,    -1,   127,    69,     5,    -1,   127,    69,    53,
      -1,    -1,   128,    69,     5,    80,   150,    81,    -1,   128,
      69,     5,    -1,   128,    69,    53,    -1,    -1,    93,    69,
       5,    80,   150,    81,   130,   128,    -1,    -1,   127,    69,
       5,    80,   150,    81,   131,   128,    -1,    -1,     4,    69,
       5,    80,   150,    81,   132,   128,    -1,    93,    44,    -1,
      93,    45,    -1,    44,    93,    -1,    45,    93,    -1,   127,
      44,    -1,   127,    45,    -1,    44,   127,    -1,    45,   127,
      -1,    94,    23,    94,    -1,    94,    24,    94,    -1,    94,
      17,    94,    -1,    94,    15,    94,    -1,    94,    16,    94,
      -1,    94,    14,    94,    -1,    94,    31,    94,    -1,    94,
      33,    94,    -1,    94,    32,    94,    -1,    94,    34,    94,
      -1,    94,    68,    94,    -1,    94,    67,    94,    -1,    94,
      70,    94,    -1,    94,    71,    94,    -1,    94,    72,    94,
      -1,    94,    66,    94,    -1,    94,    64,    94,    -1,    94,
      65,    94,    -1,    94,    20,    94,    -1,    94,    18,    94,
      -1,     3,   140,    -1,    41,   142,    -1,   141,    -1,   140,
      60,   141,    -1,     5,    61,    94,    -1,     5,    -1,   143,
      -1,   142,    60,   143,    -1,    53,    61,    94,    -1,    95,
      61,    94,    -1,     5,    -1,   145,    69,     5,    -1,    25,
     145,    69,    70,    -1,    25,   145,    63,    70,    -1,    25,
     145,    63,     5,    -1,    25,   145,    63,     4,    -1,    25,
     145,    -1,     5,    69,    69,    69,    -1,    42,     5,    80,
      81,    88,    -1,    42,     4,    80,    81,    88,    -1,    42,
      74,     4,    80,    81,    88,    -1,    42,     5,    80,   147,
      81,    88,    -1,    42,     4,    80,   147,    81,    88,    -1,
      42,     5,    80,   140,    81,    88,    -1,    42,     4,    80,
     140,    81,    88,    -1,    42,     5,    80,   140,    60,   147,
      81,    88,    -1,    42,     4,    80,   140,    60,   147,    81,
      88,    -1,    42,    80,    81,    88,    -1,    42,    80,   147,
      81,    88,    -1,    42,    80,   140,    81,    88,    -1,    42,
      80,   140,    60,   147,    81,    88,    -1,    -1,   151,    -1,
      94,    -1,   151,    60,    94,    -1,    -1,   152,    80,   150,
      81,    -1,   152,    75,    94,    82,    -1,     5,    -1,   153,
      63,     5,    -1,    -1,   153,    63,     5,    80,   150,    81,
     155,   152,    -1,   153,    63,    53,    -1,   153,    63,     5,
      -1,   153,    63,     4,    69,    53,    -1,   153,    63,     4,
      69,    47,    -1,   153,    63,     4,    69,    47,    80,   150,
      81,    -1,    -1,   153,    63,     4,    69,     5,    80,   150,
      81,   156,   128,    -1,    -1,     5,    80,   150,    81,   158,
     152,    -1,    38,    94,    -1,    38,    -1,    10,    80,    94,
      81,    88,    -1,    -1,   161,    13,    80,    94,    81,    88,
      -1,    -1,    12,    88,    -1,    -1,    -1,    11,    80,    94,
      81,    88,   164,   161,   165,   162,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     8,    11,    14,    17,    20,
      23,    26,    28,    31,    33,    35,    38,    40,    42,    45,
      48,    51,    53,    55,    58,    61,    63,    67,    71,    78,
      80,    82,    85,    87,    89,    91,    93,    95,    97,    99,
     101,   103,   105,   109,   111,   113,   115,   117,   119,   121,
     123,   125,   127,   129,   131,   133,   135,   137,   139,   141,
     143,   145,   147,   152,   153,   162,   164,   166,   168,   170,
     172,   174,   179,   183,   189,   194,   197,   200,   203,   206,
     213,   214,   216,   217,   221,   222,   227,   228,   232,   233,
     237,   239,   241,   243,   245,   247,   249,   251,   253,   255,
     259,   263,   265,   267,   271,   275,   276,   278,   279,   281,
     283,   286,   290,   294,   298,   304,   308,   312,   315,   317,
     319,   322,   328,   329,   332,   337,   341,   345,   349,   353,
     357,   361,   362,   369,   373,   377,   378,   387,   388,   397,
     398,   407,   410,   413,   416,   419,   422,   425,   428,   431,
     435,   439,   443,   447,   451,   455,   459,   463,   467,   471,
     475,   479,   483,   487,   491,   495,   499,   503,   507,   511,
     514,   517,   519,   523,   527,   529,   531,   535,   539,   543,
     545,   549,   554,   559,   564,   569,   572,   577,   583,   589,
     596,   603,   610,   617,   624,   633,   642,   647,   653,   659,
     667,   668,   670,   672,   676,   677,   682,   687,   689,   693,
     694,   703,   707,   711,   717,   723,   732,   733,   744,   745,
     752,   755,   757,   763,   764,   771,   772,   775,   776,   777
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   215,   215,   215,   219,   220,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   247,   251,   252,   256,
     260,   265,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   308,
     309,   310,   314,   318,   318,   322,   323,   324,   325,   326,
     327,   331,   332,   333,   334,   338,   339,   340,   341,   345,
     349,   350,   354,   354,   355,   355,   359,   359,   360,   360,
     364,   365,   366,   367,   368,   369,   370,   371,   375,   376,
     380,   381,   385,   386,   390,   394,   395,   399,   400,   401,
     405,   406,   410,   414,   415,   419,   420,   424,   428,   432,
     433,   437,   441,   442,   446,   450,   451,   452,   453,   454,
     455,   459,   460,   461,   462,   466,   466,   467,   467,   468,
     468,   472,   473,   474,   475,   476,   477,   478,   479,   483,
     484,   485,   486,   487,   488,   492,   493,   497,   498,   502,
     503,   504,   505,   506,   510,   511,   512,   513,   514,   518,
     519,   523,   524,   528,   529,   533,   534,   538,   542,   546,
     547,   551,   552,   553,   554,   555,   559,   563,   565,   567,
     569,   571,   573,   575,   577,   579,   584,   586,   588,   590,
     595,   596,   600,   601,   605,   606,   607,   611,   612,   616,
     616,   617,   618,   619,   620,   621,   622,   622,   626,   626,
     630,   631,   635,   639,   641,   646,   647,   651,   652,   651
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
  const int Parser::yylast_ = 1022;
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

