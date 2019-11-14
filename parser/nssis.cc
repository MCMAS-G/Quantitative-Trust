// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "parser/nssis.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "nssis.hh"

// User implementation prologue.
#line 70 "parser/nssis_new.yy" // lalr1.cc:412

#include "mcmas-driver.hh"

  extern map < string, int > options;
  extern vector<string *> *string_table;
  extern vector<variable *> *variable_table;
  extern vector<bool_expression *> *logic_expression_table;
  extern vector<bool_expression *> *logic_expression_table1;
  extern map<string, basic_agent *> *is_agents;
  extern vector<basic_agent *> *agents;
  extern map<string, bool_expression *> *is_evaluation;
  extern bool_expression *is_istates;
  extern map<string, set<string> > *is_groups;
  extern vector<modal_formula> *is_formulae;
  extern vector<fairness_expression *> *is_fairness;

  extern int search_string_table(string *s);
  extern int search_variable_table(variable *v);
  extern int search_logic_expression_table(bool_expression *le);
  extern int search_logic_expression_table1(bool_expression *le);

#line 72 "parser/nssis.cc" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 158 "parser/nssis.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  mcmas_parser::yytnamerr_ (const char *yystr)
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
              // Fall through.
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
  mcmas_parser::mcmas_parser (mcmas_driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  mcmas_parser::~mcmas_parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  mcmas_parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  mcmas_parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  mcmas_parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  mcmas_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  mcmas_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  mcmas_parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  mcmas_parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  mcmas_parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  mcmas_parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  mcmas_parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  mcmas_parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  mcmas_parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  mcmas_parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  mcmas_parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  mcmas_parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  mcmas_parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  mcmas_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  mcmas_parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  mcmas_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  mcmas_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  mcmas_parser::symbol_number_type
  mcmas_parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  mcmas_parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  mcmas_parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  mcmas_parser::stack_symbol_type&
  mcmas_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  mcmas_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 85: // "identifier"

#line 234 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.sval); }
#line 411 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 97: // obsvardef

#line 235 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.map_vec_basictype); }
#line 418 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 98: // varidlist

#line 236 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.map_vec_basictype); }
#line 425 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 99: // onevardef

#line 237 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._basictype); }
#line 432 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 100: // enumlist

#line 238 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.set_string); }
#line 439 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 104: // envardef

#line 240 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.map_vec_basictype); }
#line 446 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 105: // vardef

#line 239 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.map_vec_basictype); }
#line 453 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 109: // reddef

#line 248 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._bool_expression); }
#line 460 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 111: // rboolcond

#line 247 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._bool_expression); }
#line 467 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 114: // envevdef

#line 241 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.vector_evolution_line); }
#line 474 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 115: // envevdeflist

#line 242 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.vector_evolution_line); }
#line 481 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 116: // envevline

#line 243 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._evolution_line); }
#line 488 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 117: // boolresult

#line 244 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.vector_assignment); }
#line 495 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 122: // agent

#line 253 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._basic_agent); }
#line 502 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 129: // enactiondef

#line 255 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.set_string); }
#line 509 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 130: // actiondef

#line 254 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.set_string); }
#line 516 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 131: // actionidlist

#line 256 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.set_string); }
#line 523 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 134: // enprotdef

#line 258 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.vector_protocol_line); }
#line 530 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 135: // protdef

#line 257 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.vector_protocol_line); }
#line 537 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 137: // protdeflist

#line 259 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.vector_protocol_line); }
#line 544 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 141: // protline

#line 260 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._protocol_line); }
#line 551 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 143: // enabledidlist

#line 261 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.set_string); }
#line 558 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 144: // evdef

#line 262 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.vector_evolution_line); }
#line 565 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 145: // evdeflist

#line 263 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.vector_evolution_line); }
#line 572 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 146: // evline

#line 264 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._evolution_line); }
#line 579 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 148: // lboolcond

#line 245 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._bool_expression); }
#line 586 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 170: // eboolcond

#line 246 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._bool_expression); }
#line 593 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 172: // gboolcond

#line 265 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._bool_expression); }
#line 600 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 173: // varvalue1

#line 249 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._expression); }
#line 607 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 174: // boolvalue

#line 266 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._bool_value); }
#line 614 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 175: // varvalue2

#line 250 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._expression); }
#line 621 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 176: // varvalue3

#line 251 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._expression); }
#line 628 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 177: // varvalue4

#line 252 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._expression); }
#line 635 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 182: // evaboolcond

#line 267 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._bool_expression); }
#line 642 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 186: // isboolcond

#line 268 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._bool_expression); }
#line 649 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 193: // namelist

#line 269 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.set_string); }
#line 656 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 194: // agentname

#line 270 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value.sval); }
#line 663 "parser/nssis.cc" // lalr1.cc:614
        break;

      case 215: // formula

#line 271 "parser/nssis_new.yy" // lalr1.cc:614
        { delete (yysym.value._modal_formula); }
#line 670 "parser/nssis.cc" // lalr1.cc:614
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  mcmas_parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 85: // "identifier"

#line 233 "parser/nssis_new.yy" // lalr1.cc:636
        { debug_stream () << *(yysym.value.sval); }
#line 701 "parser/nssis.cc" // lalr1.cc:636
        break;

      case 86: // "number"

#line 273 "parser/nssis_new.yy" // lalr1.cc:636
        { debug_stream () << (yysym.value.ival); }
#line 708 "parser/nssis.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  mcmas_parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  mcmas_parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  mcmas_parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  mcmas_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  mcmas_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  mcmas_parser::debug_level_type
  mcmas_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  mcmas_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline mcmas_parser::state_type
  mcmas_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  mcmas_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  mcmas_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  mcmas_parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 29 "parser/nssis_new.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 827 "parser/nssis.cc" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 4:
#line 281 "parser/nssis_new.yy" // lalr1.cc:859
    {
    options["smv"] = 0;
 }
#line 939 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 5:
#line 284 "parser/nssis_new.yy" // lalr1.cc:859
    {
    options["smv"] = 1;
 }
#line 947 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 6:
#line 287 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
 }
#line 955 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 11:
#line 296 "parser/nssis_new.yy" // lalr1.cc:859
    {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>,
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
#line 967 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 12:
#line 303 "parser/nssis_new.yy" // lalr1.cc:859
    {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
#line 979 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 13:
#line 310 "parser/nssis_new.yy" // lalr1.cc:859
    {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
#line 991 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 14:
#line 317 "parser/nssis_new.yy" // lalr1.cc:859
    {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
#line 1003 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 15:
#line 327 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 1011 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 16:
#line 330 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1020 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 17:
#line 334 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1029 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 18:
#line 338 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1038 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 19:
#line 342 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 1046 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 20:
#line 345 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1055 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 21:
#line 349 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1064 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 22:
#line 353 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1073 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 23:
#line 358 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[7].value.ival)==1 && (yystack_[6].value.map_vec_basictype)!=NULL && (yystack_[5].value.map_vec_basictype)!=NULL && (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, (yystack_[6].value.map_vec_basictype)->first, (yystack_[6].value.map_vec_basictype)->second, (yystack_[5].value.map_vec_basictype)->first, (yystack_[5].value.map_vec_basictype)->second, (yystack_[4].value._bool_expression), (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
#line 1085 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 24:
#line 365 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[6].value.ival)==1 && (yystack_[5].value.map_vec_basictype)!=NULL && (yystack_[4].value.map_vec_basictype)!=NULL && (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, (yystack_[5].value.map_vec_basictype)->first, (yystack_[5].value.map_vec_basictype)->second, (yystack_[4].value.map_vec_basictype)->first, (yystack_[4].value.map_vec_basictype)->second, NULL, (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
#line 1097 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 25:
#line 372 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[6].value.ival)==1 && (yystack_[5].value.map_vec_basictype)!=NULL && (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, (yystack_[5].value.map_vec_basictype)->first, (yystack_[5].value.map_vec_basictype)->second, (yystack_[4].value._bool_expression), (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
#line 1109 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 26:
#line 379 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[5].value.ival)==1 && (yystack_[4].value.map_vec_basictype)!=NULL && (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, (yystack_[4].value.map_vec_basictype)->first, (yystack_[4].value.map_vec_basictype)->second, NULL, (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
#line 1121 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 27:
#line 386 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[6].value.ival)==1 && (yystack_[5].value.map_vec_basictype)!=NULL && (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, (yystack_[5].value.map_vec_basictype)->first, (yystack_[5].value.map_vec_basictype)->second, new map<string, basictype *>, new vector<basictype *>, (yystack_[4].value._bool_expression), (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
#line 1133 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 28:
#line 393 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[5].value.ival)==1 && (yystack_[4].value.map_vec_basictype)!=NULL && (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, (yystack_[4].value.map_vec_basictype)->first, (yystack_[4].value.map_vec_basictype)->second, new map<string, basictype *>, new vector<basictype *>, NULL, (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
#line 1145 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 29:
#line 400 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[5].value.ival)==1 && (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				       new map<string, basictype *>, new vector<basictype *>, (yystack_[4].value._bool_expression), (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
#line 1158 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 30:
#line 408 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[4].value.ival)==1 && (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				       new map<string, basictype *>, new vector<basictype *>, NULL, (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
#line 1171 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 31:
#line 416 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  }
#line 1179 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 32:
#line 421 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 1187 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 33:
#line 424 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1196 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 34:
#line 428 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1205 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 35:
#line 432 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1214 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 36:
#line 436 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 1222 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 37:
#line 439 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1231 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 38:
#line 443 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1240 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 39:
#line 447 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1249 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 40:
#line 451 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value.map_vec_basictype) = (yystack_[1].value.map_vec_basictype);
  else
    (yylhs.value.map_vec_basictype) = NULL;
 }
#line 1260 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 41:
#line 457 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value.ival)==1 && (yystack_[0].value.ival)==1) {
    map<string, basictype *>* a = new map<string, basictype *>;
    vector<basictype *>* b = new vector<basictype *>;
    (yylhs.value.map_vec_basictype) = new pair<map<string, basictype *>*, vector<basictype *>* >(a, b);
  } else
    (yylhs.value.map_vec_basictype) = NULL;
 }
#line 1273 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 42:
#line 465 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value._basictype)!=NULL) {
    map<string, basictype *>* a = new map<string, basictype *>;
    vector<basictype *>* b = new vector<basictype *>;
    (yylhs.value.map_vec_basictype) = new pair<map<string, basictype *>*, vector<basictype *>* >(a, b);
    (*a)[(yystack_[1].value._basictype)->get_name()] = (yystack_[1].value._basictype);
    b->push_back((yystack_[1].value._basictype));
  } else
    (yylhs.value.map_vec_basictype) = NULL;
 }
#line 1288 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 43:
#line 475 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.map_vec_basictype) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._basictype));
 }
#line 1298 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 44:
#line 480 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.map_vec_basictype)!=NULL && (yystack_[1].value._basictype)!=NULL) {
    if((yystack_[2].value.map_vec_basictype)->first->find((yystack_[1].value._basictype)->get_name()) != (yystack_[2].value.map_vec_basictype)->first->end())
      cout << "warning: type " << (yystack_[1].value._basictype)->get_name() << " has already been defined." << endl;
    else { 
      (*((yystack_[2].value.map_vec_basictype)->first))[(yystack_[1].value._basictype)->get_name()] = (yystack_[1].value._basictype);
      (yystack_[2].value.map_vec_basictype)->second->push_back((yystack_[1].value._basictype));
      (yylhs.value.map_vec_basictype) = (yystack_[2].value.map_vec_basictype);
    }
  } else
    (yylhs.value.map_vec_basictype) = NULL;
 }
#line 1315 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 45:
#line 492 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.map_vec_basictype) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.map_vec_basictype));
  USE((yystack_[1].value._basictype));
 }
#line 1326 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 46:
#line 498 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.map_vec_basictype) = NULL;
  driver.syntax_error = true;
  }
#line 1335 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 47:
#line 503 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.sval)!=NULL) {
    int i = search_string_table((yystack_[2].value.sval));
    if(i>=0) {
      (yylhs.value._basictype) = new basictype((*string_table)[i]);
      free((yystack_[2].value.sval));
    } else {
      (yylhs.value._basictype) = new basictype((yystack_[2].value.sval));
      string_table->push_back((yystack_[2].value.sval));
    }
  } else
    (yylhs.value._basictype) = NULL;
 }
#line 1353 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 48:
#line 516 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._basictype) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
 }
#line 1363 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 49:
#line 521 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._basictype) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
 }
#line 1373 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 50:
#line 526 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[4].value.sval)!=NULL) {
    if((yystack_[2].value.ival)>(yystack_[0].value.ival))
      cout << "warning: the lower bound " << (yystack_[2].value.ival) << " is greater than the upper bound " << (yystack_[0].value.ival) << endl;
    int i = search_string_table((yystack_[4].value.sval));
    if(i>=0) {
      (yylhs.value._basictype) = new rangedint((*string_table)[i], (yystack_[2].value.ival), (yystack_[0].value.ival));
      free((yystack_[4].value.sval));
    } else {
      (yylhs.value._basictype) = new rangedint((yystack_[4].value.sval), (yystack_[2].value.ival), (yystack_[0].value.ival));
      string_table->push_back((yystack_[4].value.sval));
    }
  }
  else
    (yylhs.value._basictype) = NULL;
 }
#line 1394 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 51:
#line 542 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._basictype) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
 }
#line 1404 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 52:
#line 547 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._basictype) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
 }
#line 1414 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 53:
#line 552 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._basictype) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
 }
#line 1424 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 54:
#line 557 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[4].value.sval)!=NULL && (yystack_[1].value.set_string)!=NULL) {
    int i = search_string_table((yystack_[4].value.sval));
    if(i>=0) {
      (yylhs.value._basictype) = new enumerate((*string_table)[i], (yystack_[1].value.set_string));
      free((yystack_[4].value.sval));
    } else {
      (yylhs.value._basictype) = new enumerate((yystack_[4].value.sval), (yystack_[1].value.set_string));
      string_table->push_back((yystack_[4].value.sval));
    }
  } else
    (yylhs.value._basictype) = NULL;
 }
#line 1442 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 55:
#line 570 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._basictype) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value.set_string));
 }
#line 1453 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 56:
#line 576 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._basictype) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[1].value.set_string));
 }
#line 1464 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 57:
#line 582 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._basictype) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value.set_string));
 }
#line 1475 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 58:
#line 588 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._basictype) = NULL;
  driver.syntax_error = true;
 }
#line 1484 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 59:
#line 592 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.sval)!=NULL) {
    (yylhs.value.set_string) = new set<string>;
    (yylhs.value.set_string)->insert(*(yystack_[0].value.sval));
    free ((yystack_[0].value.sval));
  } else
    (yylhs.value.set_string) = NULL;
 }
#line 1497 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 60:
#line 600 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.set_string)!=NULL && (yystack_[0].value.sval)!=NULL) {
    pair<set<string>::iterator, bool> ret = (yystack_[2].value.set_string)->insert(*(yystack_[0].value.sval));
    if(!ret.second)
      cout << "warning: " << *(yystack_[0].value.sval) << " has been defined for the enum type." << endl;
    (yylhs.value.set_string) = (yystack_[2].value.set_string);
    free ((yystack_[0].value.sval));
  } else
    (yylhs.value.set_string) = NULL;
	USE((yystack_[2].value.set_string));
 }
#line 1513 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 61:
#line 611 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.set_string) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.set_string));
  USE((yystack_[0].value.sval));
 }
#line 1524 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 62:
#line 617 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.set_string) = NULL;
  driver.syntax_error = true;
  }
#line 1533 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 63:
#line 621 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = (yystack_[0].value.ival);
 }
#line 1541 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 64:
#line 624 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0-(yystack_[0].value.ival);
 }
#line 1549 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 65:
#line 627 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = -1;
  driver.syntax_error = true;
 }
#line 1558 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 66:
#line 631 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = -1;
  driver.syntax_error = true;
  }
#line 1567 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 67:
#line 637 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 1575 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 68:
#line 640 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1584 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 69:
#line 644 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1593 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 70:
#line 648 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1602 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 71:
#line 652 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 1610 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 72:
#line 655 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1619 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 73:
#line 659 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1628 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 74:
#line 663 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1637 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 75:
#line 667 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value.map_vec_basictype) = (yystack_[1].value.map_vec_basictype);
  else
    (yylhs.value.map_vec_basictype) = NULL;
 }
#line 1648 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 76:
#line 673 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value.ival)==1 && (yystack_[0].value.ival)==1) {
    map<string, basictype *>* a = new map<string, basictype *>;
    vector<basictype *>* b = new vector<basictype *>;
    (yylhs.value.map_vec_basictype) = new pair<map<string, basictype *>*, vector<basictype *>* >(a, b);
  } else
    (yylhs.value.map_vec_basictype) = NULL;
 }
#line 1661 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 77:
#line 681 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.map_vec_basictype) = NULL;
  driver.syntax_error = true;
  }
#line 1670 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 78:
#line 687 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value.map_vec_basictype) = (yystack_[1].value.map_vec_basictype);
  else
    (yylhs.value.map_vec_basictype) = NULL;
 }
#line 1681 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 79:
#line 693 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.map_vec_basictype) = NULL;
  driver.syntax_error = true;
  }
#line 1690 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 80:
#line 699 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 1698 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 81:
#line 702 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1707 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 82:
#line 706 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1716 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 83:
#line 710 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1725 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 84:
#line 714 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 1733 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 85:
#line 717 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1742 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 86:
#line 721 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1751 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 87:
#line 725 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1760 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 88:
#line 730 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value._bool_expression) = (yystack_[1].value._bool_expression);
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 1771 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 89:
#line 736 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL; 
 }
#line 1779 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 90:
#line 739 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  }
#line 1788 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 91:
#line 744 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value._bool_expression) = (yystack_[1].value._bool_expression);
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 1799 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 92:
#line 750 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL; 
 }
#line 1807 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 93:
#line 753 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  }
#line 1816 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 94:
#line 758 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = (yystack_[1].value._bool_expression);
  }
#line 1824 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 95:
#line 761 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
  }
#line 1834 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 96:
#line 766 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  }
#line 1843 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 97:
#line 771 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = (yystack_[1].value._bool_expression);
  }
#line 1851 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 98:
#line 774 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
  }
#line 1861 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 99:
#line 779 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  }
#line 1870 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 100:
#line 786 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 1878 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 101:
#line 789 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1887 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 102:
#line 793 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1896 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 103:
#line 797 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1905 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 104:
#line 801 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 1913 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 105:
#line 804 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1922 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 106:
#line 808 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1931 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 107:
#line 812 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 1940 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 108:
#line 816 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value.vector_evolution_line) = (yystack_[1].value.vector_evolution_line);
  else
    (yylhs.value.vector_evolution_line) = NULL;
 }
#line 1951 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 109:
#line 822 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value.vector_evolution_line) = new vector<evolution_line *>;
  else
    (yylhs.value.vector_evolution_line) = NULL;
 }
#line 1962 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 110:
#line 828 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._evolution_line)!=NULL) {
    (yylhs.value.vector_evolution_line) = new vector<evolution_line *>;
    (yylhs.value.vector_evolution_line)->push_back((yystack_[0].value._evolution_line));
  } else
    (yylhs.value.vector_evolution_line) = NULL;
 }
#line 1974 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 111:
#line 835 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value._evolution_line)!=NULL) {
    (yystack_[1].value.vector_evolution_line)->push_back((yystack_[0].value._evolution_line));
    (yylhs.value.vector_evolution_line) = (yystack_[1].value.vector_evolution_line);
  } else
    (yylhs.value.vector_evolution_line) = NULL;
 }
#line 1986 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 112:
#line 842 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_evolution_line) = NULL;
  driver.syntax_error = true;
  }
#line 1995 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 113:
#line 846 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value.vector_assignment)!=NULL && (yystack_[1].value._bool_expression)!=NULL) 
    (yylhs.value._evolution_line) = new evolution_line((yystack_[3].value.vector_assignment), (yystack_[1].value._bool_expression));
  else
    (yylhs.value._evolution_line) = NULL;
 }
#line 2006 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 114:
#line 852 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._evolution_line) = NULL;
  driver.syntax_error = true;
  }
#line 2015 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 115:
#line 856 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_assignment) = (yystack_[1].value.vector_assignment);
 }
#line 2023 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 116:
#line 859 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.vector_assignment)!=NULL && (yystack_[0].value.vector_assignment)!=NULL) {
    (yylhs.value.vector_assignment) = (yystack_[2].value.vector_assignment);
    vector<assignment*>::iterator i;
    for(i=(yystack_[0].value.vector_assignment)->begin(); i != (yystack_[0].value.vector_assignment)->end(); i++)
      (yylhs.value.vector_assignment)->push_back(*i);
  } else
    (yylhs.value.vector_assignment) = NULL;
 }
#line 2037 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 117:
#line 868 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.sval)!=NULL && (yystack_[0].value._expression)!=NULL) {
    assignment *a;
    int i = search_string_table((yystack_[2].value.sval));
    if(i>=0) {
      a = new assignment((*string_table)[i], (yystack_[0].value._expression));
      free((yystack_[2].value.sval));
    } else {
      a = new assignment((yystack_[2].value.sval), (yystack_[0].value._expression));
      string_table->push_back((yystack_[2].value.sval));
    }
    (yylhs.value.vector_assignment) = new vector<assignment*>;
    (yylhs.value.vector_assignment)->push_back(a);
  } else
    (yylhs.value.vector_assignment) = NULL;
 }
#line 2058 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 118:
#line 884 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_assignment) = NULL;
  driver.syntax_error = true;
  }
#line 2067 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 119:
#line 889 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_assignment) = (yystack_[1].value.vector_assignment);
 }
#line 2075 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 120:
#line 892 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.vector_assignment)!=NULL && (yystack_[0].value.vector_assignment)!=NULL) {
    (yylhs.value.vector_assignment) = (yystack_[2].value.vector_assignment);
    vector<assignment*>::iterator i;
    for(i=(yystack_[0].value.vector_assignment)->begin(); i != (yystack_[0].value.vector_assignment)->end(); i++)
      (yylhs.value.vector_assignment)->push_back(*i);
  } else
    (yylhs.value.vector_assignment) = NULL;
 }
#line 2089 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 121:
#line 901 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.sval)!=NULL && (yystack_[0].value._expression)!=NULL) {
    assignment *a;
    int i = search_string_table((yystack_[2].value.sval));
    if(i>=0) {
      a = new assignment((*string_table)[i], (yystack_[0].value._expression));
      free((yystack_[2].value.sval));
    } else {
      a = new assignment((yystack_[2].value.sval), (yystack_[0].value._expression));
      string_table->push_back((yystack_[2].value.sval));
    }
    (yylhs.value.vector_assignment) = new vector<assignment*>;
    (yylhs.value.vector_assignment)->push_back(a);
  } else
    (yylhs.value.vector_assignment) = NULL;
 }
#line 2110 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 122:
#line 917 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_assignment) = NULL;
  driver.syntax_error = true;
  }
#line 2119 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 123:
#line 922 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._basic_agent)!=NULL) {
    (*is_agents)[(yystack_[0].value._basic_agent)->get_name()] = (yystack_[0].value._basic_agent);
    agents->push_back((yystack_[0].value._basic_agent));
  } 
 }
#line 2130 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 124:
#line 928 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._basic_agent)!=NULL) {
    if(is_agents->find((yystack_[0].value._basic_agent)->get_name()) != is_agents->end())
      cout << "warning: agent " << (yystack_[0].value._basic_agent)->get_name() << " already exists." << endl;
    else
      agents->push_back((yystack_[0].value._basic_agent));
    (*is_agents)[(yystack_[0].value._basic_agent)->get_name()] = (yystack_[0].value._basic_agent);
  }
 }
#line 2144 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 125:
#line 937 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  }
#line 2152 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 126:
#line 941 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 2160 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 127:
#line 944 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2169 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 128:
#line 948 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 2177 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 129:
#line 951 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2186 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 130:
#line 955 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2195 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 131:
#line 959 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2204 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 132:
#line 964 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[7].value.ival)==1 && (yystack_[6].value.sval)!=NULL && (yystack_[5].value.map_vec_basictype)!=NULL && 
     (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) {// redstates is NULL if no red state at all
    int i = search_string_table((yystack_[6].value.sval));
    if(i>=0) {
      (yylhs.value._basic_agent) = new basic_agent((*string_table)[i], NULL, NULL, NULL, (yystack_[5].value.map_vec_basictype)->first, (yystack_[5].value.map_vec_basictype)->second, (yystack_[4].value._bool_expression), (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
      free((yystack_[6].value.sval));
    } else {
      (yylhs.value._basic_agent) = new basic_agent((yystack_[6].value.sval), NULL, NULL, NULL, (yystack_[5].value.map_vec_basictype)->first, (yystack_[5].value.map_vec_basictype)->second, (yystack_[4].value._bool_expression), (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
      string_table->push_back((yystack_[6].value.sval));
    }
  } else
    (yylhs.value._basic_agent) = NULL;
 }
#line 2223 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 133:
#line 978 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[6].value.ival)==1 && (yystack_[5].value.sval)!=NULL && (yystack_[4].value.map_vec_basictype)!=NULL && 
     (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) {// redstates is NULL if no red state at all
    int i = search_string_table((yystack_[5].value.sval));
    if(i>=0) {
      (yylhs.value._basic_agent) = new basic_agent((*string_table)[i], NULL, NULL, NULL, (yystack_[4].value.map_vec_basictype)->first, (yystack_[4].value.map_vec_basictype)->second, NULL, (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
      free((yystack_[5].value.sval));
    } else {
      (yylhs.value._basic_agent) = new basic_agent((yystack_[5].value.sval), NULL, NULL, NULL, (yystack_[4].value.map_vec_basictype)->first, (yystack_[4].value.map_vec_basictype)->second, NULL, (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
      string_table->push_back((yystack_[5].value.sval));
    }
  } else
    (yylhs.value._basic_agent) = NULL;
 }
#line 2242 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 134:
#line 992 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[8].value.ival)==1 && (yystack_[7].value.sval)!=NULL && (yystack_[5].value.map_vec_basictype)!=NULL && 
     (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) {// redstates is NULL if no red state at all
    int i = search_string_table((yystack_[7].value.sval));
    if(i>=0) {
      (yylhs.value._basic_agent) = new basic_agent((*string_table)[i], (yystack_[6].value.map_string_variable), NULL, NULL, (yystack_[5].value.map_vec_basictype)->first, (yystack_[5].value.map_vec_basictype)->second, (yystack_[4].value._bool_expression), (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
      free((yystack_[7].value.sval));
    } else {
      (yylhs.value._basic_agent) = new basic_agent((yystack_[7].value.sval), (yystack_[6].value.map_string_variable), NULL, NULL, (yystack_[5].value.map_vec_basictype)->first, (yystack_[5].value.map_vec_basictype)->second, (yystack_[4].value._bool_expression), (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
      string_table->push_back((yystack_[7].value.sval));
    }
  } else
    (yylhs.value._basic_agent) = NULL;
 }
#line 2261 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 135:
#line 1006 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[7].value.ival)==1 && (yystack_[6].value.sval)!=NULL && 
     (yystack_[4].value.map_vec_basictype)!=NULL && (yystack_[3].value.set_string)!=NULL && (yystack_[2].value.vector_protocol_line)!=NULL && (yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value.ival)==1) {// redstates is NULL if no red state at all
    int i = search_string_table((yystack_[6].value.sval));
    if(i>=0) {
      (yylhs.value._basic_agent) = new basic_agent((*string_table)[i], (yystack_[5].value.map_string_variable), NULL, NULL, (yystack_[4].value.map_vec_basictype)->first, (yystack_[4].value.map_vec_basictype)->second, NULL, (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
      free((yystack_[6].value.sval));
    } else {
      (yylhs.value._basic_agent) = new basic_agent((yystack_[6].value.sval), (yystack_[5].value.map_string_variable), NULL, NULL, (yystack_[4].value.map_vec_basictype)->first, (yystack_[4].value.map_vec_basictype)->second, NULL, (yystack_[3].value.set_string), (yystack_[2].value.vector_protocol_line), (yystack_[1].value.vector_evolution_line));
      string_table->push_back((yystack_[6].value.sval));
    }
  } else
    (yylhs.value._basic_agent) = NULL;
 }
#line 2280 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 136:
#line 1020 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._basic_agent) = NULL;
  driver.syntax_error = true;
  }
#line 2289 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 137:
#line 1026 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 2297 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 138:
#line 1029 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2306 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 139:
#line 1033 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2315 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 140:
#line 1037 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2324 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 141:
#line 1041 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2333 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 142:
#line 1045 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2342 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 143:
#line 1049 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2351 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 144:
#line 1053 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2360 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 145:
#line 1057 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 2368 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 146:
#line 1060 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2377 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 147:
#line 1064 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2386 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 148:
#line 1068 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2395 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 149:
#line 1072 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value.map_string_variable) = (yystack_[1].value.map_string_variable);
  else
    (yylhs.value.map_string_variable) = NULL;
 }
#line 2406 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 150:
#line 1078 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.map_string_variable) = NULL;
 }
#line 2414 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 151:
#line 1081 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.map_string_variable) = NULL;
  driver.syntax_error = true;
  }
#line 2423 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 152:
#line 1085 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.sval)!=NULL) {
    (yylhs.value.map_string_variable) = new map<string, variable *>;
    if((yylhs.value.map_string_variable)->find(*(yystack_[0].value.sval)) != (yylhs.value.map_string_variable)->end())
      cout << "warning: local observable variable " << *(yystack_[0].value.sval) << " has already been defined." << endl;
    int i = search_string_table((yystack_[0].value.sval));
    if(i>=0) {
      (*(yylhs.value.map_string_variable))[*(yystack_[0].value.sval)] = new variable((*string_table)[0], (*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      (*(yylhs.value.map_string_variable))[*(yystack_[0].value.sval)] = new variable((*string_table)[0], (yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
  } else
    (yylhs.value.map_string_variable) = NULL;
 }
#line 2444 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 153:
#line 1101 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.map_string_variable)!=NULL && (yystack_[0].value.sval)!=NULL) {
    if((yystack_[2].value.map_string_variable)->find(*(yystack_[0].value.sval)) != (yylhs.value.map_string_variable)->end())
      cout << "warning: local observable variable " << *(yystack_[0].value.sval) << " has already been defined." << endl;
    int i = search_string_table((yystack_[0].value.sval));
    if(i>=0) {
      (*(yystack_[2].value.map_string_variable))[*(yystack_[0].value.sval)] = new variable((*string_table)[0], (*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      (*(yystack_[2].value.map_string_variable))[*(yystack_[0].value.sval)] = new variable((*string_table)[0], (yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
    (yylhs.value.map_string_variable) = (yystack_[2].value.map_string_variable);
  } else
    (yylhs.value.map_string_variable) = NULL;
 }
#line 2465 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 154:
#line 1117 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.map_string_variable) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.map_string_variable));
  USE((yystack_[0].value.sval));
 }
#line 2476 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 155:
#line 1123 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.map_string_variable) = NULL;
  driver.syntax_error = true;
  }
#line 2485 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 156:
#line 1130 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 2493 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 157:
#line 1133 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2502 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 158:
#line 1137 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2511 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 159:
#line 1141 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2520 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 160:
#line 1145 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2529 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 161:
#line 1149 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2538 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 162:
#line 1153 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2547 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 163:
#line 1157 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2556 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 164:
#line 1161 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 2564 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 165:
#line 1164 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2573 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 166:
#line 1168 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2582 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 167:
#line 1172 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2591 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 168:
#line 1176 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value.set_string) = (yystack_[1].value.set_string);
  else
    (yylhs.value.set_string) = NULL;
 }
#line 2602 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 169:
#line 1182 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value.set_string) = new set<string>;
  else
    (yylhs.value.set_string) = NULL;
 }
#line 2613 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 170:
#line 1188 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.set_string) = NULL;
  driver.syntax_error = true;
  }
#line 2622 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 171:
#line 1194 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1) 
    (yylhs.value.set_string) = (yystack_[1].value.set_string);
  else
    (yylhs.value.set_string) = NULL;
 }
#line 2633 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 172:
#line 1200 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.set_string) = NULL;
  driver.syntax_error = true;
  }
#line 2642 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 173:
#line 1204 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.sval)!=NULL) {
    (yylhs.value.set_string) = new set<string>;
    (yylhs.value.set_string)->insert(*(yystack_[0].value.sval));
    free ((yystack_[0].value.sval));
  } else
    (yylhs.value.set_string) = NULL;
 }
#line 2655 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 174:
#line 1212 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.set_string)!=NULL && (yystack_[0].value.sval)!=NULL) {
    pair<set<string>::iterator, bool> ret = (yystack_[2].value.set_string)->insert(*(yystack_[0].value.sval));
    if(!ret.second)
      cout << "warning: action " << *(yystack_[0].value.sval) << " has been defined." << endl;
    (yylhs.value.set_string) = (yystack_[2].value.set_string);
    free ((yystack_[0].value.sval));
  } else
    (yylhs.value.set_string) = NULL;
 }
#line 2670 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 175:
#line 1222 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.set_string) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.set_string));
  USE((yystack_[0].value.sval));
 }
#line 2681 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 176:
#line 1228 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.set_string) = NULL;
  driver.syntax_error = true;
  }
#line 2690 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 177:
#line 1235 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 2698 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 178:
#line 1238 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2707 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 179:
#line 1242 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2716 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 180:
#line 1246 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2725 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 181:
#line 1250 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 2733 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 182:
#line 1253 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2742 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 183:
#line 1257 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2751 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 184:
#line 1261 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2760 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 185:
#line 1266 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1) 
    (yylhs.value.vector_protocol_line) = (yystack_[1].value.vector_protocol_line);
  else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2771 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 186:
#line 1272 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value.ival)==1 && (yystack_[0].value.ival)==1) {
    (yylhs.value.vector_protocol_line) = (yystack_[2].value.vector_protocol_line);
    (yylhs.value.vector_protocol_line)->push_back((yystack_[1].value._protocol_line));
  }
  else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2784 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 187:
#line 1280 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1) {
    (yylhs.value.vector_protocol_line) = new vector<protocol_line*>;
    (yylhs.value.vector_protocol_line)->push_back((yystack_[1].value._protocol_line));;
  }
  else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2797 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 188:
#line 1288 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value.ival)==1 && (yystack_[0].value.ival)==1) 
    (yylhs.value.vector_protocol_line) = new vector<protocol_line*>;
  else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2808 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 189:
#line 1294 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_protocol_line) = NULL;
  driver.syntax_error = true;
  }
#line 2817 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 190:
#line 1300 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1) 
    (yylhs.value.vector_protocol_line) = (yystack_[1].value.vector_protocol_line);
  else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2828 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 191:
#line 1306 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value.ival)==1 && (yystack_[0].value.ival)==1) {
    (yylhs.value.vector_protocol_line) = (yystack_[2].value.vector_protocol_line);
    (yylhs.value.vector_protocol_line)->push_back((yystack_[1].value._protocol_line));
  }
  else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2841 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 192:
#line 1314 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1) {
    (yylhs.value.vector_protocol_line) = new vector<protocol_line*>;
    (yylhs.value.vector_protocol_line)->push_back((yystack_[1].value._protocol_line));;
  }
  else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2854 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 193:
#line 1322 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_protocol_line) = NULL;
  driver.syntax_error = true;
  }
#line 2863 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 194:
#line 1327 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._protocol_line)!=NULL) {
    (yylhs.value.vector_protocol_line) = new vector<protocol_line*>;
    (yylhs.value.vector_protocol_line)->push_back((yystack_[0].value._protocol_line));
  } else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2875 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 195:
#line 1334 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value.vector_protocol_line)!=NULL && (yystack_[0].value._protocol_line)!=NULL) {
    (yystack_[1].value.vector_protocol_line)->push_back((yystack_[0].value._protocol_line));
    (yylhs.value.vector_protocol_line) = (yystack_[1].value.vector_protocol_line);
  } else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2887 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 196:
#line 1341 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_protocol_line) = NULL;
  driver.syntax_error = true;
  }
#line 2896 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 197:
#line 1346 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._protocol_line)!=NULL) {
    (yylhs.value.vector_protocol_line) = new vector<protocol_line*>;
    (yylhs.value.vector_protocol_line)->push_back((yystack_[0].value._protocol_line));
  } else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2908 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 198:
#line 1353 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value.vector_protocol_line)!=NULL && (yystack_[0].value._protocol_line)!=NULL) {
    (yystack_[1].value.vector_protocol_line)->push_back((yystack_[0].value._protocol_line));
    (yylhs.value.vector_protocol_line) = (yystack_[1].value.vector_protocol_line);
  } else
    (yylhs.value.vector_protocol_line) = NULL;
 }
#line 2920 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 199:
#line 1360 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_protocol_line) = NULL;
  driver.syntax_error = true;
  }
#line 2929 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 200:
#line 1365 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 2937 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 201:
#line 1368 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2946 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 202:
#line 1372 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2955 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 203:
#line 1376 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2964 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 204:
#line 1380 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 2972 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 205:
#line 1383 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2981 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 206:
#line 1387 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2990 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 207:
#line 1391 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 2999 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 208:
#line 1395 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value._bool_expression)!=NULL && (yystack_[2].value.ival)==1 && (yystack_[1].value.set_string)!=NULL && (yystack_[0].value.ival)==1) 
    (yylhs.value._protocol_line) = new protocol_line((yystack_[3].value._bool_expression), (yystack_[1].value.set_string));
  else
    (yylhs.value._protocol_line) = NULL;
 }
#line 3010 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 209:
#line 1401 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._protocol_line) = NULL;
  driver.syntax_error = true;
  }
#line 3019 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 210:
#line 1406 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value._bool_expression)!=NULL && (yystack_[2].value.ival)==1 && (yystack_[1].value.set_string)!=NULL && (yystack_[0].value.ival)==1) 
    (yylhs.value._protocol_line) = new protocol_line((yystack_[3].value._bool_expression), (yystack_[1].value.set_string));
  else
    (yylhs.value._protocol_line) = NULL;
 }
#line 3030 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 211:
#line 1412 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._protocol_line) = NULL;
  driver.syntax_error = true;
  }
#line 3039 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 212:
#line 1417 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[1].value.set_string)!=NULL && (yystack_[0].value.ival)==1) 
    (yylhs.value._protocol_line) = new protocol_line(new bool_expression(), (yystack_[1].value.set_string));
  else
    (yylhs.value._protocol_line) = NULL;
 }
#line 3050 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 213:
#line 1423 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._protocol_line) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value.set_string));
 }
#line 3060 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 214:
#line 1429 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.sval)!=NULL) {
    (yylhs.value.set_string) = new set<string>;
    (yylhs.value.set_string)->insert(*(yystack_[0].value.sval));
    free ((yystack_[0].value.sval));
  } else
    (yylhs.value.set_string) = NULL;
 }
#line 3073 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 215:
#line 1437 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.set_string)!=NULL && (yystack_[0].value.sval)!=NULL) {
    pair<set<string>::iterator, bool> ret = (yystack_[2].value.set_string)->insert(*(yystack_[0].value.sval));
    if(!ret.second)
      cout << "warning: action " << *(yystack_[0].value.sval) << " is repeated." << endl;
    (yylhs.value.set_string) = (yystack_[2].value.set_string);
    free ((yystack_[0].value.sval));
  } else
    (yylhs.value.set_string) = NULL;
 }
#line 3088 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 216:
#line 1447 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.set_string) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.set_string));
  USE((yystack_[0].value.sval));
 }
#line 3099 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 217:
#line 1453 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.set_string) = NULL;
  driver.syntax_error = true;
  }
#line 3108 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 218:
#line 1460 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1)
    (yylhs.value.vector_evolution_line) = (yystack_[1].value.vector_evolution_line);
  else
    (yylhs.value.vector_evolution_line) = NULL;
}
#line 3119 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 219:
#line 1466 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_evolution_line) = NULL;
  driver.syntax_error = true;
  }
#line 3128 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 220:
#line 1470 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._evolution_line)!=NULL) {
    (yylhs.value.vector_evolution_line) = new vector<evolution_line*>;
    (yylhs.value.vector_evolution_line)->push_back((yystack_[0].value._evolution_line));
  } else
    (yylhs.value.vector_evolution_line) = NULL;
 }
#line 3140 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 221:
#line 1477 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value.vector_evolution_line)!=NULL && (yystack_[0].value._evolution_line)!=NULL) {
    (yystack_[1].value.vector_evolution_line)->push_back((yystack_[0].value._evolution_line));
    (yylhs.value.vector_evolution_line) = (yystack_[1].value.vector_evolution_line);
  } else
    (yylhs.value.vector_evolution_line) = NULL;
 }
#line 3152 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 222:
#line 1484 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.vector_evolution_line) = NULL;
  driver.syntax_error = true;
  }
#line 3161 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 223:
#line 1489 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value.vector_assignment)!=NULL)
    (yylhs.value._evolution_line) = new evolution_line((yystack_[3].value.vector_assignment), (yystack_[1].value._bool_expression));
  else
    (yylhs.value._evolution_line) = NULL;
 }
#line 3172 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 224:
#line 1495 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._evolution_line) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.vector_assignment));
  USE((yystack_[1].value._bool_expression));
 }
#line 3183 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 225:
#line 1501 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._evolution_line) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.vector_assignment));
  USE((yystack_[1].value._bool_expression));
 }
#line 3194 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 226:
#line 1507 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._evolution_line) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.vector_assignment));
  USE((yystack_[1].value._bool_expression));
 }
#line 3205 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 227:
#line 1513 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._evolution_line) = NULL;
  driver.syntax_error = true;
  }
#line 3214 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 228:
#line 1518 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = (yystack_[1].value._bool_expression); 
 }
#line 3222 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 229:
#line 1521 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 3232 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 230:
#line 1526 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 3242 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 231:
#line 1531 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 3252 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 232:
#line 1536 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(1, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 3263 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 233:
#line 1542 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(2, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 3274 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 234:
#line 1548 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._bool_expression));
  USE((yystack_[0].value._bool_expression));
 }
#line 3285 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 235:
#line 1554 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(3, (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 3296 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 236:
#line 1560 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._bool_expression));
 }
#line 3306 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 237:
#line 1565 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    logic_expression *expr = new logic_expression((yystack_[1].value._unsigned_char), (yystack_[2].value._expression), (yystack_[0].value._expression));
    (yylhs.value._bool_expression) = new bool_expression(0,  expr);
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 3318 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 238:
#line 1572 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  }
#line 3327 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 239:
#line 1577 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = (yystack_[1].value._bool_expression); 
 }
#line 3335 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 240:
#line 1580 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 3345 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 241:
#line 1585 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 3355 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 242:
#line 1590 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 3365 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 243:
#line 1595 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(1, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 3376 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 244:
#line 1601 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(2, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 3387 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 245:
#line 1607 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._bool_expression));
  USE((yystack_[0].value._bool_expression));
 }
#line 3398 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 246:
#line 1613 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(3, (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 3409 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 247:
#line 1619 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._bool_expression));
 }
#line 3419 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 248:
#line 1624 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    logic_expression *expr = new logic_expression((yystack_[1].value._unsigned_char), (yystack_[2].value._expression), (yystack_[0].value._expression));
    (yylhs.value._bool_expression) = new bool_expression(0,  expr);
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 3431 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 249:
#line 1631 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
 }
#line 3440 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 250:
#line 1636 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(5, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3451 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 251:
#line 1642 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(6, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3462 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 252:
#line 1648 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 3472 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 253:
#line 1653 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3480 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 254:
#line 1656 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(7, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3491 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 255:
#line 1662 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(8, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3502 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 256:
#line 1668 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 3512 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 257:
#line 1673 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3520 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 258:
#line 1676 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[1].value._expression);
  }
#line 3528 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 259:
#line 1679 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 3538 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 260:
#line 1684 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 3548 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 261:
#line 1689 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3556 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 262:
#line 1693 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(10, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3567 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 263:
#line 1699 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(12, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3578 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 264:
#line 1705 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 3588 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 265:
#line 1710 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3596 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 266:
#line 1713 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(9, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3607 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 267:
#line 1719 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 3617 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 268:
#line 1724 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3625 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 269:
#line 1727 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(11, (yystack_[0].value._expression), NULL);
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3636 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 270:
#line 1733 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._expression));
 }
#line 3646 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 271:
#line 1738 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3654 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 272:
#line 1741 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[1].value._expression);
  }
#line 3662 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 273:
#line 1744 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 3672 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 274:
#line 1749 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 3682 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 275:
#line 1754 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3690 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 276:
#line 1758 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(10, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3701 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 277:
#line 1764 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(12, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3712 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 278:
#line 1770 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 3722 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 279:
#line 1775 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3730 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 280:
#line 1778 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(9, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3741 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 281:
#line 1784 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 3751 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 282:
#line 1789 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3759 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 283:
#line 1792 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(11, (yystack_[0].value._expression), NULL);
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3770 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 284:
#line 1798 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._expression));
 }
#line 3780 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 285:
#line 1803 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3788 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 286:
#line 1806 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[1].value._expression);
  }
#line 3796 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 287:
#line 1809 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 3806 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 288:
#line 1814 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 3816 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 289:
#line 1819 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3824 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 290:
#line 1823 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(10, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3835 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 291:
#line 1829 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(12, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3846 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 292:
#line 1835 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 3856 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 293:
#line 1840 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3864 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 294:
#line 1843 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(9, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3875 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 295:
#line 1849 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 3885 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 296:
#line 1854 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3893 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 297:
#line 1857 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new bit_expression(11, (yystack_[0].value._expression), NULL);
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3904 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 298:
#line 1863 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._expression));
 }
#line 3914 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 299:
#line 1868 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3922 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 300:
#line 1871 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[1].value._expression);
  }
#line 3930 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 301:
#line 1874 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 3940 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 302:
#line 1879 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 3950 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 303:
#line 1884 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3958 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 304:
#line 1888 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(5, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3969 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 305:
#line 1894 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(6, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 3980 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 306:
#line 1900 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 3990 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 307:
#line 1905 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 3998 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 308:
#line 1908 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(7, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 4009 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 309:
#line 1914 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(8, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 4020 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 310:
#line 1920 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 4030 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 311:
#line 1925 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 4038 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 312:
#line 1928 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[1].value._expression);
  }
#line 4046 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 313:
#line 1931 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 4056 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 314:
#line 1936 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 4066 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 315:
#line 1941 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 4074 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 316:
#line 1944 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(5, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 4085 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 317:
#line 1950 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(6, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 4096 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 318:
#line 1956 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 4106 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 319:
#line 1961 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 4114 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 320:
#line 1964 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(7, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 4125 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 321:
#line 1970 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    (yylhs.value._expression) = new arithmetic_expression(8, (yystack_[2].value._expression), (yystack_[0].value._expression));
  } else
    (yylhs.value._expression) = NULL;
 }
#line 4136 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 322:
#line 1976 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._expression));
 }
#line 4146 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 323:
#line 1981 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 4154 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 324:
#line 1984 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[1].value._expression);
  }
#line 4162 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 325:
#line 1987 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 4172 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 326:
#line 1992 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._expression));
 }
#line 4182 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 327:
#line 1997 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._expression);
  }
#line 4190 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 328:
#line 2003 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = (yystack_[1].value._bool_expression); 
 }
#line 4198 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 329:
#line 2006 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 4208 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 330:
#line 2011 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 4218 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 331:
#line 2016 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 4228 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 332:
#line 2021 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(1, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4239 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 333:
#line 2027 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(2, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4250 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 334:
#line 2033 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._bool_expression));
  USE((yystack_[0].value._bool_expression));
 }
#line 4261 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 335:
#line 2039 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(3, (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4272 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 336:
#line 2045 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._bool_expression));
 }
#line 4282 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 337:
#line 2050 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    logic_expression *expr = new logic_expression((yystack_[1].value._unsigned_char), (yystack_[2].value._expression), (yystack_[0].value._expression));
    (yylhs.value._bool_expression) = new bool_expression(0,  expr);
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4294 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 338:
#line 2057 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.sval)!=NULL) {
    laction *a = new laction();
    variable *v;
    int i = search_string_table((yystack_[0].value.sval));
    if(i>=0) {
      v = new variable((*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      v = new variable((yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
    logic_expression *expr = new logic_expression(0, a, v);
    (yylhs.value._bool_expression) = new bool_expression(0,  expr);
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4316 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 339:
#line 2074 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4326 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 340:
#line 2079 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4336 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 341:
#line 2084 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4346 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 342:
#line 2089 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[4].value.sval)!=NULL && (yystack_[0].value.sval)!=NULL) {
    laction *a;
    int i = search_string_table((yystack_[4].value.sval));
    if(i>=0) {
      a = new laction((*string_table)[i]);
      free((yystack_[4].value.sval));
    } else {
      a = new laction((yystack_[4].value.sval));
      string_table->push_back((yystack_[4].value.sval));
    }
    variable *v;
    int j = search_string_table((yystack_[0].value.sval));
    if(j>=0) {
      if(i>=0)
	v = new variable((*string_table)[i], (*string_table)[j]);
      else
	v = new variable((yystack_[4].value.sval), (*string_table)[j]);
      free((yystack_[0].value.sval));
    } else {
      if(i>=0)
	v = new variable((*string_table)[i], (yystack_[0].value.sval));
      else
	v = new variable((yystack_[4].value.sval), (yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
    logic_expression *expr = new logic_expression(0, a, v);
    bool_expression *bexpr = new bool_expression(0,  expr);
    i = search_logic_expression_table(bexpr);
    if(i>=0) {
      (yylhs.value._bool_expression) = (*logic_expression_table)[i];
      delete a;
      delete v;
      delete expr;
      delete bexpr;
    } else {
      (yylhs.value._bool_expression) = bexpr;
      logic_expression_table->push_back(bexpr);
    }
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4393 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 343:
#line 2131 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4404 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 344:
#line 2137 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4415 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 345:
#line 2143 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4426 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 346:
#line 2149 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4437 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 347:
#line 2155 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4448 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 348:
#line 2161 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4459 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 349:
#line 2167 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4470 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 350:
#line 2173 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  }
#line 4479 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 351:
#line 2178 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._unsigned_char) = 2;
 }
#line 4487 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 352:
#line 2181 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._unsigned_char) = 3;
  }
#line 4495 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 353:
#line 2184 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._unsigned_char) = 4;
  }
#line 4503 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 354:
#line 2187 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._unsigned_char) = 5;
  }
#line 4511 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 355:
#line 2190 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._unsigned_char) = 0;
  }
#line 4519 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 356:
#line 2193 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._unsigned_char) = 1;
  }
#line 4527 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 357:
#line 2198 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = (yystack_[1].value._bool_expression); 
 }
#line 4535 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 358:
#line 2201 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 4545 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 359:
#line 2206 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 4555 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 360:
#line 2211 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 4565 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 361:
#line 2216 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(1, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4576 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 362:
#line 2222 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(2, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4587 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 363:
#line 2228 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._bool_expression));
  USE((yystack_[0].value._bool_expression));
 }
#line 4598 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 364:
#line 2234 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(3, (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4609 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 365:
#line 2240 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._bool_expression));
 }
#line 4619 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 366:
#line 2245 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    logic_expression *expr = new logic_expression((yystack_[1].value._unsigned_char), (yystack_[2].value._expression), (yystack_[0].value._expression));
    (yylhs.value._bool_expression) = new bool_expression(0,  expr);
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4631 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 367:
#line 2252 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.sval)!=NULL) {
    laction *a = new laction();
    variable *v;
    int i = search_string_table((yystack_[0].value.sval));
    if(i>=0) {
      v = new variable((*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      v = new variable((yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
    logic_expression *expr = new logic_expression(0, a, v);
    (yylhs.value._bool_expression) = new bool_expression(0,  expr);
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4653 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 368:
#line 2269 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4663 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 369:
#line 2274 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4673 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 370:
#line 2279 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4683 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 371:
#line 2284 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[4].value.sval)!=NULL && (yystack_[0].value.sval)!=NULL) {
    laction *a;
    int i = search_string_table((yystack_[4].value.sval));
    if(i>=0) {
      a = new laction((*string_table)[i]);
      free((yystack_[4].value.sval));
    } else {
      a = new laction((yystack_[4].value.sval));
      string_table->push_back((yystack_[4].value.sval));
    }
    variable *v;
    int j = search_string_table((yystack_[0].value.sval));
    if(j>=0) {
      if(i>=0)
	v = new variable((*string_table)[i], (*string_table)[j]);
      else
	v = new variable((yystack_[4].value.sval), (*string_table)[j]);
      free((yystack_[0].value.sval));
    } else {
      if(i>=0)
	v = new variable((*string_table)[i], (yystack_[0].value.sval));
      else
	v = new variable((yystack_[4].value.sval), (yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
    logic_expression *expr = new logic_expression(0, a, v);
    (yylhs.value._bool_expression) = new bool_expression(0,  expr);
  } else 
    (yylhs.value._bool_expression) = NULL;
 }
#line 4719 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 372:
#line 2315 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4730 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 373:
#line 2321 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4741 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 374:
#line 2327 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4752 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 375:
#line 2333 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4763 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 376:
#line 2339 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4774 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 377:
#line 2345 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4785 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 378:
#line 2351 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value.sval));
 }
#line 4796 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 379:
#line 2357 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.sval)!=NULL) {
    laction *a = new laction((*string_table)[0]);
    variable *v;
    int j = search_string_table((yystack_[0].value.sval));
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free((yystack_[0].value.sval));
    } else { 
      v = new variable((*string_table)[0], (yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
    logic_expression *expr = new logic_expression(0, a, v);
    (yylhs.value._bool_expression) = new bool_expression(0,  expr);
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 4818 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 380:
#line 2374 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4828 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 381:
#line 2379 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4838 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 382:
#line 2384 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4848 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 383:
#line 2389 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4858 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 384:
#line 2394 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4868 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 385:
#line 2399 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
 }
#line 4878 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 386:
#line 2404 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  }
#line 4887 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 387:
#line 2410 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._bool_value);
 }
#line 4895 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 388:
#line 2413 "parser/nssis_new.yy" // lalr1.cc:859
    {
    int i = search_string_table((yystack_[0].value.sval));
    if(i>=0) {
      (yylhs.value._expression) = new variable((*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      (yylhs.value._expression) = new variable((yystack_[0].value.sval)); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back((yystack_[0].value.sval));
    }
  }
#line 4910 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 389:
#line 2423 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = new int_value((yystack_[0].value.ival));
  }
#line 4918 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 390:
#line 2426 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_value) = new bool_value(true);
  }
#line 4926 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 391:
#line 2429 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_value) = new bool_value(false);
  }
#line 4934 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 392:
#line 2433 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._bool_value);
 }
#line 4942 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 393:
#line 2436 "parser/nssis_new.yy" // lalr1.cc:859
    {
    int i = search_string_table((yystack_[0].value.sval));
    if(i>=0) {
      (yylhs.value._expression) = new variable((*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      (yylhs.value._expression) = new variable((yystack_[0].value.sval)); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back((yystack_[0].value.sval));
    }
  }
#line 4957 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 394:
#line 2446 "parser/nssis_new.yy" // lalr1.cc:859
    {
    int i = search_string_table((yystack_[0].value.sval));
    variable *var;
    if(i>=0) {
      var = new variable((*string_table)[0], (*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      var = new variable((*string_table)[0], (yystack_[0].value.sval)); 
      string_table->push_back((yystack_[0].value.sval));
    }
    i = search_variable_table(var);
    if(i>=0) {
      (yylhs.value._expression) = (*variable_table)[i];
      delete var;
    } else {
      (yylhs.value._expression) = var;
      variable_table->push_back(var);
    }
  }
#line 4981 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 395:
#line 2465 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
  }
#line 4991 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 396:
#line 2470 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
  }
#line 5001 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 397:
#line 2475 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = new int_value((yystack_[0].value.ival));
  }
#line 5009 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 398:
#line 2478 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._bool_value);
 }
#line 5017 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 399:
#line 2481 "parser/nssis_new.yy" // lalr1.cc:859
    {
    int i = search_string_table((yystack_[0].value.sval));
    if(i>=0) {
      (yylhs.value._expression) = new variable((*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      (yylhs.value._expression) = new variable((yystack_[0].value.sval)); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back((yystack_[0].value.sval));
    }
  }
#line 5032 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 400:
#line 2491 "parser/nssis_new.yy" // lalr1.cc:859
    {
    int i = search_string_table((yystack_[2].value.sval));
    int j = search_string_table((yystack_[0].value.sval));
    variable *var;
    if(i>=0) {
      if(j>=0) {
	var = new variable((*string_table)[i], (*string_table)[j]);
	free((yystack_[0].value.sval));
      } else {
	var = new variable((*string_table)[i], (yystack_[0].value.sval));
	string_table->push_back((yystack_[0].value.sval));
      }
      free((yystack_[2].value.sval));
    } else {
      if(j>=0) {
	var = new variable((yystack_[2].value.sval), (*string_table)[j]);
	free((yystack_[0].value.sval));
      } else {
	var = new variable((yystack_[2].value.sval), (yystack_[0].value.sval));
	string_table->push_back((yystack_[0].value.sval));
      }
      string_table->push_back((yystack_[2].value.sval));
    }
    i = search_variable_table(var);
    if(i>=0) {
      (yylhs.value._expression) = (*variable_table)[i];
      delete var;
    } else {
      (yylhs.value._expression) = var;
      variable_table->push_back(var);
    }
  }
#line 5069 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 401:
#line 2523 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value.sval));
  }
#line 5080 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 402:
#line 2529 "parser/nssis_new.yy" // lalr1.cc:859
    {
    int i = search_string_table((yystack_[0].value.sval));
    variable *var;
    if(i>=0) {
      var = new variable((*string_table)[0], (*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      var = new variable((*string_table)[0], (yystack_[0].value.sval)); 
      string_table->push_back((yystack_[0].value.sval));
    }
    i = search_variable_table(var);
    if(i>=0) {
      (yylhs.value._expression) = (*variable_table)[i];
      delete var;
    } else {
      (yylhs.value._expression) = var;
      variable_table->push_back(var);
    }
  }
#line 5104 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 403:
#line 2548 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
  }
#line 5114 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 404:
#line 2553 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value.sval));
  }
#line 5124 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 405:
#line 2558 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = new int_value((yystack_[0].value.ival));
  }
#line 5132 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 406:
#line 2562 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = (yystack_[0].value._bool_value);
 }
#line 5140 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 407:
#line 2565 "parser/nssis_new.yy" // lalr1.cc:859
    {
    int i = search_string_table((yystack_[0].value.sval));
    if(i>=0) {
      (yylhs.value._expression) = new enum_value((*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      (yylhs.value._expression) = new enum_value((yystack_[0].value.sval)); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back((yystack_[0].value.sval));
    }
  }
#line 5155 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 408:
#line 2575 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._expression) = new int_value((yystack_[0].value.ival));
  }
#line 5163 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 409:
#line 2580 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 5171 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 410:
#line 2583 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 5179 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 411:
#line 2586 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 5188 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 412:
#line 2590 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 5197 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 413:
#line 2594 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
  }
#line 5206 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 415:
#line 2599 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  }
#line 5214 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 416:
#line 2603 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value.sval)!=NULL && (yystack_[1].value._bool_expression)!=NULL) {
    (*is_evaluation)[*(yystack_[3].value.sval)] = (yystack_[1].value._bool_expression);
    free((yystack_[3].value.sval));
  } 
 }
#line 5225 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 417:
#line 2609 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._bool_expression));
 }
#line 5235 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 418:
#line 2614 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._bool_expression));
 }
#line 5245 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 419:
#line 2619 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._bool_expression));
 }
#line 5255 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 420:
#line 2624 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value.sval)!=NULL && (yystack_[1].value._bool_expression)!=NULL) {
    if(is_evaluation->find(*(yystack_[3].value.sval)) != is_evaluation->end())
      cout << "warning: atomic proposition " << *(yystack_[3].value.sval) << " has already been defined." << endl;
    (*is_evaluation)[*(yystack_[3].value.sval)] = (yystack_[1].value._bool_expression);
    free((yystack_[3].value.sval));
  }
 }
#line 5268 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 421:
#line 2632 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._bool_expression));
 }
#line 5278 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 422:
#line 2637 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._bool_expression));
 }
#line 5288 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 423:
#line 2642 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._bool_expression));
 }
#line 5298 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 424:
#line 2647 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  }
#line 5306 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 425:
#line 2651 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = (yystack_[1].value._bool_expression); 
 }
#line 5314 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 426:
#line 2654 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 5324 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 427:
#line 2659 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 5334 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 428:
#line 2664 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 5344 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 429:
#line 2669 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(1, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5355 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 430:
#line 2675 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(2, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5366 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 431:
#line 2681 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._bool_expression));USE((yystack_[0].value._bool_expression));
 }
#line 5376 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 432:
#line 2686 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(3, (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5387 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 433:
#line 2692 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._bool_expression));
 }
#line 5397 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 434:
#line 2697 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._expression)!=NULL && (yystack_[0].value._expression)!=NULL) {
    logic_expression *expr = new logic_expression((yystack_[1].value._unsigned_char), (yystack_[2].value._expression), (yystack_[0].value._expression));
    (yylhs.value._bool_expression) = new bool_expression(0,  expr);
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5409 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 435:
#line 2704 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  }
#line 5418 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 436:
#line 2712 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 5426 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 437:
#line 2715 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 5435 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 438:
#line 2719 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 5443 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 439:
#line 2722 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 5452 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 440:
#line 2726 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 5461 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 441:
#line 2730 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 5470 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 442:
#line 2734 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 5479 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 443:
#line 2738 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 5488 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 444:
#line 2742 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 5497 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 445:
#line 2746 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
  }
#line 5506 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 446:
#line 2750 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.ival)==1 && (yystack_[0].value.ival)==1)
    is_istates = (yystack_[1].value._bool_expression); 
 }
#line 5515 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 447:
#line 2754 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  }
#line 5523 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 448:
#line 2758 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = (yystack_[1].value._bool_expression); 
}
#line 5531 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 449:
#line 2761 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 5541 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 450:
#line 2766 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression));
 }
#line 5551 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 451:
#line 2771 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._bool_expression))
 }
#line 5561 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 452:
#line 2776 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(1, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5572 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 453:
#line 2782 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._bool_expression)!=NULL && (yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(2, (yystack_[2].value._bool_expression), (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5583 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 454:
#line 2788 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._bool_expression));USE((yystack_[0].value._bool_expression));
 }
#line 5593 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 455:
#line 2793 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._bool_expression)!=NULL)
    (yylhs.value._bool_expression) = new bool_expression(3, (yystack_[0].value._bool_expression));
  else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5604 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 456:
#line 2799 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._bool_expression));
 }
#line 5614 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 457:
#line 2804 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[6].value.sval)!=NULL && (yystack_[4].value.sval)!=NULL && (yystack_[2].value.sval)!=NULL && (yystack_[0].value.sval)!=NULL) {
    int i = search_string_table((yystack_[6].value.sval));
    int j = search_string_table((yystack_[4].value.sval));
    variable *v;
    if(i>=0) {
      if(j>=0) {
	v = new variable((*string_table)[i], (*string_table)[j]);
	free((yystack_[4].value.sval));
      } else {
	v = new variable((*string_table)[i], (yystack_[4].value.sval));
	string_table->push_back((yystack_[4].value.sval));
      }
      free((yystack_[6].value.sval));
    } else {
      if(j>=0) {
	v = new variable((yystack_[6].value.sval), (*string_table)[j]);
	free((yystack_[4].value.sval));
      } else {
	v = new variable((yystack_[6].value.sval), (yystack_[4].value.sval));
	string_table->push_back((yystack_[4].value.sval));
      }
      string_table->push_back((yystack_[6].value.sval));
    }
    i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    i = search_string_table((yystack_[2].value.sval));
    j = search_string_table((yystack_[0].value.sval));
    variable *v1;
    if(i>=0) {
      if(j>=0) {
	v1 = new variable((*string_table)[i], (*string_table)[j]);
	free((yystack_[0].value.sval));
      } else {
	v1 = new variable((*string_table)[i], (yystack_[0].value.sval));
	string_table->push_back((yystack_[0].value.sval));
      }
      free((yystack_[2].value.sval));
    } else {
      if(j>=0) {
	v1 = new variable((yystack_[2].value.sval), (*string_table)[j]);
	free((yystack_[0].value.sval));
      } else {
	v1 = new variable((yystack_[2].value.sval), (yystack_[0].value.sval));
	string_table->push_back((yystack_[0].value.sval));
      }
      string_table->push_back((yystack_[2].value.sval));
    }
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    logic_expression *e = new logic_expression(0, v, v1);
    bool_expression *bexpr = new bool_expression(0, e);
    i = search_logic_expression_table1(bexpr);
    if(i>=0) {
      (yylhs.value._bool_expression) = (*logic_expression_table1)[i];
      free((yystack_[2].value.sval));
      delete e;
      delete bexpr;
    } else {
      (yylhs.value._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5696 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 458:
#line 2881 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[6].value.sval)!=NULL && (yystack_[4].value.sval)!=NULL && (yystack_[0].value.sval)!=NULL) {
    int i = search_string_table((yystack_[6].value.sval));
    int j = search_string_table((yystack_[4].value.sval));
    variable *v;
    if(i>=0) {
      if(j>=0) {
	v = new variable((*string_table)[i], (*string_table)[j]);
	free((yystack_[4].value.sval));
      } else {
	v = new variable((*string_table)[i], (yystack_[4].value.sval));
	string_table->push_back((yystack_[4].value.sval));
      }
      free((yystack_[6].value.sval));
    } else {
      if(j>=0) {
	v = new variable((yystack_[6].value.sval), (*string_table)[j]);
	free((yystack_[4].value.sval));
      } else {
	v = new variable((yystack_[6].value.sval), (yystack_[4].value.sval));
	string_table->push_back((yystack_[4].value.sval));
      }
      string_table->push_back((yystack_[6].value.sval));
    }
    i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    j = search_string_table((yystack_[0].value.sval));
    variable *v1;
    if(j>=0) {
      v1 = new variable((*string_table)[0], (*string_table)[j]);
      free((yystack_[0].value.sval));
    } else {
      v1 = new variable((*string_table)[0], (yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
    
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    logic_expression *e = new logic_expression(0, v, v1);
    bool_expression *bexpr = new bool_expression(0, e);
    i = search_logic_expression_table1(bexpr);
    if(i>=0) {
      (yylhs.value._bool_expression) = (*logic_expression_table1)[i];
      delete e;
      delete bexpr;
    } else {
      (yylhs.value._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5765 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 459:
#line 2945 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[4].value.sval)!=NULL && (yystack_[2].value.sval)!=NULL && (yystack_[0].value.sval)!=NULL) {
    int j = search_string_table((yystack_[4].value.sval));
    variable *v;
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free((yystack_[4].value.sval));
    } else {
      v = new variable((*string_table)[0], (yystack_[4].value.sval));
      string_table->push_back((yystack_[4].value.sval));
    }
    int i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    i = search_string_table((yystack_[2].value.sval));
    j = search_string_table((yystack_[0].value.sval));
    variable *v1;
    if(i>=0) {
      if(j>=0) {
	v1 = new variable((*string_table)[i], (*string_table)[j]);
	free((yystack_[0].value.sval));
      } else {
	v1 = new variable((*string_table)[i], (yystack_[0].value.sval));
	string_table->push_back((yystack_[0].value.sval));
      }
      free((yystack_[2].value.sval));
    } else {
      if(j>=0) {
	v1 = new variable((yystack_[2].value.sval), (*string_table)[j]);
	free((yystack_[0].value.sval));
      } else {
	v1 = new variable((yystack_[2].value.sval), (yystack_[0].value.sval));
	string_table->push_back((yystack_[0].value.sval));
      }
      string_table->push_back((yystack_[2].value.sval));
    }
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    logic_expression *e = new logic_expression(0, v, v1);
    bool_expression *bexpr = new bool_expression(0, e);
    i = search_logic_expression_table1(bexpr);
    if(i>=0) {
      (yylhs.value._bool_expression) = (*logic_expression_table1)[i];
      free((yystack_[2].value.sval));
      delete e;
      delete bexpr;
    } else {
      (yylhs.value._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5834 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 460:
#line 3009 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[4].value.sval)!=NULL && (yystack_[2].value.sval)!=NULL && (yystack_[0].value._expression)!=NULL) {
    int i = search_string_table((yystack_[4].value.sval));
    int j = search_string_table((yystack_[2].value.sval));
    variable *v;
    if(i>=0) {
      if(j>=0) {
	v = new variable((*string_table)[i], (*string_table)[j]);
	free((yystack_[2].value.sval));
      } else {
	v = new variable((*string_table)[i], (yystack_[2].value.sval));
	string_table->push_back((yystack_[2].value.sval));
      }
      free((yystack_[4].value.sval));
    } else {
      if(j>=0) {
	v = new variable((yystack_[4].value.sval), (*string_table)[j]);
	free((yystack_[2].value.sval));
      } else {
	v = new variable((yystack_[4].value.sval), (yystack_[2].value.sval));
	string_table->push_back((yystack_[2].value.sval));
      }
      string_table->push_back((yystack_[4].value.sval));
    }
    i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }
    logic_expression *e = new logic_expression(0, v, (yystack_[0].value._expression));
    bool_expression *bexpr = new bool_expression(0, e);
    i = search_logic_expression_table1(bexpr);
    if(i>=0) {
      (yylhs.value._bool_expression) = (*logic_expression_table1)[i];
      free((yystack_[0].value._expression));
      delete e;
      delete bexpr;
    } else {
      (yylhs.value._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5885 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 461:
#line 3055 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value._expression));
 }
#line 5897 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 462:
#line 3062 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value._expression));
 }
#line 5909 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 463:
#line 3069 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[4].value.sval));
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value._expression));
 }
#line 5921 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 464:
#line 3076 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[4].value.sval)!=NULL && (yystack_[0].value.sval)!=NULL) {
    int j = search_string_table((yystack_[4].value.sval));
    variable *v;
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free((yystack_[4].value.sval));
    } else {
      v = new variable((*string_table)[0], (yystack_[4].value.sval));
      string_table->push_back((yystack_[4].value.sval));
    }
    int i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    j = search_string_table((yystack_[0].value.sval));
    variable *v1;
    if(j>=0) {
      v1 = new variable((*string_table)[0], (*string_table)[j]);
      free((yystack_[0].value.sval));
    } else {
      v1 = new variable((*string_table)[0], (yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    logic_expression *e = new logic_expression(0, v, v1);
    bool_expression *bexpr = new bool_expression(0, e);
    i = search_logic_expression_table1(bexpr);
    if(i>=0) {
      (yylhs.value._bool_expression) = (*logic_expression_table1)[i];
      delete e;
      delete bexpr;
    } else {
      (yylhs.value._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 5976 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 465:
#line 3126 "parser/nssis_new.yy" // lalr1.cc:859
    {	
  if((yystack_[2].value.sval)!=NULL && (yystack_[0].value._expression)!=NULL) {
    int j = search_string_table((yystack_[2].value.sval));
    variable *v;
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free((yystack_[2].value.sval));
    } else {
      v = new variable((*string_table)[0], (yystack_[2].value.sval));
      string_table->push_back((yystack_[2].value.sval));
    }
    j = search_variable_table(v);
    if(j>=0) {
      delete v;
      v = (*variable_table)[j];
    } else {
      variable_table->push_back(v);
    }
    logic_expression *e = new logic_expression(0, v, (yystack_[0].value._expression));
    bool_expression *bexpr = new bool_expression(0, e);
    j = search_logic_expression_table1(bexpr);
    if(j>=0) {
      (yylhs.value._bool_expression) = (*logic_expression_table1)[j];
      free((yystack_[0].value._expression));
      delete e;
      delete bexpr;
    } else {
      (yylhs.value._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yylhs.value._bool_expression) = NULL;
 }
#line 6014 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 466:
#line 3159 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value._expression));
 }
#line 6025 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 467:
#line 3165 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value._expression));
 }
#line 6036 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 468:
#line 3171 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value._expression));
 }
#line 6047 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 469:
#line 3177 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value._expression));
 }
#line 6058 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 470:
#line 3183 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value._expression));
 }
#line 6069 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 471:
#line 3189 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
  USE((yystack_[0].value._expression));
 }
#line 6080 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 472:
#line 3195 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._bool_expression) = NULL;
  driver.syntax_error = true;
  }
#line 6089 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 473:
#line 3202 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 6097 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 474:
#line 3205 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 6106 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 475:
#line 3209 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 6114 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 476:
#line 3212 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 6123 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 477:
#line 3216 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 6132 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 478:
#line 3220 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
  }
#line 6141 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 481:
#line 3226 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  }
#line 6149 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 482:
#line 3230 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 6157 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 483:
#line 3233 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 6166 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 484:
#line 3237 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 6175 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 485:
#line 3241 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
  }
#line 6184 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 486:
#line 3245 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 6192 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 487:
#line 3248 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 6201 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 488:
#line 3252 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 6210 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 489:
#line 3256 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
  }
#line 6219 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 490:
#line 3260 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value.sval)!=NULL && (yystack_[2].value.ival)==1 && (yystack_[1].value.set_string)!=NULL && (yystack_[0].value.ival)==1) {
    (*is_groups)[*(yystack_[3].value.sval)] = *(yystack_[1].value.set_string);
    free((yystack_[3].value.sval));
  }
 }
#line 6230 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 491:
#line 3266 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value.sval)!=NULL && (yystack_[2].value.ival)==1 && (yystack_[1].value.set_string)!=NULL && (yystack_[0].value.ival)==1) {
    if(is_groups->find(*(yystack_[3].value.sval)) != is_groups->end())
      cout << "warning: group " << *(yystack_[3].value.sval) << " already exists." << endl; 
    (*is_groups)[*(yystack_[3].value.sval)] = *(yystack_[1].value.set_string);
    free((yystack_[3].value.sval));
  }
 }
#line 6243 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 492:
#line 3274 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  }
#line 6251 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 493:
#line 3278 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.sval)!=NULL) {
    (yylhs.value.set_string) = new set<string>;
    (yylhs.value.set_string)->insert(*(yystack_[0].value.sval));
  } else
    (yylhs.value.set_string) = NULL;
 }
#line 6263 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 494:
#line 3285 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.set_string)!=NULL && (yystack_[0].value.sval)!=NULL) {
    pair<set<string>::iterator, bool> ret = (yystack_[2].value.set_string)->insert(*(yystack_[0].value.sval));
    if(!ret.second)
      cout << "warning: agent " << *(yystack_[0].value.sval) << " in group definition is redundant." << endl;
    (yylhs.value.set_string) = (yystack_[2].value.set_string);
  } else
    (yylhs.value.set_string) = NULL;
 }
#line 6277 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 495:
#line 3294 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.set_string) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.set_string));USE((yystack_[0].value.sval));
 }
#line 6287 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 496:
#line 3299 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.set_string) = NULL;
  driver.syntax_error = true;
  }
#line 6296 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 497:
#line 3303 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.sval) = (*string_table)[0];
 }
#line 6304 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 498:
#line 3306 "parser/nssis_new.yy" // lalr1.cc:859
    {
    int i = search_string_table((yystack_[0].value.sval));
    if(i>=0) {
      (yylhs.value.sval) = (*string_table)[i];
      free((yystack_[0].value.sval));
    } else {
      (yylhs.value.sval) = (yystack_[0].value.sval);
      string_table->push_back((yystack_[0].value.sval));
    }
  }
#line 6319 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 499:
#line 3316 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.sval) = NULL;
  driver.syntax_error = true;
  }
#line 6328 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 500:
#line 3323 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 6336 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 501:
#line 3326 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 6345 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 502:
#line 3330 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 6353 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 503:
#line 3333 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 6362 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 504:
#line 3337 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 6371 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 505:
#line 3341 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
  }
#line 6380 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 508:
#line 3348 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  if((yystack_[1].value._fairness_expression)!=NULL)
    is_fairness->push_back((yystack_[1].value._fairness_expression));
 }
#line 6389 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 509:
#line 3352 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6398 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 510:
#line 3356 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  if((yystack_[1].value._fairness_expression)!=NULL)
    is_fairness->push_back((yystack_[1].value._fairness_expression)); 
 }
#line 6407 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 511:
#line 3360 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6416 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 512:
#line 3364 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  }
#line 6424 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 513:
#line 3368 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value._fairness_expression)!=NULL && (yystack_[1].value._fairness_expression)!=NULL)
    (yylhs.value.dual_fairness_expression) = new pair<fairness_expression *, fairness_expression *>((yystack_[3].value._fairness_expression), (yystack_[1].value._fairness_expression));
  else
    (yylhs.value.dual_fairness_expression) = NULL;
 }
#line 6435 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 514:
#line 3374 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._fairness_expression));USE((yystack_[1].value._fairness_expression));
 }
#line 6445 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 515:
#line 3379 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._fairness_expression));USE((yystack_[1].value._fairness_expression));
 }
#line 6455 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 516:
#line 3384 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._fairness_expression));USE((yystack_[1].value._fairness_expression));
 }
#line 6465 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 517:
#line 3389 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._fairness_expression));USE((yystack_[1].value._fairness_expression));
 }
#line 6475 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 518:
#line 3394 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._fairness_expression));USE((yystack_[1].value._fairness_expression));
 }
#line 6485 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 519:
#line 3399 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._fairness_expression));USE((yystack_[1].value._fairness_expression));
 }
#line 6495 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 520:
#line 3404 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._fairness_expression));USE((yystack_[1].value._fairness_expression));
 }
#line 6505 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 521:
#line 3409 "parser/nssis_new.yy" // lalr1.cc:859
    {
    if((yystack_[3].value.sval)!=NULL && (yystack_[1].value._fairness_expression)!=NULL) {
      int i = search_string_table((yystack_[3].value.sval));
      if(i>=0) {
	(yylhs.value.ID_fairness_expression) = new pair<string *, fairness_expression *>((*string_table)[i], (yystack_[1].value._fairness_expression));
	free((yystack_[3].value.sval));
      } else {
	(yylhs.value.ID_fairness_expression) = new pair<string *, fairness_expression *>((yystack_[3].value.sval), (yystack_[1].value._fairness_expression));
	string_table->push_back((yystack_[3].value.sval));
      }
    } else
      (yylhs.value.ID_fairness_expression) = NULL;
 }
#line 6523 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 522:
#line 3422 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6534 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 523:
#line 3428 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6545 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 524:
#line 3434 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6556 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 525:
#line 3440 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6567 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 526:
#line 3446 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6578 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 527:
#line 3452 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6589 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 528:
#line 3458 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6600 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 529:
#line 3464 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value._fairness_expression)!=NULL)
    (yylhs.value.ID_fairness_expression) = new pair<string *, fairness_expression *>((*string_table)[0], (yystack_[1].value._fairness_expression));
  else
    (yylhs.value.ID_fairness_expression) = NULL;
 }
#line 6611 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 530:
#line 3470 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6621 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 531:
#line 3475 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6631 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 532:
#line 3480 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6641 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 533:
#line 3485 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6651 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 534:
#line 3490 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6661 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 535:
#line 3495 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6671 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 536:
#line 3500 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6681 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 537:
#line 3505 "parser/nssis_new.yy" // lalr1.cc:859
    {
    if((yystack_[3].value.sval)!=NULL && (yystack_[1].value._fairness_expression)!=NULL) {
      int i = search_string_table((yystack_[3].value.sval));
      if(i>=0) {
	(yylhs.value.ID_fairness_expression) = new pair<string *, fairness_expression *>((*string_table)[i], (yystack_[1].value._fairness_expression));
	free((yystack_[3].value.sval));
      } else {
	(yylhs.value.ID_fairness_expression) = new pair<string *, fairness_expression *>((yystack_[3].value.sval), (yystack_[1].value._fairness_expression));
	string_table->push_back((yystack_[3].value.sval));
      }
    } else
      (yylhs.value.ID_fairness_expression) = NULL;
 }
#line 6699 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 538:
#line 3518 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6710 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 539:
#line 3524 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6721 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 540:
#line 3530 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6732 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 541:
#line 3536 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6743 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 542:
#line 3542 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6754 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 543:
#line 3548 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6765 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 544:
#line 3554 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._fairness_expression));
 }
#line 6776 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 545:
#line 3561 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._fairness_expression) = (yystack_[1].value._fairness_expression); 
 }
#line 6784 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 546:
#line 3564 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6794 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 547:
#line 3569 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6804 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 548:
#line 3574 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._fairness_expression));
 }
#line 6814 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 549:
#line 3579 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._fairness_expression)!=NULL && (yystack_[0].value._fairness_expression)!=NULL)
    (yylhs.value._fairness_expression) = new fairness_expression(1, (yystack_[2].value._fairness_expression), (yystack_[0].value._fairness_expression));
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6825 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 550:
#line 3585 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._fairness_expression)!=NULL && (yystack_[0].value._fairness_expression)!=NULL)
    (yylhs.value._fairness_expression) = new fairness_expression(2, (yystack_[2].value._fairness_expression), (yystack_[0].value._fairness_expression));
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6836 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 551:
#line 3591 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._fairness_expression));USE((yystack_[0].value._fairness_expression));
 }
#line 6846 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 552:
#line 3596 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._fairness_expression)!=NULL)
    (yylhs.value._fairness_expression) = new fairness_expression(3, (yystack_[0].value._fairness_expression));
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6857 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 553:
#line 3602 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._fairness_expression));
 }
#line 6867 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 554:
#line 3607 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._fairness_expression)!=NULL && (yystack_[0].value._fairness_expression)!=NULL)
    (yylhs.value._fairness_expression) = new fairness_expression(4, (yystack_[2].value._fairness_expression), (yystack_[0].value._fairness_expression));
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6878 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 555:
#line 3613 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._fairness_expression)!=NULL)
    (yylhs.value._fairness_expression) = new fairness_expression(10, (yystack_[0].value._fairness_expression));
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6889 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 556:
#line 3619 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._fairness_expression)!=NULL)
    (yylhs.value._fairness_expression) = new fairness_expression(11, (yystack_[0].value._fairness_expression));
  else
    (yylhs.value._fairness_expression) = NULL;
  }
#line 6900 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 557:
#line 3625 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._fairness_expression)!=NULL)
    (yylhs.value._fairness_expression) = new fairness_expression(12, (yystack_[0].value._fairness_expression));
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6911 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 558:
#line 3631 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._fairness_expression)!=NULL)
    (yylhs.value._fairness_expression) = new fairness_expression(13, (yystack_[0].value._fairness_expression));
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6922 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 559:
#line 3637 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._fairness_expression)!=NULL)
    (yylhs.value._fairness_expression) = new fairness_expression(14, (yystack_[0].value._fairness_expression));
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6933 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 560:
#line 3643 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._fairness_expression)!=NULL)
    (yylhs.value._fairness_expression) = new fairness_expression(15, (yystack_[0].value._fairness_expression));
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6944 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 561:
#line 3649 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.dual_fairness_expression)!=NULL) {
    (yylhs.value._fairness_expression) = new fairness_expression(16, (yystack_[0].value.dual_fairness_expression)->first, (yystack_[0].value.dual_fairness_expression)->second);
    free((yystack_[0].value.dual_fairness_expression));
  }
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6957 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 562:
#line 3657 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.dual_fairness_expression)!=NULL) {
    (yylhs.value._fairness_expression) = new fairness_expression(17, (yystack_[0].value.dual_fairness_expression)->first, (yystack_[0].value.dual_fairness_expression)->second);
    free((yystack_[0].value.dual_fairness_expression));
  }
  else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6970 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 563:
#line 3665 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.ID_fairness_expression)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_fairness_expression)->first);
    fairness_expression *a = new fairness_expression(ap);
    (yylhs.value._fairness_expression) = new fairness_expression(30, a, (yystack_[0].value.ID_fairness_expression)->second);
    free((yystack_[0].value.ID_fairness_expression));
  } else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6984 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 564:
#line 3674 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // Knowledge in a group (everybody knows)
  if((yystack_[0].value.ID_fairness_expression)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_fairness_expression)->first);
    fairness_expression *a = new fairness_expression(ap);
    (yylhs.value._fairness_expression) = new fairness_expression(31, a, (yystack_[0].value.ID_fairness_expression)->second);
    free((yystack_[0].value.ID_fairness_expression));
  } else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 6999 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 565:
#line 3684 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // Common knowledge in a group
  if((yystack_[0].value.ID_fairness_expression)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_fairness_expression)->first);
    fairness_expression *a = new fairness_expression(ap);
    (yylhs.value._fairness_expression) = new fairness_expression(32, a, (yystack_[0].value.ID_fairness_expression)->second);
    free((yystack_[0].value.ID_fairness_expression));
  } else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 7014 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 566:
#line 3694 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // deontic operator
  if((yystack_[0].value.ID_fairness_expression)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_fairness_expression)->first);
    fairness_expression *a = new fairness_expression(ap);
    (yylhs.value._fairness_expression) = new fairness_expression(40, a, (yystack_[0].value.ID_fairness_expression)->second);
    free((yystack_[0].value.ID_fairness_expression));
  } else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 7029 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 567:
#line 3704 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // Distributed knowledge in a group
  if((yystack_[0].value.ID_fairness_expression)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_fairness_expression)->first);
    fairness_expression *a = new fairness_expression(ap);
    (yylhs.value._fairness_expression) = new fairness_expression(42, a, (yystack_[0].value.ID_fairness_expression)->second);
    free((yystack_[0].value.ID_fairness_expression));
  } else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 7044 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 568:
#line 3714 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._fairness_expression) = NULL;
  if((yystack_[0].value.ID_fairness_expression) != NULL)
    free((yystack_[0].value.ID_fairness_expression));
  driver.syntax_error = true;
 }
#line 7055 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 569:
#line 3720 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._fairness_expression) = NULL;
  if((yystack_[0].value.ID_fairness_expression) != NULL)
    free((yystack_[0].value.ID_fairness_expression));
  driver.syntax_error = true;
 }
#line 7066 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 570:
#line 3726 "parser/nssis_new.yy" // lalr1.cc:859
    {	
  if((yystack_[0].value.sval)!=NULL) {
    int i = search_string_table((yystack_[0].value.sval));
    atomic_proposition *ap;
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      ap = new atomic_proposition((yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
    (yylhs.value._fairness_expression) = new fairness_expression(ap);
  } else
    (yylhs.value._fairness_expression) = NULL;
  }
#line 7086 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 571:
#line 3741 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.sval)!=NULL) {
    string *newname = new string(*(yystack_[2].value.sval) + ".GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free((yystack_[2].value.sval));
    (yylhs.value._fairness_expression) = new fairness_expression(ap);
  } else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 7108 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 572:
#line 3758 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.sval)!=NULL) {
    string *newname = new string(*(yystack_[2].value.sval) + ".RedStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free((yystack_[2].value.sval));
    (yylhs.value._fairness_expression) = new fairness_expression(ap);
  } else
    (yylhs.value._fairness_expression) = NULL;
 }
#line 7130 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 573:
#line 3775 "parser/nssis_new.yy" // lalr1.cc:859
    {
    string *newname = new string("Environment.GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    (yylhs.value._fairness_expression) = new fairness_expression(ap);
 }
#line 7148 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 574:
#line 3788 "parser/nssis_new.yy" // lalr1.cc:859
    {
  string *newname = new string("Environment.RedStates");
  atomic_proposition *ap;
  int i = search_string_table(newname);
  if(i>=0) {
    ap = new atomic_proposition((*string_table)[i]);
    free(newname);
  } else {
    ap = new atomic_proposition(newname);
    string_table->push_back(newname);
  }
  (yylhs.value._fairness_expression) = new fairness_expression(ap);
 }
#line 7166 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 575:
#line 3801 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
 }
#line 7176 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 576:
#line 3806 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
 }
#line 7186 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 577:
#line 3811 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
 }
#line 7196 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 578:
#line 3816 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._fairness_expression) = NULL;
  driver.syntax_error = true;
  }
#line 7205 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 579:
#line 3823 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 7213 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 580:
#line 3826 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 7222 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 581:
#line 3830 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 1;
 }
#line 7230 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 582:
#line 3833 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 7239 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 583:
#line 3837 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
 }
#line 7248 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 584:
#line 3841 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ival) = 0;
  driver.syntax_error = true;
  }
#line 7257 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 586:
#line 3847 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  if((yystack_[1].value._modal_formula)!=NULL) {
    is_formulae->push_back(*(yystack_[1].value._modal_formula));
  }
 }
#line 7267 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 587:
#line 3852 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7276 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 588:
#line 3856 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  if((yystack_[1].value._modal_formula)!=NULL) {
    is_formulae->push_back(*(yystack_[1].value._modal_formula)); 
  }
 }
#line 7286 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 589:
#line 3861 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7295 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 590:
#line 3865 "parser/nssis_new.yy" // lalr1.cc:859
    {
  driver.syntax_error = true;
  }
#line 7303 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 591:
#line 3869 "parser/nssis_new.yy" // lalr1.cc:859
    {
    int i = search_string_table((yystack_[1].value.sval));
    if(i>=0) {
      (yylhs.value.sval) = (*string_table)[i];
      free((yystack_[1].value.sval));
    } else {
      (yylhs.value.sval) = (yystack_[1].value.sval);
      string_table->push_back((yystack_[1].value.sval));
    }
 }
#line 7318 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 592:
#line 3879 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.sval) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value.sval));
 }
#line 7328 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 593:
#line 3884 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.sval) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value.sval));
 }
#line 7338 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 594:
#line 3889 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value._modal_formula)!=NULL && (yystack_[1].value._modal_formula)!=NULL)
    (yylhs.value.dual_modal_formula) = new pair<modal_formula *, modal_formula *>((yystack_[3].value._modal_formula), (yystack_[1].value._modal_formula));
  else
    (yylhs.value.dual_modal_formula) = NULL;
 }
#line 7349 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 595:
#line 3895 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._modal_formula));USE((yystack_[1].value._modal_formula));
 }
#line 7359 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 596:
#line 3900 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._modal_formula));USE((yystack_[1].value._modal_formula));
 }
#line 7369 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 597:
#line 3905 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._modal_formula));USE((yystack_[1].value._modal_formula));
 }
#line 7379 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 598:
#line 3910 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._modal_formula));USE((yystack_[1].value._modal_formula));
 }
#line 7389 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 599:
#line 3915 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._modal_formula));USE((yystack_[1].value._modal_formula));
 }
#line 7399 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 600:
#line 3920 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._modal_formula));USE((yystack_[1].value._modal_formula));
 }
#line 7409 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 601:
#line 3925 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value._modal_formula));USE((yystack_[1].value._modal_formula));
 }
#line 7419 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 602:
#line 3930 "parser/nssis_new.yy" // lalr1.cc:859
    {
    if((yystack_[3].value.sval)!=NULL && (yystack_[1].value._modal_formula)!=NULL) {
      int i = search_string_table((yystack_[3].value.sval));
      if(i>=0) {
	(yylhs.value.ID_modal_formula) = new pair<string *, modal_formula *>((*string_table)[i], (yystack_[1].value._modal_formula));
	free((yystack_[3].value.sval));
      } else {
	(yylhs.value.ID_modal_formula) = new pair<string *, modal_formula *>((yystack_[3].value.sval), (yystack_[1].value._modal_formula));
	string_table->push_back((yystack_[3].value.sval));
      }
    } else
    (yylhs.value.ID_modal_formula) = NULL;
 }
#line 7437 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 603:
#line 3943 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7448 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 604:
#line 3949 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7459 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 605:
#line 3955 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7470 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 606:
#line 3961 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7481 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 607:
#line 3967 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7492 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 608:
#line 3973 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7503 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 609:
#line 3979 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7514 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 610:
#line 3985 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[1].value._modal_formula)!=NULL)
    (yylhs.value.ID_modal_formula) = new pair<string *, modal_formula *>((*string_table)[0], (yystack_[1].value._modal_formula));
  else
    (yylhs.value.ID_modal_formula) = NULL;
 }
#line 7525 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 611:
#line 3991 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7535 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 612:
#line 3996 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7545 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 613:
#line 4001 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7555 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 614:
#line 4006 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7565 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 615:
#line 4011 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7575 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 616:
#line 4016 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7585 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 617:
#line 4021 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7595 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 618:
#line 4026 "parser/nssis_new.yy" // lalr1.cc:859
    {
    if((yystack_[3].value.sval)!=NULL && (yystack_[1].value._modal_formula)!=NULL) {
      int i = search_string_table((yystack_[3].value.sval));
      if(i>=0) {
	(yylhs.value.ID_modal_formula) = new pair<string *, modal_formula *>((*string_table)[i], (yystack_[1].value._modal_formula));
	free((yystack_[3].value.sval));
      } else {
	(yylhs.value.ID_modal_formula) = new pair<string *, modal_formula *>((yystack_[3].value.sval), (yystack_[1].value._modal_formula));
	string_table->push_back((yystack_[3].value.sval));
      }
    } else
      (yylhs.value.ID_modal_formula) = NULL;
 }
#line 7613 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 619:
#line 4039 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7624 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 620:
#line 4045 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7635 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 621:
#line 4051 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7646 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 622:
#line 4057 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7657 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 623:
#line 4063 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7668 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 624:
#line 4069 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7679 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 625:
#line 4075 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[3].value.sval));
  USE((yystack_[1].value._modal_formula));
 }
#line 7690 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 626:
#line 4082 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[5].value.sval)!=NULL && (yystack_[3].value.sval)!=NULL && (yystack_[1].value._modal_formula)!=NULL) {
    pair<string *, string *> *two;// = new pair<string *, string *>($2, $4);
    int i = search_string_table((yystack_[5].value.sval));
    int j = search_string_table((yystack_[3].value.sval));
    if(i>=0) {
      if(j>=0) {
	two = new pair<string *, string *>((*string_table)[i], (*string_table)[j]);
	free((yystack_[3].value.sval));
      } else {
	two = new pair<string *, string *>((*string_table)[i], (yystack_[3].value.sval));
	string_table->push_back((yystack_[3].value.sval));
      }
      free((yystack_[5].value.sval));
    } else {
      if(j>=0) {
	two = new pair<string *, string *>((yystack_[5].value.sval), (*string_table)[j]);
	free((yystack_[3].value.sval));
      } else {
	two = new pair<string *, string *>((yystack_[5].value.sval), (yystack_[3].value.sval));
	string_table->push_back((yystack_[3].value.sval));
      }
      string_table->push_back((yystack_[5].value.sval));
    }
    (yylhs.value.ID_ID_modal_formula) = new pair<pair<string *, string *>*, modal_formula *>(two, (yystack_[1].value._modal_formula));
  } else
    (yylhs.value.ID_ID_modal_formula) = NULL;
 }
#line 7723 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 627:
#line 4110 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[5].value.sval)!=NULL && (yystack_[1].value._modal_formula)!=NULL) {
    pair<string *, string *> *two;// = new pair<string *, string *>($2, (*string_table)[0]);
    int i = search_string_table((yystack_[5].value.sval));
    if(i>=0) {
      two = new pair<string *, string *>((*string_table)[i], (*string_table)[0]);
      free((yystack_[5].value.sval));
    } else {
      two = new pair<string *, string *>((yystack_[5].value.sval), (*string_table)[0]);
      string_table->push_back((yystack_[5].value.sval));
    }
    (yylhs.value.ID_ID_modal_formula) = new pair<pair<string *, string *>*, modal_formula *>(two, (yystack_[1].value._modal_formula));
  } else
    (yylhs.value.ID_ID_modal_formula) = NULL;
 }
#line 7743 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 628:
#line 4125 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[3].value.sval)!=NULL && (yystack_[1].value._modal_formula)!=NULL) {
    pair<string *, string *> *two;// = new pair<string *, string *>($2, (*string_table)[0]);
    int i = search_string_table((yystack_[3].value.sval));
    if(i>=0) {
      two = new pair<string *, string *>((*string_table)[0], (*string_table)[i]);
      free((yystack_[3].value.sval));
    } else {
      two = new pair<string *, string *>((*string_table)[0], (yystack_[3].value.sval));
      string_table->push_back((yystack_[3].value.sval));
    }
    (yylhs.value.ID_ID_modal_formula) = new pair<pair<string *, string *>*, modal_formula *>(two, (yystack_[1].value._modal_formula));
  } else
    (yylhs.value.ID_ID_modal_formula) = NULL;
 }
#line 7763 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 629:
#line 4140 "parser/nssis_new.yy" // lalr1.cc:859
    {
	(yylhs.value.ID_ID_modal_formula) = NULL;
  driver.syntax_error = true;
	}
#line 7772 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 630:
#line 4144 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[9].value.sval)!=NULL && (yystack_[7].value.sval)!=NULL && (yystack_[5].value.sval)!=NULL && (yystack_[3].value._modal_formula)!=NULL & (yystack_[1].value._modal_formula)!=NULL) {
    pair<string *, string *> *two;
    pair<string *, pair<string *, string *>* > *three;// = new pair<string *, string *>($2, $4);
    int i = search_string_table((yystack_[9].value.sval));
    int j = search_string_table((yystack_[7].value.sval));
    int k = search_string_table((yystack_[5].value.sval));
    if(i>=0) {
      if(j>=0) {
	if(k>=0) {
	  two = new pair<string *, string *>((*string_table)[j], (*string_table)[k]);
	  free((yystack_[5].value.sval));
	} else {
	  two = new pair<string *, string *>((*string_table)[j], (yystack_[5].value.sval));
	  string_table->push_back((yystack_[5].value.sval));
	}
	three = new pair<string *, pair<string *, string *>* >((*string_table)[i], two);
	free((yystack_[7].value.sval));
      } else {
	if(k>=0) {
	  two = new pair<string *, string *>((yystack_[7].value.sval), (*string_table)[k]);
	  free((yystack_[5].value.sval));
	} else {
	  two = new pair<string *, string *>((yystack_[7].value.sval), (yystack_[5].value.sval));
	  string_table->push_back((yystack_[5].value.sval));
	}
	three = new pair<string *, pair<string *, string *>* >((*string_table)[i], two);
	string_table->push_back((yystack_[7].value.sval));
      }
      free((yystack_[9].value.sval));
    } else {
      if(j>=0) {
	if(k>=0) {
	  two = new pair<string *, string *>((*string_table)[j], (*string_table)[k]);
	  free((yystack_[5].value.sval));
	} else {
	  two = new pair<string *, string *>((*string_table)[j], (yystack_[5].value.sval));
	  string_table->push_back((yystack_[5].value.sval));
	}
	three = new pair<string *, pair<string *, string *>* >((yystack_[9].value.sval), two);
	free((yystack_[7].value.sval));
      } else {
	if(k>=0) {
	  two = new pair<string *, string *>((yystack_[7].value.sval), (*string_table)[k]);
	  free((yystack_[5].value.sval));
	} else {
	  two = new pair<string *, string *>((yystack_[7].value.sval), (yystack_[5].value.sval));
	  string_table->push_back((yystack_[5].value.sval));
	}
	three = new pair<string *, pair<string *, string *>* >((yystack_[9].value.sval), two);
	string_table->push_back((yystack_[7].value.sval));
      }
      string_table->push_back((yystack_[9].value.sval));
    }
    pair<modal_formula *, modal_formula *> *twoformulae = new pair<modal_formula *, modal_formula *>((yystack_[3].value._modal_formula), (yystack_[1].value._modal_formula));
    (yylhs.value.ID_ID_ID_modal_formula_modal_formula) = new pair<pair<string *, pair<string *, string *>*>*, pair<modal_formula *, modal_formula *> *>(three, twoformulae);
  } else
    (yylhs.value.ID_ID_ID_modal_formula_modal_formula) = NULL;
 }
#line 7836 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 631:
#line 4203 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[7].value.sval)!=NULL && (yystack_[5].value.sval)!=NULL && (yystack_[3].value._modal_formula)!=NULL && (yystack_[1].value._modal_formula)!=NULL) {
    pair<string *, string *> *two;// = new pair<string *, string *>($2, $4);
    int i = search_string_table((yystack_[7].value.sval));
    int j = search_string_table((yystack_[5].value.sval));
    if(i>=0) {
      if(j>=0) {
				two = new pair<string *, string *>((*string_table)[i], (*string_table)[j]);
				free((yystack_[5].value.sval));
      } else {
				two = new pair<string *, string *>((*string_table)[i], (yystack_[5].value.sval));
				string_table->push_back((yystack_[5].value.sval));
      }
      free((yystack_[7].value.sval));
    } else {
      if(j>=0) {
				two = new pair<string *, string *>((yystack_[7].value.sval), (*string_table)[j]);
				free((yystack_[5].value.sval));
      } else {
				two = new pair<string *, string *>((yystack_[7].value.sval), (yystack_[5].value.sval));
				string_table->push_back((yystack_[5].value.sval));
      }
      string_table->push_back((yystack_[7].value.sval));
    }
    pair<modal_formula *, modal_formula *> *twoformulae = new pair<modal_formula *, modal_formula *>((yystack_[3].value._modal_formula), (yystack_[1].value._modal_formula));
    (yylhs.value.ID_ID_modal_formula_modal_formula) = new pair<pair<string *, string *>*, pair<modal_formula *, modal_formula *> *>(two, twoformulae);
  } else
    (yylhs.value.ID_ID_modal_formula_modal_formula) = NULL;
 }
#line 7870 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 632:
#line 4232 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[7].value.sval)!=NULL && (yystack_[3].value._modal_formula)!=NULL && (yystack_[1].value._modal_formula)!=NULL) {
    pair<string *, string *> *two;// = new pair<string *, string *>($2, (*string_table)[0]);
    int i = search_string_table((yystack_[7].value.sval));
    if(i>=0) {
      two = new pair<string *, string *>((*string_table)[i], (*string_table)[0]);
      free((yystack_[7].value.sval));
    } else {
      two = new pair<string *, string *>((yystack_[7].value.sval), (*string_table)[0]);
      string_table->push_back((yystack_[7].value.sval));
    }
    pair<modal_formula *, modal_formula *> *twoformulae = new pair<modal_formula *, modal_formula *>((yystack_[3].value._modal_formula), (yystack_[1].value._modal_formula));
    (yylhs.value.ID_ID_modal_formula_modal_formula) = new pair<pair<string *, string *>*, pair<modal_formula *, modal_formula *> *>(two, twoformulae);
  } else
    (yylhs.value.ID_ID_modal_formula_modal_formula) = NULL;
 }
#line 7891 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 633:
#line 4248 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[5].value.sval)!=NULL && (yystack_[3].value._modal_formula)!=NULL && (yystack_[1].value._modal_formula)!=NULL) {
    pair<string *, string *> *two;// = new pair<string *, string *>($2, (*string_table)[0]);
    int i = search_string_table((yystack_[5].value.sval));
    if(i>=0) {
      two = new pair<string *, string *>((*string_table)[0], (*string_table)[i]);
      free((yystack_[5].value.sval));
    } else {
      two = new pair<string *, string *>((*string_table)[0], (yystack_[5].value.sval));
      string_table->push_back((yystack_[5].value.sval));
    }
    pair<modal_formula *, modal_formula *> *twoformulae = new pair<modal_formula *, modal_formula *>((yystack_[3].value._modal_formula), (yystack_[1].value._modal_formula));
    (yylhs.value.ID_ID_modal_formula_modal_formula) = new pair<pair<string *, string *>*, pair<modal_formula *, modal_formula *> *>(two, twoformulae);
  } else
    (yylhs.value.ID_ID_modal_formula_modal_formula) = NULL;
 }
#line 7912 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 634:
#line 4264 "parser/nssis_new.yy" // lalr1.cc:859
    {
	(yylhs.value.ID_ID_modal_formula_modal_formula) = NULL;
  driver.syntax_error = true;
	}
#line 7921 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 635:
#line 4269 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[10].value.sval)!=NULL && (yystack_[8].value.sval)!=NULL && (yystack_[6].value._modal_formula)!=NULL && (yystack_[4].value._modal_formula)!=NULL) {
    pair<string *, string *> *two;// = new pair<string *, string *>($2, $4);
    int i = search_string_table((yystack_[10].value.sval));
    int j = search_string_table((yystack_[8].value.sval));
    if(i>=0) {
      if(j>=0) {
				two = new pair<string *, string *>((*string_table)[i], (*string_table)[j]);
				free((yystack_[8].value.sval));
      } else {
				two = new pair<string *, string *>((*string_table)[i], (yystack_[8].value.sval));
				string_table->push_back((yystack_[8].value.sval));
      }
      free((yystack_[10].value.sval));
    } else {
      if(j>=0) {
				two = new pair<string *, string *>((yystack_[10].value.sval), (*string_table)[j]);
				free((yystack_[8].value.sval));
      } else {
				two = new pair<string *, string *>((yystack_[10].value.sval), (yystack_[8].value.sval));
				string_table->push_back((yystack_[8].value.sval));
      }
      string_table->push_back((yystack_[10].value.sval));
    }
    pair<modal_formula *, modal_formula *> *twoformulae = new pair<modal_formula *, modal_formula *>((yystack_[6].value._modal_formula), (yystack_[4].value._modal_formula));
    pair<int, int> *twointegers = new pair<int, int>((yystack_[2].value._unsigned_char), (yystack_[1].value.ival));
    pair<pair<string*, string*>*, pair<modal_formula*, modal_formula*>*> *ids_formulae = new pair<pair<string *, string *>*, pair<modal_formula *, modal_formula *> *>(two, twoformulae);
    (yylhs.value.ID_ID_modal_formula_modal_formula_equation) = new pair<pair<pair<string*, string*>*, pair<modal_formula*, modal_formula*>*>*, pair<int, int>* >(ids_formulae, twointegers);
  } else
    (yylhs.value.ID_ID_modal_formula_modal_formula_equation) = NULL;
 }
#line 7957 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 636:
#line 4300 "parser/nssis_new.yy" // lalr1.cc:859
    {
	(yylhs.value.ID_ID_modal_formula_modal_formula_equation) = NULL;
  driver.syntax_error = true;
	}
#line 7966 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 637:
#line 4305 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._modal_formula) = (yystack_[1].value._modal_formula); 
 }
#line 7974 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 638:
#line 4308 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7984 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 639:
#line 4313 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 7994 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 640:
#line 4318 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[1].value._modal_formula));
 }
#line 8004 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 641:
#line 4323 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._modal_formula)!=NULL && (yystack_[0].value._modal_formula)!=NULL)
    (yylhs.value._modal_formula) = new modal_formula(1, (yystack_[2].value._modal_formula), (yystack_[0].value._modal_formula));
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8015 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 642:
#line 4329 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._modal_formula)!=NULL && (yystack_[0].value._modal_formula)!=NULL)
    (yylhs.value._modal_formula) = new modal_formula(2, (yystack_[2].value._modal_formula), (yystack_[0].value._modal_formula));
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8026 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 643:
#line 4335 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value._modal_formula));USE((yystack_[0].value._modal_formula));
 }
#line 8036 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 644:
#line 4340 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._modal_formula)!=NULL)
    (yylhs.value._modal_formula) = new modal_formula(3, (yystack_[0].value._modal_formula));
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8047 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 645:
#line 4346 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._modal_formula));
 }
#line 8057 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 646:
#line 4351 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value._modal_formula)!=NULL && (yystack_[0].value._modal_formula)!=NULL)
    (yylhs.value._modal_formula) = new modal_formula(4, (yystack_[2].value._modal_formula), (yystack_[0].value._modal_formula));
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8068 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 647:
#line 4357 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._modal_formula)!=NULL)
    (yylhs.value._modal_formula) = new modal_formula(10, (yystack_[0].value._modal_formula));
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8079 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 648:
#line 4363 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._modal_formula)!=NULL)
    (yylhs.value._modal_formula) = new modal_formula(11, (yystack_[0].value._modal_formula));
  else
    (yylhs.value._modal_formula) = NULL;
  }
#line 8090 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 649:
#line 4369 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._modal_formula)!=NULL)
    (yylhs.value._modal_formula) = new modal_formula(12, (yystack_[0].value._modal_formula));
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8101 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 650:
#line 4375 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._modal_formula)!=NULL)
    (yylhs.value._modal_formula) = new modal_formula(13, (yystack_[0].value._modal_formula));
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8112 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 651:
#line 4381 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._modal_formula)!=NULL)
    (yylhs.value._modal_formula) = new modal_formula(14, (yystack_[0].value._modal_formula));
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8123 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 652:
#line 4387 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value._modal_formula)!=NULL)
    (yylhs.value._modal_formula) = new modal_formula(15, (yystack_[0].value._modal_formula));
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8134 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 653:
#line 4393 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.dual_modal_formula)!=NULL) {
    (yylhs.value._modal_formula) = new modal_formula(16, (yystack_[0].value.dual_modal_formula)->first, (yystack_[0].value.dual_modal_formula)->second);
    free((yystack_[0].value.dual_modal_formula));
  }
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8147 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 654:
#line 4401 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.dual_modal_formula)!=NULL) {
    (yylhs.value._modal_formula) = new modal_formula(17, (yystack_[0].value.dual_modal_formula)->first, (yystack_[0].value.dual_modal_formula)->second);
    free((yystack_[0].value.dual_modal_formula));
  }
  else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8160 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 655:
#line 4409 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[0].value.ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_modal_formula)->first);
    modal_formula *a = new modal_formula(ap);
    (yylhs.value._modal_formula) = new modal_formula(30, a, (yystack_[0].value.ID_modal_formula)->second);
    free((yystack_[0].value.ID_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8174 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 656:
#line 4418 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // Knowledge in a group (everybody knows)
  if((yystack_[0].value.ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_modal_formula)->first);
    modal_formula *a = new modal_formula(ap);
    (yylhs.value._modal_formula) = new modal_formula(31, a, (yystack_[0].value.ID_modal_formula)->second);
    free((yystack_[0].value.ID_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8189 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 657:
#line 4428 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // Common knowledge in a group
  if((yystack_[0].value.ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_modal_formula)->first);
    modal_formula *a = new modal_formula(ap);
    (yylhs.value._modal_formula) = new modal_formula(32, a, (yystack_[0].value.ID_modal_formula)->second);
    free((yystack_[0].value.ID_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8204 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 658:
#line 4438 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // deontic operator
  if((yystack_[0].value.ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_modal_formula)->first);
    modal_formula *a = new modal_formula(ap);
    (yylhs.value._modal_formula) = new modal_formula(40, a, (yystack_[0].value.ID_modal_formula)->second);
    free((yystack_[0].value.ID_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8219 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 659:
#line 4448 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // Distributed knowledge in a group
  if((yystack_[0].value.ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_modal_formula)->first);
    modal_formula *a = new modal_formula(ap);
    (yylhs.value._modal_formula) = new modal_formula(42, a, (yystack_[0].value.ID_modal_formula)->second);
    free((yystack_[0].value.ID_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8234 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 660:
#line 4458 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
 }
#line 8243 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 661:
#line 4462 "parser/nssis_new.yy" // lalr1.cc:859
    { 
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
 }
#line 8252 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 662:
#line 4466 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // ATL X operator
  if((yystack_[2].value.sval)!=NULL && (yystack_[0].value._modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[2].value.sval));
    modal_formula *a = new modal_formula(ap);
    (yylhs.value._modal_formula) = new modal_formula(45, a, (yystack_[0].value._modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8266 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 663:
#line 4475 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // ATL F operator
  if((yystack_[2].value.sval)!=NULL && (yystack_[0].value._modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[2].value.sval));
    modal_formula *a = new modal_formula(ap);
    (yylhs.value._modal_formula) = new modal_formula(46, a, (yystack_[0].value._modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8280 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 664:
#line 4484 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // ATL G operator
  if((yystack_[2].value.sval)!=NULL && (yystack_[0].value._modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[2].value.sval));
    modal_formula *a = new modal_formula(ap);
    (yylhs.value._modal_formula) = new modal_formula(47, a, (yystack_[0].value._modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8294 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 665:
#line 4493 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[0].value._modal_formula));
 }
#line 8304 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 666:
#line 4498 "parser/nssis_new.yy" // lalr1.cc:859
    {
  // ATL U operator
  if((yystack_[1].value.sval)!=NULL && (yystack_[0].value.dual_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[1].value.sval));
    modal_formula *a = new modal_formula(ap);
    (yylhs.value._modal_formula) = new modal_formula(48, a, (yystack_[0].value.dual_modal_formula)->first, (yystack_[0].value.dual_modal_formula)->second);
    free((yystack_[0].value.dual_modal_formula));
  } else {
    if((yystack_[0].value.dual_modal_formula) != NULL)
       free((yystack_[0].value.dual_modal_formula));
    if((yystack_[1].value.sval) != NULL)
      free((yystack_[1].value.sval));
    (yylhs.value._modal_formula) = NULL;
  }
 }
#line 8324 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 667:
#line 4513 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula)->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula)->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(51, a, b, (yystack_[0].value.ID_ID_modal_formula)->second);
    free((yystack_[0].value.ID_ID_modal_formula)->first);
    free((yystack_[0].value.ID_ID_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8341 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 668:
#line 4525 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula)->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula)->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(52, a, b, (yystack_[0].value.ID_ID_modal_formula)->second);
    free((yystack_[0].value.ID_ID_modal_formula)->first);
    free((yystack_[0].value.ID_ID_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8358 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 669:
#line 4549 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
 }
#line 8367 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 670:
#line 4553 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(61, a, b, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8384 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 671:
#line 4565 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(62, a, b, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8401 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 672:
#line 4577 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(63, a, b, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8418 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 673:
#line 4589 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(64, a, b, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8435 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 674:
#line 4601 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(65, a, b, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8452 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 675:
#line 4613 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(66, a, b, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8469 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 676:
#line 4625 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(71, a, b, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula)->second->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula)->first);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8486 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 677:
#line 4637 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
 }
#line 8495 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 678:
#line 4641 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_ID_modal_formula_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_ID_modal_formula_modal_formula)->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_ID_modal_formula_modal_formula)->first->second->first);
    atomic_proposition *ap2 = new atomic_proposition((yystack_[0].value.ID_ID_ID_modal_formula_modal_formula)->first->second->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    modal_formula *c = new modal_formula(ap2);
    (yylhs.value._modal_formula) = new modal_formula(67, a, b, c, (yystack_[0].value.ID_ID_ID_modal_formula_modal_formula)->second->first, (yystack_[0].value.ID_ID_ID_modal_formula_modal_formula)->second->second);
    free((yystack_[0].value.ID_ID_ID_modal_formula_modal_formula)->first->second);
    free((yystack_[0].value.ID_ID_ID_modal_formula_modal_formula)->first);
    free((yystack_[0].value.ID_ID_ID_modal_formula_modal_formula));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8515 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 679:
#line 4656 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
 }
#line 8524 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 680:
#line 4660 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->first->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->first->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(81, a, b, (yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->first->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->first->second->second, (yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->second->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->first->first);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8542 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 681:
#line 4673 "parser/nssis_new.yy" // lalr1.cc:859
    {
	if((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->first->first->first);
    atomic_proposition *ap1 = new atomic_proposition((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->first->first->second);
    modal_formula *a = new modal_formula(ap);
    modal_formula *b = new modal_formula(ap1);
    (yylhs.value._modal_formula) = new modal_formula(82, a, b, (yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->first->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->first->second->second, (yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->second->first, (yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->second->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->first->first);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation)->second);
    free((yystack_[0].value.ID_ID_modal_formula_modal_formula_equation));
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8560 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 682:
#line 4686 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
 }
#line 8569 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 683:
#line 4691 "parser/nssis_new.yy" // lalr1.cc:859
    {	
  if((yystack_[0].value.sval)!=NULL) {
    atomic_proposition *ap;
    int i = search_string_table((yystack_[0].value.sval));
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free((yystack_[0].value.sval));
    } else {
      ap = new atomic_proposition((yystack_[0].value.sval));
      string_table->push_back((yystack_[0].value.sval));
    }
    (yylhs.value._modal_formula) = new modal_formula(ap);
  } else
    (yylhs.value._modal_formula) = NULL;
  }
#line 8589 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 684:
#line 4706 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.sval)!=NULL) {
    string *newname = new string(*(yystack_[2].value.sval) + ".GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free((yystack_[2].value.sval));
    (yylhs.value._modal_formula) = new modal_formula(ap);
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8611 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 685:
#line 4723 "parser/nssis_new.yy" // lalr1.cc:859
    {
  if((yystack_[2].value.sval)!=NULL) {
    string *newname = new string(*(yystack_[2].value.sval) + ".RedStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free((yystack_[2].value.sval));
    (yylhs.value._modal_formula) = new modal_formula(ap);
  } else
    (yylhs.value._modal_formula) = NULL;
 }
#line 8633 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 686:
#line 4740 "parser/nssis_new.yy" // lalr1.cc:859
    {
    string *newname = new string("Environment.GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    (yylhs.value._modal_formula) = new modal_formula(ap);
 }
#line 8651 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 687:
#line 4753 "parser/nssis_new.yy" // lalr1.cc:859
    {
  string *newname = new string("Environment.RedStates");
  atomic_proposition *ap;
  int i = search_string_table(newname);
  if(i>=0) {
    ap = new atomic_proposition((*string_table)[i]);
    free(newname);
  } else {
    ap = new atomic_proposition(newname);
    string_table->push_back(newname);
  }
  (yylhs.value._modal_formula) = new modal_formula(ap);
 }
#line 8669 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 688:
#line 4766 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
 }
#line 8679 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 689:
#line 4771 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
 }
#line 8689 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 690:
#line 4776 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yystack_[2].value.sval));
 }
#line 8699 "parser/nssis.cc" // lalr1.cc:859
    break;

  case 691:
#line 4781 "parser/nssis_new.yy" // lalr1.cc:859
    {
  (yylhs.value._modal_formula) = NULL;
  driver.syntax_error = true;
  }
#line 8708 "parser/nssis.cc" // lalr1.cc:859
    break;


#line 8712 "parser/nssis.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
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
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
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

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  mcmas_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  mcmas_parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
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
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
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
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
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

    char const* yyformat = YY_NULLPTR;
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

    std::string yyres;
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


  const short int mcmas_parser::yypact_ninf_ = -946;

  const short int mcmas_parser::yytable_ninf_ = -692;

  const short int
  mcmas_parser::yypact_[] =
  {
     594,   170,   122,   107,   247,  1122,  -946,  1917,  1189,    87,
     332,  -946,  -946,  -946,  -946,  1033,  -946,   621,  -946,  3155,
     485,   357,   505,   973,   103,  1472,   298,  1169,   425,   624,
     132,   686,   366,  -946,    87,   368,  -946,  -946,   137,   102,
    1010,   451,   522,  -946,  1236,   323,   612,  1354,  -946,  -946,
    -946,  -946,  -946,  -946,   339,  1177,   975,  -946,   325,   550,
    3400,  1169,   624,   686,  1691,  1096,   340,  -946,  3233,   624,
     686,  5763,   678,  5975,  -946,  -946,   603,  5975,  1543,  -946,
    -946,  -946,  -946,  1406,   756,  7274,  6908,  -946,  4607,  7538,
    -946,  -946,  -946,  -946,  1739,   686,  1345,   592,  -946,  -946,
    1105,   435,   991,   564,   574,   102,  -946,  1304,   358,  1590,
    -946,   488,   662,  3235,   679,   222,  1193,   243,  1125,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,    65,
     117,   650,  -946,   619,  -946,  -946,   406,   624,   686,   686,
     574,  -946,  -946,  -946,  1675,  -946,  -946,   686,   574,  5979,
    -946,  -946,  2341,  7306,  1696,  -946,  -946,  -946,  1303,  4187,
    1845,  -946,  2421,  6011,  1308,  -946,   708,  -946,  5378,  5975,
    5975,  -946,  1552,  1552,  1552,  1552,  1552,  1552,  1308,  -946,
    -946,  -946,  -946,  -946,  -946,  1308,  1308,  1308,  1308,  1308,
     574,  -946,  -946,  -946,   355,   697,  -946,  -946,  -946,  -946,
    3952,   834,  1042,  -946,  5369,  -946,  1626,  1829,   763,  1054,
     124,  1705,   662,  6803,  6803,   842,   265,  1324,  -946,  1758,
     488,   497,   488,   501,  1242,  3246,  -946,  -946,  -946,   471,
      73,   860,   258,  3376,  -946,  -946,  1379,  -946,   891,  1551,
     874,   340,  3058,  3214,   978,   227,  1277,  1457,   629,  -946,
    -946,  1209,  1276,  1193,    61,  -946,  -946,  1387,   674,    61,
     285,  -946,   766,  -946,  -946,   686,   574,   574,  1705,   574,
    1705,  6595,  -946,  -946,  -946,  6627,  -946,  6277,  -946,  6541,
    -946,  5975,  6011,   664,   728,  2501,  2581,  2661,  6309,  1552,
    6940,  6974,  7006,  -946,  -946,  -946,  7570,  7604,  7636,  2181,
    -946,  -946,  1705,  -946,  -946,  6079,  -946,  1655,   289,  -946,
    -946,   922,   289,  5470,  -946,  -946,  1626,  1055,  -946,   836,
     289,  -946,  -946,  -946,   627,  1146,    69,  1065,  -946,   371,
    -946,  1512,  1274,  1358,  -946,    73,   258,  -946,  5838,  6803,
     858,  6803,   428,  7172,  -946,  4667,  7868,  -946,  -946,  7670,
    7340,  -946,  -946,  -946,  1284,  1321,  -946,  -946,  -946,  6803,
    6803,  1160,  1030,   971,  1547,  1232,  1297,  3301,  1343,  1372,
    6861,   488,   488,  1816,  -946,   385,   294,   789,  -946,   481,
    1410,   258,  -946,  3861,   360,  5242,  1368,  5242,  5242,  5242,
    5242,  5242,  5242,  5242,  1312,  1312,  1400,  1432,  1432,  1400,
    4926,  1432,  -946,  5104,  1915,  -946,  -946,  3041,  3456,  1375,
    1424,  3456,  3456,  3456,  3456,  3456,  3456,  3456,  1561,  1561,
    1598,  1688,  1688,  1598,  1762,  1762,  1820,  1820,  1820,  1820,
    1820,  1820,  1541,  1820,  1821,  1821,  4806,  1688,  3126,   586,
    3121,  -946,  -946,  -946,  -946,  -946,  -946,  5402,  6827,   863,
    6827,   482,  -946,  -946,  -946,  1406,  1323,  4727,  7702,  -946,
    -946,  7372,  7040,  -946,  -946,  -946,  1787,  1277,  -946,  1105,
     684,  5632,  1356,  -946,  -946,  -946,   489,  1474,  -946,   978,
    1277,  -946,  1487,  -946,  1492,    81,    81,  -946,  1389,    81,
      81,   574,  1705,  1705,  -946,  1705,  -946,  1396,  1749,  -946,
    -946,  -946,  -946,  -946,  -946,  1395,  1395,  -946,  1395,  -946,
    -946,  -946,  -946,  1667,  1308,   822,  -946,  -946,  6825,    69,
    -946,  -946,  -946,   258,  -946,  -946,  1558,  4367,  -946,  7736,
    3481,  4427,  4247,  2005,  1588,  1592,  3541,  6111,   562,  -946,
    1596,  1600,   562,   562,   562,   562,   562,   562,   714,   714,
     714,   714,   714,   714,  5805,  6803,  6803,  -946,  5880,  -946,
    1565,  1566,  1703,   741,   904,  2023,  -946,  2103,  -946,  1199,
    1233,   488,  1235,  1556,   546,  -946,  3561,  3621,  3641,  1690,
     559,  -946,  -946,  -946,  1727,  1735,   125,  1708,   789,  -946,
    -946,  3885,  5260,  -946,  -946,  -946,  5437,  -946,  -946,  3946,
     832,  1445,  5836,  6113,  8198,  8201,  8223,  8235,  8246,  5242,
    5242,  -946,  -946,    64,    72,  -946,  1672,  1742,  -946,  -946,
    -946,  1568,   737,  -946,  4006,  -946,  4034,  5164,  5242,  5242,
    -946,  5242,  1214,  3536,  5689,  -946,  -946,  -946,  -946,  -946,
    -946,  4986,  1294,  1171,   324,  1599,  5046,  8005,  8006,  8017,
    8040,  8062,  8074,  3456,  3456,  -946,  -946,   225,   226,  -946,
    1759,  1807,  -946,  -946,  -946,  -946,   270,  -946,  -946,  -946,
     318,  -946,  -946,  -946,  -946,  -946,  -946,  1837,  -946,  -946,
    -946,  1849,  -946,  -946,  1761,   901,  -946,  1082,   290,  -946,
    4569,  3456,  3456,  3456,  3456,  -946,  3211,  3456,  3456,  -946,
    3456,  5502,  1865,  2741,  4487,  -946,  7406,  2085,  4547,  4307,
    1876,  1899,  2821,  1633,   980,  -946,  -946,  6351,  6827,  6827,
    -946,   980,   980,   980,   980,   980,   980,  1306,  1306,  1306,
    1306,  1306,  1306,  1356,  -946,  5577,  4067,  -946,  1626,  1944,
     844,   101,  1824,  -946,  -946,  1277,  1356,  -946,  -946,  1712,
    -946,  -946,  1487,  -946,  -946,  -946,  1705,  -946,  -946,  -946,
     554,   659,  1901,  -946,  -946,  -946,  -946,   982,  6179,  6825,
    1604,  6825,  1823,  4607,  1567,  -946,  -946,  -946,  -946,  -946,
    6662,  -946,  6573,  -946,  6441,  -946,  6689,  -946,  -946,  -946,
    6803,  6111,   794,   985,  -946,  -946,  7900,  7934,  7966,  1167,
    -946,  -946,  6375,   714,  7438,  7472,  7504,  -946,  -946,  -946,
    3701,  3721,  3781,  6406,  -946,  6701,  -946,   904,  3300,  -946,
    -946,  -946,  -946,  -946,   904,   904,   904,   770,   904,   904,
     904,  1100,  -946,  -946,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  1518,  -946,   125,   841,  4866,   883,  3480,
    4061,  -946,  4121,  -946,  -946,  -946,  5242,  1383,  3135,   113,
     447,   636,   671,   703,   800,  -946,  -946,  -946,  -946,  -946,
    5187,  -946,  8252,  8258,  8295,  8297,   929,  7988,  1162,  3560,
    -946,  1458,  -946,  1538,  -946,  -946,  -946,  -946,  -946,  3456,
    3366,  3446,   899,   945,   992,   994,  1022,  1027,  1772,  1866,
    1874,  1967,  1969,  1971,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  3296,  -946,  8075,  8092,  8104,  8124,  8136,  8149,
    8153,  8166,  -946,   661,  -946,  -946,  -946,  1190,  -946,  6473,
    -946,  6211,  -946,  -946,  -946,  6827,  1633,  1083,  1215,  2901,
    2981,  3068,  7768,  7802,  7834,  2261,  -946,  -946,  5913,  1306,
    7072,  7106,  7138,  -946,  -946,  -946,  1824,  5656,  5327,  -946,
    -946,  1626,  -946,  6775,   289,    92,   359,  2008,  1239,   427,
    -946,  2017,  1713,  -946,  1356,  1824,  -946,  -946,  -946,  -946,
    -946,  -946,  1942,  7206,  1696,  3801,  1845,  2165,  1956,  1972,
    3863,   442,  1060,  1308,  6825,  6825,  6825,  -946,  1950,  2001,
    -946,  -946,  -946,  -946,  1994,  2018,  -946,  -946,  -946,  -946,
    2041,  2049,  -946,   581,   685,   394,  -946,  1518,  5242,  5242,
     967,  5242,  5242,  5242,   967,  5242,  5242,  5242,  5242,  5242,
    5242,  5242,  5242,  5242,  5242,  5242,  5242,  5242,  3456,  3456,
     701,  3456,  3456,  3616,   701,  3696,  3456,  3456,  3456,  3456,
    3456,  3456,  3456,  3456,  3456,  3456,  3456,  3456,  3456,  1977,
     352,  1979,   399,  2006,  2010,  2241,  2321,  -946,  -946,  1395,
    -946,  1921,   980,  6800,  6800,   359,   921,  -946,  -946,  -946,
    -946,  -946,  1824,  -946,  -946,  6724,  -946,  6751,  -946,  -946,
    -946,  2011,  1625,  -946,    28,  1629,  2021,  3888,  4091,  4123,
    2012,  2013,  2014,  2015,  -946,  -946,  -946,  -946,  -946,  -946,
    -946,  3475,  3555,  3635,  3715,  3795,  4148,  4808,  4868,   658,
    4928,  1137,  4988,  5048,  5183,  5269,  5322,  5563,  5691,  5824,
    6074,  6687,  6734,  6768,  6850,  6882,  3640,  7207,  7683,  1799,
    3720,  7749,  8178,  7881,  1425,  7947,  8091,  8308,  8309,  8311,
    8320,  8322,  8334,  8359,  2063,  2065,  2066,  2067,  2069,  2075,
    2081,  2097,  -946,  -946,  1403,  5731,  6800,   895,  1638,  6800,
    1914,  4727,  1650,  1651,  -946,  -946,  -946,  2054,  2057,  2059,
    -946,  2061,  2062,  -946,  -946,  -946,  -946,  4181,  -946,  4241,
    -946,  4301,  -946,  4361,  -946,  4421,  -946,  4481,  -946,  4541,
    -946,  4601,  -946,  4661,  -946,  4721,  -946,  4781,  -946,  4841,
    -946,  4301,  -946,  4361,  -946,  4541,  -946,  4601,  -946,  4901,
    -946,  4961,  -946,  5021,  -946,  5081,  -946,  1731,  -946,  1825,
    -946,  1916,  -946,  1996,  -946,  2076,  -946,  3456,  2156,  -946,
    2236,  -946,  3456,  3776,  2316,  -946,  2396,  -946,  2476,  -946,
    2556,  -946,  2636,  -946,  1916,  -946,  1996,  -946,  2236,  -946,
    2316,  -946,  2716,  -946,  2796,  -946,  2876,  -946,  2956,  -946,
    3456,  3456,  3456,  3456,  3456,  3456,  2077,  3456,  2086,  7240,
    4487,  4245,  4547,  2245,   470,   519,  2090,  2091,  4305,   547,
    1078,   980,  1734,  6800,  6800,  -946,  3044,  -946,  -946,  -946,
    -946,  -946,  -946,  4146,  5873,  3800,  5935,  8361,  8363,  8364,
    5419,  5673,  5916,  2130,  5930,  -946,  1394,  -946,  5544,  -946,
    2092,  2177,  4365,    79,  1663,  -946,  -946,  6800,  2094,  1737,
    -946,   161,  1745,  2101,  4425,  4485,  4545,  -946,  3456,  -946,
    3456,  3456,  -946,  3456,  3456,  3456,  -946,  2095,  2098,  -946,
    2099,  2100,  -946,  2102,  2104,  2106,  -946,  2107,  2110,  8375,
    8377,  6114,  6233,  8381,  6214,  -946,  -946,  -946,  -946,  -946,
    -946,  -946,  -946,  -946,  -946,  -946,  3456,  -946,  2394,  8386,
    2113,  -946,  2191,  -946
  };

  const unsigned short int
  mcmas_parser::yydefact_[] =
  {
       0,    18,     0,     0,     0,     0,     2,     0,     0,     0,
       0,   123,    16,    17,    15,     0,     1,    18,     3,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   125,   126,     0,   136,   409,   124,     0,     0,
       0,     0,     0,   160,     0,    82,   161,     0,    34,    32,
      69,    67,    81,    80,    39,     0,     0,    41,     0,     0,
      83,     0,     0,     0,    46,     0,     0,    76,    83,     0,
       0,     0,     0,     0,   390,   391,     0,     0,     0,   388,
      63,   389,    89,     0,     0,     0,     0,   257,     0,     0,
     268,   271,   261,   387,   163,     0,   167,     0,   173,   169,
       0,   180,     0,     0,     0,     0,   424,     0,     0,   437,
     436,     0,     0,    70,     0,     0,     0,     0,     0,     4,
       5,   162,   157,   158,   159,   156,    37,    38,    36,     0,
       0,    39,    40,     0,    43,    42,    82,     0,     0,     0,
       0,    72,    73,    71,    58,    75,    82,     0,     0,     0,
      85,    63,     0,     0,     0,   270,    86,    84,     0,     0,
       0,    64,     0,     0,     0,   269,    87,    88,     0,     0,
       0,    94,     0,     0,     0,     0,     0,     0,     0,   351,
     353,   355,   352,   354,   356,     0,     0,     0,     0,     0,
       0,   166,   165,   164,   167,     0,   168,   178,   179,   177,
       0,     0,     0,   188,     0,   194,     0,     0,   103,     0,
       0,     0,     0,     0,     0,   413,     0,     0,   414,     0,
       0,     0,     0,     0,     0,   501,   500,   473,   579,     0,
       0,     0,     0,     0,    14,   141,     0,    68,   142,     0,
      46,     0,    83,     0,     0,     0,     0,   148,     0,   152,
     150,     0,    70,     0,    62,    49,    59,     0,     0,    48,
       0,    47,     0,    45,    44,     0,     0,     0,     0,     0,
       0,     0,   229,   259,   273,     0,   228,     0,   258,     0,
     272,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   256,   254,   255,     0,     0,     0,     0,
     267,   266,     0,   175,   174,     0,   182,     0,     0,   183,
     181,   203,     0,     0,   185,   195,     0,   184,   187,     0,
       0,   101,   102,   100,   107,     0,     0,     0,   109,     0,
     110,     0,    22,     0,    30,     0,     0,    10,     0,     0,
       0,     0,     0,     0,   405,     0,     0,   296,   299,     0,
       0,   323,   398,   327,     0,     0,   411,   412,   410,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   446,   478,     0,     0,   480,     0,
     501,     0,    12,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   506,     0,     0,   580,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   143,   138,   139,   140,   137,    78,     0,     0,     0,
       0,     0,   393,   397,    92,     0,     0,     0,     0,   282,
     285,     0,     0,   311,   392,   315,   163,     0,   176,     0,
     180,     0,     0,   147,   146,   145,   148,     0,   149,     0,
       0,    65,    57,    55,     0,     0,     0,    62,     0,     0,
       0,     0,     0,     0,    28,     0,    26,     0,     0,    29,
     201,   202,   200,   217,   214,     0,     0,   186,     0,   105,
     106,   104,   118,     0,     0,   107,   108,   111,     0,     0,
      20,    21,    19,     0,     8,     9,     0,     0,   298,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   297,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   417,     0,   416,
       0,     0,     0,     0,     0,     0,   449,     0,   448,     0,
       0,     0,     0,     0,     0,   442,     0,     0,     0,   443,
       0,   476,   477,   475,   485,     0,     0,   478,     0,   479,
      11,     0,     0,   503,   568,   569,     0,   504,   502,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   561,   562,     0,     0,   563,     0,     0,   564,   565,
     566,     0,     0,   567,     0,   507,     0,     0,     0,     0,
     508,     0,     0,     0,     0,   660,   661,   669,   679,   677,
     682,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   653,   654,     0,     0,   655,
       0,     0,   656,   657,   658,   629,     0,   667,   668,   634,
       0,   671,   670,   672,   673,   674,   675,     0,   678,   676,
     636,     0,   680,   681,     0,     0,   659,     0,     0,   585,
       0,     0,     0,     0,     0,   666,     0,     0,     0,   586,
       0,     0,     0,     0,     0,   284,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   283,    91,     0,     0,     0,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   171,     0,     0,   197,     0,     0,
     103,     0,     0,   154,   153,     0,     0,    61,    60,    66,
      53,    51,    56,    54,    52,    50,     0,    24,    27,    25,
     207,     0,     0,   213,   212,   208,   115,     0,     0,     0,
       0,     0,     0,     0,     0,   116,     7,   403,   301,   325,
       0,   426,     0,   300,     0,   324,     0,   425,   404,   402,
       0,     0,     0,     0,   401,   400,     0,     0,     0,     0,
     295,   294,     0,     0,     0,     0,     0,   322,   320,   321,
       0,     0,     0,     0,   421,     0,   420,     0,     0,   408,
     406,   471,   407,   469,     0,     0,     0,     0,     0,     0,
       0,     0,   444,   439,   440,   441,   438,   483,   484,   482,
     496,   497,   498,     0,   493,     0,     0,     0,     0,     0,
       0,   546,     0,   545,   574,   573,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   577,   576,   575,   572,   571,
       0,   510,     0,     0,     0,     0,     0,     0,     0,     0,
     593,     0,   638,     0,   637,   592,   591,   687,   686,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   690,   689,   688,   685,   684,   582,
     583,   581,     0,   588,     0,     0,     0,     0,     0,     0,
       0,     0,   395,     0,   240,   287,   313,     0,   239,     0,
     286,     0,   312,   396,   394,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   281,   280,     0,     0,
       0,     0,     0,   310,   308,   309,     0,     0,     0,   190,
     198,     0,   192,     0,     0,   122,     0,     0,     0,     0,
     220,   131,     0,   133,     0,     0,    23,   205,   216,   206,
     204,   215,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,     0,     0,
     470,   468,   466,   467,     0,   407,   465,   463,   461,   462,
       0,   407,   460,     0,     0,     0,   490,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   132,   191,     0,
     122,     0,     0,     0,     0,     0,   107,   218,   221,   129,
     130,   128,     0,   135,   339,     0,   329,     0,   328,   340,
     338,     0,     0,   349,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   499,   487,   495,   488,   486,   494,
     491,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   210,   119,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   120,   134,   346,     0,     0,     0,
     347,     0,     0,   464,   459,   458,   457,     0,   533,     0,
     530,     0,   525,     0,   522,     0,   531,     0,   529,     0,
     523,     0,   521,     0,   517,     0,   514,     0,   515,     0,
     513,     0,   525,     0,   522,     0,   523,     0,   521,     0,
     541,     0,   538,     0,   539,     0,   537,     0,   614,     0,
     611,     0,   606,     0,   603,     0,   612,     0,     0,   610,
       0,   604,     0,     0,     0,   602,     0,   598,     0,   595,
       0,   596,     0,   594,     0,   606,     0,   603,     0,   604,
       0,   602,     0,   622,     0,   619,     0,   620,     0,   618,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   224,     0,   223,   348,   343,
     344,   345,   342,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   368,     0,   358,     0,   357,
       0,     0,   396,     0,     0,   369,   367,     0,     0,     0,
     378,     0,     0,     0,     0,     0,     0,   628,     0,   627,
       0,     0,   626,     0,     0,     0,   382,     0,     0,   383,
       0,     0,   375,     0,     0,     0,   376,     0,     0,     0,
       0,     0,     0,     0,     0,   384,   380,   381,   379,   377,
     372,   373,   374,   371,   633,   632,     0,   631,     0,     0,
       0,   630,     0,   635
  };

  const short int
  mcmas_parser::yypgoto_[] =
  {
    -946,  -946,  -946,  2196,  -946,  -224,  -946,  -946,  2128,  -946,
       5,    29,  1957,    63,    77,   -30,  2194,  2108,   -83,   -49,
     825,  1968,  -946,  -946,  -444,  -324,  -111,  -946,  1893,  -294,
    -910,  2216,  -946,  -892,  1187,  -946,  1974,  -946,  -946,   -81,
     -96,   302,  -173,  1982,  -222,  -195,   280,  -429,  -946,  -946,
    -182,  -493,  2047,  1519,  -190,  -310,  -691,  -946,  1287,   365,
    -242,    -4,  -115,  1326,   -52,   -80,  1830,   -48,  -421,  -673,
    1130,  -439,  -263,  -503,  1373,  -320,  -441,  -667,  1216,  -322,
    -496,  1464,  -471,  -342,  -945,  -946,   900,  -946,  -946,  -440,
    -946,  -946,  2223,  -946,  -141,  -946,  -946,  2153,   -18,  -946,
    1880,  2048,  1676,  1246,  -946,  1420,   846,  -946,  1863,  -144,
    -946,  1872,   848,  1489,   -70,  -946,  -946,  -167,  -946,  -946,
    -323,   963,   681,  1601,  1839,  1094,  1632,  -233
  };

  const short int
  mcmas_parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,   334,     8,    24,    57,    25,
      58,    59,   257,   453,    26,    67,    27,   116,    28,    82,
      29,   244,    83,   455,   210,   328,   211,   329,   330,   331,
     968,     9,    10,   973,    11,   117,   250,   118,   251,    30,
      99,    31,   246,   100,   103,   203,   104,   472,   204,   736,
     308,   763,   205,   737,   206,   505,   742,   969,   970,   152,
     703,    85,    86,    87,    88,    89,    90,    91,   457,   458,
     459,   460,   345,   346,   347,   348,   461,   462,   463,   349,
     350,   351,  1097,   187,  1334,    92,   464,   465,   353,   821,
      38,   218,    39,   108,   810,   111,   374,   112,   576,   229,
     378,   230,   586,  1016,   379,   843,   844,   231,   402,   232,
     403,   611,   594,   595,   872,   233,   689,   234,   438,   439,
     655,   635,   636,   637,   638,   639,   640,   918
  };

  const short int
  mcmas_parser::yytable_[] =
  {
     440,   456,   506,   545,   196,   516,   706,   709,   705,   314,
     508,   318,   715,   764,   316,   765,   529,   532,   528,   154,
     312,   160,   539,   155,   471,   320,   704,   708,   741,   268,
     165,    66,   513,   243,   167,   245,   145,   270,   733,   796,
     797,   798,   956,  1179,   494,   337,   496,   774,   942,   943,
     944,   746,   804,   805,   806,   975,  1071,   290,   291,   292,
     950,   951,   952,   382,  1067,   406,   254,   153,   336,   159,
     512,   467,   354,   355,   380,   527,   531,   326,   499,   302,
     480,   859,   749,  1083,   -66,   255,   381,   133,    35,   861,
      33,    81,    76,   224,  1348,   133,   656,   154,   296,  -222,
    -222,   155,   965,   109,    54,   297,   298,   226,    76,   966,
      55,   283,   284,  1180,  1018,   724,   695,   115,   259,   228,
     241,   507,    15,    13,   823,   324,   840,   260,  1172,  1173,
      36,   325,   326,    96,    81,   299,    81,   261,   106,    14,
      81,    81,   841,    97,    76,   153,   110,   481,   154,   860,
     256,    80,   155,  1019,   327,   492,   493,   862,   495,   153,
     159,   404,   290,   245,  1349,  1174,    81,    80,   524,   525,
     243,    -6,   245,    -6,   641,   643,  1355,  -222,   646,   647,
     648,   649,   650,   651,   652,   545,   967,    12,    56,   545,
    1175,   523,   258,   262,   454,   115,   153,   530,   533,   296,
     536,   363,   364,    80,   367,   690,   707,  -126,   712,   327,
     842,   446,    81,  -125,   590,   529,   532,    98,   560,   561,
    1281,  1283,   107,   240,  1288,   775,    81,    81,   468,   739,
     283,    81,    81,    81,   155,    81,    81,    81,    81,    81,
      81,    81,   892,   894,   247,   471,  1356,    16,    81,    81,
      81,    81,    81,   154,   248,  -127,   942,   155,   471,   405,
     706,   154,   705,    81,   950,   155,   357,    81,   757,   758,
     133,   759,   706,   709,   792,   793,   344,   344,   153,   796,
     704,   738,   799,  1082,   497,   498,   487,   898,   804,   741,
     503,   910,   937,   938,   706,   582,   705,   985,   987,    64,
     990,   153,   741,   945,   228,    65,   745,    56,   358,   153,
     893,   895,    98,   596,   704,   600,   974,   602,   603,   604,
     605,   606,   607,   608,   -33,   885,   131,    63,   249,    70,
     -33,    95,    55,   626,    81,   900,   911,   886,    81,   583,
      81,   144,    81,   140,    81,    81,   -46,    65,  1335,  1336,
     148,    81,    81,   577,   578,   899,   776,   126,    48,   215,
    1070,   597,   724,   138,   139,   216,   724,   966,    81,  1155,
     256,   147,   515,   734,   504,   190,    81,  1000,   325,   326,
     756,   -58,    81,    56,  1001,  1002,  1003,  1006,  1007,  1008,
    1009,  1012,  -492,    84,   598,  1104,    49,   191,   245,   641,
     643,   344,   344,   901,   344,   344,   716,   -68,   -33,   641,
      56,   841,  -415,   -68,   811,   812,  1158,    40,   266,   267,
     890,   891,   344,   344,   -46,    56,    71,   269,  1076,   537,
     581,   993,    72,    73,   325,   966,   538,  1156,   158,   265,
     303,  -189,   162,   217,   967,   340,    74,    75,  1030,    74,
      75,  -127,    76,  -127,   641,    76,   327,  1091,   914,   915,
     916,   917,   767,    77,   919,   920,   773,   921,   207,   529,
    -492,   528,   375,  1092,   197,   939,   940,   941,   376,   842,
     998,   999,   587,   713,  1159,  1320,    46,  1031,   376,   219,
     714,   -68,    78,   119,   739,   706,   220,   705,   365,   449,
      47,  1321,   368,    74,    75,   221,    50,  1065,  1066,    76,
      79,    80,   967,   343,    80,   937,   706,   706,   705,   705,
    1323,   596,   600,   471,  1098,  1099,   222,  1093,   792,   596,
     741,   473,   976,   285,   286,   287,   704,   704,   366,   857,
     858,   959,   369,   962,    51,   491,   961,   832,   750,   751,
    1324,   134,   754,   755,   596,  1322,   377,   964,   873,   874,
     835,   875,  1328,   791,   120,   200,   588,   452,    80,   207,
     538,   201,    73,   223,   743,   208,  1162,    81,  1329,   340,
     209,    81,  1104,    74,    75,    74,    75,   691,  -489,    76,
     833,    76,   135,   192,   654,     1,   977,     2,   841,   202,
     344,   344,    77,   836,   934,   344,   344,   344,   344,   344,
     344,   344,   344,   344,   344,   344,   344,   344,   344,   344,
     263,   344,   123,  1105,   -31,    94,   819,   819,    20,   342,
     474,    78,  1330,   509,   193,  -112,   285,  1022,    12,   978,
     285,  -118,   993,  -118,   993,  1077,   285,   343,    80,    79,
      80,  1164,  1171,  1171,  1069,   692,   693,   694,     3,  1203,
     979,   264,   701,   225,  -125,   178,   842,  1204,   126,   448,
    -242,   475,  1032,   274,   628,   485,  1023,  -242,   449,   156,
     238,   939,    74,    75,   285,   939,  1107,   101,    76,   161,
    -193,   102,   -58,   939,   239,   629,   226,   486,  -242,   450,
    -242,   980,   642,  -242,  1034,   631,  -127,   227,   228,   408,
     157,  1033,  -112,   409,  -551,   802,   984,   986,   410,   773,
     155,   939,   803,   197,   706,   709,   705,  1108,   451,   279,
     185,   340,   186,   904,   905,    74,    75,   280,   867,   411,
     150,    76,   749,  1035,  1280,  1282,   452,    80,  1171,   412,
     413,   414,   415,   416,   417,   418,   419,   168,   420,   421,
     422,   423,    74,    75,   153,   159,  1068,   489,    76,   868,
     869,   749,   169,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   304,   433,   434,   435,   436,  1004,   437,   490,
     584,    74,    75,   170,   185,   542,   186,    76,   171,   343,
      80,  1036,   321,   778,   585,  1131,  1132,  1133,  1134,  1135,
    1137,  1138,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1137,
    1148,  1149,  1150,  1151,  1152,  1153,   818,    80,   509,  1291,
    -114,    81,    81,   852,    81,   309,  -118,   149,  -118,   310,
    1037,   853,  1018,   344,    73,   344,   500,   344,   628,   344,
      62,  -219,    69,   344,   344,  1005,    80,    74,    75,   534,
     543,   383,   544,    76,   710,   344,   344,   384,   385,   629,
    1333,  1171,  1171,  1171,    77,  1171,   344,   386,   344,   631,
     819,  1019,   601,   321,  1022,   356,   137,   819,   819,   819,
     819,   819,   819,   819,   819,  1171,  1284,  1171,   387,   535,
    1038,   443,   906,    78,   711,   749,  1171,  -114,   388,   389,
     390,   391,   392,   393,   394,   395,   -58,   396,   397,   398,
     399,    79,    80,  1023,   601,    74,    75,   509,    93,  -227,
    1038,    76,   500,   907,   908,  -122,  1285,  -122,  1291,  1039,
    1291,  1096,   773,   773,   773,   400,  1050,   401,  1111,  1112,
    1113,  1114,  1115,  1116,  1117,  1118,  1119,  1120,  1121,  1122,
    1123,  1124,  1125,  1126,  1127,  1128,  1129,  1130,   599,  1039,
     645,    93,   565,    93,    52,   385,   129,    93,    93,   466,
     566,   936,    20,   178,   386,  1051,   782,   371,   714,   822,
      80,  -117,   198,  1042,   783,  1053,  -117,   449,  -117,   865,
     866,    74,    75,    93,  1303,   387,  -227,    76,   372,  1304,
    1306,   113,    53,  -456,   130,   388,   389,   390,   391,   392,
     393,   394,   395,  1055,   396,   397,   398,   399,  1057,    22,
     199,   563,  1052,   773,  1054,   773,  1380,  1307,  1308,  1309,
    1310,  1311,  1312,   311,  1314,   564,   114,   451,   185,    93,
     186,   543,   400,   544,   401,   322,    81,    81,    81,    81,
     306,  1094,  1056,    93,    93,   452,    80,  1058,    93,    93,
      93,   369,    93,    93,    93,    93,    93,    93,    93,  1331,
     514,   307,  -584,   632,   721,    93,    93,    93,    93,    93,
     633,  1095,   925,   323,   409,    41,    42,   142,  -691,   410,
      93,   749,   662,   663,    93,  1359,   194,  1360,  1361,  1332,
    1362,  1363,  1364,   352,   352,   143,    97,  1010,   686,  -691,
     411,    74,    75,    17,  -691,     2,   252,    76,   909,  -691,
     412,   413,   414,   415,   416,   417,   418,   419,  1207,   420,
     421,   422,   423,  1379,    22,   195,  1208,   510,    81,   722,
      81,   723,   511,   628,   424,   425,   426,   427,   428,   429,
     430,   431,   432,  1042,   433,   434,   435,   634,   542,   437,
      68,    93,   883,    20,   629,    93,  -434,    93,   127,    93,
     884,    93,    93,  -434,   631,  1011,    80,   697,    93,    93,
      32,   701,    33,  -551,   242,   128,    37,    20,   448,  -241,
     824,    23,  1043,   645,  -434,    93,  -241,   449,   698,  -434,
     476,    74,    75,    93,   825,   632,   929,    76,   700,    93,
     248,    37,   633,  -629,   930,    23,   409,  -241,   450,  -241,
    -629,   876,  -241,   543,   826,   544,   828,   121,   352,   352,
    1073,   352,   352,   370,   615,   562,   122,   620,   827,   477,
     829,  -629,   411,  1074,  -629,  1075,  -629,   451,   371,   352,
     352,  -629,   412,   413,   414,   415,   416,   417,   418,   419,
    -629,   420,   421,   422,   423,   452,    80,   520,   470,   372,
     -79,   722,   102,   723,   373,   554,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   632,   433,   434,   435,   877,
     555,   437,   633,  -691,   275,   213,   409,   948,   -79,   282,
    -691,   410,   276,   609,   949,   237,   164,   569,   214,   169,
     610,   556,   558,   449,   717,   359,   557,    74,    75,    74,
      75,  -691,   411,    76,  -691,    76,  -691,   555,   360,   718,
     170,  -691,   412,   413,   414,   415,   416,   417,   418,   419,
    -691,   420,   421,   422,   423,   124,  -176,   740,   556,   521,
     719,   522,   209,   559,   125,   720,   424,   425,   426,   427,
     428,   429,   430,   431,   432,    78,   433,   434,   435,   634,
     441,   437,   570,   659,  1026,  -176,   664,   191,   482,   442,
     752,   452,    80,    79,    80,  1165,   760,   172,   483,   628,
     753,   613,  1166,  -360,   721,   273,   761,   166,   614,   601,
    -360,  1167,  -121,    72,    93,    74,    75,  -121,    93,  -121,
     629,    76,  -580,   173,   174,  1168,  1250,   484,   572,   484,
     631,  -360,  1169,   616,  1251,   762,  -360,   352,   352,  1027,
     617,   697,   352,   352,   352,   352,   352,   352,   352,   352,
     352,   352,   352,   352,   352,   352,   352,   573,   352,   642,
     644,   451,   698,   820,   820,   645,   408,  -640,  -155,   722,
     409,   723,   700,    60,  -640,   410,    20,   854,   855,  1170,
      80,  -643,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,
    -580,    22,  -580,  -580,  -580,  -640,   411,  -155,  -640,   473,
    -640,   293,   294,   295,    23,  -640,   412,   413,   414,   415,
     416,   417,   418,   419,  -640,   420,   421,   422,   423,  1013,
     671,   672,   673,   674,   675,   676,   518,   679,   519,  1014,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   642,
     433,   434,   435,   436,   163,   437,   408,  -639,   567,   677,
     409,   164,   444,   288,  -639,   410,   568,   830,  1015,   744,
     289,   445,   653,   371,    74,    75,   813,   815,   994,   654,
      76,   831,   747,    74,    75,  -639,   411,   748,  -639,    76,
    -639,   555,   555,   995,   372,  -639,   412,   413,   414,   415,
     416,   417,   418,   419,  -639,   420,   421,   422,   423,   657,
     865,   866,   556,   556,   996,   988,   658,   814,   816,   997,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   989,
     433,   434,   435,   436,  -447,   437,  1177,   317,    79,    80,
    1181,   887,   888,   201,   936,  -447,  -447,    79,    80,  1286,
    1178,   714,   -66,   777,  1182,   -66,   -66,   -66,   -66,   -66,
     449,  1292,  1296,  1287,    74,    75,   501,   -66,   -66,   -66,
      76,   -66,   -66,   -66,  1350,   502,  1293,  1293,    93,    93,
     -66,    93,   -66,   788,   702,   -66,   766,   789,  1351,   -74,
     352,   794,   352,   519,   352,   795,   352,  1294,  1294,   660,
     352,   352,  1295,  1297,   141,   -74,   661,   178,   -66,   -66,
     451,   -66,   352,   352,   817,   274,   332,   -74,   179,   180,
     141,   181,   333,   352,  1080,   352,  1081,   820,   452,   151,
     182,   183,   184,   -74,   820,   820,   820,   820,   820,   820,
     820,   820,   642,   -58,   834,  1165,   838,   837,  1353,   408,
    -617,  -226,  1166,   409,  -170,   839,  1357,  -617,   410,    43,
     277,  1167,  1354,   581,    44,    74,    75,   863,   278,   219,
    1358,    76,   185,   665,   186,  1168,   220,  -472,  -617,   411,
     666,  -617,  1169,  -617,  -472,   221,   173,   174,  -617,   412,
     413,   414,   415,   416,   417,   418,   419,  -617,   420,   421,
     422,   423,  -172,   904,   905,  -472,   222,    43,   481,   361,
    -472,   451,    44,   424,   425,   426,   427,   428,   429,   430,
     431,   432,  1059,   433,   434,   435,   436,   579,   437,  1170,
      80,   669,   680,   580,   991,   971,   642,   864,   670,   681,
     319,   972,  -388,   408,  -615,  -388,  -388,   409,  -388,  1242,
     645,  -615,   410,   362,   896,   169,   279,  -388,  -388,  -388,
    -388,  -388,  -388,  -388,   280,   946,   947,   179,   180,  1106,
     181,  1109,  -615,   411,   992,  -615,   170,  -615,   307,   182,
     183,   184,  -615,   412,   413,   414,   415,   416,   417,   418,
     419,  -615,   420,   421,   422,   423,   618,   619,  -388,  -388,
     623,  -388,   897,    93,    93,    93,    93,   424,   425,   426,
     427,   428,   429,   430,   431,   432,  1060,   433,   434,   435,
     436,   185,   437,   186,  1061,  1289,   627,   642,    19,   800,
     801,    20,   902,  -393,   408,  -609,  -393,  -393,   409,  -393,
    1163,   628,  -609,   410,   903,    21,    22,  1075,  -393,  -393,
    -393,  -393,  -393,  -393,  -393,   963,   953,   954,   955,    23,
     922,   548,   629,  -609,   411,  1290,  -609,   630,  -609,   779,
     718,   933,   631,  -609,   412,   413,   414,   415,   416,   417,
     418,   419,  -609,   420,   421,   422,   423,   549,   550,  -393,
    -393,   719,  -393,   307,   934,    93,   981,    93,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,   784,   437,   408,  -607,   786,  1062,   409,  1063,
     785,  1064,  -607,   410,   787,   807,   808,   809,   300,   301,
    1079,   555,   178,  1072,   219,   667,   668,  1084,   549,   550,
    -337,   220,  -451,  -607,   411,  1100,  -607,  -337,  -607,  -451,
     221,  1089,   556,  -607,   412,   413,   414,   415,   416,   417,
     418,   419,  -607,   420,   421,   422,   423,  1090,  -337,  1101,
    -451,   222,  1154,  -337,  1157,  -451,   682,   683,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,  1102,   437,   408,  -616,   927,   185,   409,   186,
    1103,  1160,  -616,   410,   928,  1161,  1176,  1183,  1184,  1185,
    1186,   718,   721,  1270,   219,  1271,  1272,  1273,   223,  1274,
    -366,   220,  -450,  -616,   411,  1275,  -616,  -366,  -616,  -450,
     221,  1276,   719,  -616,   412,   413,   414,   415,   416,   417,
     418,   419,  -616,   420,   421,   422,   423,  1277,  -366,  1298,
    -450,   222,  1299,  -366,  1300,  -450,  1301,  1302,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,  1313,   437,   408,  -613,  1087,   722,   409,   723,
    1341,  1315,  -613,   410,  1088,  1325,  1326,  1346,  1347,  1352,
    1365,   995,   178,  1366,  1367,  1368,   132,  1369,   223,  1370,
    -237,  1371,  1372,  -613,   411,  1373,  -613,  -237,  -613,  1382,
    1383,    18,   996,  -613,   412,   413,   414,   415,   416,   417,
     418,   419,  -613,   420,   421,   422,   423,   488,  -237,    61,
    -237,   479,   517,  -237,    34,   478,   253,   469,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,   727,   437,   408,  -608,  1318,   185,   409,   186,
     926,   315,  -608,   410,  1319,   960,  1078,   105,   212,   589,
     335,  1293,   721,  1110,   845,  1017,   625,   612,   728,   729,
    -248,   678,     0,  -608,   411,     0,  -608,  -248,  -608,     0,
       0,     0,  1294,  -608,   412,   413,   414,   415,   416,   417,
     418,   419,  -608,   420,   421,   422,   423,     0,  -248,     0,
    -248,     0,     0,  -248,     0,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,   931,   437,   408,  -605,     0,   722,   409,   723,
     932,     0,  -605,   410,     0,     0,     0,     0,     0,     0,
       0,     0,   271,     0,     0,     0,     0,     0,   728,   729,
     272,     0,     0,  -605,   411,     0,  -605,   169,  -605,     0,
       0,     0,     0,  -605,   412,   413,   414,   415,   416,   417,
     418,   419,  -605,   420,   421,   422,   423,     0,   170,     0,
    -236,     0,     0,  -236,     0,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,     0,   437,   408,  -601,   179,   180,   409,   181,
       0,     0,  -601,   410,     0,     0,     0,     0,   182,   183,
     184,     0,   281,     0,     0,     0,     0,     0,     0,     0,
    -235,     0,     0,  -601,   411,     0,  -601,  -235,  -601,     0,
       0,     0,     0,  -601,   412,   413,   414,   415,   416,   417,
     418,   419,  -601,   420,   421,   422,   423,     0,  -235,     0,
    -235,     0,     0,  -235,     0,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,     0,   437,   408,  -599,     0,     0,   409,     0,
       0,     0,  -599,   410,     0,     0,     0,     0,     0,     0,
       0,     0,   281,     0,     0,     0,     0,     0,     0,     0,
    -234,     0,     0,  -599,   411,     0,  -599,   169,  -599,     0,
       0,     0,     0,  -599,   412,   413,   414,   415,   416,   417,
     418,   419,  -599,   420,   421,   422,   423,     0,   170,     0,
    -234,     0,     0,  -234,     0,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,     0,   437,   408,  -600,     0,     0,   409,     0,
       0,     0,  -600,   410,     0,     0,     0,     0,     0,     0,
       0,     0,   281,     0,     0,     0,     0,     0,     0,     0,
    -232,     0,     0,  -600,   411,     0,  -600,  -232,  -600,     0,
       0,     0,     0,  -600,   412,   413,   414,   415,   416,   417,
     418,   419,  -600,   420,   421,   422,   423,     0,  -232,     0,
    -232,     0,     0,  -232,     0,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,     0,   437,   408,  -597,     0,     0,   409,     0,
       0,     0,  -597,   410,     0,     0,     0,     0,     0,     0,
       0,     0,   281,     0,     0,     0,     0,     0,     0,     0,
    -233,     0,     0,  -597,   411,     0,  -597,   169,  -597,     0,
       0,     0,     0,  -597,   412,   413,   414,   415,   416,   417,
     418,   419,  -597,   420,   421,   422,   423,     0,  -233,     0,
    -233,     0,     0,  -233,     0,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,     0,   437,   408,  -625,     0,     0,   409,     0,
       0,     0,  -625,   410,     0,     0,     0,     0,     0,     0,
       0,     0,   923,     0,     0,     0,     0,     0,     0,     0,
     924,     0,     0,  -625,   411,     0,  -625,   718,  -625,     0,
       0,     0,     0,  -625,   412,   413,   414,   415,   416,   417,
     418,   419,  -625,   420,   421,   422,   423,     0,   719,     0,
    -247,     0,     0,  -247,     0,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,     0,   437,   408,  -623,     0,     0,   409,     0,
       0,     0,  -623,   410,     0,     0,     0,     0,     0,     0,
       0,     0,   935,     0,     0,     0,     0,     0,     0,     0,
    -246,     0,     0,  -623,   411,     0,  -623,  -246,  -623,     0,
       0,     0,     0,  -623,   412,   413,   414,   415,   416,   417,
     418,   419,  -623,   420,   421,   422,   423,     0,  -246,     0,
    -246,     0,     0,  -246,     0,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,     0,   437,   408,  -624,     0,     0,   409,     0,
       0,     0,  -624,   410,     0,     0,     0,     0,     0,     0,
       0,     0,   935,     0,     0,     0,     0,     0,     0,     0,
    -245,     0,     0,  -624,   411,     0,  -624,   718,  -624,     0,
       0,     0,     0,  -624,   412,   413,   414,   415,   416,   417,
     418,   419,  -624,   420,   421,   422,   423,     0,   719,     0,
    -245,     0,     0,  -245,     0,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,     0,   437,   408,  -621,     0,     0,   409,     0,
       0,     0,  -621,   410,     0,     0,     0,     0,     0,     0,
       0,     0,   935,     0,     0,     0,     0,     0,     0,     0,
    -243,     0,     0,  -621,   411,     0,  -621,  -243,  -621,     0,
       0,     0,     0,  -621,   412,   413,   414,   415,   416,   417,
     418,   419,  -621,   420,   421,   422,   423,     0,  -243,     0,
    -243,     0,     0,  -243,     0,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,     0,   433,   434,
     435,   436,   632,   437,     0,  1165,     0,     0,  -590,   633,
       0,  -225,  1166,   409,     0,     0,     0,  -691,   410,     0,
       0,  1167,   -93,  -172,     0,    74,    75,     0,    43,   935,
       0,    76,     0,    44,     0,  1168,     0,  -244,  -691,   411,
       0,     0,  1169,  -691,   718,     0,     0,     0,  -691,   412,
     413,   414,   415,   416,   417,   418,   419,   146,   420,   421,
     422,   423,     0,     0,     0,  -244,     0,  -244,     0,     0,
    -244,   451,     0,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   696,   433,   434,   435,   634,   687,   437,  1170,
      80,     0,     0,   688,   408,     0,  1028,   697,   409,     0,
       0,     0,     0,   410,     0,     0,     0,     0,     0,     0,
       0,   628,     0,     0,     0,     0,   -35,     0,   698,   -77,
    -170,     0,   -35,   699,   411,    43,  -163,     0,   700,     0,
      44,     0,   629,     0,   412,   413,   414,   415,   416,   417,
     418,   419,   631,   420,   421,   422,   423,   -77,     0,     0,
       0,  1029,     0,     0,    45,     0,     0,     0,   424,   425,
     426,   427,   428,   429,   430,   431,   432,     0,   433,   434,
     435,   436,   642,   437,     0,   447,     0,     0,  -587,   408,
       0,    72,   448,   409,     0,     0,     0,     0,   410,     0,
       0,   449,     0,     0,     0,    74,    75,   -90,  -170,   -79,
     -35,    76,     0,    43,  -163,   235,  -144,  -474,    44,   411,
     236,     0,   450,  -474,  -151,     0,     0,     0,  -580,   412,
     413,   414,   415,   416,   417,   418,   419,   -79,   420,   421,
     422,   423,   146,     0,   237,     0,     0,     0,     0,     0,
    -481,   451,     0,   424,   425,   426,   427,   428,   429,   430,
     431,   432,  -481,   433,   434,   435,   436,   642,   437,   452,
      80,   828,   571,  -589,   408,     0,     0,     0,   409,  -407,
    -455,     0,     0,   410,     0,   829,  -407,  -455,  -580,  -580,
    -580,  -580,  -580,  -580,  -580,  -580,  -580,     0,  -580,  -580,
    -580,  -474,     0,     0,   411,     0,     0,  -407,  -455,     0,
       0,     0,  -407,  -455,   412,   413,   414,   415,   416,   417,
     418,   419,     0,   420,   421,   422,   423,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1046,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   407,   433,   434,
     435,   436,   697,   437,   408,     0,     0,     0,   409,     0,
       0,     0,     0,   410,     0,     0,     0,     0,     0,     0,
       0,   -70,     0,   698,   -77,  -170,     0,   -70,     0,     0,
      43,  -163,     0,   700,   411,    44,     0,     0,     0,     0,
       0,     0,  1047,     0,   412,   413,   414,   415,   416,   417,
     418,   419,   -77,   420,   421,   422,   423,     0,     0,   136,
       0,     0,     0,     0,     0,     0,     0,  1048,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,   697,   437,   408,     0,     0,     0,   409,     0,
       0,     0,     0,   410,     0,     0,  1187,     0,     0,     0,
       0,  1024,   780,   698,  1188,   -70,     0,     0,     0,  -570,
     781,   628,     0,   700,   411,     0,  -570,   555,     0,     0,
       0,     0,  1049,     0,   412,   413,   414,   415,   416,   417,
     418,   419,   629,   420,   421,   422,   423,  -570,   556,     0,
    1025,   622,   631,  -433,     0,     0,     0,  -570,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   436,   790,   437,   408,     0,     0,     0,   409,     0,
    -432,     0,     0,   878,     0,     0,  1189,  -432,     0,     0,
       0,  1044,   571,     0,  1190,     0,     0,     0,     0,  -683,
    -454,   628,     0,     0,   411,     0,  -683,   371,  -432,     0,
       0,     0,     0,  -432,   412,   413,   414,   415,   416,   417,
     418,   419,   629,   420,   421,   422,   423,  -683,   372,     0,
    1045,   685,   631,  -454,     0,     0,     0,  -683,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,   879,   571,   437,   408,     0,     0,     0,   409,     0,
    -452,     0,     0,   410,     0,     0,  1191,  -452,     0,     0,
       0,   684,   571,     0,  1192,     0,     0,     0,     0,  -683,
    -453,   628,     0,     0,   411,     0,  -683,   371,  -452,     0,
       0,     0,     0,  -452,   412,   413,   414,   415,   416,   417,
     418,   419,   629,   420,   421,   422,   423,  -683,  -453,     0,
    1237,   685,   631,  -453,     0,     0,     0,  -683,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,  1136,   790,   437,   408,     0,     0,     0,   409,     0,
    -431,     0,     0,  1139,     0,     0,  1193,   555,     0,     0,
       0,   684,   790,     0,  1194,     0,     0,     0,     0,  -683,
    -429,   628,     0,     0,   411,     0,  -683,  -429,   556,     0,
       0,     0,     0,  -431,   412,   413,   414,   415,   416,   417,
     418,   419,   629,   420,   421,   422,   423,  -683,  -429,     0,
    1243,   685,   631,  -429,     0,     0,     0,  -683,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   642,   433,   434,
     435,  1140,   790,   437,   408,     0,     0,     0,   409,     0,
    -430,     0,     0,   410,     0,     0,  1195,   555,     0,     0,
       0,   684,  1085,     0,  1196,     0,     0,     0,     0,  -683,
    1086,   628,     0,     0,   411,     0,  -683,   995,  -430,     0,
       0,     0,     0,  -430,   412,   413,   414,   415,   416,   417,
     418,   419,   629,   420,   421,   422,   423,  -683,   996,     0,
    1341,   685,   631,  -336,     0,     0,     0,  -683,   424,   425,
     426,   427,   428,   429,   430,   431,   432,     0,   433,   434,
     435,  1305,   591,   437,   994,     0,     0,     0,  -512,   592,
       0,     0,  -335,     0,     0,     0,     0,  -578,   386,  -335,
       0,     0,     0,     0,     0,     0,   591,     0,     0,   994,
       0,     0,     0,   592,  -578,   593,     0,  -334,  -578,   387,
    -335,  -578,   846,  -578,   995,  -335,     0,  -505,  -578,   388,
     389,   390,   391,   392,   393,   394,   395,     0,   396,   397,
     398,   399,  -578,   387,     0,   996,     0,  -578,     0,     0,
    -334,     0,  -578,   388,   389,   390,   391,   392,   393,   394,
     395,  -578,   396,   397,   398,   399,   400,   591,   401,     0,
       0,     0,     0,   305,   592,  -578,     0,   306,  -184,  -196,
      73,     0,  -578,   386,   -66,   -66,     0,   -66,  -238,     0,
     847,     0,   401,    74,    75,     0,   -66,   -66,   -66,    76,
     -66,   -66,   -66,  -578,   387,     0,     0,  -196,  -578,  -238,
      77,   307,     0,  -578,   388,   389,   390,   391,   392,   393,
     394,   395,  -578,   396,   397,   398,   399,   591,     0,     0,
       0,     0,     0,     0,   592,     0,     0,   -66,   -66,    78,
     -66,     0,  -578,   386,     0,     0,     0,     0,     0,     0,
       0,   400,     0,   401,     0,   870,     0,    79,   151,     0,
     593,     0,     0,  -578,   387,     0,     0,     0,  -578,     0,
     628,     0,  -505,  -578,   388,   389,   390,   391,   392,   393,
     394,   395,   599,   396,   397,   398,   399,     0,   958,   385,
    -548,   629,     0,     0,   201,   448,   871,  -548,   386,     0,
       0,   631,     0,     0,   449,     0,     0,     0,    74,    75,
       0,   400,   994,   401,    76,     0,     0,     0,  -548,   387,
    -332,     0,   202,  -548,     0,   450,     0,  -332,  -548,   388,
     389,   390,   391,   392,   393,   394,   395,  -548,   396,   397,
     398,   399,   599,     0,   994,     0,     0,     0,  -332,   385,
    -547,     0,  -333,  -332,   451,     0,     0,  -547,   386,   995,
       0,     0,     0,     0,     0,     0,   400,   889,   401,  1197,
       0,     0,   452,    80,     0,  1337,     0,  1198,  -547,   387,
    -333,     0,   697,  -547,   628,  -333,     0,     0,  -547,   388,
     389,   390,   391,   392,   393,   394,   395,  -547,   396,   397,
     398,   399,   599,   698,     0,   629,  1338,     0,   277,   385,
    -536,     0,     0,   700,     0,   631,   278,  -536,   386,  -275,
    -275,     0,  -275,     0,     0,     0,   400,     0,   401,     0,
       0,  -275,  -275,  -275,   173,   174,     0,     0,  -536,   387,
       0,     0,     0,  -536,     0,     0,     0,     0,  -536,   388,
     389,   390,   391,   392,   393,   394,   395,  -536,   396,   397,
     398,   399,   599,     0,     0,     0,  1316,     0,   784,   385,
    -534,     0,  -275,  -275,  1317,  -275,   785,  -534,   386,  -303,
    -303,  1293,  -303,     0,     0,     0,   400,     0,   401,     0,
       0,  -303,  -303,  -303,   549,   550,     0,     0,  -534,   387,
       0,     0,  1294,  -534,     0,     0,     0,  -365,  -534,   388,
     389,   390,   391,   392,   393,   394,   395,  -534,   396,   397,
     398,   399,   599,     0,     0,     0,  1327,     0,   931,   385,
    -528,     0,  -303,  -303,  -364,  -303,   932,  -528,   386,  -289,
    -289,  -364,  -289,     0,     0,     0,   400,     0,   401,     0,
       0,  -289,  -289,  -289,   728,   729,     0,     0,  -528,   387,
       0,     0,  -364,  -528,     0,     0,     0,  -364,  -528,   388,
     389,   390,   391,   392,   393,   394,   395,  -528,   396,   397,
     398,   399,   599,     0,     0,     0,  -385,     0,   542,   385,
    -526,     0,  -289,  -289,  -385,  -289,   778,  -526,   386,   179,
     180,  -385,   181,     0,     0,     0,   400,     0,   401,     0,
       0,   182,   183,   184,     0,     0,     0,     0,  -526,   387,
       0,     0,  -385,  -526,     0,     0,     0,  -385,  -526,   388,
     389,   390,   391,   392,   393,   394,   395,  -526,   396,   397,
     398,   399,   599,     0,     0,     0,  1327,     0,   782,   385,
    -535,     0,     0,   543,  -363,   544,   783,  -535,   386,   179,
     180,  1293,   181,     0,     0,     0,   400,     0,   401,     0,
       0,   182,   183,   184,     0,     0,     0,     0,  -535,   387,
       0,     0,  1294,  -535,     0,     0,     0,  -363,  -535,   388,
     389,   390,   391,   392,   393,   394,   395,  -535,   396,   397,
     398,   399,   599,     0,     0,     0,  1327,     0,   721,   385,
    -532,     0,     0,   543,  -361,   544,   925,  -532,   386,   179,
     180,  -361,   181,     0,     0,     0,   400,     0,   401,     0,
       0,   182,   183,   184,     0,     0,     0,     0,  -532,   387,
       0,     0,  -361,  -532,     0,     0,     0,  -361,  -532,   388,
     389,   390,   391,   392,   393,   394,   395,  -532,   396,   397,
     398,   399,   599,     0,     0,     0,  1327,     0,   929,   385,
    -527,     0,     0,   722,  -362,   723,   930,  -527,   386,   179,
     180,  1293,   181,     0,     0,     0,   400,     0,   401,     0,
     912,   182,   183,   184,     0,     0,     0,     0,  -527,   387,
       0,     0,  -362,  -527,     0,   697,     0,  -362,  -527,   388,
     389,   390,   391,   392,   393,   394,   395,  -527,   396,   397,
     398,   399,   599,     0,     0,     0,   698,     0,   178,   385,
    -524,   913,     0,   722,     0,   723,   700,  -524,   386,   179,
     180,     0,   181,     0,     0,     0,   400,     0,   401,     0,
       0,   182,   183,   184,     0,     0,     0,     0,  -524,   387,
       0,     0,     0,  -524,     0,     0,     0,     0,  -524,   388,
     389,   390,   391,   392,   393,   394,   395,  -524,   396,   397,
     398,   399,   599,     0,     0,     0,     0,     0,   542,   385,
    -520,     0,     0,   185,     0,   186,     0,  -520,   386,   179,
     180,     0,   181,     0,     0,     0,   400,     0,   401,     0,
       0,   182,   183,   184,     0,     0,     0,     0,  -520,   387,
       0,     0,     0,  -520,     0,     0,     0,     0,  -520,   388,
     389,   390,   391,   392,   393,   394,   395,  -520,   396,   397,
     398,   399,   599,     0,     0,     0,     0,     0,   721,   385,
    -518,     0,     0,   543,     0,   544,     0,  -518,   386,   179,
     180,     0,   181,     0,     0,     0,   400,     0,   401,     0,
       0,   182,   183,   184,     0,     0,     0,     0,  -518,   387,
       0,     0,     0,  -518,     0,     0,     0,     0,  -518,   388,
     389,   390,   391,   392,   393,   394,   395,  -518,   396,   397,
     398,   399,   599,     0,     0,     0,     0,     0,     0,   385,
    -519,     0,     0,   722,     0,   723,     0,  -519,   386,     0,
       0,     0,     0,     0,     0,     0,   400,   684,   401,  1199,
       0,     0,     0,     0,     0,  -683,     0,  1200,  -519,   387,
       0,     0,  -683,  -519,   628,     0,     0,     0,  -519,   388,
     389,   390,   391,   392,   393,   394,   395,  -519,   396,   397,
     398,   399,   599,  -683,     0,   629,  -683,   685,  -683,   385,
    -516,     0,     0,  -683,     0,   631,     0,  -516,   386,     0,
       0,     0,  -683,     0,     0,     0,   400,  1020,   401,  1201,
       0,     0,     0,     0,     0,  -570,     0,  1202,  -516,   387,
       0,     0,  -570,  -516,   628,     0,     0,     0,  -516,   388,
     389,   390,   391,   392,   393,   394,   395,  -516,   396,   397,
     398,   399,   599,  -570,     0,   629,  1021,   622,  -570,   385,
    -544,     0,     0,  -570,     0,   631,     0,  -544,   386,     0,
       0,     0,  -570,     0,     0,     0,   400,   621,   401,  1205,
       0,     0,     0,     0,     0,  -570,     0,  1206,  -544,   387,
       0,     0,  -570,  -544,   628,     0,     0,     0,  -544,   388,
     389,   390,   391,   392,   393,   394,   395,  -544,   396,   397,
     398,   399,   599,  -570,     0,   629,     0,   622,  -570,   385,
    -542,     0,     0,  -570,     0,   631,     0,  -542,   386,     0,
       0,     0,  -570,     0,     0,     0,   400,   881,   401,  1209,
       0,     0,     0,     0,     0,   882,     0,  1210,  -542,   387,
       0,     0,   697,  -542,   628,     0,     0,     0,  -542,   388,
     389,   390,   391,   392,   393,   394,   395,  -542,   396,   397,
     398,   399,   599,   698,     0,   629,  -645,     0,  -645,   385,
    -543,     0,     0,   700,     0,   631,     0,  -543,   386,     0,
       0,     0,  -645,     0,     0,     0,   400,   889,   401,  1211,
       0,     0,     0,     0,     0,  -644,     0,  1212,  -543,   387,
       0,     0,  -644,  -543,   628,     0,     0,     0,  -543,   388,
     389,   390,   391,   392,   393,   394,   395,  -543,   396,   397,
     398,   399,   599,  -644,     0,   629,  -644,     0,  -644,   385,
    -540,     0,     0,  -644,     0,   631,     0,  -540,   386,     0,
       0,     0,  -644,     0,     0,   624,   400,     0,   401,     0,
       0,   384,   385,     0,     0,     0,     0,     0,  -540,   387,
       0,   386,     0,  -540,     0,     0,     0,     0,  -540,   388,
     389,   390,   391,   392,   393,   394,   395,  -540,   396,   397,
     398,   399,   387,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   388,   389,   390,   391,   392,   393,   394,   395,
       0,   396,   397,   398,   399,   599,   400,     0,   401,     0,
       0,  -509,   385,     0,     0,     0,     0,     0,     0,     0,
       0,   386,     0,     0,  1213,     0,     0,     0,   599,   400,
       0,   401,  1214,     0,  -511,   385,     0,     0,     0,   628,
       0,     0,   387,     0,   386,     0,     0,     0,     0,     0,
       0,     0,   388,   389,   390,   391,   392,   393,   394,   395,
     629,   396,   397,   398,   399,   387,     0,     0,     0,     0,
     631,     0,     0,     0,     0,   388,   389,   390,   391,   392,
     393,   394,   395,   599,   396,   397,   398,   399,     0,   400,
     385,   401,     0,     0,     0,     0,     0,     0,     0,   386,
       0,   599,     0,     0,     0,     0,     0,     0,   385,     0,
    1215,     0,   400,     0,   401,     0,     0,   848,  1216,     0,
     387,     0,     0,     0,     0,   628,     0,     0,     0,     0,
     388,   389,   390,   391,   392,   393,   394,   395,   387,   396,
     397,   398,   399,     0,     0,     0,   629,     0,   388,   389,
     390,   391,   392,   393,   394,   395,   631,   396,   397,   398,
     399,     0,     0,  1217,     0,     0,     0,   400,   957,   401,
       0,  1218,   306,  -184,  -211,   448,     0,     0,   628,   -66,
     -66,     0,   -66,  -249,   449,   849,     0,   401,    74,    75,
       0,   -66,   -66,   -66,    76,   -66,   -66,   -66,     0,   629,
       0,     0,  -211,     0,  -249,   450,   307,     0,   702,   631,
     313,     0,     0,     0,     0,     0,   201,    73,     0,   149,
       0,     0,     0,     0,     0,   -95,    73,     0,     0,     0,
      74,    75,   -66,   -66,   451,   -66,    76,     0,     0,    74,
      75,     0,     0,   701,   202,    76,   -87,    77,     0,   -99,
     448,     0,   452,   151,   -66,   -66,    77,   -66,  -249,   449,
     889,     0,     0,    74,    75,     0,   -66,   -66,   -66,    76,
     -66,   -66,   -66,     0,   150,   697,    78,     0,   850,  -249,
     450,     0,     0,   702,  -249,    78,   851,     0,     0,     0,
       0,     0,     0,   628,    79,    80,   698,     0,     0,  1338,
       0,     0,     0,    79,    80,     0,   700,   -66,   -66,   451,
     -66,   305,     0,     0,   629,   306,  -184,  -209,    73,  -553,
       0,     0,   -66,   -66,   631,   -66,  -238,   452,   151,     0,
       0,    74,    75,  -553,   -66,   -66,   -66,    76,   -66,   -66,
     -66,     0,     0,   701,     0,  -209,     0,  -238,    77,   307,
     448,   -66,     0,     0,   -66,   -66,     0,   -66,  -249,   449,
       0,     0,     0,    74,    75,     0,   -66,   -66,   -66,    76,
     -66,   -66,   -66,     0,     0,   -66,   -66,    78,   -66,  -249,
     450,  -249,     0,   702,  -249,  1165,     0,     0,     0,     0,
       0,     0,  1166,  -359,     0,    79,   151,     0,     0,     0,
    -359,  1167,     0,     0,  1219,    74,    75,   -66,   -66,   451,
     -66,    76,  1220,     0,     0,  1168,     0,     0,   957,   628,
       0,  -359,  1169,     0,  -199,   448,  -359,   452,   151,   -66,
     -66,     0,   -66,  -249,   449,     0,     0,     0,    74,    75,
     629,   -66,   -66,   -66,    76,   -66,   -66,   -66,     0,     0,
     631,   451,  -199,     0,  -249,   450,   307,     0,   702,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1170,
      80,     0,     0,   735,     0,     0,     0,     0,     0,     0,
     448,     0,   -66,   -66,   451,   -66,     0,     0,     0,   449,
       0,     0,     0,    74,    75,     0,     0,   701,     0,    76,
       0,     0,   452,   151,   448,   -66,   500,   202,   -66,   -66,
     450,   -66,  -249,   449,   889,     0,     0,    74,    75,     0,
     -66,   -66,   -66,    76,   -66,   -66,   -66,     0,     0,   697,
     684,     0,  1221,  -249,   450,  -249,     0,   702,  -683,   451,
    1222,     0,   880,     0,     0,  -683,     0,   628,     0,     0,
     698,     0,     0,  1340,     0,     0,     0,   452,    80,     0,
     700,   -66,   -66,   451,   -66,     0,  -683,     0,   629,  -683,
     685,  -683,  1165,     0,     0,     0,  -683,     0,   631,  1166,
     -66,   452,   151,   -66,   -66,  -683,  1278,  -386,  1167,     0,
       0,     0,    74,    75,     0,   -66,   -66,   -66,    76,   -66,
     -66,   -66,  1168,     0,   149,     0,     0,   -87,  -386,  1169,
     -96,    73,   702,  -386,     0,   -66,   -66,     0,   -66,  -238,
       0,     0,     0,     0,    74,    75,     0,   -66,   -66,   -66,
      76,   -66,   -66,   -66,     0,   150,   -66,   -66,   451,   -66,
    -238,    77,     0,     0,     0,  -238,   338,     0,     0,     0,
       0,     0,  -419,   339,     0,     0,  1279,   151,     0,     0,
       0,     0,   340,     0,     0,  1223,    74,    75,   -66,   -66,
      78,   -66,    76,  1224,     0,     0,     0,   856,     0,   338,
     628,     0,     0,   341,     0,  -552,   339,   -66,    79,   151,
     -66,   -66,  -552,   -66,  -435,   340,     0,     0,     0,    74,
      75,   629,   -66,   -66,   -66,    76,   -66,   -66,   -66,     0,
       0,   631,   342,  -552,   889,  -435,   341,     0,  -552,   526,
    -435,   338,  1339,  -552,     0,     0,     0,  -418,   339,   697,
     343,    80,  -552,     0,     0,     0,     0,   340,     0,     0,
       0,    74,    75,   -66,   -66,   342,   -66,    76,     0,     0,
     698,     0,     0,  1340,   948,     0,     0,   889,   341,     0,
     700,   949,   -66,   343,   151,   -66,   -66,   -66,   -66,   -66,
     449,   889,   697,     0,    74,    75,   889,   -66,   -66,   -66,
      76,   -66,   -66,   -66,  1342,     0,   697,   342,     0,     0,
     -66,   697,   -66,   698,   702,   -66,  1344,     0,     0,     0,
       0,     0,     0,   700,     0,   343,    80,   698,     0,     0,
    1345,     0,   698,     0,     0,  1343,   149,   700,   -66,   -66,
     149,   -66,   700,    73,     0,     0,     0,    73,   -66,     0,
       0,   -66,   -66,     0,   -66,  -238,    74,    75,   452,   151,
      74,    75,    76,   -66,   -66,   -66,    76,   -66,   -66,   -66,
       0,     0,   282,    77,     0,     0,  -238,    77,  -238,   164,
     -66,  -238,     0,   -66,   -66,   -66,   -66,   -66,     0,     0,
       0,     0,    74,    75,     0,   -66,   -66,   -66,    76,   -66,
     -66,   -66,    78,     0,   -66,   -66,    78,   -66,   -66,     0,
     -66,     0,     0,   -66,     0,     0,     0,     0,     0,     0,
      79,    80,     0,     0,    79,   151,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1225,   -66,   -66,    78,   -66,
     149,     0,     0,  1226,     0,     0,     0,    73,   -66,   500,
     628,   -66,   -66,     0,   -66,  -238,    79,   151,     0,     0,
      74,    75,     0,   -66,   -66,   -66,    76,   -66,   -66,   -66,
       0,   629,   791,     0,   856,   889,  -238,    77,  -238,   538,
     -66,   631,  -555,   -66,   -66,     0,   -66,   -66,   340,  -555,
     697,     0,    74,    75,     0,   -66,   -66,   -66,    76,   -66,
     -66,   -66,     0,     0,   -66,   -66,    78,   -66,   -66,     0,
    -555,   698,   526,   -66,  1376,  -555,     0,     0,     0,     0,
    -555,   700,     0,     0,    79,   151,     0,     0,     0,  -555,
       0,     0,     0,     0,     0,     0,   -66,   -66,   342,   -66,
     768,     0,     0,     0,     0,     0,     0,   769,   -66,     0,
       0,   -66,   -66,     0,   982,  -350,   343,   151,     0,     0,
      74,    75,     0,   -66,   -66,   -66,    76,   -66,   -66,   -66,
     770,     0,   948,     0,     0,   889,  -350,   771,     0,   949,
    -314,  -350,     0,  -314,  -314,  -314,  -314,  -314,   449,     0,
     697,     0,    74,    75,   889,  -314,  -314,  -314,    76,  -314,
    -314,  -314,  1377,     0,   -66,   -66,    78,   -66,  -314,   697,
    -314,   698,     0,  -314,  1378,     0,     0,     0,     0,     0,
       0,   700,     0,     0,   983,   151,     0,     0,     0,     0,
     698,     0,     0,  1378,     0,     0,  -314,  -314,   288,  -314,
     700,     0,     0,     0,     0,   289,  -260,     0,     0,  -260,
    -260,  -260,  -260,  -260,     0,     0,   452,    80,    74,    75,
       0,  -260,  -260,  -260,    76,  -260,  -260,  -260,     0,     0,
     288,     0,     0,     0,  -260,     0,  -260,   289,   -66,  -260,
       0,   -66,   -66,   -66,   -66,   -66,     0,     0,     0,     0,
      74,    75,     0,   -66,   -66,   -66,    76,   -66,   -66,   -66,
       0,     0,  -260,  -260,     0,  -260,   -66,     0,   -66,     0,
       0,   -66,   701,     0,     0,     0,     0,     0,   -98,   448,
       0,     0,    79,    80,     0,     0,     0,     0,   449,     0,
       0,     0,    74,    75,   -66,   -66,   802,   -66,    76,     0,
       0,     0,     0,   803,   -66,     0,     0,   -66,   -66,   450,
     -66,   -66,   340,     0,    79,   151,    74,    75,     0,   -66,
     -66,   -66,    76,   -66,   -66,   -66,     0,   338,     0,     0,
       0,     0,   -66,  -423,   339,     0,   526,   -66,   451,     0,
       0,     0,     0,   340,     0,     0,     0,    74,    75,     0,
       0,     0,     0,    76,     0,     0,   452,    80,     0,     0,
     -66,   -66,   802,   -66,   341,     0,     0,     0,     0,   803,
    -326,     0,     0,  -326,  -326,     0,  -326,  -326,   340,     0,
     343,   151,    74,    75,     0,  -326,  -326,  -326,    76,  -326,
    -326,  -326,     0,   342,   936,     0,     0,     0,  -326,     0,
       0,   714,  -288,  -326,     0,  -288,  -288,  -288,  -288,  -288,
     449,   343,    80,     0,    74,    75,     0,  -288,  -288,  -288,
      76,     0,     0,     0,     0,     0,  -326,  -326,     0,  -326,
    -288,     0,  -288,     0,     0,  -288,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   343,    80,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -288,  -288,
     451,  -288,   282,     0,     0,     0,     0,     0,     0,   164,
    -274,     0,     0,  -274,  -274,  -274,  -274,  -274,   452,    80,
       0,     0,    74,    75,     0,  -274,  -274,  -274,    76,     0,
       0,     0,     0,     0,   791,     0,     0,     0,  -274,     0,
    -274,   538,  -302,  -274,     0,  -302,  -302,     0,  -302,  -302,
     340,     0,     0,     0,    74,    75,   149,  -302,  -302,  -302,
      76,     0,     0,    73,  -231,     0,  -274,  -274,    78,  -274,
    -302,  -231,     0,     0,     0,  -302,    74,    75,     0,     0,
       0,     0,    76,     0,     0,     0,    79,    80,   149,     0,
       0,     0,  -231,    77,  -231,    73,  -230,  -231,  -302,  -302,
     342,  -302,     0,  -230,     0,     0,     0,     0,    74,    75,
       0,     0,     0,     0,    76,     0,     0,     0,   343,    80,
       0,     0,    78,   338,  -230,    77,  -230,     0,     0,  -230,
     339,  -428,     0,     0,     0,     0,     0,     0,  -428,   340,
      79,    80,     0,    74,    75,     0,     0,     0,  1227,    76,
     338,     0,     0,     0,    78,     0,  1228,   339,  -427,  -428,
     341,     0,   338,   697,  -428,  -427,   340,     0,  -422,   339,
      74,    75,    79,    80,     0,     0,    76,     0,   340,     0,
       0,     0,    74,    75,   698,   768,  -427,   341,    76,   342,
       0,  -427,   769,  -331,   700,  1229,     0,     0,     0,   341,
    -331,     0,     0,  1230,     0,    74,    75,   343,    80,     0,
     697,    76,   768,     0,     0,   770,   342,     0,     0,   769,
    -330,  -331,   771,     0,     0,     0,  -331,  -330,   342,  1231,
       0,   698,    74,    75,   343,    80,   701,  1232,    76,     0,
       0,   700,   770,   448,   697,   500,   343,    80,  -330,   771,
       0,    78,   449,  -330,     0,     0,    74,    75,     0,     0,
       0,  1165,    76,     0,   338,   698,     0,     0,  1166,   772,
      80,   339,     0,   450,     0,   700,     0,  1167,    78,     0,
     340,    74,    75,     0,    74,    75,   768,    76,   701,     0,
      76,  1168,     0,   769,     0,   448,   772,    80,  1169,     0,
       0,   341,   451,     0,   449,     0,    74,    75,    74,    75,
       0,  1233,    76,     0,    76,     0,   770,     0,     0,  1234,
     452,    80,   219,   771,     0,   450,   697,   451,   574,   220,
     342,     0,     0,     0,     0,     0,     0,     0,   221,     0,
       0,     0,     0,  1235,     0,  1170,    80,   698,   343,    80,
       0,  1236,    78,     0,   451,  -445,     0,   700,   697,   222,
       0,     0,     0,     0,     0,   575,  -445,  -445,     0,   175,
     772,    80,   452,    80,     0,     0,     0,  -253,     0,   698,
    -253,  -253,  -253,  -253,  -253,     0,     0,     0,     0,   700,
       0,     0,  -253,  -253,  -253,  -253,  -253,   176,   177,     0,
       0,   175,     0,     0,     0,  -253,   223,  -253,     0,  -252,
    -253,     0,  -252,  -252,  -252,  -252,  -252,     0,     0,     0,
       0,     0,     0,     0,  -252,  -252,  -252,  -252,  -252,   176,
     177,     0,     0,  -253,  -253,   175,  -253,  -252,     0,  -252,
       0,     0,  -252,  -251,     0,     0,  -251,  -251,  -251,  -251,
    -251,     0,     0,     0,     0,     0,     0,     0,  -251,  -251,
    -251,  -251,  -251,   176,   177,  -252,  -252,   175,  -252,     0,
       0,  -251,     0,  -251,     0,  -250,  -251,     0,  -250,  -250,
    -250,  -250,  -250,     0,     0,     0,     0,     0,     0,     0,
    -250,  -250,  -250,  -250,  -250,   176,   177,     0,     0,  -251,
    -251,   730,  -251,  -250,     0,  -250,     0,     0,  -250,  -307,
       0,     0,  -307,  -307,  -307,  -307,  -307,     0,     0,     0,
       0,     0,     0,     0,  -307,  -307,  -307,  -307,  -307,   731,
     732,  -250,  -250,   730,  -250,     0,     0,  -307,     0,  -307,
       0,  -306,  -307,     0,  -306,  -306,  -306,  -306,  -306,     0,
       0,     0,     0,     0,     0,     0,  -306,  -306,  -306,  -306,
    -306,   731,   732,     0,     0,  -307,  -307,   730,  -307,  -306,
       0,  -306,     0,     0,  -306,  -305,     0,     0,  -305,  -305,
    -305,  -305,  -305,     0,     0,     0,     0,     0,     0,     0,
    -305,  -305,  -305,  -305,  -305,   731,   732,  -306,  -306,   730,
    -306,     0,     0,  -305,     0,  -305,     0,  -304,  -305,     0,
    -304,  -304,  -304,  -304,  -304,     0,     0,     0,     0,     0,
       0,     0,  -304,  -304,  -304,  -304,  -304,   731,   732,     0,
       0,  -305,  -305,   540,  -305,  -304,     0,  -304,     0,     0,
    -304,  -399,     0,     0,  -399,  -399,     0,  -399,  -399,     0,
       0,     0,     0,     0,     0,     0,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -304,  -304,     0,  -304,   991,  1238,  -399,
       0,     0,     0,   541,  -399,  -341,  1239,     0,  -388,  -388,
       0,  -388,  -341,   697,     0,     0,     0,     0,     0,     0,
    -388,  -388,  -388,  -388,  -388,  -388,  -388,  -399,  -399,     0,
    -399,  1289,     0,  -341,   698,     0,     0,   992,  -341,  -370,
       0,     0,  -393,  -393,   700,  -393,  -370,     0,     0,     0,
       0,     0,     0,     0,  -393,  -393,  -393,  -393,  -393,  -393,
    -393,  -388,  -388,     0,  -388,   172,     0,  -370,     0,     0,
       0,  1290,  -370,  -275,     0,     0,  -275,  -275,  -275,  -275,
    -275,     0,     0,     0,     0,     0,     0,     0,  -275,  -275,
    -275,   173,   174,     0,     0,  -393,  -393,   172,  -393,     0,
       0,  -275,     0,  -275,     0,   273,  -275,     0,  -275,  -275,
    -275,  -275,  -275,     0,     0,     0,     0,     0,     0,     0,
    -275,  -275,  -275,   173,   174,     0,     0,     0,     0,  -275,
    -275,   551,  -275,  -275,     0,  -275,     0,     0,  -275,  -319,
       0,     0,  -319,  -319,     0,  -319,  -319,     0,     0,     0,
       0,     0,     0,     0,  -319,  -319,  -319,  -319,  -319,   552,
     553,  -275,  -275,   727,  -275,     0,     0,  -319,     0,     0,
       0,  -289,  -319,     0,  -289,  -289,  -289,  -289,  -289,     0,
       0,     0,     0,     0,     0,     0,  -289,  -289,  -289,   728,
     729,     0,     0,     0,     0,  -319,  -319,   727,  -319,  -289,
       0,  -289,     0,     0,  -289,   926,     0,     0,  -289,  -289,
    -289,  -289,  -289,     0,     0,     0,     0,     0,     0,     0,
    -289,  -289,  -289,   728,   729,     0,     0,  -289,  -289,   551,
    -289,     0,     0,  -289,     0,  -289,     0,  -318,  -289,     0,
    -318,  -318,     0,  -318,  -318,     0,     0,     0,     0,     0,
       0,     0,  -318,  -318,  -318,  -318,  -318,   552,   553,     0,
       0,  -289,  -289,   551,  -289,  -318,     0,     0,     0,     0,
    -318,  -317,     0,     0,  -317,  -317,     0,  -317,  -317,     0,
       0,     0,     0,     0,     0,     0,  -317,  -317,  -317,  -317,
    -317,   552,   553,  -318,  -318,   551,  -318,     0,     0,  -317,
       0,     0,     0,  -316,  -317,     0,  -316,  -316,     0,  -316,
    -316,     0,     0,     0,     0,     0,     0,     0,  -316,  -316,
    -316,  -316,  -316,   552,   553,     0,     0,  -317,  -317,   188,
    -317,  -316,     0,     0,     0,     0,  -316,  -265,     0,     0,
    -265,  -265,  -265,  -265,  -265,     0,     0,     0,     0,     0,
       0,     0,  -265,  -265,  -265,     0,     0,     0,     0,  -316,
    -316,   188,  -316,     0,     0,  -265,     0,  -265,     0,  -264,
    -265,     0,  -264,  -264,  -264,  -264,  -264,     0,     0,     0,
       0,     0,     0,     0,  -264,  -264,  -264,     0,     0,     0,
       0,     0,     0,   189,  -265,   188,  -265,  -264,     0,  -264,
       0,     0,  -264,  -262,     0,     0,  -262,  -262,  -262,  -262,
    -262,     0,     0,     0,     0,     0,     0,     0,  -262,  -262,
    -262,     0,     0,     0,     0,   189,  -264,   188,  -264,     0,
       0,  -262,     0,  -262,     0,  -263,  -262,     0,  -263,  -263,
    -263,  -263,  -263,     0,     0,     0,     0,     0,     0,     0,
    -263,  -263,  -263,     0,     0,     0,     0,     0,     0,   189,
    -262,   548,  -262,  -263,     0,  -263,     0,     0,  -263,  -303,
       0,     0,  -303,  -303,  1240,  -303,  -303,     0,     0,     0,
       0,     0,  1241,     0,  -303,  -303,  -303,   549,   550,   697,
       0,   189,  -263,   725,  -263,     0,     0,  -303,     0,     0,
       0,  -279,  -303,     0,  -279,  -279,  -279,  -279,  -279,     0,
     698,     0,     0,     0,     0,     0,  -279,  -279,  -279,     0,
     700,     0,     0,     0,     0,  -303,  -303,   548,  -303,  -279,
       0,  -279,     0,     0,  -279,   779,     0,     0,  -303,  -303,
    1244,  -303,  -303,     0,     0,     0,     0,     0,  1245,     0,
    -303,  -303,  -303,   549,   550,   697,     0,   726,  -279,   725,
    -279,     0,     0,  -303,     0,     0,     0,  -278,  -303,     0,
    -278,  -278,  -278,  -278,  -278,     0,   698,     0,     0,     0,
       0,     0,  -278,  -278,  -278,     0,   700,     0,     0,     0,
       0,  -303,  -303,   725,  -303,  -278,     0,  -278,     0,     0,
    -278,  -276,     0,     0,  -276,  -276,  -276,  -276,  -276,     0,
       0,     0,     0,     0,     0,     0,  -276,  -276,  -276,     0,
       0,     0,     0,   726,  -278,   725,  -278,     0,     0,  -276,
       0,  -276,     0,  -277,  -276,     0,  -277,  -277,  -277,  -277,
    -277,     0,     0,     0,     0,     0,     0,     0,  -277,  -277,
    -277,     0,     0,     0,     0,     0,     0,   726,  -276,   546,
    -276,  -277,     0,  -277,     0,     0,  -277,  -293,     0,     0,
    -293,  -293,  1248,  -293,  -293,     0,     0,     0,     0,     0,
    1249,     0,  -293,  -293,  -293,     0,     0,   697,     0,   726,
    -277,   546,  -277,     0,     0,  -293,     0,     0,     0,  -292,
    -293,     0,  -292,  -292,     0,  -292,  -292,     0,   698,     0,
       0,     0,     0,     0,  -292,  -292,  -292,     0,   700,     0,
       0,     0,     0,   547,  -293,   546,  -293,  -292,     0,     0,
       0,     0,  -292,  -290,     0,     0,  -290,  -290,  1252,  -290,
    -290,     0,     0,     0,     0,     0,  1253,     0,  -290,  -290,
    -290,     0,     0,   697,     0,   547,  -292,   546,  -292,     0,
       0,  -290,     0,     0,     0,  -291,  -290,     0,  -291,  -291,
       0,  -291,  -291,     0,   698,     0,     0,     0,     0,  1040,
    -291,  -291,  -291,     0,   700,     0,     0,  -683,     0,   547,
    -290,   880,  -290,  -291,  -683,     0,   889,   889,  -291,     0,
       0,     0,     0,     0,  -647,  -648,     0,     0,   889,     0,
       0,  -647,  -648,     0,     0,  -683,  -649,     0,  1041,   685,
    -683,   547,  -291,  -649,  -291,  -683,     0,     0,     0,     0,
       0,   889,  -647,  -648,  -683,  -647,  -648,  -647,  -648,  -650,
       0,     0,  -647,  -648,  -649,     0,  -650,  -649,     0,  -649,
       0,  -647,  -648,   889,  -649,     0,     0,     0,     0,     0,
       0,  -651,     0,  -649,     0,   889,  1046,  -650,  -651,     0,
    -650,     0,  -650,  -652,  -665,     0,     0,  -650,     0,     0,
    -652,   697,  1254,   889,     0,     0,  -650,     0,     0,  -651,
    1255,  -662,  -651,     0,  -651,   889,     0,   697,  -662,  -651,
       0,  -652,   698,  -663,  -652,  -665,  -652,  -665,  -651,     0,
    -663,  -652,   700,     0,     0,   889,     0,     0,   698,  -662,
    -652,  1047,  -662,  -664,  -662,     0,     0,   889,   700,  -662,
    -664,  -663,     0,     0,  -663,  -643,  -663,     0,  -662,     0,
     889,  -663,   697,     0,   889,     0,     0,     0,  -641,     0,
    -663,  -664,  -642,     0,  -664,  -641,  -664,   889,     0,   697,
       0,  -664,     0,   698,     0,  -646,  -643,     0,  -643,  1246,
    -664,     0,   697,   700,     0,     0,  -641,  1247,     0,  -641,
    -642,  -641,  -643,  -642,   697,  -642,  -641,     0,     0,   856,
    -642,     0,   856,   698,     0,  -641,  -646,  -556,  -646,  -642,
    -557,     0,     0,   700,  -556,   698,     0,  -557,  -643,     0,
    -643,     0,  -646,     0,   856,   700,     0,     0,     0,     0,
       0,     0,  -558,     0,  -643,  -556,   856,     0,  -557,  -558,
    -556,     0,     0,  -557,  -559,  -556,     0,   856,  -557,     0,
       0,  -559,     0,   856,  -556,  -560,     0,  -557,     0,   856,
    -558,  -551,  -560,     0,     0,  -558,     0,  -549,   628,     0,
    -558,     0,  -559,     0,  -549,     0,     0,  -559,     0,  -558,
       0,     0,  -559,  -560,     0,     0,     0,     0,  -560,   629,
       0,  -559,     0,  -560,  -551,  -549,   856,     0,   856,   631,
    -549,     0,  -560,     0,  -550,  -549,  -554,     0,  -551,  1256,
    1258,   628,  1260,   628,  -549,     0,     0,  1257,  1259,     0,
    1261,  1262,     0,  1264,   697,   697,     0,   697,     0,  1263,
       0,  1265,  -550,     0,   629,  1266,   697,  -550,   697,  -554,
       0,     0,  -550,  1267,   631,   698,   698,     0,   698,     0,
     697,  -550,     0,  -554,     0,   700,   700,   698,   700,   698,
    1268,     0,   889,     0,   889,   889,     0,   700,  1269,   700,
    1337,   698,  1339,  1342,     0,   697,   889,   697,   889,   697,
     697,   700,   889,     0,  1374,     0,  1375,   889,     0,     0,
    1377,   697,     0,   697,     0,  1381,   698,   697,   698,     0,
     698,   698,   697,     0,     0,     0,   700,     0,   700,     0,
     700,   700,   698,     0,   698,     0,     0,     0,   698,     0,
       0,     0,   700,   698,   700,     0,     0,     0,   700,     0,
       0,     0,     0,   700
  };

  const short int
  mcmas_parser::yycheck_[] =
  {
     233,   243,   312,   345,   100,   329,   447,   448,   447,   204,
     320,   206,   451,   506,   204,   508,   338,   339,   338,    71,
     202,    73,   342,    71,   246,   207,   447,   448,   472,   140,
      78,    26,   326,   116,    83,   116,    66,   148,   467,   542,
     543,   544,   733,    15,   268,   212,   270,   518,   721,   722,
     723,   480,   548,   549,   550,   746,   966,   172,   173,   174,
     727,   728,   729,   230,   956,   232,     1,    71,   212,    73,
       1,   244,   213,   214,     1,   338,   339,     8,   302,   190,
     253,    17,     1,   975,    23,    20,   230,    58,     1,    17,
       3,    28,    27,   111,    15,    66,   419,   149,   178,     7,
       8,   149,     1,     1,     1,   185,   186,    34,    27,     8,
       7,   163,   164,    85,     1,   457,   439,    40,     1,    46,
     115,   316,    15,     1,   564,     1,     1,    10,  1073,  1074,
      43,     7,     8,     1,    71,   187,    73,    20,     1,    17,
      77,    78,    17,    11,    27,   149,    44,    86,   200,    85,
      85,    86,   200,    40,    85,   266,   267,    85,   269,   163,
     164,   231,   277,   244,    85,  1075,   103,    86,   335,   336,
     253,     1,   253,     3,   407,   408,    15,    85,   411,   412,
     413,   414,   415,   416,   417,   527,    85,    17,    85,   531,
    1082,   335,   129,   130,   243,   118,   200,   338,   339,   279,
     341,   219,   220,    86,   222,   438,   448,    85,   450,    85,
      85,   241,   149,    43,   381,   537,   538,    85,   359,   360,
    1165,  1166,    85,     1,  1169,   519,   163,   164,     1,   471,
     282,   168,   169,   170,   282,   172,   173,   174,   175,   176,
     177,   178,    17,    17,     1,   467,    85,     0,   185,   186,
     187,   188,   189,   305,    11,    85,   929,   305,   480,     1,
     701,   313,   701,   200,   931,   313,     1,   204,   492,   493,
     241,   495,   713,   714,   537,   538,   213,   214,   282,   782,
     701,   471,   545,   974,   288,   289,     1,    17,   784,   733,
       1,     1,   713,   714,   735,     1,   735,   768,   769,     1,
     771,   305,   746,   724,    46,     7,   479,    85,    43,   313,
      85,    85,    85,   383,   735,   385,   745,   387,   388,   389,
     390,   391,   392,   393,     1,     1,     1,    25,    85,    27,
       7,    29,     7,   403,   271,    17,    46,    13,   275,    45,
     277,     1,   279,    63,   281,   282,     7,     7,  1293,  1294,
      70,   288,   289,   371,   372,    85,   523,    18,     1,     1,
       1,     1,   704,    61,    62,     7,   708,     8,   305,    17,
      85,    69,     1,   469,    85,    95,   313,   817,     7,     8,
     491,    42,   319,    85,   824,   825,   826,   827,   828,   829,
     830,   831,     7,    28,    34,     1,    39,    42,   479,   632,
     633,   338,   339,    85,   341,   342,   455,     1,    85,   642,
      85,    17,    44,     7,   555,   556,    17,    85,   138,   139,
     653,   654,   359,   360,    85,    85,     1,   147,     1,     1,
      45,   773,     7,     8,     7,     8,     8,    85,    73,   137,
      85,     6,    77,    85,    85,    17,    21,    22,     1,    21,
      22,    85,    27,    85,   687,    27,    85,    15,   691,   692,
     693,   694,   514,    38,   697,   698,   518,   700,   103,   791,
      85,   791,     1,    31,    39,   717,   718,   719,     7,    85,
     802,   803,     1,     1,    85,    15,     1,    40,     7,     1,
       8,    85,    67,    42,   736,   936,     8,   936,     1,    17,
      15,    31,     1,    21,    22,    17,     1,   948,   949,    27,
      85,    86,    85,    85,    86,   936,   957,   958,   957,   958,
       1,   591,   592,   745,   995,   996,    38,    85,   791,   599,
     974,    42,   756,   168,   169,   170,   957,   958,    41,   609,
     610,   736,    41,   738,    39,   265,   736,     1,   485,   486,
      31,     1,   489,   490,   624,    85,    85,   739,   628,   629,
       1,   631,    15,     1,    42,     1,    85,    85,    86,   204,
       8,     7,     8,    85,    85,     1,  1069,   514,    31,    17,
       6,   518,     1,    21,    22,    21,    22,     1,     7,    27,
      44,    27,    42,     1,     8,     1,    42,     3,    17,    35,
     537,   538,    38,    44,    85,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
       1,   558,    10,    42,     3,     1,   563,   564,     4,    67,
       1,    67,    85,     6,    42,     8,   271,     1,    17,    85,
     275,    14,   984,    16,   986,   969,   281,    85,    86,    85,
      86,  1072,  1073,  1074,   964,    69,    70,    71,    64,     1,
       1,    42,     1,     1,    43,     1,    85,     9,    18,     8,
       9,    42,     1,     9,    16,     1,    40,    16,    17,     1,
       1,   923,    21,    22,   319,   927,     1,     1,    27,    86,
       6,     5,    42,   935,    15,    37,    34,    23,    37,    38,
      39,    42,     1,    42,     1,    47,    85,    45,    46,     8,
      32,    40,    85,    12,    56,     1,   768,   769,    17,   771,
     768,   963,     8,    39,  1165,  1166,  1165,    42,    67,     1,
      66,    17,    68,    32,    33,    21,    22,     9,     1,    38,
      32,    27,     1,    40,  1165,  1166,    85,    86,  1169,    48,
      49,    50,    51,    52,    53,    54,    55,     1,    57,    58,
      59,    60,    21,    22,   768,   769,   961,     1,    27,    32,
      33,     1,    16,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    85,    82,    83,    84,    85,    17,    87,    23,
       1,    21,    22,    37,    66,     1,    68,    27,    42,    85,
      86,     1,    39,     9,    15,  1038,  1039,  1040,  1041,  1042,
    1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1051,  1052,
    1053,  1054,  1055,  1056,  1057,  1058,    85,    86,     6,  1171,
       8,   768,   769,     1,   771,     1,    14,     1,    16,     5,
      40,     9,     1,   780,     8,   782,    10,   784,    16,   786,
      25,     7,    27,   790,   791,    85,    86,    21,    22,     1,
      66,     1,    68,    27,     1,   802,   803,     7,     8,    37,
    1291,  1292,  1293,  1294,    38,  1296,   813,    17,   815,    47,
     817,    40,    41,    39,     1,    43,    61,   824,   825,   826,
     827,   828,   829,   830,   831,  1316,     1,  1318,    38,    41,
       1,    10,     1,    67,    41,     1,  1327,    85,    48,    49,
      50,    51,    52,    53,    54,    55,    42,    57,    58,    59,
      60,    85,    86,    40,    41,    21,    22,     6,    28,     8,
       1,    27,    10,    32,    33,    14,    41,    16,  1280,    40,
    1282,   993,   994,   995,   996,    85,     1,    87,  1018,  1019,
    1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,
    1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,     1,    40,
      41,    71,     1,    73,     1,     8,     1,    77,    78,     1,
       9,     1,     4,     1,    17,    40,     1,    16,     8,    85,
      86,     9,     1,     1,     9,     1,    14,    17,    16,    32,
      33,    21,    22,   103,  1237,    38,    85,    27,    37,  1242,
    1243,     1,    39,    42,    39,    48,    49,    50,    51,    52,
      53,    54,    55,     1,    57,    58,    59,    60,     1,    19,
      39,     1,    40,  1085,    40,  1087,  1378,  1270,  1271,  1272,
    1273,  1274,  1275,     1,  1277,    15,    36,    67,    66,   149,
      68,    66,    85,    68,    87,     1,   993,   994,   995,   996,
       5,     1,    40,   163,   164,    85,    86,    40,   168,   169,
     170,    41,   172,   173,   174,   175,   176,   177,   178,     1,
      15,    39,     0,     1,     1,   185,   186,   187,   188,   189,
       8,    31,     9,    39,    12,    62,    63,     1,    16,    17,
     200,     1,   421,   422,   204,  1338,     1,  1340,  1341,    31,
    1343,  1344,  1345,   213,   214,    19,    11,    17,   437,    37,
      38,    21,    22,     1,    42,     3,     1,    27,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,     1,    57,
      58,    59,    60,  1376,    19,    40,     9,     1,  1085,    66,
    1087,    68,     6,    16,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     1,    82,    83,    84,    85,     1,    87,
       1,   271,     1,     4,    37,   275,     9,   277,     1,   279,
       9,   281,   282,    16,    47,    85,    86,    16,   288,   289,
       1,     1,     3,    56,     1,    18,     9,     4,     8,     9,
       1,    32,    40,    41,    37,   305,    16,    17,    37,    42,
       1,    21,    22,   313,    15,     1,     1,    27,    47,   319,
      11,    34,     8,     9,     9,    32,    12,    37,    38,    39,
      16,    17,    42,    66,     1,    68,     1,     1,   338,   339,
       1,   341,   342,     1,   396,    85,    10,   399,    15,    40,
      15,    37,    38,    14,    40,    16,    42,    67,    16,   359,
     360,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    85,    86,     3,     1,    37,
       4,    66,     5,    68,    42,     1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,     1,    82,    83,    84,    85,
      16,    87,     8,     9,     1,     1,    12,     1,    32,     1,
      16,    17,     9,     1,     8,    39,     8,    85,    14,    16,
       8,    37,     1,    17,     1,     1,    42,    21,    22,    21,
      22,    37,    38,    27,    40,    27,    42,    16,    14,    16,
      37,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,     1,    11,     1,    37,     1,
      37,     3,     6,    42,    10,    42,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    67,    82,    83,    84,    85,
       1,    87,    85,   420,     1,    40,   423,    42,     1,    10,
       1,    85,    86,    85,    86,     1,     1,     1,    11,    16,
      11,     1,     8,     9,     1,     9,    11,     1,     8,    41,
      16,    17,     9,     7,   514,    21,    22,    14,   518,    16,
      37,    27,    12,    27,    28,    31,     1,    40,    85,    40,
      47,    37,    38,     1,     9,    40,    42,   537,   538,    56,
       8,    16,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,    85,   558,     1,
      85,    67,    37,   563,   564,    41,     8,     9,    11,    66,
      12,    68,    47,     1,    16,    17,     4,    32,    33,    85,
      86,    56,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    19,    82,    83,    84,    37,    38,    40,    40,    42,
      42,   175,   176,   177,    32,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     1,
     426,   427,   428,   429,   430,   431,    14,   433,    16,    11,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     1,
      82,    83,    84,    85,     1,    87,     8,     9,     1,     8,
      12,     8,     1,     1,    16,    17,     9,     1,    40,    85,
       8,    10,     1,    16,    21,    22,     1,     1,     1,     8,
      27,    15,    85,    21,    22,    37,    38,    85,    40,    27,
      42,    16,    16,    16,    37,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     1,
      32,    33,    37,    37,    37,     1,     8,    42,    42,    42,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    15,
      82,    83,    84,    85,    34,    87,     1,     1,    85,    86,
       1,    32,    33,     7,     1,    45,    46,    85,    86,     1,
      15,     8,     9,    85,    15,    12,    13,    14,    15,    16,
      17,     1,     1,    15,    21,    22,     1,    24,    25,    26,
      27,    28,    29,    30,     1,    10,    16,    16,   768,   769,
      37,   771,    39,    85,    41,    42,     9,    85,    15,     4,
     780,    85,   782,    16,   784,    85,   786,    37,    37,     1,
     790,   791,    42,    42,    19,     4,     8,     1,    65,    66,
      67,    68,   802,   803,     1,     9,     1,    32,    12,    13,
      19,    15,     7,   813,     1,   815,     3,   817,    85,    86,
      24,    25,    26,    32,   824,   825,   826,   827,   828,   829,
     830,   831,     1,    42,    44,     1,     1,    10,     1,     8,
       9,     7,     8,    12,     5,    10,     1,    16,    17,    10,
       1,    17,    15,    45,    15,    21,    22,    85,     9,     1,
      15,    27,    66,     1,    68,    31,     8,     9,    37,    38,
       8,    40,    38,    42,    16,    17,    27,    28,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     5,    32,    33,    37,    38,    10,    86,    41,
      42,    67,    15,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    40,    82,    83,    84,    85,     1,    87,    85,
      86,     1,     1,     7,     1,     1,     1,    85,     8,     8,
       1,     7,     9,     8,     9,    12,    13,    12,    15,    40,
      41,    16,    17,    85,    85,    16,     1,    24,    25,    26,
      27,    28,    29,    30,     9,   725,   726,    12,    13,  1013,
      15,  1015,    37,    38,    41,    40,    37,    42,    39,    24,
      25,    26,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   397,   398,    65,    66,
     401,    68,    85,   993,   994,   995,   996,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    40,    82,    83,    84,
      85,    66,    87,    68,    40,     1,     1,     1,     1,   546,
     547,     4,    85,     9,     8,     9,    12,    13,    12,    15,
       9,    16,    16,    17,    85,    18,    19,    16,    24,    25,
      26,    27,    28,    29,    30,     1,   730,   731,   732,    32,
      85,     1,    37,    37,    38,    41,    40,    42,    42,     9,
      16,    85,    47,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    27,    28,    65,
      66,    37,    68,    39,    85,  1085,    85,  1087,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,     1,    87,     8,     9,     1,    40,    12,    40,
       9,    40,    16,    17,     9,   551,   552,   553,   188,   189,
       3,    16,     1,    15,     1,   424,   425,    85,    27,    28,
       9,     8,     9,    37,    38,    41,    40,    16,    42,    16,
      17,    85,    37,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    85,    37,    41,
      37,    38,    85,    42,    85,    42,   434,   435,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    41,    87,     8,     9,     1,    66,    12,    68,
      41,    85,    16,    17,     9,    85,    85,    85,    85,    85,
      85,    16,     1,    40,     1,    40,    40,    40,    85,    40,
       9,     8,     9,    37,    38,    40,    40,    16,    42,    16,
      17,    40,    37,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    40,    37,    85,
      37,    38,    85,    42,    85,    42,    85,    85,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    85,    87,     8,     9,     1,    66,    12,    68,
      40,    85,    16,    17,     9,    85,    85,    85,     1,    85,
      85,    16,     1,    85,    85,    85,    58,    85,    85,    85,
       9,    85,    85,    37,    38,    85,    40,    16,    42,    86,
       9,     5,    37,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,   260,    37,    25,
      39,   253,   329,    42,     8,   251,   118,   245,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,     1,    87,     8,     9,     1,    66,    12,    68,
       9,   204,    16,    17,     9,   736,   969,    34,   105,   379,
     212,    16,     1,  1017,   588,   845,   403,   395,    27,    28,
       9,   432,    -1,    37,    38,    -1,    40,    16,    42,    -1,
      -1,    -1,    37,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,     1,    87,     8,     9,    -1,    66,    12,    68,
       9,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    27,    28,
       9,    -1,    -1,    37,    38,    -1,    40,    16,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    -1,    87,     8,     9,    12,    13,    12,    15,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    24,    25,
      26,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    -1,    -1,    37,    38,    -1,    40,    16,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    -1,    87,     8,     9,    -1,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    -1,    -1,    37,    38,    -1,    40,    16,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    -1,    87,     8,     9,    -1,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    -1,    -1,    37,    38,    -1,    40,    16,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    -1,    87,     8,     9,    -1,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    -1,    -1,    37,    38,    -1,    40,    16,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    -1,    87,     8,     9,    -1,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    -1,    -1,    37,    38,    -1,    40,    16,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    -1,    87,     8,     9,    -1,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    -1,    -1,    37,    38,    -1,    40,    16,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    -1,    87,     8,     9,    -1,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    -1,    -1,    37,    38,    -1,    40,    16,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    -1,    87,     8,     9,    -1,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    -1,    -1,    37,    38,    -1,    40,    16,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,     1,    87,    -1,     1,    -1,    -1,     7,     8,
      -1,     7,     8,    12,    -1,    -1,    -1,    16,    17,    -1,
      -1,    17,     4,     5,    -1,    21,    22,    -1,    10,     1,
      -1,    27,    -1,    15,    -1,    31,    -1,     9,    37,    38,
      -1,    -1,    38,    42,    16,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    39,    57,    58,
      59,    60,    -1,    -1,    -1,    37,    -1,    39,    -1,    -1,
      42,    67,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     1,    82,    83,    84,    85,     1,    87,    85,
      86,    -1,    -1,     7,     8,    -1,     1,    16,    12,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    16,    -1,    -1,    -1,    -1,     1,    -1,    37,     4,
       5,    -1,     7,    42,    38,    10,    11,    -1,    47,    -1,
      15,    -1,    37,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    47,    57,    58,    59,    60,    32,    -1,    -1,
      -1,    56,    -1,    -1,    39,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,     1,    87,    -1,     1,    -1,    -1,     7,     8,
      -1,     7,     8,    12,    -1,    -1,    -1,    -1,    17,    -1,
      -1,    17,    -1,    -1,    -1,    21,    22,     4,     5,     4,
      85,    27,    -1,    10,    11,    10,    11,     1,    15,    38,
      15,    -1,    38,     7,    19,    -1,    -1,    -1,    12,    48,
      49,    50,    51,    52,    53,    54,    55,    32,    57,    58,
      59,    60,    39,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      34,    67,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    46,    82,    83,    84,    85,     1,    87,    85,
      86,     1,     1,     7,     8,    -1,    -1,    -1,    12,     9,
       9,    -1,    -1,    17,    -1,    15,    16,    16,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,    -1,    -1,    38,    -1,    -1,    37,    37,    -1,
      -1,    -1,    42,    42,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    16,    87,     8,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    37,     4,     5,    -1,     7,    -1,    -1,
      10,    11,    -1,    47,    38,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    32,    57,    58,    59,    60,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,    16,    87,     8,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    17,    -1,    -1,     1,    -1,    -1,    -1,
      -1,     1,     1,    37,     9,    85,    -1,    -1,    -1,     9,
       9,    16,    -1,    47,    38,    -1,    16,    16,    -1,    -1,
      -1,    -1,    56,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    37,    57,    58,    59,    60,    37,    37,    -1,
      40,    41,    47,    42,    -1,    -1,    -1,    47,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,     1,    87,     8,    -1,    -1,    -1,    12,    -1,
       9,    -1,    -1,    17,    -1,    -1,     1,    16,    -1,    -1,
      -1,     1,     1,    -1,     9,    -1,    -1,    -1,    -1,     9,
       9,    16,    -1,    -1,    38,    -1,    16,    16,    37,    -1,
      -1,    -1,    -1,    42,    48,    49,    50,    51,    52,    53,
      54,    55,    37,    57,    58,    59,    60,    37,    37,    -1,
      40,    41,    47,    42,    -1,    -1,    -1,    47,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,     1,    87,     8,    -1,    -1,    -1,    12,    -1,
       9,    -1,    -1,    17,    -1,    -1,     1,    16,    -1,    -1,
      -1,     1,     1,    -1,     9,    -1,    -1,    -1,    -1,     9,
       9,    16,    -1,    -1,    38,    -1,    16,    16,    37,    -1,
      -1,    -1,    -1,    42,    48,    49,    50,    51,    52,    53,
      54,    55,    37,    57,    58,    59,    60,    37,    37,    -1,
      40,    41,    47,    42,    -1,    -1,    -1,    47,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,     1,    87,     8,    -1,    -1,    -1,    12,    -1,
       9,    -1,    -1,    17,    -1,    -1,     1,    16,    -1,    -1,
      -1,     1,     1,    -1,     9,    -1,    -1,    -1,    -1,     9,
       9,    16,    -1,    -1,    38,    -1,    16,    16,    37,    -1,
      -1,    -1,    -1,    42,    48,    49,    50,    51,    52,    53,
      54,    55,    37,    57,    58,    59,    60,    37,    37,    -1,
      40,    41,    47,    42,    -1,    -1,    -1,    47,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     1,    82,    83,
      84,    85,     1,    87,     8,    -1,    -1,    -1,    12,    -1,
       9,    -1,    -1,    17,    -1,    -1,     1,    16,    -1,    -1,
      -1,     1,     1,    -1,     9,    -1,    -1,    -1,    -1,     9,
       9,    16,    -1,    -1,    38,    -1,    16,    16,    37,    -1,
      -1,    -1,    -1,    42,    48,    49,    50,    51,    52,    53,
      54,    55,    37,    57,    58,    59,    60,    37,    37,    -1,
      40,    41,    47,    42,    -1,    -1,    -1,    47,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,     1,    87,     1,    -1,    -1,    -1,     7,     8,
      -1,    -1,     9,    -1,    -1,    -1,    -1,    16,    17,    16,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,     1,
      -1,    -1,    -1,     8,     9,    34,    -1,     9,    37,    38,
      37,    16,    17,    42,    16,    42,    -1,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    57,    58,
      59,    60,    37,    38,    -1,    37,    -1,    42,    -1,    -1,
      42,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    85,     1,    87,    -1,
      -1,    -1,    -1,     1,     8,     9,    -1,     5,     6,     7,
       8,    -1,    16,    17,    12,    13,    -1,    15,    16,    -1,
      85,    -1,    87,    21,    22,    -1,    24,    25,    26,    27,
      28,    29,    30,    37,    38,    -1,    -1,    35,    42,    37,
      38,    39,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    65,    66,    67,
      68,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    -1,    87,    -1,     1,    -1,    85,    86,    -1,
      34,    -1,    -1,    37,    38,    -1,    -1,    -1,    42,    -1,
      16,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,     1,    57,    58,    59,    60,    -1,     1,     8,
       9,    37,    -1,    -1,     7,     8,    42,    16,    17,    -1,
      -1,    47,    -1,    -1,    17,    -1,    -1,    -1,    21,    22,
      -1,    85,     1,    87,    27,    -1,    -1,    -1,    37,    38,
       9,    -1,    35,    42,    -1,    38,    -1,    16,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,     1,    -1,    -1,    -1,    37,     8,
       9,    -1,     9,    42,    67,    -1,    -1,    16,    17,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    85,     1,    87,     1,
      -1,    -1,    85,    86,    -1,     9,    -1,     9,    37,    38,
      37,    -1,    16,    42,    16,    42,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    37,    -1,    37,    40,    -1,     1,     8,
       9,    -1,    -1,    47,    -1,    47,     9,    16,    17,    12,
      13,    -1,    15,    -1,    -1,    -1,    85,    -1,    87,    -1,
      -1,    24,    25,    26,    27,    28,    -1,    -1,    37,    38,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,    -1,    -1,     1,    -1,     1,     8,
       9,    -1,    65,    66,     9,    68,     9,    16,    17,    12,
      13,    16,    15,    -1,    -1,    -1,    85,    -1,    87,    -1,
      -1,    24,    25,    26,    27,    28,    -1,    -1,    37,    38,
      -1,    -1,    37,    42,    -1,    -1,    -1,    42,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,    -1,    -1,     1,    -1,     1,     8,
       9,    -1,    65,    66,     9,    68,     9,    16,    17,    12,
      13,    16,    15,    -1,    -1,    -1,    85,    -1,    87,    -1,
      -1,    24,    25,    26,    27,    28,    -1,    -1,    37,    38,
      -1,    -1,    37,    42,    -1,    -1,    -1,    42,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,    -1,    -1,     1,    -1,     1,     8,
       9,    -1,    65,    66,     9,    68,     9,    16,    17,    12,
      13,    16,    15,    -1,    -1,    -1,    85,    -1,    87,    -1,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    37,    42,    -1,    -1,    -1,    42,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,    -1,    -1,     1,    -1,     1,     8,
       9,    -1,    -1,    66,     9,    68,     9,    16,    17,    12,
      13,    16,    15,    -1,    -1,    -1,    85,    -1,    87,    -1,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    37,    42,    -1,    -1,    -1,    42,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,    -1,    -1,     1,    -1,     1,     8,
       9,    -1,    -1,    66,     9,    68,     9,    16,    17,    12,
      13,    16,    15,    -1,    -1,    -1,    85,    -1,    87,    -1,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    37,    42,    -1,    -1,    -1,    42,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,    -1,    -1,     1,    -1,     1,     8,
       9,    -1,    -1,    66,     9,    68,     9,    16,    17,    12,
      13,    16,    15,    -1,    -1,    -1,    85,    -1,    87,    -1,
       1,    24,    25,    26,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    37,    42,    -1,    16,    -1,    42,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,    -1,    -1,    37,    -1,     1,     8,
       9,    42,    -1,    66,    -1,    68,    47,    16,    17,    12,
      13,    -1,    15,    -1,    -1,    -1,    85,    -1,    87,    -1,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,    -1,    -1,    -1,    -1,     1,     8,
       9,    -1,    -1,    66,    -1,    68,    -1,    16,    17,    12,
      13,    -1,    15,    -1,    -1,    -1,    85,    -1,    87,    -1,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,    -1,    -1,    -1,    -1,     1,     8,
       9,    -1,    -1,    66,    -1,    68,    -1,    16,    17,    12,
      13,    -1,    15,    -1,    -1,    -1,    85,    -1,    87,    -1,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
       9,    -1,    -1,    66,    -1,    68,    -1,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,     1,    87,     1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,     9,    37,    38,
      -1,    -1,    16,    42,    16,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    37,    -1,    37,    40,    41,    42,     8,
       9,    -1,    -1,    47,    -1,    47,    -1,    16,    17,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    85,     1,    87,     1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,     9,    37,    38,
      -1,    -1,    16,    42,    16,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    37,    -1,    37,    40,    41,    42,     8,
       9,    -1,    -1,    47,    -1,    47,    -1,    16,    17,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    85,     1,    87,     1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,     9,    37,    38,
      -1,    -1,    16,    42,    16,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    37,    -1,    37,    -1,    41,    42,     8,
       9,    -1,    -1,    47,    -1,    47,    -1,    16,    17,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    85,     1,    87,     1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,     9,    37,    38,
      -1,    -1,    16,    42,    16,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    37,    -1,    37,    40,    -1,    42,     8,
       9,    -1,    -1,    47,    -1,    47,    -1,    16,    17,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    85,     1,    87,     1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,     9,    37,    38,
      -1,    -1,    16,    42,    16,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     1,    37,    -1,    37,    40,    -1,    42,     8,
       9,    -1,    -1,    47,    -1,    47,    -1,    16,    17,    -1,
      -1,    -1,    56,    -1,    -1,     1,    85,    -1,    87,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    17,    -1,    42,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    57,    58,    59,    60,     1,    85,    -1,    87,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    -1,    -1,     1,    -1,    -1,    -1,     1,    85,
      -1,    87,     9,    -1,     7,     8,    -1,    -1,    -1,    16,
      -1,    -1,    38,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      37,    57,    58,    59,    60,    38,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,     1,    57,    58,    59,    60,    -1,    85,
       8,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,
       1,    -1,    85,    -1,    87,    -1,    -1,    17,     9,    -1,
      38,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    38,    57,
      58,    59,    60,    -1,    -1,    -1,    37,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    47,    57,    58,    59,
      60,    -1,    -1,     1,    -1,    -1,    -1,    85,     1,    87,
      -1,     9,     5,     6,     7,     8,    -1,    -1,    16,    12,
      13,    -1,    15,    16,    17,    85,    -1,    87,    21,    22,
      -1,    24,    25,    26,    27,    28,    29,    30,    -1,    37,
      -1,    -1,    35,    -1,    37,    38,    39,    -1,    41,    47,
       1,    -1,    -1,    -1,    -1,    -1,     7,     8,    -1,     1,
      -1,    -1,    -1,    -1,    -1,     7,     8,    -1,    -1,    -1,
      21,    22,    65,    66,    67,    68,    27,    -1,    -1,    21,
      22,    -1,    -1,     1,    35,    27,     4,    38,    -1,     7,
       8,    -1,    85,    86,    12,    13,    38,    15,    16,    17,
       1,    -1,    -1,    21,    22,    -1,    24,    25,    26,    27,
      28,    29,    30,    -1,    32,    16,    67,    -1,     1,    37,
      38,    -1,    -1,    41,    42,    67,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    85,    86,    37,    -1,    -1,    40,
      -1,    -1,    -1,    85,    86,    -1,    47,    65,    66,    67,
      68,     1,    -1,    -1,    37,     5,     6,     7,     8,    42,
      -1,    -1,    12,    13,    47,    15,    16,    85,    86,    -1,
      -1,    21,    22,    56,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,     1,    -1,    35,    -1,    37,    38,    39,
       8,     9,    -1,    -1,    12,    13,    -1,    15,    16,    17,
      -1,    -1,    -1,    21,    22,    -1,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    65,    66,    67,    68,    37,
      38,    39,    -1,    41,    42,     1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,     9,    -1,    85,    86,    -1,    -1,    -1,
      16,    17,    -1,    -1,     1,    21,    22,    65,    66,    67,
      68,    27,     9,    -1,    -1,    31,    -1,    -1,     1,    16,
      -1,    37,    38,    -1,     7,     8,    42,    85,    86,    12,
      13,    -1,    15,    16,    17,    -1,    -1,    -1,    21,    22,
      37,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      47,    67,    35,    -1,    37,    38,    39,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
       8,    -1,    65,    66,    67,    68,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    21,    22,    -1,    -1,     1,    -1,    27,
      -1,    -1,    85,    86,     8,     9,    10,    35,    12,    13,
      38,    15,    16,    17,     1,    -1,    -1,    21,    22,    -1,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    16,
       1,    -1,     1,    37,    38,    39,    -1,    41,     9,    67,
       9,    -1,    13,    -1,    -1,    16,    -1,    16,    -1,    -1,
      37,    -1,    -1,    40,    -1,    -1,    -1,    85,    86,    -1,
      47,    65,    66,    67,    68,    -1,    37,    -1,    37,    40,
      41,    42,     1,    -1,    -1,    -1,    47,    -1,    47,     8,
       9,    85,    86,    12,    13,    56,    15,    16,    17,    -1,
      -1,    -1,    21,    22,    -1,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,     1,    -1,    -1,     4,    37,    38,
       7,     8,    41,    42,    -1,    12,    13,    -1,    15,    16,
      -1,    -1,    -1,    -1,    21,    22,    -1,    24,    25,    26,
      27,    28,    29,    30,    -1,    32,    65,    66,    67,    68,
      37,    38,    -1,    -1,    -1,    42,     1,    -1,    -1,    -1,
      -1,    -1,     7,     8,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    17,    -1,    -1,     1,    21,    22,    65,    66,
      67,    68,    27,     9,    -1,    -1,    -1,     1,    -1,     1,
      16,    -1,    -1,    38,    -1,     9,     8,     9,    85,    86,
      12,    13,    16,    15,    16,    17,    -1,    -1,    -1,    21,
      22,    37,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    47,    67,    37,     1,    37,    38,    -1,    42,    41,
      42,     1,     9,    47,    -1,    -1,    -1,     7,     8,    16,
      85,    86,    56,    -1,    -1,    -1,    -1,    17,    -1,    -1,
      -1,    21,    22,    65,    66,    67,    68,    27,    -1,    -1,
      37,    -1,    -1,    40,     1,    -1,    -1,     1,    38,    -1,
      47,     8,     9,    85,    86,    12,    13,    14,    15,    16,
      17,     1,    16,    -1,    21,    22,     1,    24,    25,    26,
      27,    28,    29,    30,     9,    -1,    16,    67,    -1,    -1,
      37,    16,    39,    37,    41,    42,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    85,    86,    37,    -1,    -1,
      40,    -1,    37,    -1,    -1,    40,     1,    47,    65,    66,
       1,    68,    47,     8,    -1,    -1,    -1,     8,     9,    -1,
      -1,    12,    13,    -1,    15,    16,    21,    22,    85,    86,
      21,    22,    27,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,     1,    38,    -1,    -1,    37,    38,    39,     8,
       9,    42,    -1,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    21,    22,    -1,    24,    25,    26,    27,    28,
      29,    30,    67,    -1,    65,    66,    67,    68,    37,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    65,    66,    67,    68,
       1,    -1,    -1,     9,    -1,    -1,    -1,     8,     9,    10,
      16,    12,    13,    -1,    15,    16,    85,    86,    -1,    -1,
      21,    22,    -1,    24,    25,    26,    27,    28,    29,    30,
      -1,    37,     1,    -1,     1,     1,    37,    38,    39,     8,
       9,    47,     9,    12,    13,    -1,    15,    16,    17,    16,
      16,    -1,    21,    22,    -1,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    65,    66,    67,    68,    37,    -1,
      37,    37,    41,    42,    40,    42,    -1,    -1,    -1,    -1,
      47,    47,    -1,    -1,    85,    86,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
       1,    -1,    -1,    -1,    -1,    -1,    -1,     8,     9,    -1,
      -1,    12,    13,    -1,    15,    16,    85,    86,    -1,    -1,
      21,    22,    -1,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,     1,    -1,    -1,     1,    37,    38,    -1,     8,
       9,    42,    -1,    12,    13,    14,    15,    16,    17,    -1,
      16,    -1,    21,    22,     1,    24,    25,    26,    27,    28,
      29,    30,     9,    -1,    65,    66,    67,    68,    37,    16,
      39,    37,    -1,    42,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    40,    -1,    -1,    65,    66,     1,    68,
      47,    -1,    -1,    -1,    -1,     8,     9,    -1,    -1,    12,
      13,    14,    15,    16,    -1,    -1,    85,    86,    21,    22,
      -1,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
       1,    -1,    -1,    -1,    37,    -1,    39,     8,     9,    42,
      -1,    12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      21,    22,    -1,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,    65,    66,    -1,    68,    37,    -1,    39,    -1,
      -1,    42,     1,    -1,    -1,    -1,    -1,    -1,     7,     8,
      -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    17,    -1,
      -1,    -1,    21,    22,    65,    66,     1,    68,    27,    -1,
      -1,    -1,    -1,     8,     9,    -1,    -1,    12,    13,    38,
      15,    16,    17,    -1,    85,    86,    21,    22,    -1,    24,
      25,    26,    27,    28,    29,    30,    -1,     1,    -1,    -1,
      -1,    -1,    37,     7,     8,    -1,    41,    42,    67,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    22,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    85,    86,    -1,    -1,
      65,    66,     1,    68,    38,    -1,    -1,    -1,    -1,     8,
       9,    -1,    -1,    12,    13,    -1,    15,    16,    17,    -1,
      85,    86,    21,    22,    -1,    24,    25,    26,    27,    28,
      29,    30,    -1,    67,     1,    -1,    -1,    -1,    37,    -1,
      -1,     8,     9,    42,    -1,    12,    13,    14,    15,    16,
      17,    85,    86,    -1,    21,    22,    -1,    24,    25,    26,
      27,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,    68,
      37,    -1,    39,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,     1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
       9,    -1,    -1,    12,    13,    14,    15,    16,    85,    86,
      -1,    -1,    21,    22,    -1,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    37,    -1,
      39,     8,     9,    42,    -1,    12,    13,    -1,    15,    16,
      17,    -1,    -1,    -1,    21,    22,     1,    24,    25,    26,
      27,    -1,    -1,     8,     9,    -1,    65,    66,    67,    68,
      37,    16,    -1,    -1,    -1,    42,    21,    22,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    85,    86,     1,    -1,
      -1,    -1,    37,    38,    39,     8,     9,    42,    65,    66,
      67,    68,    -1,    16,    -1,    -1,    -1,    -1,    21,    22,
      -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    85,    86,
      -1,    -1,    67,     1,    37,    38,    39,    -1,    -1,    42,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,
      85,    86,    -1,    21,    22,    -1,    -1,    -1,     1,    27,
       1,    -1,    -1,    -1,    67,    -1,     9,     8,     9,    37,
      38,    -1,     1,    16,    42,    16,    17,    -1,     7,     8,
      21,    22,    85,    86,    -1,    -1,    27,    -1,    17,    -1,
      -1,    -1,    21,    22,    37,     1,    37,    38,    27,    67,
      -1,    42,     8,     9,    47,     1,    -1,    -1,    -1,    38,
      16,    -1,    -1,     9,    -1,    21,    22,    85,    86,    -1,
      16,    27,     1,    -1,    -1,    31,    67,    -1,    -1,     8,
       9,    37,    38,    -1,    -1,    -1,    42,    16,    67,     1,
      -1,    37,    21,    22,    85,    86,     1,     9,    27,    -1,
      -1,    47,    31,     8,    16,    10,    85,    86,    37,    38,
      -1,    67,    17,    42,    -1,    -1,    21,    22,    -1,    -1,
      -1,     1,    27,    -1,     1,    37,    -1,    -1,     8,    85,
      86,     8,    -1,    38,    -1,    47,    -1,    17,    67,    -1,
      17,    21,    22,    -1,    21,    22,     1,    27,     1,    -1,
      27,    31,    -1,     8,    -1,     8,    85,    86,    38,    -1,
      -1,    38,    67,    -1,    17,    -1,    21,    22,    21,    22,
      -1,     1,    27,    -1,    27,    -1,    31,    -1,    -1,     9,
      85,    86,     1,    38,    -1,    38,    16,    67,     7,     8,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,
      -1,    -1,    -1,     1,    -1,    85,    86,    37,    85,    86,
      -1,     9,    67,    -1,    67,    34,    -1,    47,    16,    38,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    -1,     1,
      85,    86,    85,    86,    -1,    -1,    -1,     9,    -1,    37,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,     1,    -1,    -1,    -1,    37,    85,    39,    -1,     9,
      42,    -1,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    65,    66,     1,    68,    37,    -1,    39,
      -1,    -1,    42,     9,    -1,    -1,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    29,    30,    65,    66,     1,    68,    -1,
      -1,    37,    -1,    39,    -1,     9,    42,    -1,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    65,
      66,     1,    68,    37,    -1,    39,    -1,    -1,    42,     9,
      -1,    -1,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    65,    66,     1,    68,    -1,    -1,    37,    -1,    39,
      -1,     9,    42,    -1,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    65,    66,     1,    68,    37,
      -1,    39,    -1,    -1,    42,     9,    -1,    -1,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    65,    66,     1,
      68,    -1,    -1,    37,    -1,    39,    -1,     9,    42,    -1,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    65,    66,     1,    68,    37,    -1,    39,    -1,    -1,
      42,     9,    -1,    -1,    12,    13,    -1,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,    30,    65,    66,    -1,    68,     1,     1,    37,
      -1,    -1,    -1,    41,    42,     9,     9,    -1,    12,    13,
      -1,    15,    16,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    65,    66,    -1,
      68,     1,    -1,    37,    37,    -1,    -1,    41,    42,     9,
      -1,    -1,    12,    13,    47,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    65,    66,    -1,    68,     1,    -1,    37,    -1,    -1,
      -1,    41,    42,     9,    -1,    -1,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    -1,    -1,    65,    66,     1,    68,    -1,
      -1,    37,    -1,    39,    -1,     9,    42,    -1,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    -1,    -1,    -1,    -1,    65,
      66,     1,    68,    37,    -1,    39,    -1,    -1,    42,     9,
      -1,    -1,    12,    13,    -1,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    65,    66,     1,    68,    -1,    -1,    37,    -1,    -1,
      -1,     9,    42,    -1,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    -1,    -1,    -1,    -1,    65,    66,     1,    68,    37,
      -1,    39,    -1,    -1,    42,     9,    -1,    -1,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    -1,    -1,    65,    66,     1,
      68,    -1,    -1,    37,    -1,    39,    -1,     9,    42,    -1,
      12,    13,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    65,    66,     1,    68,    37,    -1,    -1,    -1,    -1,
      42,     9,    -1,    -1,    12,    13,    -1,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,    30,    65,    66,     1,    68,    -1,    -1,    37,
      -1,    -1,    -1,     9,    42,    -1,    12,    13,    -1,    15,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    65,    66,     1,
      68,    37,    -1,    -1,    -1,    -1,    42,     9,    -1,    -1,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,    65,
      66,     1,    68,    -1,    -1,    37,    -1,    39,    -1,     9,
      42,    -1,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,     1,    68,    37,    -1,    39,
      -1,    -1,    42,     9,    -1,    -1,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,    65,    66,     1,    68,    -1,
      -1,    37,    -1,    39,    -1,     9,    42,    -1,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,     1,    68,    37,    -1,    39,    -1,    -1,    42,     9,
      -1,    -1,    12,    13,     1,    15,    16,    -1,    -1,    -1,
      -1,    -1,     9,    -1,    24,    25,    26,    27,    28,    16,
      -1,    65,    66,     1,    68,    -1,    -1,    37,    -1,    -1,
      -1,     9,    42,    -1,    12,    13,    14,    15,    16,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    -1,
      47,    -1,    -1,    -1,    -1,    65,    66,     1,    68,    37,
      -1,    39,    -1,    -1,    42,     9,    -1,    -1,    12,    13,
       1,    15,    16,    -1,    -1,    -1,    -1,    -1,     9,    -1,
      24,    25,    26,    27,    28,    16,    -1,    65,    66,     1,
      68,    -1,    -1,    37,    -1,    -1,    -1,     9,    42,    -1,
      12,    13,    14,    15,    16,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    -1,    47,    -1,    -1,    -1,
      -1,    65,    66,     1,    68,    37,    -1,    39,    -1,    -1,
      42,     9,    -1,    -1,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    -1,
      -1,    -1,    -1,    65,    66,     1,    68,    -1,    -1,    37,
      -1,    39,    -1,     9,    42,    -1,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,     1,
      68,    37,    -1,    39,    -1,    -1,    42,     9,    -1,    -1,
      12,    13,     1,    15,    16,    -1,    -1,    -1,    -1,    -1,
       9,    -1,    24,    25,    26,    -1,    -1,    16,    -1,    65,
      66,     1,    68,    -1,    -1,    37,    -1,    -1,    -1,     9,
      42,    -1,    12,    13,    -1,    15,    16,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    -1,    47,    -1,
      -1,    -1,    -1,    65,    66,     1,    68,    37,    -1,    -1,
      -1,    -1,    42,     9,    -1,    -1,    12,    13,     1,    15,
      16,    -1,    -1,    -1,    -1,    -1,     9,    -1,    24,    25,
      26,    -1,    -1,    16,    -1,    65,    66,     1,    68,    -1,
      -1,    37,    -1,    -1,    -1,     9,    42,    -1,    12,    13,
      -1,    15,    16,    -1,    37,    -1,    -1,    -1,    -1,     1,
      24,    25,    26,    -1,    47,    -1,    -1,     9,    -1,    65,
      66,    13,    68,    37,    16,    -1,     1,     1,    42,    -1,
      -1,    -1,    -1,    -1,     9,     9,    -1,    -1,     1,    -1,
      -1,    16,    16,    -1,    -1,    37,     9,    -1,    40,    41,
      42,    65,    66,    16,    68,    47,    -1,    -1,    -1,    -1,
      -1,     1,    37,    37,    56,    40,    40,    42,    42,     9,
      -1,    -1,    47,    47,    37,    -1,    16,    40,    -1,    42,
      -1,    56,    56,     1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    -1,    56,    -1,     1,     1,    37,    16,    -1,
      40,    -1,    42,     9,     9,    -1,    -1,    47,    -1,    -1,
      16,    16,     1,     1,    -1,    -1,    56,    -1,    -1,    37,
       9,     9,    40,    -1,    42,     1,    -1,    16,    16,    47,
      -1,    37,    37,     9,    40,    40,    42,    42,    56,    -1,
      16,    47,    47,    -1,    -1,     1,    -1,    -1,    37,    37,
      56,    56,    40,     9,    42,    -1,    -1,     1,    47,    47,
      16,    37,    -1,    -1,    40,     9,    42,    -1,    56,    -1,
       1,    47,    16,    -1,     1,    -1,    -1,    -1,     9,    -1,
      56,    37,     9,    -1,    40,    16,    42,     1,    -1,    16,
      -1,    47,    -1,    37,    -1,     9,    40,    -1,    42,     1,
      56,    -1,    16,    47,    -1,    -1,    37,     9,    -1,    40,
      37,    42,    56,    40,    16,    42,    47,    -1,    -1,     1,
      47,    -1,     1,    37,    -1,    56,    40,     9,    42,    56,
       9,    -1,    -1,    47,    16,    37,    -1,    16,    40,    -1,
      42,    -1,    56,    -1,     1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    -1,    56,    37,     1,    -1,    37,    16,
      42,    -1,    -1,    42,     9,    47,    -1,     1,    47,    -1,
      -1,    16,    -1,     1,    56,     9,    -1,    56,    -1,     1,
      37,     9,    16,    -1,    -1,    42,    -1,     9,    16,    -1,
      47,    -1,    37,    -1,    16,    -1,    -1,    42,    -1,    56,
      -1,    -1,    47,    37,    -1,    -1,    -1,    -1,    42,    37,
      -1,    56,    -1,    47,    42,    37,     1,    -1,     1,    47,
      42,    -1,    56,    -1,     9,    47,     9,    -1,    56,     1,
       1,    16,     1,    16,    56,    -1,    -1,     9,     9,    -1,
       9,     1,    -1,     1,    16,    16,    -1,    16,    -1,     9,
      -1,     9,    37,    -1,    37,     1,    16,    42,    16,    42,
      -1,    -1,    47,     9,    47,    37,    37,    -1,    37,    -1,
      16,    56,    -1,    56,    -1,    47,    47,    37,    47,    37,
       1,    -1,     1,    -1,     1,     1,    -1,    47,     9,    47,
       9,    37,     9,     9,    -1,    16,     1,    16,     1,    16,
      16,    47,     1,    -1,     9,    -1,     9,     1,    -1,    -1,
       9,    16,    -1,    16,    -1,     9,    37,    16,    37,    -1,
      37,    37,    16,    -1,    -1,    -1,    47,    -1,    47,    -1,
      47,    47,    37,    -1,    37,    -1,    -1,    -1,    37,    -1,
      -1,    -1,    47,    37,    47,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    47
  };

  const unsigned char
  mcmas_parser::yystos_[] =
  {
       0,     1,     3,    64,    89,    90,    91,    92,    94,   119,
     120,   122,    17,     1,    17,    15,     0,     1,    91,     1,
       4,    18,    19,    32,    95,    97,   102,   104,   106,   108,
     127,   129,     1,     3,   119,     1,    43,   122,   178,   180,
      85,    62,    63,    10,    15,    39,     1,    15,     1,    39,
       1,    39,     1,    39,     1,     7,    85,    96,    98,    99,
       1,   104,   108,   129,     1,     7,    98,   103,     1,   108,
     129,     1,     7,     8,    21,    22,    27,    38,    67,    85,
      86,   101,   107,   110,   147,   149,   150,   151,   152,   153,
     154,   155,   173,   174,     1,   129,     1,    11,    85,   128,
     131,     1,     5,   132,   134,   180,     1,    85,   181,     1,
      44,   183,   185,     1,    36,   102,   105,   123,   125,    42,
      42,     1,    10,    10,     1,    10,    18,     1,    18,     1,
      39,     1,    96,    99,     1,    42,    39,   108,   129,   129,
     134,    19,     1,    19,     1,   103,    39,   129,   134,     1,
      32,    86,   147,   149,   152,   155,     1,    32,   147,   149,
     152,    86,   147,     1,     8,   155,     1,   107,     1,    16,
      37,    42,     1,    27,    28,     1,    29,    30,     1,    12,
      13,    15,    24,    25,    26,    66,    68,   171,     1,    65,
     134,    42,     1,    42,     1,    40,   128,    39,     1,    39,
       1,     7,    35,   133,   136,   140,   142,   147,     1,     6,
     112,   114,   185,     1,    14,     1,     7,    85,   179,     1,
       8,    17,    38,    85,   186,     1,    34,    45,    46,   187,
     189,   195,   197,   203,   205,    10,    15,    39,     1,    15,
       1,    98,     1,   106,   109,   127,   130,     1,    11,    85,
     124,   126,     1,   105,     1,    20,    85,   100,   101,     1,
      10,    20,   101,     1,    42,   129,   134,   134,   114,   134,
     114,     1,     9,     9,     9,     1,     9,     1,     9,     1,
       9,     1,     1,   152,   152,   147,   147,   147,     1,     8,
     150,   150,   150,   151,   151,   151,   153,   153,   153,   152,
     154,   154,   114,    85,    85,     1,     5,    39,   138,     1,
       5,     1,   138,     1,   133,   140,   142,     1,   133,     1,
     138,    39,     1,    39,     1,     7,     8,    85,   113,   115,
     116,   117,     1,     7,    93,   189,   197,   205,     1,     8,
      17,    38,    67,    85,   101,   160,   161,   162,   163,   167,
     168,   169,   174,   176,   182,   182,    43,     1,    43,     1,
      14,    41,    85,   186,   186,     1,    41,   186,     1,    41,
       1,    16,    37,    42,   184,     1,     7,    85,   188,   192,
       1,   197,   205,     1,     7,     8,    17,    38,    48,    49,
      50,    51,    52,    53,    54,    55,    57,    58,    59,    60,
      85,    87,   196,   198,   202,     1,   205,     1,     8,    12,
      17,    38,    48,    49,    50,    51,    52,    53,    54,    55,
      57,    58,    59,    60,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    82,    83,    84,    85,    87,   206,   207,
     215,     1,    10,    10,     1,    10,   103,     1,     8,    17,
      38,    67,    85,   101,   107,   111,   148,   156,   157,   158,
     159,   164,   165,   166,   174,   175,     1,   130,     1,   131,
       1,   132,   135,    42,     1,    42,     1,    40,   124,   109,
     130,    86,     1,    11,    40,     1,    23,     1,   100,     1,
      23,   134,   114,   114,    93,   114,    93,   149,   149,    93,
      10,     1,    10,     1,    85,   143,   143,   133,   143,     6,
       1,     6,     1,   117,    15,     1,   113,   116,    14,    16,
       3,     1,     3,   197,   205,   205,    41,   160,   163,   167,
     182,   160,   167,   182,     1,    41,   182,     1,     8,   163,
       1,    41,     1,    66,    68,   171,     1,    65,     1,    27,
      28,     1,    29,    30,     1,    16,    37,    42,     1,    42,
     182,   182,    85,     1,    15,     1,     9,     1,     9,    85,
      85,     1,    85,    85,     7,    44,   186,   186,   186,     1,
       7,    45,     1,    45,     1,    15,   190,     1,    85,   188,
     205,     1,     8,    34,   200,   201,   202,     1,    34,     1,
     202,    41,   202,   202,   202,   202,   202,   202,   202,     1,
       8,   199,   199,     1,     8,   200,     1,     8,   201,   201,
     200,     1,    41,   201,     1,   196,   202,     1,    16,    37,
      42,    47,     1,     8,    85,   209,   210,   211,   212,   213,
     214,   215,     1,   215,    85,    41,   215,   215,   215,   215,
     215,   215,   215,     1,     8,   208,   208,     1,     8,   209,
       1,     8,   210,   210,   209,     1,     8,   211,   211,     1,
       8,   213,   213,   213,   213,   213,   213,     8,   212,   213,
       1,     8,   214,   214,     1,    41,   210,     1,     7,   204,
     215,     1,    69,    70,    71,   208,     1,    16,    37,    42,
      47,     1,    41,   148,   156,   159,   164,   148,   156,   164,
       1,    41,   148,     1,     8,   159,   107,     1,    16,    37,
      42,     1,    66,    68,   171,     1,    65,     1,    27,    28,
       1,    29,    30,   135,   128,     1,   137,   141,   142,   148,
       1,   112,   144,    85,    85,   130,   135,    85,    85,     1,
     101,   101,     1,    11,   101,   101,   114,    93,    93,    93,
       1,    11,    40,   139,   139,   139,     9,   152,     1,     8,
      31,    38,    85,   152,   170,   117,   205,    85,     9,     9,
       1,     9,     1,     9,     1,     9,     1,     9,    85,    85,
       1,     1,   160,   160,    85,    85,   161,   161,   161,   160,
     162,   162,     1,     8,   168,   168,   168,   169,   169,   169,
     182,   182,   182,     1,    42,     1,    42,     1,    85,   101,
     174,   177,    85,   177,     1,    15,     1,    15,     1,    15,
       1,    15,     1,    44,    44,     1,    44,    10,     1,    10,
       1,    17,    85,   193,   194,   190,    17,    85,    17,    85,
       1,     9,     1,     9,    32,    33,     1,   202,   202,    17,
      85,    17,    85,    85,    85,    32,    33,     1,    32,    33,
       1,    42,   202,   202,   202,   202,    17,    85,    17,    85,
      13,     1,     9,     1,     9,     1,    13,    32,    33,     1,
     215,   215,    17,    85,    17,    85,    85,    85,    17,    85,
      17,    85,    85,    85,    32,    33,     1,    32,    33,    46,
       1,    46,     1,    42,   215,   215,   215,   215,   215,   215,
     215,   215,    85,     1,     9,     9,     9,     1,     9,     1,
       9,     1,     9,    85,    85,     1,     1,   156,   156,   148,
     148,   148,   157,   157,   157,   156,   158,   158,     1,     8,
     165,   165,   165,   166,   166,   166,   144,     1,     1,   133,
     141,   142,   133,     1,   138,     1,     8,    85,   118,   145,
     146,     1,     7,   121,   135,   144,    93,    42,    85,     1,
      42,    85,    15,    85,   152,   170,   152,   170,     1,    15,
     170,     1,    41,   171,     1,    16,    37,    42,   167,   167,
     177,   177,   177,   177,    17,    85,   177,   177,   177,   177,
      17,    85,   177,     1,    11,    40,   191,   193,     1,    40,
       1,    40,     1,    40,     1,    40,     1,    56,     1,    56,
       1,    40,     1,    40,     1,    40,     1,    40,     1,    40,
       1,    40,     1,    40,     1,    40,     1,    56,     1,    56,
       1,    40,    40,     1,    40,     1,    40,     1,    40,    40,
      40,    40,    40,    40,    40,   164,   164,   121,   133,   143,
       1,   118,    15,     1,    14,    16,     1,   113,   146,     3,
       1,     3,   144,   121,    85,     1,     9,     1,     9,    85,
      85,    15,    31,    85,     1,    31,   152,   170,   170,   170,
      41,    41,    41,    41,     1,    42,   194,     1,    42,   194,
     191,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   215,   215,   215,   215,   215,    85,   215,   215,    17,
      85,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,    85,    17,    85,    85,    17,    85,
      85,    85,   139,     9,   156,     1,     8,    17,    31,    38,
      85,   156,   172,   172,   118,   121,    85,     1,    15,    15,
      85,     1,    15,    85,    85,    85,    85,     1,     9,     1,
       9,     1,     9,     1,     9,     1,     9,     1,     9,     1,
       9,     1,     9,     1,     9,     1,     9,     1,     9,     1,
       9,     1,     9,     1,     9,     1,     9,     1,     9,     1,
       9,     1,     9,     1,     9,     1,     9,     1,     9,     1,
       9,     1,     9,     1,     9,     1,     9,    40,     1,     9,
       1,     9,    40,    40,     1,     9,     1,     9,     1,     9,
       1,     9,     1,     9,     1,     9,     1,     9,     1,     9,
       1,     9,     1,     9,     1,     9,     1,     9,     1,     9,
      40,    40,    40,    40,    40,    40,    40,    40,    15,    85,
     156,   172,   156,   172,     1,    41,     1,    15,   172,     1,
      41,   171,     1,    16,    37,    42,     1,    42,    85,    85,
      85,    85,    85,   215,   215,    85,   215,   215,   215,   215,
     215,   215,   215,    85,   215,    85,     1,     9,     1,     9,
      15,    31,    85,     1,    31,    85,    85,     1,    15,    31,
      85,     1,    31,   156,   172,   172,   172,     9,    40,     9,
      40,    40,     9,    40,    40,    40,    85,     1,    15,    85,
       1,    15,    85,     1,    15,    15,    85,     1,    15,   215,
     215,   215,   215,   215,   215,    85,    85,    85,    85,    85,
      85,    85,    85,    85,     9,     9,    40,     9,    40,   215,
     171,     9,    86,     9
  };

  const unsigned char
  mcmas_parser::yyr1_[] =
  {
       0,    88,    89,    89,    90,    90,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    92,    92,    92,    92,    93,
      93,    93,    93,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    95,    95,    95,    95,    96,    96,    96,    96,
      97,    97,    98,    98,    98,    98,    98,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,   100,
     100,   100,   100,   101,   101,   101,   101,   102,   102,   102,
     102,   103,   103,   103,   103,   104,   104,   104,   105,   105,
     106,   106,   106,   106,   107,   107,   107,   107,   108,   108,
     108,   109,   109,   109,   110,   110,   110,   111,   111,   111,
     112,   112,   112,   112,   113,   113,   113,   113,   114,   114,
     115,   115,   115,   116,   116,   117,   117,   117,   117,   118,
     118,   118,   118,   119,   119,   119,   120,   120,   121,   121,
     121,   121,   122,   122,   122,   122,   122,   123,   123,   123,
     123,   123,   123,   123,   123,   124,   124,   124,   124,   125,
     125,   125,   126,   126,   126,   126,   127,   127,   127,   127,
     127,   127,   127,   127,   128,   128,   128,   128,   129,   129,
     129,   130,   130,   131,   131,   131,   131,   132,   132,   132,
     132,   133,   133,   133,   133,   134,   134,   134,   134,   134,
     135,   135,   135,   135,   136,   136,   136,   137,   137,   137,
     138,   138,   138,   138,   139,   139,   139,   139,   140,   140,
     141,   141,   142,   142,   143,   143,   143,   143,   144,   144,
     145,   145,   145,   146,   146,   146,   146,   146,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     149,   149,   149,   149,   150,   150,   150,   150,   151,   151,
     151,   151,   152,   152,   152,   152,   153,   153,   153,   154,
     154,   154,   155,   155,   155,   155,   156,   156,   156,   156,
     157,   157,   157,   158,   158,   158,   159,   159,   159,   159,
     160,   160,   160,   160,   161,   161,   161,   162,   162,   162,
     163,   163,   163,   163,   164,   164,   164,   164,   165,   165,
     165,   165,   166,   166,   166,   166,   167,   167,   167,   167,
     168,   168,   168,   168,   169,   169,   169,   169,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   171,   171,   171,   171,   171,   171,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   173,   173,   173,
     174,   174,   175,   175,   175,   175,   175,   175,   176,   176,
     176,   176,   176,   176,   176,   176,   177,   177,   177,   178,
     179,   179,   179,   179,   180,   180,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   183,   183,   184,   184,
     184,   184,   184,   184,   184,   184,   185,   185,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   187,   187,   188,   188,   188,   188,   189,
     189,   189,   190,   190,   190,   190,   191,   191,   191,   191,
     192,   192,   192,   193,   193,   193,   193,   194,   194,   194,
     195,   195,   196,   196,   196,   196,   197,   197,   198,   198,
     198,   198,   198,   199,   199,   199,   199,   199,   199,   199,
     199,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   201,   201,   201,
     201,   201,   201,   201,   201,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   203,
     203,   204,   204,   204,   204,   205,   206,   206,   206,   206,
     206,   207,   207,   207,   208,   208,   208,   208,   208,   208,
     208,   208,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   210,   210,
     210,   210,   210,   210,   210,   210,   211,   211,   211,   211,
     212,   213,   213,   213,   213,   214,   214,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215
  };

  const unsigned char
  mcmas_parser::yyr2_[] =
  {
       0,     2,     1,     2,     4,     4,     1,     7,     6,     6,
       5,     6,     5,     5,     4,     2,     2,     2,     1,     2,
       2,     2,     1,     8,     7,     7,     6,     7,     6,     6,
       5,     1,     2,     2,     2,     1,     2,     2,     2,     1,
       3,     2,     2,     2,     3,     3,     1,     3,     3,     3,
       5,     5,     5,     5,     5,     4,     5,     4,     1,     1,
       3,     3,     1,     1,     2,     2,     1,     2,     2,     2,
       1,     2,     2,     2,     1,     3,     2,     1,     3,     1,
       2,     2,     2,     1,     2,     2,     2,     1,     3,     2,
       1,     3,     2,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     2,     1,     2,     2,     2,     1,     3,     2,
       1,     2,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     3,     1,     1,     2,     1,     1,     1,     2,     2,
       2,     1,     8,     7,     9,     8,     1,     3,     3,     3,
       3,     2,     2,     3,     1,     2,     2,     2,     1,     3,
       2,     1,     1,     3,     3,     1,     3,     3,     3,     3,
       2,     2,     3,     1,     2,     2,     2,     1,     3,     2,
       1,     3,     1,     1,     3,     3,     1,     2,     2,     2,
       1,     2,     2,     2,     1,     3,     4,     3,     2,     1,
       3,     4,     3,     1,     1,     2,     1,     1,     2,     1,
       2,     2,     2,     1,     2,     2,     2,     1,     4,     1,
       4,     1,     4,     4,     1,     3,     3,     1,     3,     1,
       1,     2,     1,     4,     4,     4,     4,     1,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     3,     1,
       3,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     1,     2,
       2,     1,     3,     3,     3,     1,     3,     3,     3,     1,
       3,     3,     1,     2,     2,     1,     3,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     1,     2,     2,     1,
       3,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     3,     3,     3,
       3,     2,     5,     5,     5,     5,     4,     4,     5,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     3,     3,     3,
       2,     5,     5,     5,     5,     4,     4,     5,     3,     5,
       5,     5,     4,     4,     5,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     1,     1,     1,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       2,     2,     2,     1,     3,     1,     4,     4,     4,     4,
       5,     5,     5,     5,     1,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     1,     1,     1,     3,     3,
       3,     3,     2,     2,     3,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     7,     7,     7,
       5,     5,     5,     5,     7,     5,     5,     5,     5,     4,
       5,     4,     1,     1,     1,     2,     2,     2,     1,     3,
       2,     1,     2,     2,     2,     1,     2,     2,     2,     1,
       4,     5,     1,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     1,     2,     3,     2,     2,
       3,     3,     1,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     2,     2,     2,     1,     3,     2,     2,     3,     3,
       1,     3,     3,     3,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     7,     7,     7,     1,
      11,     9,     9,     9,     1,    12,     1,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     3,     3,     3,     3,     3,     3,
       3,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const mcmas_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "AGENT", "ACTIONS",
  "PROTOCOL", "EVOLUTION", "END", "LB", "RB", "LCB", "RCB", "LT", "GT",
  "IF", "EQ", "AND", "ENVIRONMENT", "OBSVARS", "VARS", "BOOLEAN", "BTRUE",
  "BFALSE", "TO", "LE", "GE", "NEQ", "MINUS", "PLUS", "TIMES", "DIVIDE",
  "ACTION", "REDSTATES", "GREENSTATES", "FAIRNESS", "OTHER", "LOBSVARS",
  "OR", "NOT", "COLON", "COMMA", "DOT", "SEMICOLON", "EVALUATION",
  "INITSTATES", "GROUPS", "FORMULAE", "IMPLIES", "AG", "EG", "AX", "EX",
  "AF", "EF", "A", "E", "UNTIL", "K", "GK", "GCK", "O", "D",
  "MULTIASSIGNMENT", "SINGLEASSIGNMENT", "SEMANTICS", "BITAND", "BITOR",
  "BITNOT", "BITXOR", "X", "F", "G", "SC", "FU", "SCC", "WCC", "FUW",
  "FUS", "CAS", "RES", "DES", "ASS", "TR", "TP", "TC", "\"identifier\"",
  "\"number\"", "DK", "$accept", "eis", "semantics", "is", "envprefix",
  "envsuffix", "environment", "obsprefix", "obssuffix", "obsvardef",
  "varidlist", "onevardef", "enumlist", "integer", "varprefix",
  "varsuffix", "envardef", "vardef", "redprefix", "redsuffix", "enreddef",
  "reddef", "enrboolcond", "rboolcond", "evprefix", "evsuffix", "envevdef",
  "envevdeflist", "envevline", "boolresult", "boolresult1", "agents",
  "agprefix", "agsuffix", "agent", "lobsprefix", "lobssuffix",
  "lobsvarsdef", "lobsvaridlist", "actprefix", "actsuffix", "enactiondef",
  "actiondef", "actionidlist", "protprefix", "protsuffix", "enprotdef",
  "protdef", "enprotdeflist", "protdeflist", "plprefix", "plsuffix",
  "enprotline", "protline", "otherbranch", "enabledidlist", "evdef",
  "evdeflist", "evline", "enlboolcond", "lboolcond", "expr1", "term1",
  "element1", "expr4", "term4", "factor4", "element4", "expr5", "term5",
  "factor5", "element5", "expr6", "term6", "factor6", "element6", "expr2",
  "term2", "element2", "expr3", "term3", "element3", "eboolcond",
  "logicop", "gboolcond", "varvalue1", "boolvalue", "varvalue2",
  "varvalue3", "varvalue4", "evaprefix", "evasuffix", "evaluation",
  "evalist", "evaboolcond", "iniprefix", "inisuffix", "istates",
  "isboolcond", "groupprefix", "groupsuffix", "groups", "gplprefix",
  "gplsufffix", "groupdeflist", "namelist", "agentname", "fairprefix",
  "fairsuffix", "fairness", "fformlist", "untilprefixfair",
  "epistemicprefixfair", "gepistemicprefixfair", "fformula", "forprefix",
  "forsuffix", "formulae", "formlist", "atlprefix", "untilprefix",
  "epistemicprefix", "gepistemicprefix", "scprefix", "sccprefix2",
  "sccprefix", "gtprefix", "formula", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  mcmas_parser::yyrline_[] =
  {
       0,   277,   277,   278,   281,   284,   287,   292,   293,   294,
     295,   296,   303,   310,   317,   327,   330,   334,   338,   342,
     345,   349,   353,   358,   365,   372,   379,   386,   393,   400,
     408,   416,   421,   424,   428,   432,   436,   439,   443,   447,
     451,   457,   465,   475,   480,   492,   498,   503,   516,   521,
     526,   542,   547,   552,   557,   570,   576,   582,   588,   592,
     600,   611,   617,   621,   624,   627,   631,   637,   640,   644,
     648,   652,   655,   659,   663,   667,   673,   681,   687,   693,
     699,   702,   706,   710,   714,   717,   721,   725,   730,   736,
     739,   744,   750,   753,   758,   761,   766,   771,   774,   779,
     786,   789,   793,   797,   801,   804,   808,   812,   816,   822,
     828,   835,   842,   846,   852,   856,   859,   868,   884,   889,
     892,   901,   917,   922,   928,   937,   941,   944,   948,   951,
     955,   959,   964,   978,   992,  1006,  1020,  1026,  1029,  1033,
    1037,  1041,  1045,  1049,  1053,  1057,  1060,  1064,  1068,  1072,
    1078,  1081,  1085,  1101,  1117,  1123,  1130,  1133,  1137,  1141,
    1145,  1149,  1153,  1157,  1161,  1164,  1168,  1172,  1176,  1182,
    1188,  1194,  1200,  1204,  1212,  1222,  1228,  1235,  1238,  1242,
    1246,  1250,  1253,  1257,  1261,  1266,  1272,  1280,  1288,  1294,
    1300,  1306,  1314,  1322,  1327,  1334,  1341,  1346,  1353,  1360,
    1365,  1368,  1372,  1376,  1380,  1383,  1387,  1391,  1395,  1401,
    1406,  1412,  1417,  1423,  1429,  1437,  1447,  1453,  1460,  1466,
    1470,  1477,  1484,  1489,  1495,  1501,  1507,  1513,  1518,  1521,
    1526,  1531,  1536,  1542,  1548,  1554,  1560,  1565,  1572,  1577,
    1580,  1585,  1590,  1595,  1601,  1607,  1613,  1619,  1624,  1631,
    1636,  1642,  1648,  1653,  1656,  1662,  1668,  1673,  1676,  1679,
    1684,  1689,  1693,  1699,  1705,  1710,  1713,  1719,  1724,  1727,
    1733,  1738,  1741,  1744,  1749,  1754,  1758,  1764,  1770,  1775,
    1778,  1784,  1789,  1792,  1798,  1803,  1806,  1809,  1814,  1819,
    1823,  1829,  1835,  1840,  1843,  1849,  1854,  1857,  1863,  1868,
    1871,  1874,  1879,  1884,  1888,  1894,  1900,  1905,  1908,  1914,
    1920,  1925,  1928,  1931,  1936,  1941,  1944,  1950,  1956,  1961,
    1964,  1970,  1976,  1981,  1984,  1987,  1992,  1997,  2003,  2006,
    2011,  2016,  2021,  2027,  2033,  2039,  2045,  2050,  2057,  2074,
    2079,  2084,  2089,  2131,  2137,  2143,  2149,  2155,  2161,  2167,
    2173,  2178,  2181,  2184,  2187,  2190,  2193,  2198,  2201,  2206,
    2211,  2216,  2222,  2228,  2234,  2240,  2245,  2252,  2269,  2274,
    2279,  2284,  2315,  2321,  2327,  2333,  2339,  2345,  2351,  2357,
    2374,  2379,  2384,  2389,  2394,  2399,  2404,  2410,  2413,  2423,
    2426,  2429,  2433,  2436,  2446,  2465,  2470,  2475,  2478,  2481,
    2491,  2523,  2529,  2548,  2553,  2558,  2562,  2565,  2575,  2580,
    2583,  2586,  2590,  2594,  2598,  2599,  2603,  2609,  2614,  2619,
    2624,  2632,  2637,  2642,  2647,  2651,  2654,  2659,  2664,  2669,
    2675,  2681,  2686,  2692,  2697,  2704,  2712,  2715,  2719,  2722,
    2726,  2730,  2734,  2738,  2742,  2746,  2750,  2754,  2758,  2761,
    2766,  2771,  2776,  2782,  2788,  2793,  2799,  2804,  2881,  2945,
    3009,  3055,  3062,  3069,  3076,  3126,  3159,  3165,  3171,  3177,
    3183,  3189,  3195,  3202,  3205,  3209,  3212,  3216,  3220,  3224,
    3225,  3226,  3230,  3233,  3237,  3241,  3245,  3248,  3252,  3256,
    3260,  3266,  3274,  3278,  3285,  3294,  3299,  3303,  3306,  3316,
    3323,  3326,  3330,  3333,  3337,  3341,  3345,  3346,  3348,  3352,
    3356,  3360,  3364,  3368,  3374,  3379,  3384,  3389,  3394,  3399,
    3404,  3409,  3422,  3428,  3434,  3440,  3446,  3452,  3458,  3464,
    3470,  3475,  3480,  3485,  3490,  3495,  3500,  3505,  3518,  3524,
    3530,  3536,  3542,  3548,  3554,  3561,  3564,  3569,  3574,  3579,
    3585,  3591,  3596,  3602,  3607,  3613,  3619,  3625,  3631,  3637,
    3643,  3649,  3657,  3665,  3674,  3684,  3694,  3704,  3714,  3720,
    3726,  3741,  3758,  3775,  3788,  3801,  3806,  3811,  3816,  3823,
    3826,  3830,  3833,  3837,  3841,  3845,  3847,  3852,  3856,  3861,
    3865,  3869,  3879,  3884,  3889,  3895,  3900,  3905,  3910,  3915,
    3920,  3925,  3930,  3943,  3949,  3955,  3961,  3967,  3973,  3979,
    3985,  3991,  3996,  4001,  4006,  4011,  4016,  4021,  4026,  4039,
    4045,  4051,  4057,  4063,  4069,  4075,  4082,  4110,  4125,  4140,
    4144,  4203,  4232,  4248,  4264,  4269,  4300,  4305,  4308,  4313,
    4318,  4323,  4329,  4335,  4340,  4346,  4351,  4357,  4363,  4369,
    4375,  4381,  4387,  4393,  4401,  4409,  4418,  4428,  4438,  4448,
    4458,  4462,  4466,  4475,  4484,  4493,  4498,  4513,  4525,  4549,
    4553,  4565,  4577,  4589,  4601,  4613,  4625,  4637,  4641,  4656,
    4660,  4673,  4686,  4691,  4706,  4723,  4740,  4753,  4766,  4771,
    4776,  4781
  };

  // Print the state stack on the debug stream.
  void
  mcmas_parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  mcmas_parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  mcmas_parser::token_number_type
  mcmas_parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87
    };
    const unsigned int user_token_number_max_ = 342;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 11495 "parser/nssis.cc" // lalr1.cc:1167
#line 4786 "parser/nssis_new.yy" // lalr1.cc:1168

void
yy::mcmas_parser::error (const yy::mcmas_parser::location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
