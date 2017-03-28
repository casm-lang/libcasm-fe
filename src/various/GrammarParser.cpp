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
      case 142: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 143: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 144: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 102: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 138: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 141: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 133: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 132: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 134: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 103: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 124: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 131: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 80: // Definition
      case 81: // AttributedDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case 82: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 93: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 122: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 94: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 126: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 85: // MaybeDefined
      case 107: // Atom
      case 116: // Term
      case 117: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 145: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 120: // Terms
      case 121: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 104: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 136: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 83: // FunctionDefinition
      case 89: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 95: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 123: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 137: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 135: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 119: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 88: // MaybeFunctionAttributes
      case 96: // Identifiers
      case 97: // MaybeIdentifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 84: // MaybeInitially
      case 91: // Initializers
      case 92: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 99: // Parameters
      case 100: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 118: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 105: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 128: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 127: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 115: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 129: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 139: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 130: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 79: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 101: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 86: // FunctionParameters
      case 87: // MaybeFunctionParameters
      case 106: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 108: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 125: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 90: // Initializer
      case 140: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 109: // Boolean
      case 110: // String
      case 111: // BitNumber
      case 112: // IntegerNumber
      case 113: // FloatingNumber
      case 114: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 98: // Variable
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
      case 142: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 143: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 144: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 102: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 138: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 141: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 133: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 132: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 134: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 103: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 124: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 131: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 80: // Definition
      case 81: // AttributedDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 82: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 93: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 122: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 94: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 126: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 85: // MaybeDefined
      case 107: // Atom
      case 116: // Term
      case 117: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 145: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 120: // Terms
      case 121: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 104: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 136: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 83: // FunctionDefinition
      case 89: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 95: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 123: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 137: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 135: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 119: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 88: // MaybeFunctionAttributes
      case 96: // Identifiers
      case 97: // MaybeIdentifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 84: // MaybeInitially
      case 91: // Initializers
      case 92: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 99: // Parameters
      case 100: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 118: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 105: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 128: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 127: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 115: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 129: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 139: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 130: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 79: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 101: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 86: // FunctionParameters
      case 87: // MaybeFunctionParameters
      case 106: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 108: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 125: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 90: // Initializer
      case 140: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 109: // Boolean
      case 110: // String
      case 111: // BitNumber
      case 112: // IntegerNumber
      case 113: // FloatingNumber
      case 114: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 98: // Variable
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
      case 142: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 143: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 144: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 102: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 138: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 141: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 133: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 132: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 134: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 103: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 124: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 131: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 80: // Definition
      case 81: // AttributedDefinition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 82: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 93: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 122: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 94: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 126: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 85: // MaybeDefined
      case 107: // Atom
      case 116: // Term
      case 117: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 145: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 120: // Terms
      case 121: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 104: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 136: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 83: // FunctionDefinition
      case 89: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 95: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 123: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 137: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 135: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 119: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 88: // MaybeFunctionAttributes
      case 96: // Identifiers
      case 97: // MaybeIdentifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 84: // MaybeInitially
      case 91: // Initializers
      case 92: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 99: // Parameters
      case 100: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 118: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 105: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 128: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 127: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 115: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 129: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 139: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 130: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 79: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 101: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 86: // FunctionParameters
      case 87: // MaybeFunctionParameters
      case 106: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 108: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 125: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 90: // Initializer
      case 140: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 109: // Boolean
      case 110: // String
      case 111: // BitNumber
      case 112: // IntegerNumber
      case 113: // FloatingNumber
      case 114: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 98: // Variable
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
#line 401 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto name = make< IdentifierNode >( yylhs.location, specificationName );
      result = make< Specification >( yylhs.location, name, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 414 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 418 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1354 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1362 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1380 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1390 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1400 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 481 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 505 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 519 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1485 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 529 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1493 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = make< Types >( yylhs.location );
  }
#line 1501 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1538 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto arguments = make< Expressions >( yylhs.location );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 596 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 607 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 619 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1605 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 625 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 635 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 639 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 647 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 655 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 663 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1665 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = make< NodeList< IdentifierNode > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 687 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[0].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 699 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 703 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), unresolvedType );
  }
#line 1708 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1718 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1744 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 744 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1760 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1768 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 752 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1776 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1784 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 768 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1800 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 784 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1808 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 792 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1818 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 798 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1828 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1844 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1852 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 820 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1860 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 824 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1868 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 828 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 836 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 844 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 852 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 857 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1918 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 866 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1927 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 875 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1936 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 880 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 889 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1954 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1963 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1972 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto ruleName = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
      yylhs.value.as< RuleReferenceAtom::Ptr > () = make< RuleReferenceAtom >( yylhs.location, ruleName );
  }
#line 1981 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 925 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1989 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1997 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2005 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 937 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2013 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2021 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2029 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2037 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2045 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2053 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 965 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2061 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 969 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2069 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 973 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2077 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2085 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2093 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2101 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2109 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2117 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 997 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2125 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1001 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 2133 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1005 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2141 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1009 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2149 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1013 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2157 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1017 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2165 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1021 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2173 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2181 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2189 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1037 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1041 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2213 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2221 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1054 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2229 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1062 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, expressions );
  }
#line 2238 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1067 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, expressions );
  }
#line 2248 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1073 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2256 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1080 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1096 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2284 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1100 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1109 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), arguments );
  }
#line 2302 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1114 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2310 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1122 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2318 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1130 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2326 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2334 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1146 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2342 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1159 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1168 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1172 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1176 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1180 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1184 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2400 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1188 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2424 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1200 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1204 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2440 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1212 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1228 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = make< SkipRule >( yylhs.location );
  }
#line 2468 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1236 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2476 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1240 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2484 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1248 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2492 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1256 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2500 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1260 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1264 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2516 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1272 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2526 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1278 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1288 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1296 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1304 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2560 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1312 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1316 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2576 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1324 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1328 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2592 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1336 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2600 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1344 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2610 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2621 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1357 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1363 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2650 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2658 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1386 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1392 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2678 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1402 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = make< BasicAttribute >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 2686 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2694 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2698 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -130;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      16,     4,    23,   -30,   -50,   -50,   -50,   -17,   -50,  -130,
    -130,     4,  -130,  -130,  -130,  -130,  -130,  -130,   696,  -130,
    -130,     9,    22,     9,   -50,   -50,   751,  -130,     7,  -130,
    -130,  -130,   -50,   751,   -50,  -130,  -130,  -130,   751,   751,
     751,   421,   531,   -23,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,    15,    10,    29,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  1061,  -130,  -130,  -130,     5,  -130,  -130,
    -130,  -130,  -130,   -50,    18,    32,   -26,  -130,    37,    46,
      44,   586,  1271,   108,   -50,    51,    83,   840,    84,  -130,
    -130,  -130,  -130,   751,  1091,    62,   -25,  -130,  1031,     8,
    -130,   696,  -130,   641,  -130,   751,   751,   751,   751,   751,
     751,   751,   751,   751,   751,   751,   751,   751,   751,   751,
     751,   751,   751,  -130,   -15,   -50,   -50,   385,   -50,   -50,
    -130,   -50,  1091,  -130,  -130,   -50,   751,   751,   751,  1121,
    -130,  -130,  -130,   751,  -130,   751,  -130,  -130,  1271,    41,
    1361,  1386,  1331,    78,    78,  1405,    30,    30,    49,    49,
      49,  -130,  1271,  1405,    30,    30,  1271,  -130,   -50,   -28,
      66,  -130,  -130,  -130,  -130,     3,   385,   385,  -130,   -50,
     -50,   385,   -29,   751,   751,    57,   385,   385,    58,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,    76,  -130,    65,    63,  -130,  -130,   971,   909,  1001,
      29,  1271,  1151,  -130,   -50,   751,   751,  -130,  -130,    19,
     307,    87,   112,  -130,  -130,  -130,   875,   941,   320,   372,
     751,   385,   -50,   -50,   751,   751,   751,  -130,  -130,  -130,
      -4,  1181,  1271,  -130,  -130,  -130,   751,   751,   385,    79,
    -130,  -130,  1271,  -130,  -130,   148,  -130,  1271,  -130,  -130,
     -50,   751,   751,   775,   805,   136,   476,   115,   153,  -130,
    1301,   385,   385,   385,   116,   117,  1211,   476,   119,   751,
     121,  -130,   751,  -130,  -130,  -130,   385,   385,   385,  -130,
    -130,  1241,   696,  -130,  -130,  -130,  -130,   126,  -130
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    22,     0,     8,
      10,     2,     3,    12,     4,     6,     5,     1,    31,    34,
      23,    44,     0,    44,    38,     0,   156,   155,     0,   152,
     153,     9,     0,     0,     0,    63,    65,    64,     0,     0,
       0,     0,     0,     0,    67,    68,    69,    71,    70,    66,
      29,    30,     0,   111,    81,    61,    62,    60,    56,    57,
      58,    59,    55,    25,    78,    80,    79,     0,    73,    74,
      75,    76,    77,     0,     0,     0,     0,    36,    37,     0,
       0,     0,   157,     0,     0,    40,     0,     0,     0,   102,
      83,    85,   110,     0,   108,    78,     0,   104,   108,     0,
      72,     0,    24,     0,   112,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
      21,    20,     0,     7,   154,     0,     0,     0,     0,     0,
      84,    82,   109,     0,   105,     0,   106,    28,   108,   100,
      98,    99,   101,    86,    87,    93,    94,    95,    88,    89,
      90,    91,    26,    92,    96,    97,    27,    43,     0,    49,
       0,    45,    46,    47,    48,     0,     0,     0,   131,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149,   151,
     117,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,     0,    35,    19,     0,    18,    39,     0,     0,     0,
       0,   107,     0,    41,     0,     0,     0,    33,   130,     0,
       0,     0,     0,   142,   148,   150,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   103,    54,
       0,     0,    32,   146,   129,   144,     0,     0,     0,     0,
     143,   145,   147,   118,    17,    16,   115,   114,   116,    50,
       0,    51,     0,     0,     0,   132,     0,     0,    14,    53,
       0,     0,     0,     0,     0,     0,     0,   139,     0,     0,
       0,    11,    52,   140,   141,   133,     0,     0,     0,   138,
     134,     0,    31,   135,   136,   137,    15,     0,    13
  };

  const short int
  Parser::yypgoto_[] =
  {
    -130,  -130,    95,   169,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,    85,  -130,  -108,  -130,  -130,    -3,    59,  -130,
      -9,  -130,   168,  -122,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,    36,   -34,
    -130,  -130,   154,   -49,     6,    13,  -130,  -130,  -130,  -130,
      88,  -129,  -130,  -130,  -130,  -130,   -80,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,   114,  -130,  -130,  -130
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     9,    10,    11,    12,   281,   268,   203,   204,
      25,    13,    50,    51,    52,    14,    15,    53,    78,    79,
      86,   124,    74,   170,   171,   172,   173,   174,   240,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    96,    67,    68,    69,    70,    71,    72,    16,
     218,   219,   191,   192,   193,   277,   278,   194,   195,   196,
     197,   198,   199,   200,    27,    28,    29,    30
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      20,    21,    22,    23,   104,    26,   201,    95,     3,   205,
       4,     5,     6,   206,     7,   185,   214,   127,    18,     1,
     142,    77,    80,    17,    19,    88,   215,    24,   143,    85,
     167,    85,   176,   243,   177,   128,   178,   179,   168,   180,
     181,   259,   182,   183,    19,    19,   184,    95,   220,   260,
       8,   100,   217,    73,    83,   146,   129,   228,   229,   102,
      84,   143,    82,   185,   123,    75,   122,   186,   101,    87,
      85,   109,   110,   103,    89,    90,    91,    94,    98,   125,
     126,    26,   109,   110,   111,   187,   114,   115,   116,   117,
     129,   130,   239,    19,   131,   112,   113,   114,   115,   116,
     117,   135,   136,   138,   119,   120,   121,   141,   117,   216,
     254,   255,     3,    93,     4,     5,     6,   132,     7,   231,
     230,   232,   169,    77,   233,   169,   202,   266,   169,   139,
     246,   247,   169,   188,   114,   115,   116,   117,   269,   148,
     189,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   213,
     267,   237,   273,   279,   280,    85,   286,   287,   290,   292,
     221,   222,   207,   208,   209,   298,    85,    85,   133,   211,
      31,   212,   188,   188,   297,   175,   147,   188,   224,   189,
     189,    76,   188,   188,   189,   225,    99,   289,   134,   189,
     189,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   169,     0,     0,     0,   190,     0,     0,     0,   226,
     227,     0,     0,     0,     0,   188,   188,     0,     0,   169,
     169,     0,   189,   189,   188,   188,     0,   188,     0,     0,
       0,   189,   189,     0,   189,     0,     0,     0,     0,     0,
       0,   241,   242,     0,   188,     0,     0,   169,     0,     0,
       0,   189,     0,     0,     0,     0,   252,     0,     0,   223,
     256,   257,   258,     0,     0,     0,     0,   188,   188,   188,
       0,     0,   263,   264,   189,   189,   189,     0,     0,     0,
       0,     0,   188,   188,   188,     0,     0,   157,   270,   189,
     189,   189,   276,     0,     0,     0,     0,   244,   244,     0,
       0,     0,     0,   276,     0,   291,   244,   244,   157,   253,
     176,     0,   177,   245,   178,   179,     0,   180,   181,     0,
     182,   183,     0,   176,   184,   177,   265,   178,   179,     0,
     180,   181,     0,   182,   183,     0,     0,   184,     0,     0,
       0,   185,     0,     0,     0,   186,     0,     0,     0,   283,
     284,   285,     0,     0,   185,     0,     0,     0,   186,   250,
       0,     0,     0,   187,   293,   294,   295,     0,     0,     0,
       0,    19,     0,     0,     0,   176,   187,   177,     0,   178,
     179,     0,   180,   181,    19,   182,   183,     0,   176,   184,
     177,     0,   178,   179,     0,   180,   181,     0,   182,   183,
       0,     0,   184,     0,     0,     0,   185,     0,     0,     0,
     186,     0,     0,     0,     0,     0,     0,     0,     0,   185,
       0,     0,     0,   186,     0,     0,     0,     0,   187,   251,
       0,    32,     0,     0,     0,    33,    19,     0,     0,     0,
       0,   187,    34,     0,    35,    36,    37,     0,     0,    19,
       0,    38,    39,    40,     0,    81,    92,    42,     0,     0,
       0,     0,     0,    43,     0,     0,     0,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
      45,    46,    47,    48,    49,    19,    32,     0,     0,     0,
      33,     0,     0,     0,     0,   274,     0,    34,     0,    35,
      36,    37,     0,     0,     0,     0,    38,    39,    40,     0,
      81,     0,    42,     0,     0,     0,     0,   275,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    44,    45,    46,    47,    48,    49,
      19,    32,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,    34,     0,    35,    36,    37,     0,     0,     0,
       0,    38,    39,    40,     0,    81,     0,    42,    97,     0,
       0,     0,     0,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
      45,    46,    47,    48,    49,    19,    32,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,    34,     0,    35,
      36,    37,     0,     0,     0,     0,    38,    39,    40,     0,
      81,     0,    42,     0,     0,     0,     0,     0,    43,     0,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    44,    45,    46,    47,    48,    49,
      19,    32,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,    34,     0,    35,    36,    37,     0,     0,     0,
       0,    38,    39,    40,     0,    81,    92,    42,     0,     0,
       0,     0,     0,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
      45,    46,    47,    48,    49,    19,    32,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,    34,     0,    35,
      36,    37,     0,     0,     0,     0,    38,    39,    40,     0,
      41,     0,    42,     0,     0,     0,     0,     0,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    44,    45,    46,    47,    48,    49,
      19,    32,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,    34,     0,    35,    36,    37,     0,     0,     0,
       0,    38,    39,    40,   271,    81,     0,    42,     0,     0,
       0,     0,     0,    43,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,     0,   109,   110,   111,    44,
      45,    46,    47,    48,    49,    19,     0,   272,     0,   112,
     113,   114,   115,   116,   117,     0,     0,     0,   119,   120,
     121,   105,   106,   107,   108,     0,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,   114,   115,   116,   117,   137,     0,     0,   119,   120,
     121,     0,     0,     0,     0,     0,   105,   106,   107,   108,
       0,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   113,   114,   115,   116,   117,
     248,     0,     0,   119,   120,   121,     0,     0,     0,     0,
       0,   105,   106,   107,   108,     0,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,   114,   115,   116,   117,   235,     0,     0,   119,   120,
     121,     0,     0,     0,     0,   105,   106,   107,   108,     0,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   113,   114,   115,   116,   117,   249,
       0,     0,   119,   120,   121,     0,     0,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,   234,     0,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,   236,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,   144,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,   145,     0,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,   118,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,   140,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,   210,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,   238,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   261,   114,   115,   116,
     117,   262,     0,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,   288,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
     296,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   282,   114,   115,   116,
     117,     0,     0,     0,   119,   120,   121,   105,   106,   107,
       0,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   119,   120,   121,   105,     0,   107,
       0,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,   105,     0,   119,   120,   121,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     112,   113,   114,   115,   116,   117,   109,   110,     0,   119,
     120,   121,     0,     0,     0,     0,     0,     0,     0,   112,
     113,   114,   115,   116,   117,     0,     0,     0,     0,   120,
     121
  };

  const short int
  Parser::yycheck_[] =
  {
       3,     4,     5,     6,    53,     8,   128,    41,     4,   131,
       6,     7,     8,   135,    10,    44,    44,    43,    48,     3,
      45,    24,    25,     0,    74,    34,    54,    44,    53,    32,
      45,    34,    13,    14,    15,    61,    17,    18,    53,    20,
      21,    45,    23,    24,    74,    74,    27,    81,   177,    53,
      46,    74,    49,    44,    47,    47,    53,   186,   187,    49,
      53,    53,    26,    44,    73,    43,    61,    48,    53,    33,
      73,    41,    42,    44,    38,    39,    40,    41,    42,    61,
      48,    84,    41,    42,    43,    66,    56,    57,    58,    59,
      53,    45,   214,    74,    50,    54,    55,    56,    57,    58,
      59,    50,    19,    19,    63,    64,    65,    45,    59,    43,
     232,   233,     4,    56,     6,     7,     8,    81,    10,    43,
      62,    56,   125,   126,    61,   128,   129,    48,   131,    93,
      43,    19,   135,   127,    56,    57,    58,    59,   260,   103,
     127,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   168,
      12,   210,    26,    48,    11,   168,    50,    50,    49,    48,
     179,   180,   136,   137,   138,    49,   179,   180,    83,   143,
      11,   145,   176,   177,   292,   126,   101,   181,   182,   176,
     177,    23,   186,   187,   181,   182,    42,   277,    84,   186,
     187,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   214,    -1,    -1,    -1,   127,    -1,    -1,    -1,   183,
     184,    -1,    -1,    -1,    -1,   219,   220,    -1,    -1,   232,
     233,    -1,   219,   220,   228,   229,    -1,   231,    -1,    -1,
      -1,   228,   229,    -1,   231,    -1,    -1,    -1,    -1,    -1,
      -1,   215,   216,    -1,   248,    -1,    -1,   260,    -1,    -1,
      -1,   248,    -1,    -1,    -1,    -1,   230,    -1,    -1,   181,
     234,   235,   236,    -1,    -1,    -1,    -1,   271,   272,   273,
      -1,    -1,   246,   247,   271,   272,   273,    -1,    -1,    -1,
      -1,    -1,   286,   287,   288,    -1,    -1,   261,   262,   286,
     287,   288,   266,    -1,    -1,    -1,    -1,   219,   220,    -1,
      -1,    -1,    -1,   277,    -1,   279,   228,   229,   282,   231,
      13,    -1,    15,    16,    17,    18,    -1,    20,    21,    -1,
      23,    24,    -1,    13,    27,    15,   248,    17,    18,    -1,
      20,    21,    -1,    23,    24,    -1,    -1,    27,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    48,    -1,    -1,    -1,   271,
     272,   273,    -1,    -1,    44,    -1,    -1,    -1,    48,    49,
      -1,    -1,    -1,    66,   286,   287,   288,    -1,    -1,    -1,
      -1,    74,    -1,    -1,    -1,    13,    66,    15,    -1,    17,
      18,    -1,    20,    21,    74,    23,    24,    -1,    13,    27,
      15,    -1,    17,    18,    -1,    20,    21,    -1,    23,    24,
      -1,    -1,    27,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    66,    67,
      -1,    20,    -1,    -1,    -1,    24,    74,    -1,    -1,    -1,
      -1,    66,    31,    -1,    33,    34,    35,    -1,    -1,    74,
      -1,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    20,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,
      44,    -1,    46,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    -1,    44,    -1,    46,    47,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
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
      54,    55,    56,    57,    58,    59,    41,    42,    -1,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    64,
      65
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    79,     4,     6,     7,     8,    10,    46,    80,
      81,    82,    83,    89,    93,    94,   127,     0,    48,    74,
      95,    95,    95,    95,    44,    88,    95,   142,   143,   144,
     145,    81,    20,    24,    31,    33,    34,    35,    40,    41,
      42,    44,    46,    52,    68,    69,    70,    71,    72,    73,
      90,    91,    92,    95,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   121,   122,   123,
     124,   125,   126,    44,   100,    43,   100,    95,    96,    97,
      95,    44,   116,    47,    53,    95,    98,   116,    98,   116,
     116,   116,    45,    56,   116,   117,   120,    47,   116,   120,
      74,    53,    49,    44,   121,    36,    37,    38,    39,    41,
      42,    43,    54,    55,    56,    57,    58,    59,    61,    63,
      64,    65,    61,    98,    99,    61,    48,    43,    61,    53,
      45,    50,   116,    80,   142,    50,    19,    25,    19,   116,
      45,    45,    45,    53,    47,    60,    47,    90,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,    45,    53,    95,
     101,   102,   103,   104,   105,    96,    13,    15,    17,    18,
      20,    21,    23,    24,    27,    44,    48,    66,   122,   123,
     128,   130,   131,   132,   135,   136,   137,   138,   139,   140,
     141,   101,    95,    86,    87,   101,   101,   116,   116,   116,
      45,   116,   116,    98,    44,    54,    43,    49,   128,   129,
     129,    98,    98,   128,   122,   123,   116,   116,   129,   129,
      62,    43,    56,    61,    30,    26,    32,   121,    47,   101,
     106,   116,   116,    14,   128,    16,    43,    19,    25,    28,
      49,    67,   116,   128,   101,   101,   116,   116,   116,    45,
      53,    55,    60,   116,   116,   128,    48,    12,    85,   101,
     116,    19,    22,    26,    29,    51,   116,   133,   134,    48,
      11,    84,    55,   128,   128,   128,    50,    50,    50,   134,
      49,   116,    48,   128,   128,   128,    49,    92,    49
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    78,    79,    80,    80,    80,    80,    81,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    89,    90,    90,    90,    91,    91,
      92,    92,    93,    94,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   101,   101,   101,   101,   102,
     103,   104,   105,   106,   106,   107,   107,   107,   107,   107,
     107,   107,   107,   108,   109,   109,   110,   111,   111,   112,
     113,   114,   115,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   118,   119,   119,   119,   120,   120,   121,
     121,   122,   122,   123,   124,   125,   126,   127,   127,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   129,
     129,   130,   131,   131,   132,   133,   133,   133,   134,   134,
     135,   136,   137,   138,   138,   139,   139,   140,   141,   141,
     141,   141,   142,   142,   143,   143,   144,   145
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     4,     1,     2,
       1,     9,     1,     4,     0,     4,     0,     3,     1,     1,
       0,     3,     0,     2,     4,     1,     3,     3,     3,     1,
       1,     0,     7,     6,     1,     3,     1,     1,     0,     3,
       1,     3,     1,     3,     0,     1,     1,     1,     1,     1,
       4,     4,     6,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     5,     2,     3,     3,     3,     1,     3,
       2,     1,     2,     5,     6,     6,     6,     5,     7,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     4,     6,     6,     3,     3,     3,     2,     1,
       6,     6,     2,     3,     3,     3,     3,     3,     2,     1,
       2,     1,     1,     1,     3,     1,     1,     2
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
  "AttributedDefinition", "Definitions", "FunctionDefinition",
  "MaybeInitially", "MaybeDefined", "FunctionParameters",
  "MaybeFunctionParameters", "MaybeFunctionAttributes",
  "ProgramFunctionDefinition", "Initializer", "Initializers",
  "MaybeInitializers", "DerivedDefinition", "EnumerationDefinition",
  "Identifier", "Identifiers", "MaybeIdentifiers", "Variable",
  "Parameters", "MaybeParameters", "Type", "BasicType", "ComposedType",
  "FixedSizedType", "RangedType", "Types", "Atom", "Undefined", "Boolean",
  "String", "BitNumber", "IntegerNumber", "FloatingNumber",
  "RationalNumber", "RuleReference", "Term", "Expression", "Range", "List",
  "Terms", "Arguments", "DirectCallExpression", "IndirectCallExpression",
  "ConditionalExpression", "UniversalQuantifierExpression",
  "ExistentialQuantifierExpression", "RuleDefinition", "Rule", "Rules",
  "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels",
  "LetRule", "ForallRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", "Attribute", "Attributes", "BasicAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   400,   400,   409,   413,   417,   421,   429,   435,   443,
     449,   459,   480,   488,   492,   500,   504,   512,   518,   528,
     532,   540,   544,   552,   569,   586,   595,   606,   618,   624,
     634,   638,   646,   654,   662,   670,   676,   686,   690,   698,
     702,   711,   717,   727,   731,   739,   743,   747,   751,   759,
     767,   775,   783,   791,   797,   807,   811,   815,   819,   823,
     827,   831,   835,   843,   851,   856,   865,   874,   879,   888,
     897,   906,   915,   924,   928,   932,   936,   940,   944,   948,
     952,   956,   964,   968,   972,   976,   980,   984,   988,   992,
     996,  1000,  1004,  1008,  1012,  1016,  1020,  1024,  1028,  1032,
    1036,  1040,  1044,  1053,  1061,  1066,  1072,  1079,  1085,  1095,
    1099,  1108,  1113,  1121,  1129,  1137,  1145,  1153,  1158,  1167,
    1171,  1175,  1179,  1183,  1187,  1191,  1195,  1199,  1203,  1211,
    1217,  1227,  1235,  1239,  1247,  1255,  1259,  1263,  1271,  1277,
    1287,  1295,  1303,  1311,  1315,  1323,  1327,  1335,  1343,  1349,
    1356,  1362,  1373,  1377,  1385,  1391,  1401,  1409
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
#line 3528 "GrammarParser.cpp" // lalr1.cc:1167
#line 1415 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
