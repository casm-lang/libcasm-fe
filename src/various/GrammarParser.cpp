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
#line 61 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

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

    static BasicType::Ptr createVoidType( location& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::VoidType >();
        const auto name = make< IdentifierNode >( sourceLocation, type->description() );
        const auto node = make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( location& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::RuleReferenceType >();
        const auto name = make< IdentifierNode >( sourceLocation, type->description() );
        const auto node = make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( location& sourceLocation )
    {
        const auto name = make< IdentifierNode >( sourceLocation, "Agent" );
        const auto node = make< BasicType >( sourceLocation, name );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( location& sourceLocation )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = make< IdentifierNode >( sourceLocation, "program" );
        return make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = make< Rules >( sourceLocation );
        rules->add( rule );
        return make< BlockRule >( sourceLocation, rules );
    }

#line 201 "GrammarParser.cpp" // lalr1.cc:413


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
#line 287 "GrammarParser.cpp" // lalr1.cc:479

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
  Parser::Parser (Lexer& lexer_yyarg, const std::string& specificationName_yyarg, Specification::Ptr& result_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      specificationName (specificationName_yyarg),
      result (result_yyarg)
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
#line 395 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto name = make< IdentifierNode >( yylhs.location, specificationName );
      result = make< Specification >( yylhs.location, name, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1321 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1331 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 473 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1380 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 481 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 485 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1396 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1406 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1424 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = make< Types >( yylhs.location );
  }
#line 1432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 521 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1440 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 525 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 550 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 567 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto arguments = make< Expressions >( yylhs.location );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 576 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1526 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1546 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 619 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 627 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1570 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 635 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1578 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 643 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1586 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 657 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = make< NodeList< IdentifierNode > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1606 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 667 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[0].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1614 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1622 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 679 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1630 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 683 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), unresolvedType );
  }
#line 1639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 698 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 708 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 724 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1739 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1759 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1767 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 792 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1775 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1783 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 800 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1791 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 804 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1799 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1823 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 824 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1840 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 837 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 846 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 855 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1867 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 860 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 869 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1903 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 896 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto ruleName = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
      yylhs.value.as< RuleReferenceAtom::Ptr > () = make< RuleReferenceAtom >( yylhs.location, ruleName );
  }
#line 1912 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 905 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1920 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 909 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1928 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 913 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1936 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 917 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1944 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 921 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1952 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 925 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1960 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1968 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 937 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2000 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2008 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto zero = make< ZeroAtom >( yylhs.location );
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, zero, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2017 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2025 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2033 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2049 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2057 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 2065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2081 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2089 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2097 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2105 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2113 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2121 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2129 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2137 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2145 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2153 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1035 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2161 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1043 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, expressions );
  }
#line 2170 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, expressions );
  }
#line 2180 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1054 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2188 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1061 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2198 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1067 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1077 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1081 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), arguments );
  }
#line 2234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1103 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2250 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1111 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2258 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1119 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2274 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1135 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2283 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1140 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2292 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1149 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2300 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1153 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2308 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1157 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2316 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1161 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2324 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2332 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1169 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2340 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1173 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2348 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1177 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1181 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1185 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1193 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1209 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = make< SkipRule >( yylhs.location );
  }
#line 2400 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1217 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1221 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1229 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< std::vector< CaseRule::Case > > () );
  }
#line 2424 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1237 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1242 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1247 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1255 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = std::move( yystack_[0].value.as< std::vector< CaseRule::Case > > () );
      yylhs.value.as< std::vector< CaseRule::Case > > ().push_back( yystack_[1].value.as< CaseRule::Case > () );
  }
#line 2459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1260 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = { yystack_[0].value.as< CaseRule::Case > () };
  }
#line 2467 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1268 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1276 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1284 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1292 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1296 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1304 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1308 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1316 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1324 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2541 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1337 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1343 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2573 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2577 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -143;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      25,   129,    26,   -35,   -34,   -34,   -34,    12,  -143,   129,
    -143,  -143,  -143,  -143,  -143,  -143,   636,  -143,  -143,    15,
      19,    15,   -34,   -34,  -143,   -34,   691,   -34,  -143,  -143,
    -143,   691,   691,   691,   416,    53,    -5,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,    17,    27,    28,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  1001,  -143,  -143,  -143,
      14,  -143,  -143,  -143,  -143,  -143,   -34,    22,    37,   -27,
    -143,    49,    58,    48,    64,    98,   526,   780,   101,  -143,
    -143,  -143,  -143,   691,  1031,    83,   -16,  -143,   971,     8,
    -143,   636,  -143,   581,  -143,   691,   691,   691,   691,   691,
     691,   691,   691,   691,   691,   691,   691,   691,   691,   691,
     691,   691,   691,  -143,    -4,   -34,   -34,   404,   -34,   -34,
    -143,   -34,   -34,   691,  1031,   691,   691,  1061,  -143,  -143,
    -143,   691,  -143,   691,  -143,  -143,  1211,   170,  1301,  1326,
    1271,    33,    33,   201,    23,    23,    72,    72,    72,  -143,
    1211,   201,    23,    23,  1211,  -143,   -34,   -19,    89,  -143,
    -143,  -143,  -143,    18,   404,   404,  -143,   -34,   -34,   404,
     -38,   691,   691,    82,   404,   404,    78,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,    99,
    -143,    85,    86,  -143,  -143,   911,   849,   941,    28,  1211,
    1091,  -143,   -34,   691,   691,  -143,  -143,    -6,    30,   100,
     125,  -143,  -143,  -143,   815,   881,   334,   349,   691,   404,
     -34,   -34,   691,   691,   691,  -143,  -143,  -143,    13,  1121,
    1211,  -143,  -143,  -143,   691,   691,   404,   102,  -143,  -143,
    1211,  -143,  -143,   136,  -143,  1211,  -143,  -143,   -34,   691,
     691,   715,   745,   123,   471,   104,   143,  -143,  1241,   404,
     404,   404,   105,   109,  1151,   471,   111,   691,   113,  -143,
     691,  -143,  -143,  -143,   404,   404,   404,  -143,  -143,  1181,
     636,  -143,  -143,  -143,  -143,   114,  -143
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    20,     8,     2,
       3,    10,     4,     6,     5,     1,    29,    32,    21,    42,
       0,    42,    36,     0,     7,     0,     0,     0,    61,    63,
      62,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      69,    68,    64,    27,    28,     0,   109,    79,    59,    60,
      58,    54,    55,    56,    57,    53,    23,    76,    78,    77,
       0,    71,    72,    73,    74,    75,     0,     0,     0,     0,
      34,    35,     0,     0,    38,     0,     0,     0,     0,   100,
      81,    83,   108,     0,   106,    76,     0,   102,   106,     0,
      70,     0,    22,     0,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,     0,     0,     0,     0,     0,     0,
      19,    18,     0,     0,     0,     0,     0,     0,    82,    80,
     107,     0,   103,     0,   104,    26,   106,    98,    96,    97,
      99,    84,    85,    91,    92,    93,    86,    87,    88,    89,
      24,    90,    94,    95,    25,    41,     0,    47,     0,    43,
      44,    45,    46,     0,     0,     0,   129,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   147,   149,   115,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,     0,
      33,    17,     0,    16,    37,     0,     0,     0,     0,   105,
       0,    39,     0,     0,     0,    31,   128,     0,     0,     0,
       0,   140,   146,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   111,   101,    52,     0,     0,
      30,   144,   127,   142,     0,     0,     0,     0,   141,   143,
     145,   116,    15,    14,   113,   112,   114,    48,     0,    49,
       0,     0,     0,   130,     0,     0,    12,    51,     0,     0,
       0,     0,     0,     0,     0,   137,     0,     0,     0,     9,
      50,   138,   139,   131,     0,     0,     0,   136,   132,     0,
      29,   133,   134,   135,    13,     0,    11
  };

  const short int
  Parser::yypgoto_[] =
  {
    -143,  -143,   157,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,    76,  -143,  -111,  -143,  -143,    -3,    73,  -143,   -22,
    -143,   167,   -91,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,    75,   -24,  -143,
    -143,   155,   -42,    45,   120,  -143,  -143,  -143,  -143,   127,
    -142,  -143,  -143,  -143,  -143,   -74,  -143,  -143,  -143,  -143,
    -143,  -143,  -143
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     8,     9,    10,   269,   256,   191,   192,    23,
      11,    43,    44,    45,    12,    13,    46,    71,    72,    75,
     114,    67,   158,   159,   160,   161,   162,   228,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    86,    60,    61,    62,    63,    64,    65,    14,   206,
     207,   179,   180,   181,   265,   266,   182,   183,   184,   185,
     186,   187,   188
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      18,    19,    20,    21,    94,    78,   173,   164,   231,   165,
      85,   166,   167,    16,   168,   169,   117,   170,   171,    70,
      73,   172,    74,   208,    74,   202,    15,   189,     1,   130,
     193,   194,   216,   217,   118,   203,    17,   131,   173,    17,
      17,   155,   174,   164,   113,   165,   233,   166,   167,   156,
     168,   169,    85,   170,   171,   134,    22,   172,   247,    66,
     175,   131,    68,    74,    99,   100,   248,   205,    17,    90,
      91,   119,    93,    25,   173,   112,    92,    26,   174,   104,
     105,   106,   107,   115,    27,   116,    28,    29,    30,   104,
     105,   106,   107,    31,    32,    33,   175,    76,   121,    35,
      87,    77,   119,   120,    17,    36,    79,    80,    81,    84,
      88,   227,   157,    70,   122,   157,   190,   123,   157,   157,
     126,    37,    38,    39,    40,    41,    42,    17,   129,   242,
     243,   107,   204,     3,   201,     4,     5,     6,    83,     7,
     218,   220,   219,   234,   235,   209,   210,   221,   255,   261,
     254,   124,   267,    74,   268,   274,   225,   257,   127,   275,
     278,   280,   176,   286,    74,    74,    24,   135,   136,   285,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,    69,   163,
      89,   277,     0,     0,     0,     0,     0,     0,   195,   157,
     196,   197,     0,     0,     0,     0,   199,     0,   200,   176,
     176,    99,   100,   101,   176,   212,     0,   157,   157,   176,
     176,     0,     0,     0,   102,   103,   104,   105,   106,   107,
       0,     0,     0,   109,   110,   111,     0,   177,     0,     0,
       0,     0,    99,   100,   178,   157,   214,   215,     0,     0,
       0,     0,   176,   176,     0,   102,   103,   104,   105,   106,
     107,   176,   176,     0,   176,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   229,   230,
       0,   176,     0,     0,   177,   177,     0,     0,     0,   177,
     213,     0,     0,   240,   177,   177,   211,   244,   245,   246,
       0,     0,     0,     0,   176,   176,   176,     0,     0,   251,
     252,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     176,   176,     0,     0,   145,   258,     0,   177,   177,   264,
       0,     0,     0,     0,   232,   232,   177,   177,     0,   177,
     264,     0,   279,   232,   232,   145,   241,   164,     0,   165,
       0,   166,   167,     0,   168,   169,   177,   170,   171,     0,
       0,   172,   164,   253,   165,     0,   166,   167,     0,   168,
     169,     0,   170,   171,     0,     0,   172,     0,   173,   177,
     177,   177,   174,   238,     0,     0,   271,   272,   273,     0,
       0,     0,     0,   173,   177,   177,   177,   174,     0,     0,
     175,   281,   282,   283,     0,     0,     0,     0,    17,     0,
       0,     0,     0,     0,     0,   175,   239,   164,     0,   165,
       0,   166,   167,    17,   168,   169,     0,   170,   171,     0,
       0,   172,     0,     0,     0,     0,    25,     0,     0,     0,
      26,     0,     0,     0,     0,     0,     0,    27,   173,    28,
      29,    30,   174,     0,     0,     0,    31,    32,    33,     0,
      76,    82,    35,     0,     0,     0,     0,     0,    36,     0,
     175,     0,    83,     0,     0,     0,     0,     0,    17,     0,
       0,     0,     0,     0,    37,    38,    39,    40,    41,    42,
      17,    25,     0,     0,     0,    26,     0,     0,     0,     0,
     262,     0,    27,     0,    28,    29,    30,     0,     0,     0,
       0,    31,    32,    33,     0,    76,     0,    35,     0,     0,
       0,     0,   263,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      38,    39,    40,    41,    42,    17,    25,     0,     0,     0,
      26,     0,     0,     0,     0,     0,     0,    27,     0,    28,
      29,    30,     0,     0,     0,     0,    31,    32,    33,     0,
      76,     0,    35,     0,     0,     0,     0,     0,    36,     0,
       0,     0,    83,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    38,    39,    40,    41,    42,
      17,    25,     0,     0,     0,    26,     0,     0,     0,     0,
       0,     0,    27,     0,    28,    29,    30,     0,     0,     0,
       0,    31,    32,    33,     0,    76,    82,    35,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      38,    39,    40,    41,    42,    17,    25,     0,     0,     0,
      26,     0,     0,     0,     0,     0,     0,    27,     0,    28,
      29,    30,     0,     0,     0,     0,    31,    32,    33,     0,
      34,     0,    35,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    38,    39,    40,    41,    42,
      17,    25,     0,     0,     0,    26,     0,     0,     0,     0,
       0,     0,    27,     0,    28,    29,    30,     0,     0,     0,
       0,    31,    32,    33,   259,    76,     0,    35,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,    95,    96,    97,    98,     0,    99,   100,   101,    37,
      38,    39,    40,    41,    42,    17,     0,   260,     0,   102,
     103,   104,   105,   106,   107,     0,     0,     0,   109,   110,
     111,    95,    96,    97,    98,     0,    99,   100,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   102,
     103,   104,   105,   106,   107,   125,     0,     0,   109,   110,
     111,     0,     0,     0,     0,     0,    95,    96,    97,    98,
       0,    99,   100,   101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   102,   103,   104,   105,   106,   107,
     236,     0,     0,   109,   110,   111,     0,     0,     0,     0,
       0,    95,    96,    97,    98,     0,    99,   100,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   102,
     103,   104,   105,   106,   107,   223,     0,     0,   109,   110,
     111,     0,     0,     0,     0,    95,    96,    97,    98,     0,
      99,   100,   101,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   102,   103,   104,   105,   106,   107,   237,
       0,     0,   109,   110,   111,     0,     0,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,   222,     0,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,     0,   224,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,     0,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,   132,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,   133,     0,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,   108,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,   128,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,     0,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,   198,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,     0,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,   226,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,     0,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   249,   104,   105,   106,
     107,   250,     0,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,   276,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,     0,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,     0,     0,
     284,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,     0,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,     0,     0,   109,   110,   111,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   270,   104,   105,   106,
     107,     0,     0,     0,   109,   110,   111,    95,    96,    97,
       0,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,     0,     0,   109,   110,   111,    95,     0,    97,
       0,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,     0,    95,     0,   109,   110,   111,    99,   100,   101,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     102,   103,   104,   105,   106,   107,     0,     0,     0,   109,
     110,   111
  };

  const short int
  Parser::yycheck_[] =
  {
       3,     4,     5,     6,    46,    27,    44,    13,    14,    15,
      34,    17,    18,    48,    20,    21,    43,    23,    24,    22,
      23,    27,    25,   165,    27,    44,     0,   118,     3,    45,
     121,   122,   174,   175,    61,    54,    74,    53,    44,    74,
      74,    45,    48,    13,    66,    15,    16,    17,    18,    53,
      20,    21,    76,    23,    24,    47,    44,    27,    45,    44,
      66,    53,    43,    66,    41,    42,    53,    49,    74,    74,
      53,    53,    44,    20,    44,    61,    49,    24,    48,    56,
      57,    58,    59,    61,    31,    48,    33,    34,    35,    56,
      57,    58,    59,    40,    41,    42,    66,    44,    50,    46,
      47,    26,    53,    45,    74,    52,    31,    32,    33,    34,
      35,   202,   115,   116,    50,   118,   119,    19,   121,   122,
      19,    68,    69,    70,    71,    72,    73,    74,    45,   220,
     221,    59,    43,     4,   156,     6,     7,     8,    56,    10,
      62,    56,    43,    43,    19,   167,   168,    61,    12,    26,
      48,    76,    48,   156,    11,    50,   198,   248,    83,    50,
      49,    48,   117,    49,   167,   168,     9,    91,    93,   280,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,    21,   116,
      35,   265,    -1,    -1,    -1,    -1,    -1,    -1,   123,   202,
     125,   126,    -1,    -1,    -1,    -1,   131,    -1,   133,   164,
     165,    41,    42,    43,   169,   170,    -1,   220,   221,   174,
     175,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    63,    64,    65,    -1,   117,    -1,    -1,
      -1,    -1,    41,    42,   117,   248,   171,   172,    -1,    -1,
      -1,    -1,   207,   208,    -1,    54,    55,    56,    57,    58,
      59,   216,   217,    -1,   219,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   203,   204,
      -1,   236,    -1,    -1,   164,   165,    -1,    -1,    -1,   169,
     170,    -1,    -1,   218,   174,   175,   169,   222,   223,   224,
      -1,    -1,    -1,    -1,   259,   260,   261,    -1,    -1,   234,
     235,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   274,
     275,   276,    -1,    -1,   249,   250,    -1,   207,   208,   254,
      -1,    -1,    -1,    -1,   207,   208,   216,   217,    -1,   219,
     265,    -1,   267,   216,   217,   270,   219,    13,    -1,    15,
      -1,    17,    18,    -1,    20,    21,   236,    23,    24,    -1,
      -1,    27,    13,   236,    15,    -1,    17,    18,    -1,    20,
      21,    -1,    23,    24,    -1,    -1,    27,    -1,    44,   259,
     260,   261,    48,    49,    -1,    -1,   259,   260,   261,    -1,
      -1,    -1,    -1,    44,   274,   275,   276,    48,    -1,    -1,
      66,   274,   275,   276,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    13,    -1,    15,
      -1,    17,    18,    74,    20,    21,    -1,    23,    24,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    44,    33,
      34,    35,    48,    -1,    -1,    -1,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      66,    -1,    56,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      29,    -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,
      -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    20,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,
      44,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    20,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,
      44,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    19,    44,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    68,
      69,    70,    71,    72,    73,    74,    -1,    22,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    64,
      65,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    25,    -1,    -1,    63,    64,
      65,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      25,    -1,    -1,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    26,    -1,    -1,    63,    64,
      65,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    28,
      -1,    -1,    63,    64,    65,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    30,    -1,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    32,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    61,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    64,    65,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    64,    65,    36,    37,    38,
      -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    64,    65,    36,    -1,    38,
      -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    36,    -1,    63,    64,    65,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    63,
      64,    65
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
      94,    95,    96,    94,    94,    97,    44,   115,    97,   115,
     115,   115,    45,    56,   115,   116,   119,    47,   115,   119,
      74,    53,    49,    44,   120,    36,    37,    38,    39,    41,
      42,    43,    54,    55,    56,    57,    58,    59,    61,    63,
      64,    65,    61,    97,    98,    61,    48,    43,    61,    53,
      45,    50,    50,    19,   115,    25,    19,   115,    45,    45,
      45,    53,    47,    60,    47,    89,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,    45,    53,    94,   100,   101,
     102,   103,   104,    95,    13,    15,    17,    18,    20,    21,
      23,    24,    27,    44,    48,    66,   121,   122,   127,   129,
     130,   131,   134,   135,   136,   137,   138,   139,   140,   100,
      94,    85,    86,   100,   100,   115,   115,   115,    45,   115,
     115,    97,    44,    54,    43,    49,   127,   128,   128,    97,
      97,   127,   121,   122,   115,   115,   128,   128,    62,    43,
      56,    61,    30,    26,    32,   120,    47,   100,   105,   115,
     115,    14,   127,    16,    43,    19,    25,    28,    49,    67,
     115,   127,   100,   100,   115,   115,   115,    45,    53,    55,
      60,   115,   115,   127,    48,    12,    84,   100,   115,    19,
      22,    26,    29,    51,   115,   132,   133,    48,    11,    83,
      55,   127,   127,   127,    50,    50,    50,   133,    49,   115,
      48,   127,   127,   127,    49,    91,    49
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
       2,     5,     2,     3,     3,     3,     1,     3,     2,     1,
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
       0,   394,   394,   403,   407,   411,   415,   423,   429,   439,
     460,   468,   472,   480,   484,   492,   498,   508,   512,   520,
     524,   532,   549,   566,   575,   586,   598,   604,   614,   618,
     626,   634,   642,   650,   656,   666,   670,   678,   682,   691,
     697,   707,   711,   719,   723,   727,   731,   739,   747,   755,
     763,   771,   777,   787,   791,   795,   799,   803,   807,   811,
     815,   823,   831,   836,   845,   854,   859,   868,   877,   886,
     895,   904,   908,   912,   916,   920,   924,   928,   932,   936,
     944,   948,   952,   956,   961,   965,   969,   973,   977,   981,
     985,   989,   993,   997,  1001,  1005,  1009,  1013,  1017,  1021,
    1025,  1034,  1042,  1047,  1053,  1060,  1066,  1076,  1080,  1089,
    1094,  1102,  1110,  1118,  1126,  1134,  1139,  1148,  1152,  1156,
    1160,  1164,  1168,  1172,  1176,  1180,  1184,  1192,  1198,  1208,
    1216,  1220,  1228,  1236,  1241,  1246,  1254,  1259,  1267,  1275,
    1283,  1291,  1295,  1303,  1307,  1315,  1323,  1329,  1336,  1342
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
#line 3384 "GrammarParser.cpp" // lalr1.cc:1167
#line 1351 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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

    std::cerr << l << ": " << m << std::endl;
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
