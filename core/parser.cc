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

  case 225:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 226:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 227:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 228:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 229:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 230:

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
  const short int Parser::yypact_ninf_ = -329;
  const short int
  Parser::yypact_[] =
  {
      -329,    72,  -329,  -329,   300,    83,    63,   145,  -329,  -329,
    -329,    55,   102,  -329,   140,   426,  -329,  -329,    94,    27,
     181,   155,     6,     6,  -329,   155,   426,  -329,  -329,   231,
     157,   426,    16,   426,  -329,  -329,   159,   169,   180,  -329,
    -329,     9,   118,   149,  -329,  -329,  -329,  -329,   182,  -329,
      67,   191,   194,   195,   200,   201,  -329,   197,   204,   205,
     206,  -329,  -329,   235,   237,  -329,    52,   426,   426,   426,
    -329,   117,   218,   426,   426,   426,   426,    16,  -329,     9,
     819,  -329,    79,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,   238,   240,  -329,   221,   232,   308,
     127,  -329,  -329,   244,    -8,   246,   241,   112,   246,   112,
     268,   819,   242,   426,   819,   243,   259,   257,   245,   212,
     124,   597,  -329,  -329,  -329,  -329,  -329,    35,   426,   426,
    -329,  -329,  -329,    39,  -329,  -329,  -329,  -329,  -329,    37,
    -329,  -329,  -329,   426,    83,   247,   248,  -329,   249,   657,
     678,    32,    30,     3,  -329,  -329,  -329,  -329,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,    94,
      10,    17,   251,   426,  -329,    51,    53,    54,   252,   275,
     268,  -329,    40,   738,  -329,   426,   426,  -329,  -329,   319,
    -329,  -329,   253,  -329,   900,   494,   269,  -329,   260,    70,
    -329,   819,  -329,   426,   426,  -329,   155,   155,  -329,  -329,
    -329,  -329,  -329,    58,   155,   -35,   267,   472,   472,   472,
     472,   223,   223,   382,   382,   912,   840,   175,   900,   880,
     940,   972,    85,    85,  -329,  -329,  -329,   819,  -329,   155,
      61,   274,   155,    65,   277,   278,   515,  -329,  -329,  -329,
     352,   155,  -329,  -329,   171,    45,    68,   284,   819,   819,
     298,   426,  -329,   426,    73,   426,   281,   282,  -329,  -329,
    -329,   296,  -329,   362,   155,   155,  -329,   362,   155,   155,
    -329,   362,   155,   155,   155,   155,   286,  -329,  -329,  -329,
     291,   328,   171,    68,  -329,  -329,   292,  -329,   426,   289,
     293,   297,   299,  -329,   301,  -329,  -329,   148,  -329,   303,
     302,  -329,  -329,   304,  -329,  -329,   305,  -329,  -329,  -329,
    -329,   155,  -329,  -329,   328,   294,   374,   377,  -329,   146,
     819,  -329,  -329,   426,   426,  -329,  -329,   426,   426,   375,
    -329,   155,   155,   155,  -329,  -329,  -329,   327,   329,  -329,
     330,   332,  -329,    44,   331,    64,  -329,  -329,   309,   312,
    -329,   333,   576,   322,   326,   396,  -329,  -329,  -329,    57,
     374,    57,   377,  -329,  -329,  -329,  -329,  -329,   345,  -329,
      44,  -329,   333,   333,  -329,  -329,   148,    56,  -329,  -329,
     426,   155,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,   300,   346,  -329,   337,
    -329,   759,  -329,   300,  -329,   333,   426,   155,   300,   356,
    -329,  -329
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    35,    38,    39,
      37,     0,     0,    30,     0,   222,    41,    42,     0,     0,
       0,     0,     0,     0,    40,     0,     0,    31,    36,     0,
       0,   201,     4,     0,     5,    16,     0,     0,     0,    17,
      18,     0,     0,    46,    26,    23,    44,    43,     0,    22,
      63,     0,     0,     0,     0,     0,    11,     0,     0,    47,
       0,    14,    13,   175,   170,   172,     0,   201,     0,     0,
     180,   186,     0,     0,     0,     0,     0,     0,    58,    48,
     221,    49,    61,    59,    56,    54,    53,    51,    50,    52,
      55,    57,    60,    47,     0,   171,   176,     0,     0,     0,
       0,     4,    34,     0,    35,   144,     0,   148,   145,   149,
       0,   118,     0,     0,   203,     0,   202,     0,     0,     0,
       0,     0,    25,    20,    21,   142,   143,     0,     0,     0,
      19,   146,   147,     0,    10,    15,     7,     8,     6,     0,
      24,     9,    12,     0,     0,   127,    28,   129,     0,     0,
       0,     0,     0,     0,    76,    77,    78,    79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,     0,     0,     0,     0,   123,
     119,   120,    81,     0,   113,     0,     0,   116,    27,     0,
     117,    45,   126,   128,   179,     0,   130,   131,     0,   213,
     212,   174,   173,   201,   201,   219,     0,     0,   185,   184,
     183,   181,   182,   175,     0,     0,     0,   155,   153,   154,
     152,   169,   168,   150,   151,   156,   158,   157,   159,   166,
     167,   165,   161,   160,   162,   163,   164,   178,   177,     0,
       0,     0,     0,     0,     0,     0,     0,   127,   126,   130,
       0,     0,   125,   121,   106,    82,     0,     0,   204,   114,
       0,   201,    65,   201,     0,   201,     0,     0,   205,   223,
     228,     0,   197,     0,     0,     0,   189,     0,     0,     0,
     188,     0,     0,     0,     0,     0,     0,   124,   109,   110,
       0,     0,   107,     0,    87,    89,     0,    66,     0,     0,
       0,     0,   215,   214,     0,   140,    29,   220,   224,     0,
       0,   199,   198,     0,   194,   192,     0,   193,   191,   190,
      33,     0,    80,   111,     0,     0,     0,     0,    84,     0,
     115,   136,   138,   201,   201,   210,   132,     0,   201,   229,
     187,     0,     0,     0,   122,   112,    86,   102,    88,    99,
       0,    90,   103,     0,     0,     0,   132,   132,     0,     0,
     205,   141,     0,     0,     0,   226,   200,   196,   195,     0,
       0,     0,     0,    68,    71,    72,    70,    69,     0,     4,
       0,    67,   137,   139,   217,   216,   211,     0,   207,   206,
       0,     0,   230,    91,    94,    95,    93,    97,    98,    96,
      92,   101,   100,   105,   104,     4,    74,     0,   132,   134,
     135,     0,   227,    73,     4,   218,   201,     0,    75,     0,
     225,   133
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -329,  -329,  -329,    28,  -329,   -16,    -3,  -329,  -329,  -329,
    -329,    -4,     1,   208,  -329,  -329,  -329,    49,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,   137,  -329,  -329,    75,  -329,
      66,  -329,    76,  -329,   143,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,   258,  -329,  -329,    -2,  -328,    -1,  -329,  -329,
    -329,     0,  -329,  -329,  -329,  -329,  -329,  -329,   -86,  -137,
    -329,   280,    13,  -329,  -329,  -152,  -268,  -329,   -61,  -329,
      87,  -329,    19,  -329,  -329,    21,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   119,    34,    35,    78,    37,    38,    39,
      40,    79,   114,    42,    43,    44,   339,   388,   365,    81,
      45,   264,   265,   266,   303,   306,   336,   337,   411,   358,
     359,   361,   362,   300,   301,   302,    46,   120,    47,    48,
     189,   190,   191,   262,    49,    82,   371,    83,   366,   367,
     346,    84,    85,    86,    87,    88,    89,    53,    64,    65,
      95,    96,    90,    71,    55,   226,    56,    91,   115,   116,
     317,    57,    92,   370,   418,    93,   278,    60,    61,   349,
     402,    62,   318,   375
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -210;
  const short int
  Parser::yytable_[] =
  {
        41,    36,    50,    51,    52,   102,   148,   212,   223,   110,
     103,   104,     8,     9,    10,   223,    80,    54,   105,   108,
     107,   109,   223,    58,   117,    59,   283,   111,   251,   254,
       4,    97,    98,   333,   121,   221,   218,   219,   392,   393,
     202,   208,   209,   -83,   206,    16,    17,   284,   -85,   383,
     384,   385,   386,    24,   125,   126,   257,   145,   258,   259,
      28,   419,   403,   404,   405,   406,   355,   225,   -62,   149,
     150,   304,     3,    67,   154,   155,   156,   157,   311,   127,
     118,   -83,    31,    77,   184,   224,   -85,    33,    63,   203,
     425,   210,   249,   207,   250,   253,   407,   408,   387,   252,
     146,   222,    99,   220,   409,   147,   147,   203,   207,   305,
     420,   410,   131,   132,   193,    41,    36,    50,    51,    52,
     143,   312,   287,   390,   131,   132,   291,   313,   281,   204,
     205,   320,    54,    66,  -209,   323,    68,   133,    58,   326,
      59,   -63,   391,   288,   211,    70,   212,   292,    94,   133,
     212,   275,   276,   277,   212,   -63,   175,   176,   177,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     128,   151,   187,    69,   256,   199,   100,   152,   -63,   158,
     159,   160,   161,   162,   129,   163,   268,   269,   164,   165,
     279,   280,   200,   183,   101,   363,   364,   -62,   282,  -208,
     309,   -64,   310,  -108,   314,     5,     6,     7,     8,     9,
      10,   -62,    11,    12,   347,   -64,    67,   298,   299,   348,
     106,   106,   101,   286,    13,   112,   290,    14,   113,   122,
     170,   171,   172,   173,   174,   297,   175,   176,   177,   123,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
     124,   139,   130,    25,    26,    27,    28,    29,   321,   322,
      30,   134,   324,   325,   135,   136,   327,   328,   329,   330,
     137,   138,   368,   369,   140,   141,   142,   373,    31,    32,
     198,   173,   174,    33,   175,   176,   177,   143,   144,   153,
     178,   179,   180,     5,     6,     7,     8,     9,    10,   340,
      11,    12,   182,   181,   185,   354,   186,   129,   188,   192,
     195,   196,    13,   197,   261,    14,   194,   270,   213,   214,
     274,   215,   255,   260,   271,   376,   377,   378,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,   372,   285,
     273,    25,    26,    27,    28,    29,   289,   296,    30,   293,
     294,   307,   308,   315,   316,   429,   319,   223,   331,   332,
      19,   341,   338,   350,   356,   342,    31,    32,   343,   357,
     344,    33,   360,   345,   351,   422,   352,   353,   374,   379,
     380,   394,   381,   382,   395,   389,   158,   159,   160,   161,
     162,   421,   163,   397,   399,  -210,  -210,   400,   401,   415,
     424,   430,    41,    36,    50,    51,    52,   416,   426,    41,
      36,    50,    51,    52,    41,    36,    50,    51,    52,    54,
       6,     7,     8,     9,    10,    58,    54,    59,   431,   417,
     335,    54,    58,   423,    59,   334,   412,    58,   263,    59,
     173,   174,   428,   175,   176,   177,   413,   396,   414,   248,
       0,     0,     0,     0,     0,    16,    17,     0,    72,     0,
       0,    22,    23,    24,     0,     0,     0,     0,     0,     0,
      28,     0,     0,     0,     0,     0,  -210,  -210,  -210,  -210,
     162,     0,   163,     0,    73,    74,     0,     0,     0,     0,
      75,    76,    31,    77,     0,     0,     0,    33,   158,   159,
     160,   161,   162,     0,   163,     0,     0,   164,   165,     0,
       0,     0,     0,     0,     0,   166,   167,   168,   169,   158,
     159,   160,   161,   162,     0,   163,     0,     0,   164,   165,
     173,   174,     0,   175,   176,   177,   166,   167,   168,   169,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   170,
     171,   172,   173,   174,     0,   175,   176,   177,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   272,     0,     0,
     170,   171,   172,   173,   174,     0,   175,   176,   177,     0,
     158,   159,   160,   161,   162,     0,   163,     0,   295,   164,
     165,     0,     0,     0,     0,     0,     0,   166,   167,   168,
     169,   158,   159,   160,   161,   162,     0,   163,     0,     0,
     164,   165,     0,     0,     0,     0,     0,     0,   166,   167,
     168,   169,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   170,   171,   172,   173,   174,     0,   175,   176,   177,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   398,
       0,     0,   170,   171,   172,   173,   174,     0,   175,   176,
     177,   158,   159,   160,   161,   162,     0,   163,     0,   201,
     164,   165,     0,     0,     0,     0,     0,     0,   166,   167,
     168,   169,   158,   159,   160,   161,   162,     0,   163,     0,
       0,   164,   165,     0,     0,     0,     0,     0,     0,   166,
     167,   168,   169,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   170,   171,   172,   173,   174,     0,   175,   176,
     177,     0,     0,     0,     0,     0,     0,     0,     0,   216,
       0,     0,     0,   170,   171,   172,   173,   174,     0,   175,
     176,   177,   158,   159,   160,   161,   162,     0,   163,     0,
     217,   164,   165,     0,     0,     0,     0,     0,     0,   166,
     167,   168,   169,   158,   159,   160,   161,   162,     0,   163,
       0,     0,   164,   165,     0,     0,     0,     0,     0,     0,
     166,   167,   168,   169,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   170,   171,   172,   173,   174,     0,   175,
     176,   177,     0,     0,     0,     0,     0,     0,     0,     0,
     267,     0,     0,     0,   170,   171,   172,   173,   174,     0,
     175,   176,   177,   158,   159,   160,   161,   162,     0,   163,
       0,   427,   164,   165,     0,     0,     0,     0,     0,     0,
     166,   167,   168,   169,   158,   159,   160,   161,   162,     0,
     163,     0,     0,   164,   165,     0,     0,     0,     0,     0,
       0,   166,     0,   168,   169,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   170,   171,   172,   173,   174,     0,
     175,   176,   177,     0,   158,   159,   160,   161,   162,     0,
     163,     0,     0,   164,   165,   170,   171,   172,   173,   174,
       0,   175,   176,   177,   158,   159,   160,   161,   162,     0,
     163,     0,     0,   164,   165,     0,   158,   159,   160,   161,
     162,   166,   163,   168,     0,   164,   165,     0,     0,     0,
       0,     0,     0,     0,     0,   168,   171,   172,   173,   174,
       0,   175,   176,   177,   158,   159,   160,   161,   162,     0,
     163,     0,     0,   164,   165,   170,   171,   172,   173,   174,
       0,   175,   176,   177,     0,     0,     0,   170,   171,   172,
     173,   174,     0,   175,   176,   177,   158,   159,   160,   161,
     162,     0,   163,     0,     0,   164,   165,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   172,   173,   174,
       0,   175,   176,   177,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   174,     0,   175,   176,   177
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     4,     4,     4,    21,    67,   144,     5,    25,
       4,     5,     6,     7,     8,     5,    15,     4,    22,    23,
      22,    23,     5,     4,     8,     4,    61,    26,   180,   181,
       2,     4,     5,   301,    33,     5,     4,     5,   366,   367,
       5,     4,     5,     3,     5,    39,    40,    82,     3,     5,
       6,     7,     8,    47,    45,    46,     5,     5,     5,     5,
      54,     5,     5,     6,     7,     8,   334,   153,    76,    68,
      69,     3,     0,    81,    73,    74,    75,    76,     5,    70,
      64,    41,    76,    77,   100,    82,    41,    81,     5,    54,
     418,    54,    82,    54,   180,   181,    39,    40,    54,    82,
      48,    71,    75,    71,    47,    54,    54,    54,    54,    41,
      54,    54,    45,    46,   113,   119,   119,   119,   119,   119,
      62,    48,    61,    59,    45,    46,    61,    54,    70,   128,
     129,   283,   119,    70,    64,   287,    81,    70,   119,   291,
     119,    62,    78,    82,   143,     5,   283,    82,    54,    70,
     287,    81,   213,   214,   291,    76,    71,    72,    73,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
      62,    64,    70,    81,   183,    61,     5,    70,    76,    14,
      15,    16,    17,    18,    76,    20,   195,   196,    23,    24,
     216,   217,    78,    76,    77,    59,    60,    62,   224,    64,
     271,    62,   273,    42,   275,     3,     4,     5,     6,     7,
       8,    76,    10,    11,    76,    76,    81,    56,    57,    81,
      22,    23,    77,   249,    22,     4,   252,    25,    81,    80,
      65,    66,    67,    68,    69,   261,    71,    72,    73,    80,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      80,    64,    80,    51,    52,    53,    54,    55,   284,   285,
      58,    80,   288,   289,    80,    80,   292,   293,   294,   295,
      80,    80,   343,   344,    80,    80,    80,   348,    76,    77,
      78,    68,    69,    81,    71,    72,    73,    62,    61,    81,
      62,    61,    81,     3,     4,     5,     6,     7,     8,   308,
      10,    11,     4,    81,    70,   331,    70,    76,    50,    77,
      61,    64,    22,    78,    49,    25,    83,     8,    81,    81,
      70,    82,    81,    81,    81,   351,   352,   353,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,   347,    82,
      81,    51,    52,    53,    54,    55,    82,     5,    58,    82,
      82,    77,    64,    82,    82,   426,    70,     5,    82,    78,
      42,    82,    80,    70,    80,    82,    76,    77,    81,     5,
      81,    81,     5,    82,    82,   401,    82,    82,    13,    62,
      61,    82,    62,    61,    82,    64,    14,    15,    16,    17,
      18,   400,    20,    70,    82,    23,    24,    81,    12,    64,
      64,   427,   416,   416,   416,   416,   416,   389,    81,   423,
     423,   423,   423,   423,   428,   428,   428,   428,   428,   416,
       4,     5,     6,     7,     8,   416,   423,   416,    82,   390,
     303,   428,   423,   415,   423,   302,   380,   428,   190,   428,
      68,    69,   424,    71,    72,    73,   381,   370,   382,   179,
      -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    42,    -1,
      -1,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    20,    -1,    68,    69,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    -1,    -1,    -1,    81,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      68,    69,    -1,    71,    72,    73,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    71,    72,    73,    -1,
      14,    15,    16,    17,    18,    -1,    20,    -1,    83,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    -1,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
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
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      71,    72,    73,    14,    15,    16,    17,    18,    -1,    20,
      -1,    82,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      71,    72,    73,    -1,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    65,    66,    67,    68,    69,
      -1,    71,    72,    73,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    14,    15,    16,    17,
      18,    31,    20,    33,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    66,    67,    68,    69,
      -1,    71,    72,    73,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    65,    66,    67,    68,    69,
      -1,    71,    72,    73,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    71,    72,    73,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      -1,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    -1,    71,    72,    73
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
      61,    62,    61,     5,     6,     7,     8,    54,   101,    64,
      59,    78,   130,   130,    82,    82,   154,    70,    83,    82,
      81,    12,   164,     5,     6,     7,     8,    39,    40,    47,
      54,   112,   114,   112,   116,    64,    87,   101,   158,     5,
      54,    96,    89,    87,    64,   130,    81,    82,    87,   152,
      89,    82
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
     101,   101,   101,   102,   102,   102,   103,   103,   103,   103,
     104,   105,   105,   107,   106,   108,   106,   110,   109,   111,
     109,   112,   112,   112,   112,   112,   112,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   117,   117,   118,   118,
     118,   119,   119,   120,   121,   121,   122,   122,   123,   124,
     125,   125,   126,   127,   127,   128,   129,   129,   129,   129,
     129,   129,   130,   130,   130,   130,   132,   131,   133,   131,
     134,   131,   135,   135,   135,   135,   135,   135,   135,   135,
     136,   136,   136,   136,   136,   136,   137,   137,   138,   138,
     139,   139,   139,   139,   139,   140,   140,   140,   140,   140,
     141,   141,   142,   142,   143,   143,   144,   144,   145,   146,
     147,   147,   148,   148,   148,   148,   148,   149,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   151,   151,   151,
     151,   152,   152,   153,   153,   154,   154,   154,   155,   155,
     157,   156,   156,   156,   156,   156,   156,   158,   156,   160,
     159,   161,   161,   162,   163,   163,   164,   164,   166,   167,
     165
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
       1,     1,     1,     4,     3,     5,     2,     2,     2,     2,
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
       6,     2,     1,     5,     0,     6,     0,     2,     0,     0,
       9
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
      -1,     6,    -1,     7,    -1,    59,   101,    64,    87,    -1,
      60,    64,    87,    -1,   102,    59,   101,    64,    87,    -1,
      68,    96,    -1,    69,    96,    -1,    74,    96,    -1,    75,
      96,    -1,    55,     4,    77,   105,   117,    78,    -1,    -1,
     106,    -1,    -1,   107,   109,    80,    -1,    -1,   106,   108,
     109,    80,    -1,    -1,     3,   110,   113,    -1,    -1,    41,
     111,   115,    -1,     5,    -1,    54,    -1,     8,    -1,     6,
      -1,     7,    -1,    47,    -1,    39,    -1,    40,    -1,   114,
      -1,   113,    61,   114,    -1,     5,    62,   112,    -1,     5,
      -1,   116,    -1,   115,    61,   116,    -1,     5,    62,   112,
      -1,    -1,   119,    -1,    -1,    56,    -1,    57,    -1,   118,
     150,    -1,   119,   118,   150,    -1,    76,   152,    83,    -1,
       8,    64,    96,    -1,   121,    61,     8,    64,    96,    -1,
      77,    64,    78,    -1,    77,   121,    78,    -1,    52,    96,
      -1,   125,    -1,   126,    -1,   125,   126,    -1,    50,    81,
       5,    82,    89,    -1,    -1,    49,    89,    -1,    51,    89,
     124,   127,    -1,    95,    70,     5,    -1,     4,    70,     5,
      -1,    95,    70,    54,    -1,     4,    70,    54,    -1,   129,
      70,     5,    -1,   129,    70,    54,    -1,    -1,   130,    70,
       5,    81,   152,    82,    -1,   130,    70,     5,    -1,   130,
      70,    54,    -1,    -1,    95,    70,     5,    81,   152,    82,
     132,   130,    -1,    -1,   129,    70,     5,    81,   152,    82,
     133,   130,    -1,    -1,     4,    70,     5,    81,   152,    82,
     134,   130,    -1,    95,    45,    -1,    95,    46,    -1,    45,
      95,    -1,    46,    95,    -1,   129,    45,    -1,   129,    46,
      -1,    45,   129,    -1,    46,   129,    -1,    96,    23,    96,
      -1,    96,    24,    96,    -1,    96,    17,    96,    -1,    96,
      15,    96,    -1,    96,    16,    96,    -1,    96,    14,    96,
      -1,    96,    31,    96,    -1,    96,    33,    96,    -1,    96,
      32,    96,    -1,    96,    34,    96,    -1,    96,    69,    96,
      -1,    96,    68,    96,    -1,    96,    71,    96,    -1,    96,
      72,    96,    -1,    96,    73,    96,    -1,    96,    67,    96,
      -1,    96,    65,    96,    -1,    96,    66,    96,    -1,    96,
      20,    96,    -1,    96,    18,    96,    -1,     3,   142,    -1,
      41,   144,    -1,   143,    -1,   142,    61,   143,    -1,     5,
      62,    96,    -1,     5,    -1,   145,    -1,   144,    61,   145,
      -1,    54,    62,    96,    -1,    97,    62,    96,    -1,     5,
      -1,   147,    70,     5,    -1,    25,   147,    70,    71,    -1,
      25,   147,    64,    71,    -1,    25,   147,    64,     5,    -1,
      25,   147,    64,     4,    -1,    25,   147,    -1,     5,    70,
      70,    70,    -1,    42,     5,    81,    82,    89,    -1,    42,
       4,    81,    82,    89,    -1,    42,    75,     4,    81,    82,
      89,    -1,    42,     5,    81,   149,    82,    89,    -1,    42,
       4,    81,   149,    82,    89,    -1,    42,     5,    81,   142,
      82,    89,    -1,    42,     4,    81,   142,    82,    89,    -1,
      42,     5,    81,   142,    61,   149,    82,    89,    -1,    42,
       4,    81,   142,    61,   149,    82,    89,    -1,    42,    81,
      82,    89,    -1,    42,    81,   149,    82,    89,    -1,    42,
      81,   142,    82,    89,    -1,    42,    81,   142,    61,   149,
      82,    89,    -1,    -1,   153,    -1,    96,    -1,   153,    61,
      96,    -1,    -1,   154,    81,   152,    82,    -1,   154,    76,
      96,    83,    -1,     5,    -1,   155,    64,     5,    -1,    -1,
     155,    64,     5,    81,   152,    82,   157,   154,    -1,   155,
      64,    54,    -1,   155,    64,     5,    -1,   155,    64,     4,
      70,    54,    -1,   155,    64,     4,    70,    48,    -1,   155,
      64,     4,    70,    48,    81,   152,    82,    -1,    -1,   155,
      64,     4,    70,     5,    81,   152,    82,   158,   130,    -1,
      -1,     5,    81,   152,    82,   160,   154,    -1,    38,    96,
      -1,    38,    -1,    10,    81,    96,    82,    89,    -1,    -1,
     163,    13,    81,    96,    82,    89,    -1,    -1,    12,    89,
      -1,    -1,    -1,    11,    81,    96,    82,    89,   166,   163,
     167,   164,    -1
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
     179,   181,   183,   185,   190,   194,   200,   203,   206,   209,
     212,   219,   220,   222,   223,   227,   228,   233,   234,   238,
     239,   243,   245,   247,   249,   251,   253,   255,   257,   259,
     261,   265,   269,   271,   273,   277,   281,   282,   284,   285,
     287,   289,   292,   296,   300,   304,   310,   314,   318,   321,
     323,   325,   328,   334,   335,   338,   343,   347,   351,   355,
     359,   363,   367,   368,   375,   379,   383,   384,   393,   394,
     403,   404,   413,   416,   419,   422,   425,   428,   431,   434,
     437,   441,   445,   449,   453,   457,   461,   465,   469,   473,
     477,   481,   485,   489,   493,   497,   501,   505,   509,   513,
     517,   520,   523,   525,   529,   533,   535,   537,   541,   545,
     549,   551,   555,   560,   565,   570,   575,   578,   583,   589,
     595,   602,   609,   616,   623,   630,   639,   648,   653,   659,
     665,   673,   674,   676,   678,   682,   683,   688,   693,   695,
     699,   700,   709,   713,   717,   723,   729,   738,   739,   750,
     751,   758,   761,   763,   769,   770,   777,   778,   781,   782,
     783
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
     345,   346,   347,   351,   352,   353,   357,   358,   359,   360,
     364,   368,   369,   373,   373,   374,   374,   378,   378,   379,
     379,   383,   384,   385,   386,   387,   388,   389,   390,   394,
     395,   399,   400,   404,   405,   409,   413,   414,   418,   419,
     420,   424,   425,   429,   433,   434,   438,   439,   443,   447,
     451,   452,   456,   460,   461,   465,   469,   470,   471,   472,
     473,   474,   478,   479,   480,   481,   485,   485,   486,   486,
     487,   487,   491,   492,   493,   494,   495,   496,   497,   498,
     502,   503,   504,   505,   506,   507,   511,   512,   516,   517,
     521,   522,   523,   524,   525,   529,   530,   531,   532,   533,
     537,   538,   542,   543,   547,   548,   552,   553,   557,   561,
     565,   566,   570,   571,   572,   573,   574,   578,   582,   584,
     586,   588,   590,   592,   594,   596,   598,   603,   605,   607,
     609,   614,   615,   619,   620,   624,   625,   626,   630,   631,
     635,   635,   636,   637,   638,   639,   640,   641,   641,   645,
     645,   649,   650,   654,   658,   660,   665,   666,   670,   671,
     670
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
  const int Parser::yylast_ = 1045;
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

