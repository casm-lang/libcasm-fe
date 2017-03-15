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

    #include "src/Lexer.h"
    #include "src/Exceptions.h"

    #include "../stdhl/cpp/Type.h"

    #undef yylex
    #define yylex lexer.nextToken

    std::pair< FunctionDefinition::Classification, bool > parseFunctionAttributes(
        const NodeList< IdentifierNode >::Ptr& attributes )
    {
        using Classification = FunctionDefinition::Classification;

        auto functionClass = Classification::CONTROLLED;
        bool symbolicFunction = false;

        bool classAttributeAlreadyUsed = false;
        IdentifierNode::Ptr classAttribute;

        bool symbolicAttributeAlreadyUsed = false;
        IdentifierNode::Ptr symbolicAttribute;

        for( const auto& attribute : *attributes )
        {
            const auto& name = attribute->identifier();

            if( name == "symbolic" )
            {
                symbolicFunction = true;

                if( symbolicAttributeAlreadyUsed )
                {
                    /*driver.error
                    ( { symbolicAttribute->location(), attribute->location() }
                    , "`symbolic` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfSymbolic
                    ); TODO */
                }
                else
                {
                    symbolicAttributeAlreadyUsed = true;
                    symbolicAttribute = attribute;
                }

                continue;
            }

            if( name == "in" or name == "monitored" )
            {
                functionClass = Classification::IN;
            }
            else if( name == "controlled" )
            {
                functionClass = Classification::CONTROLLED;
            }
            else if( name == "shared" )
            {
                functionClass = Classification::SHARED;
            }
            else if( name == "out" )
            {
                functionClass = Classification::OUT;
            }
            else if( name == "static" )
            {
                functionClass = Classification::STATIC;
            }
            else
            {
                /*driver.error
                ( attribute->location()
                , "`" + name + "` is no valid function attribute, only in, monitored, "
                + "controlled, shared, out, static and symbolic are allowed"
                , libcasm_fe::Codes::FunctionAttributeIsInvalid
                ); TODO */
            }

            if( classAttributeAlreadyUsed )
            {
                /*driver.error
                ( { classAttribute->location(), attribute->location() }
                , "a function classifier attribute can only be used once per function"
                , libcasm_fe::Codes::FunctionAttributeMultipleUseOfFunctionClassifier
                ); TODO */
            }
            else
            {
                classAttributeAlreadyUsed = true;
                classAttribute = attribute;
            }
        }

        return { functionClass, symbolicFunction };
    }

    static FunctionDefinition::Ptr createProgramFunction( location& location )
    {
        //auto argTypes = { new Type( TypeType::AGENT ) }; // TODO add args and return type
        //auto retType = new Type( TypeType::RuleReference );

        const auto program = make< IdentifierNode >( location, "program" );
        return make< FunctionDefinition >( location, program, nullptr, nullptr );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& location = rule->location();
        const auto rules = make< Rules >( location );
        rules->add( rule );
        return make< BlockRule >( location, rules );
    }

#line 173 "GrammarParser.cpp" // lalr1.cc:413


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

#line 31 "../../obj/src/GrammarParser.yy" // lalr1.cc:479
namespace libcasm_fe {
#line 259 "GrammarParser.cpp" // lalr1.cc:479

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
  Parser::Parser (Lexer& lexer_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg)
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
      case 101: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 137: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 140: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 132: // CaseLabel
        value.move< CaseRule::Case > (that.value);
        break;

      case 131: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 102: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 123: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 130: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 80: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 81: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 121: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 93: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 125: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 115: // Term
      case 116: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 119: // Terms
      case 120: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 103: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 135: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 94: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 122: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 136: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 134: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 118: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 117: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 104: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 127: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 126: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 114: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 128: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 138: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 129: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 79: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 100: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 107: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 124: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 89: // Initializer
      case 139: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 97: // Variable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
        value.move< std::string > (that.value);
        break;

      case 133: // CaseLabels
        value.move< std::vector< CaseRule::Case > > (that.value);
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
      case 101: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 137: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 140: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 132: // CaseLabel
        value.copy< CaseRule::Case > (that.value);
        break;

      case 131: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 102: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 123: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 130: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 80: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 81: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 121: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 93: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 125: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 115: // Term
      case 116: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 119: // Terms
      case 120: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 103: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 135: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 94: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 122: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 136: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 134: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 118: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 117: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 104: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 127: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 126: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 114: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 128: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 138: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 129: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 79: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 100: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 107: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 124: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 89: // Initializer
      case 139: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 97: // Variable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
        value.copy< std::string > (that.value);
        break;

      case 133: // CaseLabels
        value.copy< std::vector< CaseRule::Case > > (that.value);
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
    #line 59 "../../obj/src/GrammarParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
}

#line 943 "GrammarParser.cpp" // lalr1.cc:741

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
            symbol_type yylookahead (yylex ());
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
      case 101: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 137: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 140: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 132: // CaseLabel
        yylhs.value.build< CaseRule::Case > ();
        break;

      case 131: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 102: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 123: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 130: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 80: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 81: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 92: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 121: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 93: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 125: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 115: // Term
      case 116: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 119: // Terms
      case 120: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 103: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 135: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 94: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 122: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 136: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 134: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 118: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 117: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 104: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 127: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 126: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 114: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 128: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 138: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 129: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 79: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 100: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 107: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 124: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 89: // Initializer
      case 139: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 97: // Variable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
        yylhs.value.build< std::string > ();
        break;

      case 133: // CaseLabels
        yylhs.value.build< std::vector< CaseRule::Case > > ();
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
#line 373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      /*const std::string& filepath = driver.get_filename();
      const std::string& filename
          = filepath.substr( filepath.find_last_of( "/\\" ) + 1 );
      const std::string& filenameWithoutExtension
          = filename.substr( 0, filename.rfind( "." ) );*/

      const auto name = make< IdentifierNode >( yylhs.location, "filenameWithoutExtension" );
      const auto specification = make< Specification >( yylhs.location, name, yystack_[0].value.as< Definitions::Ptr > () );

      //driver.result = specification; TODO
  }
#line 1268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 394 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1284 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1292 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 402 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1300 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1310 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< IdentifierNode::Ptr > ();

      auto function = make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< Type::Ptr > () );

      const auto attributes = parseFunctionAttributes( yystack_[7].value.as< NodeList< IdentifierNode >::Ptr > () );
      function->setClassification( attributes.first );
      function->setSymbolic( attributes.second );

      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
           initializer->function()->setIdentifier( identifier );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1345 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1353 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1361 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 459 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1369 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1377 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 471 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1385 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1395 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 485 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 495 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = make< Types >( yylhs.location );
  }
#line 1421 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 507 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 511 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1437 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 519 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      auto arguments = make< Expressions >( yylhs.location );
      // TODO add `default` agent to arguments
      const auto program = make< DirectCallExpression >(
          yylhs.location, programDefinition->identifier(), arguments );

      const auto ruleReference = make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );

      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1458 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 536 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier( programDefinition->identifier() );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto arguments = make< Expressions >( yylhs.location );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1488 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 562 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1535 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 601 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1543 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1551 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 613 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1559 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 621 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 629 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 637 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 643 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = make< NodeList< IdentifierNode > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 653 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[0].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 657 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 665 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), nullptr ); // TODO
  }
#line 1627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1637 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 683 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 693 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 697 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 709 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1679 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 713 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 717 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 725 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1703 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 733 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1711 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 741 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1719 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 749 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1727 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 763 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 773 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 777 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1763 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 781 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 789 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1787 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 793 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1795 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 797 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1811 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1819 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1828 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 822 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1837 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 831 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1846 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 840 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1855 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 845 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1864 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 854 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 863 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1882 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 872 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1891 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 881 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto ruleName = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
      yylhs.value.as< RuleReferenceAtom::Ptr > () = make< RuleReferenceAtom >( yylhs.location, ruleName );
  }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1908 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 894 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1916 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1924 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1932 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1940 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 910 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1948 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1956 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1964 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1972 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 930 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1980 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1988 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1996 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 942 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto zero = make< ZeroAtom >( yylhs.location );
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, zero, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2005 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 947 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2013 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 951 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2021 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 955 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2029 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 959 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2037 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 963 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2045 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 967 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 2053 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 971 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2061 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 975 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2069 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 979 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2077 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 983 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2085 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 987 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2093 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 991 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2101 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 995 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2109 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 999 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2117 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1003 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2125 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1007 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2133 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1011 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2141 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1020 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2149 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1028 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, expressions );
  }
#line 2158 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, expressions );
  }
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1039 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1052 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2195 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1061 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2203 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1065 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2212 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), arguments );
  }
#line 2221 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1079 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2229 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1087 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2237 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2245 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1103 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2253 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1111 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2261 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1119 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), nullptr,
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) ); // TODO nullptr -> void
  }
#line 2270 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1124 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1137 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1141 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1145 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1149 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1153 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1157 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1161 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2343 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1169 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1177 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2369 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2379 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1193 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = make< SkipRule >( yylhs.location );
  }
#line 2387 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1201 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2395 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1205 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2403 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1213 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< std::vector< CaseRule::Case > > () );
  }
#line 2411 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1221 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2420 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1226 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1231 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2437 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1239 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = std::move( yystack_[0].value.as< std::vector< CaseRule::Case > > () );
      yylhs.value.as< std::vector< CaseRule::Case > > ().push_back( yystack_[1].value.as< CaseRule::Case > () );
  }
#line 2446 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1244 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = { yystack_[0].value.as< CaseRule::Case > () };
  }
#line 2454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1252 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1260 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2470 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1268 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2478 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1276 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1280 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2494 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1288 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2502 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1292 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2510 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1300 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2518 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1308 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2528 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1314 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1321 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2549 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1327 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2560 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2564 "GrammarParser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -105;

  const signed char Parser::yytable_ninf_ = -77;

  const short int
  Parser::yypact_[] =
  {
      14,    95,    20,   -44,   -48,   -48,   -48,     5,  -105,    95,
    -105,  -105,  -105,  -105,  -105,  -105,   830,  -105,  -105,     6,
      18,     6,   -48,   -48,  -105,   -48,   885,   -48,  -105,  -105,
    -105,   885,   885,   885,   445,   555,    -7,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,    45,    25,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,    66,  1165,  -105,  -105,
      48,  -105,  -105,  -105,  -105,  -105,   -48,    56,    72,     4,
    -105,    75,    84,    80,    89,   118,   610,   974,   122,   102,
    -105,  1345,  -105,  -105,   885,    59,  1195,   665,  -105,    -1,
     720,  -105,   830,  -105,   775,  -105,   885,   885,   885,   885,
     885,   885,   885,   885,   885,   885,   885,   885,   885,   885,
     885,   885,   885,   885,  -105,     3,   -48,   -48,   433,   -48,
     -48,  -105,   -48,   -48,   885,    82,   885,   885,    97,  -105,
    -105,  -105,  -105,     1,  -105,   885,  -105,  -105,    17,  -105,
     218,  1435,   -20,  1375,    21,  1454,    93,    93,    12,    12,
      12,   102,  1225,  1454,    93,    93,  1225,  -105,   -48,   -35,
     103,  -105,  -105,  -105,  -105,    87,   433,   433,  -105,   -48,
     -48,   433,   -41,   885,   885,    91,   433,   433,    86,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,   110,  -105,    98,   100,  -105,  -105,  1105,  1043,  1135,
     112,  -105,    10,  -105,   -48,   885,   885,  -105,  -105,   305,
     365,   119,   144,  -105,  -105,  -105,  1009,  1075,   378,   397,
     885,   433,   -48,   -48,   885,   885,   885,  -105,  -105,  -105,
      19,  1255,  1225,  -105,  -105,  -105,   885,   885,   433,   116,
    -105,  -105,  1225,  -105,  -105,   153,   102,  1225,   102,  -105,
     -48,   885,   885,   909,   939,   140,   500,   120,   156,  -105,
    1405,   433,   433,   433,   123,   126,  1285,   500,   121,   885,
     129,  -105,   885,  -105,  -105,  -105,   433,   433,   433,  -105,
    -105,  1315,   830,  -105,  -105,  -105,  -105,   132,  -105
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    20,     8,     2,
       3,    10,     4,     6,     5,     1,    29,    32,    21,    42,
       0,    42,    36,     0,     7,     0,     0,     0,    61,    63,
      62,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      69,    68,    64,    27,    28,     0,   109,    79,    59,    60,
      58,    54,    55,    56,    57,    53,     0,    23,    78,    77,
       0,    71,    72,    73,    74,    75,     0,     0,     0,     0,
      34,    35,     0,     0,    38,     0,     0,    76,     0,   100,
      81,    76,    83,   108,     0,     0,    76,     0,   102,     0,
       0,    70,     0,    22,     0,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    40,     0,     0,     0,     0,     0,
       0,    19,    18,     0,     0,     0,     0,     0,     0,    82,
     106,    80,   107,     0,   103,     0,   104,    26,     0,    84,
      98,    96,    97,    99,    85,    91,    92,    93,    86,    87,
      88,    89,    24,    90,    94,    95,    25,    41,     0,    47,
       0,    43,    44,    45,    46,     0,     0,     0,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,   149,
     115,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,     0,    33,    17,     0,    16,    37,    76,    76,    76,
       0,   105,     0,    39,     0,     0,     0,    31,   128,     0,
       0,     0,     0,   140,   146,   148,    76,    76,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   111,   101,    52,
       0,    76,    30,   144,   127,   142,     0,     0,     0,     0,
     141,   143,   145,   116,    15,    14,   113,   112,   114,    48,
       0,    49,     0,    76,    76,   130,     0,     0,    12,    51,
      76,     0,     0,     0,     0,     0,    76,   137,     0,     0,
       0,     9,    50,   138,   139,   131,     0,     0,     0,   136,
     132,    76,    29,   133,   134,   135,    13,     0,    11
  };

  const short int
  Parser::yypgoto_[] =
  {
    -105,  -105,   160,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,    90,  -105,  -104,  -105,  -105,     2,    69,  -105,   -25,
    -105,   162,   -91,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,   -21,   -16,  -105,
    -105,   152,   -45,     8,    78,  -105,  -105,  -105,  -105,    96,
     -61,  -105,  -105,  -105,  -105,   -79,  -105,  -105,  -105,  -105,
    -105,  -105,  -105
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     8,     9,    10,   271,   258,   193,   194,    23,
      11,    43,    44,    45,    12,    13,    46,    71,    72,    75,
     115,    67,   160,   161,   162,   163,   164,   230,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    81,    58,
      59,    87,    60,    61,    62,    63,    64,    65,    14,   208,
     209,   181,   182,   183,   267,   268,   184,   185,   186,   187,
     188,   189,   190
  };

  const short int
  Parser::yytable_[] =
  {
      57,    95,    78,   175,    16,    18,    19,    20,    21,   204,
      77,    80,    82,    85,    89,    79,    97,     1,    86,   205,
      15,   -76,   101,   102,    70,    73,    17,    74,   191,    74,
      17,   195,   196,    17,   103,   104,   105,   106,   107,   108,
      96,   114,    96,   110,   111,   112,   134,   118,   157,    22,
      66,    96,   130,   -76,   201,   125,   158,   228,    96,   135,
      86,    68,   -76,   128,   249,   119,   133,    91,    74,   133,
     130,   108,   250,   138,    93,   139,    57,   105,   106,   107,
     108,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,    92,     3,
      96,     4,     5,     6,   129,     7,   210,    96,   197,   113,
     198,   199,   130,   229,   202,   218,   219,   116,   159,    70,
     117,   159,   192,    96,   159,   159,   178,   129,   120,   121,
     122,   244,   245,   203,   -76,   101,   207,   124,    96,   123,
     120,   127,   200,   -76,   211,   212,   206,    84,   220,   105,
     106,   107,   108,   221,   222,   227,    94,   216,   217,   259,
      74,   223,   236,   237,   256,   257,   263,   270,   269,    24,
     280,    74,    74,   276,   178,   178,   277,   282,   287,   178,
     214,   288,   137,    69,   178,   178,   165,    90,   279,   231,
     232,     0,     0,     0,     0,     0,   179,     0,     0,     0,
       0,     0,     0,     0,   242,     0,   159,     0,   246,   247,
     248,     0,     0,     0,   180,     0,     0,   178,   178,     0,
     253,   254,     0,     0,   159,   159,   178,   178,     0,   178,
       0,     0,     0,     0,     0,   147,   260,     0,     0,     0,
     266,     0,     0,     0,   179,   179,   178,     0,     0,   179,
     215,   266,   159,   281,   179,   179,   147,     0,     0,   -76,
     101,   102,     0,     0,     0,     0,    57,   213,     0,   178,
     178,   178,   103,   104,   105,   106,   107,   108,     0,     0,
       0,   110,   111,   112,   178,   178,   178,   179,   179,     0,
       0,     0,     0,     0,     0,     0,   179,   179,     0,   179,
       0,     0,     0,     0,     0,   234,   234,     0,     0,     0,
       0,     0,     0,     0,   234,   234,   179,   243,   166,   233,
     167,     0,   168,   169,     0,   170,   171,     0,   172,   173,
       0,     0,   174,     0,   255,     0,     0,     0,     0,   179,
     179,   179,     0,     0,     0,     0,     0,     0,     0,   175,
       0,     0,     0,   176,   179,   179,   179,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   177,   283,   284,   285,     0,     0,     0,   166,    17,
     167,   235,   168,   169,     0,   170,   171,     0,   172,   173,
       0,   166,   174,   167,     0,   168,   169,     0,   170,   171,
       0,   172,   173,     0,     0,   174,     0,     0,     0,   175,
     166,     0,   167,   176,   168,   169,     0,   170,   171,     0,
     172,   173,   175,     0,   174,     0,   176,   240,     0,     0,
       0,   177,     0,     0,     0,     0,     0,     0,     0,    17,
       0,   175,     0,     0,   177,   176,   166,     0,   167,     0,
     168,   169,    17,   170,   171,     0,   172,   173,     0,     0,
     174,     0,     0,   177,   241,    25,     0,     0,     0,    26,
       0,    17,     0,     0,     0,     0,    27,   175,    28,    29,
      30,   176,     0,     0,     0,    31,    32,    33,     0,    76,
      83,    35,     0,     0,     0,     0,     0,    36,     0,   177,
       0,    84,     0,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,    37,    38,    39,    40,    41,    42,    17,
      25,     0,     0,     0,    26,     0,     0,     0,     0,   264,
       0,    27,     0,    28,    29,    30,     0,     0,     0,     0,
      31,    32,    33,     0,    76,     0,    35,     0,     0,     0,
       0,   265,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,    41,    42,    17,    25,     0,     0,     0,    26,
       0,     0,     0,     0,     0,     0,    27,     0,    28,    29,
      30,     0,     0,     0,     0,    31,    32,    33,     0,    76,
       0,    35,    88,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,    41,    42,    17,
      25,     0,     0,     0,    26,     0,     0,     0,     0,     0,
       0,    27,     0,    28,    29,    30,     0,     0,     0,     0,
      31,    32,    33,     0,    76,     0,    35,     0,     0,     0,
       0,     0,    36,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,    41,    42,    17,    25,     0,     0,     0,    26,
       0,     0,     0,     0,     0,     0,    27,     0,    28,    29,
      30,     0,     0,     0,     0,    31,    32,    33,     0,    76,
     132,    35,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,    41,    42,    17,
      25,     0,     0,     0,    26,     0,     0,     0,     0,     0,
       0,    27,     0,    28,    29,    30,     0,     0,     0,     0,
      31,    32,    33,     0,    76,     0,    35,   136,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,    41,    42,    17,    25,     0,     0,     0,    26,
       0,     0,     0,     0,     0,     0,    27,     0,    28,    29,
      30,     0,     0,     0,     0,    31,    32,    33,     0,    76,
      83,    35,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,    41,    42,    17,
      25,     0,     0,     0,    26,     0,     0,     0,     0,     0,
       0,    27,     0,    28,    29,    30,     0,     0,     0,     0,
      31,    32,    33,     0,    34,     0,    35,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,    41,    42,    17,    25,     0,     0,     0,    26,
       0,     0,     0,     0,     0,     0,    27,     0,    28,    29,
      30,     0,     0,     0,     0,    31,    32,    33,   261,    76,
       0,    35,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,    97,    98,    99,   100,     0,
       0,   101,   102,    37,    38,    39,    40,    41,    42,    17,
       0,   262,     0,   103,   104,   105,   106,   107,   108,     0,
       0,     0,   110,   111,   112,    97,    98,    99,   100,     0,
       0,   101,   102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   103,   104,   105,   106,   107,   108,   126,
       0,     0,   110,   111,   112,     0,     0,     0,     0,     0,
      97,    98,    99,   100,     0,     0,   101,   102,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   103,   104,
     105,   106,   107,   108,   238,     0,     0,   110,   111,   112,
       0,     0,     0,     0,     0,    97,    98,    99,   100,     0,
       0,   101,   102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   103,   104,   105,   106,   107,   108,   225,
       0,     0,   110,   111,   112,     0,     0,     0,     0,    97,
      98,    99,   100,     0,     0,   101,   102,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   103,   104,   105,
     106,   107,   108,   239,     0,     0,   110,   111,   112,     0,
       0,    97,    98,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,   224,     0,     0,   110,   111,
     112,    97,    98,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,     0,     0,   226,   110,   111,
     112,    97,    98,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,     0,     0,     0,   110,   111,
     112,    97,    98,    99,   100,     0,   -76,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,     0,   109,     0,   110,   111,
     112,    97,    98,    99,   100,     0,     0,   101,   102,     0,
     131,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,     0,     0,     0,   110,   111,
     112,    97,    98,    99,   100,     0,   -76,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,     0,     0,     0,   110,   111,
     112,    97,    98,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     251,   105,   106,   107,   108,   252,     0,     0,   110,   111,
     112,    97,    98,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,   278,     0,     0,     0,   103,
     104,   105,   106,   107,   108,     0,     0,     0,   110,   111,
     112,    97,    98,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,   286,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,     0,     0,     0,   110,   111,
     112,    97,    98,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,     0,     0,     0,   110,   111,
     112,    97,    98,    99,     0,     0,   -76,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,     0,     0,     0,   110,   111,
     112,    97,    98,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     272,   105,   106,   107,   108,     0,     0,     0,   110,   111,
     112,    97,     0,    99,     0,     0,   -76,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,   -76,   101,     0,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,   103,   104,
     105,   106,   107,   108,     0,     0,     0,     0,   111,   112
  };

  const short int
  Parser::yycheck_[] =
  {
      16,    46,    27,    44,    48,     3,     4,     5,     6,    44,
      26,    32,    33,    34,    35,    31,    36,     3,    34,    54,
       0,    41,    42,    43,    22,    23,    74,    25,   119,    27,
      74,   122,   123,    74,    54,    55,    56,    57,    58,    59,
      41,    66,    41,    63,    64,    65,    47,    43,    45,    44,
      44,    41,    53,    41,    53,    76,    53,    47,    41,    60,
      76,    43,    41,    84,    45,    61,    87,    74,    66,    90,
      53,    59,    53,    94,    49,    96,    92,    56,    57,    58,
      59,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,    53,     4,
      41,     6,     7,     8,    45,    10,   167,    41,   124,    61,
     126,   127,    53,   204,   135,   176,   177,    61,   116,   117,
      48,   119,   120,    41,   122,   123,   118,    45,    53,    45,
      50,   222,   223,   158,    41,    42,    49,    19,    41,    50,
      53,    19,    45,    41,   169,   170,    43,    56,    62,    56,
      57,    58,    59,    43,    56,   200,    44,   173,   174,   250,
     158,    61,    43,    19,    48,    12,    26,    11,    48,     9,
      49,   169,   170,    50,   166,   167,    50,    48,   282,   171,
     172,    49,    92,    21,   176,   177,   117,    35,   267,   205,
     206,    -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   220,    -1,   204,    -1,   224,   225,
     226,    -1,    -1,    -1,   118,    -1,    -1,   209,   210,    -1,
     236,   237,    -1,    -1,   222,   223,   218,   219,    -1,   221,
      -1,    -1,    -1,    -1,    -1,   251,   252,    -1,    -1,    -1,
     256,    -1,    -1,    -1,   166,   167,   238,    -1,    -1,   171,
     172,   267,   250,   269,   176,   177,   272,    -1,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,   282,   171,    -1,   261,
     262,   263,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    63,    64,    65,   276,   277,   278,   209,   210,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   218,   219,    -1,   221,
      -1,    -1,    -1,    -1,    -1,   209,   210,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   218,   219,   238,   221,    13,    14,
      15,    -1,    17,    18,    -1,    20,    21,    -1,    23,    24,
      -1,    -1,    27,    -1,   238,    -1,    -1,    -1,    -1,   261,
     262,   263,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    48,   276,   277,   278,   261,   262,   263,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,   276,   277,   278,    -1,    -1,    -1,    13,    74,
      15,    16,    17,    18,    -1,    20,    21,    -1,    23,    24,
      -1,    13,    27,    15,    -1,    17,    18,    -1,    20,    21,
      -1,    23,    24,    -1,    -1,    27,    -1,    -1,    -1,    44,
      13,    -1,    15,    48,    17,    18,    -1,    20,    21,    -1,
      23,    24,    44,    -1,    27,    -1,    48,    49,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      -1,    44,    -1,    -1,    66,    48,    13,    -1,    15,    -1,
      17,    18,    74,    20,    21,    -1,    23,    24,    -1,    -1,
      27,    -1,    -1,    66,    67,    20,    -1,    -1,    -1,    24,
      -1,    74,    -1,    -1,    -1,    -1,    31,    44,    33,    34,
      35,    48,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    66,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      -1,    46,    47,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    19,    44,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    -1,
      -1,    42,    43,    68,    69,    70,    71,    72,    73,    74,
      -1,    22,    -1,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    63,    64,    65,    36,    37,    38,    39,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    25,
      -1,    -1,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    25,    -1,    -1,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    26,
      -1,    -1,    63,    64,    65,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    28,    -1,    -1,    63,    64,    65,    -1,
      -1,    36,    37,    38,    39,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    30,    -1,    -1,    63,    64,
      65,    36,    37,    38,    39,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    32,    63,    64,
      65,    36,    37,    38,    39,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    64,
      65,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    61,    -1,    63,    64,
      65,    36,    37,    38,    39,    -1,    -1,    42,    43,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    64,
      65,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    64,
      65,    36,    37,    38,    39,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    64,
      65,    36,    37,    38,    39,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    64,
      65,    36,    37,    38,    39,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    64,
      65,    36,    37,    38,    39,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    64,
      65,    36,    37,    38,    -1,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    64,
      65,    36,    37,    38,    39,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    64,
      65,    36,    -1,    38,    -1,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    41,    42,    -1,    63,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    64,    65
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    79,     4,     6,     7,     8,    10,    80,    81,
      82,    88,    92,    93,   126,     0,    48,    74,    94,    94,
      94,    94,    44,    87,    80,    20,    24,    31,    33,    34,
      35,    40,    41,    42,    44,    46,    52,    68,    69,    70,
      71,    72,    73,    89,    90,    91,    94,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     120,   121,   122,   123,   124,   125,    44,    99,    43,    99,
      94,    95,    96,    94,    94,    97,    44,   116,    97,   116,
     115,   116,   115,    45,    56,   115,   116,   119,    47,   115,
     119,    74,    53,    49,    44,   120,    41,    36,    37,    38,
      39,    42,    43,    54,    55,    56,    57,    58,    59,    61,
      63,    64,    65,    61,    97,    98,    61,    48,    43,    61,
      53,    45,    50,    50,    19,   115,    25,    19,   115,    45,
      53,    45,    45,   115,    47,    60,    47,    89,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,    45,    53,    94,
     100,   101,   102,   103,   104,    95,    13,    15,    17,    18,
      20,    21,    23,    24,    27,    44,    48,    66,   121,   122,
     127,   129,   130,   131,   134,   135,   136,   137,   138,   139,
     140,   100,    94,    85,    86,   100,   100,   116,   116,   116,
      45,    53,   115,    97,    44,    54,    43,    49,   127,   128,
     128,    97,    97,   127,   121,   122,   116,   116,   128,   128,
      62,    43,    56,    61,    30,    26,    32,   120,    47,   100,
     105,   116,   116,    14,   127,    16,    43,    19,    25,    28,
      49,    67,   116,   127,   100,   100,   116,   116,   116,    45,
      53,    55,    60,   116,   116,   127,    48,    12,    84,   100,
     116,    19,    22,    26,    29,    51,   116,   132,   133,    48,
      11,    83,    55,   127,   127,   127,    50,    50,    50,   133,
      49,   116,    48,   127,   127,   127,    49,    91,    49
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    78,    79,    80,    80,    80,    80,    81,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    89,    89,    90,    90,    91,    91,
      92,    93,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   100,   100,   101,   102,   103,
     104,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     106,   107,   108,   108,   109,   110,   110,   111,   112,   113,
     114,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   117,   118,   118,   118,   119,   119,   120,   120,   121,
     121,   122,   123,   124,   125,   126,   126,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   128,   128,   129,
     130,   130,   131,   132,   132,   132,   133,   133,   134,   135,
     136,   137,   137,   138,   138,   139,   140,   140,   140,   140
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     2,     1,     9,
       1,     4,     0,     4,     0,     3,     1,     1,     0,     3,
       0,     2,     4,     1,     3,     3,     3,     1,     1,     0,
       7,     6,     1,     3,     1,     1,     0,     3,     1,     3,
       1,     3,     0,     1,     1,     1,     1,     1,     4,     4,
       6,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     5,     2,     3,     3,     3,     2,     3,     2,     1,
       2,     5,     6,     6,     6,     5,     7,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       4,     6,     6,     3,     3,     3,     2,     1,     6,     6,
       2,     3,     3,     3,     3,     3,     2,     1,     2,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"option\"", "\"derived\"", "\"enum\"", "\"rule\"", "\"dumps\"",
  "\"function\"", "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"",
  "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"iterate\"", "\"do\"", "\"call\"", "\"if\"", "\"then\"", "\"else\"",
  "\"case\"", "\"of\"", "\"default\"", "\"holds\"", "\"exists\"",
  "\"with\"", "\"undef\"", "\"false\"", "\"true\"", "\"and\"", "\"or\"",
  "\"xor\"", "\"implies\"", "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"",
  "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\":\"", "\"_\"", "\"@\"",
  "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"..\"",
  "\"->\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"",
  "\"binary\"", "\"hexadecimal\"", "\"integer\"", "\"rational\"",
  "\"floating\"", "\"string\"", "\"identifier\"", "UPLUS", "UMINUS",
  "DIRECT_CALL_EXPR_NO_ARG", "$accept", "Specification", "Definition",
  "Definitions", "FunctionDefinition", "MaybeInitially", "MaybeDefined",
  "FunctionParameters", "MaybeFunctionParameters",
  "MaybeFunctionAttributes", "ProgramFunctionDefinition", "Initializer",
  "Initializers", "MaybeInitializers", "DerivedDefinition",
  "EnumerationDefinition", "Identifier", "Identifiers", "MaybeIdentifiers",
  "Variable", "Parameters", "MaybeParameters", "Type", "BasicType",
  "ComposedType", "FixedSizedType", "RangedType", "Types", "Atom",
  "Undefined", "Boolean", "String", "BitNumber", "IntegerNumber",
  "FloatingNumber", "RationalNumber", "RuleReference", "Term",
  "Expression", "Range", "List", "Terms", "Arguments",
  "DirectCallExpression", "IndirectCallExpression",
  "ConditionalExpression", "UniversalQuantifierExpression",
  "ExistentialQuantifierExpression", "RuleDefinition", "Rule", "Rules",
  "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels",
  "LetRule", "ForallRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   372,   372,   389,   393,   397,   401,   409,   415,   425,
     446,   454,   458,   466,   470,   478,   484,   494,   498,   506,
     510,   518,   535,   552,   561,   572,   584,   590,   600,   604,
     612,   620,   628,   636,   642,   652,   656,   664,   668,   676,
     682,   692,   696,   704,   708,   712,   716,   724,   732,   740,
     748,   756,   762,   772,   776,   780,   784,   788,   792,   796,
     800,   808,   816,   821,   830,   839,   844,   853,   862,   871,
     880,   889,   893,   897,   901,   905,   909,   913,   917,   921,
     929,   933,   937,   941,   946,   950,   954,   958,   962,   966,
     970,   974,   978,   982,   986,   990,   994,   998,  1002,  1006,
    1010,  1019,  1027,  1032,  1038,  1045,  1051,  1060,  1064,  1073,
    1078,  1086,  1094,  1102,  1110,  1118,  1123,  1132,  1136,  1140,
    1144,  1148,  1152,  1156,  1160,  1164,  1168,  1176,  1182,  1192,
    1200,  1204,  1212,  1220,  1225,  1230,  1238,  1243,  1251,  1259,
    1267,  1275,  1279,  1287,  1291,  1299,  1307,  1313,  1320,  1326
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


#line 31 "../../obj/src/GrammarParser.yy" // lalr1.cc:1167
} // libcasm_fe
#line 3395 "GrammarParser.cpp" // lalr1.cc:1167
#line 1335 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void Parser::error( const location_type& l, const std::string& m )
{
    if( m.compare( "syntax error, unexpected end of file, expecting CASM" ) == 0 )
    {
        i32 pos = (l.begin.line - 1);
        pos = ( pos > 0 ? pos : 1 );

        /*driver.error
        ( location( position( 0, pos, 1 ) )
        , m
        , libcasm_fe::Codes::SyntaxError
        ); TODO */
    }
    else
    {
        //driver.error( l, m, libcasm_fe::Codes::SyntaxError ); TODO
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
