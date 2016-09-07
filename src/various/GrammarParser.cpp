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
#line 66 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

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
    #line 55 "../../obj/src/GrammarParser.yy" // lalr1.cc:741
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
#line 343 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, driver.get_filename() );
  }
#line 1176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 363 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
      yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 372 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode(NodeType::OPTION);
  }
#line 1202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 376 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new EnumDefNode(yylhs.location, yystack_[0].value.as< Enum* > ());
  }
#line 1210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new FunctionDefNode(yylhs.location, yystack_[0].value.as< Function* > ());
      
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
          driver.add(yystack_[0].value.as< Function* > ());
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
#line 1246 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< Function* > ()->binding_offsets = std::move(driver.binding_offsets);
      driver.binding_offsets.clear();
      yylhs.value.as< AstNode* > () = new FunctionDefNode(yylhs.location, yystack_[0].value.as< Function* > ());
      try
      {
          driver.add(yystack_[0].value.as< Function* > ());
      }
      catch( const Exception& e )
      {
          driver.error(yylhs.location, e.what());
          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[0].value.as< Function* > ();
      }
  }
#line 1267 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 429 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1275 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 433 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
      // TODO check, we trust bison to pass only RuleNodes up
      try
      {
          driver.add(reinterpret_cast<RuleNode*>(yystack_[0].value.as< AstNode* > ()));
      }
      catch( const Exception& e )
      {
          driver.error( yylhs.location, e.what() );
          // we do not need to delete $1 here, because it's already in
          // the AST, so it will be deleted later
      }
  }
#line 1294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 452 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Enum* > () = new Enum(yystack_[4].value.as< std::string > (), yylhs.location);
      try
      {
          driver.function_table.add(yylhs.value.as< Enum* > ());
      }
      catch( const Exception& e )
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
              catch( const Exception& e )
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
#line 1364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 527 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: 2nd argument should be a reference
      yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 536 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 544 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 548 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 556 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > ());
      yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > ());
      yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 566 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1439 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1447 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1455 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
      yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1472 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
      yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 603 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      /* this constructor is implementation dependant! */
      std::vector<Type*> foo;
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 623 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
      // TODO: fail for rules without types and print warnings
      yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1520 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1528 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 659 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: limit memory size
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1606 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 700 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 713 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 753 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
      yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 762 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1692 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1700 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 774 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr;
  }
#line 1708 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 782 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 786 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 790 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector< std::pair<ExpressionBase*, ExpressionBase* > >();
      yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 799 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 811 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1757 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 815 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 819 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 823 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 827 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 835 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 839 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 847 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 851 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 855 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1837 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 859 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); 
  }
#line 1845 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 863 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1853 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 871 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 879 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 883 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 895 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1901 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 915 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
      yystack_[0].value.as< IntegerAtom* > ()->val_ *= (-1);
  }
#line 1926 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1934 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1942 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
      yystack_[0].value.as< FloatingAtom* > ()->val_ *= (-1);
  }
#line 1951 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1959 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1967 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< rational_t > ().numerator *= -1;
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 1984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new NumberRangeAtom( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< ExpressionBase* > () );
  }
#line 1992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2000 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 2008 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2016 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2024 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2033 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 1003 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2042 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 1012 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::ADD );
  }
#line 2050 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1016 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 2058 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1020 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MUL );
  }
#line 2066 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::DIV );
  }
#line 2074 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1028 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MOD );
  }
#line 2082 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::RAT_DIV );
  }
#line 2090 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1036 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::NEQ );
  }
#line 2098 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::EQ );
  }
#line 2106 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1044 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSER );
  }
#line 2114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATER );
  }
#line 2122 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1052 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSEREQ );
  }
#line 2130 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1056 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATEREQ );
  }
#line 2138 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1060 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::OR );
  }
#line 2146 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1064 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::XOR );
  }
#line 2154 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1068 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::AND );
  }
#line 2162 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), nullptr, ExpressionOperation::NOT );
  }
#line 2170 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1076 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2178 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1107 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1111 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1119 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2233 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1123 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      stmts->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1137 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2259 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1141 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2267 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1145 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1169 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2312 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1178 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1186 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1190 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1194 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1198 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1202 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1206 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1210 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1214 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1222 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2400 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1226 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1230 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1234 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2424 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1242 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2440 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1246 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1250 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.error
      ( yylhs.location
      , "invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
      , libcasm_fe::Codes::SyntaxErrorInvalidStatement
      );
  }
#line 2460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1270 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2468 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1274 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2476 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1282 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2484 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1290 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2492 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1298 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2500 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1302 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1318 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2516 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1326 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2524 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[1].value.as< std::string > () );
  }
#line 2532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1342 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1363 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[0].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[1].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2570 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1376 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::vector< std::pair< AtomNode*, AstNode* > >();
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // equivalent to 'default' 
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1402 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2620 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2628 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1414 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 2636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1418 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 2644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2692 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2700 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1462 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2708 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1470 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1475 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2726 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2734 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1488 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2742 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[5].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2767 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1514 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2783 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1526 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[7].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1535 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1550 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2838 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1583 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2846 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2850 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int casmi_parser::yypact_ninf_ = -287;

  const signed char casmi_parser::yytable_ninf_ = -108;

  const short int
  casmi_parser::yypact_[] =
  {
      23,  -287,    49,   530,  -287,    -5,     2,    45,    64,    69,
     -18,   530,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,
      61,    32,    34,     3,    86,    48,  -287,    95,   635,    24,
      99,   125,   168,   430,    28,  -287,   169,   159,   -52,   219,
     151,  -287,  -287,  -287,  -287,   635,   128,   162,   635,   553,
     152,  -287,  -287,  -287,  -287,   181,  -287,  -287,  -287,  -287,
    -287,  -287,  -287,  -287,  -287,  -287,  -287,   908,  -287,   -22,
     177,  -287,   189,   186,   207,   209,    86,    86,    66,  -287,
     430,   430,   635,   635,   635,  -287,  -287,   182,   183,   430,
      -9,   635,   635,   635,   200,   635,   201,   430,   430,   -34,
     213,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,
    -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,
    -287,     6,   236,   210,   212,    99,   224,   240,   251,  -287,
    -287,  -287,    11,   197,   635,  -287,  -287,  -287,    -4,    -4,
     635,  -287,  -287,  -287,   747,  -287,   271,   267,   758,  -287,
     594,   635,   635,   635,   635,   635,   635,   635,   635,   635,
     635,   635,   635,   635,   635,   635,   635,    99,    99,    27,
     252,   -36,   635,   276,   282,   430,   168,  -287,  -287,  -287,
     304,   331,   908,   908,   908,    39,   314,  -287,   635,   289,
     519,    87,   908,   635,   717,   305,   356,   405,   635,   168,
     430,     7,    48,  -287,  -287,    99,    99,   667,   788,   818,
    -287,  -287,   635,   635,  -287,   300,   908,   205,   945,   919,
      96,   248,   337,   237,   349,   150,  -287,   291,    55,   956,
     424,   976,   908,   308,  -287,   635,    99,  -287,   -25,   -25,
     301,   309,   -26,   908,  -287,   302,  -287,  -287,  -287,  -287,
    -287,  -287,    99,   635,   848,   635,   430,   325,   908,   201,
     201,  -287,  -287,   908,    78,  -287,   168,   430,   219,  -287,
    -287,  -287,    84,  -287,   319,  -287,  -287,   908,   878,  -287,
     635,   908,   338,    99,  -287,  -287,   -25,   313,   635,   344,
     508,   348,   343,   372,   -10,  -287,  -287,   430,   156,  -287,
    -287,  -287,   699,   699,  -287,   908,   635,  -287,   353,  -287,
     448,  -287,   430,   635,  -287,   430,  -287,  -287,  -287,  -287,
    -287,  -287,  -287,   350,   -10,   351,  -287,   430,  -287,  -287,
     908,  -287,   430,   635,  -287,   355,  -287,  -287,  -287,   430,
    -287,  -287,   478,  -287,  -287,   430,  -287
  };

  const unsigned char
  casmi_parser::yydefact_[] =
  {
       0,     3,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     2,     5,    10,     6,     7,     9,     8,    11,    12,
       0,     0,     0,     0,     0,     0,     4,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,    26,     0,    24,
       0,    64,    67,    69,    68,     0,     0,     0,     0,     0,
       0,    76,    73,    79,    61,   107,   106,    55,    65,    66,
      60,    70,    71,    72,    59,    63,    62,    16,    54,     0,
      32,    36,     0,    33,    40,     0,     0,     0,     0,   121,
       0,     0,     0,     0,   145,   146,   138,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   139,
       0,   112,   114,   113,   123,   124,   125,   126,   128,   127,
     129,   130,   131,   110,   111,   132,   133,   134,   135,   136,
     137,     0,     0,     0,    25,     0,     0,    39,     0,    23,
      13,   105,     0,     0,     0,    74,    77,    80,     0,     0,
       0,    81,    75,    78,     0,    85,     0,    86,    89,    82,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,   140,   141,   170,
       0,     0,   142,   143,   144,     0,     0,   180,     0,   164,
       0,     0,   147,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,    29,     0,    38,     0,     0,     0,
      56,    84,    87,     0,   108,     0,    89,   104,   102,   103,
      95,    90,    91,    97,    98,    99,    92,    93,    94,    96,
     100,   101,    17,     0,    31,     0,     0,    35,     0,     0,
      46,     0,     0,    19,    14,     0,   117,   120,   166,   169,
     168,   173,     0,     0,     0,     0,     0,     0,   148,     0,
       0,   167,   165,   149,     0,   115,     0,     0,    22,    30,
      37,    48,     0,    51,    52,    57,    58,    88,     0,   109,
       0,    15,     0,    45,    42,    41,     0,     0,     0,     0,
       0,   162,     0,   171,     0,   177,   178,     0,     0,   116,
      21,    47,    50,     0,    83,    20,     0,    44,     0,   122,
       0,   175,     0,     0,   163,     0,   154,   155,   159,   156,
     157,   158,   160,     0,   152,     0,   118,     0,    49,    53,
      18,    43,     0,     0,   179,     0,   172,   150,   151,     0,
     119,   174,     0,   161,   153,     0,   176
  };

  const short int
  casmi_parser::yypgoto_[] =
  {
    -287,  -287,  -287,  -287,   398,  -287,  -287,  -287,  -287,  -287,
     132,  -287,   216,   250,   393,  -287,   227,     5,   154,   166,
    -287,   136,  -203,  -287,  -286,  -273,  -271,   -37,   -27,   -40,
    -287,  -287,  -287,  -139,  -287,    31,   -33,   -32,  -170,  -287,
    -192,   269,   -30,   -87,  -287,  -287,  -287,  -287,  -287,  -287,
    -287,  -287,   131,  -287,  -287,  -287,  -287,  -287,    58,  -287,
    -287,  -287,  -287,  -287,  -287,  -287,  -287
  };

  const short int
  casmi_parser::yydefgoto_[] =
  {
      -1,     2,     3,    11,    12,    13,    14,    15,    16,    17,
      36,    37,    39,    71,    72,    73,   126,   127,   241,   129,
     272,   273,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,   146,   147,   216,    68,   177,   102,    18,
      78,    79,   178,   179,   104,   105,   106,   107,   108,   109,
     110,   111,   323,   324,   325,   112,   113,   114,   180,   115,
     116,   288,   333,   117,   118,   119,   120
  };

  const short int
  casmi_parser::yytable_[] =
  {
     100,   101,   187,   103,   274,   246,   137,   264,   319,   135,
     142,   215,    32,   238,   239,   199,   266,   125,   150,   136,
     143,   320,   316,   321,   238,   239,     1,   285,    74,   166,
     265,    42,    43,    44,    24,    75,  -107,   167,   319,   132,
     133,    52,   286,   188,    74,   138,   139,   100,   100,     4,
     317,   320,    52,   321,    33,    34,   100,   200,   267,    67,
     132,   133,    25,   195,   100,   100,    51,    52,    53,   318,
      55,   189,    51,    52,   298,    19,   131,    69,   235,   144,
     148,   121,    20,    28,    29,    31,   236,    51,    52,    53,
     251,    30,   137,   249,   249,   135,   142,   299,   252,   274,
     329,   135,   142,   154,    70,   136,   143,    38,    70,   249,
     249,   136,   143,   182,   183,   184,   292,   175,   257,    27,
     160,   161,   190,   191,   192,    21,   194,   326,   176,   297,
     204,   151,   152,   153,   242,   154,   155,   156,   157,   181,
     176,   301,   100,   101,    22,   103,   302,   100,   100,    23,
     158,   159,   160,   161,   162,   196,   197,   340,   163,   164,
     165,   160,   161,   100,   100,   208,    35,   100,   101,   293,
     103,   209,   233,   234,   335,    40,   240,   132,   133,    74,
     134,    76,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   154,   155,
     156,   135,   142,   243,    51,    52,    53,   327,   173,   174,
     269,   138,   139,   158,   140,   160,   161,   162,   176,   254,
      77,   124,   123,   100,   258,   334,   295,   296,   336,   263,
     128,   130,   149,   150,   100,   101,   168,   103,    51,    52,
     141,   282,   169,   277,   278,   341,   138,   139,   170,   308,
     152,   153,   344,   154,   155,   156,   157,   289,   346,   171,
     172,   322,   185,   186,   100,   101,   281,   103,   158,   159,
     160,   161,   162,    51,    52,   141,   163,   164,   165,   100,
     193,    55,   100,   198,   290,   154,   155,   156,   240,   201,
     202,   322,   203,   205,   100,   101,   154,   103,   156,   100,
     158,   159,   160,   161,   162,   206,   100,   207,   163,   164,
     165,   305,   100,   160,   161,   162,    80,   248,    81,   310,
      82,    83,    84,    85,    86,    87,   211,    88,    89,   212,
      90,    91,    70,   244,    92,   245,   253,   330,    93,    94,
      95,   255,    96,    80,   260,    81,   250,    82,    83,    84,
      85,    86,    87,   279,    88,    89,   160,    90,    91,   280,
      97,    92,   284,   283,   342,    93,    94,    95,    80,    96,
      81,   287,    82,    83,    84,    85,    86,    87,    98,    88,
      89,   294,    90,    91,    99,   154,    92,    97,   303,   306,
      93,    94,    95,   309,    96,   311,   314,   154,   155,   156,
     313,   315,   160,   161,   162,    98,   331,   337,   343,    26,
     339,    99,    97,   261,   160,   161,   162,    80,   268,    81,
     237,    82,    83,    84,    85,    86,    87,   122,    88,    89,
      98,    90,    91,   270,   300,    92,    99,   307,   328,    93,
      94,    95,    80,    96,    81,   247,    82,    83,    84,    85,
      86,    87,     0,    88,    89,   338,    90,    91,     0,     0,
      92,    97,     0,     0,    93,    94,    95,     0,    96,     0,
     332,     0,   154,   155,   156,     0,     0,     0,     0,    98,
     262,     0,     0,     0,     0,    99,    97,   158,   159,   160,
     161,   162,   151,   152,   153,     0,   154,   155,   156,   157,
     345,     0,     0,     0,    98,     0,     0,     0,     0,     0,
      99,   158,   159,   160,   161,   162,     0,     0,     0,   163,
     164,   165,   151,   152,   153,     0,   154,   155,   156,   157,
       0,     0,     0,   312,     5,     6,     7,     8,     9,     0,
      10,   158,   159,   160,   161,   162,     0,   256,     0,   163,
     164,   165,   151,   152,   153,     0,   154,   155,   156,   157,
       0,     0,     0,   151,   152,   153,     0,   154,   155,   156,
     157,   158,   159,   160,   161,   162,     0,     0,     0,   163,
     164,   165,   158,   159,   160,   161,   162,     0,     0,     0,
     163,   164,   165,    41,    42,    43,    44,     0,     0,     0,
      45,     0,    46,    47,     0,    48,     0,    49,   145,     0,
       0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,    53,    54,    55,    41,    42,    43,    44,     0,     0,
       0,    45,     0,    46,    47,     0,    48,   214,    49,     0,
       0,     0,     0,     0,     0,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,    52,    53,    54,    55,    41,    42,    43,    44,     0,
       0,     0,    45,     0,    46,    47,     0,    48,     0,    49,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    42,    43,
      44,    51,    52,    53,    54,    55,    46,    47,     0,    48,
       0,    49,     0,     0,   271,     0,     0,     0,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      42,    43,    44,    51,    52,    53,    54,    55,    46,    47,
       0,    48,     0,    49,   259,     0,     0,     0,     0,     0,
      50,   151,   152,   153,     0,   154,   155,   156,   157,     0,
       0,     0,     0,     0,     0,    51,    52,    53,    54,    55,
     158,   159,   160,   161,   162,     0,     0,     0,   163,   164,
     165,   151,   152,   153,     0,   154,   155,   156,   157,     0,
     210,     0,   151,   152,   153,     0,   154,   155,   156,   157,
     158,   159,   160,   161,   162,     0,     0,     0,   163,   164,
     165,   158,   159,   160,   161,   162,   213,     0,     0,   163,
     164,   165,   151,   152,   153,     0,   154,   155,   156,   157,
       0,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,   159,   160,   161,   162,     0,     0,     0,   163,
     164,   165,   151,   152,   153,     0,   154,   155,   156,   157,
       0,   276,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,   159,   160,   161,   162,     0,     0,     0,   163,
     164,   165,   151,   152,   153,     0,   154,   155,   156,   157,
       0,   291,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,   159,   160,   161,   162,     0,     0,     0,   163,
     164,   165,   151,   152,   153,     0,   154,   155,   156,   157,
       0,     0,     0,   304,     0,     0,     0,     0,     0,     0,
       0,   158,   159,   160,   161,   162,     0,     0,     0,   163,
     164,   165,   151,   152,   153,     0,   154,   155,   156,   157,
       0,     0,     0,     0,   152,     0,     0,   154,   155,   156,
     157,   158,   159,   160,   161,   162,     0,     0,     0,   163,
     164,   165,   158,   159,   160,   161,   162,     0,     0,     0,
     163,   164,   165,   154,   155,   156,   157,     0,     0,     0,
       0,     0,     0,     0,   154,   155,   156,     0,   158,   159,
     160,   161,   162,     0,     0,     0,   163,   164,   165,   158,
     159,   160,   161,   162,   154,   155,   156,     0,   164,   165,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
     159,   160,   161,   162,     0,     0,     0,     0,   164
  };

  const short int
  casmi_parser::yycheck_[] =
  {
      33,    33,    89,    33,   207,   175,    46,   199,   294,    46,
      47,   150,     9,    49,    50,     9,     9,    69,    52,    46,
      47,   294,    32,   294,    49,    50,     3,    53,    80,    51,
     200,    41,    42,    43,    52,    30,    70,    59,   324,    49,
      50,    77,    68,    52,    80,    49,    50,    80,    81,     0,
      60,   324,    77,   324,    51,    52,    89,    51,    51,    28,
      49,    50,    80,    96,    97,    98,    76,    77,    78,    79,
      80,    80,    76,    77,   266,    80,    45,    53,    51,    48,
      49,    53,    80,    51,    52,    51,    59,    76,    77,    78,
      51,    59,   132,   180,   181,   132,   133,   267,    59,   302,
     303,   138,   139,    48,    80,   132,   133,    59,    80,   196,
     197,   138,   139,    82,    83,    84,   255,    51,    31,    58,
      65,    66,    91,    92,    93,    80,    95,   297,    62,    51,
     125,    44,    45,    46,   171,    48,    49,    50,    51,    81,
      62,    57,   175,   175,    80,   175,    62,   180,   181,    80,
      63,    64,    65,    66,    67,    97,    98,   327,    71,    72,
      73,    65,    66,   196,   197,   134,    80,   200,   200,   256,
     200,   140,   167,   168,   313,    80,   171,    49,    50,    80,
      52,    56,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,    48,    49,
      50,   238,   239,   172,    76,    77,    78,    51,    76,    77,
     205,    49,    50,    63,    52,    65,    66,    67,    62,   188,
      52,    62,    53,   256,   193,   312,   259,   260,   315,   198,
      11,    80,    80,    52,   267,   267,    59,   267,    76,    77,
      78,   236,    53,   212,   213,   332,    49,    50,    62,   286,
      45,    46,   339,    48,    49,    50,    51,   252,   345,    52,
      51,   294,    80,    80,   297,   297,   235,   297,    63,    64,
      65,    66,    67,    76,    77,    78,    71,    72,    73,   312,
      80,    80,   315,    70,   253,    48,    49,    50,   283,    53,
      80,   324,    80,    69,   327,   327,    48,   327,    50,   332,
      63,    64,    65,    66,    67,    65,   339,    56,    71,    72,
      73,   280,   345,    65,    66,    67,    12,    13,    14,   288,
      16,    17,    18,    19,    20,    21,    55,    23,    24,    62,
      26,    27,    80,    57,    30,    53,    22,   306,    34,    35,
      36,    52,    38,    12,    39,    14,    15,    16,    17,    18,
      19,    20,    21,    53,    23,    24,    65,    26,    27,    51,
      56,    30,    53,    62,   333,    34,    35,    36,    12,    38,
      14,    69,    16,    17,    18,    19,    20,    21,    74,    23,
      24,    56,    26,    27,    80,    48,    30,    56,    69,    51,
      34,    35,    36,    80,    38,    51,    53,    48,    49,    50,
      52,    29,    65,    66,    67,    74,    53,    57,    53,    11,
      59,    80,    56,    57,    65,    66,    67,    12,   202,    14,
     170,    16,    17,    18,    19,    20,    21,    34,    23,    24,
      74,    26,    27,   206,   268,    30,    80,   283,   302,    34,
      35,    36,    12,    38,    14,   176,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,   324,    26,    27,    -1,    -1,
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
       0,     3,    84,    85,     0,     4,     5,     6,     7,     8,
      10,    86,    87,    88,    89,    90,    91,    92,   122,    80,
      80,    80,    80,    80,    52,    80,    87,    58,    51,    52,
      59,    51,     9,    51,    52,    80,    93,    94,    59,    95,
      80,    40,    41,    42,    43,    47,    49,    50,    52,    54,
      61,    76,    77,    78,    79,    80,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   118,   119,    53,
      80,    96,    97,    98,    80,   100,    56,    52,   123,   124,
      12,    14,    16,    17,    18,    19,    20,    21,    23,    24,
      26,    27,    30,    34,    35,    36,    38,    56,    74,    80,
     119,   120,   121,   125,   127,   128,   129,   130,   131,   132,
     133,   134,   138,   139,   140,   142,   143,   146,   147,   148,
     149,    53,    97,    53,    62,    69,    99,   100,    11,   102,
      80,   118,    49,    50,    52,   110,   111,   112,    49,    50,
      52,    78,   110,   111,   118,    55,   116,   117,   118,    80,
      52,    44,    45,    46,    48,    49,    50,    51,    63,    64,
      65,    66,    67,    71,    72,    73,    51,    59,    59,    53,
      62,    52,    51,    93,    93,    51,    62,   120,   125,   126,
     141,   141,   118,   118,   118,    80,    80,   126,    52,    80,
     118,   118,   118,    80,   118,   119,   141,   141,    70,     9,
      51,    53,    80,    80,   100,    69,    65,    56,   118,   118,
      53,    55,    62,    68,    53,   116,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   100,   100,    51,    59,    96,    49,    50,
     100,   101,   110,   118,    57,    53,   121,   124,    13,   126,
      15,    51,    59,    22,   118,    52,    28,    31,   118,    37,
      39,    57,    75,   118,   123,   121,     9,    51,    95,   100,
      99,    57,   103,   104,   105,    53,    53,   118,   118,    53,
      51,   118,   100,    62,    53,    53,    68,    69,   144,   100,
     118,    53,   116,   126,    56,   119,   119,    51,   123,   121,
     102,    57,    62,    69,    55,   118,    51,   101,   110,    80,
     118,    51,    25,    52,    53,    29,    32,    60,    79,   107,
     108,   109,   119,   135,   136,   137,   121,    51,   104,   105,
     118,    53,    22,   145,   126,   116,   126,    57,   135,    59,
     121,   126,   118,    53,   126,    22,   126
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
       0,   342,   342,   350,   357,   362,   371,   375,   379,   411,
     428,   432,   451,   487,   492,   526,   531,   535,   539,   543,
     547,   555,   560,   565,   569,   576,   580,   588,   593,   602,
     608,   616,   622,   633,   637,   645,   650,   658,   663,   668,
     676,   699,   712,   734,   752,   757,   761,   769,   773,   781,
     785,   789,   798,   802,   810,   814,   818,   822,   826,   834,
     838,   842,   846,   850,   854,   858,   862,   870,   878,   882,
     890,   894,   898,   906,   910,   914,   923,   927,   931,   940,
     944,   948,   957,   965,   973,   977,   985,   989,   997,  1002,
    1011,  1015,  1019,  1023,  1027,  1031,  1035,  1039,  1043,  1047,
    1051,  1055,  1059,  1063,  1067,  1071,  1075,  1083,  1087,  1091,
    1106,  1110,  1118,  1122,  1132,  1136,  1140,  1144,  1149,  1154,
    1163,  1168,  1177,  1185,  1189,  1193,  1197,  1201,  1205,  1209,
    1213,  1217,  1221,  1225,  1229,  1233,  1237,  1241,  1245,  1249,
    1269,  1273,  1281,  1289,  1297,  1301,  1317,  1325,  1333,  1341,
    1362,  1370,  1375,  1384,  1392,  1396,  1401,  1405,  1409,  1413,
    1417,  1425,  1429,  1433,  1437,  1445,  1449,  1457,  1461,  1469,
    1474,  1483,  1487,  1497,  1496,  1514,  1513,  1534,  1549,  1572,
    1582
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
#line 3617 "GrammarParser.cpp" // lalr1.cc:1167
#line 1588 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
