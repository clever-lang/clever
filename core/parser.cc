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

  case 24:

    { (yyval.block) = (yysemantic_stack_[(3) - (2)].block); }
    break;

  case 25:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(3) - (1)].type), NULL, yyloc); }
    break;

  case 26:

    { (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (5)].narray),   yyloc); }
    break;

  case 27:

    { (yyval.break_) = new ast::Break(yyloc); }
    break;

  case 28:

    { (yyval.continue_) = new ast::Continue(yyloc); }
    break;

  case 29:

    {
#ifndef CLEVER_THREADS
		error(yyloc, "Cannot use process block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(3) - (3)].block), (yysemantic_stack_[(3) - (2)].ident), yyloc);
#endif
	}
    break;

  case 30:

    {
#ifndef CLEVER_THREADS
		error(yyloc, "Cannot use process block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].node), yyloc);
#endif
	}
    break;

  case 31:

    {
#ifndef CLEVER_THREADS
		error(yyloc, "Cannot use critical block syntax, threads is disabled!"); YYABORT;
#else
		(yyval.criticalblock) = new ast::CriticalBlock((yysemantic_stack_[(2) - (2)].block), yyloc);
#endif
	}
    break;

  case 42:

    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 58:

    { (yysemantic_stack_[(1) - (1)].property)->setWriteMode(); }
    break;

  case 60:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 61:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 62:

    { (yyval.node) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, new ast::IntLit(0, yyloc), (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 63:

    { (yyval.node) = new ast::Boolean(ast::Boolean::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 64:

    { (yyval.node) = new ast::Bitwise(ast::Bitwise::BOP_NOT, (yysemantic_stack_[(2) - (2)].node), yyloc);                                  }
    break;

  case 65:

    { (yyval.class_) = new ast::ClassDef((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 66:

    { (yyval.narray) = NULL; }
    break;

  case 68:

    { (yyval.narray) = new ast::NodeArray(yyloc); }
    break;

  case 69:

    { (yyval.narray) = (yysemantic_stack_[(3) - (1)].narray); }
    break;

  case 70:

    { (yyval.narray) = (yysemantic_stack_[(1) - (1)].narray); }
    break;

  case 72:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 74:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 84:

    { (yysemantic_stack_[(1) - (0)].narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 85:

    { (yysemantic_stack_[(3) - (0)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 86:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), false, yyloc); }
    break;

  case 87:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(1) - (1)].ident), NULL, false, yyloc);     }
    break;

  case 88:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 89:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 90:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), true, yyloc);   }
    break;

  case 91:

    { (yyval.narray) = NULL; }
    break;

  case 93:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].fdecl)); }
    break;

  case 94:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].fdecl)); }
    break;

  case 95:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 96:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 97:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 98:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 99:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 100:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 102:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 103:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 104:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 105:

    { (yyval.block) = NULL; }
    break;

  case 106:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 107:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 108:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 109:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 110:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 111:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 112:

    { (yyval.mcall) = (yysemantic_stack_[(0) - (0)].mcall); }
    break;

  case 113:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (0)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 114:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 115:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); (yyval.property)->setStatic(); }
    break;

  case 116:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 117:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 118:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 119:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 120:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 121:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 122:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 123:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 124:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 125:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 126:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 127:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 128:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 129:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 130:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 131:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 132:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 133:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 134:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 135:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 136:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 137:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 138:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 139:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 140:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 141:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 142:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 143:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 144:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 145:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 146:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 147:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 148:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 149:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 150:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 151:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 152:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 153:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 154:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 155:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 156:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 157:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 158:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 159:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 160:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 161:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 162:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 163:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); }
    break;

  case 164:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 165:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); }
    break;

  case 166:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 167:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); }
    break;

  case 168:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 169:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); }
    break;

  case 170:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 171:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 172:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 173:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 174:

    { (yyval.narray) = NULL; }
    break;

  case 176:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 177:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 178:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 179:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 181:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 182:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 183:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 184:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 185:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 186:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 188:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 189:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 190:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 191:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 192:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 193:

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
  const short int Parser::yypact_ninf_ = -200;
  const short int
  Parser::yypact_[] =
  {
      -200,    10,  -200,  -200,   327,    20,   -29,    98,  -200,  -200,
    -200,    -7,    17,  -200,    75,   350,  -200,  -200,    44,   117,
      77,   -11,   175,   175,  -200,   -11,   350,  -200,  -200,   103,
     350,    16,   350,  -200,  -200,    42,    50,  -200,  -200,    54,
      31,  -200,  -200,  -200,  -200,    52,  -200,  -200,    53,    81,
      91,    92,   110,  -200,    47,   111,   112,  -200,  -200,   121,
      96,  -200,    23,   350,   350,  -200,    61,   119,   113,   350,
     350,   350,   350,    16,  -200,    54,   642,   122,   123,  -200,
     124,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
     131,   134,  -200,   116,   120,    88,  -200,  -200,  -200,  -200,
    -200,   147,   642,   126,   642,   125,   143,   141,   128,   249,
      95,   490,  -200,  -200,  -200,  -200,    29,   350,   350,  -200,
    -200,  -200,  -200,  -200,  -200,   197,   350,  -200,  -200,   350,
      20,   129,  -200,   511,   566,    15,    18,    22,     8,  -200,
    -200,  -200,  -200,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,    44,     9,    12,   350,  -200,   130,
     159,   147,  -200,    32,  -200,   350,   350,  -200,  -200,   201,
    -200,  -200,   135,  -200,   642,   413,  -200,   133,   642,  -200,
     350,   -11,   -11,  -200,  -200,  -200,  -200,  -200,   137,     6,
     -11,   -17,   139,   296,   296,   296,   296,   109,   109,   785,
     785,   730,   663,   698,   718,   753,    28,   808,    97,    97,
    -200,  -200,  -200,   642,  -200,   -11,   -15,   140,   -11,    -9,
     142,   434,   213,   -11,  -200,  -200,   178,    37,    56,   642,
     642,   162,   350,  -200,  -200,   146,  -200,  -200,   350,   161,
    -200,   219,   -11,   -11,  -200,   219,   -11,   -11,  -200,   219,
     -11,   -11,   -11,   150,  -200,   155,   178,  -200,    56,  -200,
    -200,   158,   350,   153,  -200,  -200,  -200,   157,   172,   165,
    -200,  -200,   166,  -200,  -200,   167,  -200,  -200,  -200,   -11,
    -200,  -200,   163,   240,   243,  -200,   642,  -200,   173,  -200,
     237,  -200,  -200,   -11,   -11,   -11,  -200,  -200,   204,   206,
    -200,   207,   209,  -200,  -200,   350,   198,   190,   255,  -200,
    -200,  -200,    25,   240,    25,   243,   198,   192,    33,   350,
     -11,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,   194,  -200,   587,  -200,   350,
     -11,   195,  -200,  -200
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    32,    35,    36,
      34,     0,     0,    27,     0,   185,    38,    39,     0,     0,
       0,     0,     0,     0,    37,     0,     0,    28,    33,     0,
     174,     4,     0,     5,    16,     0,     0,    17,    18,     0,
       0,    59,    23,    41,    40,     0,    22,    58,     0,     0,
       0,     0,     0,    11,     0,     0,     0,    14,    13,   149,
     144,   146,     0,     0,     0,   154,   160,     0,     0,     0,
       0,     0,     0,     0,    53,    43,   184,     0,    56,    44,
      54,    55,    50,    49,    48,    46,    45,    47,    52,    51,
       0,   145,   150,     0,     0,     0,     4,    31,    32,   122,
     123,     0,   100,     0,   176,     0,   175,     0,     0,     0,
       0,     0,    20,    21,   120,   121,     0,     0,     0,    19,
      10,    15,     7,     8,     6,     0,   174,     9,    12,     0,
       0,   109,   111,     0,     0,     0,     0,     0,     0,    61,
      62,    63,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
     105,   101,   102,    66,    95,     0,     0,    98,    24,     0,
      99,    42,   108,   110,   153,     0,   181,     0,   148,   147,
     174,     0,     0,   159,   158,   157,   155,   156,    25,   149,
       0,     0,     0,   129,   127,   128,   126,   143,   142,   124,
     125,   130,   132,   131,   133,   140,   141,   139,   135,   134,
     136,   137,   138,   152,   151,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   107,   103,    91,    67,     0,   177,
      96,     0,   174,    60,   182,     0,   186,   191,   174,     0,
     170,     0,     0,     0,   163,     0,     0,     0,   162,     0,
       0,     0,     0,     0,   106,     0,    92,    93,     0,    72,
      74,     0,     0,     0,   178,   118,   187,     0,     0,     0,
     172,   171,     0,   167,   165,     0,   166,   164,    30,     0,
      65,    94,     0,     0,     0,    69,    97,   116,   183,   112,
     192,    26,   161,     0,     0,     0,   104,    71,    87,    73,
      84,     0,    75,    88,   112,   174,   119,     0,   189,   173,
     169,   168,     0,     0,     0,     0,   117,     0,     0,     0,
       0,   193,    76,    79,    80,    78,    82,    83,    81,    77,
      86,    85,    90,    89,   179,   114,   115,     0,   190,   174,
       0,     0,   188,   113
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -200,  -200,  -200,   271,  -200,   -21,  -200,  -200,  -200,  -200,
    -200,    -1,   -14,     1,     2,  -200,  -200,  -200,  -200,  -200,
    -200,    11,  -200,  -200,   -49,  -200,   -47,  -200,   -48,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,   107,  -200,  -200,
       3,   -34,     4,  -200,  -200,     5,  -200,  -200,  -200,  -200,
    -200,  -200,  -112,  -101,  -200,   144,  -200,  -200,  -200,  -150,
    -199,  -200,  -124,  -200,  -200,  -200,     7,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   109,    33,    34,    74,    35,    36,    37,
      38,    75,   104,    77,    78,    79,    42,   236,   237,   238,
     268,   271,   293,   294,   340,   309,   310,   312,   313,   265,
     266,    43,   110,    44,    45,   170,   171,   172,   234,    46,
      80,   316,    81,   314,   299,    82,    83,    84,    85,    86,
      87,    50,    60,    61,    91,    92,    51,    66,    52,   202,
      53,    88,   105,   106,   298,    54,    89,   274,    56,    57,
     300,   331,    58,   276,   318
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -181;
  const short int
  Parser::yytable_[] =
  {
        97,    76,   187,    39,   101,    40,    41,    47,    48,    49,
       3,    55,   102,   199,   199,   227,   230,   199,   111,   193,
     194,    99,   100,   196,   107,    59,   201,   131,   131,   189,
     332,   333,   334,   335,   182,   -68,    62,   267,   345,   251,
     -70,   255,   143,   144,   145,   146,   147,   259,   148,   133,
     134,   149,   150,   226,   229,   139,   140,   141,   142,   269,
     252,    96,   256,   129,   336,   337,   245,   291,   260,    63,
     198,   249,   338,   -68,   168,   108,   132,   132,   -70,   339,
      65,   195,    95,   183,   197,   200,   225,   346,   117,   228,
     157,   158,   159,    64,   160,   161,   162,   270,    90,   114,
     115,   279,   118,   184,   185,   282,   125,   103,    39,   285,
      40,    41,    47,    48,    49,   188,    55,   112,   273,   116,
     135,    93,    94,   126,   277,   113,   136,   119,   120,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     189,   179,   130,   231,   189,   -57,   121,  -180,   189,   167,
      96,   239,   240,   160,   161,   162,   122,   123,   180,   -57,
     246,   247,   158,   159,  -180,   160,   161,   162,   129,   250,
      98,     8,     9,    10,   137,   124,   127,   128,   163,   138,
     164,   327,   165,   118,   -59,   -58,   166,   169,   173,   175,
     176,   177,   186,   174,   254,   190,   232,   258,   233,   241,
     244,   242,   264,   248,    16,    17,   253,   257,   263,   261,
      19,   272,    24,   275,   199,   351,   278,   289,   290,    28,
     297,   280,   281,   295,   301,   283,   284,   302,   307,   286,
     287,   288,   303,   304,   305,   308,    30,    73,   311,   315,
     317,    32,     5,     6,     7,     8,     9,    10,   296,    11,
      12,   322,   323,   328,   324,   325,   329,   330,   306,   344,
     349,    13,   353,     4,    14,   342,   341,   343,   235,   292,
     326,     0,   319,   320,   321,     0,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,     0,     0,
      25,    26,    27,    28,    29,     0,     0,     0,   224,   348,
    -181,  -181,  -181,  -181,   147,   347,   148,     0,     0,     0,
      30,    31,   178,     0,     0,    32,     0,     0,     0,   352,
       5,     6,     7,     8,     9,    10,     0,    11,    12,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     0,    14,     0,    67,     7,     8,     9,    10,   158,
     159,     0,   160,   161,   162,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     0,     0,     0,    25,    26,
      27,    28,    29,     0,     0,     0,     0,     0,     0,    16,
      17,     0,    68,     0,     0,    22,    23,    24,    30,    31,
       0,     0,     0,    32,    28,     0,     0,     0,     0,     0,
       0,     0,     0,    69,    70,     0,     0,     0,     0,    71,
      72,    30,    73,     0,     0,     0,    32,   143,   144,   145,
     146,   147,     0,   148,     0,     0,   149,   150,     0,     0,
       0,     0,     0,     0,   151,   152,   153,   154,   143,   144,
     145,   146,   147,     0,   148,     0,     0,   149,   150,     0,
       0,     0,     0,     0,     0,   151,   152,   153,   154,     0,
       0,     0,     0,   155,   156,   157,   158,   159,     0,   160,
     161,   162,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   243,     0,     0,   155,   156,   157,   158,   159,     0,
     160,   161,   162,     0,   143,   144,   145,   146,   147,     0,
     148,     0,   262,   149,   150,     0,     0,     0,     0,     0,
       0,   151,   152,   153,   154,   143,   144,   145,   146,   147,
       0,   148,     0,     0,   149,   150,     0,     0,     0,     0,
       0,     0,   151,   152,   153,   154,     0,     0,     0,     0,
     155,   156,   157,   158,   159,     0,   160,   161,   162,     0,
       0,     0,     0,     0,     0,     0,     0,   181,     0,     0,
       0,   155,   156,   157,   158,   159,     0,   160,   161,   162,
     143,   144,   145,   146,   147,     0,   148,     0,   191,   149,
     150,     0,     0,     0,     0,     0,     0,   151,   152,   153,
     154,   143,   144,   145,   146,   147,     0,   148,     0,     0,
     149,   150,     0,     0,     0,     0,     0,     0,   151,   152,
     153,   154,     0,     0,     0,     0,   155,   156,   157,   158,
     159,     0,   160,   161,   162,     0,     0,     0,     0,     0,
       0,     0,     0,   192,     0,     0,     0,   155,   156,   157,
     158,   159,     0,   160,   161,   162,   143,   144,   145,   146,
     147,     0,   148,     0,   350,   149,   150,     0,     0,     0,
       0,     0,     0,   151,   152,   153,   154,   143,   144,   145,
     146,   147,     0,   148,     0,     0,   149,   150,     0,     0,
       0,     0,     0,     0,   151,     0,   153,   154,     0,     0,
       0,     0,   155,   156,   157,   158,   159,     0,   160,   161,
     162,     0,   143,   144,   145,   146,   147,     0,   148,     0,
       0,   149,   150,   155,   156,   157,   158,   159,     0,   160,
     161,   162,   143,   144,   145,   146,   147,     0,   148,     0,
       0,   149,   150,     0,   143,   144,   145,   146,   147,   151,
     148,   153,     0,   149,   150,     0,     0,     0,   155,   156,
     157,   158,   159,   153,   160,   161,   162,   143,   144,   145,
     146,   147,     0,   148,     0,     0,   149,   150,   155,   156,
     157,   158,   159,     0,   160,   161,   162,     0,     0,     0,
     155,   156,   157,   158,   159,     0,   160,   161,   162,   143,
     144,   145,   146,   147,     0,   148,     0,     0,  -181,  -181,
       0,     0,     0,     0,   156,   157,   158,   159,     0,   160,
     161,   162,   143,   144,   145,   146,   147,     0,   148,     0,
       0,   149,   150,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,   159,
       0,   160,   161,   162,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,   159,     0,   160,   161,   162
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        21,    15,   126,     4,    25,     4,     4,     4,     4,     4,
       0,     4,    26,     5,     5,   165,   166,     5,    32,     4,
       5,    22,    23,     5,     8,     5,   138,     5,     5,   130,
       5,     6,     7,     8,     5,     3,    65,   236,     5,    56,
       3,    56,    14,    15,    16,    17,    18,    56,    20,    63,
      64,    23,    24,   165,   166,    69,    70,    71,    72,     3,
      77,    72,    77,    57,    39,    40,   190,   266,    77,    76,
      48,    65,    47,    41,    95,    59,    54,    54,    41,    54,
       5,    66,     5,    54,    66,    77,    77,    54,    57,    77,
      62,    63,    64,    76,    66,    67,    68,    41,    54,    45,
      46,   251,    71,   117,   118,   255,    59,     4,   109,   259,
     109,   109,   109,   109,   109,   129,   109,    75,   242,    65,
      59,     4,     5,    76,   248,    75,    65,    75,    75,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     251,    56,    56,   167,   255,    57,    75,    59,   259,    71,
      72,   175,   176,    66,    67,    68,    75,    75,    73,    71,
     191,   192,    63,    64,    76,    66,    67,    68,    57,   200,
       5,     6,     7,     8,    65,    75,    75,    75,    57,    76,
      56,   315,    76,    71,    71,    71,    76,    50,    72,    56,
      59,    73,     5,    78,   225,    76,    76,   228,    49,     8,
      77,    76,   233,    76,    39,    40,    77,    77,     5,    77,
      42,    59,    47,    77,     5,   349,    65,    77,    73,    54,
      77,   252,   253,    75,    77,   256,   257,    65,    75,   260,
     261,   262,    77,    77,    77,     5,    71,    72,     5,    76,
      13,    76,     3,     4,     5,     6,     7,     8,   272,    10,
      11,    57,    56,    65,    57,    56,    76,    12,   289,    77,
      76,    22,    77,     2,    25,   324,   323,   325,   171,   268,
     314,    -1,   303,   304,   305,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      51,    52,    53,    54,    55,    -1,    -1,    -1,   164,   330,
      14,    15,    16,    17,    18,   329,    20,    -1,    -1,    -1,
      71,    72,    73,    -1,    -1,    76,    -1,    -1,    -1,   350,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      -1,    -1,    25,    -1,     4,     5,     6,     7,     8,    63,
      64,    -1,    66,    67,    68,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    -1,    -1,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    -1,    42,    -1,    -1,    45,    46,    47,    71,    72,
      -1,    -1,    -1,    76,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    -1,    -1,    -1,    -1,    69,
      70,    71,    72,    -1,    -1,    -1,    76,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    -1,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    60,    61,    62,    63,    64,    -1,
      66,    67,    68,    -1,    14,    15,    16,    17,    18,    -1,
      20,    -1,    78,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    -1,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    -1,    66,    67,    68,
      14,    15,    16,    17,    18,    -1,    20,    -1,    77,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    -1,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    -1,    66,    67,    68,    14,    15,    16,    17,
      18,    -1,    20,    -1,    77,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    33,    34,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    -1,    66,    67,
      68,    -1,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    60,    61,    62,    63,    64,    -1,    66,
      67,    68,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    14,    15,    16,    17,    18,    31,
      20,    33,    -1,    23,    24,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    33,    66,    67,    68,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    60,    61,
      62,    63,    64,    -1,    66,    67,    68,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    -1,    66,    67,    68,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    -1,    66,
      67,    68,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      -1,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    -1,    66,    67,    68
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    80,    81,     0,    82,     3,     4,     5,     6,     7,
       8,    10,    11,    22,    25,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    51,    52,    53,    54,    55,
      71,    72,    76,    83,    84,    86,    87,    88,    89,    90,
      92,    93,    95,   110,   112,   113,   118,   119,   121,   124,
     130,   135,   137,   139,   144,   145,   147,   148,   151,     5,
     131,   132,    65,    76,    76,     5,   136,     4,    42,    63,
      64,    69,    70,    72,    85,    90,    91,    92,    93,    94,
     119,   121,   124,   125,   126,   127,   128,   129,   140,   145,
      54,   133,   134,     4,     5,     5,    72,    84,     5,    90,
      90,    84,    91,     4,    91,   141,   142,     8,    59,    82,
     111,    91,    75,    75,    45,    46,    65,    57,    71,    75,
      75,    75,    75,    75,    75,    59,    76,    75,    75,    57,
      56,     5,    54,    91,    91,    59,    65,    65,    76,    91,
      91,    91,    91,    14,    15,    16,    17,    18,    20,    23,
      24,    31,    32,    33,    34,    60,    61,    62,    63,    64,
      66,    67,    68,    57,    56,    76,    76,    71,    84,    50,
     114,   115,   116,    72,    78,    56,    59,    73,    73,    56,
      73,    77,     5,    54,    91,    91,     5,   141,    91,   132,
      76,    77,    77,     4,     5,    66,     5,    66,    48,     5,
      77,   131,   138,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,   134,    77,   131,   138,    77,   131,
     138,    91,    76,    49,   117,   116,    96,    97,    98,    91,
      91,     8,    76,    78,    77,   141,    84,    84,    76,    65,
      84,    56,    77,    77,    84,    56,    77,    77,    84,    56,
      77,    77,    78,     5,    84,   108,   109,   139,    99,     3,
      41,   100,    59,   141,   146,    77,   152,   141,    65,   138,
      84,    84,   138,    84,    84,   138,    84,    84,    84,    77,
      73,   139,   100,   101,   102,    75,    91,    77,   143,   123,
     149,    77,    65,    77,    77,    77,    84,    75,     5,   104,
     105,     5,   106,   107,   122,    76,   120,    13,   153,    84,
      84,    84,    57,    56,    57,    56,   120,   141,    65,    76,
      12,   150,     5,     6,     7,     8,    39,    40,    47,    54,
     103,   105,   103,   107,    77,     5,    54,    91,    84,    76,
      77,   141,    84,    77
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
      83,    83,    83,    83,    84,    85,    85,    86,    87,    88,
      88,    89,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    92,    92,    92,
      93,    94,    94,    94,    94,    95,    96,    96,    98,    97,
      99,    97,   101,   100,   102,   100,   103,   103,   103,   103,
     103,   103,   103,   103,   104,   104,   105,   105,   106,   106,
     107,   108,   108,   109,   109,   110,   111,   111,   112,   112,
     113,   114,   115,   115,   116,   117,   117,   118,   119,   119,
     119,   119,   120,   120,   120,   120,   122,   121,   123,   121,
     124,   124,   124,   124,   125,   125,   125,   125,   125,   125,
     126,   126,   127,   127,   128,   128,   128,   128,   128,   129,
     129,   129,   129,   129,   130,   130,   131,   131,   132,   132,
     133,   133,   134,   135,   136,   136,   137,   137,   137,   137,
     137,   138,   139,   139,   139,   139,   139,   139,   139,   139,
     140,   140,   140,   140,   141,   141,   142,   142,   143,   143,
     144,   144,   146,   145,   147,   147,   148,   149,   149,   150,
     150,   152,   153,   151
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     2,     1,     1,     1,     2,
       2,     2,     1,     1,     3,     3,     6,     1,     1,     3,
       6,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     2,     2,     2,     2,     6,     0,     1,     0,     3,
       0,     4,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     1,     1,     3,
       3,     0,     1,     1,     2,     3,     3,     5,     3,     3,
       2,     1,     1,     2,     5,     0,     2,     4,     3,     3,
       3,     3,     0,     6,     3,     3,     0,     8,     0,     8,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     3,     3,     1,
       1,     3,     3,     3,     1,     3,     4,     4,     4,     4,
       2,     4,     5,     5,     6,     6,     6,     6,     8,     8,
       4,     5,     5,     7,     0,     1,     1,     3,     0,     4,
       1,     3,     0,     6,     2,     1,     5,     0,     6,     0,
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
  "non_empty_call_args", "fcall_chain", "fully_qualified_name", "fcall",
  "@8", "return_stmt", "while", "elseif", "else", "if", "@9", "@10", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        80,     0,    -1,    -1,    81,    82,    -1,    -1,    82,    83,
      -1,   137,    75,    -1,   130,    75,    -1,   135,    75,    -1,
     145,    75,    -1,   121,    75,    -1,   139,    -1,   147,    75,
      -1,   151,    -1,   148,    -1,   124,    75,    -1,    84,    -1,
      88,    -1,    89,    -1,   113,    75,    -1,    86,    75,    -1,
      87,    75,    -1,   118,    -1,    95,    -1,    72,    82,    73,
      -1,     4,    65,    48,    -1,     4,    65,    48,    76,   141,
      77,    -1,    22,    -1,    53,    -1,    43,     5,    84,    -1,
      43,     5,    71,    91,    78,    84,    -1,    44,    84,    -1,
       5,    -1,    54,    -1,     8,    -1,     6,    -1,     7,    -1,
      47,    -1,    39,    -1,    40,    -1,   112,    -1,   110,    -1,
      76,    91,    77,    -1,    90,    -1,    94,    -1,   128,    -1,
     127,    -1,   129,    -1,   126,    -1,   125,    -1,   124,    -1,
     145,    -1,   140,    -1,    85,    -1,   119,    -1,   121,    -1,
      93,    -1,     5,    -1,   119,    -1,    93,    -1,    92,    71,
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
      -1,    42,     5,    76,   138,    77,    84,    -1,    42,     4,
      76,   138,    77,    84,    -1,    42,     5,    76,   131,    77,
      84,    -1,    42,     4,    76,   131,    77,    84,    -1,    42,
       5,    76,   131,    56,   138,    77,    84,    -1,    42,     4,
      76,   131,    56,   138,    77,    84,    -1,    42,    76,    77,
      84,    -1,    42,    76,   138,    77,    84,    -1,    42,    76,
     131,    77,    84,    -1,    42,    76,   131,    56,   138,    77,
      84,    -1,    -1,   142,    -1,    91,    -1,   142,    56,    91,
      -1,    -1,   143,    76,   141,    77,    -1,     5,    -1,   144,
      59,     5,    -1,    -1,   144,    76,   141,    77,   146,   143,
      -1,    38,    91,    -1,    38,    -1,    10,    76,    91,    77,
      84,    -1,    -1,   149,    13,    76,    91,    77,    84,    -1,
      -1,    12,    84,    -1,    -1,    -1,    11,    76,    91,    77,
      84,   152,   149,   153,   150,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     7,     8,    11,    14,    17,    20,
      23,    26,    28,    31,    33,    35,    38,    40,    42,    44,
      47,    50,    53,    55,    57,    61,    65,    72,    74,    76,
      80,    87,    90,    92,    94,    96,    98,   100,   102,   104,
     106,   108,   110,   114,   116,   118,   120,   122,   124,   126,
     128,   130,   132,   134,   136,   138,   140,   142,   144,   146,
     148,   153,   156,   159,   162,   165,   172,   173,   175,   176,
     180,   181,   186,   187,   191,   192,   196,   198,   200,   202,
     204,   206,   208,   210,   212,   214,   218,   222,   224,   226,
     230,   234,   235,   237,   239,   242,   246,   250,   256,   260,
     264,   267,   269,   271,   274,   280,   281,   284,   289,   293,
     297,   301,   305,   306,   313,   317,   321,   322,   331,   332,
     341,   344,   347,   350,   353,   357,   361,   365,   369,   373,
     377,   381,   385,   389,   393,   397,   401,   405,   409,   413,
     417,   421,   425,   429,   433,   436,   439,   441,   445,   449,
     451,   453,   457,   461,   465,   467,   471,   476,   481,   486,
     491,   494,   499,   505,   511,   518,   525,   532,   539,   548,
     557,   562,   568,   574,   582,   583,   585,   587,   591,   592,
     597,   599,   603,   604,   611,   614,   616,   622,   623,   630,
     631,   634,   635,   636
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   210,   210,   210,   214,   215,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   240,   244,   245,   249,   253,   257,
     264,   274,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   315,   316,   317,
     321,   325,   326,   327,   328,   332,   336,   337,   341,   341,
     342,   342,   346,   346,   347,   347,   351,   352,   353,   354,
     355,   356,   357,   358,   362,   363,   367,   368,   372,   373,
     377,   381,   382,   386,   387,   391,   395,   396,   400,   401,
     405,   409,   413,   414,   418,   422,   423,   427,   431,   432,
     433,   434,   438,   439,   440,   441,   445,   445,   446,   446,
     450,   451,   452,   453,   457,   458,   459,   460,   461,   462,
     466,   467,   471,   472,   476,   477,   478,   479,   480,   484,
     485,   486,   487,   488,   492,   493,   497,   498,   502,   503,
     507,   508,   512,   516,   520,   521,   525,   526,   527,   528,
     529,   533,   537,   539,   541,   543,   545,   547,   549,   551,
     556,   558,   560,   562,   567,   568,   572,   573,   577,   578,
     582,   583,   587,   587,   591,   592,   596,   600,   602,   607,
     608,   612,   613,   612
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
  const int Parser::yylast_ = 876;
  const int Parser::yynnts_ = 75;
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

