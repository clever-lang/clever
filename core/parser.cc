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

  case 55:

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

    { (yysemantic_stack_[(1) - (0)].narray)->append((yysemantic_stack_[(1) - (1)].attr)); (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 92:

    { (yysemantic_stack_[(3) - (0)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 93:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), false, yyloc); }
    break;

  case 94:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(1) - (1)].ident), NULL, false, yyloc);     }
    break;

  case 95:

    { (yysemantic_stack_[(1) - (0)].narray)->append((yysemantic_stack_[(1) - (1)].attr)); (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 96:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
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

    { (yyval.narray) = new ast::NodeArray(yyloc); }
    break;

  case 105:

    { (yyval.narray) = (yysemantic_stack_[(5) - (4)].narray); }
    break;

  case 106:

    { (yyval.narray) = new ast::NodeArray(yyloc); }
    break;

  case 107:

    { (yyval.narray) = (yysemantic_stack_[(5) - (4)].narray); }
    break;

  case 108:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].fdecl)); (yysemantic_stack_[(3) - (3)].fdecl)->setVisibility((yysemantic_stack_[(3) - (2)].flags)); }
    break;

  case 109:

    { (yyval.narray) = (yysemantic_stack_[(3) - (1)].narray); }
    break;

  case 110:

    { (yyval.narray) = (yysemantic_stack_[(6) - (5)].narray); }
    break;

  case 111:

    { (yyval.narray) = (yysemantic_stack_[(3) - (1)].narray); }
    break;

  case 112:

    { (yyval.narray) = (yysemantic_stack_[(6) - (5)].narray); }
    break;

  case 113:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 114:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 115:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 116:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 117:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 118:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 120:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 121:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 122:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 123:

    { (yyval.block) = NULL; }
    break;

  case 124:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 125:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 126:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 127:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 128:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 129:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
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

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (0)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
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

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 143:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 144:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 145:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 146:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].property)->setWriteMode(); }
    break;

  case 147:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].property)->setWriteMode(); }
    break;

  case 148:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].property)->setWriteMode(); }
    break;

  case 149:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].property)->setWriteMode(); }
    break;

  case 150:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 151:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 152:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 153:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 154:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 155:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 156:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 157:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 158:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 159:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 160:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 161:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 162:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 163:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 164:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 165:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 166:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 167:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 168:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 169:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 170:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 171:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR,     (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 172:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 173:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 174:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 175:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 176:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR,     (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 177:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 178:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 179:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 180:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 181:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 182:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 183:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 184:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 185:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 186:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 187:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 188:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 189:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 190:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 191:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 192:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 193:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 194:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 195:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 196:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 197:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 198:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 199:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 200:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 201:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 202:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 203:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 204:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 205:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 206:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 207:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 208:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 209:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 210:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 211:

    { (yyval.narray) = NULL; }
    break;

  case 213:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 214:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 215:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 216:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 217:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 219:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 220:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 221:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 222:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 223:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 224:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 225:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 226:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 227:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 228:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 229:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 230:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 231:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 232:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 233:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 234:

    { (yyval.narray) = NULL; }
    break;

  case 237:

    { (yyval.node) = NULL;     }
    break;

  case 238:

    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); }
    break;

  case 240:

    { (yyval.for_loop) = new ast::For((yysemantic_stack_[(9) - (3)].narray), (yysemantic_stack_[(9) - (5)].node), (yysemantic_stack_[(9) - (7)].narray), (yysemantic_stack_[(9) - (9)].block), yyloc); }
    break;

  case 242:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 243:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 244:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 245:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 246:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 247:

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
  const short int Parser::yypact_ninf_ = -343;
  const short int
  Parser::yypact_[] =
  {
      -343,    16,  -343,  -343,   540,    46,   -26,   881,  -343,  -343,
    -343,   -23,   -13,    44,  -343,   109,   638,  -343,  -343,    64,
      14,    51,    30,    30,  -343,    51,   638,  -343,  -343,   177,
     108,   638,   638,   638,   638,   638,    12,   638,  -343,  -343,
     139,   150,   172,  -343,    18,   934,  1127,  1168,  -343,  -343,
    -343,  -343,  -343,   176,  -343,  1115,   185,   189,  -343,  -343,
    -343,   190,   201,   202,   206,   207,  -343,  -343,   164,   208,
     209,   210,  -343,  -343,  -343,   184,   205,  -343,    54,   638,
     595,   638,   638,  -343,    60,   198,    12,  -343,   934,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,   233,   211,  -343,   215,
     216,   266,     8,  -343,  -343,   228,   163,   231,   226,   161,
     231,   161,   258,   934,   232,   638,  -343,  -343,  -343,  -343,
     934,   227,   251,   249,   236,   311,   144,   705,  -343,  -343,
    -343,  -343,  -343,    47,   638,   638,   638,   638,   638,   638,
     638,   638,   638,   638,   638,   638,   638,   638,   638,   638,
     638,   638,   638,   638,   638,   638,   638,   638,   638,   638,
     638,   638,   638,   638,   638,   638,  -343,  -343,  -343,    56,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,    19,  -343,  -343,
    -343,   638,    46,   248,   254,  -343,   256,  -343,   251,   261,
     726,   785,    27,    34,   638,    64,     9,    10,   255,    57,
      51,    22,   262,    66,   120,   123,   264,   294,   258,  -343,
     128,   806,  -343,   638,   638,  -343,  -343,   337,  -343,  -343,
     267,  -343,   152,   152,   152,   152,   182,   182,   684,   684,
    1026,   955,  1037,  1014,  1048,  1107,   764,   191,   191,  -343,
    -343,  -343,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1014,
    1014,  1014,  1014,   259,   268,  -343,   277,   148,  -343,   934,
    -343,   638,   638,  -343,   638,    51,    51,  -343,  -343,  -343,
    -343,  -343,   934,  -343,    51,    32,   279,    51,   125,   285,
     288,   301,  -343,   367,    51,    51,  -343,  -343,  -343,   368,
      51,  -343,  -343,  -343,  -343,   298,   175,   158,   304,   934,
     934,   314,   638,  -343,   638,    55,   638,   302,   308,  -343,
     934,   303,  -343,  -343,  -343,   367,    51,    51,  -343,   367,
      51,    51,    51,   321,   312,  -343,  -343,   313,  -343,  -343,
    -343,  -343,    21,  -343,   192,  -343,   638,   315,   316,   318,
     319,  -343,   322,  -343,  -343,   166,   638,  -343,   324,  -343,
    -343,   325,  -343,  -343,  -343,  -343,    51,    51,   387,   390,
    -343,  -343,  -343,   199,   934,  -343,  -343,   638,   638,  -343,
    -343,   638,   638,  -343,   327,   389,    51,    51,  -343,  -343,
     339,   -39,  -343,   349,    -5,  -343,   387,   390,    40,   348,
     121,  -343,  -343,   331,   332,  -343,   345,   408,   334,    51,
     338,   405,  -343,  -343,   186,   387,  -343,   186,   390,  -343,
     129,   136,    -7,   356,   358,   364,   370,   231,   371,   168,
    -343,    40,   372,  -343,   345,   345,  -343,  -343,   166,   159,
    -343,  -343,  -343,   638,    51,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,   540,   373,  -343,  -343,   350,  -343,   865,  -343,   540,
    -343,   540,   345,   638,    51,   540,   357,  -343,  -343
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    35,    38,    39,
      37,     0,     0,     0,    32,     0,   232,    41,    42,     0,
       0,     0,     0,     0,    40,     0,     0,    33,    36,     0,
       0,     0,     0,     0,     0,   211,     4,     0,     5,    17,
      58,     0,     0,    18,    48,     0,     0,    46,    26,    49,
      23,    44,    43,     0,    22,    61,    59,    56,    54,    53,
      51,    50,    52,     0,    55,     0,    11,    57,     0,    60,
      47,     0,    14,    15,    13,   185,   180,   182,     0,   211,
     234,     0,     0,   190,   196,     0,     0,    58,   231,    59,
      56,    50,    52,    55,    60,    47,     0,   181,   186,     0,
       0,     0,     0,     4,    34,     0,    35,   144,     0,   148,
     145,   149,     0,   118,     0,     0,    78,    79,    80,    81,
     213,     0,   212,     0,     0,     0,     0,     0,    25,    20,
      21,   142,   143,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,   146,   147,     0,
      10,    16,    27,    28,     7,     8,     6,     0,    24,     9,
      12,     0,     0,   127,    30,   129,     0,   235,   236,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   185,
       0,     0,     0,     0,     0,     0,     0,   123,   119,   120,
     100,     0,   113,     0,     0,   116,    29,     0,   117,    45,
     126,   128,   155,   153,   154,   152,   174,   173,   150,   151,
     156,   158,   157,   159,   171,   172,   170,   161,   160,   162,
     163,   164,   179,   178,   165,   167,   168,   166,   169,   175,
     176,   177,   189,     0,   130,   131,     0,   223,   222,   184,
     183,   211,   211,   229,   237,     0,     0,   195,   194,   193,
     191,   192,   188,   187,     0,     0,     0,     0,     0,     0,
       0,     0,   207,     0,     0,     0,   127,   126,   130,     0,
       0,   125,   121,   101,   102,     0,     0,   100,     0,   214,
     114,     0,   211,    65,   211,     0,   211,     0,     0,   215,
     238,     0,   233,   245,   199,     0,     0,     0,   198,     0,
       0,     0,     0,     0,     0,   209,   208,     0,   124,    82,
     104,   106,     0,   103,     0,    66,     0,     0,     0,     0,
     225,   224,     0,   140,    31,   230,   211,   241,     0,   204,
     202,     0,   203,   201,   200,   197,     0,     0,     0,     0,
     109,   111,   108,     0,   115,   136,   138,   211,   211,   220,
     132,     0,   211,   239,     0,   246,     0,     0,   210,   122,
      94,     0,    91,     0,     0,    95,     0,     0,     0,     0,
       0,   132,   132,     0,     0,   215,   141,     0,     0,     0,
       0,   243,   206,   205,     0,     0,   105,     0,     0,   107,
       0,     0,    35,    38,    39,    37,    36,     0,     0,    63,
       4,     0,     0,    67,   137,   139,   227,   226,   221,     0,
     217,   216,   240,     0,     0,   247,    83,    86,    87,    85,
      89,    90,    88,    84,    93,    92,    97,    96,   110,   112,
       4,    75,     0,     4,   132,   134,   135,     0,   244,    74,
       4,    77,   228,   211,     0,    76,     0,   242,   133
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -343,  -343,  -343,     0,  -343,   -18,    -3,  -343,  -343,  -343,
     -17,    -4,   -14,  -343,  -343,  -343,    23,  -343,  -343,  -343,
      36,    59,    58,    65,    29,  -343,   154,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,   241,  -343,
    -343,   -12,  -342,    37,  -343,  -343,  -343,    38,  -343,  -343,
    -343,    49,    50,   374,   -98,  -118,  -343,   269,    61,  -343,
    -343,  -112,  -238,  -343,   -62,   379,    70,  -343,    62,  -343,
    -343,    77,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   125,    38,    39,    87,    41,    42,    43,
      44,   120,    46,    47,    48,   363,   418,   390,    49,    50,
     444,   381,   382,   384,   385,   295,   296,   297,   358,   359,
     386,   387,    51,   126,    52,    53,   207,   208,   209,   291,
      54,    55,   396,    89,   391,   392,   370,    90,    58,    59,
      60,    91,    92,    63,    76,    77,    97,    98,    93,    84,
      65,   202,    66,    67,   121,   122,   345,    68,    94,   395,
     454,    95,   309,    71,    72,   189,   311,   374,    73,   375,
     435,    74,   347,   401
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -220;
  const short int
  Parser::yytable_[] =
  {
        45,    40,     4,   104,   201,   107,   110,   112,   108,   108,
     109,   111,    88,   199,   199,   199,     3,   186,    99,   100,
     123,   405,   113,   256,   257,    99,   100,   116,   117,   118,
     119,   267,   268,   127,   105,   106,     8,     9,    10,   270,
     406,    56,    57,    78,   105,   412,   413,   414,   415,   424,
     425,    75,   220,    61,    62,   408,   -68,    80,   333,   183,
     339,   254,   131,   132,   260,    64,    69,    81,   -62,    17,
      18,   286,   258,    79,   409,   124,    24,   190,   191,    17,
      18,    70,   283,    28,   276,   279,    24,   133,   101,   200,
     274,   277,   315,   416,   102,   101,   362,   269,   275,   278,
     221,   184,   340,   284,   271,    35,    86,   185,   341,   255,
      37,   211,   462,   316,    83,    35,    86,    96,   181,   185,
      37,    45,    40,   192,    82,   287,   281,   103,   288,   193,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,    56,    57,   455,   260,  -220,  -220,  -220,  -220,
     138,   324,   139,   221,    61,    62,   255,   259,   330,   421,
     422,   114,   282,   293,   294,   319,    64,    69,   115,   405,
     272,   436,   437,   438,   439,   360,   408,   260,   423,   307,
     308,   260,    70,   348,   217,   -98,   320,   351,   448,   299,
     300,  -219,   456,   293,   294,   449,   331,   332,   128,   149,
     150,   218,   151,   152,   153,   440,   441,   177,   306,   129,
     205,   -73,   442,   361,   332,   -99,   -63,   205,   -62,   443,
     337,   371,   338,    79,   342,   181,   372,   312,   313,   149,
     150,   130,   151,   152,   153,   166,   314,   388,   389,   318,
     310,   151,   152,   153,   170,   182,   325,   326,   171,   172,
     198,   195,   328,   134,   135,   136,   137,   138,   102,   139,
     173,   174,   140,   141,   373,   175,   176,   178,   179,   180,
     142,   143,   144,   145,   194,   196,   197,   203,   349,   350,
     204,   165,   352,   353,   354,   393,   394,   206,   210,   212,
     398,   213,   214,   215,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   146,   147,   148,   149,   150,   261,   151,
     152,   153,   364,    14,   262,   280,    15,   263,   378,   379,
     264,   303,   290,   285,   289,   301,   305,   302,   304,    16,
      17,    18,    19,    20,    21,    22,    23,    24,   402,   403,
     317,    25,    26,    27,    28,    29,   321,   397,    30,   322,
     323,   417,   199,   327,   108,   329,   419,   336,    31,    32,
     335,   432,   346,   343,    33,    34,    35,    36,   216,   344,
     355,    37,   380,   356,   357,   383,   365,   366,   367,   368,
     404,   466,   400,   369,   417,   376,   377,   108,   399,   419,
     407,   420,   426,   427,   429,   431,   458,   434,   433,   -71,
     451,   -72,   134,   135,   136,   137,   138,   -70,   139,   457,
     463,   140,   141,   -69,   450,   453,   460,   447,   468,   142,
     143,   144,   145,   446,   452,   410,   467,    45,    40,   292,
     459,   334,   411,   461,   187,    45,    40,    45,    40,   188,
     465,    45,    40,   445,   273,   428,     0,     0,     0,     0,
       0,     0,   146,   147,   148,   149,   150,     0,   151,   152,
     153,     0,     0,     0,     0,     0,     0,     0,    56,    57,
     430,     0,     0,     0,     0,     0,    56,    57,    56,    57,
      61,    62,    56,    57,     0,     0,     0,     0,    61,    62,
      61,    62,    64,    69,    61,    62,     0,     0,     0,     0,
      64,    69,    64,    69,     0,     0,    64,    69,    70,     0,
       0,     0,     0,     0,     0,     0,    70,     0,    70,     0,
       0,     0,    70,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,     0,     0,    15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,     0,     0,
      25,    26,    27,    28,    29,     0,     0,    30,     5,     6,
       7,     8,     9,    10,     0,     0,     0,    31,    32,     0,
       0,     0,     0,    33,    34,    35,    36,     0,     0,     0,
      37,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,    18,    19,    85,     0,    22,
      23,    24,     6,     7,     8,     9,    10,     0,    28,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,    33,    34,
      35,    86,     0,     0,     0,    37,     0,    17,    18,     0,
      85,     0,    22,    23,    24,     0,     0,     0,     0,     0,
       0,    28,     0,     0,     0,     0,     0,     0,   134,   135,
     136,   137,   138,     0,   139,    31,    32,  -220,  -220,     0,
       0,    33,    34,    35,    86,     0,     0,     0,    37,   134,
     135,   136,   137,   138,     0,   139,     0,     0,   140,   141,
       0,     0,     0,     0,     0,     0,   142,   143,   144,   145,
     134,   135,   136,   137,   138,     0,   139,     0,     0,   140,
     141,   149,   150,     0,   151,   152,   153,   142,   143,   144,
     145,     0,     0,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,   150,     0,   151,   152,   153,   134,   135,
     136,   137,   138,     0,   139,     0,   219,   140,   141,     0,
     146,   147,   148,   149,   150,     0,   151,   152,   153,   134,
     135,   136,   137,   138,     0,   139,     0,   265,   140,   141,
       0,     0,     0,     0,     0,     0,   142,   143,   144,   145,
     134,   135,   136,   137,   138,     0,   139,     0,     0,   140,
     141,   149,   150,     0,   151,   152,   153,   142,   143,   144,
     145,     0,     0,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,   150,     0,   151,   152,   153,     0,     0,
       0,     0,     0,     0,     0,     0,   266,     0,     0,     0,
     146,   147,   148,   149,   150,     0,   151,   152,   153,   134,
     135,   136,   137,   138,     0,   139,     0,   298,   140,   141,
       0,     0,     0,     0,     0,     0,   142,   143,   144,   145,
     -62,     0,   -62,     0,     0,     0,     0,   -62,   -62,   -62,
     -62,   -62,     0,     0,     0,     0,   -62,   -62,   -62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,   150,     0,   151,   152,   153,     0,     0,
       0,     0,   -62,     0,  -218,     0,   464,     0,   134,   135,
     136,   137,   138,     0,   139,     0,   -62,   140,   141,     0,
       0,    79,     0,     0,     0,   142,   143,   144,   145,   134,
     135,   136,   137,   138,     0,   139,     0,     0,   140,   141,
       0,     0,     0,     0,     0,     0,   142,     0,   144,   145,
       0,     0,     0,     0,     0,     0,     0,     0,   146,   147,
     148,   149,   150,     0,   151,   152,   153,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,   150,     0,   151,   152,   153,   134,   135,
     136,   137,   138,     0,   139,     0,     0,   140,   141,     0,
     134,   135,   136,   137,   138,   142,   139,   144,     0,   140,
     141,   134,   135,   136,   137,   138,     0,   139,     0,   144,
     140,   141,   134,   135,   136,   137,   138,     0,   139,     0,
       0,   140,   141,     0,     0,     0,     0,     0,   146,   147,
     148,   149,   150,     0,   151,   152,   153,     0,     0,     0,
     146,   147,   148,   149,   150,     0,   151,   152,   153,     0,
       0,   146,   147,   148,   149,   150,     0,   151,   152,   153,
       0,     0,     0,   147,   148,   149,   150,     0,   151,   152,
     153,   134,   135,   136,   137,   138,     0,   139,     0,     0,
     140,   141,     0,     0,   -63,     0,   -63,     0,     0,     0,
       0,   -63,   -63,   -63,   -63,   -63,   154,     0,   155,     0,
     -63,   -63,   -63,   156,   157,   158,   159,   160,     0,   167,
     168,     0,   161,   162,   163,     0,     0,     0,     0,     0,
       0,     0,     0,   148,   149,   150,   -63,   151,   152,   153,
       0,     0,     0,     0,   169,     0,     0,   -64,   164,   -64,
     -63,     0,     0,     0,   -64,   -64,   -64,   -64,   -64,     0,
       0,     0,   165,   -64,   -64,   -64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -64
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     2,    21,   102,    22,    23,    25,    22,    23,
      22,    23,    16,     5,     5,     5,     0,    79,     4,     5,
       8,    60,    26,     4,     5,     4,     5,    31,    32,    33,
      34,     4,     5,    37,     4,     5,     6,     7,     8,     5,
      79,     4,     4,    69,     4,     5,     6,     7,     8,   391,
     392,     5,     5,     4,     4,    60,    63,    80,   296,     5,
       5,     5,    44,    45,   182,     4,     4,    80,    75,    39,
      40,     5,    53,    80,    79,    63,    46,    81,    82,    39,
      40,     4,    60,    53,   196,   197,    46,    69,    74,    81,
      81,    81,    60,    53,    80,    74,   334,    70,   196,   197,
      53,    47,    47,    81,    70,    75,    76,    53,    53,    53,
      80,   115,   454,    81,     5,    75,    76,    53,    61,    53,
      80,   125,   125,    63,    80,     5,    69,    76,     5,    69,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   125,   125,     5,   283,    14,    15,    16,    17,
      18,   283,    20,    53,   125,   125,    53,   181,     3,    58,
      59,     4,   200,    55,    56,    60,   125,   125,    80,    60,
     194,     5,     6,     7,     8,     3,    60,   315,    77,   261,
     262,   319,   125,   315,    60,    77,    81,   319,    79,   213,
     214,    63,    53,    55,    56,    79,    41,    42,    79,    67,
      68,    77,    70,    71,    72,    39,    40,    63,    80,    79,
      69,    63,    46,    41,    42,    77,    75,    69,    75,    53,
     302,    75,   304,    80,   306,    61,    80,   265,   266,    67,
      68,    79,    70,    71,    72,    79,   274,    58,    59,   277,
     264,    70,    71,    72,    79,    60,   284,   285,    79,    79,
       4,    60,   290,    14,    15,    16,    17,    18,    80,    20,
      79,    79,    23,    24,   346,    79,    79,    79,    79,    79,
      31,    32,    33,    34,    61,    80,    80,    69,   316,   317,
      69,    75,   320,   321,   322,   367,   368,    49,    76,    82,
     372,    60,    63,    77,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    64,    65,    66,    67,    68,    80,    70,
      71,    72,   336,    22,    80,    80,    25,    81,   356,   357,
      79,    82,    48,    81,    80,     8,    69,    80,    80,    38,
      39,    40,    41,    42,    43,    44,    45,    46,   376,   377,
      81,    50,    51,    52,    53,    54,    81,   371,    57,    81,
      69,   388,     5,     5,   388,    77,   388,    63,    67,    68,
      76,   399,    79,    81,    73,    74,    75,    76,    77,    81,
      69,    80,     5,    81,    81,     5,    81,    81,    80,    80,
      61,   463,    13,    81,   421,    81,    81,   421,    81,   421,
      61,    63,    81,    81,    69,    81,   434,    12,    80,    63,
     420,    63,    14,    15,    16,    17,    18,    63,    20,   433,
      80,    23,    24,    63,    63,    63,    63,   408,    81,    31,
      32,    33,    34,   407,   421,   386,   464,   451,   451,   208,
     450,   297,   387,   453,    80,   459,   459,   461,   461,    80,
     460,   465,   465,   405,   195,   395,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   451,   451,
      82,    -1,    -1,    -1,    -1,    -1,   459,   459,   461,   461,
     451,   451,   465,   465,    -1,    -1,    -1,    -1,   459,   459,
     461,   461,   451,   451,   465,   465,    -1,    -1,    -1,    -1,
     459,   459,   461,   461,    -1,    -1,   465,   465,   451,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   459,    -1,   461,    -1,
      -1,    -1,   465,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    22,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    -1,    -1,    57,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    67,    68,    -1,
      -1,    -1,    -1,    73,    74,    75,    76,    -1,    -1,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,
      45,    46,     4,     5,     6,     7,     8,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    73,    74,
      75,    76,    -1,    -1,    -1,    80,    -1,    39,    40,    -1,
      42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    -1,    20,    67,    68,    23,    24,    -1,
      -1,    73,    74,    75,    76,    -1,    -1,    -1,    80,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    67,    68,    -1,    70,    71,    72,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    14,    15,
      16,    17,    18,    -1,    20,    -1,    81,    23,    24,    -1,
      64,    65,    66,    67,    68,    -1,    70,    71,    72,    14,
      15,    16,    17,    18,    -1,    20,    -1,    81,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    67,    68,    -1,    70,    71,    72,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    -1,    70,    71,    72,    14,
      15,    16,    17,    18,    -1,    20,    -1,    81,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      19,    -1,    21,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    -1,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    61,    -1,    63,    -1,    81,    -1,    14,    15,
      16,    17,    18,    -1,    20,    -1,    75,    23,    24,    -1,
      -1,    80,    -1,    -1,    -1,    31,    32,    33,    34,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      14,    15,    16,    17,    18,    31,    20,    33,    -1,    23,
      24,    14,    15,    16,    17,    18,    -1,    20,    -1,    33,
      23,    24,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    -1,    70,    71,    72,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    65,    66,    67,    68,    -1,    70,    71,
      72,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    -1,    -1,    19,    -1,    21,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,    19,    -1,    21,    -1,
      35,    36,    37,    26,    27,    28,    29,    30,    -1,    44,
      45,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    61,    70,    71,    72,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    19,    61,    21,
      75,    -1,    -1,    -1,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    75,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75
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
     102,   115,   117,   118,   123,   124,   126,   130,   131,   132,
     133,   134,   135,   136,   141,   143,   145,   146,   150,   151,
     154,   156,   157,   161,   164,     5,   137,   138,    69,    80,
      80,    80,    80,     5,   142,    42,    76,    89,    94,   126,
     130,   134,   135,   141,   151,   154,    53,   139,   140,     4,
       5,    74,    80,    76,    88,     4,     5,    93,    95,   124,
      93,   124,    88,    94,     4,    80,    94,    94,    94,    94,
      94,   147,   148,     8,    63,    86,   116,    94,    79,    79,
      79,    44,    45,    69,    14,    15,    16,    17,    18,    20,
      23,    24,    31,    32,    33,    34,    64,    65,    66,    67,
      68,    70,    71,    72,    19,    21,    26,    27,    28,    29,
      30,    35,    36,    37,    61,    75,    79,    44,    45,    69,
      79,    79,    79,    79,    79,    79,    79,    63,    79,    79,
      79,    61,    60,     5,    47,    53,   147,   136,   148,   158,
      94,    94,    63,    69,    61,    60,    80,    80,     4,     5,
      81,   137,   144,    69,    69,    69,    49,   119,   120,   121,
      76,    94,    82,    60,    63,    77,    77,    60,    77,    81,
       5,    53,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,     5,    53,     4,     5,    53,    94,
     138,    80,    80,    81,    79,    81,    81,     4,     5,    70,
       5,    70,    94,   140,    81,   137,   144,    81,   137,   144,
      80,    69,    88,    60,    81,    81,     5,     5,     5,    80,
      48,   122,   121,    55,    56,   108,   109,   110,    81,    94,
      94,     8,    80,    82,    80,    69,    80,   147,   147,   155,
      94,   159,    88,    88,    88,    60,    81,    81,    88,    60,
      81,    81,    81,    69,   144,    88,    88,     5,    88,    77,
       3,    41,    42,   145,   109,    76,    63,   147,   147,     5,
      47,    53,   147,    81,    81,   149,    79,   165,   144,    88,
      88,   144,    88,    88,    88,    69,    81,    81,   111,   112,
       3,    41,   145,    98,    94,    81,    81,    80,    80,    81,
     129,    75,    80,   147,   160,   162,    81,    81,    88,    88,
       5,   104,   105,     5,   106,   107,   113,   114,    58,    59,
     100,   127,   128,   147,   147,   152,   125,    94,   147,    81,
      13,   166,    88,    88,    61,    60,    79,    61,    60,    79,
     104,   106,     5,     6,     7,     8,    53,    93,    99,   124,
      63,    58,    59,    77,   125,   125,    81,    81,   149,    69,
      82,    81,    88,    80,    12,   163,     5,     6,     7,     8,
      39,    40,    46,    53,   103,   105,   103,   107,    79,    79,
      63,    86,    99,    63,   153,     5,    53,    94,    88,    86,
      63,    86,   125,    80,    81,    86,   147,    88,    81
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
      87,    87,    87,    87,    87,    87,    87,    87,    87,    88,
      89,    89,    90,    91,    92,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    95,    95,    95,    96,    98,    97,    99,    99,
      99,    99,    99,    99,   100,   100,   100,   100,   101,   101,
     101,   101,   102,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   105,   105,   106,   106,   107,   108,   108,
     109,   109,   109,   110,   111,   110,   112,   110,   110,   113,
     110,   114,   110,   115,   116,   116,   117,   117,   118,   119,
     120,   120,   121,   122,   122,   123,   124,   124,   124,   124,
     124,   124,   125,   125,   125,   125,   127,   126,   128,   126,
     129,   126,   130,   130,   130,   130,   130,   130,   130,   130,
     131,   131,   131,   131,   131,   131,   132,   132,   133,   133,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     136,   136,   137,   137,   138,   138,   139,   139,   140,   141,
     142,   142,   143,   143,   143,   143,   143,   144,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   146,   146,   146,
     146,   147,   147,   148,   148,   149,   149,   149,   150,   150,
     152,   151,   151,   151,   151,   151,   151,   153,   151,   155,
     154,   156,   156,   157,   158,   158,   158,   159,   159,   160,
     161,   162,   162,   163,   163,   165,   166,   164
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
       0,     1,     1,     2,     0,     5,     0,     5,     3,     0,
       6,     0,     6,     3,     3,     5,     3,     3,     2,     1,
       1,     2,     5,     0,     2,     4,     3,     3,     3,     3,
       3,     3,     0,     6,     3,     3,     0,     8,     0,     8,
       0,     8,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     3,     3,     1,     1,     3,     3,     3,
       1,     3,     4,     4,     4,     4,     2,     4,     5,     5,
       6,     6,     6,     6,     6,     8,     8,     4,     5,     5,
       7,     0,     1,     1,     3,     0,     4,     4,     1,     3,
       0,     8,     3,     3,     5,     5,     8,     0,    10,     0,
       6,     2,     1,     5,     0,     1,     1,     0,     1,     1,
       9,     0,     6,     0,     2,     0,     0,     9
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
  "case_list", "unary", "class_def", "attr_rvalue", "class_attr_decl_list",
  "class_attr_decl_impl", "class_attr_const_decl_list",
  "class_attr_const_decl_impl", "class_member_decl", "visibility",
  "class_member_list", "@3", "@4", "@5", "@6", "array", "key_value_list",
  "map", "throw", "catch", "not_empty_catch", "catch_impl", "finally",
  "try_catch_finally", "property_access", "mcall_chain", "mcall", "@7",
  "@8", "@9", "inc_dec", "comparison", "boolean", "logic", "arithmetic",
  "bitwise", "variable_decl", "variable_decl_list", "variable_decl_impl",
  "const_decl_list", "const_decl_impl", "assignment", "import_ident_list",
  "import", "vararg", "fdecl", "anonymous_fdecl", "call_args",
  "non_empty_call_args", "fcall_chain", "fully_qualified_name",
  "fully_qualified_call", "@10", "@11", "fcall", "@12", "return_stmt",
  "while", "for_expr_1", "for_expr_2", "for_expr_3", "for", "elseif",
  "else", "if", "@13", "@14", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        84,     0,    -1,    -1,    85,    86,    -1,    -1,    86,    87,
      -1,   143,    79,    -1,   136,    79,    -1,   141,    79,    -1,
     154,    79,    -1,   126,    79,    -1,   145,    -1,   156,    79,
      -1,   164,    -1,   157,    -1,   161,    -1,   130,    79,    -1,
      88,    -1,    92,    -1,   118,    79,    -1,    90,    79,    -1,
      91,    79,    -1,   123,    -1,   102,    -1,   151,    79,    -1,
      89,    79,    -1,    97,    -1,   134,    79,    -1,   135,    79,
      -1,    76,    86,    77,    -1,     4,    69,    47,    -1,     4,
      69,    47,    80,   147,    81,    -1,    22,    -1,    52,    -1,
      43,    88,    -1,     5,    -1,    53,    -1,     8,    -1,     6,
      -1,     7,    -1,    46,    -1,    39,    -1,    40,    -1,   117,
      -1,   115,    -1,    80,    94,    81,    -1,    96,    -1,   154,
      -1,    93,    -1,   101,    -1,   134,    -1,   133,    -1,   135,
      -1,   132,    -1,   131,    -1,   141,    -1,   130,    -1,   146,
      -1,    89,    -1,   126,    -1,   151,    -1,   124,    -1,     5,
      -1,   124,    -1,    96,    -1,    95,    75,    94,    82,    -1,
      -1,    57,    80,    94,    81,    76,    98,   100,    77,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
     124,    -1,    58,    99,    63,    86,    -1,    59,    63,    86,
      -1,   100,    58,    99,    63,    86,    -1,   100,    59,    63,
      86,    -1,    67,    94,    -1,    68,    94,    -1,    73,    94,
      -1,    74,    94,    -1,    54,     4,    76,   108,    77,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
      46,    -1,    39,    -1,    40,    -1,   105,    -1,   104,    60,
     105,    -1,     5,    61,   103,    -1,     5,    -1,   107,    -1,
     106,    60,   107,    -1,     5,    61,   103,    -1,    -1,   110,
      -1,    -1,    55,    -1,    56,    -1,   109,   145,    -1,    -1,
     109,     3,   111,   104,    79,    -1,    -1,   109,    41,   112,
     106,    79,    -1,   110,   109,   145,    -1,    -1,   110,   109,
       3,   113,   104,    79,    -1,    -1,   110,   109,    41,   114,
     106,    79,    -1,    75,   147,    82,    -1,     8,    63,    94,
      -1,   116,    60,     8,    63,    94,    -1,    76,    63,    77,
      -1,    76,   116,    77,    -1,    51,    94,    -1,   120,    -1,
     121,    -1,   120,   121,    -1,    49,    80,     5,    81,    88,
      -1,    -1,    48,    88,    -1,    50,    88,   119,   122,    -1,
      93,    69,     5,    -1,     4,    69,     5,    -1,    93,    69,
      53,    -1,     4,    69,    53,    -1,   124,    69,     5,    -1,
     124,    69,    53,    -1,    -1,   125,    69,     5,    80,   147,
      81,    -1,   125,    69,     5,    -1,   125,    69,    53,    -1,
      -1,    93,    69,     5,    80,   147,    81,   127,   125,    -1,
      -1,   124,    69,     5,    80,   147,    81,   128,   125,    -1,
      -1,     4,    69,     5,    80,   147,    81,   129,   125,    -1,
      93,    44,    -1,    93,    45,    -1,    44,    93,    -1,    45,
      93,    -1,   124,    44,    -1,   124,    45,    -1,    44,   124,
      -1,    45,   124,    -1,    94,    23,    94,    -1,    94,    24,
      94,    -1,    94,    17,    94,    -1,    94,    15,    94,    -1,
      94,    16,    94,    -1,    94,    14,    94,    -1,    94,    31,
      94,    -1,    94,    33,    94,    -1,    94,    32,    94,    -1,
      94,    34,    94,    -1,    94,    68,    94,    -1,    94,    67,
      94,    -1,    94,    70,    94,    -1,    94,    71,    94,    -1,
      94,    72,    94,    -1,    95,    26,    94,    -1,    95,    29,
      94,    -1,    95,    27,    94,    -1,    95,    28,    94,    -1,
      95,    30,    94,    -1,    94,    66,    94,    -1,    94,    64,
      94,    -1,    94,    65,    94,    -1,    94,    20,    94,    -1,
      94,    18,    94,    -1,    95,    35,    94,    -1,    95,    36,
      94,    -1,    95,    37,    94,    -1,    95,    21,    94,    -1,
      95,    19,    94,    -1,     3,   137,    -1,    41,   139,    -1,
     138,    -1,   137,    60,   138,    -1,     5,    61,    94,    -1,
       5,    -1,   140,    -1,   139,    60,   140,    -1,    53,    61,
      94,    -1,    95,    61,    94,    -1,     5,    -1,   142,    69,
       5,    -1,    25,   142,    69,    70,    -1,    25,   142,    63,
      70,    -1,    25,   142,    63,     5,    -1,    25,   142,    63,
       4,    -1,    25,   142,    -1,     5,    69,    69,    69,    -1,
      42,     5,    80,    81,    88,    -1,    42,     4,    80,    81,
      88,    -1,    42,    74,     4,    80,    81,    88,    -1,    42,
       5,    80,   144,    81,    88,    -1,    42,     4,    80,   144,
      81,    88,    -1,    42,     5,    80,   137,    81,    88,    -1,
      42,     4,    80,   137,    81,    88,    -1,    42,     5,    80,
     137,    60,   144,    81,    88,    -1,    42,     4,    80,   137,
      60,   144,    81,    88,    -1,    42,    80,    81,    88,    -1,
      42,    80,   144,    81,    88,    -1,    42,    80,   137,    81,
      88,    -1,    42,    80,   137,    60,   144,    81,    88,    -1,
      -1,   148,    -1,    94,    -1,   148,    60,    94,    -1,    -1,
     149,    80,   147,    81,    -1,   149,    75,    94,    82,    -1,
       5,    -1,   150,    63,     5,    -1,    -1,   150,    63,     5,
      80,   147,    81,   152,   149,    -1,   150,    63,    53,    -1,
     150,    63,     5,    -1,   150,    63,     4,    69,    53,    -1,
     150,    63,     4,    69,    47,    -1,   150,    63,     4,    69,
      47,    80,   147,    81,    -1,    -1,   150,    63,     4,    69,
       5,    80,   147,    81,   153,   125,    -1,    -1,     5,    80,
     147,    81,   155,   149,    -1,    38,    94,    -1,    38,    -1,
      10,    80,    94,    81,    88,    -1,    -1,   136,    -1,   148,
      -1,    -1,    94,    -1,   147,    -1,     9,    80,   158,    79,
     159,    79,   160,    81,    88,    -1,    -1,   162,    13,    80,
      94,    81,    88,    -1,    -1,    12,    88,    -1,    -1,    -1,
      11,    80,    94,    81,    88,   165,   162,   166,   163,    -1
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
     261,   262,   264,   266,   269,   270,   276,   277,   283,   287,
     288,   295,   296,   303,   307,   311,   317,   321,   325,   328,
     330,   332,   335,   341,   342,   345,   350,   354,   358,   362,
     366,   370,   374,   375,   382,   386,   390,   391,   400,   401,
     410,   411,   420,   423,   426,   429,   432,   435,   438,   441,
     444,   448,   452,   456,   460,   464,   468,   472,   476,   480,
     484,   488,   492,   496,   500,   504,   508,   512,   516,   520,
     524,   528,   532,   536,   540,   544,   548,   552,   556,   560,
     564,   567,   570,   572,   576,   580,   582,   584,   588,   592,
     596,   598,   602,   607,   612,   617,   622,   625,   630,   636,
     642,   649,   656,   663,   670,   677,   686,   695,   700,   706,
     712,   720,   721,   723,   725,   729,   730,   735,   740,   742,
     746,   747,   756,   760,   764,   770,   776,   785,   786,   797,
     798,   805,   808,   810,   816,   817,   819,   821,   822,   824,
     826,   836,   837,   844,   845,   848,   849,   850
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   219,   219,   219,   223,   224,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   254,
     258,   259,   263,   267,   272,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   315,   316,   317,   321,   325,   325,   329,   330,
     331,   332,   333,   334,   338,   339,   340,   341,   345,   346,
     347,   348,   352,   356,   357,   358,   359,   360,   361,   362,
     363,   367,   368,   372,   373,   377,   378,   382,   386,   387,
     391,   392,   393,   397,   398,   398,   399,   399,   400,   401,
     401,   402,   402,   406,   410,   411,   415,   416,   420,   424,
     428,   429,   433,   437,   438,   442,   446,   447,   448,   449,
     450,   451,   455,   456,   457,   458,   462,   462,   463,   463,
     464,   464,   468,   469,   470,   471,   472,   473,   474,   475,
     479,   480,   481,   482,   483,   484,   488,   489,   493,   494,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     524,   525,   529,   530,   534,   535,   539,   540,   544,   548,
     552,   553,   557,   558,   559,   560,   561,   565,   569,   571,
     573,   575,   577,   579,   581,   583,   585,   590,   592,   594,
     596,   601,   602,   606,   607,   611,   612,   613,   617,   618,
     622,   622,   623,   624,   625,   626,   627,   628,   628,   632,
     632,   636,   637,   641,   645,   646,   647,   651,   652,   656,
     660,   663,   665,   669,   670,   674,   675,   674
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
  const int Parser::yylast_ = 1243;
  const int Parser::yynnts_ = 84;
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

