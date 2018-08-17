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

#line 111 "GrammarParser.cpp" // lalr1.cc:413


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
#line 197 "GrammarParser.cpp" // lalr1.cc:479

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
      case 179: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 178: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 180: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 151: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 113: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 122: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case 116: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 133: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (that.value);
        break;

      case 107: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 106: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 108: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 130: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 111: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 152: // ComposedType
      case 153: // TupleType
      case 154: // RecordType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 129: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 105: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 90: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 94: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 123: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 93: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 98: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 99: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 132: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
      case 163: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 181: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 118: // Terms
      case 158: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 157: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 110: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 96: // FunctionDefinition
      case 97: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 89: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 168: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 169: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 126: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 101: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (that.value);
        break;

      case 112: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 128: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 109: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 143: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 134: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 125: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 124: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 148: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 147: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 144: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 146: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 142: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 156: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 102: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 95: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 103: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 114: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 104: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 88: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 155: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 145: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 127: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 149: // Types
      case 159: // FunctionParameters
      case 160: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 135: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 131: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 115: // UpdateRule
      case 166: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 164: // MaybeInitially
      case 165: // Initializers
      case 167: // MaybeInitializers
        value.move< UpdateRules::Ptr > (that.value);
        break;

      case 100: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 136: // BooleanLiteral
      case 137: // IntegerLiteral
      case 138: // RationalLiteral
      case 139: // DecimalLiteral
      case 140: // BinaryLiteral
      case 141: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 176: // VariableBinding
        value.move< VariableBinding::Ptr > (that.value);
        break;

      case 177: // VariableBindings
        value.move< VariableBindings::Ptr > (that.value);
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 161: // Parameters
      case 162: // MaybeParameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 117: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case 150: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 81: // "identifier"
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
      case 179: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 178: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 180: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 151: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 113: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 122: // CallExpression
        value.copy< CallExpression::Ptr > (that.value);
        break;

      case 116: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 133: // CardinalityExpression
        value.copy< CardinalityExpression::Ptr > (that.value);
        break;

      case 107: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 106: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 108: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 130: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 111: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 152: // ComposedType
      case 153: // TupleType
      case 154: // RecordType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 129: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 105: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 90: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 94: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 123: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 93: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 98: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 99: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 132: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
      case 163: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 181: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 118: // Terms
      case 158: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 157: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 110: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 96: // FunctionDefinition
      case 97: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 89: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 168: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 169: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 126: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 101: // InvariantDefinition
        value.copy< InvariantDefinition::Ptr > (that.value);
        break;

      case 112: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 128: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 109: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 143: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 134: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 125: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 124: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 148: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 147: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 144: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 146: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 142: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 156: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 102: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 95: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 103: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 114: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 104: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 88: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 155: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 145: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 127: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 149: // Types
      case 159: // FunctionParameters
      case 160: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 135: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 131: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 115: // UpdateRule
      case 166: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 164: // MaybeInitially
      case 165: // Initializers
      case 167: // MaybeInitializers
        value.copy< UpdateRules::Ptr > (that.value);
        break;

      case 100: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 136: // BooleanLiteral
      case 137: // IntegerLiteral
      case 138: // RationalLiteral
      case 139: // DecimalLiteral
      case 140: // BinaryLiteral
      case 141: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 176: // VariableBinding
        value.copy< VariableBinding::Ptr > (that.value);
        break;

      case 177: // VariableBindings
        value.copy< VariableBindings::Ptr > (that.value);
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 161: // Parameters
      case 162: // MaybeParameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 117: // WhileRule
        value.copy< WhileRule::Ptr > (that.value);
        break;

      case 150: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 81: // "identifier"
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
      case 179: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 178: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 180: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 151: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 113: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 122: // CallExpression
        yylhs.value.build< CallExpression::Ptr > ();
        break;

      case 116: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 133: // CardinalityExpression
        yylhs.value.build< CardinalityExpression::Ptr > ();
        break;

      case 107: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 106: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 108: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 130: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 111: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 152: // ComposedType
      case 153: // TupleType
      case 154: // RecordType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 129: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 105: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 90: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 94: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 123: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 93: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 98: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 99: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 132: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
      case 163: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 181: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 118: // Terms
      case 158: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 157: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 110: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 96: // FunctionDefinition
      case 97: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 89: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 168: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 169: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 126: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 101: // InvariantDefinition
        yylhs.value.build< InvariantDefinition::Ptr > ();
        break;

      case 112: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 128: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 109: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 143: // ListLiteral
        yylhs.value.build< ListLiteral::Ptr > ();
        break;

      case 134: // Literal
        yylhs.value.build< Literal::Ptr > ();
        break;

      case 125: // LiteralCallExpression
        yylhs.value.build< LiteralCallExpression::Ptr > ();
        break;

      case 124: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 148: // Assignment
        yylhs.value.build< NamedExpression::Ptr > ();
        break;

      case 147: // Assignments
        yylhs.value.build< NamedExpressions::Ptr > ();
        break;

      case 144: // RangeLiteral
        yylhs.value.build< RangeLiteral::Ptr > ();
        break;

      case 146: // RecordLiteral
        yylhs.value.build< RecordLiteral::Ptr > ();
        break;

      case 142: // ReferenceLiteral
        yylhs.value.build< ReferenceLiteral::Ptr > ();
        break;

      case 156: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 102: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 95: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 103: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 114: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 104: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 88: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 155: // TemplateType
        yylhs.value.build< TemplateType::Ptr > ();
        break;

      case 145: // TupleLiteral
        yylhs.value.build< TupleLiteral::Ptr > ();
        break;

      case 127: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 149: // Types
      case 159: // FunctionParameters
      case 160: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 135: // UndefinedLiteral
        yylhs.value.build< UndefLiteral::Ptr > ();
        break;

      case 131: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 115: // UpdateRule
      case 166: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 164: // MaybeInitially
      case 165: // Initializers
      case 167: // MaybeInitializers
        yylhs.value.build< UpdateRules::Ptr > ();
        break;

      case 100: // UsingDefinition
        yylhs.value.build< UsingDefinition::Ptr > ();
        break;

      case 136: // BooleanLiteral
      case 137: // IntegerLiteral
      case 138: // RationalLiteral
      case 139: // DecimalLiteral
      case 140: // BinaryLiteral
      case 141: // StringLiteral
        yylhs.value.build< ValueLiteral::Ptr > ();
        break;

      case 176: // VariableBinding
        yylhs.value.build< VariableBinding::Ptr > ();
        break;

      case 177: // VariableBindings
        yylhs.value.build< VariableBindings::Ptr > ();
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 161: // Parameters
      case 162: // MaybeParameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        yylhs.value.build< VariableDefinitions::Ptr > ();
        break;

      case 117: // WhileRule
        yylhs.value.build< WhileRule::Ptr > ();
        break;

      case 150: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 81: // "identifier"
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
#line 1519 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1591 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 454 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< UsingDefinition::Ptr > ();
  }
#line 1623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< InvariantDefinition::Ptr > ();
  }
#line 1631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 474 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 482 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< VariableDefinitions::Ptr > (), createVoidType( yylhs.location ), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 486 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 510 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 518 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1735 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 562 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1753 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 568 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 576 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 582 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 600 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 628 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1837 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1845 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 636 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1853 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 640 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 644 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 648 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 652 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 656 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< WhileRule::Ptr > ();
  }
#line 1893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1903 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 670 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 680 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1929 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1937 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 700 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 716 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1987 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1997 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 744 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[2].value.as< VariableBindings::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2005 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 752 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2013 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinitions::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2021 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2029 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2037 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2045 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 784 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2053 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2062 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 793 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2071 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 802 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2079 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 806 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2087 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 810 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 815 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2105 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 824 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2113 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< CallExpression::Ptr > () );
  }
#line 2121 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 840 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2129 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 852 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2139 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 858 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2149 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 868 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2157 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 872 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2165 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 876 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2173 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 880 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2181 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 884 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2189 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 888 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 892 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 896 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2213 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 900 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< CardinalityExpression::Ptr > ();
  }
#line 2221 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 908 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2229 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 912 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2237 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< CallExpression::Ptr > ();
  }
#line 2245 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 920 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LiteralCallExpression::Ptr > ();
  }
#line 2253 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Literal::Ptr > ();
  }
#line 2261 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2269 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2277 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 944 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 952 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2301 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2309 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2317 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 964 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2325 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 984 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 988 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 992 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 996 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1000 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1004 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1008 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1012 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2421 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1020 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2437 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1028 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2445 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1036 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1041 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1049 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2471 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1054 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2479 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1062 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< ValueLiteral::Ptr > () );
  }
#line 2487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1070 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< CallExpression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2495 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1078 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[2].value.as< VariableBindings::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2511 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1094 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2519 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1102 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2527 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1110 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2535 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1118 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2543 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1126 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2551 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1139 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< UndefLiteral::Ptr > ();
  }
#line 2559 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1147 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2591 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1159 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1163 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1167 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ReferenceLiteral::Ptr > ();
  }
#line 2615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ListLiteral::Ptr > ();
  }
#line 2623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1175 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RangeLiteral::Ptr > ();
  }
#line 2631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1179 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< TupleLiteral::Ptr > ();
  }
#line 2639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RecordLiteral::Ptr > ();
  }
#line 2647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1191 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 2655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1204 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2673 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1213 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2689 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1229 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1245 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2721 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1261 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1273 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2753 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1289 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1305 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2777 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1313 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
  }
#line 2786 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1318 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1322 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = nullptr;
  }
#line 2802 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2810 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1337 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
  }
#line 2820 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1345 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as< NamedExpressions::Ptr > () );
  }
#line 2828 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1352 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = yystack_[2].value.as< NamedExpressions::Ptr > ();
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2838 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1367 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2856 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1395 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1403 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< TemplateType::Ptr > ();
  }
#line 2900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2908 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1411 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2916 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1419 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2924 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2932 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2940 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Tuple" );
      auto subTypes = yystack_[3].value.as< Types::Ptr > ();
      subTypes->add( yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes );
  }
#line 2951 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2971 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1468 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2979 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2987 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2995 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1496 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 3003 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1500 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 3011 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1504 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 3020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1518 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 3030 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1524 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 3040 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1534 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 3048 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1538 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3056 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1546 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3066 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1552 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3076 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1562 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = yystack_[1].value.as< VariableDefinitions::Ptr > ();
  }
#line 3084 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1566 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = nullptr;
  }
#line 3092 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 3100 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1582 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 3108 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1586 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 3116 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[1].value.as< UpdateRules::Ptr > ();
  }
#line 3124 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1598 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3132 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< UpdateRules::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3142 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3163 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1629 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< TupleLiteral::Ptr > ()->expressions() );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1648 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[0].value.as< UpdateRules::Ptr > ();
  }
#line 3194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1652 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 3210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1668 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 3218 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1676 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto path = yystack_[2].value.as< IdentifierPath::Ptr > ();
      path->addIdentifier( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = path;
  }
#line 3228 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1682 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3236 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1694 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3244 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1698 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 3253 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1707 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      variables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = variables;
  }
#line 3263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1713 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = variables;
  }
#line 3273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1723 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3283 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1729 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1739 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3301 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1747 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1753 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1761 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3329 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1767 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3337 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1775 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as< VariableDefinition::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3345 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1783 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variableBindings = yystack_[2].value.as< VariableBindings::Ptr > ();
      variableBindings->add( yystack_[0].value.as< VariableBinding::Ptr > () );
      yylhs.value.as< VariableBindings::Ptr > () = variableBindings;
  }
#line 3355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 1789 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as< VariableBinding::Ptr > () );
      yylhs.value.as< VariableBindings::Ptr > () = variableBindings;
  }
#line 3365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 1803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[1].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 1809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3385 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 212:
#line 1819 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< BasicAttribute::Ptr > ();
  }
#line 3393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 213:
#line 1823 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 214:
#line 1827 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = nullptr;
  }
#line 3409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 215:
#line 1835 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3417 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 216:
#line 1843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3425 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3429 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -171;

  const short int Parser::yytable_ninf_ = -174;

  const short int
  Parser::yypact_[] =
  {
      16,  -171,     7,    18,    52,    27,  -171,   -17,  -171,  -171,
    1514,     0,    22,  -171,  -171,    -5,    -2,    -2,    -2,    -2,
      -2,    -2,   257,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,   272,  -171,  -171,  -171,    -8,    -8,    -8,  1514,
      -8,  -171,  -171,  -171,  1514,   393,   393,  1041,   913,   393,
      -2,  -171,  -171,  -171,  -171,  -171,  -171,  2270,    36,  -171,
      44,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,    96,  -171,  -171,  1578,
      -6,    49,     5,    49,    53,    64,    60,  -171,  -171,    94,
    -171,  -171,    98,  -171,     8,    -8,    17,  -171,    25,  1807,
      29,  -171,  -171,  -171,   104,   101,  2025,    37,  -171,   103,
     113,  -171,    34,  2060,   -20,    -6,  1514,  1514,  1514,  1514,
    1514,  1514,  1514,  1514,  1514,  1514,  1514,  1514,  1514,  1514,
    1514,  1514,  1514,    -3,    -9,   977,  -171,    -2,  -171,  1041,
    2270,    99,   108,  -171,    45,     4,   106,   126,    10,    -3,
    1514,    -3,    -3,  1514,  1514,    -8,  -171,  1514,    -8,  1514,
    1514,  1514,  -171,  1514,  -171,  -171,    -2,  1514,  -171,  -171,
    1514,  1514,  -171,  2341,   492,  2335,  2305,   159,   159,  2365,
     125,   125,   114,   114,   114,  -171,  2305,  2365,   125,   125,
      -3,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,    39,
    -171,    44,   131,  -171,    90,  2270,  -171,  2095,  1514,  1578,
    -171,   134,    91,    94,  -171,  -171,    -8,    -3,     6,  1386,
      -3,  -171,  2270,  -171,   122,   123,  -171,  2270,  2270,  -171,
    1955,  -171,  1645,  1884,  1990,  2130,  -171,   103,  2270,  2270,
    2165,   132,  -171,    94,   135,  -171,    -3,  1514,  -171,  -171,
    -171,   136,  2270,  -171,  -171,  -171,    -8,  -171,   148,  -171,
    -171,   149,  -171,    -8,   578,   647,  -171,    -8,    -8,    -8,
    1386,  1514,  1514,  1514,   716,   785,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,   139,
      35,   133,   156,    -3,    -3,  1514,  1514,  1514,  1514,  -171,
    -171,    -3,    -2,    54,    85,   140,  -171,  1514,  -171,  1514,
    -171,     6,  -171,   195,  -171,  1110,   194,  1179,    32,    47,
      51,  -171,  1846,  1920,  1686,   160,  1248,   138,  1317,  1514,
    1386,  -171,   205,  2270,  2270,  2270,  2270,   176,   177,    -3,
    -171,    -3,  2270,  2270,  -171,  -171,  -171,  -171,  -171,  -171,
    1386,  1514,  1514,  1386,   182,  1386,  -171,  -171,  -171,  -171,
    2270,  -171,   183,   215,  -171,  -171,  -171,   169,  -171,  1604,
    1727,   204,   849,  -171,  1514,   184,  -171,  -171,  1386,  1514,
    1386,  1386,   185,   186,   187,  -171,  1450,  2200,  2235,  1578,
    -171,  1768,  -171,  -171,  -171,  1386,  1386,  -171,  -171,  1386,
    -171,   193,  1386,  -171,  -171,  -171,  -171,  -171
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   211,     0,   193,   192,
     215,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     8,    10,    11,    12,    13,    21,
      14,    15,     0,     3,   210,   214,     0,     0,     0,     0,
       0,   135,   137,   136,     0,     0,     0,     0,     0,     0,
       0,   141,   142,   138,   139,   140,   143,   216,    73,    75,
      84,   107,   108,    85,   109,    74,    76,    77,    78,    79,
      80,    81,    86,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   195,   110,   212,   213,   191,
      22,   180,     0,   180,     0,     0,     0,     5,     7,   197,
     204,   196,     0,   209,     0,     0,     0,   199,     0,     0,
       0,   106,    87,    88,     0,     0,    72,     0,   152,   195,
       0,   145,     0,    72,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,     0,   111,     0,
     187,   133,   190,   186,     0,     0,     0,     0,     0,     0,
       0,   175,     0,     0,     0,     0,   203,     0,     0,     0,
       0,     0,    83,     0,    82,   150,     0,     0,   147,   146,
       0,     0,   122,   103,   101,   102,   105,    89,    90,    96,
      97,    98,    91,    92,    93,    94,   104,    95,    99,   100,
       0,   116,   156,   157,   162,   163,   158,   159,   160,   161,
     114,   112,     0,   171,     0,    72,   194,    72,     0,     0,
      23,     0,     0,     0,   206,   177,     0,     0,     0,     0,
       0,    29,    30,   173,   174,     0,   202,   207,   117,   208,
       0,   198,     0,     0,     0,    71,   151,     0,   153,    71,
       0,     0,   155,   195,     0,   201,   175,     0,   113,   170,
     169,    82,   189,   185,   179,   178,     0,   205,     0,    26,
      28,     0,    24,     0,     0,     0,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,     0,
      69,   107,     0,     0,     0,     0,     0,     0,     0,   149,
     148,     0,     0,     0,   155,     0,   168,     0,   176,     0,
      16,     0,    25,     0,    44,     0,     0,     0,     0,     0,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   172,   182,   120,   119,   118,   121,   154,   200,     0,
     166,     0,   188,    17,    27,    67,    65,    43,    63,    61,
       0,     0,     0,     0,     0,     0,    62,    60,    66,    64,
      68,    19,     0,   184,   164,   165,   154,     0,    55,     0,
       0,    46,     0,    70,     0,     0,    20,   167,     0,     0,
       0,     0,     0,     0,     0,    54,     0,     0,     0,   191,
      56,     0,    58,    47,    49,     0,     0,    48,    53,     0,
     181,     0,     0,    50,    51,    52,   183,    57
  };

  const short int
  Parser::yypgoto_[] =
  {
    -171,  -171,  -171,  -171,   213,   214,  -171,  -171,  -171,  -171,
    -171,   -76,  -171,  -171,  -171,   180,  -170,  -171,  -171,  -171,
    -148,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,   -46,   -10,   -25,  -171,    75,   168,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
     107,  -171,  -171,  -171,  -171,  -171,  -171,  -171,   -85,  -171,
    -171,    76,    12,  -120,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,   -71,  -171,    14,  -171,   161,  -171,  -171,  -171,    65,
    -143,   178,    13,   181,   -37,  -171,  -133,   -24,    19,   124,
      11,     9,     1,  -171,  -171
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    22,    23,    24,    25,    26,    27,    28,
      29,   270,   271,    30,    31,   324,   325,   287,   288,   289,
     395,   396,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   115,   150,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
     117,   118,   251,   201,   202,   203,   204,   205,   206,   207,
     208,   146,   234,   235,   222,   156,   373,   386,   152,   153,
     154,    85,    86,   100,   106,   254,   101,   107,   225,   103,
     104,   105,     6,    11,    12
  };

  const short int
  Parser::yytable_[] =
  {
      57,   108,   122,   110,   151,   221,    34,   269,     7,     5,
       8,     8,   102,    32,     8,   148,     8,     8,    13,     1,
     112,   113,   224,     8,   124,     8,     8,   164,    90,   109,
      33,    32,    35,    34,   111,   182,   167,   116,   123,   231,
       2,   233,   236,   200,   169,    89,   144,   147,   171,    87,
     157,   360,     2,    14,     2,   229,    15,    16,    17,    18,
      19,    20,    21,   125,     2,   165,   361,   255,    53,   143,
     362,    88,     9,     9,   168,     2,     9,   230,     9,     9,
     252,   145,   168,   179,   175,     9,   168,     9,     9,   165,
     145,   180,   147,   267,   176,   155,   220,   256,   159,   214,
       2,   -84,   144,   257,   168,   327,    34,   268,   168,   160,
     302,   349,   161,   350,   336,   338,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   224,   151,   215,   314,   260,   265,   217,
     258,   102,   145,   163,   241,  -173,   162,   180,   266,   147,
     232,   172,  -173,   237,   238,   177,   209,   240,   173,   242,
     243,   244,   178,   245,   226,   219,   218,   248,   130,   131,
     249,   250,   209,   227,   209,   209,   228,   138,   259,   348,
      10,   264,   303,   341,   342,   135,   136,   137,   138,   311,
     304,   347,   312,   319,    91,    92,    93,    94,    95,    96,
     320,   340,   339,   317,   299,   144,   321,   351,   262,   355,
     358,   366,   368,   209,    99,    99,    99,   372,    99,   135,
     136,   137,   138,   374,   375,   119,   385,    34,   387,   376,
     391,   377,   382,   384,   399,    97,   404,   273,   405,   406,
     209,   329,   330,   209,   416,   354,    98,   316,   408,   299,
     299,   210,   246,   102,   158,   299,   411,    -2,    14,   299,
     299,    15,    16,    17,    18,    19,    20,    21,   313,   209,
     315,   332,   333,   334,    34,   226,    15,    16,    17,    18,
      19,    20,    21,    99,   263,   318,   166,     0,   328,   239,
       0,     0,     0,     0,     0,   343,   344,   345,   346,     0,
     299,     0,   299,     0,   300,     2,     0,   352,     0,   353,
       0,   299,     0,   299,   151,   299,   209,   209,     0,     0,
       2,     0,   211,     0,   209,   216,     0,   119,     0,   370,
     273,     0,     0,   223,     0,   299,     0,     0,   299,     0,
     299,     0,     0,    99,     0,     0,    99,     0,     0,   300,
     300,   379,   380,     0,   247,   300,     0,     0,     0,   300,
     300,     0,   209,   299,   209,   299,   299,     0,     0,     0,
       0,     0,   397,     0,   398,     0,     0,     0,   253,   401,
     299,   299,     0,     0,   299,     0,   397,   299,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   301,     0,     0,
     300,     0,   300,     0,   223,     0,   272,     0,     0,   286,
       0,   300,     8,   300,     0,   300,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
      43,     0,     0,     0,     0,   300,    45,    46,   300,    47,
     300,    48,   301,   301,   223,     0,     0,     0,   301,    50,
       0,   322,   301,   301,     0,    99,    99,    99,     0,     0,
     331,     0,     0,   300,     0,   300,   300,     0,    51,    52,
      53,    54,    55,    56,     9,     0,     0,     0,     0,     0,
     300,   300,     0,     0,   300,     0,     0,   300,     0,     0,
     223,     0,     0,   301,     0,   301,     0,     0,     0,   272,
       0,     0,     0,     0,   301,   357,   301,   357,   301,     0,
       0,     0,     0,     0,     0,     0,   357,     0,   357,     0,
     371,     0,     0,     0,     0,     0,     0,     0,   301,     0,
     126,   301,   128,   301,     0,   130,   131,   132,     0,     0,
     378,     0,     0,   381,     0,   383,     0,     0,     0,     0,
     133,   134,   135,   136,   137,   138,   301,     0,   301,   301,
       0,     0,   140,   141,   142,     0,     0,     0,   400,     0,
     402,   403,     0,   301,   301,     0,     0,   301,     0,   323,
     301,     0,     0,     0,     0,   413,   414,     0,     0,   415,
       0,   274,   417,   275,     0,   276,   277,     8,   278,   279,
     280,     0,   281,     0,     0,   282,     0,     0,     0,     0,
       0,     0,   283,    41,    42,    43,     0,     0,     0,     0,
       0,    45,    46,     0,    47,     0,    48,     0,   284,     0,
       0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   326,     0,
       0,   285,     0,    51,    52,    53,    54,    55,    56,     9,
     274,     0,   275,     0,   276,   277,     8,   278,   279,   280,
       0,   281,     0,     0,   282,     0,     0,     0,     0,     0,
       0,   283,    41,    42,    43,     0,     0,     0,     0,     0,
      45,    46,     0,    47,     0,    48,     0,   284,     0,     0,
       0,     0,     0,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   335,     0,     0,
     285,     0,    51,    52,    53,    54,    55,    56,     9,   274,
       0,   275,     0,   276,   277,     8,   278,   279,   280,     0,
     281,     0,     0,   282,     0,     0,     0,     0,     0,     0,
     283,    41,    42,    43,     0,     0,     0,     0,     0,    45,
      46,     0,    47,     0,    48,     0,   284,     0,     0,     0,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   337,     0,     0,   285,
       0,    51,    52,    53,    54,    55,    56,     9,   274,     0,
     275,     0,   276,   277,     8,   278,   279,   280,     0,   281,
       0,     0,   282,     0,     0,     0,     0,     0,     0,   283,
      41,    42,    43,     0,     0,     0,     0,     0,    45,    46,
       0,    47,     0,    48,     0,   284,     0,     0,     0,     0,
       0,    50,     0,     0,     0,     0,     0,     0,     0,     0,
     392,     0,     0,     0,     0,     0,     0,     0,   285,     0,
      51,    52,    53,    54,    55,    56,     9,    36,     8,    37,
      38,     0,     0,    39,     0,     0,     0,     0,   393,     0,
      40,     0,     0,     0,    41,    42,    43,     0,     0,     0,
       0,    44,    45,    46,     0,    47,     0,    48,     0,     0,
       0,     0,     0,   394,    49,    50,     0,     0,     0,     0,
       0,     0,     0,     0,   120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    54,    55,    56,
       9,    36,     8,    37,    38,     0,     0,    39,     0,     0,
       0,     0,     0,     0,    40,     0,     0,     0,    41,    42,
      43,     0,     0,     0,     0,    44,    45,    46,     0,    47,
       0,    48,   121,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,     0,     0,     0,     0,     0,   212,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,    52,
      53,    54,    55,    56,     9,    36,     8,    37,    38,     0,
       0,    39,     0,     0,     0,     0,     0,     0,    40,     0,
       0,     0,    41,    42,    43,     0,     0,     0,     0,    44,
      45,    46,     0,    47,   213,    48,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    52,    53,    54,    55,    56,     9,    36,
       8,    37,    38,     0,     0,    39,     0,     0,     0,     0,
       0,     0,    40,     0,     0,     0,    41,    42,    43,     0,
       0,     0,     0,    44,    45,    46,     0,    47,     0,    48,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,    52,    53,    54,
      55,    56,     9,   274,   356,   275,     0,   276,   277,     8,
     278,   279,   280,     0,   281,     0,     0,   282,     0,     0,
       0,     0,     0,     0,   283,    41,    42,    43,     0,     0,
       0,     0,     0,    45,    46,     0,    47,     0,    48,     0,
     284,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   285,     0,    51,    52,    53,    54,    55,
      56,     9,   274,     0,   275,   359,   276,   277,     8,   278,
     279,   280,     0,   281,     0,     0,   282,     0,     0,     0,
       0,     0,     0,   283,    41,    42,    43,     0,     0,     0,
       0,     0,    45,    46,     0,    47,     0,    48,     0,   284,
       0,     0,     0,     0,     0,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   285,     0,    51,    52,    53,    54,    55,    56,
       9,   274,     0,   275,     0,   276,   277,     8,   278,   279,
     280,     0,   281,     0,     0,   282,     0,     0,     0,     0,
       0,     0,   283,    41,    42,    43,     0,     0,     0,     0,
       0,    45,    46,     0,    47,     0,    48,     0,   284,   367,
       0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   285,     0,    51,    52,    53,    54,    55,    56,     9,
     274,     0,   275,     0,   276,   277,     8,   278,   279,   280,
       0,   281,     0,     0,   282,     0,     0,     0,     0,     0,
       0,   283,    41,    42,    43,     0,     0,     0,     0,     0,
      45,    46,     0,    47,     0,    48,     0,   284,     0,     0,
       0,     0,     0,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     285,   369,    51,    52,    53,    54,    55,    56,     9,   274,
       0,   275,     0,   276,   277,     8,   278,   279,   280,     0,
     281,     0,     0,   282,     0,     0,     0,     0,     0,     0,
     283,    41,    42,    43,     0,     0,     0,     0,     0,    45,
      46,     0,    47,     0,    48,     0,   284,     0,     0,     0,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   285,
       0,    51,    52,    53,    54,    55,    56,     9,    36,     8,
      37,    38,     0,     0,    39,     0,     0,     0,     0,   393,
       0,    40,     0,     0,     0,    41,    42,    43,     0,     0,
       0,     0,    44,    45,    46,     0,    47,     0,    48,     0,
       0,   407,     0,     0,   394,    49,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    52,    53,    54,    55,
      56,     9,    36,     8,    37,    38,     0,     0,    39,     0,
       0,     0,     0,     0,     0,    40,     0,     0,     0,    41,
      42,    43,     0,     0,     0,     0,    44,    45,    46,     0,
      47,     0,    48,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,    53,    54,    55,    56,     9,    36,     8,    37,    38,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    40,
       0,     0,     0,    41,    42,    43,     0,     0,     0,     0,
      44,    45,    46,     0,   149,     0,    48,   388,     0,     0,
       0,     0,     0,    49,    50,     0,   389,     0,     0,     0,
       0,     0,   126,   127,   128,   129,     0,   130,   131,   132,
       0,     0,     0,    51,    52,    53,    54,    55,    56,     9,
       0,     0,   133,   134,   135,   136,   137,   138,   306,     0,
       0,     0,   139,     0,   140,   141,   142,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,     0,   130,   131,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,   365,
       0,     0,     0,   139,     0,   140,   141,   142,     0,     0,
       0,     0,     0,     0,   126,   127,   128,   129,     0,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   137,   138,
     390,     0,     0,     0,   139,     0,   140,   141,   142,     0,
       0,     0,     0,     0,     0,   126,   127,   128,   129,     0,
     130,   131,   132,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,   134,   135,   136,   137,
     138,   412,     0,     0,     0,   139,     0,   140,   141,   142,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
       0,   130,   131,   132,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,   134,   135,   136,
     137,   138,   170,     0,     0,     0,   139,     0,   140,   141,
     142,     0,     0,     0,     0,   126,   127,   128,   129,     0,
     130,   131,   132,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,   134,   135,   136,   137,
     138,   363,     0,     0,     0,   139,     0,   140,   141,   142,
       0,     0,     0,     0,   126,   127,   128,   129,     0,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   137,   138,
     307,     0,     0,     0,   139,     0,   140,   141,   142,     0,
       0,     0,   126,   127,   128,   129,     0,   130,   131,   132,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   133,   134,   135,   136,   137,   138,   364,     0,
       0,     0,   139,     0,   140,   141,   142,     0,   126,   127,
     128,   129,     0,   130,   131,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   133,   134,
     135,   136,   137,   138,     0,   305,     0,     0,   139,     0,
     140,   141,   142,   126,   127,   128,   129,     0,   130,   131,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,     0,
       0,     0,   308,   139,     0,   140,   141,   142,   126,   127,
     128,   129,     0,   130,   131,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   133,   134,
     135,   136,   137,   138,     0,     0,     0,     0,   139,     0,
     140,   141,   142,   126,   127,   128,   129,     0,   130,   131,
     132,     0,   174,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,     0,
       0,     0,     0,   139,     0,   140,   141,   142,   126,   127,
     128,   129,     0,   130,   131,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   133,   134,
     135,   136,   137,   138,     0,   181,     0,     0,   139,     0,
     140,   141,   142,   126,   127,   128,   129,     0,   130,   131,
     132,     0,   261,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,     0,
       0,     0,     0,   139,     0,   140,   141,   142,   126,   127,
     128,   129,     0,   130,   131,   132,     0,   309,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   133,   134,
     135,   136,   137,   138,     0,     0,     0,     0,   139,     0,
     140,   141,   142,   126,   127,   128,   129,     0,   130,   131,
     132,     0,     0,     0,   310,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,     0,
       0,     0,     0,   139,     0,   140,   141,   142,   126,   127,
     128,   129,     0,   130,   131,   132,     0,     0,     0,     0,
       0,     0,   409,     0,     0,     0,     0,     0,   133,   134,
     135,   136,   137,   138,     0,     0,     0,     0,   139,     0,
     140,   141,   142,   126,   127,   128,   129,     0,   130,   131,
     132,     0,     0,     0,     0,     0,   410,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,     0,
       0,     0,     0,   139,     0,   140,   141,   142,   126,   127,
     128,   129,     0,   130,   131,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   133,   134,
     135,   136,   137,   138,     0,     0,     0,     0,   139,     0,
     140,   141,   142,   126,   127,   128,     0,     0,   130,   131,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,     0,
       0,     0,     0,   126,     0,   140,   141,   142,   130,   131,
     132,     0,     0,     0,   130,   131,   132,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,   133,
     134,   135,   136,   137,   138,   140,   141,   142,   130,   131,
       0,   140,   141,   142,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,     0,
       0,     0,     0,     0,     0,     0,   141,   142
  };

  const short int
  Parser::yycheck_[] =
  {
      10,    38,    48,    40,    89,     1,     5,     1,     1,     0,
      19,    19,    36,     4,    19,    86,    19,    19,     0,     3,
      45,    46,   155,    19,    49,    19,    19,    19,    15,    39,
       3,    22,    49,    32,    44,    55,    19,    47,    48,   159,
      48,   161,   162,    46,    19,    50,    66,    53,    19,    49,
      45,    19,    48,     1,    48,    45,     4,     5,     6,     7,
       8,     9,    10,    50,    48,    57,    19,   200,    77,    33,
      19,    49,    81,    81,    57,    48,    81,    67,    81,    81,
     200,    46,    57,    49,    47,    81,    57,    81,    81,    57,
      46,    57,    53,   226,    57,    46,    51,    58,    45,   145,
      48,    66,    66,    64,    57,   275,   105,   227,    57,    45,
     230,    57,    52,    59,   284,   285,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   266,   219,   145,   256,    47,    47,   149,
     211,   165,    46,    45,   168,    60,    52,    57,    57,    53,
     160,    47,    67,   163,   164,    52,   143,   167,    57,   169,
     170,   171,    49,   173,   155,    57,    67,   177,    43,    44,
     180,   181,   159,    67,   161,   162,    50,    63,    47,   312,
       2,    47,    60,   303,   304,    60,    61,    62,    63,    57,
      67,   311,    57,    45,    16,    17,    18,    19,    20,    21,
      51,    45,    69,    67,   229,    66,    57,    67,   218,    14,
      16,    51,    74,   200,    36,    37,    38,    12,    40,    60,
      61,    62,    63,    47,    47,    47,    11,   226,    59,   349,
      26,   351,    50,    50,    50,    22,    51,   228,    52,    52,
     227,   278,   279,   230,    51,   321,    32,   257,   396,   274,
     275,   144,   176,   277,    93,   280,   399,     0,     1,   284,
     285,     4,     5,     6,     7,     8,     9,    10,   256,   256,
     256,   281,   282,   283,   273,   266,     4,     5,     6,     7,
       8,     9,    10,   105,   219,   266,   105,    -1,   277,   165,
      -1,    -1,    -1,    -1,    -1,   305,   306,   307,   308,    -1,
     325,    -1,   327,    -1,   229,    48,    -1,   317,    -1,   319,
      -1,   336,    -1,   338,   399,   340,   303,   304,    -1,    -1,
      48,    -1,   144,    -1,   311,   147,    -1,   149,    -1,   339,
     321,    -1,    -1,   155,    -1,   360,    -1,    -1,   363,    -1,
     365,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,   274,
     275,   361,   362,    -1,   176,   280,    -1,    -1,    -1,   284,
     285,    -1,   349,   388,   351,   390,   391,    -1,    -1,    -1,
      -1,    -1,   382,    -1,   384,    -1,    -1,    -1,   200,   389,
     405,   406,    -1,    -1,   409,    -1,   396,   412,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   229,    -1,    -1,
     325,    -1,   327,    -1,   226,    -1,   228,    -1,    -1,   229,
      -1,   336,    19,   338,    -1,   340,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    -1,    -1,    -1,    -1,   360,    43,    44,   363,    46,
     365,    48,   274,   275,   266,    -1,    -1,    -1,   280,    56,
      -1,   273,   284,   285,    -1,   277,   278,   279,    -1,    -1,
     280,    -1,    -1,   388,    -1,   390,   391,    -1,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,    -1,
     405,   406,    -1,    -1,   409,    -1,    -1,   412,    -1,    -1,
     312,    -1,    -1,   325,    -1,   327,    -1,    -1,    -1,   321,
      -1,    -1,    -1,    -1,   336,   325,   338,   327,   340,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   336,    -1,   338,    -1,
     340,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   360,    -1,
      38,   363,    40,   365,    -1,    43,    44,    45,    -1,    -1,
     360,    -1,    -1,   363,    -1,   365,    -1,    -1,    -1,    -1,
      58,    59,    60,    61,    62,    63,   388,    -1,   390,   391,
      -1,    -1,    70,    71,    72,    -1,    -1,    -1,   388,    -1,
     390,   391,    -1,   405,   406,    -1,    -1,   409,    -1,     1,
     412,    -1,    -1,    -1,    -1,   405,   406,    -1,    -1,   409,
      -1,    13,   412,    15,    -1,    17,    18,    19,    20,    21,
      22,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    46,    -1,    48,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      43,    44,    -1,    46,    -1,    48,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    13,
      -1,    15,    -1,    17,    18,    19,    20,    21,    22,    -1,
      24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    46,    -1,    48,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    13,    -1,
      15,    -1,    17,    18,    19,    20,    21,    22,    -1,    24,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    43,    44,
      -1,    46,    -1,    48,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    18,    19,    20,
      21,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,
      31,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,
      -1,    42,    43,    44,    -1,    46,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      81,    18,    19,    20,    21,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    36,
      37,    -1,    -1,    -1,    -1,    42,    43,    44,    -1,    46,
      -1,    48,    49,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    79,    80,    81,    18,    19,    20,    21,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
      43,    44,    -1,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    81,    18,
      19,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    35,    36,    37,    -1,
      -1,    -1,    -1,    42,    43,    44,    -1,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    81,    13,    14,    15,    -1,    17,    18,    19,
      20,    21,    22,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    46,    -1,    48,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    46,    -1,    48,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    13,    -1,    15,    -1,    17,    18,    19,    20,    21,
      22,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    46,    -1,    48,    -1,    50,    51,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      43,    44,    -1,    46,    -1,    48,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    13,
      -1,    15,    -1,    17,    18,    19,    20,    21,    22,    -1,
      24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    46,    -1,    48,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    18,    19,
      20,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      -1,    31,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,
      -1,    -1,    42,    43,    44,    -1,    46,    -1,    48,    -1,
      -1,    51,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    81,    18,    19,    20,    21,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,
      36,    37,    -1,    -1,    -1,    -1,    42,    43,    44,    -1,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    81,    18,    19,    20,    21,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,    43,    44,    -1,    46,    -1,    48,    23,    -1,    -1,
      -1,    -1,    -1,    55,    56,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    -1,    43,    44,    45,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    58,    59,    60,    61,    62,    63,    23,    -1,
      -1,    -1,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    23,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      23,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    23,    -1,    -1,    -1,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      62,    63,    25,    -1,    -1,    -1,    68,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    25,    -1,    -1,    -1,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      26,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    38,    39,    40,    41,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    62,    63,    28,    -1,
      -1,    -1,    68,    -1,    70,    71,    72,    -1,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    30,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    32,    68,    -1,    70,    71,    72,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    65,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    38,    -1,    70,    71,    72,    43,    44,
      45,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    58,
      59,    60,    61,    62,    63,    70,    71,    72,    43,    44,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    48,    88,    89,   178,   179,     1,    19,    81,
     168,   180,   181,     0,     1,     4,     5,     6,     7,     8,
       9,    10,    90,    91,    92,    93,    94,    95,    96,    97,
     100,   101,   178,     3,   179,    49,    18,    20,    21,    24,
      31,    35,    36,    37,    42,    43,    44,    46,    48,    55,
      56,    75,    76,    77,    78,    79,    80,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   168,   169,    49,    49,    50,
     169,   168,   168,   168,   168,   168,   168,    91,    92,   168,
     170,   173,   174,   176,   177,   178,   171,   174,   171,   119,
     171,   119,   120,   120,     1,   118,   119,   147,   148,   168,
       1,    49,   118,   119,   120,   169,    38,    39,    40,    41,
      43,    44,    45,    58,    59,    60,    61,    62,    63,    68,
      70,    71,    72,    33,    66,    46,   158,    53,   158,    46,
     119,   145,   165,   166,   167,    46,   162,    45,   162,    45,
      45,    52,    52,    45,    19,    57,   170,    19,    57,    19,
      25,    19,    47,    57,    47,    47,    57,    52,    49,    49,
      57,    65,    55,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
      46,   150,   151,   152,   153,   154,   155,   156,   157,   169,
     137,   168,     1,    47,   118,   119,   168,   119,    67,    57,
      51,     1,   161,   168,   173,   175,   178,    67,    50,    45,
      67,   150,   119,   150,   159,   160,   150,   119,   119,   176,
     119,   174,   119,   119,   119,   119,   148,   168,   119,   119,
     119,   149,   150,   168,   172,   173,    58,    64,   158,    47,
      47,    47,   119,   166,    47,    47,    57,   173,   150,     1,
      98,    99,   168,   178,    13,    15,    17,    18,    20,    21,
      22,    24,    27,    34,    50,    73,   102,   104,   105,   106,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   120,
     122,   123,   150,    60,    67,    30,    23,    26,    32,    47,
      49,    57,    57,   149,   150,   160,   119,    67,   175,    45,
      51,    57,   168,     1,   102,   103,     1,   103,   177,   171,
     171,   102,   119,   119,   119,     1,   103,     1,   103,    69,
      45,   150,   150,   119,   119,   119,   119,   150,   173,    57,
      59,    67,   119,   119,    98,    14,    14,   102,    16,    16,
      19,    19,    19,    25,    28,    23,    51,    51,    74,    74,
     119,   102,    12,   163,    47,    47,   150,   150,   102,   119,
     119,   102,    50,   102,    50,    11,   164,    59,    23,    32,
      23,    26,     1,    29,    54,   107,   108,   119,   119,    50,
     102,   119,   102,   102,    51,    52,    52,    51,   107,    52,
      51,   167,    23,   102,   102,   102,    51,   102
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    87,    88,    89,    89,    90,    90,    91,    91,    91,
      92,    92,    92,    92,    92,    92,    93,    94,    95,    95,
      96,    96,    97,    97,    98,    98,    98,    99,    99,   100,
     101,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   103,   103,   104,   105,   105,   106,   106,
     107,   107,   107,   108,   108,   109,   110,   110,   111,   112,
     113,   113,   113,   113,   114,   114,   114,   114,   115,   116,
     117,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   120,   120,   120,   120,   120,   120,   120,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   122,   122,   122,
     123,   123,   124,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   135,   136,   136,   137,   138,
     139,   140,   140,   141,   142,   143,   143,   143,   144,   145,
     146,   147,   147,   148,   149,   149,   150,   150,   150,   150,
     150,   151,   152,   152,   153,   154,   155,   156,   157,   158,
     158,   158,   159,   159,   160,   160,   161,   161,   162,   162,
     162,   163,   163,   164,   164,   165,   165,   166,   166,   166,
     167,   167,   168,   168,   169,   169,   170,   170,   171,   171,
     172,   172,   173,   174,   174,   175,   175,   176,   177,   177,
     178,   178,   179,   179,   179,   180,   181
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     6,     7,     5,     7,
       8,     1,     2,     4,     1,     2,     1,     3,     1,     4,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     4,     6,     6,     6,
       3,     3,     3,     2,     1,     4,     6,     8,     6,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     1,     1,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     1,     1,     1,
       1,     2,     3,     4,     3,     2,     3,     4,     6,     6,
       6,     6,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     3,     3,     5,     5,
       3,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     5,     4,     6,     3,     3,
       3,     2,     3,     1,     1,     0,     3,     1,     3,     3,
       0,     4,     0,     4,     0,     3,     1,     1,     5,     3,
       1,     0,     1,     1,     3,     1,     1,     1,     3,     1,
       3,     1,     3,     2,     1,     2,     1,     3,     3,     1,
       2,     1,     3,     3,     3,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"using\"",
  "\"invariant\"", "\"function\"", "\"initially\"", "\"defined\"",
  "\"seq\"", "\"endseq\"", "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"",
  "\"in\"", "\"forall\"", "\"choose\"", "\"iterate\"", "\"do\"", "\"if\"",
  "\"then\"", "\"else\"", "\"case\"", "\"of\"", "\"default\"", "\"holds\"",
  "\"exists\"", "\"with\"", "\"as\"", "\"while\"", "\"undef\"",
  "\"false\"", "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"implies\"",
  "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\":\"", "\"::\"", "\"_\"", "\"|\"", "\"@\"", "\",\"",
  "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"'\"", "\"..\"",
  "\".\"", "\"->\"", "\"=>\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"",
  "\"{|\"", "\"|}\"", "\"binary\"", "\"hexadecimal\"", "\"integer\"",
  "\"rational\"", "\"decimal\"", "\"string\"", "\"identifier\"",
  "BASIC_TYPE", "CALL", "UPLUS", "UMINUS", "CALL_WITHOUT_ARGS", "$accept",
  "Specification", "Header", "Definitions", "AttributedDefinition",
  "Definition", "EnumerationDefinition", "DerivedDefinition",
  "RuleDefinition", "FunctionDefinition", "ProgramFunctionDefinition",
  "EnumeratorDefinition", "Enumerators", "UsingDefinition",
  "InvariantDefinition", "Rule", "Rules", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabel", "CaseLabels", "LetRule", "ForallRule",
  "ChooseRule", "IterateRule", "BlockRule", "SequenceRule", "UpdateRule",
  "CallRule", "WhileRule", "Terms", "Term", "SimpleOrClaspedTerm",
  "OperatorExpression", "CallExpression", "DirectCallExpression",
  "MethodCallExpression", "LiteralCallExpression",
  "IndirectCallExpression", "TypeCastingExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "CardinalityExpression", "Literal", "UndefinedLiteral", "BooleanLiteral",
  "IntegerLiteral", "RationalLiteral", "DecimalLiteral", "BinaryLiteral",
  "StringLiteral", "ReferenceLiteral", "ListLiteral", "RangeLiteral",
  "TupleLiteral", "RecordLiteral", "Assignments", "Assignment", "Types",
  "Type", "BasicType", "ComposedType", "TupleType", "RecordType",
  "TemplateType", "RelationType", "FixedSizedType", "Arguments",
  "FunctionParameters", "MaybeFunctionParameters", "Parameters",
  "MaybeParameters", "MaybeDefined", "MaybeInitially", "Initializers",
  "Initializer", "MaybeInitializers", "Identifier", "IdentifierPath",
  "Variable", "AttributedVariables", "TypedVariables", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "VariableBinding",
  "VariableBindings", "Attributes", "Attribute", "BasicAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   380,   380,   389,   395,   403,   409,   419,   425,   429,
     437,   441,   445,   449,   453,   457,   465,   473,   481,   485,
     493,   509,   517,   539,   557,   561,   567,   575,   581,   591,
     599,   611,   615,   619,   623,   627,   631,   635,   639,   643,
     647,   651,   655,   663,   669,   679,   687,   691,   699,   703,
     711,   715,   719,   727,   733,   743,   751,   755,   763,   771,
     779,   783,   787,   792,   801,   805,   809,   814,   823,   831,
     839,   851,   857,   867,   871,   875,   879,   883,   887,   891,
     895,   899,   907,   911,   915,   919,   923,   927,   931,   943,
     947,   951,   955,   959,   963,   967,   971,   975,   979,   983,
     987,   991,   995,   999,  1003,  1007,  1011,  1019,  1023,  1027,
    1035,  1040,  1048,  1053,  1061,  1069,  1077,  1085,  1093,  1101,
    1109,  1117,  1125,  1138,  1142,  1146,  1150,  1154,  1158,  1162,
    1166,  1170,  1174,  1178,  1182,  1190,  1198,  1203,  1212,  1228,
    1244,  1260,  1272,  1288,  1304,  1312,  1317,  1321,  1329,  1336,
    1344,  1351,  1357,  1366,  1378,  1384,  1394,  1398,  1402,  1406,
    1410,  1418,  1426,  1430,  1437,  1447,  1467,  1475,  1483,  1495,
    1499,  1503,  1517,  1523,  1533,  1537,  1545,  1551,  1561,  1565,
    1569,  1581,  1585,  1593,  1597,  1605,  1611,  1621,  1628,  1637,
    1647,  1651,  1663,  1667,  1675,  1681,  1693,  1697,  1706,  1712,
    1722,  1728,  1738,  1746,  1752,  1760,  1766,  1774,  1782,  1788,
    1802,  1808,  1818,  1822,  1826,  1834,  1842
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
#line 4521 "GrammarParser.cpp" // lalr1.cc:1167
#line 1848 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
