/* A Bison parser, made by GNU Bison 2.7.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2012 Free Software Foundation, Inc.
   
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





# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

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

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


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
# define YY_SYMBOL_PRINT(Title, Type, Value, Location) YYUSE(Type)
# define YY_REDUCE_PRINT(Rule)        static_cast<void>(0)
# define YY_STACK_PRINT()             static_cast<void>(0)

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
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
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

    if (yymsg)
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

    // State.
    int yyn;
    int yylen = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
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

    // Compute the default @$.
    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }

    // Perform the reduction.
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

  case 29:

    { (yyval.block) = (yysemantic_stack_[(3) - (2)].block); }
    break;

  case 30:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(3) - (1)].type), NULL, yyloc); }
    break;

  case 31:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (5)].narray),   yyloc); }
    break;

  case 32:

    { (yyval.break_) = new ast::Break(yyloc); }
    break;

  case 33:

    { (yyval.continue_) = new ast::Continue(yyloc); }
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

  case 64:

    { (yysemantic_stack_[(1) - (1)].subscript)->setWriteMode(); }
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

  case 74:

    { (yysemantic_stack_[(4) - (0)].switch_)->addCase((yysemantic_stack_[(4) - (2)].node), (yysemantic_stack_[(4) - (4)].block)); (yyval.switch_) = (yysemantic_stack_[(4) - (0)].switch_); }
    break;

  case 75:

    { (yysemantic_stack_[(3) - (0)].switch_)->addCase(NULL, (yysemantic_stack_[(3) - (3)].block)); (yyval.switch_) = (yysemantic_stack_[(3) - (0)].switch_);     }
    break;

  case 76:

    { (yysemantic_stack_[(5) - (0)].switch_)->addCase((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block)); (yyval.switch_) = (yysemantic_stack_[(5) - (0)].switch_); }
    break;

  case 77:

    { (yysemantic_stack_[(4) - (0)].switch_)->addCase(NULL, (yysemantic_stack_[(4) - (4)].block)); (yyval.switch_) = (yysemantic_stack_[(4) - (0)].switch_);     }
    break;

  case 78:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 79:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 80:

    { (yyval.node) = new ast::Boolean(ast::Boolean::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 81:

    { (yyval.node) = new ast::Bitwise(ast::Bitwise::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 82:

    { (yyval.class_) = new ast::ClassDef((yysemantic_stack_[(5) - (2)].type), (yysemantic_stack_[(5) - (4)].narray), yyloc); }
    break;

  case 91:

    { (yyval.attrarray) = new ast::AttrArray(yyloc); (yyval.attrarray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 92:

    { (yysemantic_stack_[(3) - (1)].attrarray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 93:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), false, yyloc); }
    break;

  case 94:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(1) - (1)].ident), NULL, false, yyloc);     }
    break;

  case 95:

    { (yyval.attrarray) = new ast::AttrArray(yyloc); (yyval.attrarray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 96:

    { (yysemantic_stack_[(3) - (1)].attrarray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 97:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), true, yyloc);   }
    break;

  case 98:

    { (yyval.narray) = NULL; }
    break;

  case 100:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 101:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 102:

    { (yyval.flags) = ast::PRIVATE; }
    break;

  case 103:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(2) - (2)].fdecl)); (yysemantic_stack_[(2) - (2)].fdecl)->setVisibility((yysemantic_stack_[(2) - (1)].flags)); }
    break;

  case 104:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].fdecl)); (yysemantic_stack_[(3) - (3)].fdecl)->setVisibility((yysemantic_stack_[(3) - (2)].flags)); (yysemantic_stack_[(3) - (3)].fdecl)->setStatic(); }
    break;

  case 105:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(4) - (3)].attrarray)); (yysemantic_stack_[(4) - (3)].attrarray)->setVisibility((yysemantic_stack_[(4) - (1)].flags)); }
    break;

  case 106:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(4) - (3)].attrarray)); (yysemantic_stack_[(4) - (3)].attrarray)->setVisibility((yysemantic_stack_[(4) - (1)].flags)); }
    break;

  case 107:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].fdecl)); (yysemantic_stack_[(3) - (3)].fdecl)->setVisibility((yysemantic_stack_[(3) - (2)].flags)); }
    break;

  case 108:

    { (yysemantic_stack_[(4) - (1)].narray)->append((yysemantic_stack_[(4) - (4)].fdecl)); (yysemantic_stack_[(4) - (4)].fdecl)->setVisibility((yysemantic_stack_[(4) - (3)].flags)); (yysemantic_stack_[(4) - (4)].fdecl)->setStatic(); }
    break;

  case 109:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (4)].attrarray)); (yysemantic_stack_[(5) - (4)].attrarray)->setVisibility((yysemantic_stack_[(5) - (2)].flags)); }
    break;

  case 110:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (4)].attrarray)); (yysemantic_stack_[(5) - (4)].attrarray)->setVisibility((yysemantic_stack_[(5) - (2)].flags)); }
    break;

  case 111:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 112:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 113:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 114:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 115:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 116:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 118:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 119:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 120:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 121:

    { (yyval.block) = NULL; }
    break;

  case 122:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 123:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 124:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 125:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 126:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 127:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 128:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 129:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 130:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 131:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 132:

    { (yyval.mcall) = (yysemantic_stack_[(0) - (0)].mcall); }
    break;

  case 133:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 134:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 135:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); (yyval.property)->setStatic(); }
    break;

  case 136:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 137:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 138:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 139:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 140:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 141:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 142:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 143:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 144:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 145:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 146:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 147:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 148:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].property)->setWriteMode(); }
    break;

  case 149:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].property)->setWriteMode(); }
    break;

  case 150:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].property)->setWriteMode(); }
    break;

  case 151:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].property)->setWriteMode(); }
    break;

  case 152:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].subscript)->setWriteMode(); }
    break;

  case 153:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].subscript)->setWriteMode(); }
    break;

  case 154:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].subscript)->setWriteMode(); }
    break;

  case 155:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].subscript)->setWriteMode(); }
    break;

  case 156:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 157:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 158:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 159:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 160:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 161:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 162:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 163:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 164:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 165:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 166:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 167:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 168:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 169:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 170:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 171:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 172:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 173:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 174:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 175:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 176:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 177:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR,     (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 178:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 179:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 180:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 181:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 182:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR,     (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 183:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 184:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 185:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 186:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 187:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 188:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 189:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 190:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 191:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 192:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 193:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 194:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 195:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 196:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 197:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 198:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 199:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 200:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 201:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 202:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 203:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 204:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 205:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 206:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 207:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 208:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 209:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 210:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 211:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 212:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 213:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 214:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 215:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 216:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 217:

    { (yyval.narray) = NULL; }
    break;

  case 219:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 220:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 221:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 222:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 223:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 225:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 226:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 227:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 228:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 229:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 230:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 231:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 232:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 233:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 234:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 235:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 236:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 237:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 238:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 239:

    { (yyval.node) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc);   }
    break;

  case 240:

    { (yyval.node) = new ast::DoWhile((yysemantic_stack_[(7) - (5)].node), (yysemantic_stack_[(7) - (2)].block), yyloc); }
    break;

  case 241:

    { (yyval.narray) = NULL; }
    break;

  case 244:

    { (yyval.node) = NULL;     }
    break;

  case 245:

    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); }
    break;

  case 247:

    { (yyval.for_loop) = new ast::For((yysemantic_stack_[(9) - (3)].narray), (yysemantic_stack_[(9) - (5)].node), (yysemantic_stack_[(9) - (7)].narray), (yysemantic_stack_[(9) - (9)].block), yyloc); }
    break;

  case 248:

    {	(yyval.foreach_loop) = new ast::ForEach(new ast::VariableDecl((yysemantic_stack_[(8) - (4)].ident), new ast::Assignment((yysemantic_stack_[(8) - (4)].ident), NULL, yyloc), false, yyloc), (yysemantic_stack_[(8) - (6)].node), (yysemantic_stack_[(8) - (8)].block), yyloc); }
    break;

  case 250:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 251:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 252:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 253:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 254:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 255:

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
    while (1 < yystate_stack_.height ())
      {
        yydestruct_ ("Cleanup: popping",
                     yystos_[yystate_stack_[0]],
                     &yysemantic_stack_[0],
                     &yylocation_stack_[0]);
        yypop_ ();
      }

    return yyresult;
    }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (yychar != yyempty_)
          {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_ (yychar);
            yydestruct_ (YY_NULL, yytoken, &yylval, &yylloc);
          }

        while (1 < yystate_stack_.height ())
          {
            yydestruct_ (YY_NULL,
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
          }
        return yyresult;
      }
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

    char const* yyformat = YY_NULL;
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
  const short int Parser::yypact_ninf_ = -367;
  const short int
  Parser::yypact_[] =
  {
      -367,    45,  -367,  -367,   566,    42,   -16,   255,  -367,  -367,
    -367,    15,    34,    99,  -367,    75,   624,  -367,  -367,    14,
      16,   139,    11,    11,  -367,   139,   624,  -367,  -367,   192,
     151,   139,   624,   624,   624,   624,   624,    31,   624,  -367,
    -367,   168,   183,   184,  -367,    56,   991,  1272,  1240,  -367,
    -367,  -367,  -367,  -367,   185,  -367,  1252,   195,   196,  -367,
    -367,  -367,   198,   204,   205,   211,   217,  -367,  -367,   176,
     220,   221,   222,  -367,  -367,  -367,   189,   244,  -367,    63,
     624,   339,   624,   624,  -367,   145,   165,    31,  -367,   991,
    -367,  -367,  -367,  -367,  -367,  -367,  -367,   191,   252,  -367,
     233,   235,   316,     3,  -367,  -367,   250,    13,   254,   249,
     158,   160,   254,   158,   160,   279,   991,   253,   624,   325,
    -367,  -367,  -367,  -367,   991,   251,   274,   273,   260,   218,
     123,   721,  -367,  -367,  -367,  -367,  -367,    30,   624,   624,
     624,   624,   624,   624,   624,   624,   624,   624,   624,   624,
     624,   624,   624,   624,   624,   624,   624,   624,   624,   624,
     624,   624,   624,   624,   624,   624,   624,   624,   624,   624,
    -367,  -367,    35,  -367,  -367,  -367,    58,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,    39,  -367,  -367,  -367,   624,    42,
     258,   265,  -367,   266,   344,  -367,   274,   269,   742,   804,
      33,    22,   624,    14,    18,    20,   276,   167,   139,   -14,
     268,    66,    67,    69,    70,   277,   315,   279,  -367,   119,
     825,   281,  -367,   624,   624,  -367,  -367,   360,  -367,  -367,
     286,  -367,  1183,  1183,  1183,  1183,   238,   238,   638,   638,
    1077,  1053,  1088,  1065,  1150,  1161,  1172,   171,   171,  -367,
    -367,  -367,  1065,  1065,  1065,  1065,  1065,  1065,  1065,  1065,
    1065,  1065,  1065,   426,   287,  -367,   288,  -367,   300,    46,
    -367,   991,  -367,   624,   624,  -367,   173,   624,   139,   139,
    -367,  -367,  -367,  -367,  -367,   991,  -367,   139,    23,   289,
     139,   122,   290,   291,   304,  -367,   372,   139,   139,  -367,
    -367,  -367,  -367,   377,   139,  -367,  -367,  -367,  -367,    77,
     306,    43,   121,   308,   624,   991,   991,   322,   624,  -367,
     624,   624,    68,   624,   307,   309,  -367,   624,   991,   312,
    -367,  -367,  -367,   372,   139,   139,  -367,   372,   139,   139,
     139,   323,   313,  -367,  -367,   317,  -367,   357,  -367,   395,
     400,    28,  -367,    77,   166,  -367,   887,   624,   327,   329,
     330,   336,   337,  -367,   341,  -367,  -367,   117,   908,   624,
    -367,   342,  -367,  -367,   343,  -367,  -367,  -367,  -367,   139,
     139,  -367,   359,   -27,  -367,   366,   107,  -367,   357,   395,
     400,  -367,   157,   352,   991,  -367,  -367,  -367,   624,   624,
    -367,  -367,   624,   624,   139,  -367,   348,   408,   139,   139,
    -367,  -367,   463,   395,  -367,   463,   400,  -367,  -367,   130,
     131,   350,   371,   129,  -367,  -367,  -367,  -367,   354,   355,
    -367,   376,   658,   368,  -367,   139,   370,   442,  -367,  -367,
    -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,   114,   390,   398,   399,   401,   254,
     389,   406,   175,  -367,   350,   409,  -367,   376,   376,   376,
    -367,  -367,   117,    71,  -367,  -367,  -367,   624,   139,  -367,
    -367,   566,   410,  -367,  -367,   383,  -367,   970,  -367,   566,
    -367,   566,   376,   624,   139,   566,   397,  -367,  -367
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    35,    38,    39,
      37,     0,     0,     0,    32,     0,   238,    41,    42,     0,
       0,     0,     0,     0,    40,     0,     0,    33,    36,     0,
       0,     0,     0,     0,     0,     0,   217,     4,     0,     5,
      17,    47,     0,     0,    18,    48,     0,     0,    49,    26,
      50,    23,    44,    43,     0,    22,    61,    59,    57,    55,
      54,    52,    51,    53,     0,    56,     0,    11,    58,     0,
      60,    46,     0,    14,    15,    13,   191,   186,   188,     0,
     217,   241,     0,     0,   196,   202,     0,     0,    47,   237,
      59,    57,    51,    53,    56,    60,    46,     0,   187,   192,
       0,     0,     0,     0,     4,    34,     0,    35,   146,     0,
     154,   150,   147,   155,   151,     0,   116,     0,     0,     0,
      78,    79,    80,    81,   219,     0,   218,     0,     0,     0,
       0,     0,    25,    20,    21,   144,   145,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     152,   153,     0,    19,   148,   149,     0,    10,    16,    27,
      28,     7,     8,     6,     0,    24,     9,    12,     0,     0,
     126,    30,   127,     0,     0,   242,   243,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   191,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   117,   118,   100,
       0,     0,   111,     0,     0,   114,    29,     0,   115,    45,
     124,   125,   161,   159,   160,   158,   180,   179,   156,   157,
     162,   164,   163,   165,   177,   178,   176,   167,   166,   168,
     169,   170,   185,   184,   171,   173,   174,   172,   175,   181,
     182,   183,   195,     0,   130,   131,   128,   129,     0,   229,
     228,   190,   189,   217,   217,   235,   191,   244,     0,     0,
     201,   200,   199,   197,   198,   194,   193,     0,     0,     0,
       0,     0,     0,     0,     0,   213,     0,     0,     0,   126,
     124,   130,   128,     0,     0,   123,   119,   101,   102,   100,
       0,     0,   100,     0,     0,   220,   112,     0,   217,    65,
     217,   217,     0,   217,     0,     0,   221,     0,   245,     0,
     239,   253,   205,     0,     0,     0,   204,     0,     0,     0,
       0,     0,     0,   215,   214,     0,   122,     0,    82,     0,
       0,     0,   103,   100,     0,    66,     0,     0,     0,     0,
       0,     0,   231,   230,     0,   140,    31,   236,     0,   217,
     249,     0,   210,   208,     0,   209,   207,   206,   203,     0,
       0,   104,    94,     0,    91,     0,     0,    95,     0,     0,
       0,   107,     0,     0,   113,   136,   142,   138,   217,   217,
     226,   132,     0,   217,     0,   246,     0,   254,     0,     0,
     216,   120,     0,     0,   105,     0,     0,   106,   108,     0,
       0,     0,     0,     0,   240,   132,   132,   132,     0,     0,
     221,   141,     0,     0,   248,     0,     0,   251,   212,   211,
      83,    86,    87,    85,    89,    90,    88,    84,    93,    92,
      97,    96,   109,   110,    35,    38,    39,    37,    36,     0,
      64,     0,    63,     4,     0,     0,    67,   137,   143,   139,
     233,   232,   227,     0,   223,   222,   247,     0,     0,   255,
       4,    75,     0,     4,   132,   134,   135,     0,   252,    74,
       4,    77,   234,   217,     0,    76,     0,   250,   133
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -367,  -367,  -367,     0,  -367,    27,    -3,  -367,  -367,  -367,
     -19,    -4,   -17,   -13,  -367,  -367,    10,  -367,  -367,  -367,
      64,    93,    76,    94,    82,  -367,  -182,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,   293,  -367,  -367,    -9,  -366,    37,
    -367,  -367,  -367,  -367,    38,  -367,  -367,  -367,    49,    50,
     423,   -96,  -165,  -367,   303,    61,  -367,  -367,  -123,  -285,
    -367,   -69,   427,    83,  -367,    62,  -367,  -367,    73,  -367,
    -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,
    -367
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   129,    39,    40,    88,    42,    43,    44,
      45,   124,    47,    48,    49,   392,   461,   423,    50,    51,
     448,   383,   384,   386,   387,   310,   311,   312,    52,   130,
      53,    54,   216,   217,   218,   305,    55,    56,   431,    90,
     425,   427,   401,   426,    91,    59,    60,    61,    92,    93,
      64,    77,    78,    98,    99,    94,    85,    66,   210,    67,
      68,   125,   126,   367,    69,    95,   430,   484,    96,   326,
      72,    73,   197,   329,   406,    74,   407,   479,    75,   370,
     437
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -226;
  const short int
  Parser::yytable_[] =
  {
        46,    41,     4,   108,   112,   109,   109,   209,   207,   110,
     113,   193,    89,   111,   114,   106,   107,     8,     9,    10,
     100,   101,   116,   207,   272,   207,   352,   283,   120,   121,
     122,   123,   100,   101,   131,   230,   413,   280,   281,   127,
     264,    57,    58,   268,   269,     3,   349,    76,   105,   296,
      17,    18,   115,    62,    63,   414,    79,    24,   119,   467,
     468,   469,   381,   266,    28,    65,    70,    97,   190,   391,
     297,   299,   300,   361,   301,   302,   485,    71,   198,   199,
      84,   289,   292,   231,   350,   351,   333,   208,   265,    36,
      87,   -62,   270,   102,    38,   284,    80,   128,    81,   103,
     135,   136,   287,   418,   290,   102,   282,   334,   288,   291,
     191,   267,  -225,   191,   220,   362,   192,    82,   492,   192,
     231,   363,   265,   267,   486,    46,    41,   347,   137,   323,
     354,   272,   307,   308,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,    57,    58,   272,   389,
     416,   388,   272,   342,   307,   308,   307,   308,    62,    63,
     -68,   309,    83,   353,   271,   337,   227,   464,   465,   417,
      65,    70,   -62,   413,   416,   402,   117,    80,   285,   -98,
     403,   -99,    71,   228,   324,   325,   338,   390,   351,   466,
     371,   200,   452,   453,   374,   421,   422,   201,   104,   315,
     316,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     213,   188,   214,   327,   118,   295,   -64,   188,   -63,   294,
      14,   -73,   184,    15,   155,   156,   157,   214,   103,   358,
     132,   359,   360,   188,   364,   202,    16,    17,    18,    19,
      20,    21,    22,    23,    24,   133,   134,   173,    25,    26,
      27,    28,    29,   328,   -62,    30,   -62,   177,   178,    31,
     179,   -62,   -62,   -62,   -62,   -62,   180,   181,    32,    33,
     -62,   -62,   -62,   182,    34,    35,    36,    37,   226,   183,
     405,    38,   185,   186,   187,   330,   331,   189,   153,   154,
     356,   155,   156,   157,   332,   203,   204,   336,   205,   -62,
     206,  -224,   211,   368,   343,   344,   212,   169,   215,   428,
     429,   346,   219,   -62,   433,   221,   222,   223,    80,   224,
     225,   273,   194,     6,     7,     8,     9,    10,   274,   276,
     275,   277,   298,   394,   106,   454,   455,   456,   457,   293,
     303,   372,   373,   304,   314,   375,   376,   377,   317,   318,
     320,   321,   322,   335,   339,   340,   341,   207,    17,    18,
      19,    86,   345,    22,    23,    24,   348,   355,   357,    17,
      18,   365,    28,   366,   369,   378,    24,   379,   432,   351,
     382,   380,   459,   458,   109,   385,   410,   411,   460,    32,
      33,   395,   462,   396,   397,    34,    35,    36,    87,   398,
     399,   436,    38,   412,   496,   400,   408,   409,    36,    87,
     415,   434,   435,    38,   424,   438,   439,   463,   470,   471,
     138,   139,   140,   141,   142,   459,   143,   109,   473,   144,
     145,   460,   475,   477,   478,   462,   -71,   146,   147,   148,
     149,   213,   476,   481,   -72,   -70,   493,   -69,   440,   441,
     442,   443,   480,   487,   482,   483,   490,    46,    41,   450,
     489,   498,   419,   491,   420,    46,    41,    46,    41,   449,
     495,    46,    41,   150,   151,   152,   153,   154,   451,   155,
     156,   157,   444,   445,   195,   488,   286,     0,   196,   446,
     306,   319,     0,   472,     0,     0,   447,     0,    57,    58,
       0,   497,     0,     0,     0,     0,    57,    58,    57,    58,
      62,    63,    57,    58,     0,     0,     0,     0,    62,    63,
      62,    63,    65,    70,    62,    63,     0,     0,     0,     0,
      65,    70,    65,    70,    71,     0,    65,    70,     0,     0,
       0,     0,    71,     0,    71,     0,     0,     0,    71,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,     0,
       0,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,     0,     0,    25,    26,    27,    28,
      29,     0,     0,    30,     0,     0,     0,    31,     6,     7,
       8,     9,    10,     0,     0,     0,    32,    33,     0,     0,
       0,     0,    34,    35,    36,    37,     0,     0,     0,    38,
       0,     0,   138,   139,   140,   141,   142,     0,   143,     0,
       0,  -226,  -226,    17,    18,     0,    86,     0,    22,    23,
      24,     0,   138,   139,   140,   141,   142,    28,   143,     0,
       0,   144,   145,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,     0,    32,    33,     0,     0,     0,     0,
      34,    35,    36,    87,     0,     0,     0,    38,   153,   154,
       0,   155,   156,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,   151,   152,   153,   154,
       0,   155,   156,   157,     0,   138,   139,   140,   141,   142,
       0,   143,     0,   474,   144,   145,     0,     0,     0,     0,
       0,     0,   146,   147,   148,   149,   138,   139,   140,   141,
     142,     0,   143,     0,     0,   144,   145,     0,     0,     0,
       0,     0,     0,   146,   147,   148,   149,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,   154,     0,   155,   156,   157,     0,     0,     0,
       0,     0,     0,     0,     0,   229,     0,     0,     0,   150,
     151,   152,   153,   154,     0,   155,   156,   157,   138,   139,
     140,   141,   142,     0,   143,     0,   278,   144,   145,     0,
       0,     0,     0,     0,     0,   146,   147,   148,   149,   138,
     139,   140,   141,   142,     0,   143,     0,     0,   144,   145,
       0,     0,     0,     0,     0,     0,   146,   147,   148,   149,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   150,   151,   152,   153,   154,     0,   155,   156,   157,
       0,     0,     0,     0,     0,     0,     0,     0,   279,     0,
       0,     0,   150,   151,   152,   153,   154,     0,   155,   156,
     157,   138,   139,   140,   141,   142,     0,   143,     0,   313,
     144,   145,     0,     0,     0,     0,     0,     0,   146,   147,
     148,   149,   138,   139,   140,   141,   142,     0,   143,     0,
       0,   144,   145,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150,   151,   152,   153,   154,     0,
     155,   156,   157,     0,     0,     0,     0,     0,     0,     0,
       0,   393,     0,     0,     0,   150,   151,   152,   153,   154,
       0,   155,   156,   157,   138,   139,   140,   141,   142,     0,
     143,     0,   404,   144,   145,     0,     0,     0,     0,     0,
       0,   146,   147,   148,   149,   138,   139,   140,   141,   142,
       0,   143,     0,     0,   144,   145,     0,     0,     0,     0,
       0,     0,   146,   147,   148,   149,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   150,   151,   152,
     153,   154,     0,   155,   156,   157,     0,     0,     0,     0,
       0,     0,     0,     0,   494,     0,     0,     0,   150,   151,
     152,   153,   154,     0,   155,   156,   157,   138,   139,   140,
     141,   142,     0,   143,     0,     0,   144,   145,     0,   138,
     139,   140,   141,   142,   146,   143,   148,   149,   144,   145,
       0,   138,   139,   140,   141,   142,   146,   143,   148,     0,
     144,   145,   138,   139,   140,   141,   142,     0,   143,     0,
     148,   144,   145,     0,     0,     0,     0,     0,     0,     0,
     150,   151,   152,   153,   154,     0,   155,   156,   157,     0,
       0,     0,   150,   151,   152,   153,   154,     0,   155,   156,
     157,     0,     0,     0,   150,   151,   152,   153,   154,     0,
     155,   156,   157,     0,     0,   150,   151,   152,   153,   154,
       0,   155,   156,   157,   138,   139,   140,   141,   142,     0,
     143,     0,     0,   144,   145,   138,   139,   140,   141,   142,
       0,   143,     0,     0,   144,   145,   138,   139,   140,   141,
     142,     0,   143,     0,     0,   144,   145,  -226,  -226,  -226,
    -226,   142,     0,   143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   151,   152,
     153,   154,     0,   155,   156,   157,     0,     0,     0,     0,
     152,   153,   154,     0,   155,   156,   157,     0,     0,     0,
       0,     0,   153,   154,     0,   155,   156,   157,     0,     0,
       0,     0,     0,   153,   154,     0,   155,   156,   157,   -64,
       0,   -64,     0,     0,     0,     0,   -64,   -64,   -64,   -64,
     -64,   -63,     0,   -63,     0,   -64,   -64,   -64,   -63,   -63,
     -63,   -63,   -63,     0,   170,   171,     0,   -63,   -63,   -63,
       0,   158,     0,   159,     0,     0,   174,   175,   160,   161,
     162,   163,   164,     0,   -64,     0,     0,   165,   166,   167,
       0,     0,   172,     0,     0,     0,   -63,     0,   -64,     0,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
     -63,     0,     0,     0,     0,     0,   168,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     169
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     2,    22,    23,    22,    23,   103,     5,    22,
      23,    80,    16,    22,    23,     4,     5,     6,     7,     8,
       4,     5,    26,     5,   189,     5,   311,     5,    32,    33,
      34,    35,     4,     5,    38,     5,    63,     4,     5,     8,
       5,     4,     4,     4,     5,     0,     3,     5,    21,    63,
      39,    40,    25,     4,     4,    82,    72,    46,    31,   425,
     426,   427,   347,     5,    53,     4,     4,    53,     5,   354,
      84,     5,     5,     5,     5,     5,     5,     4,    82,    83,
       5,   204,   205,    53,    41,    42,    63,    84,    53,    78,
      79,    78,    53,    77,    83,    73,    83,    66,    83,    83,
      44,    45,    84,   388,    84,    77,    73,    84,   204,   205,
      47,    53,    66,    47,   118,    47,    53,    83,   484,    53,
      53,    53,    53,    53,    53,   129,   129,   309,    72,    83,
     312,   296,    55,    56,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   129,   129,   333,     3,
      63,   353,   337,   296,    55,    56,    55,    56,   129,   129,
      66,    62,    83,    62,   188,    63,    63,    58,    59,    82,
     129,   129,    78,    63,    63,    78,     4,    83,   202,    80,
      83,    80,   129,    80,   273,   274,    84,    41,    42,    80,
     333,    66,    82,    82,   337,    58,    59,    72,    79,   223,
     224,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      72,    64,    72,    60,    83,   208,    78,    64,    78,    72,
      22,    66,    66,    25,    73,    74,    75,    72,    83,   318,
      82,   320,   321,    64,   323,    64,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    82,    82,    82,    50,    51,
      52,    53,    54,   277,    19,    57,    21,    82,    82,    61,
      82,    26,    27,    28,    29,    30,    82,    82,    70,    71,
      35,    36,    37,    82,    76,    77,    78,    79,    80,    82,
     369,    83,    82,    82,    82,   278,   279,    63,    70,    71,
     314,    73,    74,    75,   287,    63,    83,   290,    83,    64,
       4,    66,    72,   327,   297,   298,    72,    78,    49,   398,
     399,   304,    79,    78,   403,    10,    85,    63,    83,    66,
      80,    83,     3,     4,     5,     6,     7,     8,    83,     5,
      84,    82,    84,   357,     4,     5,     6,     7,     8,    83,
      83,   334,   335,    48,    83,   338,   339,   340,     8,    83,
      83,    83,    72,    84,    84,    84,    72,     5,    39,    40,
      41,    42,     5,    44,    45,    46,    80,    79,    66,    39,
      40,    84,    53,    84,    82,    72,    46,    84,   402,    42,
       5,    84,   421,    53,   421,     5,   379,   380,   421,    70,
      71,    84,   421,    84,    84,    76,    77,    78,    79,    83,
      83,    13,    83,    64,   493,    84,    84,    84,    78,    79,
      64,   404,    84,    83,    82,   408,   409,    66,    84,    84,
      14,    15,    16,    17,    18,   464,    20,   464,    72,    23,
      24,   464,    84,    83,    12,   464,    66,    31,    32,    33,
      34,    72,   435,   463,    66,    66,    83,    66,     5,     6,
       7,     8,    66,   477,   464,    66,    66,   481,   481,   415,
     480,    84,   389,   483,   390,   489,   489,   491,   491,   413,
     490,   495,   495,    67,    68,    69,    70,    71,   416,    73,
      74,    75,    39,    40,    81,   478,   203,    -1,    81,    46,
     217,    85,    -1,   430,    -1,    -1,    53,    -1,   481,   481,
      -1,   494,    -1,    -1,    -1,    -1,   489,   489,   491,   491,
     481,   481,   495,   495,    -1,    -1,    -1,    -1,   489,   489,
     491,   491,   481,   481,   495,   495,    -1,    -1,    -1,    -1,
     489,   489,   491,   491,   481,    -1,   495,   495,    -1,    -1,
      -1,    -1,   489,    -1,   491,    -1,    -1,    -1,   495,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    -1,    61,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    70,    71,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    -1,    -1,    -1,    83,
      -1,    -1,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    39,    40,    -1,    42,    -1,    44,    45,
      46,    -1,    14,    15,    16,    17,    18,    53,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    70,    71,    -1,    -1,    -1,    -1,
      76,    77,    78,    79,    -1,    -1,    -1,    83,    70,    71,
      -1,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      -1,    73,    74,    75,    -1,    14,    15,    16,    17,    18,
      -1,    20,    -1,    85,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    -1,    73,    74,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    -1,    73,    74,    75,    14,    15,
      16,    17,    18,    -1,    20,    -1,    84,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    -1,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    -1,    73,    74,
      75,    14,    15,    16,    17,    18,    -1,    20,    -1,    84,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    -1,
      73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      -1,    73,    74,    75,    14,    15,    16,    17,    18,    -1,
      20,    -1,    84,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    -1,    73,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    -1,    73,    74,    75,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    14,
      15,    16,    17,    18,    31,    20,    33,    34,    23,    24,
      -1,    14,    15,    16,    17,    18,    31,    20,    33,    -1,
      23,    24,    14,    15,    16,    17,    18,    -1,    20,    -1,
      33,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    -1,    73,    74,    75,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    -1,    73,    74,
      75,    -1,    -1,    -1,    67,    68,    69,    70,    71,    -1,
      73,    74,    75,    -1,    -1,    67,    68,    69,    70,    71,
      -1,    73,    74,    75,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    73,    74,    75,    -1,    -1,    -1,    -1,
      69,    70,    71,    -1,    73,    74,    75,    -1,    -1,    -1,
      -1,    -1,    70,    71,    -1,    73,    74,    75,    -1,    -1,
      -1,    -1,    -1,    70,    71,    -1,    73,    74,    75,    19,
      -1,    21,    -1,    -1,    -1,    -1,    26,    27,    28,    29,
      30,    19,    -1,    21,    -1,    35,    36,    37,    26,    27,
      28,    29,    30,    -1,    44,    45,    -1,    35,    36,    37,
      -1,    19,    -1,    21,    -1,    -1,    44,    45,    26,    27,
      28,    29,    30,    -1,    64,    -1,    -1,    35,    36,    37,
      -1,    -1,    72,    -1,    -1,    -1,    64,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    87,    88,     0,    89,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    22,    25,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    50,    51,    52,    53,    54,
      57,    61,    70,    71,    76,    77,    78,    79,    83,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     104,   105,   114,   116,   117,   122,   123,   125,   130,   131,
     132,   133,   134,   135,   136,   141,   143,   145,   146,   150,
     151,   154,   156,   157,   161,   164,     5,   137,   138,    72,
      83,    83,    83,    83,     5,   142,    42,    79,    92,    97,
     125,   130,   134,   135,   141,   151,   154,    53,   139,   140,
       4,     5,    77,    83,    79,    91,     4,     5,    96,    98,
      99,   123,    96,    99,   123,    91,    97,     4,    83,    91,
      97,    97,    97,    97,    97,   147,   148,     8,    66,    89,
     115,    97,    82,    82,    82,    44,    45,    72,    14,    15,
      16,    17,    18,    20,    23,    24,    31,    32,    33,    34,
      67,    68,    69,    70,    71,    73,    74,    75,    19,    21,
      26,    27,    28,    29,    30,    35,    36,    37,    64,    78,
      44,    45,    72,    82,    44,    45,    72,    82,    82,    82,
      82,    82,    82,    82,    66,    82,    82,    82,    64,    63,
       5,    47,    53,   147,     3,   136,   148,   158,    97,    97,
      66,    72,    64,    63,    83,    83,     4,     5,    84,   137,
     144,    72,    72,    72,    72,    49,   118,   119,   120,    79,
      97,    10,    85,    63,    66,    80,    80,    63,    80,    84,
       5,    53,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,     5,    53,     5,    53,     4,     5,
      53,    97,   138,    83,    83,    84,     5,    82,    84,    84,
       4,     5,    73,     5,    73,    97,   140,    84,   137,   144,
      84,   137,   144,    83,    72,    91,    63,    84,    84,     5,
       5,     5,     5,    83,    48,   121,   120,    55,    56,    62,
     111,   112,   113,    84,    83,    97,    97,     8,    83,    85,
      83,    83,    72,    83,   147,   147,   155,    60,    97,   159,
      91,    91,    91,    63,    84,    84,    91,    63,    84,    84,
      84,    72,   144,    91,    91,     5,    91,   112,    80,     3,
      41,    42,   145,    62,   112,    79,    97,    66,   147,   147,
     147,     5,    47,    53,   147,    84,    84,   149,    97,    82,
     165,   144,    91,    91,   144,    91,    91,    91,    72,    84,
      84,   145,     5,   107,   108,     5,   109,   110,   112,     3,
      41,   145,   101,    84,    97,    84,    84,    84,    83,    83,
      84,   128,    78,    83,    84,   147,   160,   162,    84,    84,
      91,    91,    64,    63,    82,    64,    63,    82,   145,   107,
     109,    58,    59,   103,    82,   126,   129,   127,   147,   147,
     152,   124,    97,   147,    91,    84,    13,   166,    91,    91,
       5,     6,     7,     8,    39,    40,    46,    53,   106,   108,
     106,   110,    82,    82,     5,     6,     7,     8,    53,    96,
      99,   102,   123,    66,    58,    59,    80,   124,   124,   124,
      84,    84,   149,    72,    85,    84,    91,    83,    12,   163,
      66,    89,   102,    66,   153,     5,    53,    97,    91,    89,
      66,    89,   124,    83,    84,    89,   147,    91,    84
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
     315,   316,   317,    44,    61,   318,    58,   124,    94,    38,
      45,    43,    46,    42,    47,    37,    33,   126,    91,   123,
     125,   319,    59,    40,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    86,    88,    87,    89,    89,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    91,
      92,    92,    93,    94,    95,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    98,    98,    98,    99,   101,   100,   102,   102,
     102,   102,   102,   102,   103,   103,   103,   103,   104,   104,
     104,   104,   105,   106,   106,   106,   106,   106,   106,   106,
     106,   107,   107,   108,   108,   109,   109,   110,   111,   111,
     112,   112,   112,   113,   113,   113,   113,   113,   113,   113,
     113,   114,   115,   115,   116,   116,   117,   118,   119,   119,
     120,   121,   121,   122,   123,   123,   123,   123,   123,   123,
     123,   123,   124,   124,   124,   124,   126,   125,   127,   125,
     128,   125,   129,   125,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   131,   131,   131,   131,
     131,   131,   132,   132,   133,   133,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   136,   136,   137,   137,
     138,   138,   139,   139,   140,   141,   142,   142,   143,   143,
     143,   143,   143,   144,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   146,   146,   146,   146,   147,   147,   148,
     148,   149,   149,   149,   150,   150,   152,   151,   151,   151,
     151,   151,   151,   153,   151,   155,   154,   156,   156,   157,
     157,   158,   158,   158,   159,   159,   160,   161,   161,   162,
     162,   163,   163,   165,   166,   164
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     1,     2,     1,     1,     2,
       2,     2,     1,     1,     2,     2,     1,     2,     2,     3,
       3,     6,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     0,     8,     1,     1,
       1,     1,     1,     1,     4,     3,     5,     4,     2,     2,
       2,     2,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     1,     3,     3,     0,     1,
       0,     1,     1,     2,     3,     4,     4,     3,     4,     5,
       5,     3,     3,     5,     3,     3,     2,     1,     1,     2,
       5,     0,     2,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     6,     3,     3,     0,     8,     0,     8,
       0,     8,     0,     8,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     3,
       3,     1,     1,     3,     3,     3,     1,     3,     4,     4,
       4,     4,     2,     4,     5,     5,     6,     6,     6,     6,
       6,     8,     8,     4,     5,     5,     7,     0,     1,     1,
       3,     0,     4,     4,     1,     3,     0,     8,     3,     3,
       5,     5,     8,     0,    10,     0,     6,     2,     1,     5,
       7,     0,     1,     1,     0,     1,     1,     9,     8,     0,
       6,     0,     2,     0,     0,     9
  };


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
  "\"switch\"", "\"case\"", "\"default\"", "\"in\"", "\"do\"",
  "\"static\"", "','", "'='", "XOR_EQUAL", "':'", "'|'", "'^'", "'&'",
  "'-'", "'+'", "'.'", "'*'", "'/'", "'%'", "'!'", "'~'", "'['", "'{'",
  "'}'", "UMINUS", "';'", "'('", "')'", "']'", "$accept", "program", "$@1",
  "statement_list", "statement", "block", "instantiation", "break",
  "continue", "critical_block", "object", "rvalue", "lvalue", "subscript",
  "switch_expr", "@2", "label", "case_list", "unary", "class_def",
  "attr_rvalue", "class_attr_decl_list", "class_attr_decl_impl",
  "class_attr_const_decl_list", "class_attr_const_decl_impl",
  "class_member_decl", "visibility", "class_member_list", "array",
  "key_value_list", "map", "throw", "catch", "not_empty_catch",
  "catch_impl", "finally", "try_catch_finally", "property_access",
  "mcall_chain", "mcall", "@3", "@4", "@5", "@6", "inc_dec", "comparison",
  "boolean", "logic", "arithmetic", "bitwise", "variable_decl",
  "variable_decl_list", "variable_decl_impl", "const_decl_list",
  "const_decl_impl", "assignment", "import_ident_list", "import", "vararg",
  "fdecl", "anonymous_fdecl", "call_args", "non_empty_call_args",
  "fcall_chain", "fully_qualified_name", "fully_qualified_call", "@7",
  "@8", "fcall", "@9", "return_stmt", "while", "for_expr_1", "for_expr_2",
  "for_expr_3", "for", "elseif", "else", "if", "@10", "@11", YY_NULL
  };

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        87,     0,    -1,    -1,    88,    89,    -1,    -1,    89,    90,
      -1,   143,    82,    -1,   136,    82,    -1,   141,    82,    -1,
     154,    82,    -1,   125,    82,    -1,   145,    -1,   156,    82,
      -1,   164,    -1,   157,    -1,   161,    -1,   130,    82,    -1,
      91,    -1,    95,    -1,   117,    82,    -1,    93,    82,    -1,
      94,    82,    -1,   122,    -1,   105,    -1,   151,    82,    -1,
      92,    82,    -1,   100,    -1,   134,    82,    -1,   135,    82,
      -1,    79,    89,    80,    -1,     4,    72,    47,    -1,     4,
      72,    47,    83,   147,    84,    -1,    22,    -1,    52,    -1,
      43,    91,    -1,     5,    -1,    53,    -1,     8,    -1,     6,
      -1,     7,    -1,    46,    -1,    39,    -1,    40,    -1,   116,
      -1,   114,    -1,    83,    97,    84,    -1,   154,    -1,    92,
      -1,    96,    -1,    99,    -1,   104,    -1,   134,    -1,   133,
      -1,   135,    -1,   132,    -1,   131,    -1,   141,    -1,   130,
      -1,   146,    -1,   125,    -1,   151,    -1,   123,    -1,     5,
      -1,   123,    -1,    99,    -1,    98,    78,    97,    85,    -1,
      -1,    57,    83,    97,    84,    79,   101,   103,    80,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
     123,    -1,    58,   102,    66,    89,    -1,    59,    66,    89,
      -1,   103,    58,   102,    66,    89,    -1,   103,    59,    66,
      89,    -1,    70,    97,    -1,    71,    97,    -1,    76,    97,
      -1,    77,    97,    -1,    54,     4,    79,   111,    80,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
      46,    -1,    39,    -1,    40,    -1,   108,    -1,   107,    63,
     108,    -1,     5,    64,   106,    -1,     5,    -1,   110,    -1,
     109,    63,   110,    -1,     5,    64,   106,    -1,    -1,   113,
      -1,    -1,    55,    -1,    56,    -1,   112,   145,    -1,    62,
     112,   145,    -1,   112,     3,   107,    82,    -1,   112,    41,
     109,    82,    -1,   113,   112,   145,    -1,   113,    62,   112,
     145,    -1,   113,   112,     3,   107,    82,    -1,   113,   112,
      41,   109,    82,    -1,    78,   147,    85,    -1,     8,    66,
      97,    -1,   115,    63,     8,    66,    97,    -1,    79,    66,
      80,    -1,    79,   115,    80,    -1,    51,    97,    -1,   119,
      -1,   120,    -1,   119,   120,    -1,    49,    83,     5,    84,
      91,    -1,    -1,    48,    91,    -1,    50,    91,   118,   121,
      -1,    96,    72,     5,    -1,    96,    72,    53,    -1,     4,
      72,     5,    -1,     4,    72,    53,    -1,   123,    72,     5,
      -1,   123,    72,    53,    -1,    99,    72,     5,    -1,    99,
      72,    53,    -1,    -1,   124,    72,     5,    83,   147,    84,
      -1,   124,    72,     5,    -1,   124,    72,    53,    -1,    -1,
      96,    72,     5,    83,   147,    84,   126,   124,    -1,    -1,
     123,    72,     5,    83,   147,    84,   127,   124,    -1,    -1,
       4,    72,     5,    83,   147,    84,   128,   124,    -1,    -1,
      99,    72,     5,    83,   147,    84,   129,   124,    -1,    96,
      44,    -1,    96,    45,    -1,    44,    96,    -1,    45,    96,
      -1,   123,    44,    -1,   123,    45,    -1,    44,   123,    -1,
      45,   123,    -1,    99,    44,    -1,    99,    45,    -1,    44,
      99,    -1,    45,    99,    -1,    97,    23,    97,    -1,    97,
      24,    97,    -1,    97,    17,    97,    -1,    97,    15,    97,
      -1,    97,    16,    97,    -1,    97,    14,    97,    -1,    97,
      31,    97,    -1,    97,    33,    97,    -1,    97,    32,    97,
      -1,    97,    34,    97,    -1,    97,    71,    97,    -1,    97,
      70,    97,    -1,    97,    73,    97,    -1,    97,    74,    97,
      -1,    97,    75,    97,    -1,    98,    26,    97,    -1,    98,
      29,    97,    -1,    98,    27,    97,    -1,    98,    28,    97,
      -1,    98,    30,    97,    -1,    97,    69,    97,    -1,    97,
      67,    97,    -1,    97,    68,    97,    -1,    97,    20,    97,
      -1,    97,    18,    97,    -1,    98,    35,    97,    -1,    98,
      36,    97,    -1,    98,    37,    97,    -1,    98,    21,    97,
      -1,    98,    19,    97,    -1,     3,   137,    -1,    41,   139,
      -1,   138,    -1,   137,    63,   138,    -1,     5,    64,    97,
      -1,     5,    -1,   140,    -1,   139,    63,   140,    -1,    53,
      64,    97,    -1,    98,    64,    97,    -1,     5,    -1,   142,
      72,     5,    -1,    25,   142,    72,    73,    -1,    25,   142,
      66,    73,    -1,    25,   142,    66,     5,    -1,    25,   142,
      66,     4,    -1,    25,   142,    -1,     5,    72,    72,    72,
      -1,    42,     5,    83,    84,    91,    -1,    42,     4,    83,
      84,    91,    -1,    42,    77,     4,    83,    84,    91,    -1,
      42,     5,    83,   144,    84,    91,    -1,    42,     4,    83,
     144,    84,    91,    -1,    42,     5,    83,   137,    84,    91,
      -1,    42,     4,    83,   137,    84,    91,    -1,    42,     5,
      83,   137,    63,   144,    84,    91,    -1,    42,     4,    83,
     137,    63,   144,    84,    91,    -1,    42,    83,    84,    91,
      -1,    42,    83,   144,    84,    91,    -1,    42,    83,   137,
      84,    91,    -1,    42,    83,   137,    63,   144,    84,    91,
      -1,    -1,   148,    -1,    97,    -1,   148,    63,    97,    -1,
      -1,   149,    83,   147,    84,    -1,   149,    78,    97,    85,
      -1,     5,    -1,   150,    66,     5,    -1,    -1,   150,    66,
       5,    83,   147,    84,   152,   149,    -1,   150,    66,    53,
      -1,   150,    66,     5,    -1,   150,    66,     4,    72,    53,
      -1,   150,    66,     4,    72,    47,    -1,   150,    66,     4,
      72,    47,    83,   147,    84,    -1,    -1,   150,    66,     4,
      72,     5,    83,   147,    84,   153,   124,    -1,    -1,     5,
      83,   147,    84,   155,   149,    -1,    38,    97,    -1,    38,
      -1,    10,    83,    97,    84,    91,    -1,    61,    91,    10,
      83,    97,    84,    82,    -1,    -1,   136,    -1,   148,    -1,
      -1,    97,    -1,   147,    -1,     9,    83,   158,    82,   159,
      82,   160,    84,    91,    -1,     9,    83,     3,     5,    60,
      97,    84,    91,    -1,    -1,   162,    13,    83,    97,    84,
      91,    -1,    -1,    12,    91,    -1,    -1,    -1,    11,    83,
      97,    84,    91,   165,   162,   166,   163,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     8,    11,    14,    17,    20,
      23,    26,    28,    31,    33,    35,    37,    40,    42,    44,
      47,    50,    53,    55,    57,    60,    63,    65,    68,    71,
      75,    79,    86,    88,    90,    93,    95,    97,    99,   101,
     103,   105,   107,   109,   111,   113,   117,   119,   121,   123,
     125,   127,   129,   131,   133,   135,   137,   139,   141,   143,
     145,   147,   149,   151,   153,   155,   160,   161,   170,   172,
     174,   176,   178,   180,   182,   187,   191,   197,   202,   205,
     208,   211,   214,   220,   222,   224,   226,   228,   230,   232,
     234,   236,   238,   242,   246,   248,   250,   254,   258,   259,
     261,   262,   264,   266,   269,   273,   278,   283,   287,   292,
     298,   304,   308,   312,   318,   322,   326,   329,   331,   333,
     336,   342,   343,   346,   351,   355,   359,   363,   367,   371,
     375,   379,   383,   384,   391,   395,   399,   400,   409,   410,
     419,   420,   429,   430,   439,   442,   445,   448,   451,   454,
     457,   460,   463,   466,   469,   472,   475,   479,   483,   487,
     491,   495,   499,   503,   507,   511,   515,   519,   523,   527,
     531,   535,   539,   543,   547,   551,   555,   559,   563,   567,
     571,   575,   579,   583,   587,   591,   595,   598,   601,   603,
     607,   611,   613,   615,   619,   623,   627,   629,   633,   638,
     643,   648,   653,   656,   661,   667,   673,   680,   687,   694,
     701,   708,   717,   726,   731,   737,   743,   751,   752,   754,
     756,   760,   761,   766,   771,   773,   777,   778,   787,   791,
     795,   801,   807,   816,   817,   828,   829,   836,   839,   841,
     847,   855,   856,   858,   860,   861,   863,   865,   875,   884,
     885,   892,   893,   896,   897,   898
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   224,   224,   224,   228,   229,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   259,
     263,   264,   268,   272,   276,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   319,   320,   321,   325,   329,   329,   333,   334,
     335,   336,   337,   338,   342,   343,   344,   345,   349,   350,
     351,   352,   356,   360,   361,   362,   363,   364,   365,   366,
     367,   371,   372,   376,   377,   381,   382,   386,   390,   391,
     395,   396,   397,   401,   402,   403,   404,   405,   406,   407,
     408,   412,   416,   417,   421,   422,   426,   430,   434,   435,
     439,   443,   444,   448,   452,   453,   454,   455,   456,   457,
     458,   459,   463,   464,   465,   466,   470,   470,   471,   471,
     472,   472,   473,   473,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   492,   493,   494,   495,
     496,   497,   501,   502,   506,   507,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   537,   538,   542,   543,
     547,   548,   552,   553,   557,   561,   565,   566,   570,   571,
     572,   573,   574,   578,   582,   584,   586,   588,   590,   592,
     594,   596,   598,   603,   605,   607,   609,   614,   615,   619,
     620,   624,   625,   626,   630,   631,   635,   635,   636,   637,
     638,   639,   640,   641,   641,   645,   645,   649,   650,   654,
     655,   659,   660,   661,   665,   666,   670,   674,   675,   678,
     680,   684,   685,   689,   689,   689
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
       2,     2,     2,    76,     2,     2,     2,    75,    69,     2,
      83,    84,    73,    71,    63,    70,    72,    74,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    66,    82,
       2,    64,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    78,     2,    85,    68,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    79,    67,    80,    77,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    65,    81
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 1350;
  const int Parser::yynnts_ = 81;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 3;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 86;

  const unsigned int Parser::yyuser_token_number_max_ = 319;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} // clever




namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever
