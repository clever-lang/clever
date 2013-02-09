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

    { (yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(3) - (3)].block), (yysemantic_stack_[(3) - (2)].ident), yyloc); }
    break;

  case 30:

    { (yyval.threadblock) = new ast::ThreadBlock((yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].node), yyloc); }
    break;

  case 31:

    { (yyval.criticalblock) = new ast::CriticalBlock((yysemantic_stack_[(2) - (2)].block), yyloc); }
    break;

  case 53:

    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 55:

    { (yyval.class_) = new ast::ClassDef((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 56:

    { (yyval.narray) = NULL; }
    break;

  case 58:

    { (yyval.narray) = new ast::NodeArray(yyloc); }
    break;

  case 59:

    { (yyval.narray) = (yysemantic_stack_[(3) - (1)].narray); }
    break;

  case 60:

    { (yyval.narray) = (yysemantic_stack_[(1) - (1)].narray); }
    break;

  case 62:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 64:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 74:

    { (yysemantic_stack_[(1) - (0)].narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 75:

    { (yysemantic_stack_[(3) - (0)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 76:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), false, yyloc); }
    break;

  case 77:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(1) - (1)].ident), NULL, false, yyloc);     }
    break;

  case 78:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 79:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 80:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), true, yyloc);   }
    break;

  case 81:

    { (yyval.narray) = NULL; }
    break;

  case 83:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].fdecl)); }
    break;

  case 84:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].fdecl)); }
    break;

  case 85:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Array"), (yysemantic_stack_[(3) - (2)].narray), yyloc); }
    break;

  case 87:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(3) - (1)].strlit)); (yyval.narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 88:

    { (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (3)].strlit)); (yysemantic_stack_[(5) - (1)].narray)->append((yysemantic_stack_[(5) - (5)].node));                                 }
    break;

  case 89:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), NULL, yyloc); }
    break;

  case 90:

    { (yyval.inst) = new ast::Instantiation(CSTRING("Map"), (yysemantic_stack_[(3) - (2)].narray), yyloc);   }
    break;

  case 91:

    { (yyval.throw_) = new ast::Throw((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 93:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].catch_)); }
    break;

  case 94:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].catch_));                                 }
    break;

  case 95:

    { (yyval.catch_) = new ast::Catch((yysemantic_stack_[(5) - (3)].ident), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 96:

    { (yyval.block) = NULL; }
    break;

  case 97:

    { (yyval.block) = (yysemantic_stack_[(2) - (2)].block);   }
    break;

  case 98:

    { (yyval.except) = new ast::Try((yysemantic_stack_[(4) - (2)].block), (yysemantic_stack_[(4) - (3)].narray), (yysemantic_stack_[(4) - (4)].block), yyloc); }
    break;

  case 99:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 100:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 101:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 102:

    { (yyval.property) = new ast::Property((yysemantic_stack_[(3) - (1)].type), (yysemantic_stack_[(3) - (3)].ident), yyloc); }
    break;

  case 103:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 104:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 105:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 106:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 107:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 108:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 109:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 110:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 111:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 112:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 113:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 114:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 115:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 116:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 117:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 118:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 119:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 120:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 121:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 122:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 123:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 124:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 125:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 126:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 127:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 128:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 129:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 130:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 131:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 132:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 133:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 134:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 135:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 136:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 137:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 138:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 139:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 140:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 141:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 142:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 143:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 144:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 145:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); }
    break;

  case 146:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); }
    break;

  case 147:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); }
    break;

  case 148:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); }
    break;

  case 149:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, yyloc); }
    break;

  case 150:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), yyloc); }
    break;

  case 151:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); }
    break;

  case 152:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), yyloc); }
    break;

  case 153:

    { (yyval.narray) = NULL; }
    break;

  case 155:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 156:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 157:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 158:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 159:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 160:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 161:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 162:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 163:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 165:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 166:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 167:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 168:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 169:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 170:

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
  const short int Parser::yypact_ninf_ = -172;
  const short int
  Parser::yypact_[] =
  {
      -172,    46,  -172,  -172,   299,    52,    20,    82,  -172,  -172,
    -172,   -19,    -3,  -172,    53,     8,  -172,  -172,     6,    14,
      85,    16,    86,    86,  -172,    16,     8,  -172,  -172,    94,
       8,    43,     8,  -172,  -172,  -172,    45,    51,  -172,  -172,
     525,    -5,  -172,  -172,  -172,    56,  -172,  -172,    57,    58,
    -172,  -172,  -172,  -172,  -172,    59,    60,    62,  -172,  -172,
      63,    72,  -172,  -172,    73,    75,  -172,    22,     8,     8,
       8,  -172,    87,    71,    43,   525,    -7,  -172,  -172,  -172,
      96,    99,  -172,    76,     5,   -33,  -172,  -172,  -172,  -172,
    -172,   109,   525,    84,   525,    79,   107,   105,  -172,   221,
      88,   110,   371,  -172,  -172,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,    28,     8,     8,     8,  -172,  -172,     8,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,     8,    52,   100,
     101,  -172,    93,   393,   448,    21,     8,     6,    12,   -20,
      16,   -32,    95,     8,  -172,   102,   116,   109,  -172,    15,
    -172,     8,     8,  -172,  -172,   160,  -172,   155,   155,   155,
     155,    80,    80,   690,   690,   613,   546,   624,   601,   635,
     190,   701,    13,    13,   103,  -172,  -172,  -172,  -172,   525,
     525,  -172,     8,     8,  -172,    16,    16,  -172,   108,  -172,
     525,  -172,    16,   -22,    98,   120,  -172,   182,    16,    16,
     302,   183,    16,  -172,  -172,   147,    32,    33,   525,   525,
     133,     8,   112,   114,  -172,  -172,  -172,  -172,   182,    16,
      16,   131,   117,  -172,  -172,    16,   118,  -172,   192,   122,
     147,  -172,    33,  -172,  -172,   124,     8,   128,  -172,  -172,
     123,  -172,   134,  -172,  -172,  -172,    16,  -172,    16,  -172,
    -172,   138,   225,   228,  -172,   525,  -172,     8,   222,    16,
    -172,  -172,  -172,   177,   180,  -172,   184,   181,  -172,   158,
     164,   233,  -172,    24,   225,    24,   228,  -172,     8,    16,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,   470,  -172,    16,  -172
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    32,    35,    36,
      34,     0,     0,    27,     0,   162,    38,    39,     0,     0,
       0,     0,     0,     0,    37,     0,     0,    28,    33,     0,
     153,     4,     0,     5,    16,    48,     0,     0,    17,    18,
       0,     0,    23,    51,    52,     0,    22,    49,    50,    45,
      44,    43,    41,    40,    42,     0,     0,     0,    11,    47,
      46,     0,    14,    13,   134,   129,   131,     0,   153,     0,
       0,   139,     0,     0,     0,   161,     0,    50,    45,    46,
       0,   130,   135,     0,     0,     0,     4,    31,    54,   107,
     108,     0,    91,     0,   155,     0,   154,     0,    89,     0,
       0,    86,     0,    20,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   106,     0,    19,
      10,    15,     7,     8,     6,     9,    12,     0,     0,   100,
      25,   102,     0,     0,     0,     0,     0,     0,     0,   134,
       0,     0,     0,     0,    29,     0,    96,    92,    93,    56,
      85,     0,     0,    24,    90,     0,    53,   114,   112,   113,
     111,   128,   127,   109,   110,   115,   117,   116,   118,   125,
     126,   124,   120,   119,    99,   101,   121,   122,   123,   138,
     133,   132,   153,   153,   159,     0,     0,   143,   140,   141,
     137,   136,     0,     0,     0,     0,   149,     0,     0,     0,
       0,     0,     0,    98,    94,    81,    57,     0,   156,    87,
       0,   153,     0,     0,   157,   163,   168,   145,     0,     0,
       0,     0,     0,   151,   150,     0,     0,    97,     0,     0,
      82,    83,     0,    62,    64,     0,     0,     0,   104,    26,
     160,   164,     0,   147,   146,   144,     0,    30,     0,    55,
      84,     0,     0,     0,    59,    88,   103,   153,   169,     0,
     152,    95,    61,    77,    63,    74,     0,    65,    78,     0,
       0,   166,   148,     0,     0,     0,     0,   158,     0,     0,
     170,    66,    69,    70,    68,    72,    73,    71,    67,    76,
      75,    80,    79,     0,   167,     0,   165
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -172,  -172,  -172,   245,  -172,   -18,  -172,  -172,  -172,  -172,
    -172,    -4,    -2,  -172,  -172,  -172,  -172,  -172,     7,  -172,
    -172,   -37,  -172,   -34,  -172,   -17,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,   113,  -172,  -172,  -172,     0,
       1,  -172,  -172,  -172,  -172,  -172,  -172,   -76,  -132,  -172,
     130,  -172,  -172,  -172,  -139,  -171,  -172,   -67,  -172,  -172,
      19,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,    99,    33,    34,    35,    36,    37,    38,
      39,    94,    76,    42,   215,   216,   217,   242,   245,   262,
     263,   299,   274,   275,   277,   278,   239,   240,    43,   100,
     101,    44,    45,   156,   157,   158,   213,    46,    47,    77,
      78,    50,    51,    52,    53,    54,    55,    65,    66,    81,
      82,    56,    72,    57,   152,    58,    59,    95,    96,   250,
      79,   224,    61,    62,   268,   290,    63,   251,   281
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -143;
  const short int
  Parser::yytable_[] =
  {
        40,   142,    41,    87,    48,    49,   191,    91,   151,   204,
     149,    75,     6,     7,     8,     9,    10,   149,   -58,    83,
      89,    90,    92,    60,   207,   197,   198,   139,   102,   291,
     292,   293,   294,   184,   228,   -60,   243,   137,   126,   127,
     126,   127,   153,    86,   241,   205,     3,    16,    17,   208,
      73,    97,   128,    22,    23,    24,   -58,    64,    71,   229,
      80,    69,    28,   295,   296,   143,   144,   154,   232,   260,
     140,   297,   203,   -60,   244,   191,   141,    70,   298,   123,
     124,   125,   185,    30,    74,    67,   150,   199,    32,   252,
      85,    88,    86,   202,    84,    40,   191,    41,    93,    48,
      49,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,    60,   186,
     187,   188,    98,   103,   189,   222,   223,   -54,   -54,   104,
     137,   138,   206,   190,   129,   130,   131,   132,   133,   -54,
     134,   135,   200,   120,   121,   122,   123,   124,   125,   210,
     136,    84,   145,   146,   247,   147,   148,   218,   219,   155,
     159,   160,    68,   161,   162,   212,   165,   164,   220,  -143,
    -143,  -143,  -143,   109,   194,   110,   209,   225,   226,   230,
     192,   193,   211,   221,   227,   231,  -142,   149,   236,   238,
     233,   234,   246,   248,   237,   249,   255,    83,   256,   258,
     279,   259,   264,   267,   105,   106,   107,   108,   109,   266,
     110,   253,   254,   111,   112,   269,   272,   257,   120,   121,
     122,   123,   124,   125,     5,     6,     7,     8,     9,    10,
     273,    11,    12,   276,   283,   280,   284,   286,   270,   287,
     271,   285,   265,    13,   288,   289,    14,     4,   301,   261,
     300,   282,   119,   120,   121,   122,   123,   124,   125,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,   302,
     214,   304,    25,    26,    27,    28,    29,   201,     0,     0,
       0,     0,     0,     0,   303,     0,     0,   306,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    31,     0,     0,
     163,    32,     5,     6,     7,     8,     9,    10,     0,    11,
      12,     0,     0,     0,     0,     0,   105,   106,   107,   108,
     109,    13,   110,     0,    14,   111,   112,     0,     0,     0,
       0,     0,     0,   113,   114,   115,   116,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,     0,     0,
      25,    26,    27,    28,    29,     0,     0,     0,     0,     0,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,     0,     0,     0,    30,    31,     0,     0,     0,    32,
       0,     0,     0,     0,   235,   105,   106,   107,   108,   109,
       0,   110,     0,     0,   111,   112,     0,     0,     0,     0,
       0,     0,   113,   114,   115,   116,     0,   105,   106,   107,
     108,   109,     0,   110,     0,     0,   111,   112,     0,     0,
       0,     0,     0,     0,   113,   114,   115,   116,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   166,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   105,   106,   107,   108,   109,     0,   110,     0,
       0,   111,   112,     0,   195,     0,     0,     0,     0,   113,
     114,   115,   116,     0,   105,   106,   107,   108,   109,     0,
     110,     0,     0,   111,   112,     0,     0,     0,     0,     0,
       0,   113,   114,   115,   116,     0,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   196,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   105,
     106,   107,   108,   109,     0,   110,     0,     0,   111,   112,
       0,   305,     0,     0,     0,     0,   113,   114,   115,   116,
     105,   106,   107,   108,   109,     0,   110,     0,     0,   111,
     112,     0,     0,     0,     0,     0,     0,   113,     0,   115,
     116,     0,     0,     0,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   105,   106,   107,   108,   109,
       0,   110,     0,     0,   111,   112,     0,   105,   106,   107,
     108,   109,   113,   110,   115,     0,   111,   112,   105,   106,
     107,   108,   109,     0,   110,     0,   115,   111,   112,   105,
     106,   107,   108,   109,     0,   110,     0,     0,   111,   112,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,   118,   119,   120,   121,
     122,   123,   124,   125,   105,   106,   107,   108,   109,     0,
     110,     0,     0,  -143,  -143,   105,   106,   107,   108,   109,
       0,   110,     0,     0,   111,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   120,   121,   122,   123,   124,   125,     0,
       0,     0,     0,     0,   120,   121,   122,   123,   124,   125
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,    68,     4,    21,     4,     4,   138,    25,    84,   148,
       5,    15,     4,     5,     6,     7,     8,     5,     3,     5,
      22,    23,    26,     4,    56,     4,     5,     5,    32,     5,
       6,     7,     8,     5,    56,     3,     3,    57,    45,    46,
      45,    46,    75,    76,   215,    65,     0,    39,    40,    81,
      42,     8,    57,    45,    46,    47,    41,     5,     5,    81,
      54,    80,    54,    39,    40,    69,    70,    85,   207,   240,
      48,    47,   148,    41,    41,   207,    54,    80,    54,    66,
      67,    68,    54,    75,    76,    65,    81,    66,    80,   228,
       5,     5,    76,    81,    80,    99,   228,    99,     4,    99,
      99,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,    99,   123,
     124,   125,    79,    78,   128,   192,   193,    45,    46,    78,
      57,    56,   150,   137,    78,    78,    78,    78,    78,    57,
      78,    78,   146,    63,    64,    65,    66,    67,    68,   153,
      78,    80,    65,    57,   221,    56,    80,   161,   162,    50,
      76,    82,    80,    56,    59,    49,    56,    79,     8,    14,
      15,    16,    17,    18,    81,    20,    81,   195,   196,    81,
      80,    80,    80,    80,   202,    65,    78,     5,     5,    42,
     208,   209,    59,    81,   212,    81,    65,     5,    81,    81,
     267,    79,    78,    80,    14,    15,    16,    17,    18,    81,
      20,   229,   230,    23,    24,    81,    78,   235,    63,    64,
      65,    66,    67,    68,     3,     4,     5,     6,     7,     8,
       5,    10,    11,     5,    57,    13,    56,    56,   256,    81,
     258,    57,   246,    22,    80,    12,    25,     2,   285,   242,
     284,   269,    62,    63,    64,    65,    66,    67,    68,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,   286,
     157,   289,    51,    52,    53,    54,    55,   147,    -1,    -1,
      -1,    -1,    -1,    -1,   288,    -1,    -1,   305,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,    -1,
      79,    80,     3,     4,     5,     6,     7,     8,    -1,    10,
      11,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    22,    20,    -1,    25,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    -1,    82,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    81,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    81,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,
      34,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    14,    15,    16,
      17,    18,    31,    20,    33,    -1,    23,    24,    14,    15,
      16,    17,    18,    -1,    20,    -1,    33,    23,    24,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    -1,    -1,    -1,    61,    62,    63,    64,
      65,    66,    67,    68,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,    68
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    84,    85,     0,    86,     3,     4,     5,     6,     7,
       8,    10,    11,    22,    25,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    51,    52,    53,    54,    55,
      75,    76,    80,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,   111,   114,   115,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   134,   136,   138,   139,
     143,   145,   146,   149,     5,   130,   131,    65,    80,    80,
      80,     5,   135,    42,    76,    94,    95,   122,   123,   143,
      54,   132,   133,     5,    80,     5,    76,    88,     5,    95,
      95,    88,    94,     4,    94,   140,   141,     8,    79,    86,
     112,   113,    94,    78,    78,    14,    15,    16,    17,    18,
      20,    23,    24,    31,    32,    33,    34,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    45,    46,    57,    78,
      78,    78,    78,    78,    78,    78,    78,    57,    56,     5,
      48,    54,   140,    94,    94,    65,    57,    56,    80,     5,
      81,   130,   137,    75,    88,    50,   116,   117,   118,    76,
      82,    56,    59,    79,    79,    56,    81,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,     5,    54,    94,    94,    94,    94,
      94,   131,    80,    80,    81,    81,    81,     4,     5,    66,
      94,   133,    81,   130,   137,    65,    88,    56,    81,    81,
      94,    80,    49,   119,   118,    97,    98,    99,    94,    94,
       8,    80,   140,   140,   144,    88,    88,    88,    56,    81,
      81,    65,   137,    88,    88,    82,     5,    88,    42,   109,
     110,   138,   100,     3,    41,   101,    59,   140,    81,    81,
     142,   150,   137,    88,    88,    65,    81,    88,    81,    79,
     138,   101,   102,   103,    78,    94,    81,    80,   147,    81,
      88,    88,    78,     5,   105,   106,     5,   107,   108,   140,
      13,   151,    88,    57,    56,    57,    56,    81,    80,    12,
     148,     5,     6,     7,     8,    39,    40,    47,    54,   104,
     106,   104,   108,    94,    88,    81,    88
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
     126,   312,   313,   314,   315,    91,   123,   316,    59,   125,
      40,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    83,    85,    84,    86,    86,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    89,    89,    90,    91,    92,
      92,    93,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    95,    96,    97,    97,    99,    98,
     100,    98,   102,   101,   103,   101,   104,   104,   104,   104,
     104,   104,   104,   104,   105,   105,   106,   106,   107,   107,
     108,   109,   109,   110,   110,   111,   112,   113,   113,   114,
     114,   115,   116,   117,   117,   118,   119,   119,   120,   121,
     121,   121,   121,   122,   122,   123,   123,   123,   123,   124,
     124,   124,   124,   124,   124,   125,   125,   126,   126,   127,
     127,   127,   127,   127,   128,   128,   128,   128,   128,   129,
     129,   130,   130,   131,   131,   132,   132,   133,   134,   135,
     135,   136,   136,   136,   137,   138,   138,   138,   138,   139,
     139,   139,   139,   140,   140,   141,   141,   142,   142,   144,
     143,   145,   145,   146,   147,   147,   148,   148,   150,   151,
     149
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     1,     2,     1,     1,     2,     1,     1,     1,     2,
       2,     2,     1,     1,     3,     3,     6,     1,     1,     3,
       6,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     6,     0,     1,     0,     3,
       0,     4,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     1,     1,     3,
       3,     0,     1,     1,     2,     3,     1,     3,     5,     2,
       3,     2,     1,     1,     2,     5,     0,     2,     4,     3,
       3,     3,     3,     6,     6,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     3,     3,     1,     1,     3,     3,     3,     1,
       3,     4,     4,     4,     4,     5,     6,     6,     8,     4,
       5,     5,     7,     0,     1,     1,     3,     0,     4,     0,
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
  "\"constant identifier\"", "\"class\"", "','", "'='", "XOR_EQUAL", "':'",
  "'|'", "'^'", "'&'", "'-'", "'+'", "'.'", "'*'", "'/'", "'%'", "'!'",
  "'~'", "DEEPCOPY", "COPY", "DECREMENT", "INCREMENT", "'['", "'{'",
  "UMINUS", "';'", "'}'", "'('", "')'", "']'", "$accept", "program", "$@1",
  "statement_list", "statement", "block", "instantiation", "break",
  "continue", "thread_block", "critical_block", "rvalue", "lvalue",
  "class_def", "class_attr_decl", "class_attr_list", "@2", "@3",
  "non_empty_class_attr_list", "@4", "@5", "attr_rvalue",
  "class_attr_decl_list", "class_attr_decl_impl",
  "class_attr_const_decl_list", "class_attr_const_decl_impl",
  "class_method_decl", "class_method_list", "array", "key_value_list",
  "non_empty_key_value_list", "map", "throw", "catch", "not_empty_catch",
  "catch_impl", "finally", "try_catch_finally", "property_access", "mcall",
  "inc_dec", "comparison", "boolean", "logic", "arithmetic", "bitwise",
  "variable_decl", "variable_decl_list", "variable_decl_impl",
  "const_decl_list", "const_decl_impl", "assignment", "import_ident_list",
  "import", "vararg", "fdecl", "anonymous_fdecl", "call_args",
  "non_empty_call_args", "fcall_chain", "fcall", "@6", "return_stmt",
  "while", "elseif", "else", "if", "@7", "@8", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        84,     0,    -1,    -1,    85,    86,    -1,    -1,    86,    87,
      -1,   136,    78,    -1,   129,    78,    -1,   134,    78,    -1,
     143,    78,    -1,   122,    78,    -1,   138,    -1,   145,    78,
      -1,   149,    -1,   146,    -1,   123,    78,    -1,    88,    -1,
      92,    -1,    93,    -1,   115,    78,    -1,    90,    78,    -1,
      91,    78,    -1,   120,    -1,    96,    -1,    76,    86,    79,
      -1,     4,    65,    48,    -1,     4,    65,    48,    80,   140,
      81,    -1,    22,    -1,    53,    -1,    43,     5,    88,    -1,
      43,     5,    75,    94,    82,    88,    -1,    44,    88,    -1,
       5,    -1,    54,    -1,     8,    -1,     6,    -1,     7,    -1,
      47,    -1,    39,    -1,    40,    -1,   127,    -1,   126,    -1,
     128,    -1,   125,    -1,   124,    -1,   123,    -1,   143,    -1,
     139,    -1,    89,    -1,   121,    -1,   122,    -1,   111,    -1,
     114,    -1,    80,    94,    81,    -1,     5,    -1,    55,     4,
      76,    97,   109,    79,    -1,    -1,    98,    -1,    -1,    99,
     101,    78,    -1,    -1,    98,   100,   101,    78,    -1,    -1,
       3,   102,   105,    -1,    -1,    41,   103,   107,    -1,     5,
      -1,    54,    -1,     8,    -1,     6,    -1,     7,    -1,    47,
      -1,    39,    -1,    40,    -1,   106,    -1,   105,    56,   106,
      -1,     5,    57,   104,    -1,     5,    -1,   108,    -1,   107,
      56,   108,    -1,     5,    57,   104,    -1,    -1,   110,    -1,
     138,    -1,   110,   138,    -1,    75,   140,    82,    -1,   113,
      -1,     8,    59,    94,    -1,   113,    56,     8,    59,    94,
      -1,    76,    79,    -1,    76,   112,    79,    -1,    52,    94,
      -1,   117,    -1,   118,    -1,   117,   118,    -1,    50,    80,
       5,    81,    88,    -1,    -1,    49,    88,    -1,    51,    88,
     116,   119,    -1,    94,    65,     5,    -1,     4,    65,     5,
      -1,    94,    65,    54,    -1,     4,    65,    54,    -1,    94,
      65,     5,    80,   140,    81,    -1,     4,    65,     5,    80,
     140,    81,    -1,    95,    45,    -1,    95,    46,    -1,    45,
      95,    -1,    46,    95,    -1,    94,    23,    94,    -1,    94,
      24,    94,    -1,    94,    17,    94,    -1,    94,    15,    94,
      -1,    94,    16,    94,    -1,    94,    14,    94,    -1,    94,
      31,    94,    -1,    94,    33,    94,    -1,    94,    32,    94,
      -1,    94,    34,    94,    -1,    94,    64,    94,    -1,    94,
      63,    94,    -1,    94,    66,    94,    -1,    94,    67,    94,
      -1,    94,    68,    94,    -1,    94,    62,    94,    -1,    94,
      60,    94,    -1,    94,    61,    94,    -1,    94,    20,    94,
      -1,    94,    18,    94,    -1,     3,   130,    -1,    41,   132,
      -1,   131,    -1,   130,    56,   131,    -1,     5,    57,    94,
      -1,     5,    -1,   133,    -1,   132,    56,   133,    -1,    54,
      57,    94,    -1,    95,    57,    94,    -1,     5,    -1,   135,
      65,     5,    -1,    25,   135,    65,    66,    -1,    25,   135,
      65,     5,    -1,    25,   135,    65,     4,    -1,     5,    65,
      65,    65,    -1,    42,     5,    80,    81,    88,    -1,    42,
       5,    80,   137,    81,    88,    -1,    42,     5,    80,   130,
      81,    88,    -1,    42,     5,    80,   130,    56,   137,    81,
      88,    -1,    42,    80,    81,    88,    -1,    42,    80,   137,
      81,    88,    -1,    42,    80,   130,    81,    88,    -1,    42,
      80,   130,    56,   137,    81,    88,    -1,    -1,   141,    -1,
      94,    -1,   141,    56,    94,    -1,    -1,   142,    80,   140,
      81,    -1,    -1,     5,    80,   140,    81,   144,   142,    -1,
      38,    94,    -1,    38,    -1,    10,    80,    94,    81,    88,
      -1,    -1,   147,    13,    80,    94,    81,    88,    -1,    -1,
      12,    88,    -1,    -1,    -1,    11,    80,    94,    81,    88,
     150,   147,   151,   148,    -1
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
     106,   108,   110,   112,   114,   116,   118,   120,   122,   124,
     126,   128,   130,   132,   136,   138,   145,   146,   148,   149,
     153,   154,   159,   160,   164,   165,   169,   171,   173,   175,
     177,   179,   181,   183,   185,   187,   191,   195,   197,   199,
     203,   207,   208,   210,   212,   215,   219,   221,   225,   231,
     234,   238,   241,   243,   245,   248,   254,   255,   258,   263,
     267,   271,   275,   279,   286,   293,   296,   299,   302,   305,
     309,   313,   317,   321,   325,   329,   333,   337,   341,   345,
     349,   353,   357,   361,   365,   369,   373,   377,   381,   385,
     388,   391,   393,   397,   401,   403,   405,   409,   413,   417,
     419,   423,   428,   433,   438,   443,   449,   456,   463,   472,
     477,   483,   489,   497,   498,   500,   502,   506,   507,   512,
     513,   520,   523,   525,   531,   532,   539,   540,   543,   544,
     545
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   211,   211,   211,   215,   216,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   241,   245,   246,   250,   254,   259,
     260,   264,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   293,   297,   301,   302,   306,   306,
     307,   307,   311,   311,   312,   312,   316,   317,   318,   319,
     320,   321,   322,   323,   327,   328,   332,   333,   337,   338,
     342,   346,   347,   351,   352,   356,   360,   364,   365,   369,
     370,   374,   378,   382,   383,   387,   391,   392,   396,   400,
     401,   402,   403,   407,   408,   412,   413,   414,   415,   419,
     420,   421,   422,   423,   424,   428,   429,   433,   434,   438,
     439,   440,   441,   442,   446,   447,   448,   449,   450,   454,
     455,   459,   460,   464,   465,   469,   470,   474,   478,   482,
     483,   487,   488,   489,   493,   497,   499,   501,   503,   508,
     510,   512,   514,   519,   520,   524,   525,   529,   530,   534,
     534,   538,   539,   543,   547,   549,   554,   555,   559,   560,
     559
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
      80,    81,    66,    64,    56,    63,    65,    67,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    78,
       2,    57,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    75,     2,    82,    61,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    76,    60,    79,    70,     2,     2,     2,
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
      55,    58,    71,    72,    73,    74,    77
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 769;
  const int Parser::yynnts_ = 69;
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

