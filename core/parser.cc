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

    { (yyval.class_) = new ast::ClassDef((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 83:

    { (yyval.narray) = NULL; }
    break;

  case 85:

    { (yyval.narray) = new ast::NodeArray(yyloc); }
    break;

  case 86:

    { (yyval.narray) = (yysemantic_stack_[(3) - (1)].narray); }
    break;

  case 87:

    { (yyval.narray) = (yysemantic_stack_[(1) - (1)].narray); }
    break;

  case 89:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 91:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 101:

    { (yysemantic_stack_[(1) - (0)].narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 102:

    { (yysemantic_stack_[(3) - (0)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 103:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), false, yyloc); }
    break;

  case 104:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(1) - (1)].ident), NULL, false, yyloc);     }
    break;

  case 105:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 106:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 107:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), true, yyloc);   }
    break;

  case 108:

    { (yyval.narray) = NULL; }
    break;

  case 110:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 111:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 112:

    { (yyval.flags) = ast::PRIVATE; }
    break;

  case 113:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(2) - (2)].fdecl)); (yysemantic_stack_[(2) - (2)].fdecl)->setVisibility((yysemantic_stack_[(2) - (1)].flags)); }
    break;

  case 114:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].fdecl)); (yysemantic_stack_[(3) - (3)].fdecl)->setVisibility((yysemantic_stack_[(3) - (2)].flags)); }
    break;

  case 115:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 116:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 117:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 118:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 119:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 120:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 122:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 123:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 124:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 125:

    { (yyval.block) = NULL; }
    break;

  case 126:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 127:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
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

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 132:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 133:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 134:

    { (yyval.mcall) = (yysemantic_stack_[(0) - (0)].mcall); }
    break;

  case 135:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (0)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 136:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 137:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); (yyval.property)->setStatic(); }
    break;

  case 138:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 139:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 140:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 141:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 142:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
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

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 153:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 154:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 155:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 156:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 157:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 158:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 159:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 160:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 161:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 162:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 163:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 164:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 165:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 166:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 167:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 168:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 169:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 170:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 171:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 172:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 173:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR,     (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 174:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 175:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 176:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 177:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 178:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR,     (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 179:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 180:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 181:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 182:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 183:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 184:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 185:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 186:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 187:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 188:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 189:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 190:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 191:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 192:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 193:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 194:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 195:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 196:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 197:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 198:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 199:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 200:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 201:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 202:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 203:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 204:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 205:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 206:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 207:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 208:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 209:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 210:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 211:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 212:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 213:

    { (yyval.narray) = NULL; }
    break;

  case 215:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 216:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 217:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 218:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 219:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 221:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 222:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 223:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 224:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 225:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 226:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 227:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 228:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 229:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 230:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 231:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 232:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 233:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 234:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 235:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 236:

    { (yyval.narray) = NULL; }
    break;

  case 239:

    { (yyval.node) = NULL;     }
    break;

  case 240:

    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); }
    break;

  case 242:

    { (yyval.for_loop) = new ast::For((yysemantic_stack_[(9) - (3)].narray), (yysemantic_stack_[(9) - (5)].node), (yysemantic_stack_[(9) - (7)].narray), (yysemantic_stack_[(9) - (9)].block), yyloc); }
    break;

  case 244:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 245:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 246:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 247:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 248:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 249:

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
  const short int Parser::yypact_ninf_ = -360;
  const short int
  Parser::yypact_[] =
  {
      -360,    45,  -360,  -360,   616,    33,    -2,   316,  -360,  -360,
    -360,   -22,   101,   103,  -360,    71,   394,  -360,  -360,    76,
      16,   117,    11,    11,  -360,   117,   394,  -360,  -360,   193,
     121,   394,   394,   394,   394,   394,    31,   394,  -360,  -360,
     129,   132,   139,  -360,   135,   945,  1105,  1146,  -360,  -360,
    -360,  -360,  -360,   141,  -360,  1093,   149,   152,  -360,  -360,
    -360,   162,   166,   167,   176,   186,  -360,  -360,   153,   189,
     190,   194,  -360,  -360,  -360,   168,   210,  -360,    42,   394,
     246,   394,   394,  -360,   150,   199,    31,  -360,   945,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,   221,   229,  -360,   215,
     223,   300,    19,  -360,  -360,   238,   155,   239,   234,   146,
     239,   146,   262,   945,   236,   394,  -360,  -360,  -360,  -360,
     945,   233,   256,   254,   241,   538,    -8,   764,  -360,  -360,
    -360,  -360,  -360,    35,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,  -360,  -360,  -360,    54,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,    39,  -360,  -360,
    -360,   394,    33,   243,   244,  -360,   248,  -360,   256,   255,
     785,   844,    27,     9,   394,    76,    20,    21,   245,   -13,
     117,   -11,   257,    55,    57,    75,   261,   288,   262,  -360,
      43,   865,  -360,   394,   394,  -360,  -360,   339,  -360,  -360,
     268,  -360,   743,   743,   743,   743,   172,   172,   260,   260,
    1028,  1004,  1039,  1016,   100,   461,   662,   191,   191,  -360,
    -360,  -360,  1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,
    1016,  1016,  1016,   683,   269,  -360,   281,     5,  -360,   945,
    -360,   394,   394,  -360,   394,   117,   117,  -360,  -360,  -360,
    -360,  -360,   945,  -360,   117,   124,   273,   117,   125,   274,
     275,   289,  -360,   352,   117,   117,  -360,  -360,  -360,   354,
     117,  -360,  -360,   136,    72,   173,   284,   945,   945,   298,
     394,  -360,   394,    56,   394,   283,   285,  -360,   945,   286,
    -360,  -360,  -360,   352,   117,   117,  -360,   352,   117,   117,
     117,   299,   291,  -360,  -360,   292,  -360,  -360,  -360,   290,
     327,   136,   173,  -360,  -360,   295,  -360,   394,   301,   302,
     296,   304,  -360,   305,  -360,  -360,   157,   394,  -360,   306,
    -360,  -360,   307,  -360,  -360,  -360,  -360,   117,   117,  -360,
      30,  -360,   327,   310,   365,   376,  -360,    68,   945,  -360,
    -360,   394,   394,  -360,  -360,   394,   394,  -360,   309,   379,
     117,   117,  -360,  -360,  -360,  -360,   332,   334,  -360,   336,
     343,  -360,   218,   342,   130,  -360,  -360,   325,   329,  -360,
     344,   704,   330,   117,   328,   400,  -360,  -360,    66,   365,
      66,   376,   137,   351,   355,   356,   358,   239,   359,   164,
    -360,   218,   360,  -360,   344,   344,  -360,  -360,   157,   120,
    -360,  -360,  -360,   394,   117,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,   616,
     361,  -360,  -360,   335,  -360,   924,  -360,   616,  -360,   616,
     344,   394,   117,   616,   345,  -360,  -360
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    35,    38,    39,
      37,     0,     0,     0,    32,     0,   234,    41,    42,     0,
       0,     0,     0,     0,    40,     0,     0,    33,    36,     0,
       0,     0,     0,     0,     0,   213,     4,     0,     5,    17,
      58,     0,     0,    18,    48,     0,     0,    46,    26,    49,
      23,    44,    43,     0,    22,    61,    59,    56,    54,    53,
      51,    50,    52,     0,    55,     0,    11,    57,     0,    60,
      47,     0,    14,    15,    13,   187,   182,   184,     0,   213,
     236,     0,     0,   192,   198,     0,     0,    58,   233,    59,
      56,    50,    52,    55,    60,    47,     0,   183,   188,     0,
       0,     0,     0,     4,    34,     0,    35,   146,     0,   150,
     147,   151,     0,   120,     0,     0,    78,    79,    80,    81,
     215,     0,   214,     0,     0,     0,     0,     0,    25,    20,
      21,   144,   145,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,   148,   149,     0,
      10,    16,    27,    28,     7,     8,     6,     0,    24,     9,
      12,     0,     0,   129,    30,   131,     0,   237,   238,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   187,
       0,     0,     0,     0,     0,     0,     0,   125,   121,   122,
      83,     0,   115,     0,     0,   118,    29,     0,   119,    45,
     128,   130,   157,   155,   156,   154,   176,   175,   152,   153,
     158,   160,   159,   161,   173,   174,   172,   163,   162,   164,
     165,   166,   181,   180,   167,   169,   170,   168,   171,   177,
     178,   179,   191,     0,   132,   133,     0,   225,   224,   186,
     185,   213,   213,   231,   239,     0,     0,   197,   196,   195,
     193,   194,   190,   189,     0,     0,     0,     0,     0,     0,
       0,     0,   209,     0,     0,     0,   129,   128,   132,     0,
       0,   127,   123,   108,    84,     0,     0,   216,   116,     0,
     213,    65,   213,     0,   213,     0,     0,   217,   240,     0,
     235,   247,   201,     0,     0,     0,   200,     0,     0,     0,
       0,     0,     0,   211,   210,     0,   126,   111,   112,     0,
       0,   109,     0,    89,    91,     0,    66,     0,     0,     0,
       0,   227,   226,     0,   142,    31,   232,   213,   243,     0,
     206,   204,     0,   205,   203,   202,   199,     0,     0,    82,
       0,   113,     0,     0,     0,     0,    86,     0,   117,   138,
     140,   213,   213,   222,   134,     0,   213,   241,     0,   248,
       0,     0,   212,   124,   114,    88,   104,    90,   101,     0,
      92,   105,     0,     0,     0,   134,   134,     0,     0,   217,
     143,     0,     0,     0,     0,   245,   208,   207,     0,     0,
       0,     0,    35,    38,    39,    37,    36,     0,     0,    63,
       4,     0,     0,    67,   139,   141,   229,   228,   223,     0,
     219,   218,   242,     0,     0,   249,    93,    96,    97,    95,
      99,   100,    98,    94,   103,   102,   107,   106,     4,    75,
       0,     4,   134,   136,   137,     0,   246,    74,     4,    77,
     230,   213,     0,    76,     0,   244,   135
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -360,  -360,  -360,     0,  -360,   -18,    -3,  -360,  -360,  -360,
     -17,    -4,   -14,  -360,  -360,  -360,     4,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,    85,  -360,  -360,    17,  -360,    22,
    -360,    24,  -360,    97,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,   222,  -360,  -360,   -12,  -359,    37,  -360,  -360,  -360,
      38,  -360,  -360,  -360,    49,    50,   357,   -98,  -119,  -360,
     237,    61,  -360,  -360,  -114,  -307,  -360,   -66,   362,    44,
    -360,    62,  -360,  -360,    77,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   125,    38,    39,    87,    41,    42,    43,
      44,   120,    46,    47,    48,   367,   418,   394,    49,    50,
     293,   294,   295,   332,   335,   364,   365,   444,   387,   388,
     390,   391,   329,   330,   331,    51,   126,    52,    53,   207,
     208,   209,   291,    54,    55,   400,    89,   395,   396,   374,
      90,    58,    59,    60,    91,    92,    63,    76,    77,    97,
      98,    93,    84,    65,   202,    66,    67,   121,   122,   346,
      68,    94,   399,   452,    95,   307,    71,    72,   189,   309,
     378,    73,   379,   435,    74,   348,   405
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -222;
  const short int
  Parser::yytable_[] =
  {
        45,    40,     4,   104,   201,   107,   110,   112,   108,   108,
     109,   111,    88,   186,   270,   105,   106,     8,     9,    10,
      99,   100,   113,   361,   199,   199,   199,   116,   117,   118,
     119,   267,   268,   127,    99,   100,   424,   425,    75,   123,
     220,    56,    57,   256,   257,     3,   -85,   183,   181,   283,
      17,    18,   217,    61,    62,   384,   281,    24,    80,   254,
     286,   340,   287,   260,    28,    64,    69,    78,  -221,   218,
     284,   436,   437,   438,   439,   -87,    83,   190,   191,   271,
     288,    70,   276,   279,   -85,   304,    35,    86,   221,   184,
     101,    37,   258,   460,   124,   185,   102,   269,   275,   278,
     200,   274,   277,   341,   101,   440,   441,   255,   185,   342,
     221,   211,   442,   -87,   134,   135,   136,   137,   138,   443,
     139,    45,    40,   140,   141,   453,   392,   393,   255,    96,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,    56,    57,   260,   147,   148,   149,   150,   322,
     151,   152,   153,   454,    61,    62,   333,   259,  -110,   131,
     132,    81,   282,    82,   313,   317,    64,    69,   421,   422,
     272,   327,   328,   103,   260,   305,   306,   114,   260,   349,
     -68,   115,    70,   352,   133,   314,   318,   423,   128,   297,
     298,   129,   -62,   192,   334,   205,   177,    79,   130,   193,
     166,   -63,   105,   412,   413,   414,   415,   -73,   170,   181,
     -62,   171,   375,   205,   338,    79,   339,   376,   343,   149,
     150,   172,   151,   152,   153,   173,   174,   310,   311,     5,
       6,     7,     8,     9,    10,   175,   312,    17,    18,   316,
     308,   151,   152,   153,    24,   176,   323,   324,   178,   179,
     182,   416,   326,   180,   134,   135,   136,   137,   138,   102,
     139,   377,   194,  -222,  -222,    17,    18,    19,    85,   195,
      22,    23,    24,    35,    86,   196,   350,   351,    37,    28,
     353,   354,   355,   197,   198,   397,   398,   203,   204,   165,
     402,   206,   210,    31,    32,   212,   213,   214,   215,    33,
      34,    35,    86,   261,   262,   280,    37,   149,   150,   263,
     151,   152,   153,   368,   264,   -62,   290,   -62,   285,   382,
     383,   289,   -62,   -62,   -62,   -62,   -62,   299,   300,   302,
     303,   -62,   -62,   -62,   315,   319,   320,   199,   321,   325,
     336,   337,   406,   407,   344,   347,   345,   359,   356,   360,
     386,   401,   357,   358,   366,   417,   371,   -62,   108,  -220,
     419,   389,   369,   370,   372,   432,   373,   380,   381,   385,
     403,   -62,   404,   408,   409,   464,    79,   410,     6,     7,
       8,     9,    10,   411,   417,   420,   426,   108,   433,   419,
     427,   431,   434,   429,   -71,   461,   456,   363,   -72,   -70,
     449,   -69,   448,   451,   458,   450,   466,   446,   362,   455,
     292,   445,   273,    17,    18,   447,    85,   187,    22,    23,
      24,     0,   188,   428,   465,    45,    40,    28,   457,     0,
       0,   459,     0,    45,    40,    45,    40,     0,   463,    45,
      40,    31,    32,     0,     0,     0,     0,    33,    34,    35,
      86,     0,     0,     0,    37,   134,   135,   136,   137,   138,
       0,   139,     0,     0,   140,   141,    56,    57,     0,     0,
       0,     0,     0,     0,    56,    57,    56,    57,    61,    62,
      56,    57,     0,     0,     0,     0,    61,    62,    61,    62,
      64,    69,    61,    62,     0,     0,     0,     0,    64,    69,
      64,    69,     0,     0,    64,    69,    70,   148,   149,   150,
       0,   151,   152,   153,    70,     0,    70,     0,     0,     0,
      70,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      14,     0,     0,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     0,     0,     0,    25,    26,
      27,    28,    29,     0,     0,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,    33,    34,    35,    36,   216,     0,     0,    37,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,     0,
       0,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,     0,     0,    25,    26,    27,    28,
      29,     0,     0,    30,     0,     0,   134,   135,   136,   137,
     138,     0,   139,    31,    32,   140,   141,     0,     0,    33,
      34,    35,    36,     0,     0,     0,    37,   134,   135,   136,
     137,   138,     0,   139,     0,     0,   140,   141,     0,     0,
       0,     0,     0,     0,   142,   143,   144,   145,   134,   135,
     136,   137,   138,     0,   139,     0,     0,   140,   141,   149,
     150,     0,   151,   152,   153,   142,   143,   144,   145,     0,
       0,     0,     0,     0,     0,     0,     0,   146,   147,   148,
     149,   150,     0,   151,   152,   153,     0,  -222,  -222,  -222,
    -222,   138,     0,   139,     0,   301,     0,     0,   146,   147,
     148,   149,   150,     0,   151,   152,   153,     0,   134,   135,
     136,   137,   138,     0,   139,     0,   430,   140,   141,     0,
       0,     0,     0,     0,     0,   142,   143,   144,   145,   134,
     135,   136,   137,   138,     0,   139,     0,     0,   140,   141,
     149,   150,     0,   151,   152,   153,   142,   143,   144,   145,
       0,     0,     0,     0,     0,     0,     0,     0,   146,   147,
     148,   149,   150,     0,   151,   152,   153,     0,     0,     0,
       0,     0,     0,     0,     0,   219,     0,     0,     0,   146,
     147,   148,   149,   150,     0,   151,   152,   153,   134,   135,
     136,   137,   138,     0,   139,     0,   265,   140,   141,     0,
       0,     0,     0,     0,     0,   142,   143,   144,   145,   134,
     135,   136,   137,   138,     0,   139,     0,     0,   140,   141,
       0,     0,     0,     0,     0,     0,   142,   143,   144,   145,
       0,     0,     0,     0,     0,     0,     0,     0,   146,   147,
     148,   149,   150,     0,   151,   152,   153,     0,     0,     0,
       0,     0,     0,     0,     0,   266,     0,     0,     0,   146,
     147,   148,   149,   150,     0,   151,   152,   153,   134,   135,
     136,   137,   138,     0,   139,     0,   296,   140,   141,     0,
       0,     0,     0,     0,     0,   142,   143,   144,   145,   134,
     135,   136,   137,   138,     0,   139,     0,     0,   140,   141,
       0,     0,     0,     0,     0,     0,   142,   143,   144,   145,
       0,     0,     0,     0,     0,     0,     0,     0,   146,   147,
     148,   149,   150,     0,   151,   152,   153,     0,     0,     0,
       0,     0,     0,     0,     0,   462,     0,     0,     0,   146,
     147,   148,   149,   150,     0,   151,   152,   153,   134,   135,
     136,   137,   138,     0,   139,     0,     0,   140,   141,     0,
     134,   135,   136,   137,   138,   142,   139,   144,   145,   140,
     141,     0,   134,   135,   136,   137,   138,   142,   139,   144,
       0,   140,   141,   134,   135,   136,   137,   138,     0,   139,
       0,   144,   140,   141,     0,     0,     0,     0,   146,   147,
     148,   149,   150,     0,   151,   152,   153,     0,     0,     0,
     146,   147,   148,   149,   150,     0,   151,   152,   153,     0,
       0,     0,   146,   147,   148,   149,   150,     0,   151,   152,
     153,     0,     0,   146,   147,   148,   149,   150,     0,   151,
     152,   153,   -63,     0,   -63,     0,     0,     0,     0,   -63,
     -63,   -63,   -63,   -63,   154,     0,   155,     0,   -63,   -63,
     -63,   156,   157,   158,   159,   160,     0,   167,   168,     0,
     161,   162,   163,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -63,     0,     0,     0,     0,     0,
       0,     0,   169,     0,     0,   -64,   164,   -64,   -63,     0,
       0,     0,   -64,   -64,   -64,   -64,   -64,     0,     0,     0,
     165,   -64,   -64,   -64,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -64
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     2,    21,   102,    22,    23,    25,    22,    23,
      22,    23,    16,    79,     5,     4,     5,     6,     7,     8,
       4,     5,    26,   330,     5,     5,     5,    31,    32,    33,
      34,     4,     5,    37,     4,     5,   395,   396,     5,     8,
       5,     4,     4,     4,     5,     0,     3,     5,    61,    60,
      39,    40,    60,     4,     4,   362,    69,    46,    80,     5,
       5,     5,     5,   182,    53,     4,     4,    69,    63,    77,
      81,     5,     6,     7,     8,     3,     5,    81,    82,    70,
       5,     4,   196,   197,    41,    80,    75,    76,    53,    47,
      74,    80,    53,   452,    63,    53,    80,    70,   196,   197,
      81,    81,    81,    47,    74,    39,    40,    53,    53,    53,
      53,   115,    46,    41,    14,    15,    16,    17,    18,    53,
      20,   125,   125,    23,    24,     5,    58,    59,    53,    53,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   125,   125,   283,    65,    66,    67,    68,   283,
      70,    71,    72,    53,   125,   125,     3,   181,    42,    44,
      45,    80,   200,    80,    60,    60,   125,   125,    58,    59,
     194,    55,    56,    76,   313,   261,   262,     4,   317,   313,
      63,    80,   125,   317,    69,    81,    81,    77,    79,   213,
     214,    79,    75,    63,    41,    69,    63,    80,    79,    69,
      79,    75,     4,     5,     6,     7,     8,    63,    79,    61,
      75,    79,    75,    69,   300,    80,   302,    80,   304,    67,
      68,    79,    70,    71,    72,    79,    79,   265,   266,     3,
       4,     5,     6,     7,     8,    79,   274,    39,    40,   277,
     264,    70,    71,    72,    46,    79,   284,   285,    79,    79,
      60,    53,   290,    79,    14,    15,    16,    17,    18,    80,
      20,   347,    61,    23,    24,    39,    40,    41,    42,    60,
      44,    45,    46,    75,    76,    80,   314,   315,    80,    53,
     318,   319,   320,    80,     4,   371,   372,    69,    69,    75,
     376,    49,    76,    67,    68,    82,    60,    63,    77,    73,
      74,    75,    76,    80,    80,    80,    80,    67,    68,    81,
      70,    71,    72,   337,    79,    19,    48,    21,    81,   357,
     358,    80,    26,    27,    28,    29,    30,     8,    80,    80,
      69,    35,    36,    37,    81,    81,    81,     5,    69,     5,
      76,    63,   380,   381,    81,    79,    81,    77,    69,    42,
       5,   375,    81,    81,    79,   392,    80,    61,   392,    63,
     392,     5,    81,    81,    80,   403,    81,    81,    81,    79,
      81,    75,    13,    61,    60,   461,    80,    61,     4,     5,
       6,     7,     8,    60,   421,    63,    81,   421,    80,   421,
      81,    81,    12,    69,    63,    80,   434,   332,    63,    63,
     420,    63,    63,    63,    63,   421,    81,   410,   331,   433,
     208,   409,   195,    39,    40,   411,    42,    80,    44,    45,
      46,    -1,    80,   399,   462,   449,   449,    53,   448,    -1,
      -1,   451,    -1,   457,   457,   459,   459,    -1,   458,   463,
     463,    67,    68,    -1,    -1,    -1,    -1,    73,    74,    75,
      76,    -1,    -1,    -1,    80,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,   449,   449,    -1,    -1,
      -1,    -1,    -1,    -1,   457,   457,   459,   459,   449,   449,
     463,   463,    -1,    -1,    -1,    -1,   457,   457,   459,   459,
     449,   449,   463,   463,    -1,    -1,    -1,    -1,   457,   457,
     459,   459,    -1,    -1,   463,   463,   449,    66,    67,    68,
      -1,    70,    71,    72,   457,    -1,   459,    -1,    -1,    -1,
     463,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    -1,    -1,    80,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    20,    67,    68,    23,    24,    -1,    -1,    73,
      74,    75,    76,    -1,    -1,    -1,    80,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    67,
      68,    -1,    70,    71,    72,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    -1,    70,    71,    72,    -1,    14,    15,    16,
      17,    18,    -1,    20,    -1,    82,    -1,    -1,    64,    65,
      66,    67,    68,    -1,    70,    71,    72,    -1,    14,    15,
      16,    17,    18,    -1,    20,    -1,    82,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      67,    68,    -1,    70,    71,    72,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    14,    15,
      16,    17,    18,    -1,    20,    -1,    81,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    14,    15,
      16,    17,    18,    -1,    20,    -1,    81,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      14,    15,    16,    17,    18,    31,    20,    33,    34,    23,
      24,    -1,    14,    15,    16,    17,    18,    31,    20,    33,
      -1,    23,    24,    14,    15,    16,    17,    18,    -1,    20,
      -1,    33,    23,    24,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    -1,    70,    71,
      72,    -1,    -1,    64,    65,    66,    67,    68,    -1,    70,
      71,    72,    19,    -1,    21,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    30,    19,    -1,    21,    -1,    35,    36,
      37,    26,    27,    28,    29,    30,    -1,    44,    45,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    -1,    -1,    19,    61,    21,    75,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    -1,    -1,
      75,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75
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
     133,   137,   138,   144,   154,   157,    53,   142,   143,     4,
       5,    74,    80,    76,    88,     4,     5,    93,    95,   127,
      93,   127,    88,    94,     4,    80,    94,    94,    94,    94,
      94,   150,   151,     8,    63,    86,   119,    94,    79,    79,
      79,    44,    45,    69,    14,    15,    16,    17,    18,    20,
      23,    24,    31,    32,    33,    34,    64,    65,    66,    67,
      68,    70,    71,    72,    19,    21,    26,    27,    28,    29,
      30,    35,    36,    37,    61,    75,    79,    44,    45,    69,
      79,    79,    79,    79,    79,    79,    79,    63,    79,    79,
      79,    61,    60,     5,    47,    53,   150,   139,   151,   161,
      94,    94,    63,    69,    61,    60,    80,    80,     4,     5,
      81,   140,   147,    69,    69,    69,    49,   122,   123,   124,
      76,    94,    82,    60,    63,    77,    77,    60,    77,    81,
       5,    53,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,     5,    53,     4,     5,    53,    94,
     141,    80,    80,    81,    79,    81,    81,     4,     5,    70,
       5,    70,    94,   143,    81,   140,   147,    81,   140,   147,
      80,    69,    88,    60,    81,    81,     5,     5,     5,    80,
      48,   125,   124,   103,   104,   105,    81,    94,    94,     8,
      80,    82,    80,    69,    80,   150,   150,   158,    94,   162,
      88,    88,    88,    60,    81,    81,    88,    60,    81,    81,
      81,    69,   147,    88,    88,     5,    88,    55,    56,   115,
     116,   117,   106,     3,    41,   107,    76,    63,   150,   150,
       5,    47,    53,   150,    81,    81,   152,    79,   168,   147,
      88,    88,   147,    88,    88,    88,    69,    81,    81,    77,
      42,   148,   116,   107,   108,   109,    79,    98,    94,    81,
      81,    80,    80,    81,   132,    75,    80,   150,   163,   165,
      81,    81,    88,    88,   148,    79,     5,   111,   112,     5,
     113,   114,    58,    59,   100,   130,   131,   150,   150,   155,
     128,    94,   150,    81,    13,   169,    88,    88,    61,    60,
      61,    60,     5,     6,     7,     8,    53,    93,    99,   127,
      63,    58,    59,    77,   128,   128,    81,    81,   152,    69,
      82,    81,    88,    80,    12,   166,     5,     6,     7,     8,
      39,    40,    46,    53,   110,   112,   110,   114,    63,    86,
      99,    63,   156,     5,    53,    94,    88,    86,    63,    86,
     128,    80,    81,    86,   150,    88,    81
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
     101,   101,   102,   103,   103,   105,   104,   106,   104,   108,
     107,   109,   107,   110,   110,   110,   110,   110,   110,   110,
     110,   111,   111,   112,   112,   113,   113,   114,   115,   115,
     116,   116,   116,   117,   117,   118,   119,   119,   120,   120,
     121,   122,   123,   123,   124,   125,   125,   126,   127,   127,
     127,   127,   127,   127,   128,   128,   128,   128,   130,   129,
     131,   129,   132,   129,   133,   133,   133,   133,   133,   133,
     133,   133,   134,   134,   134,   134,   134,   134,   135,   135,
     136,   136,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   139,   139,   140,   140,   141,   141,   142,   142,
     143,   144,   145,   145,   146,   146,   146,   146,   146,   147,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   149,
     149,   149,   149,   150,   150,   151,   151,   152,   152,   152,
     153,   153,   155,   154,   154,   154,   154,   154,   154,   156,
     154,   158,   157,   159,   159,   160,   161,   161,   161,   162,
     162,   163,   164,   165,   165,   166,   166,   168,   169,   167
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
       2,     2,     6,     0,     1,     0,     3,     0,     4,     0,
       3,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     1,     3,     3,     0,     1,
       0,     1,     1,     2,     3,     3,     3,     5,     3,     3,
       2,     1,     1,     2,     5,     0,     2,     4,     3,     3,
       3,     3,     3,     3,     0,     6,     3,     3,     0,     8,
       0,     8,     0,     8,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     1,     3,     3,     1,     1,     3,
       3,     3,     1,     3,     4,     4,     4,     4,     2,     4,
       5,     5,     6,     6,     6,     6,     6,     8,     8,     4,
       5,     5,     7,     0,     1,     1,     3,     0,     4,     4,
       1,     3,     0,     8,     3,     3,     5,     5,     8,     0,
      10,     0,     6,     2,     1,     5,     0,     1,     1,     0,
       1,     1,     9,     0,     6,     0,     2,     0,     0,     9
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
      89,    79,    -1,    97,    -1,   137,    79,    -1,   138,    79,
      -1,    76,    86,    77,    -1,     4,    69,    47,    -1,     4,
      69,    47,    80,   150,    81,    -1,    22,    -1,    52,    -1,
      43,    88,    -1,     5,    -1,    53,    -1,     8,    -1,     6,
      -1,     7,    -1,    46,    -1,    39,    -1,    40,    -1,   120,
      -1,   118,    -1,    80,    94,    81,    -1,    96,    -1,   157,
      -1,    93,    -1,   101,    -1,   137,    -1,   136,    -1,   138,
      -1,   135,    -1,   134,    -1,   144,    -1,   133,    -1,   149,
      -1,    89,    -1,   129,    -1,   154,    -1,   127,    -1,     5,
      -1,   127,    -1,    96,    -1,    95,    75,    94,    82,    -1,
      -1,    57,    80,    94,    81,    76,    98,   100,    77,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
     127,    -1,    58,    99,    63,    86,    -1,    59,    63,    86,
      -1,   100,    58,    99,    63,    86,    -1,   100,    59,    63,
      86,    -1,    67,    94,    -1,    68,    94,    -1,    73,    94,
      -1,    74,    94,    -1,    54,     4,    76,   103,   115,    77,
      -1,    -1,   104,    -1,    -1,   105,   107,    79,    -1,    -1,
     104,   106,   107,    79,    -1,    -1,     3,   108,   111,    -1,
      -1,    41,   109,   113,    -1,     5,    -1,    53,    -1,     8,
      -1,     6,    -1,     7,    -1,    46,    -1,    39,    -1,    40,
      -1,   112,    -1,   111,    60,   112,    -1,     5,    61,   110,
      -1,     5,    -1,   114,    -1,   113,    60,   114,    -1,     5,
      61,   110,    -1,    -1,   117,    -1,    -1,    55,    -1,    56,
      -1,   116,   148,    -1,   117,   116,   148,    -1,    75,   150,
      82,    -1,     8,    63,    94,    -1,   119,    60,     8,    63,
      94,    -1,    76,    63,    77,    -1,    76,   119,    77,    -1,
      51,    94,    -1,   123,    -1,   124,    -1,   123,   124,    -1,
      49,    80,     5,    81,    88,    -1,    -1,    48,    88,    -1,
      50,    88,   122,   125,    -1,    93,    69,     5,    -1,     4,
      69,     5,    -1,    93,    69,    53,    -1,     4,    69,    53,
      -1,   127,    69,     5,    -1,   127,    69,    53,    -1,    -1,
     128,    69,     5,    80,   150,    81,    -1,   128,    69,     5,
      -1,   128,    69,    53,    -1,    -1,    93,    69,     5,    80,
     150,    81,   130,   128,    -1,    -1,   127,    69,     5,    80,
     150,    81,   131,   128,    -1,    -1,     4,    69,     5,    80,
     150,    81,   132,   128,    -1,    93,    44,    -1,    93,    45,
      -1,    44,    93,    -1,    45,    93,    -1,   127,    44,    -1,
     127,    45,    -1,    44,   127,    -1,    45,   127,    -1,    94,
      23,    94,    -1,    94,    24,    94,    -1,    94,    17,    94,
      -1,    94,    15,    94,    -1,    94,    16,    94,    -1,    94,
      14,    94,    -1,    94,    31,    94,    -1,    94,    33,    94,
      -1,    94,    32,    94,    -1,    94,    34,    94,    -1,    94,
      68,    94,    -1,    94,    67,    94,    -1,    94,    70,    94,
      -1,    94,    71,    94,    -1,    94,    72,    94,    -1,    95,
      26,    94,    -1,    95,    29,    94,    -1,    95,    27,    94,
      -1,    95,    28,    94,    -1,    95,    30,    94,    -1,    94,
      66,    94,    -1,    94,    64,    94,    -1,    94,    65,    94,
      -1,    94,    20,    94,    -1,    94,    18,    94,    -1,    95,
      35,    94,    -1,    95,    36,    94,    -1,    95,    37,    94,
      -1,    95,    21,    94,    -1,    95,    19,    94,    -1,     3,
     140,    -1,    41,   142,    -1,   141,    -1,   140,    60,   141,
      -1,     5,    61,    94,    -1,     5,    -1,   143,    -1,   142,
      60,   143,    -1,    53,    61,    94,    -1,    95,    61,    94,
      -1,     5,    -1,   145,    69,     5,    -1,    25,   145,    69,
      70,    -1,    25,   145,    63,    70,    -1,    25,   145,    63,
       5,    -1,    25,   145,    63,     4,    -1,    25,   145,    -1,
       5,    69,    69,    69,    -1,    42,     5,    80,    81,    88,
      -1,    42,     4,    80,    81,    88,    -1,    42,    74,     4,
      80,    81,    88,    -1,    42,     5,    80,   147,    81,    88,
      -1,    42,     4,    80,   147,    81,    88,    -1,    42,     5,
      80,   140,    81,    88,    -1,    42,     4,    80,   140,    81,
      88,    -1,    42,     5,    80,   140,    60,   147,    81,    88,
      -1,    42,     4,    80,   140,    60,   147,    81,    88,    -1,
      42,    80,    81,    88,    -1,    42,    80,   147,    81,    88,
      -1,    42,    80,   140,    81,    88,    -1,    42,    80,   140,
      60,   147,    81,    88,    -1,    -1,   151,    -1,    94,    -1,
     151,    60,    94,    -1,    -1,   152,    80,   150,    81,    -1,
     152,    75,    94,    82,    -1,     5,    -1,   153,    63,     5,
      -1,    -1,   153,    63,     5,    80,   150,    81,   155,   152,
      -1,   153,    63,    53,    -1,   153,    63,     5,    -1,   153,
      63,     4,    69,    53,    -1,   153,    63,     4,    69,    47,
      -1,   153,    63,     4,    69,    47,    80,   150,    81,    -1,
      -1,   153,    63,     4,    69,     5,    80,   150,    81,   156,
     128,    -1,    -1,     5,    80,   150,    81,   158,   152,    -1,
      38,    94,    -1,    38,    -1,    10,    80,    94,    81,    88,
      -1,    -1,   139,    -1,   151,    -1,    -1,    94,    -1,   150,
      -1,     9,    80,   161,    79,   162,    79,   163,    81,    88,
      -1,    -1,   165,    13,    80,    94,    81,    88,    -1,    -1,
      12,    88,    -1,    -1,    -1,    11,    80,    94,    81,    88,
     168,   165,   169,   166,    -1
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
     208,   211,   214,   221,   222,   224,   225,   229,   230,   235,
     236,   240,   241,   245,   247,   249,   251,   253,   255,   257,
     259,   261,   263,   267,   271,   273,   275,   279,   283,   284,
     286,   287,   289,   291,   294,   298,   302,   306,   312,   316,
     320,   323,   325,   327,   330,   336,   337,   340,   345,   349,
     353,   357,   361,   365,   369,   370,   377,   381,   385,   386,
     395,   396,   405,   406,   415,   418,   421,   424,   427,   430,
     433,   436,   439,   443,   447,   451,   455,   459,   463,   467,
     471,   475,   479,   483,   487,   491,   495,   499,   503,   507,
     511,   515,   519,   523,   527,   531,   535,   539,   543,   547,
     551,   555,   559,   562,   565,   567,   571,   575,   577,   579,
     583,   587,   591,   593,   597,   602,   607,   612,   617,   620,
     625,   631,   637,   644,   651,   658,   665,   672,   681,   690,
     695,   701,   707,   715,   716,   718,   720,   724,   725,   730,
     735,   737,   741,   742,   751,   755,   759,   765,   771,   780,
     781,   792,   793,   800,   803,   805,   811,   812,   814,   816,
     817,   819,   821,   831,   832,   839,   840,   843,   844,   845
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
     347,   348,   352,   356,   357,   361,   361,   362,   362,   366,
     366,   367,   367,   371,   372,   373,   374,   375,   376,   377,
     378,   382,   383,   387,   388,   392,   393,   397,   401,   402,
     406,   407,   408,   412,   413,   417,   421,   422,   426,   427,
     431,   435,   439,   440,   444,   448,   449,   453,   457,   458,
     459,   460,   461,   462,   466,   467,   468,   469,   473,   473,
     474,   474,   475,   475,   479,   480,   481,   482,   483,   484,
     485,   486,   490,   491,   492,   493,   494,   495,   499,   500,
     504,   505,   509,   510,   511,   512,   513,   514,   515,   516,
     517,   518,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   535,   536,   540,   541,   545,   546,   550,   551,
     555,   559,   563,   564,   568,   569,   570,   571,   572,   576,
     580,   582,   584,   586,   588,   590,   592,   594,   596,   601,
     603,   605,   607,   612,   613,   617,   618,   622,   623,   624,
     628,   629,   633,   633,   634,   635,   636,   637,   638,   639,
     639,   643,   643,   647,   648,   652,   656,   657,   658,   662,
     663,   667,   671,   674,   676,   680,   681,   685,   686,   685
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
  const int Parser::yylast_ = 1221;
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

