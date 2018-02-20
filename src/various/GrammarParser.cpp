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
#line 88 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

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
      case 173: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 172: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 174: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 146: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 110: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 118: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case 113: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 104: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 103: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 105: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 126: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 108: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 147: // ComposedType
      case 148: // TupleType
      case 149: // RecordType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 125: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 102: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 89: // AttributedDefinition
      case 90: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 88: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 119: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 91: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 96: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 97: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 128: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 115: // Term
      case 116: // SimpleOrClaspedTerm
      case 117: // OperatorExpression
      case 158: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 175: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 114: // Terms
      case 153: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 152: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 107: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 94: // FunctionDefinition
      case 95: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 87: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 163: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 164: // IdentifierPath
      case 165: // AbsoluteIdentifierPath
      case 166: // RelativeIdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 122: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 109: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 124: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 106: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 138: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 129: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 121: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 120: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 143: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 142: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 139: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 141: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 137: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 151: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 99: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 93: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 100: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 111: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 101: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 86: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 150: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 140: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 123: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 144: // Types
      case 154: // FunctionParameters
      case 155: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 130: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 127: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 112: // UpdateRule
      case 161: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 159: // MaybeInitially
      case 160: // Initializers
      case 162: // MaybeInitializers
        value.move< UpdateRules::Ptr > (that.value);
        break;

      case 98: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 131: // BooleanLiteral
      case 132: // IntegerLiteral
      case 133: // RationalLiteral
      case 134: // DecimalLiteral
      case 135: // BinaryLiteral
      case 136: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 167: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 156: // Parameters
      case 157: // MaybeParameters
      case 168: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 145: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
      case 78: // "absoluteIdentifierPath"
      case 79: // "relativeIdentifierPath"
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
      case 173: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 172: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 174: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 146: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 110: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 118: // CallExpression
        value.copy< CallExpression::Ptr > (that.value);
        break;

      case 113: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 104: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 103: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 105: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 126: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 108: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 147: // ComposedType
      case 148: // TupleType
      case 149: // RecordType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 125: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 102: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 89: // AttributedDefinition
      case 90: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 88: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 119: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 91: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 96: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 97: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 128: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 115: // Term
      case 116: // SimpleOrClaspedTerm
      case 117: // OperatorExpression
      case 158: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 175: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 114: // Terms
      case 153: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 152: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 107: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 94: // FunctionDefinition
      case 95: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 87: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 163: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 164: // IdentifierPath
      case 165: // AbsoluteIdentifierPath
      case 166: // RelativeIdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 122: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 109: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 124: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 106: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 138: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 129: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 121: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 120: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 143: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 142: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 139: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 141: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 137: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 151: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 99: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 93: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 100: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 111: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 101: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 86: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 150: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 140: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 123: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 144: // Types
      case 154: // FunctionParameters
      case 155: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 130: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 127: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 112: // UpdateRule
      case 161: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 159: // MaybeInitially
      case 160: // Initializers
      case 162: // MaybeInitializers
        value.copy< UpdateRules::Ptr > (that.value);
        break;

      case 98: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 131: // BooleanLiteral
      case 132: // IntegerLiteral
      case 133: // RationalLiteral
      case 134: // DecimalLiteral
      case 135: // BinaryLiteral
      case 136: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 167: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 156: // Parameters
      case 157: // MaybeParameters
      case 168: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 145: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
      case 78: // "absoluteIdentifierPath"
      case 79: // "relativeIdentifierPath"
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
      case 173: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 172: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 174: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 146: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 110: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 118: // CallExpression
        yylhs.value.build< CallExpression::Ptr > ();
        break;

      case 113: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 104: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 103: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 105: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 126: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 108: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 147: // ComposedType
      case 148: // TupleType
      case 149: // RecordType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 125: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 102: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 89: // AttributedDefinition
      case 90: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 88: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 92: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 119: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 91: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 96: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 97: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 128: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 115: // Term
      case 116: // SimpleOrClaspedTerm
      case 117: // OperatorExpression
      case 158: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 175: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 114: // Terms
      case 153: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 152: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 107: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 94: // FunctionDefinition
      case 95: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 87: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 163: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 164: // IdentifierPath
      case 165: // AbsoluteIdentifierPath
      case 166: // RelativeIdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 122: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 109: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 124: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 106: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 138: // ListLiteral
        yylhs.value.build< ListLiteral::Ptr > ();
        break;

      case 129: // Literal
        yylhs.value.build< Literal::Ptr > ();
        break;

      case 121: // LiteralCallExpression
        yylhs.value.build< LiteralCallExpression::Ptr > ();
        break;

      case 120: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 143: // Assignment
        yylhs.value.build< NamedExpression::Ptr > ();
        break;

      case 142: // Assignments
        yylhs.value.build< NamedExpressions::Ptr > ();
        break;

      case 139: // RangeLiteral
        yylhs.value.build< RangeLiteral::Ptr > ();
        break;

      case 141: // RecordLiteral
        yylhs.value.build< RecordLiteral::Ptr > ();
        break;

      case 137: // ReferenceLiteral
        yylhs.value.build< ReferenceLiteral::Ptr > ();
        break;

      case 151: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 99: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 93: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 100: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 111: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 101: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 86: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 150: // TemplateType
        yylhs.value.build< TemplateType::Ptr > ();
        break;

      case 140: // TupleLiteral
        yylhs.value.build< TupleLiteral::Ptr > ();
        break;

      case 123: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 144: // Types
      case 154: // FunctionParameters
      case 155: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 130: // UndefinedLiteral
        yylhs.value.build< UndefLiteral::Ptr > ();
        break;

      case 127: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 112: // UpdateRule
      case 161: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 159: // MaybeInitially
      case 160: // Initializers
      case 162: // MaybeInitializers
        yylhs.value.build< UpdateRules::Ptr > ();
        break;

      case 98: // UsingDefinition
        yylhs.value.build< UsingDefinition::Ptr > ();
        break;

      case 131: // BooleanLiteral
      case 132: // IntegerLiteral
      case 133: // RationalLiteral
      case 134: // DecimalLiteral
      case 135: // BinaryLiteral
      case 136: // StringLiteral
        yylhs.value.build< ValueLiteral::Ptr > ();
        break;

      case 167: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 156: // Parameters
      case 157: // MaybeParameters
      case 168: // TypedVariables
        yylhs.value.build< VariableDefinitions::Ptr > ();
        break;

      case 145: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
      case 78: // "absoluteIdentifierPath"
      case 79: // "relativeIdentifierPath"
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

      const auto ruleReference = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );

      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 552 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1698 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1706 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 580 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 588 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1734 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1744 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 604 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1760 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1768 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1776 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 628 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1784 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 636 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1800 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 640 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1808 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 644 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1816 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 648 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1824 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 652 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1832 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 656 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1840 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 670 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1860 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 680 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1868 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 700 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1908 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 716 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1916 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1924 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1934 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1944 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 744 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1952 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 752 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1960 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1968 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 784 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2000 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2009 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 793 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2018 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 802 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2026 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 806 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2034 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 810 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2043 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 815 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2052 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 824 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2060 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< CallExpression::Ptr > () );
  }
#line 2068 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 844 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 850 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 860 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 864 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2104 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 868 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2112 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 872 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2120 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 876 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2128 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 880 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2136 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 884 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2144 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 888 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 896 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 900 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 904 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< CallExpression::Ptr > ();
  }
#line 2176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 908 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LiteralCallExpression::Ptr > ();
  }
#line 2184 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 912 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Literal::Ptr > ();
  }
#line 2192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2200 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 920 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2224 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 940 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2232 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 944 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2240 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2248 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 952 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2256 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2264 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 964 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2280 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2312 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 984 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 988 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 992 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 996 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1000 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1008 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1012 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1016 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2385 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1037 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1042 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1050 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< ValueLiteral::Ptr > () );
  }
#line 2418 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< CallExpression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2426 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2434 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2458 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2466 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2474 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1118 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< UndefLiteral::Ptr > ();
  }
#line 2482 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1122 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2490 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1126 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2498 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1130 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2506 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2530 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1146 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ReferenceLiteral::Ptr > ();
  }
#line 2538 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ListLiteral::Ptr > ();
  }
#line 2546 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RangeLiteral::Ptr > ();
  }
#line 2554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1158 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< TupleLiteral::Ptr > ();
  }
#line 2562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1162 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RecordLiteral::Ptr > ();
  }
#line 2570 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1170 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 2578 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1178 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
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
#line 2612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
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
#line 2628 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
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
#line 2644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
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
#line 2660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
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
#line 2676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
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
#line 2692 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1284 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2700 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1292 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
  }
#line 2709 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1297 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1301 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = nullptr;
  }
#line 2725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1309 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1316 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
  }
#line 2743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1324 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as< NamedExpressions::Ptr > () );
  }
#line 2751 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1331 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = yystack_[2].value.as< NamedExpressions::Ptr > ();
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1337 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1364 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2799 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< TemplateType::Ptr > ();
  }
#line 2823 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1386 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2847 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2855 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2863 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Tuple" );
      auto subTypes = yystack_[3].value.as< Types::Ptr > ();
      subTypes->add( yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes );
  }
#line 2874 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
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
#line 2894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2902 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2910 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1463 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2918 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1475 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2926 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2934 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1483 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2943 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1503 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2963 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2971 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1517 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2979 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1525 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 2989 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 2999 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = yystack_[1].value.as< VariableDefinitions::Ptr > ();
  }
#line 3007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = nullptr;
  }
#line 3015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1549 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 3023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 3031 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 3039 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[1].value.as< UpdateRules::Ptr > ();
  }
#line 3047 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3055 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< UpdateRules::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3075 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1601 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3086 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3099 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< TupleLiteral::Ptr > ()->expressions() );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3109 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1627 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[0].value.as< UpdateRules::Ptr > ();
  }
#line 3117 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1631 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3125 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1643 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 3133 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1647 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 3141 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1655 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = yystack_[0].value.as< IdentifierPath::Ptr > ();
  }
#line 3149 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1659 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = yystack_[0].value.as< IdentifierPath::Ptr > ();
  }
#line 3157 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1667 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, GrammarParser::parseIdentifierPath( yylhs.location, yystack_[0].value.as< std::string > () ), IdentifierPath::Type::ABSOLUTE );
  }
#line 3165 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = asIdentifierPath( yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3173 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1679 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, GrammarParser::parseIdentifierPath( yylhs.location, yystack_[0].value.as< std::string > () ), IdentifierPath::Type::RELATIVE );
  }
#line 3181 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3189 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1695 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 3198 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3218 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3226 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3236 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3244 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1742 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3254 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3262 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1759 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[1].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1765 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1775 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< BasicAttribute::Ptr > ();
  }
#line 3290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1779 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3298 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1783 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = nullptr;
  }
#line 3306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1791 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1799 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -198;

  const short int Parser::yytable_ninf_ = -168;

  const short int
  Parser::yypact_[] =
  {
      55,  -198,    11,    22,    90,    86,  -198,   -22,  -198,  -198,
    1447,    -9,    -7,  -198,  -198,    -2,    15,    15,    15,    15,
      15,    59,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
     133,  -198,  -198,  -198,    -5,    -5,    -5,  1447,    -5,  -198,
    -198,  -198,  1447,  1524,  1524,   981,   855,     2,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  2228,   -15,  -198,     7,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,     7,  -198,  -198,  -198,  -198,  1510,
    -198,     9,    12,     9,    26,    24,  -198,  -198,    53,  -198,
    -198,    65,    -5,    34,   116,  1793,   117,  -198,  -198,  -198,
      98,    91,  1997,    -8,  -198,    95,   115,  -198,   112,  2030,
    -198,  1447,  1447,  1447,  1447,  1447,  1447,  1447,  1447,  1447,
    1447,  1447,  1447,  1447,  1447,  1447,  1447,  1447,     5,    13,
     918,  -198,  -198,   981,  2228,   104,   105,  -198,   121,     8,
     110,   123,   -29,     5,     5,     5,  1447,  -198,  1447,  1447,
    1447,  1447,  -198,  1447,  -198,  -198,    15,  1447,  -198,  -198,
    1447,  1447,  2328,  2294,  2322,  2261,   188,   188,  2350,   153,
     153,   118,   118,   118,  -198,  2261,  2350,   153,   153,     5,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   109,  -198,
       7,   131,  -198,   102,  2228,  2063,  1447,  1510,  -198,   135,
     111,    53,  -198,  -198,    -5,     5,    10,  1321,     5,  -198,
    -198,   122,   119,  -198,  1572,  1930,  1681,  1864,  1964,  2096,
    -198,    95,  2228,  2228,  2129,   128,  -198,    53,   132,  -198,
       5,  1447,  -198,  -198,  -198,   130,  2228,  -198,  -198,  -198,
      -5,  -198,   148,  -198,  -198,    57,  -198,    -5,   522,   591,
    -198,    -5,    -5,    -5,  1321,  1447,  1447,   660,   729,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,   136,   -23,   137,   154,     5,     5,  1447,  1447,  1447,
    1447,  1447,  -198,  -198,     5,    15,   113,    -6,   144,  -198,
    1447,  -198,  1447,  -198,    10,  -198,   190,  -198,  1049,   198,
    1117,   173,   199,   200,  -198,  1829,  1897,   171,  1185,   152,
    1253,  1447,  1321,  -198,   213,  2228,  2228,  2228,  2228,  2228,
     180,   181,     5,  -198,     5,  2228,  2228,  -198,  -198,  -198,
    -198,  -198,  -198,  1447,  1447,  1447,  1321,   182,  -198,  -198,
    -198,  -198,  2228,  -198,   184,   226,  -198,  -198,  -198,   183,
    1605,  1643,  1719,   212,   792,  1447,   192,  -198,  -198,  1321,
    1321,  1447,  1321,  1321,   201,   191,   202,  -198,  1384,  2162,
    2195,  1510,  -198,  -198,  1757,  -198,  -198,  -198,  1321,  1321,
    -198,  -198,  1321,  -198,   205,  1321,  -198,  -198,  -198,  -198,
    -198
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   203,     0,   187,   186,
     207,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     6,     8,    10,    11,    12,    13,    20,    14,
       0,     3,   202,   206,     0,     0,     0,     0,     0,   129,
     131,   130,     0,     0,     0,     0,     0,     0,   135,   136,
     132,   133,   134,   137,   190,   192,   208,    69,    71,    79,
     102,   103,    80,   104,    70,    72,    73,    74,    75,    76,
      81,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   191,   105,   188,   189,   204,   205,   185,
      21,   174,     0,   174,     0,     0,     5,     7,   194,   199,
     193,     0,     0,     0,     0,     0,     0,   101,    82,    83,
       0,     0,    68,     0,   146,   191,     0,   139,     0,    68,
     138,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   106,     0,   181,   127,   184,   180,     0,     0,
       0,     0,     0,     0,   169,     0,     0,   198,     0,     0,
       0,     0,    78,     0,    77,   144,     0,     0,   141,   140,
       0,     0,    98,    96,    97,   100,    84,    85,    91,    92,
      93,    86,    87,    88,    89,    99,    90,    94,    95,     0,
     111,   150,   151,   156,   157,   152,   153,   154,   155,   109,
     107,     0,   165,     0,    68,    68,     0,     0,    22,     0,
       0,     0,   201,   171,     0,     0,     0,     0,     0,    28,
     167,   168,     0,   197,     0,     0,     0,     0,     0,    67,
     145,     0,   147,    67,     0,     0,   149,   191,     0,   196,
     169,     0,   108,   164,   163,    77,   183,   179,   173,   172,
       0,   200,     0,    25,    27,     0,    23,     0,     0,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,    17,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    66,   102,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   142,     0,     0,     0,   149,     0,   162,
       0,   170,     0,    15,     0,    24,     0,    41,     0,     0,
       0,     0,     0,     0,    56,     0,     0,     0,     0,     0,
       0,     0,     0,   166,   176,   112,   115,   114,   113,   116,
     148,   195,     0,   160,     0,   182,    16,    26,    64,    62,
      40,    60,    58,     0,     0,     0,     0,     0,    59,    57,
      63,    61,    65,    18,     0,   178,   158,   159,   148,     0,
       0,     0,     0,    43,     0,     0,     0,    19,   161,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
       0,   185,    52,    53,     0,    55,    44,    46,     0,     0,
      45,    50,     0,   175,     0,     0,    47,    48,    49,   177,
      54
  };

  const short int
  Parser::yypgoto_[] =
  {
    -198,  -198,  -198,  -198,   227,   219,  -198,  -198,  -198,  -198,
    -198,   -53,  -198,  -198,   108,  -197,  -198,  -198,  -198,  -120,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   -40,
     -10,   -25,  -198,   129,   140,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,   120,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,   -79,  -198,  -198,    94,    23,
    -111,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   -69,  -198,
      25,  -198,   169,  -198,  -198,  -198,    60,  -115,   170,    46,
    -198,  -198,   166,  -198,  -141,   -34,    19,     3,     0,  -198,
    -198
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,   254,   255,    29,   307,   308,   270,   271,   272,   377,
     378,   273,   274,   275,   276,   277,   278,   279,   280,   111,
     144,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,   113,   114,   235,
     190,   191,   192,   193,   194,   195,   196,   197,   141,   221,
     222,   210,   150,   355,   367,   146,   147,   148,    83,    84,
      85,    86,    99,   238,   100,   101,   213,   102,     6,    11,
      12
  };

  const short int
  Parser::yytable_[] =
  {
      56,   103,   104,     5,   106,    32,   118,    30,   212,   209,
     145,   253,     7,     8,   217,   142,     8,   138,   108,   109,
       8,   140,    13,     8,    30,    33,     8,   105,     8,     8,
      32,     8,   107,     8,   218,   112,   119,   165,    87,   -79,
      88,     2,   219,   220,   223,   166,    89,   139,   239,   189,
    -167,   140,   158,   149,     2,   151,     2,  -167,     1,    -2,
      14,    90,   310,    15,    16,    17,    18,    19,    20,   153,
     318,   320,     9,   251,   154,     9,    54,    55,   236,     9,
      54,    55,     9,    54,    55,     9,    50,     9,     9,    31,
       9,    14,     9,   120,    15,    16,    17,    18,    19,    20,
     203,     2,    32,   155,   252,     2,   303,   284,   156,   212,
     304,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   145,   297,
     204,   242,     2,   205,   159,   161,     2,    15,    16,    17,
      18,    19,    20,   162,   163,   167,   224,   244,   225,   226,
     227,   228,   214,   229,   331,   170,   249,   232,   207,   169,
     233,   234,   168,   240,   250,   170,   332,   206,   333,   241,
     208,   216,    10,   215,   323,   324,   243,   133,   285,     2,
     248,   294,   286,   330,   198,   295,    91,    92,    93,    94,
      95,   302,   281,   300,   125,   126,   246,   322,   139,   198,
     198,   198,   321,   338,    98,    98,    98,   334,    98,   130,
     131,   132,   133,   341,    32,   115,   343,   344,   345,   257,
     348,   358,   350,   359,   354,   356,   357,   311,   312,   313,
     364,   299,   365,   281,   281,   198,   366,   373,   368,   281,
     381,   388,   281,   281,   130,   131,   132,   133,    96,    97,
     387,   337,   389,   214,   399,   315,   316,    32,   391,   199,
     230,   198,   152,   296,   198,   298,   394,   247,   157,   301,
       0,     0,    98,     0,     0,     0,     0,   325,   326,   327,
     328,   329,     0,   281,     0,   281,   198,     0,     0,     0,
     335,     0,   336,   281,     0,   281,     0,   281,     0,     0,
       0,     0,   145,     0,     0,     0,     0,   257,     0,   200,
       0,   352,     0,   115,     0,     0,     0,     0,     0,   211,
       0,   281,     0,     0,     0,   269,     0,     0,     0,     0,
       0,   198,   198,   360,   361,   362,   231,     0,     0,     0,
     198,     0,     0,     0,   281,   281,   282,   281,   281,     0,
       0,     0,     0,     0,   379,   380,     0,   283,     0,   237,
       0,   384,     0,   281,   281,     0,     0,   281,   379,     0,
     281,     0,   314,     0,     0,     0,     0,     0,   198,     0,
     198,     0,     0,     0,   211,     0,   256,   282,   282,     0,
       0,     0,     0,   282,     0,     0,   282,   282,   283,   283,
       0,     0,     0,     0,   283,     0,     0,   283,   283,     0,
       0,     0,     0,     0,     0,     0,   340,     0,   340,     0,
     211,     0,     0,     0,     0,     0,   340,   305,   340,     0,
     353,    98,    98,    98,     0,     0,     0,   282,     0,   282,
       0,     0,     0,     0,     0,     0,     0,   282,   283,   282,
     283,   282,     0,     0,   363,     0,     0,     0,   283,     0,
     283,     0,   283,     0,     0,   211,     0,     0,     0,     0,
       0,     0,     0,     0,   256,   282,     0,   382,   383,     0,
     385,   386,     0,     0,     0,     0,   283,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   396,   397,   282,   282,
     398,   282,   282,   400,     0,     0,     0,     0,     0,   283,
     283,     0,   283,   283,     0,     0,     0,   282,   282,     0,
       0,   282,     0,   306,   282,     0,     0,     0,   283,   283,
       0,     0,   283,     0,   258,   283,   259,     0,   260,   261,
       8,   262,   263,   264,     0,   265,     0,     0,   266,     0,
       0,     0,     0,     0,     0,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     267,     0,     0,     0,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,   309,    48,    49,    50,    51,    52,    53,     9,
      54,    55,     0,   258,     0,   259,     0,   260,   261,     8,
     262,   263,   264,     0,   265,     0,     0,   266,     0,     0,
       0,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,     0,    43,    44,     0,    45,     0,    46,     0,   267,
       0,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     268,   317,    48,    49,    50,    51,    52,    53,     9,    54,
      55,     0,   258,     0,   259,     0,   260,   261,     8,   262,
     263,   264,     0,   265,     0,     0,   266,     0,     0,     0,
       0,     0,     0,    39,    40,    41,     0,     0,     0,     0,
       0,    43,    44,     0,    45,     0,    46,     0,   267,     0,
       0,     0,    47,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
     319,    48,    49,    50,    51,    52,    53,     9,    54,    55,
       0,   258,     0,   259,     0,   260,   261,     8,   262,   263,
     264,     0,   265,     0,     0,   266,     0,     0,     0,     0,
       0,     0,    39,    40,    41,     0,     0,     0,     0,     0,
      43,    44,     0,    45,     0,    46,     0,   267,     0,     0,
       0,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   374,     0,     0,     0,     0,   268,     0,
      48,    49,    50,    51,    52,    53,     9,    54,    55,    34,
       8,    35,    36,     0,     0,    37,     0,     0,     0,     0,
     375,     0,    38,     0,     0,    39,    40,    41,     0,     0,
       0,     0,    42,    43,    44,     0,    45,     0,    46,     0,
       0,     0,     0,   376,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,    48,    49,    50,    51,    52,    53,     9,
      54,    55,    34,     8,    35,    36,     0,     0,    37,     0,
       0,     0,     0,     0,     0,    38,     0,     0,    39,    40,
      41,     0,     0,     0,     0,    42,    43,    44,     0,    45,
       0,    46,   117,     0,     0,     0,     0,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
       0,     0,     0,     0,     0,     0,    48,    49,    50,    51,
      52,    53,     9,    54,    55,    34,     8,    35,    36,     0,
       0,    37,     0,     0,     0,     0,     0,     0,    38,     0,
       0,    39,    40,    41,     0,     0,     0,     0,    42,    43,
      44,     0,    45,   202,    46,     0,     0,     0,     0,     0,
      47,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,     0,     0,     0,     0,     0,     0,    48,
      49,    50,    51,    52,    53,     9,    54,    55,    34,     8,
      35,    36,     0,     0,    37,     0,     0,     0,     0,     0,
       0,    38,     0,     0,    39,    40,    41,     0,     0,     0,
       0,    42,    43,    44,     0,    45,     0,    46,     0,     0,
       0,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,    49,    50,    51,    52,    53,     9,    54,
      55,   258,   339,   259,     0,   260,   261,     8,   262,   263,
     264,     0,   265,     0,     0,   266,     0,     0,     0,     0,
       0,     0,    39,    40,    41,     0,     0,     0,     0,     0,
      43,    44,     0,    45,     0,    46,     0,   267,     0,     0,
       0,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   268,     0,
      48,    49,    50,    51,    52,    53,     9,    54,    55,   258,
       0,   259,   342,   260,   261,     8,   262,   263,   264,     0,
     265,     0,     0,   266,     0,     0,     0,     0,     0,     0,
      39,    40,    41,     0,     0,     0,     0,     0,    43,    44,
       0,    45,     0,    46,     0,   267,     0,     0,     0,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   268,     0,    48,    49,
      50,    51,    52,    53,     9,    54,    55,   258,     0,   259,
       0,   260,   261,     8,   262,   263,   264,     0,   265,     0,
       0,   266,     0,     0,     0,     0,     0,     0,    39,    40,
      41,     0,     0,     0,     0,     0,    43,    44,     0,    45,
       0,    46,     0,   267,   349,     0,     0,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   268,     0,    48,    49,    50,    51,
      52,    53,     9,    54,    55,   258,     0,   259,     0,   260,
     261,     8,   262,   263,   264,     0,   265,     0,     0,   266,
       0,     0,     0,     0,     0,     0,    39,    40,    41,     0,
       0,     0,     0,     0,    43,    44,     0,    45,     0,    46,
       0,   267,     0,     0,     0,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   268,   351,    48,    49,    50,    51,    52,    53,
       9,    54,    55,   258,     0,   259,     0,   260,   261,     8,
     262,   263,   264,     0,   265,     0,     0,   266,     0,     0,
       0,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,     0,    43,    44,     0,    45,     0,    46,     0,   267,
       0,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     268,     0,    48,    49,    50,    51,    52,    53,     9,    54,
      55,    34,     8,    35,    36,     0,     0,    37,     0,     0,
       0,     0,   375,     0,    38,     0,     0,    39,    40,    41,
       0,     0,     0,     0,    42,    43,    44,     0,    45,     0,
      46,     0,     0,   390,     0,   376,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,    51,    52,
      53,     9,    54,    55,    34,     8,    35,    36,     0,     0,
      37,     0,     0,     0,     0,     0,     0,    38,     0,     0,
      39,    40,    41,     0,     0,     0,     0,    42,    43,    44,
       0,    45,     0,    46,     0,     0,     0,     0,     0,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,    51,    52,    53,     9,    54,    55,    34,     8,    35,
      36,     0,     0,    37,     0,     0,     0,     0,     0,     0,
      38,     0,     8,    39,    40,    41,     0,     0,     0,     0,
      42,    43,    44,     0,   143,     0,    46,    39,    40,    41,
       0,     0,    47,     0,     0,    43,    44,     0,    45,     0,
      46,     0,     0,     0,     0,     0,    47,     0,     0,     0,
       0,    48,    49,    50,    51,    52,    53,     9,    54,    55,
     287,     0,     0,     0,     0,    48,    49,    50,    51,    52,
      53,     9,    54,    55,     0,     0,     0,     0,   121,   122,
     123,   124,     0,   125,   126,   127,     0,     0,     0,     0,
       0,     0,     0,   369,     0,     0,   128,   129,   130,   131,
     132,   133,     0,     0,     0,     0,   134,     0,   135,   136,
     137,   121,   122,   123,   124,     0,   125,   126,   127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     129,   130,   131,   132,   133,   370,     0,     0,     0,   134,
       0,   135,   136,   137,   371,     0,     0,     0,     0,   121,
     122,   123,   124,     0,   125,   126,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,   129,   130,
     131,   132,   133,   289,     0,     0,     0,   134,     0,   135,
     136,   137,     0,     0,     0,     0,     0,   121,   122,   123,
     124,     0,   125,   126,   127,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,   129,   130,   131,   132,
     133,   372,     0,     0,     0,   134,     0,   135,   136,   137,
       0,     0,     0,     0,     0,   121,   122,   123,   124,     0,
     125,   126,   127,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   128,   129,   130,   131,   132,   133,   395,
       0,     0,     0,   134,     0,   135,   136,   137,     0,     0,
       0,     0,     0,   121,   122,   123,   124,     0,   125,   126,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   128,   129,   130,   131,   132,   133,   160,     0,     0,
       0,   134,     0,   135,   136,   137,     0,     0,     0,   121,
     122,   123,   124,     0,   125,   126,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,   129,   130,
     131,   132,   133,   346,     0,     0,     0,   134,     0,   135,
     136,   137,     0,     0,     0,   121,   122,   123,   124,     0,
     125,   126,   127,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   128,   129,   130,   131,   132,   133,   290,
       0,     0,     0,   134,     0,   135,   136,   137,     0,     0,
     121,   122,   123,   124,     0,   125,   126,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   128,   129,
     130,   131,   132,   133,   347,     0,     0,     0,   134,     0,
     135,   136,   137,   121,   122,   123,   124,     0,   125,   126,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   128,   129,   130,   131,   132,   133,     0,     0,   288,
       0,   134,     0,   135,   136,   137,   121,   122,   123,   124,
       0,   125,   126,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,   291,   135,   136,   137,     0,
     121,   122,   123,   124,     0,   125,   126,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   128,   129,
     130,   131,   132,   133,     0,     0,     0,     0,   134,     0,
     135,   136,   137,   121,   122,   123,   124,     0,   125,   126,
     127,     0,   164,     0,     0,     0,     0,     0,     0,     0,
       0,   128,   129,   130,   131,   132,   133,     0,     0,     0,
       0,   134,     0,   135,   136,   137,   121,   122,   123,   124,
       0,   125,   126,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   128,   129,   130,   131,   132,   133,
       0,   171,     0,     0,   134,     0,   135,   136,   137,   121,
     122,   123,   124,     0,   125,   126,   127,     0,   245,     0,
       0,     0,     0,     0,     0,     0,     0,   128,   129,   130,
     131,   132,   133,     0,     0,     0,     0,   134,     0,   135,
     136,   137,   121,   122,   123,   124,     0,   125,   126,   127,
       0,   292,     0,     0,     0,     0,     0,     0,     0,     0,
     128,   129,   130,   131,   132,   133,     0,     0,     0,     0,
     134,     0,   135,   136,   137,   121,   122,   123,   124,     0,
     125,   126,   127,     0,     0,     0,   293,     0,     0,     0,
       0,     0,     0,   128,   129,   130,   131,   132,   133,     0,
       0,     0,     0,   134,     0,   135,   136,   137,   121,   122,
     123,   124,     0,   125,   126,   127,     0,     0,     0,     0,
       0,     0,   392,     0,     0,     0,   128,   129,   130,   131,
     132,   133,     0,     0,     0,     0,   134,     0,   135,   136,
     137,   121,   122,   123,   124,     0,   125,   126,   127,     0,
       0,     0,     0,     0,   393,     0,     0,     0,     0,   128,
     129,   130,   131,   132,   133,     0,     0,     0,     0,   134,
       0,   135,   136,   137,   121,   122,   123,   124,     0,   125,
     126,   127,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   128,   129,   130,   131,   132,   133,     0,     0,
       0,     0,   134,     0,   135,   136,   137,   121,   122,   123,
       0,     0,   125,   126,   127,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,   129,   130,   131,   132,
     133,     0,     0,     0,     0,     0,     0,   135,   136,   137,
     121,     0,   123,     0,     0,   125,   126,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   128,   129,
     130,   131,   132,   133,     0,     0,     0,     0,   121,     0,
     135,   136,   137,   125,   126,   127,     0,     0,     0,   125,
     126,   127,     0,     0,     0,     0,   128,   129,   130,   131,
     132,   133,   128,   129,   130,   131,   132,   133,   135,   136,
     137,   125,   126,     0,   135,   136,   137,     0,     0,     0,
       0,     0,     0,     0,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,     0,     0,     0,   136,   137
  };

  const short int
  Parser::yycheck_[] =
  {
      10,    35,    36,     0,    38,     5,    46,     4,   149,     1,
      89,     1,     1,    18,    43,    84,    18,    32,    43,    44,
      18,    44,     0,    18,    21,    47,    18,    37,    18,    18,
      30,    18,    42,    18,    63,    45,    46,    45,    47,    62,
      47,    46,   153,   154,   155,    53,    48,    62,   189,    44,
      56,    44,    18,    44,    46,    43,    46,    63,     3,     0,
       1,    15,   259,     4,     5,     6,     7,     8,     9,    43,
     267,   268,    77,   214,    50,    77,    78,    79,   189,    77,
      78,    79,    77,    78,    79,    77,    73,    77,    77,     3,
      77,     1,    77,    47,     4,     5,     6,     7,     8,     9,
     140,    46,   102,    50,   215,    46,    49,   218,    43,   250,
      53,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   207,   240,
     140,   200,    46,   143,    18,    18,    46,     4,     5,     6,
       7,     8,     9,    45,    53,    50,   156,    45,   158,   159,
     160,   161,   149,   163,   295,    53,    45,   167,    53,    47,
     170,   171,    47,    54,    53,    53,    53,    63,    55,    60,
      49,    48,     2,    63,   285,   286,    45,    59,    56,    46,
      45,    53,    63,   294,   138,    53,    16,    17,    18,    19,
      20,    43,   217,    63,    41,    42,   206,    43,    62,   153,
     154,   155,    65,    13,    34,    35,    36,    63,    38,    56,
      57,    58,    59,    15,   214,    45,    43,    18,    18,   216,
      49,   332,    70,   334,    11,    45,    45,   261,   262,   263,
      48,   241,    48,   258,   259,   189,    10,    25,    55,   264,
      48,    50,   267,   268,    56,    57,    58,    59,    21,    30,
      49,   304,    50,   250,    49,   265,   266,   257,   378,   139,
     166,   215,    93,   240,   218,   240,   381,   207,   102,   250,
      -1,    -1,   102,    -1,    -1,    -1,    -1,   287,   288,   289,
     290,   291,    -1,   308,    -1,   310,   240,    -1,    -1,    -1,
     300,    -1,   302,   318,    -1,   320,    -1,   322,    -1,    -1,
      -1,    -1,   381,    -1,    -1,    -1,    -1,   304,    -1,   139,
      -1,   321,    -1,   143,    -1,    -1,    -1,    -1,    -1,   149,
      -1,   346,    -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,
      -1,   285,   286,   343,   344,   345,   166,    -1,    -1,    -1,
     294,    -1,    -1,    -1,   369,   370,   217,   372,   373,    -1,
      -1,    -1,    -1,    -1,   364,   365,    -1,   217,    -1,   189,
      -1,   371,    -1,   388,   389,    -1,    -1,   392,   378,    -1,
     395,    -1,   264,    -1,    -1,    -1,    -1,    -1,   332,    -1,
     334,    -1,    -1,    -1,   214,    -1,   216,   258,   259,    -1,
      -1,    -1,    -1,   264,    -1,    -1,   267,   268,   258,   259,
      -1,    -1,    -1,    -1,   264,    -1,    -1,   267,   268,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   308,    -1,   310,    -1,
     250,    -1,    -1,    -1,    -1,    -1,   318,   257,   320,    -1,
     322,   261,   262,   263,    -1,    -1,    -1,   308,    -1,   310,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   318,   308,   320,
     310,   322,    -1,    -1,   346,    -1,    -1,    -1,   318,    -1,
     320,    -1,   322,    -1,    -1,   295,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   304,   346,    -1,   369,   370,    -1,
     372,   373,    -1,    -1,    -1,    -1,   346,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   388,   389,   369,   370,
     392,   372,   373,   395,    -1,    -1,    -1,    -1,    -1,   369,
     370,    -1,   372,   373,    -1,    -1,    -1,   388,   389,    -1,
      -1,   392,    -1,     1,   395,    -1,    -1,    -1,   388,   389,
      -1,    -1,   392,    -1,    12,   395,    14,    -1,    16,    17,
      18,    19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    44,    -1,    46,    -1,
      48,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,     1,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    -1,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    44,    -1,    46,    -1,    48,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,     1,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    12,    -1,    14,    -1,    16,    17,    18,    19,
      20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    -1,    48,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
       1,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      -1,    12,    -1,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    44,    -1,    46,    -1,    48,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    69,    -1,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    17,
      18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      28,    -1,    30,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    -1,    44,    -1,    46,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    17,    18,    19,    20,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      -1,    46,    47,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    17,    18,    19,    20,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    12,    13,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    44,    -1,    46,    -1,    48,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    44,    -1,    46,    -1,    48,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    44,
      -1,    46,    -1,    48,    49,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    12,    -1,    14,    -1,    16,
      17,    18,    19,    20,    21,    -1,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    44,    -1,    46,
      -1,    48,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    44,    -1,    46,    -1,    48,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    -1,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    28,    -1,    30,    -1,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,    -1,
      46,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    17,    18,    19,    20,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    17,    18,    19,
      20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    18,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    33,    34,    35,
      -1,    -1,    52,    -1,    -1,    41,    42,    -1,    44,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      18,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    64,    -1,    66,    67,
      68,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    22,    -1,    -1,    -1,    64,
      -1,    66,    67,    68,    31,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    22,    -1,    -1,    -1,    64,    -1,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    22,    -1,    -1,    -1,    64,    -1,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    22,
      -1,    -1,    -1,    64,    -1,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    24,    -1,    -1,
      -1,    64,    -1,    66,    67,    68,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    24,    -1,    -1,    -1,    64,    -1,    66,
      67,    68,    -1,    -1,    -1,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    25,
      -1,    -1,    -1,    64,    -1,    66,    67,    68,    -1,    -1,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    27,    -1,    -1,    -1,    64,    -1,
      66,    67,    68,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    29,
      -1,    64,    -1,    66,    67,    68,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    64,    31,    66,    67,    68,    -1,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    64,    -1,
      66,    67,    68,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    64,    -1,    66,    67,    68,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    61,    -1,    -1,    64,    -1,    66,    67,    68,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    64,    -1,    66,
      67,    68,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      64,    -1,    66,    67,    68,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    64,    -1,    66,    67,    68,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    64,    -1,    66,    67,
      68,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    64,
      -1,    66,    67,    68,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    64,    -1,    66,    67,    68,    36,    37,    38,
      -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,
      36,    -1,    38,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    36,    -1,
      66,    67,    68,    41,    42,    43,    -1,    -1,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    54,    55,    56,    57,    58,    59,    66,    67,
      68,    41,    42,    -1,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    46,    86,    87,   172,   173,     1,    18,    77,
     163,   174,   175,     0,     1,     4,     5,     6,     7,     8,
       9,    88,    89,    90,    91,    92,    93,    94,    95,    98,
     172,     3,   173,    47,    17,    19,    20,    23,    30,    33,
      34,    35,    40,    41,    42,    44,    46,    52,    71,    72,
      73,    74,    75,    76,    78,    79,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   163,   164,   165,   166,    47,    47,    48,
     164,   163,   163,   163,   163,   163,    89,    90,   163,   167,
     169,   170,   172,   170,   170,   115,   170,   115,   116,   116,
       1,   114,   115,   142,   143,   163,     1,    47,   114,   115,
     164,    36,    37,    38,    39,    41,    42,    43,    54,    55,
      56,    57,    58,    59,    64,    66,    67,    68,    32,    62,
      44,   153,   153,    44,   115,   140,   160,   161,   162,    44,
     157,    43,   157,    43,    50,    50,    43,   167,    18,    18,
      24,    18,    45,    53,    45,    45,    53,    50,    47,    47,
      53,    61,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,    44,
     145,   146,   147,   148,   149,   150,   151,   152,   164,   132,
     163,     1,    45,   114,   115,   115,    63,    53,    49,     1,
     156,   163,   169,   171,   172,    63,    48,    43,    63,   145,
     145,   154,   155,   145,   115,   115,   115,   115,   115,   115,
     143,   163,   115,   115,   115,   144,   145,   163,   168,   169,
      54,    60,   153,    45,    45,    45,   115,   161,    45,    45,
      53,   169,   145,     1,    96,    97,   163,   172,    12,    14,
      16,    17,    19,    20,    21,    23,    26,    48,    69,    99,
     101,   102,   103,   106,   107,   108,   109,   110,   111,   112,
     113,   116,   118,   119,   145,    56,    63,    18,    29,    22,
      25,    31,    45,    47,    53,    53,   144,   145,   155,   115,
      63,   171,    43,    49,    53,   163,     1,    99,   100,     1,
     100,   170,   170,   170,    99,   115,   115,     1,   100,     1,
     100,    65,    43,   145,   145,   115,   115,   115,   115,   115,
     145,   169,    53,    55,    63,   115,   115,    96,    13,    13,
      99,    15,    15,    43,    18,    18,    24,    27,    49,    49,
      70,    70,   115,    99,    11,   158,    45,    45,   145,   145,
     115,   115,   115,    99,    48,    48,    10,   159,    55,    18,
      22,    31,    22,    25,     1,    28,    51,   104,   105,   115,
     115,    48,    99,    99,   115,    99,    99,    49,    50,    50,
      49,   104,    50,    49,   162,    22,    99,    99,    99,    49,
      99
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    85,    86,    87,    87,    88,    88,    89,    89,    89,
      90,    90,    90,    90,    90,    91,    92,    93,    93,    94,
      94,    95,    95,    96,    96,    96,    97,    97,    98,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
     100,   100,   101,   102,   102,   103,   103,   104,   104,   104,
     105,   105,   106,   107,   107,   108,   109,   110,   110,   110,
     110,   111,   111,   111,   111,   112,   113,   114,   114,   115,
     115,   115,   115,   115,   115,   115,   115,   116,   116,   116,
     116,   116,   116,   116,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   118,   118,   118,   119,   119,   120,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   130,
     131,   131,   132,   133,   134,   135,   135,   136,   137,   138,
     138,   138,   139,   140,   141,   142,   142,   143,   144,   144,
     145,   145,   145,   145,   145,   146,   147,   147,   148,   149,
     150,   151,   152,   153,   153,   153,   154,   154,   155,   155,
     156,   156,   157,   157,   157,   158,   158,   159,   159,   160,
     160,   161,   161,   161,   162,   162,   163,   163,   164,   164,
     165,   165,   166,   167,   167,   168,   168,   169,   170,   170,
     171,   171,   172,   172,   173,   173,   173,   174,   175
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
       1,     1,     5,     3,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     2,     1,
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
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\":\"", "\"_\"",
  "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"", "\"^\"",
  "\"'\"", "\"..\"", "\".\"", "\"->\"", "\"=>\"", "\":=\"", "\"!=\"",
  "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"", "\"hexadecimal\"",
  "\"integer\"", "\"rational\"", "\"decimal\"", "\"string\"",
  "\"identifier\"", "\"absoluteIdentifierPath\"",
  "\"relativeIdentifierPath\"", "ABSOLUTE_PATH", "CALL", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header", "Definitions",
  "AttributedDefinition", "Definition", "EnumerationDefinition",
  "DerivedDefinition", "RuleDefinition", "FunctionDefinition",
  "ProgramFunctionDefinition", "EnumeratorDefinition", "Enumerators",
  "UsingDefinition", "Rule", "Rules", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabel", "CaseLabels", "LetRule", "ForallRule",
  "ChooseRule", "IterateRule", "BlockRule", "SequenceRule", "UpdateRule",
  "CallRule", "Terms", "Term", "SimpleOrClaspedTerm", "OperatorExpression",
  "CallExpression", "DirectCallExpression", "MethodCallExpression",
  "LiteralCallExpression", "IndirectCallExpression",
  "TypeCastingExpression", "LetExpression", "ConditionalExpression",
  "ChooseExpression", "UniversalQuantifierExpression",
  "ExistentialQuantifierExpression", "Literal", "UndefinedLiteral",
  "BooleanLiteral", "IntegerLiteral", "RationalLiteral", "DecimalLiteral",
  "BinaryLiteral", "StringLiteral", "ReferenceLiteral", "ListLiteral",
  "RangeLiteral", "TupleLiteral", "RecordLiteral", "Assignments",
  "Assignment", "Types", "Type", "BasicType", "ComposedType", "TupleType",
  "RecordType", "TemplateType", "RelationType", "FixedSizedType",
  "Arguments", "FunctionParameters", "MaybeFunctionParameters",
  "Parameters", "MaybeParameters", "MaybeDefined", "MaybeInitially",
  "Initializers", "Initializer", "MaybeInitializers", "Identifier",
  "IdentifierPath", "AbsoluteIdentifierPath", "RelativeIdentifierPath",
  "Variable", "TypedVariables", "TypedVariable", "AttributedVariable",
  "TypedAttributedVariable", "Attributes", "Attribute", "BasicAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   394,   394,   403,   409,   417,   423,   433,   439,   443,
     451,   455,   459,   463,   467,   475,   483,   491,   496,   505,
     521,   529,   551,   569,   573,   579,   587,   593,   603,   615,
     619,   623,   627,   631,   635,   639,   643,   647,   651,   655,
     663,   669,   679,   687,   691,   699,   703,   711,   715,   719,
     727,   733,   743,   751,   755,   763,   771,   779,   783,   787,
     792,   801,   805,   809,   814,   823,   831,   843,   849,   859,
     863,   867,   871,   875,   879,   883,   887,   895,   899,   903,
     907,   911,   915,   919,   931,   935,   939,   943,   947,   951,
     955,   959,   963,   967,   971,   975,   979,   983,   987,   991,
     995,   999,  1007,  1011,  1015,  1023,  1028,  1036,  1041,  1049,
    1057,  1065,  1073,  1081,  1089,  1097,  1105,  1117,  1121,  1125,
    1129,  1133,  1137,  1141,  1145,  1149,  1153,  1157,  1161,  1169,
    1177,  1182,  1191,  1207,  1223,  1239,  1251,  1267,  1283,  1291,
    1296,  1300,  1308,  1315,  1323,  1330,  1336,  1345,  1357,  1363,
    1373,  1377,  1381,  1385,  1389,  1397,  1405,  1409,  1416,  1426,
    1446,  1454,  1462,  1474,  1478,  1482,  1496,  1502,  1512,  1516,
    1524,  1530,  1540,  1544,  1548,  1560,  1564,  1572,  1576,  1584,
    1590,  1600,  1607,  1616,  1626,  1630,  1642,  1646,  1654,  1658,
    1666,  1670,  1678,  1690,  1694,  1703,  1709,  1719,  1727,  1733,
    1741,  1747,  1758,  1764,  1774,  1778,  1782,  1790,  1798
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
#line 4407 "GrammarParser.cpp" // lalr1.cc:1167
#line 1804 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
