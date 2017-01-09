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

#line 37 "GrammarParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "GrammarParser.tab.h"

// User implementation prologue.

#line 51 "GrammarParser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 67 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    yy::Parser::symbol_type yylex( libcasm_fe::Driver& driver );
        
    void parse_function_attributes
    ( Driver& driver
    , const yy::location& loc
    , const std::vector<std::string>& attribute_names
    , Function* function
    )
    {
        bool is_static = false;
        bool is_symbolic = false;
        bool is_controlled = false;
        
        for( const auto& attribute_name : attribute_names )
        {
            if( attribute_name == "static" )
            {
                if( is_static )
                {
                    driver.error
                    ( loc
                    , "`static` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfStatic
                    );
                    break;
                }
                else
                {
                    is_static = true;
                }
            }
            else if( attribute_name == "symbolic" )
            {
                if( is_symbolic )
                {
                    driver.error
                    ( loc
                    , "`symbolic` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfSymbolic
                    );
                    break;
                }
                else
                {
                    is_symbolic = true;
                }
            }
            else if( attribute_name == "controlled" )
            {
                if( is_controlled )
                {
                    driver.error
                    ( loc
                    , "`controlled` attribute can only be used once per function"
                      , libcasm_fe::Codes::FunctionAttributeMultipleUseOfControlled
                    );
                    break;
                }
                else
                {
                    is_controlled = true;
                }
            }
            else
            {
                driver.error
                ( loc
                , "`"+attribute_name+"` is no valid function attribute, only static, symbolic and controlled are allowed"
                , libcasm_fe::Codes::FunctionAttributeIsInvalid
                );
            }
        }
        if( is_static && is_controlled )
        {
            driver.error
            ( loc
            , "attributes `controlled` and `static` are mutually exclusive"
            , libcasm_fe::Codes::FunctionAttributeControlledAndStaticIsInvalid
            );
        }
        
        function->is_static = is_static;
        function->is_symbolic = is_symbolic;
    }

#line 140 "GrammarParser.cpp" // lalr1.cc:413


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
#line 226 "GrammarParser.cpp" // lalr1.cc:479

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
  Parser::Parser (Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 83: // SPECIFICATION
        value.move< Ast* > (that.value);
        break;

      case 85: // BODY_ELEMENTS
      case 140: // STATEMENTS
        value.move< AstListNode* > (that.value);
        break;

      case 86: // BODY_ELEMENT
      case 119: // SCOPE
      case 120: // RULE_STMT
      case 121: // RULE_SYNTAX
      case 124: // SIMPLE_STMT
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.move< AstNode* > (that.value);
        break;

      case 105: // VALUE
      case 106: // UNDEFINED
      case 107: // BOOLEAN
      case 108: // NUMBER
      case 113: // NUMBER_RANGE
      case 136: // CASE_VALUE
        value.move< AtomNode* > (that.value);
        break;

      case 118: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (that.value);
        break;

      case 137: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 133: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 128: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (that.value);
        break;

      case 89: // ENUM_SYNTAX
        value.move< Enum* > (that.value);
        break;

      case 104: // ATOM
      case 117: // EXPRESSION
        value.move< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.move< FLOATING_T > (that.value);
        break;

      case 110: // FLOATING_NUMBER
        value.move< FloatingAtom* > (that.value);
        break;

      case 147: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 90: // DERIVED_SYNTAX
      case 91: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 76: // "integer"
        value.move< INTEGER_T > (that.value);
        break;

      case 141: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 87: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 109: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 142: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 146: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 130: // PRINT_SYNTAX
      case 131: // DEBUG_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 145: // PUSH_SYNTAX
        value.move< PushNode* > (that.value);
        break;

      case 111: // RATIONAL_NUMBER
        value.move< RationalAtom* > (that.value);
        break;

      case 84: // HEADER
        value.move< SpecificationNode* > (that.value);
        break;

      case 95: // PARAM
      case 99: // TYPE_SYNTAX
        value.move< Type* > (that.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 132: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.move< rational_t > (that.value);
        break;

      case 135: // CASE_LABEL
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 103: // INITIALIZER
        value.move< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 123: // DUMPSPEC
        value.move< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 94: // FUNCTION_SIGNATURE
        value.move< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 112: // RULEREF
        value.move< std::string > (that.value);
        break;

      case 114: // LISTCONST
      case 115: // EXPRESSION_LIST
      case 116: // EXPRESSION_LIST_NO_COMMA
        value.move< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 96: // PARAM_LIST
      case 97: // PARAM_LIST_NO_COMMA
      case 98: // TYPE_IDENTIFIER_STARLIST
      case 100: // TYPE_SYNTAX_LIST
        value.move< std::vector<Type*> > (that.value);
        break;

      case 134: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 101: // INITIALIZERS
      case 102: // INITIALIZER_LIST
        value.move< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 122: // DUMPSPEC_LIST
        value.move< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 92: // IDENTIFIER_LIST
      case 93: // IDENTIFIER_LIST_NO_COMMA
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 83: // SPECIFICATION
        value.copy< Ast* > (that.value);
        break;

      case 85: // BODY_ELEMENTS
      case 140: // STATEMENTS
        value.copy< AstListNode* > (that.value);
        break;

      case 86: // BODY_ELEMENT
      case 119: // SCOPE
      case 120: // RULE_STMT
      case 121: // RULE_SYNTAX
      case 124: // SIMPLE_STMT
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (that.value);
        break;

      case 105: // VALUE
      case 106: // UNDEFINED
      case 107: // BOOLEAN
      case 108: // NUMBER
      case 113: // NUMBER_RANGE
      case 136: // CASE_VALUE
        value.copy< AtomNode* > (that.value);
        break;

      case 118: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (that.value);
        break;

      case 137: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 133: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 128: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (that.value);
        break;

      case 89: // ENUM_SYNTAX
        value.copy< Enum* > (that.value);
        break;

      case 104: // ATOM
      case 117: // EXPRESSION
        value.copy< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.copy< FLOATING_T > (that.value);
        break;

      case 110: // FLOATING_NUMBER
        value.copy< FloatingAtom* > (that.value);
        break;

      case 147: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 90: // DERIVED_SYNTAX
      case 91: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 76: // "integer"
        value.copy< INTEGER_T > (that.value);
        break;

      case 141: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 87: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 109: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 142: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 146: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 130: // PRINT_SYNTAX
      case 131: // DEBUG_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 145: // PUSH_SYNTAX
        value.copy< PushNode* > (that.value);
        break;

      case 111: // RATIONAL_NUMBER
        value.copy< RationalAtom* > (that.value);
        break;

      case 84: // HEADER
        value.copy< SpecificationNode* > (that.value);
        break;

      case 95: // PARAM
      case 99: // TYPE_SYNTAX
        value.copy< Type* > (that.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 132: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.copy< rational_t > (that.value);
        break;

      case 135: // CASE_LABEL
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 103: // INITIALIZER
        value.copy< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 123: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 94: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 112: // RULEREF
        value.copy< std::string > (that.value);
        break;

      case 114: // LISTCONST
      case 115: // EXPRESSION_LIST
      case 116: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 96: // PARAM_LIST
      case 97: // PARAM_LIST_NO_COMMA
      case 98: // TYPE_IDENTIFIER_STARLIST
      case 100: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (that.value);
        break;

      case 134: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 101: // INITIALIZERS
      case 102: // INITIALIZER_LIST
        value.copy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 122: // DUMPSPEC_LIST
        value.copy< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 92: // IDENTIFIER_LIST
      case 93: // IDENTIFIER_LIST_NO_COMMA
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
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
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
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
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

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
    #line 55 "../../obj/src/GrammarParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
}

#line 872 "GrammarParser.cpp" // lalr1.cc:741

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
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
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
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 83: // SPECIFICATION
        yylhs.value.build< Ast* > ();
        break;

      case 85: // BODY_ELEMENTS
      case 140: // STATEMENTS
        yylhs.value.build< AstListNode* > ();
        break;

      case 86: // BODY_ELEMENT
      case 119: // SCOPE
      case 120: // RULE_STMT
      case 121: // RULE_SYNTAX
      case 124: // SIMPLE_STMT
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        yylhs.value.build< AstNode* > ();
        break;

      case 105: // VALUE
      case 106: // UNDEFINED
      case 107: // BOOLEAN
      case 108: // NUMBER
      case 113: // NUMBER_RANGE
      case 136: // CASE_VALUE
        yylhs.value.build< AtomNode* > ();
        break;

      case 118: // FUNCTION_SYNTAX
        yylhs.value.build< BaseFunctionAtom* > ();
        break;

      case 137: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 133: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 128: // DIEDIE_SYNTAX
        yylhs.value.build< DiedieNode* > ();
        break;

      case 89: // ENUM_SYNTAX
        yylhs.value.build< Enum* > ();
        break;

      case 104: // ATOM
      case 117: // EXPRESSION
        yylhs.value.build< ExpressionBase* > ();
        break;

      case 75: // "floating"
        yylhs.value.build< FLOATING_T > ();
        break;

      case 110: // FLOATING_NUMBER
        yylhs.value.build< FloatingAtom* > ();
        break;

      case 147: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 90: // DERIVED_SYNTAX
      case 91: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 76: // "integer"
        yylhs.value.build< INTEGER_T > ();
        break;

      case 141: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 87: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 109: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 142: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 146: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 130: // PRINT_SYNTAX
      case 131: // DEBUG_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 145: // PUSH_SYNTAX
        yylhs.value.build< PushNode* > ();
        break;

      case 111: // RATIONAL_NUMBER
        yylhs.value.build< RationalAtom* > ();
        break;

      case 84: // HEADER
        yylhs.value.build< SpecificationNode* > ();
        break;

      case 95: // PARAM
      case 99: // TYPE_SYNTAX
        yylhs.value.build< Type* > ();
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 132: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 77: // "rational"
        yylhs.value.build< rational_t > ();
        break;

      case 135: // CASE_LABEL
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 103: // INITIALIZER
        yylhs.value.build< std::pair<ExpressionBase*, ExpressionBase*> > ();
        break;

      case 123: // DUMPSPEC
        yylhs.value.build< std::pair<std::string, std::vector<std::string>> > ();
        break;

      case 94: // FUNCTION_SIGNATURE
        yylhs.value.build< std::pair<std::vector<Type*>, Type*> > ();
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 112: // RULEREF
        yylhs.value.build< std::string > ();
        break;

      case 114: // LISTCONST
      case 115: // EXPRESSION_LIST
      case 116: // EXPRESSION_LIST_NO_COMMA
        yylhs.value.build< std::vector<ExpressionBase*>* > ();
        break;

      case 96: // PARAM_LIST
      case 97: // PARAM_LIST_NO_COMMA
      case 98: // TYPE_IDENTIFIER_STARLIST
      case 100: // TYPE_SYNTAX_LIST
        yylhs.value.build< std::vector<Type*> > ();
        break;

      case 134: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 101: // INITIALIZERS
      case 102: // INITIALIZER_LIST
        yylhs.value.build< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
        break;

      case 122: // DUMPSPEC_LIST
        yylhs.value.build< std::vector<std::pair<std::string, std::vector<std::string>>> > ();
        break;

      case 92: // IDENTIFIER_LIST
      case 93: // IDENTIFIER_LIST_NO_COMMA
        yylhs.value.build< std::vector<std::string> > ();
        break;

      default:
        break;
    }


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
  case 2:
#line 343 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1169 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& filepath = driver.get_filename();
      
      const std::string& filename
          = filepath.substr( filepath.find_last_of( "/\\" ) + 1 );
      
      const std::string& filename_without_extension
          = filename.substr( 0, filename.rfind( "." ) );
      
      yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, filename_without_extension );
  }
#line 1185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
      yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1203 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::OPTION );
  }
#line 1211 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 384 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new EnumDefNode( yylhs.location, yystack_[0].value.as< Enum* > () );
  }
#line 1219 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new FunctionDefNode( yylhs.location, yystack_[0].value.as< Function* > () );
      
      if( yystack_[0].value.as< Function* > ()->is_builtin() )
      {
          driver.error
          ( yylhs.location
          , "cannot use builtin name '"
            + yystack_[0].value.as< Function* > ()->name
            + "' as function identifier"
          , libcasm_fe::Codes::FunctionIdentifierIsBuiltinName
          );
      }
      
      try
      {
          driver.add( yystack_[0].value.as< Function* > () );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
          
          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[0].value.as< Function* > ();
      }
  }
#line 1255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< Function* > ()->binding_offsets = std::move( driver.binding_offsets );
      driver.binding_offsets.clear();
      
      yylhs.value.as< AstNode* > () = new FunctionDefNode( yylhs.location, yystack_[0].value.as< Function* > () );
      try
      {
          driver.add( yystack_[0].value.as< Function* > () );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
          
          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[0].value.as< Function* > ();
      }
  }
#line 1282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
      // TODO: check, we trust bison to pass only RuleNodes up
      
      try
      {
          driver.add( reinterpret_cast< RuleNode* >( yystack_[0].value.as< AstNode* > () ) );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
          
          // we do not need to delete $1 here, because it's already in
          // the AST, so it will be deleted later
      }
  }
#line 1315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      static InitNode* init_node = 0;

      if( not init_node )
      {
          init_node = new InitNode( yylhs.location, yystack_[0].value.as< std::string > () );
      }
      else
      {
          static u1 flag = true;
          
          if( flag )
          {
              flag = false;
              
              driver.error
              ( init_node->location
              , "multiple definition of 'init' node"
              , libcasm_fe::Codes::AgentInitRuleMultipleDefinitions
              );
          }
          
          driver.error
          ( yylhs.location
          , "multiple definition of 'init' node"
          , libcasm_fe::Codes::AgentInitRuleMultipleDefinitions
          );
      }
      
      yylhs.value.as< InitNode* > () = init_node;
  }
#line 1351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Enum* > () = new Enum(yystack_[4].value.as< std::string > (), yylhs.location);
      try
      {
          driver.function_table.add(yylhs.value.as< Enum* > ());
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
      }
      for( const std::string& name : yystack_[1].value.as< std::vector<std::string> > () )
      {
          if( yylhs.value.as< Enum* > ()->add_enum_element(name) )
          {
              try
              {
                  driver.function_table.add_enum_element( name, yylhs.value.as< Enum* > () );
              }
              catch( const Exception& e )
              {
                  driver.error
                  ( e.getLocations()
                  , e.what()
                  , e.getErrorCode()
                  );
              }
          }
          else
          {
              driver.error
              ( yylhs.location
              , "name '"
                + name
                + "' already used in enum"
              );
          }
      }
  }
#line 1398 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 560 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: 2nd argument should be a reference
      yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1439 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1447 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
      parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > (), function);
      yylhs.value.as< Function* > () = function;
  }
#line 1457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 595 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
      parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > (), function);
      yylhs.value.as< Function* > () = function;
  }
#line 1467 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 601 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
      yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 629 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
      yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      /* this constructor is implementation dependant! */
      std::vector<Type*> foo;
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1527 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 644 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1535 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 652 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
      // TODO: fail for rules without types and print warnings
      yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1556 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 673 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1581 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 686 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1589 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 694 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1598 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 699 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: limit memory size
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[0].value.as< std::string > () );
      
      // TODO: FUTURE: integrate the IR-based type-list here to perform checks!,
      //               or maybe we should check everything in the typecheckpass?
      if( yystack_[0].value.as< std::string > ().compare( "Bit" ) == 0 )
      {
          driver.error
          ( yylhs.location
          , "missing bit-size for Bit type 'Bit(<bitsize>)'"
          , libcasm_fe::Codes::TypeBitSyntaxError
          );
      }
      else if( yystack_[0].value.as< std::string > ().compare( "List" ) == 0 )
      {
          driver.error
          ( yylhs.location
          , "unsupported type '" + yystack_[0].value.as< std::string > () + "'"
          , libcasm_fe::Codes::TypeUnsupported
          );
      }      
  }
#line 1642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[3].value.as< std::string > () );
      yylhs.value.as< Type* > ()->bitsize = yystack_[1].value.as< IntegerAtom* > ()->val_;
      if( yylhs.value.as< Type* > ()->bitsize <= 0 || yylhs.value.as< Type* > ()->bitsize > 256 )
      {
          driver.error
          ( yylhs.location
          , "invalid bit-size for Bit type, must between 1 <= x <= 256"
          , libcasm_fe::Codes::TypeBitSizeIsInvalid
          );
      }
  }
#line 1659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<Type*> > () );

      if( yystack_[3].value.as< std::string > ().compare( "List" ) == 0 )
      {
          driver.error
          ( yylhs.location
          , "unsupported type '" + yystack_[3].value.as< std::string > () + "'"
          , libcasm_fe::Codes::TypeUnsupported
          );
      }
      // TODO: FUTURE: PPA: better and generic type checking in the type check pass
      else if( yystack_[3].value.as< std::string > ().compare( "Tuple" ) != 0 )
      {
          driver.error
          ( yylhs.location
          , "unknown type '" + yystack_[3].value.as< std::string > () + "'"
          , libcasm_fe::Codes::TypeUnknown
          );
      }      
  }
#line 1685 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[5].value.as< std::string > () );
      yylhs.value.as< Type* > ()->subrange_start = yystack_[3].value.as< IntegerAtom* > ()->val_;
      yylhs.value.as< Type* > ()->subrange_end = yystack_[1].value.as< IntegerAtom* > ()->val_;
      if( yylhs.value.as< Type* > ()->subrange_start >= yylhs.value.as< Type* > ()->subrange_end )
      {
          driver.error
          ( yylhs.location
          , "start of subrange must be smaller than the end"
          , libcasm_fe::Codes::TypeIntegerRangedInvalidInterval
          );
      }
  }
#line 1703 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
      yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 793 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 797 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr;
  }
#line 1744 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1760 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector< std::pair<ExpressionBase*, ExpressionBase* > >();
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 834 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1777 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 838 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 846 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1793 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 850 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1801 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 854 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1809 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 858 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1817 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 862 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (),
                                 libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1826 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 871 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1834 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 875 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1842 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 879 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 883 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1874 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 895 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); 
  }
#line 1882 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1890 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1898 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 915 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1906 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1914 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 927 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1922 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 931 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1930 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 935 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1938 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 943 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1946 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 947 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1954 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 951 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
      yystack_[0].value.as< IntegerAtom* > ()->val_ *= (-1);
  }
#line 1963 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1971 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 964 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1979 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
      yystack_[0].value.as< FloatingAtom* > ()->val_ *= (-1);
  }
#line 1988 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1996 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 2004 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< rational_t > ().numerator *= -1;
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 2013 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 2021 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new NumberRangeAtom( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2029 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2037 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 2045 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2053 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2061 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 1034 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2070 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 1039 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2079 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2087 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1052 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2095 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1056 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2103 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1060 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1064 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1068 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1076 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1080 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1096 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1100 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1104 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new UnaryExpression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2199 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1108 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1116 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1120 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1124 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( Builtin::isBuiltin( yystack_[3].value.as< std::string > () ) )
      {
          yylhs.value.as< BaseFunctionAtom* > () = new BuiltinAtom( yylhs.location, yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
      }
      else
      {
          yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
      }
  }
#line 2238 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1139 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2246 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2254 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2262 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      stmts->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2280 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1169 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1173 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1177 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2305 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1182 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2323 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2332 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1201 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1210 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1222 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1226 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1230 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1234 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1242 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1246 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1250 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2421 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1254 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1258 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2437 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1262 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2445 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1266 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2453 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1270 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2461 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1274 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1278 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2477 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1282 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.error
      ( yylhs.location
      , "invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
      , libcasm_fe::Codes::SyntaxErrorInvalidStatement
      );
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1302 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1306 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1314 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1322 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[1].value.as< std::string > () );
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::FUNCTION_ATOM )
      {
          yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, reinterpret_cast< FunctionAtom* >( yystack_[2].value.as< BaseFunctionAtom* > () ), yystack_[0].value.as< ExpressionBase* > () );
      }
      else
      {
          driver.error
          ( yylhs.location
          , "can only use functions for updates but '"
            + yystack_[2].value.as< BaseFunctionAtom* > ()->to_str()
            + "` is a '"
            + type_to_str( yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ )
          );
      }
  }
#line 2582 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1395 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2590 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1403 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[0].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[1].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::vector< std::pair< AtomNode*, AstNode* > >();
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2608 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2616 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1425 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2624 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1429 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // equivalent to 'default' 
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2633 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2657 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 2665 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 2673 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2681 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1462 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2689 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1470 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1482 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2721 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1490 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2729 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1502 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2746 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1507 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1516 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2763 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1520 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1529 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto var = Symbol( yystack_[1].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET );
      try
      {
          driver.function_table.add( &var );      
      }
      catch( const Exception& e)
      {
          driver.error( yylhs.location, e.what() );
      }
  }
#line 2787 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[5].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2796 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1546 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto var = Symbol( yystack_[3].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET );
      try
      {
          driver.function_table.add( &var );
      }
      catch( const Exception& e)
      {
          driver.error( yylhs.location, e.what() );
      }
  }
#line 2812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[7].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1567 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( yylhs.location, "cannot push to builtin '" + yystack_[0].value.as< BaseFunctionAtom* > ()->to_str() + "'" );
      }
      else
      {
          yylhs.value.as< PushNode* > () = new PushNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), reinterpret_cast< FunctionAtom* >( yystack_[0].value.as< BaseFunctionAtom* > () ) );
      }
  }
#line 2836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1582 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( yylhs.location, "cannot pop to builtin '" + yystack_[2].value.as< BaseFunctionAtom* > ()->to_str() + "'" );
      }
      else if( yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( yylhs.location, "cannot pop from builtin '" + yystack_[0].value.as< BaseFunctionAtom* > ()->to_str() + "'" );
      }
      else
      {
          yylhs.value.as< PopNode* > () = new PopNode
          ( yylhs.location
          , reinterpret_cast< FunctionAtom* >( yystack_[2].value.as< BaseFunctionAtom* > () )
          , reinterpret_cast< FunctionAtom* >( yystack_[0].value.as< BaseFunctionAtom* > () )
          );
      }
  }
#line 2859 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2867 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2875 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2879 "GrammarParser.cpp" // lalr1.cc:859
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
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int Parser::yypact_ninf_ = -274;

  const signed char Parser::yytable_ninf_ = -107;

  const short int
  Parser::yypact_[] =
  {
      14,  -274,    23,   431,  -274,    47,    52,    58,    61,    65,
     -41,   431,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
      18,    35,    29,     0,    66,    26,  -274,    70,   604,    71,
      72,    93,   102,   438,    73,  -274,   103,    20,   -48,   159,
      95,  -274,  -274,  -274,  -274,   604,    81,   124,   604,   562,
     116,  -274,  -274,  -274,  -274,   146,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,   814,  -274,   -25,
     147,  -274,   152,   154,   155,   173,    66,    66,   -29,  -274,
     438,   438,   604,   604,   604,  -274,  -274,   156,   160,   438,
     -36,   604,   604,   604,   164,   604,   169,   438,   438,   -35,
     157,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,     2,   179,   170,   174,    72,   187,   192,   183,  -274,
    -274,  -274,   143,   165,   604,  -274,  -274,  -274,    39,    39,
     604,  -274,  -274,  -274,   676,  -274,   207,   196,   687,  -274,
     583,   604,   604,   604,   604,   604,   604,   604,   604,   604,
     604,   604,   604,   604,   604,   604,    72,    72,    42,   195,
     -22,   604,   226,   235,   438,   102,  -274,  -274,  -274,   300,
     327,   814,   814,   814,    45,   266,  -274,   604,   240,   518,
     529,   814,   604,   647,   256,   369,   396,   604,   102,   438,
       5,    26,  -274,  -274,    72,    72,   230,   716,   745,  -274,
    -274,   604,   604,  -274,   244,   814,   842,   872,   853,   303,
      69,   418,   310,   236,  -274,   251,    74,   883,   203,   145,
     814,   249,  -274,   604,    72,  -274,    34,    34,   261,   273,
     -30,   814,  -274,   260,  -274,  -274,  -274,  -274,  -274,  -274,
      72,   604,   774,   604,   438,   276,   814,   169,   169,  -274,
    -274,   814,    28,  -274,   102,   438,   159,  -274,  -274,  -274,
      16,  -274,   264,  -274,  -274,   814,   803,  -274,   604,   814,
     283,    72,  -274,  -274,    34,   258,   604,   290,   485,   298,
     308,   335,   466,  -274,  -274,   438,    30,  -274,  -274,  -274,
     625,   625,  -274,   814,   604,  -274,   314,  -274,    -4,  -274,
     438,   604,  -274,   438,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,   315,   466,   312,  -274,   438,  -274,  -274,   814,  -274,
     438,   604,  -274,   320,  -274,  -274,  -274,   438,  -274,  -274,
     456,  -274,  -274,   438,  -274
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     3,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     2,     5,    10,     6,     7,     9,     8,    11,    12,
       0,     0,     0,     0,     0,     0,     4,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,    26,     0,    24,
       0,    64,    67,    69,    68,     0,     0,     0,     0,     0,
       0,    76,    73,    79,    61,   106,   105,    55,    65,    66,
      60,    70,    71,    72,    59,    63,    62,    16,    54,     0,
      32,    36,     0,    33,    40,     0,     0,     0,     0,   120,
       0,     0,     0,     0,   144,   145,   137,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   138,
       0,   111,   113,   112,   122,   123,   124,   125,   127,   126,
     128,   129,   130,   109,   110,   131,   132,   133,   134,   135,
     136,     0,     0,     0,    25,     0,     0,    39,     0,    23,
      13,   104,     0,     0,     0,    74,    77,    80,     0,     0,
       0,    81,    75,    78,     0,    85,     0,    86,    89,    82,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
       0,     0,     0,     0,     0,     0,   139,   140,   169,     0,
       0,   141,   142,   143,     0,     0,   179,     0,   163,     0,
       0,   146,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,    29,     0,    38,     0,     0,     0,    56,
      84,    87,     0,   107,     0,    89,   103,   101,   102,    90,
      91,    96,    97,    98,    92,    93,    94,    95,    99,   100,
      17,     0,    31,     0,     0,    35,     0,     0,    46,     0,
       0,    19,    14,     0,   116,   119,   165,   168,   167,   172,
       0,     0,     0,     0,     0,     0,   147,     0,     0,   166,
     164,   148,     0,   114,     0,     0,    22,    30,    37,    48,
       0,    51,    52,    57,    58,    88,     0,   108,     0,    15,
       0,    45,    42,    41,     0,     0,     0,     0,     0,   161,
       0,   170,     0,   176,   177,     0,     0,   115,    21,    47,
      50,     0,    83,    20,     0,    44,     0,   121,     0,   174,
       0,     0,   162,     0,   153,   154,   158,   155,   156,   157,
     159,     0,   151,     0,   117,     0,    49,    53,    18,    43,
       0,     0,   178,     0,   171,   149,   150,     0,   118,   173,
       0,   160,   152,     0,   175
  };

  const short int
  Parser::yypgoto_[] =
  {
    -274,  -274,  -274,  -274,   366,  -274,  -274,  -274,  -274,  -274,
     -47,  -274,   177,   211,   350,  -274,   186,    -6,   113,   131,
    -274,    98,  -199,  -274,  -273,  -253,  -216,   -34,   -11,   -42,
    -274,  -274,  -274,  -142,  -274,    25,   -33,   -32,  -171,  -274,
    -193,   227,   -31,   -83,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,    79,  -274,  -274,  -274,  -274,  -274,   148,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,    11,    12,    13,    14,    15,    16,    17,
      36,    37,    39,    71,    72,    73,   126,   127,   239,   129,
     270,   271,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,   146,   147,   215,    68,   176,   102,    18,
      78,    79,   177,   178,   104,   105,   106,   107,   108,   109,
     110,   111,   321,   322,   323,   112,   113,   114,   179,   115,
     116,   286,   331,   117,   118,   119,   120
  };

  const short int
  Parser::yytable_[] =
  {
     100,   101,   103,   244,   137,   262,   186,   272,   214,    32,
      24,   198,   135,   142,   264,   187,   150,     1,   330,   317,
     125,   174,   283,     4,    75,   165,   236,   237,   263,   172,
     173,    74,   175,   166,  -106,   136,   143,   284,    25,   318,
     151,   152,   153,   188,   154,   155,   156,   100,   100,   317,
      33,    34,   199,    67,    52,   265,   100,    74,   157,   158,
     159,   160,   161,   194,   100,   100,   162,   163,   164,   318,
     131,   296,   299,   144,   148,    27,   319,   300,   295,    31,
     325,   124,   236,   237,    38,    28,    29,   138,   139,   175,
     137,   175,   233,    30,   297,   249,   247,   247,   135,   142,
     234,   272,   327,   250,   135,   142,   319,   181,   182,   183,
      52,   290,   247,   247,    51,    52,   189,   190,   191,   203,
     193,   136,   143,    69,   324,   121,    19,   136,   143,   132,
     133,    20,   134,   159,   160,   161,   240,    21,   159,   160,
      22,   100,   101,   103,    23,    35,   100,   100,    76,    40,
      70,    74,    70,    77,   338,   123,    51,    52,    53,   207,
     231,   232,   100,   100,   238,   208,   100,   101,   103,   333,
     128,   291,   138,   139,   130,   140,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   132,   133,   154,   155,   149,   241,   150,   267,    51,
      52,   141,   135,   142,   168,   167,   170,   157,   158,   159,
     160,   161,   252,   138,   139,   169,   163,   256,    51,    52,
      53,   100,   261,   171,   293,   294,   197,   332,   280,   180,
     334,   200,   100,   101,   103,   184,   275,   276,   206,   185,
      51,    52,   141,   192,   287,   195,   196,   339,    55,   201,
     306,   154,   155,   202,   342,   204,   205,   211,   279,   320,
     344,   210,   100,   101,   103,   157,   158,   159,   160,   161,
      41,    42,    43,    44,    70,   238,   288,   100,    46,    47,
     100,    48,   242,    49,   154,   155,   269,   243,   251,   320,
      50,   253,   100,   101,   103,   258,   277,   100,   157,   278,
     159,   160,   161,   303,   100,    51,    52,    53,    54,    55,
     100,   308,    80,   246,    81,   159,    82,    83,    84,    85,
      86,    87,   281,    88,    89,   282,    90,    91,   285,   328,
      92,   292,   301,   304,    93,    94,    95,   307,    96,    80,
     309,    81,   248,    82,    83,    84,    85,    86,    87,   311,
      88,    89,   155,    90,    91,    97,   340,    92,   154,   155,
     312,    93,    94,    95,   313,    96,   329,   159,   160,   161,
     337,   335,   341,    98,   159,   160,   161,    26,   266,    99,
     235,    80,    97,    81,   122,    82,    83,    84,    85,    86,
      87,   268,    88,    89,   305,    90,    91,   298,   326,    92,
      98,   336,   245,    93,    94,    95,    99,    96,    80,     0,
      81,     0,    82,    83,    84,    85,    86,    87,     0,    88,
      89,     0,    90,    91,    97,   259,    92,     0,     0,     0,
      93,    94,    95,     0,    96,     5,     6,     7,     8,     9,
       0,    10,    98,     0,     0,     0,     0,     0,    99,     0,
      80,    97,    81,     0,    82,    83,    84,    85,    86,    87,
       0,    88,    89,     0,    90,    91,   154,   155,    92,    98,
     260,     0,    93,    94,    95,    99,    96,     0,   343,     0,
     157,   158,   159,   160,   161,     0,     0,     0,   162,   163,
     164,     0,     0,    97,     0,     0,     0,     0,   314,     0,
     151,   152,   153,     0,   154,   155,   156,    42,    43,    44,
     310,    98,     0,     0,   132,   133,     0,    99,   157,   158,
     159,   160,   161,     0,     0,   315,   162,   163,   164,   151,
     152,   153,     0,   154,   155,   156,     0,     0,     0,     0,
       0,    51,    52,    53,   316,    55,   254,   157,   158,   159,
     160,   161,     0,     0,     0,   162,   163,   164,     0,     0,
     255,     0,   151,   152,   153,     0,   154,   155,   156,     0,
       0,     0,     0,   151,   152,   153,     0,   154,   155,   156,
     157,   158,   159,   160,   161,     0,     0,     0,   162,   163,
     164,   157,   158,   159,   160,   161,     0,     0,     0,   162,
     163,   164,    41,    42,    43,    44,     0,     0,     0,    45,
      46,    47,     0,    48,     0,    49,   145,     0,     0,     0,
       0,     0,    50,    41,    42,    43,    44,     0,     0,     0,
      45,    46,    47,     0,    48,   213,    49,    51,    52,    53,
      54,    55,     0,    50,    41,    42,    43,    44,     0,     0,
       0,    45,    46,    47,     0,    48,     0,    49,    51,    52,
      53,    54,    55,     0,    50,    41,    42,    43,    44,     0,
       0,     0,     0,    46,    47,     0,    48,     0,    49,    51,
      52,    53,    54,    55,   257,    50,     0,     0,     0,     0,
       0,   151,   152,   153,     0,   154,   155,   156,     0,     0,
      51,    52,    53,    54,    55,     0,     0,     0,     0,   157,
     158,   159,   160,   161,     0,     0,     0,   162,   163,   164,
     151,   152,   153,     0,   154,   155,   156,     0,   209,     0,
       0,   151,   152,   153,     0,   154,   155,   156,   157,   158,
     159,   160,   161,     0,     0,     0,   162,   163,   164,   157,
     158,   159,   160,   161,   212,     0,     0,   162,   163,   164,
     151,   152,   153,     0,   154,   155,   156,     0,   273,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,   158,
     159,   160,   161,     0,     0,     0,   162,   163,   164,   151,
     152,   153,     0,   154,   155,   156,     0,   274,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,   158,   159,
     160,   161,     0,     0,     0,   162,   163,   164,   151,   152,
     153,     0,   154,   155,   156,     0,   289,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,   158,   159,   160,
     161,     0,     0,     0,   162,   163,   164,   151,   152,   153,
       0,   154,   155,   156,     0,     0,     0,   302,   151,   152,
     153,     0,   154,   155,   156,   157,   158,   159,   160,   161,
       0,     0,     0,   162,   163,   164,   157,   158,   159,   160,
     161,     0,     0,     0,   162,   163,   164,   152,   153,     0,
     154,   155,   156,     0,     0,     0,     0,     0,   152,     0,
       0,   154,   155,   156,   157,   158,   159,   160,   161,     0,
       0,     0,   162,   163,   164,   157,   158,   159,   160,   161,
     154,   155,   156,   162,   163,   164,     0,     0,     0,     0,
       0,   154,   155,     0,   157,   158,   159,   160,   161,     0,
       0,     0,   162,   163,   164,   157,   158,   159,   160,   161,
       0,     0,     0,     0,   163,   164
  };

  const short int
  Parser::yycheck_[] =
  {
      33,    33,    33,   174,    46,   198,    89,   206,   150,     9,
      51,     9,    46,    47,     9,    51,    51,     3,    22,   292,
      68,    50,    52,     0,    30,    50,    48,    49,   199,    76,
      77,    79,    61,    58,    69,    46,    47,    67,    79,   292,
      44,    45,    46,    79,    48,    49,    50,    80,    81,   322,
      50,    51,    50,    28,    76,    50,    89,    79,    62,    63,
      64,    65,    66,    96,    97,    98,    70,    71,    72,   322,
      45,   264,    56,    48,    49,    57,   292,    61,    50,    50,
      50,    61,    48,    49,    58,    50,    51,    48,    49,    61,
     132,    61,    50,    58,   265,    50,   179,   180,   132,   133,
      58,   300,   301,    58,   138,   139,   322,    82,    83,    84,
      76,   253,   195,   196,    75,    76,    91,    92,    93,   125,
      95,   132,   133,    52,   295,    52,    79,   138,   139,    48,
      49,    79,    51,    64,    65,    66,   170,    79,    64,    65,
      79,   174,   174,   174,    79,    79,   179,   180,    55,    79,
      79,    79,    79,    51,   325,    52,    75,    76,    77,   134,
     166,   167,   195,   196,   170,   140,   199,   199,   199,   311,
      11,   254,    48,    49,    79,    51,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,    48,    49,    48,    49,    79,   171,    51,   204,    75,
      76,    77,   236,   237,    52,    58,    51,    62,    63,    64,
      65,    66,   187,    48,    49,    61,    71,   192,    75,    76,
      77,   254,   197,    50,   257,   258,    69,   310,   234,    81,
     313,    52,   265,   265,   265,    79,   211,   212,    55,    79,
      75,    76,    77,    79,   250,    97,    98,   330,    79,    79,
     284,    48,    49,    79,   337,    68,    64,    61,   233,   292,
     343,    54,   295,   295,   295,    62,    63,    64,    65,    66,
      40,    41,    42,    43,    79,   281,   251,   310,    48,    49,
     313,    51,    56,    53,    48,    49,    56,    52,    22,   322,
      60,    51,   325,   325,   325,    39,    52,   330,    62,    50,
      64,    65,    66,   278,   337,    75,    76,    77,    78,    79,
     343,   286,    12,    13,    14,    64,    16,    17,    18,    19,
      20,    21,    61,    23,    24,    52,    26,    27,    68,   304,
      30,    55,    68,    50,    34,    35,    36,    79,    38,    12,
      50,    14,    15,    16,    17,    18,    19,    20,    21,    51,
      23,    24,    49,    26,    27,    55,   331,    30,    48,    49,
      52,    34,    35,    36,    29,    38,    52,    64,    65,    66,
      58,    56,    52,    73,    64,    65,    66,    11,   201,    79,
     169,    12,    55,    14,    34,    16,    17,    18,    19,    20,
      21,   205,    23,    24,   281,    26,    27,   266,   300,    30,
      73,   322,   175,    34,    35,    36,    79,    38,    12,    -1,
      14,    -1,    16,    17,    18,    19,    20,    21,    -1,    23,
      24,    -1,    26,    27,    55,    56,    30,    -1,    -1,    -1,
      34,    35,    36,    -1,    38,     4,     5,     6,     7,     8,
      -1,    10,    73,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      12,    55,    14,    -1,    16,    17,    18,    19,    20,    21,
      -1,    23,    24,    -1,    26,    27,    48,    49,    30,    73,
      74,    -1,    34,    35,    36,    79,    38,    -1,    22,    -1,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    70,    71,
      72,    -1,    -1,    55,    -1,    -1,    -1,    -1,    32,    -1,
      44,    45,    46,    -1,    48,    49,    50,    41,    42,    43,
      25,    73,    -1,    -1,    48,    49,    -1,    79,    62,    63,
      64,    65,    66,    -1,    -1,    59,    70,    71,    72,    44,
      45,    46,    -1,    48,    49,    50,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    28,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    -1,    -1,
      31,    -1,    44,    45,    46,    -1,    48,    49,    50,    -1,
      -1,    -1,    -1,    44,    45,    46,    -1,    48,    49,    50,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    70,    71,
      72,    62,    63,    64,    65,    66,    -1,    -1,    -1,    70,
      71,    72,    40,    41,    42,    43,    -1,    -1,    -1,    47,
      48,    49,    -1,    51,    -1,    53,    54,    -1,    -1,    -1,
      -1,    -1,    60,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    48,    49,    -1,    51,    52,    53,    75,    76,    77,
      78,    79,    -1,    60,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    48,    49,    -1,    51,    -1,    53,    75,    76,
      77,    78,    79,    -1,    60,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    -1,    53,    75,
      76,    77,    78,    79,    37,    60,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    -1,    48,    49,    50,    -1,    -1,
      75,    76,    77,    78,    79,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72,
      44,    45,    46,    -1,    48,    49,    50,    -1,    52,    -1,
      -1,    44,    45,    46,    -1,    48,    49,    50,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    62,
      63,    64,    65,    66,    67,    -1,    -1,    70,    71,    72,
      44,    45,    46,    -1,    48,    49,    50,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    44,
      45,    46,    -1,    48,    49,    50,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    44,    45,
      46,    -1,    48,    49,    50,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    44,    45,    46,
      -1,    48,    49,    50,    -1,    -1,    -1,    54,    44,    45,
      46,    -1,    48,    49,    50,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    45,    46,    -1,
      48,    49,    50,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    49,    50,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    62,    63,    64,    65,    66,
      48,    49,    50,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    71,    72
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    83,    84,     0,     4,     5,     6,     7,     8,
      10,    85,    86,    87,    88,    89,    90,    91,   121,    79,
      79,    79,    79,    79,    51,    79,    86,    57,    50,    51,
      58,    50,     9,    50,    51,    79,    92,    93,    58,    94,
      79,    40,    41,    42,    43,    47,    48,    49,    51,    53,
      60,    75,    76,    77,    78,    79,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   117,   118,    52,
      79,    95,    96,    97,    79,    99,    55,    51,   122,   123,
      12,    14,    16,    17,    18,    19,    20,    21,    23,    24,
      26,    27,    30,    34,    35,    36,    38,    55,    73,    79,
     118,   119,   120,   124,   126,   127,   128,   129,   130,   131,
     132,   133,   137,   138,   139,   141,   142,   145,   146,   147,
     148,    52,    96,    52,    61,    68,    98,    99,    11,   101,
      79,   117,    48,    49,    51,   109,   110,   111,    48,    49,
      51,    77,   109,   110,   117,    54,   115,   116,   117,    79,
      51,    44,    45,    46,    48,    49,    50,    62,    63,    64,
      65,    66,    70,    71,    72,    50,    58,    58,    52,    61,
      51,    50,    92,    92,    50,    61,   119,   124,   125,   140,
     140,   117,   117,   117,    79,    79,   125,    51,    79,   117,
     117,   117,    79,   117,   118,   140,   140,    69,     9,    50,
      52,    79,    79,    99,    68,    64,    55,   117,   117,    52,
      54,    61,    67,    52,   115,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,    99,    99,    50,    58,    95,    48,    49,    99,   100,
     109,   117,    56,    52,   120,   123,    13,   125,    15,    50,
      58,    22,   117,    51,    28,    31,   117,    37,    39,    56,
      74,   117,   122,   120,     9,    50,    94,    99,    98,    56,
     102,   103,   104,    52,    52,   117,   117,    52,    50,   117,
      99,    61,    52,    52,    67,    68,   143,    99,   117,    52,
     115,   125,    55,   118,   118,    50,   122,   120,   101,    56,
      61,    68,    54,   117,    50,   100,   109,    79,   117,    50,
      25,    51,    52,    29,    32,    59,    78,   106,   107,   108,
     118,   134,   135,   136,   120,    50,   103,   104,   117,    52,
      22,   144,   125,   115,   125,    56,   134,    58,   120,   125,
     117,    52,   125,    22,   125
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    82,    83,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    87,    88,    89,    90,    90,    90,    90,    90,
      90,    91,    91,    91,    91,    92,    92,    93,    93,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    98,
      99,    99,    99,    99,   100,   100,   100,   101,   101,   102,
     102,   102,   103,   103,   104,   104,   104,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   107,   107,
     108,   108,   108,   109,   109,   109,   110,   110,   110,   111,
     111,   111,   112,   113,   114,   114,   115,   115,   116,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   118,   118,   118,   119,
     119,   120,   120,   121,   121,   121,   121,   121,   121,   122,
     122,   123,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   126,   127,   128,   128,   129,   130,   131,   132,   133,
     134,   134,   135,   136,   136,   136,   136,   136,   136,   136,
     137,   137,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   143,   142,   144,   142,   145,   146,   147,   148
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     5,     6,     7,     4,     6,     9,     6,
       8,     7,     6,     4,     3,     2,     1,     3,     1,     3,
       4,     3,     1,     1,     2,     3,     1,     3,     2,     1,
       1,     4,     4,     6,     3,     2,     1,     4,     3,     3,
       2,     1,     1,     3,     1,     1,     3,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     2,     5,     3,     2,     1,     2,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     3,     4,     1,
       1,     1,     1,     4,     6,     7,     6,     8,     9,     3,
       1,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     1,     1,     2,     3,     3,     6,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       7,     4,     5,     2,     3,     3,     3,     3,     2,     1,
       4,     6,     0,     7,     0,     9,     4,     4,     6,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"option\"", "\"derived\"", "\"enum\"", "\"rule\"", "\"dumps\"",
  "\"function\"", "\"initially\"", "\"seq\"", "\"endseq\"", "\"par\"",
  "\"endpar\"", "\"assert\"", "\"assure\"", "\"diedie\"", "\"impossible\"",
  "\"skip\"", "\"let\"", "\"in\"", "\"forall\"", "\"iterate\"", "\"do\"",
  "\"call\"", "\"if\"", "\"then\"", "\"else\"", "\"case\"", "\"of\"",
  "\"default\"", "\"endcase\"", "\"print\"", "\"debug\"", "\"push\"",
  "\"into\"", "\"pop\"", "\"from\"", "\"self\"", "\"undef\"", "\"false\"",
  "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"not\"", "\"+\"", "\"-\"",
  "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\".\"",
  "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"",
  "\"%\"", "\"..\"", "\"->\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"",
  "\"{|\"", "\"|}\"", "\"floating\"", "\"integer\"", "\"rational\"",
  "\"string\"", "\"identifier\"", "UPLUS", "UMINUS", "$accept",
  "SPECIFICATION", "HEADER", "BODY_ELEMENTS", "BODY_ELEMENT",
  "INIT_SYNTAX", "OPTION_SYNTAX", "ENUM_SYNTAX", "DERIVED_SYNTAX",
  "FUNCTION_DEFINITION", "IDENTIFIER_LIST", "IDENTIFIER_LIST_NO_COMMA",
  "FUNCTION_SIGNATURE", "PARAM", "PARAM_LIST", "PARAM_LIST_NO_COMMA",
  "TYPE_IDENTIFIER_STARLIST", "TYPE_SYNTAX", "TYPE_SYNTAX_LIST",
  "INITIALIZERS", "INITIALIZER_LIST", "INITIALIZER", "ATOM", "VALUE",
  "UNDEFINED", "BOOLEAN", "NUMBER", "INTEGER_NUMBER", "FLOATING_NUMBER",
  "RATIONAL_NUMBER", "RULEREF", "NUMBER_RANGE", "LISTCONST",
  "EXPRESSION_LIST", "EXPRESSION_LIST_NO_COMMA", "EXPRESSION",
  "FUNCTION_SYNTAX", "SCOPE", "RULE_STMT", "RULE_SYNTAX", "DUMPSPEC_LIST",
  "DUMPSPEC", "SIMPLE_STMT", "STATEMENT", "ASSERT_SYNTAX", "ASSURE_SYNTAX",
  "DIEDIE_SYNTAX", "IMPOSSIBLE_SYNTAX", "PRINT_SYNTAX", "DEBUG_SYNTAX",
  "UPDATE_SYNTAX", "CASE_SYNTAX", "CASE_LABEL_LIST", "CASE_LABEL",
  "CASE_VALUE", "CALL_SYNTAX", "SEQ_SYNTAX", "PAR_SYNTAX", "STATEMENTS",
  "IFTHENELSE", "LET_SYNTAX", "$@1", "$@2", "PUSH_SYNTAX", "POP_SYNTAX",
  "FORALL_SYNTAX", "ITERATE_SYNTAX", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   342,   342,   350,   365,   370,   379,   383,   387,   419,
     442,   446,   471,   507,   512,   559,   564,   568,   572,   576,
     580,   588,   594,   600,   604,   611,   615,   623,   628,   637,
     643,   651,   657,   668,   672,   680,   685,   693,   698,   703,
     711,   734,   747,   769,   787,   792,   796,   804,   808,   816,
     820,   824,   833,   837,   845,   849,   853,   857,   861,   870,
     874,   878,   882,   886,   890,   894,   898,   906,   914,   918,
     926,   930,   934,   942,   946,   950,   959,   963,   967,   976,
     980,   984,   993,  1001,  1009,  1013,  1021,  1025,  1033,  1038,
    1047,  1051,  1055,  1059,  1063,  1067,  1071,  1075,  1079,  1083,
    1087,  1091,  1095,  1099,  1103,  1107,  1115,  1119,  1123,  1138,
    1142,  1150,  1154,  1164,  1168,  1172,  1176,  1181,  1186,  1195,
    1200,  1209,  1217,  1221,  1225,  1229,  1233,  1237,  1241,  1245,
    1249,  1253,  1257,  1261,  1265,  1269,  1273,  1277,  1281,  1301,
    1305,  1313,  1321,  1329,  1333,  1349,  1357,  1365,  1373,  1394,
    1402,  1407,  1416,  1424,  1428,  1433,  1437,  1441,  1445,  1449,
    1457,  1461,  1465,  1469,  1477,  1481,  1489,  1493,  1501,  1506,
    1515,  1519,  1529,  1528,  1546,  1545,  1566,  1581,  1604,  1614
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
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
  Parser::yy_reduce_print_ (int yyrule)
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



} // yy
#line 3625 "GrammarParser.cpp" // lalr1.cc:1167
#line 1620 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void yy::Parser::error
( const location_type& l
, const std::string& m
)
{
    if( m.compare( "syntax error, unexpected end of file, expecting CASM" ) == 0 )
    {
        i32 pos = (l.begin.line - 1);
        pos = ( pos > 0 ? pos : 1 );
        
        driver.error
        ( yy::location( yy::position( 0, pos, 1 ) )
        , m
        , libcasm_fe::Codes::SyntaxError
        );
    }
    else
    {
        driver.error( l, m, libcasm_fe::Codes::SyntaxError );
    }
}


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
