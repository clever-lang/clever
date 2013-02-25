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
		error(yyloc, "Cannot use process block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(3) - (3)].block), (yysemantic_stack_[(3) - (2)].ident), yyloc);
#endif
	}
    break;

  case 32:

    {
#ifndef CLEVER_THREADS
		error(yyloc, "Cannot use process block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].node), yyloc);
#endif
	}
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

  case 55:

    { (yysemantic_stack_[(1) - (1)].assignment)->setUseResult(); }
    break;

  case 62:

    { (yysemantic_stack_[(1) - (1)].property)->setWriteMode(); }
    break;

  case 64:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 65:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 66:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 67:

    { (yyval.node) = new ast::Boolean(ast::Boolean::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 68:

    { (yyval.node) = new ast::Bitwise(ast::Bitwise::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 69:

    { (yyval.class_) = new ast::ClassDef((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 70:

    { (yyval.narray) = NULL; }
    break;

  case 72:

    { (yyval.narray) = new ast::NodeArray(yyloc); }
    break;

  case 73:

    { (yyval.narray) = (yysemantic_stack_[(3) - (1)].narray); }
    break;

  case 74:

    { (yyval.narray) = (yysemantic_stack_[(1) - (1)].narray); }
    break;

  case 76:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 78:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 88:

    { (yysemantic_stack_[(1) - (0)].narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 89:

    { (yysemantic_stack_[(3) - (0)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 90:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), false, yyloc); }
    break;

  case 91:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(1) - (1)].ident), NULL, false, yyloc);     }
    break;

  case 92:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 93:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 94:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), true, yyloc);   }
    break;

  case 95:

    { (yyval.narray) = NULL; }
    break;

  case 97:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 98:

    { (yyval.flags) = ast::PUBLIC;  }
    break;

  case 99:

    { (yyval.flags) = ast::PRIVATE; }
    break;

  case 100:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(2) - (2)].fdecl)); (yysemantic_stack_[(2) - (2)].fdecl)->setVisibility((yysemantic_stack_[(2) - (1)].flags)); }
    break;

  case 101:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].fdecl)); (yysemantic_stack_[(3) - (3)].fdecl)->setVisibility((yysemantic_stack_[(3) - (2)].flags)); }
    break;

  case 102:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 103:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 104:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 105:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 106:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 107:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 109:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 110:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 111:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 112:

    { (yyval.block) = NULL; }
    break;

  case 113:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 114:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 115:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 116:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 117:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 118:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 119:

    { (yyval.mcall) = (yysemantic_stack_[(0) - (0)].mcall); }
    break;

  case 120:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (0)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 121:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 122:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); (yyval.property)->setStatic(); }
    break;

  case 123:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 124:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 125:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 126:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 127:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 128:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 129:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 130:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 131:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 132:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 133:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 134:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 135:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 136:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 137:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 138:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 139:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 140:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 141:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 142:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 143:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 144:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 145:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 146:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 147:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 148:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 149:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 150:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 151:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 152:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 153:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 154:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 155:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 156:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 157:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 158:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 159:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 160:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 161:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 162:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 163:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 164:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 165:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 166:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 167:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 168:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 169:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 170:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 171:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 172:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 173:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 174:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 175:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 176:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 177:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 178:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 179:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 180:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 181:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 182:

    { (yyval.narray) = NULL; }
    break;

  case 184:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 185:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 186:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 187:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 188:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 190:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 191:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 192:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 193:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 194:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 195:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 196:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 197:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 198:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 199:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 200:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 201:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 202:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 203:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 204:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 206:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 207:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 208:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 209:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 210:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 211:

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
  const short int Parser::yypact_ninf_ = -327;
  const short int
  Parser::yypact_[] =
  {
      -327,    10,  -327,  -327,   189,    23,   -29,   200,  -327,  -327,
    -327,   -28,    -4,  -327,    97,   282,  -327,  -327,    71,    11,
     170,   104,   291,   291,  -327,   104,   282,  -327,  -327,   181,
     282,    36,   282,  -327,  -327,   135,   143,   145,  -327,  -327,
     131,   114,   144,  -327,  -327,  -327,   146,  -327,   148,   147,
     160,   161,   162,   169,  -327,   192,   183,   187,   188,  -327,
    -327,   207,   210,  -327,    44,   282,   282,   282,  -327,   158,
     191,   282,   282,   282,   282,    36,  -327,   131,   612,  -327,
    -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,
    -327,   211,   221,  -327,   204,   205,   280,   -11,  -327,  -327,
     224,   172,   226,   227,   226,   244,   612,   228,   612,   223,
     243,   245,   229,    26,   111,   456,  -327,  -327,  -327,  -327,
    -327,    30,   282,   282,  -327,  -327,  -327,  -327,  -327,  -327,
      42,  -327,  -327,  -327,   282,    23,   230,   231,  -327,   235,
     513,   534,    21,    14,     6,  -327,  -327,  -327,  -327,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
      71,     8,     9,   237,   282,  -327,    49,    51,   238,   256,
     244,  -327,    83,  -327,   282,   282,  -327,  -327,   299,  -327,
    -327,   239,  -327,   681,   356,   251,   113,  -327,   612,  -327,
     282,   282,  -327,   104,   104,  -327,  -327,  -327,  -327,  -327,
      67,   104,   122,   240,    25,    25,    25,    25,   206,   206,
     783,   783,   693,   669,   704,   681,   761,   772,   794,   140,
     140,  -327,  -327,  -327,   612,  -327,   104,   123,   241,   104,
     126,   246,   247,   377,  -327,  -327,   318,   104,  -327,  -327,
      65,   163,   165,   612,   612,   271,   282,  -327,   108,   282,
     254,   255,  -327,  -327,  -327,   268,  -327,   332,   104,   104,
    -327,   332,   104,   104,  -327,   332,   104,   104,   104,   104,
     260,  -327,  -327,  -327,   265,   300,    65,   165,  -327,  -327,
     264,   282,   270,   272,   273,  -327,   278,  -327,  -327,   176,
    -327,   276,   279,  -327,  -327,   283,  -327,  -327,   284,  -327,
    -327,  -327,  -327,   104,  -327,  -327,   300,   289,   354,   363,
    -327,   612,  -327,   282,   282,  -327,  -327,   282,   282,   348,
    -327,   104,   104,   104,  -327,  -327,  -327,   316,   319,  -327,
     322,   320,  -327,  -327,   303,   304,  -327,   317,   435,   306,
     308,   384,  -327,  -327,  -327,   125,   354,   125,   363,   317,
    -327,  -327,   176,    56,  -327,  -327,   282,   104,  -327,  -327,
    -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,
    -327,  -327,   321,  -327,   591,  -327,   317,   282,   104,   323,
    -327,  -327
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    34,    37,    38,
      36,     0,     0,    29,     0,   203,    40,    41,     0,     0,
       0,     0,     0,     0,    39,     0,     0,    30,    35,     0,
     182,     4,     0,     5,    16,     0,     0,     0,    17,    18,
       0,     0,    45,    23,    43,    42,     0,    22,    46,     0,
       0,     0,     0,     0,    11,     0,     0,    47,     0,    14,
      13,   156,   151,   153,     0,   182,     0,     0,   161,   167,
       0,     0,     0,     0,     0,     0,    58,    48,   202,    49,
      59,    56,    54,    53,    51,    50,    52,    55,    57,    60,
      47,     0,   152,   157,     0,     0,     0,     0,     4,    33,
       0,    34,   129,     0,   130,     0,   107,     0,   184,     0,
     183,     0,     0,     0,     0,     0,    25,    20,    21,   127,
     128,     0,     0,     0,    19,    10,    15,     7,     8,     6,
       0,    24,     9,    12,     0,     0,   116,    27,   118,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,   112,
     108,   109,    70,   102,     0,     0,   105,    26,     0,   106,
      44,   115,   117,   160,     0,     0,   194,   193,   155,   154,
     182,   182,   200,     0,     0,   166,   165,   164,   162,   163,
     156,     0,     0,     0,   136,   134,   135,   133,   150,   149,
     131,   132,   137,   139,   138,   140,   147,   148,   146,   142,
     141,   143,   144,   145,   159,   158,     0,     0,     0,     0,
       0,     0,     0,     0,   116,   115,     0,     0,   114,   110,
      95,    71,     0,   185,   103,     0,   182,    64,     0,   182,
       0,     0,   186,   204,   209,     0,   178,     0,     0,     0,
     170,     0,     0,     0,   169,     0,     0,     0,     0,     0,
       0,   113,    98,    99,     0,     0,    96,     0,    76,    78,
       0,     0,     0,     0,   196,   195,     0,   125,    28,   201,
     205,     0,     0,   180,   179,     0,   175,   173,     0,   174,
     172,   171,    32,     0,    69,   100,     0,     0,     0,     0,
      73,   104,   123,   182,   182,   191,   119,     0,   182,   210,
     168,     0,     0,     0,   111,   101,    75,    91,    77,    88,
       0,    79,    92,   119,     0,     0,   186,   126,     0,     0,
       0,   207,   181,   177,   176,     0,     0,     0,     0,   124,
     198,   197,   192,     0,   188,   187,     0,     0,   211,    80,
      83,    84,    82,    86,    87,    85,    81,    90,    89,    94,
      93,   119,   121,   122,     0,   208,   199,   182,     0,     0,
     206,   120
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -327,  -327,  -327,   396,  -327,   -21,    -1,  -327,  -327,  -327,
    -327,    -2,   -14,   106,  -327,  -327,  -327,  -327,  -327,  -327,
    -327,   116,  -327,  -327,    47,  -327,    50,  -327,    54,  -327,
     119,  -327,  -327,  -327,  -327,  -327,  -327,  -327,   233,  -327,
    -327,  -327,  -326,     1,  -327,  -327,     2,  -327,  -327,  -327,
    -327,  -327,  -327,    17,  -108,  -327,   253,     3,  -327,  -327,
    -148,  -210,  -327,   -43,  -327,    61,  -327,     4,  -327,  -327,
       5,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   113,    33,    34,    76,    36,    37,    38,
      39,    77,   108,    41,    42,    79,    43,   250,   251,   252,
     287,   290,   318,   319,   377,   338,   339,   341,   342,   284,
     285,   286,    44,   114,    45,    46,   179,   180,   181,   248,
      47,    48,   347,    80,   343,   326,    81,    82,    83,    84,
      85,    86,    51,    62,    63,    92,    93,    87,    69,    53,
     213,    54,    88,   109,   110,   299,    55,    89,   346,   381,
      90,   262,    58,    59,   329,   368,    60,   300,   351
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -191;
  const short int
  Parser::yytable_[] =
  {
        99,    78,    40,    35,   105,    49,    50,    52,    56,    57,
       3,   210,   106,   210,   210,    94,    95,   359,   115,   208,
     102,   104,   139,   238,   241,   205,   206,   199,    61,     5,
       6,     7,     8,     9,    10,   191,    11,    12,    64,  -191,
    -191,  -191,  -191,   153,   111,   154,   195,   196,    13,   136,
      66,    14,   140,   141,   244,   386,   245,   145,   146,   147,
     148,   382,   174,    98,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    67,   315,   175,    25,    26,    27,
      28,    29,   209,    96,   192,   211,   -72,   236,   239,   207,
     164,   165,   137,   166,   167,   168,   197,   112,   138,    30,
      31,   187,    68,   138,    32,   192,   335,   -97,   193,   194,
     383,    40,    35,   293,    49,    50,    52,    56,    57,   302,
     198,   282,   283,   305,   -72,    91,   134,   308,   103,   103,
     369,   370,   371,   372,   265,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   294,   260,   261,   199,
     243,   212,   295,   199,   373,   374,   -74,   199,   288,   188,
     253,   254,   375,   122,  -190,    97,   119,   120,    98,   376,
     267,   271,   263,   264,   275,   107,   189,   123,   237,   240,
     266,   259,     5,     6,     7,     8,     9,    10,   121,    11,
      12,   268,   272,   -63,   -74,   276,   289,   -62,   166,   167,
     168,    13,   116,   292,    14,   270,   296,   -63,   274,   142,
     117,   -62,   118,   124,   125,   143,   281,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   126,   127,   128,
      25,    26,    27,    28,    29,   -61,   129,   303,   304,   327,
      65,   306,   307,   130,   328,   309,   310,   311,   312,   -61,
     131,  -189,    30,    31,   132,   133,   134,    32,   135,   144,
     169,   164,   165,   -61,   166,   167,   168,   321,    65,   170,
     344,   345,   171,   172,   173,   349,     6,     7,     8,     9,
      10,   176,   334,   177,   178,   100,   101,     8,     9,    10,
     123,   184,   182,   183,   186,   247,   185,   255,   200,   201,
     352,   353,   354,   348,   202,   242,   246,   256,   258,   269,
     273,    16,    17,   280,    70,   277,   278,    22,    23,    24,
      16,    17,   291,   297,   298,   301,    28,   210,    24,   313,
     314,   320,    19,   330,   389,    28,   385,    71,    72,   322,
     323,   324,   384,    73,    74,    30,    75,   325,   331,   337,
      32,   350,   332,   333,    30,    75,   336,   390,   340,    32,
     149,   150,   151,   152,   153,   355,   154,   356,   358,   155,
     156,   357,   360,   361,   363,   365,   366,   157,   158,   159,
     160,   149,   150,   151,   152,   153,   367,   154,     4,   387,
     155,   156,   391,   317,   379,   316,   378,   362,   157,   158,
     159,   160,   380,   249,     0,     0,     0,     0,   161,   162,
     163,   164,   165,   235,   166,   167,   168,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   257,     0,     0,   161,
     162,   163,   164,   165,     0,   166,   167,   168,     0,   149,
     150,   151,   152,   153,     0,   154,     0,   279,   155,   156,
       0,     0,     0,     0,     0,     0,   157,   158,   159,   160,
     149,   150,   151,   152,   153,     0,   154,     0,     0,   155,
     156,     0,     0,     0,     0,     0,     0,   157,   158,   159,
     160,     0,     0,     0,     0,     0,     0,   161,   162,   163,
     164,   165,     0,   166,   167,   168,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   364,     0,     0,   161,   162,
     163,   164,   165,     0,   166,   167,   168,   149,   150,   151,
     152,   153,     0,   154,     0,   190,   155,   156,     0,     0,
       0,     0,     0,     0,   157,   158,   159,   160,   149,   150,
     151,   152,   153,     0,   154,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,   157,   158,   159,   160,     0,
       0,     0,     0,     0,     0,   161,   162,   163,   164,   165,
       0,   166,   167,   168,     0,     0,     0,     0,     0,     0,
       0,     0,   203,     0,     0,     0,   161,   162,   163,   164,
     165,     0,   166,   167,   168,   149,   150,   151,   152,   153,
       0,   154,     0,   204,   155,   156,     0,     0,     0,     0,
       0,     0,   157,   158,   159,   160,   149,   150,   151,   152,
     153,     0,   154,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,   157,   158,   159,   160,     0,     0,     0,
       0,     0,     0,   161,   162,   163,   164,   165,     0,   166,
     167,   168,     0,     0,     0,     0,     0,     0,     0,     0,
     388,     0,     0,     0,   161,   162,   163,   164,   165,     0,
     166,   167,   168,   149,   150,   151,   152,   153,     0,   154,
       0,     0,   155,   156,     0,   149,   150,   151,   152,   153,
     157,   154,   159,   160,   155,   156,     0,   149,   150,   151,
     152,   153,   157,   154,   159,     0,   155,   156,   149,   150,
     151,   152,   153,     0,   154,     0,   159,   155,   156,     0,
       0,   161,   162,   163,   164,   165,     0,   166,   167,   168,
       0,     0,     0,   161,   162,   163,   164,   165,     0,   166,
     167,   168,     0,     0,     0,   161,   162,   163,   164,   165,
       0,   166,   167,   168,     0,     0,   161,   162,   163,   164,
     165,     0,   166,   167,   168,   149,   150,   151,   152,   153,
       0,   154,     0,     0,   155,   156,   149,   150,   151,   152,
     153,     0,   154,     0,     0,   155,   156,   149,   150,   151,
     152,   153,     0,   154,     0,     0,  -191,  -191,   149,   150,
     151,   152,   153,     0,   154,     0,     0,   155,   156,     0,
       0,     0,     0,     0,   162,   163,   164,   165,     0,   166,
     167,   168,     0,     0,     0,     0,   163,   164,   165,     0,
     166,   167,   168,     0,     0,     0,     0,     0,   164,   165,
       0,   166,   167,   168,     0,     0,     0,     0,     0,   164,
     165,     0,   166,   167,   168
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        21,    15,     4,     4,    25,     4,     4,     4,     4,     4,
       0,     5,    26,     5,     5,     4,     5,   343,    32,     5,
      22,    23,    65,   171,   172,     4,     5,   135,     5,     3,
       4,     5,     6,     7,     8,     5,    10,    11,    67,    14,
      15,    16,    17,    18,     8,    20,     4,     5,    22,     5,
      78,    25,    66,    67,     5,   381,     5,    71,    72,    73,
      74,     5,    73,    74,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    78,   285,    97,    51,    52,    53,
      54,    55,    68,    72,    54,    79,     3,    79,    79,    68,
      65,    66,    48,    68,    69,    70,    54,    61,    54,    73,
      74,    75,     5,    54,    78,    54,   316,    42,   122,   123,
      54,   113,   113,     5,   113,   113,   113,   113,   113,   267,
     134,    56,    57,   271,    41,    54,    59,   275,    22,    23,
       5,     6,     7,     8,    67,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,    48,   200,   201,   267,
     174,   144,    54,   271,    39,    40,     3,   275,     3,    58,
     184,   185,    47,    59,    61,     5,    45,    46,    74,    54,
      58,    58,   203,   204,    58,     4,    75,    73,   171,   172,
     211,    78,     3,     4,     5,     6,     7,     8,    67,    10,
      11,    79,    79,    59,    41,    79,    41,    59,    68,    69,
      70,    22,    77,   256,    25,   236,   259,    73,   239,    61,
      77,    73,    77,    77,    77,    67,   247,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    77,    77,    77,
      51,    52,    53,    54,    55,    73,    77,   268,   269,    73,
      78,   272,   273,    61,    78,   276,   277,   278,   279,    59,
      77,    61,    73,    74,    77,    77,    59,    78,    58,    78,
      59,    65,    66,    73,    68,    69,    70,   291,    78,    58,
     323,   324,    78,    78,     4,   328,     4,     5,     6,     7,
       8,    67,   313,    67,    50,     4,     5,     6,     7,     8,
      73,    58,    74,    80,    75,    49,    61,     8,    78,    78,
     331,   332,   333,   327,    79,    78,    78,    78,    67,    79,
      79,    39,    40,     5,    42,    79,    79,    45,    46,    47,
      39,    40,    61,    79,    79,    67,    54,     5,    47,    79,
      75,    77,    42,    67,   387,    54,   367,    65,    66,    79,
      78,    78,   366,    71,    72,    73,    74,    79,    79,     5,
      78,    13,    79,    79,    73,    74,    77,   388,     5,    78,
      14,    15,    16,    17,    18,    59,    20,    58,    58,    23,
      24,    59,    79,    79,    67,    79,    78,    31,    32,    33,
      34,    14,    15,    16,    17,    18,    12,    20,     2,    78,
      23,    24,    79,   287,   357,   286,   356,   346,    31,    32,
      33,    34,   358,   180,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,   170,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    62,
      63,    64,    65,    66,    -1,    68,    69,    70,    -1,    14,
      15,    16,    17,    18,    -1,    20,    -1,    80,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    68,    69,    70,    14,    15,    16,
      17,    18,    -1,    20,    -1,    79,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    -1,    68,    69,    70,    14,    15,    16,    17,    18,
      -1,    20,    -1,    79,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      68,    69,    70,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    -1,    14,    15,    16,    17,    18,
      31,    20,    33,    34,    23,    24,    -1,    14,    15,    16,
      17,    18,    31,    20,    33,    -1,    23,    24,    14,    15,
      16,    17,    18,    -1,    20,    -1,    33,    23,    24,    -1,
      -1,    62,    63,    64,    65,    66,    -1,    68,    69,    70,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    68,
      69,    70,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    68,    69,    70,    -1,    -1,    62,    63,    64,    65,
      66,    -1,    68,    69,    70,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,    68,
      69,    70,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    65,    66,
      -1,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    65,
      66,    -1,    68,    69,    70
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    82,    83,     0,    84,     3,     4,     5,     6,     7,
       8,    10,    11,    22,    25,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    51,    52,    53,    54,    55,
      73,    74,    78,    85,    86,    87,    88,    89,    90,    91,
      92,    94,    95,    97,   113,   115,   116,   121,   122,   124,
     127,   133,   138,   140,   142,   147,   148,   151,   153,   154,
     157,     5,   134,   135,    67,    78,    78,    78,     5,   139,
      42,    65,    66,    71,    72,    74,    87,    92,    93,    96,
     124,   127,   128,   129,   130,   131,   132,   138,   143,   148,
     151,    54,   136,   137,     4,     5,    72,     5,    74,    86,
       4,     5,    92,    94,    92,    86,    93,     4,    93,   144,
     145,     8,    61,    84,   114,    93,    77,    77,    77,    45,
      46,    67,    59,    73,    77,    77,    77,    77,    77,    77,
      61,    77,    77,    77,    59,    58,     5,    48,    54,   144,
      93,    93,    61,    67,    78,    93,    93,    93,    93,    14,
      15,    16,    17,    18,    20,    23,    24,    31,    32,    33,
      34,    62,    63,    64,    65,    66,    68,    69,    70,    59,
      58,    78,    78,     4,    73,    86,    67,    67,    50,   117,
     118,   119,    74,    80,    58,    61,    75,    75,    58,    75,
      79,     5,    54,    93,    93,     4,     5,    54,    93,   135,
      78,    78,    79,    79,    79,     4,     5,    68,     5,    68,
       5,    79,   134,   141,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,   137,    79,   134,   141,    79,
     134,   141,    78,    93,     5,     5,    78,    49,   120,   119,
      98,    99,   100,    93,    93,     8,    78,    80,    67,    78,
     144,   144,   152,    86,    86,    67,    86,    58,    79,    79,
      86,    58,    79,    79,    86,    58,    79,    79,    79,    80,
       5,    86,    56,    57,   110,   111,   112,   101,     3,    41,
     102,    61,   144,     5,    48,    54,   144,    79,    79,   146,
     158,    67,   141,    86,    86,   141,    86,    86,   141,    86,
      86,    86,    86,    79,    75,   142,   111,   102,   103,   104,
      77,    93,    79,    78,    78,    79,   126,    73,    78,   155,
      67,    79,    79,    79,    86,   142,    77,     5,   106,   107,
       5,   108,   109,   125,   144,   144,   149,   123,    93,   144,
      13,   159,    86,    86,    86,    59,    58,    59,    58,   123,
      79,    79,   146,    67,    80,    79,    78,    12,   156,     5,
       6,     7,     8,    39,    40,    47,    54,   105,   107,   105,
     109,   150,     5,    54,    93,    86,   123,    78,    79,   144,
      86,    79
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
     305,   306,   307,   308,   309,   310,   311,   312,    44,    61,
     313,    58,   124,    94,    38,    45,    43,    46,    42,    47,
      37,    33,   126,    91,   123,   125,   314,    59,    40,    41,
      93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    81,    83,    82,    84,    84,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    86,    87,    87,    88,
      89,    90,    90,    91,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    94,    94,    94,    95,    96,    96,    96,    96,    97,
      98,    98,   100,    99,   101,    99,   103,   102,   104,   102,
     105,   105,   105,   105,   105,   105,   105,   105,   106,   106,
     107,   107,   108,   108,   109,   110,   110,   111,   111,   111,
     112,   112,   113,   114,   114,   115,   115,   116,   117,   118,
     118,   119,   120,   120,   121,   122,   122,   122,   122,   123,
     123,   123,   123,   125,   124,   126,   124,   127,   127,   127,
     127,   128,   128,   128,   128,   128,   128,   129,   129,   130,
     130,   131,   131,   131,   131,   131,   132,   132,   132,   132,
     132,   133,   133,   134,   134,   135,   135,   136,   136,   137,
     138,   139,   139,   140,   140,   140,   140,   140,   141,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   143,   143,
     143,   143,   144,   144,   145,   145,   146,   146,   146,   147,
     147,   149,   148,   148,   148,   148,   148,   148,   150,   148,
     152,   151,   153,   153,   154,   155,   155,   156,   156,   158,
     159,   157
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     2,     1,     1,     1,     2,
       2,     2,     1,     1,     2,     2,     3,     3,     6,     1,
       1,     3,     6,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     2,     2,     2,     2,     6,
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
  "','", "'='", "XOR_EQUAL", "':'", "'|'", "'^'", "'&'", "'-'", "'+'",
  "'.'", "'*'", "'/'", "'%'", "'!'", "'~'", "'['", "'{'", "'}'", "UMINUS",
  "';'", "'('", "')'", "']'", "$accept", "program", "$@1",
  "statement_list", "statement", "block", "instantiation", "break",
  "continue", "thread_block", "critical_block", "object", "rvalue",
  "lvalue", "subscript", "unary", "class_def", "class_attr_decl",
  "class_attr_list", "@2", "@3", "non_empty_class_attr_list", "@4", "@5",
  "attr_rvalue", "class_attr_decl_list", "class_attr_decl_impl",
  "class_attr_const_decl_list", "class_attr_const_decl_impl",
  "class_method_decl", "visibility", "class_method_list", "array",
  "key_value_list", "map", "throw", "catch", "not_empty_catch",
  "catch_impl", "finally", "try_catch_finally", "property_access",
  "mcall_chain", "mcall", "@6", "@7", "inc_dec", "comparison", "boolean",
  "logic", "arithmetic", "bitwise", "variable_decl", "variable_decl_list",
  "variable_decl_impl", "const_decl_list", "const_decl_impl", "assignment",
  "import_ident_list", "import", "vararg", "fdecl", "anonymous_fdecl",
  "call_args", "non_empty_call_args", "fcall_chain",
  "fully_qualified_name", "fully_qualified_call", "@8", "@9", "fcall",
  "@10", "return_stmt", "while", "elseif", "else", "if", "@11", "@12", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        82,     0,    -1,    -1,    83,    84,    -1,    -1,    84,    85,
      -1,   140,    77,    -1,   133,    77,    -1,   138,    77,    -1,
     151,    77,    -1,   124,    77,    -1,   142,    -1,   153,    77,
      -1,   157,    -1,   154,    -1,   127,    77,    -1,    86,    -1,
      90,    -1,    91,    -1,   116,    77,    -1,    88,    77,    -1,
      89,    77,    -1,   121,    -1,    97,    -1,   148,    77,    -1,
      87,    77,    -1,    74,    84,    75,    -1,     4,    67,    48,
      -1,     4,    67,    48,    78,   144,    79,    -1,    22,    -1,
      53,    -1,    43,     5,    86,    -1,    43,     5,    73,    93,
      80,    86,    -1,    44,    86,    -1,     5,    -1,    54,    -1,
       8,    -1,     6,    -1,     7,    -1,    47,    -1,    39,    -1,
      40,    -1,   115,    -1,   113,    -1,    78,    93,    79,    -1,
      95,    -1,   122,    -1,   151,    -1,    92,    -1,    96,    -1,
     131,    -1,   130,    -1,   132,    -1,   129,    -1,   128,    -1,
     138,    -1,   127,    -1,   143,    -1,    87,    -1,   124,    -1,
     148,    -1,     5,    -1,   122,    -1,    95,    -1,    94,    73,
      93,    80,    -1,    65,    93,    -1,    66,    93,    -1,    71,
      93,    -1,    72,    93,    -1,    55,     4,    74,    98,   110,
      75,    -1,    -1,    99,    -1,    -1,   100,   102,    77,    -1,
      -1,    99,   101,   102,    77,    -1,    -1,     3,   103,   106,
      -1,    -1,    41,   104,   108,    -1,     5,    -1,    54,    -1,
       8,    -1,     6,    -1,     7,    -1,    47,    -1,    39,    -1,
      40,    -1,   107,    -1,   106,    58,   107,    -1,     5,    59,
     105,    -1,     5,    -1,   109,    -1,   108,    58,   109,    -1,
       5,    59,   105,    -1,    -1,   112,    -1,    -1,    56,    -1,
      57,    -1,   111,   142,    -1,   112,   111,   142,    -1,    73,
     144,    80,    -1,     8,    61,    93,    -1,   114,    58,     8,
      61,    93,    -1,    74,    61,    75,    -1,    74,   114,    75,
      -1,    52,    93,    -1,   118,    -1,   119,    -1,   118,   119,
      -1,    50,    78,     5,    79,    86,    -1,    -1,    49,    86,
      -1,    51,    86,   117,   120,    -1,    92,    67,     5,    -1,
       4,    67,     5,    -1,    92,    67,    54,    -1,     4,    67,
      54,    -1,    -1,   123,    67,     5,    78,   144,    79,    -1,
     123,    67,     5,    -1,   123,    67,    54,    -1,    -1,    92,
      67,     5,    78,   144,    79,   125,   123,    -1,    -1,     4,
      67,     5,    78,   144,    79,   126,   123,    -1,    92,    45,
      -1,    92,    46,    -1,    45,    92,    -1,    46,    92,    -1,
      93,    23,    93,    -1,    93,    24,    93,    -1,    93,    17,
      93,    -1,    93,    15,    93,    -1,    93,    16,    93,    -1,
      93,    14,    93,    -1,    93,    31,    93,    -1,    93,    33,
      93,    -1,    93,    32,    93,    -1,    93,    34,    93,    -1,
      93,    66,    93,    -1,    93,    65,    93,    -1,    93,    68,
      93,    -1,    93,    69,    93,    -1,    93,    70,    93,    -1,
      93,    64,    93,    -1,    93,    62,    93,    -1,    93,    63,
      93,    -1,    93,    20,    93,    -1,    93,    18,    93,    -1,
       3,   134,    -1,    41,   136,    -1,   135,    -1,   134,    58,
     135,    -1,     5,    59,    93,    -1,     5,    -1,   137,    -1,
     136,    58,   137,    -1,    54,    59,    93,    -1,    94,    59,
      93,    -1,     5,    -1,   139,    67,     5,    -1,    25,   139,
      67,    68,    -1,    25,   139,    61,    68,    -1,    25,   139,
      61,     5,    -1,    25,   139,    61,     4,    -1,    25,   139,
      -1,     5,    67,    67,    67,    -1,    42,     5,    78,    79,
      86,    -1,    42,     4,    78,    79,    86,    -1,    42,    72,
       4,    78,    79,    86,    -1,    42,     5,    78,   141,    79,
      86,    -1,    42,     4,    78,   141,    79,    86,    -1,    42,
       5,    78,   134,    79,    86,    -1,    42,     4,    78,   134,
      79,    86,    -1,    42,     5,    78,   134,    58,   141,    79,
      86,    -1,    42,     4,    78,   134,    58,   141,    79,    86,
      -1,    42,    78,    79,    86,    -1,    42,    78,   141,    79,
      86,    -1,    42,    78,   134,    79,    86,    -1,    42,    78,
     134,    58,   141,    79,    86,    -1,    -1,   145,    -1,    93,
      -1,   145,    58,    93,    -1,    -1,   146,    78,   144,    79,
      -1,   146,    73,    93,    80,    -1,     5,    -1,   147,    61,
       5,    -1,    -1,   147,    61,     5,    78,   144,    79,   149,
     146,    -1,   147,    61,    54,    -1,   147,    61,     5,    -1,
     147,    61,     4,    67,    54,    -1,   147,    61,     4,    67,
      48,    -1,   147,    61,     4,    67,    48,    78,   144,    79,
      -1,    -1,   147,    61,     4,    67,     5,    78,   144,    79,
     150,   123,    -1,    -1,     5,    78,   144,    79,   152,   146,
      -1,    38,    93,    -1,    38,    -1,    10,    78,    93,    79,
      86,    -1,    -1,   155,    13,    78,    93,    79,    86,    -1,
      -1,    12,    86,    -1,    -1,    -1,    11,    78,    93,    79,
      86,   158,   155,   159,   156,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     8,    11,    14,    17,    20,
      23,    26,    28,    31,    33,    35,    38,    40,    42,    44,
      47,    50,    53,    55,    57,    60,    63,    67,    71,    78,
      80,    82,    86,    93,    96,    98,   100,   102,   104,   106,
     108,   110,   112,   114,   116,   120,   122,   124,   126,   128,
     130,   132,   134,   136,   138,   140,   142,   144,   146,   148,
     150,   152,   154,   156,   158,   163,   166,   169,   172,   175,
     182,   183,   185,   186,   190,   191,   196,   197,   201,   202,
     206,   208,   210,   212,   214,   216,   218,   220,   222,   224,
     228,   232,   234,   236,   240,   244,   245,   247,   248,   250,
     252,   255,   259,   263,   267,   273,   277,   281,   284,   286,
     288,   291,   297,   298,   301,   306,   310,   314,   318,   322,
     323,   330,   334,   338,   339,   348,   349,   358,   361,   364,
     367,   370,   374,   378,   382,   386,   390,   394,   398,   402,
     406,   410,   414,   418,   422,   426,   430,   434,   438,   442,
     446,   450,   453,   456,   458,   462,   466,   468,   470,   474,
     478,   482,   484,   488,   493,   498,   503,   508,   511,   516,
     522,   528,   535,   542,   549,   556,   563,   572,   581,   586,
     592,   598,   606,   607,   609,   611,   615,   616,   621,   626,
     628,   632,   633,   642,   646,   650,   656,   662,   671,   672,
     683,   684,   691,   694,   696,   702,   703,   710,   711,   714,
     715,   716
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   214,   214,   214,   218,   219,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   246,   250,   251,   255,
     259,   263,   270,   280,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   323,   324,   325,   329,   333,   334,   335,   336,   340,
     344,   345,   349,   349,   350,   350,   354,   354,   355,   355,
     359,   360,   361,   362,   363,   364,   365,   366,   370,   371,
     375,   376,   380,   381,   385,   389,   390,   394,   395,   396,
     400,   401,   405,   409,   410,   414,   415,   419,   423,   427,
     428,   432,   436,   437,   441,   445,   446,   447,   448,   452,
     453,   454,   455,   459,   459,   460,   460,   464,   465,   466,
     467,   471,   472,   473,   474,   475,   476,   480,   481,   485,
     486,   490,   491,   492,   493,   494,   498,   499,   500,   501,
     502,   506,   507,   511,   512,   516,   517,   521,   522,   526,
     530,   534,   535,   539,   540,   541,   542,   543,   547,   551,
     553,   555,   557,   559,   561,   563,   565,   567,   572,   574,
     576,   578,   583,   584,   588,   589,   593,   594,   595,   599,
     600,   604,   604,   605,   606,   607,   608,   609,   610,   610,
     614,   614,   618,   619,   623,   627,   629,   634,   635,   639,
     640,   639
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
       2,     2,     2,    71,     2,     2,     2,    70,    64,     2,
      78,    79,    68,    66,    58,    65,    67,    69,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    77,
       2,    59,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    73,     2,    80,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    62,    75,    72,     2,     2,     2,
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
      55,    56,    57,    60,    76
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 864;
  const int Parser::yynnts_ = 79;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 3;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 81;

  const unsigned int Parser::yyuser_token_number_max_ = 314;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} // clever





namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever

