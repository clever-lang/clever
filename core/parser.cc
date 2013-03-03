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

    { (yysemantic_stack_[(4) - (0)].switch_)->addCase(NULL, (yysemantic_stack_[(4) - (4)].block)); (yyval.switch_) = (yysemantic_stack_[(4) - (0)].switch_);     }
    break;

  case 78:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 79:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 80:

    { (yyval.node) = new ast::Boolean(ast::Boolean::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 81:

    { (yyval.node) = new ast::Bitwise(ast::Bitwise::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
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

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 168:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 169:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 170:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 171:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 172:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 173:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 174:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 175:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 176:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 177:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 178:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 179:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 180:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 181:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 182:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 183:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 184:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 185:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 186:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 187:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 188:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 189:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 190:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 191:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 192:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 193:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 194:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 195:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 196:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 197:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 198:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 199:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 200:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 201:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 202:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 203:

    { (yyval.narray) = NULL; }
    break;

  case 205:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 206:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 207:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 208:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 209:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 211:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 212:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 213:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 214:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 215:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 216:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 217:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 218:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 219:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 220:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 221:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 222:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 223:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 224:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 225:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 227:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 228:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 229:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 230:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 231:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 232:

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
  const short int Parser::yypact_ninf_ = -311;
  const short int
  Parser::yypact_[] =
  {
      -311,     4,  -311,  -311,   298,    27,   -69,   164,  -311,  -311,
    -311,   -46,   -37,  -311,   121,   465,  -311,  -311,    74,    12,
     132,    70,   162,   162,  -311,    70,   465,  -311,  -311,   136,
      69,   465,    59,   465,  -311,  -311,    80,   126,   157,  -311,
    -311,     1,    72,   142,  -311,  -311,  -311,  -311,   171,  -311,
       5,   183,   192,   199,   203,   204,  -311,   223,   211,   212,
     215,  -311,  -311,   185,   227,  -311,    25,   465,   465,   465,
    -311,    71,   216,   465,   465,   465,   465,    59,  -311,     1,
     858,  -311,   174,  -311,  -311,  -311,  -311,  -311,  -311,  -311,
    -311,  -311,  -311,  -311,   234,   228,  -311,   218,   219,   303,
      96,  -311,  -311,   240,   151,   241,   242,   179,   241,   179,
     271,   858,   245,   465,   858,   243,   264,   263,   250,    55,
      60,   636,  -311,  -311,  -311,  -311,  -311,    18,   465,   465,
    -311,  -311,  -311,    63,  -311,  -311,  -311,  -311,  -311,    24,
    -311,  -311,  -311,   465,    27,   248,   249,  -311,   253,   696,
     717,    33,    15,     6,  -311,  -311,  -311,  -311,   465,   465,
     465,   465,   465,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   465,   465,   465,   465,   465,   465,   465,    74,
      21,    29,   265,   465,  -311,    65,   117,   153,   266,   282,
     271,  -311,    42,   777,  -311,   465,   465,  -311,  -311,   346,
    -311,  -311,   274,  -311,   939,   533,   276,  -311,   288,   167,
    -311,   858,  -311,   465,   465,  -311,    70,    70,  -311,  -311,
    -311,  -311,  -311,   138,    70,   -18,   278,   299,   299,   299,
     299,   209,   209,  1044,  1044,   951,   879,   962,   939,   973,
    1033,  1055,   189,   189,  -311,  -311,  -311,   858,  -311,    70,
     -13,   279,    70,    64,   283,   284,   554,  -311,  -311,  -311,
     359,    70,  -311,  -311,    -2,   102,   111,   292,   858,   858,
     312,   465,  -311,   465,    28,   465,   296,   300,  -311,  -311,
    -311,   310,  -311,   376,    70,    70,  -311,   376,    70,    70,
    -311,   376,    70,    70,    70,    70,   301,  -311,  -311,  -311,
     306,   344,    -2,   111,  -311,  -311,   307,  -311,   465,   308,
     311,   314,   315,  -311,   316,  -311,  -311,   178,  -311,   319,
     317,  -311,  -311,   318,  -311,  -311,   320,  -311,  -311,  -311,
    -311,    70,  -311,  -311,   344,   321,   387,   392,  -311,   208,
     858,  -311,  -311,   465,   465,  -311,  -311,   465,   465,   390,
    -311,    70,    70,    70,  -311,  -311,  -311,   342,   345,  -311,
     343,   347,  -311,   217,   348,   175,  -311,  -311,   325,   327,
    -311,   340,   615,   329,   333,   404,  -311,  -311,  -311,   156,
     387,   156,   392,   165,   353,   356,   358,   369,   241,   370,
     188,  -311,   217,   372,  -311,   340,   340,  -311,  -311,   178,
     160,  -311,  -311,   465,    70,  -311,  -311,  -311,  -311,  -311,
    -311,  -311,  -311,  -311,  -311,  -311,  -311,  -311,  -311,   298,
     379,  -311,  -311,   364,  -311,   798,  -311,   298,  -311,   298,
     340,   465,    70,   298,   366,  -311,  -311
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    35,    38,    39,
      37,     0,     0,    30,     0,   224,    41,    42,     0,     0,
       0,     0,     0,     0,    40,     0,     0,    31,    36,     0,
       0,   203,     4,     0,     5,    16,     0,     0,     0,    17,
      18,     0,     0,    46,    26,    23,    44,    43,     0,    22,
      63,     0,     0,     0,     0,     0,    11,     0,     0,    47,
       0,    14,    13,   177,   172,   174,     0,   203,     0,     0,
     182,   188,     0,     0,     0,     0,     0,     0,    58,    48,
     223,    49,    61,    59,    56,    54,    53,    51,    50,    52,
      55,    57,    60,    47,     0,   173,   178,     0,     0,     0,
       0,     4,    34,     0,    35,   146,     0,   150,   147,   151,
       0,   120,     0,     0,   205,     0,   204,     0,     0,     0,
       0,     0,    25,    20,    21,   144,   145,     0,     0,     0,
      19,   148,   149,     0,    10,    15,     7,     8,     6,     0,
      24,     9,    12,     0,     0,   129,    28,   131,     0,     0,
       0,     0,     0,     0,    78,    79,    80,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,     0,     0,     0,     0,   125,
     121,   122,    83,     0,   115,     0,     0,   118,    27,     0,
     119,    45,   128,   130,   181,     0,   132,   133,     0,   215,
     214,   176,   175,   203,   203,   221,     0,     0,   187,   186,
     185,   183,   184,   177,     0,     0,     0,   157,   155,   156,
     154,   171,   170,   152,   153,   158,   160,   159,   161,   168,
     169,   167,   163,   162,   164,   165,   166,   180,   179,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   128,   132,
       0,     0,   127,   123,   108,    84,     0,     0,   206,   116,
       0,   203,    65,   203,     0,   203,     0,     0,   207,   225,
     230,     0,   199,     0,     0,     0,   191,     0,     0,     0,
     190,     0,     0,     0,     0,     0,     0,   126,   111,   112,
       0,     0,   109,     0,    89,    91,     0,    66,     0,     0,
       0,     0,   217,   216,     0,   142,    29,   222,   226,     0,
       0,   201,   200,     0,   196,   194,     0,   195,   193,   192,
      33,     0,    82,   113,     0,     0,     0,     0,    86,     0,
     117,   138,   140,   203,   203,   212,   134,     0,   203,   231,
     189,     0,     0,     0,   124,   114,    88,   104,    90,   101,
       0,    92,   105,     0,     0,     0,   134,   134,     0,     0,
     207,   143,     0,     0,     0,   228,   202,   198,   197,     0,
       0,     0,     0,    35,    38,    39,    37,    36,     0,     0,
      63,     4,     0,     0,    67,   139,   141,   219,   218,   213,
       0,   209,   208,     0,     0,   232,    93,    96,    97,    95,
      99,   100,    98,    94,   103,   102,   107,   106,     4,    75,
       0,     4,   134,   136,   137,     0,   229,    74,     4,    77,
     220,   203,     0,    76,     0,   227,   135
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -311,  -311,  -311,     3,  -311,   -19,     8,  -311,  -311,  -311,
    -311,    -4,    16,   -15,  -311,  -311,  -311,    54,  -311,  -311,
    -311,  -311,  -311,  -311,  -311,   152,  -311,  -311,    76,  -311,
      78,  -311,    81,  -311,   158,  -311,  -311,  -311,  -311,  -311,
    -311,  -311,   277,  -311,  -311,    -1,  -310,    11,  -311,  -311,
    -311,    20,  -311,  -311,  -311,  -311,  -311,  -311,  -128,  -134,
    -311,   287,    23,  -311,  -311,  -167,  -260,  -311,   -58,  -311,
     104,  -311,    32,  -311,  -311,    35,  -311,  -311,  -311,  -311,
    -311,  -311,  -311,  -311
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   119,    34,    35,    78,    37,    38,    39,
      40,    79,   114,    42,    43,    44,   339,   389,   365,    81,
      45,   264,   265,   266,   303,   306,   336,   337,   414,   358,
     359,   361,   362,   300,   301,   302,    46,   120,    47,    48,
     189,   190,   191,   262,    49,    82,   371,    83,   366,   367,
     346,    84,    85,    86,    87,    88,    89,    53,    64,    65,
      95,    96,    90,    71,    55,   226,    56,    91,   115,   116,
     317,    57,    92,   370,   422,    93,   278,    60,    61,   349,
     405,    62,   318,   375
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -212;
  const short int
  Parser::yytable_[] =
  {
        41,    66,   102,    50,     3,     4,   110,   106,   106,   148,
     212,   223,    36,   251,   254,    51,    97,    98,   105,   108,
     221,   107,   109,   202,    52,   225,   223,    54,   208,   209,
     145,    80,    63,   311,   223,    68,    58,   218,   219,    59,
    -110,   333,   111,   283,    69,   -85,   125,   126,   287,   121,
     131,   132,   250,   253,   298,   299,   395,   396,     5,     6,
       7,     8,     9,    10,   284,    11,    12,   117,   206,   288,
     257,   127,   203,   146,   355,   133,   312,    13,   210,   147,
      14,   184,   313,   -85,   149,   150,   222,    99,   224,   154,
     155,   156,   157,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,   249,   220,   -87,    25,    26,    27,    28,
      29,   252,   430,    30,   304,    41,   320,   207,    50,   147,
     323,   199,   258,   118,   326,   291,    70,    36,    94,   193,
      51,    31,    32,   198,   128,   151,    33,   100,   200,    52,
     112,   152,    54,   -87,   204,   205,   292,   101,   129,   212,
     113,    58,   305,   212,    59,   276,   277,   212,   259,   211,
     122,   406,   407,   408,   409,   423,   103,   104,     8,     9,
      10,   203,   183,   101,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   410,   411,   279,   280,   256,
     143,    16,    17,   412,   -64,   282,   123,   207,   281,    24,
     413,   268,   269,   309,   424,   310,    28,   314,   -64,   131,
     132,   103,   383,   384,   385,   386,   -62,   -62,  -210,   -68,
     286,  -211,    67,   290,   392,   393,   -63,   124,    31,    77,
     -62,   -62,   297,    33,   133,    67,    67,   143,   275,   187,
     -63,   130,   -73,   394,   347,   -63,    16,    17,   187,   348,
     175,   176,   177,   134,    24,   321,   322,   363,   364,   324,
     325,   387,   135,   327,   328,   329,   330,   173,   174,   136,
     175,   176,   177,   137,   138,   368,   369,   139,   144,   179,
     373,   140,   141,    31,    77,   142,   178,   153,    33,   180,
     181,     5,     6,     7,     8,     9,    10,   182,    11,    12,
     185,   186,   354,  -212,  -212,  -212,  -212,   162,   129,   163,
      13,   188,   192,    14,   340,   195,   194,   196,   197,   213,
     214,   261,   376,   377,   378,   215,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,   255,   260,   106,    25,
      26,    27,    28,    29,   270,   271,    30,   273,   274,   388,
     285,   289,   390,   372,   296,   293,   294,   173,   174,   307,
     175,   176,   177,   434,    31,    32,   308,   106,   315,    33,
     319,   223,   316,   331,   332,   426,    19,   338,   388,   350,
     341,   390,   357,   342,   419,   343,   344,   360,   345,   351,
     352,   356,   353,   374,   379,   381,   380,   397,   382,   398,
     400,   402,   391,   435,   403,    41,   404,   -71,    50,   425,
     -72,   427,   -70,    41,   429,    41,    50,    36,    50,    41,
      51,   433,    50,   -69,   418,    36,   421,    36,    51,    52,
      51,    36,    54,   428,    51,   431,   420,    52,   436,    52,
      54,    58,    54,    52,    59,   335,    54,   416,   415,    58,
     334,    58,    59,   417,    59,    58,   248,   263,    59,     6,
       7,     8,     9,    10,   399,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    17,     0,    72,     0,     0,
      22,    23,    24,     0,     0,     0,     0,     0,     0,    28,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,    74,     0,     0,     0,     0,    75,
      76,    31,    77,     0,     0,     0,    33,   158,   159,   160,
     161,   162,     0,   163,     0,     0,   164,   165,     0,     0,
       0,     0,     0,     0,   166,   167,   168,   169,   158,   159,
     160,   161,   162,     0,   163,     0,     0,   164,   165,     0,
       0,     0,     0,     0,     0,   166,   167,   168,   169,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   170,   171,
     172,   173,   174,     0,   175,   176,   177,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   272,     0,     0,   170,
     171,   172,   173,   174,     0,   175,   176,   177,     0,   158,
     159,   160,   161,   162,     0,   163,     0,   295,   164,   165,
       0,     0,     0,     0,     0,     0,   166,   167,   168,   169,
     158,   159,   160,   161,   162,     0,   163,     0,     0,   164,
     165,     0,     0,     0,     0,     0,     0,   166,   167,   168,
     169,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     170,   171,   172,   173,   174,     0,   175,   176,   177,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   401,     0,
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
     432,   164,   165,     0,     0,     0,     0,     0,     0,   166,
     167,   168,   169,   158,   159,   160,   161,   162,     0,   163,
       0,     0,   164,   165,     0,     0,     0,     0,     0,     0,
     166,     0,   168,   169,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   170,   171,   172,   173,   174,     0,   175,
     176,   177,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   170,   171,   172,   173,   174,     0,
     175,   176,   177,   158,   159,   160,   161,   162,     0,   163,
       0,     0,   164,   165,     0,   158,   159,   160,   161,   162,
     166,   163,   168,     0,   164,   165,   158,   159,   160,   161,
     162,     0,   163,     0,   168,   164,   165,   158,   159,   160,
     161,   162,     0,   163,     0,     0,   164,   165,     0,     0,
       0,     0,     0,     0,   170,   171,   172,   173,   174,     0,
     175,   176,   177,     0,     0,     0,   170,   171,   172,   173,
     174,     0,   175,   176,   177,     0,     0,   170,   171,   172,
     173,   174,     0,   175,   176,   177,     0,     0,     0,   171,
     172,   173,   174,     0,   175,   176,   177,   158,   159,   160,
     161,   162,     0,   163,     0,     0,   164,   165,   158,   159,
     160,   161,   162,     0,   163,     0,     0,  -212,  -212,   158,
     159,   160,   161,   162,     0,   163,     0,     0,   164,   165,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     172,   173,   174,     0,   175,   176,   177,     0,     0,     0,
       0,     0,   173,   174,     0,   175,   176,   177,     0,     0,
       0,     0,     0,   173,   174,     0,   175,   176,   177
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,    70,    21,     4,     0,     2,    25,    22,    23,    67,
     144,     5,     4,   180,   181,     4,     4,     5,    22,    23,
       5,    22,    23,     5,     4,   153,     5,     4,     4,     5,
       5,    15,     5,     5,     5,    81,     4,     4,     5,     4,
      42,   301,    26,    61,    81,     3,    45,    46,    61,    33,
      45,    46,   180,   181,    56,    57,   366,   367,     3,     4,
       5,     6,     7,     8,    82,    10,    11,     8,     5,    82,
       5,    70,    54,    48,   334,    70,    48,    22,    54,    54,
      25,   100,    54,    41,    68,    69,    71,    75,    82,    73,
      74,    75,    76,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    82,    71,     3,    51,    52,    53,    54,
      55,    82,   422,    58,     3,   119,   283,    54,   119,    54,
     287,    61,     5,    64,   291,    61,     5,   119,    54,   113,
     119,    76,    77,    78,    62,    64,    81,     5,    78,   119,
       4,    70,   119,    41,   128,   129,    82,    77,    76,   283,
      81,   119,    41,   287,   119,   213,   214,   291,     5,   143,
      80,     5,     6,     7,     8,     5,     4,     5,     6,     7,
       8,    54,    76,    77,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,    39,    40,   216,   217,   183,
      62,    39,    40,    47,    62,   224,    80,    54,    70,    47,
      54,   195,   196,   271,    54,   273,    54,   275,    76,    45,
      46,     4,     5,     6,     7,     8,    62,    76,    64,    64,
     249,    64,    81,   252,    59,    60,    62,    80,    76,    77,
      76,    76,   261,    81,    70,    81,    81,    62,    81,    70,
      76,    80,    64,    78,    76,    76,    39,    40,    70,    81,
      71,    72,    73,    80,    47,   284,   285,    59,    60,   288,
     289,    54,    80,   292,   293,   294,   295,    68,    69,    80,
      71,    72,    73,    80,    80,   343,   344,    64,    61,    61,
     348,    80,    80,    76,    77,    80,    62,    81,    81,    81,
      81,     3,     4,     5,     6,     7,     8,     4,    10,    11,
      70,    70,   331,    14,    15,    16,    17,    18,    76,    20,
      22,    50,    77,    25,   308,    61,    83,    64,    78,    81,
      81,    49,   351,   352,   353,    82,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    81,    81,   363,    51,
      52,    53,    54,    55,     8,    81,    58,    81,    70,   363,
      82,    82,   363,   347,     5,    82,    82,    68,    69,    77,
      71,    72,    73,   431,    76,    77,    64,   392,    82,    81,
      70,     5,    82,    82,    78,   404,    42,    80,   392,    70,
      82,   392,     5,    82,   391,    81,    81,     5,    82,    82,
      82,    80,    82,    13,    62,    62,    61,    82,    61,    82,
      70,    82,    64,   432,    81,   419,    12,    64,   419,   403,
      64,   418,    64,   427,   421,   429,   427,   419,   429,   433,
     419,   428,   433,    64,    64,   427,    64,   429,   427,   419,
     429,   433,   419,    64,   433,    81,   392,   427,    82,   429,
     427,   419,   429,   433,   419,   303,   433,   381,   380,   427,
     302,   429,   427,   382,   429,   433,   179,   190,   433,     4,
       5,     6,     7,     8,   370,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    -1,    42,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    74,
      75,    76,    77,    -1,    -1,    -1,    81,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    -1,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    71,    72,    73,    -1,    14,
      15,    16,    17,    18,    -1,    20,    -1,    83,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
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
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      71,    72,    73,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    -1,    14,    15,    16,    17,    18,
      31,    20,    33,    -1,    23,    24,    14,    15,    16,    17,
      18,    -1,    20,    -1,    33,    23,    24,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      71,    72,    73,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    -1,    71,    72,    73,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    71,    72,    73,    -1,    -1,    -1,    66,
      67,    68,    69,    -1,    71,    72,    73,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    -1,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    68,    69,    -1,    71,    72,    73
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
     129,    64,    59,    60,    78,   130,   130,    82,    82,   154,
      70,    83,    82,    81,    12,   164,     5,     6,     7,     8,
      39,    40,    47,    54,   112,   114,   112,   116,    64,    87,
     101,    64,   158,     5,    54,    96,    89,    87,    64,    87,
     130,    81,    82,    87,   152,    89,    82
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
     101,   101,   101,   101,   102,   102,   102,   102,   103,   103,
     103,   103,   104,   105,   105,   107,   106,   108,   106,   110,
     109,   111,   109,   112,   112,   112,   112,   112,   112,   112,
     112,   113,   113,   114,   114,   115,   115,   116,   117,   117,
     118,   118,   118,   119,   119,   120,   121,   121,   122,   122,
     123,   124,   125,   125,   126,   127,   127,   128,   129,   129,
     129,   129,   129,   129,   130,   130,   130,   130,   132,   131,
     133,   131,   134,   131,   135,   135,   135,   135,   135,   135,
     135,   135,   136,   136,   136,   136,   136,   136,   137,   137,
     138,   138,   139,   139,   139,   139,   139,   140,   140,   140,
     140,   140,   141,   141,   142,   142,   143,   143,   144,   144,
     145,   146,   147,   147,   148,   148,   148,   148,   148,   149,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   151,
     151,   151,   151,   152,   152,   153,   153,   154,   154,   154,
     155,   155,   157,   156,   156,   156,   156,   156,   156,   158,
     156,   160,   159,   161,   161,   162,   163,   163,   164,   164,
     166,   167,   165
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
       3,     3,     2,     2,     1,     3,     3,     1,     1,     3,
       3,     3,     1,     3,     4,     4,     4,     4,     2,     4,
       5,     5,     6,     6,     6,     6,     6,     8,     8,     4,
       5,     5,     7,     0,     1,     1,     3,     0,     4,     4,
       1,     3,     0,     8,     3,     3,     5,     5,     8,     0,
      10,     0,     6,     2,     1,     5,     0,     6,     0,     2,
       0,     0,     9
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
      87,    -1,   102,    60,    64,    87,    -1,    68,    96,    -1,
      69,    96,    -1,    74,    96,    -1,    75,    96,    -1,    55,
       4,    77,   105,   117,    78,    -1,    -1,   106,    -1,    -1,
     107,   109,    80,    -1,    -1,   106,   108,   109,    80,    -1,
      -1,     3,   110,   113,    -1,    -1,    41,   111,   115,    -1,
       5,    -1,    54,    -1,     8,    -1,     6,    -1,     7,    -1,
      47,    -1,    39,    -1,    40,    -1,   114,    -1,   113,    61,
     114,    -1,     5,    62,   112,    -1,     5,    -1,   116,    -1,
     115,    61,   116,    -1,     5,    62,   112,    -1,    -1,   119,
      -1,    -1,    56,    -1,    57,    -1,   118,   150,    -1,   119,
     118,   150,    -1,    76,   152,    83,    -1,     8,    64,    96,
      -1,   121,    61,     8,    64,    96,    -1,    77,    64,    78,
      -1,    77,   121,    78,    -1,    52,    96,    -1,   125,    -1,
     126,    -1,   125,   126,    -1,    50,    81,     5,    82,    89,
      -1,    -1,    49,    89,    -1,    51,    89,   124,   127,    -1,
      95,    70,     5,    -1,     4,    70,     5,    -1,    95,    70,
      54,    -1,     4,    70,    54,    -1,   129,    70,     5,    -1,
     129,    70,    54,    -1,    -1,   130,    70,     5,    81,   152,
      82,    -1,   130,    70,     5,    -1,   130,    70,    54,    -1,
      -1,    95,    70,     5,    81,   152,    82,   132,   130,    -1,
      -1,   129,    70,     5,    81,   152,    82,   133,   130,    -1,
      -1,     4,    70,     5,    81,   152,    82,   134,   130,    -1,
      95,    45,    -1,    95,    46,    -1,    45,    95,    -1,    46,
      95,    -1,   129,    45,    -1,   129,    46,    -1,    45,   129,
      -1,    46,   129,    -1,    96,    23,    96,    -1,    96,    24,
      96,    -1,    96,    17,    96,    -1,    96,    15,    96,    -1,
      96,    16,    96,    -1,    96,    14,    96,    -1,    96,    31,
      96,    -1,    96,    33,    96,    -1,    96,    32,    96,    -1,
      96,    34,    96,    -1,    96,    69,    96,    -1,    96,    68,
      96,    -1,    96,    71,    96,    -1,    96,    72,    96,    -1,
      96,    73,    96,    -1,    96,    67,    96,    -1,    96,    65,
      96,    -1,    96,    66,    96,    -1,    96,    20,    96,    -1,
      96,    18,    96,    -1,     3,   142,    -1,    41,   144,    -1,
     143,    -1,   142,    61,   143,    -1,     5,    62,    96,    -1,
       5,    -1,   145,    -1,   144,    61,   145,    -1,    54,    62,
      96,    -1,    97,    62,    96,    -1,     5,    -1,   147,    70,
       5,    -1,    25,   147,    70,    71,    -1,    25,   147,    64,
      71,    -1,    25,   147,    64,     5,    -1,    25,   147,    64,
       4,    -1,    25,   147,    -1,     5,    70,    70,    70,    -1,
      42,     5,    81,    82,    89,    -1,    42,     4,    81,    82,
      89,    -1,    42,    75,     4,    81,    82,    89,    -1,    42,
       5,    81,   149,    82,    89,    -1,    42,     4,    81,   149,
      82,    89,    -1,    42,     5,    81,   142,    82,    89,    -1,
      42,     4,    81,   142,    82,    89,    -1,    42,     5,    81,
     142,    61,   149,    82,    89,    -1,    42,     4,    81,   142,
      61,   149,    82,    89,    -1,    42,    81,    82,    89,    -1,
      42,    81,   149,    82,    89,    -1,    42,    81,   142,    82,
      89,    -1,    42,    81,   142,    61,   149,    82,    89,    -1,
      -1,   153,    -1,    96,    -1,   153,    61,    96,    -1,    -1,
     154,    81,   152,    82,    -1,   154,    76,    96,    83,    -1,
       5,    -1,   155,    64,     5,    -1,    -1,   155,    64,     5,
      81,   152,    82,   157,   154,    -1,   155,    64,    54,    -1,
     155,    64,     5,    -1,   155,    64,     4,    70,    54,    -1,
     155,    64,     4,    70,    48,    -1,   155,    64,     4,    70,
      48,    81,   152,    82,    -1,    -1,   155,    64,     4,    70,
       5,    81,   152,    82,   158,   130,    -1,    -1,     5,    81,
     152,    82,   160,   154,    -1,    38,    96,    -1,    38,    -1,
      10,    81,    96,    82,    89,    -1,    -1,   163,    13,    81,
      96,    82,    89,    -1,    -1,    12,    89,    -1,    -1,    -1,
      11,    81,    96,    82,    89,   166,   163,   167,   164,    -1
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
     179,   181,   183,   185,   187,   192,   196,   202,   207,   210,
     213,   216,   219,   226,   227,   229,   230,   234,   235,   240,
     241,   245,   246,   250,   252,   254,   256,   258,   260,   262,
     264,   266,   268,   272,   276,   278,   280,   284,   288,   289,
     291,   292,   294,   296,   299,   303,   307,   311,   317,   321,
     325,   328,   330,   332,   335,   341,   342,   345,   350,   354,
     358,   362,   366,   370,   374,   375,   382,   386,   390,   391,
     400,   401,   410,   411,   420,   423,   426,   429,   432,   435,
     438,   441,   444,   448,   452,   456,   460,   464,   468,   472,
     476,   480,   484,   488,   492,   496,   500,   504,   508,   512,
     516,   520,   524,   527,   530,   532,   536,   540,   542,   544,
     548,   552,   556,   558,   562,   567,   572,   577,   582,   585,
     590,   596,   602,   609,   616,   623,   630,   637,   646,   655,
     660,   666,   672,   680,   681,   683,   685,   689,   690,   695,
     700,   702,   706,   707,   716,   720,   724,   730,   736,   745,
     746,   757,   758,   765,   768,   770,   776,   777,   784,   785,
     788,   789,   790
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
     345,   346,   347,   348,   352,   353,   354,   355,   359,   360,
     361,   362,   366,   370,   371,   375,   375,   376,   376,   380,
     380,   381,   381,   385,   386,   387,   388,   389,   390,   391,
     392,   396,   397,   401,   402,   406,   407,   411,   415,   416,
     420,   421,   422,   426,   427,   431,   435,   436,   440,   441,
     445,   449,   453,   454,   458,   462,   463,   467,   471,   472,
     473,   474,   475,   476,   480,   481,   482,   483,   487,   487,
     488,   488,   489,   489,   493,   494,   495,   496,   497,   498,
     499,   500,   504,   505,   506,   507,   508,   509,   513,   514,
     518,   519,   523,   524,   525,   526,   527,   531,   532,   533,
     534,   535,   539,   540,   544,   545,   549,   550,   554,   555,
     559,   563,   567,   568,   572,   573,   574,   575,   576,   580,
     584,   586,   588,   590,   592,   594,   596,   598,   600,   605,
     607,   609,   611,   616,   617,   621,   622,   626,   627,   628,
     632,   633,   637,   637,   638,   639,   640,   641,   642,   643,
     643,   647,   647,   651,   652,   656,   660,   662,   667,   668,
     672,   673,   672
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
  const int Parser::yylast_ = 1128;
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

