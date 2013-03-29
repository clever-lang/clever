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

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(4) - (3)].attrarray)); (yysemantic_stack_[(4) - (3)].attrarray)->setVisibility((yysemantic_stack_[(4) - (1)].flags)); }
    break;

  case 105:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(4) - (3)].attrarray)); (yysemantic_stack_[(4) - (3)].attrarray)->setVisibility((yysemantic_stack_[(4) - (1)].flags)); }
    break;

  case 106:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].fdecl)); (yysemantic_stack_[(3) - (3)].fdecl)->setVisibility((yysemantic_stack_[(3) - (2)].flags)); }
    break;

  case 107:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (4)].attrarray)); (yysemantic_stack_[(5) - (4)].attrarray)->setVisibility((yysemantic_stack_[(5) - (2)].flags)); }
    break;

  case 108:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (4)].attrarray)); (yysemantic_stack_[(5) - (4)].attrarray)->setVisibility((yysemantic_stack_[(5) - (2)].flags)); }
    break;

  case 109:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 110:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 111:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 112:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 113:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 114:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 116:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 117:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 118:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 119:

    { (yyval.block) = NULL; }
    break;

  case 120:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 121:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 122:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 123:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 124:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 125:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 126:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 127:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 128:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 129:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 130:

    { (yyval.mcall) = (yysemantic_stack_[(0) - (0)].mcall); }
    break;

  case 131:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (0)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 132:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 133:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); (yyval.property)->setStatic(); }
    break;

  case 134:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 135:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 136:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 137:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 138:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
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

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].subscript)->setWriteMode(); }
    break;

  case 151:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].subscript)->setWriteMode(); }
    break;

  case 152:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].subscript)->setWriteMode(); }
    break;

  case 153:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].subscript)->setWriteMode(); }
    break;

  case 154:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 155:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 156:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 157:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 158:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 159:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 160:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 161:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 162:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 163:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 164:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 165:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 166:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 167:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 168:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 169:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 170:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 171:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 172:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 173:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 174:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 175:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR,     (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 176:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 177:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 178:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 179:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 180:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR,     (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 181:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 182:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 183:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 184:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 185:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 186:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 187:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 188:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 189:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 190:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 191:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 192:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 193:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 194:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 195:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 196:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 197:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 198:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 199:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 200:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 201:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 202:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 203:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 204:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 205:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 206:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 207:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 208:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 209:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 210:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 211:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 212:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 213:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 214:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 215:

    { (yyval.narray) = NULL; }
    break;

  case 217:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 218:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 219:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 220:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 221:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 223:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 224:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 225:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 226:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 227:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 228:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 229:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 230:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 231:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 232:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 233:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 234:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 235:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 236:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 237:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 238:

    { (yyval.narray) = NULL; }
    break;

  case 241:

    { (yyval.node) = NULL;     }
    break;

  case 242:

    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); }
    break;

  case 244:

    { (yyval.for_loop) = new ast::For((yysemantic_stack_[(9) - (3)].narray), (yysemantic_stack_[(9) - (5)].node), (yysemantic_stack_[(9) - (7)].narray), (yysemantic_stack_[(9) - (9)].block), yyloc); }
    break;

  case 245:

    {	(yyval.foreach_loop) = new ast::ForEach(new ast::VariableDecl((yysemantic_stack_[(8) - (4)].ident), new ast::Assignment((yysemantic_stack_[(8) - (4)].ident), NULL, yyloc), false, yyloc), (yysemantic_stack_[(8) - (6)].node), (yysemantic_stack_[(8) - (8)].block), yyloc); }
    break;

  case 247:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 248:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 249:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 250:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 251:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 252:

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
  const short int Parser::yypact_ninf_ = -364;
  const short int
  Parser::yypact_[] =
  {
      -364,   101,  -364,  -364,   636,   110,    44,   280,  -364,  -364,
    -364,    41,    45,    48,  -364,   176,   690,  -364,  -364,   157,
      10,   145,    40,    40,  -364,   145,   690,  -364,  -364,   126,
     130,   690,   690,   690,   690,   690,    11,   690,  -364,  -364,
     158,   171,   174,  -364,   127,  1022,   725,  1254,  -364,  -364,
    -364,  -364,  -364,   177,  -364,  1266,   178,   184,  -364,  -364,
    -364,   197,   207,   208,   209,   210,  -364,  -364,   192,   211,
     212,   215,  -364,  -364,  -364,   221,   198,  -364,    29,   690,
     331,   690,   690,  -364,    55,   216,    11,  -364,  1022,  -364,
    -364,  -364,  -364,  -364,  -364,  -364,   238,   204,  -364,   222,
     223,   307,     8,  -364,  -364,   244,   104,   250,   245,    99,
     103,   250,    99,   103,   273,  1022,   246,   690,  -364,  -364,
    -364,  -364,  1022,   243,   266,   264,   252,   557,   162,   779,
    -364,  -364,  -364,  -364,  -364,    35,   690,   690,   690,   690,
     690,   690,   690,   690,   690,   690,   690,   690,   690,   690,
     690,   690,   690,   690,   690,   690,   690,   690,   690,   690,
     690,   690,   690,   690,   690,   690,   690,   690,  -364,  -364,
      54,  -364,  -364,  -364,    56,  -364,  -364,  -364,  -364,  -364,
    -364,  -364,    19,  -364,  -364,  -364,   690,   110,   251,   259,
    -364,   249,   328,  -364,   266,   261,   839,   860,    16,    21,
     690,   157,    12,    13,   262,    -2,   145,   117,   267,    52,
      57,    58,    59,   265,   302,   273,  -364,    42,   920,  -364,
     690,   690,  -364,  -364,   346,  -364,  -364,   274,  -364,   650,
     650,   650,   650,   200,   200,  1188,  1188,   429,  1082,  1106,
    1094,  1117,  1177,  1199,   203,   203,  -364,  -364,  -364,  1094,
    1094,  1094,  1094,  1094,  1094,  1094,  1094,  1094,  1094,  1094,
     213,   276,  -364,   277,  -364,   289,   179,  -364,  1022,  -364,
     690,   690,  -364,     7,   690,   145,   145,  -364,  -364,  -364,
    -364,  -364,  1022,  -364,   145,   137,   278,   145,   160,   281,
     282,   292,  -364,   360,   145,   145,  -364,  -364,  -364,  -364,
     361,   145,  -364,  -364,  -364,  -364,   290,    32,   128,   297,
    1022,  1022,   303,   690,  -364,   690,   690,    53,   690,   287,
     296,  -364,   690,  1022,   299,  -364,  -364,  -364,   360,   145,
     145,  -364,   360,   145,   145,   145,   310,   300,  -364,  -364,
     301,  -364,  -364,   376,   380,    27,  -364,    86,  -364,   690,
     304,   306,   312,   311,   315,  -364,   316,  -364,  -364,   139,
     941,   690,  -364,   319,  -364,  -364,   320,  -364,  -364,  -364,
    -364,   145,   145,   341,   -25,  -364,   342,    -9,  -364,   376,
     380,  -364,   -21,  1022,  -364,  -364,  -364,   690,   690,  -364,
    -364,   690,   690,   145,  -364,   327,   397,   145,   145,  -364,
    -364,   195,   376,  -364,   195,   380,  -364,   125,   134,   186,
     349,   109,  -364,  -364,  -364,   332,   336,  -364,   350,   758,
     337,  -364,   145,   340,   410,  -364,  -364,  -364,  -364,  -364,
    -364,  -364,  -364,  -364,  -364,  -364,  -364,  -364,  -364,  -364,
    -364,   185,   359,   362,   363,   364,   250,   354,   365,   148,
    -364,   186,   366,  -364,   350,   350,   350,  -364,  -364,   139,
      65,  -364,  -364,  -364,   690,   145,  -364,  -364,   636,   367,
    -364,  -364,   344,  -364,  1001,  -364,   636,  -364,   636,   350,
     690,   145,   636,   352,  -364,  -364
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    35,    38,    39,
      37,     0,     0,     0,    32,     0,   236,    41,    42,     0,
       0,     0,     0,     0,    40,     0,     0,    33,    36,     0,
       0,     0,     0,     0,     0,   215,     4,     0,     5,    17,
      47,     0,     0,    18,    48,     0,     0,    49,    26,    50,
      23,    44,    43,     0,    22,    61,    59,    57,    55,    54,
      52,    51,    53,     0,    56,     0,    11,    58,     0,    60,
      46,     0,    14,    15,    13,   189,   184,   186,     0,   215,
     238,     0,     0,   194,   200,     0,     0,    47,   235,    59,
      57,    51,    53,    56,    60,    46,     0,   185,   190,     0,
       0,     0,     0,     4,    34,     0,    35,   144,     0,   152,
     148,   145,   153,   149,     0,   114,     0,     0,    78,    79,
      80,    81,   217,     0,   216,     0,     0,     0,     0,     0,
      25,    20,    21,   142,   143,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
       0,    19,   146,   147,     0,    10,    16,    27,    28,     7,
       8,     6,     0,    24,     9,    12,     0,     0,   124,    30,
     125,     0,     0,   239,   240,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   189,     0,     0,     0,     0,
       0,     0,     0,     0,   119,   115,   116,   100,     0,   109,
       0,     0,   112,    29,     0,   113,    45,   122,   123,   159,
     157,   158,   156,   178,   177,   154,   155,   160,   162,   161,
     163,   175,   176,   174,   165,   164,   166,   167,   168,   183,
     182,   169,   171,   172,   170,   173,   179,   180,   181,   193,
       0,   128,   129,   126,   127,     0,   227,   226,   188,   187,
     215,   215,   233,   189,   241,     0,     0,   199,   198,   197,
     195,   196,   192,   191,     0,     0,     0,     0,     0,     0,
       0,     0,   211,     0,     0,     0,   124,   122,   128,   126,
       0,     0,   121,   117,   101,   102,     0,     0,   100,     0,
     218,   110,     0,   215,    65,   215,   215,     0,   215,     0,
       0,   219,     0,   242,     0,   237,   250,   203,     0,     0,
       0,   202,     0,     0,     0,     0,     0,     0,   213,   212,
       0,   120,    82,     0,     0,     0,   103,     0,    66,     0,
       0,     0,     0,     0,   229,   228,     0,   138,    31,   234,
       0,   215,   246,     0,   208,   206,     0,   207,   205,   204,
     201,     0,     0,    94,     0,    91,     0,     0,    95,     0,
       0,   106,     0,   111,   134,   140,   136,   215,   215,   224,
     130,     0,   215,     0,   243,     0,   251,     0,     0,   214,
     118,     0,     0,   104,     0,     0,   105,     0,     0,     0,
       0,     0,   130,   130,   130,     0,     0,   219,   139,     0,
       0,   245,     0,     0,   248,   210,   209,    83,    86,    87,
      85,    89,    90,    88,    84,    93,    92,    97,    96,   107,
     108,    35,    38,    39,    37,    36,     0,    64,     0,    63,
       4,     0,     0,    67,   135,   141,   137,   231,   230,   225,
       0,   221,   220,   244,     0,     0,   252,     4,    75,     0,
       4,   130,   132,   133,     0,   249,    74,     4,    77,   232,
     215,     0,    76,     0,   247,   131
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -364,  -364,  -364,     0,  -364,    18,    -3,  -364,  -364,  -364,
     -18,    -4,   -16,   -14,  -364,  -364,   -19,  -364,  -364,  -364,
      34,    63,    39,    68,    31,  -364,   143,  -364,  -364,  -364,
    -364,  -364,  -364,  -364,   239,  -364,  -364,   -12,  -363,    37,
    -364,  -364,  -364,  -364,    38,  -364,  -364,  -364,    49,    50,
     375,   -99,  -162,  -364,   255,    61,  -364,  -364,  -119,  -251,
    -364,   -63,   377,    46,  -364,    62,  -364,  -364,    77,  -364,
    -364,  -364,  -364,  -364,  -364,  -364,  -364,  -364,  -364,  -364,
    -364
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   127,    38,    39,    87,    41,    42,    43,
      44,   122,    46,    47,    48,   382,   448,   411,    49,    50,
     435,   374,   375,   377,   378,   306,   307,   308,    51,   128,
      52,    53,   214,   215,   216,   302,    54,    55,   418,    89,
     412,   414,   390,   413,    90,    58,    59,    60,    91,    92,
      63,    76,    77,    97,    98,    93,    84,    65,   208,    66,
      67,   123,   124,   359,    68,    94,   417,   471,    95,   321,
      71,    72,   195,   324,   395,    73,   396,   466,    74,   362,
     424
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -224;
  const short int
  Parser::yytable_[] =
  {
        45,    40,     4,   207,   107,   111,   108,   108,   109,   112,
     110,   113,    88,   205,    99,   100,   191,   205,   205,   125,
     277,   278,   115,   265,   266,   269,   280,   118,   119,   120,
     121,    99,   100,   129,   188,   343,   402,   409,   410,   104,
     227,    56,    57,   114,   105,   106,     8,     9,    10,   454,
     455,   456,   405,    61,    62,   403,   346,   296,   353,   261,
     186,   263,   297,   298,   299,    64,    69,   322,   291,   186,
     472,   406,   267,   344,   345,   126,   189,   196,   197,    17,
      18,    70,   190,   286,   289,   101,    24,   279,   228,   379,
     206,   102,   281,    28,   284,   287,   381,   304,   305,   189,
     354,     3,   101,   285,   288,   190,   355,   262,   479,   264,
     228,   262,   264,   218,    78,    75,    35,    86,   473,   198,
     -98,    37,    80,    45,    40,   199,    81,   380,   345,    82,
     116,   269,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,    56,    57,   269,   451,   452,   211,
     269,   133,   134,   212,   337,   -64,    61,    62,   293,   -63,
     -62,    83,   268,   304,   305,    79,   402,   453,    64,    69,
     105,   441,   442,   443,   444,   405,   282,   135,   328,   294,
     427,   428,   429,   430,    70,   439,   -99,   319,   320,   363,
      96,   117,   -73,   366,   440,   391,   310,   311,   212,   329,
     392,   332,   103,   224,   292,    17,    18,   136,   137,   138,
     139,   140,    24,   141,   431,   432,   142,   143,   130,   445,
     225,   433,   333,  -223,   144,   145,   146,   147,   434,   -68,
     350,   131,   351,   352,   132,   356,   182,   171,   175,   187,
     318,   -62,    35,    86,   176,   201,    79,    37,   151,   152,
     323,   153,   154,   155,   153,   154,   155,   177,   148,   149,
     150,   151,   152,   186,   153,   154,   155,   178,   179,   180,
     181,   183,   184,   325,   326,   185,   314,   102,   394,   -62,
     200,   -62,   327,   202,   203,   331,   -62,   -62,   -62,   -62,
     -62,   204,   338,   339,   209,   -62,   -62,   -62,   360,   341,
     210,   167,   213,   217,   415,   416,   219,   220,   221,   420,
     222,   272,   270,   273,   192,     6,     7,     8,     9,    10,
     271,   274,   -62,   290,  -222,   383,   300,   364,   365,   295,
     301,   367,   368,   369,   312,   313,   -62,   315,   316,   317,
     330,    79,   336,   334,   335,   205,   340,   349,   342,   357,
      17,    18,    19,    85,   348,    22,    23,    24,   358,   361,
     370,   373,   371,   372,    28,   376,   384,   419,   385,   399,
     400,   446,   387,   108,   386,   447,   388,   449,   389,    31,
      32,   397,   398,   401,   404,    33,    34,    35,    86,   422,
     423,   421,    37,   450,   457,   425,   426,   483,   458,   462,
     460,   464,   465,   -71,   211,   480,   -72,   -70,   -69,   467,
     470,   477,   469,   446,   485,   108,   438,   447,   437,   449,
     463,   436,   407,   136,   137,   138,   139,   140,   408,   141,
     468,   347,   142,   143,   303,   193,   283,   194,     0,     0,
     474,     0,   146,   459,    45,    40,     0,   476,     0,     0,
     478,     0,    45,    40,    45,    40,     0,   482,    45,    40,
       0,     0,     0,   475,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   148,   149,   150,   151,   152,   484,
     153,   154,   155,     0,     0,    56,    57,     0,     0,     0,
       0,     0,     0,    56,    57,    56,    57,    61,    62,    56,
      57,     0,     0,     0,     0,    61,    62,    61,    62,    64,
      69,    61,    62,     0,     0,     0,     0,    64,    69,    64,
      69,     0,     0,    64,    69,    70,     0,     0,     0,     0,
       0,     0,     0,    70,     0,    70,     0,     0,     0,    70,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
       0,     0,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,     0,     0,    25,    26,    27,
      28,    29,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
       0,    33,    34,    35,    36,   223,     0,     0,    37,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,     0,
       0,    15,     0,     0,  -224,  -224,  -224,  -224,   140,     0,
     141,     0,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,     0,     0,    25,    26,    27,    28,
      29,     0,     0,    30,     6,     7,     8,     9,    10,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,     0,
      33,    34,    35,    36,     0,     0,     0,    37,   151,   152,
       0,   153,   154,   155,     0,     0,     0,     0,     0,    17,
      18,     0,    85,     0,    22,    23,    24,     0,     0,     0,
       0,     0,     0,    28,   156,     0,   157,     0,     0,     0,
       0,   158,   159,   160,   161,   162,     0,     0,    31,    32,
     163,   164,   165,     0,    33,    34,    35,    86,     0,     0,
       0,    37,   136,   137,   138,   139,   140,     0,   141,     0,
       0,   142,   143,     0,     0,     0,     0,   166,     0,   144,
     145,   146,   147,   136,   137,   138,   139,   140,     0,   141,
       0,   167,   142,   143,     0,     0,     0,     0,     0,     0,
     144,   145,   146,   147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   148,   149,   150,   151,   152,     0,   153,
     154,   155,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   461,     0,     0,   148,   149,   150,   151,   152,     0,
     153,   154,   155,   136,   137,   138,   139,   140,     0,   141,
       0,   226,   142,   143,     0,     0,     0,     0,     0,     0,
     144,   145,   146,   147,   136,   137,   138,   139,   140,     0,
     141,     0,     0,   142,   143,     0,     0,     0,     0,     0,
       0,   144,   145,   146,   147,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   148,   149,   150,   151,   152,     0,
     153,   154,   155,     0,     0,     0,     0,     0,     0,     0,
       0,   275,     0,     0,     0,   148,   149,   150,   151,   152,
       0,   153,   154,   155,   136,   137,   138,   139,   140,     0,
     141,     0,   276,   142,   143,     0,     0,     0,     0,     0,
       0,   144,   145,   146,   147,   136,   137,   138,   139,   140,
       0,   141,     0,     0,   142,   143,     0,     0,     0,     0,
       0,     0,   144,   145,   146,   147,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   148,   149,   150,   151,   152,
       0,   153,   154,   155,     0,     0,     0,     0,     0,     0,
       0,     0,   309,     0,     0,     0,   148,   149,   150,   151,
     152,     0,   153,   154,   155,   136,   137,   138,   139,   140,
       0,   141,     0,   393,   142,   143,     0,     0,     0,     0,
       0,     0,   144,   145,   146,   147,   136,   137,   138,   139,
     140,     0,   141,     0,     0,   142,   143,     0,     0,     0,
       0,     0,     0,   144,   145,   146,   147,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   148,   149,   150,   151,
     152,     0,   153,   154,   155,     0,     0,     0,     0,     0,
       0,     0,     0,   481,     0,     0,     0,   148,   149,   150,
     151,   152,     0,   153,   154,   155,   136,   137,   138,   139,
     140,     0,   141,     0,     0,   142,   143,     0,   136,   137,
     138,   139,   140,   144,   141,   146,   147,   142,   143,     0,
     136,   137,   138,   139,   140,   144,   141,   146,     0,   142,
     143,   136,   137,   138,   139,   140,     0,   141,     0,     0,
     142,   143,     0,     0,     0,     0,     0,   148,   149,   150,
     151,   152,     0,   153,   154,   155,     0,     0,     0,   148,
     149,   150,   151,   152,     0,   153,   154,   155,     0,     0,
       0,   148,   149,   150,   151,   152,     0,   153,   154,   155,
       0,     0,     0,   149,   150,   151,   152,     0,   153,   154,
     155,   136,   137,   138,   139,   140,     0,   141,     0,     0,
     142,   143,   136,   137,   138,   139,   140,     0,   141,     0,
       0,  -224,  -224,   136,   137,   138,   139,   140,     0,   141,
       0,     0,   142,   143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150,   151,   152,     0,   153,   154,
     155,     0,     0,     0,     0,     0,   151,   152,     0,   153,
     154,   155,     0,     0,     0,     0,     0,   151,   152,     0,
     153,   154,   155,   -64,     0,   -64,     0,     0,     0,     0,
     -64,   -64,   -64,   -64,   -64,   -63,     0,   -63,     0,   -64,
     -64,   -64,   -63,   -63,   -63,   -63,   -63,     0,   168,   169,
       0,   -63,   -63,   -63,     0,     0,     0,     0,     0,     0,
     172,   173,     0,     0,     0,     0,   -64,     0,     0,     0,
       0,     0,     0,     0,   170,     0,     0,     0,   -63,     0,
     -64,     0,     0,     0,     0,     0,   174,     0,     0,     0,
       0,     0,   -63
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     2,   102,    22,    23,    22,    23,    22,    23,
      22,    23,    16,     5,     4,     5,    79,     5,     5,     8,
       4,     5,    26,     4,     5,   187,     5,    31,    32,    33,
      34,     4,     5,    37,     5,     3,    61,    58,    59,    21,
       5,     4,     4,    25,     4,     5,     6,     7,     8,   412,
     413,   414,    61,     4,     4,    80,   307,     5,     5,     5,
      62,     5,     5,     5,     5,     4,     4,    60,    70,    62,
       5,    80,    53,    41,    42,    64,    47,    81,    82,    39,
      40,     4,    53,   202,   203,    75,    46,    71,    53,     3,
      82,    81,    71,    53,    82,    82,   347,    55,    56,    47,
      47,     0,    75,   202,   203,    53,    53,    53,   471,    53,
      53,    53,    53,   117,    70,     5,    76,    77,    53,    64,
      78,    81,    81,   127,   127,    70,    81,    41,    42,    81,
       4,   293,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   127,   127,   328,    58,    59,    70,
     332,    44,    45,    70,   293,    76,   127,   127,    61,    76,
      76,     5,   186,    55,    56,    81,    61,    78,   127,   127,
       4,     5,     6,     7,     8,    61,   200,    70,    61,    82,
       5,     6,     7,     8,   127,    80,    78,   270,   271,   328,
      53,    81,    64,   332,    80,    76,   220,   221,    70,    82,
      81,    61,    77,    61,   206,    39,    40,    14,    15,    16,
      17,    18,    46,    20,    39,    40,    23,    24,    80,    53,
      78,    46,    82,    64,    31,    32,    33,    34,    53,    64,
     313,    80,   315,   316,    80,   318,    64,    80,    80,    61,
      81,    76,    76,    77,    80,    61,    81,    81,    68,    69,
     274,    71,    72,    73,    71,    72,    73,    80,    65,    66,
      67,    68,    69,    62,    71,    72,    73,    80,    80,    80,
      80,    80,    80,   275,   276,    80,    83,    81,   361,    19,
      62,    21,   284,    81,    81,   287,    26,    27,    28,    29,
      30,     4,   294,   295,    70,    35,    36,    37,   322,   301,
      70,    76,    49,    77,   387,   388,    83,    61,    64,   392,
      78,    82,    81,     5,     3,     4,     5,     6,     7,     8,
      81,    80,    62,    81,    64,   349,    81,   329,   330,    82,
      48,   333,   334,   335,     8,    81,    76,    81,    81,    70,
      82,    81,    70,    82,    82,     5,     5,    64,    78,    82,
      39,    40,    41,    42,    77,    44,    45,    46,    82,    80,
      70,     5,    82,    82,    53,     5,    82,   391,    82,   371,
     372,   409,    81,   409,    82,   409,    81,   409,    82,    68,
      69,    82,    82,    62,    62,    74,    75,    76,    77,    82,
      13,   393,    81,    64,    82,   397,   398,   480,    82,    82,
      70,    81,    12,    64,    70,    81,    64,    64,    64,    64,
      64,    64,   451,   451,    82,   451,   405,   451,   404,   451,
     422,   402,   379,    14,    15,    16,    17,    18,   380,    20,
     450,   308,    23,    24,   215,    80,   201,    80,    -1,    -1,
     464,    -1,    33,   417,   468,   468,    -1,   467,    -1,    -1,
     470,    -1,   476,   476,   478,   478,    -1,   477,   482,   482,
      -1,    -1,    -1,   465,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,   481,
      71,    72,    73,    -1,    -1,   468,   468,    -1,    -1,    -1,
      -1,    -1,    -1,   476,   476,   478,   478,   468,   468,   482,
     482,    -1,    -1,    -1,    -1,   476,   476,   478,   478,   468,
     468,   482,   482,    -1,    -1,    -1,    -1,   476,   476,   478,
     478,    -1,    -1,   482,   482,   468,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   476,    -1,   478,    -1,    -1,    -1,   482,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    81,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    25,    -1,    -1,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    -1,    -1,    57,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    -1,    -1,    -1,    81,    68,    69,
      -1,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    39,
      40,    -1,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    19,    -1,    21,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,    -1,    -1,    68,    69,
      35,    36,    37,    -1,    74,    75,    76,    77,    -1,    -1,
      -1,    81,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    62,    -1,    31,
      32,    33,    34,    14,    15,    16,    17,    18,    -1,    20,
      -1,    76,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      71,    72,    73,    14,    15,    16,    17,    18,    -1,    20,
      -1,    82,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    -1,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    -1,    65,    66,    67,    68,    69,
      -1,    71,    72,    73,    14,    15,    16,    17,    18,    -1,
      20,    -1,    82,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,
      -1,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    -1,    71,    72,    73,    14,    15,    16,    17,    18,
      -1,    20,    -1,    82,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    -1,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    71,    72,    73,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    14,    15,
      16,    17,    18,    31,    20,    33,    34,    23,    24,    -1,
      14,    15,    16,    17,    18,    31,    20,    33,    -1,    23,
      24,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    71,    72,    73,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    71,    72,    73,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    -1,    71,    72,    73,
      -1,    -1,    -1,    66,    67,    68,    69,    -1,    71,    72,
      73,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    -1,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    68,    69,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    68,    69,    -1,
      71,    72,    73,    19,    -1,    21,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,    30,    19,    -1,    21,    -1,    35,
      36,    37,    26,    27,    28,    29,    30,    -1,    44,    45,
      -1,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    62,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    76
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    85,    86,     0,    87,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    22,    25,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    50,    51,    52,    53,    54,
      57,    68,    69,    74,    75,    76,    77,    81,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,   102,
     103,   112,   114,   115,   120,   121,   123,   128,   129,   130,
     131,   132,   133,   134,   139,   141,   143,   144,   148,   149,
     152,   154,   155,   159,   162,     5,   135,   136,    70,    81,
      81,    81,    81,     5,   140,    42,    77,    90,    95,   123,
     128,   132,   133,   139,   149,   152,    53,   137,   138,     4,
       5,    75,    81,    77,    89,     4,     5,    94,    96,    97,
     121,    94,    97,   121,    89,    95,     4,    81,    95,    95,
      95,    95,    95,   145,   146,     8,    64,    87,   113,    95,
      80,    80,    80,    44,    45,    70,    14,    15,    16,    17,
      18,    20,    23,    24,    31,    32,    33,    34,    65,    66,
      67,    68,    69,    71,    72,    73,    19,    21,    26,    27,
      28,    29,    30,    35,    36,    37,    62,    76,    44,    45,
      70,    80,    44,    45,    70,    80,    80,    80,    80,    80,
      80,    80,    64,    80,    80,    80,    62,    61,     5,    47,
      53,   145,     3,   134,   146,   156,    95,    95,    64,    70,
      62,    61,    81,    81,     4,     5,    82,   135,   142,    70,
      70,    70,    70,    49,   116,   117,   118,    77,    95,    83,
      61,    64,    78,    78,    61,    78,    82,     5,    53,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,     5,    53,     5,    53,     4,     5,    53,    95,   136,
      81,    81,    82,     5,    80,    82,    82,     4,     5,    71,
       5,    71,    95,   138,    82,   135,   142,    82,   135,   142,
      81,    70,    89,    61,    82,    82,     5,     5,     5,     5,
      81,    48,   119,   118,    55,    56,   109,   110,   111,    82,
      95,    95,     8,    81,    83,    81,    81,    70,    81,   145,
     145,   153,    60,    95,   157,    89,    89,    89,    61,    82,
      82,    89,    61,    82,    82,    82,    70,   142,    89,    89,
       5,    89,    78,     3,    41,    42,   143,   110,    77,    64,
     145,   145,   145,     5,    47,    53,   145,    82,    82,   147,
      95,    80,   163,   142,    89,    89,   142,    89,    89,    89,
      70,    82,    82,     5,   105,   106,     5,   107,   108,     3,
      41,   143,    99,    95,    82,    82,    82,    81,    81,    82,
     126,    76,    81,    82,   145,   158,   160,    82,    82,    89,
      89,    62,    61,    80,    62,    61,    80,   105,   107,    58,
      59,   101,   124,   127,   125,   145,   145,   150,   122,    95,
     145,    89,    82,    13,   164,    89,    89,     5,     6,     7,
       8,    39,    40,    46,    53,   104,   106,   104,   108,    80,
      80,     5,     6,     7,     8,    53,    94,    97,   100,   121,
      64,    58,    59,    78,   122,   122,   122,    82,    82,   147,
      70,    83,    82,    89,    81,    12,   161,    64,    87,   100,
      64,   151,     5,    53,    95,    89,    87,    64,    87,   122,
      81,    82,    87,   145,    89,    82
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
      88,    88,    88,    88,    88,    88,    88,    88,    88,    89,
      90,    90,    91,    92,    93,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    96,    96,    96,    97,    99,    98,   100,   100,
     100,   100,   100,   100,   101,   101,   101,   101,   102,   102,
     102,   102,   103,   104,   104,   104,   104,   104,   104,   104,
     104,   105,   105,   106,   106,   107,   107,   108,   109,   109,
     110,   110,   110,   111,   111,   111,   111,   111,   111,   112,
     113,   113,   114,   114,   115,   116,   117,   117,   118,   119,
     119,   120,   121,   121,   121,   121,   121,   121,   121,   121,
     122,   122,   122,   122,   124,   123,   125,   123,   126,   123,
     127,   123,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   129,   129,   129,   129,   129,   129,
     130,   130,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   134,   134,   135,   135,   136,   136,
     137,   137,   138,   139,   140,   140,   141,   141,   141,   141,
     141,   142,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   144,   144,   144,   144,   145,   145,   146,   146,   147,
     147,   147,   148,   148,   150,   149,   149,   149,   149,   149,
     149,   151,   149,   153,   152,   154,   154,   155,   156,   156,
     156,   157,   157,   158,   159,   159,   160,   160,   161,   161,
     163,   164,   162
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
       0,     1,     1,     2,     4,     4,     3,     5,     5,     3,
       3,     5,     3,     3,     2,     1,     1,     2,     5,     0,
       2,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     6,     3,     3,     0,     8,     0,     8,     0,     8,
       0,     8,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     3,     3,     1,
       1,     3,     3,     3,     1,     3,     4,     4,     4,     4,
       2,     4,     5,     5,     6,     6,     6,     6,     6,     8,
       8,     4,     5,     5,     7,     0,     1,     1,     3,     0,
       4,     4,     1,     3,     0,     8,     3,     3,     5,     5,
       8,     0,    10,     0,     6,     2,     1,     5,     0,     1,
       1,     0,     1,     1,     9,     8,     0,     6,     0,     2,
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
  "\"critical\"", "\"++\"", "\"--\"", "\"null\"", "\"new\"", "\"finally\"",
  "\"catch\"", "\"try\"", "\"throw\"", "\"continue\"",
  "\"constant identifier\"", "\"class\"", "\"public\"", "\"private\"",
  "\"switch\"", "\"case\"", "\"default\"", "\"in\"", "','", "'='",
  "XOR_EQUAL", "':'", "'|'", "'^'", "'&'", "'-'", "'+'", "'.'", "'*'",
  "'/'", "'%'", "'!'", "'~'", "'['", "'{'", "'}'", "UMINUS", "';'", "'('",
  "')'", "']'", "$accept", "program", "$@1", "statement_list", "statement",
  "block", "instantiation", "break", "continue", "critical_block",
  "object", "rvalue", "lvalue", "subscript", "switch_expr", "@2", "label",
  "case_list", "unary", "class_def", "attr_rvalue", "class_attr_decl_list",
  "class_attr_decl_impl", "class_attr_const_decl_list",
  "class_attr_const_decl_impl", "class_member_decl", "visibility",
  "class_member_list", "array", "key_value_list", "map", "throw", "catch",
  "not_empty_catch", "catch_impl", "finally", "try_catch_finally",
  "property_access", "mcall_chain", "mcall", "@3", "@4", "@5", "@6",
  "inc_dec", "comparison", "boolean", "logic", "arithmetic", "bitwise",
  "variable_decl", "variable_decl_list", "variable_decl_impl",
  "const_decl_list", "const_decl_impl", "assignment", "import_ident_list",
  "import", "vararg", "fdecl", "anonymous_fdecl", "call_args",
  "non_empty_call_args", "fcall_chain", "fully_qualified_name",
  "fully_qualified_call", "@7", "@8", "fcall", "@9", "return_stmt",
  "while", "for_expr_1", "for_expr_2", "for_expr_3", "for", "elseif",
  "else", "if", "@10", "@11", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        85,     0,    -1,    -1,    86,    87,    -1,    -1,    87,    88,
      -1,   141,    80,    -1,   134,    80,    -1,   139,    80,    -1,
     152,    80,    -1,   123,    80,    -1,   143,    -1,   154,    80,
      -1,   162,    -1,   155,    -1,   159,    -1,   128,    80,    -1,
      89,    -1,    93,    -1,   115,    80,    -1,    91,    80,    -1,
      92,    80,    -1,   120,    -1,   103,    -1,   149,    80,    -1,
      90,    80,    -1,    98,    -1,   132,    80,    -1,   133,    80,
      -1,    77,    87,    78,    -1,     4,    70,    47,    -1,     4,
      70,    47,    81,   145,    82,    -1,    22,    -1,    52,    -1,
      43,    89,    -1,     5,    -1,    53,    -1,     8,    -1,     6,
      -1,     7,    -1,    46,    -1,    39,    -1,    40,    -1,   114,
      -1,   112,    -1,    81,    95,    82,    -1,   152,    -1,    90,
      -1,    94,    -1,    97,    -1,   102,    -1,   132,    -1,   131,
      -1,   133,    -1,   130,    -1,   129,    -1,   139,    -1,   128,
      -1,   144,    -1,   123,    -1,   149,    -1,   121,    -1,     5,
      -1,   121,    -1,    97,    -1,    96,    76,    95,    83,    -1,
      -1,    57,    81,    95,    82,    77,    99,   101,    78,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
     121,    -1,    58,   100,    64,    87,    -1,    59,    64,    87,
      -1,   101,    58,   100,    64,    87,    -1,   101,    59,    64,
      87,    -1,    68,    95,    -1,    69,    95,    -1,    74,    95,
      -1,    75,    95,    -1,    54,     4,    77,   109,    78,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
      46,    -1,    39,    -1,    40,    -1,   106,    -1,   105,    61,
     106,    -1,     5,    62,   104,    -1,     5,    -1,   108,    -1,
     107,    61,   108,    -1,     5,    62,   104,    -1,    -1,   111,
      -1,    -1,    55,    -1,    56,    -1,   110,   143,    -1,   110,
       3,   105,    80,    -1,   110,    41,   107,    80,    -1,   111,
     110,   143,    -1,   111,   110,     3,   105,    80,    -1,   111,
     110,    41,   107,    80,    -1,    76,   145,    83,    -1,     8,
      64,    95,    -1,   113,    61,     8,    64,    95,    -1,    77,
      64,    78,    -1,    77,   113,    78,    -1,    51,    95,    -1,
     117,    -1,   118,    -1,   117,   118,    -1,    49,    81,     5,
      82,    89,    -1,    -1,    48,    89,    -1,    50,    89,   116,
     119,    -1,    94,    70,     5,    -1,    94,    70,    53,    -1,
       4,    70,     5,    -1,     4,    70,    53,    -1,   121,    70,
       5,    -1,   121,    70,    53,    -1,    97,    70,     5,    -1,
      97,    70,    53,    -1,    -1,   122,    70,     5,    81,   145,
      82,    -1,   122,    70,     5,    -1,   122,    70,    53,    -1,
      -1,    94,    70,     5,    81,   145,    82,   124,   122,    -1,
      -1,   121,    70,     5,    81,   145,    82,   125,   122,    -1,
      -1,     4,    70,     5,    81,   145,    82,   126,   122,    -1,
      -1,    97,    70,     5,    81,   145,    82,   127,   122,    -1,
      94,    44,    -1,    94,    45,    -1,    44,    94,    -1,    45,
      94,    -1,   121,    44,    -1,   121,    45,    -1,    44,   121,
      -1,    45,   121,    -1,    97,    44,    -1,    97,    45,    -1,
      44,    97,    -1,    45,    97,    -1,    95,    23,    95,    -1,
      95,    24,    95,    -1,    95,    17,    95,    -1,    95,    15,
      95,    -1,    95,    16,    95,    -1,    95,    14,    95,    -1,
      95,    31,    95,    -1,    95,    33,    95,    -1,    95,    32,
      95,    -1,    95,    34,    95,    -1,    95,    69,    95,    -1,
      95,    68,    95,    -1,    95,    71,    95,    -1,    95,    72,
      95,    -1,    95,    73,    95,    -1,    96,    26,    95,    -1,
      96,    29,    95,    -1,    96,    27,    95,    -1,    96,    28,
      95,    -1,    96,    30,    95,    -1,    95,    67,    95,    -1,
      95,    65,    95,    -1,    95,    66,    95,    -1,    95,    20,
      95,    -1,    95,    18,    95,    -1,    96,    35,    95,    -1,
      96,    36,    95,    -1,    96,    37,    95,    -1,    96,    21,
      95,    -1,    96,    19,    95,    -1,     3,   135,    -1,    41,
     137,    -1,   136,    -1,   135,    61,   136,    -1,     5,    62,
      95,    -1,     5,    -1,   138,    -1,   137,    61,   138,    -1,
      53,    62,    95,    -1,    96,    62,    95,    -1,     5,    -1,
     140,    70,     5,    -1,    25,   140,    70,    71,    -1,    25,
     140,    64,    71,    -1,    25,   140,    64,     5,    -1,    25,
     140,    64,     4,    -1,    25,   140,    -1,     5,    70,    70,
      70,    -1,    42,     5,    81,    82,    89,    -1,    42,     4,
      81,    82,    89,    -1,    42,    75,     4,    81,    82,    89,
      -1,    42,     5,    81,   142,    82,    89,    -1,    42,     4,
      81,   142,    82,    89,    -1,    42,     5,    81,   135,    82,
      89,    -1,    42,     4,    81,   135,    82,    89,    -1,    42,
       5,    81,   135,    61,   142,    82,    89,    -1,    42,     4,
      81,   135,    61,   142,    82,    89,    -1,    42,    81,    82,
      89,    -1,    42,    81,   142,    82,    89,    -1,    42,    81,
     135,    82,    89,    -1,    42,    81,   135,    61,   142,    82,
      89,    -1,    -1,   146,    -1,    95,    -1,   146,    61,    95,
      -1,    -1,   147,    81,   145,    82,    -1,   147,    76,    95,
      83,    -1,     5,    -1,   148,    64,     5,    -1,    -1,   148,
      64,     5,    81,   145,    82,   150,   147,    -1,   148,    64,
      53,    -1,   148,    64,     5,    -1,   148,    64,     4,    70,
      53,    -1,   148,    64,     4,    70,    47,    -1,   148,    64,
       4,    70,    47,    81,   145,    82,    -1,    -1,   148,    64,
       4,    70,     5,    81,   145,    82,   151,   122,    -1,    -1,
       5,    81,   145,    82,   153,   147,    -1,    38,    95,    -1,
      38,    -1,    10,    81,    95,    82,    89,    -1,    -1,   134,
      -1,   146,    -1,    -1,    95,    -1,   145,    -1,     9,    81,
     156,    80,   157,    80,   158,    82,    89,    -1,     9,    81,
       3,     5,    60,    95,    82,    89,    -1,    -1,   160,    13,
      81,    95,    82,    89,    -1,    -1,    12,    89,    -1,    -1,
      -1,    11,    81,    95,    82,    89,   163,   160,   164,   161,
      -1
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
     261,   262,   264,   266,   269,   274,   279,   283,   289,   295,
     299,   303,   309,   313,   317,   320,   322,   324,   327,   333,
     334,   337,   342,   346,   350,   354,   358,   362,   366,   370,
     374,   375,   382,   386,   390,   391,   400,   401,   410,   411,
     420,   421,   430,   433,   436,   439,   442,   445,   448,   451,
     454,   457,   460,   463,   466,   470,   474,   478,   482,   486,
     490,   494,   498,   502,   506,   510,   514,   518,   522,   526,
     530,   534,   538,   542,   546,   550,   554,   558,   562,   566,
     570,   574,   578,   582,   586,   589,   592,   594,   598,   602,
     604,   606,   610,   614,   618,   620,   624,   629,   634,   639,
     644,   647,   652,   658,   664,   671,   678,   685,   692,   699,
     708,   717,   722,   728,   734,   742,   743,   745,   747,   751,
     752,   757,   762,   764,   768,   769,   778,   782,   786,   792,
     798,   807,   808,   819,   820,   827,   830,   832,   838,   839,
     841,   843,   844,   846,   848,   858,   867,   868,   875,   876,
     879,   880,   881
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   223,   223,   223,   227,   228,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   258,
     262,   263,   267,   271,   275,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   318,   319,   320,   324,   328,   328,   332,   333,
     334,   335,   336,   337,   341,   342,   343,   344,   348,   349,
     350,   351,   355,   359,   360,   361,   362,   363,   364,   365,
     366,   370,   371,   375,   376,   380,   381,   385,   389,   390,
     394,   395,   396,   400,   401,   402,   403,   404,   405,   409,
     413,   414,   418,   419,   423,   427,   431,   432,   436,   440,
     441,   445,   449,   450,   451,   452,   453,   454,   455,   456,
     460,   461,   462,   463,   467,   467,   468,   468,   469,   469,
     470,   470,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   489,   490,   491,   492,   493,   494,
     498,   499,   503,   504,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   534,   535,   539,   540,   544,   545,
     549,   550,   554,   558,   562,   563,   567,   568,   569,   570,
     571,   575,   579,   581,   583,   585,   587,   589,   591,   593,
     595,   600,   602,   604,   606,   611,   612,   616,   617,   621,
     622,   623,   627,   628,   632,   632,   633,   634,   635,   636,
     637,   638,   638,   642,   642,   646,   647,   651,   655,   656,
     657,   661,   662,   666,   670,   671,   674,   676,   680,   681,
     685,   685,   685
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
  const int Parser::yylast_ = 1342;
  const int Parser::yynnts_ = 81;
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

