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

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].node), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 113:

    { (yyval.mcall) = new ast::MethodCall((yysemantic_stack_[(6) - (1)].type), (yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].narray), yyloc); }
    break;

  case 114:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_INC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 115:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::POS_DEC, (yysemantic_stack_[(2) - (1)].node), yyloc); }
    break;

  case 116:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_INC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 117:

    { (yyval.inc_dec) = new ast::IncDec(ast::IncDec::PRE_DEC, (yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 118:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_EQUAL,   (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 119:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_NEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 120:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GREATER, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 121:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_GEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 122:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LESS,    (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 123:

    { (yyval.comp) = new ast::Comparison(ast::Comparison::COP_LEQUAL,  (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 124:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);  }
    break;

  case 125:

    { (yyval.boolean) = new ast::Boolean(ast::Boolean::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 126:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);      }
    break;

  case 127:

    { (yyval.logic) = new ast::Logic(ast::Logic::LOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 128:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_ADD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 129:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_SUB, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 130:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MUL, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 131:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_DIV, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 132:

    { (yyval.arithmetic) = new ast::Arithmetic(ast::Arithmetic::MOP_MOD, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 133:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_AND, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 134:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_OR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);     }
    break;

  case 135:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_XOR, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc);    }
    break;

  case 136:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_LSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 137:

    { (yyval.bitwise) = new ast::Bitwise(ast::Bitwise::BOP_RSHIFT, (yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 138:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 139:

    { (yyval.narray) = (yysemantic_stack_[(2) - (2)].narray); }
    break;

  case 140:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 141:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 142:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), false, yyloc); }
    break;

  case 143:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(1) - (1)].ident), new ast::Assignment((yysemantic_stack_[(1) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 144:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].vardecl)); }
    break;

  case 145:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].vardecl)); }
    break;

  case 146:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(3) - (1)].ident), new ast::Assignment((yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (3)].node), yyloc), true, yyloc); }
    break;

  case 147:

    { (yyval.assignment) = new ast::Assignment((yysemantic_stack_[(3) - (1)].node), (yysemantic_stack_[(3) - (3)].node), yyloc); }
    break;

  case 148:

    { (yyval.ident) = (yysemantic_stack_[(1) - (1)].ident); }
    break;

  case 149:

    { (yysemantic_stack_[(3) - (1)].ident)->append('.', (yysemantic_stack_[(3) - (3)].ident)); (yyval.ident) = (yysemantic_stack_[(3) - (1)].ident); }
    break;

  case 150:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), yyloc);     }
    break;

  case 151:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].ident), yyloc); }
    break;

  case 152:

    { (yyval.import) = new ast::Import((yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (4)].type), yyloc); }
    break;

  case 153:

    { (yyval.vardecl) = new ast::VariableDecl((yysemantic_stack_[(4) - (1)].ident), new ast::Assignment((yysemantic_stack_[(4) - (1)].ident), NULL, yyloc), false, yyloc); }
    break;

  case 154:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].ident), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, false, yyloc); }
    break;

  case 155:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(5) - (2)].type), NULL, (yysemantic_stack_[(5) - (5)].block), NULL, yyloc); }
    break;

  case 156:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), false, yyloc); }
    break;

  case 157:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), NULL, (yysemantic_stack_[(6) - (6)].block), (yysemantic_stack_[(6) - (4)].vardecl), yyloc); }
    break;

  case 158:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].ident), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, false, yyloc); }
    break;

  case 159:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(6) - (2)].type), (yysemantic_stack_[(6) - (4)].narray), (yysemantic_stack_[(6) - (6)].block), NULL, yyloc); }
    break;

  case 160:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].ident), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), false, yyloc); }
    break;

  case 161:

    { (yyval.fdecl) = new ast::FunctionDecl((yysemantic_stack_[(8) - (2)].type), (yysemantic_stack_[(8) - (4)].narray), (yysemantic_stack_[(8) - (8)].block), (yysemantic_stack_[(8) - (6)].vardecl), yyloc); }
    break;

  case 162:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(4) - (4)].block), NULL, true, yyloc); }
    break;

  case 163:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, NULL, (yysemantic_stack_[(5) - (5)].block), (yysemantic_stack_[(5) - (3)].vardecl), true, yyloc); }
    break;

  case 164:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(5) - (3)].narray), (yysemantic_stack_[(5) - (5)].block), NULL, true, yyloc); }
    break;

  case 165:

    { (yyval.fdecl) = new ast::FunctionDecl(NULL, (yysemantic_stack_[(7) - (3)].narray), (yysemantic_stack_[(7) - (7)].block), (yysemantic_stack_[(7) - (5)].vardecl), true, yyloc); }
    break;

  case 166:

    { (yyval.narray) = NULL; }
    break;

  case 168:

    { (yyval.narray) = new ast::NodeArray(yyloc); (yyval.narray)->append((yysemantic_stack_[(1) - (1)].node)); }
    break;

  case 169:

    { (yysemantic_stack_[(3) - (1)].narray)->append((yysemantic_stack_[(3) - (3)].node)); }
    break;

  case 170:

    { (yyval.fcall) = (yysemantic_stack_[(0) - (0)].fcall); }
    break;

  case 171:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].node), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 172:

    { (yyval.fcall) = new ast::FunctionCall((yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].narray), yyloc); }
    break;

  case 173:

    { (yyval.fcall) = (yysemantic_stack_[(6) - (6)].fcall); }
    break;

  case 174:

    { (yyval.ret) = new ast::Return((yysemantic_stack_[(2) - (2)].node), yyloc); }
    break;

  case 175:

    { (yyval.ret) = new ast::Return(NULL, yyloc); }
    break;

  case 176:

    { (yyval.while_loop) = new ast::While((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].block), yyloc); }
    break;

  case 178:

    { (yysemantic_stack_[(6) - (0)].ifcond)->addConditional((yysemantic_stack_[(6) - (4)].node), (yysemantic_stack_[(6) - (6)].block)); }
    break;

  case 179:

    { (yyval.ifcond) = (yysemantic_stack_[(0) - (0)].ifcond); }
    break;

  case 180:

    { (yysemantic_stack_[(2) - (0)].ifcond)->setElseNode((yysemantic_stack_[(2) - (2)].node)); (yyval.ifcond) = (yysemantic_stack_[(2) - (0)].ifcond); }
    break;

  case 181:

    { (yyval.ifcond) = new ast::If((yysemantic_stack_[(5) - (3)].node), (yysemantic_stack_[(5) - (5)].node), yyloc); }
    break;

  case 182:

    { (yyval.ifcond) = (yysemantic_stack_[(7) - (6)].ifcond); }
    break;

  case 183:

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
  const short int Parser::yypact_ninf_ = -197;
  const short int
  Parser::yypact_[] =
  {
      -197,    38,  -197,  -197,   331,    56,    17,    -9,  -197,  -197,
    -197,    -8,    19,  -197,    79,   174,  -197,  -197,    45,   120,
      97,    37,   115,   115,  -197,    37,   174,  -197,  -197,   103,
     174,     0,   174,  -197,  -197,    43,    75,  -197,  -197,   119,
      35,  -197,  -197,  -197,  -197,    78,  -197,  -197,    83,    86,
      88,    91,    98,  -197,   100,   101,  -197,  -197,   128,   132,
    -197,    26,   174,   174,   174,  -197,   133,   135,   121,   174,
     174,   174,   174,     0,  -197,   119,   550,   130,   134,  -197,
     137,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
     146,   148,  -197,   136,   139,   124,  -197,  -197,  -197,  -197,
    -197,   156,   550,   138,   550,   131,   155,   158,   145,   278,
     -19,   398,  -197,  -197,  -197,  -197,    29,   174,   174,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,   174,    56,   147,
    -197,   152,   453,   474,    15,    46,     8,  -197,  -197,  -197,
    -197,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,    45,    11,    12,   174,  -197,   149,   173,   156,
    -197,    25,  -197,   174,   174,  -197,  -197,   216,  -197,  -197,
     163,  -197,   550,     9,   550,  -197,   174,  -197,    37,    37,
    -197,   157,  -197,   164,    92,    37,   -17,   165,   436,   436,
     436,   436,   126,   126,   706,   706,   629,   605,   640,   617,
     695,   244,   717,   104,   104,  -197,  -197,  -197,   550,  -197,
      37,    40,   170,    37,    42,   171,   377,   236,    37,  -197,
    -197,   207,    49,    50,   550,   550,   192,   174,  -197,   175,
    -197,  -197,  -197,   174,   189,  -197,   250,    37,    37,  -197,
     250,    37,    37,  -197,   250,    37,    37,    37,   179,  -197,
     184,   207,  -197,    50,  -197,  -197,   190,   174,   193,  -197,
     195,  -197,   196,   201,   197,  -197,  -197,   198,  -197,  -197,
     202,  -197,  -197,  -197,    37,  -197,  -197,   194,   267,   275,
    -197,   550,  -197,   174,   274,  -197,  -197,    37,    37,    37,
    -197,  -197,   233,   235,  -197,   237,   239,  -197,   215,   217,
     284,  -197,  -197,  -197,    39,   267,    39,   275,  -197,   174,
      37,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,   529,  -197,    37,  -197
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     4,     1,     3,     0,     0,    32,    35,    36,
      34,     0,     0,    27,     0,   175,    38,    39,     0,     0,
       0,     0,     0,     0,    37,     0,     0,    28,    33,     0,
     166,     4,     0,     5,    16,     0,     0,    17,    18,     0,
       0,    59,    23,    41,    40,     0,    22,    58,     0,     0,
       0,     0,     0,    11,     0,     0,    14,    13,   143,   138,
     140,     0,   166,     0,     0,   148,     0,     0,     0,     0,
       0,     0,     0,     0,    53,    43,   174,     0,    56,    44,
      54,    55,    50,    49,    48,    46,    45,    47,    52,    51,
       0,   139,   144,     0,     0,     0,     4,    31,    32,   116,
     117,     0,   100,     0,   168,     0,   167,     0,     0,     0,
       0,     0,    20,    21,   114,   115,     0,     0,     0,    19,
      10,    15,     7,     8,     6,     9,    12,     0,     0,   109,
     111,     0,     0,     0,     0,     0,     0,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,   105,   101,
     102,    66,    95,     0,     0,    98,    24,     0,    99,    42,
     108,   110,   147,     0,   142,   141,   166,   172,     0,     0,
     152,   149,   150,    25,   143,     0,     0,     0,   123,   121,
     122,   120,   137,   136,   118,   119,   124,   126,   125,   127,
     134,   135,   133,   129,   128,   130,   131,   132,   146,   145,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   107,
     103,    91,    67,     0,   169,    96,     0,   166,    60,     0,
     170,   176,   181,   166,     0,   162,     0,     0,     0,   155,
       0,     0,     0,   154,     0,     0,     0,     0,     0,   106,
       0,    92,    93,     0,    72,    74,     0,     0,     0,   113,
     173,   177,     0,     0,     0,   164,   163,     0,   159,   157,
       0,   158,   156,    30,     0,    65,    94,     0,     0,     0,
      69,    97,   112,   166,   182,    26,   153,     0,     0,     0,
     104,    71,    87,    73,    84,     0,    75,    88,     0,     0,
     179,   165,   161,   160,     0,     0,     0,     0,   171,     0,
       0,   183,    76,    79,    80,    78,    82,    83,    81,    77,
      86,    85,    90,    89,     0,   180,     0,   178
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -197,  -197,  -197,   295,  -197,   -21,  -197,  -197,  -197,  -197,
    -197,    -1,   -14,     1,     2,  -197,  -197,  -197,  -197,  -197,
    -197,    41,  -197,  -197,   -18,  -197,   -13,  -197,   -16,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,   140,  -197,  -197,
       3,     5,     6,  -197,  -197,  -197,  -197,  -197,  -197,  -100,
     -98,  -197,   151,  -197,  -197,  -197,  -149,  -196,  -197,   -60,
    -197,  -197,     7,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     1,     2,   109,    33,    34,    74,    35,    36,    37,
      38,    75,   104,    77,    78,    79,    42,   231,   232,   233,
     263,   266,   288,   289,   330,   303,   304,   306,   307,   260,
     261,    43,   110,    44,    45,   168,   169,   170,   229,    46,
      80,    81,    82,    83,    84,    85,    86,    87,    50,    59,
      60,    91,    92,    51,    66,    52,   197,    53,    88,   105,
     106,   270,    89,   240,    55,    56,   294,   321,    57,   271,
     310
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int Parser::yytable_ninf_ = -152;
  const short int
  Parser::yytable_[] =
  {
        97,    76,   131,    39,   101,    40,    41,    47,   107,    48,
      49,    54,   102,   194,   222,   225,   194,   194,   111,   190,
     191,    99,   100,   141,   142,   143,   144,   145,   -68,   146,
     185,   129,   147,   148,   180,   262,   196,   177,     3,   246,
     149,   150,   151,   152,   322,   323,   324,   325,   -57,   132,
     133,   129,   -70,   264,   178,   137,   138,   139,   140,   108,
     247,    58,   -57,   221,   224,   286,   -68,    62,    63,   153,
     154,   155,   156,   157,   166,   158,   159,   160,   326,   327,
     130,   192,    61,   181,    65,   195,   328,   238,   220,   223,
     -70,   265,   117,   329,   193,    64,   250,   274,   254,    90,
     130,   277,    95,   182,   183,   280,   118,   103,    39,    96,
      40,    41,    47,   184,    48,    49,    54,   251,   112,   255,
      98,     8,     9,    10,    93,    94,   239,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   185,   127,
     113,   226,   185,   119,    16,    17,   185,   244,   120,   234,
     235,   121,    24,   122,   114,   115,   123,   241,   242,    28,
     158,   159,   160,   124,   245,   125,   126,   268,    67,     7,
       8,     9,    10,   272,   116,   127,    30,    73,   128,   156,
     157,    32,   158,   159,   160,   165,    96,   136,   134,   249,
     135,   118,   253,   161,   162,   -59,   167,   259,   -58,   172,
     171,   173,   163,    16,    17,   164,    68,   174,   175,    22,
      23,    24,   228,   186,   236,   227,   275,   276,    28,   187,
     278,   279,  -151,   308,   281,   282,   283,    69,    70,   237,
     243,   258,   248,    71,    72,    30,    73,   252,   256,    19,
      32,   267,   269,   291,   273,   194,   284,   285,   141,   142,
     143,   144,   145,   300,   146,   290,   296,   147,   148,   301,
     292,   293,   302,   295,   297,   298,   311,   312,   313,   299,
     305,     5,     6,     7,     8,     9,    10,   309,    11,    12,
     314,   315,   318,   319,   316,   317,   320,     4,   332,   335,
      13,   333,   331,    14,   287,   334,   155,   156,   157,   230,
     158,   159,   160,   219,     0,   337,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,     0,     0,    25,
      26,    27,    28,    29,     5,     6,     7,     8,     9,    10,
       0,    11,    12,     0,     0,     0,     0,     0,     0,    30,
      31,   176,     0,    13,    32,     0,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     0,
       0,     0,    25,    26,    27,    28,    29,     0,     0,     0,
       0,   141,   142,   143,   144,   145,     0,   146,     0,     0,
     147,   148,    30,    31,     0,     0,     0,    32,   149,   150,
     151,   152,   141,   142,   143,   144,   145,     0,   146,     0,
       0,   147,   148,     0,     0,     0,     0,     0,     0,   149,
     150,   151,   152,     0,     0,     0,     0,   153,   154,   155,
     156,   157,     0,   158,   159,   160,     0,     0,     0,     0,
    -152,  -152,  -152,  -152,   145,   257,   146,     0,   153,   154,
     155,   156,   157,     0,   158,   159,   160,   141,   142,   143,
     144,   145,     0,   146,     0,   179,   147,   148,     0,     0,
       0,     0,     0,     0,   149,   150,   151,   152,   141,   142,
     143,   144,   145,     0,   146,     0,     0,   147,   148,   156,
     157,     0,   158,   159,   160,   149,   150,   151,   152,     0,
       0,     0,     0,   153,   154,   155,   156,   157,     0,   158,
     159,   160,     0,     0,     0,     0,     0,     0,     0,     0,
     188,     0,     0,     0,   153,   154,   155,   156,   157,     0,
     158,   159,   160,   141,   142,   143,   144,   145,     0,   146,
       0,   189,   147,   148,     0,     0,     0,     0,     0,     0,
     149,   150,   151,   152,   141,   142,   143,   144,   145,     0,
     146,     0,     0,   147,   148,     0,     0,     0,     0,     0,
       0,   149,   150,   151,   152,     0,     0,     0,     0,   153,
     154,   155,   156,   157,     0,   158,   159,   160,     0,     0,
       0,     0,     0,     0,     0,     0,   336,     0,     0,     0,
     153,   154,   155,   156,   157,     0,   158,   159,   160,   141,
     142,   143,   144,   145,     0,   146,     0,     0,   147,   148,
       0,   141,   142,   143,   144,   145,   149,   146,   151,   152,
     147,   148,     0,   141,   142,   143,   144,   145,   149,   146,
     151,     0,   147,   148,   141,   142,   143,   144,   145,     0,
     146,     0,   151,   147,   148,   153,   154,   155,   156,   157,
       0,   158,   159,   160,     0,     0,     0,   153,   154,   155,
     156,   157,     0,   158,   159,   160,     0,     0,     0,   153,
     154,   155,   156,   157,     0,   158,   159,   160,     0,     0,
     153,   154,   155,   156,   157,     0,   158,   159,   160,   141,
     142,   143,   144,   145,     0,   146,     0,     0,   147,   148,
     141,   142,   143,   144,   145,     0,   146,     0,     0,  -152,
    -152,   141,   142,   143,   144,   145,     0,   146,     0,     0,
     147,   148,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   154,   155,   156,   157,
       0,   158,   159,   160,     0,     0,     0,     0,     0,   156,
     157,     0,   158,   159,   160,     0,     0,     0,     0,     0,
     156,   157,     0,   158,   159,   160
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        21,    15,    62,     4,    25,     4,     4,     4,     8,     4,
       4,     4,    26,     5,   163,   164,     5,     5,    32,     4,
       5,    22,    23,    14,    15,    16,    17,    18,     3,    20,
     128,     5,    23,    24,     5,   231,   136,    56,     0,    56,
      31,    32,    33,    34,     5,     6,     7,     8,    57,    63,
      64,     5,     3,     3,    73,    69,    70,    71,    72,    59,
      77,     5,    71,   163,   164,   261,    41,    76,    76,    60,
      61,    62,    63,    64,    95,    66,    67,    68,    39,    40,
      54,    66,    65,    54,     5,    77,    47,    78,    77,    77,
      41,    41,    57,    54,    48,    76,    56,   246,    56,    54,
      54,   250,     5,   117,   118,   254,    71,     4,   109,    72,
     109,   109,   109,   127,   109,   109,   109,    77,    75,    77,
       5,     6,     7,     8,     4,     5,   186,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   246,    57,
      75,   165,   250,    75,    39,    40,   254,    65,    75,   173,
     174,    75,    47,    75,    45,    46,    75,   188,   189,    54,
      66,    67,    68,    75,   195,    75,    75,   237,     4,     5,
       6,     7,     8,   243,    65,    57,    71,    72,    56,    63,
      64,    76,    66,    67,    68,    71,    72,    76,    65,   220,
      65,    71,   223,    57,    56,    71,    50,   228,    71,    78,
      72,    56,    76,    39,    40,    76,    42,    59,    73,    45,
      46,    47,    49,    76,     8,    76,   247,   248,    54,    77,
     251,   252,    75,   293,   255,   256,   257,    63,    64,    76,
      76,     5,    77,    69,    70,    71,    72,    77,    77,    42,
      76,    59,    77,   267,    65,     5,    77,    73,    14,    15,
      16,    17,    18,   284,    20,    75,    65,    23,    24,    75,
      77,    76,     5,    77,    77,    77,   297,   298,   299,    77,
       5,     3,     4,     5,     6,     7,     8,    13,    10,    11,
      57,    56,    77,    76,    57,    56,    12,     2,   316,   320,
      22,   317,   315,    25,   263,   319,    62,    63,    64,   169,
      66,    67,    68,   162,    -1,   336,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    51,
      52,    53,    54,    55,     3,     4,     5,     6,     7,     8,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    -1,    22,    76,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      -1,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    71,    72,    -1,    -1,    -1,    76,    31,    32,
      33,    34,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    -1,    66,    67,    68,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    78,    20,    -1,    60,    61,
      62,    63,    64,    -1,    66,    67,    68,    14,    15,    16,
      17,    18,    -1,    20,    -1,    77,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    14,    15,
      16,    17,    18,    -1,    20,    -1,    -1,    23,    24,    63,
      64,    -1,    66,    67,    68,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    -1,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    60,    61,    62,    63,    64,    -1,
      66,    67,    68,    14,    15,    16,    17,    18,    -1,    20,
      -1,    77,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    -1,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    -1,    66,    67,    68,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      -1,    14,    15,    16,    17,    18,    31,    20,    33,    34,
      23,    24,    -1,    14,    15,    16,    17,    18,    31,    20,
      33,    -1,    23,    24,    14,    15,    16,    17,    18,    -1,
      20,    -1,    33,    23,    24,    60,    61,    62,    63,    64,
      -1,    66,    67,    68,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    -1,    66,    67,    68,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    -1,    66,    67,    68,    -1,    -1,
      60,    61,    62,    63,    64,    -1,    66,    67,    68,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      14,    15,    16,    17,    18,    -1,    20,    -1,    -1,    23,
      24,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,
      -1,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    63,
      64,    -1,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      63,    64,    -1,    66,    67,    68
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
      92,    93,    95,   110,   112,   113,   118,   119,   120,   121,
     127,   132,   134,   136,   141,   143,   144,   147,     5,   128,
     129,    65,    76,    76,    76,     5,   133,     4,    42,    63,
      64,    69,    70,    72,    85,    90,    91,    92,    93,    94,
     119,   120,   121,   122,   123,   124,   125,   126,   137,   141,
      54,   130,   131,     4,     5,     5,    72,    84,     5,    90,
      90,    84,    91,     4,    91,   138,   139,     8,    59,    82,
     111,    91,    75,    75,    45,    46,    65,    57,    71,    75,
      75,    75,    75,    75,    75,    75,    75,    57,    56,     5,
      54,   138,    91,    91,    65,    65,    76,    91,    91,    91,
      91,    14,    15,    16,    17,    18,    20,    23,    24,    31,
      32,    33,    34,    60,    61,    62,    63,    64,    66,    67,
      68,    57,    56,    76,    76,    71,    84,    50,   114,   115,
     116,    72,    78,    56,    59,    73,    73,    56,    73,    77,
       5,    54,    91,    91,    91,   129,    76,    77,    77,    77,
       4,     5,    66,    48,     5,    77,   128,   135,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,   131,
      77,   128,   135,    77,   128,   135,    91,    76,    49,   117,
     116,    96,    97,    98,    91,    91,     8,    76,    78,   138,
     142,    84,    84,    76,    65,    84,    56,    77,    77,    84,
      56,    77,    77,    84,    56,    77,    77,    78,     5,    84,
     108,   109,   136,    99,     3,    41,   100,    59,   138,    77,
     140,   148,   138,    65,   135,    84,    84,   135,    84,    84,
     135,    84,    84,    84,    77,    73,   136,   100,   101,   102,
      75,    91,    77,    76,   145,    77,    65,    77,    77,    77,
      84,    75,     5,   104,   105,     5,   106,   107,   138,    13,
     149,    84,    84,    84,    57,    56,    57,    56,    77,    76,
      12,   146,     5,     6,     7,     8,    39,    40,    47,    54,
     103,   105,   103,   107,    91,    84,    77,    84
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
     119,   119,   120,   120,   121,   121,   121,   121,   122,   122,
     122,   122,   122,   122,   123,   123,   124,   124,   125,   125,
     125,   125,   125,   126,   126,   126,   126,   126,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   132,   133,   133,
     134,   134,   134,   135,   136,   136,   136,   136,   136,   136,
     136,   136,   137,   137,   137,   137,   138,   138,   139,   139,
     140,   140,   142,   141,   143,   143,   144,   145,   145,   146,
     146,   148,   149,   147
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
       3,     3,     6,     6,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     3,     3,     1,     1,     3,     3,     3,     1,     3,
       4,     4,     4,     4,     5,     5,     6,     6,     6,     6,
       8,     8,     4,     5,     5,     7,     0,     1,     1,     3,
       0,     4,     0,     6,     2,     1,     5,     0,     6,     0,
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
        80,     0,    -1,    -1,    81,    82,    -1,    -1,    82,    83,
      -1,   134,    75,    -1,   127,    75,    -1,   132,    75,    -1,
     141,    75,    -1,   120,    75,    -1,   136,    -1,   143,    75,
      -1,   147,    -1,   144,    -1,   121,    75,    -1,    84,    -1,
      88,    -1,    89,    -1,   113,    75,    -1,    86,    75,    -1,
      87,    75,    -1,   118,    -1,    95,    -1,    72,    82,    73,
      -1,     4,    65,    48,    -1,     4,    65,    48,    76,   138,
      77,    -1,    22,    -1,    53,    -1,    43,     5,    84,    -1,
      43,     5,    71,    91,    78,    84,    -1,    44,    84,    -1,
       5,    -1,    54,    -1,     8,    -1,     6,    -1,     7,    -1,
      47,    -1,    39,    -1,    40,    -1,   112,    -1,   110,    -1,
      76,    91,    77,    -1,    90,    -1,    94,    -1,   125,    -1,
     124,    -1,   126,    -1,   123,    -1,   122,    -1,   121,    -1,
     141,    -1,   137,    -1,    85,    -1,   119,    -1,   120,    -1,
      93,    -1,     5,    -1,   119,    -1,    93,    -1,    92,    71,
      91,    78,    -1,    63,    91,    -1,    64,    91,    -1,    69,
      91,    -1,    70,    91,    -1,    55,     4,    72,    96,   108,
      73,    -1,    -1,    97,    -1,    -1,    98,   100,    75,    -1,
      -1,    97,    99,   100,    75,    -1,    -1,     3,   101,   104,
      -1,    -1,    41,   102,   106,    -1,     5,    -1,    54,    -1,
       8,    -1,     6,    -1,     7,    -1,    47,    -1,    39,    -1,
      40,    -1,   105,    -1,   104,    56,   105,    -1,     5,    57,
     103,    -1,     5,    -1,   107,    -1,   106,    56,   107,    -1,
       5,    57,   103,    -1,    -1,   109,    -1,   136,    -1,   109,
     136,    -1,    71,   138,    78,    -1,     8,    59,    91,    -1,
     111,    56,     8,    59,    91,    -1,    72,    59,    73,    -1,
      72,   111,    73,    -1,    52,    91,    -1,   115,    -1,   116,
      -1,   115,   116,    -1,    50,    76,     5,    77,    84,    -1,
      -1,    49,    84,    -1,    51,    84,   114,   117,    -1,    90,
      65,     5,    -1,     4,    65,     5,    -1,    90,    65,    54,
      -1,     4,    65,    54,    -1,    90,    65,     5,    76,   138,
      77,    -1,     4,    65,     5,    76,   138,    77,    -1,    90,
      45,    -1,    90,    46,    -1,    45,    90,    -1,    46,    90,
      -1,    91,    23,    91,    -1,    91,    24,    91,    -1,    91,
      17,    91,    -1,    91,    15,    91,    -1,    91,    16,    91,
      -1,    91,    14,    91,    -1,    91,    31,    91,    -1,    91,
      33,    91,    -1,    91,    32,    91,    -1,    91,    34,    91,
      -1,    91,    64,    91,    -1,    91,    63,    91,    -1,    91,
      66,    91,    -1,    91,    67,    91,    -1,    91,    68,    91,
      -1,    91,    62,    91,    -1,    91,    60,    91,    -1,    91,
      61,    91,    -1,    91,    20,    91,    -1,    91,    18,    91,
      -1,     3,   128,    -1,    41,   130,    -1,   129,    -1,   128,
      56,   129,    -1,     5,    57,    91,    -1,     5,    -1,   131,
      -1,   130,    56,   131,    -1,    54,    57,    91,    -1,    92,
      57,    91,    -1,     5,    -1,   133,    65,     5,    -1,    25,
     133,    65,    66,    -1,    25,   133,    65,     5,    -1,    25,
     133,    65,     4,    -1,     5,    65,    65,    65,    -1,    42,
       5,    76,    77,    84,    -1,    42,     4,    76,    77,    84,
      -1,    42,     5,    76,   135,    77,    84,    -1,    42,     4,
      76,   135,    77,    84,    -1,    42,     5,    76,   128,    77,
      84,    -1,    42,     4,    76,   128,    77,    84,    -1,    42,
       5,    76,   128,    56,   135,    77,    84,    -1,    42,     4,
      76,   128,    56,   135,    77,    84,    -1,    42,    76,    77,
      84,    -1,    42,    76,   135,    77,    84,    -1,    42,    76,
     128,    77,    84,    -1,    42,    76,   128,    56,   135,    77,
      84,    -1,    -1,   139,    -1,    91,    -1,   139,    56,    91,
      -1,    -1,   140,    76,   138,    77,    -1,    -1,     5,    76,
     138,    77,   142,   140,    -1,    38,    91,    -1,    38,    -1,
      10,    76,    91,    77,    84,    -1,    -1,   145,    13,    76,
      91,    77,    84,    -1,    -1,    12,    84,    -1,    -1,    -1,
      11,    76,    91,    77,    84,   148,   145,   149,   146,    -1
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
     297,   301,   305,   312,   319,   322,   325,   328,   331,   335,
     339,   343,   347,   351,   355,   359,   363,   367,   371,   375,
     379,   383,   387,   391,   395,   399,   403,   407,   411,   414,
     417,   419,   423,   427,   429,   431,   435,   439,   443,   445,
     449,   454,   459,   464,   469,   475,   481,   488,   495,   502,
     509,   518,   527,   532,   538,   544,   552,   553,   555,   557,
     561,   562,   567,   568,   575,   578,   580,   586,   587,   594,
     595,   598,   599,   600
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   211,   211,   211,   215,   216,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   241,   245,   246,   250,   254,   258,
     259,   263,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   298,   299,   300,
     304,   308,   309,   310,   311,   315,   319,   320,   324,   324,
     325,   325,   329,   329,   330,   330,   334,   335,   336,   337,
     338,   339,   340,   341,   345,   346,   350,   351,   355,   356,
     360,   364,   365,   369,   370,   374,   378,   379,   383,   384,
     388,   392,   396,   397,   401,   405,   406,   410,   414,   415,
     416,   417,   421,   422,   426,   427,   428,   429,   433,   434,
     435,   436,   437,   438,   442,   443,   447,   448,   452,   453,
     454,   455,   456,   460,   461,   462,   463,   464,   468,   469,
     473,   474,   478,   479,   483,   484,   488,   492,   496,   497,
     501,   502,   503,   507,   511,   513,   515,   517,   519,   521,
     523,   525,   530,   532,   534,   536,   541,   542,   546,   547,
     551,   552,   556,   556,   560,   561,   565,   569,   571,   576,
     577,   581,   582,   581
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
  const int Parser::yylast_ = 785;
  const int Parser::yynnts_ = 71;
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

