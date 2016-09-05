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
#line 64 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    #include "src/Driver.h"
    #include "src/Codes.h"

    std::pair<bool, bool> parse_function_attributes
    ( Driver& driver
    , const yy::location& loc
    , const std::vector<std::string>& attribute_names
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
        
        return std::pair<bool, bool>(is_static, is_symbolic);
    }

#line 139 "GrammarParser.cpp" // lalr1.cc:413


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
#line 225 "GrammarParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  casmi_parser::yytnamerr_ (const char *yystr)
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
  casmi_parser::casmi_parser (Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  casmi_parser::~casmi_parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  casmi_parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  casmi_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  casmi_parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  casmi_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  casmi_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  casmi_parser::symbol_number_type
  casmi_parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  casmi_parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  casmi_parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 84: // SPECIFICATION
        value.move< Ast* > (that.value);
        break;

      case 86: // BODY_ELEMENTS
      case 141: // STATEMENTS
        value.move< AstListNode* > (that.value);
        break;

      case 87: // BODY_ELEMENT
      case 120: // SCOPE
      case 121: // RULE_STMT
      case 122: // RULE_SYNTAX
      case 125: // SIMPLE_STMT
      case 126: // STATEMENT
      case 130: // IMPOSSIBLE_SYNTAX
        value.move< AstNode* > (that.value);
        break;

      case 106: // VALUE
      case 107: // UNDEFINED
      case 108: // BOOLEAN
      case 109: // NUMBER
      case 114: // NUMBER_RANGE
      case 137: // CASE_VALUE
        value.move< AtomNode* > (that.value);
        break;

      case 119: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (that.value);
        break;

      case 138: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 134: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 129: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (that.value);
        break;

      case 90: // ENUM_SYNTAX
        value.move< Enum* > (that.value);
        break;

      case 105: // ATOM
      case 118: // EXPRESSION
        value.move< ExpressionBase* > (that.value);
        break;

      case 76: // "floating"
        value.move< FLOATING_T > (that.value);
        break;

      case 111: // FLOATING_NUMBER
        value.move< FloatingAtom* > (that.value);
        break;

      case 148: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 91: // DERIVED_SYNTAX
      case 92: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 77: // "integer"
        value.move< INTEGER_T > (that.value);
        break;

      case 142: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 88: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 110: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 143: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 147: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 131: // PRINT_SYNTAX
      case 132: // DEBUG_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 146: // PUSH_SYNTAX
        value.move< PushNode* > (that.value);
        break;

      case 112: // RATIONAL_NUMBER
        value.move< RationalAtom* > (that.value);
        break;

      case 85: // HEADER
        value.move< SpecificationNode* > (that.value);
        break;

      case 96: // PARAM
      case 100: // TYPE_SYNTAX
        value.move< Type* > (that.value);
        break;

      case 127: // ASSERT_SYNTAX
      case 128: // ASSURE_SYNTAX
      case 139: // SEQ_SYNTAX
      case 140: // PAR_SYNTAX
      case 149: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 133: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 78: // "rational"
        value.move< rational_t > (that.value);
        break;

      case 136: // CASE_LABEL
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 104: // INITIALIZER
        value.move< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 124: // DUMPSPEC
        value.move< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 95: // FUNCTION_SIGNATURE
        value.move< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 79: // "string"
      case 80: // "identifier"
      case 113: // RULEREF
        value.move< std::string > (that.value);
        break;

      case 115: // LISTCONST
      case 116: // EXPRESSION_LIST
      case 117: // EXPRESSION_LIST_NO_COMMA
        value.move< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 97: // PARAM_LIST
      case 98: // PARAM_LIST_NO_COMMA
      case 99: // TYPE_IDENTIFIER_STARLIST
      case 101: // TYPE_SYNTAX_LIST
        value.move< std::vector<Type*> > (that.value);
        break;

      case 135: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 102: // INITIALIZERS
      case 103: // INITIALIZER_LIST
        value.move< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 123: // DUMPSPEC_LIST
        value.move< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 93: // IDENTIFIER_LIST
      case 94: // IDENTIFIER_LIST_NO_COMMA
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  casmi_parser::stack_symbol_type&
  casmi_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 84: // SPECIFICATION
        value.copy< Ast* > (that.value);
        break;

      case 86: // BODY_ELEMENTS
      case 141: // STATEMENTS
        value.copy< AstListNode* > (that.value);
        break;

      case 87: // BODY_ELEMENT
      case 120: // SCOPE
      case 121: // RULE_STMT
      case 122: // RULE_SYNTAX
      case 125: // SIMPLE_STMT
      case 126: // STATEMENT
      case 130: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (that.value);
        break;

      case 106: // VALUE
      case 107: // UNDEFINED
      case 108: // BOOLEAN
      case 109: // NUMBER
      case 114: // NUMBER_RANGE
      case 137: // CASE_VALUE
        value.copy< AtomNode* > (that.value);
        break;

      case 119: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (that.value);
        break;

      case 138: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 134: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 129: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (that.value);
        break;

      case 90: // ENUM_SYNTAX
        value.copy< Enum* > (that.value);
        break;

      case 105: // ATOM
      case 118: // EXPRESSION
        value.copy< ExpressionBase* > (that.value);
        break;

      case 76: // "floating"
        value.copy< FLOATING_T > (that.value);
        break;

      case 111: // FLOATING_NUMBER
        value.copy< FloatingAtom* > (that.value);
        break;

      case 148: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 91: // DERIVED_SYNTAX
      case 92: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 77: // "integer"
        value.copy< INTEGER_T > (that.value);
        break;

      case 142: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 88: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 110: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 143: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 147: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 131: // PRINT_SYNTAX
      case 132: // DEBUG_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 146: // PUSH_SYNTAX
        value.copy< PushNode* > (that.value);
        break;

      case 112: // RATIONAL_NUMBER
        value.copy< RationalAtom* > (that.value);
        break;

      case 85: // HEADER
        value.copy< SpecificationNode* > (that.value);
        break;

      case 96: // PARAM
      case 100: // TYPE_SYNTAX
        value.copy< Type* > (that.value);
        break;

      case 127: // ASSERT_SYNTAX
      case 128: // ASSURE_SYNTAX
      case 139: // SEQ_SYNTAX
      case 140: // PAR_SYNTAX
      case 149: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 133: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 78: // "rational"
        value.copy< rational_t > (that.value);
        break;

      case 136: // CASE_LABEL
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 104: // INITIALIZER
        value.copy< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 124: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 95: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 79: // "string"
      case 80: // "identifier"
      case 113: // RULEREF
        value.copy< std::string > (that.value);
        break;

      case 115: // LISTCONST
      case 116: // EXPRESSION_LIST
      case 117: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 97: // PARAM_LIST
      case 98: // PARAM_LIST_NO_COMMA
      case 99: // TYPE_IDENTIFIER_STARLIST
      case 101: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (that.value);
        break;

      case 135: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 102: // INITIALIZERS
      case 103: // INITIALIZER_LIST
        value.copy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 123: // DUMPSPEC_LIST
        value.copy< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 93: // IDENTIFIER_LIST
      case 94: // IDENTIFIER_LIST_NO_COMMA
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
  casmi_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  casmi_parser::yy_print_ (std::ostream& yyo,
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
  casmi_parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  casmi_parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  casmi_parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  casmi_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  casmi_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  casmi_parser::debug_level_type
  casmi_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  casmi_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline casmi_parser::state_type
  casmi_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  casmi_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  casmi_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  casmi_parser::parse ()
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
    #line 53 "../../obj/src/GrammarParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
}

#line 871 "GrammarParser.cpp" // lalr1.cc:741

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
      case 84: // SPECIFICATION
        yylhs.value.build< Ast* > ();
        break;

      case 86: // BODY_ELEMENTS
      case 141: // STATEMENTS
        yylhs.value.build< AstListNode* > ();
        break;

      case 87: // BODY_ELEMENT
      case 120: // SCOPE
      case 121: // RULE_STMT
      case 122: // RULE_SYNTAX
      case 125: // SIMPLE_STMT
      case 126: // STATEMENT
      case 130: // IMPOSSIBLE_SYNTAX
        yylhs.value.build< AstNode* > ();
        break;

      case 106: // VALUE
      case 107: // UNDEFINED
      case 108: // BOOLEAN
      case 109: // NUMBER
      case 114: // NUMBER_RANGE
      case 137: // CASE_VALUE
        yylhs.value.build< AtomNode* > ();
        break;

      case 119: // FUNCTION_SYNTAX
        yylhs.value.build< BaseFunctionAtom* > ();
        break;

      case 138: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 134: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 129: // DIEDIE_SYNTAX
        yylhs.value.build< DiedieNode* > ();
        break;

      case 90: // ENUM_SYNTAX
        yylhs.value.build< Enum* > ();
        break;

      case 105: // ATOM
      case 118: // EXPRESSION
        yylhs.value.build< ExpressionBase* > ();
        break;

      case 76: // "floating"
        yylhs.value.build< FLOATING_T > ();
        break;

      case 111: // FLOATING_NUMBER
        yylhs.value.build< FloatingAtom* > ();
        break;

      case 148: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 91: // DERIVED_SYNTAX
      case 92: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 77: // "integer"
        yylhs.value.build< INTEGER_T > ();
        break;

      case 142: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 88: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 110: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 143: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 147: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 131: // PRINT_SYNTAX
      case 132: // DEBUG_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 146: // PUSH_SYNTAX
        yylhs.value.build< PushNode* > ();
        break;

      case 112: // RATIONAL_NUMBER
        yylhs.value.build< RationalAtom* > ();
        break;

      case 85: // HEADER
        yylhs.value.build< SpecificationNode* > ();
        break;

      case 96: // PARAM
      case 100: // TYPE_SYNTAX
        yylhs.value.build< Type* > ();
        break;

      case 127: // ASSERT_SYNTAX
      case 128: // ASSURE_SYNTAX
      case 139: // SEQ_SYNTAX
      case 140: // PAR_SYNTAX
      case 149: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 133: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 78: // "rational"
        yylhs.value.build< rational_t > ();
        break;

      case 136: // CASE_LABEL
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 104: // INITIALIZER
        yylhs.value.build< std::pair<ExpressionBase*, ExpressionBase*> > ();
        break;

      case 124: // DUMPSPEC
        yylhs.value.build< std::pair<std::string, std::vector<std::string>> > ();
        break;

      case 95: // FUNCTION_SIGNATURE
        yylhs.value.build< std::pair<std::vector<Type*>, Type*> > ();
        break;

      case 79: // "string"
      case 80: // "identifier"
      case 113: // RULEREF
        yylhs.value.build< std::string > ();
        break;

      case 115: // LISTCONST
      case 116: // EXPRESSION_LIST
      case 117: // EXPRESSION_LIST_NO_COMMA
        yylhs.value.build< std::vector<ExpressionBase*>* > ();
        break;

      case 97: // PARAM_LIST
      case 98: // PARAM_LIST_NO_COMMA
      case 99: // TYPE_IDENTIFIER_STARLIST
      case 101: // TYPE_SYNTAX_LIST
        yylhs.value.build< std::vector<Type*> > ();
        break;

      case 135: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 102: // INITIALIZERS
      case 103: // INITIALIZER_LIST
        yylhs.value.build< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
        break;

      case 123: // DUMPSPEC_LIST
        yylhs.value.build< std::vector<std::pair<std::string, std::vector<std::string>>> > ();
        break;

      case 93: // IDENTIFIER_LIST
      case 94: // IDENTIFIER_LIST_NO_COMMA
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
#line 341 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 356 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 361 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
      yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode(NodeType::OPTION);
  }
#line 1202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new EnumDefNode(yylhs.location, yystack_[0].value.as< Enum* > ());
  }
#line 1210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new FunctionDefNode(yylhs.location, yystack_[0].value.as< Function* > ());
      
      if( yystack_[0].value.as< Function* > ()->is_builtin() )
      {
          driver.error(yylhs.location, "cannot use `"+yystack_[0].value.as< Function* > ()->name+"` as function identifier because it is a builtin name");
      }
      try
      {
          driver.add(yystack_[0].value.as< Function* > ());
      }
      catch( const IdentifierAlreadyUsed& e )
      {
          driver.error(yylhs.location, e.what());
          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[0].value.as< Function* > ();
      }
  }
#line 1234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< Function* > ()->binding_offsets = std::move(driver.binding_offsets);
      driver.binding_offsets.clear();
      yylhs.value.as< AstNode* > () = new FunctionDefNode(yylhs.location, yystack_[0].value.as< Function* > ());
      try
      {
          driver.add(yystack_[0].value.as< Function* > ());
      }
      catch( const IdentifierAlreadyUsed& e )
      {
          driver.error(yylhs.location, e.what());
          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[0].value.as< Function* > ();
      }
  }
#line 1255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 415 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 419 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
      // TODO check, we trust bison to pass only RuleNodes up
      try
      {
          driver.add(reinterpret_cast<RuleNode*>(yystack_[0].value.as< AstNode* > ()));
      }
      catch( const IdentifierAlreadyUsed& e )
      {
          driver.error( yylhs.location, e.what() );
          // we do not need to delete $1 here, because it's already in
          // the AST, so it will be deleted later
      }
  }
#line 1282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 451 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Enum* > () = new Enum(yystack_[4].value.as< std::string > (), yylhs.location);
      try
      {
          driver.function_table.add(yylhs.value.as< Enum* > ());
      }
      catch( const SymbolAlreadyExists& e )
      {
          driver.error( yylhs.location, e.what() );
      }
      for( const std::string& name : yystack_[1].value.as< std::vector<std::string> > () )
      {
          if( yylhs.value.as< Enum* > ()->add_enum_element(name) )
          {
              try
              {
                  driver.function_table.add_enum_element( name, yylhs.value.as< Enum* > () );
              }
              catch( const SymbolAlreadyExists& e )
              {
                  driver.error( yylhs.location, e.what() );
              }
          }
          else
          {
              driver.error( yylhs.location, "name `"+name+"` already used in enum" );
          }
      }
  }
#line 1324 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 485 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: 2nd argument should be a reference
      yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 490 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 498 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 502 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 506 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 514 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > ());
      yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 519 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > ());
      yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 524 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 528 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 535 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 539 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
      yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 552 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
      yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      /* this constructor is implementation dependant! */
      std::vector<Type*> foo;
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 567 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 575 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
      // TODO: fail for rules without types and print warnings
      yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1480 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1488 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 596 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1496 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 604 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: limit memory size
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 627 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 635 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1566 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 693 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
      yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 716 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr;
  }
#line 1668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 744 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector< std::pair<ExpressionBase*, ExpressionBase* > >();
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1701 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 761 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1709 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 769 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 773 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 777 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 781 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 793 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1757 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 797 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); 
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 829 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 837 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 841 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1837 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 849 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1845 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 853 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1853 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 857 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 865 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 869 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 873 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
      yystack_[0].value.as< IntegerAtom* > ()->val_ *= (-1);
  }
#line 1886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 882 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1902 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
      yystack_[0].value.as< FloatingAtom* > ()->val_ *= (-1);
  }
#line 1911 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1919 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1927 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< rational_t > ().numerator *= -1;
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1936 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 1944 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new NumberRangeAtom( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< ExpressionBase* > () );
  }
#line 1952 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1960 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 1968 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 944 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1993 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 961 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::ADD );
  }
#line 2010 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 2018 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MUL );
  }
#line 2026 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::DIV );
  }
#line 2034 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MOD );
  }
#line 2042 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::RAT_DIV );
  }
#line 2050 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::NEQ );
  }
#line 2058 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::EQ );
  }
#line 2066 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSER );
  }
#line 2074 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATER );
  }
#line 2082 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSEREQ );
  }
#line 2090 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATEREQ );
  }
#line 2098 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::OR );
  }
#line 2106 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::XOR );
  }
#line 2114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::AND );
  }
#line 2122 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1030 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), nullptr, ExpressionOperation::NOT );
  }
#line 2130 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1034 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2138 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1042 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2146 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2154 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1050 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2169 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1065 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2177 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1069 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1077 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1081 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      stmts->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2203 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1091 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2211 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2219 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1099 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2227 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1103 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2236 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1108 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2245 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1113 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2254 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1122 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1136 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2280 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1144 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1148 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1152 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1156 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2312 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1160 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1168 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1172 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1176 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1180 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1184 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1188 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1200 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2400 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1204 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1208 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.error
      ( yylhs.location
      , "invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
      , libcasm_fe::Codes::SyntaxErrorInvalidStatement
      );
  }
#line 2420 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1228 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2428 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1232 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2436 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1240 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2444 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1248 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2452 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1256 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1260 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2468 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1276 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2476 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1284 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2484 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1292 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[1].value.as< std::string > () );
  }
#line 2492 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1300 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1321 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1329 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[0].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[1].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2530 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::vector< std::pair< AtomNode*, AstNode* > >();
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1343 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1355 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // equivalent to 'default' 
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1360 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1364 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1368 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1372 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 2596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1376 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 2604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1384 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2620 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1392 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2628 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1428 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2677 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1433 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2686 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2694 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2702 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto var = Symbol( yystack_[1].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET );
      try
      {
          driver.function_table.add( &var );      
      }
      catch( const SymbolAlreadyExists& e)
      {
          driver.error( yylhs.location, e.what() );
      }
  }
#line 2718 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[5].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2727 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto var = Symbol( yystack_[3].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET );
      try
      {
          driver.function_table.add( &var );
      }
      catch( const SymbolAlreadyExists& e)
      {
          driver.error( yylhs.location, e.what() );
      }
  }
#line 2743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[7].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2767 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1508 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2790 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2798 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1539 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2806 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2810 "GrammarParser.cpp" // lalr1.cc:859
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
  casmi_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  casmi_parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int casmi_parser::yypact_ninf_ = -288;

  const signed char casmi_parser::yytable_ninf_ = -108;

  const short int
  casmi_parser::yypact_[] =
  {
      15,   -54,    36,   530,  -288,  -288,    -5,    18,    39,    61,
      64,   -18,   530,  -288,  -288,  -288,  -288,  -288,  -288,  -288,
    -288,    33,    31,    -2,     3,    69,    48,  -288,    82,   635,
      24,    95,   123,   129,   430,    28,  -288,   155,   168,   -52,
     220,   152,  -288,  -288,  -288,  -288,   635,   128,   162,   635,
     553,   153,  -288,  -288,  -288,  -288,   184,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,   908,  -288,
     -22,   183,  -288,   195,   198,   207,   211,    69,    69,    78,
    -288,   430,   430,   635,   635,   635,  -288,  -288,   200,   201,
     430,    -9,   635,   635,   635,   203,   635,   209,   430,   430,
      76,   193,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,
    -288,  -288,     6,   239,   210,   213,    95,   236,   242,   270,
    -288,  -288,  -288,    11,   197,   635,  -288,  -288,  -288,    -4,
      -4,   635,  -288,  -288,  -288,   747,  -288,   274,   271,   758,
    -288,   594,   635,   635,   635,   635,   635,   635,   635,   635,
     635,   635,   635,   635,   635,   635,   635,   635,    95,    95,
      27,   252,   -36,   635,   278,   283,   430,   129,  -288,  -288,
    -288,   304,   331,   908,   908,   908,    66,   319,  -288,   635,
     292,   519,    87,   908,   635,   717,   314,   356,   405,   635,
     129,   430,     7,    48,  -288,  -288,    95,    95,   667,   788,
     818,  -288,  -288,   635,   635,  -288,   303,   908,   205,   945,
     919,    19,   248,   337,   237,   349,   150,  -288,   294,    55,
     956,   424,   976,   908,   311,  -288,   635,    95,  -288,   -25,
     -25,   301,   318,   -26,   908,  -288,   312,  -288,  -288,  -288,
    -288,  -288,  -288,    95,   635,   848,   635,   430,   332,   908,
     209,   209,  -288,  -288,   908,   156,  -288,   129,   430,   220,
    -288,  -288,  -288,   104,  -288,   320,  -288,  -288,   908,   878,
    -288,   635,   908,   342,    95,  -288,  -288,   -25,   315,   635,
     345,   508,   348,   353,   372,   -10,  -288,  -288,   430,   158,
    -288,  -288,  -288,   699,   699,  -288,   908,   635,  -288,   354,
    -288,   448,  -288,   430,   635,  -288,   430,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,   351,   -10,   350,  -288,   430,  -288,
    -288,   908,  -288,   430,   635,  -288,   357,  -288,  -288,  -288,
     430,  -288,  -288,   478,  -288,  -288,   430,  -288
  };

  const unsigned char
  casmi_parser::yydefact_[] =
  {
       0,     0,     0,     0,     3,     1,     0,     0,     0,     0,
       0,     0,     2,     5,    10,     6,     7,     9,     8,    11,
      12,     0,     0,     0,     0,     0,     0,     4,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,    26,     0,
      24,     0,    64,    67,    69,    68,     0,     0,     0,     0,
       0,     0,    76,    73,    79,    61,   107,   106,    55,    65,
      66,    60,    70,    71,    72,    59,    63,    62,    16,    54,
       0,    32,    36,     0,    33,    40,     0,     0,     0,     0,
     121,     0,     0,     0,     0,   145,   146,   138,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     139,     0,   112,   114,   113,   123,   124,   125,   126,   128,
     127,   129,   130,   131,   110,   111,   132,   133,   134,   135,
     136,   137,     0,     0,     0,    25,     0,     0,    39,     0,
      23,    13,   105,     0,     0,     0,    74,    77,    80,     0,
       0,     0,    81,    75,    78,     0,    85,     0,    86,    89,
      82,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,     0,     0,     0,     0,   140,   141,
     170,     0,     0,   142,   143,   144,     0,     0,   180,     0,
     164,     0,     0,   147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,    29,     0,    38,     0,     0,
       0,    56,    84,    87,     0,   108,     0,    89,   104,   102,
     103,    95,    90,    91,    97,    98,    99,    92,    93,    94,
      96,   100,   101,    17,     0,    31,     0,     0,    35,     0,
       0,    46,     0,     0,    19,    14,     0,   117,   120,   166,
     169,   168,   173,     0,     0,     0,     0,     0,     0,   148,
       0,     0,   167,   165,   149,     0,   115,     0,     0,    22,
      30,    37,    48,     0,    51,    52,    57,    58,    88,     0,
     109,     0,    15,     0,    45,    42,    41,     0,     0,     0,
       0,     0,   162,     0,   171,     0,   177,   178,     0,     0,
     116,    21,    47,    50,     0,    83,    20,     0,    44,     0,
     122,     0,   175,     0,     0,   163,     0,   154,   155,   159,
     156,   157,   158,   160,     0,   152,     0,   118,     0,    49,
      53,    18,    43,     0,     0,   179,     0,   172,   150,   151,
       0,   119,   174,     0,   161,   153,     0,   176
  };

  const short int
  casmi_parser::yypgoto_[] =
  {
    -288,  -288,  -288,  -288,   406,  -288,  -288,  -288,  -288,  -288,
     144,  -288,   217,   256,   398,  -288,   227,     4,   154,   176,
    -288,   134,  -204,  -288,  -287,  -274,  -272,   -38,   -28,   -41,
    -288,  -288,  -288,  -140,  -288,    30,   -34,   -33,  -171,  -288,
    -193,   275,   -31,   -88,  -288,  -288,  -288,  -288,  -288,  -288,
    -288,  -288,   130,  -288,  -288,  -288,  -288,  -288,    57,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  -288
  };

  const short int
  casmi_parser::yydefgoto_[] =
  {
      -1,     2,     3,    12,    13,    14,    15,    16,    17,    18,
      37,    38,    40,    72,    73,    74,   127,   128,   242,   130,
     273,   274,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,   147,   148,   217,    69,   178,   103,    19,
      79,    80,   179,   180,   105,   106,   107,   108,   109,   110,
     111,   112,   324,   325,   326,   113,   114,   115,   181,   116,
     117,   289,   334,   118,   119,   120,   121
  };

  const short int
  casmi_parser::yytable_[] =
  {
     101,   102,   188,   104,   275,   247,   138,   265,   320,   136,
     143,   216,    33,   239,   240,   200,   267,   126,     1,   137,
     144,   321,   317,   322,   239,   240,     4,   286,    75,   167,
     266,    43,    44,    45,    25,    76,     5,   168,   320,   133,
     134,    53,   287,   189,    75,   139,   140,   101,   101,    32,
     318,   321,    53,   322,    34,    35,   101,   201,   268,    68,
     133,   134,    26,   196,   101,   101,    52,    53,    54,   319,
      56,   190,    52,    53,   299,    20,   132,    70,   236,   145,
     149,   122,    29,    30,   161,   162,   237,    52,    53,    54,
      31,    28,   138,   250,   250,   136,   143,   300,    21,   275,
     330,   136,   143,   155,    71,   137,   144,    39,    71,   250,
     250,   137,   144,   183,   184,   185,   293,   252,   258,    22,
     161,   162,   191,   192,   193,   253,   195,   327,   151,   176,
     205,   152,   153,   154,   243,   155,   156,   157,   158,   182,
     177,    23,   101,   102,    24,   104,  -107,   101,   101,    36,
     159,   160,   161,   162,   163,   197,   198,   341,   164,   165,
     166,   302,    41,   101,   101,   209,   303,   101,   102,   294,
     104,   210,   234,   235,   336,    75,   241,   133,   134,    77,
     135,    78,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   155,   156,
     157,   136,   143,   244,    52,    53,    54,   298,   124,   328,
     270,   139,   140,   159,   141,   161,   162,   163,   177,   255,
     177,   174,   175,   101,   259,   335,   296,   297,   337,   264,
     125,   129,   131,   150,   101,   102,   151,   104,    52,    53,
     142,   283,   169,   278,   279,   342,   139,   140,   170,   309,
     153,   154,   345,   155,   156,   157,   158,   290,   347,   172,
     171,   323,   173,   199,   101,   102,   282,   104,   159,   160,
     161,   162,   163,    52,    53,   142,   164,   165,   166,   101,
     186,   187,   101,   194,   291,   155,   156,   157,   241,    56,
     203,   323,   202,   204,   101,   102,   155,   104,   157,   101,
     159,   160,   161,   162,   163,   206,   101,   207,   164,   165,
     166,   306,   101,   161,   162,   163,    81,   249,    82,   311,
      83,    84,    85,    86,    87,    88,   208,    89,    90,   212,
      91,    92,    71,   213,    93,   245,   246,   331,    94,    95,
      96,   254,    97,    81,   256,    82,   251,    83,    84,    85,
      86,    87,    88,   261,    89,    90,   280,    91,    92,   161,
      98,    93,   281,   284,   343,    94,    95,    96,    81,    97,
      82,   285,    83,    84,    85,    86,    87,    88,    99,    89,
      90,   288,    91,    92,   100,   155,    93,    98,   295,   304,
      94,    95,    96,   307,    97,   310,   312,   155,   156,   157,
     314,   316,   161,   162,   163,    99,   315,   332,   338,   340,
     344,   100,    98,   262,   161,   162,   163,    81,    27,    82,
     269,    83,    84,    85,    86,    87,    88,   238,    89,    90,
      99,    91,    92,   123,   271,    93,   100,   329,   308,    94,
      95,    96,    81,    97,    82,   301,    83,    84,    85,    86,
      87,    88,   248,    89,    90,   339,    91,    92,     0,     0,
      93,    98,     0,     0,    94,    95,    96,     0,    97,     0,
     333,     0,   155,   156,   157,     0,     0,     0,     0,    99,
     263,     0,     0,     0,     0,   100,    98,   159,   160,   161,
     162,   163,   152,   153,   154,     0,   155,   156,   157,   158,
     346,     0,     0,     0,    99,     0,     0,     0,     0,     0,
     100,   159,   160,   161,   162,   163,     0,     0,     0,   164,
     165,   166,   152,   153,   154,     0,   155,   156,   157,   158,
       0,     0,     0,   313,     6,     7,     8,     9,    10,     0,
      11,   159,   160,   161,   162,   163,     0,   257,     0,   164,
     165,   166,   152,   153,   154,     0,   155,   156,   157,   158,
       0,     0,     0,   152,   153,   154,     0,   155,   156,   157,
     158,   159,   160,   161,   162,   163,     0,     0,     0,   164,
     165,   166,   159,   160,   161,   162,   163,     0,     0,     0,
     164,   165,   166,    42,    43,    44,    45,     0,     0,     0,
      46,     0,    47,    48,     0,    49,     0,    50,   146,     0,
       0,     0,     0,     0,    51,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
      53,    54,    55,    56,    42,    43,    44,    45,     0,     0,
       0,    46,     0,    47,    48,     0,    49,   215,    50,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,    53,    54,    55,    56,    42,    43,    44,    45,     0,
       0,     0,    46,     0,    47,    48,     0,    49,     0,    50,
       0,     0,     0,     0,     0,     0,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    43,    44,
      45,    52,    53,    54,    55,    56,    47,    48,     0,    49,
       0,    50,     0,     0,   272,     0,     0,     0,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
      43,    44,    45,    52,    53,    54,    55,    56,    47,    48,
       0,    49,     0,    50,   260,     0,     0,     0,     0,     0,
      51,   152,   153,   154,     0,   155,   156,   157,   158,     0,
       0,     0,     0,     0,     0,    52,    53,    54,    55,    56,
     159,   160,   161,   162,   163,     0,     0,     0,   164,   165,
     166,   152,   153,   154,     0,   155,   156,   157,   158,     0,
     211,     0,   152,   153,   154,     0,   155,   156,   157,   158,
     159,   160,   161,   162,   163,     0,     0,     0,   164,   165,
     166,   159,   160,   161,   162,   163,   214,     0,     0,   164,
     165,   166,   152,   153,   154,     0,   155,   156,   157,   158,
       0,   276,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,   160,   161,   162,   163,     0,     0,     0,   164,
     165,   166,   152,   153,   154,     0,   155,   156,   157,   158,
       0,   277,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,   160,   161,   162,   163,     0,     0,     0,   164,
     165,   166,   152,   153,   154,     0,   155,   156,   157,   158,
       0,   292,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,   160,   161,   162,   163,     0,     0,     0,   164,
     165,   166,   152,   153,   154,     0,   155,   156,   157,   158,
       0,     0,     0,   305,     0,     0,     0,     0,     0,     0,
       0,   159,   160,   161,   162,   163,     0,     0,     0,   164,
     165,   166,   152,   153,   154,     0,   155,   156,   157,   158,
       0,     0,     0,     0,   153,     0,     0,   155,   156,   157,
     158,   159,   160,   161,   162,   163,     0,     0,     0,   164,
     165,   166,   159,   160,   161,   162,   163,     0,     0,     0,
     164,   165,   166,   155,   156,   157,   158,     0,     0,     0,
       0,     0,     0,     0,   155,   156,   157,     0,   159,   160,
     161,   162,   163,     0,     0,     0,   164,   165,   166,   159,
     160,   161,   162,   163,   155,   156,   157,     0,   165,   166,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   159,
     160,   161,   162,   163,     0,     0,     0,     0,   165
  };

  const short int
  casmi_parser::yycheck_[] =
  {
      34,    34,    90,    34,   208,   176,    47,   200,   295,    47,
      48,   151,     9,    49,    50,     9,     9,    69,     3,    47,
      48,   295,    32,   295,    49,    50,    80,    53,    80,    51,
     201,    41,    42,    43,    52,    31,     0,    59,   325,    49,
      50,    77,    68,    52,    80,    49,    50,    81,    82,    51,
      60,   325,    77,   325,    51,    52,    90,    51,    51,    29,
      49,    50,    80,    97,    98,    99,    76,    77,    78,    79,
      80,    80,    76,    77,   267,    80,    46,    53,    51,    49,
      50,    53,    51,    52,    65,    66,    59,    76,    77,    78,
      59,    58,   133,   181,   182,   133,   134,   268,    80,   303,
     304,   139,   140,    48,    80,   133,   134,    59,    80,   197,
     198,   139,   140,    83,    84,    85,   256,    51,    31,    80,
      65,    66,    92,    93,    94,    59,    96,   298,    52,    51,
     126,    44,    45,    46,   172,    48,    49,    50,    51,    82,
      62,    80,   176,   176,    80,   176,    70,   181,   182,    80,
      63,    64,    65,    66,    67,    98,    99,   328,    71,    72,
      73,    57,    80,   197,   198,   135,    62,   201,   201,   257,
     201,   141,   168,   169,   314,    80,   172,    49,    50,    56,
      52,    52,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,    48,    49,
      50,   239,   240,   173,    76,    77,    78,    51,    53,    51,
     206,    49,    50,    63,    52,    65,    66,    67,    62,   189,
      62,    77,    78,   257,   194,   313,   260,   261,   316,   199,
      62,    11,    80,    80,   268,   268,    52,   268,    76,    77,
      78,   237,    59,   213,   214,   333,    49,    50,    53,   287,
      45,    46,   340,    48,    49,    50,    51,   253,   346,    52,
      62,   295,    51,    70,   298,   298,   236,   298,    63,    64,
      65,    66,    67,    76,    77,    78,    71,    72,    73,   313,
      80,    80,   316,    80,   254,    48,    49,    50,   284,    80,
      80,   325,    53,    80,   328,   328,    48,   328,    50,   333,
      63,    64,    65,    66,    67,    69,   340,    65,    71,    72,
      73,   281,   346,    65,    66,    67,    12,    13,    14,   289,
      16,    17,    18,    19,    20,    21,    56,    23,    24,    55,
      26,    27,    80,    62,    30,    57,    53,   307,    34,    35,
      36,    22,    38,    12,    52,    14,    15,    16,    17,    18,
      19,    20,    21,    39,    23,    24,    53,    26,    27,    65,
      56,    30,    51,    62,   334,    34,    35,    36,    12,    38,
      14,    53,    16,    17,    18,    19,    20,    21,    74,    23,
      24,    69,    26,    27,    80,    48,    30,    56,    56,    69,
      34,    35,    36,    51,    38,    80,    51,    48,    49,    50,
      52,    29,    65,    66,    67,    74,    53,    53,    57,    59,
      53,    80,    56,    57,    65,    66,    67,    12,    12,    14,
     203,    16,    17,    18,    19,    20,    21,   171,    23,    24,
      74,    26,    27,    35,   207,    30,    80,   303,   284,    34,
      35,    36,    12,    38,    14,   269,    16,    17,    18,    19,
      20,    21,   177,    23,    24,   325,    26,    27,    -1,    -1,
      30,    56,    -1,    -1,    34,    35,    36,    -1,    38,    -1,
      22,    -1,    48,    49,    50,    -1,    -1,    -1,    -1,    74,
      75,    -1,    -1,    -1,    -1,    80,    56,    63,    64,    65,
      66,    67,    44,    45,    46,    -1,    48,    49,    50,    51,
      22,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      80,    63,    64,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    73,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    -1,    -1,    25,     4,     5,     6,     7,     8,    -1,
      10,    63,    64,    65,    66,    67,    -1,    28,    -1,    71,
      72,    73,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    -1,    -1,    44,    45,    46,    -1,    48,    49,    50,
      51,    63,    64,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    73,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      71,    72,    73,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    -1,    49,    50,    -1,    52,    -1,    54,    55,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    49,    50,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78,    79,    80,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    -1,    49,    50,    -1,    52,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    76,    77,    78,    79,    80,    49,    50,    -1,    52,
      -1,    54,    -1,    -1,    57,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    76,    77,    78,    79,    80,    49,    50,
      -1,    52,    -1,    54,    37,    -1,    -1,    -1,    -1,    -1,
      61,    44,    45,    46,    -1,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    44,    45,    46,    -1,    48,    49,    50,    51,    -1,
      53,    -1,    44,    45,    46,    -1,    48,    49,    50,    51,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    63,    64,    65,    66,    67,    68,    -1,    -1,    71,
      72,    73,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    73,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    73,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    73,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    73,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    63,    64,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    73,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      71,    72,    73,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    71,    72,    73,    63,
      64,    65,    66,    67,    48,    49,    50,    -1,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    72
  };

  const unsigned char
  casmi_parser::yystos_[] =
  {
       0,     3,    84,    85,    80,     0,     4,     5,     6,     7,
       8,    10,    86,    87,    88,    89,    90,    91,    92,   122,
      80,    80,    80,    80,    80,    52,    80,    87,    58,    51,
      52,    59,    51,     9,    51,    52,    80,    93,    94,    59,
      95,    80,    40,    41,    42,    43,    47,    49,    50,    52,
      54,    61,    76,    77,    78,    79,    80,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   118,   119,
      53,    80,    96,    97,    98,    80,   100,    56,    52,   123,
     124,    12,    14,    16,    17,    18,    19,    20,    21,    23,
      24,    26,    27,    30,    34,    35,    36,    38,    56,    74,
      80,   119,   120,   121,   125,   127,   128,   129,   130,   131,
     132,   133,   134,   138,   139,   140,   142,   143,   146,   147,
     148,   149,    53,    97,    53,    62,    69,    99,   100,    11,
     102,    80,   118,    49,    50,    52,   110,   111,   112,    49,
      50,    52,    78,   110,   111,   118,    55,   116,   117,   118,
      80,    52,    44,    45,    46,    48,    49,    50,    51,    63,
      64,    65,    66,    67,    71,    72,    73,    51,    59,    59,
      53,    62,    52,    51,    93,    93,    51,    62,   120,   125,
     126,   141,   141,   118,   118,   118,    80,    80,   126,    52,
      80,   118,   118,   118,    80,   118,   119,   141,   141,    70,
       9,    51,    53,    80,    80,   100,    69,    65,    56,   118,
     118,    53,    55,    62,    68,    53,   116,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   100,   100,    51,    59,    96,    49,
      50,   100,   101,   110,   118,    57,    53,   121,   124,    13,
     126,    15,    51,    59,    22,   118,    52,    28,    31,   118,
      37,    39,    57,    75,   118,   123,   121,     9,    51,    95,
     100,    99,    57,   103,   104,   105,    53,    53,   118,   118,
      53,    51,   118,   100,    62,    53,    53,    68,    69,   144,
     100,   118,    53,   116,   126,    56,   119,   119,    51,   123,
     121,   102,    57,    62,    69,    55,   118,    51,   101,   110,
      80,   118,    51,    25,    52,    53,    29,    32,    60,    79,
     107,   108,   109,   119,   135,   136,   137,   121,    51,   104,
     105,   118,    53,    22,   145,   126,   116,   126,    57,   135,
      59,   121,   126,   118,    53,   126,    22,   126
  };

  const unsigned char
  casmi_parser::yyr1_[] =
  {
       0,    83,    84,    85,    86,    86,    87,    87,    87,    87,
      87,    87,    88,    89,    90,    91,    91,    91,    91,    91,
      91,    92,    92,    92,    92,    93,    93,    94,    94,    95,
      95,    96,    96,    97,    97,    98,    98,    99,    99,    99,
     100,   100,   100,   100,   101,   101,   101,   102,   102,   103,
     103,   103,   104,   104,   105,   105,   105,   105,   105,   106,
     106,   106,   106,   106,   106,   106,   106,   107,   108,   108,
     109,   109,   109,   110,   110,   110,   111,   111,   111,   112,
     112,   112,   113,   114,   115,   115,   116,   116,   117,   117,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   119,   119,   119,
     120,   120,   121,   121,   122,   122,   122,   122,   122,   122,
     123,   123,   124,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     126,   126,   127,   128,   129,   129,   130,   131,   132,   133,
     134,   135,   135,   136,   137,   137,   137,   137,   137,   137,
     137,   138,   138,   138,   138,   139,   139,   140,   140,   141,
     141,   142,   142,   144,   143,   145,   143,   146,   147,   148,
     149
  };

  const unsigned char
  casmi_parser::yyr2_[] =
  {
       0,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     5,     6,     7,     4,     6,     9,     6,
       8,     7,     6,     4,     3,     2,     1,     3,     1,     3,
       4,     3,     1,     1,     2,     3,     1,     3,     2,     1,
       1,     4,     4,     6,     3,     2,     1,     4,     3,     3,
       2,     1,     1,     3,     1,     1,     3,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     2,     5,     3,     2,     1,     2,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     3,     4,
       1,     1,     1,     1,     4,     6,     7,     6,     8,     9,
       3,     1,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     1,     1,     2,     3,     3,
       6,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     7,     4,     5,     2,     3,     3,     3,     3,     2,
       1,     4,     6,     0,     7,     0,     9,     4,     4,     6,
       2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const casmi_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"option\"", "\"derived\"", "\"enum\"", "\"rule\"", "\"dumps\"",
  "\"function\"", "\"initially\"", "\"seq\"", "\"endseq\"", "\"par\"",
  "\"endpar\"", "\"assert\"", "\"assure\"", "\"diedie\"", "\"impossible\"",
  "\"skip\"", "\"let\"", "\"in\"", "\"forall\"", "\"iterate\"", "\"do\"",
  "\"call\"", "\"if\"", "\"then\"", "\"else\"", "\"case\"", "\"of\"",
  "\"default\"", "\"endcase\"", "\"print\"", "\"debug\"", "\"push\"",
  "\"into\"", "\"pop\"", "\"from\"", "\"self\"", "\"undef\"", "\"false\"",
  "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"not\"", "\"div\"",
  "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"",
  "\"}\"", "\".\"", "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"",
  "\"*\"", "\"/\"", "\"%\"", "\"..\"", "\"->\"", "\":=\"", "\"!=\"",
  "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"floating\"", "\"integer\"",
  "\"rational\"", "\"string\"", "\"identifier\"", "UPLUS", "UMINUS",
  "$accept", "SPECIFICATION", "HEADER", "BODY_ELEMENTS", "BODY_ELEMENT",
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
  casmi_parser::yyrline_[] =
  {
       0,   340,   340,   348,   355,   360,   369,   373,   377,   397,
     414,   418,   437,   445,   450,   484,   489,   493,   497,   501,
     505,   513,   518,   523,   527,   534,   538,   546,   551,   560,
     566,   574,   580,   591,   595,   603,   608,   616,   621,   626,
     634,   657,   670,   692,   710,   715,   719,   727,   731,   739,
     743,   747,   756,   760,   768,   772,   776,   780,   784,   792,
     796,   800,   804,   808,   812,   816,   820,   828,   836,   840,
     848,   852,   856,   864,   868,   872,   881,   885,   889,   898,
     902,   906,   915,   923,   931,   935,   943,   947,   955,   960,
     969,   973,   977,   981,   985,   989,   993,   997,  1001,  1005,
    1009,  1013,  1017,  1021,  1025,  1029,  1033,  1041,  1045,  1049,
    1064,  1068,  1076,  1080,  1090,  1094,  1098,  1102,  1107,  1112,
    1121,  1126,  1135,  1143,  1147,  1151,  1155,  1159,  1163,  1167,
    1171,  1175,  1179,  1183,  1187,  1191,  1195,  1199,  1203,  1207,
    1227,  1231,  1239,  1247,  1255,  1259,  1275,  1283,  1291,  1299,
    1320,  1328,  1333,  1342,  1350,  1354,  1359,  1363,  1367,  1371,
    1375,  1383,  1387,  1391,  1395,  1403,  1407,  1415,  1419,  1427,
    1432,  1441,  1445,  1455,  1454,  1472,  1471,  1492,  1507,  1530,
    1538
  };

  // Print the state stack on the debug stream.
  void
  casmi_parser::yystack_print_ ()
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
  casmi_parser::yy_reduce_print_ (int yyrule)
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
#line 3577 "GrammarParser.cpp" // lalr1.cc:1167
#line 1544 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void yy::casmi_parser::error
( const location_type& l
, const std::string& m
)
{
    driver.error( l, m, libcasm_fe::Codes::SyntaxError );
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
