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
      case 169: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 168: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 170: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 143: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 108: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 111: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 102: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 101: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 103: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 123: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 106: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 144: // ComposedType
      case 145: // TupleType
      case 146: // RecordType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 122: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 100: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 87: // AttributedDefinition
      case 88: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 86: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 90: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 116: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 89: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 94: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 95: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 125: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 113: // Term
      case 114: // SimpleOrClaspedTerm
      case 115: // OperatorExpression
      case 155: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 171: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 112: // Terms
      case 150: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 149: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 105: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 92: // FunctionDefinition
      case 93: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 85: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 160: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 161: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 162: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 119: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 107: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 121: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 104: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 135: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 126: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 118: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 117: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 140: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 139: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 136: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 138: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 134: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 148: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 97: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 91: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 98: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 109: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 99: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 84: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 147: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 137: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 120: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 141: // Types
      case 151: // FunctionParameters
      case 152: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 127: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 124: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 110: // UpdateRule
      case 158: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 156: // MaybeInitially
      case 157: // Initializers
      case 159: // MaybeInitializers
        value.move< UpdateRules::Ptr > (that.value);
        break;

      case 96: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 128: // BooleanLiteral
      case 129: // IntegerLiteral
      case 130: // RationalLiteral
      case 131: // DecimalLiteral
      case 132: // BinaryLiteral
      case 133: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 163: // Variable
      case 165: // TypedVariable
      case 166: // AttributedVariable
      case 167: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 153: // Parameters
      case 154: // MaybeParameters
      case 164: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 142: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 72: // "binary"
      case 73: // "hexadecimal"
      case 74: // "integer"
      case 75: // "rational"
      case 76: // "decimal"
      case 77: // "string"
      case 78: // "identifier"
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
      case 169: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 168: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 170: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 143: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 108: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 111: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 102: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 101: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 103: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 123: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 106: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 144: // ComposedType
      case 145: // TupleType
      case 146: // RecordType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 122: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 100: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 87: // AttributedDefinition
      case 88: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 86: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 90: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 116: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 89: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 94: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 95: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 125: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 113: // Term
      case 114: // SimpleOrClaspedTerm
      case 115: // OperatorExpression
      case 155: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 171: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 112: // Terms
      case 150: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 149: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 105: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 92: // FunctionDefinition
      case 93: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 85: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 160: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 161: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 162: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 119: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 107: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 121: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 104: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 135: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 126: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 118: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 117: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 140: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 139: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 136: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 138: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 134: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 148: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 97: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 91: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 98: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 109: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 99: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 84: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 147: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 137: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 120: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 141: // Types
      case 151: // FunctionParameters
      case 152: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 127: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 124: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 110: // UpdateRule
      case 158: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 156: // MaybeInitially
      case 157: // Initializers
      case 159: // MaybeInitializers
        value.copy< UpdateRules::Ptr > (that.value);
        break;

      case 96: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 128: // BooleanLiteral
      case 129: // IntegerLiteral
      case 130: // RationalLiteral
      case 131: // DecimalLiteral
      case 132: // BinaryLiteral
      case 133: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 163: // Variable
      case 165: // TypedVariable
      case 166: // AttributedVariable
      case 167: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 153: // Parameters
      case 154: // MaybeParameters
      case 164: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 142: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 72: // "binary"
      case 73: // "hexadecimal"
      case 74: // "integer"
      case 75: // "rational"
      case 76: // "decimal"
      case 77: // "string"
      case 78: // "identifier"
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
      case 169: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 168: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 170: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 143: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 108: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 111: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 102: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 101: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 103: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 123: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 106: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 144: // ComposedType
      case 145: // TupleType
      case 146: // RecordType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 122: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 100: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 87: // AttributedDefinition
      case 88: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 86: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 90: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 116: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 89: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 94: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 95: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 125: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 113: // Term
      case 114: // SimpleOrClaspedTerm
      case 115: // OperatorExpression
      case 155: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 171: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 112: // Terms
      case 150: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 149: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 105: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 92: // FunctionDefinition
      case 93: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 85: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 160: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 161: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 162: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 119: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 107: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 121: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 104: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 135: // ListLiteral
        yylhs.value.build< ListLiteral::Ptr > ();
        break;

      case 126: // Literal
        yylhs.value.build< Literal::Ptr > ();
        break;

      case 118: // LiteralCallExpression
        yylhs.value.build< LiteralCallExpression::Ptr > ();
        break;

      case 117: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 140: // Assignment
        yylhs.value.build< NamedExpression::Ptr > ();
        break;

      case 139: // Assignments
        yylhs.value.build< NamedExpressions::Ptr > ();
        break;

      case 136: // RangeLiteral
        yylhs.value.build< RangeLiteral::Ptr > ();
        break;

      case 138: // RecordLiteral
        yylhs.value.build< RecordLiteral::Ptr > ();
        break;

      case 134: // ReferenceLiteral
        yylhs.value.build< ReferenceLiteral::Ptr > ();
        break;

      case 148: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 97: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 91: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 98: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 109: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 99: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 84: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 147: // TemplateType
        yylhs.value.build< TemplateType::Ptr > ();
        break;

      case 137: // TupleLiteral
        yylhs.value.build< TupleLiteral::Ptr > ();
        break;

      case 120: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 141: // Types
      case 151: // FunctionParameters
      case 152: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 127: // UndefinedLiteral
        yylhs.value.build< UndefLiteral::Ptr > ();
        break;

      case 124: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 110: // UpdateRule
      case 158: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 156: // MaybeInitially
      case 157: // Initializers
      case 159: // MaybeInitializers
        yylhs.value.build< UpdateRules::Ptr > ();
        break;

      case 96: // UsingDefinition
        yylhs.value.build< UsingDefinition::Ptr > ();
        break;

      case 128: // BooleanLiteral
      case 129: // IntegerLiteral
      case 130: // RationalLiteral
      case 131: // DecimalLiteral
      case 132: // BinaryLiteral
      case 133: // StringLiteral
        yylhs.value.build< ValueLiteral::Ptr > ();
        break;

      case 163: // Variable
      case 165: // TypedVariable
      case 166: // AttributedVariable
      case 167: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 153: // Parameters
      case 154: // MaybeParameters
      case 164: // TypedVariables
        yylhs.value.build< VariableDefinitions::Ptr > ();
        break;

      case 142: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 72: // "binary"
      case 73: // "hexadecimal"
      case 74: // "integer"
      case 75: // "rational"
      case 76: // "decimal"
      case 77: // "string"
      case 78: // "identifier"
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
#line 392 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1476 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 401 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1494 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 415 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 421 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1524 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 437 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 441 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1540 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 449 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1548 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 453 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1556 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 457 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 465 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< UsingDefinition::Ptr > ();
  }
#line 1580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 473 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 481 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< VariableDefinitions::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1605 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1614 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 503 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< Identifier::Ptr > ();

      auto function = Ast::make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > () );
      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< UpdateRules::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier( asIdentifierPath( identifier ) );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1634 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 519 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 527 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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

      const auto ruleReference = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );

      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1669 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 550 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< UpdateRules::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier(
              asIdentifierPath( programDefinition->identifier() ) );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 568 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 586 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 614 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 618 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1757 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 654 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 668 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 678 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 686 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 690 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 698 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 702 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1889 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 714 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1923 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 742 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 754 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 762 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1973 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1981 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 782 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1989 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 786 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1998 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 791 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 800 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 804 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2032 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 822 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2051 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > () );
  }
#line 2059 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 836 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< MethodCallExpression::Ptr > () );
  }
#line 2067 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 840 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > () );
  }
#line 2075 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 852 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2085 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 858 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2095 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 868 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2103 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 872 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 876 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 880 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 884 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 888 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 892 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 896 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 904 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 908 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 912 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 920 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LiteralCallExpression::Ptr > ();
  }
#line 2199 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Literal::Ptr > ();
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 940 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 944 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 952 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 964 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 984 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 988 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 992 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 996 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1000 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2343 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1004 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1008 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1012 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1016 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1037 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1042 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1050 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< ValueLiteral::Ptr > () );
  }
#line 2417 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1118 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< UndefLiteral::Ptr > ();
  }
#line 2481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1122 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1126 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1130 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1146 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ReferenceLiteral::Ptr > ();
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ListLiteral::Ptr > ();
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RangeLiteral::Ptr > ();
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1158 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< TupleLiteral::Ptr > ();
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1162 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RecordLiteral::Ptr > ();
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1170 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1178 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2586 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1208 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1224 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::DecimalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1240 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1252 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1268 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1284 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1292 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
  }
#line 2708 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1297 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1301 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = nullptr;
  }
#line 2724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1309 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2732 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1316 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
  }
#line 2742 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1324 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as< NamedExpressions::Ptr > () );
  }
#line 2750 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1331 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = yystack_[2].value.as< NamedExpressions::Ptr > ();
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2760 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1337 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2770 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2778 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1364 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2798 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2806 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2814 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< TemplateType::Ptr > ();
  }
#line 2822 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1386 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2838 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2846 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2854 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2862 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Tuple" );
      auto subTypes = yystack_[3].value.as< Types::Ptr > ();
      subTypes->add( yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes );
  }
#line 2873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Record" );
      auto namedSubTypes = yystack_[3].value.as< VariableDefinitions::Ptr > ();
      namedSubTypes->add( yystack_[1].value.as< VariableDefinition::Ptr > () );

      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      auto subTypes = Ast::make< Types >( yylhs.location );
      for( const auto& namedSubType : *namedSubTypes )
      {
          identifiers->add( namedSubType->identifier() );
          subTypes->add( namedSubType->variableType() );
      }

      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes, identifiers );
  }
#line 2893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2901 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1463 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1475 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1483 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2942 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2952 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1503 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2962 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2970 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1517 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2978 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1525 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 2988 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 2998 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = yystack_[1].value.as< VariableDefinitions::Ptr > ();
  }
#line 3006 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = nullptr;
  }
#line 3014 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1549 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 3022 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 3030 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 3038 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[1].value.as< UpdateRules::Ptr > ();
  }
#line 3046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3054 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< UpdateRules::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3064 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3074 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1601 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3086 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3100 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1619 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< TupleLiteral::Ptr > ()->expressions() );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[0].value.as< UpdateRules::Ptr > ();
  }
#line 3119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 3135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 3143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 3151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 3161 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1672 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 3171 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1678 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 3181 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3189 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1696 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 3198 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3218 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1721 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3226 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1729 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3236 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3244 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3254 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1749 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3262 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[1].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1766 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< BasicAttribute::Ptr > ();
  }
#line 3290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3298 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1784 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = nullptr;
  }
#line 3306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1792 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1800 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3322 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3326 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -191;

  const short int Parser::yytable_ninf_ = -169;

  const short int
  Parser::yypact_[] =
  {
      11,  -191,    30,    56,   239,    42,  -191,    -9,  -191,  -191,
    1515,    17,    19,  -191,  -191,    -1,   -16,   -16,   -16,   -16,
     -16,   399,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
     134,  -191,  -191,  -191,    57,    57,    57,  1515,    57,  -191,
    -191,  -191,  1515,  1515,  1515,   932,   994,   -16,     7,  -191,
    -191,  -191,  -191,  -191,  -191,  2176,   -17,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,   -22,     9,  -191,  -191,  1515,  -191,    40,    33,
      40,    47,    55,  -191,  -191,    81,  -191,  -191,    64,    57,
     115,   119,  1694,   127,  -191,  -191,  -191,   108,  1515,   103,
    1904,   -38,  -191,   111,   116,  -191,   -28,  1938,  -191,  -191,
    1515,  1515,  1515,  1515,  1515,  1515,  1515,  1515,  1515,  1515,
    1515,  1515,  1515,  1515,  1515,  1515,  1515,    23,   -15,  1056,
    -191,   -16,  1972,    94,   113,  -191,   120,     3,    98,   123,
      29,    23,    23,    23,  1515,  -191,  1515,  1515,  1515,  1515,
    -191,  2006,  1515,  -191,  -191,   -16,  1515,  -191,  -191,  1515,
    1515,   263,  2244,  2273,  2210,   161,   161,   373,   152,   152,
     112,   112,   112,  -191,  2210,   373,   152,   152,    23,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,    75,  -191,   -22,
     129,  -191,    38,  2176,  -191,  1515,  1515,  1515,  -191,   132,
      50,    81,  -191,  -191,    57,    23,    22,  1391,    23,  -191,
    -191,   124,   104,  -191,   515,  1835,   148,  1767,  1870,   -22,
    2040,  -191,   111,  2176,  2176,  2074,   138,  -191,    81,   143,
    -191,    23,  1515,  -191,  -191,  -191,  2176,  2176,  -191,  -191,
    -191,    57,  -191,   140,  -191,  -191,    48,  -191,    57,   607,
     674,  -191,    57,    57,    57,  1391,  1515,  1515,   741,   808,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,   135,    88,   136,   139,   183,    23,    23,  1515,
    1515,  1515,  1515,  1515,  -191,  -191,  -191,    23,   -16,   -36,
      32,   165,  -191,  -191,  1515,  -191,    22,  -191,   220,  -191,
    1123,   215,  1190,   191,   218,   223,  -191,  1731,  1801,   186,
    1257,   171,  1324,  1515,  1391,  -191,   241,  2176,  2176,  2176,
    2176,  2176,   205,   208,    23,  -191,    23,  2176,  -191,  -191,
    -191,  -191,  -191,  -191,  1515,  1515,  1515,  1391,   207,  -191,
    -191,  -191,  -191,  2176,  -191,   212,   251,  -191,  -191,  -191,
     206,  1540,  1579,  1618,   238,   870,  1515,   219,  -191,  -191,
    1391,  1391,  1515,  1391,  1391,   226,   216,   221,  -191,  1453,
    2108,  2142,  1515,  -191,  -191,  1657,  -191,  -191,  -191,  1391,
    1391,  -191,  -191,  1391,  -191,   227,  1391,  -191,  -191,  -191,
    -191,  -191
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   203,     0,   188,   187,
     207,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     6,     8,    10,    11,    12,    13,    20,    14,
       0,     3,   202,   206,     0,     0,     0,     0,     0,   130,
     132,   131,     0,     0,     0,     0,     0,     0,     0,   136,
     137,   133,   134,   135,   138,   208,    71,    73,    81,    82,
      83,    84,    72,    74,    75,    76,    77,    78,    85,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   192,   106,   189,   204,   205,   186,    21,   175,     0,
     175,     0,     0,     5,     7,   194,   199,   193,     0,     0,
       0,     0,     0,     0,   105,    86,    87,     0,     0,     0,
      70,     0,   147,   192,     0,   140,     0,    70,   190,   139,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     107,     0,   182,   128,   185,   181,     0,     0,     0,     0,
       0,     0,   170,     0,     0,   198,     0,     0,     0,     0,
      80,     0,     0,    79,   145,     0,     0,   142,   141,     0,
       0,   102,   100,   101,   104,    88,    89,    95,    96,    97,
      90,    91,    92,    93,   103,    94,    98,    99,     0,   112,
     151,   152,   157,   158,   153,   154,   155,   156,   110,   108,
       0,   166,     0,    70,   191,     0,     0,     0,    22,     0,
       0,     0,   201,   172,     0,     0,     0,     0,     0,    28,
     168,   169,     0,   197,     0,     0,     0,     0,     0,     0,
      69,   146,     0,   148,    69,     0,     0,   150,   192,     0,
     196,   170,     0,   109,   165,   164,   183,   184,   180,   174,
     173,     0,   200,     0,    25,    27,     0,    23,     0,     0,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
      17,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     0,    66,    67,    68,     0,     0,     0,     0,
       0,     0,     0,     0,   111,   144,   143,     0,     0,     0,
     150,     0,   163,   171,     0,    15,     0,    24,     0,    41,
       0,     0,     0,     0,     0,     0,    56,     0,     0,     0,
       0,     0,     0,     0,     0,   167,   177,   113,   116,   115,
     114,   117,   149,   195,     0,   161,     0,    16,    26,    64,
      62,    40,    60,    58,     0,     0,     0,     0,     0,    59,
      57,    63,    61,    65,    18,     0,   179,   159,   160,   149,
       0,     0,     0,     0,    43,     0,     0,     0,    19,   162,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
       0,     0,   186,    52,    53,     0,    55,    44,    46,     0,
       0,    45,    50,     0,   176,     0,     0,    47,    48,    49,
     178,    54
  };

  const short int
  Parser::yypgoto_[] =
  {
    -191,  -191,  -191,  -191,   247,   242,  -191,  -191,  -191,  -191,
    -191,   -37,  -191,  -191,   222,  -182,  -191,  -191,  -191,  -102,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,   -45,
     -10,     5,  -191,    99,   128,  -191,   217,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,   146,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,   -80,  -191,  -191,   122,    37,  -109,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -190,  -191,    49,
    -191,   198,  -191,  -191,  -191,    82,   -91,    35,    13,  -191,
     193,  -191,  -123,   -25,    44,     8,     0,  -191,  -191
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,   255,   256,    29,   309,   310,   271,   272,   273,   378,
     379,   274,   275,   276,   277,   278,   279,   280,   281,   109,
     142,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   111,   112,   236,   189,
     190,   191,   192,   193,   194,   195,   196,   140,   221,   222,
     210,   148,   356,   368,   144,   145,   146,    81,    82,    83,
      96,   239,    97,    98,   213,    99,     6,    11,    12
  };

  const short int
  Parser::yytable_[] =
  {
      55,   116,     8,     8,   209,    32,   143,   164,     5,   243,
     100,   101,    30,   103,     1,   137,   165,     8,   334,   168,
     335,     8,   139,   254,   212,     8,   169,   102,    87,    30,
      32,     7,   104,   105,   106,   110,   117,    10,    33,   294,
       8,     8,   219,   220,   223,    31,   138,    86,     8,     2,
      47,    88,    89,    90,    91,    92,    13,     2,    47,    51,
     141,   119,     9,     9,    84,   240,    85,   188,     2,    95,
      95,    95,   217,    95,    47,     8,   149,     9,   312,   237,
     113,     9,   118,   245,   147,     9,   320,   322,     2,  -168,
     151,   252,   169,   218,   202,   250,  -168,   305,   161,    32,
       9,     9,   306,     2,   251,   152,   253,   154,     9,   286,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   143,   212,   203,
     241,   153,   300,   156,    95,     9,   242,   157,    15,    16,
      17,    18,    19,    20,   224,   159,   225,   226,   227,   228,
     197,   -81,   230,   160,   323,   214,   233,   162,   206,   234,
     235,   166,   215,   167,   197,   197,   197,   207,   288,   208,
     291,   216,   132,   199,   244,   333,   204,   249,   325,   326,
       2,   287,   211,   304,   120,   121,   122,   123,   332,   124,
     125,   126,   297,   124,   125,   246,   247,   298,   138,   -82,
     232,   197,   -84,   127,   128,   129,   130,   131,   132,   129,
     130,   131,   132,   133,    32,   134,   135,   136,   129,   130,
     131,   132,   282,   238,   258,   359,   324,   360,   197,   336,
     342,   197,   302,   339,   344,   349,   345,   313,   314,   315,
      14,   346,   351,    15,    16,    17,    18,    19,    20,   211,
     357,   257,   355,   358,   197,   365,   317,   318,    32,   214,
     366,   367,   369,   374,   282,   282,   389,   382,    93,   338,
     282,   390,    94,   282,   282,   388,   400,   392,   299,   327,
     328,   329,   330,   331,   198,     2,   211,   231,   150,   248,
     301,   395,   155,   307,   337,   303,     0,    95,    95,    95,
     197,   197,   143,     0,   124,   125,   126,     0,     0,     0,
     197,     0,     0,   353,   258,   282,   283,   282,   127,   128,
     129,   130,   131,   132,     0,   282,     0,   282,     0,   282,
     134,   135,   136,   211,   361,   362,   363,     0,     0,     0,
       0,   257,     0,     0,     0,   284,     0,   197,     0,   197,
       0,     0,   282,     0,     0,   380,   381,     0,   283,   283,
       0,     0,   385,     0,   283,     0,     0,   283,   283,   380,
       0,     0,     0,     0,     0,   282,   282,     0,   282,   282,
       0,     0,     0,     0,     0,     0,     0,   284,   284,     0,
       0,     0,     0,   284,   282,   282,   284,   284,   282,    -2,
      14,   282,     0,    15,    16,    17,    18,    19,    20,   283,
       0,   283,     0,     0,   124,   125,     0,     0,     0,   283,
       0,   283,     0,   283,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,   285,     0,     0,     0,   284,   270,
     284,   135,   136,     0,     0,     2,   283,     0,   284,     0,
     284,     0,   284,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   283,
     283,     0,   283,   283,     0,   284,   285,   285,     0,     0,
       0,     0,   285,     0,     0,   285,   285,   316,   283,   283,
       0,     0,   283,     0,     0,   283,     0,     0,   284,   284,
       0,   284,   284,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   284,   284,     0,
       0,   284,     0,     0,   284,     0,     0,   285,     0,   285,
       0,     0,   341,   289,   341,     0,     0,   285,     0,   285,
       0,   285,   341,     0,   341,     0,   354,     0,     0,     0,
       0,   120,   121,   122,   123,     0,   124,   125,   126,     0,
       0,     0,     0,     0,   285,     0,     0,     0,     0,   364,
     127,   128,   129,   130,   131,   132,     0,     0,     0,     0,
     133,     0,   134,   135,   136,     0,     0,   285,   285,     0,
     285,   285,   383,   384,     0,   386,   387,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   285,   285,   308,     0,
     285,   397,   398,   285,     0,   399,     0,     0,   401,   259,
       0,   260,     0,   261,   262,     8,   263,   264,   265,     0,
     266,     0,     0,   267,     0,     0,     0,     0,     0,     0,
      39,    40,    41,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,     0,   268,     0,     0,    47,     0,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   311,     0,   269,     0,    49,
      50,    51,    52,    53,    54,     9,   259,     0,   260,     0,
     261,   262,     8,   263,   264,   265,     0,   266,     0,     0,
     267,     0,     0,     0,     0,     0,     0,    39,    40,    41,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
      46,     0,   268,     0,     0,    47,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   319,     0,   269,     0,    49,    50,    51,    52,
      53,    54,     9,   259,     0,   260,     0,   261,   262,     8,
     263,   264,   265,     0,   266,     0,     0,   267,     0,     0,
       0,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,    46,     0,   268,
       0,     0,    47,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   321,
       0,   269,     0,    49,    50,    51,    52,    53,    54,     9,
     259,     0,   260,     0,   261,   262,     8,   263,   264,   265,
       0,   266,     0,     0,   267,     0,     0,     0,     0,     0,
       0,    39,    40,    41,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    46,     0,   268,     0,     0,    47,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   375,     0,     0,     0,     0,     0,     0,   269,     0,
      49,    50,    51,    52,    53,    54,     9,    34,     8,    35,
      36,     0,     0,    37,     0,     0,     0,     0,   376,     0,
      38,     0,     0,    39,    40,    41,     0,     0,     0,     0,
      42,    43,    44,     0,    45,     0,    46,     0,     0,     0,
       0,    47,   377,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,    53,    54,     9,    34,
       8,    35,    36,     0,     0,    37,     0,     0,     0,     0,
       0,     0,    38,     0,     0,    39,    40,    41,     0,     0,
       0,     0,    42,    43,    44,     0,    45,     0,    46,     0,
       0,     0,     0,    47,     0,    48,     0,     0,     0,   108,
       0,     0,     0,     0,     0,   114,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,    51,    52,    53,    54,
       9,    34,     8,    35,    36,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    38,     0,     0,    39,    40,    41,
       0,     0,     0,     0,    42,    43,    44,     0,    45,     0,
      46,   115,     0,     0,     0,    47,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   200,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
      53,    54,     9,    34,     8,    35,    36,     0,     0,    37,
       0,     0,     0,     0,     0,     0,    38,     0,     0,    39,
      40,    41,     0,     0,     0,     0,    42,    43,    44,     0,
      45,   201,    46,     0,     0,     0,     0,    47,     0,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
      51,    52,    53,    54,     9,   259,   340,   260,     0,   261,
     262,     8,   263,   264,   265,     0,   266,     0,     0,   267,
       0,     0,     0,     0,     0,     0,    39,    40,    41,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    46,
       0,   268,     0,     0,    47,     0,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   269,     0,    49,    50,    51,    52,    53,
      54,     9,   259,     0,   260,   343,   261,   262,     8,   263,
     264,   265,     0,   266,     0,     0,   267,     0,     0,     0,
       0,     0,     0,    39,    40,    41,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,     0,   268,     0,
       0,    47,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     269,     0,    49,    50,    51,    52,    53,    54,     9,   259,
       0,   260,     0,   261,   262,     8,   263,   264,   265,     0,
     266,     0,     0,   267,     0,     0,     0,     0,     0,     0,
      39,    40,    41,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,     0,   268,   350,     0,    47,     0,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   269,     0,    49,
      50,    51,    52,    53,    54,     9,   259,     0,   260,     0,
     261,   262,     8,   263,   264,   265,     0,   266,     0,     0,
     267,     0,     0,     0,     0,     0,     0,    39,    40,    41,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
      46,     0,   268,     0,     0,    47,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   269,   352,    49,    50,    51,    52,
      53,    54,     9,   259,     0,   260,     0,   261,   262,     8,
     263,   264,   265,     0,   266,     0,     0,   267,     0,     0,
       0,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,    46,     0,   268,
       0,     0,    47,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   269,     0,    49,    50,    51,    52,    53,    54,     9,
      34,     8,    35,    36,     0,     0,    37,     0,     0,     0,
       0,   376,     0,    38,     0,     0,    39,    40,    41,     0,
       0,     0,     0,    42,    43,    44,     0,    45,     0,    46,
       0,     0,   391,     0,    47,   377,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,    51,    52,    53,
      54,     9,    34,     8,    35,    36,     0,     0,    37,     0,
       0,     0,     0,     0,     0,    38,     0,     0,    39,    40,
      41,     0,     0,     0,     0,    42,    43,    44,   370,    45,
       0,    46,     0,     0,     0,     0,    47,     0,    48,     0,
       0,     0,     0,     0,     0,     0,   120,   121,   122,   123,
       0,   124,   125,   126,     0,     0,     0,    49,    50,    51,
      52,    53,    54,     9,     0,   127,   128,   129,   130,   131,
     132,   371,     0,     0,     0,   133,     0,   134,   135,   136,
     372,     0,     0,     0,     0,   120,   121,   122,   123,     0,
     124,   125,   126,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   127,   128,   129,   130,   131,   132,
     373,     0,     0,     0,   133,     0,   134,   135,   136,     0,
       0,     0,     0,     0,   120,   121,   122,   123,     0,   124,
     125,   126,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   396,
       0,     0,     0,   133,     0,   134,   135,   136,     0,     0,
       0,     0,     0,   120,   121,   122,   123,     0,   124,   125,
     126,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,   129,   130,   131,   132,   158,     0,
       0,     0,   133,     0,   134,   135,   136,     0,     0,     0,
     120,   121,   122,   123,     0,   124,   125,   126,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,   129,   130,   131,   132,   347,     0,     0,     0,   133,
       0,   134,   135,   136,     0,     0,     0,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,   292,     0,     0,     0,   133,     0,   134,   135,
     136,     0,     0,   120,   121,   122,   123,     0,   124,   125,
     126,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,   129,   130,   131,   132,   348,     0,
       0,     0,   133,     0,   134,   135,   136,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,     0,     0,   290,     0,   133,     0,   134,   135,
     136,   120,   121,   122,   123,     0,   124,   125,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,     0,     0,     0,     0,
     133,   293,   134,   135,   136,     0,   120,   121,   122,   123,
       0,   124,   125,   126,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,     0,     0,     0,     0,   133,     0,   134,   135,   136,
     120,   121,   122,   123,     0,   124,   125,   126,     0,   163,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,   129,   130,   131,   132,     0,     0,     0,     0,   133,
       0,   134,   135,   136,   120,   121,   122,   123,     0,   124,
     125,   126,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,   129,   130,   131,   132,     0,
     170,     0,     0,   133,     0,   134,   135,   136,   120,   121,
     122,   123,     0,   124,   125,   126,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   127,   128,   129,
     130,   131,   132,     0,     0,     0,   205,   133,     0,   134,
     135,   136,   120,   121,   122,   123,     0,   124,   125,   126,
       0,   229,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,   129,   130,   131,   132,     0,     0,     0,
       0,   133,     0,   134,   135,   136,   120,   121,   122,   123,
       0,   124,   125,   126,     0,   295,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,     0,     0,     0,     0,   133,     0,   134,   135,   136,
     120,   121,   122,   123,     0,   124,   125,   126,     0,     0,
       0,   296,     0,     0,     0,     0,     0,     0,     0,   127,
     128,   129,   130,   131,   132,     0,     0,     0,     0,   133,
       0,   134,   135,   136,   120,   121,   122,   123,     0,   124,
     125,   126,     0,     0,     0,     0,     0,     0,   393,     0,
       0,     0,     0,   127,   128,   129,   130,   131,   132,     0,
       0,     0,     0,   133,     0,   134,   135,   136,   120,   121,
     122,   123,     0,   124,   125,   126,     0,     0,     0,     0,
       0,   394,     0,     0,     0,     0,     0,   127,   128,   129,
     130,   131,   132,     0,     0,     0,     0,   133,     0,   134,
     135,   136,   120,   121,   122,   123,     0,   124,   125,   126,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,   129,   130,   131,   132,     0,     0,     0,
       0,   133,     0,   134,   135,   136,   120,   121,   122,     0,
       0,   124,   125,   126,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,     0,     0,     0,     0,     0,     0,   134,   135,   136,
     120,     0,   122,     0,     0,   124,   125,   126,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,   129,   130,   131,   132,     0,     0,     0,     0,   120,
       0,   134,   135,   136,   124,   125,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,     0,     0,
     134,   135,   136
  };

  const short int
  Parser::yycheck_[] =
  {
      10,    46,    18,    18,     1,     5,    86,    45,     0,   199,
      35,    36,     4,    38,     3,    32,    54,    18,    54,    47,
      56,    18,    44,     1,   147,    18,    54,    37,    15,    21,
      30,     1,    42,    43,    44,    45,    46,     2,    47,   229,
      18,    18,   151,   152,   153,     3,    63,    48,    18,    46,
      51,    16,    17,    18,    19,    20,     0,    46,    51,    74,
      51,    48,    78,    78,    47,   188,    47,    44,    46,    34,
      35,    36,    43,    38,    51,    18,    43,    78,   260,   188,
      45,    78,    47,    45,    44,    78,   268,   269,    46,    57,
      43,   214,    54,    64,   139,    45,    64,    49,   108,    99,
      78,    78,    54,    46,    54,    50,   215,    43,    78,   218,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   207,   251,   139,
      55,    50,   241,    18,    99,    78,    61,    18,     4,     5,
       6,     7,     8,     9,   154,    18,   156,   157,   158,   159,
     137,    63,   162,    45,    66,   147,   166,    54,    64,   169,
     170,    50,    64,    47,   151,   152,   153,    54,    64,    49,
      22,    48,    60,   138,    45,   298,   141,    45,   287,   288,
      46,    57,   147,    43,    36,    37,    38,    39,   297,    41,
      42,    43,    54,    41,    42,   205,   206,    54,    63,    63,
     165,   188,    63,    55,    56,    57,    58,    59,    60,    57,
      58,    59,    60,    65,   214,    67,    68,    69,    57,    58,
      59,    60,   217,   188,   216,   334,    43,   336,   215,    64,
      15,   218,   242,    13,    43,    49,    18,   262,   263,   264,
       1,    18,    71,     4,     5,     6,     7,     8,     9,   214,
      45,   216,    11,    45,   241,    48,   266,   267,   258,   251,
      48,    10,    56,    25,   259,   260,    50,    48,    21,   306,
     265,    50,    30,   268,   269,    49,    49,   379,   241,   289,
     290,   291,   292,   293,   138,    46,   251,   165,    90,   207,
     241,   382,    99,   258,   304,   251,    -1,   262,   263,   264,
     287,   288,   382,    -1,    41,    42,    43,    -1,    -1,    -1,
     297,    -1,    -1,   323,   306,   310,   217,   312,    55,    56,
      57,    58,    59,    60,    -1,   320,    -1,   322,    -1,   324,
      67,    68,    69,   298,   344,   345,   346,    -1,    -1,    -1,
      -1,   306,    -1,    -1,    -1,   217,    -1,   334,    -1,   336,
      -1,    -1,   347,    -1,    -1,   365,   366,    -1,   259,   260,
      -1,    -1,   372,    -1,   265,    -1,    -1,   268,   269,   379,
      -1,    -1,    -1,    -1,    -1,   370,   371,    -1,   373,   374,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   259,   260,    -1,
      -1,    -1,    -1,   265,   389,   390,   268,   269,   393,     0,
       1,   396,    -1,     4,     5,     6,     7,     8,     9,   310,
      -1,   312,    -1,    -1,    41,    42,    -1,    -1,    -1,   320,
      -1,   322,    -1,   324,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,   217,    -1,    -1,    -1,   310,   217,
     312,    68,    69,    -1,    -1,    46,   347,    -1,   320,    -1,
     322,    -1,   324,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   370,
     371,    -1,   373,   374,    -1,   347,   259,   260,    -1,    -1,
      -1,    -1,   265,    -1,    -1,   268,   269,   265,   389,   390,
      -1,    -1,   393,    -1,    -1,   396,    -1,    -1,   370,   371,
      -1,   373,   374,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   389,   390,    -1,
      -1,   393,    -1,    -1,   396,    -1,    -1,   310,    -1,   312,
      -1,    -1,   310,    18,   312,    -1,    -1,   320,    -1,   322,
      -1,   324,   320,    -1,   322,    -1,   324,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,   347,    -1,    -1,    -1,    -1,   347,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      65,    -1,    67,    68,    69,    -1,    -1,   370,   371,    -1,
     373,   374,   370,   371,    -1,   373,   374,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   389,   390,     1,    -1,
     393,   389,   390,   396,    -1,   393,    -1,    -1,   396,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    46,    -1,    48,    -1,    -1,    51,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    70,    -1,    72,
      73,    74,    75,    76,    77,    78,    12,    -1,    14,    -1,
      16,    17,    18,    19,    20,    21,    -1,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      46,    -1,    48,    -1,    -1,    51,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    70,    -1,    72,    73,    74,    75,
      76,    77,    78,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    46,    -1,    48,
      -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    70,    -1,    72,    73,    74,    75,    76,    77,    78,
      12,    -1,    14,    -1,    16,    17,    18,    19,    20,    21,
      -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    46,    -1,    48,    -1,    -1,    51,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      72,    73,    74,    75,    76,    77,    78,    17,    18,    19,
      20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    -1,
      30,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,
      -1,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    17,
      18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    -1,    44,    -1,    46,    -1,
      -1,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,    -1,
      46,    47,    -1,    -1,    -1,    51,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    17,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    51,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    12,    13,    14,    -1,    16,
      17,    18,    19,    20,    21,    -1,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    46,
      -1,    48,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    72,    73,    74,    75,    76,
      77,    78,    12,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    46,    -1,    48,    -1,
      -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    75,    76,    77,    78,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    46,    -1,    48,    49,    -1,    51,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,
      73,    74,    75,    76,    77,    78,    12,    -1,    14,    -1,
      16,    17,    18,    19,    20,    21,    -1,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      46,    -1,    48,    -1,    -1,    51,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    46,    -1,    48,
      -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    72,    73,    74,    75,    76,    77,    78,
      17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    28,    -1,    30,    -1,    -1,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    -1,    44,    -1,    46,
      -1,    -1,    49,    -1,    51,    52,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    17,    18,    19,    20,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    18,    44,
      -1,    46,    -1,    -1,    -1,    -1,    51,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    -1,    55,    56,    57,    58,    59,
      60,    22,    -1,    -1,    -1,    65,    -1,    67,    68,    69,
      31,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      22,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    22,
      -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    24,    -1,
      -1,    -1,    65,    -1,    67,    68,    69,    -1,    -1,    -1,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    24,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    25,    -1,    -1,    -1,    65,    -1,    67,    68,
      69,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    27,    -1,
      -1,    -1,    65,    -1,    67,    68,    69,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    29,    -1,    65,    -1,    67,    68,
      69,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      65,    31,    67,    68,    69,    -1,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,    -1,    65,    -1,    67,    68,    69,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    64,    65,    -1,    67,
      68,    69,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    65,    -1,    67,    68,    69,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    -1,    67,
      68,    69,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    36,    37,    38,    -1,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      36,    -1,    38,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    36,
      -1,    67,    68,    69,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    46,    84,    85,   168,   169,     1,    18,    78,
     160,   170,   171,     0,     1,     4,     5,     6,     7,     8,
       9,    86,    87,    88,    89,    90,    91,    92,    93,    96,
     168,     3,   169,    47,    17,    19,    20,    23,    30,    33,
      34,    35,    40,    41,    42,    44,    46,    51,    53,    72,
      73,    74,    75,    76,    77,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   160,   161,   162,    47,    47,    48,   161,   160,   160,
     160,   160,   160,    87,    88,   160,   163,   165,   166,   168,
     166,   166,   113,   166,   113,   113,   113,     1,    57,   112,
     113,   139,   140,   160,     1,    47,   112,   113,   160,   161,
      36,    37,    38,    39,    41,    42,    43,    55,    56,    57,
      58,    59,    60,    65,    67,    68,    69,    32,    63,    44,
     150,    51,   113,   137,   157,   158,   159,    44,   154,    43,
     154,    43,    50,    50,    43,   163,    18,    18,    24,    18,
      45,   113,    54,    45,    45,    54,    50,    47,    47,    54,
      62,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,    44,   142,
     143,   144,   145,   146,   147,   148,   149,   161,   129,   160,
       1,    45,   112,   113,   160,    64,    64,    54,    49,     1,
     153,   160,   165,   167,   168,    64,    48,    43,    64,   142,
     142,   151,   152,   142,   113,   113,   113,   113,   113,    45,
     113,   140,   160,   113,   113,   113,   141,   142,   160,   164,
     165,    55,    61,   150,    45,    45,   113,   113,   158,    45,
      45,    54,   165,   142,     1,    94,    95,   160,   168,    12,
      14,    16,    17,    19,    20,    21,    23,    26,    48,    70,
      97,    99,   100,   101,   104,   105,   106,   107,   108,   109,
     110,   111,   114,   116,   117,   119,   142,    57,    64,    18,
      29,    22,    25,    31,   150,    45,    47,    54,    54,   141,
     142,   152,   113,   167,    43,    49,    54,   160,     1,    97,
      98,     1,    98,   166,   166,   166,    97,   113,   113,     1,
      98,     1,    98,    66,    43,   142,   142,   113,   113,   113,
     113,   113,   142,   165,    54,    56,    64,   113,    94,    13,
      13,    97,    15,    15,    43,    18,    18,    24,    27,    49,
      49,    71,    71,   113,    97,    11,   155,    45,    45,   142,
     142,   113,   113,   113,    97,    48,    48,    10,   156,    56,
      18,    22,    31,    22,    25,     1,    28,    52,   102,   103,
     113,   113,    48,    97,    97,   113,    97,    97,    49,    50,
      50,    49,   102,    50,    49,   159,    22,    97,    97,    97,
      49,    97
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    83,    84,    85,    85,    86,    86,    87,    87,    87,
      88,    88,    88,    88,    88,    89,    90,    91,    91,    92,
      92,    93,    93,    94,    94,    94,    95,    95,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      98,    98,    99,   100,   100,   101,   101,   102,   102,   102,
     103,   103,   104,   105,   105,   106,   107,   108,   108,   108,
     108,   109,   109,   109,   109,   110,   111,   111,   111,   112,
     112,   113,   113,   113,   113,   113,   113,   113,   113,   114,
     114,   114,   114,   114,   114,   114,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   116,   116,   117,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     127,   128,   128,   129,   130,   131,   132,   132,   133,   134,
     135,   135,   135,   136,   137,   138,   139,   139,   140,   141,
     141,   142,   142,   142,   142,   142,   143,   144,   144,   145,
     146,   147,   148,   149,   150,   150,   150,   151,   151,   152,
     152,   153,   153,   154,   154,   154,   155,   155,   156,   156,
     157,   157,   158,   158,   158,   159,   159,   160,   160,   161,
     161,   162,   162,   163,   163,   164,   164,   165,   166,   166,
     167,   167,   168,   168,   169,   169,   169,   170,   171
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     6,     7,     5,     7,     8,
       1,     2,     4,     1,     2,     1,     3,     1,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     4,     6,     6,     6,     3,     3,     3,
       2,     1,     6,     6,     8,     6,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     1,     1,     1,     1,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     2,     3,     4,
       3,     5,     3,     6,     6,     6,     6,     6,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     5,     5,     3,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       5,     4,     6,     3,     3,     3,     2,     3,     1,     1,
       0,     3,     1,     3,     3,     0,     4,     0,     4,     0,
       3,     1,     1,     3,     3,     1,     0,     1,     1,     1,
       2,     3,     1,     1,     1,     3,     1,     3,     2,     1,
       2,     1,     2,     1,     3,     3,     3,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"using\"",
  "\"function\"", "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"",
  "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"choose\"", "\"iterate\"", "\"do\"", "\"if\"", "\"then\"", "\"else\"",
  "\"case\"", "\"of\"", "\"default\"", "\"holds\"", "\"exists\"",
  "\"with\"", "\"as\"", "\"undef\"", "\"false\"", "\"true\"", "\"and\"",
  "\"or\"", "\"xor\"", "\"implies\"", "\"not\"", "\"+\"", "\"-\"", "\"=\"",
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\":\"", "\"::\"",
  "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"",
  "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"", "\"=>\"", "\":=\"",
  "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"decimal\"",
  "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header", "Definitions",
  "AttributedDefinition", "Definition", "EnumerationDefinition",
  "DerivedDefinition", "RuleDefinition", "FunctionDefinition",
  "ProgramFunctionDefinition", "EnumeratorDefinition", "Enumerators",
  "UsingDefinition", "Rule", "Rules", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabel", "CaseLabels", "LetRule", "ForallRule",
  "ChooseRule", "IterateRule", "BlockRule", "SequenceRule", "UpdateRule",
  "CallRule", "Terms", "Term", "SimpleOrClaspedTerm", "OperatorExpression",
  "DirectCallExpression", "MethodCallExpression", "LiteralCallExpression",
  "IndirectCallExpression", "TypeCastingExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "Literal", "UndefinedLiteral", "BooleanLiteral", "IntegerLiteral",
  "RationalLiteral", "DecimalLiteral", "BinaryLiteral", "StringLiteral",
  "ReferenceLiteral", "ListLiteral", "RangeLiteral", "TupleLiteral",
  "RecordLiteral", "Assignments", "Assignment", "Types", "Type",
  "BasicType", "ComposedType", "TupleType", "RecordType", "TemplateType",
  "RelationType", "FixedSizedType", "Arguments", "FunctionParameters",
  "MaybeFunctionParameters", "Parameters", "MaybeParameters",
  "MaybeDefined", "MaybeInitially", "Initializers", "Initializer",
  "MaybeInitializers", "Identifier", "IdentifierPath",
  "DotSeparatedIdentifiers", "Variable", "TypedVariables", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "Attributes",
  "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   391,   391,   400,   406,   414,   420,   430,   436,   440,
     448,   452,   456,   460,   464,   472,   480,   488,   493,   502,
     518,   526,   549,   567,   571,   577,   585,   591,   601,   613,
     617,   621,   625,   629,   633,   637,   641,   645,   649,   653,
     661,   667,   677,   685,   689,   697,   701,   709,   713,   717,
     725,   731,   741,   749,   753,   761,   769,   777,   781,   785,
     790,   799,   803,   807,   812,   821,   831,   835,   839,   851,
     857,   867,   871,   875,   879,   883,   887,   891,   895,   903,
     907,   911,   915,   919,   923,   927,   939,   943,   947,   951,
     955,   959,   963,   967,   971,   975,   979,   983,   987,   991,
     995,   999,  1003,  1007,  1011,  1015,  1023,  1028,  1036,  1041,
    1049,  1057,  1065,  1073,  1081,  1089,  1097,  1105,  1117,  1121,
    1125,  1129,  1133,  1137,  1141,  1145,  1149,  1153,  1157,  1161,
    1169,  1177,  1182,  1191,  1207,  1223,  1239,  1251,  1267,  1283,
    1291,  1296,  1300,  1308,  1315,  1323,  1330,  1336,  1345,  1357,
    1363,  1373,  1377,  1381,  1385,  1389,  1397,  1405,  1409,  1416,
    1426,  1446,  1454,  1462,  1474,  1478,  1482,  1496,  1502,  1512,
    1516,  1524,  1530,  1540,  1544,  1548,  1560,  1564,  1572,  1576,
    1584,  1590,  1600,  1608,  1618,  1629,  1633,  1645,  1649,  1657,
    1661,  1671,  1677,  1691,  1695,  1704,  1710,  1720,  1728,  1734,
    1742,  1748,  1759,  1765,  1775,  1779,  1783,  1791,  1799
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
#line 4389 "GrammarParser.cpp" // lalr1.cc:1167
#line 1805 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
