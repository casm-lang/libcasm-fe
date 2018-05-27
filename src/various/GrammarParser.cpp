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
      case 177: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 176: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 178: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 149: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 111: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 120: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case 114: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 131: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (that.value);
        break;

      case 105: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 104: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 106: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 128: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 109: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 150: // ComposedType
      case 151: // TupleType
      case 152: // RecordType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 127: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 103: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 90: // AttributedDefinition
      case 91: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 89: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 93: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 121: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 92: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 97: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 98: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 130: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 117: // Term
      case 118: // SimpleOrClaspedTerm
      case 119: // OperatorExpression
      case 161: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 179: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 116: // Terms
      case 156: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 155: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 108: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 95: // FunctionDefinition
      case 96: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 88: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 166: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 167: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 124: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 110: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 126: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 107: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 141: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 132: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 123: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 122: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 146: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 145: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 142: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 144: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 140: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 154: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 100: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 94: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 101: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 112: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 102: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 87: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 153: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 143: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 125: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 147: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 133: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 129: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 113: // UpdateRule
      case 164: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 162: // MaybeInitially
      case 163: // Initializers
      case 165: // MaybeInitializers
        value.move< UpdateRules::Ptr > (that.value);
        break;

      case 99: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 134: // BooleanLiteral
      case 135: // IntegerLiteral
      case 136: // RationalLiteral
      case 137: // DecimalLiteral
      case 138: // BinaryLiteral
      case 139: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 174: // VariableBinding
        value.move< VariableBinding::Ptr > (that.value);
        break;

      case 175: // VariableBindings
        value.move< VariableBindings::Ptr > (that.value);
        break;

      case 168: // Variable
      case 171: // TypedVariable
      case 172: // AttributedVariable
      case 173: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 159: // Parameters
      case 160: // MaybeParameters
      case 169: // AttributedVariables
      case 170: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 115: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case 148: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 74: // "binary"
      case 75: // "hexadecimal"
      case 76: // "integer"
      case 77: // "rational"
      case 78: // "decimal"
      case 79: // "string"
      case 80: // "identifier"
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
      case 177: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 176: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 178: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 149: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 111: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 120: // CallExpression
        value.copy< CallExpression::Ptr > (that.value);
        break;

      case 114: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 131: // CardinalityExpression
        value.copy< CardinalityExpression::Ptr > (that.value);
        break;

      case 105: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 104: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 106: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 128: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 109: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 150: // ComposedType
      case 151: // TupleType
      case 152: // RecordType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 127: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 103: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 90: // AttributedDefinition
      case 91: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 89: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 93: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 121: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 92: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 97: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 98: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 130: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 117: // Term
      case 118: // SimpleOrClaspedTerm
      case 119: // OperatorExpression
      case 161: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 179: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 116: // Terms
      case 156: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 155: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 108: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 95: // FunctionDefinition
      case 96: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 88: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 166: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 167: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 124: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 110: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 126: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 107: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 141: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 132: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 123: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 122: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 146: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 145: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 142: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 144: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 140: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 154: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 100: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 94: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 101: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 112: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 102: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 87: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 153: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 143: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 125: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 147: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 133: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 129: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 113: // UpdateRule
      case 164: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 162: // MaybeInitially
      case 163: // Initializers
      case 165: // MaybeInitializers
        value.copy< UpdateRules::Ptr > (that.value);
        break;

      case 99: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 134: // BooleanLiteral
      case 135: // IntegerLiteral
      case 136: // RationalLiteral
      case 137: // DecimalLiteral
      case 138: // BinaryLiteral
      case 139: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 174: // VariableBinding
        value.copy< VariableBinding::Ptr > (that.value);
        break;

      case 175: // VariableBindings
        value.copy< VariableBindings::Ptr > (that.value);
        break;

      case 168: // Variable
      case 171: // TypedVariable
      case 172: // AttributedVariable
      case 173: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 159: // Parameters
      case 160: // MaybeParameters
      case 169: // AttributedVariables
      case 170: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 115: // WhileRule
        value.copy< WhileRule::Ptr > (that.value);
        break;

      case 148: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 74: // "binary"
      case 75: // "hexadecimal"
      case 76: // "integer"
      case 77: // "rational"
      case 78: // "decimal"
      case 79: // "string"
      case 80: // "identifier"
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
      case 177: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 176: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 178: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 149: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 111: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 120: // CallExpression
        yylhs.value.build< CallExpression::Ptr > ();
        break;

      case 114: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 131: // CardinalityExpression
        yylhs.value.build< CardinalityExpression::Ptr > ();
        break;

      case 105: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 104: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 106: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 128: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 109: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 150: // ComposedType
      case 151: // TupleType
      case 152: // RecordType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 127: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 103: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 90: // AttributedDefinition
      case 91: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 89: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 93: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 121: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 92: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 97: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 98: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 130: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 117: // Term
      case 118: // SimpleOrClaspedTerm
      case 119: // OperatorExpression
      case 161: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 179: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 116: // Terms
      case 156: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 155: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 108: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 95: // FunctionDefinition
      case 96: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 88: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 166: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 167: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 124: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 110: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 126: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 107: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 141: // ListLiteral
        yylhs.value.build< ListLiteral::Ptr > ();
        break;

      case 132: // Literal
        yylhs.value.build< Literal::Ptr > ();
        break;

      case 123: // LiteralCallExpression
        yylhs.value.build< LiteralCallExpression::Ptr > ();
        break;

      case 122: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 146: // Assignment
        yylhs.value.build< NamedExpression::Ptr > ();
        break;

      case 145: // Assignments
        yylhs.value.build< NamedExpressions::Ptr > ();
        break;

      case 142: // RangeLiteral
        yylhs.value.build< RangeLiteral::Ptr > ();
        break;

      case 144: // RecordLiteral
        yylhs.value.build< RecordLiteral::Ptr > ();
        break;

      case 140: // ReferenceLiteral
        yylhs.value.build< ReferenceLiteral::Ptr > ();
        break;

      case 154: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 100: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 94: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 101: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 112: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 102: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 87: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 153: // TemplateType
        yylhs.value.build< TemplateType::Ptr > ();
        break;

      case 143: // TupleLiteral
        yylhs.value.build< TupleLiteral::Ptr > ();
        break;

      case 125: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 147: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 133: // UndefinedLiteral
        yylhs.value.build< UndefLiteral::Ptr > ();
        break;

      case 129: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 113: // UpdateRule
      case 164: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 162: // MaybeInitially
      case 163: // Initializers
      case 165: // MaybeInitializers
        yylhs.value.build< UpdateRules::Ptr > ();
        break;

      case 99: // UsingDefinition
        yylhs.value.build< UsingDefinition::Ptr > ();
        break;

      case 134: // BooleanLiteral
      case 135: // IntegerLiteral
      case 136: // RationalLiteral
      case 137: // DecimalLiteral
      case 138: // BinaryLiteral
      case 139: // StringLiteral
        yylhs.value.build< ValueLiteral::Ptr > ();
        break;

      case 174: // VariableBinding
        yylhs.value.build< VariableBinding::Ptr > ();
        break;

      case 175: // VariableBindings
        yylhs.value.build< VariableBindings::Ptr > ();
        break;

      case 168: // Variable
      case 171: // TypedVariable
      case 172: // AttributedVariable
      case 173: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 159: // Parameters
      case 160: // MaybeParameters
      case 169: // AttributedVariables
      case 170: // TypedVariables
        yylhs.value.build< VariableDefinitions::Ptr > ();
        break;

      case 115: // WhileRule
        yylhs.value.build< WhileRule::Ptr > ();
        break;

      case 148: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 74: // "binary"
      case 75: // "hexadecimal"
      case 76: // "integer"
      case 77: // "rational"
      case 78: // "decimal"
      case 79: // "string"
      case 80: // "identifier"
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
#line 379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 394 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 402 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1535 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 418 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1563 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 428 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 452 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< UsingDefinition::Ptr > ();
  }
#line 1611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 468 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< VariableDefinitions::Ptr > (), createVoidType( yylhs.location ), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 488 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 504 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 512 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 534 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 552 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 556 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 562 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1751 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 576 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 586 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 598 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1777 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1793 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 610 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1801 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 614 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1809 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 618 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1817 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1825 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1833 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1841 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< WhileRule::Ptr > ();
  }
#line 1865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 656 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 666 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 674 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1901 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 678 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 686 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 690 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 698 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 702 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 706 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 714 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1959 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 730 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[2].value.as< VariableBindings::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 738 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1985 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 742 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinitions::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1993 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2009 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 766 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2017 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2025 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 774 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2034 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 779 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2043 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2051 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 792 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2059 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2068 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2077 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 810 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2085 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 818 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< CallExpression::Ptr > () );
  }
#line 2093 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 826 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2101 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 838 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 844 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2121 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 854 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2129 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 858 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2137 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 862 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2145 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 866 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2153 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 870 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2161 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 874 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2169 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2177 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 882 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< CardinalityExpression::Ptr > ();
  }
#line 2193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 894 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< CallExpression::Ptr > ();
  }
#line 2217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LiteralCallExpression::Ptr > ();
  }
#line 2225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 910 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Literal::Ptr > ();
  }
#line 2233 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2241 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2249 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 930 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2257 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2265 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 942 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2281 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2289 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2297 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2305 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2313 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2321 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2329 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2337 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2345 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2353 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2361 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2369 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2377 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2385 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2417 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2426 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1027 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2434 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1035 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2443 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< ValueLiteral::Ptr > () );
  }
#line 2459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1056 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< CallExpression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2467 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1064 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[2].value.as< VariableBindings::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1080 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1096 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1104 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1112 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1125 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< UndefLiteral::Ptr > ();
  }
#line 2531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1129 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1137 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1141 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2563 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1145 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1149 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1153 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ReferenceLiteral::Ptr > ();
  }
#line 2587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1157 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ListLiteral::Ptr > ();
  }
#line 2595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1161 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RangeLiteral::Ptr > ();
  }
#line 2603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< TupleLiteral::Ptr > ();
  }
#line 2611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1169 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RecordLiteral::Ptr > ();
  }
#line 2619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1177 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 2627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1185 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1190 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2645 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2661 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2677 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1231 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1247 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2709 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1259 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1291 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1299 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
  }
#line 2758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1304 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2766 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1308 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = nullptr;
  }
#line 2774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1316 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1323 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
  }
#line 2792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1331 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as< NamedExpressions::Ptr > () );
  }
#line 2800 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = yystack_[2].value.as< NamedExpressions::Ptr > ();
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2810 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1344 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2820 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1353 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2828 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1365 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2838 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1381 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2856 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2864 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1389 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< TemplateType::Ptr > ();
  }
#line 2872 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2880 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2888 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1405 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2896 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1413 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2904 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2912 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Tuple" );
      auto subTypes = yystack_[3].value.as< Types::Ptr > ();
      subTypes->add( yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes );
  }
#line 2923 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2943 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1454 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2951 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1462 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2959 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1470 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2967 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1482 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2975 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1486 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2983 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1490 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1504 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 3002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1510 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 3012 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1520 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 3020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1524 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3038 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1538 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3048 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1548 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = yystack_[1].value.as< VariableDefinitions::Ptr > ();
  }
#line 3056 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1552 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = nullptr;
  }
#line 3064 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1556 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 3072 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1568 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 3080 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 3088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1580 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[1].value.as< UpdateRules::Ptr > ();
  }
#line 3096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1584 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3104 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< UpdateRules::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1598 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3124 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3148 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< TupleLiteral::Ptr > ()->expressions() );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3158 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[0].value.as< UpdateRules::Ptr > ();
  }
#line 3166 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3174 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 3182 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1654 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 3190 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto path = yystack_[2].value.as< IdentifierPath::Ptr > ();
      path->addIdentifier( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = path;
  }
#line 3200 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1668 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1680 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1684 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 3225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1693 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      variables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = variables;
  }
#line 3235 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1699 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = variables;
  }
#line 3245 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1709 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1715 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3265 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1725 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1733 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3283 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1739 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3291 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1747 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3301 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1753 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3309 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1761 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as< VariableDefinition::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3317 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1769 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variableBindings = yystack_[2].value.as< VariableBindings::Ptr > ();
      variableBindings->add( yystack_[0].value.as< VariableBinding::Ptr > () );
      yylhs.value.as< VariableBindings::Ptr > () = variableBindings;
  }
#line 3327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1775 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as< VariableBinding::Ptr > () );
      yylhs.value.as< VariableBindings::Ptr > () = variableBindings;
  }
#line 3337 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1789 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[1].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 1795 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 1805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< BasicAttribute::Ptr > ();
  }
#line 3365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 1809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 212:
#line 1813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = nullptr;
  }
#line 3381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 213:
#line 1821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 214:
#line 1829 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3397 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3401 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -170;

  const short int Parser::yytable_ninf_ = -172;

  const short int
  Parser::yypact_[] =
  {
      22,  -170,    12,    20,    55,    28,  -170,   -27,  -170,  -170,
    1567,    19,    33,  -170,  -170,    -6,    -2,    -2,    -2,    -2,
      -2,   164,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
     138,  -170,  -170,  -170,    -3,    -3,    -3,  1567,    -3,  -170,
    -170,  -170,  1567,   380,   380,  1094,   966,   380,    -2,  -170,
    -170,  -170,  -170,  -170,  -170,  2245,   -15,  -170,    -8,  -170,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,   106,  -170,  -170,  1631,   -14,     1,
      64,     1,    68,    43,  -170,  -170,    84,  -170,  -170,    95,
    -170,    24,    -3,    27,  -170,    29,  1817,    31,  -170,  -170,
    -170,   102,    96,   434,    47,  -170,   111,   126,  -170,   127,
    2035,    17,   -14,  1567,  1567,  1567,  1567,  1567,  1567,  1567,
    1567,  1567,  1567,  1567,  1567,  1567,  1567,  1567,  1567,  1567,
       6,    -4,  1030,  -170,    -2,  -170,  1094,  2245,   110,   132,
    -170,    18,     8,   129,   152,     4,     6,     6,     6,  1567,
    1567,    -3,  -170,  1567,    -3,  1567,  1567,  1567,  -170,  1567,
    -170,  -170,    -2,  1567,  -170,  -170,  1567,  1567,  -170,  2316,
     544,  2310,  2280,   137,   137,   160,   118,   118,   143,   143,
     143,  -170,  2280,   160,   118,   118,     6,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,    32,  -170,    -8,   163,  -170,
      51,  2245,  -170,  2070,  1567,  1631,  -170,   166,    85,    84,
    -170,  -170,    -3,     6,    10,  1439,     6,  -170,  -170,    -7,
     144,  -170,  2245,  2245,  -170,  1965,  -170,  1655,  1894,  2000,
    2105,  -170,   111,  2245,  2245,  2140,   157,  -170,    84,   158,
    -170,     6,  1567,  -170,  -170,  -170,   149,  2245,  -170,  -170,
    -170,    -3,  -170,   172,  -170,  -170,   136,  -170,    -3,   631,
     700,  -170,    -3,    -3,    -3,  1439,  1567,  1567,  1567,   769,
     838,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,   159,   -11,   155,   184,     6,     6,
    1567,  1567,  1567,  1567,  -170,  -170,     6,    -2,   135,   128,
     168,  -170,  1567,  -170,  1567,  -170,    10,  -170,   219,  -170,
    1163,   218,  1232,    35,    40,    48,  -170,  1856,  1930,  1696,
     185,  1301,   170,  1370,  1567,  1439,  -170,   225,  2245,  2245,
    2245,  2245,   191,   194,     6,  -170,     6,  2245,  2245,  -170,
    -170,  -170,  -170,  -170,  -170,  1439,  1567,  1567,  1439,   192,
    1439,  -170,  -170,  -170,  -170,  2245,  -170,   198,   239,  -170,
    -170,  -170,   193,  -170,   283,  1737,   227,   902,  -170,  1567,
     204,  -170,  -170,  1439,  1567,  1439,  1439,   206,   207,   208,
    -170,  1503,  2175,  2210,  1631,  -170,  1778,  -170,  -170,  -170,
    1439,  1439,  -170,  -170,  1439,  -170,   210,  1439,  -170,  -170,
    -170,  -170,  -170
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   209,     0,   191,   190,
     213,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     6,     8,    10,    11,    12,    13,    20,    14,
       0,     3,   208,   212,     0,     0,     0,     0,     0,   133,
     135,   134,     0,     0,     0,     0,     0,     0,     0,   139,
     140,   136,   137,   138,   141,   214,    71,    73,    82,   105,
     106,    83,   107,    72,    74,    75,    76,    77,    78,    79,
      84,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   193,   108,   210,   211,   189,    21,   178,
       0,   178,     0,     0,     5,     7,   195,   202,   194,     0,
     207,     0,     0,     0,   197,     0,     0,     0,   104,    85,
      86,     0,     0,    70,     0,   150,   193,     0,   143,     0,
      70,     0,   142,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,     0,   109,     0,   185,   131,   188,
     184,     0,     0,     0,     0,     0,     0,   173,     0,     0,
       0,     0,   201,     0,     0,     0,     0,     0,    81,     0,
      80,   148,     0,     0,   145,   144,     0,     0,   120,   101,
      99,   100,   103,    87,    88,    94,    95,    96,    89,    90,
      91,    92,   102,    93,    97,    98,     0,   114,   154,   155,
     160,   161,   156,   157,   158,   159,   112,   110,     0,   169,
       0,    70,   192,    70,     0,     0,    22,     0,     0,     0,
     204,   175,     0,     0,     0,     0,     0,    28,   171,   172,
       0,   200,   205,   115,   206,     0,   196,     0,     0,     0,
      69,   149,     0,   151,    69,     0,     0,   153,   193,     0,
     199,   173,     0,   111,   168,   167,    80,   187,   183,   177,
     176,     0,   203,     0,    25,    27,     0,    23,     0,     0,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    67,   105,     0,     0,     0,
       0,     0,     0,     0,   147,   146,     0,     0,     0,   153,
       0,   166,     0,   174,     0,    15,     0,    24,     0,    42,
       0,     0,     0,     0,     0,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   170,   180,   118,   117,
     116,   119,   152,   198,     0,   164,     0,   186,    16,    26,
      65,    63,    41,    61,    59,     0,     0,     0,     0,     0,
       0,    60,    58,    64,    62,    66,    18,     0,   182,   162,
     163,   152,     0,    53,     0,     0,    44,     0,    68,     0,
       0,    19,   165,     0,     0,     0,     0,     0,     0,     0,
      52,     0,     0,     0,   189,    54,     0,    56,    45,    47,
       0,     0,    46,    51,     0,   179,     0,     0,    48,    49,
      50,   181,    55
  };

  const short int
  Parser::yypgoto_[] =
  {
    -170,  -170,  -170,  -170,   236,   231,  -170,  -170,  -170,  -170,
    -170,   -54,  -170,  -170,   224,  -169,  -170,  -170,  -170,  -127,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
     -42,   -10,   -25,  -170,   130,   167,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,   124,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,   -82,  -170,  -170,
      97,    21,  -117,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
     -77,  -170,    23,  -170,   179,  -170,  -170,  -170,    60,  -116,
     368,    50,   175,   -35,  -170,  -123,   -24,    25,   119,     7,
       2,     3,  -170,  -170
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,   265,   266,    29,   319,   320,   282,   283,   284,   390,
     391,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     112,   147,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,   114,
     115,   246,   197,   198,   199,   200,   201,   202,   203,   204,
     143,   229,   230,   218,   153,   368,   381,   149,   150,   151,
      83,    84,    97,   103,   249,    98,   104,   221,   100,   101,
     102,     6,    11,    12
  };

  const short int
  Parser::yytable_[] =
  {
      55,   105,     5,   107,   119,   148,    30,   145,    32,   217,
      99,   264,     8,     7,     8,     8,     8,   140,   109,   110,
      13,    33,   121,    30,     8,     1,     8,   106,     8,   220,
       8,    31,   108,    32,   142,   113,   120,   142,   144,   227,
     228,   231,   160,    87,     2,   163,   152,   165,   225,   167,
     141,   196,   298,   355,   -82,     2,    14,     2,   356,    15,
      16,    17,    18,    19,    20,    88,   357,    85,   216,     2,
     226,   178,    51,   250,     9,     2,     9,     9,     9,   247,
     161,    86,   141,   164,   144,   164,     9,   164,     9,   251,
       9,   161,     9,   171,   157,   252,   164,   255,   122,   262,
     210,   322,     2,   172,   164,    32,   263,   176,   154,   297,
     331,   333,   156,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     253,   260,   211,   148,   309,   158,   213,    99,   220,   159,
     236,   261,    15,    16,    17,    18,    19,    20,   168,   232,
     233,   142,   169,   235,   222,   237,   238,   239,   144,   240,
     127,   128,   173,   243,    -2,    14,   244,   245,    15,    16,
      17,    18,    19,    20,   174,   175,   214,   132,   133,   134,
     135,   336,   337,   176,   343,     2,   315,  -171,   215,   342,
     205,   344,   316,   345,  -171,   223,   132,   133,   134,   135,
     294,   224,   127,   128,   257,   135,   205,   205,   205,   254,
     299,     2,   259,   306,   307,   312,   314,   130,   131,   132,
     133,   134,   135,   334,   141,    32,   268,   371,   335,   372,
     138,   139,   350,   353,   346,   361,   367,   369,   324,   325,
     370,   377,   311,   363,   294,   294,   205,   379,    99,   380,
     294,   382,   386,   394,   294,   294,   399,    94,   400,   401,
     411,    95,   349,   222,   403,   206,   327,   328,   329,   241,
     155,    32,   308,   205,   310,   258,   205,   162,   406,   323,
     234,     0,     0,     0,     0,     0,   313,     0,     0,     0,
     338,   339,   340,   341,     0,   294,     0,   294,     0,     0,
       0,   205,   347,     0,   348,   383,   294,     0,   294,     0,
     294,     0,   148,     0,   384,     0,     0,     0,   268,     0,
     123,   124,   125,   126,   365,   127,   128,   129,     0,     0,
     294,     0,     0,   294,     0,   294,     0,     0,     0,     0,
     130,   131,   132,   133,   134,   135,   374,   375,   205,   205,
     136,     0,   137,   138,   139,   295,   205,     0,   294,     0,
     294,   294,     0,     0,     0,     0,     0,   392,     0,   393,
      10,     0,     0,     0,   396,   294,   294,     0,     0,   294,
       0,   392,   294,     0,    89,    90,    91,    92,    93,     0,
       0,     0,   296,     0,   205,     0,   205,     0,     8,   295,
     295,     0,    96,    96,    96,   295,    96,     0,     0,   295,
     295,     0,     0,   116,    39,    40,    41,     0,     0,     0,
       0,     0,    43,    44,     0,    45,     0,    46,     0,     0,
       0,     0,     0,     0,     0,    48,   296,   296,     0,     0,
       0,     0,   296,     0,     0,     0,   296,   296,     0,   281,
     295,     0,   295,     0,    49,    50,    51,    52,    53,    54,
       9,   295,     0,   295,     0,   295,     0,     0,     0,     0,
      96,   123,   124,   125,   126,     0,   127,   128,   129,     0,
     170,     0,     0,     0,     0,   295,     0,   296,   295,   296,
     295,   130,   131,   132,   133,   134,   135,     0,   296,   326,
     296,   136,   296,   137,   138,   139,     0,     0,     0,   207,
       0,     0,   212,   295,   116,   295,   295,     0,     0,     0,
     219,     0,   296,     0,     0,   296,     0,   296,     0,    96,
     295,   295,    96,     0,   295,     0,     0,   295,     0,     0,
     242,     0,     0,     0,   352,     0,   352,     0,     0,     0,
     296,     0,   296,   296,     0,   352,     0,   352,     0,   366,
       0,     0,     0,     0,   248,     0,     0,   296,   296,     0,
       0,   296,     0,     0,   296,     0,     0,     0,     0,   373,
       0,   123,   376,   125,   378,     0,   127,   128,   129,     0,
     219,     0,   267,     0,     0,     0,     0,     0,     0,     0,
       0,   130,   131,   132,   133,   134,   135,   395,     0,   397,
     398,     0,     0,   137,   138,   139,     0,     0,     0,     0,
       0,     0,     0,     0,   408,   409,     0,     0,   410,   219,
       0,   412,   318,     0,     0,     0,   317,     0,     0,     0,
      96,    96,    96,   269,     0,   270,     0,   271,   272,     8,
     273,   274,   275,     0,   276,     0,     0,   277,     0,     0,
       0,     0,     0,     0,   278,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,   219,    45,     0,    46,     0,
     279,     0,     0,     0,   267,     0,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   321,     0,   280,     0,    49,    50,    51,    52,    53,
      54,     9,   269,     0,   270,     0,   271,   272,     8,   273,
     274,   275,     0,   276,     0,     0,   277,     0,     0,     0,
       0,     0,     0,   278,    39,    40,    41,     0,     0,     0,
       0,     0,    43,    44,     0,    45,     0,    46,     0,   279,
       0,     0,     0,     0,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     330,     0,   280,     0,    49,    50,    51,    52,    53,    54,
       9,   269,     0,   270,     0,   271,   272,     8,   273,   274,
     275,     0,   276,     0,     0,   277,     0,     0,     0,     0,
       0,     0,   278,    39,    40,    41,     0,     0,     0,     0,
       0,    43,    44,     0,    45,     0,    46,     0,   279,     0,
       0,     0,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   332,
       0,   280,     0,    49,    50,    51,    52,    53,    54,     9,
     269,     0,   270,     0,   271,   272,     8,   273,   274,   275,
       0,   276,     0,     0,   277,     0,     0,     0,     0,     0,
       0,   278,    39,    40,    41,     0,     0,     0,     0,     0,
      43,    44,     0,    45,     0,    46,     0,   279,     0,     0,
       0,     0,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   387,     0,     0,     0,     0,     0,     0,
     280,     0,    49,    50,    51,    52,    53,    54,     9,    34,
       8,    35,    36,     0,     0,    37,     0,     0,     0,     0,
     388,     0,    38,     0,     0,     0,    39,    40,    41,     0,
       0,     0,     0,    42,    43,    44,     0,    45,     0,    46,
       0,     0,     0,     0,     0,   389,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
      53,    54,     9,    34,     8,    35,    36,     0,     0,    37,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
      39,    40,    41,     0,     0,     0,     0,    42,    43,    44,
       0,    45,     0,    46,   118,     0,     0,     0,     0,     0,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   208,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,    51,    52,    53,    54,     9,    34,     8,    35,
      36,     0,     0,    37,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,    42,    43,    44,     0,    45,   209,    46,     0,     0,
       0,     0,     0,     0,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   111,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,    51,    52,    53,    54,
       9,    34,     8,    35,    36,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,    39,    40,
      41,     0,     0,     0,     0,    42,    43,    44,     0,    45,
       0,    46,     0,     0,     0,     0,     0,     0,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
      51,    52,    53,    54,     9,   269,   351,   270,     0,   271,
     272,     8,   273,   274,   275,     0,   276,     0,     0,   277,
       0,     0,     0,     0,     0,     0,   278,    39,    40,    41,
       0,     0,     0,     0,     0,    43,    44,     0,    45,     0,
      46,     0,   279,     0,     0,     0,     0,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   280,     0,    49,    50,    51,
      52,    53,    54,     9,   269,     0,   270,   354,   271,   272,
       8,   273,   274,   275,     0,   276,     0,     0,   277,     0,
       0,     0,     0,     0,     0,   278,    39,    40,    41,     0,
       0,     0,     0,     0,    43,    44,     0,    45,     0,    46,
       0,   279,     0,     0,     0,     0,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   280,     0,    49,    50,    51,    52,
      53,    54,     9,   269,     0,   270,     0,   271,   272,     8,
     273,   274,   275,     0,   276,     0,     0,   277,     0,     0,
       0,     0,     0,     0,   278,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     279,   362,     0,     0,     0,     0,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   280,     0,    49,    50,    51,    52,    53,
      54,     9,   269,     0,   270,     0,   271,   272,     8,   273,
     274,   275,     0,   276,     0,     0,   277,     0,     0,     0,
       0,     0,     0,   278,    39,    40,    41,     0,     0,     0,
       0,     0,    43,    44,     0,    45,     0,    46,     0,   279,
       0,     0,     0,     0,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   280,   364,    49,    50,    51,    52,    53,    54,
       9,   269,     0,   270,     0,   271,   272,     8,   273,   274,
     275,     0,   276,     0,     0,   277,     0,     0,     0,     0,
       0,     0,   278,    39,    40,    41,     0,     0,     0,     0,
       0,    43,    44,     0,    45,     0,    46,     0,   279,     0,
       0,     0,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   280,     0,    49,    50,    51,    52,    53,    54,     9,
      34,     8,    35,    36,     0,     0,    37,     0,     0,     0,
       0,   388,     0,    38,     0,     0,     0,    39,    40,    41,
       0,     0,     0,     0,    42,    43,    44,     0,    45,     0,
      46,     0,     0,   402,     0,     0,   389,    47,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50,    51,
      52,    53,    54,     9,    34,     8,    35,    36,     0,     0,
      37,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,    39,    40,    41,     0,     0,     0,     0,    42,    43,
      44,     0,    45,     0,    46,     0,     0,     0,     0,     0,
       0,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,    50,    51,    52,    53,    54,     9,    34,     8,
      35,    36,     0,     0,    37,     0,     0,     0,     0,     0,
       0,    38,     0,     0,     0,    39,    40,    41,     0,     0,
       0,     0,    42,    43,    44,     0,   146,   301,    46,     0,
       0,     0,     0,     0,     0,    47,    48,     0,     0,     0,
       0,     0,   123,   124,   125,   126,     0,   127,   128,   129,
       0,     0,     0,     0,     0,    49,    50,    51,    52,    53,
      54,     9,   130,   131,   132,   133,   134,   135,   360,     0,
       0,     0,   136,     0,   137,   138,   139,     0,     0,     0,
       0,     0,     0,   123,   124,   125,   126,     0,   127,   128,
     129,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   130,   131,   132,   133,   134,   135,   385,
       0,     0,     0,   136,     0,   137,   138,   139,     0,     0,
       0,     0,     0,     0,   123,   124,   125,   126,     0,   127,
     128,   129,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   130,   131,   132,   133,   134,   135,
     407,     0,     0,     0,   136,     0,   137,   138,   139,     0,
       0,     0,     0,     0,     0,   123,   124,   125,   126,     0,
     127,   128,   129,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   130,   131,   132,   133,   134,
     135,   166,     0,     0,     0,   136,     0,   137,   138,   139,
       0,     0,     0,     0,   123,   124,   125,   126,     0,   127,
     128,   129,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   130,   131,   132,   133,   134,   135,
     358,     0,     0,     0,   136,     0,   137,   138,   139,     0,
       0,     0,     0,   123,   124,   125,   126,     0,   127,   128,
     129,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   130,   131,   132,   133,   134,   135,   302,
       0,     0,     0,   136,     0,   137,   138,   139,     0,     0,
       0,   123,   124,   125,   126,     0,   127,   128,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   130,   131,   132,   133,   134,   135,   359,     0,     0,
       0,   136,     0,   137,   138,   139,     0,   123,   124,   125,
     126,     0,   127,   128,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   130,   131,   132,
     133,   134,   135,     0,   300,     0,     0,   136,     0,   137,
     138,   139,   123,   124,   125,   126,     0,   127,   128,   129,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,   135,     0,     0,
       0,   303,   136,     0,   137,   138,   139,   123,   124,   125,
     126,     0,   127,   128,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   130,   131,   132,
     133,   134,   135,     0,     0,     0,     0,   136,     0,   137,
     138,   139,   123,   124,   125,   126,     0,   127,   128,   129,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,   135,     0,   177,
       0,     0,   136,     0,   137,   138,   139,   123,   124,   125,
     126,     0,   127,   128,   129,     0,   256,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   130,   131,   132,
     133,   134,   135,     0,     0,     0,     0,   136,     0,   137,
     138,   139,   123,   124,   125,   126,     0,   127,   128,   129,
       0,   304,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,   135,     0,     0,
       0,     0,   136,     0,   137,   138,   139,   123,   124,   125,
     126,     0,   127,   128,   129,     0,     0,     0,   305,     0,
       0,     0,     0,     0,     0,     0,     0,   130,   131,   132,
     133,   134,   135,     0,     0,     0,     0,   136,     0,   137,
     138,   139,   123,   124,   125,   126,     0,   127,   128,   129,
       0,     0,     0,     0,     0,     0,   404,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,   135,     0,     0,
       0,     0,   136,     0,   137,   138,   139,   123,   124,   125,
     126,     0,   127,   128,   129,     0,     0,     0,     0,     0,
     405,     0,     0,     0,     0,     0,     0,   130,   131,   132,
     133,   134,   135,     0,     0,     0,     0,   136,     0,   137,
     138,   139,   123,   124,   125,   126,     0,   127,   128,   129,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,   135,     0,     0,
       0,     0,   136,     0,   137,   138,   139,   123,   124,   125,
       0,     0,   127,   128,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   130,   131,   132,
     133,   134,   135,     0,     0,     0,     0,   123,     0,   137,
     138,   139,   127,   128,   129,     0,     0,     0,   127,   128,
     129,     0,     0,     0,     0,     0,     0,   130,   131,   132,
     133,   134,   135,   130,   131,   132,   133,   134,   135,   137,
     138,   139,     0,     0,     0,   137,   138,   139
  };

  const short int
  Parser::yycheck_[] =
  {
      10,    36,     0,    38,    46,    87,     4,    84,     5,     1,
      34,     1,    18,     1,    18,    18,    18,    32,    43,    44,
       0,    48,    47,    21,    18,     3,    18,    37,    18,   152,
      18,     3,    42,    30,    45,    45,    46,    45,    52,   156,
     157,   158,    18,    49,    47,    18,    45,    18,    44,    18,
      65,    45,    59,    18,    65,    47,     1,    47,    18,     4,
       5,     6,     7,     8,     9,    15,    18,    48,    50,    47,
      66,    54,    76,   196,    80,    47,    80,    80,    80,   196,
      56,    48,    65,    56,    52,    56,    80,    56,    80,    57,
      80,    56,    80,    46,    51,    63,    56,    46,    48,   222,
     142,   270,    47,    56,    56,   102,   223,    56,    44,   226,
     279,   280,    44,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     207,    46,   142,   215,   251,    51,   146,   161,   261,    44,
     164,    56,     4,     5,     6,     7,     8,     9,    46,   159,
     160,    45,    56,   163,   152,   165,   166,   167,    52,   169,
      42,    43,    51,   173,     0,     1,   176,   177,     4,     5,
       6,     7,     8,     9,    48,    48,    66,    59,    60,    61,
      62,   298,   299,    56,   307,    47,    50,    59,    56,   306,
     140,    56,    56,    58,    66,    66,    59,    60,    61,    62,
     225,    49,    42,    43,   214,    62,   156,   157,   158,    46,
      66,    47,    46,    56,    56,    66,    44,    57,    58,    59,
      60,    61,    62,    68,    65,   222,   224,   344,    44,   346,
      70,    71,    13,    15,    66,    50,    11,    46,   273,   274,
      46,    49,   252,    73,   269,   270,   196,    49,   272,    10,
     275,    58,    25,    49,   279,   280,    50,    21,    51,    51,
      50,    30,   316,   261,   391,   141,   276,   277,   278,   172,
      91,   268,   251,   223,   251,   215,   226,   102,   394,   272,
     161,    -1,    -1,    -1,    -1,    -1,   261,    -1,    -1,    -1,
     300,   301,   302,   303,    -1,   320,    -1,   322,    -1,    -1,
      -1,   251,   312,    -1,   314,    22,   331,    -1,   333,    -1,
     335,    -1,   394,    -1,    31,    -1,    -1,    -1,   316,    -1,
      37,    38,    39,    40,   334,    42,    43,    44,    -1,    -1,
     355,    -1,    -1,   358,    -1,   360,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,   356,   357,   298,   299,
      67,    -1,    69,    70,    71,   225,   306,    -1,   383,    -1,
     385,   386,    -1,    -1,    -1,    -1,    -1,   377,    -1,   379,
       2,    -1,    -1,    -1,   384,   400,   401,    -1,    -1,   404,
      -1,   391,   407,    -1,    16,    17,    18,    19,    20,    -1,
      -1,    -1,   225,    -1,   344,    -1,   346,    -1,    18,   269,
     270,    -1,    34,    35,    36,   275,    38,    -1,    -1,   279,
     280,    -1,    -1,    45,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,   269,   270,    -1,    -1,
      -1,    -1,   275,    -1,    -1,    -1,   279,   280,    -1,   225,
     320,    -1,   322,    -1,    74,    75,    76,    77,    78,    79,
      80,   331,    -1,   333,    -1,   335,    -1,    -1,    -1,    -1,
     102,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      46,    -1,    -1,    -1,    -1,   355,    -1,   320,   358,   322,
     360,    57,    58,    59,    60,    61,    62,    -1,   331,   275,
     333,    67,   335,    69,    70,    71,    -1,    -1,    -1,   141,
      -1,    -1,   144,   383,   146,   385,   386,    -1,    -1,    -1,
     152,    -1,   355,    -1,    -1,   358,    -1,   360,    -1,   161,
     400,   401,   164,    -1,   404,    -1,    -1,   407,    -1,    -1,
     172,    -1,    -1,    -1,   320,    -1,   322,    -1,    -1,    -1,
     383,    -1,   385,   386,    -1,   331,    -1,   333,    -1,   335,
      -1,    -1,    -1,    -1,   196,    -1,    -1,   400,   401,    -1,
      -1,   404,    -1,    -1,   407,    -1,    -1,    -1,    -1,   355,
      -1,    37,   358,    39,   360,    -1,    42,    43,    44,    -1,
     222,    -1,   224,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    62,   383,    -1,   385,
     386,    -1,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   400,   401,    -1,    -1,   404,   261,
      -1,   407,     1,    -1,    -1,    -1,   268,    -1,    -1,    -1,
     272,   273,   274,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,   307,    45,    -1,    47,    -1,
      49,    -1,    -1,    -1,   316,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    72,    -1,    74,    75,    76,    77,    78,
      79,    80,    12,    -1,    14,    -1,    16,    17,    18,    19,
      20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    72,    -1,    74,    75,    76,    77,    78,    79,
      80,    12,    -1,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    45,    -1,    47,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    72,    -1,    74,    75,    76,    77,    78,    79,    80,
      12,    -1,    14,    -1,    16,    17,    18,    19,    20,    21,
      -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    76,    77,    78,    79,    80,    17,
      18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      28,    -1,    30,    -1,    -1,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    41,    42,    43,    -1,    45,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,
      78,    79,    80,    17,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,    43,
      -1,    45,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    78,    79,    80,    17,    18,    19,
      20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    41,    42,    43,    -1,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    45,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,    77,    78,    79,    80,    12,    13,    14,    -1,    16,
      17,    18,    19,    20,    21,    -1,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    45,    -1,
      47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    74,    75,    76,
      77,    78,    79,    80,    12,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    45,    -1,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    74,    75,    76,    77,
      78,    79,    80,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,
      49,    50,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    -1,    74,    75,    76,    77,    78,
      79,    80,    12,    -1,    14,    -1,    16,    17,    18,    19,
      20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    12,    -1,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    45,    -1,    47,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    -1,    74,    75,    76,    77,    78,    79,    80,
      17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    28,    -1,    30,    -1,    -1,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    41,    42,    43,    -1,    45,    -1,
      47,    -1,    -1,    50,    -1,    -1,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
      77,    78,    79,    80,    17,    18,    19,    20,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,
      43,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    77,    78,    79,    80,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,
      -1,    -1,    41,    42,    43,    -1,    45,    22,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      79,    80,    57,    58,    59,    60,    61,    62,    22,    -1,
      -1,    -1,    67,    -1,    69,    70,    71,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    22,
      -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,    62,
      22,    -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      62,    24,    -1,    -1,    -1,    67,    -1,    69,    70,    71,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,    62,
      24,    -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    25,
      -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,    -1,
      -1,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    62,    27,    -1,    -1,
      -1,    67,    -1,    69,    70,    71,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    -1,    29,    -1,    -1,    67,    -1,    69,
      70,    71,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    31,    67,    -1,    69,    70,    71,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    67,    -1,    69,
      70,    71,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    -1,    64,
      -1,    -1,    67,    -1,    69,    70,    71,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    67,    -1,    69,
      70,    71,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    67,    -1,    69,    70,    71,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    67,    -1,    69,
      70,    71,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    67,    -1,    69,    70,    71,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    67,    -1,    69,
      70,    71,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    67,    -1,    69,    70,    71,    37,    38,    39,
      -1,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    37,    -1,    69,
      70,    71,    42,    43,    44,    -1,    -1,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    57,    58,    59,    60,    61,    62,    69,
      70,    71,    -1,    -1,    -1,    69,    70,    71
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    47,    87,    88,   176,   177,     1,    18,    80,
     166,   178,   179,     0,     1,     4,     5,     6,     7,     8,
       9,    89,    90,    91,    92,    93,    94,    95,    96,    99,
     176,     3,   177,    48,    17,    19,    20,    23,    30,    34,
      35,    36,    41,    42,    43,    45,    47,    54,    55,    74,
      75,    76,    77,    78,    79,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   166,   167,    48,    48,    49,   167,   166,
     166,   166,   166,   166,    90,    91,   166,   168,   171,   172,
     174,   175,   176,   169,   172,   169,   117,   169,   117,   118,
     118,     1,   116,   117,   145,   146,   166,     1,    48,   116,
     117,   118,   167,    37,    38,    39,    40,    42,    43,    44,
      57,    58,    59,    60,    61,    62,    67,    69,    70,    71,
      32,    65,    45,   156,    52,   156,    45,   117,   143,   163,
     164,   165,    45,   160,    44,   160,    44,    51,    51,    44,
      18,    56,   168,    18,    56,    18,    24,    18,    46,    56,
      46,    46,    56,    51,    48,    48,    56,    64,    54,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,    45,   148,   149,   150,
     151,   152,   153,   154,   155,   167,   135,   166,     1,    46,
     116,   117,   166,   117,    66,    56,    50,     1,   159,   166,
     171,   173,   176,    66,    49,    44,    66,   148,   148,   157,
     158,   148,   117,   117,   174,   117,   172,   117,   117,   117,
     117,   146,   166,   117,   117,   117,   147,   148,   166,   170,
     171,    57,    63,   156,    46,    46,    46,   117,   164,    46,
      46,    56,   171,   148,     1,    97,    98,   166,   176,    12,
      14,    16,    17,    19,    20,    21,    23,    26,    33,    49,
      72,   100,   102,   103,   104,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   118,   120,   121,   148,    59,    66,
      29,    22,    25,    31,    46,    48,    56,    56,   147,   148,
     158,   117,    66,   173,    44,    50,    56,   166,     1,   100,
     101,     1,   101,   175,   169,   169,   100,   117,   117,   117,
       1,   101,     1,   101,    68,    44,   148,   148,   117,   117,
     117,   117,   148,   171,    56,    58,    66,   117,   117,    97,
      13,    13,   100,    15,    15,    18,    18,    18,    24,    27,
      22,    50,    50,    73,    73,   117,   100,    11,   161,    46,
      46,   148,   148,   100,   117,   117,   100,    49,   100,    49,
      10,   162,    58,    22,    31,    22,    25,     1,    28,    53,
     105,   106,   117,   117,    49,   100,   117,   100,   100,    50,
      51,    51,    50,   105,    51,    50,   165,    22,   100,   100,
     100,    50,   100
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    86,    87,    88,    88,    89,    89,    90,    90,    90,
      91,    91,    91,    91,    91,    92,    93,    94,    94,    95,
      95,    96,    96,    97,    97,    97,    98,    98,    99,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   101,   101,   102,   103,   103,   104,   104,   105,   105,
     105,   106,   106,   107,   108,   108,   109,   110,   111,   111,
     111,   111,   112,   112,   112,   112,   113,   114,   115,   116,
     116,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   118,   118,   118,   118,   118,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   120,   120,   120,   121,   121,
     122,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   133,   134,   134,   135,   136,   137,   138,
     138,   139,   140,   141,   141,   141,   142,   143,   144,   145,
     145,   146,   147,   147,   148,   148,   148,   148,   148,   149,
     150,   150,   151,   152,   153,   154,   155,   156,   156,   156,
     157,   157,   158,   158,   159,   159,   160,   160,   160,   161,
     161,   162,   162,   163,   163,   164,   164,   164,   165,   165,
     166,   166,   167,   167,   168,   168,   169,   169,   170,   170,
     171,   172,   172,   173,   173,   174,   175,   175,   176,   176,
     177,   177,   177,   178,   179
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     1,     1,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     1,     1,     2,
       3,     4,     3,     2,     3,     4,     6,     6,     6,     6,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     3,     5,     5,     3,     3,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     5,     4,     6,     3,     3,     3,     2,
       3,     1,     1,     0,     3,     1,     3,     3,     0,     4,
       0,     4,     0,     3,     1,     1,     5,     3,     1,     0,
       1,     1,     3,     1,     1,     1,     3,     1,     3,     1,
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
  "\":\"", "\"::\"", "\"_\"", "\"|\"", "\"@\"", "\",\"", "\"<\"", "\">\"",
  "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"",
  "\"=>\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"",
  "\"binary\"", "\"hexadecimal\"", "\"integer\"", "\"rational\"",
  "\"decimal\"", "\"string\"", "\"identifier\"", "BASIC_TYPE", "CALL",
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
  "ExistentialQuantifierExpression", "CardinalityExpression", "Literal",
  "UndefinedLiteral", "BooleanLiteral", "IntegerLiteral",
  "RationalLiteral", "DecimalLiteral", "BinaryLiteral", "StringLiteral",
  "ReferenceLiteral", "ListLiteral", "RangeLiteral", "TupleLiteral",
  "RecordLiteral", "Assignments", "Assignment", "Types", "Type",
  "BasicType", "ComposedType", "TupleType", "RecordType", "TemplateType",
  "RelationType", "FixedSizedType", "Arguments", "FunctionParameters",
  "MaybeFunctionParameters", "Parameters", "MaybeParameters",
  "MaybeDefined", "MaybeInitially", "Initializers", "Initializer",
  "MaybeInitializers", "Identifier", "IdentifierPath", "Variable",
  "AttributedVariables", "TypedVariables", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "VariableBinding",
  "VariableBindings", "Attributes", "Attribute", "BasicAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   378,   378,   387,   393,   401,   407,   417,   423,   427,
     435,   439,   443,   447,   451,   459,   467,   475,   479,   487,
     503,   511,   533,   551,   555,   561,   569,   575,   585,   597,
     601,   605,   609,   613,   617,   621,   625,   629,   633,   637,
     641,   649,   655,   665,   673,   677,   685,   689,   697,   701,
     705,   713,   719,   729,   737,   741,   749,   757,   765,   769,
     773,   778,   787,   791,   795,   800,   809,   817,   825,   837,
     843,   853,   857,   861,   865,   869,   873,   877,   881,   885,
     893,   897,   901,   905,   909,   913,   917,   929,   933,   937,
     941,   945,   949,   953,   957,   961,   965,   969,   973,   977,
     981,   985,   989,   993,   997,  1005,  1009,  1013,  1021,  1026,
    1034,  1039,  1047,  1055,  1063,  1071,  1079,  1087,  1095,  1103,
    1111,  1124,  1128,  1132,  1136,  1140,  1144,  1148,  1152,  1156,
    1160,  1164,  1168,  1176,  1184,  1189,  1198,  1214,  1230,  1246,
    1258,  1274,  1290,  1298,  1303,  1307,  1315,  1322,  1330,  1337,
    1343,  1352,  1364,  1370,  1380,  1384,  1388,  1392,  1396,  1404,
    1412,  1416,  1423,  1433,  1453,  1461,  1469,  1481,  1485,  1489,
    1503,  1509,  1519,  1523,  1531,  1537,  1547,  1551,  1555,  1567,
    1571,  1579,  1583,  1591,  1597,  1607,  1614,  1623,  1633,  1637,
    1649,  1653,  1661,  1667,  1679,  1683,  1692,  1698,  1708,  1714,
    1724,  1732,  1738,  1746,  1752,  1760,  1768,  1774,  1788,  1794,
    1804,  1808,  1812,  1820,  1828
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
#line 4483 "GrammarParser.cpp" // lalr1.cc:1167
#line 1834 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
