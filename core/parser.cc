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

    { (yyval.node) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc);   }
    break;

  case 238:

    { (yyval.node) = new ast::DoWhile((yysemantic_stack_[(7) - (5)].node), (yysemantic_stack_[(7) - (2)].block), yyloc); }
    break;

  case 239:

    { (yyval.narray) = NULL; }
    break;

  case 242:

    { (yyval.node) = NULL;     }
    break;

  case 243:

    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); }
    break;

  case 245:

    { (yyval.for_loop) = new ast::For((yysemantic_stack_[(9) - (3)].narray), (yysemantic_stack_[(9) - (5)].node), (yysemantic_stack_[(9) - (7)].narray), (yysemantic_stack_[(9) - (9)].block), yyloc); }
    break;

  case 246:

    {	(yyval.foreach_loop) = new ast::ForEach(new ast::VariableDecl((yysemantic_stack_[(8) - (4)].ident), new ast::Assignment((yysemantic_stack_[(8) - (4)].ident), NULL, yyloc), false, yyloc), (yysemantic_stack_[(8) - (6)].node), (yysemantic_stack_[(8) - (8)].block), yyloc); }
    break;

  case 248:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 249:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 250:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 251:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 252:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 253:

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
  const short int Parser::yypact_ninf_ = -377;
  const short int
  Parser::yypact_[] =
  {
      -377,    52,  -377,  -377,   640,    57,    13,   396,  -377,  -377,
    -377,   -18,     9,    11,  -377,    93,   334,  -377,  -377,    70,
      19,    27,    10,    10,  -377,    27,   334,  -377,  -377,   201,
     133,    27,   334,   334,   334,   334,   334,    31,   334,  -377,
    -377,   135,   145,   158,  -377,   130,  1037,   597,  1252,  -377,
    -377,  -377,  -377,  -377,   168,  -377,  1290,   180,   187,  -377,
    -377,  -377,   191,   195,   196,   209,   210,  -377,  -377,   162,
     219,   220,   222,  -377,  -377,  -377,   174,   212,  -377,    63,
     334,   189,   334,   334,  -377,   186,   207,    31,  -377,  1037,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,   241,   244,  -377,
     225,   226,   306,    14,  -377,  -377,   240,    -2,   243,   238,
     183,   185,   243,   183,   185,   269,  1037,   242,   334,   313,
    -377,  -377,  -377,  -377,  1037,   248,   262,   260,   249,   560,
     146,   730,  -377,  -377,  -377,  -377,  -377,    30,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
    -377,  -377,    54,  -377,  -377,  -377,    55,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,    53,  -377,  -377,  -377,   334,    57,
     251,   252,  -377,   254,   330,  -377,   262,   263,   791,   812,
      28,    22,   334,    70,    16,    21,   264,   177,    27,    -7,
     268,    64,    65,    66,    67,   265,   297,   269,  -377,   121,
     873,   273,  -377,   334,   334,  -377,  -377,   348,  -377,  -377,
     275,  -377,   113,   113,   113,   113,   214,   214,  1221,  1221,
    1131,  1058,  1099,  1119,  1160,  1192,  1232,   208,   208,  -377,
    -377,  -377,  1119,  1119,  1119,  1119,  1119,  1119,  1119,  1119,
    1119,  1119,  1119,   432,   276,  -377,   277,  -377,   289,   156,
    -377,  1037,  -377,   334,   334,  -377,   154,   334,    27,    27,
    -377,  -377,  -377,  -377,  -377,  1037,  -377,    27,    41,   278,
      27,   127,   279,   280,   293,  -377,   360,    27,    27,  -377,
    -377,  -377,  -377,   361,    27,  -377,  -377,  -377,  -377,   288,
      44,   125,   291,   334,  1037,  1037,   303,   334,  -377,   334,
     334,    68,   334,   287,   292,  -377,   334,  1037,   296,  -377,
    -377,  -377,   360,    27,    27,  -377,   360,    27,    27,    27,
     300,   298,  -377,  -377,   299,  -377,  -377,   367,   378,    33,
    -377,    48,  -377,   894,   334,   301,   302,   305,   304,   307,
    -377,   311,  -377,  -377,   193,   955,   334,  -377,   312,  -377,
    -377,   314,  -377,  -377,  -377,  -377,    27,    27,   327,   -14,
    -377,   336,   107,  -377,   367,   378,  -377,   112,   320,  1037,
    -377,  -377,  -377,   334,   334,  -377,  -377,   334,   334,    27,
    -377,   322,   393,    27,    27,  -377,  -377,   290,   367,  -377,
     290,   378,  -377,   137,   141,   239,   342,   153,  -377,  -377,
    -377,  -377,   325,   338,  -377,   356,   709,   345,  -377,    27,
     331,   417,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,   159,   365,
     369,   370,   371,   243,   366,   373,   198,  -377,   239,   375,
    -377,   356,   356,   356,  -377,  -377,   193,    69,  -377,  -377,
    -377,   334,    27,  -377,  -377,   640,   377,  -377,  -377,   372,
    -377,   976,  -377,   640,  -377,   640,   356,   334,    27,   640,
     368,  -377,  -377
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
       0,     0,     0,     0,     0,     0,   215,     4,     0,     5,
      17,    47,     0,     0,    18,    48,     0,     0,    49,    26,
      50,    23,    44,    43,     0,    22,    61,    59,    57,    55,
      54,    52,    51,    53,     0,    56,     0,    11,    58,     0,
      60,    46,     0,    14,    15,    13,   189,   184,   186,     0,
     215,   239,     0,     0,   194,   200,     0,     0,    47,   235,
      59,    57,    51,    53,    56,    60,    46,     0,   185,   190,
       0,     0,     0,     0,     4,    34,     0,    35,   144,     0,
     152,   148,   145,   153,   149,     0,   114,     0,     0,     0,
      78,    79,    80,    81,   217,     0,   216,     0,     0,     0,
       0,     0,    25,    20,    21,   142,   143,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     150,   151,     0,    19,   146,   147,     0,    10,    16,    27,
      28,     7,     8,     6,     0,    24,     9,    12,     0,     0,
     124,    30,   125,     0,     0,   240,   241,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   189,     0,     0,
       0,     0,     0,     0,     0,     0,   119,   115,   116,   100,
       0,     0,   109,     0,     0,   112,    29,     0,   113,    45,
     122,   123,   159,   157,   158,   156,   178,   177,   154,   155,
     160,   162,   161,   163,   175,   176,   174,   165,   164,   166,
     167,   168,   183,   182,   169,   171,   172,   170,   173,   179,
     180,   181,   193,     0,   128,   129,   126,   127,     0,   227,
     226,   188,   187,   215,   215,   233,   189,   242,     0,     0,
     199,   198,   197,   195,   196,   192,   191,     0,     0,     0,
       0,     0,     0,     0,     0,   211,     0,     0,     0,   124,
     122,   128,   126,     0,     0,   121,   117,   101,   102,     0,
       0,   100,     0,     0,   218,   110,     0,   215,    65,   215,
     215,     0,   215,     0,     0,   219,     0,   243,     0,   237,
     251,   203,     0,     0,     0,   202,     0,     0,     0,     0,
       0,     0,   213,   212,     0,   120,    82,     0,     0,     0,
     103,     0,    66,     0,     0,     0,     0,     0,     0,   229,
     228,     0,   138,    31,   234,     0,   215,   247,     0,   208,
     206,     0,   207,   205,   204,   201,     0,     0,    94,     0,
      91,     0,     0,    95,     0,     0,   106,     0,     0,   111,
     134,   140,   136,   215,   215,   224,   130,     0,   215,     0,
     244,     0,   252,     0,     0,   214,   118,     0,     0,   104,
       0,     0,   105,     0,     0,     0,     0,     0,   238,   130,
     130,   130,     0,     0,   219,   139,     0,     0,   246,     0,
       0,   249,   210,   209,    83,    86,    87,    85,    89,    90,
      88,    84,    93,    92,    97,    96,   107,   108,    35,    38,
      39,    37,    36,     0,    64,     0,    63,     4,     0,     0,
      67,   135,   141,   137,   231,   230,   225,     0,   221,   220,
     245,     0,     0,   253,     4,    75,     0,     4,   130,   132,
     133,     0,   250,    74,     4,    77,   232,   215,     0,    76,
       0,   248,   131
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -377,  -377,  -377,     0,  -377,    15,    -3,  -377,  -377,  -377,
     -19,    -4,   -17,   -15,  -377,  -377,    -5,  -377,  -377,  -377,
      58,    74,    75,    77,    59,  -377,   149,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,   258,  -377,  -377,   -13,  -376,    37,
    -377,  -377,  -377,  -377,    38,  -377,  -377,  -377,    49,    50,
     388,   -92,  -164,  -377,   285,    61,  -377,  -377,  -123,  -290,
    -377,   -67,   395,    71,  -377,    62,  -377,  -377,    73,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   129,    39,    40,    88,    42,    43,    44,
      45,   124,    47,    48,    49,   387,   455,   417,    50,    51,
     442,   379,   380,   382,   383,   309,   310,   311,    52,   130,
      53,    54,   216,   217,   218,   305,    55,    56,   425,    90,
     419,   421,   396,   420,    91,    59,    60,    61,    92,    93,
      64,    77,    78,    98,    99,    94,    85,    66,   210,    67,
      68,   125,   126,   364,    69,    95,   424,   478,    96,   325,
      72,    73,   197,   328,   401,    74,   402,   473,    75,   367,
     431
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -224;
  const short int
  Parser::yytable_[] =
  {
        46,    41,     4,   108,   112,   109,   109,   110,   113,   111,
     114,   209,    89,   193,   106,   107,     8,     9,    10,   207,
     350,   207,   116,   100,   101,   272,   207,   283,   120,   121,
     122,   123,   280,   281,   131,   230,   105,   100,   101,   127,
     115,    57,    58,   461,   462,   463,   119,   347,   408,    17,
      18,   384,     3,    62,    63,   296,    24,   268,   269,   264,
     266,   386,    76,    28,    81,    65,    70,   409,   190,   299,
     300,   301,   302,   358,   479,   -62,   297,    71,   198,   199,
      80,   289,   292,   231,    79,   348,   349,    36,    87,   385,
     349,    82,    38,    83,   284,   102,   128,   208,    84,   287,
     282,   103,   486,   332,   290,   104,   270,   265,   267,   102,
     191,   191,   288,   291,   220,   359,   192,   192,   231,   265,
     267,   360,   480,    97,   333,    46,    41,  -224,  -224,  -224,
    -224,   142,   272,   143,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,    57,    58,   272,   411,
     415,   416,   272,   341,   135,   136,   307,   308,    62,    63,
     307,   308,   153,   154,   271,   155,   156,   157,   412,   336,
      65,    70,   194,     6,     7,     8,     9,    10,   285,   408,
     -98,   137,    71,   411,   -99,   117,   323,   324,   227,   368,
     337,   458,   459,   371,   326,   118,   132,   188,   446,   314,
     315,  -223,   447,   295,   -68,   228,   133,   184,    17,    18,
      19,    86,   460,    22,    23,    24,   -62,   188,   322,   134,
     188,    80,    28,   106,   448,   449,   450,   451,   294,   173,
     355,   200,   356,   357,   213,   361,   214,   201,    32,    33,
     -64,   177,   -63,   -73,    34,    35,    36,    87,   178,   214,
     397,    38,   179,   327,   189,   398,   180,   181,    17,    18,
     155,   156,   157,   153,   154,    24,   155,   156,   157,   103,
     182,   183,   452,   329,   330,   434,   435,   436,   437,   400,
     185,   186,   331,   187,   202,   335,   203,   204,   205,   353,
     206,   211,   342,   343,   212,   169,    36,    87,   215,   345,
     219,    38,   365,   221,   223,   224,   422,   423,   225,   438,
     439,   427,   222,   273,   274,   276,   440,   275,     6,     7,
       8,     9,    10,   441,   277,   304,   293,   303,   369,   370,
     389,   298,   372,   373,   374,   313,   316,   317,   319,   320,
     321,   334,   338,   339,   340,   207,   344,   346,   354,   352,
     362,   375,   378,    17,    18,   363,    86,   366,    22,    23,
      24,   376,   377,   381,   390,   391,   393,    28,   392,   394,
     407,   405,   406,   426,   395,   403,   453,   404,   109,   410,
     454,   418,   456,    32,    33,   429,   430,   457,   464,    34,
      35,    36,    87,   471,   428,   -62,    38,   -62,   432,   433,
     490,   465,   -62,   -62,   -62,   -62,   -62,   467,   469,   472,
     -71,   -62,   -62,   -62,   -72,   -70,   -69,   213,   474,   453,
     477,   109,   484,   454,   470,   456,   138,   139,   140,   141,
     142,   492,   143,   476,   487,   144,   145,   475,   413,   -62,
     351,  -222,   414,   146,   147,   148,   149,   481,   444,   195,
     445,    46,    41,   -62,   483,   306,   196,   485,    80,    46,
      41,    46,    41,   443,   489,    46,    41,   482,   286,     0,
       0,     0,     0,     0,     0,   466,     0,     0,   150,   151,
     152,   153,   154,   491,   155,   156,   157,     0,     0,     0,
       0,     0,    57,    58,     0,     0,   318,     0,     0,     0,
      57,    58,    57,    58,    62,    63,    57,    58,     0,     0,
       0,     0,    62,    63,    62,    63,    65,    70,    62,    63,
       0,     0,     0,     0,    65,    70,    65,    70,    71,     0,
      65,    70,     0,     0,     0,     0,    71,     0,    71,     0,
       0,     0,    71,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,     0,     0,    15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,     0,     0,
      25,    26,    27,    28,    29,     0,   158,    30,   159,     0,
       0,    31,     0,   160,   161,   162,   163,   164,     0,    32,
      33,     0,   165,   166,   167,    34,    35,    36,    37,   226,
       0,     0,    38,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,     0,
     168,     0,    14,     0,     0,    15,     0,     0,     0,     0,
       0,     0,     0,     0,   169,     0,     0,     0,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,     0,     0,
      25,    26,    27,    28,    29,     0,     0,    30,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,     0,    32,
      33,     0,     0,     0,     0,    34,    35,    36,    37,     0,
       0,     0,    38,   138,   139,   140,   141,   142,     0,   143,
       0,     0,   144,   145,     0,     0,     0,     0,     0,     0,
     146,   147,   148,   149,   138,   139,   140,   141,   142,     0,
     143,     0,     0,   144,   145,     0,     0,     0,     0,     0,
       0,   146,   147,   148,   149,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,   151,   152,   153,   154,
       0,   155,   156,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   468,     0,     0,   150,   151,   152,   153,
     154,     0,   155,   156,   157,   138,   139,   140,   141,   142,
       0,   143,     0,   229,   144,   145,     0,     0,     0,     0,
       0,     0,   146,   147,   148,   149,   138,   139,   140,   141,
     142,     0,   143,     0,     0,   144,   145,     0,     0,     0,
       0,     0,     0,   146,   147,   148,   149,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   150,   151,   152,
     153,   154,     0,   155,   156,   157,     0,     0,     0,     0,
       0,     0,     0,     0,   278,     0,     0,     0,   150,   151,
     152,   153,   154,     0,   155,   156,   157,   138,   139,   140,
     141,   142,     0,   143,     0,   279,   144,   145,     0,     0,
       0,     0,     0,     0,   146,   147,   148,   149,   138,   139,
     140,   141,   142,     0,   143,     0,     0,   144,   145,     0,
       0,     0,     0,     0,     0,   146,   147,   148,   149,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
     151,   152,   153,   154,     0,   155,   156,   157,     0,     0,
       0,     0,     0,     0,     0,     0,   312,     0,     0,     0,
     150,   151,   152,   153,   154,     0,   155,   156,   157,   138,
     139,   140,   141,   142,     0,   143,     0,   388,   144,   145,
       0,     0,     0,     0,     0,     0,   146,   147,   148,   149,
     138,   139,   140,   141,   142,     0,   143,     0,     0,   144,
     145,     0,     0,     0,     0,     0,     0,   146,   147,   148,
     149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   150,   151,   152,   153,   154,     0,   155,   156,   157,
       0,     0,     0,     0,     0,     0,     0,     0,   399,     0,
       0,     0,   150,   151,   152,   153,   154,     0,   155,   156,
     157,   138,   139,   140,   141,   142,     0,   143,     0,   488,
     144,   145,     0,     0,     0,     0,     0,     0,   146,   147,
     148,   149,   138,   139,   140,   141,   142,     0,   143,     0,
       0,   144,   145,     0,     0,     0,     0,     0,     0,   146,
       0,   148,   149,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   151,   152,   153,   154,     0,   155,
     156,   157,     0,   138,   139,   140,   141,   142,     0,   143,
       0,     0,   144,   145,   150,   151,   152,   153,   154,     0,
     155,   156,   157,   138,   139,   140,   141,   142,     0,   143,
       0,     0,   144,   145,     0,   138,   139,   140,   141,   142,
     146,   143,   148,     0,   144,   145,     0,     0,     0,     0,
       0,     0,     0,     0,   148,   150,   151,   152,   153,   154,
       0,   155,   156,   157,   138,   139,   140,   141,   142,     0,
     143,     0,     0,   144,   145,   150,   151,   152,   153,   154,
       0,   155,   156,   157,     0,     0,     0,   150,   151,   152,
     153,   154,     0,   155,   156,   157,   138,   139,   140,   141,
     142,     0,   143,     0,     0,   144,   145,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   151,   152,   153,
     154,     0,   155,   156,   157,   138,   139,   140,   141,   142,
       0,   143,     0,     0,  -224,  -224,   138,   139,   140,   141,
     142,     0,   143,     0,     0,   144,   145,     0,     0,     0,
     152,   153,   154,     0,   155,   156,   157,     0,     0,     0,
       0,   -64,     0,   -64,     0,     0,     0,     0,   -64,   -64,
     -64,   -64,   -64,     0,     0,     0,     0,   -64,   -64,   -64,
     153,   154,     0,   155,   156,   157,   170,   171,     0,     0,
       0,   153,   154,     0,   155,   156,   157,     0,     0,   -63,
       0,   -63,     0,     0,     0,   -64,   -63,   -63,   -63,   -63,
     -63,     0,     0,   172,     0,   -63,   -63,   -63,     0,   -64,
       0,     0,     0,     0,   174,   175,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -63,     0,     0,     0,     0,     0,     0,
       0,   176,     0,     0,     0,     0,     0,   -63
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     2,    22,    23,    22,    23,    22,    23,    22,
      23,   103,    16,    80,     4,     5,     6,     7,     8,     5,
     310,     5,    26,     4,     5,   189,     5,     5,    32,    33,
      34,    35,     4,     5,    38,     5,    21,     4,     5,     8,
      25,     4,     4,   419,   420,   421,    31,     3,    62,    39,
      40,     3,     0,     4,     4,    62,    46,     4,     5,     5,
       5,   351,     5,    53,    82,     4,     4,    81,     5,     5,
       5,     5,     5,     5,     5,    77,    83,     4,    82,    83,
      82,   204,   205,    53,    71,    41,    42,    77,    78,    41,
      42,    82,    82,    82,    72,    76,    65,    83,     5,    83,
      72,    82,   478,    62,    83,    78,    53,    53,    53,    76,
      47,    47,   204,   205,   118,    47,    53,    53,    53,    53,
      53,    53,    53,    53,    83,   129,   129,    14,    15,    16,
      17,    18,   296,    20,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   129,   129,   332,    62,
      58,    59,   336,   296,    44,    45,    55,    56,   129,   129,
      55,    56,    69,    70,   188,    72,    73,    74,    81,    62,
     129,   129,     3,     4,     5,     6,     7,     8,   202,    62,
      79,    71,   129,    62,    79,     4,   273,   274,    62,   332,
      83,    58,    59,   336,    60,    82,    81,    63,    81,   223,
     224,    65,    81,   208,    65,    79,    81,    65,    39,    40,
      41,    42,    79,    44,    45,    46,    77,    63,    82,    81,
      63,    82,    53,     4,     5,     6,     7,     8,    71,    81,
     317,    65,   319,   320,    71,   322,    71,    71,    69,    70,
      77,    81,    77,    65,    75,    76,    77,    78,    81,    71,
      77,    82,    81,   277,    62,    82,    81,    81,    39,    40,
      72,    73,    74,    69,    70,    46,    72,    73,    74,    82,
      81,    81,    53,   278,   279,     5,     6,     7,     8,   366,
      81,    81,   287,    81,    63,   290,    62,    82,    82,   313,
       4,    71,   297,   298,    71,    77,    77,    78,    49,   304,
      78,    82,   326,    10,    62,    65,   393,   394,    79,    39,
      40,   398,    84,    82,    82,     5,    46,    83,     4,     5,
       6,     7,     8,    53,    81,    48,    82,    82,   333,   334,
     354,    83,   337,   338,   339,    82,     8,    82,    82,    82,
      71,    83,    83,    83,    71,     5,     5,    79,    65,    78,
      83,    71,     5,    39,    40,    83,    42,    81,    44,    45,
      46,    83,    83,     5,    83,    83,    82,    53,    83,    82,
      63,   376,   377,   397,    83,    83,   415,    83,   415,    63,
     415,    81,   415,    69,    70,    83,    13,    65,    83,    75,
      76,    77,    78,    82,   399,    19,    82,    21,   403,   404,
     487,    83,    26,    27,    28,    29,    30,    71,    83,    12,
      65,    35,    36,    37,    65,    65,    65,    71,    65,   458,
      65,   458,    65,   458,   429,   458,    14,    15,    16,    17,
      18,    83,    20,   458,    82,    23,    24,   457,   384,    63,
     311,    65,   385,    31,    32,    33,    34,   471,   410,    81,
     411,   475,   475,    77,   474,   217,    81,   477,    82,   483,
     483,   485,   485,   408,   484,   489,   489,   472,   203,    -1,
      -1,    -1,    -1,    -1,    -1,   424,    -1,    -1,    66,    67,
      68,    69,    70,   488,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,   475,   475,    -1,    -1,    84,    -1,    -1,    -1,
     483,   483,   485,   485,   475,   475,   489,   489,    -1,    -1,
      -1,    -1,   483,   483,   485,   485,   475,   475,   489,   489,
      -1,    -1,    -1,    -1,   483,   483,   485,   485,   475,    -1,
     489,   489,    -1,    -1,    -1,    -1,   483,    -1,   485,    -1,
      -1,    -1,   489,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    22,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    -1,    19,    57,    21,    -1,
      -1,    61,    -1,    26,    27,    28,    29,    30,    -1,    69,
      70,    -1,    35,    36,    37,    75,    76,    77,    78,    79,
      -1,    -1,    82,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    22,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    -1,    -1,    57,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      70,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    -1,
      -1,    -1,    82,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    66,    67,    68,    69,
      70,    -1,    72,    73,    74,    14,    15,    16,    17,    18,
      -1,    20,    -1,    83,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    -1,    72,    73,    74,    14,    15,    16,
      17,    18,    -1,    20,    -1,    83,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    -1,    72,    73,    74,    14,
      15,    16,    17,    18,    -1,    20,    -1,    83,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    -1,    72,    73,
      74,    14,    15,    16,    17,    18,    -1,    20,    -1,    83,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,    72,
      73,    74,    -1,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    66,    67,    68,    69,    70,    -1,
      72,    73,    74,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    -1,    14,    15,    16,    17,    18,
      31,    20,    33,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    66,    67,    68,    69,    70,
      -1,    72,    73,    74,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    66,    67,    68,    69,    70,
      -1,    72,    73,    74,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    -1,    72,    73,    74,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    -1,    72,    73,    74,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,
      68,    69,    70,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    19,    -1,    21,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    35,    36,    37,
      69,    70,    -1,    72,    73,    74,    44,    45,    -1,    -1,
      -1,    69,    70,    -1,    72,    73,    74,    -1,    -1,    19,
      -1,    21,    -1,    -1,    -1,    63,    26,    27,    28,    29,
      30,    -1,    -1,    71,    -1,    35,    36,    37,    -1,    77,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    -1,    -1,    -1,    -1,    -1,    77
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    86,    87,     0,    88,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    22,    25,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    50,    51,    52,    53,    54,
      57,    61,    69,    70,    75,    76,    77,    78,    82,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     103,   104,   113,   115,   116,   121,   122,   124,   129,   130,
     131,   132,   133,   134,   135,   140,   142,   144,   145,   149,
     150,   153,   155,   156,   160,   163,     5,   136,   137,    71,
      82,    82,    82,    82,     5,   141,    42,    78,    91,    96,
     124,   129,   133,   134,   140,   150,   153,    53,   138,   139,
       4,     5,    76,    82,    78,    90,     4,     5,    95,    97,
      98,   122,    95,    98,   122,    90,    96,     4,    82,    90,
      96,    96,    96,    96,    96,   146,   147,     8,    65,    88,
     114,    96,    81,    81,    81,    44,    45,    71,    14,    15,
      16,    17,    18,    20,    23,    24,    31,    32,    33,    34,
      66,    67,    68,    69,    70,    72,    73,    74,    19,    21,
      26,    27,    28,    29,    30,    35,    36,    37,    63,    77,
      44,    45,    71,    81,    44,    45,    71,    81,    81,    81,
      81,    81,    81,    81,    65,    81,    81,    81,    63,    62,
       5,    47,    53,   146,     3,   135,   147,   157,    96,    96,
      65,    71,    63,    62,    82,    82,     4,     5,    83,   136,
     143,    71,    71,    71,    71,    49,   117,   118,   119,    78,
      96,    10,    84,    62,    65,    79,    79,    62,    79,    83,
       5,    53,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,     5,    53,     5,    53,     4,     5,
      53,    96,   137,    82,    82,    83,     5,    81,    83,    83,
       4,     5,    72,     5,    72,    96,   139,    83,   136,   143,
      83,   136,   143,    82,    71,    90,    62,    83,    83,     5,
       5,     5,     5,    82,    48,   120,   119,    55,    56,   110,
     111,   112,    83,    82,    96,    96,     8,    82,    84,    82,
      82,    71,    82,   146,   146,   154,    60,    96,   158,    90,
      90,    90,    62,    83,    83,    90,    62,    83,    83,    83,
      71,   143,    90,    90,     5,    90,    79,     3,    41,    42,
     144,   111,    78,    96,    65,   146,   146,   146,     5,    47,
      53,   146,    83,    83,   148,    96,    81,   164,   143,    90,
      90,   143,    90,    90,    90,    71,    83,    83,     5,   106,
     107,     5,   108,   109,     3,    41,   144,   100,    83,    96,
      83,    83,    83,    82,    82,    83,   127,    77,    82,    83,
     146,   159,   161,    83,    83,    90,    90,    63,    62,    81,
      63,    62,    81,   106,   108,    58,    59,   102,    81,   125,
     128,   126,   146,   146,   151,   123,    96,   146,    90,    83,
      13,   165,    90,    90,     5,     6,     7,     8,    39,    40,
      46,    53,   105,   107,   105,   109,    81,    81,     5,     6,
       7,     8,    53,    95,    98,   101,   122,    65,    58,    59,
      79,   123,   123,   123,    83,    83,   148,    71,    84,    83,
      90,    82,    12,   162,    65,    88,   101,    65,   152,     5,
      53,    96,    90,    88,    65,    88,   123,    82,    83,    88,
     146,    90,    83
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
     315,   316,    44,    61,   317,    58,   124,    94,    38,    45,
      43,    46,    42,    47,    37,    33,   126,    91,   123,   125,
     318,    59,    40,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    85,    87,    86,    88,    88,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    90,
      91,    91,    92,    93,    94,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    97,    97,    97,    98,   100,    99,   101,   101,
     101,   101,   101,   101,   102,   102,   102,   102,   103,   103,
     103,   103,   104,   105,   105,   105,   105,   105,   105,   105,
     105,   106,   106,   107,   107,   108,   108,   109,   110,   110,
     111,   111,   111,   112,   112,   112,   112,   112,   112,   113,
     114,   114,   115,   115,   116,   117,   118,   118,   119,   120,
     120,   121,   122,   122,   122,   122,   122,   122,   122,   122,
     123,   123,   123,   123,   125,   124,   126,   124,   127,   124,
     128,   124,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   130,   130,   130,   130,   130,   130,
     131,   131,   132,   132,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   135,   135,   136,   136,   137,   137,
     138,   138,   139,   140,   141,   141,   142,   142,   142,   142,
     142,   143,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   145,   145,   145,   145,   146,   146,   147,   147,   148,
     148,   148,   149,   149,   151,   150,   150,   150,   150,   150,
     150,   152,   150,   154,   153,   155,   155,   156,   156,   157,
     157,   157,   158,   158,   159,   160,   160,   161,   161,   162,
     162,   164,   165,   163
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
       8,     0,    10,     0,     6,     2,     1,     5,     7,     0,
       1,     1,     0,     1,     1,     9,     8,     0,     6,     0,
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
  "\"critical\"", "\"++\"", "\"--\"", "\"null\"", "\"new\"", "\"finally\"",
  "\"catch\"", "\"try\"", "\"throw\"", "\"continue\"",
  "\"constant identifier\"", "\"class\"", "\"public\"", "\"private\"",
  "\"switch\"", "\"case\"", "\"default\"", "\"in\"", "\"do\"", "','",
  "'='", "XOR_EQUAL", "':'", "'|'", "'^'", "'&'", "'-'", "'+'", "'.'",
  "'*'", "'/'", "'%'", "'!'", "'~'", "'['", "'{'", "'}'", "UMINUS", "';'",
  "'('", "')'", "']'", "$accept", "program", "$@1", "statement_list",
  "statement", "block", "instantiation", "break", "continue",
  "critical_block", "object", "rvalue", "lvalue", "subscript",
  "switch_expr", "@2", "label", "case_list", "unary", "class_def",
  "attr_rvalue", "class_attr_decl_list", "class_attr_decl_impl",
  "class_attr_const_decl_list", "class_attr_const_decl_impl",
  "class_member_decl", "visibility", "class_member_list", "array",
  "key_value_list", "map", "throw", "catch", "not_empty_catch",
  "catch_impl", "finally", "try_catch_finally", "property_access",
  "mcall_chain", "mcall", "@3", "@4", "@5", "@6", "inc_dec", "comparison",
  "boolean", "logic", "arithmetic", "bitwise", "variable_decl",
  "variable_decl_list", "variable_decl_impl", "const_decl_list",
  "const_decl_impl", "assignment", "import_ident_list", "import", "vararg",
  "fdecl", "anonymous_fdecl", "call_args", "non_empty_call_args",
  "fcall_chain", "fully_qualified_name", "fully_qualified_call", "@7",
  "@8", "fcall", "@9", "return_stmt", "while", "for_expr_1", "for_expr_2",
  "for_expr_3", "for", "elseif", "else", "if", "@10", "@11", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        86,     0,    -1,    -1,    87,    88,    -1,    -1,    88,    89,
      -1,   142,    81,    -1,   135,    81,    -1,   140,    81,    -1,
     153,    81,    -1,   124,    81,    -1,   144,    -1,   155,    81,
      -1,   163,    -1,   156,    -1,   160,    -1,   129,    81,    -1,
      90,    -1,    94,    -1,   116,    81,    -1,    92,    81,    -1,
      93,    81,    -1,   121,    -1,   104,    -1,   150,    81,    -1,
      91,    81,    -1,    99,    -1,   133,    81,    -1,   134,    81,
      -1,    78,    88,    79,    -1,     4,    71,    47,    -1,     4,
      71,    47,    82,   146,    83,    -1,    22,    -1,    52,    -1,
      43,    90,    -1,     5,    -1,    53,    -1,     8,    -1,     6,
      -1,     7,    -1,    46,    -1,    39,    -1,    40,    -1,   115,
      -1,   113,    -1,    82,    96,    83,    -1,   153,    -1,    91,
      -1,    95,    -1,    98,    -1,   103,    -1,   133,    -1,   132,
      -1,   134,    -1,   131,    -1,   130,    -1,   140,    -1,   129,
      -1,   145,    -1,   124,    -1,   150,    -1,   122,    -1,     5,
      -1,   122,    -1,    98,    -1,    97,    77,    96,    84,    -1,
      -1,    57,    82,    96,    83,    78,   100,   102,    79,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
     122,    -1,    58,   101,    65,    88,    -1,    59,    65,    88,
      -1,   102,    58,   101,    65,    88,    -1,   102,    59,    65,
      88,    -1,    69,    96,    -1,    70,    96,    -1,    75,    96,
      -1,    76,    96,    -1,    54,     4,    78,   110,    79,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
      46,    -1,    39,    -1,    40,    -1,   107,    -1,   106,    62,
     107,    -1,     5,    63,   105,    -1,     5,    -1,   109,    -1,
     108,    62,   109,    -1,     5,    63,   105,    -1,    -1,   112,
      -1,    -1,    55,    -1,    56,    -1,   111,   144,    -1,   111,
       3,   106,    81,    -1,   111,    41,   108,    81,    -1,   112,
     111,   144,    -1,   112,   111,     3,   106,    81,    -1,   112,
     111,    41,   108,    81,    -1,    77,   146,    84,    -1,     8,
      65,    96,    -1,   114,    62,     8,    65,    96,    -1,    78,
      65,    79,    -1,    78,   114,    79,    -1,    51,    96,    -1,
     118,    -1,   119,    -1,   118,   119,    -1,    49,    82,     5,
      83,    90,    -1,    -1,    48,    90,    -1,    50,    90,   117,
     120,    -1,    95,    71,     5,    -1,    95,    71,    53,    -1,
       4,    71,     5,    -1,     4,    71,    53,    -1,   122,    71,
       5,    -1,   122,    71,    53,    -1,    98,    71,     5,    -1,
      98,    71,    53,    -1,    -1,   123,    71,     5,    82,   146,
      83,    -1,   123,    71,     5,    -1,   123,    71,    53,    -1,
      -1,    95,    71,     5,    82,   146,    83,   125,   123,    -1,
      -1,   122,    71,     5,    82,   146,    83,   126,   123,    -1,
      -1,     4,    71,     5,    82,   146,    83,   127,   123,    -1,
      -1,    98,    71,     5,    82,   146,    83,   128,   123,    -1,
      95,    44,    -1,    95,    45,    -1,    44,    95,    -1,    45,
      95,    -1,   122,    44,    -1,   122,    45,    -1,    44,   122,
      -1,    45,   122,    -1,    98,    44,    -1,    98,    45,    -1,
      44,    98,    -1,    45,    98,    -1,    96,    23,    96,    -1,
      96,    24,    96,    -1,    96,    17,    96,    -1,    96,    15,
      96,    -1,    96,    16,    96,    -1,    96,    14,    96,    -1,
      96,    31,    96,    -1,    96,    33,    96,    -1,    96,    32,
      96,    -1,    96,    34,    96,    -1,    96,    70,    96,    -1,
      96,    69,    96,    -1,    96,    72,    96,    -1,    96,    73,
      96,    -1,    96,    74,    96,    -1,    97,    26,    96,    -1,
      97,    29,    96,    -1,    97,    27,    96,    -1,    97,    28,
      96,    -1,    97,    30,    96,    -1,    96,    68,    96,    -1,
      96,    66,    96,    -1,    96,    67,    96,    -1,    96,    20,
      96,    -1,    96,    18,    96,    -1,    97,    35,    96,    -1,
      97,    36,    96,    -1,    97,    37,    96,    -1,    97,    21,
      96,    -1,    97,    19,    96,    -1,     3,   136,    -1,    41,
     138,    -1,   137,    -1,   136,    62,   137,    -1,     5,    63,
      96,    -1,     5,    -1,   139,    -1,   138,    62,   139,    -1,
      53,    63,    96,    -1,    97,    63,    96,    -1,     5,    -1,
     141,    71,     5,    -1,    25,   141,    71,    72,    -1,    25,
     141,    65,    72,    -1,    25,   141,    65,     5,    -1,    25,
     141,    65,     4,    -1,    25,   141,    -1,     5,    71,    71,
      71,    -1,    42,     5,    82,    83,    90,    -1,    42,     4,
      82,    83,    90,    -1,    42,    76,     4,    82,    83,    90,
      -1,    42,     5,    82,   143,    83,    90,    -1,    42,     4,
      82,   143,    83,    90,    -1,    42,     5,    82,   136,    83,
      90,    -1,    42,     4,    82,   136,    83,    90,    -1,    42,
       5,    82,   136,    62,   143,    83,    90,    -1,    42,     4,
      82,   136,    62,   143,    83,    90,    -1,    42,    82,    83,
      90,    -1,    42,    82,   143,    83,    90,    -1,    42,    82,
     136,    83,    90,    -1,    42,    82,   136,    62,   143,    83,
      90,    -1,    -1,   147,    -1,    96,    -1,   147,    62,    96,
      -1,    -1,   148,    82,   146,    83,    -1,   148,    77,    96,
      84,    -1,     5,    -1,   149,    65,     5,    -1,    -1,   149,
      65,     5,    82,   146,    83,   151,   148,    -1,   149,    65,
      53,    -1,   149,    65,     5,    -1,   149,    65,     4,    71,
      53,    -1,   149,    65,     4,    71,    47,    -1,   149,    65,
       4,    71,    47,    82,   146,    83,    -1,    -1,   149,    65,
       4,    71,     5,    82,   146,    83,   152,   123,    -1,    -1,
       5,    82,   146,    83,   154,   148,    -1,    38,    96,    -1,
      38,    -1,    10,    82,    96,    83,    90,    -1,    61,    90,
      10,    82,    96,    83,    81,    -1,    -1,   135,    -1,   147,
      -1,    -1,    96,    -1,   146,    -1,     9,    82,   157,    81,
     158,    81,   159,    83,    90,    -1,     9,    82,     3,     5,
      60,    96,    83,    90,    -1,    -1,   161,    13,    82,    96,
      83,    90,    -1,    -1,    12,    90,    -1,    -1,    -1,    11,
      82,    96,    83,    90,   164,   161,   165,   162,    -1
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
     798,   807,   808,   819,   820,   827,   830,   832,   838,   846,
     847,   849,   851,   852,   854,   856,   866,   875,   876,   883,
     884,   887,   888,   889
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
     637,   638,   638,   642,   642,   646,   647,   651,   652,   656,
     657,   658,   662,   663,   667,   671,   672,   675,   677,   681,
     682,   686,   686,   686
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
       2,     2,     2,    75,     2,     2,     2,    74,    68,     2,
      82,    83,    72,    70,    62,    69,    71,    73,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    65,    81,
       2,    63,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    77,     2,    84,    67,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    78,    66,    79,    76,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    64,    80
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 1367;
  const int Parser::yynnts_ = 81;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 3;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 85;

  const unsigned int Parser::yyuser_token_number_max_ = 318;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} // clever





namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever

