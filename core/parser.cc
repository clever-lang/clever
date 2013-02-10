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

  case 42:

    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 56:

    { (yyval.class_) = new ast::ClassDef((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 57:

    { (yyval.narray) = NULL; }
    break;

  case 59:

    { (yyval.narray) = new ast::NodeArray(yyloc); }
    break;

  case 60:

    { (yyval.narray) = (yysemantic_stack_[(3) - (1)].narray); }
    break;

  case 61:

    { (yyval.narray) = (yysemantic_stack_[(1) - (1)].narray); }
    break;

  case 63:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 65:

    { (yyval.narray) = (yysemantic_stack_[(1) - (0)].narray); }
    break;

  case 75:

    { (yysemantic_stack_[(1) - (0)].narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 76:

    { (yysemantic_stack_[(3) - (0)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 77:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), false, yyloc); }
    break;

  case 78:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(1) - (1)].ident), NULL, false, yyloc);     }
    break;

  case 79:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].attr)); }
    break;

  case 80:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].attr)); }
    break;

  case 81:

    { (yyval.attr) = new ast::AttrDecl((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), true, yyloc);   }
    break;

  case 82:

    { (yyval.narray) = NULL; }
    break;

  case 84:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].fdecl)); }
    break;

  case 85:

    { (yysemantic_stack_[(2) - (1)].narray)->append((yysemantic_stack_[(2) - (2)].fdecl)); }
    break;

  case 86:

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
  const short int Parser::yypact_ninf_ = -207;
  const short int
  Parser::yypact_[] =
  {
      -207,    43,  -207,  -207,   277,    44,    -2,   -43,  -207,  -207,
    -207,   -15,     0,  -207,    53,    22,  -207,  -207,    20,    77,
      78,    14,    32,    32,  -207,    14,    22,  -207,  -207,    85,
      22,    17,    22,  -207,  -207,    21,    58,  -207,  -207,    -4,
      39,  -207,  -207,  -207,    60,  -207,    66,    69,    70,    71,
      72,  -207,    80,    83,  -207,  -207,    54,    34,  -207,    88,
      22,    22,    22,  -207,   107,   108,    89,   102,    17,  -207,
      35,   481,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,   124,   110,  -207,   105,   -28,  -207,  -207,  -207,
    -207,  -207,   135,   481,   113,   481,   104,   133,   130,   117,
     223,   -25,   325,  -207,  -207,  -207,  -207,   188,    22,  -207,
    -207,  -207,  -207,  -207,  -207,  -207,  -207,    22,    44,   116,
     118,   346,   403,     9,    12,     5,    19,    22,    22,    22,
      22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,    22,    22,    20,     6,
      22,  -207,   120,   146,   135,  -207,    13,  -207,    22,    22,
    -207,  -207,   199,  -207,  -207,   139,   481,   481,  -207,    22,
    -207,    14,    14,  -207,   119,  -207,   116,   141,  -207,    -6,
      14,   -23,   129,   139,  -207,   240,   240,   240,   240,   111,
     111,   226,   226,   569,   502,   580,   557,   591,   646,   657,
      41,    41,  -207,  -207,  -207,   481,  -207,    14,   -20,   137,
     138,   207,    14,  -207,  -207,   178,    16,    29,   481,   481,
     161,    22,   143,  -207,  -207,  -207,    22,   166,  -207,   219,
      14,    14,  -207,   219,    14,    14,    14,   156,  -207,   150,
     178,  -207,    29,  -207,  -207,   159,    22,   158,  -207,   160,
    -207,   168,   194,   180,  -207,  -207,   192,  -207,  -207,  -207,
      14,  -207,  -207,   195,   281,   290,  -207,   481,  -207,    22,
     287,  -207,  -207,    14,    14,  -207,  -207,   245,   253,  -207,
     252,   255,  -207,   233,   235,   302,  -207,  -207,   134,   281,
     134,   290,  -207,    22,    14,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,   424,  -207,
      14,  -207
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
     153,     4,     0,     5,    16,     0,     0,    17,    18,     0,
       0,    23,    41,    40,     0,    22,     0,     0,     0,     0,
       0,    11,     0,     0,    14,    13,   134,   129,   131,     0,
     153,     0,     0,   139,     0,     0,    32,     0,     0,    52,
      43,   161,    53,    54,    49,    48,    47,    45,    44,    46,
      51,    50,     0,   130,   135,     0,     0,     4,    31,    32,
     107,   108,     0,    91,     0,   155,     0,   154,     0,     0,
       0,     0,     0,    20,    21,   105,   106,     0,     0,    19,
      10,    15,     7,     8,     6,     9,    12,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,     0,    96,    92,    93,    57,    86,     0,     0,
      89,    24,     0,    90,    42,     0,   138,   133,   132,   153,
     159,     0,     0,   143,   140,   141,   100,    25,   102,   134,
       0,     0,     0,    99,   101,   114,   112,   113,   111,   128,
     127,   109,   110,   115,   117,   116,   118,   125,   126,   124,
     120,   119,   121,   122,   123,   137,   136,     0,     0,     0,
       0,     0,     0,    98,    94,    82,    58,     0,   156,    87,
       0,   153,     0,   157,   163,   168,   153,     0,   149,     0,
       0,     0,   145,     0,     0,     0,     0,     0,    97,     0,
      83,    84,     0,    63,    65,     0,     0,     0,   104,   160,
     164,     0,     0,     0,   151,   150,     0,   147,   146,    30,
       0,    56,    85,     0,     0,     0,    60,    88,   103,   153,
     169,    26,   144,     0,     0,    95,    62,    78,    64,    75,
       0,    66,    79,     0,     0,   166,   152,   148,     0,     0,
       0,     0,   158,     0,     0,   170,    67,    70,    71,    69,
      73,    74,    72,    68,    77,    76,    81,    80,     0,   167,
       0,   165
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -207,  -207,  -207,   323,  -207,   -21,  -207,  -207,  -207,  -207,
    -207,    -1,   -14,  -207,  -207,  -207,  -207,  -207,  -207,    84,
    -207,  -207,    37,  -207,    45,  -207,    42,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,  -207,   181,  -207,  -207,  -207,     1,
       2,  -207,  -207,  -207,  -207,  -207,  -207,  -105,   -95,  -207,
     189,  -207,  -207,  -207,  -142,  -206,  -207,   -58,  -207,  -207,
       4,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   100,    33,    34,    69,    35,    36,    37,
      38,    70,    95,    40,    41,   215,   216,   217,   242,   245,
     264,   265,   304,   278,   279,   281,   282,   239,   240,    42,
     101,    43,    44,   153,   154,   155,   213,    45,    72,    73,
      74,    75,    76,    77,    78,    79,    48,    57,    58,    83,
      84,    49,    64,    50,   182,    51,    80,    96,    97,   249,
      81,   223,    53,    54,   270,   295,    55,   250,   285
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -143;
  const short int
  Parser::yytable_[] =
  {
        88,    71,   120,    39,    92,    46,    47,   209,    52,   241,
     179,   179,    93,   173,   174,   -55,   -59,   176,   102,   -61,
     181,    90,    91,   168,   183,    98,    65,    66,     8,     9,
      10,   162,   243,   229,   262,    60,   233,    89,     8,     9,
      10,   105,   106,     3,   208,   150,    87,   121,   122,    56,
     163,   227,   117,   107,   -59,    59,   230,   -61,    63,   234,
     177,    16,    17,    61,    67,   151,   178,    22,    23,    24,
     244,    16,    17,   184,    82,   175,    28,    99,    62,    24,
     105,   106,    85,    86,   180,   207,    28,   253,    87,    94,
     118,   256,   126,   119,   166,    30,    68,   108,   103,    39,
      32,    46,    47,   167,    52,    30,    68,   144,   145,   146,
      32,   222,   117,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   168,   104,   210,   109,   168,   296,
     297,   298,   299,   110,   218,   219,   111,   112,   113,   114,
     224,   225,   127,   128,   129,   130,   131,   115,   132,   228,
     116,   133,   134,   247,   123,   124,   148,    60,   251,   135,
     136,   137,   138,   300,   301,   142,   143,   144,   145,   146,
     125,   302,   147,   149,   157,   152,   232,   156,   303,   158,
     159,   238,   160,   165,   169,   212,  -142,   170,   211,   139,
     140,   141,   142,   143,   144,   145,   146,   220,   231,   254,
     255,   283,   237,   257,   258,   259,   235,   221,   236,   226,
      19,   246,   248,   252,   179,   261,     5,     6,     7,     8,
       9,    10,   267,    11,    12,   260,   266,   268,   269,   275,
     127,   128,   129,   130,   131,    13,   132,   271,    14,  -143,
    -143,   272,   286,   287,  -143,  -143,  -143,  -143,   131,   273,
     132,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,   274,   276,   309,    25,    26,    27,    28,    29,   308,
       5,     6,     7,     8,     9,    10,   277,    11,    12,   311,
     142,   143,   144,   145,   146,   280,    30,    31,   161,    13,
     284,    32,    14,   288,   142,   143,   144,   145,   146,   289,
     290,   291,   292,   293,   294,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     4,   263,   306,    25,    26,
      27,    28,    29,   307,   305,   214,     0,   206,     0,   127,
     128,   129,   130,   131,     0,   132,     0,     0,   133,   134,
      30,    31,     0,     0,     0,    32,   135,   136,   137,   138,
     127,   128,   129,   130,   131,     0,   132,     0,     0,   133,
     134,     0,     0,     0,     0,     0,     0,   135,   136,   137,
     138,     0,     0,     0,     0,     0,   139,   140,   141,   142,
     143,   144,   145,   146,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,   139,   140,   141,
     142,   143,   144,   145,   146,     0,     0,   127,   128,   129,
     130,   131,     0,   132,     0,   171,   133,   134,     0,     0,
       0,     0,     0,     0,   135,   136,   137,   138,   127,   128,
     129,   130,   131,     0,   132,     0,     0,   133,   134,     0,
       0,     0,     0,     0,     0,   135,   136,   137,   138,     0,
       0,     0,     0,     0,   139,   140,   141,   142,   143,   144,
     145,   146,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   172,     0,     0,   139,   140,   141,   142,   143,
     144,   145,   146,     0,     0,   127,   128,   129,   130,   131,
       0,   132,     0,   310,   133,   134,     0,     0,     0,     0,
       0,     0,   135,   136,   137,   138,   127,   128,   129,   130,
     131,     0,   132,     0,     0,   133,   134,     0,     0,     0,
       0,     0,     0,   135,     0,   137,   138,     0,     0,     0,
       0,     0,   139,   140,   141,   142,   143,   144,   145,   146,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   127,   128,   129,   130,   131,     0,   132,     0,     0,
     133,   134,     0,   127,   128,   129,   130,   131,   135,   132,
     137,     0,   133,   134,   127,   128,   129,   130,   131,     0,
     132,     0,   137,   133,   134,   127,   128,   129,   130,   131,
       0,   132,     0,     0,   133,   134,     0,     0,   139,   140,
     141,   142,   143,   144,   145,   146,     0,     0,     0,     0,
     139,   140,   141,   142,   143,   144,   145,   146,     0,     0,
       0,   139,   140,   141,   142,   143,   144,   145,   146,     0,
       0,     0,     0,   140,   141,   142,   143,   144,   145,   146,
     127,   128,   129,   130,   131,     0,   132,     0,     0,   133,
     134,   127,   128,   129,   130,   131,     0,   132,     0,     0,
     133,   134,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
     142,   143,   144,   145,   146,     0,     0,     0,     0,     0,
       0,   142,   143,   144,   145,   146
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        21,    15,    60,     4,    25,     4,     4,   149,     4,   215,
       5,     5,    26,     4,     5,    58,     3,     5,    32,     3,
     125,    22,    23,   118,     5,     8,     4,     5,     6,     7,
       8,    56,     3,    56,   240,    78,    56,     5,     6,     7,
       8,    45,    46,     0,   149,    73,    74,    61,    62,     5,
      75,    57,    58,    57,    41,    57,    79,    41,     5,    79,
      48,    39,    40,    78,    42,    86,    54,    45,    46,    47,
      41,    39,    40,    54,    54,    66,    54,    60,    78,    47,
      45,    46,     5,     5,    79,    79,    54,   229,    74,     4,
      56,   233,    57,     5,   108,    73,    74,    58,    77,   100,
      78,   100,   100,   117,   100,    73,    74,    66,    67,    68,
      78,   169,    58,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   229,    77,   150,    77,   233,     5,
       6,     7,     8,    77,   158,   159,    77,    77,    77,    77,
     171,   172,    14,    15,    16,    17,    18,    77,    20,   180,
      77,    23,    24,   221,    57,    57,    56,    78,   226,    31,
      32,    33,    34,    39,    40,    64,    65,    66,    67,    68,
      78,    47,    58,    78,    80,    50,   207,    74,    54,    56,
      60,   212,    75,     5,    78,    49,    77,    79,    78,    61,
      62,    63,    64,    65,    66,    67,    68,     8,    79,   230,
     231,   269,     5,   234,   235,   236,    79,    78,    80,    78,
      42,    60,    79,    57,     5,    75,     3,     4,     5,     6,
       7,     8,   246,    10,    11,    79,    77,    79,    78,   260,
      14,    15,    16,    17,    18,    22,    20,    79,    25,    23,
      24,    57,   273,   274,    14,    15,    16,    17,    18,    79,
      20,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    79,    77,   294,    51,    52,    53,    54,    55,   293,
       3,     4,     5,     6,     7,     8,     5,    10,    11,   310,
      64,    65,    66,    67,    68,     5,    73,    74,    75,    22,
      13,    78,    25,    58,    64,    65,    66,    67,    68,    56,
      58,    56,    79,    78,    12,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     2,   242,   290,    51,    52,
      53,    54,    55,   291,   289,   154,    -1,   148,    -1,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      73,    74,    -1,    -1,    -1,    78,    31,    32,    33,    34,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    -1,    -1,    14,    15,    16,
      17,    18,    -1,    20,    -1,    79,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    -1,    -1,    14,    15,    16,    17,    18,
      -1,    20,    -1,    79,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    61,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    63,    64,    65,    66,    67,
      68,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    -1,    14,    15,    16,    17,    18,    31,    20,
      33,    -1,    23,    24,    14,    15,    16,    17,    18,    -1,
      20,    -1,    33,    23,    24,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    -1,    -1,    61,    62,
      63,    64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      61,    62,    63,    64,    65,    66,    67,    68,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    67,    68,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    82,    83,     0,    84,     3,     4,     5,     6,     7,
       8,    10,    11,    22,    25,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    51,    52,    53,    54,    55,
      73,    74,    78,    85,    86,    88,    89,    90,    91,    92,
      94,    95,   110,   112,   113,   118,   120,   121,   127,   132,
     134,   136,   141,   143,   144,   147,     5,   128,   129,    57,
      78,    78,    78,     5,   133,     4,     5,    42,    74,    87,
      92,    93,   119,   120,   121,   122,   123,   124,   125,   126,
     137,   141,    54,   130,   131,     5,     5,    74,    86,     5,
      92,    92,    86,    93,     4,    93,   138,   139,     8,    60,
      84,   111,    93,    77,    77,    45,    46,    57,    58,    77,
      77,    77,    77,    77,    77,    77,    77,    58,    56,     5,
     138,    93,    93,    57,    57,    78,    57,    14,    15,    16,
      17,    18,    20,    23,    24,    31,    32,    33,    34,    61,
      62,    63,    64,    65,    66,    67,    68,    58,    56,    78,
      73,    86,    50,   114,   115,   116,    74,    80,    56,    60,
      75,    75,    56,    75,    79,     5,    93,    93,   129,    78,
      79,    79,    79,     4,     5,    66,     5,    48,    54,     5,
      79,   128,   135,     5,    54,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,   131,    79,   128,   135,
      93,    78,    49,   117,   116,    96,    97,    98,    93,    93,
       8,    78,   138,   142,    86,    86,    78,    57,    86,    56,
      79,    79,    86,    56,    79,    79,    80,     5,    86,   108,
     109,   136,    99,     3,    41,   100,    60,   138,    79,   140,
     148,   138,    57,   135,    86,    86,   135,    86,    86,    86,
      79,    75,   136,   100,   101,   102,    77,    93,    79,    78,
     145,    79,    57,    79,    79,    86,    77,     5,   104,   105,
       5,   106,   107,   138,    13,   149,    86,    86,    58,    56,
      58,    56,    79,    78,    12,   146,     5,     6,     7,     8,
      39,    40,    47,    54,   103,   105,   103,   107,    93,    86,
      79,    86
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
     305,   306,   307,   308,   309,   310,    44,    46,    61,   311,
      58,   124,    94,    38,    45,    43,    42,    47,    37,    33,
     126,   312,   313,    91,   123,   125,   314,    59,    40,    41,
      93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    81,    83,    82,    84,    84,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    86,    87,    87,    88,    89,    90,
      90,    91,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    94,    95,    96,    96,    98,
      97,    99,    97,   101,   100,   102,   100,   103,   103,   103,
     103,   103,   103,   103,   103,   104,   104,   105,   105,   106,
     106,   107,   108,   108,   109,   109,   110,   111,   111,   112,
     112,   113,   114,   115,   115,   116,   117,   117,   118,   119,
     119,   119,   119,   120,   120,   121,   121,   121,   121,   122,
     122,   122,   122,   122,   122,   123,   123,   124,   124,   125,
     125,   125,   125,   125,   126,   126,   126,   126,   126,   127,
     127,   128,   128,   129,   129,   130,   130,   131,   132,   133,
     133,   134,   134,   134,   135,   136,   136,   136,   136,   137,
     137,   137,   137,   138,   138,   139,   139,   140,   140,   142,
     141,   143,   143,   144,   145,   145,   146,   146,   148,   149,
     147
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
       1,     1,     1,     1,     1,     1,     6,     0,     1,     0,
       3,     0,     4,     0,     3,     0,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     1,
       3,     3,     0,     1,     1,     2,     3,     3,     5,     3,
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
  "\"constant identifier\"", "\"class\"", "','", "'.'", "'='", "XOR_EQUAL",
  "':'", "'|'", "'^'", "'&'", "'-'", "'+'", "'*'", "'/'", "'%'", "'!'",
  "'~'", "DECREMENT", "INCREMENT", "'['", "'{'", "'}'", "UMINUS", "';'",
  "'('", "')'", "']'", "$accept", "program", "$@1", "statement_list",
  "statement", "block", "instantiation", "break", "continue",
  "thread_block", "critical_block", "object", "rvalue", "lvalue",
  "class_def", "class_attr_decl", "class_attr_list", "@2", "@3",
  "non_empty_class_attr_list", "@4", "@5", "attr_rvalue",
  "class_attr_decl_list", "class_attr_decl_impl",
  "class_attr_const_decl_list", "class_attr_const_decl_impl",
  "class_method_decl", "class_method_list", "array", "key_value_list",
  "map", "throw", "catch", "not_empty_catch", "catch_impl", "finally",
  "try_catch_finally", "property_access", "mcall", "inc_dec", "comparison",
  "boolean", "logic", "arithmetic", "bitwise", "variable_decl",
  "variable_decl_list", "variable_decl_impl", "const_decl_list",
  "const_decl_impl", "assignment", "import_ident_list", "import", "vararg",
  "fdecl", "anonymous_fdecl", "call_args", "non_empty_call_args",
  "fcall_chain", "fcall", "@6", "return_stmt", "while", "elseif", "else",
  "if", "@7", "@8", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        82,     0,    -1,    -1,    83,    84,    -1,    -1,    84,    85,
      -1,   134,    77,    -1,   127,    77,    -1,   132,    77,    -1,
     141,    77,    -1,   120,    77,    -1,   136,    -1,   143,    77,
      -1,   147,    -1,   144,    -1,   121,    77,    -1,    86,    -1,
      90,    -1,    91,    -1,   113,    77,    -1,    88,    77,    -1,
      89,    77,    -1,   118,    -1,    95,    -1,    74,    84,    75,
      -1,     4,    57,    48,    -1,     4,    57,    48,    78,   138,
      79,    -1,    22,    -1,    53,    -1,    43,     5,    86,    -1,
      43,     5,    73,    93,    80,    86,    -1,    44,    86,    -1,
       5,    -1,    54,    -1,     8,    -1,     6,    -1,     7,    -1,
      47,    -1,    39,    -1,    40,    -1,   112,    -1,   110,    -1,
      78,    93,    79,    -1,    92,    -1,   125,    -1,   124,    -1,
     126,    -1,   123,    -1,   122,    -1,   121,    -1,   141,    -1,
     137,    -1,    87,    -1,   119,    -1,   120,    -1,     5,    -1,
      55,     4,    74,    96,   108,    75,    -1,    -1,    97,    -1,
      -1,    98,   100,    77,    -1,    -1,    97,    99,   100,    77,
      -1,    -1,     3,   101,   104,    -1,    -1,    41,   102,   106,
      -1,     5,    -1,    54,    -1,     8,    -1,     6,    -1,     7,
      -1,    47,    -1,    39,    -1,    40,    -1,   105,    -1,   104,
      56,   105,    -1,     5,    58,   103,    -1,     5,    -1,   107,
      -1,   106,    56,   107,    -1,     5,    58,   103,    -1,    -1,
     109,    -1,   136,    -1,   109,   136,    -1,    73,   138,    80,
      -1,     8,    60,    93,    -1,   111,    56,     8,    60,    93,
      -1,    74,    60,    75,    -1,    74,   111,    75,    -1,    52,
      93,    -1,   115,    -1,   116,    -1,   115,   116,    -1,    50,
      78,     5,    79,    86,    -1,    -1,    49,    86,    -1,    51,
      86,   114,   117,    -1,    92,    57,     5,    -1,     4,    57,
       5,    -1,    92,    57,    54,    -1,     4,    57,    54,    -1,
      92,    57,     5,    78,   138,    79,    -1,     4,    57,     5,
      78,   138,    79,    -1,    92,    45,    -1,    92,    46,    -1,
      45,    92,    -1,    46,    92,    -1,    93,    23,    93,    -1,
      93,    24,    93,    -1,    93,    17,    93,    -1,    93,    15,
      93,    -1,    93,    16,    93,    -1,    93,    14,    93,    -1,
      93,    31,    93,    -1,    93,    33,    93,    -1,    93,    32,
      93,    -1,    93,    34,    93,    -1,    93,    65,    93,    -1,
      93,    64,    93,    -1,    93,    66,    93,    -1,    93,    67,
      93,    -1,    93,    68,    93,    -1,    93,    63,    93,    -1,
      93,    61,    93,    -1,    93,    62,    93,    -1,    93,    20,
      93,    -1,    93,    18,    93,    -1,     3,   128,    -1,    41,
     130,    -1,   129,    -1,   128,    56,   129,    -1,     5,    58,
      93,    -1,     5,    -1,   131,    -1,   130,    56,   131,    -1,
      54,    58,    93,    -1,    94,    58,    93,    -1,     5,    -1,
     133,    57,     5,    -1,    25,   133,    57,    66,    -1,    25,
     133,    57,     5,    -1,    25,   133,    57,     4,    -1,     5,
      57,    57,    57,    -1,    42,     5,    78,    79,    86,    -1,
      42,     5,    78,   135,    79,    86,    -1,    42,     5,    78,
     128,    79,    86,    -1,    42,     5,    78,   128,    56,   135,
      79,    86,    -1,    42,    78,    79,    86,    -1,    42,    78,
     135,    79,    86,    -1,    42,    78,   128,    79,    86,    -1,
      42,    78,   128,    56,   135,    79,    86,    -1,    -1,   139,
      -1,    93,    -1,   139,    56,    93,    -1,    -1,   140,    78,
     138,    79,    -1,    -1,     5,    78,   138,    79,   142,   140,
      -1,    38,    93,    -1,    38,    -1,    10,    78,    93,    79,
      86,    -1,    -1,   145,    13,    78,    93,    79,    86,    -1,
      -1,    12,    86,    -1,    -1,    -1,    11,    78,    93,    79,
      86,   148,   145,   149,   146,    -1
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
     128,   130,   132,   134,   136,   138,   140,   147,   148,   150,
     151,   155,   156,   161,   162,   166,   167,   171,   173,   175,
     177,   179,   181,   183,   185,   187,   189,   193,   197,   199,
     201,   205,   209,   210,   212,   214,   217,   221,   225,   231,
     235,   239,   242,   244,   246,   249,   255,   256,   259,   264,
     268,   272,   276,   280,   287,   294,   297,   300,   303,   306,
     310,   314,   318,   322,   326,   330,   334,   338,   342,   346,
     350,   354,   358,   362,   366,   370,   374,   378,   382,   386,
     389,   392,   394,   398,   402,   404,   406,   410,   414,   418,
     420,   424,   429,   434,   439,   444,   450,   457,   464,   473,
     478,   484,   490,   498,   499,   501,   503,   507,   508,   513,
     514,   521,   524,   526,   532,   533,   540,   541,   544,   545,
     546
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   212,   212,   212,   216,   217,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   242,   246,   247,   251,   255,   260,
     261,   265,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   298,   303,   307,   308,   312,
     312,   313,   313,   317,   317,   318,   318,   322,   323,   324,
     325,   326,   327,   328,   329,   333,   334,   338,   339,   343,
     344,   348,   352,   353,   357,   358,   362,   366,   367,   371,
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
       2,     2,     2,    69,     2,     2,     2,    68,    63,     2,
      78,    79,    66,    65,    56,    64,    57,    67,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,    77,
       2,    58,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    73,     2,    80,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    61,    75,    70,     2,     2,     2,
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
      55,    59,    71,    72,    76
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 725;
  const int Parser::yynnts_ = 69;
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

