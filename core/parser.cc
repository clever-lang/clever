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

  case 238:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 239:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 240:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 241:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 242:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 243:

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
  const short int Parser::yypact_ninf_ = -376;
  const short int
  Parser::yypact_[] =
  {
      -376,    39,  -376,  -376,   536,    58,   -26,   895,  -376,  -376,
    -376,    -7,    34,   108,  -376,   119,   392,  -376,  -376,    74,
      14,    53,    30,    30,  -376,    53,   392,  -376,  -376,   217,
     153,   392,   392,   392,   392,   392,    24,   392,  -376,  -376,
     158,   160,   176,  -376,   135,   919,  1106,  1147,  -376,  -376,
    -376,  -376,  -376,   178,  -376,  1094,   185,   186,  -376,  -376,
    -376,   192,   194,   195,   205,   206,  -376,  -376,   223,   208,
     209,   210,  -376,  -376,  -376,   229,   231,  -376,    54,   392,
     591,   392,   392,  -376,    -1,   212,    24,  -376,   919,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,   239,   241,  -376,   227,
     228,   305,     9,  -376,  -376,   242,   166,   243,   238,    48,
     243,    48,   265,   919,   240,   392,  -376,  -376,  -376,  -376,
     919,   233,   257,   264,   253,   315,   -20,   679,  -376,  -376,
    -376,  -376,  -376,    44,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,  -376,  -376,  -376,    51,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,    47,  -376,  -376,
    -376,   392,    58,   251,   254,  -376,   252,  -376,   257,   262,
     738,   759,    19,    12,   392,    74,    10,    11,   256,    57,
      53,   104,   263,    55,    66,   120,   266,   295,   265,  -376,
     128,   818,  -376,   392,   392,  -376,  -376,   337,  -376,  -376,
     267,  -376,   152,   152,   152,   152,   182,   182,   637,   637,
     981,   945,  1016,  1004,  1040,   459,   797,   198,   198,  -376,
    -376,  -376,  1004,  1004,  1004,  1004,  1004,  1004,  1004,  1004,
    1004,  1004,  1004,   211,   268,  -376,   280,   118,  -376,   919,
    -376,   392,   392,  -376,   392,    53,    53,  -376,  -376,  -376,
    -376,  -376,   919,  -376,    53,   133,   269,    53,   134,   270,
     271,   301,  -376,   359,    53,    53,  -376,  -376,  -376,   368,
      53,  -376,  -376,  -376,  -376,   297,    71,   136,   300,   919,
     919,   314,   392,  -376,   392,    56,   392,   298,   303,  -376,
     919,   302,  -376,  -376,  -376,   359,    53,    53,  -376,   359,
      53,    53,    53,   317,   306,  -376,  -376,   313,  -376,  -376,
     396,   397,    21,  -376,   175,  -376,   392,   322,   323,   325,
     326,  -376,   327,  -376,  -376,   183,   392,  -376,   328,  -376,
    -376,   329,  -376,  -376,  -376,  -376,    53,    53,   346,   -29,
    -376,   350,   129,  -376,   396,   397,  -376,   203,   919,  -376,
    -376,   392,   392,  -376,  -376,   392,   392,  -376,   331,   400,
      53,    53,  -376,  -376,   289,   396,  -376,   289,   397,  -376,
     151,   172,    40,   352,   141,  -376,  -376,   335,   339,  -376,
     349,   658,   340,    53,   342,   411,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,    -8,   361,   362,   364,   365,   243,   366,   143,
    -376,    40,   370,  -376,   349,   349,  -376,  -376,   183,   123,
    -376,  -376,  -376,   392,    53,  -376,  -376,   536,   372,  -376,
    -376,   360,  -376,   839,  -376,   536,  -376,   536,   349,   392,
      53,   536,   367,  -376,  -376
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
      12,     0,     0,   124,    30,   125,     0,   231,   232,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   181,
       0,     0,     0,     0,     0,     0,     0,   119,   115,   116,
     100,     0,   109,     0,     0,   112,    29,     0,   113,    45,
     122,   123,   151,   149,   150,   148,   170,   169,   146,   147,
     152,   154,   153,   155,   167,   168,   166,   157,   156,   158,
     159,   160,   175,   174,   161,   163,   164,   162,   165,   171,
     172,   173,   185,     0,   126,   127,     0,   219,   218,   180,
     179,   207,   207,   225,   233,     0,     0,   191,   190,   189,
     187,   188,   184,   183,     0,     0,     0,     0,     0,     0,
       0,     0,   203,     0,     0,     0,   124,   122,   126,     0,
       0,   121,   117,   101,   102,     0,     0,   100,     0,   210,
     110,     0,   207,    65,   207,     0,   207,     0,     0,   211,
     234,     0,   229,   241,   195,     0,     0,     0,   194,     0,
       0,     0,     0,     0,     0,   205,   204,     0,   120,    82,
       0,     0,     0,   103,     0,    66,     0,     0,     0,     0,
     221,   220,     0,   136,    31,   226,   207,   237,     0,   200,
     198,     0,   199,   197,   196,   193,     0,     0,    94,     0,
      91,     0,     0,    95,     0,     0,   106,     0,   111,   132,
     134,   207,   207,   216,   128,     0,   207,   235,     0,   242,
       0,     0,   206,   118,     0,     0,   104,     0,     0,   105,
       0,     0,     0,     0,     0,   128,   128,     0,     0,   211,
     137,     0,     0,     0,     0,   239,   202,   201,    83,    86,
      87,    85,    89,    90,    88,    84,    93,    92,    97,    96,
     107,   108,    35,    38,    39,    37,    36,     0,     0,    63,
       4,     0,     0,    67,   133,   135,   223,   222,   217,     0,
     213,   212,   236,     0,     0,   243,     4,    75,     0,     4,
     128,   130,   131,     0,   240,    74,     4,    77,   224,   207,
       0,    76,     0,   238,   129
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -376,  -376,  -376,     0,  -376,   -18,    -3,  -376,  -376,  -376,
     -17,    -4,   -14,  -376,  -376,  -376,    16,  -376,  -376,  -376,
      63,    91,    76,    97,    75,  -376,   144,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,   261,  -376,  -376,   -12,  -375,    37,
    -376,  -376,  -376,    38,  -376,  -376,  -376,    49,    50,   384,
     -98,  -118,  -376,   275,    61,  -376,  -376,  -112,  -238,  -376,
     -66,   391,    79,  -376,    62,  -376,  -376,    77,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   125,    38,    39,    87,    41,    42,    43,
      44,   120,    46,    47,    48,   367,   428,   394,    49,    50,
     416,   359,   360,   362,   363,   295,   296,   297,    51,   126,
      52,    53,   207,   208,   209,   291,    54,    55,   400,    89,
     395,   396,   374,    90,    58,    59,    60,    91,    92,    63,
      76,    77,    97,    98,    93,    84,    65,   202,    66,    67,
     121,   122,   345,    68,    94,   399,   450,    95,   309,    71,
      72,   189,   311,   378,    73,   379,   445,    74,   347,   405
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -216;
  const short int
  Parser::yytable_[] =
  {
        45,    40,     4,   104,   201,   107,   110,   112,   108,   108,
     109,   111,    88,   186,   199,   199,   199,   270,    99,   100,
     434,   435,   113,   267,   268,    99,   100,   116,   117,   118,
     119,   385,   123,   127,   105,   106,     8,     9,    10,     3,
     217,    56,    57,    78,   105,   422,   423,   424,   425,   220,
     386,   256,   257,    61,    62,   -68,   254,   218,   333,   183,
     286,   339,   192,    75,   260,    64,    69,   -62,   193,    17,
      18,   287,    79,    80,   330,   458,    24,   190,   191,    17,
      18,    70,   271,    28,   276,   279,    24,   124,   101,   269,
     200,   274,   277,   426,   102,   101,   366,   221,   275,   278,
     258,   184,   184,   340,   255,    35,    86,   185,   185,   341,
      37,   211,   331,   332,    81,    35,    86,   205,   181,   221,
      37,    45,    40,   -63,    83,   288,   281,    96,   451,   103,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,    56,    57,   283,   260,  -216,  -216,  -216,  -216,
     138,   324,   139,   255,    61,    62,   452,   259,   364,   131,
     132,  -215,   282,   293,   294,   284,    64,    69,    82,   388,
     272,   293,   294,   315,   319,   307,   308,   260,   306,   431,
     432,   260,    70,   348,   133,   -98,   -73,   351,   389,   299,
     300,   385,   205,   -99,   316,   320,   365,   332,   433,   149,
     150,   114,   151,   152,   153,   134,   135,   136,   137,   138,
     420,   139,   388,   115,   140,   141,   337,   128,   338,   129,
     342,   -62,   142,   143,   144,   145,    79,   312,   313,   149,
     150,   421,   151,   152,   153,   130,   314,   166,   375,   318,
     310,   392,   393,   376,   170,   171,   325,   326,   151,   152,
     153,   172,   328,   173,   174,   146,   147,   148,   149,   150,
     377,   151,   152,   153,   175,   176,   177,   178,   179,   180,
     181,   182,   102,   303,   408,   409,   410,   411,   349,   350,
     194,   195,   352,   353,   354,   397,   398,   196,   197,   198,
     402,   203,   204,   165,   206,   212,   210,   213,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   214,   412,   413,
     215,   261,   368,   263,   262,   414,   280,    14,   382,   383,
      15,   264,   415,   290,   285,   301,   289,   302,   304,   305,
     317,   321,   322,    16,    17,    18,    19,    20,    21,    22,
      23,    24,   406,   407,   199,    25,    26,    27,    28,    29,
     323,   401,    30,   327,   329,   427,   335,   336,   108,   343,
     429,   346,    31,    32,   344,   442,   355,   356,    33,    34,
      35,    36,   216,   462,   357,    37,     6,     7,     8,     9,
      10,   358,   361,   369,   370,   371,   372,   384,   373,   380,
     381,   387,   403,   404,   427,   430,   436,   108,   439,   429,
     437,   441,   443,   444,   -71,   -72,   454,   -70,   -69,   446,
     447,    17,    18,   449,    85,   456,    22,    23,    24,   453,
     459,   334,   463,    45,    40,    28,   455,   448,   464,   457,
     418,    45,    40,    45,    40,   390,   461,    45,    40,    31,
      32,   417,   391,   419,   187,    33,    34,    35,    86,   292,
     273,   188,    37,   134,   135,   136,   137,   138,   438,   139,
       0,     0,   140,   141,    56,    57,     0,     0,     0,     0,
       0,     0,    56,    57,    56,    57,    61,    62,    56,    57,
       0,     0,     0,     0,    61,    62,    61,    62,    64,    69,
      61,    62,     0,     0,     0,     0,    64,    69,    64,    69,
       0,     0,    64,    69,    70,   148,   149,   150,     0,   151,
     152,   153,    70,     0,    70,     0,     0,     0,    70,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,     0,
       0,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,     0,     0,    25,    26,    27,    28,
      29,     0,     0,    30,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    31,    32,     0,     0,     0,     0,    33,
      34,    35,    36,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,    18,    19,    85,     0,    22,    23,    24,     0,     0,
       0,     0,     0,     0,    28,     0,     0,     0,     0,     0,
       0,   134,   135,   136,   137,   138,     0,   139,    31,    32,
    -216,  -216,     0,     0,    33,    34,    35,    86,     0,     0,
       0,    37,   134,   135,   136,   137,   138,     0,   139,     0,
       0,   140,   141,     0,     0,     0,     0,     0,     0,   142,
     143,   144,   145,   134,   135,   136,   137,   138,     0,   139,
       0,     0,   140,   141,   149,   150,     0,   151,   152,   153,
     142,   143,   144,   145,     0,     0,     0,     0,     0,     0,
       0,     0,   146,   147,   148,   149,   150,     0,   151,   152,
     153,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     440,     0,     0,   146,   147,   148,   149,   150,     0,   151,
     152,   153,   134,   135,   136,   137,   138,     0,   139,     0,
     219,   140,   141,     0,     0,     0,     0,     0,     0,   142,
     143,   144,   145,   134,   135,   136,   137,   138,     0,   139,
       0,     0,   140,   141,     0,     0,     0,     0,     0,     0,
     142,   143,   144,   145,     0,     0,     0,     0,     0,     0,
       0,     0,   146,   147,   148,   149,   150,     0,   151,   152,
     153,   134,   135,   136,   137,   138,     0,   139,     0,   265,
     140,   141,     0,   146,   147,   148,   149,   150,     0,   151,
     152,   153,   134,   135,   136,   137,   138,     0,   139,     0,
     266,   140,   141,     0,     0,     0,     0,     0,     0,   142,
     143,   144,   145,   134,   135,   136,   137,   138,     0,   139,
       0,     0,   140,   141,   149,   150,     0,   151,   152,   153,
     142,   143,   144,   145,     0,     0,     0,     0,     0,     0,
       0,     0,   146,   147,   148,   149,   150,     0,   151,   152,
     153,     0,     0,     0,     0,     0,     0,     0,     0,   298,
       0,     0,     0,   146,   147,   148,   149,   150,     0,   151,
     152,   153,     0,     0,   -62,     0,   -62,     0,     0,     0,
     460,   -62,   -62,   -62,   -62,   -62,     0,     0,     0,     0,
     -62,   -62,   -62,   134,   135,   136,   137,   138,     0,   139,
       0,     0,   140,   141,     0,     0,     0,     0,     0,     0,
     142,   143,   144,   145,     0,     0,   -62,     0,  -214,   134,
     135,   136,   137,   138,     0,   139,     0,     0,   140,   141,
     -62,     0,     0,     0,     0,    79,   142,     0,   144,   145,
       0,     0,     0,   146,   147,   148,   149,   150,     0,   151,
     152,   153,     0,     0,     0,   134,   135,   136,   137,   138,
       0,   139,     0,     0,   140,   141,     0,     0,     0,   146,
     147,   148,   149,   150,   144,   151,   152,   153,   134,   135,
     136,   137,   138,     0,   139,     0,     0,   140,   141,     0,
     134,   135,   136,   137,   138,   142,   139,   144,     0,   140,
     141,     0,     0,     0,     0,   146,   147,   148,   149,   150,
       0,   151,   152,   153,   134,   135,   136,   137,   138,     0,
     139,     0,     0,   140,   141,     0,     0,     0,   146,   147,
     148,   149,   150,     0,   151,   152,   153,     0,     0,     0,
     146,   147,   148,   149,   150,     0,   151,   152,   153,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   147,   148,   149,   150,     0,
     151,   152,   153,   -63,     0,   -63,     0,     0,     0,     0,
     -63,   -63,   -63,   -63,   -63,   154,     0,   155,     0,   -63,
     -63,   -63,   156,   157,   158,   159,   160,     0,   167,   168,
       0,   161,   162,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -63,     0,     0,     0,     0,
       0,     0,     0,   169,     0,     0,   -64,   164,   -64,   -63,
       0,     0,     0,   -64,   -64,   -64,   -64,   -64,     0,     0,
       0,   165,   -64,   -64,   -64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -64
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,     4,     2,    21,   102,    22,    23,    25,    22,    23,
      22,    23,    16,    79,     5,     5,     5,     5,     4,     5,
     395,   396,    26,     4,     5,     4,     5,    31,    32,    33,
      34,    60,     8,    37,     4,     5,     6,     7,     8,     0,
      60,     4,     4,    69,     4,     5,     6,     7,     8,     5,
      79,     4,     5,     4,     4,    63,     5,    77,   296,     5,
       5,     5,    63,     5,   182,     4,     4,    75,    69,    39,
      40,     5,    80,    80,     3,   450,    46,    81,    82,    39,
      40,     4,    70,    53,   196,   197,    46,    63,    74,    70,
      81,    81,    81,    53,    80,    74,   334,    53,   196,   197,
      53,    47,    47,    47,    53,    75,    76,    53,    53,    53,
      80,   115,    41,    42,    80,    75,    76,    69,    61,    53,
      80,   125,   125,    75,     5,     5,    69,    53,     5,    76,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   125,   125,    60,   283,    14,    15,    16,    17,
      18,   283,    20,    53,   125,   125,    53,   181,     3,    44,
      45,    63,   200,    55,    56,    81,   125,   125,    80,    60,
     194,    55,    56,    60,    60,   261,   262,   315,    80,    58,
      59,   319,   125,   315,    69,    77,    63,   319,    79,   213,
     214,    60,    69,    77,    81,    81,    41,    42,    77,    67,
      68,     4,    70,    71,    72,    14,    15,    16,    17,    18,
      79,    20,    60,    80,    23,    24,   302,    79,   304,    79,
     306,    75,    31,    32,    33,    34,    80,   265,   266,    67,
      68,    79,    70,    71,    72,    79,   274,    79,    75,   277,
     264,    58,    59,    80,    79,    79,   284,   285,    70,    71,
      72,    79,   290,    79,    79,    64,    65,    66,    67,    68,
     346,    70,    71,    72,    79,    79,    63,    79,    79,    79,
      61,    60,    80,    82,     5,     6,     7,     8,   316,   317,
      61,    60,   320,   321,   322,   371,   372,    80,    80,     4,
     376,    69,    69,    75,    49,    82,    76,    60,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    63,    39,    40,
      77,    80,   336,    81,    80,    46,    80,    22,   356,   357,
      25,    79,    53,    48,    81,     8,    80,    80,    80,    69,
      81,    81,    81,    38,    39,    40,    41,    42,    43,    44,
      45,    46,   380,   381,     5,    50,    51,    52,    53,    54,
      69,   375,    57,     5,    77,   392,    76,    63,   392,    81,
     392,    79,    67,    68,    81,   403,    69,    81,    73,    74,
      75,    76,    77,   459,    81,    80,     4,     5,     6,     7,
       8,     5,     5,    81,    81,    80,    80,    61,    81,    81,
      81,    61,    81,    13,   431,    63,    81,   431,    69,   431,
      81,    81,    80,    12,    63,    63,   444,    63,    63,    63,
     430,    39,    40,    63,    42,    63,    44,    45,    46,   443,
      80,   297,   460,   447,   447,    53,   446,   431,    81,   449,
     387,   455,   455,   457,   457,   364,   456,   461,   461,    67,
      68,   385,   365,   388,    80,    73,    74,    75,    76,   208,
     195,    80,    80,    14,    15,    16,    17,    18,   399,    20,
      -1,    -1,    23,    24,   447,   447,    -1,    -1,    -1,    -1,
      -1,    -1,   455,   455,   457,   457,   447,   447,   461,   461,
      -1,    -1,    -1,    -1,   455,   455,   457,   457,   447,   447,
     461,   461,    -1,    -1,    -1,    -1,   455,   455,   457,   457,
      -1,    -1,   461,   461,   447,    66,    67,    68,    -1,    70,
      71,    72,   455,    -1,   457,    -1,    -1,    -1,   461,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    -1,    -1,    57,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    14,    15,    16,    17,    18,    -1,    20,    67,    68,
      23,    24,    -1,    -1,    73,    74,    75,    76,    -1,    -1,
      -1,    80,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    67,    68,    -1,    70,    71,    72,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    64,    65,    66,    67,    68,    -1,    70,
      71,    72,    14,    15,    16,    17,    18,    -1,    20,    -1,
      81,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    -1,    70,    71,
      72,    14,    15,    16,    17,    18,    -1,    20,    -1,    81,
      23,    24,    -1,    64,    65,    66,    67,    68,    -1,    70,
      71,    72,    14,    15,    16,    17,    18,    -1,    20,    -1,
      81,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    67,    68,    -1,    70,    71,    72,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,    70,
      71,    72,    -1,    -1,    19,    -1,    21,    -1,    -1,    -1,
      81,    26,    27,    28,    29,    30,    -1,    -1,    -1,    -1,
      35,    36,    37,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    -1,    -1,    61,    -1,    63,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      75,    -1,    -1,    -1,    -1,    80,    31,    -1,    33,    34,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    -1,    70,
      71,    72,    -1,    -1,    -1,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    33,    70,    71,    72,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      14,    15,    16,    17,    18,    31,    20,    33,    -1,    23,
      24,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    70,    71,    72,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      70,    71,    72,    19,    -1,    21,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,    30,    19,    -1,    21,    -1,    35,
      36,    37,    26,    27,    28,    29,    30,    -1,    44,    45,
      -1,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    19,    61,    21,    75,
      -1,    -1,    -1,    26,    27,    28,    29,    30,    -1,    -1,
      -1,    75,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    84,    85,     0,    86,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    22,    25,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    50,    51,    52,    53,    54,
      57,    67,    68,    73,    74,    75,    76,    80,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,   101,
     102,   111,   113,   114,   119,   120,   122,   126,   127,   128,
     129,   130,   131,   132,   137,   139,   141,   142,   146,   147,
     150,   152,   153,   157,   160,     5,   133,   134,    69,    80,
      80,    80,    80,     5,   138,    42,    76,    89,    94,   122,
     126,   130,   131,   137,   147,   150,    53,   135,   136,     4,
       5,    74,    80,    76,    88,     4,     5,    93,    95,   120,
      93,   120,    88,    94,     4,    80,    94,    94,    94,    94,
      94,   143,   144,     8,    63,    86,   112,    94,    79,    79,
      79,    44,    45,    69,    14,    15,    16,    17,    18,    20,
      23,    24,    31,    32,    33,    34,    64,    65,    66,    67,
      68,    70,    71,    72,    19,    21,    26,    27,    28,    29,
      30,    35,    36,    37,    61,    75,    79,    44,    45,    69,
      79,    79,    79,    79,    79,    79,    79,    63,    79,    79,
      79,    61,    60,     5,    47,    53,   143,   132,   144,   154,
      94,    94,    63,    69,    61,    60,    80,    80,     4,     5,
      81,   133,   140,    69,    69,    69,    49,   115,   116,   117,
      76,    94,    82,    60,    63,    77,    77,    60,    77,    81,
       5,    53,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,     5,    53,     4,     5,    53,    94,
     134,    80,    80,    81,    79,    81,    81,     4,     5,    70,
       5,    70,    94,   136,    81,   133,   140,    81,   133,   140,
      80,    69,    88,    60,    81,    81,     5,     5,     5,    80,
      48,   118,   117,    55,    56,   108,   109,   110,    81,    94,
      94,     8,    80,    82,    80,    69,    80,   143,   143,   151,
      94,   155,    88,    88,    88,    60,    81,    81,    88,    60,
      81,    81,    81,    69,   140,    88,    88,     5,    88,    77,
       3,    41,    42,   141,   109,    76,    63,   143,   143,     5,
      47,    53,   143,    81,    81,   145,    79,   161,   140,    88,
      88,   140,    88,    88,    88,    69,    81,    81,     5,   104,
     105,     5,   106,   107,     3,    41,   141,    98,    94,    81,
      81,    80,    80,    81,   125,    75,    80,   143,   156,   158,
      81,    81,    88,    88,    61,    60,    79,    61,    60,    79,
     104,   106,    58,    59,   100,   123,   124,   143,   143,   148,
     121,    94,   143,    81,    13,   162,    88,    88,     5,     6,
       7,     8,    39,    40,    46,    53,   103,   105,   103,   107,
      79,    79,     5,     6,     7,     8,    53,    93,    99,   120,
      63,    58,    59,    77,   121,   121,    81,    81,   145,    69,
      82,    81,    88,    80,    12,   159,    63,    86,    99,    63,
     149,     5,    53,    94,    88,    86,    63,    86,   121,    80,
      81,    86,   143,    88,    81
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
      87,    87,    87,    87,    87,    87,    87,    87,    87,    88,
      89,    89,    90,    91,    92,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    95,    95,    95,    96,    98,    97,    99,    99,
      99,    99,    99,    99,   100,   100,   100,   100,   101,   101,
     101,   101,   102,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   105,   105,   106,   106,   107,   108,   108,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   111,
     112,   112,   113,   113,   114,   115,   116,   116,   117,   118,
     118,   119,   120,   120,   120,   120,   120,   120,   121,   121,
     121,   121,   123,   122,   124,   122,   125,   122,   126,   126,
     126,   126,   126,   126,   126,   126,   127,   127,   127,   127,
     127,   127,   128,   128,   129,   129,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   132,   132,   133,   133,
     134,   134,   135,   135,   136,   137,   138,   138,   139,   139,
     139,   139,   139,   140,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   142,   142,   142,   142,   143,   143,   144,
     144,   145,   145,   145,   146,   146,   148,   147,   147,   147,
     147,   147,   147,   149,   147,   151,   150,   152,   152,   153,
     154,   154,   154,   155,   155,   156,   157,   158,   158,   159,
     159,   161,   162,   160
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
       0,     1,     1,     0,     1,     1,     9,     0,     6,     0,
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
  "\"switch\"", "\"case\"", "\"default\"", "','", "'='", "XOR_EQUAL",
  "':'", "'|'", "'^'", "'&'", "'-'", "'+'", "'.'", "'*'", "'/'", "'%'",
  "'!'", "'~'", "'['", "'{'", "'}'", "UMINUS", "';'", "'('", "')'", "']'",
  "$accept", "program", "$@1", "statement_list", "statement", "block",
  "instantiation", "break", "continue", "critical_block", "object",
  "rvalue", "lvalue", "subscript", "switch_expr", "@2", "label",
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
        84,     0,    -1,    -1,    85,    86,    -1,    -1,    86,    87,
      -1,   139,    79,    -1,   132,    79,    -1,   137,    79,    -1,
     150,    79,    -1,   122,    79,    -1,   141,    -1,   152,    79,
      -1,   160,    -1,   153,    -1,   157,    -1,   126,    79,    -1,
      88,    -1,    92,    -1,   114,    79,    -1,    90,    79,    -1,
      91,    79,    -1,   119,    -1,   102,    -1,   147,    79,    -1,
      89,    79,    -1,    97,    -1,   130,    79,    -1,   131,    79,
      -1,    76,    86,    77,    -1,     4,    69,    47,    -1,     4,
      69,    47,    80,   143,    81,    -1,    22,    -1,    52,    -1,
      43,    88,    -1,     5,    -1,    53,    -1,     8,    -1,     6,
      -1,     7,    -1,    46,    -1,    39,    -1,    40,    -1,   113,
      -1,   111,    -1,    80,    94,    81,    -1,    96,    -1,   150,
      -1,    89,    -1,    93,    -1,   101,    -1,   130,    -1,   129,
      -1,   131,    -1,   128,    -1,   127,    -1,   137,    -1,   126,
      -1,   142,    -1,   122,    -1,   147,    -1,   120,    -1,     5,
      -1,   120,    -1,    96,    -1,    95,    75,    94,    82,    -1,
      -1,    57,    80,    94,    81,    76,    98,   100,    77,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
     120,    -1,    58,    99,    63,    86,    -1,    59,    63,    86,
      -1,   100,    58,    99,    63,    86,    -1,   100,    59,    63,
      86,    -1,    67,    94,    -1,    68,    94,    -1,    73,    94,
      -1,    74,    94,    -1,    54,     4,    76,   108,    77,    -1,
       5,    -1,    53,    -1,     8,    -1,     6,    -1,     7,    -1,
      46,    -1,    39,    -1,    40,    -1,   105,    -1,   104,    60,
     105,    -1,     5,    61,   103,    -1,     5,    -1,   107,    -1,
     106,    60,   107,    -1,     5,    61,   103,    -1,    -1,   110,
      -1,    -1,    55,    -1,    56,    -1,   109,   141,    -1,   109,
       3,   104,    79,    -1,   109,    41,   106,    79,    -1,   110,
     109,   141,    -1,   110,   109,     3,   104,    79,    -1,   110,
     109,    41,   106,    79,    -1,    75,   143,    82,    -1,     8,
      63,    94,    -1,   112,    60,     8,    63,    94,    -1,    76,
      63,    77,    -1,    76,   112,    77,    -1,    51,    94,    -1,
     116,    -1,   117,    -1,   116,   117,    -1,    49,    80,     5,
      81,    88,    -1,    -1,    48,    88,    -1,    50,    88,   115,
     118,    -1,    93,    69,     5,    -1,    93,    69,    53,    -1,
       4,    69,     5,    -1,     4,    69,    53,    -1,   120,    69,
       5,    -1,   120,    69,    53,    -1,    -1,   121,    69,     5,
      80,   143,    81,    -1,   121,    69,     5,    -1,   121,    69,
      53,    -1,    -1,    93,    69,     5,    80,   143,    81,   123,
     121,    -1,    -1,   120,    69,     5,    80,   143,    81,   124,
     121,    -1,    -1,     4,    69,     5,    80,   143,    81,   125,
     121,    -1,    93,    44,    -1,    93,    45,    -1,    44,    93,
      -1,    45,    93,    -1,   120,    44,    -1,   120,    45,    -1,
      44,   120,    -1,    45,   120,    -1,    94,    23,    94,    -1,
      94,    24,    94,    -1,    94,    17,    94,    -1,    94,    15,
      94,    -1,    94,    16,    94,    -1,    94,    14,    94,    -1,
      94,    31,    94,    -1,    94,    33,    94,    -1,    94,    32,
      94,    -1,    94,    34,    94,    -1,    94,    68,    94,    -1,
      94,    67,    94,    -1,    94,    70,    94,    -1,    94,    71,
      94,    -1,    94,    72,    94,    -1,    95,    26,    94,    -1,
      95,    29,    94,    -1,    95,    27,    94,    -1,    95,    28,
      94,    -1,    95,    30,    94,    -1,    94,    66,    94,    -1,
      94,    64,    94,    -1,    94,    65,    94,    -1,    94,    20,
      94,    -1,    94,    18,    94,    -1,    95,    35,    94,    -1,
      95,    36,    94,    -1,    95,    37,    94,    -1,    95,    21,
      94,    -1,    95,    19,    94,    -1,     3,   133,    -1,    41,
     135,    -1,   134,    -1,   133,    60,   134,    -1,     5,    61,
      94,    -1,     5,    -1,   136,    -1,   135,    60,   136,    -1,
      53,    61,    94,    -1,    95,    61,    94,    -1,     5,    -1,
     138,    69,     5,    -1,    25,   138,    69,    70,    -1,    25,
     138,    63,    70,    -1,    25,   138,    63,     5,    -1,    25,
     138,    63,     4,    -1,    25,   138,    -1,     5,    69,    69,
      69,    -1,    42,     5,    80,    81,    88,    -1,    42,     4,
      80,    81,    88,    -1,    42,    74,     4,    80,    81,    88,
      -1,    42,     5,    80,   140,    81,    88,    -1,    42,     4,
      80,   140,    81,    88,    -1,    42,     5,    80,   133,    81,
      88,    -1,    42,     4,    80,   133,    81,    88,    -1,    42,
       5,    80,   133,    60,   140,    81,    88,    -1,    42,     4,
      80,   133,    60,   140,    81,    88,    -1,    42,    80,    81,
      88,    -1,    42,    80,   140,    81,    88,    -1,    42,    80,
     133,    81,    88,    -1,    42,    80,   133,    60,   140,    81,
      88,    -1,    -1,   144,    -1,    94,    -1,   144,    60,    94,
      -1,    -1,   145,    80,   143,    81,    -1,   145,    75,    94,
      82,    -1,     5,    -1,   146,    63,     5,    -1,    -1,   146,
      63,     5,    80,   143,    81,   148,   145,    -1,   146,    63,
      53,    -1,   146,    63,     5,    -1,   146,    63,     4,    69,
      53,    -1,   146,    63,     4,    69,    47,    -1,   146,    63,
       4,    69,    47,    80,   143,    81,    -1,    -1,   146,    63,
       4,    69,     5,    80,   143,    81,   149,   121,    -1,    -1,
       5,    80,   143,    81,   151,   145,    -1,    38,    94,    -1,
      38,    -1,    10,    80,    94,    81,    88,    -1,    -1,   132,
      -1,   144,    -1,    -1,    94,    -1,   143,    -1,     9,    80,
     154,    79,   155,    79,   156,    81,    88,    -1,    -1,   158,
      13,    80,    94,    81,    88,    -1,    -1,    12,    88,    -1,
      -1,    -1,    11,    80,    94,    81,    88,   161,   158,   162,
     159,    -1
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
     808,   809,   811,   813,   814,   816,   818,   828,   829,   836,
     837,   840,   841,   842
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   220,   220,   220,   224,   225,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   255,
     259,   260,   264,   268,   272,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   315,   316,   317,   321,   325,   325,   329,   330,
     331,   332,   333,   334,   338,   339,   340,   341,   345,   346,
     347,   348,   352,   356,   357,   358,   359,   360,   361,   362,
     363,   367,   368,   372,   373,   377,   378,   382,   386,   387,
     391,   392,   393,   397,   398,   399,   400,   401,   402,   406,
     410,   411,   415,   416,   420,   424,   428,   429,   433,   437,
     438,   442,   446,   447,   448,   449,   450,   451,   455,   456,
     457,   458,   462,   462,   463,   463,   464,   464,   468,   469,
     470,   471,   472,   473,   474,   475,   479,   480,   481,   482,
     483,   484,   488,   489,   493,   494,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   524,   525,   529,   530,
     534,   535,   539,   540,   544,   548,   552,   553,   557,   558,
     559,   560,   561,   565,   569,   571,   573,   575,   577,   579,
     581,   583,   585,   590,   592,   594,   596,   601,   602,   606,
     607,   611,   612,   613,   617,   618,   622,   622,   623,   624,
     625,   626,   627,   628,   628,   632,   632,   636,   637,   641,
     645,   646,   647,   651,   652,   656,   660,   663,   665,   669,
     670,   674,   674,   674
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
  const int Parser::yylast_ = 1222;
  const int Parser::yynnts_ = 80;
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

