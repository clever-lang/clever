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

    { c.init(); }
    break;

  case 3:

    { c.emitAST((yysemantic_stack_[(2) - (2)].block)); }
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
  const short int Parser::yypact_ninf_ = -182;
  const short int
  Parser::yypact_[] =
  {
      -182,    37,  -182,  -182,   270,    38,   -21,    -9,  -182,  -182,
    -182,   -31,   -24,  -182,    47,     8,  -182,  -182,     7,     2,
      88,    45,    92,    92,  -182,    45,     8,  -182,  -182,   122,
       8,    10,     8,  -182,  -182,  -182,    48,    49,  -182,  -182,
     477,   -12,  -182,  -182,  -182,    50,  -182,  -182,    51,    54,
    -182,  -182,  -182,  -182,  -182,    55,    56,    57,  -182,  -182,
      58,    59,  -182,  -182,    81,    83,  -182,    21,     8,     8,
       8,  -182,    76,    62,    10,   477,    -6,  -182,  -182,  -182,
      86,    89,  -182,    64,     4,    15,  -182,  -182,  -182,  -182,
    -182,    96,   477,    72,   477,    67,    94,    95,  -182,   213,
      74,   101,   321,  -182,  -182,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,    18,     8,     8,     8,  -182,  -182,     8,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,     8,    38,    71,
      78,  -182,    79,   343,   399,    20,     8,     7,    39,   -27,
      45,   -40,    80,     8,  -182,    82,   110,    96,  -182,    27,
    -182,     8,     8,  -182,  -182,   156,  -182,   382,   382,   382,
     382,    13,    13,   655,   655,   566,   498,   577,   554,   588,
     644,   666,    -8,    -8,    84,  -182,  -182,  -182,  -182,   477,
     477,  -182,     8,     8,  -182,    45,    45,  -182,    87,  -182,
     477,  -182,    45,   -29,    85,   102,  -182,   165,    45,    45,
     164,   166,    45,  -182,  -182,   126,    28,    30,   477,   477,
     112,     8,    91,    93,  -182,  -182,  -182,  -182,   165,    45,
      45,   108,   103,  -182,  -182,    45,   104,  -182,   186,   114,
     126,  -182,    30,  -182,  -182,   113,     8,   118,  -182,  -182,
     120,  -182,   121,  -182,  -182,  -182,    45,  -182,    45,  -182,
    -182,   123,   199,   200,  -182,   477,  -182,     8,   193,    45,
    -182,  -182,  -182,   149,   151,  -182,   154,   152,  -182,   131,
     133,   210,  -182,   294,   199,   294,   200,  -182,     8,    45,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,   421,  -182,    45,  -182
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
      -182,  -182,  -182,   233,  -182,   -18,  -182,  -182,  -182,  -182,
    -182,    -4,    -2,  -182,  -182,  -182,  -182,  -182,    -5,  -182,
    -182,   -44,  -182,   -41,  -182,   -42,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,    90,  -182,  -182,  -182,     0,
       1,  -182,  -182,  -182,  -182,  -182,  -182,   -72,  -132,  -182,
      98,  -182,  -182,  -182,  -139,  -181,  -182,   -67,  -182,  -182,
      19,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182
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
        40,   142,    41,    87,    48,    49,   191,    91,    83,   204,
     149,    75,   151,     6,     7,     8,     9,    10,   207,    97,
      89,    90,    92,    60,   184,   197,   198,   139,   102,   228,
     -58,   -60,   137,   243,   241,   126,   127,     3,   -54,   -54,
     205,   126,   127,   208,    64,   149,    67,   128,    16,    17,
     -54,    69,    73,    71,   229,    22,    23,    24,    70,   260,
     123,   124,   125,    80,    28,   143,   144,   154,   232,   -58,
     -60,   140,   244,    68,   185,   191,   203,   141,   120,   121,
     122,   123,   124,   125,    84,    30,    74,   150,   199,   252,
      32,    98,   153,    86,    85,    40,   191,    41,    88,    48,
      49,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,    60,   186,
     187,   188,   202,    86,   189,   222,   223,    93,   103,   104,
     129,   130,   206,   190,   131,   132,   133,   134,   135,   136,
     137,   138,   200,   145,    84,   146,   148,   147,   155,   210,
     159,   160,   161,   192,   247,   164,   162,   218,   219,   165,
     193,   212,   194,   209,   211,   220,   221,  -142,   230,   231,
     238,   149,   236,   246,   248,   255,   249,   225,   226,   105,
     106,   107,   108,   109,   227,   110,   256,   258,   111,   112,
     233,   234,    83,   264,   237,   259,   113,   114,   115,   116,
     279,   266,   267,   272,   269,   273,   276,   280,   283,   284,
     286,   253,   254,   285,   287,   288,     5,   257,     6,     7,
       8,     9,    10,   289,    11,    12,   117,   118,   119,   120,
     121,   122,   123,   124,   125,     4,    13,   261,   270,    14,
     271,   301,   265,   300,   302,   201,     0,   214,   235,     0,
       0,   282,    15,    16,    17,    18,     0,    19,    20,    21,
      22,    23,    24,     0,     0,     0,    25,    26,    27,    28,
      29,   304,     0,     5,     0,     6,     7,     8,     9,    10,
       0,    11,    12,     0,   303,     0,     0,   306,     0,     0,
      30,    31,     0,    13,   163,    32,    14,     0,     0,     0,
     291,   292,   293,   294,     0,     0,     0,     0,     0,    15,
      16,    17,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,     0,    25,    26,    27,    28,    29,     0,     0,
       0,     0,     0,     0,   295,   296,   105,   106,   107,   108,
     109,     0,   110,   297,     0,   111,   112,    30,    31,     0,
     298,     0,    32,   113,   114,   115,   116,     0,   105,   106,
     107,   108,   109,     0,   110,     0,     0,   111,   112,     0,
       0,     0,     0,     0,     0,   113,   114,   115,   116,     0,
       0,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,     0,  -143,  -143,  -143,
    -143,   109,     0,   110,   166,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   105,   106,   107,   108,   109,     0,
     110,     0,     0,   111,   112,     0,   195,     0,     0,     0,
       0,   113,   114,   115,   116,     0,   105,   106,   107,   108,
     109,     0,   110,     0,     0,   111,   112,   120,   121,   122,
     123,   124,   125,   113,   114,   115,   116,     0,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   196,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   105,   106,   107,   108,   109,     0,   110,     0,
       0,   111,   112,     0,   305,     0,     0,     0,     0,   113,
     114,   115,   116,   105,   106,   107,   108,   109,     0,   110,
       0,     0,   111,   112,     0,     0,     0,     0,     0,     0,
     113,     0,   115,   116,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   105,
     106,   107,   108,   109,     0,   110,     0,     0,   111,   112,
       0,   105,   106,   107,   108,   109,   113,   110,   115,     0,
     111,   112,   105,   106,   107,   108,   109,     0,   110,     0,
     115,   111,   112,   105,   106,   107,   108,   109,     0,   110,
       0,     0,   111,   112,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   125,     0,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,   125,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,   118,   119,   120,   121,   122,   123,   124,   125,   105,
     106,   107,   108,   109,     0,   110,     0,     0,   111,   112,
     105,   106,   107,   108,   109,     0,   110,     0,     0,  -143,
    -143,   105,   106,   107,   108,   109,     0,   110,     0,     0,
     111,   112,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   120,
     121,   122,   123,   124,   125,     0,     0,     0,     0,     0,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,   120,   121,   122,   123,   124,   125
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         4,    68,     4,    21,     4,     4,   138,    25,     6,   148,
       6,    15,    84,     5,     6,     7,     8,     9,    58,     9,
      22,    23,    26,     4,     6,     5,     6,     6,    32,    58,
       3,     3,    59,     3,   215,    47,    48,     0,    47,    48,
      67,    47,    48,    83,     6,     6,    67,    59,    40,    41,
      59,    82,    44,     6,    83,    47,    48,    49,    82,   240,
      68,    69,    70,    56,    56,    69,    70,    85,   207,    42,
      42,    50,    42,    82,    56,   207,   148,    56,    65,    66,
      67,    68,    69,    70,    82,    77,    78,    83,    68,   228,
      82,    81,    77,    78,     6,    99,   228,    99,     6,    99,
      99,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,    99,   123,
     124,   125,    83,    78,   128,   192,   193,     5,    80,    80,
      80,    80,   150,   137,    80,    80,    80,    80,    80,    80,
      59,    58,   146,    67,    82,    59,    82,    58,    52,   153,
      78,    84,    58,    82,   221,    81,    61,   161,   162,    58,
      82,    51,    83,    83,    82,     9,    82,    80,    83,    67,
      44,     6,     6,    61,    83,    67,    83,   195,   196,    15,
      16,    17,    18,    19,   202,    21,    83,    83,    24,    25,
     208,   209,     6,    80,   212,    81,    32,    33,    34,    35,
     267,    83,    82,    80,    83,     6,     6,    14,    59,    58,
      58,   229,   230,    59,    83,    82,     3,   235,     5,     6,
       7,     8,     9,    13,    11,    12,    62,    63,    64,    65,
      66,    67,    68,    69,    70,     2,    23,   242,   256,    26,
     258,   285,   246,   284,   286,   147,    -1,   157,    84,    -1,
      -1,   269,    39,    40,    41,    42,    -1,    44,    45,    46,
      47,    48,    49,    -1,    -1,    -1,    53,    54,    55,    56,
      57,   289,    -1,     3,    -1,     5,     6,     7,     8,     9,
      -1,    11,    12,    -1,   288,    -1,    -1,   305,    -1,    -1,
      77,    78,    -1,    23,    81,    82,    26,    -1,    -1,    -1,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,    39,
      40,    41,    42,    -1,    44,    45,    46,    47,    48,    49,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    15,    16,    17,    18,
      19,    -1,    21,    49,    -1,    24,    25,    77,    78,    -1,
      56,    -1,    82,    32,    33,    34,    35,    -1,    15,    16,
      17,    18,    19,    -1,    21,    -1,    -1,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
      18,    19,    -1,    21,    83,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    15,    16,    17,    18,    19,    -1,
      21,    -1,    -1,    24,    25,    -1,    83,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    -1,    15,    16,    17,    18,
      19,    -1,    21,    -1,    -1,    24,    25,    65,    66,    67,
      68,    69,    70,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    15,    16,    17,    18,    19,    -1,    21,    -1,
      -1,    24,    25,    -1,    83,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    15,    16,    17,    18,    19,    -1,    21,
      -1,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    15,
      16,    17,    18,    19,    -1,    21,    -1,    -1,    24,    25,
      -1,    15,    16,    17,    18,    19,    32,    21,    34,    -1,
      24,    25,    15,    16,    17,    18,    19,    -1,    21,    -1,
      34,    24,    25,    15,    16,    17,    18,    19,    -1,    21,
      -1,    -1,    24,    25,    -1,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    15,
      16,    17,    18,    19,    -1,    21,    -1,    -1,    24,    25,
      15,    16,    17,    18,    19,    -1,    21,    -1,    -1,    24,
      25,    15,    16,    17,    18,    19,    -1,    21,    -1,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    70
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    86,    87,     0,    88,     3,     5,     6,     7,     8,
       9,    11,    12,    23,    26,    39,    40,    41,    42,    44,
      45,    46,    47,    48,    49,    53,    54,    55,    56,    57,
      77,    78,    82,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,   113,   116,   117,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   136,   138,   140,   141,
     145,   147,   148,   151,     6,   132,   133,    67,    82,    82,
      82,     6,   137,    44,    78,    96,    97,   124,   125,   145,
      56,   134,   135,     6,    82,     6,    78,    90,     6,    97,
      97,    90,    96,     5,    96,   142,   143,     9,    81,    88,
     114,   115,    96,    80,    80,    15,    16,    17,    18,    19,
      21,    24,    25,    32,    33,    34,    35,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    47,    48,    59,    80,
      80,    80,    80,    80,    80,    80,    80,    59,    58,     6,
      50,    56,   142,    96,    96,    67,    59,    58,    82,     6,
      83,   132,   139,    77,    90,    52,   118,   119,   120,    78,
      84,    58,    61,    81,    81,    58,    83,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,     6,    56,    96,    96,    96,    96,
      96,   133,    82,    82,    83,    83,    83,     5,     6,    68,
      96,   135,    83,   132,   139,    67,    90,    58,    83,    83,
      96,    82,    51,   121,   120,    99,   100,   101,    96,    96,
       9,    82,   142,   142,   146,    90,    90,    90,    58,    83,
      83,    67,   139,    90,    90,    84,     6,    90,    44,   111,
     112,   140,   102,     3,    42,   103,    61,   142,    83,    83,
     144,   152,   139,    90,    90,    67,    83,    90,    83,    81,
     140,   103,   104,   105,    80,    96,    83,    82,   149,    83,
      90,    90,    80,     6,   107,   108,     6,   109,   110,   142,
      14,   153,    90,    59,    58,    59,    58,    83,    82,    13,
     150,     6,     7,     8,     9,    40,    41,    49,    56,   106,
     108,   106,   110,    96,    90,    83,    90
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
      37,    33,   126,   314,   315,   316,   317,    91,   123,   318,
      59,   125,    40,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    85,    87,    86,    88,    88,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    90,    91,    91,    92,    93,    94,
      94,    95,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    97,    98,    99,    99,   101,   100,
     102,   100,   104,   103,   105,   103,   106,   106,   106,   106,
     106,   106,   106,   106,   107,   107,   108,   108,   109,   109,
     110,   111,   111,   112,   112,   113,   114,   115,   115,   116,
     116,   117,   118,   119,   119,   120,   121,   121,   122,   123,
     123,   123,   123,   124,   124,   125,   125,   125,   125,   126,
     126,   126,   126,   126,   126,   127,   127,   128,   128,   129,
     129,   129,   129,   129,   130,   130,   130,   130,   130,   131,
     131,   132,   132,   133,   133,   134,   134,   135,   136,   137,
     137,   138,   138,   138,   139,   140,   140,   140,   140,   141,
     141,   141,   141,   142,   142,   143,   143,   144,   144,   146,
     145,   147,   147,   148,   149,   149,   150,   150,   152,   153,
     151
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
    "\"end of file\"", "error", "$undefined", "\"var\"", "\"exit\"",
  "\"type specification\"", "\"identifier\"", "\"number\"",
  "\"float-number\"", "\"string\"", "\"for\"", "\"while\"", "\"if\"",
  "\"else\"", "\"else if\"", "\"<=\"", "\">=\"", "\"<\"", "\">\"",
  "\">>\"", "\">>=\"", "\"<<\"", "\"<<=\"", "\"break\"", "\"==\"",
  "\"!=\"", "\"import\"", "\"+=\"", "\"*=\"", "\"/=\"", "\"-=\"", "\"%=\"",
  "\"||\"", "\"or\"", "\"&&\"", "\"and\"", "\"&=\"", "\"|=\"", "\"^=\"",
  "\"return\"", "\"true\"", "\"false\"", "\"const\"", "\"print\"",
  "\"function\"", "\"spawn\"", "\"critical\"", "\"++\"", "\"--\"",
  "\"null\"", "\"new\"", "\"finally\"", "\"catch\"", "\"try\"",
  "\"throw\"", "\"continue\"", "\"constant identifier\"", "\"class\"",
  "','", "'='", "XOR_EQUAL", "':'", "'|'", "'^'", "'&'", "'-'", "'+'",
  "'.'", "'*'", "'/'", "'%'", "'!'", "'~'", "DEEPCOPY", "COPY",
  "DECREMENT", "INCREMENT", "'['", "'{'", "UMINUS", "';'", "'}'", "'('",
  "')'", "']'", "$accept", "program", "$@1", "statement_list", "statement",
  "block", "instantiation", "break", "continue", "thread_block",
  "critical_block", "rvalue", "lvalue", "class_def", "class_attr_decl",
  "class_attr_list", "@2", "@3", "non_empty_class_attr_list", "@4", "@5",
  "attr_rvalue", "class_attr_decl_list", "class_attr_decl_impl",
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
        86,     0,    -1,    -1,    87,    88,    -1,    -1,    88,    89,
      -1,   138,    80,    -1,   131,    80,    -1,   136,    80,    -1,
     145,    80,    -1,   124,    80,    -1,   140,    -1,   147,    80,
      -1,   151,    -1,   148,    -1,   125,    80,    -1,    90,    -1,
      94,    -1,    95,    -1,   117,    80,    -1,    92,    80,    -1,
      93,    80,    -1,   122,    -1,    98,    -1,    78,    88,    81,
      -1,     5,    67,    50,    -1,     5,    67,    50,    82,   142,
      83,    -1,    23,    -1,    55,    -1,    45,     6,    90,    -1,
      45,     6,    77,    96,    84,    90,    -1,    46,    90,    -1,
       6,    -1,    56,    -1,     9,    -1,     7,    -1,     8,    -1,
      49,    -1,    40,    -1,    41,    -1,   129,    -1,   128,    -1,
     130,    -1,   127,    -1,   126,    -1,   125,    -1,   145,    -1,
     141,    -1,    91,    -1,   123,    -1,   124,    -1,   113,    -1,
     116,    -1,    82,    96,    83,    -1,     6,    -1,    57,     5,
      78,    99,   111,    81,    -1,    -1,   100,    -1,    -1,   101,
     103,    80,    -1,    -1,   100,   102,   103,    80,    -1,    -1,
       3,   104,   107,    -1,    -1,    42,   105,   109,    -1,     6,
      -1,    56,    -1,     9,    -1,     7,    -1,     8,    -1,    49,
      -1,    40,    -1,    41,    -1,   108,    -1,   107,    58,   108,
      -1,     6,    59,   106,    -1,     6,    -1,   110,    -1,   109,
      58,   110,    -1,     6,    59,   106,    -1,    -1,   112,    -1,
     140,    -1,   112,   140,    -1,    77,   142,    84,    -1,   115,
      -1,     9,    61,    96,    -1,   115,    58,     9,    61,    96,
      -1,    78,    81,    -1,    78,   114,    81,    -1,    54,    96,
      -1,   119,    -1,   120,    -1,   119,   120,    -1,    52,    82,
       6,    83,    90,    -1,    -1,    51,    90,    -1,    53,    90,
     118,   121,    -1,    96,    67,     6,    -1,     5,    67,     6,
      -1,    96,    67,    56,    -1,     5,    67,    56,    -1,    96,
      67,     6,    82,   142,    83,    -1,     5,    67,     6,    82,
     142,    83,    -1,    97,    47,    -1,    97,    48,    -1,    47,
      97,    -1,    48,    97,    -1,    96,    24,    96,    -1,    96,
      25,    96,    -1,    96,    18,    96,    -1,    96,    16,    96,
      -1,    96,    17,    96,    -1,    96,    15,    96,    -1,    96,
      32,    96,    -1,    96,    34,    96,    -1,    96,    33,    96,
      -1,    96,    35,    96,    -1,    96,    66,    96,    -1,    96,
      65,    96,    -1,    96,    68,    96,    -1,    96,    69,    96,
      -1,    96,    70,    96,    -1,    96,    64,    96,    -1,    96,
      62,    96,    -1,    96,    63,    96,    -1,    96,    21,    96,
      -1,    96,    19,    96,    -1,     3,   132,    -1,    42,   134,
      -1,   133,    -1,   132,    58,   133,    -1,     6,    59,    96,
      -1,     6,    -1,   135,    -1,   134,    58,   135,    -1,    56,
      59,    96,    -1,    97,    59,    96,    -1,     6,    -1,   137,
      67,     6,    -1,    26,   137,    67,    68,    -1,    26,   137,
      67,     6,    -1,    26,   137,    67,     5,    -1,     6,    67,
      67,    67,    -1,    44,     6,    82,    83,    90,    -1,    44,
       6,    82,   139,    83,    90,    -1,    44,     6,    82,   132,
      83,    90,    -1,    44,     6,    82,   132,    58,   139,    83,
      90,    -1,    44,    82,    83,    90,    -1,    44,    82,   139,
      83,    90,    -1,    44,    82,   132,    83,    90,    -1,    44,
      82,   132,    58,   139,    83,    90,    -1,    -1,   143,    -1,
      96,    -1,   143,    58,    96,    -1,    -1,   144,    82,   142,
      83,    -1,    -1,     6,    82,   142,    83,   146,   144,    -1,
      39,    96,    -1,    39,    -1,    11,    82,    96,    83,    90,
      -1,    -1,   149,    14,    82,    96,    83,    90,    -1,    -1,
      13,    90,    -1,    -1,    -1,    12,    82,    96,    83,    90,
     152,   149,   153,   150,    -1
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
         0,   213,   213,   213,   217,   218,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   243,   247,   248,   252,   256,   261,
     262,   266,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   295,   299,   303,   304,   308,   308,
     309,   309,   313,   313,   314,   314,   318,   319,   320,   321,
     322,   323,   324,   325,   329,   330,   334,   335,   339,   340,
     344,   348,   349,   353,   354,   358,   362,   366,   367,   371,
     372,   376,   380,   384,   385,   389,   393,   394,   398,   402,
     403,   404,   405,   409,   410,   414,   415,   416,   417,   421,
     422,   423,   424,   425,   426,   430,   431,   435,   436,   440,
     441,   442,   443,   444,   448,   449,   450,   451,   452,   456,
     457,   461,   462,   466,   467,   471,   472,   476,   480,   484,
     485,   489,   490,   491,   495,   499,   501,   503,   505,   510,
     512,   514,   516,   521,   522,   526,   527,   531,   532,   536,
     536,   540,   541,   545,   549,   551,   556,   557,   561,   562,
     561
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
      82,    83,    68,    66,    58,    65,    67,    69,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    80,
       2,    59,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    77,     2,    84,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    78,    62,    81,    72,     2,     2,     2,
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
      55,    56,    57,    60,    73,    74,    75,    76,    79
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 736;
  const int Parser::yynnts_ = 69;
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

