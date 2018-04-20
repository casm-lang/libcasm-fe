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
      case 176: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 175: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 177: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 147: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 110: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 119: // CallExpression
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

      case 127: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 108: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 148: // ComposedType
      case 149: // TupleType
      case 150: // RecordType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 126: // ConditionalExpression
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

      case 120: // DirectCallExpression
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

      case 129: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 116: // Term
      case 117: // SimpleOrClaspedTerm
      case 118: // OperatorExpression
      case 159: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 178: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 115: // Terms
      case 154: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 153: // FixedSizedType
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

      case 164: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 165: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 166: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 123: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 109: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 125: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 106: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 139: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 130: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 122: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 121: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 144: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 143: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 140: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 142: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 138: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 152: // RelationType
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

      case 151: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 141: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 124: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 145: // Types
      case 155: // FunctionParameters
      case 156: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 131: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 128: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 112: // UpdateRule
      case 162: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 160: // MaybeInitially
      case 161: // Initializers
      case 163: // MaybeInitializers
        value.move< UpdateRules::Ptr > (that.value);
        break;

      case 98: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 132: // BooleanLiteral
      case 133: // IntegerLiteral
      case 134: // RationalLiteral
      case 135: // DecimalLiteral
      case 136: // BinaryLiteral
      case 137: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 173: // VariableBinding
        value.move< VariableBinding::Ptr > (that.value);
        break;

      case 174: // VariableBindings
        value.move< VariableBindings::Ptr > (that.value);
        break;

      case 167: // Variable
      case 170: // TypedVariable
      case 171: // AttributedVariable
      case 172: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 157: // Parameters
      case 158: // MaybeParameters
      case 168: // AttributedVariables
      case 169: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 114: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case 146: // Type
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
      case 176: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 175: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 177: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 147: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 110: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 119: // CallExpression
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

      case 127: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 108: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 148: // ComposedType
      case 149: // TupleType
      case 150: // RecordType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 126: // ConditionalExpression
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

      case 120: // DirectCallExpression
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

      case 129: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 116: // Term
      case 117: // SimpleOrClaspedTerm
      case 118: // OperatorExpression
      case 159: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 178: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 115: // Terms
      case 154: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 153: // FixedSizedType
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

      case 164: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 165: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 166: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 123: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 109: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 125: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 106: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 139: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 130: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 122: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 121: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 144: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 143: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 140: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 142: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 138: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 152: // RelationType
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

      case 151: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 141: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 124: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 145: // Types
      case 155: // FunctionParameters
      case 156: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 131: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 128: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 112: // UpdateRule
      case 162: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 160: // MaybeInitially
      case 161: // Initializers
      case 163: // MaybeInitializers
        value.copy< UpdateRules::Ptr > (that.value);
        break;

      case 98: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 132: // BooleanLiteral
      case 133: // IntegerLiteral
      case 134: // RationalLiteral
      case 135: // DecimalLiteral
      case 136: // BinaryLiteral
      case 137: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 173: // VariableBinding
        value.copy< VariableBinding::Ptr > (that.value);
        break;

      case 174: // VariableBindings
        value.copy< VariableBindings::Ptr > (that.value);
        break;

      case 167: // Variable
      case 170: // TypedVariable
      case 171: // AttributedVariable
      case 172: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 157: // Parameters
      case 158: // MaybeParameters
      case 168: // AttributedVariables
      case 169: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 114: // WhileRule
        value.copy< WhileRule::Ptr > (that.value);
        break;

      case 146: // Type
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
      case 176: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 175: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 177: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 147: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 110: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 119: // CallExpression
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

      case 127: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 108: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 148: // ComposedType
      case 149: // TupleType
      case 150: // RecordType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 126: // ConditionalExpression
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

      case 120: // DirectCallExpression
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

      case 129: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 116: // Term
      case 117: // SimpleOrClaspedTerm
      case 118: // OperatorExpression
      case 159: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 178: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 115: // Terms
      case 154: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 153: // FixedSizedType
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

      case 164: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 165: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 166: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 123: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 109: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 125: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 106: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 139: // ListLiteral
        yylhs.value.build< ListLiteral::Ptr > ();
        break;

      case 130: // Literal
        yylhs.value.build< Literal::Ptr > ();
        break;

      case 122: // LiteralCallExpression
        yylhs.value.build< LiteralCallExpression::Ptr > ();
        break;

      case 121: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 144: // Assignment
        yylhs.value.build< NamedExpression::Ptr > ();
        break;

      case 143: // Assignments
        yylhs.value.build< NamedExpressions::Ptr > ();
        break;

      case 140: // RangeLiteral
        yylhs.value.build< RangeLiteral::Ptr > ();
        break;

      case 142: // RecordLiteral
        yylhs.value.build< RecordLiteral::Ptr > ();
        break;

      case 138: // ReferenceLiteral
        yylhs.value.build< ReferenceLiteral::Ptr > ();
        break;

      case 152: // RelationType
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

      case 151: // TemplateType
        yylhs.value.build< TemplateType::Ptr > ();
        break;

      case 141: // TupleLiteral
        yylhs.value.build< TupleLiteral::Ptr > ();
        break;

      case 124: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 145: // Types
      case 155: // FunctionParameters
      case 156: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 131: // UndefinedLiteral
        yylhs.value.build< UndefLiteral::Ptr > ();
        break;

      case 128: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 112: // UpdateRule
      case 162: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 160: // MaybeInitially
      case 161: // Initializers
      case 163: // MaybeInitializers
        yylhs.value.build< UpdateRules::Ptr > ();
        break;

      case 98: // UsingDefinition
        yylhs.value.build< UsingDefinition::Ptr > ();
        break;

      case 132: // BooleanLiteral
      case 133: // IntegerLiteral
      case 134: // RationalLiteral
      case 135: // DecimalLiteral
      case 136: // BinaryLiteral
      case 137: // StringLiteral
        yylhs.value.build< ValueLiteral::Ptr > ();
        break;

      case 173: // VariableBinding
        yylhs.value.build< VariableBinding::Ptr > ();
        break;

      case 174: // VariableBindings
        yylhs.value.build< VariableBindings::Ptr > ();
        break;

      case 167: // Variable
      case 170: // TypedVariable
      case 171: // AttributedVariable
      case 172: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 157: // Parameters
      case 158: // MaybeParameters
      case 168: // AttributedVariables
      case 169: // TypedVariables
        yylhs.value.build< VariableDefinitions::Ptr > ();
        break;

      case 114: // WhileRule
        yylhs.value.build< WhileRule::Ptr > ();
        break;

      case 146: // Type
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
#line 399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1527 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 414 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 428 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1565 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1591 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 456 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 464 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 468 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< UsingDefinition::Ptr > ();
  }
#line 1631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 488 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 496 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< VariableDefinitions::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1656 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1665 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 510 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1685 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 526 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 534 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1719 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 556 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1745 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 584 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1763 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 598 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1783 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1791 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1799 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 628 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1823 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 636 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 640 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 644 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1847 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 648 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1855 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 652 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1863 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 656 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1871 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 660 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1879 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< WhileRule::Ptr > ();
  }
#line 1887 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 672 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 678 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1907 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1915 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 696 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1923 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 700 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1931 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 708 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1939 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1947 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1955 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 724 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1963 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1971 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 736 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1981 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 742 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1991 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 752 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[2].value.as< VariableBindings::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1999 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinitions::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2031 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2039 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 792 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2047 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2056 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 810 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 814 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2081 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 818 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2090 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 823 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2099 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2107 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 840 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< CallExpression::Ptr > () );
  }
#line 2115 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 848 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2123 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 860 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2133 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 866 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 876 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 880 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 884 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 888 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 892 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 896 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 900 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2199 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 904 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 912 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 920 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< CallExpression::Ptr > ();
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LiteralCallExpression::Ptr > ();
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Literal::Ptr > ();
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 952 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 964 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 984 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2343 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 988 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 992 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 996 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1000 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1004 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1008 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1012 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1016 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1028 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2440 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< ValueLiteral::Ptr > () );
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< CallExpression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[2].value.as< VariableBindings::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1114 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1122 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< UndefLiteral::Ptr > ();
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1146 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1158 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1162 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ReferenceLiteral::Ptr > ();
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1166 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ListLiteral::Ptr > ();
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1170 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RangeLiteral::Ptr > ();
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1174 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< TupleLiteral::Ptr > ();
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1178 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RecordLiteral::Ptr > ();
  }
#line 2625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1186 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 2633 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1194 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1208 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1224 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1240 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1256 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1268 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1284 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1300 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1308 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1313 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1317 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = nullptr;
  }
#line 2780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1325 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1332 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
  }
#line 2798 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1340 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as< NamedExpressions::Ptr > () );
  }
#line 2806 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1347 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = yystack_[2].value.as< NamedExpressions::Ptr > ();
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2816 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1353 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2826 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2834 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2844 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2854 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2862 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1394 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2870 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< TemplateType::Ptr > ();
  }
#line 2878 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1402 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1414 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2902 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2910 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2918 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1433 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Tuple" );
      auto subTypes = yystack_[3].value.as< Types::Ptr > ();
      subTypes->add( yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes );
  }
#line 2929 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1463 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1471 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2973 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1491 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2981 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1495 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2989 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2998 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 3008 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1519 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 3018 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1529 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 3026 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3034 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3044 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3054 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1557 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = yystack_[1].value.as< VariableDefinitions::Ptr > ();
  }
#line 3062 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = nullptr;
  }
#line 3070 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 3078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 3086 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 3094 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[1].value.as< UpdateRules::Ptr > ();
  }
#line 3102 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1593 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3110 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1601 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< UpdateRules::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3120 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1607 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3130 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3141 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3154 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< TupleLiteral::Ptr > ()->expressions() );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3164 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1643 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[0].value.as< UpdateRules::Ptr > ();
  }
#line 3172 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1647 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3180 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1659 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 3188 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1663 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 3196 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 3204 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1675 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 3214 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1685 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 3224 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 3234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1709 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 3251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      variables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = variables;
  }
#line 3261 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1724 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = variables;
  }
#line 3271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3281 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3291 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3299 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3309 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3317 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1786 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as< VariableDefinition::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3343 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1794 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variableBindings = yystack_[2].value.as< VariableBindings::Ptr > ();
      variableBindings->add( yystack_[0].value.as< VariableBinding::Ptr > () );
      yylhs.value.as< VariableBindings::Ptr > () = variableBindings;
  }
#line 3353 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1800 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as< VariableBinding::Ptr > () );
      yylhs.value.as< VariableBindings::Ptr > () = variableBindings;
  }
#line 3363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1814 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[1].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 1820 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 1830 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< BasicAttribute::Ptr > ();
  }
#line 3391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 1834 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 212:
#line 1838 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = nullptr;
  }
#line 3407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 213:
#line 1846 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 214:
#line 1854 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3423 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3427 "GrammarParser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -128;

  const short int Parser::yytable_ninf_ = -170;

  const short int
  Parser::yypact_[] =
  {
      34,  -128,    11,    21,    55,    35,  -128,   -17,  -128,  -128,
    1563,    -9,     5,  -128,  -128,    -5,     4,     4,     4,     4,
       4,   138,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,
     164,  -128,  -128,  -128,    -1,    -1,    -1,  1563,    -1,  -128,
    -128,  -128,  1563,   403,   403,  1097,   971,     4,    -4,  -128,
    -128,  -128,  -128,  -128,  -128,  2258,   -12,  -128,    24,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,    24,    18,  -128,  -128,  1626,  -128,    51,
      66,    51,    67,    61,  -128,  -128,    97,  -128,  -128,   108,
    -128,    12,    -1,    16,  -128,    31,  1808,    33,  -128,  -128,
    -128,   112,   120,  2020,    38,  -128,   125,   132,  -128,    49,
    2054,  -128,  -128,  1563,  1563,  1563,  1563,  1563,  1563,  1563,
    1563,  1563,  1563,  1563,  1563,  1563,  1563,  1563,  1563,  1563,
      -2,    -3,  1034,  -128,  -128,     4,  1097,  2258,   118,   129,
    -128,   136,     8,   122,   139,   -20,    -2,    -2,    -2,  1563,
    1563,    -1,  -128,  1563,    -1,  1563,  1563,  1563,  -128,  1563,
    -128,  -128,     4,  1563,  -128,  -128,  1563,  1563,  2327,  2292,
    2321,   282,   159,   159,   135,   155,   155,   140,   140,   140,
    -128,   282,   135,   155,   155,    -2,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,    79,  -128,    24,   154,  -128,    53,
    2258,  -128,  2088,  1563,  1626,  -128,   156,   119,    97,  -128,
    -128,    -1,    -2,    10,  1437,    -2,  -128,  -128,   151,   145,
    -128,  2258,  2258,  -128,  1952,  -128,  1650,  1883,  1986,  2122,
    -128,   125,  2258,  2258,  2156,   157,  -128,    97,   166,  -128,
      -2,  1563,  -128,  -128,  -128,   158,  2258,  -128,  -128,  -128,
      -1,  -128,   178,  -128,  -128,    30,  -128,    -1,   641,   709,
    -128,    -1,    -1,    -1,  1437,  1563,  1563,  1563,   777,   845,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,   162,    28,   161,   186,    -2,    -2,  1563,
    1563,  1563,  1563,  -128,  -128,    -2,     4,   107,    42,   167,
    -128,  1563,  -128,  1563,  -128,    10,  -128,   218,  -128,  1165,
     219,  1233,    36,    40,    48,  -128,  1846,  1918,  1690,   183,
    1301,   163,  1369,  1563,  1437,  -128,   225,  2258,  2258,  2258,
    2258,   193,   194,    -2,  -128,    -2,  2258,  2258,  -128,  -128,
    -128,  -128,  -128,  -128,  1437,  1563,  1563,  1437,   197,  1437,
    -128,  -128,  -128,  -128,  2258,  -128,   199,   232,  -128,  -128,
    -128,   195,  -128,   555,  1730,   226,   908,  -128,  1563,   201,
    -128,  -128,  1437,  1563,  1437,  1437,   205,   206,   207,  -128,
    1500,  2190,  2224,  1626,  -128,  1770,  -128,  -128,  -128,  1437,
    1437,  -128,  -128,  1437,  -128,   209,  1437,  -128,  -128,  -128,
    -128,  -128
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   209,     0,   189,   188,
     213,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     6,     8,    10,    11,    12,    13,    20,    14,
       0,     3,   208,   212,     0,     0,     0,     0,     0,   131,
     133,   132,     0,     0,     0,     0,     0,     0,     0,   137,
     138,   134,   135,   136,   139,   214,    71,    73,    81,   104,
     105,    82,   106,    72,    74,    75,    76,    77,    78,    83,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   193,   107,   190,   210,   211,   187,    21,   176,
       0,   176,     0,     0,     5,     7,   195,   202,   194,     0,
     207,     0,     0,     0,   197,     0,     0,     0,   103,    84,
      85,     0,     0,    70,     0,   148,   193,     0,   141,     0,
      70,   191,   140,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   108,     0,     0,   183,   129,   186,
     182,     0,     0,     0,     0,     0,     0,   171,     0,     0,
       0,     0,   201,     0,     0,     0,     0,     0,    80,     0,
      79,   146,     0,     0,   143,   142,     0,     0,   100,    98,
      99,   102,    86,    87,    93,    94,    95,    88,    89,    90,
      91,   101,    92,    96,    97,     0,   113,   152,   153,   158,
     159,   154,   155,   156,   157,   111,   109,     0,   167,     0,
      70,   192,    70,     0,     0,    22,     0,     0,     0,   204,
     173,     0,     0,     0,     0,     0,    28,   169,   170,     0,
     200,   205,   114,   206,     0,   196,     0,     0,     0,    69,
     147,     0,   149,    69,     0,     0,   151,   193,     0,   199,
     171,     0,   110,   166,   165,    79,   185,   181,   175,   174,
       0,   203,     0,    25,    27,     0,    23,     0,     0,     0,
      43,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    67,   104,     0,     0,     0,     0,
       0,     0,     0,   145,   144,     0,     0,     0,   151,     0,
     164,     0,   172,     0,    15,     0,    24,     0,    42,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   168,   178,   117,   116,   115,
     118,   150,   198,     0,   162,     0,   184,    16,    26,    65,
      63,    41,    61,    59,     0,     0,     0,     0,     0,     0,
      60,    58,    64,    62,    66,    18,     0,   180,   160,   161,
     150,     0,    53,     0,     0,    44,     0,    68,     0,     0,
      19,   163,     0,     0,     0,     0,     0,     0,     0,    52,
       0,     0,     0,   187,    54,     0,    56,    45,    47,     0,
       0,    46,    51,     0,   177,     0,     0,    48,    49,    50,
     179,    55
  };

  const short int
  Parser::yypgoto_[] =
  {
    -128,  -128,  -128,  -128,   235,   230,  -128,  -128,  -128,  -128,
    -128,   -54,  -128,  -128,   248,  -118,  -128,  -128,  -128,  -126,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,
     -41,   -10,   -25,  -128,   141,   173,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,   127,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,   -83,  -128,  -128,    91,
      19,  -116,  -128,  -128,  -128,  -128,  -128,  -128,  -128,   -76,
    -128,    23,  -128,   180,  -128,  -128,  -128,    60,  -117,   367,
      50,  -128,   175,   -35,  -128,  -127,   -24,    20,   117,    13,
       2,     3,  -128,  -128
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,   264,   265,    29,   318,   319,   281,   282,   283,   389,
     390,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     112,   147,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,   114,   115,
     245,   196,   197,   198,   199,   200,   201,   202,   203,   143,
     228,   229,   217,   153,   367,   380,   149,   150,   151,    82,
      83,    84,    97,   103,   248,    98,   104,   220,   100,   101,
     102,     6,    11,    12
  };

  const short int
  Parser::yytable_[] =
  {
      55,   105,     5,   107,   148,   119,    30,   144,    32,   216,
      99,   263,     7,     8,     8,     8,     8,     8,   109,   110,
     140,    13,     8,    30,   224,   219,     8,   106,     8,     8,
     160,    33,   108,    32,   163,   113,   120,     1,    31,    85,
     226,   227,   230,   195,    87,   225,     2,    47,    47,   165,
      47,   167,   141,    86,   354,     2,    14,     2,   355,    15,
      16,    17,    18,    19,    20,    88,   356,   161,   249,   142,
     145,   164,    51,   142,     9,     9,     9,     9,     9,   246,
     314,     2,     2,     9,   171,   315,   164,     9,   164,     9,
       9,   161,   -81,   172,   261,   164,   152,   175,   122,   254,
    -169,   209,     2,   164,   176,    32,   262,  -169,   176,   296,
     154,   156,   157,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     252,   148,   210,   219,   308,   250,   212,    99,    -2,    14,
     235,   251,    15,    16,    17,    18,    19,    20,   158,   231,
     232,   321,   159,   234,   221,   236,   237,   238,   168,   239,
     330,   332,   343,   242,   344,   259,   243,   244,    15,    16,
      17,    18,    19,    20,   260,   169,   173,   127,   128,   342,
     174,   335,   336,   213,   214,     2,   215,   222,   223,   341,
     204,   130,   131,   132,   133,   134,   135,   127,   128,   293,
     253,   135,   258,   256,   138,   139,   204,   204,   204,   297,
     298,     2,   305,   132,   133,   134,   135,   132,   133,   134,
     135,   306,   313,   311,    32,   267,   141,   370,   333,   371,
     334,   349,   345,   360,   352,   362,   366,   323,   324,   368,
     369,   310,   379,   293,   293,   204,   376,    99,   378,   293,
     393,   385,   381,   293,   293,   398,    94,   399,   400,   410,
      95,   348,   221,   240,   402,   326,   327,   328,   205,   307,
      32,   155,   204,   309,   257,   204,   405,   162,   233,     0,
     312,     0,     0,     0,   322,     0,     0,     0,     0,   337,
     338,   339,   340,     0,   293,     0,   293,     0,     0,     0,
     204,   346,     0,   347,     0,   293,     0,   293,     0,   293,
     148,     0,     0,     0,     0,     0,     0,   267,     0,   123,
     124,   125,     0,   364,   127,   128,   129,     0,     0,   293,
       0,     0,   293,     0,   293,     0,     0,     0,   130,   131,
     132,   133,   134,   135,     0,   373,   374,   204,   204,     0,
     137,   138,   139,     0,     0,   204,     0,   293,     0,   293,
     293,     0,     0,     0,     0,   294,   391,     0,   392,    10,
       0,     0,     0,   395,   293,   293,     0,     0,   293,     0,
     391,   293,     0,    89,    90,    91,    92,    93,     0,     0,
       0,     0,     0,   204,     0,   204,     0,   295,     0,     0,
       0,    96,    96,    96,     0,    96,     0,     0,     0,   294,
     294,     0,   116,     0,   121,   294,     0,     0,     0,   294,
     294,     8,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    39,    40,    41,
       0,   295,   295,     0,     0,    43,    44,   295,    45,     0,
      46,   295,   295,     0,     0,    47,     0,    48,     0,     0,
     294,     0,   294,     0,     0,     0,     0,     0,     0,    96,
       0,   294,   280,   294,     0,   294,    49,    50,    51,    52,
      53,    54,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   295,     0,   295,   294,     0,     0,   294,     0,
     294,     0,     0,   295,     0,   295,     0,   295,   206,     0,
       0,     0,   211,   116,     0,     0,     0,     0,     0,   218,
       0,     0,   325,   294,     0,   294,   294,   295,    96,     0,
     295,    96,   295,     0,     0,     0,     0,     0,     0,   241,
     294,   294,     0,     0,   294,     0,     0,   294,     0,     0,
       0,     0,     0,     0,     0,   295,     0,   295,   295,     0,
       0,     0,   247,     0,     0,     0,     0,   351,     0,   351,
       0,     0,   295,   295,     0,     0,   295,   382,   351,   295,
     351,     0,   365,     0,     0,     0,   383,     0,   218,     0,
     266,     0,   123,   124,   125,   126,     0,   127,   128,   129,
       0,     0,   372,     0,     0,   375,     0,   377,     0,     0,
       0,   130,   131,   132,   133,   134,   135,     0,     0,     0,
       0,   136,     0,   137,   138,   139,     0,   218,     0,     0,
     394,     0,   396,   397,   316,     0,     0,     0,    96,    96,
      96,     0,   317,     0,     0,     0,     0,   407,   408,     0,
       0,   409,     0,   268,   411,   269,     0,   270,   271,     8,
     272,   273,   274,     0,   275,     0,     0,   276,     0,     0,
       0,     0,     0,   218,   277,    39,    40,    41,     0,     0,
       0,     0,   266,    43,    44,     0,    45,     0,    46,     0,
     278,     0,     0,    47,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     320,     0,   279,     0,    49,    50,    51,    52,    53,    54,
       9,   268,     0,   269,     0,   270,   271,     8,   272,   273,
     274,     0,   275,     0,     0,   276,     0,     0,     0,     0,
       0,     0,   277,    39,    40,    41,     0,     0,     0,     0,
       0,    43,    44,     0,    45,     0,    46,     0,   278,     0,
       0,    47,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   329,     0,
     279,     0,    49,    50,    51,    52,    53,    54,     9,   268,
       0,   269,     0,   270,   271,     8,   272,   273,   274,     0,
     275,     0,     0,   276,     0,     0,     0,     0,     0,     0,
     277,    39,    40,    41,     0,     0,     0,     0,     0,    43,
      44,     0,    45,     0,    46,     0,   278,     0,     0,    47,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   331,     0,   279,     0,
      49,    50,    51,    52,    53,    54,     9,   268,     0,   269,
       0,   270,   271,     8,   272,   273,   274,     0,   275,     0,
       0,   276,     0,     0,     0,     0,     0,     0,   277,    39,
      40,    41,     0,     0,     0,     0,     0,    43,    44,     0,
      45,     0,    46,     0,   278,     0,     0,    47,     0,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   386,
       0,     0,     0,     0,     0,     0,   279,     0,    49,    50,
      51,    52,    53,    54,     9,    34,     8,    35,    36,     0,
       0,    37,     0,     0,     0,     0,   387,     0,    38,     0,
       0,     0,    39,    40,    41,     0,     0,     0,     0,    42,
      43,    44,     0,    45,     0,    46,     0,     0,     0,     0,
      47,   388,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     0,     0,     0,     0,     0,     0,     0,
       0,    49,    50,    51,    52,    53,    54,     9,    34,     8,
      35,    36,     0,     0,    37,     0,     0,     0,     0,     0,
       0,    38,     0,     0,     0,    39,    40,    41,     0,     0,
       0,     0,    42,    43,    44,     0,    45,     0,    46,   118,
       0,     0,     0,    47,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   207,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,    51,    52,    53,    54,
       9,    34,     8,    35,    36,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,    39,    40,
      41,     0,     0,     0,     0,    42,    43,    44,     0,    45,
     208,    46,     0,     0,     0,     0,    47,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50,    51,
      52,    53,    54,     9,    34,     8,    35,    36,     0,     0,
      37,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,    39,    40,    41,     0,     0,     0,     0,    42,    43,
      44,     0,    45,     0,    46,     0,     0,     0,     0,    47,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,    51,    52,    53,    54,     9,   268,   350,   269,
       0,   270,   271,     8,   272,   273,   274,     0,   275,     0,
       0,   276,     0,     0,     0,     0,     0,     0,   277,    39,
      40,    41,     0,     0,     0,     0,     0,    43,    44,     0,
      45,     0,    46,     0,   278,     0,     0,    47,     0,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   279,     0,    49,    50,
      51,    52,    53,    54,     9,   268,     0,   269,   353,   270,
     271,     8,   272,   273,   274,     0,   275,     0,     0,   276,
       0,     0,     0,     0,     0,     0,   277,    39,    40,    41,
       0,     0,     0,     0,     0,    43,    44,     0,    45,     0,
      46,     0,   278,     0,     0,    47,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   279,     0,    49,    50,    51,    52,
      53,    54,     9,   268,     0,   269,     0,   270,   271,     8,
     272,   273,   274,     0,   275,     0,     0,   276,     0,     0,
       0,     0,     0,     0,   277,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     278,   361,     0,    47,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   279,     0,    49,    50,    51,    52,    53,    54,
       9,   268,     0,   269,     0,   270,   271,     8,   272,   273,
     274,     0,   275,     0,     0,   276,     0,     0,     0,     0,
       0,     0,   277,    39,    40,    41,     0,     0,     0,     0,
       0,    43,    44,     0,    45,     0,    46,     0,   278,     0,
       0,    47,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     279,   363,    49,    50,    51,    52,    53,    54,     9,   268,
       0,   269,     0,   270,   271,     8,   272,   273,   274,     0,
     275,     0,     0,   276,     0,     0,     0,     0,     0,     0,
     277,    39,    40,    41,     0,     0,     0,     0,     0,    43,
      44,     0,    45,     0,    46,     0,   278,     0,     0,    47,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   279,     0,
      49,    50,    51,    52,    53,    54,     9,    34,     8,    35,
      36,     0,     0,    37,     0,     0,     0,     0,   387,     0,
      38,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,    42,    43,    44,     0,    45,     0,    46,     0,     0,
     401,     0,    47,   388,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,    50,    51,    52,    53,    54,     9,
      34,     8,    35,    36,     0,     0,    37,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,    39,    40,    41,
       0,     0,     0,     0,    42,    43,    44,     0,    45,     0,
      46,     0,     0,     0,     0,    47,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
      53,    54,     9,    34,     8,    35,    36,     0,     0,    37,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
      39,    40,    41,     0,     0,     0,     0,    42,    43,    44,
       0,   146,   300,    46,     0,     0,     0,     0,    47,     0,
      48,     0,     0,     0,     0,     0,     0,   123,   124,   125,
     126,     0,   127,   128,   129,     0,     0,     0,     0,    49,
      50,    51,    52,    53,    54,     9,   130,   131,   132,   133,
     134,   135,   359,     0,     0,     0,   136,     0,   137,   138,
     139,     0,     0,     0,     0,     0,     0,   123,   124,   125,
     126,     0,   127,   128,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   130,   131,   132,   133,
     134,   135,   384,     0,     0,     0,   136,     0,   137,   138,
     139,     0,     0,     0,     0,     0,     0,   123,   124,   125,
     126,     0,   127,   128,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   130,   131,   132,   133,
     134,   135,   406,     0,     0,     0,   136,     0,   137,   138,
     139,     0,     0,     0,     0,     0,     0,   123,   124,   125,
     126,     0,   127,   128,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   130,   131,   132,   133,
     134,   135,   166,     0,     0,     0,   136,     0,   137,   138,
     139,     0,     0,     0,     0,   123,   124,   125,   126,     0,
     127,   128,   129,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   130,   131,   132,   133,   134,   135,
     357,     0,     0,     0,   136,     0,   137,   138,   139,     0,
       0,     0,     0,   123,   124,   125,   126,     0,   127,   128,
     129,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,   135,   301,     0,
       0,     0,   136,     0,   137,   138,   139,     0,     0,     0,
     123,   124,   125,   126,     0,   127,   128,   129,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   130,
     131,   132,   133,   134,   135,   358,     0,     0,     0,   136,
       0,   137,   138,   139,     0,   123,   124,   125,   126,     0,
     127,   128,   129,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   130,   131,   132,   133,   134,   135,
       0,   299,     0,     0,   136,     0,   137,   138,   139,   123,
     124,   125,   126,     0,   127,   128,   129,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   130,   131,
     132,   133,   134,   135,     0,     0,     0,   302,   136,     0,
     137,   138,   139,   123,   124,   125,   126,     0,   127,   128,
     129,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,   135,     0,     0,
       0,     0,   136,     0,   137,   138,   139,   123,   124,   125,
     126,     0,   127,   128,   129,     0,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   130,   131,   132,   133,
     134,   135,     0,     0,     0,     0,   136,     0,   137,   138,
     139,   123,   124,   125,   126,     0,   127,   128,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,   131,   132,   133,   134,   135,     0,   177,     0,     0,
     136,     0,   137,   138,   139,   123,   124,   125,   126,     0,
     127,   128,   129,     0,   255,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   130,   131,   132,   133,   134,   135,
       0,     0,     0,     0,   136,     0,   137,   138,   139,   123,
     124,   125,   126,     0,   127,   128,   129,     0,   303,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   130,   131,
     132,   133,   134,   135,     0,     0,     0,     0,   136,     0,
     137,   138,   139,   123,   124,   125,   126,     0,   127,   128,
     129,     0,     0,     0,   304,     0,     0,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,   135,     0,     0,
       0,     0,   136,     0,   137,   138,   139,   123,   124,   125,
     126,     0,   127,   128,   129,     0,     0,     0,     0,     0,
       0,   403,     0,     0,     0,     0,   130,   131,   132,   133,
     134,   135,     0,     0,     0,     0,   136,     0,   137,   138,
     139,   123,   124,   125,   126,     0,   127,   128,   129,     0,
       0,     0,     0,     0,   404,     0,     0,     0,     0,     0,
     130,   131,   132,   133,   134,   135,     0,     0,     0,     0,
     136,     0,   137,   138,   139,   123,   124,   125,   126,     0,
     127,   128,   129,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   130,   131,   132,   133,   134,   135,
       0,     0,     0,     0,   136,     0,   137,   138,   139,   123,
       0,   125,     0,     0,   127,   128,   129,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   130,   131,
     132,   133,   134,   135,     0,     0,     0,     0,   123,     0,
     137,   138,   139,   127,   128,   129,     0,     0,     0,   127,
     128,   129,     0,     0,     0,     0,     0,   130,   131,   132,
     133,   134,   135,   130,   131,   132,   133,   134,   135,   137,
     138,   139,     0,     0,     0,   137,   138,   139
  };

  const short int
  Parser::yycheck_[] =
  {
      10,    36,     0,    38,    87,    46,     4,    83,     5,     1,
      34,     1,     1,    18,    18,    18,    18,    18,    43,    44,
      32,     0,    18,    21,    44,   152,    18,    37,    18,    18,
      18,    48,    42,    30,    18,    45,    46,     3,     3,    48,
     156,   157,   158,    45,    49,    65,    47,    52,    52,    18,
      52,    18,    64,    48,    18,    47,     1,    47,    18,     4,
       5,     6,     7,     8,     9,    15,    18,    55,   195,    45,
      52,    55,    75,    45,    79,    79,    79,    79,    79,   195,
      50,    47,    47,    79,    46,    55,    55,    79,    55,    79,
      79,    55,    64,    55,   221,    55,    45,    48,    48,    46,
      58,   142,    47,    55,    55,   102,   222,    65,    55,   225,
      44,    44,    51,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     206,   214,   142,   260,   250,    56,   146,   161,     0,     1,
     164,    62,     4,     5,     6,     7,     8,     9,    51,   159,
     160,   269,    44,   163,   152,   165,   166,   167,    46,   169,
     278,   279,    55,   173,    57,    46,   176,   177,     4,     5,
       6,     7,     8,     9,    55,    55,    51,    42,    43,   306,
      48,   297,   298,    65,    55,    47,    50,    65,    49,   305,
     140,    56,    57,    58,    59,    60,    61,    42,    43,   224,
      46,    61,    46,   213,    69,    70,   156,   157,   158,    58,
      65,    47,    55,    58,    59,    60,    61,    58,    59,    60,
      61,    55,    44,    65,   221,   223,    64,   343,    67,   345,
      44,    13,    65,    50,    15,    72,    11,   272,   273,    46,
      46,   251,    10,   268,   269,   195,    49,   271,    49,   274,
      49,    25,    57,   278,   279,    50,    21,    51,    51,    50,
      30,   315,   260,   172,   390,   275,   276,   277,   141,   250,
     267,    91,   222,   250,   214,   225,   393,   102,   161,    -1,
     260,    -1,    -1,    -1,   271,    -1,    -1,    -1,    -1,   299,
     300,   301,   302,    -1,   319,    -1,   321,    -1,    -1,    -1,
     250,   311,    -1,   313,    -1,   330,    -1,   332,    -1,   334,
     393,    -1,    -1,    -1,    -1,    -1,    -1,   315,    -1,    37,
      38,    39,    -1,   333,    42,    43,    44,    -1,    -1,   354,
      -1,    -1,   357,    -1,   359,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    -1,   355,   356,   297,   298,    -1,
      68,    69,    70,    -1,    -1,   305,    -1,   382,    -1,   384,
     385,    -1,    -1,    -1,    -1,   224,   376,    -1,   378,     2,
      -1,    -1,    -1,   383,   399,   400,    -1,    -1,   403,    -1,
     390,   406,    -1,    16,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    -1,   343,    -1,   345,    -1,   224,    -1,    -1,
      -1,    34,    35,    36,    -1,    38,    -1,    -1,    -1,   268,
     269,    -1,    45,    -1,    47,   274,    -1,    -1,    -1,   278,
     279,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      -1,   268,   269,    -1,    -1,    42,    43,   274,    45,    -1,
      47,   278,   279,    -1,    -1,    52,    -1,    54,    -1,    -1,
     319,    -1,   321,    -1,    -1,    -1,    -1,    -1,    -1,   102,
      -1,   330,   224,   332,    -1,   334,    73,    74,    75,    76,
      77,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   319,    -1,   321,   354,    -1,    -1,   357,    -1,
     359,    -1,    -1,   330,    -1,   332,    -1,   334,   141,    -1,
      -1,    -1,   145,   146,    -1,    -1,    -1,    -1,    -1,   152,
      -1,    -1,   274,   382,    -1,   384,   385,   354,   161,    -1,
     357,   164,   359,    -1,    -1,    -1,    -1,    -1,    -1,   172,
     399,   400,    -1,    -1,   403,    -1,    -1,   406,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   382,    -1,   384,   385,    -1,
      -1,    -1,   195,    -1,    -1,    -1,    -1,   319,    -1,   321,
      -1,    -1,   399,   400,    -1,    -1,   403,    22,   330,   406,
     332,    -1,   334,    -1,    -1,    -1,    31,    -1,   221,    -1,
     223,    -1,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,   354,    -1,    -1,   357,    -1,   359,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    66,    -1,    68,    69,    70,    -1,   260,    -1,    -1,
     382,    -1,   384,   385,   267,    -1,    -1,    -1,   271,   272,
     273,    -1,     1,    -1,    -1,    -1,    -1,   399,   400,    -1,
      -1,   403,    -1,    12,   406,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,   306,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,   315,    42,    43,    -1,    45,    -1,    47,    -1,
      49,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    71,    -1,    73,    74,    75,    76,    77,    78,
      79,    12,    -1,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    45,    -1,    47,    -1,    49,    -1,
      -1,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      71,    -1,    73,    74,    75,    76,    77,    78,    79,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,    52,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      45,    -1,    47,    -1,    49,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    73,    74,
      75,    76,    77,    78,    79,    17,    18,    19,    20,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    30,    -1,
      -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,    41,
      42,    43,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    78,    79,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,
      -1,    -1,    41,    42,    43,    -1,    45,    -1,    47,    48,
      -1,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,    78,
      79,    17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    45,
      46,    47,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
      76,    77,    78,    79,    17,    18,    19,    20,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,
      43,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    52,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    75,    76,    77,    78,    79,    12,    13,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      45,    -1,    47,    -1,    49,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    73,    74,
      75,    76,    77,    78,    79,    12,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    45,    -1,
      47,    -1,    49,    -1,    -1,    52,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    -1,    73,    74,    75,    76,
      77,    78,    79,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,
      49,    50,    -1,    52,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    73,    74,    75,    76,    77,    78,
      79,    12,    -1,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    45,    -1,    47,    -1,    49,    -1,
      -1,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,    52,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    17,    18,    19,
      20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    -1,
      30,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    41,    42,    43,    -1,    45,    -1,    47,    -1,    -1,
      50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    41,    42,    43,    -1,    45,    -1,
      47,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,
      77,    78,    79,    17,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,    43,
      -1,    45,    22,    47,    -1,    -1,    -1,    -1,    52,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    77,    78,    79,    56,    57,    58,    59,
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
      60,    61,    24,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      24,    -1,    -1,    -1,    66,    -1,    68,    69,    70,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    25,    -1,
      -1,    -1,    66,    -1,    68,    69,    70,    -1,    -1,    -1,
      37,    38,    39,    40,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    27,    -1,    -1,    -1,    66,
      -1,    68,    69,    70,    -1,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      -1,    29,    -1,    -1,    66,    -1,    68,    69,    70,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    31,    66,    -1,
      68,    69,    70,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    -1,    68,    69,    70,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    63,    -1,    -1,
      66,    -1,    68,    69,    70,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    -1,    68,    69,    70,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    66,    -1,
      68,    69,    70,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    -1,    68,    69,    70,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      66,    -1,    68,    69,    70,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    -1,    68,    69,    70,    37,
      -1,    39,    -1,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    37,    -1,
      68,    69,    70,    42,    43,    44,    -1,    -1,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    56,    57,    58,    59,    60,    61,    68,
      69,    70,    -1,    -1,    -1,    68,    69,    70
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    47,    86,    87,   175,   176,     1,    18,    79,
     164,   177,   178,     0,     1,     4,     5,     6,     7,     8,
       9,    88,    89,    90,    91,    92,    93,    94,    95,    98,
     175,     3,   176,    48,    17,    19,    20,    23,    30,    34,
      35,    36,    41,    42,    43,    45,    47,    52,    54,    73,
      74,    75,    76,    77,    78,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   164,   165,   166,    48,    48,    49,   165,   164,
     164,   164,   164,   164,    89,    90,   164,   167,   170,   171,
     173,   174,   175,   168,   171,   168,   116,   168,   116,   117,
     117,     1,   115,   116,   143,   144,   164,     1,    48,   115,
     116,   164,   165,    37,    38,    39,    40,    42,    43,    44,
      56,    57,    58,    59,    60,    61,    66,    68,    69,    70,
      32,    64,    45,   154,   154,    52,    45,   116,   141,   161,
     162,   163,    45,   158,    44,   158,    44,    51,    51,    44,
      18,    55,   167,    18,    55,    18,    24,    18,    46,    55,
      46,    46,    55,    51,    48,    48,    55,    63,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,    45,   146,   147,   148,   149,
     150,   151,   152,   153,   165,   133,   164,     1,    46,   115,
     116,   164,   116,    65,    55,    50,     1,   157,   164,   170,
     172,   175,    65,    49,    44,    65,   146,   146,   155,   156,
     146,   116,   116,   173,   116,   171,   116,   116,   116,   116,
     144,   164,   116,   116,   116,   145,   146,   164,   169,   170,
      56,    62,   154,    46,    46,    46,   116,   162,    46,    46,
      55,   170,   146,     1,    96,    97,   164,   175,    12,    14,
      16,    17,    19,    20,    21,    23,    26,    33,    49,    71,
      99,   101,   102,   103,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   117,   119,   120,   146,    58,    65,    29,
      22,    25,    31,    46,    48,    55,    55,   145,   146,   156,
     116,    65,   172,    44,    50,    55,   164,     1,    99,   100,
       1,   100,   174,   168,   168,    99,   116,   116,   116,     1,
     100,     1,   100,    67,    44,   146,   146,   116,   116,   116,
     116,   146,   170,    55,    57,    65,   116,   116,    96,    13,
      13,    99,    15,    15,    18,    18,    18,    24,    27,    22,
      50,    50,    72,    72,   116,    99,    11,   159,    46,    46,
     146,   146,    99,   116,   116,    99,    49,    99,    49,    10,
     160,    57,    22,    31,    22,    25,     1,    28,    53,   104,
     105,   116,   116,    49,    99,   116,    99,    99,    50,    51,
      51,    50,   104,    51,    50,   163,    22,    99,    99,    99,
      50,    99
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    85,    86,    87,    87,    88,    88,    89,    89,    89,
      90,    90,    90,    90,    90,    91,    92,    93,    93,    94,
      94,    95,    95,    96,    96,    96,    97,    97,    98,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,   100,   100,   101,   102,   102,   103,   103,   104,   104,
     104,   105,   105,   106,   107,   107,   108,   109,   110,   110,
     110,   110,   111,   111,   111,   111,   112,   113,   114,   115,
     115,   116,   116,   116,   116,   116,   116,   116,   116,   117,
     117,   117,   117,   117,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   119,   119,   120,   120,   121,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   131,   132,   132,   133,   134,   135,   136,   136,   137,
     138,   139,   139,   139,   140,   141,   142,   143,   143,   144,
     145,   145,   146,   146,   146,   146,   146,   147,   148,   148,
     149,   150,   151,   152,   153,   154,   154,   154,   155,   155,
     156,   156,   157,   157,   158,   158,   158,   159,   159,   160,
     160,   161,   161,   162,   162,   162,   163,   163,   164,   164,
     165,   165,   166,   166,   167,   167,   168,   168,   169,   169,
     170,   171,   171,   172,   172,   173,   174,   174,   175,   175,
     176,   176,   176,   177,   178
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     6,     7,     5,     7,     8,
       1,     2,     4,     1,     2,     1,     3,     1,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     4,     6,     6,     6,     3,     3,
       3,     2,     1,     4,     6,     8,     6,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     1,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     1,     2,     3,
       4,     3,     2,     3,     4,     6,     6,     6,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     3,     5,     5,     3,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     5,     4,     6,     3,     3,     3,     2,     3,     1,
       1,     0,     3,     1,     3,     3,     0,     4,     0,     4,
       0,     3,     1,     1,     5,     3,     1,     0,     1,     1,
       1,     2,     3,     1,     1,     1,     3,     1,     3,     1,
       3,     2,     1,     2,     1,     3,     3,     1,     2,     1,
       3,     3,     3,     1,     2
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
  "\"with\"", "\"as\"", "\"while\"", "\"undef\"", "\"false\"", "\"true\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"implies\"", "\"not\"", "\"+\"",
  "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\":\"", "\"::\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"",
  "\"/\"", "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"",
  "\"=>\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"",
  "\"binary\"", "\"hexadecimal\"", "\"integer\"", "\"rational\"",
  "\"decimal\"", "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "CALL",
  "UPLUS", "UMINUS", "CALL_WITHOUT_ARGS", "$accept", "Specification",
  "Header", "Definitions", "AttributedDefinition", "Definition",
  "EnumerationDefinition", "DerivedDefinition", "RuleDefinition",
  "FunctionDefinition", "ProgramFunctionDefinition",
  "EnumeratorDefinition", "Enumerators", "UsingDefinition", "Rule",
  "Rules", "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel",
  "CaseLabels", "LetRule", "ForallRule", "ChooseRule", "IterateRule",
  "BlockRule", "SequenceRule", "UpdateRule", "CallRule", "WhileRule",
  "Terms", "Term", "SimpleOrClaspedTerm", "OperatorExpression",
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
  "IdentifierPath", "DotSeparatedIdentifiers", "Variable",
  "AttributedVariables", "TypedVariables", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "VariableBinding",
  "VariableBindings", "Attributes", "Attribute", "BasicAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   398,   398,   407,   413,   421,   427,   437,   443,   447,
     455,   459,   463,   467,   471,   479,   487,   495,   500,   509,
     525,   533,   555,   573,   577,   583,   591,   597,   607,   619,
     623,   627,   631,   635,   639,   643,   647,   651,   655,   659,
     663,   671,   677,   687,   695,   699,   707,   711,   719,   723,
     727,   735,   741,   751,   759,   763,   771,   779,   787,   791,
     795,   800,   809,   813,   817,   822,   831,   839,   847,   859,
     865,   875,   879,   883,   887,   891,   895,   899,   903,   911,
     915,   919,   923,   927,   931,   935,   947,   951,   955,   959,
     963,   967,   971,   975,   979,   983,   987,   991,   995,   999,
    1003,  1007,  1011,  1015,  1023,  1027,  1031,  1039,  1044,  1052,
    1057,  1065,  1073,  1081,  1089,  1097,  1105,  1113,  1121,  1133,
    1137,  1141,  1145,  1149,  1153,  1157,  1161,  1165,  1169,  1173,
    1177,  1185,  1193,  1198,  1207,  1223,  1239,  1255,  1267,  1283,
    1299,  1307,  1312,  1316,  1324,  1331,  1339,  1346,  1352,  1361,
    1373,  1379,  1389,  1393,  1397,  1401,  1405,  1413,  1421,  1425,
    1432,  1442,  1462,  1470,  1478,  1490,  1494,  1498,  1512,  1518,
    1528,  1532,  1540,  1546,  1556,  1560,  1564,  1576,  1580,  1588,
    1592,  1600,  1606,  1616,  1623,  1632,  1642,  1646,  1658,  1662,
    1670,  1674,  1684,  1690,  1704,  1708,  1717,  1723,  1733,  1739,
    1749,  1757,  1763,  1771,  1777,  1785,  1793,  1799,  1813,  1819,
    1829,  1833,  1837,  1845,  1853
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
#line 4511 "GrammarParser.cpp" // lalr1.cc:1167
#line 1859 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
