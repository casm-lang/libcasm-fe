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
      case 170: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 169: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 171: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 144: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 109: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 112: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 103: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 102: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 104: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 124: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 107: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 145: // ComposedType
      case 146: // TupleType
      case 147: // RecordType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 123: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 101: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 88: // AttributedDefinition
      case 89: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 87: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 91: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 117: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 90: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 95: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 96: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 126: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 114: // Term
      case 115: // SimpleOrClaspedTerm
      case 116: // OperatorExpression
      case 156: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 172: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 113: // Terms
      case 151: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 150: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 106: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 93: // FunctionDefinition
      case 94: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 86: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 161: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 162: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 163: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 120: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 108: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 122: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 105: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 136: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 127: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 119: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 118: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 141: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 140: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 137: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 139: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 135: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 149: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 98: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 92: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 99: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 110: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 100: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 85: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 148: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 138: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 121: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 142: // Types
      case 152: // FunctionParameters
      case 153: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 128: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 125: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 111: // UpdateRule
      case 159: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 157: // MaybeInitially
      case 158: // Initializers
      case 160: // MaybeInitializers
        value.move< UpdateRules::Ptr > (that.value);
        break;

      case 97: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 129: // BooleanLiteral
      case 130: // IntegerLiteral
      case 131: // RationalLiteral
      case 132: // DecimalLiteral
      case 133: // BinaryLiteral
      case 134: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 164: // Variable
      case 166: // TypedVariable
      case 167: // AttributedVariable
      case 168: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 154: // Parameters
      case 155: // MaybeParameters
      case 165: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 143: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 73: // "binary"
      case 74: // "hexadecimal"
      case 75: // "integer"
      case 76: // "rational"
      case 77: // "decimal"
      case 78: // "string"
      case 79: // "identifier"
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
      case 170: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 169: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 171: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 144: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 109: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 112: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 103: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 102: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 104: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 124: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 107: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 145: // ComposedType
      case 146: // TupleType
      case 147: // RecordType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 123: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 101: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 88: // AttributedDefinition
      case 89: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 87: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 91: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 117: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 90: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 95: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 96: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 126: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 114: // Term
      case 115: // SimpleOrClaspedTerm
      case 116: // OperatorExpression
      case 156: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 172: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 113: // Terms
      case 151: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 150: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 106: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 93: // FunctionDefinition
      case 94: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 86: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 161: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 162: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 163: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 120: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 108: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 122: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 105: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 136: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 127: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 119: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 118: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 141: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 140: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 137: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 139: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 135: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 149: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 98: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 92: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 99: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 110: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 100: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 85: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 148: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 138: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 121: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 142: // Types
      case 152: // FunctionParameters
      case 153: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 128: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 125: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 111: // UpdateRule
      case 159: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 157: // MaybeInitially
      case 158: // Initializers
      case 160: // MaybeInitializers
        value.copy< UpdateRules::Ptr > (that.value);
        break;

      case 97: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 129: // BooleanLiteral
      case 130: // IntegerLiteral
      case 131: // RationalLiteral
      case 132: // DecimalLiteral
      case 133: // BinaryLiteral
      case 134: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 164: // Variable
      case 166: // TypedVariable
      case 167: // AttributedVariable
      case 168: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 154: // Parameters
      case 155: // MaybeParameters
      case 165: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 143: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 73: // "binary"
      case 74: // "hexadecimal"
      case 75: // "integer"
      case 76: // "rational"
      case 77: // "decimal"
      case 78: // "string"
      case 79: // "identifier"
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
      case 170: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 169: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 171: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 144: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 109: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 112: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 103: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 102: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 104: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 124: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 107: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 145: // ComposedType
      case 146: // TupleType
      case 147: // RecordType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 123: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 101: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 88: // AttributedDefinition
      case 89: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 87: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 91: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 117: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 90: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 95: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 96: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 126: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 114: // Term
      case 115: // SimpleOrClaspedTerm
      case 116: // OperatorExpression
      case 156: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 172: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 113: // Terms
      case 151: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 150: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 106: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 93: // FunctionDefinition
      case 94: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 86: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 161: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 162: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 163: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 120: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 108: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 122: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 105: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 136: // ListLiteral
        yylhs.value.build< ListLiteral::Ptr > ();
        break;

      case 127: // Literal
        yylhs.value.build< Literal::Ptr > ();
        break;

      case 119: // LiteralCallExpression
        yylhs.value.build< LiteralCallExpression::Ptr > ();
        break;

      case 118: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 141: // Assignment
        yylhs.value.build< NamedExpression::Ptr > ();
        break;

      case 140: // Assignments
        yylhs.value.build< NamedExpressions::Ptr > ();
        break;

      case 137: // RangeLiteral
        yylhs.value.build< RangeLiteral::Ptr > ();
        break;

      case 139: // RecordLiteral
        yylhs.value.build< RecordLiteral::Ptr > ();
        break;

      case 135: // ReferenceLiteral
        yylhs.value.build< ReferenceLiteral::Ptr > ();
        break;

      case 149: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 98: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 92: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 99: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 110: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 100: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 85: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 148: // TemplateType
        yylhs.value.build< TemplateType::Ptr > ();
        break;

      case 138: // TupleLiteral
        yylhs.value.build< TupleLiteral::Ptr > ();
        break;

      case 121: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 142: // Types
      case 152: // FunctionParameters
      case 153: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 128: // UndefinedLiteral
        yylhs.value.build< UndefLiteral::Ptr > ();
        break;

      case 125: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 111: // UpdateRule
      case 159: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 157: // MaybeInitially
      case 158: // Initializers
      case 160: // MaybeInitializers
        yylhs.value.build< UpdateRules::Ptr > ();
        break;

      case 97: // UsingDefinition
        yylhs.value.build< UsingDefinition::Ptr > ();
        break;

      case 129: // BooleanLiteral
      case 130: // IntegerLiteral
      case 131: // RationalLiteral
      case 132: // DecimalLiteral
      case 133: // BinaryLiteral
      case 134: // StringLiteral
        yylhs.value.build< ValueLiteral::Ptr > ();
        break;

      case 164: // Variable
      case 166: // TypedVariable
      case 167: // AttributedVariable
      case 168: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 154: // Parameters
      case 155: // MaybeParameters
      case 165: // TypedVariables
        yylhs.value.build< VariableDefinitions::Ptr > ();
        break;

      case 143: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 73: // "binary"
      case 74: // "hexadecimal"
      case 75: // "integer"
      case 76: // "rational"
      case 77: // "decimal"
      case 78: // "string"
      case 79: // "identifier"
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
#line 395 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1476 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1494 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 418 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1524 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1540 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 452 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1548 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 456 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1556 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 464 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 468 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< UsingDefinition::Ptr > ();
  }
#line 1580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 492 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< VariableDefinitions::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1605 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1614 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 506 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 522 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 530 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 571 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 575 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 595 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 621 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1757 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 625 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 629 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 637 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 641 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 649 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 653 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 657 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 665 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 689 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 693 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 701 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1889 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 713 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 717 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 721 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 729 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1923 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 745 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 753 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 765 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 773 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1973 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 781 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1981 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1989 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 789 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1998 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 794 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 807 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 811 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2032 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2051 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 835 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 2059 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 839 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 2067 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< MethodCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 2075 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 847 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< MethodCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 2083 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 851 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 2091 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 855 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 2099 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 867 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2109 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 873 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 883 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 895 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 923 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2199 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 927 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 931 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 935 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LiteralCallExpression::Ptr > ();
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 939 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 943 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Literal::Ptr > ();
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 955 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 959 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 963 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 967 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 971 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 975 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 979 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 983 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 987 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 991 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 995 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 999 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1003 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2343 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1007 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1011 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1015 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1019 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1023 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1027 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1031 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1039 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1044 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1052 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1057 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1065 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< ValueLiteral::Ptr > () );
  }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1073 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1081 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1089 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1097 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1105 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1113 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1121 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< UndefLiteral::Ptr > ();
  }
#line 2505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1137 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1141 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1145 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1149 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1153 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1157 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1161 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ReferenceLiteral::Ptr > ();
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ListLiteral::Ptr > ();
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1169 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RangeLiteral::Ptr > ();
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1173 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< TupleLiteral::Ptr > ();
  }
#line 2585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1177 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RecordLiteral::Ptr > ();
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1185 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1193 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2610 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1198 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1207 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1223 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1239 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1255 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1267 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1283 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1299 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1307 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
  }
#line 2732 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1312 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1316 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = nullptr;
  }
#line 2748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1324 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1331 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
  }
#line 2766 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1339 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as< NamedExpressions::Ptr > () );
  }
#line 2774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = yystack_[2].value.as< NamedExpressions::Ptr > ();
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2784 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1352 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1361 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2802 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2822 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1389 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2838 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< TemplateType::Ptr > ();
  }
#line 2846 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1401 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2854 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1405 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2862 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1413 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2870 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1421 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2878 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1425 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1432 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Tuple" );
      auto subTypes = yystack_[3].value.as< Types::Ptr > ();
      subTypes->add( yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes );
  }
#line 2897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1462 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1470 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1490 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1498 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2966 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1512 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1518 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2986 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1528 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2994 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3012 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1546 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3022 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1556 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = yystack_[1].value.as< VariableDefinitions::Ptr > ();
  }
#line 3030 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1560 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = nullptr;
  }
#line 3038 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1564 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 3046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1576 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 3054 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1580 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 3062 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1588 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[1].value.as< UpdateRules::Ptr > ();
  }
#line 3070 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1600 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< UpdateRules::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3098 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3110 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3124 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< TupleLiteral::Ptr > ()->expressions() );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[0].value.as< UpdateRules::Ptr > ();
  }
#line 3143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1649 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 3159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1665 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 3167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1673 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 3175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 3185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1687 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 3195 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1693 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 3205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1707 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3213 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 3222 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3232 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1736 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3250 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1744 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3260 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3278 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3286 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1775 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[1].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1781 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1791 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< BasicAttribute::Ptr > ();
  }
#line 3314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1795 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3322 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 1799 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = nullptr;
  }
#line 3330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 1807 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 1815 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3346 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3350 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -186;

  const short int Parser::yytable_ninf_ = -172;

  const short int
  Parser::yypact_[] =
  {
       5,  -186,    49,    23,   240,    16,  -186,    -7,  -186,  -186,
    1553,    20,    51,  -186,  -186,    -1,     0,     0,     0,     0,
       0,   133,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
     170,  -186,  -186,  -186,    -2,    -2,    -2,  1553,    -2,  -186,
    -186,  -186,  1553,  1553,  1553,   961,  1024,     0,   -14,  -186,
    -186,  -186,  -186,  -186,  -186,  2310,   -21,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,     8,    33,  -186,  -186,  1553,  -186,    60,    64,
      60,    65,    80,  -186,  -186,    84,  -186,  -186,    92,    -2,
     125,   127,  1821,   135,  -186,  -186,  -186,   105,  1553,   109,
    2038,   -18,  -186,   114,   118,  -186,     9,  2072,  -186,  -186,
      -3,  1553,  1553,  1553,  1553,  1553,  1553,  1553,  1553,  1553,
    1553,  1553,  1553,  1553,  1553,  1553,  1553,  1553,   -13,  1087,
    -186,     0,  2106,   103,   128,  -186,   132,    12,   119,   136,
      -5,    -3,    -3,    -3,  1553,  -186,  1553,  1553,  1553,  1553,
    -186,  2140,  1553,  -186,  -186,     0,  1553,  -186,  -186,  1553,
    1553,    -3,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
      26,   246,  2344,   452,   544,    43,    43,   286,    13,    13,
     129,   129,   129,  -186,   544,   286,    13,    13,  -186,     8,
     146,  -186,    15,  2310,  -186,  1553,  1553,  1553,  -186,   147,
      37,    84,  -186,  -186,    -2,    -3,    28,  1427,    -3,  -186,
    -186,   139,   121,  -186,  1579,  1965,  1703,  1897,  2004,     8,
    2174,  -186,   114,  2310,  2310,  2208,   144,  -186,    84,   148,
    -186,    -3,  1553,  -186,  -186,  -186,  2310,  2310,  -186,  -186,
    -186,    -2,  -186,   150,  -186,  -186,    31,  -186,    -2,   631,
     699,  -186,    -2,    -2,    -2,  1427,   188,  1553,  1553,   767,
     835,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,   -21,    29,   137,   138,   160,    -3,    -3,
    1553,  1553,  1553,  1553,  1553,  -186,  -186,  -186,    -3,     0,
      40,   -11,   143,  -186,  -186,  1553,  -186,    28,  -186,   192,
    -186,  1155,   195,  1223,   167,   194,   196,  -186,   149,   137,
     138,  1859,  1931,   166,  1291,   155,  1359,  1553,  1427,  -186,
     207,  2310,  2310,  2310,  2310,  2310,   174,   175,    -3,  -186,
      -3,  2310,  -186,  -186,  -186,  -186,  -186,  -186,  1553,  1553,
    1553,  1427,   177,  -186,  -186,  -186,  -186,  2310,  -186,   180,
     220,  -186,  -186,  -186,   182,  1623,  1663,  1743,   205,   898,
    1553,   185,  -186,  -186,  1427,  1427,  1553,  1427,  1427,   193,
     199,   202,  -186,  1490,  2242,  2276,  1553,  -186,  -186,  1783,
    -186,  -186,  -186,  1427,  1427,  -186,  -186,  1427,  -186,   206,
    1427,  -186,  -186,  -186,  -186,  -186
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   206,     0,   191,   190,
     210,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     6,     8,    10,    11,    12,    13,    20,    14,
       0,     3,   205,   209,     0,     0,     0,     0,     0,   133,
     135,   134,     0,     0,     0,     0,     0,     0,     0,   139,
     140,   136,   137,   138,   141,   211,    74,    76,    84,    85,
      86,    87,    75,    77,    78,    79,    80,    81,    88,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   195,   109,   192,   207,   208,   189,    21,   178,     0,
     178,     0,     0,     5,     7,   197,   202,   196,     0,     0,
       0,     0,     0,     0,   108,    89,    90,     0,     0,     0,
      73,     0,   150,   195,     0,   143,     0,    73,   193,   142,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,     0,   185,   131,   188,   184,     0,     0,     0,     0,
       0,     0,   173,     0,     0,   201,     0,     0,     0,     0,
      83,     0,     0,    82,   148,     0,     0,   145,   144,     0,
       0,     0,   115,   154,   155,   160,   161,   156,   157,   158,
     159,   105,   103,   104,   107,    91,    92,    98,    99,   100,
      93,    94,    95,    96,   106,    97,   101,   102,   113,   111,
       0,   169,     0,    73,   194,     0,     0,     0,    22,     0,
       0,     0,   204,   175,     0,     0,     0,     0,     0,    28,
     171,   172,     0,   200,     0,     0,     0,     0,     0,     0,
      72,   149,     0,   151,    72,     0,     0,   153,   195,     0,
     199,   173,     0,   112,   168,   167,   186,   187,   183,   177,
     176,     0,   203,     0,    25,    27,     0,    23,     0,     0,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     0,    67,    69,    71,     0,     0,     0,
       0,     0,     0,     0,     0,   114,   147,   146,     0,     0,
       0,   153,     0,   166,   174,     0,    15,     0,    24,     0,
      41,     0,     0,     0,     0,     0,     0,    56,    66,    68,
      70,     0,     0,     0,     0,     0,     0,     0,     0,   170,
     180,   116,   119,   118,   117,   120,   152,   198,     0,   164,
       0,    16,    26,    64,    62,    40,    60,    58,     0,     0,
       0,     0,     0,    59,    57,    63,    61,    65,    18,     0,
     182,   162,   163,   152,     0,     0,     0,     0,    43,     0,
       0,     0,    19,   165,     0,     0,     0,     0,     0,     0,
       0,     0,    51,     0,     0,     0,   189,    52,    53,     0,
      55,    44,    46,     0,     0,    45,    50,     0,   179,     0,
       0,    47,    48,    49,   181,    54
  };

  const short int
  Parser::yypgoto_[] =
  {
    -186,  -186,  -186,  -186,   234,   230,  -186,  -186,  -186,  -186,
    -186,   -39,  -186,  -186,   242,  -180,  -186,  -186,  -186,  -114,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,   -45,
     -10,    61,  -186,   140,   154,  -186,   233,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,   134,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,   -75,  -186,  -186,   106,    32,  -131,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -185,  -186,    34,
    -186,   184,  -186,  -186,  -186,    63,  -110,   153,    10,  -186,
     178,  -186,  -145,   -26,    35,     3,     1,  -186,  -186
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,   255,   256,    29,   310,   311,   272,   273,   274,   382,
     383,   275,   276,   277,   278,   279,   280,   281,   282,   109,
     142,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   111,   112,   236,   172,
     173,   174,   175,   176,   177,   178,   179,   140,   221,   222,
     210,   148,   360,   372,   144,   145,   146,    81,    82,    83,
      96,   239,    97,    98,   213,    99,     6,    11,    12
  };

  const short int
  Parser::yytable_[] =
  {
      55,   116,   212,     5,     8,     8,    32,    30,     1,   100,
     101,   143,   103,   209,   243,     8,     8,     8,     8,    31,
     219,   220,   223,    13,    30,    87,   240,   102,   164,   254,
       8,    32,   104,   105,   106,   110,   117,   165,    47,   217,
     237,    33,   171,   138,   295,     2,     8,  -171,    86,    47,
       7,    47,     2,   139,  -171,   125,   126,   168,   119,     2,
     218,   245,    51,     2,   169,     9,     9,     8,    84,   252,
     169,   130,   131,   132,   133,     2,     9,     9,     9,     9,
     313,   306,   241,   250,   253,   141,   307,   287,   242,   324,
     326,     9,   251,   -84,   202,   338,   327,   339,   161,    85,
      32,   130,   131,   132,   133,   147,   212,     9,   149,   151,
     301,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,     9,   203,
     180,   152,   143,    -2,    14,   153,   154,    15,    16,    17,
      18,    19,    20,   156,   224,   157,   225,   226,   227,   228,
     214,   160,   230,   159,   337,    10,   233,   329,   330,   234,
     235,   180,   180,   180,   162,   166,   167,   336,   206,    88,
      89,    90,    91,    92,    15,    16,    17,    18,    19,    20,
       2,   180,   208,   207,   215,   216,   289,    95,    95,    95,
     133,    95,   244,   249,   305,   246,   247,   288,   113,   298,
     118,   -85,   -87,   299,   328,   343,     8,   363,   340,   364,
     346,   348,   349,   -84,   350,    32,   353,     2,   359,   258,
     361,   362,    39,    40,    41,   180,   369,   355,   180,   370,
     371,   378,   303,    45,   386,    46,   314,   315,   316,   373,
      47,    14,    48,   392,    15,    16,    17,    18,    19,    20,
     393,   180,    95,   394,   214,    93,   404,   321,   322,    32,
      94,    49,    50,    51,    52,    53,    54,     9,   342,   396,
     248,   231,   198,   300,   150,   302,   399,   155,   283,     0,
     331,   332,   333,   334,   335,     0,   304,     2,   125,   126,
     127,   199,     0,     0,   204,   341,     0,     0,   180,   180,
     211,     0,   128,   129,   130,   131,   132,   133,   180,     0,
     258,   143,     0,     0,   135,   136,   137,   357,   232,     0,
     283,   283,     0,     0,   238,     0,   283,   283,   125,   126,
     283,   283,     0,     0,     0,     0,     0,     0,   365,   366,
     367,     0,   128,   129,   130,   131,   132,   133,   180,     0,
     180,     0,     0,     0,     0,   136,   137,   284,     0,   384,
     385,     0,     0,     0,     0,     0,   389,   211,     0,   257,
       0,   285,   283,   384,   283,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   283,     0,   283,     0,   283,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   284,
     284,     0,     0,     0,   211,   284,   318,     0,     0,   284,
     284,   308,   283,   285,   285,    95,    95,    95,     0,   285,
     319,     0,     0,   285,   285,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   283,   283,     0,   283,   283,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     286,   284,   211,   284,   283,   283,     0,     0,   283,   271,
     257,   283,     0,     0,   284,   285,   284,   285,   284,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   285,     0,
     285,     0,   285,     0,     0,     0,     0,     0,     0,   121,
       0,   284,   286,   286,   125,   126,   127,     0,   286,   320,
       0,     0,   286,   286,     0,   285,     0,   317,   128,   129,
     130,   131,   132,   133,   284,   284,     0,   284,   284,     0,
     135,   136,   137,     0,     0,     0,     0,     0,   285,   285,
       0,   285,   285,   284,   284,     0,     0,   284,     0,     0,
     284,     0,     0,     0,   286,     0,   286,   285,   285,     0,
       0,   285,     0,   345,   285,   345,     0,   286,     0,   286,
       0,   286,     0,     0,     0,     0,   345,     0,   345,     0,
     358,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   121,   122,   123,   286,     0,   125,   126,   127,     0,
       0,     0,     0,   368,     0,     0,     0,     0,     0,     0,
     128,   129,   130,   131,   132,   133,     0,   286,   286,     0,
     286,   286,   135,   136,   137,     0,   387,   388,     0,   390,
     391,     0,     0,     0,     0,     0,   286,   286,     0,     0,
     286,     0,   309,   286,     0,   401,   402,     0,     0,   403,
       0,     0,   405,   259,     0,   260,     0,   261,   262,     8,
     263,   264,   265,     0,   266,   267,     0,     0,   268,     0,
       0,     0,     0,     0,     0,    39,    40,    41,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,    46,     0,
     269,     0,     0,    47,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     312,     0,   270,     0,    49,    50,    51,    52,    53,    54,
       9,   259,     0,   260,     0,   261,   262,     8,   263,   264,
     265,     0,   266,   267,     0,     0,   268,     0,     0,     0,
       0,     0,     0,    39,    40,    41,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,     0,   269,     0,
       0,    47,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   323,     0,
     270,     0,    49,    50,    51,    52,    53,    54,     9,   259,
       0,   260,     0,   261,   262,     8,   263,   264,   265,     0,
     266,   267,     0,     0,   268,     0,     0,     0,     0,     0,
       0,    39,    40,    41,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    46,     0,   269,     0,     0,    47,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   325,     0,   270,     0,
      49,    50,    51,    52,    53,    54,     9,   259,     0,   260,
       0,   261,   262,     8,   263,   264,   265,     0,   266,   267,
       0,     0,   268,     0,     0,     0,     0,     0,     0,    39,
      40,    41,     0,     0,     0,     0,     0,     0,     0,     0,
      45,     0,    46,     0,   269,     0,     0,    47,     0,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   379,
       0,     0,     0,     0,     0,     0,   270,     0,    49,    50,
      51,    52,    53,    54,     9,    34,     8,    35,    36,     0,
       0,     0,    37,     0,     0,     0,     0,   380,     0,    38,
       0,     0,    39,    40,    41,     0,     0,     0,     0,    42,
      43,    44,     0,    45,     0,    46,     0,     0,     0,     0,
      47,   381,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   107,     0,     0,     0,     0,     0,     0,     0,
       0,    49,    50,    51,    52,    53,    54,     9,    34,     8,
      35,    36,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,    38,     0,     0,    39,    40,    41,     0,     0,
       0,     0,    42,    43,    44,     0,    45,     0,    46,     0,
       0,     0,     0,    47,     0,    48,     0,     0,     0,   108,
       0,     0,     0,     0,     0,   114,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,    51,    52,    53,    54,
       9,    34,     8,    35,    36,     0,     0,     0,    37,     0,
       0,     0,     0,     0,     0,    38,     0,     0,    39,    40,
      41,     0,     0,     0,     0,    42,    43,    44,     0,    45,
       0,    46,   115,     0,     0,     0,    47,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   200,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50,    51,
      52,    53,    54,     9,    34,     8,    35,    36,     0,     0,
       0,    37,     0,     0,     0,     0,     0,     0,    38,     0,
       0,    39,    40,    41,     0,     0,     0,     0,    42,    43,
      44,     0,    45,   201,    46,     0,     0,     0,     0,    47,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,    51,    52,    53,    54,     9,   259,   344,   260,
       0,   261,   262,     8,   263,   264,   265,     0,   266,   267,
       0,     0,   268,     0,     0,     0,     0,     0,     0,    39,
      40,    41,     0,     0,     0,     0,     0,     0,     0,     0,
      45,     0,    46,     0,   269,     0,     0,    47,     0,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   270,     0,    49,    50,
      51,    52,    53,    54,     9,   259,     0,   260,   347,   261,
     262,     8,   263,   264,   265,     0,   266,   267,     0,     0,
     268,     0,     0,     0,     0,     0,     0,    39,    40,    41,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
      46,     0,   269,     0,     0,    47,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   270,     0,    49,    50,    51,    52,
      53,    54,     9,   259,     0,   260,     0,   261,   262,     8,
     263,   264,   265,     0,   266,   267,     0,     0,   268,     0,
       0,     0,     0,     0,     0,    39,    40,    41,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,    46,     0,
     269,   354,     0,    47,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   270,     0,    49,    50,    51,    52,    53,    54,
       9,   259,     0,   260,     0,   261,   262,     8,   263,   264,
     265,     0,   266,   267,     0,     0,   268,     0,     0,     0,
       0,     0,     0,    39,    40,    41,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,     0,   269,     0,
       0,    47,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     270,   356,    49,    50,    51,    52,    53,    54,     9,   259,
       0,   260,     0,   261,   262,     8,   263,   264,   265,     0,
     266,   267,     0,     0,   268,     0,     0,     0,     0,     0,
       0,    39,    40,    41,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    46,     0,   269,     0,     0,    47,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   270,     0,
      49,    50,    51,    52,    53,    54,     9,    34,     8,    35,
      36,     0,     0,     0,    37,     0,     0,     0,     0,   380,
       0,    38,     0,     0,    39,    40,    41,     0,     0,     0,
       0,    42,    43,    44,     0,    45,     0,    46,     0,     0,
     395,     0,    47,   381,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,    50,    51,    52,    53,    54,     9,
      34,     8,    35,    36,     0,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    38,     0,     0,    39,    40,    41,
       0,     0,     0,     0,    42,    43,    44,   290,    45,     0,
      46,     0,     0,     0,     0,    47,     0,    48,     0,     0,
       0,     0,   120,     0,     0,     0,   121,   122,   123,   124,
       0,   125,   126,   127,     0,     0,    49,    50,    51,    52,
      53,    54,     9,     0,     0,   128,   129,   130,   131,   132,
     133,   374,     0,     0,     0,   134,     0,   135,   136,   137,
       0,     0,     0,     0,     0,     0,   120,     0,     0,     0,
     121,   122,   123,   124,     0,   125,   126,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     129,   130,   131,   132,   133,   375,     0,     0,     0,   134,
       0,   135,   136,   137,     0,   376,   120,     0,     0,     0,
     121,   122,   123,   124,     0,   125,   126,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     129,   130,   131,   132,   133,   292,     0,     0,     0,   134,
       0,   135,   136,   137,     0,     0,   120,     0,     0,     0,
     121,   122,   123,   124,     0,   125,   126,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     129,   130,   131,   132,   133,   377,     0,     0,     0,   134,
       0,   135,   136,   137,     0,     0,   120,     0,     0,     0,
     121,   122,   123,   124,     0,   125,   126,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     129,   130,   131,   132,   133,   400,     0,     0,     0,   134,
       0,   135,   136,   137,     0,     0,   120,     0,     0,     0,
     121,   122,   123,   124,     0,   125,   126,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     129,   130,   131,   132,   133,     0,   158,     0,     0,   134,
       0,   135,   136,   137,   120,     0,     0,     0,   121,   122,
     123,   124,     0,   125,   126,   127,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,   129,   130,
     131,   132,   133,     0,   351,     0,     0,   134,     0,   135,
     136,   137,   120,     0,     0,     0,   121,   122,   123,   124,
       0,   125,   126,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,   129,   130,   131,   132,
     133,     0,     0,   293,     0,   134,     0,   135,   136,   137,
     120,     0,     0,     0,   121,   122,   123,   124,     0,   125,
     126,   127,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   128,   129,   130,   131,   132,   133,   352,
       0,     0,     0,   134,   120,   135,   136,   137,   121,   122,
     123,   124,     0,   125,   126,   127,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,   129,   130,
     131,   132,   133,     0,     0,   291,     0,   134,   120,   135,
     136,   137,   121,   122,   123,   124,     0,   125,   126,   127,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   128,   129,   130,   131,   132,   133,     0,     0,     0,
       0,   134,     0,   135,   136,   137,   294,   120,     0,     0,
       0,   121,   122,   123,   124,     0,   125,   126,   127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     128,   129,   130,   131,   132,   133,     0,     0,     0,     0,
     134,   120,   135,   136,   137,   121,   122,   123,   124,     0,
     125,   126,   127,     0,   163,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,   120,   135,   136,   137,   121,
     122,   123,   124,     0,   125,   126,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   128,   129,
     130,   131,   132,   133,     0,   170,     0,     0,   134,   120,
     135,   136,   137,   121,   122,   123,   124,     0,   125,   126,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   128,   129,   130,   131,   132,   133,     0,     0,
       0,   205,   134,   120,   135,   136,   137,   121,   122,   123,
     124,     0,   125,   126,   127,     0,   229,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   128,   129,   130,   131,
     132,   133,     0,     0,     0,     0,   134,   120,   135,   136,
     137,   121,   122,   123,   124,     0,   125,   126,   127,     0,
     296,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     128,   129,   130,   131,   132,   133,     0,     0,     0,     0,
     134,   120,   135,   136,   137,   121,   122,   123,   124,     0,
     125,   126,   127,     0,     0,     0,   297,     0,     0,     0,
       0,     0,     0,     0,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,   120,   135,   136,   137,   121,
     122,   123,   124,     0,   125,   126,   127,     0,     0,     0,
       0,     0,     0,   397,     0,     0,     0,     0,   128,   129,
     130,   131,   132,   133,     0,     0,     0,     0,   134,   120,
     135,   136,   137,   121,   122,   123,   124,     0,   125,   126,
     127,     0,     0,     0,     0,     0,   398,     0,     0,     0,
       0,     0,   128,   129,   130,   131,   132,   133,     0,     0,
       0,     0,   134,   120,   135,   136,   137,   121,   122,   123,
     124,     0,   125,   126,   127,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   128,   129,   130,   131,
     132,   133,     0,     0,     0,     0,   134,     0,   135,   136,
     137,   121,     0,   123,     0,     0,   125,   126,   127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     128,   129,   130,   131,   132,   133,     0,     0,     0,     0,
       0,     0,   135,   136,   137
  };

  const short int
  Parser::yycheck_[] =
  {
      10,    46,   147,     0,    18,    18,     5,     4,     3,    35,
      36,    86,    38,     1,   199,    18,    18,    18,    18,     3,
     151,   152,   153,     0,    21,    15,   171,    37,    46,     1,
      18,    30,    42,    43,    44,    45,    46,    55,    52,    44,
     171,    48,    45,    64,   229,    47,    18,    58,    49,    52,
       1,    52,    47,    45,    65,    42,    43,    48,    48,    47,
      65,    46,    75,    47,    55,    79,    79,    18,    48,   214,
      55,    58,    59,    60,    61,    47,    79,    79,    79,    79,
     260,    50,    56,    46,   215,    52,    55,   218,    62,   269,
     270,    79,    55,    64,   139,    55,    67,    57,   108,    48,
      99,    58,    59,    60,    61,    45,   251,    79,    44,    44,
     241,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,    79,   139,
     120,    51,   207,     0,     1,    51,    44,     4,     5,     6,
       7,     8,     9,    18,   154,    18,   156,   157,   158,   159,
     147,    46,   162,    18,   299,     2,   166,   288,   289,   169,
     170,   151,   152,   153,    55,    51,    48,   298,    65,    16,
      17,    18,    19,    20,     4,     5,     6,     7,     8,     9,
      47,   171,    50,    55,    65,    49,    65,    34,    35,    36,
      61,    38,    46,    46,    44,   205,   206,    58,    45,    55,
      47,    64,    64,    55,    44,    13,    18,   338,    65,   340,
      15,    44,    18,    64,    18,   214,    50,    47,    11,   216,
      46,    46,    34,    35,    36,   215,    49,    72,   218,    49,
      10,    26,   242,    45,    49,    47,   262,   263,   264,    57,
      52,     1,    54,    50,     4,     5,     6,     7,     8,     9,
      51,   241,    99,    51,   251,    21,    50,   267,   268,   258,
      30,    73,    74,    75,    76,    77,    78,    79,   307,   383,
     207,   165,   138,   241,    90,   241,   386,    99,   217,    -1,
     290,   291,   292,   293,   294,    -1,   251,    47,    42,    43,
      44,   138,    -1,    -1,   141,   305,    -1,    -1,   288,   289,
     147,    -1,    56,    57,    58,    59,    60,    61,   298,    -1,
     307,   386,    -1,    -1,    68,    69,    70,   327,   165,    -1,
     259,   260,    -1,    -1,   171,    -1,   265,   266,    42,    43,
     269,   270,    -1,    -1,    -1,    -1,    -1,    -1,   348,   349,
     350,    -1,    56,    57,    58,    59,    60,    61,   338,    -1,
     340,    -1,    -1,    -1,    -1,    69,    70,   217,    -1,   369,
     370,    -1,    -1,    -1,    -1,    -1,   376,   214,    -1,   216,
      -1,   217,   311,   383,   313,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   324,    -1,   326,    -1,   328,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   259,
     260,    -1,    -1,    -1,   251,   265,   266,    -1,    -1,   269,
     270,   258,   351,   259,   260,   262,   263,   264,    -1,   265,
     266,    -1,    -1,   269,   270,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   374,   375,    -1,   377,   378,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     217,   311,   299,   313,   393,   394,    -1,    -1,   397,   217,
     307,   400,    -1,    -1,   324,   311,   326,   313,   328,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   324,    -1,
     326,    -1,   328,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      -1,   351,   259,   260,    42,    43,    44,    -1,   265,   266,
      -1,    -1,   269,   270,    -1,   351,    -1,   265,    56,    57,
      58,    59,    60,    61,   374,   375,    -1,   377,   378,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,   374,   375,
      -1,   377,   378,   393,   394,    -1,    -1,   397,    -1,    -1,
     400,    -1,    -1,    -1,   311,    -1,   313,   393,   394,    -1,
      -1,   397,    -1,   311,   400,   313,    -1,   324,    -1,   326,
      -1,   328,    -1,    -1,    -1,    -1,   324,    -1,   326,    -1,
     328,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,   351,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,   351,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,   374,   375,    -1,
     377,   378,    68,    69,    70,    -1,   374,   375,    -1,   377,
     378,    -1,    -1,    -1,    -1,    -1,   393,   394,    -1,    -1,
     397,    -1,     1,   400,    -1,   393,   394,    -1,    -1,   397,
      -1,    -1,   400,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,
      49,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    71,    -1,    73,    74,    75,    76,    77,    78,
      79,    12,    -1,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    24,    -1,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    47,    -1,    49,    -1,
      -1,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      71,    -1,    73,    74,    75,    76,    77,    78,    79,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      23,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,    52,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    -1,    49,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    73,    74,
      75,    76,    77,    78,    79,    17,    18,    19,    20,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,    41,
      42,    43,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    78,    79,    17,    18,
      19,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    34,    35,    36,    -1,    -1,
      -1,    -1,    41,    42,    43,    -1,    45,    -1,    47,    -1,
      -1,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,    78,
      79,    17,    18,    19,    20,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    45,
      -1,    47,    48,    -1,    -1,    -1,    52,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
      76,    77,    78,    79,    17,    18,    19,    20,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,
      43,    -1,    45,    46,    47,    -1,    -1,    -1,    -1,    52,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    75,    76,    77,    78,    79,    12,    13,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    -1,    49,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    73,    74,
      75,    76,    77,    78,    79,    12,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    23,    24,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      47,    -1,    49,    -1,    -1,    52,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    -1,    73,    74,    75,    76,
      77,    78,    79,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,
      49,    50,    -1,    52,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    73,    74,    75,    76,    77,    78,
      79,    12,    -1,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    24,    -1,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    47,    -1,    49,    -1,
      -1,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      23,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,    52,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    17,    18,    19,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      -1,    31,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    41,    42,    43,    -1,    45,    -1,    47,    -1,    -1,
      50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      17,    18,    19,    20,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    41,    42,    43,    18,    45,    -1,
      47,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    -1,    37,    38,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    73,    74,    75,    76,
      77,    78,    79,    -1,    -1,    56,    57,    58,    59,    60,
      61,    18,    -1,    -1,    -1,    66,    -1,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,
      37,    38,    39,    40,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    22,    -1,    -1,    -1,    66,
      -1,    68,    69,    70,    -1,    32,    33,    -1,    -1,    -1,
      37,    38,    39,    40,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    22,    -1,    -1,    -1,    66,
      -1,    68,    69,    70,    -1,    -1,    33,    -1,    -1,    -1,
      37,    38,    39,    40,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    22,    -1,    -1,    -1,    66,
      -1,    68,    69,    70,    -1,    -1,    33,    -1,    -1,    -1,
      37,    38,    39,    40,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    22,    -1,    -1,    -1,    66,
      -1,    68,    69,    70,    -1,    -1,    33,    -1,    -1,    -1,
      37,    38,    39,    40,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    -1,    25,    -1,    -1,    66,
      -1,    68,    69,    70,    33,    -1,    -1,    -1,    37,    38,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    -1,    25,    -1,    -1,    66,    -1,    68,
      69,    70,    33,    -1,    -1,    -1,    37,    38,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      61,    -1,    -1,    26,    -1,    66,    -1,    68,    69,    70,
      33,    -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    28,
      -1,    -1,    -1,    66,    33,    68,    69,    70,    37,    38,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    -1,    -1,    30,    -1,    66,    33,    68,
      69,    70,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    66,    -1,    68,    69,    70,    32,    33,    -1,    -1,
      -1,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      66,    33,    68,    69,    70,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    33,    68,    69,    70,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    -1,    63,    -1,    -1,    66,    33,
      68,    69,    70,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    65,    66,    33,    68,    69,    70,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    66,    33,    68,    69,
      70,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      66,    33,    68,    69,    70,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    33,    68,    69,    70,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    66,    33,
      68,    69,    70,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    33,    68,    69,    70,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    37,    -1,    39,    -1,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    47,    85,    86,   169,   170,     1,    18,    79,
     161,   171,   172,     0,     1,     4,     5,     6,     7,     8,
       9,    87,    88,    89,    90,    91,    92,    93,    94,    97,
     169,     3,   170,    48,    17,    19,    20,    24,    31,    34,
      35,    36,    41,    42,    43,    45,    47,    52,    54,    73,
      74,    75,    76,    77,    78,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   161,   162,   163,    48,    48,    49,   162,   161,   161,
     161,   161,   161,    88,    89,   161,   164,   166,   167,   169,
     167,   167,   114,   167,   114,   114,   114,     1,    58,   113,
     114,   140,   141,   161,     1,    48,   113,   114,   161,   162,
      33,    37,    38,    39,    40,    42,    43,    44,    56,    57,
      58,    59,    60,    61,    66,    68,    69,    70,    64,    45,
     151,    52,   114,   138,   158,   159,   160,    45,   155,    44,
     155,    44,    51,    51,    44,   164,    18,    18,    25,    18,
      46,   114,    55,    46,    46,    55,    51,    48,    48,    55,
      63,    45,   143,   144,   145,   146,   147,   148,   149,   150,
     162,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   130,   161,
       1,    46,   113,   114,   161,    65,    65,    55,    50,     1,
     154,   161,   166,   168,   169,    65,    49,    44,    65,   143,
     143,   152,   153,   143,   114,   114,   114,   114,   114,    46,
     114,   141,   161,   114,   114,   114,   142,   143,   161,   165,
     166,    56,    62,   151,    46,    46,   114,   114,   159,    46,
      46,    55,   166,   143,     1,    95,    96,   161,   169,    12,
      14,    16,    17,    19,    20,    21,    23,    24,    27,    49,
      71,    98,   100,   101,   102,   105,   106,   107,   108,   109,
     110,   111,   112,   115,   117,   118,   120,   143,    58,    65,
      18,    30,    22,    26,    32,   151,    46,    48,    55,    55,
     142,   143,   153,   114,   168,    44,    50,    55,   161,     1,
      98,    99,     1,    99,   167,   167,   167,    98,   117,   118,
     120,   114,   114,     1,    99,     1,    99,    67,    44,   143,
     143,   114,   114,   114,   114,   114,   143,   166,    55,    57,
      65,   114,    95,    13,    13,    98,    15,    15,    44,    18,
      18,    25,    28,    50,    50,    72,    72,   114,    98,    11,
     156,    46,    46,   143,   143,   114,   114,   114,    98,    49,
      49,    10,   157,    57,    18,    22,    32,    22,    26,     1,
      29,    53,   103,   104,   114,   114,    49,    98,    98,   114,
      98,    98,    50,    51,    51,    50,   103,    51,    50,   160,
      22,    98,    98,    98,    50,    98
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    84,    85,    86,    86,    87,    87,    88,    88,    88,
      89,    89,    89,    89,    89,    90,    91,    92,    92,    93,
      93,    94,    94,    95,    95,    95,    96,    96,    97,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      99,    99,   100,   101,   101,   102,   102,   103,   103,   103,
     104,   104,   105,   106,   106,   107,   108,   109,   109,   109,
     109,   110,   110,   110,   110,   111,   112,   112,   112,   112,
     112,   112,   113,   113,   114,   114,   114,   114,   114,   114,
     114,   114,   115,   115,   115,   115,   115,   115,   115,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   117,
     117,   118,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   129,   129,   130,   131,   132,   133,
     133,   134,   135,   136,   136,   136,   137,   138,   139,   140,
     140,   141,   142,   142,   143,   143,   143,   143,   143,   144,
     145,   145,   146,   147,   148,   149,   150,   151,   151,   151,
     152,   152,   153,   153,   154,   154,   155,   155,   155,   156,
     156,   157,   157,   158,   158,   159,   159,   159,   160,   160,
     161,   161,   162,   162,   163,   163,   164,   164,   165,   165,
     166,   167,   167,   168,   168,   169,   169,   170,   170,   170,
     171,   172
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
       3,     3,     3,     3,     3,     3,     2,     1,     2,     1,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       2,     3,     4,     3,     5,     3,     6,     6,     6,     6,
       6,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     3,     5,     5,     3,     3,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     5,     4,     6,     3,     3,     3,     2,
       3,     1,     1,     0,     3,     1,     3,     3,     0,     4,
       0,     4,     0,     3,     1,     1,     3,     3,     1,     0,
       1,     1,     1,     2,     3,     1,     1,     1,     3,     1,
       3,     2,     1,     2,     1,     2,     1,     3,     3,     3,
       1,     2
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
  "\"choose\"", "\"iterate\"", "\"do\"", "\"call\"", "\"if\"", "\"then\"",
  "\"else\"", "\"case\"", "\"of\"", "\"default\"", "\"holds\"",
  "\"exists\"", "\"with\"", "\"as\"", "\"undef\"", "\"false\"", "\"true\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"implies\"", "\"not\"", "\"+\"",
  "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\":\"", "\"::\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"",
  "\"/\"", "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"",
  "\"=>\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"",
  "\"binary\"", "\"hexadecimal\"", "\"integer\"", "\"rational\"",
  "\"decimal\"", "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "UPLUS",
  "UMINUS", "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header",
  "Definitions", "AttributedDefinition", "Definition",
  "EnumerationDefinition", "DerivedDefinition", "RuleDefinition",
  "FunctionDefinition", "ProgramFunctionDefinition",
  "EnumeratorDefinition", "Enumerators", "UsingDefinition", "Rule",
  "Rules", "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel",
  "CaseLabels", "LetRule", "ForallRule", "ChooseRule", "IterateRule",
  "BlockRule", "SequenceRule", "UpdateRule", "CallRule", "Terms", "Term",
  "SimpleOrClaspedTerm", "OperatorExpression", "DirectCallExpression",
  "MethodCallExpression", "LiteralCallExpression",
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
       0,   394,   394,   403,   409,   417,   423,   433,   439,   443,
     451,   455,   459,   463,   467,   475,   483,   491,   496,   505,
     521,   529,   552,   570,   574,   580,   588,   594,   604,   616,
     620,   624,   628,   632,   636,   640,   644,   648,   652,   656,
     664,   670,   680,   688,   692,   700,   704,   712,   716,   720,
     728,   734,   744,   752,   756,   764,   772,   780,   784,   788,
     793,   802,   806,   810,   815,   824,   834,   838,   842,   846,
     850,   854,   866,   872,   882,   886,   890,   894,   898,   902,
     906,   910,   918,   922,   926,   930,   934,   938,   942,   954,
     958,   962,   966,   970,   974,   978,   982,   986,   990,   994,
     998,  1002,  1006,  1010,  1014,  1018,  1022,  1026,  1030,  1038,
    1043,  1051,  1056,  1064,  1072,  1080,  1088,  1096,  1104,  1112,
    1120,  1132,  1136,  1140,  1144,  1148,  1152,  1156,  1160,  1164,
    1168,  1172,  1176,  1184,  1192,  1197,  1206,  1222,  1238,  1254,
    1266,  1282,  1298,  1306,  1311,  1315,  1323,  1330,  1338,  1345,
    1351,  1360,  1372,  1378,  1388,  1392,  1396,  1400,  1404,  1412,
    1420,  1424,  1431,  1441,  1461,  1469,  1477,  1489,  1493,  1497,
    1511,  1517,  1527,  1531,  1539,  1545,  1555,  1559,  1563,  1575,
    1579,  1587,  1591,  1599,  1605,  1615,  1623,  1633,  1644,  1648,
    1660,  1664,  1672,  1676,  1686,  1692,  1706,  1710,  1719,  1725,
    1735,  1743,  1749,  1757,  1763,  1774,  1780,  1790,  1794,  1798,
    1806,  1814
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
#line 4431 "GrammarParser.cpp" // lalr1.cc:1167
#line 1820 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
