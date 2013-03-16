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

  case 28:

    { (yyval.block) = (yysemantic_stack_[(3) - (2)].block); }
    break;

  case 29:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(3) - (1)].type), NULL, yyloc); }
    break;

  case 30:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (5)].narray),   yyloc); }
    break;

  case 31:

    { (yyval.break_) = new ast::Break(yyloc); }
    break;

  case 32:

    { (yyval.continue_) = new ast::Continue(yyloc); }
    break;

  case 33:

    {
#ifndef CLEVER_THREADS
		error(yyloc, "Cannot use critical block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.criticalblock) = new ast::CriticalBlock((yysemantic_stack_[(2) - (2)].block), yyloc);
#endif
	}
    break;

  case 44:

    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 54:

    { (yysemantic_stack_[(1) - (1)].assignment)->setUseResult(); }
    break;

  case 62:

    { (yysemantic_stack_[(1) - (1)].property)->setWriteMode(); }
    break;

  case 64:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 65:

    { (yyval.node) = new ast::Switch((yysemantic_stack_[(5) - (3)].node), yyloc); }
    break;

  case 66:

    { (yyval.switch_) = (yysemantic_stack_[(8) - (7)].switch_); }
    break;

  case 73:

    { (yysemantic_stack_[(4) - (0)].switch_)->addCase((yysemantic_stack_[(4) - (2)].node), (yysemantic_stack_[(4) - (4)].block)); (yyval.switch_) = (yysemantic_stack_[(4) - (0)].switch_); }
    break;

  case 74:

    { (yysemantic_stack_[(3) - (0)].switch_)->addCase(NULL, (yysemantic_stack_[(3) - (3)].block)); (yyval.switch_) = (yysemantic_stack_[(3) - (0)].switch_);     }
    break;

  case 75:

    { (yysemantic_stack_[(5) - (0)].switch_)->addCase((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block)); (yyval.switch_) = (yysemantic_stack_[(5) - (0)].switch_); }
    break;

  case 76:

    { (yysemantic_stack_[(4) - (0)].switch_)->addCase(NULL, (yysemantic_stack_[(4) - (4)].block)); (yyval.switch_) = (yysemantic_stack_[(4) - (0)].switch_);     }
    break;

  case 77:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 78:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 79:

    { (yyval.node) = new ast::Boolean(ast::Boolean::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 80:

    { (yyval.node) = new ast::Bitwise(ast::Bitwise::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 81:

    { (yyval.class_) = new ast::ClassDef((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 82:

    { (yyval.narray) = NULL; }
    break;

  case 84:

    { (yyval.narray) = new ast::NodeArray(yyloc); }
    break;

  case 85:

    { (yyval.narray) = (yysemantic_stack_[(3) - (1)].narray); }
    break;

  case 86:

    { (yyval.narray) = (yysemantic_stack_[(1) - (1)].narray); }
    break;

  case 88:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 90:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 100:

    { (yysemantic_stack_[(1) - (0)].narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 101:

    { (yysemantic_stack_[(3) - (0)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 102:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), false, yyloc); }
    break;

  case 103:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(1) - (1)].ident), NULL, false, yyloc);     }
    break;

  case 104:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 105:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 106:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), true, yyloc);   }
    break;

  case 107:

    { (yyval.narray) = NULL; }
    break;

  case 109:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 110:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 111:

    { (yyval.flags) = ast::PRIVATE; }
    break;

  case 112:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(2) - (2)].fdecl)); (yysemantic_stack_[(2) - (2)].fdecl)->setVisibility((yysemantic_stack_[(2) - (1)].flags)); }
    break;

  case 113:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].fdecl)); (yysemantic_stack_[(3) - (3)].fdecl)->setVisibility((yysemantic_stack_[(3) - (2)].flags)); }
    break;

  case 114:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 115:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 116:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 117:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 118:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 119:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 121:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 122:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 123:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 124:

    { (yyval.block) = NULL; }
    break;

  case 125:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 126:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
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

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 131:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 132:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 133:

    { (yyval.mcall) = (yysemantic_stack_[(0) - (0)].mcall); }
    break;

  case 134:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (0)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 135:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 136:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); (yyval.property)->setStatic(); }
    break;

  case 137:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 138:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 139:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 140:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 141:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 142:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 143:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 144:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 145:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 146:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 147:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].property)->setWriteMode(); }
    break;

  case 148:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].property)->setWriteMode(); }
    break;

  case 149:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].property)->setWriteMode(); }
    break;

  case 150:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].property)->setWriteMode(); }
    break;

  case 151:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 152:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 153:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 154:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 155:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 156:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 157:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 158:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 159:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 160:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 161:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 162:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 163:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 164:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 165:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 166:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 167:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 168:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 169:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 170:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 171:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 172:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 173:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 174:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 175:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 176:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 177:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 178:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 179:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 180:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 181:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 182:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 183:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 184:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 185:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 186:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 187:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 188:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 189:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 190:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 191:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 192:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 193:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 194:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 195:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 196:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 197:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 198:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 199:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 200:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 201:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 202:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 203:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 204:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 205:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 206:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 207:

    { (yyval.narray) = NULL; }
    break;

  case 209:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 210:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 211:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 212:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 213:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 215:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 216:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 217:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 218:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 219:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 220:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 221:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 222:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 223:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 224:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 225:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 226:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 227:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 228:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 229:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 230:

    { (yyval.narray) = NULL; }
    break;

  case 233:

    { (yyval.node) = NULL;     }
    break;

  case 234:

    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); }
    break;

  case 236:

    { (yyval.for_loop) = new ast::For((yysemantic_stack_[(9) - (3)].narray), (yysemantic_stack_[(9) - (5)].node), (yysemantic_stack_[(9) - (7)].narray), (yysemantic_stack_[(9) - (9)].block), yyloc); }
    break;

  case 238:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 239:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 240:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 241:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 242:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 243:

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
  const short int Parser::yypact_ninf_ = -346;
  const short int
  Parser::yypact_[] =
  {
      -346,    47,  -346,  -346,   584,    76,   -10,   171,  -346,  -346,
    -346,    -8,     8,    92,  -346,    93,   382,  -346,  -346,    52,
      16,    51,    11,    11,  -346,    51,   382,  -346,  -346,   172,
     127,   382,   382,   382,   382,   382,     5,   382,  -346,  -346,
     129,   130,   139,  -346,   119,   197,   303,   308,  -346,  -346,
    -346,  -346,  -346,   143,  -346,   296,   154,   164,  -346,  -346,
    -346,   173,  -346,   174,   177,   178,  -346,  -346,   153,   179,
     180,   187,  -346,  -346,  -346,   165,   189,  -346,    50,   382,
     234,   382,   382,  -346,   104,   191,     5,  -346,   197,  -346,
    -346,  -346,  -346,  -346,  -346,   211,   217,  -346,   201,   202,
     279,    18,  -346,  -346,   222,   144,   223,   218,   121,   223,
     121,   237,   197,   220,   382,  -346,  -346,  -346,  -346,   197,
     215,   238,   240,   227,   506,    25,   732,  -346,  -346,  -346,
    -346,  -346,    21,   382,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   382,   382,
    -346,  -346,  -346,    53,  -346,  -346,  -346,  -346,  -346,  -346,
      41,  -346,  -346,  -346,   382,    76,   225,   226,  -346,   219,
    -346,   238,   232,   753,   812,    48,    49,   382,    52,    19,
      20,   239,   113,    51,     2,   258,    61,    62,    64,   262,
     270,   237,  -346,    67,   833,  -346,   382,   382,  -346,  -346,
     312,  -346,  -346,   263,  -346,   711,   711,   711,   711,   245,
     245,   396,   396,   984,   913,   995,   972,  1006,  1065,   630,
      54,    54,  -346,  -346,  -346,   972,   972,   972,   972,   972,
     972,   651,   264,  -346,   276,    -7,  -346,   197,  -346,   382,
     382,  -346,   382,    51,    51,  -346,  -346,  -346,  -346,  -346,
     197,  -346,    51,   105,   265,    51,   106,   266,   267,   280,
    -346,   347,    51,    51,  -346,  -346,  -346,   348,    51,  -346,
    -346,   137,    68,    81,   278,   197,   197,   292,   382,  -346,
     382,    60,   382,   275,   277,  -346,   197,   281,  -346,  -346,
    -346,   347,    51,    51,  -346,   347,    51,    51,    51,   293,
     286,  -346,  -346,   289,  -346,  -346,  -346,   284,   330,   137,
      81,  -346,  -346,   295,  -346,   382,   294,   298,   297,   300,
    -346,   301,  -346,  -346,   170,   382,  -346,   304,  -346,  -346,
     310,  -346,  -346,  -346,  -346,    51,    51,  -346,    30,  -346,
     330,   302,   371,   388,  -346,   147,   197,  -346,  -346,   382,
     382,  -346,  -346,   382,   382,  -346,   313,   383,    51,    51,
    -346,  -346,  -346,  -346,   337,   339,  -346,   340,   342,  -346,
      36,   343,   101,  -346,  -346,   319,   322,  -346,   336,   672,
     326,    51,   329,   403,  -346,  -346,   480,   371,   480,   388,
     114,   355,   360,   362,   366,   223,   367,   141,  -346,    36,
     368,  -346,   336,   336,  -346,  -346,   170,   118,  -346,  -346,
    -346,   382,    51,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,   584,   374,  -346,
    -346,   358,  -346,   892,  -346,   584,  -346,   584,   336,   382,
      51,   584,   359,  -346,  -346
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    34,    37,    38,
      36,     0,     0,     0,    31,     0,   228,    40,    41,     0,
       0,     0,     0,     0,    39,     0,     0,    32,    35,     0,
       0,     0,     0,     0,     0,   207,     4,     0,     5,    17,
      57,     0,     0,    18,    47,     0,     0,    45,    26,    48,
      23,    43,    42,     0,    22,    60,    58,    55,    53,    52,
      50,    49,    51,     0,    54,     0,    11,    56,     0,    59,
      46,     0,    14,    15,    13,   181,   176,   178,     0,   207,
     230,     0,     0,   186,   192,     0,     0,    57,   227,    58,
      55,    49,    54,    59,    46,     0,   177,   182,     0,     0,
       0,     0,     4,    33,     0,    34,   145,     0,   149,   146,
     150,     0,   119,     0,     0,    77,    78,    79,    80,   209,
       0,   208,     0,     0,     0,     0,     0,    25,    20,    21,
     143,   144,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,   147,   148,     0,    10,    16,    27,     7,     8,     6,
       0,    24,     9,    12,     0,     0,   128,    29,   130,     0,
     231,   232,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   181,     0,     0,     0,     0,     0,     0,     0,
     124,   120,   121,    82,     0,   114,     0,     0,   117,    28,
       0,   118,    44,   127,   129,   156,   154,   155,   153,   175,
     174,   151,   152,   157,   159,   158,   160,   172,   173,   171,
     162,   161,   163,   164,   165,   166,   168,   169,   167,   170,
     185,     0,   131,   132,     0,   219,   218,   180,   179,   207,
     207,   225,   233,     0,     0,   191,   190,   189,   187,   188,
     184,   183,     0,     0,     0,     0,     0,     0,     0,     0,
     203,     0,     0,     0,   128,   127,   131,     0,     0,   126,
     122,   107,    83,     0,     0,   210,   115,     0,   207,    64,
     207,     0,   207,     0,     0,   211,   234,     0,   229,   241,
     195,     0,     0,     0,   194,     0,     0,     0,     0,     0,
       0,   205,   204,     0,   125,   110,   111,     0,     0,   108,
       0,    88,    90,     0,    65,     0,     0,     0,     0,   221,
     220,     0,   141,    30,   226,   207,   237,     0,   200,   198,
       0,   199,   197,   196,   193,     0,     0,    81,     0,   112,
       0,     0,     0,     0,    85,     0,   116,   137,   139,   207,
     207,   216,   133,     0,   207,   235,     0,   242,     0,     0,
     206,   123,   113,    87,   103,    89,   100,     0,    91,   104,
       0,     0,     0,   133,   133,     0,     0,   211,   142,     0,
       0,     0,     0,   239,   202,   201,     0,     0,     0,     0,
      34,    37,    38,    36,    35,     0,     0,    62,     4,     0,
       0,    66,   138,   140,   223,   222,   217,     0,   213,   212,
     236,     0,     0,   243,    92,    95,    96,    94,    98,    99,
      97,    93,   102,   101,   106,   105,     4,    74,     0,     4,
     133,   135,   136,     0,   240,    73,     4,    76,   224,   207,
       0,    75,     0,   238,   134
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -346,  -346,  -346,     0,  -346,   -18,    -3,  -346,  -346,  -346,
     -17,    -4,   -14,  -346,  -346,  -346,    42,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,   125,  -346,  -346,    55,  -346,    63,
    -346,    66,  -346,   133,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,   253,  -346,  -346,   -12,  -345,    32,  -346,  -346,  -346,
      33,  -346,  -346,  -346,    44,  -346,   379,   -97,  -143,  -346,
     273,    45,  -346,  -346,  -110,  -287,  -346,   -65,   391,    85,
    -346,    56,  -346,  -346,    57,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   124,    38,    39,    87,    41,    42,    43,
      44,   119,    46,    47,    48,   355,   406,   382,    49,    50,
     281,   282,   283,   320,   323,   352,   353,   432,   375,   376,
     378,   379,   317,   318,   319,    51,   125,    52,    53,   200,
     201,   202,   279,    54,    55,   388,    89,   383,   384,   362,
      90,    58,    59,    60,    91,    62,    63,    76,    77,    96,
      97,    92,    84,    65,   195,    66,    67,   120,   121,   334,
      68,    93,   387,   440,    94,   295,    71,    72,   182,   297,
     366,    73,   367,   423,    74,   336,   393
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -216;
  const short int
  Parser::yytable_[] =
  {
        45,    40,     4,   103,   194,   106,   109,   111,   107,   107,
     108,   110,    88,   122,   179,   104,   105,     8,     9,    10,
      98,    99,   112,   192,   192,   192,   213,   115,   116,   117,
     118,   349,   248,   126,    98,    99,    56,    57,   412,   413,
     104,   400,   401,   402,   403,   244,   245,     3,    61,    64,
      17,    18,   255,   256,   258,   176,  -215,    24,   242,    78,
      69,    70,   271,   372,    28,   328,   274,   275,   123,   276,
     -84,   -86,    80,   292,   214,    17,    18,   183,   184,   264,
     267,    75,    24,   272,   321,   210,    35,    86,    81,   404,
     100,    37,   263,   266,   246,   448,   101,   177,    83,   193,
     262,   265,   211,   178,   100,    95,   243,   329,   -84,   -86,
     204,    35,    86,   330,   178,   214,    37,   243,   257,   259,
      45,    40,   322,   441,   150,   151,   152,   102,   248,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,    56,    57,   248,   409,
     410,   310,   248,   130,   131,   301,   305,   185,    61,    64,
     247,   442,    82,   186,   174,   270,   113,   -67,   411,  -109,
      69,    70,   269,   260,   293,   294,   302,   306,   132,   -61,
     198,   337,   315,   316,    79,   340,   -62,   -61,   -61,   -61,
     -61,   -61,   285,   286,   -72,   380,   381,   114,   127,   128,
     198,   133,   134,   135,   136,   137,   170,   138,   129,   -61,
     139,   140,   160,   326,    79,   327,   174,   331,   141,   142,
     143,   144,   -61,   164,  -214,   298,   299,     5,     6,     7,
       8,     9,    10,   165,   300,   363,   -61,   304,   296,   175,
     364,    79,   166,   167,   311,   312,   168,   169,   171,   172,
     314,   145,   146,   147,   148,   149,   173,   150,   151,   152,
     365,   101,   187,    17,    18,    19,    85,   188,    22,    23,
      24,   189,   190,   191,   338,   339,   199,    28,   341,   342,
     343,   196,   197,   159,   385,   386,   203,   205,   206,   390,
     251,    31,    32,   207,   208,   249,   250,    33,    34,    35,
      86,   252,   148,   149,    37,   150,   151,   152,   278,   268,
     287,   356,   -62,   -62,   -62,   -62,   -62,   370,   371,   153,
     154,   155,   156,   157,   -63,   -63,   -63,   -63,   -63,   273,
     161,   162,   277,   288,   290,   291,   303,   307,   308,   309,
     394,   395,   192,   313,   324,   325,   332,   -62,   333,   389,
     335,   347,   344,   405,   158,   163,   107,   345,   407,   -63,
     346,   -62,   348,   420,   354,   357,   374,   359,   159,   358,
     360,   373,   361,   -63,   452,   368,     6,     7,     8,     9,
      10,   369,   405,   377,   391,   107,   392,   407,   396,   397,
     414,   398,   399,   415,   444,   417,   408,   419,   437,   421,
     133,   134,   135,   136,   137,   422,   138,   443,   -70,  -216,
    -216,    17,    18,   -71,    85,   -69,    22,    23,    24,   -68,
     436,   439,   453,    45,    40,    28,   445,   446,   449,   447,
     454,    45,    40,    45,    40,   351,   451,    45,    40,    31,
      32,   438,   350,   434,   280,    33,    34,    35,    86,   180,
     433,   261,    37,   148,   149,   435,   150,   151,   152,    56,
      57,   181,   416,     0,     0,     0,     0,    56,    57,    56,
      57,    61,    64,    56,    57,   424,   425,   426,   427,    61,
      64,    61,    64,    69,    70,    61,    64,     0,     0,     0,
       0,    69,    70,    69,    70,     0,     0,    69,    70,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,   428,
     429,     0,     0,     0,     0,     0,   430,     0,    14,     0,
       0,    15,     0,   431,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,     0,     0,    25,    26,    27,    28,
      29,     0,     0,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,     0,     0,     0,    33,
      34,    35,    36,   209,     0,     0,    37,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    14,     0,     0,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     0,     0,     0,    25,    26,    27,    28,    29,     0,
       0,    30,     0,     0,   133,   134,   135,   136,   137,     0,
     138,    31,    32,   139,   140,     0,     0,    33,    34,    35,
      36,     0,     0,     0,    37,   133,   134,   135,   136,   137,
       0,   138,     0,     0,   139,   140,     0,     0,     0,     0,
       0,     0,   141,   142,   143,   144,   133,   134,   135,   136,
     137,     0,   138,     0,     0,   139,   140,   148,   149,     0,
     150,   151,   152,   141,   142,   143,   144,     0,     0,     0,
       0,     0,     0,     0,     0,   145,   146,   147,   148,   149,
       0,   150,   151,   152,     0,  -216,  -216,  -216,  -216,   137,
       0,   138,     0,   289,     0,     0,   145,   146,   147,   148,
     149,     0,   150,   151,   152,     0,   133,   134,   135,   136,
     137,     0,   138,     0,   418,   139,   140,     0,     0,     0,
       0,     0,     0,   141,   142,   143,   144,   133,   134,   135,
     136,   137,     0,   138,     0,     0,   139,   140,   148,   149,
       0,   150,   151,   152,   141,   142,   143,   144,     0,     0,
       0,     0,     0,     0,     0,     0,   145,   146,   147,   148,
     149,     0,   150,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,   212,     0,     0,     0,   145,   146,   147,
     148,   149,     0,   150,   151,   152,   133,   134,   135,   136,
     137,     0,   138,     0,   253,   139,   140,     0,     0,     0,
       0,     0,     0,   141,   142,   143,   144,   133,   134,   135,
     136,   137,     0,   138,     0,     0,   139,   140,     0,     0,
       0,     0,     0,     0,   141,   142,   143,   144,     0,     0,
       0,     0,     0,     0,     0,     0,   145,   146,   147,   148,
     149,     0,   150,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,   254,     0,     0,     0,   145,   146,   147,
     148,   149,     0,   150,   151,   152,   133,   134,   135,   136,
     137,     0,   138,     0,   284,   139,   140,     0,     0,     0,
       0,     0,     0,   141,   142,   143,   144,   133,   134,   135,
     136,   137,     0,   138,     0,     0,   139,   140,     0,     0,
       0,     0,     0,     0,   141,     0,   143,   144,     0,     0,
       0,     0,     0,     0,     0,     0,   145,   146,   147,   148,
     149,     0,   150,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,   450,     0,     0,     0,   145,   146,   147,
     148,   149,     0,   150,   151,   152,   133,   134,   135,   136,
     137,     0,   138,     0,     0,   139,   140,     0,   133,   134,
     135,   136,   137,   141,   138,   143,     0,   139,   140,   133,
     134,   135,   136,   137,     0,   138,     0,   143,   139,   140,
     133,   134,   135,   136,   137,     0,   138,     0,     0,   139,
     140,     0,     0,     0,     0,     0,   145,   146,   147,   148,
     149,     0,   150,   151,   152,     0,     0,     0,   145,   146,
     147,   148,   149,     0,   150,   151,   152,     0,     0,   145,
     146,   147,   148,   149,     0,   150,   151,   152,     0,     0,
       0,   146,   147,   148,   149,     0,   150,   151,   152,   133,
     134,   135,   136,   137,     0,   138,     0,     0,   139,   140,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   147,   148,   149,     0,   150,   151,   152
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     2,    21,   101,    22,    23,    25,    22,    23,
      22,    23,    16,     8,    79,     4,     5,     6,     7,     8,
       4,     5,    26,     5,     5,     5,     5,    31,    32,    33,
      34,   318,   175,    37,     4,     5,     4,     4,   383,   384,
       4,     5,     6,     7,     8,     4,     5,     0,     4,     4,
      39,    40,     4,     5,     5,     5,    63,    46,     5,    69,
       4,     4,    60,   350,    53,     5,     5,     5,    63,     5,
       3,     3,    80,    80,    53,    39,    40,    81,    82,   189,
     190,     5,    46,    81,     3,    60,    75,    76,    80,    53,
      74,    80,   189,   190,    53,   440,    80,    47,     5,    81,
      81,    81,    77,    53,    74,    53,    53,    47,    41,    41,
     114,    75,    76,    53,    53,    53,    80,    53,    70,    70,
     124,   124,    41,     5,    70,    71,    72,    76,   271,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   124,   124,   301,    58,
      59,   271,   305,    44,    45,    60,    60,    63,   124,   124,
     174,    53,    80,    69,    61,   193,     4,    63,    77,    42,
     124,   124,    69,   187,   249,   250,    81,    81,    69,    75,
      69,   301,    55,    56,    80,   305,    75,    26,    27,    28,
      29,    30,   206,   207,    63,    58,    59,    80,    79,    79,
      69,    14,    15,    16,    17,    18,    63,    20,    79,    75,
      23,    24,    79,   288,    80,   290,    61,   292,    31,    32,
      33,    34,    61,    79,    63,   253,   254,     3,     4,     5,
       6,     7,     8,    79,   262,    75,    75,   265,   252,    60,
      80,    80,    79,    79,   272,   273,    79,    79,    79,    79,
     278,    64,    65,    66,    67,    68,    79,    70,    71,    72,
     335,    80,    61,    39,    40,    41,    42,    60,    44,    45,
      46,    80,    80,     4,   302,   303,    49,    53,   306,   307,
     308,    69,    69,    75,   359,   360,    76,    82,    60,   364,
      81,    67,    68,    63,    77,    80,    80,    73,    74,    75,
      76,    79,    67,    68,    80,    70,    71,    72,    48,    80,
       8,   325,    26,    27,    28,    29,    30,   345,   346,    26,
      27,    28,    29,    30,    26,    27,    28,    29,    30,    81,
      44,    45,    80,    80,    80,    69,    81,    81,    81,    69,
     368,   369,     5,     5,    76,    63,    81,    61,    81,   363,
      79,    77,    69,   380,    61,    69,   380,    81,   380,    61,
      81,    75,    42,   391,    79,    81,     5,    80,    75,    81,
      80,    79,    81,    75,   449,    81,     4,     5,     6,     7,
       8,    81,   409,     5,    81,   409,    13,   409,    61,    60,
      81,    61,    60,    81,   422,    69,    63,    81,   408,    80,
      14,    15,    16,    17,    18,    12,    20,   421,    63,    23,
      24,    39,    40,    63,    42,    63,    44,    45,    46,    63,
      63,    63,   450,   437,   437,    53,   436,    63,    80,   439,
      81,   445,   445,   447,   447,   320,   446,   451,   451,    67,
      68,   409,   319,   398,   201,    73,    74,    75,    76,    80,
     397,   188,    80,    67,    68,   399,    70,    71,    72,   437,
     437,    80,   387,    -1,    -1,    -1,    -1,   445,   445,   447,
     447,   437,   437,   451,   451,     5,     6,     7,     8,   445,
     445,   447,   447,   437,   437,   451,   451,    -1,    -1,    -1,
      -1,   445,   445,   447,   447,    -1,    -1,   451,   451,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    39,
      40,    -1,    -1,    -1,    -1,    -1,    46,    -1,    22,    -1,
      -1,    25,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    77,    -1,    -1,    80,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    50,    51,    52,    53,    54,    -1,
      -1,    57,    -1,    -1,    14,    15,    16,    17,    18,    -1,
      20,    67,    68,    23,    24,    -1,    -1,    73,    74,    75,
      76,    -1,    -1,    -1,    80,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    67,    68,    -1,
      70,    71,    72,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    70,    71,    72,    -1,    14,    15,    16,    17,    18,
      -1,    20,    -1,    82,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    70,    71,    72,    -1,    14,    15,    16,    17,
      18,    -1,    20,    -1,    82,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    67,    68,
      -1,    70,    71,    72,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    -1,    70,    71,    72,    14,    15,    16,    17,
      18,    -1,    20,    -1,    81,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    -1,    70,    71,    72,    14,    15,    16,    17,
      18,    -1,    20,    -1,    81,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    -1,    70,    71,    72,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    14,    15,
      16,    17,    18,    31,    20,    33,    -1,    23,    24,    14,
      15,    16,    17,    18,    -1,    20,    -1,    33,    23,    24,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    70,    71,    72,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    -1,    70,    71,    72,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    65,    66,    67,    68,    -1,    70,    71,    72,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    -1,    70,    71,    72
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    84,    85,     0,    86,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    22,    25,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    50,    51,    52,    53,    54,
      57,    67,    68,    73,    74,    75,    76,    80,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,   101,
     102,   118,   120,   121,   126,   127,   129,   133,   134,   135,
     136,   137,   138,   139,   144,   146,   148,   149,   153,   154,
     157,   159,   160,   164,   167,     5,   140,   141,    69,    80,
      80,    80,    80,     5,   145,    42,    76,    89,    94,   129,
     133,   137,   144,   154,   157,    53,   142,   143,     4,     5,
      74,    80,    76,    88,     4,     5,    93,    95,   127,    93,
     127,    88,    94,     4,    80,    94,    94,    94,    94,    94,
     150,   151,     8,    63,    86,   119,    94,    79,    79,    79,
      44,    45,    69,    14,    15,    16,    17,    18,    20,    23,
      24,    31,    32,    33,    34,    64,    65,    66,    67,    68,
      70,    71,    72,    26,    27,    28,    29,    30,    61,    75,
      79,    44,    45,    69,    79,    79,    79,    79,    79,    79,
      63,    79,    79,    79,    61,    60,     5,    47,    53,   150,
     139,   151,   161,    94,    94,    63,    69,    61,    60,    80,
      80,     4,     5,    81,   140,   147,    69,    69,    69,    49,
     122,   123,   124,    76,    94,    82,    60,    63,    77,    77,
      60,    77,    81,     5,    53,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,     5,    53,     4,     5,    53,    94,   141,    80,
      80,    81,    79,    81,    81,     4,     5,    70,     5,    70,
      94,   143,    81,   140,   147,    81,   140,   147,    80,    69,
      88,    60,    81,    81,     5,     5,     5,    80,    48,   125,
     124,   103,   104,   105,    81,    94,    94,     8,    80,    82,
      80,    69,    80,   150,   150,   158,    94,   162,    88,    88,
      88,    60,    81,    81,    88,    60,    81,    81,    81,    69,
     147,    88,    88,     5,    88,    55,    56,   115,   116,   117,
     106,     3,    41,   107,    76,    63,   150,   150,     5,    47,
      53,   150,    81,    81,   152,    79,   168,   147,    88,    88,
     147,    88,    88,    88,    69,    81,    81,    77,    42,   148,
     116,   107,   108,   109,    79,    98,    94,    81,    81,    80,
      80,    81,   132,    75,    80,   150,   163,   165,    81,    81,
      88,    88,   148,    79,     5,   111,   112,     5,   113,   114,
      58,    59,   100,   130,   131,   150,   150,   155,   128,    94,
     150,    81,    13,   169,    88,    88,    61,    60,    61,    60,
       5,     6,     7,     8,    53,    93,    99,   127,    63,    58,
      59,    77,   128,   128,    81,    81,   152,    69,    82,    81,
      88,    80,    12,   166,     5,     6,     7,     8,    39,    40,
      46,    53,   110,   112,   110,   114,    63,    86,    99,    63,
     156,     5,    53,    94,    88,    86,    63,    86,   128,    80,
      81,    86,   150,    88,    81
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
      87,    87,    87,    87,    87,    87,    87,    87,    88,    89,
      89,    90,    91,    92,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    95,    95,    95,    96,    98,    97,    99,    99,    99,
      99,    99,    99,   100,   100,   100,   100,   101,   101,   101,
     101,   102,   103,   103,   105,   104,   106,   104,   108,   107,
     109,   107,   110,   110,   110,   110,   110,   110,   110,   110,
     111,   111,   112,   112,   113,   113,   114,   115,   115,   116,
     116,   116,   117,   117,   118,   119,   119,   120,   120,   121,
     122,   123,   123,   124,   125,   125,   126,   127,   127,   127,
     127,   127,   127,   128,   128,   128,   128,   130,   129,   131,
     129,   132,   129,   133,   133,   133,   133,   133,   133,   133,
     133,   134,   134,   134,   134,   134,   134,   135,   135,   136,
     136,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   138,   138,   138,   138,   138,   139,   139,   140,   140,
     141,   141,   142,   142,   143,   144,   145,   145,   146,   146,
     146,   146,   146,   147,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   149,   149,   149,   149,   150,   150,   151,
     151,   152,   152,   152,   153,   153,   155,   154,   154,   154,
     154,   154,   154,   156,   154,   158,   157,   159,   159,   160,
     161,   161,   161,   162,   162,   163,   164,   165,   165,   166,
     166,   168,   169,   167
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     1,     2,     1,     1,     2,
       2,     2,     1,     1,     2,     2,     1,     2,     3,     3,
       6,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     0,     8,     1,     1,     1,
       1,     1,     1,     4,     3,     5,     4,     2,     2,     2,
       2,     6,     0,     1,     0,     3,     0,     4,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     1,     3,     3,     0,     1,     0,
       1,     1,     2,     3,     3,     3,     5,     3,     3,     2,
       1,     1,     2,     5,     0,     2,     4,     3,     3,     3,
       3,     3,     3,     0,     6,     3,     3,     0,     8,     0,
       8,     0,     8,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     3,
       3,     1,     1,     3,     3,     3,     1,     3,     4,     4,
       4,     4,     2,     4,     5,     5,     6,     6,     6,     6,
       6,     8,     8,     4,     5,     5,     7,     0,     1,     1,
       3,     0,     4,     4,     1,     3,     0,     8,     3,     3,
       5,     5,     8,     0,    10,     0,     6,     2,     1,     5,
       0,     1,     1,     0,     1,     1,     9,     0,     6,     0,
       2,     0,     0,     9
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
  "@11", "fcall", "@12", "return_stmt", "while", "for_expr_1",
  "for_expr_2", "for_expr_3", "for", "elseif", "else", "if", "@13", "@14", 0
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
      -1,   167,    -1,   160,    -1,   164,    -1,   133,    79,    -1,
      88,    -1,    92,    -1,   121,    79,    -1,    90,    79,    -1,
      91,    79,    -1,   126,    -1,   102,    -1,   154,    79,    -1,
      89,    79,    -1,    97,    -1,   137,    79,    -1,    76,    86,
      77,    -1,     4,    69,    47,    -1,     4,    69,    47,    80,
     150,    81,    -1,    22,    -1,    52,    -1,    43,    88,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
      46,    -1,    39,    -1,    40,    -1,   120,    -1,   118,    -1,
      80,    94,    81,    -1,    96,    -1,   157,    -1,    93,    -1,
     101,    -1,   137,    -1,   136,    -1,   138,    -1,   135,    -1,
     134,    -1,   144,    -1,   133,    -1,   149,    -1,    89,    -1,
     129,    -1,   154,    -1,   127,    -1,     5,    -1,   127,    -1,
      96,    -1,    95,    75,    94,    82,    -1,    -1,    57,    80,
      94,    81,    76,    98,   100,    77,    -1,     5,    -1,    53,
      -1,     8,    -1,     6,    -1,     7,    -1,   127,    -1,    58,
      99,    63,    86,    -1,    59,    63,    86,    -1,   100,    58,
      99,    63,    86,    -1,   100,    59,    63,    86,    -1,    67,
      94,    -1,    68,    94,    -1,    73,    94,    -1,    74,    94,
      -1,    54,     4,    76,   103,   115,    77,    -1,    -1,   104,
      -1,    -1,   105,   107,    79,    -1,    -1,   104,   106,   107,
      79,    -1,    -1,     3,   108,   111,    -1,    -1,    41,   109,
     113,    -1,     5,    -1,    53,    -1,     8,    -1,     6,    -1,
       7,    -1,    46,    -1,    39,    -1,    40,    -1,   112,    -1,
     111,    60,   112,    -1,     5,    61,   110,    -1,     5,    -1,
     114,    -1,   113,    60,   114,    -1,     5,    61,   110,    -1,
      -1,   117,    -1,    -1,    55,    -1,    56,    -1,   116,   148,
      -1,   117,   116,   148,    -1,    75,   150,    82,    -1,     8,
      63,    94,    -1,   119,    60,     8,    63,    94,    -1,    76,
      63,    77,    -1,    76,   119,    77,    -1,    51,    94,    -1,
     123,    -1,   124,    -1,   123,   124,    -1,    49,    80,     5,
      81,    88,    -1,    -1,    48,    88,    -1,    50,    88,   122,
     125,    -1,    93,    69,     5,    -1,     4,    69,     5,    -1,
      93,    69,    53,    -1,     4,    69,    53,    -1,   127,    69,
       5,    -1,   127,    69,    53,    -1,    -1,   128,    69,     5,
      80,   150,    81,    -1,   128,    69,     5,    -1,   128,    69,
      53,    -1,    -1,    93,    69,     5,    80,   150,    81,   130,
     128,    -1,    -1,   127,    69,     5,    80,   150,    81,   131,
     128,    -1,    -1,     4,    69,     5,    80,   150,    81,   132,
     128,    -1,    93,    44,    -1,    93,    45,    -1,    44,    93,
      -1,    45,    93,    -1,   127,    44,    -1,   127,    45,    -1,
      44,   127,    -1,    45,   127,    -1,    94,    23,    94,    -1,
      94,    24,    94,    -1,    94,    17,    94,    -1,    94,    15,
      94,    -1,    94,    16,    94,    -1,    94,    14,    94,    -1,
      94,    31,    94,    -1,    94,    33,    94,    -1,    94,    32,
      94,    -1,    94,    34,    94,    -1,    94,    68,    94,    -1,
      94,    67,    94,    -1,    94,    70,    94,    -1,    94,    71,
      94,    -1,    94,    72,    94,    -1,    95,    26,    94,    -1,
      95,    29,    94,    -1,    95,    27,    94,    -1,    95,    28,
      94,    -1,    95,    30,    94,    -1,    94,    66,    94,    -1,
      94,    64,    94,    -1,    94,    65,    94,    -1,    94,    20,
      94,    -1,    94,    18,    94,    -1,     3,   140,    -1,    41,
     142,    -1,   141,    -1,   140,    60,   141,    -1,     5,    61,
      94,    -1,     5,    -1,   143,    -1,   142,    60,   143,    -1,
      53,    61,    94,    -1,    95,    61,    94,    -1,     5,    -1,
     145,    69,     5,    -1,    25,   145,    69,    70,    -1,    25,
     145,    63,    70,    -1,    25,   145,    63,     5,    -1,    25,
     145,    63,     4,    -1,    25,   145,    -1,     5,    69,    69,
      69,    -1,    42,     5,    80,    81,    88,    -1,    42,     4,
      80,    81,    88,    -1,    42,    74,     4,    80,    81,    88,
      -1,    42,     5,    80,   147,    81,    88,    -1,    42,     4,
      80,   147,    81,    88,    -1,    42,     5,    80,   140,    81,
      88,    -1,    42,     4,    80,   140,    81,    88,    -1,    42,
       5,    80,   140,    60,   147,    81,    88,    -1,    42,     4,
      80,   140,    60,   147,    81,    88,    -1,    42,    80,    81,
      88,    -1,    42,    80,   147,    81,    88,    -1,    42,    80,
     140,    81,    88,    -1,    42,    80,   140,    60,   147,    81,
      88,    -1,    -1,   151,    -1,    94,    -1,   151,    60,    94,
      -1,    -1,   152,    80,   150,    81,    -1,   152,    75,    94,
      82,    -1,     5,    -1,   153,    63,     5,    -1,    -1,   153,
      63,     5,    80,   150,    81,   155,   152,    -1,   153,    63,
      53,    -1,   153,    63,     5,    -1,   153,    63,     4,    69,
      53,    -1,   153,    63,     4,    69,    47,    -1,   153,    63,
       4,    69,    47,    80,   150,    81,    -1,    -1,   153,    63,
       4,    69,     5,    80,   150,    81,   156,   128,    -1,    -1,
       5,    80,   150,    81,   158,   152,    -1,    38,    94,    -1,
      38,    -1,    10,    80,    94,    81,    88,    -1,    -1,   139,
      -1,   151,    -1,    -1,    94,    -1,   150,    -1,     9,    80,
     161,    79,   162,    79,   163,    81,    88,    -1,    -1,   165,
      13,    80,    94,    81,    88,    -1,    -1,    12,    88,    -1,
      -1,    -1,    11,    80,    94,    81,    88,   168,   165,   169,
     166,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     8,    11,    14,    17,    20,
      23,    26,    28,    31,    33,    35,    37,    40,    42,    44,
      47,    50,    53,    55,    57,    60,    63,    65,    68,    72,
      76,    83,    85,    87,    90,    92,    94,    96,    98,   100,
     102,   104,   106,   108,   110,   114,   116,   118,   120,   122,
     124,   126,   128,   130,   132,   134,   136,   138,   140,   142,
     144,   146,   148,   150,   152,   157,   158,   167,   169,   171,
     173,   175,   177,   179,   184,   188,   194,   199,   202,   205,
     208,   211,   218,   219,   221,   222,   226,   227,   232,   233,
     237,   238,   242,   244,   246,   248,   250,   252,   254,   256,
     258,   260,   264,   268,   270,   272,   276,   280,   281,   283,
     284,   286,   288,   291,   295,   299,   303,   309,   313,   317,
     320,   322,   324,   327,   333,   334,   337,   342,   346,   350,
     354,   358,   362,   366,   367,   374,   378,   382,   383,   392,
     393,   402,   403,   412,   415,   418,   421,   424,   427,   430,
     433,   436,   440,   444,   448,   452,   456,   460,   464,   468,
     472,   476,   480,   484,   488,   492,   496,   500,   504,   508,
     512,   516,   520,   524,   528,   532,   536,   539,   542,   544,
     548,   552,   554,   556,   560,   564,   568,   570,   574,   579,
     584,   589,   594,   597,   602,   608,   614,   621,   628,   635,
     642,   649,   658,   667,   672,   678,   684,   692,   693,   695,
     697,   701,   702,   707,   712,   714,   718,   719,   728,   732,
     736,   742,   748,   757,   758,   769,   770,   777,   780,   782,
     788,   789,   791,   793,   794,   796,   798,   808,   809,   816,
     817,   820,   821,   822
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   219,   219,   219,   223,   224,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   253,   257,
     258,   262,   266,   271,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   314,   315,   316,   320,   324,   324,   328,   329,   330,
     331,   332,   333,   337,   338,   339,   340,   344,   345,   346,
     347,   351,   355,   356,   360,   360,   361,   361,   365,   365,
     366,   366,   370,   371,   372,   373,   374,   375,   376,   377,
     381,   382,   386,   387,   391,   392,   396,   400,   401,   405,
     406,   407,   411,   412,   416,   420,   421,   425,   426,   430,
     434,   438,   439,   443,   447,   448,   452,   456,   457,   458,
     459,   460,   461,   465,   466,   467,   468,   472,   472,   473,
     473,   474,   474,   478,   479,   480,   481,   482,   483,   484,
     485,   489,   490,   491,   492,   493,   494,   498,   499,   503,
     504,   508,   509,   510,   511,   512,   513,   514,   515,   516,
     517,   521,   522,   523,   524,   525,   529,   530,   534,   535,
     539,   540,   544,   545,   549,   553,   557,   558,   562,   563,
     564,   565,   566,   570,   574,   576,   578,   580,   582,   584,
     586,   588,   590,   595,   597,   599,   601,   606,   607,   611,
     612,   616,   617,   618,   622,   623,   627,   627,   628,   629,
     630,   631,   632,   633,   633,   637,   637,   641,   642,   646,
     650,   651,   652,   656,   657,   661,   665,   668,   670,   674,
     675,   679,   680,   679
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
  const int Parser::yylast_ = 1137;
  const int Parser::yynnts_ = 87;
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

