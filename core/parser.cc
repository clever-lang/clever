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
		error(yyloc, "Cannot use critical block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.criticalblock) = new ast::CriticalBlock((yysemantic_stack_[(2) - (2)].block), yyloc);
#endif
	}
    break;

  case 43:

    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 53:

    { (yysemantic_stack_[(1) - (1)].assignment)->setUseResult(); }
    break;

  case 61:

    { (yysemantic_stack_[(1) - (1)].property)->setWriteMode(); }
    break;

  case 63:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 64:

    { (yyval.node) = new ast::Switch((yysemantic_stack_[(5) - (3)].node), yyloc); }
    break;

  case 65:

    { (yyval.switch_) = (yysemantic_stack_[(8) - (7)].switch_); }
    break;

  case 72:

    { (yysemantic_stack_[(4) - (0)].switch_)->addCase((yysemantic_stack_[(4) - (2)].node), (yysemantic_stack_[(4) - (4)].block)); (yyval.switch_) = (yysemantic_stack_[(4) - (0)].switch_); }
    break;

  case 73:

    { (yysemantic_stack_[(3) - (0)].switch_)->addCase(NULL, (yysemantic_stack_[(3) - (3)].block)); (yyval.switch_) = (yysemantic_stack_[(3) - (0)].switch_);     }
    break;

  case 74:

    { (yysemantic_stack_[(5) - (0)].switch_)->addCase((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block)); (yyval.switch_) = (yysemantic_stack_[(5) - (0)].switch_); }
    break;

  case 75:

    { (yysemantic_stack_[(4) - (0)].switch_)->addCase(NULL, (yysemantic_stack_[(4) - (4)].block)); (yyval.switch_) = (yysemantic_stack_[(4) - (0)].switch_);     }
    break;

  case 76:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 77:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 78:

    { (yyval.node) = new ast::Boolean(ast::Boolean::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 79:

    { (yyval.node) = new ast::Bitwise(ast::Bitwise::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 80:

    { (yyval.class_) = new ast::ClassDef((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 81:

    { (yyval.narray) = NULL; }
    break;

  case 83:

    { (yyval.narray) = new ast::NodeArray(yyloc); }
    break;

  case 84:

    { (yyval.narray) = (yysemantic_stack_[(3) - (1)].narray); }
    break;

  case 85:

    { (yyval.narray) = (yysemantic_stack_[(1) - (1)].narray); }
    break;

  case 87:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 89:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 99:

    { (yysemantic_stack_[(1) - (0)].narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 100:

    { (yysemantic_stack_[(3) - (0)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 101:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), false, yyloc); }
    break;

  case 102:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(1) - (1)].ident), NULL, false, yyloc);     }
    break;

  case 103:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 104:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 105:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), true, yyloc);   }
    break;

  case 106:

    { (yyval.narray) = NULL; }
    break;

  case 108:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 109:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 110:

    { (yyval.flags) = ast::PRIVATE; }
    break;

  case 111:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(2) - (2)].fdecl)); (yysemantic_stack_[(2) - (2)].fdecl)->setVisibility((yysemantic_stack_[(2) - (1)].flags)); }
    break;

  case 112:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].fdecl)); (yysemantic_stack_[(3) - (3)].fdecl)->setVisibility((yysemantic_stack_[(3) - (2)].flags)); }
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

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 166:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 167:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 168:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 169:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 170:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 171:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 172:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 173:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 174:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 175:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 176:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 177:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 178:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 179:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 180:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 181:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 182:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 183:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 184:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 185:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 186:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 187:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 188:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 189:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 190:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 191:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 192:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 193:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 194:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 195:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 196:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 197:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 198:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 199:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 200:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 201:

    { (yyval.narray) = NULL; }
    break;

  case 203:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 204:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 205:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 206:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 207:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 209:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 210:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 211:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 212:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 213:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 214:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 215:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 216:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 217:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 218:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 219:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 220:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 221:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 222:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 223:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 224:

    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); }
    break;

  case 225:

    { if ((yysemantic_stack_[(1) - (1)].narray)) { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); } else { (yyval.node) = new ast::Block(yyloc); } }
    break;

  case 226:

    { (yyval.node) = new ast::TrueLit(yyloc); }
    break;

  case 227:

    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); }
    break;

  case 228:

    { if ((yysemantic_stack_[(1) - (1)].narray)) { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); } else { (yyval.node) = NULL; } }
    break;

  case 229:

    { (yyval.block) = new ast::Block(yyloc); (yyval.block)->append((yysemantic_stack_[(9) - (3)].node)); size_t offset = 0; if ((yysemantic_stack_[(9) - (7)].node)) { (yysemantic_stack_[(9) - (9)].block)->append((yysemantic_stack_[(9) - (7)].node)); offset = (yysemantic_stack_[(9) - (7)].narray)->getSize(); } (yyval.block)->append(new ast::For((yysemantic_stack_[(9) - (5)].node), (yysemantic_stack_[(9) - (9)].block), yyloc, offset)); }
    break;

  case 231:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 232:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 233:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 234:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 235:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 236:

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
  const short int Parser::yypact_ninf_ = -330;
  const short int
  Parser::yypact_[] =
  {
      -330,     1,  -330,  -330,   472,    52,   -65,   142,  -330,  -330,
    -330,   -64,   -52,   -10,  -330,    73,   549,  -330,  -330,    50,
      30,    43,    48,    48,  -330,    43,   549,  -330,  -330,   107,
      57,   549,    29,   549,  -330,  -330,    65,   109,   117,  -330,
     139,    14,   159,  -330,  -330,  -330,  -330,   118,  -330,   147,
     119,   122,   154,   161,   167,  -330,    80,   171,   172,   185,
    -330,  -330,  -330,    92,   176,  -330,    33,   549,   496,   549,
     549,  -330,    78,   190,   549,   549,   549,   549,    29,  -330,
     139,   878,  -330,    77,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,   214,   219,  -330,   200,   201,
     278,  -330,  -330,   215,   150,   217,   208,    39,   217,    39,
     247,   878,   221,   549,   878,   216,   244,   242,   231,   249,
     127,   697,  -330,  -330,  -330,  -330,  -330,    15,   549,   549,
    -330,  -330,  -330,    26,  -330,  -330,  -330,  -330,  -330,    44,
    -330,  -330,  -330,   549,    52,   229,   232,  -330,   240,  -330,
    -330,   234,   718,   777,    21,     6,     9,  -330,  -330,  -330,
    -330,   549,   549,   549,   549,   549,   549,   549,   549,   549,
     549,   549,   549,   549,   549,   549,   549,   549,   549,   549,
     549,   549,    50,    12,    24,   243,    45,    54,    60,   248,
     279,   247,  -330,    40,   798,  -330,   549,   549,  -330,  -330,
     326,  -330,  -330,   255,  -330,   949,   616,   259,  -330,   271,
     158,  -330,   878,  -330,   549,   549,  -330,   549,    43,    43,
    -330,  -330,  -330,  -330,  -330,    16,    43,    74,   260,   302,
     302,   302,   302,   177,   177,   333,   333,   961,   937,   972,
     949,  1031,   195,   595,   157,   157,  -330,  -330,  -330,   878,
    -330,    43,   121,   261,    43,   125,   262,   263,  -330,  -330,
    -330,   340,    43,  -330,  -330,    93,    41,    42,   282,   878,
     878,   291,   549,  -330,   549,    53,   549,   274,   280,  -330,
     878,   281,  -330,  -330,   293,  -330,   362,    43,    43,  -330,
     362,    43,    43,  -330,   362,    43,    43,    43,   287,  -330,
    -330,  -330,   298,   334,    93,    42,  -330,  -330,   300,  -330,
     549,   296,   299,   301,   303,  -330,   304,  -330,  -330,   151,
     549,  -330,   315,   305,  -330,  -330,   306,  -330,  -330,   307,
    -330,  -330,  -330,    43,  -330,  -330,   334,   310,   385,   387,
    -330,   -12,   878,  -330,  -330,   549,   549,  -330,  -330,   549,
     549,  -330,   313,   382,  -330,    43,    43,    43,  -330,  -330,
    -330,   336,   338,  -330,   346,   348,  -330,    56,   347,   165,
    -330,  -330,   328,   330,  -330,   343,   637,   332,    43,   335,
     402,  -330,  -330,  -330,   325,   385,   325,   387,    70,   353,
     354,   355,   357,   217,   359,   126,  -330,    56,   360,  -330,
     343,   343,  -330,  -330,   151,    64,  -330,  -330,  -330,   549,
      43,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,   472,   363,  -330,  -330,   345,
    -330,   857,  -330,   472,  -330,   472,   343,   549,    43,   472,
     358,  -330,  -330
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    33,    36,    37,
      35,     0,     0,     0,    30,     0,   222,    39,    40,     0,
       0,     0,     0,     0,    38,     0,     0,    31,    34,     0,
       0,   201,     4,     0,     5,    17,     0,     0,     0,    18,
       0,     0,    44,    26,    23,    42,    41,     0,    22,    61,
       0,     0,     0,     0,     0,    11,     0,     0,    45,     0,
      14,    15,    13,   175,   170,   172,     0,   201,   201,     0,
       0,   180,   186,     0,     0,     0,     0,     0,     0,    56,
      46,   221,    47,    59,    57,    54,    52,    51,    49,    48,
      50,    53,    55,    58,    45,     0,   171,   176,     0,     0,
       0,     4,    32,     0,    33,   144,     0,   148,   145,   149,
       0,   118,     0,     0,   203,     0,   202,     0,     0,     0,
       0,     0,    25,    20,    21,   142,   143,     0,     0,     0,
      19,   146,   147,     0,    10,    16,     7,     8,     6,     0,
      24,     9,    12,     0,     0,   127,    28,   129,     0,   224,
     225,     0,     0,     0,     0,     0,     0,    76,    77,    78,
      79,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   119,   120,    81,     0,   113,     0,     0,   116,    27,
       0,   117,    43,   126,   128,   179,     0,   130,   131,     0,
     213,   212,   174,   173,   201,   201,   219,   226,     0,     0,
     185,   184,   183,   181,   182,   175,     0,     0,     0,   155,
     153,   154,   152,   169,   168,   150,   151,   156,   158,   157,
     159,   166,   167,   165,   161,   160,   162,   163,   164,   178,
     177,     0,     0,     0,     0,     0,     0,     0,   127,   126,
     130,     0,     0,   125,   121,   106,    82,     0,     0,   204,
     114,     0,   201,    63,   201,     0,   201,     0,     0,   205,
     227,     0,   223,   234,     0,   197,     0,     0,     0,   189,
       0,     0,     0,   188,     0,     0,     0,     0,     0,   124,
     109,   110,     0,     0,   107,     0,    87,    89,     0,    64,
       0,     0,     0,     0,   215,   214,     0,   140,    29,   220,
     201,   230,     0,     0,   199,   198,     0,   194,   192,     0,
     193,   191,   190,     0,    80,   111,     0,     0,     0,     0,
      84,     0,   115,   136,   138,   201,   201,   210,   132,     0,
     201,   228,     0,   235,   187,     0,     0,     0,   122,   112,
      86,   102,    88,    99,     0,    90,   103,     0,     0,     0,
     132,   132,     0,     0,   205,   141,     0,     0,     0,     0,
     232,   200,   196,   195,     0,     0,     0,     0,    33,    36,
      37,    35,    34,     0,     0,    61,     4,     0,     0,    65,
     137,   139,   217,   216,   211,     0,   207,   206,   229,     0,
       0,   236,    91,    94,    95,    93,    97,    98,    96,    92,
     101,   100,   105,   104,     4,    73,     0,     4,   132,   134,
     135,     0,   233,    72,     4,    75,   218,   201,     0,    74,
       0,   231,   133
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -330,  -330,  -330,     3,  -330,   -19,     8,  -330,  -330,  -330,
      -4,    -3,   -15,  -330,  -330,  -330,    31,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,   135,  -330,  -330,    63,  -330,    66,
    -330,    55,  -330,   148,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,   270,  -330,  -330,    -1,  -329,    11,  -330,  -330,  -330,
      20,  -330,  -330,  -330,  -330,  -330,   386,   -27,  -104,  -330,
     284,    23,  -330,  -330,  -174,  -252,  -330,   -35,  -330,    89,
    -330,    32,  -330,  -330,    35,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   119,    34,    35,    79,    37,    38,    39,
      80,   114,    41,    42,    43,   341,   394,   369,    82,    44,
     265,   266,   267,   305,   308,   338,   339,   420,   362,   363,
     365,   366,   302,   303,   304,    45,   120,    46,    47,   190,
     191,   192,   263,    48,    83,   375,    84,   370,   371,   348,
      85,    86,    87,    88,    89,    90,    52,    64,    65,    96,
      97,    91,    72,    54,   228,    55,    92,   115,   116,   319,
      56,    93,   374,   428,    94,   279,    59,    60,   151,   281,
     352,    61,   353,   411,    62,   321,   380
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -210;
  const short int
  Parser::yytable_[] =
  {
        40,     3,   102,    49,    66,     4,   110,   106,   106,   253,
     256,   223,    36,    81,   225,    50,    68,   225,   105,   108,
     203,   107,   109,   111,    51,   220,   221,    53,    69,   225,
     121,   207,   148,   150,    98,    99,    57,   117,   145,    58,
     213,   400,   401,   -83,   -85,   306,   367,   368,   209,   210,
     258,   335,   103,   104,     8,     9,    10,    63,   313,   259,
     103,   388,   389,   390,   391,   260,   152,   153,   204,   429,
      70,   157,   158,   159,   160,   128,   224,   143,    71,   208,
     146,   -83,   -85,   307,   359,   284,   147,    17,    18,   129,
     226,   222,   118,   251,    24,    17,    18,   211,   147,   436,
     314,    28,    24,    95,   100,   254,   315,   204,   188,   392,
     194,   112,   323,   208,   -61,    40,   326,   430,    49,   101,
     329,   131,   132,    31,    78,   205,   206,    36,    33,   227,
      50,    31,    78,   -66,   286,  -108,    33,   113,   -61,    51,
     212,   154,    53,   139,   122,   -60,   133,   155,   300,   301,
      67,    57,   -61,   143,    58,   287,   252,   255,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   277,
     278,   290,   213,   125,   126,   294,   213,   200,   123,   -71,
     213,   131,   132,   269,   270,   188,   124,   130,   134,   282,
     283,   135,   291,   -60,   201,  -208,   295,   285,   127,   161,
     162,   163,   164,   165,   280,   166,   133,   -60,   167,   168,
     -62,  -209,    67,   397,   398,   -60,   349,   178,   179,   180,
      67,   350,   289,   136,   -62,   293,   144,   311,   276,   312,
     137,   316,   399,   299,   176,   177,   138,   178,   179,   180,
     140,   141,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   175,   176,   177,   142,   178,   179,   180,   324,   325,
     156,    14,   327,   328,    15,   181,   330,   331,   332,   182,
     183,   184,   185,   129,   186,   351,   187,    16,    17,    18,
      19,    20,    21,    22,    23,    24,   189,   193,   195,    25,
      26,    27,    28,    29,   196,   197,    30,   342,   198,   214,
     372,   373,   215,   217,   358,   377,  -210,  -210,  -210,  -210,
     165,   216,   166,   257,    31,    32,   199,   262,   261,    33,
     412,   413,   414,   415,   271,   272,   381,   382,   383,   274,
     275,   288,   292,   296,   297,   298,   376,   161,   162,   163,
     164,   165,   106,   166,   310,   317,  -210,  -210,   309,   408,
     320,   318,   322,   393,   416,   417,   395,   225,   333,   176,
     177,   418,   178,   179,   180,   334,    20,   343,   419,   340,
     344,   345,   106,   346,   354,   347,   355,   356,   357,   360,
     361,   432,   364,   393,   378,   379,   395,   384,   385,   425,
     176,   177,   440,   178,   179,   180,   431,   386,   387,   402,
     396,   403,   405,   407,   410,   409,   -69,   -70,   -68,   441,
     -67,    40,   424,   427,    49,   437,   434,   433,   426,    40,
     435,    40,    49,    36,    49,    40,    50,   439,    49,   442,
     337,    36,   423,    36,    50,    51,    50,    36,    53,   422,
      50,   421,   336,    51,   149,    51,    53,    57,    53,    51,
      58,   264,    53,   404,     0,    57,   250,    57,    58,     0,
      58,    57,     0,     0,    58,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,     0,     0,    15,     0,     5,
       6,     7,     8,     9,    10,     0,     0,     0,     0,     0,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     0,
       0,     0,    25,    26,    27,    28,    29,     0,     0,    30,
       0,     0,     0,     0,     0,    17,    18,    19,    73,     0,
      22,    23,    24,     0,     0,     0,     0,    31,    32,    28,
       0,     0,    33,     6,     7,     8,     9,    10,     0,     0,
       0,     0,     0,    74,    75,     0,     0,     0,     0,    76,
      77,    31,    78,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,    18,
       0,    73,     0,    22,    23,    24,     0,     0,     0,     0,
       0,     0,    28,     0,     0,     0,     0,     0,     0,   161,
     162,   163,   164,   165,     0,   166,    74,    75,   167,   168,
       0,     0,    76,    77,    31,    78,     0,     0,     0,    33,
     161,   162,   163,   164,   165,     0,   166,     0,     0,   167,
     168,     0,     0,     0,     0,     0,     0,   169,   170,   171,
     172,   161,   162,   163,   164,   165,     0,   166,     0,     0,
     167,   168,   176,   177,     0,   178,   179,   180,   169,   170,
     171,   172,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   174,   175,   176,   177,     0,   178,   179,   180,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   273,     0,
       0,   173,   174,   175,   176,   177,     0,   178,   179,   180,
       0,   161,   162,   163,   164,   165,     0,   166,     0,   406,
     167,   168,     0,     0,     0,     0,     0,     0,   169,   170,
     171,   172,   161,   162,   163,   164,   165,     0,   166,     0,
       0,   167,   168,     0,     0,     0,     0,     0,     0,   169,
     170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,   173,   174,   175,   176,   177,     0,   178,   179,   180,
       0,     0,     0,     0,     0,     0,     0,     0,   202,     0,
       0,     0,   173,   174,   175,   176,   177,     0,   178,   179,
     180,   161,   162,   163,   164,   165,     0,   166,     0,   218,
     167,   168,     0,     0,     0,     0,     0,     0,   169,   170,
     171,   172,   161,   162,   163,   164,   165,     0,   166,     0,
       0,   167,   168,     0,     0,     0,     0,     0,     0,   169,
     170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,   173,   174,   175,   176,   177,     0,   178,   179,   180,
       0,     0,     0,     0,     0,     0,     0,     0,   219,     0,
       0,     0,   173,   174,   175,   176,   177,     0,   178,   179,
     180,   161,   162,   163,   164,   165,     0,   166,     0,   268,
     167,   168,     0,     0,     0,     0,     0,     0,   169,   170,
     171,   172,   161,   162,   163,   164,   165,     0,   166,     0,
       0,   167,   168,     0,     0,     0,     0,     0,     0,   169,
     170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,   173,   174,   175,   176,   177,     0,   178,   179,   180,
       0,     0,     0,     0,     0,     0,     0,     0,   438,     0,
       0,     0,   173,   174,   175,   176,   177,     0,   178,   179,
     180,   161,   162,   163,   164,   165,     0,   166,     0,     0,
     167,   168,     0,   161,   162,   163,   164,   165,   169,   166,
     171,   172,   167,   168,     0,   161,   162,   163,   164,   165,
     169,   166,   171,     0,   167,   168,   161,   162,   163,   164,
     165,     0,   166,     0,   171,   167,   168,     0,     0,     0,
       0,   173,   174,   175,   176,   177,     0,   178,   179,   180,
       0,     0,     0,   173,   174,   175,   176,   177,     0,   178,
     179,   180,     0,     0,     0,   173,   174,   175,   176,   177,
       0,   178,   179,   180,     0,     0,   173,   174,   175,   176,
     177,     0,   178,   179,   180,   161,   162,   163,   164,   165,
       0,   166,     0,     0,   167,   168,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   174,   175,   176,   177,
       0,   178,   179,   180
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     0,    21,     4,    69,     2,    25,    22,    23,   183,
     184,     5,     4,    16,     5,     4,    80,     5,    22,    23,
       5,    22,    23,    26,     4,     4,     5,     4,    80,     5,
      33,     5,    67,    68,     4,     5,     4,     8,     5,     4,
     144,   370,   371,     3,     3,     3,    58,    59,     4,     5,
       5,   303,     4,     5,     6,     7,     8,     5,     5,     5,
       4,     5,     6,     7,     8,     5,    69,    70,    53,     5,
      80,    74,    75,    76,    77,    61,    70,    61,     5,    53,
      47,    41,    41,    41,   336,    69,    53,    39,    40,    75,
      81,    70,    63,    81,    46,    39,    40,    53,    53,   428,
      47,    53,    46,    53,    74,    81,    53,    53,    69,    53,
     113,     4,   286,    53,    75,   119,   290,    53,   119,    76,
     294,    44,    45,    75,    76,   128,   129,   119,    80,   156,
     119,    75,    76,    63,    60,    42,    80,    80,    61,   119,
     143,    63,   119,    63,    79,    75,    69,    69,    55,    56,
      80,   119,    75,    61,   119,    81,   183,   184,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   214,
     215,    60,   286,    44,    45,    60,   290,    60,    79,    63,
     294,    44,    45,   196,   197,    69,    79,    79,    79,   218,
     219,    79,    81,    61,    77,    63,    81,   226,    69,    14,
      15,    16,    17,    18,   217,    20,    69,    75,    23,    24,
      61,    63,    80,    58,    59,    75,    75,    70,    71,    72,
      80,    80,   251,    79,    75,   254,    60,   272,    80,   274,
      79,   276,    77,   262,    67,    68,    79,    70,    71,    72,
      79,    79,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    66,    67,    68,    79,    70,    71,    72,   287,   288,
      80,    22,   291,   292,    25,    61,   295,   296,   297,    60,
      80,    80,     4,    75,    69,   320,    69,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    49,    76,    82,    50,
      51,    52,    53,    54,    60,    63,    57,   310,    77,    80,
     345,   346,    80,    79,   333,   350,    14,    15,    16,    17,
      18,    81,    20,    80,    75,    76,    77,    48,    80,    80,
       5,     6,     7,     8,     8,    80,   355,   356,   357,    80,
      69,    81,    81,    81,    81,     5,   349,    14,    15,    16,
      17,    18,   367,    20,    63,    81,    23,    24,    76,   378,
      79,    81,    69,   367,    39,    40,   367,     5,    81,    67,
      68,    46,    70,    71,    72,    77,    42,    81,    53,    79,
      81,    80,   397,    80,    69,    81,    81,    81,    81,    79,
       5,   410,     5,   397,    81,    13,   397,    61,    60,   396,
      67,    68,   437,    70,    71,    72,   409,    61,    60,    81,
      63,    81,    69,    81,    12,    80,    63,    63,    63,   438,
      63,   425,    63,    63,   425,    80,    63,   424,   397,   433,
     427,   435,   433,   425,   435,   439,   425,   434,   439,    81,
     305,   433,   387,   435,   433,   425,   435,   439,   425,   386,
     439,   385,   304,   433,    68,   435,   433,   425,   435,   439,
     425,   191,   439,   374,    -1,   433,   182,   435,   433,    -1,
     435,   439,    -1,    -1,   439,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    25,    -1,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    75,    76,    53,
      -1,    -1,    80,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      -1,    42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    14,
      15,    16,    17,    18,    -1,    20,    67,    68,    23,    24,
      -1,    -1,    73,    74,    75,    76,    -1,    -1,    -1,    80,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    67,    68,    -1,    70,    71,    72,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    70,    71,    72,
      -1,    14,    15,    16,    17,    18,    -1,    20,    -1,    82,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    -1,    70,    71,
      72,    14,    15,    16,    17,    18,    -1,    20,    -1,    81,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    -1,    70,    71,
      72,    14,    15,    16,    17,    18,    -1,    20,    -1,    81,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    -1,    70,    71,
      72,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    -1,    14,    15,    16,    17,    18,    31,    20,
      33,    34,    23,    24,    -1,    14,    15,    16,    17,    18,
      31,    20,    33,    -1,    23,    24,    14,    15,    16,    17,
      18,    -1,    20,    -1,    33,    23,    24,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,    70,
      71,    72,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    70,    71,    72,    -1,    -1,    64,    65,    66,    67,
      68,    -1,    70,    71,    72,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    70,    71,    72
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    84,    85,     0,    86,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    22,    25,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    50,    51,    52,    53,    54,
      57,    75,    76,    80,    87,    88,    89,    90,    91,    92,
      93,    95,    96,    97,   102,   118,   120,   121,   126,   127,
     129,   133,   139,   144,   146,   148,   153,   154,   157,   159,
     160,   164,   167,     5,   140,   141,    69,    80,    80,    80,
      80,     5,   145,    42,    67,    68,    73,    74,    76,    89,
      93,    94,   101,   127,   129,   133,   134,   135,   136,   137,
     138,   144,   149,   154,   157,    53,   142,   143,     4,     5,
      74,    76,    88,     4,     5,    93,    95,   127,    93,   127,
      88,    94,     4,    80,    94,   150,   151,     8,    63,    86,
     119,    94,    79,    79,    79,    44,    45,    69,    61,    75,
      79,    44,    45,    69,    79,    79,    79,    79,    79,    63,
      79,    79,    79,    61,    60,     5,    47,    53,   150,   139,
     150,   161,    94,    94,    63,    69,    80,    94,    94,    94,
      94,    14,    15,    16,    17,    18,    20,    23,    24,    31,
      32,    33,    34,    64,    65,    66,    67,    68,    70,    71,
      72,    61,    60,    80,    80,     4,    69,    69,    69,    49,
     122,   123,   124,    76,    94,    82,    60,    63,    77,    77,
      60,    77,    81,     5,    53,    94,    94,     5,    53,     4,
       5,    53,    94,   141,    80,    80,    81,    79,    81,    81,
       4,     5,    70,     5,    70,     5,    81,   140,   147,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
     143,    81,   140,   147,    81,   140,   147,    80,     5,     5,
       5,    80,    48,   125,   124,   103,   104,   105,    81,    94,
      94,     8,    80,    82,    80,    69,    80,   150,   150,   158,
      94,   162,    88,    88,    69,    88,    60,    81,    81,    88,
      60,    81,    81,    88,    60,    81,    81,    81,     5,    88,
      55,    56,   115,   116,   117,   106,     3,    41,   107,    76,
      63,   150,   150,     5,    47,    53,   150,    81,    81,   152,
      79,   168,    69,   147,    88,    88,   147,    88,    88,   147,
      88,    88,    88,    81,    77,   148,   116,   107,   108,   109,
      79,    98,    94,    81,    81,    80,    80,    81,   132,    75,
      80,   150,   163,   165,    69,    81,    81,    81,    88,   148,
      79,     5,   111,   112,     5,   113,   114,    58,    59,   100,
     130,   131,   150,   150,   155,   128,    94,   150,    81,    13,
     169,    88,    88,    88,    61,    60,    61,    60,     5,     6,
       7,     8,    53,    93,    99,   127,    63,    58,    59,    77,
     128,   128,    81,    81,   152,    69,    82,    81,    88,    80,
      12,   166,     5,     6,     7,     8,    39,    40,    46,    53,
     110,   112,   110,   114,    63,    86,    99,    63,   156,     5,
      53,    94,    88,    86,    63,    86,   128,    80,    81,    86,
     150,    88,    81
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
      90,    91,    92,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      95,    95,    95,    96,    98,    97,    99,    99,    99,    99,
      99,    99,   100,   100,   100,   100,   101,   101,   101,   101,
     102,   103,   103,   105,   104,   106,   104,   108,   107,   109,
     107,   110,   110,   110,   110,   110,   110,   110,   110,   111,
     111,   112,   112,   113,   113,   114,   115,   115,   116,   116,
     116,   117,   117,   118,   119,   119,   120,   120,   121,   122,
     123,   123,   124,   125,   125,   126,   127,   127,   127,   127,
     127,   127,   128,   128,   128,   128,   130,   129,   131,   129,
     132,   129,   133,   133,   133,   133,   133,   133,   133,   133,
     134,   134,   134,   134,   134,   134,   135,   135,   136,   136,
     137,   137,   137,   137,   137,   138,   138,   138,   138,   138,
     139,   139,   140,   140,   141,   141,   142,   142,   143,   144,
     145,   145,   146,   146,   146,   146,   146,   147,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   149,   149,   149,
     149,   150,   150,   151,   151,   152,   152,   152,   153,   153,
     155,   154,   154,   154,   154,   154,   154,   156,   154,   158,
     157,   159,   159,   160,   161,   161,   162,   162,   163,   164,
     165,   165,   166,   166,   168,   169,   167
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     1,     2,     1,     1,     2,
       2,     2,     1,     1,     2,     2,     1,     3,     3,     6,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     0,     8,     1,     1,     1,     1,
       1,     1,     4,     3,     5,     4,     2,     2,     2,     2,
       6,     0,     1,     0,     3,     0,     4,     0,     3,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     1,     3,     3,     0,     1,     0,     1,
       1,     2,     3,     3,     3,     5,     3,     3,     2,     1,
       1,     2,     5,     0,     2,     4,     3,     3,     3,     3,
       3,     3,     0,     6,     3,     3,     0,     8,     0,     8,
       0,     8,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     3,     3,     1,     1,     3,     3,     3,
       1,     3,     4,     4,     4,     4,     2,     4,     5,     5,
       6,     6,     6,     6,     6,     8,     8,     4,     5,     5,
       7,     0,     1,     1,     3,     0,     4,     4,     1,     3,
       0,     8,     3,     3,     5,     5,     8,     0,    10,     0,
       6,     2,     1,     5,     1,     1,     0,     1,     1,     9,
       0,     6,     0,     2,     0,     0,     9
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
      89,    79,    -1,    97,    -1,    76,    86,    77,    -1,     4,
      69,    47,    -1,     4,    69,    47,    80,   150,    81,    -1,
      22,    -1,    52,    -1,    43,    88,    -1,     5,    -1,    53,
      -1,     8,    -1,     6,    -1,     7,    -1,    46,    -1,    39,
      -1,    40,    -1,   120,    -1,   118,    -1,    80,    94,    81,
      -1,    96,    -1,   157,    -1,    93,    -1,   101,    -1,   137,
      -1,   136,    -1,   138,    -1,   135,    -1,   134,    -1,   144,
      -1,   133,    -1,   149,    -1,    89,    -1,   129,    -1,   154,
      -1,   127,    -1,     5,    -1,   127,    -1,    96,    -1,    95,
      75,    94,    82,    -1,    -1,    57,    80,    94,    81,    76,
      98,   100,    77,    -1,     5,    -1,    53,    -1,     8,    -1,
       6,    -1,     7,    -1,   127,    -1,    58,    99,    63,    86,
      -1,    59,    63,    86,    -1,   100,    58,    99,    63,    86,
      -1,   100,    59,    63,    86,    -1,    67,    94,    -1,    68,
      94,    -1,    73,    94,    -1,    74,    94,    -1,    54,     4,
      76,   103,   115,    77,    -1,    -1,   104,    -1,    -1,   105,
     107,    79,    -1,    -1,   104,   106,   107,    79,    -1,    -1,
       3,   108,   111,    -1,    -1,    41,   109,   113,    -1,     5,
      -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,    46,
      -1,    39,    -1,    40,    -1,   112,    -1,   111,    60,   112,
      -1,     5,    61,   110,    -1,     5,    -1,   114,    -1,   113,
      60,   114,    -1,     5,    61,   110,    -1,    -1,   117,    -1,
      -1,    55,    -1,    56,    -1,   116,   148,    -1,   117,   116,
     148,    -1,    75,   150,    82,    -1,     8,    63,    94,    -1,
     119,    60,     8,    63,    94,    -1,    76,    63,    77,    -1,
      76,   119,    77,    -1,    51,    94,    -1,   123,    -1,   124,
      -1,   123,   124,    -1,    49,    80,     5,    81,    88,    -1,
      -1,    48,    88,    -1,    50,    88,   122,   125,    -1,    93,
      69,     5,    -1,     4,    69,     5,    -1,    93,    69,    53,
      -1,     4,    69,    53,    -1,   127,    69,     5,    -1,   127,
      69,    53,    -1,    -1,   128,    69,     5,    80,   150,    81,
      -1,   128,    69,     5,    -1,   128,    69,    53,    -1,    -1,
      93,    69,     5,    80,   150,    81,   130,   128,    -1,    -1,
     127,    69,     5,    80,   150,    81,   131,   128,    -1,    -1,
       4,    69,     5,    80,   150,    81,   132,   128,    -1,    93,
      44,    -1,    93,    45,    -1,    44,    93,    -1,    45,    93,
      -1,   127,    44,    -1,   127,    45,    -1,    44,   127,    -1,
      45,   127,    -1,    94,    23,    94,    -1,    94,    24,    94,
      -1,    94,    17,    94,    -1,    94,    15,    94,    -1,    94,
      16,    94,    -1,    94,    14,    94,    -1,    94,    31,    94,
      -1,    94,    33,    94,    -1,    94,    32,    94,    -1,    94,
      34,    94,    -1,    94,    68,    94,    -1,    94,    67,    94,
      -1,    94,    70,    94,    -1,    94,    71,    94,    -1,    94,
      72,    94,    -1,    94,    66,    94,    -1,    94,    64,    94,
      -1,    94,    65,    94,    -1,    94,    20,    94,    -1,    94,
      18,    94,    -1,     3,   140,    -1,    41,   142,    -1,   141,
      -1,   140,    60,   141,    -1,     5,    61,    94,    -1,     5,
      -1,   143,    -1,   142,    60,   143,    -1,    53,    61,    94,
      -1,    95,    61,    94,    -1,     5,    -1,   145,    69,     5,
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
     151,    -1,    94,    -1,   151,    60,    94,    -1,    -1,   152,
      80,   150,    81,    -1,   152,    75,    94,    82,    -1,     5,
      -1,   153,    63,     5,    -1,    -1,   153,    63,     5,    80,
     150,    81,   155,   152,    -1,   153,    63,    53,    -1,   153,
      63,     5,    -1,   153,    63,     4,    69,    53,    -1,   153,
      63,     4,    69,    47,    -1,   153,    63,     4,    69,    47,
      80,   150,    81,    -1,    -1,   153,    63,     4,    69,     5,
      80,   150,    81,   156,   128,    -1,    -1,     5,    80,   150,
      81,   158,   152,    -1,    38,    94,    -1,    38,    -1,    10,
      80,    94,    81,    88,    -1,   139,    -1,   150,    -1,    -1,
      94,    -1,   150,    -1,     9,    80,   161,    79,   162,    79,
     163,    81,    88,    -1,    -1,   165,    13,    80,    94,    81,
      88,    -1,    -1,    12,    88,    -1,    -1,    -1,    11,    80,
      94,    81,    88,   168,   165,   169,   166,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     8,    11,    14,    17,    20,
      23,    26,    28,    31,    33,    35,    37,    40,    42,    44,
      47,    50,    53,    55,    57,    60,    63,    65,    69,    73,
      80,    82,    84,    87,    89,    91,    93,    95,    97,    99,
     101,   103,   105,   107,   111,   113,   115,   117,   119,   121,
     123,   125,   127,   129,   131,   133,   135,   137,   139,   141,
     143,   145,   147,   149,   154,   155,   164,   166,   168,   170,
     172,   174,   176,   181,   185,   191,   196,   199,   202,   205,
     208,   215,   216,   218,   219,   223,   224,   229,   230,   234,
     235,   239,   241,   243,   245,   247,   249,   251,   253,   255,
     257,   261,   265,   267,   269,   273,   277,   278,   280,   281,
     283,   285,   288,   292,   296,   300,   306,   310,   314,   317,
     319,   321,   324,   330,   331,   334,   339,   343,   347,   351,
     355,   359,   363,   364,   371,   375,   379,   380,   389,   390,
     399,   400,   409,   412,   415,   418,   421,   424,   427,   430,
     433,   437,   441,   445,   449,   453,   457,   461,   465,   469,
     473,   477,   481,   485,   489,   493,   497,   501,   505,   509,
     513,   516,   519,   521,   525,   529,   531,   533,   537,   541,
     545,   547,   551,   556,   561,   566,   571,   574,   579,   585,
     591,   598,   605,   612,   619,   626,   635,   644,   649,   655,
     661,   669,   670,   672,   674,   678,   679,   684,   689,   691,
     695,   696,   705,   709,   713,   719,   725,   734,   735,   746,
     747,   754,   757,   759,   765,   767,   769,   770,   772,   774,
     784,   785,   792,   793,   796,   797,   798
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   218,   218,   218,   222,   223,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   251,   255,   256,
     260,   264,   269,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     312,   313,   314,   318,   322,   322,   326,   327,   328,   329,
     330,   331,   335,   336,   337,   338,   342,   343,   344,   345,
     349,   353,   354,   358,   358,   359,   359,   363,   363,   364,
     364,   368,   369,   370,   371,   372,   373,   374,   375,   379,
     380,   384,   385,   389,   390,   394,   398,   399,   403,   404,
     405,   409,   410,   414,   418,   419,   423,   424,   428,   432,
     436,   437,   441,   445,   446,   450,   454,   455,   456,   457,
     458,   459,   463,   464,   465,   466,   470,   470,   471,   471,
     472,   472,   476,   477,   478,   479,   480,   481,   482,   483,
     487,   488,   489,   490,   491,   492,   496,   497,   501,   502,
     506,   507,   508,   509,   510,   514,   515,   516,   517,   518,
     522,   523,   527,   528,   532,   533,   537,   538,   542,   546,
     550,   551,   555,   556,   557,   558,   559,   563,   567,   569,
     571,   573,   575,   577,   579,   581,   583,   588,   590,   592,
     594,   599,   600,   604,   605,   609,   610,   611,   615,   616,
     620,   620,   621,   622,   623,   624,   625,   626,   626,   630,
     630,   634,   635,   639,   643,   644,   648,   649,   653,   657,
     661,   663,   667,   668,   672,   673,   672
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
  const int Parser::yylast_ = 1103;
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

