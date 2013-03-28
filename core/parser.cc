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

    { (yyval.mcall) = (yysemantic_stack_[(0) - (0)].mcall); }
    break;

  case 129:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (0)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 130:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 131:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); (yyval.property)->setStatic(); }
    break;

  case 132:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 133:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 134:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 135:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 136:

    { (yyval.node) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 137:

    { (yyval.node) = (yysemantic_stack_[(8) - (8)].node); }
    break;

  case 138:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 139:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 140:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 141:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 142:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].property)->setWriteMode(); }
    break;

  case 143:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); (yysemantic_stack_[(2) - (1)].property)->setWriteMode(); }
    break;

  case 144:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].property)->setWriteMode(); }
    break;

  case 145:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); (yysemantic_stack_[(2) - (2)].property)->setWriteMode(); }
    break;

  case 146:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 147:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 148:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 149:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 150:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 151:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 152:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 153:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 154:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 155:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 156:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 157:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 158:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 159:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 160:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 161:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 162:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 163:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 164:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 165:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 166:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 167:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR,     (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 168:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 169:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 170:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 171:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 172:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR,     (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 173:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 174:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 175:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc, true); }
    break;

  case 176:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 177:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 178:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 179:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 180:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 181:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 182:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 183:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 184:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 185:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 186:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 187:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 188:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 189:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 190:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 191:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 192:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(2) - (2)].ident), yyloc); (yyval.import)->setNamespaced(true); }
    break;

  case 193:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 194:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 195:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 196:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (3)].type), NULL, (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setDtor(); }
    break;

  case 197:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 198:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 199:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 200:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 201:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 202:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); (yyval.fdecl)->setCtor(); }
    break;

  case 203:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 204:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 205:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 206:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 207:

    { (yyval.narray) = NULL; }
    break;

  case 209:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 210:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 211:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 212:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 213:

    { (yyval.node) = new ast::Subscript((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].node), yyloc); }
    break;

  case 215:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 216:

    { (yysemantic_stack_[(6) - (1)].ident)->append(':', (yysemantic_stack_[(6) - (3)].ident)); (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(6) - (1)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 217:

    { (yyval.fcall) = (yysemantic_stack_[(8) - (8)].fcall); }
    break;

  case 218:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 219:

    { (yysemantic_stack_[(3) - (1)].ident)->append(':', (yysemantic_stack_[(3) - (3)].ident)); }
    break;

  case 220:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.property) = new ast::Property(new ast::Type((yysemantic_stack_[(5) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(5) - (5)].ident), yyloc); clever_delete((yysemantic_stack_[(5) - (1)].ident)); }
    break;

  case 221:

    { (yysemantic_stack_[(5) - (1)].ident)->append(':', (yysemantic_stack_[(5) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(5) - (1)].ident), NULL, yyloc); }
    break;

  case 222:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.inst) = new ast::Instantiation((yysemantic_stack_[(8) - (1)].ident), (yysemantic_stack_[(8) - (7)].narray),   yyloc); }
    break;

  case 223:

    { (yysemantic_stack_[(8) - (1)].ident)->append(':', (yysemantic_stack_[(8) - (3)].type)); (yyval.mcall) = new ast::MethodCall(new ast::Type((yysemantic_stack_[(8) - (1)].ident)->getName(), yyloc), (yysemantic_stack_[(8) - (5)].ident), (yysemantic_stack_[(8) - (7)].narray), yyloc); clever_delete((yysemantic_stack_[(8) - (1)].ident)); }
    break;

  case 224:

    { (yyval.node) = (yysemantic_stack_[(10) - (10)].node); }
    break;

  case 225:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 226:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 227:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 228:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 229:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 230:

    { (yyval.narray) = NULL; }
    break;

  case 233:

    { (yyval.node) = NULL;     }
    break;

  case 234:

    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); }
    break;

  case 236:

    { (yyval.for_loop) = new ast::For((yysemantic_stack_[(9) - (3)].narray), (yysemantic_stack_[(9) - (5)].node), (yysemantic_stack_[(9) - (7)].narray), (yysemantic_stack_[(9) - (9)].block), yyloc); }
    break;

  case 237:

    {
			/* Calls rvalue.begin() */
			ast::MethodCall* tmp = new ast::MethodCall((yysemantic_stack_[(7) - (5)].node), new ast::Ident(CSTRING("begin"), yyloc), NULL, yyloc);
			/* var IDENT = rvalue.begin() */
			ast::VariableDecl* init = new ast::VariableDecl((yysemantic_stack_[(7) - (3)].ident), new ast::Assignment((yysemantic_stack_[(7) - (3)].ident), tmp, yyloc), false, yyloc);
			/* Calls rvalue.end() */
			tmp = new ast::MethodCall((yysemantic_stack_[(7) - (5)].node), new ast::Ident(CSTRING("end"), yyloc), NULL, yyloc);
			/* Compares IDENT != rvalue.end() */
			ast::Comparison* comp = new ast::Comparison(ast::Comparison::COP_NEQUAL, (yysemantic_stack_[(7) - (3)].ident), tmp, yyloc);
			/* Gets the iterator for the next value (IDENT.next()) */
			tmp = new ast::MethodCall((yysemantic_stack_[(7) - (3)].ident), new ast::Ident(CSTRING("next"), yyloc), NULL, yyloc);
			/* Assigns (IDENT = IDENT.next()) */
			ast::Assignment* assign = new ast::Assignment((yysemantic_stack_[(7) - (3)].ident), tmp, yyloc);

			ast::NodeArray* init_list = new ast::NodeArray(yyloc);
			init_list->append(init);

			ast::NodeArray* assign_list = new ast::NodeArray(yyloc);
			assign_list->append(assign);

			(yyval.for_loop) = new ast::For(init_list, comp, assign_list, (yysemantic_stack_[(7) - (7)].block), yyloc);
		}
    break;

  case 239:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 240:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 241:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 242:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 243:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 244:

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
  const short int Parser::yypact_ninf_ = -363;
  const short int
  Parser::yypact_[] =
  {
      -363,    52,  -363,  -363,   620,    40,   138,  1001,  -363,  -363,
    -363,   -26,   131,   139,  -363,   114,   674,  -363,  -363,   173,
      19,   151,    10,    10,  -363,   151,   674,  -363,  -363,   244,
     177,   674,   674,   674,   674,   674,    26,   674,  -363,  -363,
     174,   197,   204,  -363,   149,  1055,   358,   709,  -363,  -363,
    -363,  -363,  -363,   218,  -363,  1230,   219,   225,  -363,  -363,
    -363,   234,   235,   238,   240,   242,  -363,  -363,   205,   243,
     245,   252,  -363,  -363,  -363,   262,   272,  -363,    57,   674,
     323,   674,   674,  -363,    33,   253,    26,  -363,  1055,  -363,
    -363,  -363,  -363,  -363,  -363,  -363,   274,   277,  -363,   258,
     259,   282,     6,  -363,  -363,   271,   200,   273,   266,   130,
     273,   130,   295,  1055,   268,   674,  -363,  -363,  -363,  -363,
    1055,   263,   289,   283,   278,   541,   -21,   763,  -363,  -363,
    -363,  -363,  -363,    46,   674,   674,   674,   674,   674,   674,
     674,   674,   674,   674,   674,   674,   674,   674,   674,   674,
     674,   674,   674,   674,   674,   674,   674,   674,   674,   674,
     674,   674,   674,   674,   674,   674,  -363,  -363,  -363,    54,
    -363,  -363,  -363,  -363,  -363,  -363,  -363,    42,  -363,  -363,
    -363,   674,    40,   279,   280,  -363,   284,   206,  -363,   289,
     290,   823,   844,    21,    30,   674,   173,    14,    16,   291,
     126,   151,   -24,   299,   160,    55,    64,   302,   341,   295,
    -363,   143,   904,  -363,   674,   674,  -363,  -363,   363,  -363,
    -363,   309,  -363,    98,    98,    98,    98,   221,   221,  1175,
    1175,   286,  1076,  1115,  1136,  1148,    56,  1208,   224,   224,
    -363,  -363,  -363,  1136,  1136,  1136,  1136,  1136,  1136,  1136,
    1136,  1136,  1136,  1136,   408,   320,  -363,   332,    45,  -363,
    1055,  -363,   674,   674,  -363,   674,   674,   151,   151,  -363,
    -363,  -363,  -363,  -363,  1055,  -363,   151,   -18,   321,   151,
       7,   324,   325,   338,  -363,   404,   151,   151,  -363,  -363,
    -363,   405,   151,  -363,  -363,  -363,  -363,   333,    41,   195,
     335,  1055,  1055,   349,   674,  -363,   674,   171,   674,   334,
     336,  -363,   925,  1055,   347,  -363,  -363,  -363,   404,   151,
     151,  -363,   404,   151,   151,   151,   344,   348,  -363,  -363,
     351,  -363,  -363,   410,   424,    27,  -363,   189,  -363,   674,
     354,   356,   362,   364,  -363,   365,  -363,  -363,   207,   151,
     674,  -363,   368,  -363,  -363,   370,  -363,  -363,  -363,  -363,
     151,   151,   384,   -13,  -363,   393,   134,  -363,   410,   424,
    -363,   120,  1055,  -363,  -363,   674,   674,  -363,  -363,   674,
     674,  -363,  -363,   378,   451,   151,   151,  -363,  -363,   232,
     410,  -363,   232,   424,  -363,   183,   185,   176,   401,   201,
    -363,  -363,   385,   386,  -363,   396,   742,   387,   151,   389,
     459,  -363,  -363,  -363,  -363,  -363,  -363,  -363,  -363,  -363,
    -363,  -363,  -363,  -363,  -363,  -363,  -363,   109,   414,   418,
     419,   420,   273,   421,   153,  -363,   176,   422,  -363,   396,
     396,  -363,  -363,   207,   115,  -363,  -363,  -363,   674,   151,
    -363,  -363,   620,   423,  -363,  -363,   391,  -363,   985,  -363,
     620,  -363,   620,   396,   674,   151,   620,   406,  -363,  -363
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    35,    38,    39,
      37,     0,     0,     0,    32,     0,   228,    41,    42,     0,
       0,     0,     0,     0,    40,     0,     0,    33,    36,     0,
       0,     0,     0,     0,     0,   207,     4,     0,     5,    17,
      48,     0,     0,    18,    49,     0,     0,    46,    26,    50,
      23,    44,    43,     0,    22,    61,    59,    57,    55,    54,
      52,    51,    53,     0,    56,     0,    11,    58,     0,    60,
      47,     0,    14,    15,    13,   181,   176,   178,     0,   207,
     230,     0,     0,   186,   192,     0,     0,    48,   227,    59,
      57,    51,    53,    56,    60,    47,     0,   177,   182,     0,
       0,     0,     0,     4,    34,     0,    35,   140,     0,   144,
     141,   145,     0,   114,     0,     0,    78,    79,    80,    81,
     209,     0,   208,     0,     0,     0,     0,     0,    25,    20,
      21,   138,   139,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,   142,   143,     0,
      10,    16,    27,    28,     7,     8,     6,     0,    24,     9,
      12,     0,     0,   124,    30,   125,     0,    35,   231,   232,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     181,     0,     0,     0,     0,     0,     0,     0,   119,   115,
     116,   100,     0,   109,     0,     0,   112,    29,     0,   113,
      45,   122,   123,   151,   149,   150,   148,   170,   169,   146,
     147,   152,   154,   153,   155,   167,   168,   166,   157,   156,
     158,   159,   160,   175,   174,   161,   163,   164,   162,   165,
     171,   172,   173,   185,     0,   126,   127,     0,   219,   218,
     180,   179,   207,   207,   225,     0,   233,     0,     0,   191,
     190,   189,   187,   188,   184,   183,     0,     0,     0,     0,
       0,     0,     0,     0,   203,     0,     0,     0,   124,   122,
     126,     0,     0,   121,   117,   101,   102,     0,     0,   100,
       0,   210,   110,     0,   207,    65,   207,     0,   207,     0,
       0,   211,     0,   234,     0,   229,   242,   195,     0,     0,
       0,   194,     0,     0,     0,     0,     0,     0,   205,   204,
       0,   120,    82,     0,     0,     0,   103,     0,    66,     0,
       0,     0,     0,   221,   220,     0,   136,    31,   226,     0,
     207,   238,     0,   200,   198,     0,   199,   197,   196,   193,
       0,     0,    94,     0,    91,     0,     0,    95,     0,     0,
     106,     0,   111,   132,   134,   207,   207,   216,   128,     0,
     207,   237,   235,     0,   243,     0,     0,   206,   118,     0,
       0,   104,     0,     0,   105,     0,     0,     0,     0,     0,
     128,   128,     0,     0,   211,   137,     0,     0,     0,     0,
     240,   202,   201,    83,    86,    87,    85,    89,    90,    88,
      84,    93,    92,    97,    96,   107,   108,    35,    38,    39,
      37,    36,     0,     0,    63,     4,     0,     0,    67,   133,
     135,   223,   222,   217,     0,   213,   212,   236,     0,     0,
     244,     4,    75,     0,     4,   128,   130,   131,     0,   241,
      74,     4,    77,   224,   207,     0,    76,     0,   239,   129
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -363,  -363,  -363,     0,  -363,   -12,    -3,  -363,  -363,  -363,
     -19,    -4,   -17,  -363,  -363,  -363,    58,  -363,  -363,  -363,
     100,   125,   105,   127,   112,  -363,   208,  -363,  -363,  -363,
    -363,  -363,  -363,  -363,   297,  -363,  -363,   -15,  -362,    37,
    -363,  -363,  -363,    38,  -363,  -363,  -363,    49,    50,   428,
     -92,  -121,  -363,   322,    61,  -363,  -363,  -113,  -262,  -363,
     -59,   437,   116,  -363,    62,  -363,  -363,    77,  -363,  -363,
    -363,  -363,  -363,  -363,  -363,  -363,  -363,  -363,  -363,  -363
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   125,    38,    39,    87,    41,    42,    43,
      44,   120,    46,    47,    48,   371,   433,   399,    49,    50,
     421,   363,   364,   366,   367,   297,   298,   299,    51,   126,
      52,    53,   208,   209,   210,   293,    54,    55,   405,    89,
     400,   401,   378,    90,    58,    59,    60,    91,    92,    63,
      76,    77,    97,    98,    93,    84,    65,   203,    66,    67,
     121,   122,   348,    68,    94,   404,   455,    95,   311,    71,
      72,   190,   314,   383,    73,   384,   450,    74,   351,   410
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -216;
  const short int
  Parser::yytable_[] =
  {
        45,    40,     4,   107,   110,   108,   108,   109,   111,   104,
     202,   200,    88,   112,   105,   106,     8,     9,    10,   200,
     186,   200,   113,    99,   100,   269,   270,   116,   117,   118,
     119,    99,   100,   127,   123,   272,   336,   285,   439,   440,
     218,    56,    57,   318,   333,    75,   257,   258,   390,    17,
      18,   221,     3,    61,    62,    80,    24,   219,   286,   255,
     289,   261,   183,    28,   319,    64,    69,   391,   322,   290,
     134,   135,   136,   137,   138,   370,   139,   191,   192,   140,
     141,    70,   334,   335,   278,   281,    35,    86,   201,   323,
     124,    37,   271,   463,   101,   259,   276,   193,   279,   222,
     102,   273,   101,   194,   184,   277,   280,   256,   222,  -215,
     185,   212,  -216,  -216,  -216,  -216,   138,   256,   139,    83,
     456,    45,    40,   148,   149,   150,   308,   151,   152,   153,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,    56,    57,   261,   288,   149,   150,   457,   151,
     152,   153,   327,   -68,    61,    62,   342,   260,   397,   398,
     105,   427,   428,   429,   430,   -62,    64,    69,   181,   284,
      79,   274,   368,   131,   132,   393,   283,   261,   295,   296,
     206,   261,    70,   309,   310,   352,   -63,   184,    78,   355,
     301,   302,    81,   185,   394,    17,    18,   -73,   343,   133,
      82,   -98,    24,   206,   344,   -62,    96,   -62,   103,   431,
     369,   335,   -62,   -62,   -62,   -62,   -62,   413,   414,   415,
     416,   -62,   -62,   -62,   390,   340,   393,   341,   114,   345,
     295,   296,    35,    86,   128,   315,   316,    37,   115,   436,
     437,   312,   313,   425,   317,   426,   265,   321,   -62,   177,
    -214,   417,   418,   -99,   328,   329,   -62,   129,   419,   438,
     331,    79,   -62,   379,   130,   420,   199,    79,   380,   149,
     150,   382,   151,   152,   153,   151,   152,   153,   166,   170,
     134,   135,   136,   137,   138,   171,   139,   353,   354,   140,
     141,   356,   357,   358,   172,   173,   402,   403,   174,   144,
     175,   407,   176,   178,   181,   179,     5,     6,   187,     8,
       9,    10,   180,   182,   102,   372,   195,   381,   196,   197,
     198,   204,   165,   205,   207,   211,   213,   215,   387,   388,
     214,   146,   147,   148,   149,   150,   216,   151,   152,   153,
     262,   263,    17,    18,    19,    85,   264,    22,    23,    24,
     266,   303,   282,   411,   412,   406,    28,   154,   432,   155,
     108,   287,   434,   291,   156,   157,   158,   159,   160,   292,
     304,    31,    32,   161,   162,   163,   447,    33,    34,    35,
      86,   306,   307,   320,    37,   467,   324,   325,   326,   200,
     330,   332,   338,   339,   359,   362,   346,   432,   347,   108,
     164,   434,   134,   135,   136,   137,   138,   350,   139,   365,
     360,   140,   141,   361,   165,   452,   373,   459,   374,   142,
     143,   144,   145,   375,   458,   376,   389,   377,    45,    40,
     385,   460,   386,   468,   462,   392,    45,    40,    45,    40,
     408,   466,    45,    40,   409,   435,   444,   441,   442,   446,
     448,   449,   464,   146,   147,   148,   149,   150,   -71,   151,
     152,   153,   -72,   -70,   -69,   451,   454,   461,   469,    56,
      57,   305,   423,   395,   453,   422,   396,    56,    57,    56,
      57,    61,    62,    56,    57,   424,   294,   337,   188,    61,
      62,    61,    62,    64,    69,    61,    62,   189,   275,     0,
     443,    64,    69,    64,    69,     0,     0,    64,    69,    70,
       0,     0,     0,     0,     0,     0,     0,    70,     0,    70,
       0,     0,     0,    70,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    14,     0,     0,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,     0,
       0,    25,    26,    27,    28,    29,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,     0,     0,     0,    33,    34,    35,    36,   217,
       0,     0,    37,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,     0,     0,    15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,     0,     0,
      25,    26,    27,    28,    29,     0,     0,    30,     6,     7,
       8,     9,    10,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,    33,    34,    35,    36,     0,     0,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,    18,     0,    85,     0,    22,    23,
      24,     0,     0,     0,     0,     0,     0,    28,   -64,     0,
     -64,     0,     0,     0,     0,   -64,   -64,   -64,   -64,   -64,
       0,     0,    31,    32,   -64,   -64,   -64,     0,    33,    34,
      35,    86,     0,     0,     0,    37,   134,   135,   136,   137,
     138,     0,   139,     0,     0,   140,   141,     0,     0,     0,
       0,   -64,     0,   142,   143,   144,   145,   134,   135,   136,
     137,   138,     0,   139,     0,   -64,   140,   141,     0,     0,
       0,     0,     0,     0,   142,   143,   144,   145,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   146,   147,   148,
     149,   150,     0,   151,   152,   153,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   445,     0,     0,   146,   147,
     148,   149,   150,     0,   151,   152,   153,   134,   135,   136,
     137,   138,     0,   139,     0,   220,   140,   141,     0,     0,
       0,     0,     0,     0,   142,   143,   144,   145,   134,   135,
     136,   137,   138,     0,   139,     0,     0,   140,   141,     0,
       0,     0,     0,     0,     0,   142,   143,   144,   145,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   146,   147,
     148,   149,   150,     0,   151,   152,   153,     0,     0,     0,
       0,     0,     0,     0,     0,   267,     0,     0,     0,   146,
     147,   148,   149,   150,     0,   151,   152,   153,   134,   135,
     136,   137,   138,     0,   139,     0,   268,   140,   141,     0,
       0,     0,     0,     0,     0,   142,   143,   144,   145,   134,
     135,   136,   137,   138,     0,   139,     0,     0,   140,   141,
       0,     0,     0,     0,     0,     0,   142,   143,   144,   145,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,   150,     0,   151,   152,   153,     0,     0,
       0,     0,     0,     0,     0,     0,   300,     0,     0,     0,
     146,   147,   148,   149,   150,     0,   151,   152,   153,   134,
     135,   136,   137,   138,     0,   139,     0,   349,   140,   141,
       0,     0,     0,     0,     0,     0,   142,   143,   144,   145,
     -62,     0,   -62,     0,     0,     0,     0,   -62,   -62,   -62,
     -62,   -62,     0,     0,     0,     0,   -62,   -62,   -62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,   147,   148,   149,   150,     0,   151,   152,   153,     0,
       0,     0,     0,   -62,     0,  -214,     0,   465,     0,   134,
     135,   136,   137,   138,     0,   139,     0,   -62,   140,   141,
       0,     0,    79,     0,     0,     0,   142,   143,   144,   145,
     134,   135,   136,   137,   138,     0,   139,     0,     0,   140,
     141,     0,     0,     0,     0,     0,     0,   142,     0,   144,
     145,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,   147,   148,   149,   150,     0,   151,   152,   153,   134,
     135,   136,   137,   138,     0,   139,     0,     0,   140,   141,
       0,   146,   147,   148,   149,   150,     0,   151,   152,   153,
     134,   135,   136,   137,   138,     0,   139,     0,     0,   140,
     141,     0,   134,   135,   136,   137,   138,   142,   139,   144,
       0,   140,   141,     0,     0,     0,     0,     0,     0,     0,
     146,   147,   148,   149,   150,     0,   151,   152,   153,   134,
     135,   136,   137,   138,     0,   139,     0,     0,  -216,  -216,
       0,   146,   147,   148,   149,   150,     0,   151,   152,   153,
       0,     0,     0,     0,   147,   148,   149,   150,     0,   151,
     152,   153,   134,   135,   136,   137,   138,     0,   139,     0,
       0,   140,   141,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,   150,     0,   151,   152,   153,   -63,
       0,   -63,     0,     0,     0,     0,   -63,   -63,   -63,   -63,
     -63,     0,     0,     0,     0,   -63,   -63,   -63,     0,     0,
       0,     0,     0,     0,   167,   168,   149,   150,     0,   151,
     152,   153,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -63,     0,     0,     0,     0,     0,     0,     0,
     169,     0,     0,     0,     0,     0,   -63
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     2,    22,    23,    22,    23,    22,    23,    21,
     102,     5,    16,    25,     4,     5,     6,     7,     8,     5,
      79,     5,    26,     4,     5,     4,     5,    31,    32,    33,
      34,     4,     5,    37,     8,     5,   298,    61,   400,   401,
      61,     4,     4,    61,     3,     5,     4,     5,    61,    39,
      40,     5,     0,     4,     4,    81,    46,    78,    82,     5,
       5,   182,     5,    53,    82,     4,     4,    80,    61,     5,
      14,    15,    16,    17,    18,   337,    20,    81,    82,    23,
      24,     4,    41,    42,   197,   198,    76,    77,    82,    82,
      64,    81,    71,   455,    75,    53,    82,    64,    82,    53,
      81,    71,    75,    70,    47,   197,   198,    53,    53,    64,
      53,   115,    14,    15,    16,    17,    18,    53,    20,     5,
       5,   125,   125,    67,    68,    69,    81,    71,    72,    73,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   125,   125,   285,     5,    68,    69,    53,    71,
      72,    73,   285,    64,   125,   125,     5,   181,    58,    59,
       4,     5,     6,     7,     8,    76,   125,   125,    62,   201,
      81,   195,     3,    44,    45,    61,    70,   318,    55,    56,
      70,   322,   125,   262,   263,   318,    76,    47,    70,   322,
     214,   215,    81,    53,    80,    39,    40,    64,    47,    70,
      81,    78,    46,    70,    53,    19,    53,    21,    77,    53,
      41,    42,    26,    27,    28,    29,    30,     5,     6,     7,
       8,    35,    36,    37,    61,   304,    61,   306,     4,   308,
      55,    56,    76,    77,    80,   267,   268,    81,    81,    58,
      59,   265,   266,    80,   276,    80,    60,   279,    62,    64,
      64,    39,    40,    78,   286,   287,    76,    80,    46,    78,
     292,    81,    76,    76,    80,    53,     4,    81,    81,    68,
      69,   350,    71,    72,    73,    71,    72,    73,    80,    80,
      14,    15,    16,    17,    18,    80,    20,   319,   320,    23,
      24,   323,   324,   325,    80,    80,   375,   376,    80,    33,
      80,   380,    80,    80,    62,    80,     3,     4,     5,     6,
       7,     8,    80,    61,    81,   339,    62,   349,    61,    81,
      81,    70,    76,    70,    49,    77,    83,    64,   360,   361,
      61,    65,    66,    67,    68,    69,    78,    71,    72,    73,
      81,    81,    39,    40,    41,    42,    82,    44,    45,    46,
      80,     8,    81,   385,   386,   379,    53,    19,   397,    21,
     397,    82,   397,    81,    26,    27,    28,    29,    30,    48,
      81,    68,    69,    35,    36,    37,   408,    74,    75,    76,
      77,    81,    70,    82,    81,   464,    82,    82,    70,     5,
       5,    78,    77,    64,    70,     5,    82,   436,    82,   436,
      62,   436,    14,    15,    16,    17,    18,    80,    20,     5,
      82,    23,    24,    82,    76,   435,    82,   449,    82,    31,
      32,    33,    34,    81,   448,    81,    62,    82,   452,   452,
      82,   451,    82,   465,   454,    62,   460,   460,   462,   462,
      82,   461,   466,   466,    13,    64,    70,    82,    82,    82,
      81,    12,    81,    65,    66,    67,    68,    69,    64,    71,
      72,    73,    64,    64,    64,    64,    64,    64,    82,   452,
     452,    83,   392,   368,   436,   390,   369,   460,   460,   462,
     462,   452,   452,   466,   466,   393,   209,   299,    80,   460,
     460,   462,   462,   452,   452,   466,   466,    80,   196,    -1,
     404,   460,   460,   462,   462,    -1,    -1,   466,   466,   452,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   460,    -1,   462,
      -1,    -1,    -1,   466,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    81,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    22,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    -1,    -1,    57,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    74,    75,    76,    77,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    -1,    42,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    53,    19,    -1,
      21,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      -1,    -1,    68,    69,    35,    36,    37,    -1,    74,    75,
      76,    77,    -1,    -1,    -1,    81,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    62,    -1,    31,    32,    33,    34,    14,    15,    16,
      17,    18,    -1,    20,    -1,    76,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    -1,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    65,    66,
      67,    68,    69,    -1,    71,    72,    73,    14,    15,    16,
      17,    18,    -1,    20,    -1,    82,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    -1,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    71,    72,    73,    14,    15,
      16,    17,    18,    -1,    20,    -1,    82,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    71,    72,    73,    14,
      15,    16,    17,    18,    -1,    20,    -1,    82,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      19,    -1,    21,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    -1,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    71,    72,    73,    -1,
      -1,    -1,    -1,    62,    -1,    64,    -1,    82,    -1,    14,
      15,    16,    17,    18,    -1,    20,    -1,    76,    23,    24,
      -1,    -1,    81,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    71,    72,    73,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    65,    66,    67,    68,    69,    -1,    71,    72,    73,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    14,    15,    16,    17,    18,    31,    20,    33,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    71,    72,    73,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    65,    66,    67,    68,    69,    -1,    71,    72,    73,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,    71,
      72,    73,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    -1,    71,    72,    73,    19,
      -1,    21,    -1,    -1,    -1,    -1,    26,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    68,    69,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    76
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
     103,   112,   114,   115,   120,   121,   123,   127,   128,   129,
     130,   131,   132,   133,   138,   140,   142,   143,   147,   148,
     151,   153,   154,   158,   161,     5,   134,   135,    70,    81,
      81,    81,    81,     5,   139,    42,    77,    90,    95,   123,
     127,   131,   132,   138,   148,   151,    53,   136,   137,     4,
       5,    75,    81,    77,    89,     4,     5,    94,    96,   121,
      94,   121,    89,    95,     4,    81,    95,    95,    95,    95,
      95,   144,   145,     8,    64,    87,   113,    95,    80,    80,
      80,    44,    45,    70,    14,    15,    16,    17,    18,    20,
      23,    24,    31,    32,    33,    34,    65,    66,    67,    68,
      69,    71,    72,    73,    19,    21,    26,    27,    28,    29,
      30,    35,    36,    37,    62,    76,    80,    44,    45,    70,
      80,    80,    80,    80,    80,    80,    80,    64,    80,    80,
      80,    62,    61,     5,    47,    53,   144,     5,   133,   145,
     155,    95,    95,    64,    70,    62,    61,    81,    81,     4,
       5,    82,   134,   141,    70,    70,    70,    49,   116,   117,
     118,    77,    95,    83,    61,    64,    78,    78,    61,    78,
      82,     5,    53,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,     5,    53,     4,     5,    53,
      95,   135,    81,    81,    82,    60,    80,    82,    82,     4,
       5,    71,     5,    71,    95,   137,    82,   134,   141,    82,
     134,   141,    81,    70,    89,    61,    82,    82,     5,     5,
       5,    81,    48,   119,   118,    55,    56,   109,   110,   111,
      82,    95,    95,     8,    81,    83,    81,    70,    81,   144,
     144,   152,    95,    95,   156,    89,    89,    89,    61,    82,
      82,    89,    61,    82,    82,    82,    70,   141,    89,    89,
       5,    89,    78,     3,    41,    42,   142,   110,    77,    64,
     144,   144,     5,    47,    53,   144,    82,    82,   146,    82,
      80,   162,   141,    89,    89,   141,    89,    89,    89,    70,
      82,    82,     5,   105,   106,     5,   107,   108,     3,    41,
     142,    99,    95,    82,    82,    81,    81,    82,   126,    76,
      81,    89,   144,   157,   159,    82,    82,    89,    89,    62,
      61,    80,    62,    61,    80,   105,   107,    58,    59,   101,
     124,   125,   144,   144,   149,   122,    95,   144,    82,    13,
     163,    89,    89,     5,     6,     7,     8,    39,    40,    46,
      53,   104,   106,   104,   108,    80,    80,     5,     6,     7,
       8,    53,    94,   100,   121,    64,    58,    59,    78,   122,
     122,    82,    82,   146,    70,    83,    82,    89,    81,    12,
     160,    64,    87,   100,    64,   150,     5,    53,    95,    89,
      87,    64,    87,   122,    81,    82,    87,   144,    89,    82
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
      94,    94,    94,    94,    94,    94,    94,    94,    94,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    96,    96,    96,    97,    99,    98,   100,   100,
     100,   100,   100,   100,   101,   101,   101,   101,   102,   102,
     102,   102,   103,   104,   104,   104,   104,   104,   104,   104,
     104,   105,   105,   106,   106,   107,   107,   108,   109,   109,
     110,   110,   110,   111,   111,   111,   111,   111,   111,   112,
     113,   113,   114,   114,   115,   116,   117,   117,   118,   119,
     119,   120,   121,   121,   121,   121,   121,   121,   122,   122,
     122,   122,   124,   123,   125,   123,   126,   123,   127,   127,
     127,   127,   127,   127,   127,   127,   128,   128,   128,   128,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   138,   139,   139,   140,   140,
     140,   140,   140,   141,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   143,   143,   143,   143,   144,   144,   145,
     145,   146,   146,   146,   147,   147,   149,   148,   148,   148,
     148,   148,   148,   150,   148,   152,   151,   153,   153,   154,
     155,   155,   155,   156,   156,   157,   158,   158,   159,   159,
     160,   160,   162,   163,   161
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
       2,     4,     3,     3,     3,     3,     3,     3,     0,     6,
       3,     3,     0,     8,     0,     8,     0,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     3,
       3,     1,     1,     3,     3,     3,     1,     3,     4,     4,
       4,     4,     2,     4,     5,     5,     6,     6,     6,     6,
       6,     8,     8,     4,     5,     5,     7,     0,     1,     1,
       3,     0,     4,     4,     1,     3,     0,     8,     3,     3,
       5,     5,     8,     0,    10,     0,     6,     2,     1,     5,
       0,     1,     1,     0,     1,     1,     9,     7,     0,     6,
       0,     2,     0,     0,     9
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
  "property_access", "mcall_chain", "mcall", "@3", "@4", "@5", "inc_dec",
  "comparison", "boolean", "logic", "arithmetic", "bitwise",
  "variable_decl", "variable_decl_list", "variable_decl_impl",
  "const_decl_list", "const_decl_impl", "assignment", "import_ident_list",
  "import", "vararg", "fdecl", "anonymous_fdecl", "call_args",
  "non_empty_call_args", "fcall_chain", "fully_qualified_name",
  "fully_qualified_call", "@6", "@7", "fcall", "@8", "return_stmt",
  "while", "for_expr_1", "for_expr_2", "for_expr_3", "for", "elseif",
  "else", "if", "@9", "@10", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        85,     0,    -1,    -1,    86,    87,    -1,    -1,    87,    88,
      -1,   140,    80,    -1,   133,    80,    -1,   138,    80,    -1,
     151,    80,    -1,   123,    80,    -1,   142,    -1,   153,    80,
      -1,   161,    -1,   154,    -1,   158,    -1,   127,    80,    -1,
      89,    -1,    93,    -1,   115,    80,    -1,    91,    80,    -1,
      92,    80,    -1,   120,    -1,   103,    -1,   148,    80,    -1,
      90,    80,    -1,    98,    -1,   131,    80,    -1,   132,    80,
      -1,    77,    87,    78,    -1,     4,    70,    47,    -1,     4,
      70,    47,    81,   144,    82,    -1,    22,    -1,    52,    -1,
      43,    89,    -1,     5,    -1,    53,    -1,     8,    -1,     6,
      -1,     7,    -1,    46,    -1,    39,    -1,    40,    -1,   114,
      -1,   112,    -1,    81,    95,    82,    -1,    97,    -1,   151,
      -1,    90,    -1,    94,    -1,   102,    -1,   131,    -1,   130,
      -1,   132,    -1,   129,    -1,   128,    -1,   138,    -1,   127,
      -1,   143,    -1,   123,    -1,   148,    -1,   121,    -1,     5,
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
      -1,    -1,    55,    -1,    56,    -1,   110,   142,    -1,   110,
       3,   105,    80,    -1,   110,    41,   107,    80,    -1,   111,
     110,   142,    -1,   111,   110,     3,   105,    80,    -1,   111,
     110,    41,   107,    80,    -1,    76,   144,    83,    -1,     8,
      64,    95,    -1,   113,    61,     8,    64,    95,    -1,    77,
      64,    78,    -1,    77,   113,    78,    -1,    51,    95,    -1,
     117,    -1,   118,    -1,   117,   118,    -1,    49,    81,     5,
      82,    89,    -1,    -1,    48,    89,    -1,    50,    89,   116,
     119,    -1,    94,    70,     5,    -1,    94,    70,    53,    -1,
       4,    70,     5,    -1,     4,    70,    53,    -1,   121,    70,
       5,    -1,   121,    70,    53,    -1,    -1,   122,    70,     5,
      81,   144,    82,    -1,   122,    70,     5,    -1,   122,    70,
      53,    -1,    -1,    94,    70,     5,    81,   144,    82,   124,
     122,    -1,    -1,   121,    70,     5,    81,   144,    82,   125,
     122,    -1,    -1,     4,    70,     5,    81,   144,    82,   126,
     122,    -1,    94,    44,    -1,    94,    45,    -1,    44,    94,
      -1,    45,    94,    -1,   121,    44,    -1,   121,    45,    -1,
      44,   121,    -1,    45,   121,    -1,    95,    23,    95,    -1,
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
      95,    -1,    96,    19,    95,    -1,     3,   134,    -1,    41,
     136,    -1,   135,    -1,   134,    61,   135,    -1,     5,    62,
      95,    -1,     5,    -1,   137,    -1,   136,    61,   137,    -1,
      53,    62,    95,    -1,    96,    62,    95,    -1,     5,    -1,
     139,    70,     5,    -1,    25,   139,    70,    71,    -1,    25,
     139,    64,    71,    -1,    25,   139,    64,     5,    -1,    25,
     139,    64,     4,    -1,    25,   139,    -1,     5,    70,    70,
      70,    -1,    42,     5,    81,    82,    89,    -1,    42,     4,
      81,    82,    89,    -1,    42,    75,     4,    81,    82,    89,
      -1,    42,     5,    81,   141,    82,    89,    -1,    42,     4,
      81,   141,    82,    89,    -1,    42,     5,    81,   134,    82,
      89,    -1,    42,     4,    81,   134,    82,    89,    -1,    42,
       5,    81,   134,    61,   141,    82,    89,    -1,    42,     4,
      81,   134,    61,   141,    82,    89,    -1,    42,    81,    82,
      89,    -1,    42,    81,   141,    82,    89,    -1,    42,    81,
     134,    82,    89,    -1,    42,    81,   134,    61,   141,    82,
      89,    -1,    -1,   145,    -1,    95,    -1,   145,    61,    95,
      -1,    -1,   146,    81,   144,    82,    -1,   146,    76,    95,
      83,    -1,     5,    -1,   147,    64,     5,    -1,    -1,   147,
      64,     5,    81,   144,    82,   149,   146,    -1,   147,    64,
      53,    -1,   147,    64,     5,    -1,   147,    64,     4,    70,
      53,    -1,   147,    64,     4,    70,    47,    -1,   147,    64,
       4,    70,    47,    81,   144,    82,    -1,    -1,   147,    64,
       4,    70,     5,    81,   144,    82,   150,   122,    -1,    -1,
       5,    81,   144,    82,   152,   146,    -1,    38,    95,    -1,
      38,    -1,    10,    81,    95,    82,    89,    -1,    -1,   133,
      -1,   145,    -1,    -1,    95,    -1,   144,    -1,     9,    81,
     155,    80,   156,    80,   157,    82,    89,    -1,     9,    81,
       5,    60,    95,    82,    89,    -1,    -1,   159,    13,    81,
      95,    82,    89,    -1,    -1,    12,    89,    -1,    -1,    -1,
      11,    81,    95,    82,    89,   162,   159,   163,   160,    -1
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
     334,   337,   342,   346,   350,   354,   358,   362,   366,   367,
     374,   378,   382,   383,   392,   393,   402,   403,   412,   415,
     418,   421,   424,   427,   430,   433,   436,   440,   444,   448,
     452,   456,   460,   464,   468,   472,   476,   480,   484,   488,
     492,   496,   500,   504,   508,   512,   516,   520,   524,   528,
     532,   536,   540,   544,   548,   552,   556,   559,   562,   564,
     568,   572,   574,   576,   580,   584,   588,   590,   594,   599,
     604,   609,   614,   617,   622,   628,   634,   641,   648,   655,
     662,   669,   678,   687,   692,   698,   704,   712,   713,   715,
     717,   721,   722,   727,   732,   734,   738,   739,   748,   752,
     756,   762,   768,   777,   778,   789,   790,   797,   800,   802,
     808,   809,   811,   813,   814,   816,   818,   828,   836,   837,
     844,   845,   848,   849,   850
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   221,   221,   221,   225,   226,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   256,
     260,   261,   265,   269,   273,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   316,   317,   318,   322,   326,   326,   330,   331,
     332,   333,   334,   335,   339,   340,   341,   342,   346,   347,
     348,   349,   353,   357,   358,   359,   360,   361,   362,   363,
     364,   368,   369,   373,   374,   378,   379,   383,   387,   388,
     392,   393,   394,   398,   399,   400,   401,   402,   403,   407,
     411,   412,   416,   417,   421,   425,   429,   430,   434,   438,
     439,   443,   447,   448,   449,   450,   451,   452,   456,   457,
     458,   459,   463,   463,   464,   464,   465,   465,   469,   470,
     471,   472,   473,   474,   475,   476,   480,   481,   482,   483,
     484,   485,   489,   490,   494,   495,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   512,   513,   514,   515,
     516,   517,   518,   519,   520,   521,   525,   526,   530,   531,
     535,   536,   540,   541,   545,   549,   553,   554,   558,   559,
     560,   561,   562,   566,   570,   572,   574,   576,   578,   580,
     582,   584,   586,   591,   593,   595,   597,   602,   603,   607,
     608,   612,   613,   614,   618,   619,   623,   623,   624,   625,
     626,   627,   628,   629,   629,   633,   633,   637,   638,   642,
     646,   647,   648,   652,   653,   657,   661,   662,   686,   688,
     692,   693,   697,   697,   697
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
  const int Parser::yylast_ = 1306;
  const int Parser::yynnts_ = 80;
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

