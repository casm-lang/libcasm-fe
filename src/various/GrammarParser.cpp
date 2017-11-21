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
#line 87 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    #include "SourceLocation.h"
    #include "Lexer.h"
    #include "Exception.h"
    #include "Logger.h"

    #include <libstdhl/Type>

    #undef yylex
    #define yylex lexer.nextToken

    static BasicType::Ptr createVoidType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::RuleReferenceType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( SourceLocation& sourceLocation )
    {
        const auto name = Ast::make< Identifier >( sourceLocation, "Agent" );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( SourceLocation& sourceLocation )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = Ast::make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = Ast::make< Identifier >( sourceLocation, "program" );
        return Ast::make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
    }

    static IdentifierPath::Ptr asIdentifierPath( const Identifier::Ptr& identifier )
    {
        const auto& location = identifier->sourceLocation();
        return Ast::make< IdentifierPath >( location, identifier );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( rule == nullptr )
        {
            // this can happen while recovering from a syntax error
            return nullptr;
        }

        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = Ast::make< Rules >( sourceLocation );
        rules->add( rule );
        return Ast::make< BlockRule >( sourceLocation, rules );
    }

#line 131 "GrammarParser.cpp" // lalr1.cc:413


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

#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:479
namespace libcasm_fe {
#line 217 "GrammarParser.cpp" // lalr1.cc:479

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
  Parser::Parser (Logger& log_yyarg, Lexer& lexer_yyarg, Specification& specification_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      log (log_yyarg),
      lexer (lexer_yyarg),
      specification (specification_yyarg)
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
      case 158: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 157: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 159: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 135: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 106: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 109: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 100: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 99: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 101: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 119: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 104: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 136: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 118: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 98: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 86: // AttributedDefinition
      case 87: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 85: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 89: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 114: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 88: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 93: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 94: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 121: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 111: // Term
      case 112: // Expression
      case 124: // Literal
      case 145: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 160: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 110: // Terms
      case 139: // Arguments
      case 140: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 138: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 103: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 91: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 84: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 150: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 151: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 152: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 115: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 105: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 117: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 102: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 122: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 116: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 146: // MaybeInitially
      case 147: // Initializers
      case 149: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 143: // Parameters
      case 144: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 123: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 132: // ReferenceLiteral
        value.move< ReferenceAtom::Ptr > (that.value);
        break;

      case 137: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 95: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 90: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 96: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 107: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 97: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 83: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 113: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 133: // Types
      case 141: // FunctionParameters
      case 142: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 125: // UndefinedLiteral
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 120: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 108: // UpdateRule
      case 148: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 126: // BooleanLiteral
      case 127: // IntegerLiteral
      case 128: // RationalLiteral
      case 129: // DecimalLiteral
      case 130: // BitLiteral
      case 131: // StringLiteral
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 153: // Variable
      case 154: // TypedVariable
      case 155: // AttributedVariable
      case 156: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 134: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
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
      case 158: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 157: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 159: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 135: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 106: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 109: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 100: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 99: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 101: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 119: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 104: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 136: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 118: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 98: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 86: // AttributedDefinition
      case 87: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 85: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 89: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 114: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 88: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 93: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 94: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 121: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 111: // Term
      case 112: // Expression
      case 124: // Literal
      case 145: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 160: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 110: // Terms
      case 139: // Arguments
      case 140: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 138: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 103: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 91: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 84: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 150: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 151: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 152: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 115: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 105: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 117: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 102: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 122: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 116: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 146: // MaybeInitially
      case 147: // Initializers
      case 149: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 143: // Parameters
      case 144: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 123: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 132: // ReferenceLiteral
        value.copy< ReferenceAtom::Ptr > (that.value);
        break;

      case 137: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 95: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 90: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 96: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 107: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 97: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 83: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 113: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 133: // Types
      case 141: // FunctionParameters
      case 142: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 125: // UndefinedLiteral
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 120: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 108: // UpdateRule
      case 148: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 126: // BooleanLiteral
      case 127: // IntegerLiteral
      case 128: // RationalLiteral
      case 129: // DecimalLiteral
      case 130: // BitLiteral
      case 131: // StringLiteral
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 153: // Variable
      case 154: // TypedVariable
      case 155: // AttributedVariable
      case 156: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 134: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
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
      case 158: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 157: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 159: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 135: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 106: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 109: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 100: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 99: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 101: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 119: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 104: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 136: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 118: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 98: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 86: // AttributedDefinition
      case 87: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 85: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 89: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 114: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 88: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 93: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 94: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 121: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 111: // Term
      case 112: // Expression
      case 124: // Literal
      case 145: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 160: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 110: // Terms
      case 139: // Arguments
      case 140: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 138: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 103: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 91: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 84: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 150: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 151: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 152: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 115: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 105: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 117: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 102: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 122: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 116: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 146: // MaybeInitially
      case 147: // Initializers
      case 149: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 143: // Parameters
      case 144: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 123: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 132: // ReferenceLiteral
        yylhs.value.build< ReferenceAtom::Ptr > ();
        break;

      case 137: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 95: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 90: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 96: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 107: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 97: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 83: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 113: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 133: // Types
      case 141: // FunctionParameters
      case 142: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 125: // UndefinedLiteral
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 120: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 108: // UpdateRule
      case 148: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 126: // BooleanLiteral
      case 127: // IntegerLiteral
      case 128: // RationalLiteral
      case 129: // DecimalLiteral
      case 130: // BitLiteral
      case 131: // StringLiteral
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 153: // Variable
      case 154: // TypedVariable
      case 155: // AttributedVariable
      case 156: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 134: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
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
#line 381 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1412 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1430 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1438 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1446 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1470 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1478 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 474 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1495 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 488 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< Identifier::Ptr > ();

      auto function = Ast::make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > () );
      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
           initializer->function()->setIdentifier( asIdentifierPath( identifier ) );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1524 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 504 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 512 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto singleAgentIdentifier = Ast::make< Identifier >( yylhs.location, "$" );
      auto singleAgentArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( singleAgentIdentifier ), singleAgentArguments );
      singleAgent->setTargetType( CallExpression::TargetType::CONSTANT );

      auto programDefinition = createProgramFunction( yylhs.location );
      auto programArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      programArguments->add( singleAgent );
      const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( programDefinition->identifier() ), programArguments );
      program->setTargetType( CallExpression::TargetType::FUNCTION );

      const auto ruleReference = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );

      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1559 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 535 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier(
                asIdentifierPath( programDefinition->identifier() ) );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 557 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 563 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 571 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1613 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 595 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 603 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 607 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 611 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1679 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 619 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 623 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 627 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1703 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 631 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1711 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 639 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1721 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 655 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1739 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 663 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 667 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 675 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1763 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 679 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 687 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1787 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 695 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1795 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 703 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 709 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1823 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 731 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 739 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1847 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 747 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1855 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 755 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1863 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 759 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1871 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 763 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1880 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 768 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1889 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 777 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 781 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1914 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 790 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1923 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 799 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 833 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1975 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 839 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1985 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 849 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1993 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 853 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 857 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2009 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 861 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2017 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 865 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2025 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 869 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2033 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 873 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 877 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2049 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 881 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2057 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 885 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 889 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 893 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2081 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 897 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2089 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 909 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2097 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 913 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2105 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 917 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2113 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 921 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2121 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 925 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2129 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2137 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2145 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 937 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2153 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2161 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2169 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2177 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 961 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 965 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 969 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 973 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2233 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2241 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2249 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2257 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2265 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1001 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1009 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2298 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1030 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< DirectCallExpression::Ptr > () );
  }
#line 2306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2322 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1054 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1062 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1070 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1078 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1083 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1087 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2371 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2379 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1107 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 2387 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1111 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2395 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1115 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2403 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1119 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2411 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1123 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2419 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2427 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1131 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2435 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1135 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 2443 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1156 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2485 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1181 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2501 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1197 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::DecimalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1213 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2533 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1225 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2549 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1241 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2565 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1257 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2573 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1269 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1285 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1289 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1293 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1297 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1305 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2633 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1313 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1321 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1329 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2657 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1341 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2665 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1345 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2673 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2682 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2692 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1372 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2702 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1392 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1400 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2738 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 2772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2796 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1452 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2804 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2814 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2824 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1505 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1521 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1525 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 2893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 2901 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1537 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 2911 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2931 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1567 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2939 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1571 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 2948 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1580 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2956 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1588 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2966 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2974 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3012 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1635 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 3020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1639 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1647 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1655 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3044 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3048 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -185;

  const short int Parser::yytable_ninf_ = -153;

  const short int
  Parser::yypact_[] =
  {
      11,  -185,     2,    16,    38,  -185,  -185,  1016,     0,  -185,
    -185,  -185,  -185,  -185,    -8,     2,     2,     2,     2,     2,
     198,  -185,  -185,  -185,  -185,  -185,  -185,  -185,    -5,    -5,
      -5,  1016,    -5,  -185,  -185,  -185,  1016,  1016,  1016,   498,
     560,    -4,     2,  -185,  -185,  -185,  -185,  -185,  -185,  1833,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,   -42,   -45,    24,     2,  1078,  -185,     8,    55,
       8,    33,    65,  -185,     2,    37,  -185,  -185,    77,    20,
      50,  1350,   106,  -185,  -185,  -185,    79,  1016,  1569,    84,
    -185,    72,  1602,  -185,  -185,    -4,  1016,  1016,  1016,  1016,
    1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,    -4,
    1016,  1016,  1016,  1016,   622,  -185,     2,  -185,  -185,   498,
    1635,    69,    82,  -185,    94,     4,    87,   104,   -28,    -4,
     214,    80,    -4,  1016,  1016,  1016,  1016,  1016,  -185,  1668,
    -185,  -185,  -185,  1016,  1016,  -185,  -185,  -185,  -185,  -185,
      74,  1933,  1899,  1927,  1866,    99,    99,   221,   182,   182,
     103,   103,   103,  -185,  -185,  1866,   221,   182,   182,   108,
    -185,    40,  1833,  -185,   107,  1569,  1016,  1016,  1078,  -185,
     124,     2,    44,    37,  -185,  -185,    -4,     5,   916,    -4,
    -185,   120,   114,  -185,     2,  -185,  1124,  1498,  1235,  1425,
    1536,   -42,  1833,  1701,    -4,  1016,  -185,  -185,  1016,  1833,
    1833,  -185,  -185,    98,  -185,     9,   135,  -185,     2,  -185,
      17,  -185,   148,   660,  -185,    -5,    -5,    -5,   916,    -6,
    1016,  1016,   126,   701,   735,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,   119,  -185,   142,
      -4,    -4,  -185,  1016,  1016,  1016,  1016,  1016,  -185,  -185,
     -19,   -38,   128,  -185,  1734,     2,  -185,  1016,   101,  -185,
       5,   175,  -185,   769,   179,   807,   146,   177,   178,  -185,
    -185,  -185,  1387,  1458,   151,   841,   127,   882,  1016,   916,
    -185,   197,  1833,  1833,  1833,  1833,  1833,    -4,  -185,    -4,
    -185,  -185,  1833,     2,  -185,  -185,  -185,  -185,  -185,  -185,
    1016,  1016,  1016,   916,   161,  -185,  -185,  -185,  -185,  1833,
    -185,   168,   217,  -185,   172,  -185,  1157,  1196,  1274,   203,
     436,  1016,   181,  -185,  -185,   916,   916,  1016,   916,   916,
     183,   180,   185,  -185,   954,  1767,  1800,  1078,  -185,  -185,
    1313,  -185,  -185,  -185,   916,   916,  -185,  -185,   916,  -185,
     187,   916,  -185,  -185,  -185,  -185,  -185
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,   172,   171,   188,     0,   185,
     186,   187,     1,     9,     0,     0,     0,     0,     0,     0,
       0,     6,     8,    10,    11,    12,    13,    19,     0,     0,
       0,     0,     0,   127,   129,   128,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   130,   131,   132,   135,   189,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,   119,   120,   121,   122,   123,   124,   125,
     126,   176,   106,   173,     0,     0,   170,    20,   159,     0,
     159,     0,     0,     5,     0,   178,   181,   177,     0,     0,
       0,     0,     0,   104,    85,    86,     0,     0,     0,     0,
     115,     0,    69,   136,   174,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   107,     0,     3,   184,     0,
     166,     0,   169,   165,     0,     0,     0,     0,     0,   154,
       0,     0,     0,     0,     0,     0,     0,     0,    84,     0,
      83,   117,   116,     0,     0,   105,   139,   140,   141,   142,
     143,   101,    99,   100,   103,    87,    88,    94,    95,    96,
      89,    90,    91,    92,   109,   102,    93,    97,    98,     0,
     149,     0,    69,   175,     0,    69,     0,     0,     0,    21,
       0,     0,     0,     0,   183,   156,     0,     0,     0,     0,
     152,   153,     0,     7,     0,   179,     0,     0,     0,     0,
       0,     0,    68,     0,   154,     0,   148,   147,     0,   167,
     168,   164,   158,     0,   157,     0,     0,    24,     0,    26,
       0,    22,     0,     0,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    16,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    65,    67,     0,
       0,     0,   180,     0,     0,     0,     0,     0,   108,   118,
       0,   138,     0,   146,    68,     0,   155,     0,     0,    14,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    54,
      64,    66,     0,     0,     0,     0,     0,     0,     0,     0,
     151,   161,   110,   113,   112,   111,   114,     0,   144,     0,
     150,   182,    15,     0,    25,    62,    60,    38,    58,    56,
       0,     0,     0,     0,     0,    57,    55,    61,    59,    63,
      17,     0,   163,   137,     0,    23,     0,     0,     0,    41,
       0,     0,     0,    18,   145,     0,     0,     0,     0,     0,
       0,     0,     0,    49,     0,     0,     0,   170,    50,    51,
       0,    53,    42,    44,     0,     0,    43,    48,     0,   160,
       0,     0,    45,    46,    47,   162,    52
  };

  const short int
  Parser::yypgoto_[] =
  {
    -185,  -185,  -185,  -185,   211,   102,  -185,  -185,  -185,  -185,
    -185,   -35,  -185,    97,  -184,  -185,  -185,  -185,  -108,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,   -33,    -7,
    -185,  -185,    54,    67,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -119,  -185,  -185,  -185,  -185,    42,  -185,  -185,
      35,  -185,   171,  -185,  -185,  -185,    66,  -102,    46,   -13,
    -185,    57,  -131,   -22,    39,   -16,   191,  -185,  -185
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    20,    21,    22,    23,    24,    25,    26,
      27,   229,   230,   282,   283,   246,   247,   248,   353,   354,
     249,   250,   251,   252,   253,   254,   255,   256,   101,   130,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,   270,   155,   156,   157,   158,   159,   125,   131,   201,
     202,   192,   136,   332,   343,   132,   133,   134,    71,    72,
      73,    86,    87,    88,   195,     8,     9,    10,    11
  };

  const short int
  Parser::yytable_[] =
  {
      49,    77,   124,    82,   194,   190,   227,    89,    90,     5,
      92,     5,     5,     5,     1,   198,    12,   126,  -152,     5,
     200,     5,     5,   205,    91,  -152,     5,   127,   103,    93,
      94,    95,    98,   102,   307,   199,   308,   144,   242,    13,
      76,    84,    14,    15,    16,    17,    18,    74,     7,   285,
     191,   228,   135,    75,    42,   191,    42,     2,    42,   295,
     297,    78,    79,    80,    81,     7,   279,   145,   141,     6,
     280,     6,     6,     6,    85,    85,    85,   226,    85,     6,
     259,     6,     6,   139,    19,   217,     6,   142,   104,   224,
     149,   181,   160,   153,   194,   271,   184,   225,   137,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   140,   175,   176,   177,   178,   182,    75,   152,
     143,     7,   185,   147,   148,   153,   160,   204,   214,   160,
       7,   151,   187,    75,   215,   188,   206,   207,   208,   209,
     210,   300,   301,   189,   311,   275,   212,   213,   313,   281,
     196,    75,   197,   216,    75,   115,   116,   117,   118,   232,
     218,   233,   118,   234,   235,     5,   236,   237,   238,   222,
     239,   240,   183,   174,   241,   223,   260,   261,   277,   219,
     220,   193,    97,   160,   298,   299,   160,   315,   333,   320,
     334,   309,   242,   318,   321,   322,   243,   327,    -2,    13,
     325,   160,    14,    15,    16,    17,    18,   331,   273,   340,
      42,   274,   278,   286,   287,   288,   341,   244,    14,    15,
      16,    17,    18,   110,   111,     6,   342,   344,   349,   357,
     364,    83,   363,   292,   293,   365,   375,     7,   115,   116,
     117,   118,   203,   231,    19,   314,   367,   160,   160,   272,
      85,   138,   257,   268,   221,   370,   302,   303,   304,   305,
     306,   262,   110,   111,   276,   258,   128,     0,     0,     0,
     312,   193,     0,     0,     7,   113,   114,   115,   116,   117,
     118,    85,    85,    85,     0,     0,   257,   257,   122,   123,
       0,   329,   257,   290,   160,   245,   160,   257,   257,   258,
     258,     0,     0,     0,     0,   258,   291,     0,     0,     0,
     258,   258,     0,   336,   337,   338,     0,     0,     0,     0,
       0,   193,     0,     0,     0,     0,   231,     0,     0,     0,
       0,     0,     0,   355,   356,   289,     0,   257,     0,   257,
     360,     0,     0,     0,     0,     0,     0,   355,     0,   257,
     258,   257,   258,   257,     0,     0,     0,     0,     0,   335,
       0,     0,   258,     0,   258,     0,   258,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   257,     0,     0,
     317,     0,   317,     0,     0,     0,     0,     0,     0,     0,
     258,     0,   317,     0,   317,     0,   330,     0,     0,   257,
     257,     0,   257,   257,     0,     0,     0,     0,     0,     0,
       0,     0,   258,   258,     0,   258,   258,     0,   257,   257,
     339,     0,   257,     0,     0,   257,     0,     0,     0,     0,
       0,   258,   258,     0,     0,   258,     0,   350,   258,     0,
       0,     0,   358,   359,     0,   361,   362,     0,     0,     0,
       0,     0,    28,     5,    29,    30,     0,     0,     0,    31,
       0,   372,   373,     0,   351,   374,    32,     0,   376,    33,
      34,    35,     0,     0,     0,     0,    36,    37,    38,     0,
      39,     0,    40,     0,     0,     0,     0,   352,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    96,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,     6,    28,     5,    29,    30,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,    32,     0,
       0,    33,    34,    35,     0,     0,     0,     0,    36,    37,
      38,     0,    39,     0,    40,     0,     0,     0,     0,     0,
      41,     0,     0,     0,    97,     0,     0,     0,     0,     0,
      42,    99,     0,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,     6,    28,     5,    29,    30,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
      32,     0,     0,    33,    34,    35,     0,     0,     0,     0,
      36,    37,    38,     0,    39,     0,    40,   100,     0,     0,
       0,     0,    41,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,   179,     0,     0,     0,     0,     0,     0,
       0,    43,    44,    45,    46,    47,    48,     6,    28,     5,
      29,    30,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,    32,     0,     0,    33,    34,    35,     0,     0,
       0,   284,    36,    37,    38,     0,    39,   180,    40,     0,
       0,   232,     0,   233,    41,   234,   235,     5,   236,   237,
     238,     0,   239,   240,    42,     0,   241,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,     6,
       0,     0,   294,     0,   242,     0,     0,     0,   243,     0,
       0,     0,   232,     0,   233,     0,   234,   235,     5,   236,
     237,   238,    42,   239,   240,     0,     0,   241,     0,   244,
       0,     0,     0,     0,     0,     0,   296,     6,     0,     0,
       0,     0,     0,     0,     0,   242,   232,     0,   233,   243,
     234,   235,     5,   236,   237,   238,     0,   239,   240,     0,
       0,   241,     0,    42,     0,     0,     0,     0,     0,     0,
     244,     0,     0,     0,     0,     0,     0,     0,     6,   242,
     232,   316,   233,   243,   234,   235,     5,   236,   237,   238,
       0,   239,   240,     0,     0,   241,     0,    42,     0,     0,
       0,     0,     0,     0,   244,     0,     0,     0,     0,     0,
       0,     0,     6,   242,     0,     0,     0,   243,   232,     0,
     233,   319,   234,   235,     5,   236,   237,   238,     0,   239,
     240,    42,     0,   241,     0,     0,     0,     0,   244,     0,
       0,     0,     0,     0,     0,     0,     6,     0,     0,     0,
       0,   242,   232,     0,   233,   243,   234,   235,     5,   236,
     237,   238,     0,   239,   240,     0,     0,   241,     0,    42,
       0,     0,     0,     0,     0,     0,   244,     0,     0,     0,
       0,     0,     0,     0,     6,   242,     0,     0,     0,   243,
     326,     0,     0,   232,     0,   233,     0,   234,   235,     5,
     236,   237,   238,    42,   239,   240,     0,     0,   241,     0,
     244,     0,     0,     0,     0,     0,     0,     0,     6,     0,
       0,     0,     0,     0,     0,     0,   242,   232,     0,   233,
     243,   234,   235,     5,   236,   237,   238,     0,   239,   240,
       0,     0,   241,     0,    42,     0,     0,     0,     0,     0,
       0,   244,   328,     0,     0,     0,     0,     0,     0,     6,
     242,     0,     0,     0,   243,     0,     0,     0,     0,     0,
      28,     5,    29,    30,     0,     0,     0,    31,    42,     0,
       0,     0,   351,     0,    32,   244,     0,    33,    34,    35,
       0,     0,     0,     6,    36,    37,    38,     0,    39,     0,
      40,     0,     0,   366,     0,   352,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,     6,    28,     5,    29,    30,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,    32,     0,     0,    33,
      34,    35,     0,     0,     0,     0,    36,    37,    38,     0,
      39,     0,    40,     0,     0,     0,     0,     0,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,     6,    28,     5,    29,    30,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,    32,     0,
       0,    33,    34,    35,     0,     0,     0,     0,    36,    37,
      38,     0,   129,     0,    40,     0,     0,     0,     0,     0,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,   263,     0,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,     6,   105,     0,     0,     0,
     106,   107,   108,   109,     0,   110,   111,   112,     0,     0,
       0,     0,     0,     0,   345,     0,     0,     0,   113,   114,
     115,   116,   117,   118,     0,     0,   119,     0,   120,   105,
     121,   122,   123,   106,   107,   108,   109,     0,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   346,     0,   119,
       0,   120,     0,   121,   122,   123,     0,   347,   105,     0,
       0,     0,   106,   107,   108,   109,     0,   110,   111,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,   114,   115,   116,   117,   118,   265,     0,   119,     0,
     120,     0,   121,   122,   123,     0,     0,   105,     0,     0,
       0,   106,   107,   108,   109,     0,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   113,
     114,   115,   116,   117,   118,   348,     0,   119,     0,   120,
       0,   121,   122,   123,     0,     0,   105,     0,     0,     0,
     106,   107,   108,   109,     0,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   114,
     115,   116,   117,   118,   371,     0,   119,     0,   120,     0,
     121,   122,   123,     0,     0,   105,     0,     0,     0,   106,
     107,   108,   109,     0,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,     0,   146,   119,     0,   120,     0,   121,
     122,   123,   105,     0,     0,     0,   106,   107,   108,   109,
       0,   110,   111,   112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   114,   115,   116,   117,   118,
       0,   323,   119,     0,   120,     0,   121,   122,   123,   105,
       0,     0,     0,   106,   107,   108,   109,     0,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,     0,     0,   119,
     266,   120,     0,   121,   122,   123,     0,   105,     0,     0,
       0,   106,   107,   108,   109,     0,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   113,
     114,   115,   116,   117,   118,   324,     0,   119,     0,   120,
     105,   121,   122,   123,   106,   107,   108,   109,     0,   110,
     111,   112,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   113,   114,   115,   116,   117,   118,     0,     0,
     119,     0,   120,     0,   121,   122,   123,   264,     0,     0,
     105,     0,     0,     0,   106,   107,   108,   109,     0,   110,
     111,   112,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   113,   114,   115,   116,   117,   118,     0,     0,
     119,     0,   120,     0,   121,   122,   123,   267,   105,     0,
       0,     0,   106,   107,   108,   109,     0,   110,   111,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,   114,   115,   116,   117,   118,     0,     0,   119,     0,
     120,   105,   121,   122,   123,   106,   107,   108,   109,     0,
     110,   111,   112,     0,   150,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   114,   115,   116,   117,   118,     0,
       0,   119,     0,   120,   105,   121,   122,   123,   106,   107,
     108,   109,     0,   110,   111,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,     0,   154,   119,     0,   120,   105,   121,   122,
     123,   106,   107,   108,   109,     0,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   113,
     114,   115,   116,   117,   118,     0,     0,   119,   186,   120,
     105,   121,   122,   123,   106,   107,   108,   109,     0,   110,
     111,   112,     0,   211,     0,     0,     0,     0,     0,     0,
       0,     0,   113,   114,   115,   116,   117,   118,     0,     0,
     119,     0,   120,   105,   121,   122,   123,   106,   107,   108,
     109,     0,   110,   111,   112,     0,     0,     0,   269,     0,
       0,     0,     0,     0,     0,   113,   114,   115,   116,   117,
     118,     0,     0,   119,     0,   120,   105,   121,   122,   123,
     106,   107,   108,   109,     0,   110,   111,   112,     0,   310,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   114,
     115,   116,   117,   118,     0,     0,   119,     0,   120,   105,
     121,   122,   123,   106,   107,   108,   109,     0,   110,   111,
     112,     0,     0,     0,     0,     0,     0,   368,     0,     0,
       0,   113,   114,   115,   116,   117,   118,     0,     0,   119,
       0,   120,   105,   121,   122,   123,   106,   107,   108,   109,
       0,   110,   111,   112,     0,     0,     0,     0,     0,   369,
       0,     0,     0,     0,   113,   114,   115,   116,   117,   118,
       0,     0,   119,     0,   120,   105,   121,   122,   123,   106,
     107,   108,   109,     0,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,     0,     0,   119,     0,   120,     0,   121,
     122,   123,   106,   107,   108,     0,     0,   110,   111,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,   114,   115,   116,   117,   118,     0,     0,     0,     0,
       0,     0,   121,   122,   123,   106,     0,   108,     0,     0,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   114,   115,   116,   117,   118,     0,
       0,     0,     0,   106,     0,   121,   122,   123,   110,   111,
     112,     0,     0,     0,   110,   111,   112,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   113,   114,   115,
     116,   117,   118,   121,   122,   123,     0,     0,     0,   121,
     122,   123
  };

  const short int
  Parser::yycheck_[] =
  {
       7,    14,    44,    19,   135,     1,     1,    29,    30,    17,
      32,    17,    17,    17,     3,    43,     0,    62,    56,    17,
     139,    17,    17,   142,    31,    63,    17,     3,    41,    36,
      37,    38,    39,    40,    53,    63,    55,    17,    44,     1,
      48,    46,     4,     5,     6,     7,     8,    47,     2,   233,
      46,    46,    44,    53,    62,    46,    62,    46,    62,   243,
     244,    15,    16,    17,    18,    19,    49,    17,    84,    77,
      53,    77,    77,    77,    28,    29,    30,   196,    32,    77,
     199,    77,    77,    50,    46,    45,    77,    50,    42,    45,
      97,   124,   105,    53,   225,   214,   129,    53,    43,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,    47,   120,   121,   122,   123,   124,    53,    47,
      43,    75,   129,    17,    45,    53,   139,    47,    54,   142,
      84,    47,    63,    53,    60,    53,   143,   144,   145,   146,
     147,   260,   261,    49,   275,    47,   153,   154,    47,     1,
      63,    53,    48,    45,    53,    56,    57,    58,    59,    11,
      53,    13,    59,    15,    16,    17,    18,    19,    20,    45,
      22,    23,   126,   119,    26,   191,    56,    63,    43,   186,
     187,   135,    56,   196,    65,    43,   199,    12,   307,    43,
     309,    63,    44,    14,    17,    17,    48,    70,     0,     1,
      49,   214,     4,     5,     6,     7,     8,    10,   215,    48,
      62,   218,   228,   235,   236,   237,    48,    69,     4,     5,
       6,     7,     8,    41,    42,    77,     9,    55,    25,    48,
      50,    20,    49,   240,   241,    50,    49,   191,    56,    57,
      58,    59,   140,   197,    46,   280,   354,   260,   261,   214,
     204,    80,   198,   211,   188,   357,   263,   264,   265,   266,
     267,   204,    41,    42,   225,   198,    75,    -1,    -1,    -1,
     277,   225,    -1,    -1,   228,    54,    55,    56,    57,    58,
      59,   235,   236,   237,    -1,    -1,   232,   233,    67,    68,
      -1,   298,   238,   239,   307,   198,   309,   243,   244,   232,
     233,    -1,    -1,    -1,    -1,   238,   239,    -1,    -1,    -1,
     243,   244,    -1,   320,   321,   322,    -1,    -1,    -1,    -1,
      -1,   275,    -1,    -1,    -1,    -1,   280,    -1,    -1,    -1,
      -1,    -1,    -1,   340,   341,   238,    -1,   283,    -1,   285,
     347,    -1,    -1,    -1,    -1,    -1,    -1,   354,    -1,   295,
     283,   297,   285,   299,    -1,    -1,    -1,    -1,    -1,   313,
      -1,    -1,   295,    -1,   297,    -1,   299,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   323,    -1,    -1,
     283,    -1,   285,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     323,    -1,   295,    -1,   297,    -1,   299,    -1,    -1,   345,
     346,    -1,   348,   349,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   345,   346,    -1,   348,   349,    -1,   364,   365,
     323,    -1,   368,    -1,    -1,   371,    -1,    -1,    -1,    -1,
      -1,   364,   365,    -1,    -1,   368,    -1,     1,   371,    -1,
      -1,    -1,   345,   346,    -1,   348,   349,    -1,    -1,    -1,
      -1,    -1,    16,    17,    18,    19,    -1,    -1,    -1,    23,
      -1,   364,   365,    -1,    28,   368,    30,    -1,   371,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,
      44,    -1,    46,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    16,    17,    18,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      62,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    16,    17,    18,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    16,    17,
      18,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,     1,    40,    41,    42,    -1,    44,    45,    46,    -1,
      -1,    11,    -1,    13,    52,    15,    16,    17,    18,    19,
      20,    -1,    22,    23,    62,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,     1,    -1,    44,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    20,    62,    22,    23,    -1,    -1,    26,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    11,    -1,    13,    48,
      15,    16,    17,    18,    19,    20,    -1,    22,    23,    -1,
      -1,    26,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    44,
      11,    12,    13,    48,    15,    16,    17,    18,    19,    20,
      -1,    22,    23,    -1,    -1,    26,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    44,    -1,    -1,    -1,    48,    11,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    22,
      23,    62,    -1,    26,    -1,    -1,    -1,    -1,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    44,    11,    -1,    13,    48,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,    -1,    26,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    44,    -1,    -1,    -1,    48,
      49,    -1,    -1,    11,    -1,    13,    -1,    15,    16,    17,
      18,    19,    20,    62,    22,    23,    -1,    -1,    26,    -1,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    11,    -1,    13,
      48,    15,    16,    17,    18,    19,    20,    -1,    22,    23,
      -1,    -1,    26,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      44,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      16,    17,    18,    19,    -1,    -1,    -1,    23,    62,    -1,
      -1,    -1,    28,    -1,    30,    69,    -1,    33,    34,    35,
      -1,    -1,    -1,    77,    40,    41,    42,    -1,    44,    -1,
      46,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    16,    17,    18,    19,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,
      44,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    16,    17,    18,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    32,    -1,    -1,    -1,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    -1,    64,    32,
      66,    67,    68,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    21,    -1,    62,
      -1,    64,    -1,    66,    67,    68,    -1,    31,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    21,    -1,    62,    -1,
      64,    -1,    66,    67,    68,    -1,    -1,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    21,    -1,    62,    -1,    64,
      -1,    66,    67,    68,    -1,    -1,    32,    -1,    -1,    -1,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    21,    -1,    62,    -1,    64,    -1,
      66,    67,    68,    -1,    -1,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    24,    62,    -1,    64,    -1,    66,
      67,    68,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    24,    62,    -1,    64,    -1,    66,    67,    68,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      25,    64,    -1,    66,    67,    68,    -1,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    27,    -1,    62,    -1,    64,
      32,    66,    67,    68,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      62,    -1,    64,    -1,    66,    67,    68,    29,    -1,    -1,
      32,    -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      62,    -1,    64,    -1,    66,    67,    68,    31,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    62,    -1,
      64,    32,    66,    67,    68,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    -1,
      -1,    62,    -1,    64,    32,    66,    67,    68,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    61,    62,    -1,    64,    32,    66,    67,
      68,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    64,
      32,    66,    67,    68,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      62,    -1,    64,    32,    66,    67,    68,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    -1,    64,    32,    66,    67,    68,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    -1,    64,    32,
      66,    67,    68,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      -1,    64,    32,    66,    67,    68,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    -1,    62,    -1,    64,    32,    66,    67,    68,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    -1,    64,    -1,    66,
      67,    68,    36,    37,    38,    -1,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    36,    -1,    38,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    36,    -1,    66,    67,    68,    41,    42,
      43,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    54,    55,    56,
      57,    58,    59,    66,    67,    68,    -1,    -1,    -1,    66,
      67,    68
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    46,    83,    84,    17,    77,   150,   157,   158,
     159,   160,     0,     1,     4,     5,     6,     7,     8,    46,
      85,    86,    87,    88,    89,    90,    91,    92,    16,    18,
      19,    23,    30,    33,    34,    35,    40,    41,    42,    44,
      46,    52,    62,    71,    72,    73,    74,    75,    76,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   150,   151,   152,    47,    53,    48,   151,   150,   150,
     150,   150,   157,    86,    46,   150,   153,   154,   155,   155,
     155,   111,   155,   111,   111,   111,     1,    56,   111,     1,
      47,   110,   111,   151,   150,    32,    36,    37,    38,    39,
      41,    42,    43,    54,    55,    56,    57,    58,    59,    62,
      64,    66,    67,    68,    44,   139,    62,     3,   158,    44,
     111,   140,   147,   148,   149,    44,   144,    43,   144,    50,
      47,   157,    50,    43,    17,    17,    24,    17,    45,   111,
      45,    47,    47,    53,    61,   134,   135,   136,   137,   138,
     151,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   114,   111,   111,   111,   111,     1,
      45,   110,   111,   150,   110,   111,    63,    63,    53,    49,
       1,    46,   143,   150,   154,   156,    63,    48,    43,    63,
     134,   141,   142,    87,    47,   134,   111,   111,   111,   111,
     111,    45,   111,   111,    54,    60,    45,    45,    53,   111,
     111,   148,    45,   157,    45,    53,   134,     1,    46,    93,
      94,   150,    11,    13,    15,    16,    18,    19,    20,    22,
      23,    26,    44,    48,    69,    95,    97,    98,    99,   102,
     103,   104,   105,   106,   107,   108,   109,   114,   115,   134,
      56,    63,   153,    17,    29,    21,    25,    31,   139,    47,
     133,   134,   142,   111,   111,    47,   156,    43,   157,    49,
      53,     1,    95,    96,     1,    96,   155,   155,   155,    95,
     114,   115,   111,   111,     1,    96,     1,    96,    65,    43,
     134,   134,   111,   111,   111,   111,   111,    53,    55,    63,
      45,   154,   111,    47,    93,    12,    12,    95,    14,    14,
      43,    17,    17,    24,    27,    49,    49,    70,    70,   111,
      95,    10,   145,   134,   134,   150,   111,   111,   111,    95,
      48,    48,     9,   146,    55,    17,    21,    31,    21,    25,
       1,    28,    51,   100,   101,   111,   111,    48,    95,    95,
     111,    95,    95,    49,    50,    50,    49,   100,    50,    49,
     149,    21,    95,    95,    95,    49,    95
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    82,    83,    84,    84,    85,    85,    86,    86,    86,
      87,    87,    87,    87,    88,    89,    90,    90,    91,    91,
      92,    92,    93,    93,    93,    94,    94,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    96,    96,
      97,    98,    98,    99,    99,   100,   100,   100,   101,   101,
     102,   103,   103,   104,   105,   106,   106,   106,   106,   107,
     107,   107,   107,   108,   109,   109,   109,   109,   110,   110,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   113,   114,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   122,   122,   123,   124,
     124,   124,   124,   124,   124,   124,   124,   125,   126,   126,
     127,   128,   129,   130,   130,   131,   132,   133,   133,   134,
     134,   134,   134,   135,   136,   137,   138,   139,   139,   139,
     140,   141,   141,   142,   142,   143,   143,   144,   144,   144,
     145,   145,   146,   146,   147,   147,   148,   148,   148,   149,
     149,   150,   150,   151,   151,   152,   152,   153,   153,   154,
     155,   155,   156,   156,   157,   157,   158,   158,   159,   160
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     4,     1,     2,     1,     4,     1,     1,
       1,     1,     1,     1,     6,     7,     5,     7,     8,     1,
       2,     4,     1,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     4,     6,     6,     6,     3,     3,     3,     2,     1,
       6,     6,     8,     6,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     1,     2,     5,     3,
       6,     6,     6,     6,     6,     2,     3,     3,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     4,     6,     3,     3,     3,     2,
       5,     3,     1,     1,     0,     3,     1,     3,     3,     0,
       4,     0,     4,     0,     3,     1,     1,     3,     3,     1,
       0,     1,     1,     1,     2,     3,     1,     1,     1,     3,
       4,     1,     4,     1,     3,     1,     1,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"function\"",
  "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"", "\"par\"",
  "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"choose\"", "\"iterate\"", "\"do\"", "\"call\"", "\"if\"", "\"then\"",
  "\"else\"", "\"case\"", "\"of\"", "\"default\"", "\"holds\"",
  "\"exists\"", "\"with\"", "\"as\"", "\"undef\"", "\"false\"", "\"true\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"implies\"", "\"not\"", "\"+\"",
  "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"",
  "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"", "\"=>\"",
  "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"decimal\"",
  "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header", "Definitions",
  "AttributedDefinition", "Definition", "EnumerationDefinition",
  "DerivedDefinition", "RuleDefinition", "FunctionDefinition",
  "ProgramFunctionDefinition", "EnumeratorDefinition", "Enumerators",
  "Rule", "Rules", "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel",
  "CaseLabels", "LetRule", "ForallRule", "ChooseRule", "IterateRule",
  "BlockRule", "SequenceRule", "UpdateRule", "CallRule", "Terms", "Term",
  "Expression", "TypeCastingExpression", "DirectCallExpression",
  "IndirectCallExpression", "MethodCallExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "List", "Range", "Literal", "UndefinedLiteral", "BooleanLiteral",
  "IntegerLiteral", "RationalLiteral", "DecimalLiteral", "BitLiteral",
  "StringLiteral", "ReferenceLiteral", "Types", "Type", "BasicType",
  "ComposedType", "RelationType", "FixedSizedType", "Arguments",
  "TwoOrMoreArguments", "FunctionParameters", "MaybeFunctionParameters",
  "Parameters", "MaybeParameters", "MaybeDefined", "MaybeInitially",
  "Initializers", "Initializer", "MaybeInitializers", "Identifier",
  "IdentifierPath", "DotSeparatedIdentifiers", "Variable", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "Attributes",
  "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   380,   380,   389,   395,   403,   409,   419,   425,   429,
     437,   441,   445,   449,   457,   465,   473,   478,   487,   503,
     511,   534,   552,   556,   562,   570,   576,   590,   594,   598,
     602,   606,   610,   614,   618,   622,   626,   630,   638,   644,
     654,   662,   666,   674,   678,   686,   690,   694,   702,   708,
     718,   726,   730,   738,   746,   754,   758,   762,   767,   776,
     780,   784,   789,   798,   808,   812,   816,   820,   832,   838,
     848,   852,   856,   860,   864,   868,   872,   876,   880,   884,
     888,   892,   896,   908,   912,   916,   920,   924,   928,   932,
     936,   940,   944,   948,   952,   956,   960,   964,   968,   972,
     976,   980,   984,   988,   992,  1000,  1008,  1013,  1021,  1029,
    1037,  1045,  1053,  1061,  1069,  1077,  1082,  1086,  1094,  1106,
    1110,  1114,  1118,  1122,  1126,  1130,  1134,  1142,  1150,  1155,
    1164,  1180,  1196,  1212,  1224,  1240,  1256,  1268,  1274,  1284,
    1288,  1292,  1296,  1304,  1312,  1320,  1328,  1340,  1344,  1348,
    1357,  1371,  1377,  1387,  1391,  1399,  1405,  1415,  1419,  1423,
    1435,  1439,  1447,  1451,  1459,  1465,  1475,  1483,  1493,  1504,
    1508,  1520,  1524,  1532,  1536,  1546,  1552,  1566,  1570,  1579,
    1587,  1593,  1601,  1607,  1619,  1625,  1634,  1638,  1646,  1654
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


#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:1167
} // libcasm_fe
#line 4023 "GrammarParser.cpp" // lalr1.cc:1167
#line 1660 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void Parser::error( const SourceLocation& location, const std::string& message )
{
    log.error( {location}, message, Code::SyntaxError );
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
