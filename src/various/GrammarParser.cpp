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
      case 171: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 170: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 172: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 145: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 109: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 117: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
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

      case 125: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 107: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 146: // ComposedType
      case 147: // TupleType
      case 148: // RecordType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 124: // ConditionalExpression
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

      case 118: // DirectCallExpression
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

      case 127: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 114: // Term
      case 115: // SimpleOrClaspedTerm
      case 116: // OperatorExpression
      case 157: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 173: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 113: // Terms
      case 152: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 151: // FixedSizedType
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

      case 162: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 163: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 164: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 121: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 108: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 123: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 105: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 137: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 128: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 120: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 119: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 142: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 141: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 138: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 140: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 136: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 150: // RelationType
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

      case 149: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 139: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 122: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 143: // Types
      case 153: // FunctionParameters
      case 154: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 129: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 126: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 111: // UpdateRule
      case 160: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 158: // MaybeInitially
      case 159: // Initializers
      case 161: // MaybeInitializers
        value.move< UpdateRules::Ptr > (that.value);
        break;

      case 97: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 130: // BooleanLiteral
      case 131: // IntegerLiteral
      case 132: // RationalLiteral
      case 133: // DecimalLiteral
      case 134: // BinaryLiteral
      case 135: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 165: // Variable
      case 167: // TypedVariable
      case 168: // AttributedVariable
      case 169: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 155: // Parameters
      case 156: // MaybeParameters
      case 166: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 144: // Type
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
      case 171: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 170: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 172: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 145: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 109: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 117: // CallExpression
        value.copy< CallExpression::Ptr > (that.value);
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

      case 125: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 107: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 146: // ComposedType
      case 147: // TupleType
      case 148: // RecordType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 124: // ConditionalExpression
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

      case 118: // DirectCallExpression
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

      case 127: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 114: // Term
      case 115: // SimpleOrClaspedTerm
      case 116: // OperatorExpression
      case 157: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 173: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 113: // Terms
      case 152: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 151: // FixedSizedType
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

      case 162: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 163: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 164: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 121: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 108: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 123: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 105: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 137: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 128: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 120: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 119: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 142: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 141: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 138: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 140: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 136: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 150: // RelationType
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

      case 149: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 139: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 122: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 143: // Types
      case 153: // FunctionParameters
      case 154: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 129: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 126: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 111: // UpdateRule
      case 160: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 158: // MaybeInitially
      case 159: // Initializers
      case 161: // MaybeInitializers
        value.copy< UpdateRules::Ptr > (that.value);
        break;

      case 97: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 130: // BooleanLiteral
      case 131: // IntegerLiteral
      case 132: // RationalLiteral
      case 133: // DecimalLiteral
      case 134: // BinaryLiteral
      case 135: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 165: // Variable
      case 167: // TypedVariable
      case 168: // AttributedVariable
      case 169: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 155: // Parameters
      case 156: // MaybeParameters
      case 166: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 144: // Type
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
      case 171: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 170: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 172: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 145: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 109: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 117: // CallExpression
        yylhs.value.build< CallExpression::Ptr > ();
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

      case 125: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 107: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 146: // ComposedType
      case 147: // TupleType
      case 148: // RecordType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 124: // ConditionalExpression
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

      case 118: // DirectCallExpression
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

      case 127: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 114: // Term
      case 115: // SimpleOrClaspedTerm
      case 116: // OperatorExpression
      case 157: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 173: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 113: // Terms
      case 152: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 151: // FixedSizedType
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

      case 162: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 163: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 164: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 121: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 108: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 123: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 105: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 137: // ListLiteral
        yylhs.value.build< ListLiteral::Ptr > ();
        break;

      case 128: // Literal
        yylhs.value.build< Literal::Ptr > ();
        break;

      case 120: // LiteralCallExpression
        yylhs.value.build< LiteralCallExpression::Ptr > ();
        break;

      case 119: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 142: // Assignment
        yylhs.value.build< NamedExpression::Ptr > ();
        break;

      case 141: // Assignments
        yylhs.value.build< NamedExpressions::Ptr > ();
        break;

      case 138: // RangeLiteral
        yylhs.value.build< RangeLiteral::Ptr > ();
        break;

      case 140: // RecordLiteral
        yylhs.value.build< RecordLiteral::Ptr > ();
        break;

      case 136: // ReferenceLiteral
        yylhs.value.build< ReferenceLiteral::Ptr > ();
        break;

      case 150: // RelationType
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

      case 149: // TemplateType
        yylhs.value.build< TemplateType::Ptr > ();
        break;

      case 139: // TupleLiteral
        yylhs.value.build< TupleLiteral::Ptr > ();
        break;

      case 122: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 143: // Types
      case 153: // FunctionParameters
      case 154: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 129: // UndefinedLiteral
        yylhs.value.build< UndefLiteral::Ptr > ();
        break;

      case 126: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 111: // UpdateRule
      case 160: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 158: // MaybeInitially
      case 159: // Initializers
      case 161: // MaybeInitializers
        yylhs.value.build< UpdateRules::Ptr > ();
        break;

      case 97: // UsingDefinition
        yylhs.value.build< UsingDefinition::Ptr > ();
        break;

      case 130: // BooleanLiteral
      case 131: // IntegerLiteral
      case 132: // RationalLiteral
      case 133: // DecimalLiteral
      case 134: // BinaryLiteral
      case 135: // StringLiteral
        yylhs.value.build< ValueLiteral::Ptr > ();
        break;

      case 165: // Variable
      case 167: // TypedVariable
      case 168: // AttributedVariable
      case 169: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 155: // Parameters
      case 156: // MaybeParameters
      case 166: // TypedVariables
        yylhs.value.build< VariableDefinitions::Ptr > ();
        break;

      case 144: // Type
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
#line 395 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1488 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1498 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1506 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 418 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1516 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1526 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 452 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1560 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 456 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1576 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 464 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 468 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< UsingDefinition::Ptr > ();
  }
#line 1592 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1600 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1608 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 492 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< VariableDefinitions::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1626 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1646 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 522 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1654 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 530 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto singleAgentIdentifier = Ast::make< Identifier >( yylhs.location, "$" );
      auto singleAgentArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( singleAgentIdentifier ), singleAgentArguments );
      singleAgent->setTargetType( DirectCallExpression::TargetType::CONSTANT );

      auto programDefinition = createProgramFunction( yylhs.location );
      auto programArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      programArguments->add( singleAgent );
      const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( programDefinition->identifier() ), programArguments );
      program->setTargetType( DirectCallExpression::TargetType::FUNCTION );

      const auto ruleReference = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );

      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1681 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 571 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 575 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1735 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 595 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1745 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1753 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 621 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 625 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1777 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 629 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1793 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 637 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1801 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 641 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1809 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1817 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 649 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1825 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 653 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1833 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 657 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1841 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 665 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1851 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 689 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 693 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 701 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1901 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 713 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 717 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 721 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 729 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1935 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 745 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 753 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 765 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 773 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1985 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 781 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1993 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 789 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2010 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 794 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2019 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2027 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 807 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2035 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 811 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2044 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2053 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( DirectCallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2063 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 835 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< CallExpression::Ptr > () );
  }
#line 2071 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 847 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2081 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 853 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2091 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 863 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2099 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 867 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2107 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 871 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2115 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 875 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2123 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 879 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2131 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 883 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2139 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2147 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2155 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2163 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2171 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< CallExpression::Ptr > ();
  }
#line 2179 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LiteralCallExpression::Ptr > ();
  }
#line 2187 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 915 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Literal::Ptr > ();
  }
#line 2195 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2203 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 923 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2211 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 935 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2219 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 939 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2227 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 943 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2235 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 947 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 951 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 955 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2259 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 959 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2267 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 963 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2275 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 967 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2283 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 971 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2291 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 975 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2299 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 979 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2307 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 983 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 987 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2323 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 991 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2331 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 995 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2339 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 999 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1003 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1011 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1015 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2371 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1019 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2379 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1027 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2396 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< ValueLiteral::Ptr > () );
  }
#line 2421 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1061 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< CallExpression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1069 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2437 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1077 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2445 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1085 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2453 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1093 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2461 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1101 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1109 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2477 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1121 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< UndefLiteral::Ptr > ();
  }
#line 2485 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1125 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2493 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1129 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2501 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1137 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1141 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1145 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2533 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1149 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ReferenceLiteral::Ptr > ();
  }
#line 2541 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1153 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ListLiteral::Ptr > ();
  }
#line 2549 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1157 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RangeLiteral::Ptr > ();
  }
#line 2557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1161 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< TupleLiteral::Ptr > ();
  }
#line 2565 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RecordLiteral::Ptr > ();
  }
#line 2573 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1173 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 2581 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1181 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2590 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1186 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1195 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1211 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1227 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1243 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1255 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2679 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1271 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1287 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2703 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1295 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
  }
#line 2712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1300 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1304 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = nullptr;
  }
#line 2728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1312 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1319 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
  }
#line 2746 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1327 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as< NamedExpressions::Ptr > () );
  }
#line 2754 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = yystack_[2].value.as< NamedExpressions::Ptr > ();
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1340 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1361 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1367 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2802 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1377 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2810 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1381 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2818 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< TemplateType::Ptr > ();
  }
#line 2826 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1389 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2834 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2842 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1401 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1409 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1413 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Tuple" );
      auto subTypes = yystack_[3].value.as< Types::Ptr > ();
      subTypes->add( yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes );
  }
#line 2877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2929 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1482 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2937 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1486 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2946 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1500 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2956 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1506 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2966 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1516 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2974 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1520 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2982 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1528 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 2992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1534 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1544 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = yystack_[1].value.as< VariableDefinitions::Ptr > ();
  }
#line 3010 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1548 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = nullptr;
  }
#line 3018 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1552 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 3026 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1564 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 3034 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1568 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 3042 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1576 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[1].value.as< UpdateRules::Ptr > ();
  }
#line 3050 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1580 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3058 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1588 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< UpdateRules::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3068 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1604 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( DirectCallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3090 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( DirectCallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3104 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< TupleLiteral::Ptr > ()->expressions() );
      function->setTargetType( DirectCallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3115 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[0].value.as< UpdateRules::Ptr > ();
  }
#line 3123 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1637 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3131 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1649 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 3139 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1653 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 3147 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 3155 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1665 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 3165 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1675 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 3175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 3185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1695 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1699 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 3202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1708 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3212 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1714 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3222 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1724 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3230 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3240 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1738 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3248 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1746 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3258 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1752 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1763 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[1].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1769 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3286 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1779 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< BasicAttribute::Ptr > ();
  }
#line 3294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1783 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3302 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1787 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = nullptr;
  }
#line 3310 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1795 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3318 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3326 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3330 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -219;

  const short int Parser::yytable_ninf_ = -168;

  const short int
  Parser::yypact_[] =
  {
       9,  -219,    19,    14,    59,    36,  -219,   -16,  -219,  -219,
    1433,    49,    60,  -219,  -219,    -8,    10,    10,    10,    10,
      10,   134,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
     160,  -219,  -219,  -219,    -1,    -1,    -1,  1433,    -1,  -219,
    -219,  -219,  1433,  1509,  1509,   974,   850,    10,    20,  -219,
    -219,  -219,  -219,  -219,  -219,  2231,   -19,  -219,     5,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,     5,    -5,  -219,  -219,  1495,  -219,    86,
      11,    86,    89,    94,  -219,  -219,    97,  -219,  -219,   115,
      -1,   141,   144,  1783,   157,  -219,  -219,  -219,   132,   124,
    1993,     2,  -219,   136,   145,  -219,    52,  2027,  -219,  -219,
    1433,  1433,  1433,  1433,  1433,  1433,  1433,  1433,  1433,  1433,
    1433,  1433,  1433,  1433,  1433,  1433,  1433,     8,    30,   912,
    -219,  -219,    10,   974,  2231,   127,   146,  -219,   147,     7,
     131,   154,    -2,     8,     8,     8,  1433,  -219,  1433,  1433,
    1433,  1433,  -219,  1433,  -219,  -219,    10,  1433,  -219,  -219,
    1433,  1433,  2305,  2299,   337,  2265,   125,   125,   465,   130,
     130,   148,   148,   148,  -219,  2265,   465,   130,   130,     8,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,   118,  -219,
       5,   159,  -219,    35,  2231,  -219,  2061,  1433,  1495,  -219,
     162,    91,    97,  -219,  -219,    -1,     8,    15,  1309,     8,
    -219,  -219,   152,   149,  -219,  1556,  1924,  1668,  1856,  1959,
    2095,  -219,   136,  2231,  2231,  2129,   156,  -219,    97,   158,
    -219,     8,  1433,  -219,  -219,  -219,   150,  2231,  -219,  -219,
    -219,    -1,  -219,   168,  -219,  -219,    29,  -219,    -1,   525,
     592,  -219,    -1,    -1,    -1,  1309,  1433,  1433,   659,   726,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,   153,   -29,   151,   175,     8,     8,  1433,  1433,
    1433,  1433,  1433,  -219,  -219,     8,    10,    25,   117,   155,
    -219,  1433,  -219,  1433,  -219,    15,  -219,   208,  -219,  1041,
     209,  1108,   180,   207,   213,  -219,  1820,  1890,   177,  1175,
     165,  1242,  1433,  1309,  -219,   216,  2231,  2231,  2231,  2231,
    2231,   188,   192,     8,  -219,     8,  2231,  2231,  -219,  -219,
    -219,  -219,  -219,  -219,  1433,  1433,  1433,  1309,   190,  -219,
    -219,  -219,  -219,  2231,  -219,   191,   231,  -219,  -219,  -219,
     186,  1590,  1629,  1707,   221,   788,  1433,   199,  -219,  -219,
    1309,  1309,  1433,  1309,  1309,   200,   198,   201,  -219,  1371,
    2163,  2197,  1495,  -219,  -219,  1746,  -219,  -219,  -219,  1309,
    1309,  -219,  -219,  1309,  -219,   203,  1309,  -219,  -219,  -219,
    -219,  -219
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   202,     0,   187,   186,
     206,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     6,     8,    10,    11,    12,    13,    20,    14,
       0,     3,   201,   205,     0,     0,     0,     0,     0,   129,
     131,   130,     0,     0,     0,     0,     0,     0,     0,   135,
     136,   132,   133,   134,   137,   207,    69,    71,    79,   102,
     103,    80,   104,    70,    72,    73,    74,    75,    76,    81,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   191,   105,   188,   203,   204,   185,    21,   174,
       0,   174,     0,     0,     5,     7,   193,   198,   192,     0,
       0,     0,     0,     0,     0,   101,    82,    83,     0,     0,
      68,     0,   146,   191,     0,   139,     0,    68,   189,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,   106,     0,     0,   181,   127,   184,   180,     0,     0,
       0,     0,     0,     0,   169,     0,     0,   197,     0,     0,
       0,     0,    78,     0,    77,   144,     0,     0,   141,   140,
       0,     0,    98,    96,    97,   100,    84,    85,    91,    92,
      93,    86,    87,    88,    89,    99,    90,    94,    95,     0,
     111,   150,   151,   156,   157,   152,   153,   154,   155,   109,
     107,     0,   165,     0,    68,   190,    68,     0,     0,    22,
       0,     0,     0,   200,   171,     0,     0,     0,     0,     0,
      28,   167,   168,     0,   196,     0,     0,     0,     0,     0,
      67,   145,     0,   147,    67,     0,     0,   149,   191,     0,
     195,   169,     0,   108,   164,   163,    77,   183,   179,   173,
     172,     0,   199,     0,    25,    27,     0,    23,     0,     0,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
      17,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     0,    66,   102,     0,     0,     0,     0,     0,
       0,     0,     0,   143,   142,     0,     0,     0,   149,     0,
     162,     0,   170,     0,    15,     0,    24,     0,    41,     0,
       0,     0,     0,     0,     0,    56,     0,     0,     0,     0,
       0,     0,     0,     0,   166,   176,   112,   115,   114,   113,
     116,   148,   194,     0,   160,     0,   182,    16,    26,    64,
      62,    40,    60,    58,     0,     0,     0,     0,     0,    59,
      57,    63,    61,    65,    18,     0,   178,   158,   159,   148,
       0,     0,     0,     0,    43,     0,     0,     0,    19,   161,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
       0,     0,   185,    52,    53,     0,    55,    44,    46,     0,
       0,    45,    50,     0,   175,     0,     0,    47,    48,    49,
     177,    54
  };

  const short int
  Parser::yypgoto_[] =
  {
    -219,  -219,  -219,  -219,   229,   223,  -219,  -219,  -219,  -219,
    -219,   -50,  -219,  -219,   112,  -218,  -219,  -219,  -219,  -119,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,   -37,
     -10,   -25,  -219,   107,   142,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,   123,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,   -81,  -219,  -219,    96,    22,
    -132,  -219,  -219,  -219,  -219,  -219,  -219,  -219,   -72,  -219,
      23,  -219,   174,  -219,  -219,  -219,    58,  -115,    56,   122,
    -219,   169,  -219,  -120,   -34,    17,     3,     0,  -219,  -219
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,   255,   256,    29,   308,   309,   271,   272,   273,   378,
     379,   274,   275,   276,   277,   278,   279,   280,   281,   109,
     144,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,   111,   112,   236,
     190,   191,   192,   193,   194,   195,   196,   197,   140,   222,
     223,   211,   150,   356,   368,   146,   147,   148,    82,    83,
      84,    97,   239,    98,    99,   214,   100,     6,    11,    12
  };

  const short int
  Parser::yytable_[] =
  {
      55,   101,   102,     5,   104,    32,   145,    30,   210,   116,
       8,   141,     1,   137,    13,   139,   254,     8,   106,   107,
       7,   220,   221,   224,    30,     8,     8,   103,     8,   213,
      32,    33,   105,     8,   -79,   110,   117,     8,     8,    31,
      87,   218,   311,    47,   138,     2,   142,   165,     8,   139,
     319,   321,   189,     2,   151,     2,   166,   237,    10,    47,
      14,     2,   219,    15,    16,    17,    18,    19,    20,   240,
       9,    47,    89,    90,    91,    92,    93,     9,   304,   333,
     245,   334,     2,   305,   253,     9,     9,   285,     9,   170,
      96,    96,    96,     9,    96,   252,    85,     9,     9,   169,
      32,   113,   203,   118,    51,     2,   170,    86,     9,   298,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   145,   243,   204,
     149,   213,   153,   206,    -2,    14,   250,    88,    15,    16,
      17,    18,    19,    20,   154,   251,   225,   155,   226,   227,
     228,   229,   215,   230,   324,   325,    96,   233,   156,   158,
     234,   235,   159,   331,    15,    16,    17,    18,    19,    20,
     119,   124,   125,   241,  -167,   161,   332,   162,   163,   242,
       2,  -167,   129,   130,   131,   132,   167,   129,   130,   131,
     132,   207,   168,   282,   200,   216,   209,   247,   205,   113,
     208,   359,   217,   360,   244,   212,     2,   249,   132,   286,
     295,   303,   296,   287,   301,    32,   138,   322,   323,   335,
     258,   339,   232,   344,   342,   345,   349,   355,   312,   313,
     314,   346,   300,   357,   282,   282,   351,   358,   365,   366,
     282,   367,   369,   282,   282,   238,   374,   382,   389,   388,
      94,   390,   400,    95,   215,   338,   316,   317,    32,   198,
     392,   199,   231,   297,   299,   152,   248,   395,   302,   157,
       0,   212,     0,   257,     0,   198,   198,   198,   326,   327,
     328,   329,   330,     0,   282,     0,   282,     0,     0,     0,
       0,   336,     0,   337,   282,     0,   282,     0,   282,     0,
       0,   145,     0,     0,     0,     0,     0,   212,   258,     0,
       0,   198,   353,     0,   306,     0,     0,     0,    96,    96,
      96,     0,   282,     0,     0,   283,     0,     0,     0,     0,
     270,     0,     0,     0,   361,   362,   363,     0,   198,     0,
       0,   198,     0,     0,     0,   282,   282,     0,   282,   282,
       0,     0,   212,     0,     0,   380,   381,     0,     0,     0,
     284,   257,   385,   198,   282,   282,   283,   283,   282,   380,
       0,   282,   283,   120,     0,   283,   283,   315,   124,   125,
     126,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,   129,   130,   131,   132,     0,     0,
       0,   284,   284,     0,   134,   135,   136,   284,   198,   198,
     284,   284,     0,     0,     0,     0,   283,   198,   283,     0,
       0,   341,     0,   341,     0,     0,   283,     0,   283,     0,
     283,   341,     0,   341,     0,   354,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   284,     0,   284,   283,   198,     0,   198,     0,   364,
       0,   284,     0,   284,     0,   284,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   283,   283,     0,
     283,   283,   383,   384,     0,   386,   387,     0,     0,   284,
       0,     0,     0,     0,     0,     0,   283,   283,     0,     0,
     283,   397,   398,   283,     0,   399,   124,   125,   401,     0,
       0,     0,   284,   284,     0,   284,   284,     0,     0,     0,
     127,   128,   129,   130,   131,   132,   307,     0,     0,     0,
       0,   284,   284,   135,   136,   284,     0,   259,   284,   260,
       0,   261,   262,     8,   263,   264,   265,     0,   266,     0,
       0,   267,     0,     0,     0,     0,     0,     0,    39,    40,
      41,     0,     0,     0,     0,     0,    43,    44,     0,    45,
       0,    46,     0,   268,     0,     0,    47,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   310,     0,   269,     0,    49,    50,    51,
      52,    53,    54,     9,   259,     0,   260,     0,   261,   262,
       8,   263,   264,   265,     0,   266,     0,     0,   267,     0,
       0,     0,     0,     0,     0,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     268,     0,     0,    47,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     318,     0,   269,     0,    49,    50,    51,    52,    53,    54,
       9,   259,     0,   260,     0,   261,   262,     8,   263,   264,
     265,     0,   266,     0,     0,   267,     0,     0,     0,     0,
       0,     0,    39,    40,    41,     0,     0,     0,     0,     0,
      43,    44,     0,    45,     0,    46,     0,   268,     0,     0,
      47,     0,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   320,     0,   269,
       0,    49,    50,    51,    52,    53,    54,     9,   259,     0,
     260,     0,   261,   262,     8,   263,   264,   265,     0,   266,
       0,     0,   267,     0,     0,     0,     0,     0,     0,    39,
      40,    41,     0,     0,     0,     0,     0,    43,    44,     0,
      45,     0,    46,     0,   268,     0,     0,    47,     0,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   375,
       0,     0,     0,     0,     0,     0,   269,     0,    49,    50,
      51,    52,    53,    54,     9,    34,     8,    35,    36,     0,
       0,    37,     0,     0,     0,     0,   376,     0,    38,     0,
       0,    39,    40,    41,     0,     0,     0,     0,    42,    43,
      44,     0,    45,     0,    46,     0,     0,     0,     0,    47,
     377,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,    51,    52,    53,    54,     9,    34,     8,    35,
      36,     0,     0,    37,     0,     0,     0,     0,     0,     0,
      38,     0,     0,    39,    40,    41,     0,     0,     0,     0,
      42,    43,    44,     0,    45,     0,    46,   115,     0,     0,
       0,    47,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,    53,    54,     9,    34,
       8,    35,    36,     0,     0,    37,     0,     0,     0,     0,
       0,     0,    38,     0,     0,    39,    40,    41,     0,     0,
       0,     0,    42,    43,    44,     0,    45,   202,    46,     0,
       0,     0,     0,    47,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,    51,    52,    53,    54,
       9,    34,     8,    35,    36,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    38,     0,     0,    39,    40,    41,
       0,     0,     0,     0,    42,    43,    44,     0,    45,     0,
      46,     0,     0,     0,     0,    47,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
      53,    54,     9,   259,   340,   260,     0,   261,   262,     8,
     263,   264,   265,     0,   266,     0,     0,   267,     0,     0,
       0,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,     0,    43,    44,     0,    45,     0,    46,     0,   268,
       0,     0,    47,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   269,     0,    49,    50,    51,    52,    53,    54,     9,
     259,     0,   260,   343,   261,   262,     8,   263,   264,   265,
       0,   266,     0,     0,   267,     0,     0,     0,     0,     0,
       0,    39,    40,    41,     0,     0,     0,     0,     0,    43,
      44,     0,    45,     0,    46,     0,   268,     0,     0,    47,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   269,     0,
      49,    50,    51,    52,    53,    54,     9,   259,     0,   260,
       0,   261,   262,     8,   263,   264,   265,     0,   266,     0,
       0,   267,     0,     0,     0,     0,     0,     0,    39,    40,
      41,     0,     0,     0,     0,     0,    43,    44,     0,    45,
       0,    46,     0,   268,   350,     0,    47,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   269,     0,    49,    50,    51,
      52,    53,    54,     9,   259,     0,   260,     0,   261,   262,
       8,   263,   264,   265,     0,   266,     0,     0,   267,     0,
       0,     0,     0,     0,     0,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     268,     0,     0,    47,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   269,   352,    49,    50,    51,    52,    53,    54,
       9,   259,     0,   260,     0,   261,   262,     8,   263,   264,
     265,     0,   266,     0,     0,   267,     0,     0,     0,     0,
       0,     0,    39,    40,    41,     0,     0,     0,     0,     0,
      43,    44,     0,    45,     0,    46,     0,   268,     0,     0,
      47,     0,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   269,
       0,    49,    50,    51,    52,    53,    54,     9,    34,     8,
      35,    36,     0,     0,    37,     0,     0,     0,     0,   376,
       0,    38,     0,     0,    39,    40,    41,     0,     0,     0,
       0,    42,    43,    44,     0,    45,     0,    46,     0,     0,
     391,     0,    47,   377,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,    50,    51,    52,    53,    54,     9,
      34,     8,    35,    36,     0,     0,    37,     0,     0,     0,
       0,     0,     0,    38,     0,     0,    39,    40,    41,     0,
       0,     0,     0,    42,    43,    44,     0,    45,     0,    46,
       0,     0,     0,     0,    47,     0,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,    51,    52,    53,
      54,     9,    34,     8,    35,    36,     0,     0,    37,     0,
       0,     0,     0,     0,     0,    38,     0,     8,    39,    40,
      41,     0,     0,     0,     0,    42,    43,    44,     0,   143,
       0,    46,    39,    40,    41,     0,    47,     0,    48,     0,
      43,    44,     0,    45,     0,    46,     0,     0,     0,     0,
      47,     0,    48,     0,     0,     0,     0,    49,    50,    51,
      52,    53,    54,     9,   288,     0,     0,     0,     0,     0,
       0,    49,    50,    51,    52,    53,    54,     9,     0,     0,
       0,     0,   120,   121,   122,   123,     0,   124,   125,   126,
       0,     0,     0,     0,     0,     0,     0,     0,   370,     0,
       0,   127,   128,   129,   130,   131,   132,     0,     0,     0,
       0,   133,     0,   134,   135,   136,   120,   121,   122,   123,
       0,   124,   125,   126,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,   371,     0,     0,     0,   133,     0,   134,   135,   136,
     372,     0,     0,     0,     0,   120,   121,   122,   123,     0,
     124,   125,   126,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   127,   128,   129,   130,   131,   132,
     290,     0,     0,     0,   133,     0,   134,   135,   136,     0,
       0,     0,     0,     0,   120,   121,   122,   123,     0,   124,
     125,   126,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   373,
       0,     0,     0,   133,     0,   134,   135,   136,     0,     0,
       0,     0,     0,   120,   121,   122,   123,     0,   124,   125,
     126,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,   129,   130,   131,   132,   396,     0,
       0,     0,   133,     0,   134,   135,   136,     0,     0,     0,
       0,     0,   120,   121,   122,   123,     0,   124,   125,   126,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,   129,   130,   131,   132,   160,     0,     0,
       0,   133,     0,   134,   135,   136,     0,     0,     0,   120,
     121,   122,   123,     0,   124,   125,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,   347,     0,     0,     0,   133,     0,
     134,   135,   136,     0,     0,     0,   120,   121,   122,   123,
       0,   124,   125,   126,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,   291,     0,     0,     0,   133,     0,   134,   135,   136,
       0,     0,   120,   121,   122,   123,     0,   124,   125,   126,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,   129,   130,   131,   132,   348,     0,     0,
       0,   133,     0,   134,   135,   136,   120,   121,   122,   123,
       0,   124,   125,   126,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,     0,     0,   289,     0,   133,     0,   134,   135,   136,
     120,   121,   122,   123,     0,   124,   125,   126,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,   129,   130,   131,   132,     0,     0,     0,     0,   133,
     292,   134,   135,   136,     0,   120,   121,   122,   123,     0,
     124,   125,   126,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   127,   128,   129,   130,   131,   132,
       0,     0,     0,     0,   133,     0,   134,   135,   136,   120,
     121,   122,   123,     0,   124,   125,   126,     0,   164,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,   133,     0,
     134,   135,   136,   120,   121,   122,   123,     0,   124,   125,
     126,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,   129,   130,   131,   132,     0,   171,
       0,     0,   133,     0,   134,   135,   136,   120,   121,   122,
     123,     0,   124,   125,   126,     0,   246,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,     0,     0,     0,     0,   133,     0,   134,   135,
     136,   120,   121,   122,   123,     0,   124,   125,   126,     0,
     293,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,     0,     0,     0,     0,
     133,     0,   134,   135,   136,   120,   121,   122,   123,     0,
     124,   125,   126,     0,     0,     0,   294,     0,     0,     0,
       0,     0,     0,     0,   127,   128,   129,   130,   131,   132,
       0,     0,     0,     0,   133,     0,   134,   135,   136,   120,
     121,   122,   123,     0,   124,   125,   126,     0,     0,     0,
       0,     0,     0,   393,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,   133,     0,
     134,   135,   136,   120,   121,   122,   123,     0,   124,   125,
     126,     0,     0,     0,     0,     0,   394,     0,     0,     0,
       0,     0,   127,   128,   129,   130,   131,   132,     0,     0,
       0,     0,   133,     0,   134,   135,   136,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,     0,     0,     0,     0,   133,     0,   134,   135,
     136,   120,   121,   122,     0,     0,   124,   125,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,     0,     0,     0,     0,
       0,     0,   134,   135,   136,   120,     0,   122,     0,     0,
     124,   125,   126,     0,     0,     0,   124,   125,   126,     0,
       0,     0,     0,     0,   127,   128,   129,   130,   131,   132,
     127,   128,   129,   130,   131,   132,   134,   135,   136,     0,
       0,     0,   134,   135,   136
  };

  const short int
  Parser::yycheck_[] =
  {
      10,    35,    36,     0,    38,     5,    87,     4,     1,    46,
      18,    83,     3,    32,     0,    44,     1,    18,    43,    44,
       1,   153,   154,   155,    21,    18,    18,    37,    18,   149,
      30,    47,    42,    18,    63,    45,    46,    18,    18,     3,
      48,    43,   260,    51,    63,    46,    51,    45,    18,    44,
     268,   269,    44,    46,    43,    46,    54,   189,     2,    51,
       1,    46,    64,     4,     5,     6,     7,     8,     9,   189,
      78,    51,    16,    17,    18,    19,    20,    78,    49,    54,
      45,    56,    46,    54,   216,    78,    78,   219,    78,    54,
      34,    35,    36,    78,    38,   215,    47,    78,    78,    47,
     100,    45,   139,    47,    74,    46,    54,    47,    78,   241,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   208,   200,   139,
      44,   251,    43,   143,     0,     1,    45,    15,     4,     5,
       6,     7,     8,     9,    50,    54,   156,    50,   158,   159,
     160,   161,   149,   163,   286,   287,   100,   167,    43,    18,
     170,   171,    18,   295,     4,     5,     6,     7,     8,     9,
      48,    41,    42,    55,    57,    18,   296,    45,    54,    61,
      46,    64,    57,    58,    59,    60,    50,    57,    58,    59,
      60,    64,    47,   218,   138,    64,    49,   207,   142,   143,
      54,   333,    48,   335,    45,   149,    46,    45,    60,    57,
      54,    43,    54,    64,    64,   215,    63,    66,    43,    64,
     217,    13,   166,    43,    15,    18,    49,    11,   262,   263,
     264,    18,   242,    45,   259,   260,    71,    45,    48,    48,
     265,    10,    56,   268,   269,   189,    25,    48,    50,    49,
      21,    50,    49,    30,   251,   305,   266,   267,   258,   137,
     379,   138,   166,   241,   241,    91,   208,   382,   251,   100,
      -1,   215,    -1,   217,    -1,   153,   154,   155,   288,   289,
     290,   291,   292,    -1,   309,    -1,   311,    -1,    -1,    -1,
      -1,   301,    -1,   303,   319,    -1,   321,    -1,   323,    -1,
      -1,   382,    -1,    -1,    -1,    -1,    -1,   251,   305,    -1,
      -1,   189,   322,    -1,   258,    -1,    -1,    -1,   262,   263,
     264,    -1,   347,    -1,    -1,   218,    -1,    -1,    -1,    -1,
     218,    -1,    -1,    -1,   344,   345,   346,    -1,   216,    -1,
      -1,   219,    -1,    -1,    -1,   370,   371,    -1,   373,   374,
      -1,    -1,   296,    -1,    -1,   365,   366,    -1,    -1,    -1,
     218,   305,   372,   241,   389,   390,   259,   260,   393,   379,
      -1,   396,   265,    36,    -1,   268,   269,   265,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,   259,   260,    -1,    67,    68,    69,   265,   286,   287,
     268,   269,    -1,    -1,    -1,    -1,   309,   295,   311,    -1,
      -1,   309,    -1,   311,    -1,    -1,   319,    -1,   321,    -1,
     323,   319,    -1,   321,    -1,   323,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   309,    -1,   311,   347,   333,    -1,   335,    -1,   347,
      -1,   319,    -1,   321,    -1,   323,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   370,   371,    -1,
     373,   374,   370,   371,    -1,   373,   374,    -1,    -1,   347,
      -1,    -1,    -1,    -1,    -1,    -1,   389,   390,    -1,    -1,
     393,   389,   390,   396,    -1,   393,    41,    42,   396,    -1,
      -1,    -1,   370,   371,    -1,   373,   374,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,     1,    -1,    -1,    -1,
      -1,   389,   390,    68,    69,   393,    -1,    12,   396,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    44,
      -1,    46,    -1,    48,    -1,    -1,    51,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    70,    -1,    72,    73,    74,
      75,    76,    77,    78,    12,    -1,    14,    -1,    16,    17,
      18,    19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    44,    -1,    46,    -1,
      48,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    70,    -1,    72,    73,    74,    75,    76,    77,
      78,    12,    -1,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    44,    -1,    46,    -1,    48,    -1,    -1,
      51,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    70,
      -1,    72,    73,    74,    75,    76,    77,    78,    12,    -1,
      14,    -1,    16,    17,    18,    19,    20,    21,    -1,    23,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      44,    -1,    46,    -1,    48,    -1,    -1,    51,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,
      74,    75,    76,    77,    78,    17,    18,    19,    20,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    30,    -1,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    17,    18,    19,
      20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    17,
      18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    -1,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,    -1,
      46,    -1,    -1,    -1,    -1,    51,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    12,    13,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    44,    -1,    46,    -1,    48,
      -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    72,    73,    74,    75,    76,    77,    78,
      12,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    44,    -1,    46,    -1,    48,    -1,    -1,    51,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      72,    73,    74,    75,    76,    77,    78,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    44,
      -1,    46,    -1,    48,    49,    -1,    51,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,
      75,    76,    77,    78,    12,    -1,    14,    -1,    16,    17,
      18,    19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    44,    -1,    46,    -1,
      48,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    12,    -1,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    44,    -1,    46,    -1,    48,    -1,    -1,
      51,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    72,    73,    74,    75,    76,    77,    78,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,
      -1,    30,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,
      49,    -1,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    -1,    44,    -1,    46,
      -1,    -1,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    17,    18,    19,    20,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    18,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      -1,    46,    33,    34,    35,    -1,    51,    -1,    53,    -1,
      41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,
      51,    -1,    53,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,
      -1,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
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
      -1,    -1,    55,    56,    57,    58,    59,    60,    22,    -1,
      -1,    -1,    65,    -1,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    24,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    24,    -1,    -1,    -1,    65,    -1,
      67,    68,    69,    -1,    -1,    -1,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    25,    -1,    -1,    -1,    65,    -1,    67,    68,    69,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    27,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    -1,    -1,    29,    -1,    65,    -1,    67,    68,    69,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      31,    67,    68,    69,    -1,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    -1,
      67,    68,    69,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,    -1,    65,    -1,    67,    68,    69,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    -1,    67,    68,
      69,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      65,    -1,    67,    68,    69,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    -1,
      67,    68,    69,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    65,    -1,    67,    68,    69,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    -1,    67,    68,
      69,    36,    37,    38,    -1,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    36,    -1,    38,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      55,    56,    57,    58,    59,    60,    67,    68,    69,    -1,
      -1,    -1,    67,    68,    69
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    46,    85,    86,   170,   171,     1,    18,    78,
     162,   172,   173,     0,     1,     4,     5,     6,     7,     8,
       9,    87,    88,    89,    90,    91,    92,    93,    94,    97,
     170,     3,   171,    47,    17,    19,    20,    23,    30,    33,
      34,    35,    40,    41,    42,    44,    46,    51,    53,    72,
      73,    74,    75,    76,    77,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   162,   163,   164,    47,    47,    48,   163,   162,
     162,   162,   162,   162,    88,    89,   162,   165,   167,   168,
     170,   168,   168,   114,   168,   114,   115,   115,     1,   113,
     114,   141,   142,   162,     1,    47,   113,   114,   162,   163,
      36,    37,    38,    39,    41,    42,    43,    55,    56,    57,
      58,    59,    60,    65,    67,    68,    69,    32,    63,    44,
     152,   152,    51,    44,   114,   139,   159,   160,   161,    44,
     156,    43,   156,    43,    50,    50,    43,   165,    18,    18,
      24,    18,    45,    54,    45,    45,    54,    50,    47,    47,
      54,    62,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,    44,
     144,   145,   146,   147,   148,   149,   150,   151,   163,   131,
     162,     1,    45,   113,   114,   162,   114,    64,    54,    49,
       1,   155,   162,   167,   169,   170,    64,    48,    43,    64,
     144,   144,   153,   154,   144,   114,   114,   114,   114,   114,
     114,   142,   162,   114,   114,   114,   143,   144,   162,   166,
     167,    55,    61,   152,    45,    45,    45,   114,   160,    45,
      45,    54,   167,   144,     1,    95,    96,   162,   170,    12,
      14,    16,    17,    19,    20,    21,    23,    26,    48,    70,
      98,   100,   101,   102,   105,   106,   107,   108,   109,   110,
     111,   112,   115,   117,   118,   144,    57,    64,    18,    29,
      22,    25,    31,    45,    47,    54,    54,   143,   144,   154,
     114,    64,   169,    43,    49,    54,   162,     1,    98,    99,
       1,    99,   168,   168,   168,    98,   114,   114,     1,    99,
       1,    99,    66,    43,   144,   144,   114,   114,   114,   114,
     114,   144,   167,    54,    56,    64,   114,   114,    95,    13,
      13,    98,    15,    15,    43,    18,    18,    24,    27,    49,
      49,    71,    71,   114,    98,    11,   157,    45,    45,   144,
     144,   114,   114,   114,    98,    48,    48,    10,   158,    56,
      18,    22,    31,    22,    25,     1,    28,    52,   103,   104,
     114,   114,    48,    98,    98,   114,    98,    98,    49,    50,
      50,    49,   103,    50,    49,   161,    22,    98,    98,    98,
      49,    98
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
     109,   110,   110,   110,   110,   111,   112,   113,   113,   114,
     114,   114,   114,   114,   114,   114,   114,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   117,   117,   117,   118,   118,   119,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   129,
     130,   130,   131,   132,   133,   134,   134,   135,   136,   137,
     137,   137,   138,   139,   140,   141,   141,   142,   143,   143,
     144,   144,   144,   144,   144,   145,   146,   146,   147,   148,
     149,   150,   151,   152,   152,   152,   153,   153,   154,   154,
     155,   155,   156,   156,   156,   157,   157,   158,   158,   159,
     159,   160,   160,   160,   161,   161,   162,   162,   163,   163,
     164,   164,   165,   165,   166,   166,   167,   168,   168,   169,
     169,   170,   170,   171,   171,   171,   172,   173
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
       3,     3,     3,     3,     3,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     1,
       1,     1,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     1,     1,     1,     1,     2,     3,     4,     3,
       2,     3,     6,     6,     6,     6,     6,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       3,     3,     5,     5,     3,     3,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     5,
       4,     6,     3,     3,     3,     2,     3,     1,     1,     0,
       3,     1,     3,     3,     0,     4,     0,     4,     0,     3,
       1,     1,     5,     3,     1,     0,     1,     1,     1,     2,
       3,     1,     1,     1,     3,     1,     3,     2,     1,     2,
       1,     2,     1,     3,     3,     3,     1,     2
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
  "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "CALL", "UPLUS",
  "UMINUS", "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header",
  "Definitions", "AttributedDefinition", "Definition",
  "EnumerationDefinition", "DerivedDefinition", "RuleDefinition",
  "FunctionDefinition", "ProgramFunctionDefinition",
  "EnumeratorDefinition", "Enumerators", "UsingDefinition", "Rule",
  "Rules", "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel",
  "CaseLabels", "LetRule", "ForallRule", "ChooseRule", "IterateRule",
  "BlockRule", "SequenceRule", "UpdateRule", "CallRule", "Terms", "Term",
  "SimpleOrClaspedTerm", "OperatorExpression", "CallExpression",
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
       0,   394,   394,   403,   409,   417,   423,   433,   439,   443,
     451,   455,   459,   463,   467,   475,   483,   491,   496,   505,
     521,   529,   552,   570,   574,   580,   588,   594,   604,   616,
     620,   624,   628,   632,   636,   640,   644,   648,   652,   656,
     664,   670,   680,   688,   692,   700,   704,   712,   716,   720,
     728,   734,   744,   752,   756,   764,   772,   780,   784,   788,
     793,   802,   806,   810,   815,   824,   834,   846,   852,   862,
     866,   870,   874,   878,   882,   886,   890,   898,   902,   906,
     910,   914,   918,   922,   934,   938,   942,   946,   950,   954,
     958,   962,   966,   970,   974,   978,   982,   986,   990,   994,
     998,  1002,  1010,  1014,  1018,  1026,  1031,  1039,  1044,  1052,
    1060,  1068,  1076,  1084,  1092,  1100,  1108,  1120,  1124,  1128,
    1132,  1136,  1140,  1144,  1148,  1152,  1156,  1160,  1164,  1172,
    1180,  1185,  1194,  1210,  1226,  1242,  1254,  1270,  1286,  1294,
    1299,  1303,  1311,  1318,  1326,  1333,  1339,  1348,  1360,  1366,
    1376,  1380,  1384,  1388,  1392,  1400,  1408,  1412,  1419,  1429,
    1449,  1457,  1465,  1477,  1481,  1485,  1499,  1505,  1515,  1519,
    1527,  1533,  1543,  1547,  1551,  1563,  1567,  1575,  1579,  1587,
    1593,  1603,  1611,  1621,  1632,  1636,  1648,  1652,  1660,  1664,
    1674,  1680,  1694,  1698,  1707,  1713,  1723,  1731,  1737,  1745,
    1751,  1762,  1768,  1778,  1782,  1786,  1794,  1802
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
#line 4400 "GrammarParser.cpp" // lalr1.cc:1167
#line 1808 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
