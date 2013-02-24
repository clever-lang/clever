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

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].fdecl)); }
    break;

  case 98:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].fdecl)); }
    break;

  case 99:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 100:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 101:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 102:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 103:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 104:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 106:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 107:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 108:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 109:

    { (yyval.block) = NULL; }
    break;

  case 110:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 111:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 112:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 113:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 114:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 115:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 116:

    { (yyval.mcall) = (yysemantic_stack_[(0) - (0)].mcall); }
    break;

  case 117:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (0)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 118:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 119:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); (yyval.property)->setStatic(); }
    break;

  case 120:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 121:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 122:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 123:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 124:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 125:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 126:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 127:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 128:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 129:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 130:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 131:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 132:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 133:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 134:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 135:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 136:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 137:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 138:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 139:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 140:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 141:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 142:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 143:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 144:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 145:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 146:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 147:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 148:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 149:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 150:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 151:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 152:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 153:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 154:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 155:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 156:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 157:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 158:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 159:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 160:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 161:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 162:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 163:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 164:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 165:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 166:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 167:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 168:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 169:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 170:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 171:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 172:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 173:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 174:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 175:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 176:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 177:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 178:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 179:

    { (yyval.narray) = NULL; }
    break;

  case 181:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 182:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 183:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 184:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 185:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 187:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 188:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 189:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 190:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 191:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 192:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 193:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 194:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 195:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 196:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 197:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 198:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 199:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 200:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 202:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 203:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 204:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 205:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 206:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 207:

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
  const short int Parser::yypact_ninf_ = -177;
  const short int
  Parser::yypact_[] =
  {
      -177,    50,  -177,  -177,   189,   101,   -10,   221,  -177,  -177,
    -177,    46,    52,  -177,   164,   279,  -177,  -177,   121,    12,
     173,   112,   306,   306,  -177,   112,   279,  -177,  -177,   208,
     279,    41,   279,  -177,  -177,   150,   170,   171,  -177,  -177,
     140,   105,   116,  -177,  -177,  -177,   174,  -177,   146,   175,
     178,   179,   184,   187,  -177,   162,   188,   191,   192,  -177,
    -177,   182,   212,  -177,    56,   279,   279,   279,  -177,   -19,
     193,   279,   279,   279,   279,    41,  -177,   140,   602,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,   207,   214,  -177,   195,   196,   269,    54,  -177,  -177,
     209,   -61,   217,   219,   217,   229,   602,   216,   602,   213,
     237,   235,   222,    26,   118,   450,  -177,  -177,  -177,  -177,
    -177,    30,   279,   279,  -177,  -177,  -177,  -177,  -177,  -177,
      34,  -177,  -177,  -177,   279,   101,   220,   223,  -177,   224,
     505,   526,    21,    23,     6,  -177,  -177,  -177,  -177,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     121,     8,     9,   226,   279,  -177,    49,    51,   227,   249,
     229,  -177,    60,  -177,   279,   279,  -177,  -177,   292,  -177,
    -177,   228,  -177,   669,   352,   240,   122,  -177,   602,  -177,
     279,   279,  -177,   112,   112,  -177,  -177,  -177,  -177,  -177,
      64,   112,    36,   238,    27,    27,    27,    27,   156,   156,
     769,   769,   681,   657,   692,   669,   747,   758,   780,   142,
     142,  -177,  -177,  -177,   602,  -177,   112,   100,   239,   112,
     124,   243,   245,   373,  -177,  -177,   312,   112,  -177,  -177,
     281,    93,   163,   602,   602,   268,   279,  -177,    14,   279,
     251,   252,  -177,  -177,  -177,   265,  -177,   326,   112,   112,
    -177,   326,   112,   112,  -177,   326,   112,   112,   112,   112,
     255,  -177,   261,   281,  -177,   163,  -177,  -177,   260,   279,
     259,   262,   264,   267,  -177,  -177,   131,  -177,   272,   275,
    -177,  -177,   277,  -177,  -177,   280,  -177,  -177,  -177,  -177,
     112,  -177,  -177,   283,   351,   354,  -177,   602,  -177,   279,
     279,  -177,  -177,   279,   279,   348,  -177,   112,   112,   112,
    -177,  -177,   307,   309,  -177,   314,   317,  -177,  -177,   286,
     297,  -177,   315,   429,   302,   305,   380,  -177,  -177,  -177,
     125,   351,   125,   354,   315,  -177,  -177,   131,    70,  -177,
    -177,   279,   112,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,   318,  -177,   581,
    -177,   315,   279,   112,   321,  -177,  -177
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    34,    37,    38,
      36,     0,     0,    29,     0,   199,    40,    41,     0,     0,
       0,     0,     0,     0,    39,     0,     0,    30,    35,     0,
     179,     4,     0,     5,    16,     0,     0,     0,    17,    18,
       0,     0,    45,    23,    43,    42,     0,    22,    46,     0,
       0,     0,     0,     0,    11,     0,     0,    47,     0,    14,
      13,   153,   148,   150,     0,   179,     0,     0,   158,   164,
       0,     0,     0,     0,     0,     0,    58,    48,   198,    49,
      59,    56,    54,    53,    51,    50,    52,    55,    57,    60,
      47,     0,   149,   154,     0,     0,     0,     0,     4,    33,
       0,    34,   126,     0,   127,     0,   104,     0,   181,     0,
     180,     0,     0,     0,     0,     0,    25,    20,    21,   124,
     125,     0,     0,     0,    19,    10,    15,     7,     8,     6,
       0,    24,     9,    12,     0,     0,   113,    27,   115,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,   109,
     105,   106,    70,    99,     0,     0,   102,    26,     0,   103,
      44,   112,   114,   157,     0,     0,   191,   190,   152,   151,
     179,   179,   196,     0,     0,   163,   162,   161,   159,   160,
     153,     0,     0,     0,   133,   131,   132,   130,   147,   146,
     128,   129,   134,   136,   135,   137,   144,   145,   143,   139,
     138,   140,   141,   142,   156,   155,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   112,     0,     0,   111,   107,
      95,    71,     0,   182,   100,     0,   179,    64,     0,   179,
       0,     0,   183,   200,   205,     0,   175,     0,     0,     0,
     167,     0,     0,     0,   166,     0,     0,     0,     0,     0,
       0,   110,     0,    96,    97,     0,    76,    78,     0,     0,
       0,     0,   192,     0,   122,    28,   197,   201,     0,     0,
     177,   176,     0,   172,   170,     0,   171,   169,   168,    32,
       0,    69,    98,     0,     0,     0,    73,   101,   120,   179,
     179,   188,   116,     0,   179,   206,   165,     0,     0,     0,
     108,    75,    91,    77,    88,     0,    79,    92,   116,     0,
       0,   183,   123,     0,     0,     0,   203,   178,   174,   173,
       0,     0,     0,     0,   121,   194,   193,   189,     0,   185,
     184,     0,     0,   207,    80,    83,    84,    82,    86,    87,
      85,    81,    90,    89,    94,    93,   116,   118,   119,     0,
     204,   195,   179,     0,     0,   202,   117
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -177,  -177,  -177,   393,  -177,   -21,    -1,  -177,  -177,  -177,
    -177,    -2,   -14,   215,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,   114,  -177,  -177,    48,  -177,    57,  -177,    58,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,   230,  -177,  -177,
    -177,  -170,     1,  -177,  -177,     2,  -177,  -177,  -177,  -177,
    -177,  -177,    17,  -108,  -177,   231,     3,  -177,  -177,  -148,
    -176,  -177,   -43,  -177,    61,  -177,     4,  -177,  -177,     5,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   113,    33,    34,    76,    36,    37,    38,
      39,    77,   108,    41,    42,    79,    43,   250,   251,   252,
     285,   288,   314,   315,   372,   333,   334,   336,   337,   282,
     283,    44,   114,    45,    46,   179,   180,   181,   248,    47,
      48,   342,    80,   338,   322,    81,    82,    83,    84,    85,
      86,    51,    62,    63,    92,    93,    87,    69,    53,   213,
      54,    88,   109,   110,   296,    55,    89,   341,   376,    90,
     262,    58,    59,   325,   363,    60,   297,   346
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -188;
  const short int
  Parser::yytable_[] =
  {
        99,    78,    40,    35,   105,    49,    50,    52,    56,    57,
     -61,   210,   106,   210,   210,    65,    94,    95,   115,   291,
     102,   104,   139,   238,   241,   205,   206,   199,   208,     5,
       6,     7,     8,     9,    10,   191,    11,    12,   195,   196,
     142,  -188,  -188,  -188,  -188,   153,   143,   154,    13,   111,
       3,    14,   140,   141,   244,    64,   245,   145,   146,   147,
     148,   136,   292,   -72,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,   284,   377,   175,    25,    26,    27,
      28,    29,    96,   211,   192,   236,   239,   207,   197,   209,
     164,   165,   267,   166,   167,   168,   -74,    30,    31,   187,
     112,   -72,    32,   138,   137,   192,    61,   312,   193,   194,
     138,    40,    35,   268,    49,    50,    52,    56,    57,   299,
     198,   134,    66,   302,   378,   174,    98,   305,    67,   265,
     364,   365,   366,   367,   -74,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   271,   260,   261,   199,
     243,   212,   122,   199,   368,   369,   286,   199,   354,    68,
     253,   254,   370,   -63,   188,    91,   123,   272,    97,   371,
     275,  -187,   263,   264,    98,   119,   120,   -63,   237,   240,
     266,   189,     5,     6,     7,     8,     9,    10,   259,    11,
      12,   276,   323,   -62,   287,   121,   381,   324,   166,   167,
     168,    13,   107,   290,    14,   270,   293,   -62,   274,   164,
     165,   130,   166,   167,   168,   116,   281,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   103,   103,   134,
      25,    26,    27,    28,    29,   117,   118,   300,   301,   124,
     125,   303,   304,   126,   127,   306,   307,   308,   309,   128,
      30,    31,   129,   131,   169,    32,   132,   133,   135,   144,
     170,   171,   172,   173,   176,   317,   339,   340,   -61,   178,
    -186,   344,   177,     6,     7,     8,     9,    10,   182,   330,
     123,   183,   -61,   184,   185,   186,   200,    65,   247,   201,
     255,   202,   242,   246,   256,   258,   347,   348,   349,   343,
     100,   101,     8,     9,    10,   269,   273,   280,    16,    17,
     277,    70,   278,    19,    22,    23,    24,   289,   294,   295,
     298,   210,   310,    28,   311,   316,   318,   326,   319,   384,
     320,   380,    71,    72,   321,    16,    17,   379,    73,    74,
      30,    75,   327,    24,   328,    32,   332,   329,   331,   335,
      28,   345,   385,   355,   350,   351,   149,   150,   151,   152,
     153,   352,   154,   353,   356,   155,   156,    30,    75,   360,
     358,   361,    32,   157,   158,   159,   160,   149,   150,   151,
     152,   153,   362,   154,   382,     4,   155,   156,   386,   313,
     374,   235,   357,     0,   157,   158,   159,   160,   373,     0,
     249,   375,   161,   162,   163,   164,   165,     0,   166,   167,
     168,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     257,     0,     0,   161,   162,   163,   164,   165,     0,   166,
     167,   168,     0,   149,   150,   151,   152,   153,     0,   154,
       0,   279,   155,   156,     0,     0,     0,     0,     0,     0,
     157,   158,   159,   160,   149,   150,   151,   152,   153,     0,
     154,     0,     0,   155,   156,     0,     0,     0,     0,     0,
       0,   157,   158,   159,   160,     0,     0,     0,     0,   161,
     162,   163,   164,   165,     0,   166,   167,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   359,     0,     0,
     161,   162,   163,   164,   165,     0,   166,   167,   168,   149,
     150,   151,   152,   153,     0,   154,     0,   190,   155,   156,
       0,     0,     0,     0,     0,     0,   157,   158,   159,   160,
     149,   150,   151,   152,   153,     0,   154,     0,     0,   155,
     156,     0,     0,     0,     0,     0,     0,   157,   158,   159,
     160,     0,     0,     0,     0,   161,   162,   163,   164,   165,
       0,   166,   167,   168,     0,     0,     0,     0,     0,     0,
       0,     0,   203,     0,     0,     0,   161,   162,   163,   164,
     165,     0,   166,   167,   168,   149,   150,   151,   152,   153,
       0,   154,     0,   204,   155,   156,     0,     0,     0,     0,
       0,     0,   157,   158,   159,   160,   149,   150,   151,   152,
     153,     0,   154,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,   157,   158,   159,   160,     0,     0,     0,
       0,   161,   162,   163,   164,   165,     0,   166,   167,   168,
       0,     0,     0,     0,     0,     0,     0,     0,   383,     0,
       0,     0,   161,   162,   163,   164,   165,     0,   166,   167,
     168,   149,   150,   151,   152,   153,     0,   154,     0,     0,
     155,   156,     0,   149,   150,   151,   152,   153,   157,   154,
     159,   160,   155,   156,     0,   149,   150,   151,   152,   153,
     157,   154,   159,     0,   155,   156,   149,   150,   151,   152,
     153,     0,   154,     0,   159,   155,   156,   161,   162,   163,
     164,   165,     0,   166,   167,   168,     0,     0,     0,   161,
     162,   163,   164,   165,     0,   166,   167,   168,     0,     0,
       0,   161,   162,   163,   164,   165,     0,   166,   167,   168,
       0,     0,   161,   162,   163,   164,   165,     0,   166,   167,
     168,   149,   150,   151,   152,   153,     0,   154,     0,     0,
     155,   156,   149,   150,   151,   152,   153,     0,   154,     0,
       0,   155,   156,   149,   150,   151,   152,   153,     0,   154,
       0,     0,  -188,  -188,   149,   150,   151,   152,   153,     0,
     154,     0,     0,   155,   156,     0,     0,     0,   162,   163,
     164,   165,     0,   166,   167,   168,     0,     0,     0,     0,
     163,   164,   165,     0,   166,   167,   168,     0,     0,     0,
       0,     0,   164,   165,     0,   166,   167,   168,     0,     0,
       0,     0,     0,   164,   165,     0,   166,   167,   168
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        21,    15,     4,     4,    25,     4,     4,     4,     4,     4,
      71,     5,    26,     5,     5,    76,     4,     5,    32,     5,
      22,    23,    65,   171,   172,     4,     5,   135,     5,     3,
       4,     5,     6,     7,     8,     5,    10,    11,     4,     5,
      59,    14,    15,    16,    17,    18,    65,    20,    22,     8,
       0,    25,    66,    67,     5,    65,     5,    71,    72,    73,
      74,     5,    48,     3,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,   250,     5,    97,    51,    52,    53,
      54,    55,    70,    77,    54,    77,    77,    66,    54,    66,
      63,    64,    56,    66,    67,    68,     3,    71,    72,    73,
      59,    41,    76,    54,    48,    54,     5,   283,   122,   123,
      54,   113,   113,    77,   113,   113,   113,   113,   113,   267,
     134,    57,    76,   271,    54,    71,    72,   275,    76,    65,
       5,     6,     7,     8,    41,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,    56,   200,   201,   267,
     174,   144,    57,   271,    39,    40,     3,   275,   338,     5,
     184,   185,    47,    57,    56,    54,    71,    77,     5,    54,
      56,    59,   203,   204,    72,    45,    46,    71,   171,   172,
     211,    73,     3,     4,     5,     6,     7,     8,    76,    10,
      11,    77,    71,    57,    41,    65,   376,    76,    66,    67,
      68,    22,     4,   256,    25,   236,   259,    71,   239,    63,
      64,    59,    66,    67,    68,    75,   247,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    22,    23,    57,
      51,    52,    53,    54,    55,    75,    75,   268,   269,    75,
      75,   272,   273,    75,    75,   276,   277,   278,   279,    75,
      71,    72,    75,    75,    57,    76,    75,    75,    56,    76,
      56,    76,    76,     4,    65,   289,   319,   320,    57,    50,
      59,   324,    65,     4,     5,     6,     7,     8,    72,   310,
      71,    78,    71,    56,    59,    73,    76,    76,    49,    76,
       8,    77,    76,    76,    76,    65,   327,   328,   329,   323,
       4,     5,     6,     7,     8,    77,    77,     5,    39,    40,
      77,    42,    77,    42,    45,    46,    47,    59,    77,    77,
      65,     5,    77,    54,    73,    75,    77,    65,    76,   382,
      76,   362,    63,    64,    77,    39,    40,   361,    69,    70,
      71,    72,    77,    47,    77,    76,     5,    77,    75,     5,
      54,    13,   383,    77,    57,    56,    14,    15,    16,    17,
      18,    57,    20,    56,    77,    23,    24,    71,    72,    77,
      65,    76,    76,    31,    32,    33,    34,    14,    15,    16,
      17,    18,    12,    20,    76,     2,    23,    24,    77,   285,
     352,   170,   341,    -1,    31,    32,    33,    34,   351,    -1,
     180,   353,    60,    61,    62,    63,    64,    -1,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    60,    61,    62,    63,    64,    -1,    66,
      67,    68,    -1,    14,    15,    16,    17,    18,    -1,    20,
      -1,    78,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    -1,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      60,    61,    62,    63,    64,    -1,    66,    67,    68,    14,
      15,    16,    17,    18,    -1,    20,    -1,    77,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      -1,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    -1,    66,    67,    68,    14,    15,    16,    17,    18,
      -1,    20,    -1,    77,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    -1,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    -1,    66,    67,
      68,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    -1,    14,    15,    16,    17,    18,    31,    20,
      33,    34,    23,    24,    -1,    14,    15,    16,    17,    18,
      31,    20,    33,    -1,    23,    24,    14,    15,    16,    17,
      18,    -1,    20,    -1,    33,    23,    24,    60,    61,    62,
      63,    64,    -1,    66,    67,    68,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    -1,    66,    67,    68,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    -1,    66,    67,    68,
      -1,    -1,    60,    61,    62,    63,    64,    -1,    66,    67,
      68,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    61,    62,
      63,    64,    -1,    66,    67,    68,    -1,    -1,    -1,    -1,
      62,    63,    64,    -1,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    63,    64,    -1,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    63,    64,    -1,    66,    67,    68
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    80,    81,     0,    82,     3,     4,     5,     6,     7,
       8,    10,    11,    22,    25,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    51,    52,    53,    54,    55,
      71,    72,    76,    83,    84,    85,    86,    87,    88,    89,
      90,    92,    93,    95,   110,   112,   113,   118,   119,   121,
     124,   130,   135,   137,   139,   144,   145,   148,   150,   151,
     154,     5,   131,   132,    65,    76,    76,    76,     5,   136,
      42,    63,    64,    69,    70,    72,    85,    90,    91,    94,
     121,   124,   125,   126,   127,   128,   129,   135,   140,   145,
     148,    54,   133,   134,     4,     5,    70,     5,    72,    84,
       4,     5,    90,    92,    90,    84,    91,     4,    91,   141,
     142,     8,    59,    82,   111,    91,    75,    75,    75,    45,
      46,    65,    57,    71,    75,    75,    75,    75,    75,    75,
      59,    75,    75,    75,    57,    56,     5,    48,    54,   141,
      91,    91,    59,    65,    76,    91,    91,    91,    91,    14,
      15,    16,    17,    18,    20,    23,    24,    31,    32,    33,
      34,    60,    61,    62,    63,    64,    66,    67,    68,    57,
      56,    76,    76,     4,    71,    84,    65,    65,    50,   114,
     115,   116,    72,    78,    56,    59,    73,    73,    56,    73,
      77,     5,    54,    91,    91,     4,     5,    54,    91,   132,
      76,    76,    77,    77,    77,     4,     5,    66,     5,    66,
       5,    77,   131,   138,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,   134,    77,   131,   138,    77,
     131,   138,    76,    91,     5,     5,    76,    49,   117,   116,
      96,    97,    98,    91,    91,     8,    76,    78,    65,    76,
     141,   141,   149,    84,    84,    65,    84,    56,    77,    77,
      84,    56,    77,    77,    84,    56,    77,    77,    77,    78,
       5,    84,   108,   109,   139,    99,     3,    41,   100,    59,
     141,     5,    48,   141,    77,    77,   143,   155,    65,   138,
      84,    84,   138,    84,    84,   138,    84,    84,    84,    84,
      77,    73,   139,   100,   101,   102,    75,    91,    77,    76,
      76,    77,   123,    71,    76,   152,    65,    77,    77,    77,
      84,    75,     5,   104,   105,     5,   106,   107,   122,   141,
     141,   146,   120,    91,   141,    13,   156,    84,    84,    84,
      57,    56,    57,    56,   120,    77,    77,   143,    65,    78,
      77,    76,    12,   153,     5,     6,     7,     8,    39,    40,
      47,    54,   103,   105,   103,   107,   147,     5,    54,    91,
      84,   120,    76,    77,   141,    84,    77
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
     305,   306,   307,   308,   309,   310,    44,    61,   311,    58,
     124,    94,    38,    45,    43,    46,    42,    47,    37,    33,
     126,    91,   123,   125,   312,    59,    40,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    79,    81,    80,    82,    82,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    84,    85,    85,    86,
      87,    88,    88,    89,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    92,    92,    92,    93,    94,    94,    94,    94,    95,
      96,    96,    98,    97,    99,    97,   101,   100,   102,   100,
     103,   103,   103,   103,   103,   103,   103,   103,   104,   104,
     105,   105,   106,   106,   107,   108,   108,   109,   109,   110,
     111,   111,   112,   112,   113,   114,   115,   115,   116,   117,
     117,   118,   119,   119,   119,   119,   120,   120,   120,   120,
     122,   121,   123,   121,   124,   124,   124,   124,   125,   125,
     125,   125,   125,   125,   126,   126,   127,   127,   128,   128,
     128,   128,   128,   129,   129,   129,   129,   129,   130,   130,
     131,   131,   132,   132,   133,   133,   134,   135,   136,   136,
     137,   137,   137,   137,   137,   138,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   140,   140,   140,   140,   141,
     141,   142,   142,   143,   143,   143,   144,   144,   146,   145,
     145,   145,   145,   145,   147,   145,   149,   148,   150,   150,
     151,   152,   152,   153,   153,   155,   156,   154
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
       3,     1,     1,     3,     3,     0,     1,     1,     2,     3,
       3,     5,     3,     3,     2,     1,     1,     2,     5,     0,
       2,     4,     3,     3,     3,     3,     0,     6,     3,     3,
       0,     8,     0,     8,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     3,     3,     1,     1,     3,     3,     3,     1,     3,
       4,     4,     4,     4,     2,     4,     5,     5,     6,     6,
       6,     6,     6,     8,     8,     4,     5,     5,     7,     0,
       1,     1,     3,     0,     4,     4,     1,     3,     0,     8,
       3,     3,     5,     8,     0,    10,     0,     6,     2,     1,
       5,     0,     6,     0,     2,     0,     0,     9
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
  "\"constant identifier\"", "\"class\"", "','", "'='", "XOR_EQUAL", "':'",
  "'|'", "'^'", "'&'", "'-'", "'+'", "'.'", "'*'", "'/'", "'%'", "'!'",
  "'~'", "'['", "'{'", "'}'", "UMINUS", "';'", "'('", "')'", "']'",
  "$accept", "program", "$@1", "statement_list", "statement", "block",
  "instantiation", "break", "continue", "thread_block", "critical_block",
  "object", "rvalue", "lvalue", "subscript", "unary", "class_def",
  "class_attr_decl", "class_attr_list", "@2", "@3",
  "non_empty_class_attr_list", "@4", "@5", "attr_rvalue",
  "class_attr_decl_list", "class_attr_decl_impl",
  "class_attr_const_decl_list", "class_attr_const_decl_impl",
  "class_method_decl", "class_method_list", "array", "key_value_list",
  "map", "throw", "catch", "not_empty_catch", "catch_impl", "finally",
  "try_catch_finally", "property_access", "mcall_chain", "mcall", "@6",
  "@7", "inc_dec", "comparison", "boolean", "logic", "arithmetic",
  "bitwise", "variable_decl", "variable_decl_list", "variable_decl_impl",
  "const_decl_list", "const_decl_impl", "assignment", "import_ident_list",
  "import", "vararg", "fdecl", "anonymous_fdecl", "call_args",
  "non_empty_call_args", "fcall_chain", "fully_qualified_name",
  "fully_qualified_call", "@8", "@9", "fcall", "@10", "return_stmt",
  "while", "elseif", "else", "if", "@11", "@12", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        80,     0,    -1,    -1,    81,    82,    -1,    -1,    82,    83,
      -1,   137,    75,    -1,   130,    75,    -1,   135,    75,    -1,
     148,    75,    -1,   121,    75,    -1,   139,    -1,   150,    75,
      -1,   154,    -1,   151,    -1,   124,    75,    -1,    84,    -1,
      88,    -1,    89,    -1,   113,    75,    -1,    86,    75,    -1,
      87,    75,    -1,   118,    -1,    95,    -1,   145,    75,    -1,
      85,    75,    -1,    72,    82,    73,    -1,     4,    65,    48,
      -1,     4,    65,    48,    76,   141,    77,    -1,    22,    -1,
      53,    -1,    43,     5,    84,    -1,    43,     5,    71,    91,
      78,    84,    -1,    44,    84,    -1,     5,    -1,    54,    -1,
       8,    -1,     6,    -1,     7,    -1,    47,    -1,    39,    -1,
      40,    -1,   112,    -1,   110,    -1,    76,    91,    77,    -1,
      93,    -1,   119,    -1,   148,    -1,    90,    -1,    94,    -1,
     128,    -1,   127,    -1,   129,    -1,   126,    -1,   125,    -1,
     135,    -1,   124,    -1,   140,    -1,    85,    -1,   121,    -1,
     145,    -1,     5,    -1,   119,    -1,    93,    -1,    92,    71,
      91,    78,    -1,    63,    91,    -1,    64,    91,    -1,    69,
      91,    -1,    70,    91,    -1,    55,     4,    72,    96,   108,
      73,    -1,    -1,    97,    -1,    -1,    98,   100,    75,    -1,
      -1,    97,    99,   100,    75,    -1,    -1,     3,   101,   104,
      -1,    -1,    41,   102,   106,    -1,     5,    -1,    54,    -1,
       8,    -1,     6,    -1,     7,    -1,    47,    -1,    39,    -1,
      40,    -1,   105,    -1,   104,    56,   105,    -1,     5,    57,
     103,    -1,     5,    -1,   107,    -1,   106,    56,   107,    -1,
       5,    57,   103,    -1,    -1,   109,    -1,   139,    -1,   109,
     139,    -1,    71,   141,    78,    -1,     8,    59,    91,    -1,
     111,    56,     8,    59,    91,    -1,    72,    59,    73,    -1,
      72,   111,    73,    -1,    52,    91,    -1,   115,    -1,   116,
      -1,   115,   116,    -1,    50,    76,     5,    77,    84,    -1,
      -1,    49,    84,    -1,    51,    84,   114,   117,    -1,    90,
      65,     5,    -1,     4,    65,     5,    -1,    90,    65,    54,
      -1,     4,    65,    54,    -1,    -1,   120,    65,     5,    76,
     141,    77,    -1,   120,    65,     5,    -1,   120,    65,    54,
      -1,    -1,    90,    65,     5,    76,   141,    77,   122,   120,
      -1,    -1,     4,    65,     5,    76,   141,    77,   123,   120,
      -1,    90,    45,    -1,    90,    46,    -1,    45,    90,    -1,
      46,    90,    -1,    91,    23,    91,    -1,    91,    24,    91,
      -1,    91,    17,    91,    -1,    91,    15,    91,    -1,    91,
      16,    91,    -1,    91,    14,    91,    -1,    91,    31,    91,
      -1,    91,    33,    91,    -1,    91,    32,    91,    -1,    91,
      34,    91,    -1,    91,    64,    91,    -1,    91,    63,    91,
      -1,    91,    66,    91,    -1,    91,    67,    91,    -1,    91,
      68,    91,    -1,    91,    62,    91,    -1,    91,    60,    91,
      -1,    91,    61,    91,    -1,    91,    20,    91,    -1,    91,
      18,    91,    -1,     3,   131,    -1,    41,   133,    -1,   132,
      -1,   131,    56,   132,    -1,     5,    57,    91,    -1,     5,
      -1,   134,    -1,   133,    56,   134,    -1,    54,    57,    91,
      -1,    92,    57,    91,    -1,     5,    -1,   136,    65,     5,
      -1,    25,   136,    65,    66,    -1,    25,   136,    59,    66,
      -1,    25,   136,    59,     5,    -1,    25,   136,    59,     4,
      -1,    25,   136,    -1,     5,    65,    65,    65,    -1,    42,
       5,    76,    77,    84,    -1,    42,     4,    76,    77,    84,
      -1,    42,    70,     4,    76,    77,    84,    -1,    42,     5,
      76,   138,    77,    84,    -1,    42,     4,    76,   138,    77,
      84,    -1,    42,     5,    76,   131,    77,    84,    -1,    42,
       4,    76,   131,    77,    84,    -1,    42,     5,    76,   131,
      56,   138,    77,    84,    -1,    42,     4,    76,   131,    56,
     138,    77,    84,    -1,    42,    76,    77,    84,    -1,    42,
      76,   138,    77,    84,    -1,    42,    76,   131,    77,    84,
      -1,    42,    76,   131,    56,   138,    77,    84,    -1,    -1,
     142,    -1,    91,    -1,   142,    56,    91,    -1,    -1,   143,
      76,   141,    77,    -1,   143,    71,    91,    78,    -1,     5,
      -1,   144,    59,     5,    -1,    -1,   144,    59,     5,    76,
     141,    77,   146,   143,    -1,   144,    59,    54,    -1,   144,
      59,     5,    -1,   144,    59,     4,    65,    48,    -1,   144,
      59,     4,    65,    48,    76,   141,    77,    -1,    -1,   144,
      59,     4,    65,     5,    76,   141,    77,   147,   120,    -1,
      -1,     5,    76,   141,    77,   149,   143,    -1,    38,    91,
      -1,    38,    -1,    10,    76,    91,    77,    84,    -1,    -1,
     152,    13,    76,    91,    77,    84,    -1,    -1,    12,    84,
      -1,    -1,    -1,    11,    76,    91,    77,    84,   155,   152,
     156,   153,    -1
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
     228,   232,   234,   236,   240,   244,   245,   247,   249,   252,
     256,   260,   266,   270,   274,   277,   279,   281,   284,   290,
     291,   294,   299,   303,   307,   311,   315,   316,   323,   327,
     331,   332,   341,   342,   351,   354,   357,   360,   363,   367,
     371,   375,   379,   383,   387,   391,   395,   399,   403,   407,
     411,   415,   419,   423,   427,   431,   435,   439,   443,   446,
     449,   451,   455,   459,   461,   463,   467,   471,   475,   477,
     481,   486,   491,   496,   501,   504,   509,   515,   521,   528,
     535,   542,   549,   556,   565,   574,   579,   585,   591,   599,
     600,   602,   604,   608,   609,   614,   619,   621,   625,   626,
     635,   639,   643,   649,   658,   659,   670,   671,   678,   681,
     683,   689,   690,   697,   698,   701,   702,   703
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   210,   210,   210,   214,   215,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   242,   246,   247,   251,
     255,   259,   266,   276,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   319,   320,   321,   325,   329,   330,   331,   332,   336,
     340,   341,   345,   345,   346,   346,   350,   350,   351,   351,
     355,   356,   357,   358,   359,   360,   361,   362,   366,   367,
     371,   372,   376,   377,   381,   385,   386,   390,   391,   395,
     399,   400,   404,   405,   409,   413,   417,   418,   422,   426,
     427,   431,   435,   436,   437,   438,   442,   443,   444,   445,
     449,   449,   450,   450,   454,   455,   456,   457,   461,   462,
     463,   464,   465,   466,   470,   471,   475,   476,   480,   481,
     482,   483,   484,   488,   489,   490,   491,   492,   496,   497,
     501,   502,   506,   507,   511,   512,   516,   520,   524,   525,
     529,   530,   531,   532,   533,   537,   541,   543,   545,   547,
     549,   551,   553,   555,   557,   562,   564,   566,   568,   573,
     574,   578,   579,   583,   584,   585,   589,   590,   594,   594,
     595,   596,   597,   598,   599,   599,   603,   603,   607,   608,
     612,   616,   618,   623,   624,   628,   629,   628
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
       2,     2,     2,    69,     2,     2,     2,    68,    62,     2,
      76,    77,    66,    64,    56,    63,    65,    67,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    75,
       2,    57,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    71,     2,    78,    61,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,    60,    73,    70,     2,     2,     2,
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
      55,    58,    74
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 848;
  const int Parser::yynnts_ = 78;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 3;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 79;

  const unsigned int Parser::yyuser_token_number_max_ = 312;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} // clever





namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever

