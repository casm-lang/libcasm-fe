// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "GrammarParser.tab.h"


// Unqualified %code blocks.
#line 92 "../../obj/src/GrammarParser.y"

    #include "../../src/Lexer.h"

    #include <libstdhl/Type>

    #undef yylex
    #define yylex m_lexer.nextToken

    static BasicType::Ptr createVoidType( libstdhl::SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

#line 65 "GrammarParser.cpp"


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


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
    while (false)
# endif


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
      *yycdebug_ << '\n';                       \
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
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 51 "../../obj/src/GrammarParser.y"
namespace libcasm_fe {
#line 158 "GrammarParser.cpp"

  /// Build a parser object.
  Parser::Parser (Logger& m_log_yyarg, Lexer& m_lexer_yyarg, Specification& m_specification_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      m_log (m_log_yyarg),
      m_lexer (m_lexer_yyarg),
      m_specification (m_specification_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_FEATURE: // "feature"
      case symbol_kind::S_IMPLEMENTS: // "implements"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_FUNCTION: // "function"
      case symbol_kind::S_DEFINED: // "defined"
      case symbol_kind::S_SEQ: // "seq"
      case symbol_kind::S_ENDSEQ: // "endseq"
      case symbol_kind::S_PAR: // "par"
      case symbol_kind::S_ENDPAR: // "endpar"
      case symbol_kind::S_SKIP: // "skip"
      case symbol_kind::S_LET: // "let"
      case symbol_kind::S_LOCAL: // "local"
      case symbol_kind::S_IN: // "in"
      case symbol_kind::S_FORALL: // "forall"
      case symbol_kind::S_CHOOSE: // "choose"
      case symbol_kind::S_ITERATE: // "iterate"
      case symbol_kind::S_DO: // "do"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_THEN: // "then"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_CASE: // "case"
      case symbol_kind::S_OF: // "of"
      case symbol_kind::S_DEFAULT: // "default"
      case symbol_kind::S_HOLDS: // "holds"
      case symbol_kind::S_EXISTS: // "exists"
      case symbol_kind::S_WITH: // "with"
      case symbol_kind::S_AS: // "as"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_UNDEF: // "undef"
      case symbol_kind::S_FALSE: // "false"
      case symbol_kind::S_TRUE: // "true"
      case symbol_kind::S_AND: // "and"
      case symbol_kind::S_OR: // "or"
      case symbol_kind::S_XOR: // "xor"
      case symbol_kind::S_IMPLIES: // "implies"
      case symbol_kind::S_NOT: // "not"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_EQUAL: // "="
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LSQPAREN: // "["
      case symbol_kind::S_RSQPAREN: // "]"
      case symbol_kind::S_LCURPAREN: // "{"
      case symbol_kind::S_RCURPAREN: // "}"
      case symbol_kind::S_COLON: // ":"
      case symbol_kind::S_DOUBLECOLON: // "::"
      case symbol_kind::S_UNDERLINE: // "_"
      case symbol_kind::S_VERTICAL_BAR: // "|"
      case symbol_kind::S_AT: // "@"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_LESSER: // "<"
      case symbol_kind::S_GREATER: // ">"
      case symbol_kind::S_ASTERIX: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_CARET: // "^"
      case symbol_kind::S_MARK: // "'"
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
        value.YY_MOVE_OR_COPY< Ast::Token::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Attribute: // Attribute
        value.YY_MOVE_OR_COPY< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Attributes: // Attributes
        value.YY_MOVE_OR_COPY< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BasicAttribute: // BasicAttribute
        value.YY_MOVE_OR_COPY< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BasicType: // BasicType
        value.YY_MOVE_OR_COPY< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.YY_MOVE_OR_COPY< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CallExpression: // CallExpression
        value.YY_MOVE_OR_COPY< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CallRule: // CallRule
        value.YY_MOVE_OR_COPY< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CardinalityExpression: // CardinalityExpression
        value.YY_MOVE_OR_COPY< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CaseLabel: // CaseLabel
        value.YY_MOVE_OR_COPY< Case::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CaseRule: // CaseRule
        value.YY_MOVE_OR_COPY< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CaseLabels: // CaseLabels
        value.YY_MOVE_OR_COPY< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ChooseExpression: // ChooseExpression
        value.YY_MOVE_OR_COPY< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ChooseRule: // ChooseRule
        value.YY_MOVE_OR_COPY< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConditionalExpression: // ConditionalExpression
        value.YY_MOVE_OR_COPY< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConditionalRule: // ConditionalRule
        value.YY_MOVE_OR_COPY< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DeclarationDefinition: // DeclarationDefinition
        value.YY_MOVE_OR_COPY< DeclarationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.YY_MOVE_OR_COPY< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDeclarationOrDefinition: // FeatureDeclarationOrDefinition
      case symbol_kind::S_ImplementationDefinitionDefinition: // ImplementationDefinitionDefinition
        value.YY_MOVE_OR_COPY< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDeclarationsAndDefinitions: // FeatureDeclarationsAndDefinitions
      case symbol_kind::S_ImplementationDefinitionDefinitions: // ImplementationDefinitionDefinitions
        value.YY_MOVE_OR_COPY< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.YY_MOVE_OR_COPY< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.YY_MOVE_OR_COPY< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_EnumerationDefinition: // EnumerationDefinition
        value.YY_MOVE_OR_COPY< EnumerationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_EnumeratorDefinition: // EnumeratorDefinition
        value.YY_MOVE_OR_COPY< EnumeratorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Enumerators: // Enumerators
        value.YY_MOVE_OR_COPY< Enumerators::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExistentialQuantifierExpression: // ExistentialQuantifierExpression
        value.YY_MOVE_OR_COPY< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Term: // Term
      case symbol_kind::S_SimpleOrClaspedTerm: // SimpleOrClaspedTerm
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.YY_MOVE_OR_COPY< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.YY_MOVE_OR_COPY< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Terms: // Terms
        value.YY_MOVE_OR_COPY< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FeatureDefinition: // FeatureDefinition
        value.YY_MOVE_OR_COPY< FeatureDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FixedSizedType: // FixedSizedType
        value.YY_MOVE_OR_COPY< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ForallRule: // ForallRule
        value.YY_MOVE_OR_COPY< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FunctionDefinition: // FunctionDefinition
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.YY_MOVE_OR_COPY< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LocalFunctionDefinitions: // LocalFunctionDefinitions
        value.YY_MOVE_OR_COPY< FunctionDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Header: // Header
        value.YY_MOVE_OR_COPY< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_Identifier: // Identifier
        value.YY_MOVE_OR_COPY< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IdentifierPath: // IdentifierPath
        value.YY_MOVE_OR_COPY< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ImplementationDefinition: // ImplementationDefinition
        value.YY_MOVE_OR_COPY< ImplementationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ImportDefinition: // ImportDefinition
        value.YY_MOVE_OR_COPY< ImportDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IndirectCallExpression: // IndirectCallExpression
        value.YY_MOVE_OR_COPY< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitDefinition: // InitDefinition
        value.YY_MOVE_OR_COPY< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Initializer: // Initializer
        value.YY_MOVE_OR_COPY< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Initializers: // Initializers
        value.YY_MOVE_OR_COPY< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MaybeInitially: // MaybeInitially
        value.YY_MOVE_OR_COPY< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InvariantDefinition: // InvariantDefinition
        value.YY_MOVE_OR_COPY< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IterateRule: // IterateRule
        value.YY_MOVE_OR_COPY< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LetExpression: // LetExpression
        value.YY_MOVE_OR_COPY< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LetRule: // LetRule
        value.YY_MOVE_OR_COPY< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ListLiteral: // ListLiteral
        value.YY_MOVE_OR_COPY< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Literal: // Literal
        value.YY_MOVE_OR_COPY< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LiteralCallExpression: // LiteralCallExpression
        value.YY_MOVE_OR_COPY< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LocalRule: // LocalRule
        value.YY_MOVE_OR_COPY< LocalRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MethodCallExpression: // MethodCallExpression
        value.YY_MOVE_OR_COPY< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Assignment: // Assignment
        value.YY_MOVE_OR_COPY< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Assignments: // Assignments
        value.YY_MOVE_OR_COPY< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RangeLiteral: // RangeLiteral
        value.YY_MOVE_OR_COPY< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RecordLiteral: // RecordLiteral
        value.YY_MOVE_OR_COPY< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RecordType: // RecordType
        value.YY_MOVE_OR_COPY< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ReferenceLiteral: // ReferenceLiteral
        value.YY_MOVE_OR_COPY< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RelationType: // RelationType
        value.YY_MOVE_OR_COPY< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Rule: // Rule
        value.YY_MOVE_OR_COPY< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RuleDefinition: // RuleDefinition
        value.YY_MOVE_OR_COPY< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Rules: // Rules
        value.YY_MOVE_OR_COPY< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SequenceRule: // SequenceRule
        value.YY_MOVE_OR_COPY< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SkipRule: // SkipRule
        value.YY_MOVE_OR_COPY< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Specification: // Specification
        value.YY_MOVE_OR_COPY< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_StructureDefinition: // StructureDefinition
        value.YY_MOVE_OR_COPY< StructureDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TemplateType: // TemplateType
        value.YY_MOVE_OR_COPY< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TupleLiteral: // TupleLiteral
        value.YY_MOVE_OR_COPY< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TupleType: // TupleType
        value.YY_MOVE_OR_COPY< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TypeCastingExpression: // TypeCastingExpression
        value.YY_MOVE_OR_COPY< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Types: // Types
      case symbol_kind::S_FunctionParameters: // FunctionParameters
      case symbol_kind::S_MaybeFunctionParameters: // MaybeFunctionParameters
        value.YY_MOVE_OR_COPY< Types::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UndefinedLiteral: // UndefinedLiteral
        value.YY_MOVE_OR_COPY< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UniversalQuantifierExpression: // UniversalQuantifierExpression
        value.YY_MOVE_OR_COPY< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UpdateRule: // UpdateRule
        value.YY_MOVE_OR_COPY< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UsingDefinition: // UsingDefinition
        value.YY_MOVE_OR_COPY< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UsingPathDefinition: // UsingPathDefinition
        value.YY_MOVE_OR_COPY< UsingPathDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BINARY: // "binary"
      case symbol_kind::S_HEXADECIMAL: // "hexadecimal"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_RATIONAL: // "rational"
      case symbol_kind::S_DECIMAL: // "decimal"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_BooleanLiteral: // BooleanLiteral
      case symbol_kind::S_IntegerLiteral: // IntegerLiteral
      case symbol_kind::S_RationalLiteral: // RationalLiteral
      case symbol_kind::S_DecimalLiteral: // DecimalLiteral
      case symbol_kind::S_BinaryLiteral: // BinaryLiteral
      case symbol_kind::S_StringLiteral: // StringLiteral
        value.YY_MOVE_OR_COPY< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VariableBinding: // VariableBinding
        value.YY_MOVE_OR_COPY< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VariableBindings: // VariableBindings
        value.YY_MOVE_OR_COPY< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Variable: // Variable
      case symbol_kind::S_TypedVariable: // TypedVariable
      case symbol_kind::S_AttributedVariable: // AttributedVariable
      case symbol_kind::S_TypedAttributedVariable: // TypedAttributedVariable
        value.YY_MOVE_OR_COPY< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.YY_MOVE_OR_COPY< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.YY_MOVE_OR_COPY< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Type: // Type
        value.YY_MOVE_OR_COPY< libcasm_fe::Ast::Type::Ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_FEATURE: // "feature"
      case symbol_kind::S_IMPLEMENTS: // "implements"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_FUNCTION: // "function"
      case symbol_kind::S_DEFINED: // "defined"
      case symbol_kind::S_SEQ: // "seq"
      case symbol_kind::S_ENDSEQ: // "endseq"
      case symbol_kind::S_PAR: // "par"
      case symbol_kind::S_ENDPAR: // "endpar"
      case symbol_kind::S_SKIP: // "skip"
      case symbol_kind::S_LET: // "let"
      case symbol_kind::S_LOCAL: // "local"
      case symbol_kind::S_IN: // "in"
      case symbol_kind::S_FORALL: // "forall"
      case symbol_kind::S_CHOOSE: // "choose"
      case symbol_kind::S_ITERATE: // "iterate"
      case symbol_kind::S_DO: // "do"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_THEN: // "then"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_CASE: // "case"
      case symbol_kind::S_OF: // "of"
      case symbol_kind::S_DEFAULT: // "default"
      case symbol_kind::S_HOLDS: // "holds"
      case symbol_kind::S_EXISTS: // "exists"
      case symbol_kind::S_WITH: // "with"
      case symbol_kind::S_AS: // "as"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_UNDEF: // "undef"
      case symbol_kind::S_FALSE: // "false"
      case symbol_kind::S_TRUE: // "true"
      case symbol_kind::S_AND: // "and"
      case symbol_kind::S_OR: // "or"
      case symbol_kind::S_XOR: // "xor"
      case symbol_kind::S_IMPLIES: // "implies"
      case symbol_kind::S_NOT: // "not"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_EQUAL: // "="
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LSQPAREN: // "["
      case symbol_kind::S_RSQPAREN: // "]"
      case symbol_kind::S_LCURPAREN: // "{"
      case symbol_kind::S_RCURPAREN: // "}"
      case symbol_kind::S_COLON: // ":"
      case symbol_kind::S_DOUBLECOLON: // "::"
      case symbol_kind::S_UNDERLINE: // "_"
      case symbol_kind::S_VERTICAL_BAR: // "|"
      case symbol_kind::S_AT: // "@"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_LESSER: // "<"
      case symbol_kind::S_GREATER: // ">"
      case symbol_kind::S_ASTERIX: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_CARET: // "^"
      case symbol_kind::S_MARK: // "'"
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
        value.move< Ast::Token::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Attribute: // Attribute
        value.move< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Attributes: // Attributes
        value.move< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BasicAttribute: // BasicAttribute
        value.move< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BasicType: // BasicType
        value.move< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.move< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CallExpression: // CallExpression
        value.move< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CallRule: // CallRule
        value.move< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CardinalityExpression: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CaseLabel: // CaseLabel
        value.move< Case::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CaseRule: // CaseRule
        value.move< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CaseLabels: // CaseLabels
        value.move< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ChooseExpression: // ChooseExpression
        value.move< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ChooseRule: // ChooseRule
        value.move< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConditionalExpression: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConditionalRule: // ConditionalRule
        value.move< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DeclarationDefinition: // DeclarationDefinition
        value.move< DeclarationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.move< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDeclarationOrDefinition: // FeatureDeclarationOrDefinition
      case symbol_kind::S_ImplementationDefinitionDefinition: // ImplementationDefinitionDefinition
        value.move< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDeclarationsAndDefinitions: // FeatureDeclarationsAndDefinitions
      case symbol_kind::S_ImplementationDefinitionDefinitions: // ImplementationDefinitionDefinitions
        value.move< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_EnumerationDefinition: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_EnumeratorDefinition: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Enumerators: // Enumerators
        value.move< Enumerators::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExistentialQuantifierExpression: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Term: // Term
      case symbol_kind::S_SimpleOrClaspedTerm: // SimpleOrClaspedTerm
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.move< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Terms: // Terms
        value.move< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FeatureDefinition: // FeatureDefinition
        value.move< FeatureDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FixedSizedType: // FixedSizedType
        value.move< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ForallRule: // ForallRule
        value.move< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FunctionDefinition: // FunctionDefinition
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.move< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LocalFunctionDefinitions: // LocalFunctionDefinitions
        value.move< FunctionDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Header: // Header
        value.move< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_Identifier: // Identifier
        value.move< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IdentifierPath: // IdentifierPath
        value.move< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ImplementationDefinition: // ImplementationDefinition
        value.move< ImplementationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ImportDefinition: // ImportDefinition
        value.move< ImportDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IndirectCallExpression: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitDefinition: // InitDefinition
        value.move< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Initializer: // Initializer
        value.move< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Initializers: // Initializers
        value.move< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MaybeInitially: // MaybeInitially
        value.move< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InvariantDefinition: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IterateRule: // IterateRule
        value.move< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LetExpression: // LetExpression
        value.move< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LetRule: // LetRule
        value.move< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ListLiteral: // ListLiteral
        value.move< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Literal: // Literal
        value.move< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LiteralCallExpression: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LocalRule: // LocalRule
        value.move< LocalRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MethodCallExpression: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Assignment: // Assignment
        value.move< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Assignments: // Assignments
        value.move< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RangeLiteral: // RangeLiteral
        value.move< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RecordLiteral: // RecordLiteral
        value.move< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RecordType: // RecordType
        value.move< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ReferenceLiteral: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RelationType: // RelationType
        value.move< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Rule: // Rule
        value.move< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RuleDefinition: // RuleDefinition
        value.move< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Rules: // Rules
        value.move< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SequenceRule: // SequenceRule
        value.move< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SkipRule: // SkipRule
        value.move< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Specification: // Specification
        value.move< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_StructureDefinition: // StructureDefinition
        value.move< StructureDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TemplateType: // TemplateType
        value.move< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TupleLiteral: // TupleLiteral
        value.move< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TupleType: // TupleType
        value.move< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TypeCastingExpression: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Types: // Types
      case symbol_kind::S_FunctionParameters: // FunctionParameters
      case symbol_kind::S_MaybeFunctionParameters: // MaybeFunctionParameters
        value.move< Types::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UndefinedLiteral: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UniversalQuantifierExpression: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UpdateRule: // UpdateRule
        value.move< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UsingDefinition: // UsingDefinition
        value.move< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UsingPathDefinition: // UsingPathDefinition
        value.move< UsingPathDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BINARY: // "binary"
      case symbol_kind::S_HEXADECIMAL: // "hexadecimal"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_RATIONAL: // "rational"
      case symbol_kind::S_DECIMAL: // "decimal"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_BooleanLiteral: // BooleanLiteral
      case symbol_kind::S_IntegerLiteral: // IntegerLiteral
      case symbol_kind::S_RationalLiteral: // RationalLiteral
      case symbol_kind::S_DecimalLiteral: // DecimalLiteral
      case symbol_kind::S_BinaryLiteral: // BinaryLiteral
      case symbol_kind::S_StringLiteral: // StringLiteral
        value.move< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VariableBinding: // VariableBinding
        value.move< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VariableBindings: // VariableBindings
        value.move< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Variable: // Variable
      case symbol_kind::S_TypedVariable: // TypedVariable
      case symbol_kind::S_AttributedVariable: // AttributedVariable
      case symbol_kind::S_TypedAttributedVariable: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.move< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.move< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Type: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_FEATURE: // "feature"
      case symbol_kind::S_IMPLEMENTS: // "implements"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_FUNCTION: // "function"
      case symbol_kind::S_DEFINED: // "defined"
      case symbol_kind::S_SEQ: // "seq"
      case symbol_kind::S_ENDSEQ: // "endseq"
      case symbol_kind::S_PAR: // "par"
      case symbol_kind::S_ENDPAR: // "endpar"
      case symbol_kind::S_SKIP: // "skip"
      case symbol_kind::S_LET: // "let"
      case symbol_kind::S_LOCAL: // "local"
      case symbol_kind::S_IN: // "in"
      case symbol_kind::S_FORALL: // "forall"
      case symbol_kind::S_CHOOSE: // "choose"
      case symbol_kind::S_ITERATE: // "iterate"
      case symbol_kind::S_DO: // "do"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_THEN: // "then"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_CASE: // "case"
      case symbol_kind::S_OF: // "of"
      case symbol_kind::S_DEFAULT: // "default"
      case symbol_kind::S_HOLDS: // "holds"
      case symbol_kind::S_EXISTS: // "exists"
      case symbol_kind::S_WITH: // "with"
      case symbol_kind::S_AS: // "as"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_UNDEF: // "undef"
      case symbol_kind::S_FALSE: // "false"
      case symbol_kind::S_TRUE: // "true"
      case symbol_kind::S_AND: // "and"
      case symbol_kind::S_OR: // "or"
      case symbol_kind::S_XOR: // "xor"
      case symbol_kind::S_IMPLIES: // "implies"
      case symbol_kind::S_NOT: // "not"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_EQUAL: // "="
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LSQPAREN: // "["
      case symbol_kind::S_RSQPAREN: // "]"
      case symbol_kind::S_LCURPAREN: // "{"
      case symbol_kind::S_RCURPAREN: // "}"
      case symbol_kind::S_COLON: // ":"
      case symbol_kind::S_DOUBLECOLON: // "::"
      case symbol_kind::S_UNDERLINE: // "_"
      case symbol_kind::S_VERTICAL_BAR: // "|"
      case symbol_kind::S_AT: // "@"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_LESSER: // "<"
      case symbol_kind::S_GREATER: // ">"
      case symbol_kind::S_ASTERIX: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_CARET: // "^"
      case symbol_kind::S_MARK: // "'"
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
        value.copy< Ast::Token::Ptr > (that.value);
        break;

      case symbol_kind::S_Attribute: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case symbol_kind::S_Attributes: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case symbol_kind::S_BasicAttribute: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case symbol_kind::S_BasicType: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case symbol_kind::S_CallExpression: // CallExpression
        value.copy< CallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_CallRule: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case symbol_kind::S_CardinalityExpression: // CardinalityExpression
        value.copy< CardinalityExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_CaseLabel: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case symbol_kind::S_CaseRule: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case symbol_kind::S_CaseLabels: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case symbol_kind::S_ChooseExpression: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_ChooseRule: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case symbol_kind::S_ConditionalExpression: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_ConditionalRule: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case symbol_kind::S_DeclarationDefinition: // DeclarationDefinition
        value.copy< DeclarationDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.copy< Defined::Ptr > (that.value);
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDeclarationOrDefinition: // FeatureDeclarationOrDefinition
      case symbol_kind::S_ImplementationDefinitionDefinition: // ImplementationDefinitionDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDeclarationsAndDefinitions: // FeatureDeclarationsAndDefinitions
      case symbol_kind::S_ImplementationDefinitionDefinitions: // ImplementationDefinitionDefinitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_EnumerationDefinition: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_EnumeratorDefinition: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_Enumerators: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case symbol_kind::S_ExistentialQuantifierExpression: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_Term: // Term
      case symbol_kind::S_SimpleOrClaspedTerm: // SimpleOrClaspedTerm
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.copy< Expression::Ptr > (that.value);
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case symbol_kind::S_Terms: // Terms
        value.copy< Expressions::Ptr > (that.value);
        break;

      case symbol_kind::S_FeatureDefinition: // FeatureDefinition
        value.copy< FeatureDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_FixedSizedType: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case symbol_kind::S_ForallRule: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case symbol_kind::S_FunctionDefinition: // FunctionDefinition
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_LocalFunctionDefinitions: // LocalFunctionDefinitions
        value.copy< FunctionDefinitions::Ptr > (that.value);
        break;

      case symbol_kind::S_Header: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_Identifier: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case symbol_kind::S_IdentifierPath: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case symbol_kind::S_ImplementationDefinition: // ImplementationDefinition
        value.copy< ImplementationDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_ImportDefinition: // ImportDefinition
        value.copy< ImportDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_IndirectCallExpression: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_InitDefinition: // InitDefinition
        value.copy< InitDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_Initializer: // Initializer
        value.copy< Initializer::Ptr > (that.value);
        break;

      case symbol_kind::S_Initializers: // Initializers
        value.copy< Initializers::Ptr > (that.value);
        break;

      case symbol_kind::S_MaybeInitially: // MaybeInitially
        value.copy< Initially::Ptr > (that.value);
        break;

      case symbol_kind::S_InvariantDefinition: // InvariantDefinition
        value.copy< InvariantDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_IterateRule: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case symbol_kind::S_LetExpression: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_LetRule: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case symbol_kind::S_ListLiteral: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_Literal: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case symbol_kind::S_LiteralCallExpression: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_LocalRule: // LocalRule
        value.copy< LocalRule::Ptr > (that.value);
        break;

      case symbol_kind::S_MethodCallExpression: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_Assignment: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_Assignments: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case symbol_kind::S_RangeLiteral: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_RecordLiteral: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_RecordType: // RecordType
        value.copy< RecordType::Ptr > (that.value);
        break;

      case symbol_kind::S_ReferenceLiteral: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_RelationType: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case symbol_kind::S_Rule: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case symbol_kind::S_RuleDefinition: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_Rules: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case symbol_kind::S_SequenceRule: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case symbol_kind::S_SkipRule: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case symbol_kind::S_Specification: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case symbol_kind::S_StructureDefinition: // StructureDefinition
        value.copy< StructureDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_TemplateType: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case symbol_kind::S_TupleLiteral: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_TupleType: // TupleType
        value.copy< TupleType::Ptr > (that.value);
        break;

      case symbol_kind::S_TypeCastingExpression: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_Types: // Types
      case symbol_kind::S_FunctionParameters: // FunctionParameters
      case symbol_kind::S_MaybeFunctionParameters: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case symbol_kind::S_UndefinedLiteral: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_UniversalQuantifierExpression: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_UpdateRule: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case symbol_kind::S_UsingDefinition: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_UsingPathDefinition: // UsingPathDefinition
        value.copy< UsingPathDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_BINARY: // "binary"
      case symbol_kind::S_HEXADECIMAL: // "hexadecimal"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_RATIONAL: // "rational"
      case symbol_kind::S_DECIMAL: // "decimal"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_BooleanLiteral: // BooleanLiteral
      case symbol_kind::S_IntegerLiteral: // IntegerLiteral
      case symbol_kind::S_RationalLiteral: // RationalLiteral
      case symbol_kind::S_DecimalLiteral: // DecimalLiteral
      case symbol_kind::S_BinaryLiteral: // BinaryLiteral
      case symbol_kind::S_StringLiteral: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_VariableBinding: // VariableBinding
        value.copy< VariableBinding::Ptr > (that.value);
        break;

      case symbol_kind::S_VariableBindings: // VariableBindings
        value.copy< VariableBindings::Ptr > (that.value);
        break;

      case symbol_kind::S_Variable: // Variable
      case symbol_kind::S_TypedVariable: // TypedVariable
      case symbol_kind::S_AttributedVariable: // AttributedVariable
      case symbol_kind::S_TypedAttributedVariable: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.copy< WhileRule::Ptr > (that.value);
        break;

      case symbol_kind::S_Type: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_FEATURE: // "feature"
      case symbol_kind::S_IMPLEMENTS: // "implements"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_FUNCTION: // "function"
      case symbol_kind::S_DEFINED: // "defined"
      case symbol_kind::S_SEQ: // "seq"
      case symbol_kind::S_ENDSEQ: // "endseq"
      case symbol_kind::S_PAR: // "par"
      case symbol_kind::S_ENDPAR: // "endpar"
      case symbol_kind::S_SKIP: // "skip"
      case symbol_kind::S_LET: // "let"
      case symbol_kind::S_LOCAL: // "local"
      case symbol_kind::S_IN: // "in"
      case symbol_kind::S_FORALL: // "forall"
      case symbol_kind::S_CHOOSE: // "choose"
      case symbol_kind::S_ITERATE: // "iterate"
      case symbol_kind::S_DO: // "do"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_THEN: // "then"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_CASE: // "case"
      case symbol_kind::S_OF: // "of"
      case symbol_kind::S_DEFAULT: // "default"
      case symbol_kind::S_HOLDS: // "holds"
      case symbol_kind::S_EXISTS: // "exists"
      case symbol_kind::S_WITH: // "with"
      case symbol_kind::S_AS: // "as"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_UNDEF: // "undef"
      case symbol_kind::S_FALSE: // "false"
      case symbol_kind::S_TRUE: // "true"
      case symbol_kind::S_AND: // "and"
      case symbol_kind::S_OR: // "or"
      case symbol_kind::S_XOR: // "xor"
      case symbol_kind::S_IMPLIES: // "implies"
      case symbol_kind::S_NOT: // "not"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_EQUAL: // "="
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LSQPAREN: // "["
      case symbol_kind::S_RSQPAREN: // "]"
      case symbol_kind::S_LCURPAREN: // "{"
      case symbol_kind::S_RCURPAREN: // "}"
      case symbol_kind::S_COLON: // ":"
      case symbol_kind::S_DOUBLECOLON: // "::"
      case symbol_kind::S_UNDERLINE: // "_"
      case symbol_kind::S_VERTICAL_BAR: // "|"
      case symbol_kind::S_AT: // "@"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_LESSER: // "<"
      case symbol_kind::S_GREATER: // ">"
      case symbol_kind::S_ASTERIX: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_CARET: // "^"
      case symbol_kind::S_MARK: // "'"
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
        value.move< Ast::Token::Ptr > (that.value);
        break;

      case symbol_kind::S_Attribute: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case symbol_kind::S_Attributes: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case symbol_kind::S_BasicAttribute: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case symbol_kind::S_BasicType: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case symbol_kind::S_CallExpression: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_CallRule: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case symbol_kind::S_CardinalityExpression: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_CaseLabel: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case symbol_kind::S_CaseRule: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case symbol_kind::S_CaseLabels: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case symbol_kind::S_ChooseExpression: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_ChooseRule: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case symbol_kind::S_ConditionalExpression: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_ConditionalRule: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case symbol_kind::S_DeclarationDefinition: // DeclarationDefinition
        value.move< DeclarationDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.move< Defined::Ptr > (that.value);
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDeclarationOrDefinition: // FeatureDeclarationOrDefinition
      case symbol_kind::S_ImplementationDefinitionDefinition: // ImplementationDefinitionDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDeclarationsAndDefinitions: // FeatureDeclarationsAndDefinitions
      case symbol_kind::S_ImplementationDefinitionDefinitions: // ImplementationDefinitionDefinitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_EnumerationDefinition: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_EnumeratorDefinition: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_Enumerators: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case symbol_kind::S_ExistentialQuantifierExpression: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_Term: // Term
      case symbol_kind::S_SimpleOrClaspedTerm: // SimpleOrClaspedTerm
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.move< Expression::Ptr > (that.value);
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case symbol_kind::S_Terms: // Terms
        value.move< Expressions::Ptr > (that.value);
        break;

      case symbol_kind::S_FeatureDefinition: // FeatureDefinition
        value.move< FeatureDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_FixedSizedType: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case symbol_kind::S_ForallRule: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case symbol_kind::S_FunctionDefinition: // FunctionDefinition
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_LocalFunctionDefinitions: // LocalFunctionDefinitions
        value.move< FunctionDefinitions::Ptr > (that.value);
        break;

      case symbol_kind::S_Header: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_Identifier: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case symbol_kind::S_IdentifierPath: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case symbol_kind::S_ImplementationDefinition: // ImplementationDefinition
        value.move< ImplementationDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_ImportDefinition: // ImportDefinition
        value.move< ImportDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_IndirectCallExpression: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_InitDefinition: // InitDefinition
        value.move< InitDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_Initializer: // Initializer
        value.move< Initializer::Ptr > (that.value);
        break;

      case symbol_kind::S_Initializers: // Initializers
        value.move< Initializers::Ptr > (that.value);
        break;

      case symbol_kind::S_MaybeInitially: // MaybeInitially
        value.move< Initially::Ptr > (that.value);
        break;

      case symbol_kind::S_InvariantDefinition: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_IterateRule: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case symbol_kind::S_LetExpression: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_LetRule: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case symbol_kind::S_ListLiteral: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_Literal: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case symbol_kind::S_LiteralCallExpression: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_LocalRule: // LocalRule
        value.move< LocalRule::Ptr > (that.value);
        break;

      case symbol_kind::S_MethodCallExpression: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_Assignment: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_Assignments: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case symbol_kind::S_RangeLiteral: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_RecordLiteral: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_RecordType: // RecordType
        value.move< RecordType::Ptr > (that.value);
        break;

      case symbol_kind::S_ReferenceLiteral: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_RelationType: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case symbol_kind::S_Rule: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case symbol_kind::S_RuleDefinition: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_Rules: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case symbol_kind::S_SequenceRule: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case symbol_kind::S_SkipRule: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case symbol_kind::S_Specification: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case symbol_kind::S_StructureDefinition: // StructureDefinition
        value.move< StructureDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_TemplateType: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case symbol_kind::S_TupleLiteral: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_TupleType: // TupleType
        value.move< TupleType::Ptr > (that.value);
        break;

      case symbol_kind::S_TypeCastingExpression: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_Types: // Types
      case symbol_kind::S_FunctionParameters: // FunctionParameters
      case symbol_kind::S_MaybeFunctionParameters: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case symbol_kind::S_UndefinedLiteral: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_UniversalQuantifierExpression: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_UpdateRule: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case symbol_kind::S_UsingDefinition: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_UsingPathDefinition: // UsingPathDefinition
        value.move< UsingPathDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_BINARY: // "binary"
      case symbol_kind::S_HEXADECIMAL: // "hexadecimal"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_RATIONAL: // "rational"
      case symbol_kind::S_DECIMAL: // "decimal"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_BooleanLiteral: // BooleanLiteral
      case symbol_kind::S_IntegerLiteral: // IntegerLiteral
      case symbol_kind::S_RationalLiteral: // RationalLiteral
      case symbol_kind::S_DecimalLiteral: // DecimalLiteral
      case symbol_kind::S_BinaryLiteral: // BinaryLiteral
      case symbol_kind::S_StringLiteral: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case symbol_kind::S_VariableBinding: // VariableBinding
        value.move< VariableBinding::Ptr > (that.value);
        break;

      case symbol_kind::S_VariableBindings: // VariableBindings
        value.move< VariableBindings::Ptr > (that.value);
        break;

      case symbol_kind::S_Variable: // Variable
      case symbol_kind::S_TypedVariable: // TypedVariable
      case symbol_kind::S_AttributedVariable: // AttributedVariable
      case symbol_kind::S_TypedAttributedVariable: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case symbol_kind::S_Type: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
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

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

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
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_FEATURE: // "feature"
      case symbol_kind::S_IMPLEMENTS: // "implements"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_FUNCTION: // "function"
      case symbol_kind::S_DEFINED: // "defined"
      case symbol_kind::S_SEQ: // "seq"
      case symbol_kind::S_ENDSEQ: // "endseq"
      case symbol_kind::S_PAR: // "par"
      case symbol_kind::S_ENDPAR: // "endpar"
      case symbol_kind::S_SKIP: // "skip"
      case symbol_kind::S_LET: // "let"
      case symbol_kind::S_LOCAL: // "local"
      case symbol_kind::S_IN: // "in"
      case symbol_kind::S_FORALL: // "forall"
      case symbol_kind::S_CHOOSE: // "choose"
      case symbol_kind::S_ITERATE: // "iterate"
      case symbol_kind::S_DO: // "do"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_THEN: // "then"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_CASE: // "case"
      case symbol_kind::S_OF: // "of"
      case symbol_kind::S_DEFAULT: // "default"
      case symbol_kind::S_HOLDS: // "holds"
      case symbol_kind::S_EXISTS: // "exists"
      case symbol_kind::S_WITH: // "with"
      case symbol_kind::S_AS: // "as"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_UNDEF: // "undef"
      case symbol_kind::S_FALSE: // "false"
      case symbol_kind::S_TRUE: // "true"
      case symbol_kind::S_AND: // "and"
      case symbol_kind::S_OR: // "or"
      case symbol_kind::S_XOR: // "xor"
      case symbol_kind::S_IMPLIES: // "implies"
      case symbol_kind::S_NOT: // "not"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_EQUAL: // "="
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LSQPAREN: // "["
      case symbol_kind::S_RSQPAREN: // "]"
      case symbol_kind::S_LCURPAREN: // "{"
      case symbol_kind::S_RCURPAREN: // "}"
      case symbol_kind::S_COLON: // ":"
      case symbol_kind::S_DOUBLECOLON: // "::"
      case symbol_kind::S_UNDERLINE: // "_"
      case symbol_kind::S_VERTICAL_BAR: // "|"
      case symbol_kind::S_AT: // "@"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_LESSER: // "<"
      case symbol_kind::S_GREATER: // ">"
      case symbol_kind::S_ASTERIX: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_CARET: // "^"
      case symbol_kind::S_MARK: // "'"
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
        yylhs.value.emplace< Ast::Token::Ptr > ();
        break;

      case symbol_kind::S_Attribute: // Attribute
        yylhs.value.emplace< Attribute::Ptr > ();
        break;

      case symbol_kind::S_Attributes: // Attributes
        yylhs.value.emplace< Attributes::Ptr > ();
        break;

      case symbol_kind::S_BasicAttribute: // BasicAttribute
        yylhs.value.emplace< BasicAttribute::Ptr > ();
        break;

      case symbol_kind::S_BasicType: // BasicType
        yylhs.value.emplace< BasicType::Ptr > ();
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        yylhs.value.emplace< BlockRule::Ptr > ();
        break;

      case symbol_kind::S_CallExpression: // CallExpression
        yylhs.value.emplace< CallExpression::Ptr > ();
        break;

      case symbol_kind::S_CallRule: // CallRule
        yylhs.value.emplace< CallRule::Ptr > ();
        break;

      case symbol_kind::S_CardinalityExpression: // CardinalityExpression
        yylhs.value.emplace< CardinalityExpression::Ptr > ();
        break;

      case symbol_kind::S_CaseLabel: // CaseLabel
        yylhs.value.emplace< Case::Ptr > ();
        break;

      case symbol_kind::S_CaseRule: // CaseRule
        yylhs.value.emplace< CaseRule::Ptr > ();
        break;

      case symbol_kind::S_CaseLabels: // CaseLabels
        yylhs.value.emplace< Cases::Ptr > ();
        break;

      case symbol_kind::S_ChooseExpression: // ChooseExpression
        yylhs.value.emplace< ChooseExpression::Ptr > ();
        break;

      case symbol_kind::S_ChooseRule: // ChooseRule
        yylhs.value.emplace< ChooseRule::Ptr > ();
        break;

      case symbol_kind::S_ConditionalExpression: // ConditionalExpression
        yylhs.value.emplace< ConditionalExpression::Ptr > ();
        break;

      case symbol_kind::S_ConditionalRule: // ConditionalRule
        yylhs.value.emplace< ConditionalRule::Ptr > ();
        break;

      case symbol_kind::S_DeclarationDefinition: // DeclarationDefinition
        yylhs.value.emplace< DeclarationDefinition::Ptr > ();
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        yylhs.value.emplace< Defined::Ptr > ();
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDeclarationOrDefinition: // FeatureDeclarationOrDefinition
      case symbol_kind::S_ImplementationDefinitionDefinition: // ImplementationDefinitionDefinition
        yylhs.value.emplace< Definition::Ptr > ();
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDeclarationsAndDefinitions: // FeatureDeclarationsAndDefinitions
      case symbol_kind::S_ImplementationDefinitionDefinitions: // ImplementationDefinitionDefinitions
        yylhs.value.emplace< Definitions::Ptr > ();
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        yylhs.value.emplace< DerivedDefinition::Ptr > ();
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        yylhs.value.emplace< DirectCallExpression::Ptr > ();
        break;

      case symbol_kind::S_EnumerationDefinition: // EnumerationDefinition
        yylhs.value.emplace< EnumerationDefinition::Ptr > ();
        break;

      case symbol_kind::S_EnumeratorDefinition: // EnumeratorDefinition
        yylhs.value.emplace< EnumeratorDefinition::Ptr > ();
        break;

      case symbol_kind::S_Enumerators: // Enumerators
        yylhs.value.emplace< Enumerators::Ptr > ();
        break;

      case symbol_kind::S_ExistentialQuantifierExpression: // ExistentialQuantifierExpression
        yylhs.value.emplace< ExistentialQuantifierExpression::Ptr > ();
        break;

      case symbol_kind::S_Term: // Term
      case symbol_kind::S_SimpleOrClaspedTerm: // SimpleOrClaspedTerm
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        yylhs.value.emplace< Expression::Ptr > ();
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        yylhs.value.emplace< ExpressionAttribute::Ptr > ();
        break;

      case symbol_kind::S_Terms: // Terms
        yylhs.value.emplace< Expressions::Ptr > ();
        break;

      case symbol_kind::S_FeatureDefinition: // FeatureDefinition
        yylhs.value.emplace< FeatureDefinition::Ptr > ();
        break;

      case symbol_kind::S_FixedSizedType: // FixedSizedType
        yylhs.value.emplace< FixedSizedType::Ptr > ();
        break;

      case symbol_kind::S_ForallRule: // ForallRule
        yylhs.value.emplace< ForallRule::Ptr > ();
        break;

      case symbol_kind::S_FunctionDefinition: // FunctionDefinition
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        yylhs.value.emplace< FunctionDefinition::Ptr > ();
        break;

      case symbol_kind::S_LocalFunctionDefinitions: // LocalFunctionDefinitions
        yylhs.value.emplace< FunctionDefinitions::Ptr > ();
        break;

      case symbol_kind::S_Header: // Header
        yylhs.value.emplace< HeaderDefinition::Ptr > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_Identifier: // Identifier
        yylhs.value.emplace< Identifier::Ptr > ();
        break;

      case symbol_kind::S_IdentifierPath: // IdentifierPath
        yylhs.value.emplace< IdentifierPath::Ptr > ();
        break;

      case symbol_kind::S_ImplementationDefinition: // ImplementationDefinition
        yylhs.value.emplace< ImplementationDefinition::Ptr > ();
        break;

      case symbol_kind::S_ImportDefinition: // ImportDefinition
        yylhs.value.emplace< ImportDefinition::Ptr > ();
        break;

      case symbol_kind::S_IndirectCallExpression: // IndirectCallExpression
        yylhs.value.emplace< IndirectCallExpression::Ptr > ();
        break;

      case symbol_kind::S_InitDefinition: // InitDefinition
        yylhs.value.emplace< InitDefinition::Ptr > ();
        break;

      case symbol_kind::S_Initializer: // Initializer
        yylhs.value.emplace< Initializer::Ptr > ();
        break;

      case symbol_kind::S_Initializers: // Initializers
        yylhs.value.emplace< Initializers::Ptr > ();
        break;

      case symbol_kind::S_MaybeInitially: // MaybeInitially
        yylhs.value.emplace< Initially::Ptr > ();
        break;

      case symbol_kind::S_InvariantDefinition: // InvariantDefinition
        yylhs.value.emplace< InvariantDefinition::Ptr > ();
        break;

      case symbol_kind::S_IterateRule: // IterateRule
        yylhs.value.emplace< IterateRule::Ptr > ();
        break;

      case symbol_kind::S_LetExpression: // LetExpression
        yylhs.value.emplace< LetExpression::Ptr > ();
        break;

      case symbol_kind::S_LetRule: // LetRule
        yylhs.value.emplace< LetRule::Ptr > ();
        break;

      case symbol_kind::S_ListLiteral: // ListLiteral
        yylhs.value.emplace< ListLiteral::Ptr > ();
        break;

      case symbol_kind::S_Literal: // Literal
        yylhs.value.emplace< Literal::Ptr > ();
        break;

      case symbol_kind::S_LiteralCallExpression: // LiteralCallExpression
        yylhs.value.emplace< LiteralCallExpression::Ptr > ();
        break;

      case symbol_kind::S_LocalRule: // LocalRule
        yylhs.value.emplace< LocalRule::Ptr > ();
        break;

      case symbol_kind::S_MethodCallExpression: // MethodCallExpression
        yylhs.value.emplace< MethodCallExpression::Ptr > ();
        break;

      case symbol_kind::S_Assignment: // Assignment
        yylhs.value.emplace< NamedExpression::Ptr > ();
        break;

      case symbol_kind::S_Assignments: // Assignments
        yylhs.value.emplace< NamedExpressions::Ptr > ();
        break;

      case symbol_kind::S_RangeLiteral: // RangeLiteral
        yylhs.value.emplace< RangeLiteral::Ptr > ();
        break;

      case symbol_kind::S_RecordLiteral: // RecordLiteral
        yylhs.value.emplace< RecordLiteral::Ptr > ();
        break;

      case symbol_kind::S_RecordType: // RecordType
        yylhs.value.emplace< RecordType::Ptr > ();
        break;

      case symbol_kind::S_ReferenceLiteral: // ReferenceLiteral
        yylhs.value.emplace< ReferenceLiteral::Ptr > ();
        break;

      case symbol_kind::S_RelationType: // RelationType
        yylhs.value.emplace< RelationType::Ptr > ();
        break;

      case symbol_kind::S_Rule: // Rule
        yylhs.value.emplace< Rule::Ptr > ();
        break;

      case symbol_kind::S_RuleDefinition: // RuleDefinition
        yylhs.value.emplace< RuleDefinition::Ptr > ();
        break;

      case symbol_kind::S_Rules: // Rules
        yylhs.value.emplace< Rules::Ptr > ();
        break;

      case symbol_kind::S_SequenceRule: // SequenceRule
        yylhs.value.emplace< SequenceRule::Ptr > ();
        break;

      case symbol_kind::S_SkipRule: // SkipRule
        yylhs.value.emplace< SkipRule::Ptr > ();
        break;

      case symbol_kind::S_Specification: // Specification
        yylhs.value.emplace< Specification::Ptr > ();
        break;

      case symbol_kind::S_StructureDefinition: // StructureDefinition
        yylhs.value.emplace< StructureDefinition::Ptr > ();
        break;

      case symbol_kind::S_TemplateType: // TemplateType
        yylhs.value.emplace< TemplateType::Ptr > ();
        break;

      case symbol_kind::S_TupleLiteral: // TupleLiteral
        yylhs.value.emplace< TupleLiteral::Ptr > ();
        break;

      case symbol_kind::S_TupleType: // TupleType
        yylhs.value.emplace< TupleType::Ptr > ();
        break;

      case symbol_kind::S_TypeCastingExpression: // TypeCastingExpression
        yylhs.value.emplace< TypeCastingExpression::Ptr > ();
        break;

      case symbol_kind::S_Types: // Types
      case symbol_kind::S_FunctionParameters: // FunctionParameters
      case symbol_kind::S_MaybeFunctionParameters: // MaybeFunctionParameters
        yylhs.value.emplace< Types::Ptr > ();
        break;

      case symbol_kind::S_UndefinedLiteral: // UndefinedLiteral
        yylhs.value.emplace< UndefLiteral::Ptr > ();
        break;

      case symbol_kind::S_UniversalQuantifierExpression: // UniversalQuantifierExpression
        yylhs.value.emplace< UniversalQuantifierExpression::Ptr > ();
        break;

      case symbol_kind::S_UpdateRule: // UpdateRule
        yylhs.value.emplace< UpdateRule::Ptr > ();
        break;

      case symbol_kind::S_UsingDefinition: // UsingDefinition
        yylhs.value.emplace< UsingDefinition::Ptr > ();
        break;

      case symbol_kind::S_UsingPathDefinition: // UsingPathDefinition
        yylhs.value.emplace< UsingPathDefinition::Ptr > ();
        break;

      case symbol_kind::S_BINARY: // "binary"
      case symbol_kind::S_HEXADECIMAL: // "hexadecimal"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_RATIONAL: // "rational"
      case symbol_kind::S_DECIMAL: // "decimal"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_BooleanLiteral: // BooleanLiteral
      case symbol_kind::S_IntegerLiteral: // IntegerLiteral
      case symbol_kind::S_RationalLiteral: // RationalLiteral
      case symbol_kind::S_DecimalLiteral: // DecimalLiteral
      case symbol_kind::S_BinaryLiteral: // BinaryLiteral
      case symbol_kind::S_StringLiteral: // StringLiteral
        yylhs.value.emplace< ValueLiteral::Ptr > ();
        break;

      case symbol_kind::S_VariableBinding: // VariableBinding
        yylhs.value.emplace< VariableBinding::Ptr > ();
        break;

      case symbol_kind::S_VariableBindings: // VariableBindings
        yylhs.value.emplace< VariableBindings::Ptr > ();
        break;

      case symbol_kind::S_Variable: // Variable
      case symbol_kind::S_TypedVariable: // TypedVariable
      case symbol_kind::S_AttributedVariable: // AttributedVariable
      case symbol_kind::S_TypedAttributedVariable: // TypedAttributedVariable
        yylhs.value.emplace< VariableDefinition::Ptr > ();
        break;

      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        yylhs.value.emplace< VariableDefinitions::Ptr > ();
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        yylhs.value.emplace< WhileRule::Ptr > ();
        break;

      case symbol_kind::S_Type: // Type
        yylhs.value.emplace< libcasm_fe::Ast::Type::Ptr > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // Specification: Header Definitions
#line 432 "../../obj/src/GrammarParser.y"
  {
      m_specification.setHeader( yystack_[1].value.as < HeaderDefinition::Ptr > () );
      m_specification.setDefinitions( yystack_[0].value.as < Definitions::Ptr > () );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 2763 "GrammarParser.cpp"
    break;

  case 3: // Header: Attributes "CASM"
#line 442 "../../obj/src/GrammarParser.y"
  {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2773 "GrammarParser.cpp"
    break;

  case 4: // Header: "CASM"
#line 448 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2781 "GrammarParser.cpp"
    break;

  case 5: // Definitions: Definitions AttributedDefinition
#line 456 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2791 "GrammarParser.cpp"
    break;

  case 6: // Definitions: AttributedDefinition
#line 462 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2801 "GrammarParser.cpp"
    break;

  case 7: // AttributedDefinition: Attributes Definition
#line 472 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2811 "GrammarParser.cpp"
    break;

  case 8: // AttributedDefinition: Definition
#line 478 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2819 "GrammarParser.cpp"
    break;

  case 9: // AttributedDefinition: error
#line 482 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2827 "GrammarParser.cpp"
    break;

  case 10: // Definition: InitDefinition
#line 490 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2835 "GrammarParser.cpp"
    break;

  case 11: // Definition: EnumerationDefinition
#line 494 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2843 "GrammarParser.cpp"
    break;

  case 12: // Definition: DerivedDefinition
#line 498 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2851 "GrammarParser.cpp"
    break;

  case 13: // Definition: RuleDefinition
#line 502 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2859 "GrammarParser.cpp"
    break;

  case 14: // Definition: FunctionDefinition
#line 506 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2867 "GrammarParser.cpp"
    break;

  case 15: // Definition: UsingDefinition
#line 510 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2875 "GrammarParser.cpp"
    break;

  case 16: // Definition: UsingPathDefinition
#line 514 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 2883 "GrammarParser.cpp"
    break;

  case 17: // Definition: InvariantDefinition
#line 518 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 2891 "GrammarParser.cpp"
    break;

  case 18: // Definition: ImportDefinition
#line 522 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 2899 "GrammarParser.cpp"
    break;

  case 19: // Definition: StructureDefinition
#line 526 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < StructureDefinition::Ptr > ();
  }
#line 2907 "GrammarParser.cpp"
    break;

  case 20: // Definition: FeatureDefinition
#line 530 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FeatureDefinition::Ptr > ();
  }
#line 2915 "GrammarParser.cpp"
    break;

  case 21: // Definition: ImplementationDefinition
#line 534 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImplementationDefinition::Ptr > ();
  }
#line 2923 "GrammarParser.cpp"
    break;

  case 22: // InitDefinition: "init" IdentifierPath
#line 542 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2931 "GrammarParser.cpp"
    break;

  case 23: // InitDefinition: "init" "{" Initializers "}"
#line 546 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2939 "GrammarParser.cpp"
    break;

  case 24: // EnumerationDefinition: "enumeration" Identifier "=" "{" Enumerators "}"
#line 554 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2947 "GrammarParser.cpp"
    break;

  case 25: // DerivedDefinition: "derived" Identifier "->" Type "=" Term
#line 562 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2956 "GrammarParser.cpp"
    break;

  case 26: // DerivedDefinition: "derived" Identifier "(" Parameters ")" "->" Type "=" Term
#line 567 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2966 "GrammarParser.cpp"
    break;

  case 27: // DerivedDefinition: "derived" Identifier "(" error ")" "->" Type "=" Term
#line 573 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 2974 "GrammarParser.cpp"
    break;

  case 28: // RuleDefinition: "rule" Identifier "=" Rule
#line 581 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2984 "GrammarParser.cpp"
    break;

  case 29: // RuleDefinition: "rule" Identifier "->" Type "=" Rule
#line 587 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2993 "GrammarParser.cpp"
    break;

  case 30: // RuleDefinition: "rule" Identifier "(" Parameters ")" "=" Rule
#line 592 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 3004 "GrammarParser.cpp"
    break;

  case 31: // RuleDefinition: "rule" Identifier "(" Parameters ")" "->" Type "=" Rule
#line 599 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 3014 "GrammarParser.cpp"
    break;

  case 32: // RuleDefinition: "rule" Identifier "(" error ")" "=" Rule
#line 605 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3022 "GrammarParser.cpp"
    break;

  case 33: // RuleDefinition: "rule" Identifier "(" error ")" "->" Type "=" Rule
#line 609 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3030 "GrammarParser.cpp"
    break;

  case 34: // FunctionDefinition: "function" Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 617 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      const auto initially = yylhs.value.as < FunctionDefinition::Ptr > ()->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->setFunction( yylhs.value.as < FunctionDefinition::Ptr > () );
      }
  }
#line 3045 "GrammarParser.cpp"
    break;

  case 35: // EnumeratorDefinition: Identifier
#line 632 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3053 "GrammarParser.cpp"
    break;

  case 36: // EnumeratorDefinition: Attributes Identifier
#line 636 "../../obj/src/GrammarParser.y"
  {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 3063 "GrammarParser.cpp"
    break;

  case 37: // EnumeratorDefinition: error
#line 642 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 3071 "GrammarParser.cpp"
    break;

  case 38: // Enumerators: Enumerators "," EnumeratorDefinition
#line 650 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3082 "GrammarParser.cpp"
    break;

  case 39: // Enumerators: EnumeratorDefinition
#line 657 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3092 "GrammarParser.cpp"
    break;

  case 40: // UsingDefinition: "using" Identifier "=" Type
#line 667 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3100 "GrammarParser.cpp"
    break;

  case 41: // UsingPathDefinition: "using" IdentifierPath
#line 675 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3108 "GrammarParser.cpp"
    break;

  case 42: // UsingPathDefinition: "using" IdentifierPath "::" "*"
#line 679 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3116 "GrammarParser.cpp"
    break;

  case 43: // InvariantDefinition: "invariant" Identifier "=" Term
#line 687 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3124 "GrammarParser.cpp"
    break;

  case 44: // ImportDefinition: "import" IdentifierPath
#line 695 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3132 "GrammarParser.cpp"
    break;

  case 45: // ImportDefinition: "import" IdentifierPath "as" Identifier
#line 699 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3140 "GrammarParser.cpp"
    break;

  case 46: // StructureDefinition: "structure" Identifier "=" "{" FunctionDefinition "}"
#line 707 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, $4, and $6
      // $$ = Ast::make< StructureDefinition >( @$, $2, $5 );
  }
#line 3149 "GrammarParser.cpp"
    break;

  case 47: // FeatureDefinition: "feature" Identifier "=" "{" FeatureDeclarationsAndDefinitions "}"
#line 716 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, $4, and $6
      yylhs.value.as < FeatureDefinition::Ptr > () = Ast::make< FeatureDefinition >( yylhs.location, yystack_[4].value.as < Identifier::Ptr > (), yystack_[1].value.as < Definitions::Ptr > () );
  }
#line 3158 "GrammarParser.cpp"
    break;

  case 48: // FeatureDeclarationOrDefinition: DeclarationDefinition
#line 725 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DeclarationDefinition::Ptr > ();
  }
#line 3166 "GrammarParser.cpp"
    break;

  case 49: // FeatureDeclarationOrDefinition: DerivedDefinition
#line 729 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3174 "GrammarParser.cpp"
    break;

  case 50: // FeatureDeclarationOrDefinition: RuleDefinition
#line 733 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3182 "GrammarParser.cpp"
    break;

  case 51: // FeatureDeclarationsAndDefinitions: FeatureDeclarationsAndDefinitions FeatureDeclarationOrDefinition
#line 741 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3192 "GrammarParser.cpp"
    break;

  case 52: // FeatureDeclarationsAndDefinitions: FeatureDeclarationOrDefinition
#line 747 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3202 "GrammarParser.cpp"
    break;

  case 53: // ImplementationDefinition: "implements" IdentifierPath "for" Type "=" "{" ImplementationDefinitionDefinitions "}"
#line 757 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementationDefinition::Ptr > () = Ast::make< ImplementationDefinition >( yylhs.location, yystack_[6].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Definitions::Ptr > () );
  }
#line 3210 "GrammarParser.cpp"
    break;

  case 54: // ImplementationDefinition: "implements" Type "=" "{" ImplementationDefinitionDefinitions "}"
#line 761 "../../obj/src/GrammarParser.y"
  {
      const auto name = Ast::make< Identifier >( yylhs.location, "" );
      const auto path = asIdentifierPath( name );
      yylhs.value.as < ImplementationDefinition::Ptr > () = Ast::make< ImplementationDefinition >( yylhs.location, path, yystack_[4].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Definitions::Ptr > () );
  }
#line 3220 "GrammarParser.cpp"
    break;

  case 55: // ImplementationDefinitionDefinition: DerivedDefinition
#line 771 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3228 "GrammarParser.cpp"
    break;

  case 56: // ImplementationDefinitionDefinition: RuleDefinition
#line 775 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3236 "GrammarParser.cpp"
    break;

  case 57: // ImplementationDefinitionDefinitions: ImplementationDefinitionDefinitions ImplementationDefinitionDefinition
#line 783 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3246 "GrammarParser.cpp"
    break;

  case 58: // ImplementationDefinitionDefinitions: ImplementationDefinitionDefinition
#line 789 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3256 "GrammarParser.cpp"
    break;

  case 59: // DeclarationDefinition: "derived" Identifier ":" MaybeFunctionParameters "->" Type
#line 799 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, and $5
      auto declaration = Ast::make< DeclarationDefinition >( yylhs.location, yystack_[4].value.as < Identifier::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      declaration->setKind( DeclarationDefinition::Kind::DERIVED );
      yylhs.value.as < DeclarationDefinition::Ptr > () = declaration;
  }
#line 3267 "GrammarParser.cpp"
    break;

  case 60: // DeclarationDefinition: "rule" Identifier ":" MaybeFunctionParameters "->" Type
#line 806 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, and $5
      auto declaration = Ast::make< DeclarationDefinition >( yylhs.location, yystack_[4].value.as < Identifier::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      declaration->setKind( DeclarationDefinition::Kind::RULE );
      yylhs.value.as < DeclarationDefinition::Ptr > () = declaration;
  }
#line 3278 "GrammarParser.cpp"
    break;

  case 61: // Rules: Rules Rule
#line 821 "../../obj/src/GrammarParser.y"
  {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3288 "GrammarParser.cpp"
    break;

  case 62: // Rules: Rule
#line 827 "../../obj/src/GrammarParser.y"
  {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3298 "GrammarParser.cpp"
    break;

  case 63: // Rule: SkipRule
#line 837 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 3306 "GrammarParser.cpp"
    break;

  case 64: // Rule: ConditionalRule
#line 841 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 3314 "GrammarParser.cpp"
    break;

  case 65: // Rule: CaseRule
#line 845 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 3322 "GrammarParser.cpp"
    break;

  case 66: // Rule: LetRule
#line 849 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 3330 "GrammarParser.cpp"
    break;

  case 67: // Rule: LocalRule
#line 853 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LocalRule::Ptr > ();
  }
#line 3338 "GrammarParser.cpp"
    break;

  case 68: // Rule: ForallRule
#line 857 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 3346 "GrammarParser.cpp"
    break;

  case 69: // Rule: ChooseRule
#line 861 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 3354 "GrammarParser.cpp"
    break;

  case 70: // Rule: IterateRule
#line 865 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 3362 "GrammarParser.cpp"
    break;

  case 71: // Rule: BlockRule
#line 869 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 3370 "GrammarParser.cpp"
    break;

  case 72: // Rule: SequenceRule
#line 873 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 3378 "GrammarParser.cpp"
    break;

  case 73: // Rule: UpdateRule
#line 877 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 3386 "GrammarParser.cpp"
    break;

  case 74: // Rule: CallRule
#line 881 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 3394 "GrammarParser.cpp"
    break;

  case 75: // Rule: WhileRule
#line 885 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 3402 "GrammarParser.cpp"
    break;

  case 76: // SkipRule: "skip"
#line 893 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3410 "GrammarParser.cpp"
    break;

  case 77: // ConditionalRule: "if" Term "then" Rule
#line 901 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3418 "GrammarParser.cpp"
    break;

  case 78: // ConditionalRule: "if" Term "then" Rule "else" Rule
#line 905 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3426 "GrammarParser.cpp"
    break;

  case 79: // CaseRule: "case" Term "of" "{" CaseLabels "}"
#line 913 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3434 "GrammarParser.cpp"
    break;

  case 80: // CaseRule: "case" Term "of" "{" error "}"
#line 917 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 3442 "GrammarParser.cpp"
    break;

  case 81: // CaseLabels: CaseLabels CaseLabel
#line 925 "../../obj/src/GrammarParser.y"
  {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3452 "GrammarParser.cpp"
    break;

  case 82: // CaseLabels: CaseLabel
#line 931 "../../obj/src/GrammarParser.y"
  {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3462 "GrammarParser.cpp"
    break;

  case 83: // CaseLabel: "default" ":" Rule
#line 941 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3470 "GrammarParser.cpp"
    break;

  case 84: // CaseLabel: "_" ":" Rule
#line 945 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3478 "GrammarParser.cpp"
    break;

  case 85: // CaseLabel: Term ":" Rule
#line 949 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3486 "GrammarParser.cpp"
    break;

  case 86: // LetRule: "let" VariableBindings "in" Rule
#line 957 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3494 "GrammarParser.cpp"
    break;

  case 87: // LocalRule: "local" LocalFunctionDefinitions "in" Rule
#line 965 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LocalRule::Ptr > () = Ast::make< LocalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < FunctionDefinitions::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3502 "GrammarParser.cpp"
    break;

  case 88: // ForallRule: "forall" AttributedVariables "in" Term "do" Rule
#line 973 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3510 "GrammarParser.cpp"
    break;

  case 89: // ForallRule: "forall" AttributedVariables "in" Term "with" Term "do" Rule
#line 977 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3518 "GrammarParser.cpp"
    break;

  case 90: // ChooseRule: "choose" AttributedVariables "in" Term "do" Rule
#line 985 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3526 "GrammarParser.cpp"
    break;

  case 91: // IterateRule: "iterate" Rule
#line 993 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3534 "GrammarParser.cpp"
    break;

  case 92: // BlockRule: "{" Rules "}"
#line 1001 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3542 "GrammarParser.cpp"
    break;

  case 93: // BlockRule: "par" Rules "endpar"
#line 1005 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3550 "GrammarParser.cpp"
    break;

  case 94: // BlockRule: "{" error "}"
#line 1009 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3559 "GrammarParser.cpp"
    break;

  case 95: // BlockRule: "par" error "endpar"
#line 1014 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3568 "GrammarParser.cpp"
    break;

  case 96: // SequenceRule: "{|" Rules "|}"
#line 1023 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3576 "GrammarParser.cpp"
    break;

  case 97: // SequenceRule: "seq" Rules "endseq"
#line 1027 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3584 "GrammarParser.cpp"
    break;

  case 98: // SequenceRule: "{|" error "|}"
#line 1031 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3593 "GrammarParser.cpp"
    break;

  case 99: // SequenceRule: "seq" error "endseq"
#line 1036 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3602 "GrammarParser.cpp"
    break;

  case 100: // UpdateRule: DirectCallExpression ":=" Term
#line 1045 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3610 "GrammarParser.cpp"
    break;

  case 101: // CallRule: CallExpression
#line 1053 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 3618 "GrammarParser.cpp"
    break;

  case 102: // WhileRule: "while" Term "do" Rule
#line 1061 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3626 "GrammarParser.cpp"
    break;

  case 103: // Terms: Terms "," Term
#line 1073 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3637 "GrammarParser.cpp"
    break;

  case 104: // Terms: Term
#line 1080 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3647 "GrammarParser.cpp"
    break;

  case 105: // Term: SimpleOrClaspedTerm
#line 1090 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3655 "GrammarParser.cpp"
    break;

  case 106: // Term: TypeCastingExpression
#line 1094 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 3663 "GrammarParser.cpp"
    break;

  case 107: // Term: OperatorExpression
#line 1098 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3671 "GrammarParser.cpp"
    break;

  case 108: // Term: LetExpression
#line 1102 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 3679 "GrammarParser.cpp"
    break;

  case 109: // Term: ConditionalExpression
#line 1106 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 3687 "GrammarParser.cpp"
    break;

  case 110: // Term: ChooseExpression
#line 1110 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 3695 "GrammarParser.cpp"
    break;

  case 111: // Term: UniversalQuantifierExpression
#line 1114 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 3703 "GrammarParser.cpp"
    break;

  case 112: // Term: ExistentialQuantifierExpression
#line 1118 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 3711 "GrammarParser.cpp"
    break;

  case 113: // Term: CardinalityExpression
#line 1122 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 3719 "GrammarParser.cpp"
    break;

  case 114: // SimpleOrClaspedTerm: "(" Term ")"
#line 1130 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< Ast::EmbracedExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3727 "GrammarParser.cpp"
    break;

  case 115: // SimpleOrClaspedTerm: "(" error ")"
#line 1134 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 3735 "GrammarParser.cpp"
    break;

  case 116: // SimpleOrClaspedTerm: CallExpression
#line 1138 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 3743 "GrammarParser.cpp"
    break;

  case 117: // SimpleOrClaspedTerm: LiteralCallExpression
#line 1142 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 3751 "GrammarParser.cpp"
    break;

  case 118: // SimpleOrClaspedTerm: Literal
#line 1146 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 3759 "GrammarParser.cpp"
    break;

  case 119: // SimpleOrClaspedTerm: "+" SimpleOrClaspedTerm
#line 1150 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3767 "GrammarParser.cpp"
    break;

  case 120: // SimpleOrClaspedTerm: "-" SimpleOrClaspedTerm
#line 1154 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 3775 "GrammarParser.cpp"
    break;

  case 121: // OperatorExpression: Term "+" Term
#line 1166 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3783 "GrammarParser.cpp"
    break;

  case 122: // OperatorExpression: Term "-" Term
#line 1170 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 3791 "GrammarParser.cpp"
    break;

  case 123: // OperatorExpression: Term "*" Term
#line 1174 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 3799 "GrammarParser.cpp"
    break;

  case 124: // OperatorExpression: Term "/" Term
#line 1178 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 3807 "GrammarParser.cpp"
    break;

  case 125: // OperatorExpression: Term "%" Term
#line 1182 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 3815 "GrammarParser.cpp"
    break;

  case 126: // OperatorExpression: Term "^" Term
#line 1186 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 3823 "GrammarParser.cpp"
    break;

  case 127: // OperatorExpression: Term "!=" Term
#line 1190 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 3831 "GrammarParser.cpp"
    break;

  case 128: // OperatorExpression: Term "=" Term
#line 1194 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 3839 "GrammarParser.cpp"
    break;

  case 129: // OperatorExpression: Term "<" Term
#line 1198 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 3847 "GrammarParser.cpp"
    break;

  case 130: // OperatorExpression: Term ">" Term
#line 1202 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 3855 "GrammarParser.cpp"
    break;

  case 131: // OperatorExpression: Term "<=" Term
#line 1206 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 3863 "GrammarParser.cpp"
    break;

  case 132: // OperatorExpression: Term ">=" Term
#line 1210 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 3871 "GrammarParser.cpp"
    break;

  case 133: // OperatorExpression: Term "or" Term
#line 1214 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 3879 "GrammarParser.cpp"
    break;

  case 134: // OperatorExpression: Term "xor" Term
#line 1218 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 3887 "GrammarParser.cpp"
    break;

  case 135: // OperatorExpression: Term "and" Term
#line 1222 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 3895 "GrammarParser.cpp"
    break;

  case 136: // OperatorExpression: Term "=>" Term
#line 1226 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3903 "GrammarParser.cpp"
    break;

  case 137: // OperatorExpression: Term "implies" Term
#line 1230 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3911 "GrammarParser.cpp"
    break;

  case 138: // OperatorExpression: "not" Term
#line 1234 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 3919 "GrammarParser.cpp"
    break;

  case 139: // CallExpression: DirectCallExpression
#line 1242 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 3927 "GrammarParser.cpp"
    break;

  case 140: // CallExpression: MethodCallExpression
#line 1246 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 3935 "GrammarParser.cpp"
    break;

  case 141: // CallExpression: IndirectCallExpression
#line 1250 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 3943 "GrammarParser.cpp"
    break;

  case 142: // DirectCallExpression: IdentifierPath
#line 1258 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > (), arguments );
  }
#line 3952 "GrammarParser.cpp"
    break;

  case 143: // DirectCallExpression: IdentifierPath "(" ")"
#line 1263 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), arguments );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3963 "GrammarParser.cpp"
    break;

  case 144: // DirectCallExpression: IdentifierPath "(" Terms ")"
#line 1270 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3973 "GrammarParser.cpp"
    break;

  case 145: // DirectCallExpression: IdentifierPath "(" error ")"
#line 1276 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 3981 "GrammarParser.cpp"
    break;

  case 146: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier
#line 1284 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 3990 "GrammarParser.cpp"
    break;

  case 147: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" ")"
#line 1289 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4001 "GrammarParser.cpp"
    break;

  case 148: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" Terms ")"
#line 1296 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4011 "GrammarParser.cpp"
    break;

  case 149: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" error ")"
#line 1302 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 4019 "GrammarParser.cpp"
    break;

  case 150: // LiteralCallExpression: SimpleOrClaspedTerm "." IntegerLiteral
#line 1310 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 4027 "GrammarParser.cpp"
    break;

  case 151: // IndirectCallExpression: CallExpression "(" ")"
#line 1318 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4038 "GrammarParser.cpp"
    break;

  case 152: // IndirectCallExpression: CallExpression "(" Terms ")"
#line 1325 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4048 "GrammarParser.cpp"
    break;

  case 153: // IndirectCallExpression: CallExpression "(" error ")"
#line 1331 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 4056 "GrammarParser.cpp"
    break;

  case 154: // TypeCastingExpression: SimpleOrClaspedTerm "as" Type
#line 1339 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 4064 "GrammarParser.cpp"
    break;

  case 155: // LetExpression: "let" VariableBindings "in" Term
#line 1347 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4072 "GrammarParser.cpp"
    break;

  case 156: // ConditionalExpression: "if" Term "then" Term "else" Term
#line 1355 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4080 "GrammarParser.cpp"
    break;

  case 157: // ChooseExpression: "choose" AttributedVariables "in" Term "do" Term
#line 1363 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4088 "GrammarParser.cpp"
    break;

  case 158: // UniversalQuantifierExpression: "forall" AttributedVariables "in" Term "holds" Term
#line 1371 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4096 "GrammarParser.cpp"
    break;

  case 159: // ExistentialQuantifierExpression: "exists" AttributedVariables "in" Term "with" Term
#line 1379 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4104 "GrammarParser.cpp"
    break;

  case 160: // CardinalityExpression: "|" SimpleOrClaspedTerm "|"
#line 1387 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4112 "GrammarParser.cpp"
    break;

  case 161: // Literal: UndefinedLiteral
#line 1400 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 4120 "GrammarParser.cpp"
    break;

  case 162: // Literal: BooleanLiteral
#line 1404 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4128 "GrammarParser.cpp"
    break;

  case 163: // Literal: IntegerLiteral
#line 1408 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4136 "GrammarParser.cpp"
    break;

  case 164: // Literal: RationalLiteral
#line 1412 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4144 "GrammarParser.cpp"
    break;

  case 165: // Literal: DecimalLiteral
#line 1416 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4152 "GrammarParser.cpp"
    break;

  case 166: // Literal: BinaryLiteral
#line 1420 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4160 "GrammarParser.cpp"
    break;

  case 167: // Literal: StringLiteral
#line 1424 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4168 "GrammarParser.cpp"
    break;

  case 168: // Literal: ReferenceLiteral
#line 1428 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 4176 "GrammarParser.cpp"
    break;

  case 169: // Literal: ListLiteral
#line 1432 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 4184 "GrammarParser.cpp"
    break;

  case 170: // Literal: RangeLiteral
#line 1436 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 4192 "GrammarParser.cpp"
    break;

  case 171: // Literal: TupleLiteral
#line 1440 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 4200 "GrammarParser.cpp"
    break;

  case 172: // Literal: RecordLiteral
#line 1444 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 4208 "GrammarParser.cpp"
    break;

  case 173: // UndefinedLiteral: "undef"
#line 1452 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4217 "GrammarParser.cpp"
    break;

  case 174: // BooleanLiteral: "true"
#line 1461 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4227 "GrammarParser.cpp"
    break;

  case 175: // BooleanLiteral: "false"
#line 1467 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4237 "GrammarParser.cpp"
    break;

  case 176: // IntegerLiteral: "integer"
#line 1477 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4245 "GrammarParser.cpp"
    break;

  case 177: // RationalLiteral: "rational"
#line 1485 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4253 "GrammarParser.cpp"
    break;

  case 178: // DecimalLiteral: "decimal"
#line 1493 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4261 "GrammarParser.cpp"
    break;

  case 179: // BinaryLiteral: "binary"
#line 1501 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4269 "GrammarParser.cpp"
    break;

  case 180: // BinaryLiteral: "hexadecimal"
#line 1505 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4277 "GrammarParser.cpp"
    break;

  case 181: // StringLiteral: "string"
#line 1513 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4285 "GrammarParser.cpp"
    break;

  case 182: // ReferenceLiteral: "@" IdentifierPath
#line 1521 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4293 "GrammarParser.cpp"
    break;

  case 183: // ListLiteral: "[" "]"
#line 1529 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4304 "GrammarParser.cpp"
    break;

  case 184: // ListLiteral: "[" Terms "]"
#line 1536 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4314 "GrammarParser.cpp"
    break;

  case 185: // ListLiteral: "[" error "]"
#line 1542 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4322 "GrammarParser.cpp"
    break;

  case 186: // RangeLiteral: "[" Term ".." Term "]"
#line 1550 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4332 "GrammarParser.cpp"
    break;

  case 187: // TupleLiteral: "(" Terms "," Term ")"
#line 1559 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4345 "GrammarParser.cpp"
    break;

  case 188: // RecordLiteral: "(" Assignments ")"
#line 1570 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4355 "GrammarParser.cpp"
    break;

  case 189: // Assignments: Assignments "," Assignment
#line 1579 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4366 "GrammarParser.cpp"
    break;

  case 190: // Assignments: Assignment
#line 1586 "../../obj/src/GrammarParser.y"
  {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4376 "GrammarParser.cpp"
    break;

  case 191: // Assignment: Identifier ":" Term
#line 1595 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4384 "GrammarParser.cpp"
    break;

  case 192: // Types: Types "," Type
#line 1607 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4395 "GrammarParser.cpp"
    break;

  case 193: // Types: Type
#line 1614 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4405 "GrammarParser.cpp"
    break;

  case 194: // Type: BasicType
#line 1623 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4413 "GrammarParser.cpp"
    break;

  case 195: // Type: TupleType
#line 1627 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4421 "GrammarParser.cpp"
    break;

  case 196: // Type: RecordType
#line 1631 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4429 "GrammarParser.cpp"
    break;

  case 197: // Type: TemplateType
#line 1635 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4437 "GrammarParser.cpp"
    break;

  case 198: // Type: RelationType
#line 1639 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4445 "GrammarParser.cpp"
    break;

  case 199: // Type: FixedSizedType
#line 1643 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4453 "GrammarParser.cpp"
    break;

  case 200: // BasicType: IdentifierPath
#line 1651 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4461 "GrammarParser.cpp"
    break;

  case 201: // TupleType: "(" Types "," Type ")"
#line 1659 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = Ast::make< TupleType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), subTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4472 "GrammarParser.cpp"
    break;

  case 202: // RecordType: "(" TypedVariables "," TypedVariable ")"
#line 1670 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = Ast::make< RecordType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4483 "GrammarParser.cpp"
    break;

  case 203: // TemplateType: IdentifierPath "<" Types ">"
#line 1681 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4491 "GrammarParser.cpp"
    break;

  case 204: // RelationType: IdentifierPath "<" MaybeFunctionParameters "->" Type ">"
#line 1689 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4499 "GrammarParser.cpp"
    break;

  case 205: // FixedSizedType: IdentifierPath "'" Term
#line 1697 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4507 "GrammarParser.cpp"
    break;

  case 206: // FunctionParameters: FunctionParameters "*" Type
#line 1709 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4518 "GrammarParser.cpp"
    break;

  case 207: // FunctionParameters: Type
#line 1716 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4528 "GrammarParser.cpp"
    break;

  case 208: // MaybeFunctionParameters: FunctionParameters
#line 1726 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 4536 "GrammarParser.cpp"
    break;

  case 209: // MaybeFunctionParameters: %empty
#line 1730 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 4544 "GrammarParser.cpp"
    break;

  case 210: // Parameters: Parameters "," TypedAttributedVariable
#line 1738 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4555 "GrammarParser.cpp"
    break;

  case 211: // Parameters: TypedAttributedVariable
#line 1745 "../../obj/src/GrammarParser.y"
  {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4565 "GrammarParser.cpp"
    break;

  case 212: // MaybeDefined: "defined" "{" Term "}"
#line 1759 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4573 "GrammarParser.cpp"
    break;

  case 213: // MaybeDefined: %empty
#line 1763 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 4581 "GrammarParser.cpp"
    break;

  case 214: // MaybeInitially: "=" "{" Initializers "}"
#line 1771 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4589 "GrammarParser.cpp"
    break;

  case 215: // MaybeInitially: %empty
#line 1775 "../../obj/src/GrammarParser.y"
  {
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 4598 "GrammarParser.cpp"
    break;

  case 216: // Initializers: Initializers "," Initializer
#line 1784 "../../obj/src/GrammarParser.y"
  {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4609 "GrammarParser.cpp"
    break;

  case 217: // Initializers: Initializer
#line 1791 "../../obj/src/GrammarParser.y"
  {
      auto initializers = Ast::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4619 "GrammarParser.cpp"
    break;

  case 218: // Initializer: Term
#line 1801 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4628 "GrammarParser.cpp"
    break;

  case 219: // Initializer: "(" Term ")" "->" Term
#line 1806 "../../obj/src/GrammarParser.y"
  {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), arguments, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4638 "GrammarParser.cpp"
    break;

  case 220: // Initializer: TupleLiteral "->" Term
#line 1812 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4649 "GrammarParser.cpp"
    break;

  case 221: // Identifier: "identifier"
#line 1827 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 4657 "GrammarParser.cpp"
    break;

  case 222: // Identifier: "in"
#line 1831 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 4666 "GrammarParser.cpp"
    break;

  case 223: // IdentifierPath: IdentifierPath "::" Identifier
#line 1840 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 4677 "GrammarParser.cpp"
    break;

  case 224: // IdentifierPath: Identifier
#line 1847 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4685 "GrammarParser.cpp"
    break;

  case 225: // Variable: TypedVariable
#line 1859 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4693 "GrammarParser.cpp"
    break;

  case 226: // Variable: Identifier
#line 1863 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 4702 "GrammarParser.cpp"
    break;

  case 227: // AttributedVariables: AttributedVariables "," AttributedVariable
#line 1872 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 4713 "GrammarParser.cpp"
    break;

  case 228: // AttributedVariables: AttributedVariable
#line 1879 "../../obj/src/GrammarParser.y"
  {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 4723 "GrammarParser.cpp"
    break;

  case 229: // TypedVariables: TypedVariables "," TypedVariable
#line 1889 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4734 "GrammarParser.cpp"
    break;

  case 230: // TypedVariables: TypedVariable
#line 1896 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4744 "GrammarParser.cpp"
    break;

  case 231: // TypedVariable: Identifier ":" Type
#line 1906 "../../obj/src/GrammarParser.y"
  {
      auto variable = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4753 "GrammarParser.cpp"
    break;

  case 232: // AttributedVariable: Attributes Variable
#line 1915 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4763 "GrammarParser.cpp"
    break;

  case 233: // AttributedVariable: Variable
#line 1921 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4771 "GrammarParser.cpp"
    break;

  case 234: // TypedAttributedVariable: Attributes TypedVariable
#line 1929 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4781 "GrammarParser.cpp"
    break;

  case 235: // TypedAttributedVariable: TypedVariable
#line 1935 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4789 "GrammarParser.cpp"
    break;

  case 236: // VariableBindings: VariableBindings "," VariableBinding
#line 1947 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4800 "GrammarParser.cpp"
    break;

  case 237: // VariableBindings: VariableBinding
#line 1954 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4810 "GrammarParser.cpp"
    break;

  case 238: // VariableBinding: AttributedVariable "=" Term
#line 1963 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4818 "GrammarParser.cpp"
    break;

  case 239: // LocalFunctionDefinitions: LocalFunctionDefinitions "," AttributedLocalFunctionDefinition
#line 1975 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 4829 "GrammarParser.cpp"
    break;

  case 240: // LocalFunctionDefinitions: AttributedLocalFunctionDefinition
#line 1982 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 4839 "GrammarParser.cpp"
    break;

  case 241: // AttributedLocalFunctionDefinition: Attributes LocalFunctionDefinition
#line 1991 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 4849 "GrammarParser.cpp"
    break;

  case 242: // AttributedLocalFunctionDefinition: LocalFunctionDefinition
#line 1997 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 4857 "GrammarParser.cpp"
    break;

  case 243: // AttributedLocalFunctionDefinition: error
#line 2001 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 4865 "GrammarParser.cpp"
    break;

  case 244: // LocalFunctionDefinition: Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 2008 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, Token::unresolved(), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > ()->setClassification( FunctionDefinition::Classification::LOCAL );

      // apply the name of the function declaration to the initializer functions
      const auto initially = yylhs.value.as < FunctionDefinition::Ptr > ()->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->setFunction( yylhs.value.as < FunctionDefinition::Ptr > () );
      }
  }
#line 4881 "GrammarParser.cpp"
    break;

  case 245: // Attributes: Attributes Attribute
#line 2028 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4891 "GrammarParser.cpp"
    break;

  case 246: // Attributes: Attribute
#line 2034 "../../obj/src/GrammarParser.y"
  {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4901 "GrammarParser.cpp"
    break;

  case 247: // Attribute: "[" BasicAttribute "]"
#line 2043 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4912 "GrammarParser.cpp"
    break;

  case 248: // Attribute: "[" ExpressionAttribute "]"
#line 2050 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4923 "GrammarParser.cpp"
    break;

  case 249: // Attribute: "[" error "]"
#line 2057 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 4931 "GrammarParser.cpp"
    break;

  case 250: // BasicAttribute: Identifier
#line 2064 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4939 "GrammarParser.cpp"
    break;

  case 251: // ExpressionAttribute: Identifier Term
#line 2071 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4947 "GrammarParser.cpp"
    break;


#line 4951 "GrammarParser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
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
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

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
        std::string yyr;
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
              else
                goto append;

            append:
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

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
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
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short Parser::yypact_ninf_ = -377;

  const short Parser::yytable_ninf_ = -208;

  const short
  Parser::yypact_[] =
  {
      32,  -377,    26,    57,   539,    33,  -377,   -17,  -377,  -377,
    1954,    18,    42,  -377,  -377,     5,     9,     9,     9,     9,
       9,     9,     9,     9,    -6,     9,   130,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,   563,  -377,  -377,  -377,    -5,    -5,    -5,  1954,    -5,
    -377,  -377,  -377,  1954,   239,   239,  1474,  1214,   239,     9,
    -377,  -377,  -377,  -377,  -377,  -377,  2711,    61,  -377,    58,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,    16,  -377,  -377,  2019,    86,
      -7,   119,   120,   135,   156,   138,    46,   143,   172,    -6,
     187,  -377,  -377,  -377,  -377,  -377,  -377,     0,   177,  -377,
    -377,   190,  -377,  -377,   200,    38,  -377,    -5,    53,  -377,
      59,  2248,    64,  -377,  -377,  -377,   199,   202,  2466,   -22,
    -377,   211,   215,  -377,    94,  2501,    19,    86,  1954,  1954,
    1954,  1954,  1954,  1954,  1954,  1954,  1954,  1954,  1954,  1954,
    1954,  1954,  1954,  1954,  1954,    -6,    28,  1279,  1344,     9,
    1474,  2711,   201,   134,  -377,    15,    -6,   230,  1824,    17,
      -6,    -6,    -4,  1954,     9,   231,   243,   237,  -377,   190,
      92,   240,  -377,   246,    -6,    -6,  1954,    -6,    -6,  1954,
    1954,    -5,  -377,  1954,    -5,  1954,  1954,  1954,  -377,  1954,
    -377,  -377,     9,  1954,  -377,  -377,  1954,  1954,  -377,   353,
     707,  2776,  2746,   228,   228,   448,   176,   176,   236,   236,
     236,  -377,  2746,   448,   176,   176,  -377,  -377,   254,   256,
    -377,   101,  2711,   257,  -377,   168,  -377,  2536,  1954,  -377,
    2019,   258,   169,   190,  -377,  -377,    -5,   261,    22,   857,
     944,  -377,    -5,    25,    -5,    -5,  1824,  1954,  1954,  1954,
    1014,  1084,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,   235,   115,   252,   262,
     171,   263,  -377,  -377,  2711,  -377,   312,   116,    -6,     9,
     255,   278,   227,   195,   264,   259,  -377,  -377,   265,  -377,
    2711,  2711,  -377,  2396,  -377,  2086,  2325,  2431,  2571,  -377,
     211,  2711,  2711,  2606,  1409,  -377,  -377,  -377,  -377,   266,
    2711,  -377,   267,   268,    -5,  -377,  1954,  -377,  -377,   221,
    -377,    -5,   315,  1544,  -377,   314,  1614,    65,  -377,   284,
      89,  -377,  -377,    -5,    95,   100,  -377,  2287,  2361,  2127,
     279,  1684,   269,  1754,  1954,   -19,     4,  1824,   287,     9,
       9,  -377,  -377,  -377,    51,  -377,   292,   293,  -377,  -377,
    -377,    60,   294,    -6,  -377,    -6,    -6,    -6,  1954,  1954,
    1954,  1954,  -377,  -377,   295,  -377,   184,  1954,    -6,    -6,
    -377,  2711,  -377,    22,  -377,  -377,  -377,  -377,  -377,  -377,
    1824,    -6,  1824,    25,  -377,  1954,  1954,  1824,   296,  1824,
    -377,  -377,  -377,  -377,  2711,  1824,    -6,  1824,    -6,  -377,
    -377,    74,   117,  -377,  -377,  -377,  -377,  -377,  -377,   255,
    -377,  -377,   286,   336,  2711,  2711,  2711,  2711,  -377,  -377,
    2711,   303,   305,  -377,  -377,   285,  -377,  -377,  2045,  2168,
     325,  1149,  -377,  -377,   308,  -377,   309,    -6,    -6,    67,
    -377,   307,   310,  1954,  1954,    -6,  1824,  1954,  1824,  1824,
     316,   311,   317,  1889,  -377,  2641,  1824,  1824,   306,   318,
    -377,  1954,   320,  -377,  2711,  2711,   336,  -377,  2209,  -377,
    -377,  -377,  1824,  1824,  -377,  -377,  1824,  -377,  -377,    -6,
      -6,  2676,  2019,   310,  1824,  -377,  -377,  -377,  -377,  -377,
    -377,   222,  -377,  -377,  -377
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   246,     0,   222,   221,
     250,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     8,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,     3,   245,   249,     0,     0,     0,     0,     0,
     173,   175,   174,     0,     0,     0,     0,     0,     0,     0,
     179,   180,   176,   177,   178,   181,   251,   105,   107,   116,
     139,   140,   117,   141,   106,   108,   109,   110,   111,   112,
     113,   118,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   224,   142,   247,   248,     0,    22,
       0,     0,     0,   224,    41,     0,    44,     0,     0,     0,
       0,   194,   195,   196,   197,   198,   199,   200,     0,     5,
       7,   226,   233,   225,     0,     0,   237,     0,     0,   228,
       0,     0,     0,   138,   119,   120,     0,     0,   104,     0,
     190,   224,     0,   183,     0,   104,     0,   182,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   218,   171,     0,   217,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   193,   224,
     200,     0,   230,     0,     0,   209,     0,   209,     0,     0,
       0,     0,   232,     0,     0,     0,     0,     0,   115,     0,
     114,   188,     0,     0,   185,   184,     0,     0,   160,   135,
     133,   134,   137,   121,   122,   128,   129,   130,   123,   124,
     125,   126,   136,   127,   131,   132,   154,   150,   146,     0,
     151,     0,   104,     0,   143,     0,   223,   104,     0,    23,
       0,     0,     0,     0,   235,   211,     0,     0,     0,     0,
       0,    76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,     0,   101,   139,     0,
       0,     0,    40,    42,    43,    45,     0,     0,     0,     0,
       0,     0,     0,   193,   208,     0,   205,   207,     0,   231,
     238,   155,   236,     0,   227,     0,     0,     0,   103,   189,
       0,   191,   103,     0,     0,   153,   152,   145,   144,   114,
     220,   216,     0,     0,     0,   234,     0,    37,    39,     0,
      35,     0,     0,     0,    62,     0,     0,     0,   243,     0,
       0,   240,   242,     0,     0,     0,    91,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,    50,    52,     0,    48,   192,   229,    55,    56,
      58,     0,     0,     0,   203,     0,     0,     0,     0,     0,
       0,     0,   187,   186,     0,   147,     0,     0,     0,     0,
     210,    25,    24,     0,    36,    99,    97,    61,    95,    93,
       0,   209,     0,     0,   241,     0,     0,     0,     0,     0,
      94,    92,    98,    96,   100,     0,     0,     0,     0,    29,
      46,     0,     0,    47,    51,   201,   202,    54,    57,     0,
     192,   206,     0,   213,   158,   157,   156,   159,   149,   148,
     219,     0,     0,    38,    86,     0,    87,   239,     0,     0,
      77,     0,   102,    32,     0,    30,     0,   209,   209,     0,
     204,     0,   215,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,     0,     0,     0,     0,
      53,     0,     0,    34,    27,    26,   213,    88,     0,    90,
      78,    80,     0,     0,    79,    81,     0,    33,    31,     0,
       0,     0,     0,   215,     0,    83,    84,    85,    59,    60,
     212,     0,   244,    89,   214
  };

  const short
  Parser::yypgoto_[] =
  {
    -377,  -377,  -377,  -377,   341,   347,  -377,  -377,     7,    11,
      96,   -13,  -377,  -377,  -377,  -377,  -377,  -377,  -377,    20,
    -377,  -377,  -376,   -46,  -377,   -75,   445,  -377,  -377,  -377,
    -377,   -84,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,   -49,    50,   -30,  -377,   220,   342,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,   234,  -377,  -377,  -377,  -377,  -377,  -377,  -377,   -97,
    -377,  -377,   189,   213,   -21,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -195,   233,   -90,  -104,  -102,   173,   483,   -15,
     297,   -37,  -377,   -80,   -23,    91,   165,   232,  -377,    21,
      75,    13,     2,  -377,  -377
  };

  const short
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    26,    27,    28,    29,    30,   378,   379,
      33,   338,   339,    34,    35,    36,    37,    38,    39,   373,
     374,    40,   380,   381,   375,   343,   344,   273,   274,   275,
     483,   484,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   137,   171,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,   139,   140,   187,   307,   111,   112,   113,   114,   115,
     116,   304,   305,   252,   472,   493,   173,   174,    94,    95,
     122,   128,   191,   123,   129,   255,   125,   126,   350,   351,
     352,   127,     6,    11,    12
  };

  const short
  Parser::yytable_[] =
  {
      99,   172,   308,   110,   104,   438,   106,    43,   144,   117,
     130,    31,   132,     5,   194,    32,   251,    41,   289,     8,
       8,     8,   124,   337,   134,   135,   348,     7,   146,   192,
       8,   211,   425,    31,     8,     1,    42,    32,    44,    41,
       8,   212,     8,    43,   147,   175,   109,     8,    31,     2,
       8,     8,    32,     8,   426,   427,   369,    13,   370,   169,
      66,    98,   293,   200,   195,    16,   176,    18,   168,     2,
     196,     2,    16,    96,    18,   169,     2,   428,   203,     2,
     218,     9,     9,     9,   205,   184,     2,     2,   188,   207,
     410,   166,     9,   438,   190,   254,     9,    97,   131,   254,
     165,   201,     9,   133,     9,   169,   138,   145,   433,     9,
     167,    62,     9,     9,   412,     9,   204,   437,   241,   245,
     415,   369,   204,   370,   490,   416,   175,   204,   201,    43,
      -2,    14,   467,   166,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,   236,   169,    25,   176,   286,   215,
     190,   169,   413,   172,   326,   257,   195,   216,   204,   291,
     292,   190,   196,   204,   216,   190,   190,   167,   178,   179,
     177,   178,   179,   301,   303,   468,   335,   309,   124,   190,
     190,   314,   190,   190,     2,   346,   181,  -116,   256,   183,
     180,   249,   256,   180,   185,   361,   363,   250,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   182,   455,   242,   242,   377,
     247,   328,   333,   186,   366,   152,   153,   354,   355,   286,
     286,   216,   334,   294,   334,   197,   286,   449,   193,   124,
     286,   286,   157,   158,   159,   160,   306,   216,   198,   310,
     311,   199,   208,   313,   254,   315,   316,   317,    43,   318,
      16,  -207,    18,   321,     8,   209,   322,   323,  -207,   213,
     214,   341,   488,   489,   248,   396,   353,   376,   402,   524,
      50,    51,    52,   190,   403,   250,   258,   296,    54,    55,
     383,    56,   384,    57,   157,   158,   159,   160,   330,   297,
     298,    59,   300,   299,   371,   160,   324,   166,   372,   325,
     327,   332,   336,   286,   367,   365,   286,   357,   358,   359,
      60,    61,    62,    63,    64,    65,     9,   364,    25,   382,
     385,   286,   386,   286,   405,   408,   420,   286,   387,   397,
     398,   399,   411,    43,   430,   435,   436,   256,   448,   422,
     439,   470,   461,   471,   473,    43,   474,   479,   475,   486,
     487,   492,   440,   491,   441,   442,   443,   119,   190,   502,
     190,   190,   190,   501,   242,   503,   512,   451,   452,   509,
     286,   371,   286,   190,   190,   372,   401,   286,   120,   286,
     453,   510,   368,   469,   434,   286,   190,   286,   287,   505,
     237,   319,   152,   153,   154,   464,   513,   466,   302,   522,
     521,   190,   290,   190,   424,   172,   341,   155,   156,   157,
     158,   159,   160,   331,   202,   400,   353,   347,   414,   162,
     163,   164,     0,   312,   457,     0,     0,     0,   444,   445,
     446,   447,     0,     0,     0,     0,   286,   450,   286,   286,
       0,     0,   190,   190,   496,     0,   286,   286,     0,     0,
     190,     0,     0,     0,     0,   458,   459,     0,     0,     0,
       0,     0,   286,   286,     0,     0,   286,     0,     0,   287,
     287,     0,     0,     0,   286,    10,   287,     0,   518,   519,
     287,   287,     0,     0,   190,   190,     0,   152,   153,   100,
     101,   102,   103,   105,     0,   107,   108,     0,   118,     0,
       0,   485,   155,   156,   157,   158,   159,   160,     0,     0,
     288,     0,     0,   494,   495,   163,   164,   498,   121,   121,
     121,     0,   121,   485,     0,     0,     0,     0,     0,   141,
      14,   511,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,     0,    25,     0,     0,     0,     0,
       0,     0,     0,   287,     0,     0,   287,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,     0,    25,
       0,   287,     0,   287,     0,     0,     0,   287,     0,     0,
       0,     0,   189,     2,     0,     0,     0,     0,     0,     0,
       0,   288,   288,     0,     0,     0,     0,     0,   288,     0,
     121,     0,   288,   288,     0,     0,     0,     2,     0,     0,
       0,     0,     0,   272,     0,     0,     0,     0,     0,     0,
     287,     0,   287,     0,     0,     0,     0,   287,     0,   287,
       0,     0,     0,     0,     0,   287,     0,   287,     0,   238,
       0,     0,   246,   141,     0,     0,     0,     0,   253,     0,
       0,     0,   253,     0,     0,   246,     0,   295,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,   288,     0,   121,   288,     0,
       0,     0,     0,     0,     0,   320,   287,     0,   287,   287,
       0,     0,     0,   288,     0,   288,   287,   287,     0,   288,
       0,   356,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   287,   287,     0,     0,   287,     0,     0,     0,
       0,     0,     0,     0,   287,     0,     0,     0,     0,   253,
       0,   340,     0,     0,     0,   121,   349,   121,   121,     0,
       0,   148,   288,   150,   288,     0,   152,   153,   154,   288,
       0,   288,     0,     0,     0,     0,     0,   288,     0,   288,
       0,   155,   156,   157,   158,   159,   160,     0,     0,     0,
       0,     0,   253,   162,   163,   164,     0,     0,   407,     0,
       0,   407,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   407,     0,   407,     0,
       0,     0,   429,     0,     0,     0,     0,   253,   288,     0,
     288,   288,     0,     0,   404,     0,     0,     0,   288,   288,
       0,     0,     0,     0,     0,     0,   349,     0,     0,     0,
       0,     0,     0,     0,   288,   288,     0,     0,   288,     0,
       0,     0,   431,   432,     0,   454,   288,   456,   342,     0,
       0,     0,   460,     0,   462,     0,     0,     0,     0,     0,
     463,     0,   465,     0,     0,   259,     0,   260,     0,   261,
     262,   263,     8,   264,   265,   266,   340,   267,     0,     0,
     268,     0,     0,     0,     0,     0,   349,   269,    50,    51,
      52,     0,     0,     0,     0,     0,    54,    55,     0,    56,
       0,    57,     0,   270,     0,     0,     0,     0,     0,    59,
       0,   497,     0,   499,   500,     0,     0,     0,     0,     0,
       0,   507,   508,     0,     0,     0,   271,     0,    60,    61,
      62,    63,    64,    65,     9,   345,     0,   515,   516,     0,
       0,   517,     0,     0,     0,     0,     0,     0,     0,   523,
       0,     0,   259,     0,   260,     0,   261,   262,   263,     8,
     264,   265,   266,     0,   267,     0,     0,   268,     0,     0,
       0,     0,     0,     0,   269,    50,    51,    52,     0,     0,
       0,     0,     0,    54,    55,     0,    56,     0,    57,     0,
     270,     0,     0,     0,     0,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,   360,     0,     0,     0,     0,
       0,     0,     0,   271,     0,    60,    61,    62,    63,    64,
      65,     9,   259,     0,   260,     0,   261,   262,   263,     8,
     264,   265,   266,     0,   267,     0,     0,   268,     0,     0,
       0,     0,     0,     0,   269,    50,    51,    52,     0,     0,
       0,     0,     0,    54,    55,     0,    56,     0,    57,     0,
     270,     0,     0,     0,     0,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,   362,     0,     0,     0,     0,
       0,     0,     0,   271,     0,    60,    61,    62,    63,    64,
      65,     9,   259,     0,   260,     0,   261,   262,   263,     8,
     264,   265,   266,     0,   267,     0,     0,   268,     0,     0,
       0,     0,     0,     0,   269,    50,    51,    52,     0,     0,
       0,     0,     0,    54,    55,     0,    56,     0,    57,     0,
     270,     0,     0,     0,     0,     0,    59,     0,     0,     0,
     480,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   271,     0,    60,    61,    62,    63,    64,
      65,     9,    45,     0,     8,    46,    47,     0,     0,    48,
       0,     0,     0,     0,   481,     0,    49,     0,     0,     0,
      50,    51,    52,     0,     0,     0,     0,    53,    54,    55,
       0,    56,     0,    57,     0,     0,     0,     0,     0,   482,
      58,    59,     0,     0,     0,   142,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    61,    62,    63,    64,    65,     9,    45,     0,     8,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,    49,     0,     0,     0,    50,    51,    52,     0,     0,
       0,     0,    53,    54,    55,     0,    56,     0,    57,   143,
       0,     0,     0,     0,     0,    58,    59,     0,     0,     0,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    61,    62,    63,    64,
      65,     9,    45,     0,     8,    46,    47,     0,     0,    48,
       0,     0,     0,     0,     0,     0,    49,     0,     0,     0,
      50,    51,    52,     0,     0,     0,     0,    53,    54,    55,
       0,    56,   240,    57,     0,     0,     0,     0,     0,     0,
      58,    59,     0,     0,     0,   243,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    61,    62,    63,    64,    65,     9,    45,     0,     8,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,    49,     0,     0,     0,    50,    51,    52,     0,     0,
       0,     0,    53,    54,    55,     0,    56,   244,    57,     0,
       0,     0,     0,     0,     0,    58,    59,     0,     0,     0,
     394,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    61,    62,    63,    64,
      65,     9,    45,     0,     8,    46,    47,     0,     0,    48,
       0,     0,     0,     0,     0,     0,    49,     0,     0,     0,
      50,    51,    52,     0,     0,     0,     0,    53,    54,    55,
       0,    56,   395,    57,     0,     0,     0,     0,     0,     0,
      58,    59,     0,     0,     0,   136,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    61,    62,    63,    64,    65,     9,    45,     0,     8,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,    49,     0,     0,     0,    50,    51,    52,     0,     0,
       0,     0,    53,    54,    55,     0,    56,     0,    57,     0,
       0,     0,     0,     0,     0,    58,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    61,    62,    63,    64,
      65,     9,   259,   406,   260,     0,   261,   262,   263,     8,
     264,   265,   266,     0,   267,     0,     0,   268,     0,     0,
       0,     0,     0,     0,   269,    50,    51,    52,     0,     0,
       0,     0,     0,    54,    55,     0,    56,     0,    57,     0,
     270,     0,     0,     0,     0,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   271,     0,    60,    61,    62,    63,    64,
      65,     9,   259,     0,   260,   409,   261,   262,   263,     8,
     264,   265,   266,     0,   267,     0,     0,   268,     0,     0,
       0,     0,     0,     0,   269,    50,    51,    52,     0,     0,
       0,     0,     0,    54,    55,     0,    56,     0,    57,     0,
     270,     0,     0,     0,     0,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   271,     0,    60,    61,    62,    63,    64,
      65,     9,   259,     0,   260,     0,   261,   262,   263,     8,
     264,   265,   266,     0,   267,     0,     0,   268,     0,     0,
       0,     0,     0,     0,   269,    50,    51,    52,     0,     0,
       0,     0,     0,    54,    55,     0,    56,     0,    57,     0,
     270,   421,     0,     0,     0,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   271,     0,    60,    61,    62,    63,    64,
      65,     9,   259,     0,   260,     0,   261,   262,   263,     8,
     264,   265,   266,     0,   267,     0,     0,   268,     0,     0,
       0,     0,     0,     0,   269,    50,    51,    52,     0,     0,
       0,     0,     0,    54,    55,     0,    56,     0,    57,     0,
     270,     0,     0,     0,     0,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   271,   423,    60,    61,    62,    63,    64,
      65,     9,   259,     0,   260,     0,   261,   262,   263,     8,
     264,   265,   266,     0,   267,     0,     0,   268,     0,     0,
       0,     0,     0,     0,   269,    50,    51,    52,     0,     0,
       0,     0,     0,    54,    55,     0,    56,     0,    57,     0,
     270,     0,     0,     0,     0,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   271,     0,    60,    61,    62,    63,    64,
      65,     9,    45,     0,     8,    46,    47,     0,     0,    48,
       0,     0,     0,     0,   481,     0,    49,     0,     0,     0,
      50,    51,    52,     0,     0,     0,     0,    53,    54,    55,
       0,    56,     0,    57,     0,     0,   504,     0,     0,   482,
      58,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    61,    62,    63,    64,    65,     9,    45,     0,     8,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,    49,     0,     0,     0,    50,    51,    52,     0,     0,
       0,     0,    53,    54,    55,     0,    56,     0,    57,     0,
       0,     0,     0,     0,     0,    58,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    61,    62,    63,    64,
      65,     9,    45,     0,     8,    46,    47,     0,     0,    48,
       0,     0,     0,     0,     0,     0,    49,     0,     0,     0,
      50,    51,    52,     0,     0,     0,     0,    53,    54,    55,
       0,   170,     0,    57,   476,     0,     0,     0,     0,     0,
      58,    59,     0,   477,     0,     0,     0,     0,     0,   148,
     149,   150,   151,     0,   152,   153,   154,     0,     0,     0,
      60,    61,    62,    63,    64,    65,     9,     0,     0,   155,
     156,   157,   158,   159,   160,   389,     0,     0,     0,   161,
       0,   162,   163,   164,     0,     0,     0,     0,     0,     0,
     148,   149,   150,   151,     0,   152,   153,   154,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,   419,     0,     0,     0,
     161,     0,   162,   163,   164,     0,     0,     0,     0,     0,
       0,   148,   149,   150,   151,     0,   152,   153,   154,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   155,   156,   157,   158,   159,   160,   478,     0,     0,
       0,   161,     0,   162,   163,   164,     0,     0,     0,     0,
       0,     0,   148,   149,   150,   151,     0,   152,   153,   154,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   155,   156,   157,   158,   159,   160,   514,     0,
       0,     0,   161,     0,   162,   163,   164,     0,     0,     0,
       0,     0,     0,   148,   149,   150,   151,     0,   152,   153,
     154,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   156,   157,   158,   159,   160,   206,
       0,     0,     0,   161,     0,   162,   163,   164,     0,     0,
       0,     0,   148,   149,   150,   151,     0,   152,   153,   154,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   155,   156,   157,   158,   159,   160,   417,     0,
       0,     0,   161,     0,   162,   163,   164,     0,     0,     0,
       0,   148,   149,   150,   151,     0,   152,   153,   154,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   155,   156,   157,   158,   159,   160,   390,     0,     0,
       0,   161,     0,   162,   163,   164,     0,     0,     0,   148,
     149,   150,   151,     0,   152,   153,   154,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   155,
     156,   157,   158,   159,   160,   418,     0,     0,     0,   161,
       0,   162,   163,   164,     0,   148,   149,   150,   151,     0,
     152,   153,   154,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   155,   156,   157,   158,   159,
     160,     0,   388,     0,     0,   161,     0,   162,   163,   164,
     148,   149,   150,   151,     0,   152,   153,   154,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,     0,     0,     0,   391,
     161,     0,   162,   163,   164,   148,   149,   150,   151,     0,
     152,   153,   154,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   155,   156,   157,   158,   159,
     160,     0,     0,     0,     0,   161,     0,   162,   163,   164,
     148,   149,   150,   151,     0,   152,   153,   154,     0,   210,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,     0,     0,     0,     0,
     161,     0,   162,   163,   164,   148,   149,   150,   151,     0,
     152,   153,   154,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   155,   156,   157,   158,   159,
     160,     0,   217,     0,     0,   161,     0,   162,   163,   164,
     148,   149,   150,   151,     0,   152,   153,   154,     0,   329,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,     0,     0,     0,     0,
     161,     0,   162,   163,   164,   148,   149,   150,   151,     0,
     152,   153,   154,     0,   392,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   155,   156,   157,   158,   159,
     160,     0,     0,     0,     0,   161,     0,   162,   163,   164,
     148,   149,   150,   151,     0,   152,   153,   154,     0,     0,
       0,   393,     0,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,     0,     0,     0,     0,
     161,     0,   162,   163,   164,   148,   149,   150,   151,     0,
     152,   153,   154,     0,     0,     0,     0,     0,     0,   506,
       0,     0,     0,     0,     0,   155,   156,   157,   158,   159,
     160,     0,     0,     0,     0,   161,     0,   162,   163,   164,
     148,   149,   150,   151,     0,   152,   153,   154,     0,     0,
       0,     0,     0,   520,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,     0,     0,     0,     0,
     161,     0,   162,   163,   164,   148,   149,   150,   151,     0,
     152,   153,   154,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   155,   156,   157,   158,   159,
     160,     0,     0,     0,     0,   161,     0,   162,   163,   164,
     148,   149,   150,     0,     0,   152,   153,   154,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,     0,     0,     0,     0,
     148,     0,   162,   163,   164,   152,   153,   154,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,     0,     0,     0,     0,
       0,     0,   162,   163,   164
  };

  const short
  Parser::yycheck_[] =
  {
      15,    98,   197,    24,    19,   381,    21,     5,    57,    24,
      47,     4,    49,     0,    14,     4,     1,     4,     1,    25,
      25,    25,    45,     1,    54,    55,     1,     1,    58,   109,
      25,    53,    51,    26,    25,     3,     3,    26,    55,    26,
      25,    63,    25,    41,    59,    52,    52,    25,    41,    54,
      25,    25,    41,    25,    73,    51,     5,     0,     7,    59,
      10,    56,    66,    25,    64,     5,    73,     7,    52,    54,
      70,    54,     5,    55,     7,    59,    54,    73,    25,    54,
      61,    87,    87,    87,    25,    39,    54,    54,   109,    25,
      25,    72,    87,   469,   109,   175,    87,    55,    48,   179,
      39,    63,    87,    53,    87,    59,    56,    57,    57,    87,
      52,    83,    87,    87,    25,    87,    63,    57,   167,   168,
      25,     5,    63,     7,    57,    25,    52,    63,    63,   127,
       0,     1,    58,    72,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   165,    59,    16,    73,   178,    55,
     165,    59,    63,   250,    53,   176,    64,    63,    63,   180,
     181,   176,    70,    63,    63,   180,   181,    52,    51,    52,
      51,    51,    52,   194,   195,    58,   256,   198,   201,   194,
     195,   204,   197,   198,    54,   260,    51,    72,   175,    51,
      73,    57,   179,    73,    51,   270,   271,    63,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,    59,   411,   167,   168,   299,
     170,    53,    53,    51,    53,    49,    50,   264,   265,   259,
     260,    63,    63,   183,    63,    58,   266,    53,    51,   262,
     270,   271,    66,    67,    68,    69,   196,    63,    58,   199,
     200,    51,    53,   203,   334,   205,   206,   207,   256,   209,
       5,    66,     7,   213,    25,    63,   216,   217,    73,    58,
      55,   258,   467,   468,    73,   324,   263,   298,    57,    57,
      41,    42,    43,   298,    63,    63,    56,    56,    49,    50,
      63,    52,    65,    54,    66,    67,    68,    69,   248,    56,
      63,    62,    56,    63,   297,    69,    52,    72,   297,    53,
      53,    53,    51,   343,    51,    53,   346,   267,   268,   269,
      81,    82,    83,    84,    85,    86,    87,    75,    16,    51,
      66,   361,    73,   363,    19,    21,    57,   367,    73,    73,
      73,    73,    58,   341,    57,    53,    53,   334,    53,    80,
      56,    65,    56,    17,    51,   353,    51,    32,    73,    51,
      51,    51,   383,    56,   385,   386,   387,    26,   383,    58,
     385,   386,   387,    57,   324,    58,    56,   398,   399,    73,
     410,   374,   412,   398,   399,   374,   336,   417,    41,   419,
     403,    73,   296,   439,   374,   425,   411,   427,   178,   483,
     166,   212,    49,    50,    51,   426,   496,   428,   195,   513,
     512,   426,   179,   428,   364,   512,   403,    64,    65,    66,
      67,    68,    69,   250,   127,   334,   413,   262,   353,    76,
      77,    78,    -1,   201,   413,    -1,    -1,    -1,   388,   389,
     390,   391,    -1,    -1,    -1,    -1,   476,   397,   478,   479,
      -1,    -1,   467,   468,   475,    -1,   486,   487,    -1,    -1,
     475,    -1,    -1,    -1,    -1,   415,   416,    -1,    -1,    -1,
      -1,    -1,   502,   503,    -1,    -1,   506,    -1,    -1,   259,
     260,    -1,    -1,    -1,   514,     2,   266,    -1,   509,   510,
     270,   271,    -1,    -1,   509,   510,    -1,    49,    50,    16,
      17,    18,    19,    20,    -1,    22,    23,    -1,    25,    -1,
      -1,   461,    64,    65,    66,    67,    68,    69,    -1,    -1,
     178,    -1,    -1,   473,   474,    77,    78,   477,    45,    46,
      47,    -1,    49,   483,    -1,    -1,    -1,    -1,    -1,    56,
       1,   491,    -1,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   343,    -1,    -1,   346,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    16,
      -1,   361,    -1,   363,    -1,    -1,    -1,   367,    -1,    -1,
      -1,    -1,   109,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   259,   260,    -1,    -1,    -1,    -1,    -1,   266,    -1,
     127,    -1,   270,   271,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,   178,    -1,    -1,    -1,    -1,    -1,    -1,
     410,    -1,   412,    -1,    -1,    -1,    -1,   417,    -1,   419,
      -1,    -1,    -1,    -1,    -1,   425,    -1,   427,    -1,   166,
      -1,    -1,   169,   170,    -1,    -1,    -1,    -1,   175,    -1,
      -1,    -1,   179,    -1,    -1,   182,    -1,   184,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   201,   343,    -1,   204,   346,    -1,
      -1,    -1,    -1,    -1,    -1,   212,   476,    -1,   478,   479,
      -1,    -1,    -1,   361,    -1,   363,   486,   487,    -1,   367,
      -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   502,   503,    -1,    -1,   506,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   514,    -1,    -1,    -1,    -1,   256,
      -1,   258,    -1,    -1,    -1,   262,   263,   264,   265,    -1,
      -1,    44,   410,    46,   412,    -1,    49,    50,    51,   417,
      -1,   419,    -1,    -1,    -1,    -1,    -1,   425,    -1,   427,
      -1,    64,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,   299,    76,    77,    78,    -1,    -1,   343,    -1,
      -1,   346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   361,    -1,   363,    -1,
      -1,    -1,   367,    -1,    -1,    -1,    -1,   334,   476,    -1,
     478,   479,    -1,    -1,   341,    -1,    -1,    -1,   486,   487,
      -1,    -1,    -1,    -1,    -1,    -1,   353,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   502,   503,    -1,    -1,   506,    -1,
      -1,    -1,   369,   370,    -1,   410,   514,   412,     1,    -1,
      -1,    -1,   417,    -1,   419,    -1,    -1,    -1,    -1,    -1,
     425,    -1,   427,    -1,    -1,    18,    -1,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,   403,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,   413,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    50,    -1,    52,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,
      -1,   476,    -1,   478,   479,    -1,    -1,    -1,    -1,    -1,
      -1,   486,   487,    -1,    -1,    -1,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,     1,    -1,   502,   503,    -1,
      -1,   506,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   514,
      -1,    -1,    18,    -1,    20,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    52,    -1,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    18,    -1,    20,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    52,    -1,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    18,    -1,    20,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    52,    -1,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    23,    -1,    25,    26,    27,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    35,    -1,    37,    -1,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    23,    -1,    25,
      26,    27,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    -1,    54,    55,
      -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    23,    -1,    25,    26,    27,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    23,    -1,    25,
      26,    27,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    23,    -1,    25,    26,    27,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    23,    -1,    25,
      26,    27,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    18,    19,    20,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    52,    -1,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    18,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    52,    -1,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    18,    -1,    20,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    52,    -1,    54,    -1,
      56,    57,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    18,    -1,    20,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    52,    -1,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    18,    -1,    20,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    52,    -1,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    23,    -1,    25,    26,    27,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    35,    -1,    37,    -1,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    52,    -1,    54,    -1,    -1,    57,    -1,    -1,    60,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    23,    -1,    25,
      26,    27,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    23,    -1,    25,    26,    27,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    52,    -1,    54,    29,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    38,    -1,    -1,    -1,    -1,    -1,    44,
      45,    46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    -1,    -1,    64,
      65,    66,    67,    68,    69,    29,    -1,    -1,    -1,    74,
      -1,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    29,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    -1,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    69,    29,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    -1,    49,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    69,    29,    -1,
      -1,    -1,    74,    -1,    76,    77,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    46,    47,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    31,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    -1,    49,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    69,    31,    -1,
      -1,    -1,    74,    -1,    76,    77,    78,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    -1,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    69,    32,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    -1,    -1,    -1,    44,
      45,    46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    69,    34,    -1,    -1,    -1,    74,
      -1,    76,    77,    78,    -1,    44,    45,    46,    47,    -1,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      69,    -1,    36,    -1,    -1,    74,    -1,    76,    77,    78,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    38,
      74,    -1,    76,    77,    78,    44,    45,    46,    47,    -1,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    74,    -1,    76,    77,    78,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    44,    45,    46,    47,    -1,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      69,    -1,    71,    -1,    -1,    74,    -1,    76,    77,    78,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    44,    45,    46,    47,    -1,
      49,    50,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    74,    -1,    76,    77,    78,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    44,    45,    46,    47,    -1,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    74,    -1,    76,    77,    78,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    44,    45,    46,    47,    -1,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    74,    -1,    76,    77,    78,
      44,    45,    46,    -1,    -1,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      44,    -1,    76,    77,    78,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    54,    94,    95,   194,   195,     1,    25,    87,
     181,   196,   197,     0,     1,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    16,    96,    97,    98,    99,
     100,   101,   102,   103,   106,   107,   108,   109,   110,   111,
     114,   194,     3,   195,    55,    23,    26,    27,    30,    37,
      41,    42,    43,    48,    49,    50,    52,    54,    61,    62,
      81,    82,    83,    84,    85,    86,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   181,   182,    55,    55,    56,   182,
     181,   181,   181,   181,   182,   181,   182,   181,   181,    52,
     167,   168,   169,   170,   171,   172,   173,   182,   181,    97,
      98,   181,   183,   186,   187,   189,   190,   194,   184,   187,
     184,   136,   184,   136,   137,   137,     1,   135,   136,   164,
     165,   181,     1,    55,   135,   136,   137,   182,    44,    45,
      46,    47,    49,    50,    51,    64,    65,    66,    67,    68,
      69,    74,    76,    77,    78,    39,    72,    52,    52,    59,
      52,   136,   162,   179,   180,    52,    73,    51,    51,    52,
      73,    51,    59,    51,    39,    51,    51,   166,   167,   181,
     182,   185,   186,    51,    14,    64,    70,    58,    58,    51,
      25,    63,   183,    25,    63,    25,    31,    25,    53,    63,
      53,    53,    63,    58,    55,    55,    63,    71,    61,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   167,   154,   181,     1,
      53,   135,   136,     1,    53,   135,   181,   136,    73,    57,
      63,     1,   176,   181,   186,   188,   194,   167,    56,    18,
      20,    22,    23,    24,    26,    27,    28,    30,    33,    40,
      56,    79,   119,   120,   121,   122,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   137,   139,   140,     1,
     176,   167,   167,    66,   136,   181,    56,    56,    63,    63,
      56,   167,   166,   167,   174,   175,   136,   167,   175,   167,
     136,   136,   190,   136,   187,   136,   136,   136,   136,   165,
     181,   136,   136,   136,    52,    53,    53,    53,    53,    53,
     136,   180,    53,    53,    63,   186,    51,     1,   104,   105,
     181,   194,     1,   118,   119,     1,   118,   189,     1,   181,
     191,   192,   193,   194,   184,   184,   119,   136,   136,   136,
       1,   118,     1,   118,    75,    53,    53,    51,   103,     5,
       7,   101,   102,   112,   113,   117,   167,   186,   101,   102,
     115,   116,    51,    63,    65,    66,    73,    73,    36,    29,
      32,    38,    53,    55,     1,    53,   135,    73,    73,    73,
     188,   136,    57,    63,   181,    19,    19,   119,    21,    21,
      25,    58,    25,    63,   193,    25,    25,    31,    34,    29,
      57,    57,    80,    80,   136,    51,    73,    51,    73,   119,
      57,   181,   181,    57,   112,    53,    53,    57,   115,    56,
     167,   167,   167,   167,   136,   136,   136,   136,    53,    53,
     136,   167,   167,   104,   119,   175,   119,   192,   136,   136,
     119,    56,   119,   119,   167,   119,   167,    58,    58,   116,
      65,    17,   177,    51,    51,    73,    29,    38,    29,    32,
       1,    35,    60,   123,   124,   136,    51,    51,   175,   175,
      57,    56,    51,   178,   136,   136,   167,   119,   136,   119,
     119,    57,    58,    58,    57,   124,    58,   119,   119,    73,
      73,   136,    56,   177,    29,   119,   119,   119,   167,   167,
      57,   179,   178,   119,    57
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    93,    94,    95,    95,    96,    96,    97,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    99,    99,   100,   101,   101,   101,   102,   102,
     102,   102,   102,   102,   103,   104,   104,   104,   105,   105,
     106,   107,   107,   108,   109,   109,   110,   111,   112,   112,
     112,   113,   113,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   120,   121,   121,   122,
     122,   123,   123,   124,   124,   124,   125,   126,   127,   127,
     128,   129,   130,   130,   130,   130,   131,   131,   131,   131,
     132,   133,   134,   135,   135,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   139,
     139,   139,   140,   140,   140,   140,   141,   141,   141,   141,
     142,   143,   143,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   152,   153,   153,   154,   155,   156,   157,
     157,   158,   159,   160,   160,   160,   161,   162,   163,   164,
     164,   165,   166,   166,   167,   167,   167,   167,   167,   167,
     168,   169,   170,   171,   172,   173,   174,   174,   175,   175,
     176,   176,   177,   177,   178,   178,   179,   179,   180,   180,
     180,   181,   181,   182,   182,   183,   183,   184,   184,   185,
     185,   186,   187,   187,   188,   188,   189,   189,   190,   191,
     191,   192,   192,   192,   193,   194,   194,   195,   195,   195,
     196,   197
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     4,     6,     6,     9,     9,     4,     6,
       7,     9,     7,     9,     8,     1,     2,     1,     3,     1,
       4,     2,     4,     4,     2,     4,     6,     6,     1,     1,
       1,     2,     1,     8,     6,     1,     1,     2,     1,     6,
       6,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     6,     6,
       6,     2,     1,     3,     3,     3,     4,     4,     6,     8,
       6,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     1,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     1,     3,     4,     4,     3,     5,     6,     6,
       3,     3,     4,     4,     3,     4,     6,     6,     6,     6,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     3,     5,     5,     3,     3,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     4,     6,     3,     3,     1,     1,     0,
       3,     1,     4,     0,     4,     0,     3,     1,     1,     5,
       3,     1,     1,     3,     1,     1,     1,     3,     1,     3,
       1,     3,     2,     1,     2,     1,     3,     1,     3,     3,
       1,     2,     1,     1,     7,     2,     1,     3,     3,     3,
       1,     2
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"using\"",
  "\"invariant\"", "\"import\"", "\"structure\"", "\"feature\"",
  "\"implements\"", "\"for\"", "\"this\"", "\"function\"", "\"defined\"",
  "\"seq\"", "\"endseq\"", "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"",
  "\"local\"", "\"in\"", "\"forall\"", "\"choose\"", "\"iterate\"",
  "\"do\"", "\"if\"", "\"then\"", "\"else\"", "\"case\"", "\"of\"",
  "\"default\"", "\"holds\"", "\"exists\"", "\"with\"", "\"as\"",
  "\"while\"", "\"undef\"", "\"false\"", "\"true\"", "\"and\"", "\"or\"",
  "\"xor\"", "\"implies\"", "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"",
  "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\":\"", "\"::\"", "\"_\"",
  "\"|\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"",
  "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"", "\"=>\"", "\":=\"",
  "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"decimal\"",
  "\"string\"", "\"identifier\"", "BASIC_TYPE", "CALL", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header", "Definitions",
  "AttributedDefinition", "Definition", "InitDefinition",
  "EnumerationDefinition", "DerivedDefinition", "RuleDefinition",
  "FunctionDefinition", "EnumeratorDefinition", "Enumerators",
  "UsingDefinition", "UsingPathDefinition", "InvariantDefinition",
  "ImportDefinition", "StructureDefinition", "FeatureDefinition",
  "FeatureDeclarationOrDefinition", "FeatureDeclarationsAndDefinitions",
  "ImplementationDefinition", "ImplementationDefinitionDefinition",
  "ImplementationDefinitionDefinitions", "DeclarationDefinition", "Rules",
  "Rule", "SkipRule", "ConditionalRule", "CaseRule", "CaseLabels",
  "CaseLabel", "LetRule", "LocalRule", "ForallRule", "ChooseRule",
  "IterateRule", "BlockRule", "SequenceRule", "UpdateRule", "CallRule",
  "WhileRule", "Terms", "Term", "SimpleOrClaspedTerm",
  "OperatorExpression", "CallExpression", "DirectCallExpression",
  "MethodCallExpression", "LiteralCallExpression",
  "IndirectCallExpression", "TypeCastingExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "CardinalityExpression", "Literal", "UndefinedLiteral", "BooleanLiteral",
  "IntegerLiteral", "RationalLiteral", "DecimalLiteral", "BinaryLiteral",
  "StringLiteral", "ReferenceLiteral", "ListLiteral", "RangeLiteral",
  "TupleLiteral", "RecordLiteral", "Assignments", "Assignment", "Types",
  "Type", "BasicType", "TupleType", "RecordType", "TemplateType",
  "RelationType", "FixedSizedType", "FunctionParameters",
  "MaybeFunctionParameters", "Parameters", "MaybeDefined",
  "MaybeInitially", "Initializers", "Initializer", "Identifier",
  "IdentifierPath", "Variable", "AttributedVariables", "TypedVariables",
  "TypedVariable", "AttributedVariable", "TypedAttributedVariable",
  "VariableBindings", "VariableBinding", "LocalFunctionDefinitions",
  "AttributedLocalFunctionDefinition", "LocalFunctionDefinition",
  "Attributes", "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   431,   431,   441,   447,   455,   461,   471,   477,   481,
     489,   493,   497,   501,   505,   509,   513,   517,   521,   525,
     529,   533,   541,   545,   553,   561,   566,   572,   580,   586,
     591,   598,   604,   608,   616,   631,   635,   641,   649,   656,
     666,   674,   678,   686,   694,   698,   706,   715,   724,   728,
     732,   740,   746,   756,   760,   770,   774,   782,   788,   798,
     805,   820,   826,   836,   840,   844,   848,   852,   856,   860,
     864,   868,   872,   876,   880,   884,   892,   900,   904,   912,
     916,   924,   930,   940,   944,   948,   956,   964,   972,   976,
     984,   992,  1000,  1004,  1008,  1013,  1022,  1026,  1030,  1035,
    1044,  1052,  1060,  1072,  1079,  1089,  1093,  1097,  1101,  1105,
    1109,  1113,  1117,  1121,  1129,  1133,  1137,  1141,  1145,  1149,
    1153,  1165,  1169,  1173,  1177,  1181,  1185,  1189,  1193,  1197,
    1201,  1205,  1209,  1213,  1217,  1221,  1225,  1229,  1233,  1241,
    1245,  1249,  1257,  1262,  1269,  1275,  1283,  1288,  1295,  1301,
    1309,  1317,  1324,  1330,  1338,  1346,  1354,  1362,  1370,  1378,
    1386,  1399,  1403,  1407,  1411,  1415,  1419,  1423,  1427,  1431,
    1435,  1439,  1443,  1451,  1460,  1466,  1476,  1484,  1492,  1500,
    1504,  1512,  1520,  1528,  1535,  1541,  1549,  1558,  1569,  1578,
    1585,  1594,  1606,  1613,  1622,  1626,  1630,  1634,  1638,  1642,
    1650,  1658,  1669,  1680,  1688,  1696,  1708,  1715,  1725,  1729,
    1737,  1744,  1758,  1762,  1770,  1774,  1783,  1790,  1800,  1805,
    1811,  1826,  1830,  1839,  1846,  1858,  1862,  1871,  1878,  1888,
    1895,  1905,  1914,  1920,  1928,  1934,  1946,  1953,  1962,  1974,
    1981,  1990,  1996,  2000,  2007,  2027,  2033,  2042,  2049,  2056,
    2063,  2070
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 51 "../../obj/src/GrammarParser.y"
} // libcasm_fe
#line 6274 "GrammarParser.cpp"

#line 2076 "../../obj/src/GrammarParser.y"


void Parser::error( const libstdhl::SourceLocation& location, const std::string& message )
{
    m_log.error( {location}, message, Code::SyntaxError );
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
