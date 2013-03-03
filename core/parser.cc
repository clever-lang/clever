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

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 167:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 168:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 169:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 170:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 171:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 172:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 173:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 174:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 175:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 176:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 177:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 178:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 179:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 180:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 181:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 182:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 183:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 184:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 185:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 186:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 187:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 188:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 189:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 190:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 191:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 192:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 193:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 194:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 195:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 196:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 197:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 198:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 199:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 200:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 201:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 202:

    { (yyval.narray) = NULL; }
    break;

  case 204:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 205:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 206:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 207:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 208:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 210:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 211:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 212:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 213:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 214:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 215:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 216:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 217:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 218:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 219:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 220:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 221:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 222:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 223:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 224:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 226:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 227:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 228:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 229:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 230:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 231:

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
  const short int Parser::yypact_ninf_ = -326;
  const short int
  Parser::yypact_[] =
  {
      -326,   125,  -326,  -326,   452,    45,    58,   145,  -326,  -326,
    -326,    55,   102,  -326,   220,   300,  -326,  -326,    83,    27,
     225,   154,    32,    32,  -326,   154,   300,  -326,  -326,   228,
     158,   300,    16,   300,  -326,  -326,   155,   180,   181,  -326,
    -326,    77,   151,   162,  -326,  -326,  -326,  -326,   182,  -326,
      88,   191,   194,   195,   200,   201,  -326,   185,   204,   205,
     206,  -326,  -326,   235,   237,  -326,    46,   300,   300,   300,
    -326,   116,   218,   300,   300,   300,   300,    16,  -326,    77,
     828,  -326,    81,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,   238,   240,  -326,   221,   222,   306,
      72,  -326,  -326,   241,     2,   242,   243,   111,   242,   111,
     263,   828,   239,   300,   828,   231,   256,   254,   247,   212,
     -13,   606,  -326,  -326,  -326,  -326,  -326,    42,   300,   300,
    -326,  -326,  -326,    44,  -326,  -326,  -326,  -326,  -326,    39,
    -326,  -326,  -326,   300,    45,   245,   246,  -326,   248,   666,
     687,    10,    17,     3,  -326,  -326,  -326,  -326,   300,   300,
     300,   300,   300,   300,   300,   300,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   300,   300,   300,   300,    83,
       7,     8,   250,   300,  -326,    47,    50,    51,   251,   279,
     263,  -326,    23,   747,  -326,   300,   300,  -326,  -326,   321,
    -326,  -326,   252,  -326,   909,   503,   253,  -326,   268,   121,
    -326,   828,  -326,   300,   300,  -326,   154,   154,  -326,  -326,
    -326,  -326,  -326,   -17,   154,   -15,   259,   563,   563,   563,
     563,   223,   223,   981,   981,   921,   849,   175,   909,   889,
     949,  1009,   132,   132,  -326,  -326,  -326,   828,  -326,   154,
      60,   261,   154,    63,   262,   267,   524,  -326,  -326,  -326,
     345,   154,  -326,  -326,    99,    70,    79,   275,   828,   828,
     289,   300,  -326,   300,    49,   300,   276,   278,  -326,  -326,
    -326,   287,  -326,   357,   154,   154,  -326,   357,   154,   154,
    -326,   357,   154,   154,   154,   154,   282,  -326,  -326,  -326,
     288,   323,    99,    79,  -326,  -326,   291,  -326,   300,   290,
     296,   292,   298,  -326,   301,  -326,  -326,    31,  -326,   312,
     302,  -326,  -326,   303,  -326,  -326,   304,  -326,  -326,  -326,
    -326,   154,  -326,  -326,   323,   309,   386,   389,  -326,   169,
     828,  -326,  -326,   300,   300,  -326,  -326,   300,   300,   382,
    -326,   154,   154,   154,  -326,  -326,  -326,   334,   337,  -326,
     338,   340,  -326,   316,   335,     9,  -326,  -326,   320,   322,
    -326,   336,   585,   325,   324,   396,  -326,  -326,  -326,    52,
     386,    52,   389,   130,   346,   347,   348,   356,   242,   368,
     118,  -326,   316,  -326,   336,   336,  -326,  -326,    31,    56,
    -326,  -326,   300,   154,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,   452,   369,
    -326,   328,  -326,   768,  -326,   452,  -326,   336,   300,   154,
     452,   352,  -326,  -326
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    35,    38,    39,
      37,     0,     0,    30,     0,   223,    41,    42,     0,     0,
       0,     0,     0,     0,    40,     0,     0,    31,    36,     0,
       0,   202,     4,     0,     5,    16,     0,     0,     0,    17,
      18,     0,     0,    46,    26,    23,    44,    43,     0,    22,
      63,     0,     0,     0,     0,     0,    11,     0,     0,    47,
       0,    14,    13,   176,   171,   173,     0,   202,     0,     0,
     181,   187,     0,     0,     0,     0,     0,     0,    58,    48,
     222,    49,    61,    59,    56,    54,    53,    51,    50,    52,
      55,    57,    60,    47,     0,   172,   177,     0,     0,     0,
       0,     4,    34,     0,    35,   145,     0,   149,   146,   150,
       0,   119,     0,     0,   204,     0,   203,     0,     0,     0,
       0,     0,    25,    20,    21,   143,   144,     0,     0,     0,
      19,   147,   148,     0,    10,    15,     7,     8,     6,     0,
      24,     9,    12,     0,     0,   128,    28,   130,     0,     0,
       0,     0,     0,     0,    77,    78,    79,    80,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,     0,     0,     0,     0,   124,
     120,   121,    82,     0,   114,     0,     0,   117,    27,     0,
     118,    45,   127,   129,   180,     0,   131,   132,     0,   214,
     213,   175,   174,   202,   202,   220,     0,     0,   186,   185,
     184,   182,   183,   176,     0,     0,     0,   156,   154,   155,
     153,   170,   169,   151,   152,   157,   159,   158,   160,   167,
     168,   166,   162,   161,   163,   164,   165,   179,   178,     0,
       0,     0,     0,     0,     0,     0,     0,   128,   127,   131,
       0,     0,   126,   122,   107,    83,     0,     0,   205,   115,
       0,   202,    65,   202,     0,   202,     0,     0,   206,   224,
     229,     0,   198,     0,     0,     0,   190,     0,     0,     0,
     189,     0,     0,     0,     0,     0,     0,   125,   110,   111,
       0,     0,   108,     0,    88,    90,     0,    66,     0,     0,
       0,     0,   216,   215,     0,   141,    29,   221,   225,     0,
       0,   200,   199,     0,   195,   193,     0,   194,   192,   191,
      33,     0,    81,   112,     0,     0,     0,     0,    85,     0,
     116,   137,   139,   202,   202,   211,   133,     0,   202,   230,
     188,     0,     0,     0,   123,   113,    87,   103,    89,   100,
       0,    91,   104,     0,     0,     0,   133,   133,     0,     0,
     206,   142,     0,     0,     0,   227,   201,   197,   196,     0,
       0,     0,     0,    35,    38,    39,    37,    36,     0,     0,
      63,     4,     0,    67,   138,   140,   218,   217,   212,     0,
     208,   207,     0,     0,   231,    92,    95,    96,    94,    98,
      99,    97,    93,   102,   101,   106,   105,     4,    75,     0,
     133,   135,   136,     0,   228,    74,     4,   219,   202,     0,
      76,     0,   226,   134
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -326,  -326,  -326,    28,  -326,   -16,    -3,  -326,  -326,  -326,
    -326,    -4,     1,   -12,  -326,  -326,  -326,    43,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,   133,  -326,  -326,    59,  -326,
      61,  -326,    65,  -326,   140,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,   258,  -326,  -326,    -2,  -325,    -1,  -326,  -326,
    -326,     0,  -326,  -326,  -326,  -326,  -326,  -326,  -118,  -137,
    -326,   271,    13,  -326,  -326,  -152,  -268,  -326,   -61,  -326,
      82,  -326,    19,  -326,  -326,    21,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   119,    34,    35,    78,    37,    38,    39,
      40,    79,   114,    42,    43,    44,   339,   389,   365,    81,
      45,   264,   265,   266,   303,   306,   336,   337,   413,   358,
     359,   361,   362,   300,   301,   302,    46,   120,    47,    48,
     189,   190,   191,   262,    49,    82,   371,    83,   366,   367,
     346,    84,    85,    86,    87,    88,    89,    53,    64,    65,
      95,    96,    90,    71,    55,   226,    56,    91,   115,   116,
     317,    57,    92,   370,   420,    93,   278,    60,    61,   349,
     404,    62,   318,   375
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -211;
  const short int
  Parser::yytable_[] =
  {
        41,    36,    50,    51,    52,   102,   148,   212,   223,   110,
     106,   106,   223,   223,   218,   219,    80,    54,   105,   108,
     107,   109,   221,    58,   117,    59,   -84,   111,   251,   254,
       4,    97,    98,   333,   121,   225,   103,   104,     8,     9,
      10,   394,   395,   208,   209,   143,   283,   202,   199,   206,
      63,   145,   257,   281,   311,   258,   259,   405,   406,   407,
     408,   421,   250,   253,   -84,   200,   355,   284,   392,   149,
     150,    16,    17,   -86,   154,   155,   156,   157,   -62,    24,
     118,   220,   304,    67,   184,   224,    28,   393,   222,   249,
     252,   409,   410,   210,   146,   427,   203,   312,   207,   411,
     147,   147,    99,   313,   203,   207,   412,   347,    31,    77,
     422,   -86,   348,    33,   193,    41,    36,    50,    51,    52,
     305,   287,   125,   126,   291,     3,   131,   132,    66,   204,
     205,   320,    54,   131,   132,   323,    68,    94,    58,   326,
      59,  -109,   288,   -63,   211,   292,   212,   127,   183,   101,
     212,   133,   276,   277,   212,   298,   299,   -63,   133,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     151,   187,   -73,    69,   256,  -210,   152,   -63,   187,   158,
     159,   160,   161,   162,   -68,   163,   268,   269,   164,   165,
     279,   280,   275,   175,   176,   177,   -62,   -62,   282,  -209,
     309,    67,   310,   128,   314,     5,     6,     7,     8,     9,
      10,   -62,    11,    12,   -64,    70,    67,   129,   363,   364,
     100,   101,   112,   286,    13,   122,   290,    14,   -64,   113,
     170,   171,   172,   173,   174,   297,   175,   176,   177,   139,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
     123,   124,   130,    25,    26,    27,    28,    29,   321,   322,
      30,   134,   324,   325,   135,   136,   327,   328,   329,   330,
     137,   138,   368,   369,   140,   141,   142,   373,    31,    32,
     198,   173,   174,    33,   175,   176,   177,   143,   144,   153,
     178,   179,   180,   181,     6,     7,     8,     9,    10,   340,
     182,   185,   186,   188,   194,   354,   192,   195,   196,   129,
     103,   383,   384,   385,   386,   197,   213,   214,   261,   270,
     215,   255,   260,   271,   273,   376,   377,   378,   274,    16,
      17,   285,    72,   289,   293,    22,    23,    24,   372,   294,
     296,   106,   307,   308,    28,    16,    17,   319,   315,   388,
     316,   390,   223,    24,   331,    19,   332,   431,    73,    74,
     387,   338,   341,   343,    75,    76,    31,    77,   342,   344,
     106,    33,   350,   345,   351,   352,   353,   424,   388,   356,
     390,   357,    31,    77,   360,   374,   379,    33,   380,   391,
     381,   382,   396,   423,   397,   402,   399,   401,   403,   428,
     -71,   -72,   -70,   432,    41,    36,    50,    51,    52,   418,
     -69,    41,    36,    50,    51,    52,    41,    36,    50,    51,
      52,    54,   417,   426,   433,   419,   335,    58,    54,    59,
     415,   414,   334,    54,    58,   425,    59,   416,   263,    58,
     248,    59,   398,     0,   430,     5,     6,     7,     8,     9,
      10,     0,    11,    12,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,     0,     0,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,     0,     0,    25,    26,    27,    28,    29,     0,     0,
      30,     0,     0,     0,     0,     0,     0,   158,   159,   160,
     161,   162,     0,   163,     0,     0,   164,   165,    31,    32,
       0,     0,     0,    33,   166,   167,   168,   169,   158,   159,
     160,   161,   162,     0,   163,     0,     0,   164,   165,     0,
       0,     0,     0,     0,     0,   166,   167,   168,   169,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   170,   171,
     172,   173,   174,     0,   175,   176,   177,  -211,  -211,  -211,
    -211,   162,     0,   163,     0,     0,   272,     0,     0,   170,
     171,   172,   173,   174,     0,   175,   176,   177,     0,   158,
     159,   160,   161,   162,     0,   163,     0,   295,   164,   165,
       0,     0,     0,     0,     0,     0,   166,   167,   168,   169,
     158,   159,   160,   161,   162,     0,   163,     0,     0,   164,
     165,   173,   174,     0,   175,   176,   177,   166,   167,   168,
     169,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     170,   171,   172,   173,   174,     0,   175,   176,   177,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   400,     0,
       0,   170,   171,   172,   173,   174,     0,   175,   176,   177,
     158,   159,   160,   161,   162,     0,   163,     0,   201,   164,
     165,     0,     0,     0,     0,     0,     0,   166,   167,   168,
     169,   158,   159,   160,   161,   162,     0,   163,     0,     0,
     164,   165,     0,     0,     0,     0,     0,     0,   166,   167,
     168,   169,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   170,   171,   172,   173,   174,     0,   175,   176,   177,
       0,     0,     0,     0,     0,     0,     0,     0,   216,     0,
       0,     0,   170,   171,   172,   173,   174,     0,   175,   176,
     177,   158,   159,   160,   161,   162,     0,   163,     0,   217,
     164,   165,     0,     0,     0,     0,     0,     0,   166,   167,
     168,   169,   158,   159,   160,   161,   162,     0,   163,     0,
       0,   164,   165,     0,     0,     0,     0,     0,     0,   166,
     167,   168,   169,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   170,   171,   172,   173,   174,     0,   175,   176,
     177,     0,     0,     0,     0,     0,     0,     0,     0,   267,
       0,     0,     0,   170,   171,   172,   173,   174,     0,   175,
     176,   177,   158,   159,   160,   161,   162,     0,   163,     0,
     429,   164,   165,     0,     0,     0,     0,     0,     0,   166,
     167,   168,   169,   158,   159,   160,   161,   162,     0,   163,
       0,     0,   164,   165,     0,     0,     0,     0,     0,     0,
     166,     0,   168,   169,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   170,   171,   172,   173,   174,     0,   175,
     176,   177,     0,   158,   159,   160,   161,   162,     0,   163,
       0,     0,   164,   165,   170,   171,   172,   173,   174,     0,
     175,   176,   177,   158,   159,   160,   161,   162,     0,   163,
       0,     0,   164,   165,     0,   158,   159,   160,   161,   162,
     166,   163,   168,     0,   164,   165,     0,     0,     0,     0,
       0,     0,     0,     0,   168,   171,   172,   173,   174,     0,
     175,   176,   177,   158,   159,   160,   161,   162,     0,   163,
       0,     0,   164,   165,   170,   171,   172,   173,   174,     0,
     175,   176,   177,     0,     0,     0,   170,   171,   172,   173,
     174,     0,   175,   176,   177,   158,   159,   160,   161,   162,
       0,   163,     0,     0,  -211,  -211,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   172,   173,   174,     0,
     175,   176,   177,   158,   159,   160,   161,   162,     0,   163,
       0,     0,   164,   165,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   173,
     174,     0,   175,   176,   177,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   173,   174,     0,
     175,   176,   177
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     4,     4,     4,    21,    67,   144,     5,    25,
      22,    23,     5,     5,     4,     5,    15,     4,    22,    23,
      22,    23,     5,     4,     8,     4,     3,    26,   180,   181,
       2,     4,     5,   301,    33,   153,     4,     5,     6,     7,
       8,   366,   367,     4,     5,    62,    61,     5,    61,     5,
       5,     5,     5,    70,     5,     5,     5,     5,     6,     7,
       8,     5,   180,   181,    41,    78,   334,    82,    59,    68,
      69,    39,    40,     3,    73,    74,    75,    76,    76,    47,
      64,    71,     3,    81,   100,    82,    54,    78,    71,    82,
      82,    39,    40,    54,    48,   420,    54,    48,    54,    47,
      54,    54,    75,    54,    54,    54,    54,    76,    76,    77,
      54,    41,    81,    81,   113,   119,   119,   119,   119,   119,
      41,    61,    45,    46,    61,     0,    45,    46,    70,   128,
     129,   283,   119,    45,    46,   287,    81,    54,   119,   291,
     119,    42,    82,    62,   143,    82,   283,    70,    76,    77,
     287,    70,   213,   214,   291,    56,    57,    76,    70,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
      64,    70,    64,    81,   183,    64,    70,    76,    70,    14,
      15,    16,    17,    18,    64,    20,   195,   196,    23,    24,
     216,   217,    81,    71,    72,    73,    76,    62,   224,    64,
     271,    81,   273,    62,   275,     3,     4,     5,     6,     7,
       8,    76,    10,    11,    62,     5,    81,    76,    59,    60,
       5,    77,     4,   249,    22,    80,   252,    25,    76,    81,
      65,    66,    67,    68,    69,   261,    71,    72,    73,    64,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      80,    80,    80,    51,    52,    53,    54,    55,   284,   285,
      58,    80,   288,   289,    80,    80,   292,   293,   294,   295,
      80,    80,   343,   344,    80,    80,    80,   348,    76,    77,
      78,    68,    69,    81,    71,    72,    73,    62,    61,    81,
      62,    61,    81,    81,     4,     5,     6,     7,     8,   308,
       4,    70,    70,    50,    83,   331,    77,    61,    64,    76,
       4,     5,     6,     7,     8,    78,    81,    81,    49,     8,
      82,    81,    81,    81,    81,   351,   352,   353,    70,    39,
      40,    82,    42,    82,    82,    45,    46,    47,   347,    82,
       5,   363,    77,    64,    54,    39,    40,    70,    82,   363,
      82,   363,     5,    47,    82,    42,    78,   428,    68,    69,
      54,    80,    82,    81,    74,    75,    76,    77,    82,    81,
     392,    81,    70,    82,    82,    82,    82,   403,   392,    80,
     392,     5,    76,    77,     5,    13,    62,    81,    61,    64,
      62,    61,    82,   402,    82,    81,    70,    82,    12,    81,
      64,    64,    64,   429,   418,   418,   418,   418,   418,   391,
      64,   425,   425,   425,   425,   425,   430,   430,   430,   430,
     430,   418,    64,    64,    82,   392,   303,   418,   425,   418,
     381,   380,   302,   430,   425,   417,   425,   382,   190,   430,
     179,   430,   370,    -1,   426,     3,     4,     5,     6,     7,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    51,    52,    53,    54,    55,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    76,    77,
      -1,    -1,    -1,    81,    31,    32,    33,    34,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    -1,    71,    72,    73,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    83,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    71,    72,    73,    -1,    14,
      15,    16,    17,    18,    -1,    20,    -1,    83,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    68,    69,    -1,    71,    72,    73,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,
      -1,    65,    66,    67,    68,    69,    -1,    71,    72,    73,
      14,    15,    16,    17,    18,    -1,    20,    -1,    82,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    -1,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    -1,    71,    72,
      73,    14,    15,    16,    17,    18,    -1,    20,    -1,    82,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    -1,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,    71,
      72,    73,    14,    15,    16,    17,    18,    -1,    20,    -1,
      82,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,    71,
      72,    73,    -1,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    65,    66,    67,    68,    69,    -1,
      71,    72,    73,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    -1,    14,    15,    16,    17,    18,
      31,    20,    33,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    66,    67,    68,    69,    -1,
      71,    72,    73,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    65,    66,    67,    68,    69,    -1,
      71,    72,    73,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    -1,    71,    72,    73,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    -1,
      71,    72,    73,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    -1,
      71,    72,    73
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    85,    86,     0,    87,     3,     4,     5,     6,     7,
       8,    10,    11,    22,    25,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    51,    52,    53,    54,    55,
      58,    76,    77,    81,    88,    89,    90,    91,    92,    93,
      94,    95,    97,    98,    99,   104,   120,   122,   123,   128,
     129,   131,   135,   141,   146,   148,   150,   155,   156,   159,
     161,   162,   165,     5,   142,   143,    70,    81,    81,    81,
       5,   147,    42,    68,    69,    74,    75,    77,    90,    95,
      96,   103,   129,   131,   135,   136,   137,   138,   139,   140,
     146,   151,   156,   159,    54,   144,   145,     4,     5,    75,
       5,    77,    89,     4,     5,    95,    97,   129,    95,   129,
      89,    96,     4,    81,    96,   152,   153,     8,    64,    87,
     121,    96,    80,    80,    80,    45,    46,    70,    62,    76,
      80,    45,    46,    70,    80,    80,    80,    80,    80,    64,
      80,    80,    80,    62,    61,     5,    48,    54,   152,    96,
      96,    64,    70,    81,    96,    96,    96,    96,    14,    15,
      16,    17,    18,    20,    23,    24,    31,    32,    33,    34,
      65,    66,    67,    68,    69,    71,    72,    73,    62,    61,
      81,    81,     4,    76,    89,    70,    70,    70,    50,   124,
     125,   126,    77,    96,    83,    61,    64,    78,    78,    61,
      78,    82,     5,    54,    96,    96,     5,    54,     4,     5,
      54,    96,   143,    81,    81,    82,    82,    82,     4,     5,
      71,     5,    71,     5,    82,   142,   149,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,   145,    82,
     142,   149,    82,   142,   149,    81,    96,     5,     5,     5,
      81,    49,   127,   126,   105,   106,   107,    82,    96,    96,
       8,    81,    83,    81,    70,    81,   152,   152,   160,    89,
      89,    70,    89,    61,    82,    82,    89,    61,    82,    82,
      89,    61,    82,    82,    82,    83,     5,    89,    56,    57,
     117,   118,   119,   108,     3,    41,   109,    77,    64,   152,
     152,     5,    48,    54,   152,    82,    82,   154,   166,    70,
     149,    89,    89,   149,    89,    89,   149,    89,    89,    89,
      89,    82,    78,   150,   118,   109,   110,   111,    80,   100,
      96,    82,    82,    81,    81,    82,   134,    76,    81,   163,
      70,    82,    82,    82,    89,   150,    80,     5,   113,   114,
       5,   115,   116,    59,    60,   102,   132,   133,   152,   152,
     157,   130,    96,   152,    13,   167,    89,    89,    89,    62,
      61,    62,    61,     5,     6,     7,     8,    54,    95,   101,
     129,    64,    59,    78,   130,   130,    82,    82,   154,    70,
      83,    82,    81,    12,   164,     5,     6,     7,     8,    39,
      40,    47,    54,   112,   114,   112,   116,    64,    87,   101,
     158,     5,    54,    96,    89,    87,    64,   130,    81,    82,
      87,   152,    89,    82
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
     315,    44,    61,   316,    58,   124,    94,    38,    45,    43,
      46,    42,    47,    37,    33,   126,    91,   123,   125,   317,
      59,    40,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    84,    86,    85,    87,    87,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    89,    90,    90,
      91,    92,    93,    93,    94,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    97,    97,    97,    98,   100,    99,   101,   101,
     101,   101,   101,   101,   102,   102,   102,   103,   103,   103,
     103,   104,   105,   105,   107,   106,   108,   106,   110,   109,
     111,   109,   112,   112,   112,   112,   112,   112,   112,   112,
     113,   113,   114,   114,   115,   115,   116,   117,   117,   118,
     118,   118,   119,   119,   120,   121,   121,   122,   122,   123,
     124,   125,   125,   126,   127,   127,   128,   129,   129,   129,
     129,   129,   129,   130,   130,   130,   130,   132,   131,   133,
     131,   134,   131,   135,   135,   135,   135,   135,   135,   135,
     135,   136,   136,   136,   136,   136,   136,   137,   137,   138,
     138,   139,   139,   139,   139,   139,   140,   140,   140,   140,
     140,   141,   141,   142,   142,   143,   143,   144,   144,   145,
     146,   147,   147,   148,   148,   148,   148,   148,   149,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   151,   151,
     151,   151,   152,   152,   153,   153,   154,   154,   154,   155,
     155,   157,   156,   156,   156,   156,   156,   156,   158,   156,
     160,   159,   161,   161,   162,   163,   163,   164,   164,   166,
     167,   165
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
       1,     1,     1,     1,     4,     3,     5,     2,     2,     2,
       2,     6,     0,     1,     0,     3,     0,     4,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     1,     3,     3,     0,     1,     0,
       1,     1,     2,     3,     3,     3,     5,     3,     3,     2,
       1,     1,     2,     5,     0,     2,     4,     3,     3,     3,
       3,     3,     3,     0,     6,     3,     3,     0,     8,     0,
       8,     0,     8,     2,     2,     2,     2,     2,     2,     2,
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
  "\"switch\"", "\"case\"", "\"default\"", "','", "'='", "XOR_EQUAL",
  "':'", "'|'", "'^'", "'&'", "'-'", "'+'", "'.'", "'*'", "'/'", "'%'",
  "'!'", "'~'", "'['", "'{'", "'}'", "UMINUS", "';'", "'('", "')'", "']'",
  "$accept", "program", "$@1", "statement_list", "statement", "block",
  "instantiation", "break", "continue", "thread_block", "critical_block",
  "object", "rvalue", "lvalue", "subscript", "switch_expr", "@2", "label",
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
        85,     0,    -1,    -1,    86,    87,    -1,    -1,    87,    88,
      -1,   148,    80,    -1,   141,    80,    -1,   146,    80,    -1,
     159,    80,    -1,   131,    80,    -1,   150,    -1,   161,    80,
      -1,   165,    -1,   162,    -1,   135,    80,    -1,    89,    -1,
      93,    -1,    94,    -1,   123,    80,    -1,    91,    80,    -1,
      92,    80,    -1,   128,    -1,   104,    -1,   156,    80,    -1,
      90,    80,    -1,    99,    -1,    77,    87,    78,    -1,     4,
      70,    48,    -1,     4,    70,    48,    81,   152,    82,    -1,
      22,    -1,    53,    -1,    43,     5,    89,    -1,    43,     5,
      76,    96,    83,    89,    -1,    44,    89,    -1,     5,    -1,
      54,    -1,     8,    -1,     6,    -1,     7,    -1,    47,    -1,
      39,    -1,    40,    -1,   122,    -1,   120,    -1,    81,    96,
      82,    -1,    98,    -1,   159,    -1,    95,    -1,   103,    -1,
     139,    -1,   138,    -1,   140,    -1,   137,    -1,   136,    -1,
     146,    -1,   135,    -1,   151,    -1,    90,    -1,   131,    -1,
     156,    -1,   129,    -1,     5,    -1,   129,    -1,    98,    -1,
      97,    76,    96,    83,    -1,    -1,    58,    81,    96,    82,
      77,   100,   102,    78,    -1,     5,    -1,    54,    -1,     8,
      -1,     6,    -1,     7,    -1,   129,    -1,    59,   101,    64,
      87,    -1,    60,    64,    87,    -1,   102,    59,   101,    64,
      87,    -1,    68,    96,    -1,    69,    96,    -1,    74,    96,
      -1,    75,    96,    -1,    55,     4,    77,   105,   117,    78,
      -1,    -1,   106,    -1,    -1,   107,   109,    80,    -1,    -1,
     106,   108,   109,    80,    -1,    -1,     3,   110,   113,    -1,
      -1,    41,   111,   115,    -1,     5,    -1,    54,    -1,     8,
      -1,     6,    -1,     7,    -1,    47,    -1,    39,    -1,    40,
      -1,   114,    -1,   113,    61,   114,    -1,     5,    62,   112,
      -1,     5,    -1,   116,    -1,   115,    61,   116,    -1,     5,
      62,   112,    -1,    -1,   119,    -1,    -1,    56,    -1,    57,
      -1,   118,   150,    -1,   119,   118,   150,    -1,    76,   152,
      83,    -1,     8,    64,    96,    -1,   121,    61,     8,    64,
      96,    -1,    77,    64,    78,    -1,    77,   121,    78,    -1,
      52,    96,    -1,   125,    -1,   126,    -1,   125,   126,    -1,
      50,    81,     5,    82,    89,    -1,    -1,    49,    89,    -1,
      51,    89,   124,   127,    -1,    95,    70,     5,    -1,     4,
      70,     5,    -1,    95,    70,    54,    -1,     4,    70,    54,
      -1,   129,    70,     5,    -1,   129,    70,    54,    -1,    -1,
     130,    70,     5,    81,   152,    82,    -1,   130,    70,     5,
      -1,   130,    70,    54,    -1,    -1,    95,    70,     5,    81,
     152,    82,   132,   130,    -1,    -1,   129,    70,     5,    81,
     152,    82,   133,   130,    -1,    -1,     4,    70,     5,    81,
     152,    82,   134,   130,    -1,    95,    45,    -1,    95,    46,
      -1,    45,    95,    -1,    46,    95,    -1,   129,    45,    -1,
     129,    46,    -1,    45,   129,    -1,    46,   129,    -1,    96,
      23,    96,    -1,    96,    24,    96,    -1,    96,    17,    96,
      -1,    96,    15,    96,    -1,    96,    16,    96,    -1,    96,
      14,    96,    -1,    96,    31,    96,    -1,    96,    33,    96,
      -1,    96,    32,    96,    -1,    96,    34,    96,    -1,    96,
      69,    96,    -1,    96,    68,    96,    -1,    96,    71,    96,
      -1,    96,    72,    96,    -1,    96,    73,    96,    -1,    96,
      67,    96,    -1,    96,    65,    96,    -1,    96,    66,    96,
      -1,    96,    20,    96,    -1,    96,    18,    96,    -1,     3,
     142,    -1,    41,   144,    -1,   143,    -1,   142,    61,   143,
      -1,     5,    62,    96,    -1,     5,    -1,   145,    -1,   144,
      61,   145,    -1,    54,    62,    96,    -1,    97,    62,    96,
      -1,     5,    -1,   147,    70,     5,    -1,    25,   147,    70,
      71,    -1,    25,   147,    64,    71,    -1,    25,   147,    64,
       5,    -1,    25,   147,    64,     4,    -1,    25,   147,    -1,
       5,    70,    70,    70,    -1,    42,     5,    81,    82,    89,
      -1,    42,     4,    81,    82,    89,    -1,    42,    75,     4,
      81,    82,    89,    -1,    42,     5,    81,   149,    82,    89,
      -1,    42,     4,    81,   149,    82,    89,    -1,    42,     5,
      81,   142,    82,    89,    -1,    42,     4,    81,   142,    82,
      89,    -1,    42,     5,    81,   142,    61,   149,    82,    89,
      -1,    42,     4,    81,   142,    61,   149,    82,    89,    -1,
      42,    81,    82,    89,    -1,    42,    81,   149,    82,    89,
      -1,    42,    81,   142,    82,    89,    -1,    42,    81,   142,
      61,   149,    82,    89,    -1,    -1,   153,    -1,    96,    -1,
     153,    61,    96,    -1,    -1,   154,    81,   152,    82,    -1,
     154,    76,    96,    83,    -1,     5,    -1,   155,    64,     5,
      -1,    -1,   155,    64,     5,    81,   152,    82,   157,   154,
      -1,   155,    64,    54,    -1,   155,    64,     5,    -1,   155,
      64,     4,    70,    54,    -1,   155,    64,     4,    70,    48,
      -1,   155,    64,     4,    70,    48,    81,   152,    82,    -1,
      -1,   155,    64,     4,    70,     5,    81,   152,    82,   158,
     130,    -1,    -1,     5,    81,   152,    82,   160,   154,    -1,
      38,    96,    -1,    38,    -1,    10,    81,    96,    82,    89,
      -1,    -1,   163,    13,    81,    96,    82,    89,    -1,    -1,
      12,    89,    -1,    -1,    -1,    11,    81,    96,    82,    89,
     166,   163,   167,   164,    -1
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
     179,   181,   183,   185,   187,   192,   196,   202,   205,   208,
     211,   214,   221,   222,   224,   225,   229,   230,   235,   236,
     240,   241,   245,   247,   249,   251,   253,   255,   257,   259,
     261,   263,   267,   271,   273,   275,   279,   283,   284,   286,
     287,   289,   291,   294,   298,   302,   306,   312,   316,   320,
     323,   325,   327,   330,   336,   337,   340,   345,   349,   353,
     357,   361,   365,   369,   370,   377,   381,   385,   386,   395,
     396,   405,   406,   415,   418,   421,   424,   427,   430,   433,
     436,   439,   443,   447,   451,   455,   459,   463,   467,   471,
     475,   479,   483,   487,   491,   495,   499,   503,   507,   511,
     515,   519,   522,   525,   527,   531,   535,   537,   539,   543,
     547,   551,   553,   557,   562,   567,   572,   577,   580,   585,
     591,   597,   604,   611,   618,   625,   632,   641,   650,   655,
     661,   667,   675,   676,   678,   680,   684,   685,   690,   695,
     697,   701,   702,   711,   715,   719,   725,   731,   740,   741,
     752,   753,   760,   763,   765,   771,   772,   779,   780,   783,
     784,   785
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   219,   219,   219,   223,   224,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   252,   256,   257,
     261,   265,   269,   276,   286,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   329,   330,   331,   335,   339,   339,   343,   344,
     345,   346,   347,   348,   352,   353,   354,   358,   359,   360,
     361,   365,   369,   370,   374,   374,   375,   375,   379,   379,
     380,   380,   384,   385,   386,   387,   388,   389,   390,   391,
     395,   396,   400,   401,   405,   406,   410,   414,   415,   419,
     420,   421,   425,   426,   430,   434,   435,   439,   440,   444,
     448,   452,   453,   457,   461,   462,   466,   470,   471,   472,
     473,   474,   475,   479,   480,   481,   482,   486,   486,   487,
     487,   488,   488,   492,   493,   494,   495,   496,   497,   498,
     499,   503,   504,   505,   506,   507,   508,   512,   513,   517,
     518,   522,   523,   524,   525,   526,   530,   531,   532,   533,
     534,   538,   539,   543,   544,   548,   549,   553,   554,   558,
     562,   566,   567,   571,   572,   573,   574,   575,   579,   583,
     585,   587,   589,   591,   593,   595,   597,   599,   604,   606,
     608,   610,   615,   616,   620,   621,   625,   626,   627,   631,
     632,   636,   636,   637,   638,   639,   640,   641,   642,   642,
     646,   646,   650,   651,   655,   659,   661,   666,   667,   671,
     672,   671
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
       2,     2,     2,    74,     2,     2,     2,    73,    67,     2,
      81,    82,    71,    69,    61,    68,    70,    72,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    64,    80,
       2,    62,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    83,    66,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    77,    65,    78,    75,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    63,    79
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 1082;
  const int Parser::yynnts_ = 84;
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

