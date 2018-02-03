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
#line 393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1476 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 402 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1494 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 432 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1524 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1540 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1548 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 454 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1556 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 462 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< UsingDefinition::Ptr > ();
  }
#line 1580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 474 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 482 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 490 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< VariableDefinitions::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1605 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 495 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1614 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 504 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 520 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 528 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 551 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 579 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 593 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 603 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 619 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1757 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 623 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 627 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 631 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 635 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 639 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 643 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 647 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 655 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 663 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 679 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 687 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 699 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 703 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1889 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 715 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1923 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 733 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 751 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 755 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 763 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 771 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1973 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 779 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1981 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 783 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1989 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 787 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1998 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 792 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2032 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 814 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 823 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2051 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 833 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 2059 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 837 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 2067 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 841 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< MethodCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 2075 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 845 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< MethodCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 2083 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 849 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 2091 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 853 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 2099 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 865 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2109 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 871 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 881 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 885 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 889 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 893 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 897 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 901 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 905 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 909 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 917 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 921 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2199 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 925 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LiteralCallExpression::Ptr > ();
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 937 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Literal::Ptr > ();
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 961 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 965 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 969 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 973 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 997 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1001 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2343 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1005 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1009 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1013 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1017 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1021 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1037 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1042 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1050 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1055 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1063 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< ValueLiteral::Ptr > () );
  }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1071 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1079 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1087 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1103 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1111 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1119 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1131 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< UndefLiteral::Ptr > ();
  }
#line 2505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1135 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1139 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1147 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1159 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ReferenceLiteral::Ptr > ();
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1163 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ListLiteral::Ptr > ();
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1167 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RangeLiteral::Ptr > ();
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< TupleLiteral::Ptr > ();
  }
#line 2585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1175 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RecordLiteral::Ptr > ();
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1191 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2610 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1205 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1221 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1237 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1253 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1265 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1281 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1297 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1305 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
  }
#line 2732 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1310 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1314 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = nullptr;
  }
#line 2748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1322 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1329 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
  }
#line 2766 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1337 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as< NamedExpressions::Ptr > () );
  }
#line 2774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1344 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = yystack_[2].value.as< NamedExpressions::Ptr > ();
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2784 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1359 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2802 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1377 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2822 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1387 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2838 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1395 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< TemplateType::Ptr > ();
  }
#line 2846 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2854 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1403 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2862 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1411 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2870 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1419 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2878 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1423 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Tuple" );
      auto subTypes = yystack_[3].value.as< Types::Ptr > ();
      subTypes->add( yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes );
  }
#line 2897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1468 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1488 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1492 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1496 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2966 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1510 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1516 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2986 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1526 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2994 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1530 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1538 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3012 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1544 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3022 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1554 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = yystack_[1].value.as< VariableDefinitions::Ptr > ();
  }
#line 3030 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = nullptr;
  }
#line 3038 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1562 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 3046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 3054 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 3062 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1586 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[1].value.as< UpdateRules::Ptr > ();
  }
#line 3070 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1590 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1598 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< UpdateRules::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1604 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3098 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1614 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< TupleLiteral::Ptr > ()->expressions() );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1643 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[0].value.as< UpdateRules::Ptr > ();
  }
#line 3143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1647 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1659 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 3159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1663 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 3167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 3175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1675 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 3185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1685 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 3195 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 3205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3213 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1709 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 3222 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3232 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1724 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3250 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1742 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3260 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3278 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1762 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3286 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1773 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[1].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1779 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1789 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< BasicAttribute::Ptr > ();
  }
#line 3314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1793 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3322 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 1797 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = nullptr;
  }
#line 3330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 1805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 1813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -174;

  const short int Parser::yytable_ninf_ = -172;

  const short int
  Parser::yypact_[] =
  {
      15,  -174,     6,    31,   132,    40,  -174,   -46,  -174,  -174,
    1428,    16,    49,  -174,  -174,    -4,   -14,   -14,   -14,   -14,
     -14,   198,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
      84,  -174,  -174,  -174,    -3,    -3,    -3,  1428,    -3,  -174,
    -174,  -174,  1428,  1428,  1428,   836,   899,   -14,     7,  -174,
    -174,  -174,  -174,  -174,  -174,  2169,   -17,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,    34,    51,  -174,  -174,  1428,  -174,    38,    57,
      38,    99,    94,  -174,  -174,   110,  -174,  -174,   118,    -3,
     145,   149,  1687,   150,  -174,  -174,  -174,   123,  1428,   119,
    1897,    12,  -174,   124,   160,  -174,    47,  1931,  -174,  -174,
    1428,  1428,  1428,  1428,  1428,  1428,  1428,  1428,  1428,  1428,
    1428,  1428,  1428,  1428,  1428,  1428,  1428,     5,    -1,   962,
    -174,   -14,  1965,   115,   129,  -174,   135,     2,   151,   148,
     -35,     5,     5,     5,  1428,  -174,  1428,  1428,  1428,  1428,
    -174,  1999,  1428,  -174,  -174,   -14,  1428,  -174,  -174,  1428,
    1428,   288,   377,   414,  2203,   133,   133,   709,   183,   183,
     156,   156,   156,  -174,  2203,   709,   183,   183,     5,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,     4,  -174,    34,
     173,  -174,    53,  2169,  -174,  1428,  1428,  1428,  -174,   174,
      96,   110,  -174,  -174,    -3,     5,    21,  1302,     5,  -174,
    -174,   163,   157,  -174,  1454,  1828,  1570,  1760,  1863,    34,
    2033,  -174,   124,  2169,  2169,  2067,   175,  -174,   110,   178,
    -174,     5,  1428,  -174,  -174,  -174,  2169,  2169,  -174,  -174,
    -174,    -3,  -174,   190,  -174,  -174,   103,  -174,    -3,   505,
     574,  -174,    -3,    -3,    -3,  1302,   136,  1428,  1428,   642,
     710,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,   171,   122,   172,   176,   202,     5,     5,
    1428,  1428,  1428,  1428,  1428,  -174,  -174,  -174,     5,   -14,
     -36,    70,   185,  -174,  -174,  1428,  -174,    21,  -174,   235,
    -174,  1030,   237,  1098,   209,   244,   245,  -174,   191,   172,
     176,  1724,  1794,   206,  1166,   192,  1234,  1428,  1302,  -174,
     254,  2169,  2169,  2169,  2169,  2169,   222,   223,     5,  -174,
       5,  2169,  -174,  -174,  -174,  -174,  -174,  -174,  1428,  1428,
    1428,  1302,   224,  -174,  -174,  -174,  -174,  2169,  -174,   225,
     262,  -174,  -174,  -174,   218,  1490,  1530,  1610,   250,   773,
    1428,   228,  -174,  -174,  1302,  1302,  1428,  1302,  1302,   229,
     227,   234,  -174,  1365,  2101,  2135,  1428,  -174,  -174,  1650,
    -174,  -174,  -174,  1302,  1302,  -174,  -174,  1302,  -174,   239,
    1302,  -174,  -174,  -174,  -174,  -174
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
       0,   105,   103,   104,   107,    91,    92,    98,    99,   100,
      93,    94,    95,    96,   106,    97,   101,   102,     0,   115,
     154,   155,   160,   161,   156,   157,   158,   159,   113,   111,
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
    -174,  -174,  -174,  -174,   266,   258,  -174,  -174,  -174,  -174,
    -174,   -15,  -174,  -174,   116,  -164,  -174,  -174,  -174,   -93,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,   -45,
     -10,     1,  -174,   102,   137,  -174,   238,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,   158,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,   -80,  -174,  -174,   138,    59,  -111,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -173,  -174,    63,
    -174,   204,  -174,  -174,  -174,    98,   -79,    35,    13,  -174,
     210,  -174,  -142,   -25,    62,     8,    33,  -174,  -174
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,   255,   256,    29,   310,   311,   272,   273,   274,   382,
     383,   275,   276,   277,   278,   279,   280,   281,   282,   109,
     142,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   111,   112,   236,   189,
     190,   191,   192,   193,   194,   195,   196,   140,   221,   222,
     210,   148,   360,   372,   144,   145,   146,    81,    82,    83,
      96,   239,    97,    98,   213,    99,     6,    11,    12
  };

  const short int
  Parser::yytable_[] =
  {
      55,   116,    33,   209,     8,   212,   143,     7,     5,   217,
     100,   101,    30,   103,     8,     8,   137,     8,     1,   338,
       8,   339,   254,     8,     8,     8,   243,   102,    87,    30,
     218,    13,   104,   105,   106,   110,   117,    10,    32,     8,
     219,   220,   223,    31,     2,    86,   240,   138,    47,     2,
     188,    88,    89,    90,    91,    92,   295,    47,   164,    47,
     241,   119,     2,    32,    84,     9,   242,   165,     2,    95,
      95,    95,   252,    95,    51,     9,     9,   237,     9,   139,
     113,     9,   118,   147,     9,     9,     9,     2,    15,    16,
      17,    18,    19,    20,   202,   168,   313,    85,   161,   245,
       9,   149,   169,   141,   253,   324,   326,   287,   169,   212,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   143,  -171,   203,
     301,     2,    32,    14,    95,  -171,    15,    16,    17,    18,
      19,    20,   250,   151,   224,   152,   225,   226,   227,   228,
     197,   251,   230,   306,     8,   214,   233,   337,   307,   234,
     235,   153,   154,   156,   197,   197,   197,   157,   159,   160,
      39,    40,    41,   199,   162,   166,   204,   329,   330,     2,
     206,    45,   211,    46,   207,   208,   -84,   336,    47,   327,
      48,   129,   130,   131,   132,   246,   247,   216,    -2,    14,
     232,   197,    15,    16,    17,    18,    19,    20,   167,    49,
      50,    51,    52,    53,    54,     9,   215,   132,   283,   244,
     249,   288,   289,   238,   258,   124,   125,   363,   197,   364,
     298,   197,   303,   299,   305,   138,   -85,   314,   315,   316,
     -87,   129,   130,   131,   132,     2,   328,    32,   343,   211,
     340,   257,   346,   348,   197,   -84,   353,   321,   322,   214,
     283,   283,   349,   350,   355,   359,   283,   283,   361,   362,
     283,   283,   371,   369,   370,   373,   378,   386,   393,   392,
     331,   332,   333,   334,   335,   394,   211,    93,    94,   404,
     396,    32,   342,   308,   150,   341,   198,    95,    95,    95,
     300,   197,   197,   231,   302,   248,   143,   399,     0,   155,
       0,   197,   283,   304,   283,   258,     0,   357,     0,   284,
       0,     0,     0,     0,     0,   283,     0,   283,     0,   283,
     124,   125,   126,   271,   211,     0,     0,     0,   365,   366,
     367,     0,   257,     0,   127,   128,   129,   130,   131,   132,
       0,   197,   283,   197,   285,     0,   134,   135,   136,   384,
     385,   284,   284,     0,     0,     0,   389,   284,   318,     0,
       0,   284,   284,   384,     0,   283,   283,     0,   283,   283,
       0,   317,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   283,   283,   285,   285,   283,     0,
       0,   283,   285,   319,     0,     0,   285,   285,     0,     0,
       0,     0,     0,   284,   120,   284,   122,     0,     0,   124,
     125,   126,     0,     0,     0,     0,   284,   345,   284,   345,
     284,     0,     0,   127,   128,   129,   130,   131,   132,     0,
     345,     0,   345,     0,   358,   134,   135,   136,   285,     0,
     285,   120,     0,   284,     0,   286,   124,   125,   126,     0,
       0,   285,     0,   285,     0,   285,     0,   368,     0,     0,
     127,   128,   129,   130,   131,   132,   284,   284,     0,   284,
     284,     0,   134,   135,   136,     0,     0,     0,   285,     0,
     387,   388,     0,   390,   391,   284,   284,   286,   286,   284,
       0,     0,   284,   286,   320,     0,   309,   286,   286,   401,
     402,   285,   285,   403,   285,   285,   405,   259,     0,   260,
       0,   261,   262,     8,   263,   264,   265,     0,   266,   267,
     285,   285,   268,     0,   285,     0,     0,   285,     0,    39,
      40,    41,     0,     0,     0,     0,     0,     0,     0,   286,
      45,   286,    46,     0,   269,     0,     0,    47,     0,    48,
       0,     0,   286,     0,   286,     0,   286,     0,     0,     0,
       0,     0,     0,     0,     0,   312,   270,     0,    49,    50,
      51,    52,    53,    54,     9,     0,   259,     0,   260,   286,
     261,   262,     8,   263,   264,   265,     0,   266,   267,     0,
       0,   268,     0,     0,     0,     0,     0,     0,    39,    40,
      41,     0,   286,   286,     0,   286,   286,     0,     0,    45,
       0,    46,     0,   269,     0,     0,    47,     0,    48,     0,
       0,   286,   286,     0,     0,   286,     0,     0,   286,     0,
       0,     0,     0,   323,     0,   270,     0,    49,    50,    51,
      52,    53,    54,     9,   259,     0,   260,     0,   261,   262,
       8,   263,   264,   265,     0,   266,   267,     0,     0,   268,
       0,     0,     0,     0,     0,     0,    39,    40,    41,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    46,
       0,   269,     0,     0,    47,     0,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   325,     0,   270,     0,    49,    50,    51,    52,    53,
      54,     9,   259,     0,   260,     0,   261,   262,     8,   263,
     264,   265,     0,   266,   267,     0,     0,   268,     0,     0,
       0,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,   124,   125,     0,     0,    45,     0,    46,     0,   269,
       0,     0,    47,     0,    48,   127,   128,   129,   130,   131,
     132,     0,     0,     0,   379,     0,     0,     0,   135,   136,
       0,   270,     0,    49,    50,    51,    52,    53,    54,     9,
      34,     8,    35,    36,     0,     0,     0,    37,     0,     0,
       0,     0,   380,     0,    38,     0,     0,    39,    40,    41,
       0,     0,     0,     0,    42,    43,    44,     0,    45,     0,
      46,     0,     0,     0,     0,    47,   381,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   107,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
      53,    54,     9,    34,     8,    35,    36,     0,     0,     0,
      37,     0,     0,     0,     0,     0,     0,    38,     0,     0,
      39,    40,    41,     0,     0,     0,     0,    42,    43,    44,
       0,    45,     0,    46,     0,     0,     0,     0,    47,     0,
      48,     0,     0,     0,   108,     0,     0,     0,     0,     0,
     114,     0,     0,     0,     0,     0,     0,     0,     0,    49,
      50,    51,    52,    53,    54,     9,    34,     8,    35,    36,
       0,     0,     0,    37,     0,     0,     0,     0,     0,     0,
      38,     0,     0,    39,    40,    41,     0,     0,     0,     0,
      42,    43,    44,     0,    45,     0,    46,   115,     0,     0,
       0,    47,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   200,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,    53,    54,     9,    34,
       8,    35,    36,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,    38,     0,     0,    39,    40,    41,     0,
       0,     0,     0,    42,    43,    44,     0,    45,   201,    46,
       0,     0,     0,     0,    47,     0,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,    51,    52,    53,
      54,     9,   259,   344,   260,     0,   261,   262,     8,   263,
     264,   265,     0,   266,   267,     0,     0,   268,     0,     0,
       0,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,    46,     0,   269,
       0,     0,    47,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   270,     0,    49,    50,    51,    52,    53,    54,     9,
     259,     0,   260,   347,   261,   262,     8,   263,   264,   265,
       0,   266,   267,     0,     0,   268,     0,     0,     0,     0,
       0,     0,    39,    40,    41,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,    46,     0,   269,     0,     0,
      47,     0,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   270,
       0,    49,    50,    51,    52,    53,    54,     9,   259,     0,
     260,     0,   261,   262,     8,   263,   264,   265,     0,   266,
     267,     0,     0,   268,     0,     0,     0,     0,     0,     0,
      39,    40,    41,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,     0,   269,   354,     0,    47,     0,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   270,     0,    49,
      50,    51,    52,    53,    54,     9,   259,     0,   260,     0,
     261,   262,     8,   263,   264,   265,     0,   266,   267,     0,
       0,   268,     0,     0,     0,     0,     0,     0,    39,    40,
      41,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       0,    46,     0,   269,     0,     0,    47,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   270,   356,    49,    50,    51,
      52,    53,    54,     9,   259,     0,   260,     0,   261,   262,
       8,   263,   264,   265,     0,   266,   267,     0,     0,   268,
       0,     0,     0,     0,     0,     0,    39,    40,    41,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    46,
       0,   269,     0,     0,    47,     0,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   270,     0,    49,    50,    51,    52,    53,
      54,     9,    34,     8,    35,    36,     0,     0,     0,    37,
       0,     0,     0,     0,   380,     0,    38,     0,     0,    39,
      40,    41,     0,     0,     0,     0,    42,    43,    44,     0,
      45,     0,    46,     0,     0,   395,     0,    47,   381,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
      51,    52,    53,    54,     9,    34,     8,    35,    36,     0,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    38,
       0,     0,    39,    40,    41,     0,     0,     0,     0,    42,
      43,    44,   290,    45,     0,    46,     0,     0,     0,     0,
      47,     0,    48,     0,     0,     0,     0,     0,     0,     0,
       0,   120,   121,   122,   123,     0,   124,   125,   126,     0,
       0,    49,    50,    51,    52,    53,    54,     9,   374,     0,
     127,   128,   129,   130,   131,   132,     0,     0,     0,     0,
     133,     0,   134,   135,   136,     0,     0,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,   375,     0,     0,     0,   133,     0,   134,   135,
     136,     0,   376,     0,     0,     0,     0,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,   292,     0,     0,     0,   133,     0,   134,   135,
     136,     0,     0,     0,     0,     0,     0,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,   377,     0,     0,     0,   133,     0,   134,   135,
     136,     0,     0,     0,     0,     0,     0,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,   400,     0,     0,     0,   133,     0,   134,   135,
     136,     0,     0,     0,     0,     0,     0,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,   158,     0,     0,     0,   133,     0,   134,   135,
     136,     0,     0,     0,   120,   121,   122,   123,     0,   124,
     125,   126,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   351,
       0,     0,     0,   133,     0,   134,   135,   136,     0,     0,
       0,   120,   121,   122,   123,     0,   124,   125,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,   293,     0,     0,     0,
     133,     0,   134,   135,   136,     0,     0,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,   352,     0,     0,     0,   133,     0,   134,   135,
     136,   120,   121,   122,   123,     0,   124,   125,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,     0,     0,   291,     0,
     133,     0,   134,   135,   136,   120,   121,   122,   123,     0,
     124,   125,   126,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   127,   128,   129,   130,   131,   132,
       0,     0,     0,     0,   133,   294,   134,   135,   136,     0,
     120,   121,   122,   123,     0,   124,   125,   126,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,   129,   130,   131,   132,     0,     0,     0,     0,   133,
       0,   134,   135,   136,   120,   121,   122,   123,     0,   124,
     125,   126,     0,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,   129,   130,   131,   132,     0,
       0,     0,     0,   133,     0,   134,   135,   136,   120,   121,
     122,   123,     0,   124,   125,   126,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   127,   128,   129,
     130,   131,   132,     0,   170,     0,     0,   133,     0,   134,
     135,   136,   120,   121,   122,   123,     0,   124,   125,   126,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,   129,   130,   131,   132,     0,     0,     0,
     205,   133,     0,   134,   135,   136,   120,   121,   122,   123,
       0,   124,   125,   126,     0,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,     0,     0,     0,     0,   133,     0,   134,   135,   136,
     120,   121,   122,   123,     0,   124,   125,   126,     0,   296,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,   129,   130,   131,   132,     0,     0,     0,     0,   133,
       0,   134,   135,   136,   120,   121,   122,   123,     0,   124,
     125,   126,     0,     0,     0,   297,     0,     0,     0,     0,
       0,     0,     0,   127,   128,   129,   130,   131,   132,     0,
       0,     0,     0,   133,     0,   134,   135,   136,   120,   121,
     122,   123,     0,   124,   125,   126,     0,     0,     0,     0,
       0,     0,   397,     0,     0,     0,     0,   127,   128,   129,
     130,   131,   132,     0,     0,     0,     0,   133,     0,   134,
     135,   136,   120,   121,   122,   123,     0,   124,   125,   126,
       0,     0,     0,     0,     0,   398,     0,     0,     0,     0,
       0,   127,   128,   129,   130,   131,   132,     0,     0,     0,
       0,   133,     0,   134,   135,   136,   120,   121,   122,   123,
       0,   124,   125,   126,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,     0,     0,     0,     0,   133,     0,   134,   135,   136,
     120,   121,   122,     0,     0,   124,   125,   126,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,   129,   130,   131,   132,     0,     0,     0,     0,     0,
       0,   134,   135,   136
  };

  const short int
  Parser::yycheck_[] =
  {
      10,    46,    48,     1,    18,   147,    86,     1,     0,    44,
      35,    36,     4,    38,    18,    18,    33,    18,     3,    55,
      18,    57,     1,    18,    18,    18,   199,    37,    15,    21,
      65,     0,    42,    43,    44,    45,    46,     2,     5,    18,
     151,   152,   153,     3,    47,    49,   188,    64,    52,    47,
      45,    16,    17,    18,    19,    20,   229,    52,    46,    52,
      56,    48,    47,    30,    48,    79,    62,    55,    47,    34,
      35,    36,   214,    38,    75,    79,    79,   188,    79,    45,
      45,    79,    47,    45,    79,    79,    79,    47,     4,     5,
       6,     7,     8,     9,   139,    48,   260,    48,   108,    46,
      79,    44,    55,    52,   215,   269,   270,   218,    55,   251,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   207,    58,   139,
     241,    47,    99,     1,    99,    65,     4,     5,     6,     7,
       8,     9,    46,    44,   154,    51,   156,   157,   158,   159,
     137,    55,   162,    50,    18,   147,   166,   299,    55,   169,
     170,    51,    44,    18,   151,   152,   153,    18,    18,    46,
      34,    35,    36,   138,    55,    51,   141,   288,   289,    47,
      65,    45,   147,    47,    55,    50,    64,   298,    52,    67,
      54,    58,    59,    60,    61,   205,   206,    49,     0,     1,
     165,   188,     4,     5,     6,     7,     8,     9,    48,    73,
      74,    75,    76,    77,    78,    79,    65,    61,   217,    46,
      46,    58,    65,   188,   216,    42,    43,   338,   215,   340,
      55,   218,   242,    55,    44,    64,    64,   262,   263,   264,
      64,    58,    59,    60,    61,    47,    44,   214,    13,   214,
      65,   216,    15,    44,   241,    64,    50,   267,   268,   251,
     259,   260,    18,    18,    72,    11,   265,   266,    46,    46,
     269,   270,    10,    49,    49,    57,    26,    49,    51,    50,
     290,   291,   292,   293,   294,    51,   251,    21,    30,    50,
     383,   258,   307,   258,    90,   305,   138,   262,   263,   264,
     241,   288,   289,   165,   241,   207,   386,   386,    -1,    99,
      -1,   298,   311,   251,   313,   307,    -1,   327,    -1,   217,
      -1,    -1,    -1,    -1,    -1,   324,    -1,   326,    -1,   328,
      42,    43,    44,   217,   299,    -1,    -1,    -1,   348,   349,
     350,    -1,   307,    -1,    56,    57,    58,    59,    60,    61,
      -1,   338,   351,   340,   217,    -1,    68,    69,    70,   369,
     370,   259,   260,    -1,    -1,    -1,   376,   265,   266,    -1,
      -1,   269,   270,   383,    -1,   374,   375,    -1,   377,   378,
      -1,   265,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   393,   394,   259,   260,   397,    -1,
      -1,   400,   265,   266,    -1,    -1,   269,   270,    -1,    -1,
      -1,    -1,    -1,   311,    37,   313,    39,    -1,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,   324,   311,   326,   313,
     328,    -1,    -1,    56,    57,    58,    59,    60,    61,    -1,
     324,    -1,   326,    -1,   328,    68,    69,    70,   311,    -1,
     313,    37,    -1,   351,    -1,   217,    42,    43,    44,    -1,
      -1,   324,    -1,   326,    -1,   328,    -1,   351,    -1,    -1,
      56,    57,    58,    59,    60,    61,   374,   375,    -1,   377,
     378,    -1,    68,    69,    70,    -1,    -1,    -1,   351,    -1,
     374,   375,    -1,   377,   378,   393,   394,   259,   260,   397,
      -1,    -1,   400,   265,   266,    -1,     1,   269,   270,   393,
     394,   374,   375,   397,   377,   378,   400,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
     393,   394,    27,    -1,   397,    -1,    -1,   400,    -1,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   311,
      45,   313,    47,    -1,    49,    -1,    -1,    52,    -1,    54,
      -1,    -1,   324,    -1,   326,    -1,   328,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    71,    -1,    73,    74,
      75,    76,    77,    78,    79,    -1,    12,    -1,    14,   351,
      16,    17,    18,    19,    20,    21,    -1,    23,    24,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    -1,   374,   375,    -1,   377,   378,    -1,    -1,    45,
      -1,    47,    -1,    49,    -1,    -1,    52,    -1,    54,    -1,
      -1,   393,   394,    -1,    -1,   397,    -1,    -1,   400,    -1,
      -1,    -1,    -1,     1,    -1,    71,    -1,    73,    74,    75,
      76,    77,    78,    79,    12,    -1,    14,    -1,    16,    17,
      18,    19,    20,    21,    -1,    23,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,
      -1,    49,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    71,    -1,    73,    74,    75,    76,    77,
      78,    79,    12,    -1,    14,    -1,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    45,    -1,    47,    -1,    49,
      -1,    -1,    52,    -1,    54,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,     1,    -1,    -1,    -1,    69,    70,
      -1,    71,    -1,    73,    74,    75,    76,    77,    78,    79,
      17,    18,    19,    20,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    29,    -1,    31,    -1,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    41,    42,    43,    -1,    45,    -1,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,
      77,    78,    79,    17,    18,    19,    20,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,    43,
      -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    52,    -1,
      54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    77,    78,    79,    17,    18,    19,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,
      41,    42,    43,    -1,    45,    -1,    47,    48,    -1,    -1,
      -1,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    76,    77,    78,    79,    17,
      18,    19,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    41,    42,    43,    -1,    45,    46,    47,
      -1,    -1,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,
      78,    79,    12,    13,    14,    -1,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,    49,
      -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    -1,    73,    74,    75,    76,    77,    78,    79,
      12,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    23,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,
      52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    73,    74,    75,    76,    77,    78,    79,    12,    -1,
      14,    -1,    16,    17,    18,    19,    20,    21,    -1,    23,
      24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    47,    -1,    49,    50,    -1,    52,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    73,
      74,    75,    76,    77,    78,    79,    12,    -1,    14,    -1,
      16,    17,    18,    19,    20,    21,    -1,    23,    24,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    47,    -1,    49,    -1,    -1,    52,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    12,    -1,    14,    -1,    16,    17,
      18,    19,    20,    21,    -1,    23,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,
      -1,    49,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,    73,    74,    75,    76,    77,
      78,    79,    17,    18,    19,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    -1,    34,
      35,    36,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,
      45,    -1,    47,    -1,    -1,    50,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      75,    76,    77,    78,    79,    17,    18,    19,    20,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,    41,
      42,    43,    18,    45,    -1,    47,    -1,    -1,    -1,    -1,
      52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    73,    74,    75,    76,    77,    78,    79,    18,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      66,    -1,    68,    69,    70,    -1,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    22,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    -1,    32,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    22,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    22,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    22,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    25,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    25,
      -1,    -1,    -1,    66,    -1,    68,    69,    70,    -1,    -1,
      -1,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    26,    -1,    -1,    -1,
      66,    -1,    68,    69,    70,    -1,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    28,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    30,    -1,
      66,    -1,    68,    69,    70,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    32,    68,    69,    70,    -1,
      37,    38,    39,    40,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    66,
      -1,    68,    69,    70,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    -1,    68,    69,    70,    37,    38,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    -1,    63,    -1,    -1,    66,    -1,    68,
      69,    70,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      65,    66,    -1,    68,    69,    70,    37,    38,    39,    40,
      -1,    42,    43,    44,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    66,    -1,    68,    69,    70,
      37,    38,    39,    40,    -1,    42,    43,    44,    -1,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    66,
      -1,    68,    69,    70,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    -1,    68,    69,    70,    37,    38,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,    66,    -1,    68,
      69,    70,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    66,    -1,    68,    69,    70,    37,    38,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    66,    -1,    68,    69,    70,
      37,    38,    39,    -1,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70
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
      37,    38,    39,    40,    42,    43,    44,    56,    57,    58,
      59,    60,    61,    66,    68,    69,    70,    33,    64,    45,
     151,    52,   114,   138,   158,   159,   160,    45,   155,    44,
     155,    44,    51,    51,    44,   164,    18,    18,    25,    18,
      46,   114,    55,    46,    46,    55,    51,    48,    48,    55,
      63,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,    45,   143,
     144,   145,   146,   147,   148,   149,   150,   162,   130,   161,
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
       0,   392,   392,   401,   407,   415,   421,   431,   437,   441,
     449,   453,   457,   461,   465,   473,   481,   489,   494,   503,
     519,   527,   550,   568,   572,   578,   586,   592,   602,   614,
     618,   622,   626,   630,   634,   638,   642,   646,   650,   654,
     662,   668,   678,   686,   690,   698,   702,   710,   714,   718,
     726,   732,   742,   750,   754,   762,   770,   778,   782,   786,
     791,   800,   804,   808,   813,   822,   832,   836,   840,   844,
     848,   852,   864,   870,   880,   884,   888,   892,   896,   900,
     904,   908,   916,   920,   924,   928,   932,   936,   940,   952,
     956,   960,   964,   968,   972,   976,   980,   984,   988,   992,
     996,  1000,  1004,  1008,  1012,  1016,  1020,  1024,  1028,  1036,
    1041,  1049,  1054,  1062,  1070,  1078,  1086,  1094,  1102,  1110,
    1118,  1130,  1134,  1138,  1142,  1146,  1150,  1154,  1158,  1162,
    1166,  1170,  1174,  1182,  1190,  1195,  1204,  1220,  1236,  1252,
    1264,  1280,  1296,  1304,  1309,  1313,  1321,  1328,  1336,  1343,
    1349,  1358,  1370,  1376,  1386,  1390,  1394,  1398,  1402,  1410,
    1418,  1422,  1429,  1439,  1459,  1467,  1475,  1487,  1491,  1495,
    1509,  1515,  1525,  1529,  1537,  1543,  1553,  1557,  1561,  1573,
    1577,  1585,  1589,  1597,  1603,  1613,  1621,  1631,  1642,  1646,
    1658,  1662,  1670,  1674,  1684,  1690,  1704,  1708,  1717,  1723,
    1733,  1741,  1747,  1755,  1761,  1772,  1778,  1788,  1792,  1796,
    1804,  1812
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
#line 4403 "GrammarParser.cpp" // lalr1.cc:1167
#line 1818 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
