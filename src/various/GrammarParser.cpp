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
        const auto name = Ast::make< Identifier >( sourceLocation, TypeInfo::TYPE_NAME_VOID );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        return node;
    }

#line 63 "GrammarParser.cpp"


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
#line 156 "GrammarParser.cpp"

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
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAIN: // "domain"
      case symbol_kind::S_BUILTIN: // "builtin"
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

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.YY_MOVE_OR_COPY< BuiltinDefinition::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_Declaration: // Declaration
        value.YY_MOVE_OR_COPY< Declaration::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.YY_MOVE_OR_COPY< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDefinitionElement: // FeatureDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
        value.YY_MOVE_OR_COPY< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
      case symbol_kind::S_ImplementDefinitionList: // ImplementDefinitionList
        value.YY_MOVE_OR_COPY< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.YY_MOVE_OR_COPY< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.YY_MOVE_OR_COPY< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DomainDefinition: // DomainDefinition
        value.YY_MOVE_OR_COPY< DomainDefinition::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_StructureDefinitionElement: // StructureDefinitionElement
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.YY_MOVE_OR_COPY< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_StructureDefinitionList: // StructureDefinitionList
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

      case symbol_kind::S_ImplementDefinition: // ImplementDefinition
        value.YY_MOVE_OR_COPY< ImplementDefinition::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_TemplateVariable: // TemplateVariable
        value.YY_MOVE_OR_COPY< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TemplateSymbols: // TemplateSymbols
      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
      case symbol_kind::S_TemplateVariables: // TemplateVariables
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
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAIN: // "domain"
      case symbol_kind::S_BUILTIN: // "builtin"
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

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.move< BuiltinDefinition::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_Declaration: // Declaration
        value.move< Declaration::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.move< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDefinitionElement: // FeatureDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
        value.move< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
      case symbol_kind::S_ImplementDefinitionList: // ImplementDefinitionList
        value.move< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DomainDefinition: // DomainDefinition
        value.move< DomainDefinition::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_StructureDefinitionElement: // StructureDefinitionElement
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.move< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_StructureDefinitionList: // StructureDefinitionList
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

      case symbol_kind::S_ImplementDefinition: // ImplementDefinition
        value.move< ImplementDefinition::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_TemplateVariable: // TemplateVariable
        value.move< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TemplateSymbols: // TemplateSymbols
      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
      case symbol_kind::S_TemplateVariables: // TemplateVariables
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
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAIN: // "domain"
      case symbol_kind::S_BUILTIN: // "builtin"
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

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.copy< BuiltinDefinition::Ptr > (that.value);
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

      case symbol_kind::S_Declaration: // Declaration
        value.copy< Declaration::Ptr > (that.value);
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.copy< Defined::Ptr > (that.value);
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDefinitionElement: // FeatureDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
        value.copy< Definition::Ptr > (that.value);
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
      case symbol_kind::S_ImplementDefinitionList: // ImplementDefinitionList
        value.copy< Definitions::Ptr > (that.value);
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_DomainDefinition: // DomainDefinition
        value.copy< DomainDefinition::Ptr > (that.value);
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
      case symbol_kind::S_StructureDefinitionElement: // StructureDefinitionElement
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_StructureDefinitionList: // StructureDefinitionList
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

      case symbol_kind::S_ImplementDefinition: // ImplementDefinition
        value.copy< ImplementDefinition::Ptr > (that.value);
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
      case symbol_kind::S_TemplateVariable: // TemplateVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_TemplateSymbols: // TemplateSymbols
      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
      case symbol_kind::S_TemplateVariables: // TemplateVariables
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
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAIN: // "domain"
      case symbol_kind::S_BUILTIN: // "builtin"
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

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.move< BuiltinDefinition::Ptr > (that.value);
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

      case symbol_kind::S_Declaration: // Declaration
        value.move< Declaration::Ptr > (that.value);
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.move< Defined::Ptr > (that.value);
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDefinitionElement: // FeatureDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
        value.move< Definition::Ptr > (that.value);
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
      case symbol_kind::S_ImplementDefinitionList: // ImplementDefinitionList
        value.move< Definitions::Ptr > (that.value);
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_DomainDefinition: // DomainDefinition
        value.move< DomainDefinition::Ptr > (that.value);
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
      case symbol_kind::S_StructureDefinitionElement: // StructureDefinitionElement
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_StructureDefinitionList: // StructureDefinitionList
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

      case symbol_kind::S_ImplementDefinition: // ImplementDefinition
        value.move< ImplementDefinition::Ptr > (that.value);
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
      case symbol_kind::S_TemplateVariable: // TemplateVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_TemplateSymbols: // TemplateSymbols
      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
      case symbol_kind::S_TemplateVariables: // TemplateVariables
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
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAIN: // "domain"
      case symbol_kind::S_BUILTIN: // "builtin"
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

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        yylhs.value.emplace< BuiltinDefinition::Ptr > ();
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

      case symbol_kind::S_Declaration: // Declaration
        yylhs.value.emplace< Declaration::Ptr > ();
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        yylhs.value.emplace< Defined::Ptr > ();
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDefinitionElement: // FeatureDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
        yylhs.value.emplace< Definition::Ptr > ();
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
      case symbol_kind::S_ImplementDefinitionList: // ImplementDefinitionList
        yylhs.value.emplace< Definitions::Ptr > ();
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        yylhs.value.emplace< DerivedDefinition::Ptr > ();
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        yylhs.value.emplace< DirectCallExpression::Ptr > ();
        break;

      case symbol_kind::S_DomainDefinition: // DomainDefinition
        yylhs.value.emplace< DomainDefinition::Ptr > ();
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
      case symbol_kind::S_StructureDefinitionElement: // StructureDefinitionElement
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        yylhs.value.emplace< FunctionDefinition::Ptr > ();
        break;

      case symbol_kind::S_StructureDefinitionList: // StructureDefinitionList
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

      case symbol_kind::S_ImplementDefinition: // ImplementDefinition
        yylhs.value.emplace< ImplementDefinition::Ptr > ();
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
      case symbol_kind::S_TemplateVariable: // TemplateVariable
        yylhs.value.emplace< VariableDefinition::Ptr > ();
        break;

      case symbol_kind::S_TemplateSymbols: // TemplateSymbols
      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
      case symbol_kind::S_TemplateVariables: // TemplateVariables
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
#line 441 "../../obj/src/GrammarParser.y"
  {
      m_specification.setHeader( yystack_[1].value.as < HeaderDefinition::Ptr > () );
      m_specification.setDefinitions( yystack_[0].value.as < Definitions::Ptr > () );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 2846 "GrammarParser.cpp"
    break;

  case 3: // Header: Attributes "CASM"
#line 451 "../../obj/src/GrammarParser.y"
  {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2856 "GrammarParser.cpp"
    break;

  case 4: // Header: "CASM"
#line 457 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2864 "GrammarParser.cpp"
    break;

  case 5: // Definitions: Definitions AttributedDefinition
#line 465 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2874 "GrammarParser.cpp"
    break;

  case 6: // Definitions: AttributedDefinition
#line 471 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2884 "GrammarParser.cpp"
    break;

  case 7: // AttributedDefinition: Attributes Definition
#line 481 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2894 "GrammarParser.cpp"
    break;

  case 8: // AttributedDefinition: Definition
#line 487 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2902 "GrammarParser.cpp"
    break;

  case 9: // AttributedDefinition: error
#line 491 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2910 "GrammarParser.cpp"
    break;

  case 10: // Definition: InitDefinition
#line 499 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2918 "GrammarParser.cpp"
    break;

  case 11: // Definition: EnumerationDefinition
#line 503 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2926 "GrammarParser.cpp"
    break;

  case 12: // Definition: DerivedDefinition
#line 507 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2934 "GrammarParser.cpp"
    break;

  case 13: // Definition: RuleDefinition
#line 511 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2942 "GrammarParser.cpp"
    break;

  case 14: // Definition: FunctionDefinition
#line 515 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2950 "GrammarParser.cpp"
    break;

  case 15: // Definition: UsingDefinition
#line 519 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2958 "GrammarParser.cpp"
    break;

  case 16: // Definition: UsingPathDefinition
#line 523 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 2966 "GrammarParser.cpp"
    break;

  case 17: // Definition: InvariantDefinition
#line 527 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 2974 "GrammarParser.cpp"
    break;

  case 18: // Definition: ImportDefinition
#line 531 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 2982 "GrammarParser.cpp"
    break;

  case 19: // Definition: StructureDefinition
#line 535 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < StructureDefinition::Ptr > ();
  }
#line 2990 "GrammarParser.cpp"
    break;

  case 20: // Definition: FeatureDefinition
#line 539 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FeatureDefinition::Ptr > ();
  }
#line 2998 "GrammarParser.cpp"
    break;

  case 21: // Definition: ImplementDefinition
#line 543 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImplementDefinition::Ptr > ();
  }
#line 3006 "GrammarParser.cpp"
    break;

  case 22: // Definition: DomainDefinition
#line 547 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DomainDefinition::Ptr > ();
  }
#line 3014 "GrammarParser.cpp"
    break;

  case 23: // Definition: BuiltinDefinition
#line 551 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < BuiltinDefinition::Ptr > ();
  }
#line 3022 "GrammarParser.cpp"
    break;

  case 24: // InitDefinition: "init" IdentifierPath
#line 559 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3030 "GrammarParser.cpp"
    break;

  case 25: // InitDefinition: "init" "{" Initializers "}"
#line 563 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3038 "GrammarParser.cpp"
    break;

  case 26: // EnumerationDefinition: "enumeration" Identifier "=" "{" Enumerators "}"
#line 571 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3046 "GrammarParser.cpp"
    break;

  case 27: // DerivedDefinition: "derived" Identifier "->" Type "=" Term
#line 579 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3055 "GrammarParser.cpp"
    break;

  case 28: // DerivedDefinition: "derived" Identifier "(" Parameters ")" "->" Type "=" Term
#line 584 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 3065 "GrammarParser.cpp"
    break;

  case 29: // DerivedDefinition: "derived" Identifier "(" MethodParameters ")" "->" Type "=" Term
#line 590 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 3075 "GrammarParser.cpp"
    break;

  case 30: // DerivedDefinition: "derived" Identifier "(" error ")" "->" Type "=" Term
#line 596 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 3083 "GrammarParser.cpp"
    break;

  case 31: // RuleDefinition: "rule" Identifier "=" Rule
#line 604 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3093 "GrammarParser.cpp"
    break;

  case 32: // RuleDefinition: "rule" Identifier "->" Type "=" Rule
#line 610 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3102 "GrammarParser.cpp"
    break;

  case 33: // RuleDefinition: "rule" Identifier "(" Parameters ")" "=" Rule
#line 615 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 3113 "GrammarParser.cpp"
    break;

  case 34: // RuleDefinition: "rule" Identifier "(" Parameters ")" "->" Type "=" Rule
#line 622 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 3123 "GrammarParser.cpp"
    break;

  case 35: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "=" Rule
#line 628 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 3134 "GrammarParser.cpp"
    break;

  case 36: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "->" Type "=" Rule
#line 635 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 3144 "GrammarParser.cpp"
    break;

  case 37: // RuleDefinition: "rule" Identifier "(" error ")" "=" Rule
#line 641 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3152 "GrammarParser.cpp"
    break;

  case 38: // RuleDefinition: "rule" Identifier "(" error ")" "->" Type "=" Rule
#line 645 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3160 "GrammarParser.cpp"
    break;

  case 39: // FunctionDefinition: "function" Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 653 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
  }
#line 3168 "GrammarParser.cpp"
    break;

  case 40: // EnumeratorDefinition: Identifier
#line 661 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3176 "GrammarParser.cpp"
    break;

  case 41: // EnumeratorDefinition: Attributes Identifier
#line 665 "../../obj/src/GrammarParser.y"
  {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 3186 "GrammarParser.cpp"
    break;

  case 42: // EnumeratorDefinition: error
#line 671 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 3194 "GrammarParser.cpp"
    break;

  case 43: // Enumerators: Enumerators "," EnumeratorDefinition
#line 679 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3205 "GrammarParser.cpp"
    break;

  case 44: // Enumerators: EnumeratorDefinition
#line 686 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3215 "GrammarParser.cpp"
    break;

  case 45: // UsingDefinition: "using" Identifier "=" Type
#line 696 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3223 "GrammarParser.cpp"
    break;

  case 46: // UsingPathDefinition: "using" IdentifierPath
#line 704 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3231 "GrammarParser.cpp"
    break;

  case 47: // UsingPathDefinition: "using" IdentifierPath "::" "*"
#line 708 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3239 "GrammarParser.cpp"
    break;

  case 48: // InvariantDefinition: "invariant" Identifier "=" Term
#line 716 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3247 "GrammarParser.cpp"
    break;

  case 49: // ImportDefinition: "import" IdentifierPath
#line 728 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3255 "GrammarParser.cpp"
    break;

  case 50: // ImportDefinition: "import" IdentifierPath "as" Identifier
#line 732 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3263 "GrammarParser.cpp"
    break;

  case 51: // StructureDefinition: "structure" Identifier "=" "{" StructureDefinitionList "}"
#line 740 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < StructureDefinition::Ptr > () = Ast::make< StructureDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < FunctionDefinitions::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3271 "GrammarParser.cpp"
    break;

  case 52: // StructureDefinitionList: StructureDefinitionList StructureDefinitionElement
#line 747 "../../obj/src/GrammarParser.y"
  {
      auto functions = yystack_[1].value.as < FunctionDefinitions::Ptr > ();
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3281 "GrammarParser.cpp"
    break;

  case 53: // StructureDefinitionList: StructureDefinitionElement
#line 753 "../../obj/src/GrammarParser.y"
  {
      auto functions = Ast::make< FunctionDefinitions >( yylhs.location );
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3291 "GrammarParser.cpp"
    break;

  case 54: // StructureDefinitionElement: Attributes FunctionDefinition
#line 762 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 3301 "GrammarParser.cpp"
    break;

  case 55: // StructureDefinitionElement: FunctionDefinition
#line 768 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 3309 "GrammarParser.cpp"
    break;

  case 56: // FeatureDefinition: "feature" Identifier "=" "{" FeatureDefinitionList "}"
#line 780 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FeatureDefinition::Ptr > () = Ast::make< FeatureDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3317 "GrammarParser.cpp"
    break;

  case 57: // FeatureDefinitionElement: Attributes Declaration
#line 788 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Declaration::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3327 "GrammarParser.cpp"
    break;

  case 58: // FeatureDefinitionElement: Declaration
#line 794 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Declaration::Ptr > ();
  }
#line 3335 "GrammarParser.cpp"
    break;

  case 59: // FeatureDefinitionElement: Attributes DerivedDefinition
#line 798 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DerivedDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3345 "GrammarParser.cpp"
    break;

  case 60: // FeatureDefinitionElement: DerivedDefinition
#line 804 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3353 "GrammarParser.cpp"
    break;

  case 61: // FeatureDefinitionElement: Attributes RuleDefinition
#line 808 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < RuleDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3363 "GrammarParser.cpp"
    break;

  case 62: // FeatureDefinitionElement: RuleDefinition
#line 814 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3371 "GrammarParser.cpp"
    break;

  case 63: // FeatureDefinitionList: FeatureDefinitionList FeatureDefinitionElement
#line 822 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3381 "GrammarParser.cpp"
    break;

  case 64: // FeatureDefinitionList: FeatureDefinitionElement
#line 828 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3391 "GrammarParser.cpp"
    break;

  case 65: // TemplateSymbols: "<" TemplateVariables ">"
#line 838 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinitions::Ptr > () = yystack_[1].value.as < VariableDefinitions::Ptr > ();
      // TODO: FIXME: @ppaulweber: handle token $1 and $3
  }
#line 3400 "GrammarParser.cpp"
    break;

  case 66: // TemplateSymbols: %empty
#line 843 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinitions::Ptr > () = Ast::make< VariableDefinitions >( yylhs.location );
  }
#line 3408 "GrammarParser.cpp"
    break;

  case 67: // ImplementDefinition: "implement" TemplateSymbols Type "=" "{" ImplementDefinitionList "}"
#line 856 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = Ast::make< ImplementDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[4].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3416 "GrammarParser.cpp"
    break;

  case 68: // ImplementDefinition: "implement" TemplateSymbols IdentifierPath "for" Type "=" "{" ImplementDefinitionList "}"
#line 860 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = Ast::make< ImplementDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < VariableDefinitions::Ptr > (), yystack_[6].value.as < IdentifierPath::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3424 "GrammarParser.cpp"
    break;

  case 69: // ImplementDefinitionElement: Attributes DerivedDefinition
#line 868 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DerivedDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3434 "GrammarParser.cpp"
    break;

  case 70: // ImplementDefinitionElement: DerivedDefinition
#line 874 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3442 "GrammarParser.cpp"
    break;

  case 71: // ImplementDefinitionElement: Attributes RuleDefinition
#line 878 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < RuleDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3452 "GrammarParser.cpp"
    break;

  case 72: // ImplementDefinitionElement: RuleDefinition
#line 884 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3460 "GrammarParser.cpp"
    break;

  case 73: // ImplementDefinitionList: ImplementDefinitionList ImplementDefinitionElement
#line 892 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3470 "GrammarParser.cpp"
    break;

  case 74: // ImplementDefinitionList: ImplementDefinitionElement
#line 898 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3480 "GrammarParser.cpp"
    break;

  case 75: // DomainDefinition: "domain" TemplateSymbols Type
#line 912 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DomainDefinition::Ptr > () = Ast::make< DomainDefinition >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < VariableDefinitions::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3488 "GrammarParser.cpp"
    break;

  case 76: // BuiltinDefinition: "builtin" TemplateSymbols RelationType
#line 924 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BuiltinDefinition::Ptr > () = Ast::make< BuiltinDefinition >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < VariableDefinitions::Ptr > (), yystack_[0].value.as < RelationType::Ptr > () );
  }
#line 3496 "GrammarParser.cpp"
    break;

  case 77: // Declaration: "derived" Identifier ":" MaybeFunctionParameters "->" Type
#line 936 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = Ast::make< Declaration >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3504 "GrammarParser.cpp"
    break;

  case 78: // Declaration: "rule" Identifier ":" MaybeFunctionParameters "->" Type
#line 940 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = Ast::make< Declaration >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3512 "GrammarParser.cpp"
    break;

  case 79: // Rules: Rules Rule
#line 952 "../../obj/src/GrammarParser.y"
  {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3522 "GrammarParser.cpp"
    break;

  case 80: // Rules: Rule
#line 958 "../../obj/src/GrammarParser.y"
  {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3532 "GrammarParser.cpp"
    break;

  case 81: // Rule: SkipRule
#line 968 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 3540 "GrammarParser.cpp"
    break;

  case 82: // Rule: ConditionalRule
#line 972 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 3548 "GrammarParser.cpp"
    break;

  case 83: // Rule: CaseRule
#line 976 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 3556 "GrammarParser.cpp"
    break;

  case 84: // Rule: LetRule
#line 980 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 3564 "GrammarParser.cpp"
    break;

  case 85: // Rule: LocalRule
#line 984 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LocalRule::Ptr > ();
  }
#line 3572 "GrammarParser.cpp"
    break;

  case 86: // Rule: ForallRule
#line 988 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 3580 "GrammarParser.cpp"
    break;

  case 87: // Rule: ChooseRule
#line 992 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 3588 "GrammarParser.cpp"
    break;

  case 88: // Rule: IterateRule
#line 996 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 3596 "GrammarParser.cpp"
    break;

  case 89: // Rule: BlockRule
#line 1000 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 3604 "GrammarParser.cpp"
    break;

  case 90: // Rule: SequenceRule
#line 1004 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 3612 "GrammarParser.cpp"
    break;

  case 91: // Rule: UpdateRule
#line 1008 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 3620 "GrammarParser.cpp"
    break;

  case 92: // Rule: CallRule
#line 1012 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 3628 "GrammarParser.cpp"
    break;

  case 93: // Rule: WhileRule
#line 1016 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 3636 "GrammarParser.cpp"
    break;

  case 94: // SkipRule: "skip"
#line 1024 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3644 "GrammarParser.cpp"
    break;

  case 95: // ConditionalRule: "if" Term "then" Rule
#line 1032 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3652 "GrammarParser.cpp"
    break;

  case 96: // ConditionalRule: "if" Term "then" Rule "else" Rule
#line 1036 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3660 "GrammarParser.cpp"
    break;

  case 97: // CaseRule: "case" Term "of" "{" CaseLabels "}"
#line 1044 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3668 "GrammarParser.cpp"
    break;

  case 98: // CaseRule: "case" Term "of" "{" error "}"
#line 1048 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 3676 "GrammarParser.cpp"
    break;

  case 99: // CaseLabels: CaseLabels CaseLabel
#line 1056 "../../obj/src/GrammarParser.y"
  {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3686 "GrammarParser.cpp"
    break;

  case 100: // CaseLabels: CaseLabel
#line 1062 "../../obj/src/GrammarParser.y"
  {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3696 "GrammarParser.cpp"
    break;

  case 101: // CaseLabel: "default" ":" Rule
#line 1072 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3704 "GrammarParser.cpp"
    break;

  case 102: // CaseLabel: "_" ":" Rule
#line 1076 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3712 "GrammarParser.cpp"
    break;

  case 103: // CaseLabel: Term ":" Rule
#line 1080 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3720 "GrammarParser.cpp"
    break;

  case 104: // LetRule: "let" VariableBindings "in" Rule
#line 1088 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3728 "GrammarParser.cpp"
    break;

  case 105: // LocalRule: "local" LocalFunctionDefinitions "in" Rule
#line 1096 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LocalRule::Ptr > () = Ast::make< LocalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < FunctionDefinitions::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3736 "GrammarParser.cpp"
    break;

  case 106: // ForallRule: "forall" AttributedVariables "in" Term "do" Rule
#line 1104 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3744 "GrammarParser.cpp"
    break;

  case 107: // ForallRule: "forall" AttributedVariables "in" Term "with" Term "do" Rule
#line 1108 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3752 "GrammarParser.cpp"
    break;

  case 108: // ChooseRule: "choose" AttributedVariables "in" Term "do" Rule
#line 1116 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3760 "GrammarParser.cpp"
    break;

  case 109: // IterateRule: "iterate" Rule
#line 1124 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3768 "GrammarParser.cpp"
    break;

  case 110: // BlockRule: "{" Rules "}"
#line 1132 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3776 "GrammarParser.cpp"
    break;

  case 111: // BlockRule: "par" Rules "endpar"
#line 1136 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3784 "GrammarParser.cpp"
    break;

  case 112: // BlockRule: "{" error "}"
#line 1140 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3793 "GrammarParser.cpp"
    break;

  case 113: // BlockRule: "par" error "endpar"
#line 1145 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3802 "GrammarParser.cpp"
    break;

  case 114: // SequenceRule: "{|" Rules "|}"
#line 1154 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3810 "GrammarParser.cpp"
    break;

  case 115: // SequenceRule: "seq" Rules "endseq"
#line 1158 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3818 "GrammarParser.cpp"
    break;

  case 116: // SequenceRule: "{|" error "|}"
#line 1162 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3827 "GrammarParser.cpp"
    break;

  case 117: // SequenceRule: "seq" error "endseq"
#line 1167 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3836 "GrammarParser.cpp"
    break;

  case 118: // UpdateRule: DirectCallExpression ":=" Term
#line 1176 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3844 "GrammarParser.cpp"
    break;

  case 119: // UpdateRule: MethodCallExpression ":=" Term
#line 1180 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < MethodCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3852 "GrammarParser.cpp"
    break;

  case 120: // CallRule: CallExpression
#line 1188 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 3860 "GrammarParser.cpp"
    break;

  case 121: // WhileRule: "while" Term "do" Rule
#line 1196 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3868 "GrammarParser.cpp"
    break;

  case 122: // Terms: Terms "," Term
#line 1208 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3879 "GrammarParser.cpp"
    break;

  case 123: // Terms: Term
#line 1215 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3889 "GrammarParser.cpp"
    break;

  case 124: // Term: SimpleOrClaspedTerm
#line 1225 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3897 "GrammarParser.cpp"
    break;

  case 125: // Term: TypeCastingExpression
#line 1229 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 3905 "GrammarParser.cpp"
    break;

  case 126: // Term: OperatorExpression
#line 1233 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3913 "GrammarParser.cpp"
    break;

  case 127: // Term: LetExpression
#line 1237 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 3921 "GrammarParser.cpp"
    break;

  case 128: // Term: ConditionalExpression
#line 1241 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 3929 "GrammarParser.cpp"
    break;

  case 129: // Term: ChooseExpression
#line 1245 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 3937 "GrammarParser.cpp"
    break;

  case 130: // Term: UniversalQuantifierExpression
#line 1249 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 3945 "GrammarParser.cpp"
    break;

  case 131: // Term: ExistentialQuantifierExpression
#line 1253 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 3953 "GrammarParser.cpp"
    break;

  case 132: // Term: CardinalityExpression
#line 1257 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 3961 "GrammarParser.cpp"
    break;

  case 133: // SimpleOrClaspedTerm: "(" Term ")"
#line 1265 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< Ast::EmbracedExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3969 "GrammarParser.cpp"
    break;

  case 134: // SimpleOrClaspedTerm: "(" error ")"
#line 1269 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 3977 "GrammarParser.cpp"
    break;

  case 135: // SimpleOrClaspedTerm: CallExpression
#line 1273 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 3985 "GrammarParser.cpp"
    break;

  case 136: // SimpleOrClaspedTerm: LiteralCallExpression
#line 1277 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 3993 "GrammarParser.cpp"
    break;

  case 137: // SimpleOrClaspedTerm: Literal
#line 1281 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 4001 "GrammarParser.cpp"
    break;

  case 138: // SimpleOrClaspedTerm: "+" SimpleOrClaspedTerm
#line 1285 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4009 "GrammarParser.cpp"
    break;

  case 139: // SimpleOrClaspedTerm: "-" SimpleOrClaspedTerm
#line 1289 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4017 "GrammarParser.cpp"
    break;

  case 140: // OperatorExpression: Term "+" Term
#line 1301 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4025 "GrammarParser.cpp"
    break;

  case 141: // OperatorExpression: Term "-" Term
#line 1305 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4033 "GrammarParser.cpp"
    break;

  case 142: // OperatorExpression: Term "*" Term
#line 1309 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4041 "GrammarParser.cpp"
    break;

  case 143: // OperatorExpression: Term "/" Term
#line 1313 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4049 "GrammarParser.cpp"
    break;

  case 144: // OperatorExpression: Term "%" Term
#line 1317 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4057 "GrammarParser.cpp"
    break;

  case 145: // OperatorExpression: Term "^" Term
#line 1321 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4065 "GrammarParser.cpp"
    break;

  case 146: // OperatorExpression: Term "!=" Term
#line 1325 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4073 "GrammarParser.cpp"
    break;

  case 147: // OperatorExpression: Term "=" Term
#line 1329 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4081 "GrammarParser.cpp"
    break;

  case 148: // OperatorExpression: Term "<" Term
#line 1333 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4089 "GrammarParser.cpp"
    break;

  case 149: // OperatorExpression: Term ">" Term
#line 1337 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4097 "GrammarParser.cpp"
    break;

  case 150: // OperatorExpression: Term "<=" Term
#line 1341 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4105 "GrammarParser.cpp"
    break;

  case 151: // OperatorExpression: Term ">=" Term
#line 1345 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4113 "GrammarParser.cpp"
    break;

  case 152: // OperatorExpression: Term "or" Term
#line 1349 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4121 "GrammarParser.cpp"
    break;

  case 153: // OperatorExpression: Term "xor" Term
#line 1353 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4129 "GrammarParser.cpp"
    break;

  case 154: // OperatorExpression: Term "and" Term
#line 1357 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4137 "GrammarParser.cpp"
    break;

  case 155: // OperatorExpression: Term "=>" Term
#line 1361 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4145 "GrammarParser.cpp"
    break;

  case 156: // OperatorExpression: Term "implies" Term
#line 1365 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4153 "GrammarParser.cpp"
    break;

  case 157: // OperatorExpression: "not" Term
#line 1369 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4161 "GrammarParser.cpp"
    break;

  case 158: // CallExpression: DirectCallExpression
#line 1377 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 4169 "GrammarParser.cpp"
    break;

  case 159: // CallExpression: MethodCallExpression
#line 1381 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 4177 "GrammarParser.cpp"
    break;

  case 160: // CallExpression: IndirectCallExpression
#line 1385 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 4185 "GrammarParser.cpp"
    break;

  case 161: // DirectCallExpression: "self"
#line 1393 "../../obj/src/GrammarParser.y"
  {
      const auto identifier = Ast::make< Identifier >( yystack_[0].location, yystack_[0].value.as < Ast::Token::Ptr > ()->tokenString() );
      const auto identifierPath = IdentifierPath::fromIdentifier( identifier );
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, identifierPath, arguments );
  }
#line 4196 "GrammarParser.cpp"
    break;

  case 162: // DirectCallExpression: "this"
#line 1400 "../../obj/src/GrammarParser.y"
  {
      const auto identifier = Ast::make< Identifier >( yystack_[0].location, yystack_[0].value.as < Ast::Token::Ptr > ()->tokenString() );
      const auto identifierPath = IdentifierPath::fromIdentifier( identifier );
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, identifierPath, arguments );
  }
#line 4207 "GrammarParser.cpp"
    break;

  case 163: // DirectCallExpression: IdentifierPath
#line 1407 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > (), arguments );
  }
#line 4216 "GrammarParser.cpp"
    break;

  case 164: // DirectCallExpression: IdentifierPath "(" ")"
#line 1412 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), arguments );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4227 "GrammarParser.cpp"
    break;

  case 165: // DirectCallExpression: IdentifierPath "(" Terms ")"
#line 1419 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4237 "GrammarParser.cpp"
    break;

  case 166: // DirectCallExpression: IdentifierPath "(" error ")"
#line 1425 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 4245 "GrammarParser.cpp"
    break;

  case 167: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier
#line 1433 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 4254 "GrammarParser.cpp"
    break;

  case 168: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" ")"
#line 1438 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4265 "GrammarParser.cpp"
    break;

  case 169: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" Terms ")"
#line 1445 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4275 "GrammarParser.cpp"
    break;

  case 170: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" error ")"
#line 1451 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 4283 "GrammarParser.cpp"
    break;

  case 171: // LiteralCallExpression: SimpleOrClaspedTerm "." IntegerLiteral
#line 1459 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 4291 "GrammarParser.cpp"
    break;

  case 172: // IndirectCallExpression: CallExpression "(" ")"
#line 1467 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4302 "GrammarParser.cpp"
    break;

  case 173: // IndirectCallExpression: CallExpression "(" Terms ")"
#line 1474 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4312 "GrammarParser.cpp"
    break;

  case 174: // IndirectCallExpression: CallExpression "(" error ")"
#line 1480 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 4320 "GrammarParser.cpp"
    break;

  case 175: // TypeCastingExpression: SimpleOrClaspedTerm "as" Type
#line 1488 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 4328 "GrammarParser.cpp"
    break;

  case 176: // LetExpression: "let" VariableBindings "in" Term
#line 1496 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4336 "GrammarParser.cpp"
    break;

  case 177: // ConditionalExpression: "if" Term "then" Term "else" Term
#line 1504 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4344 "GrammarParser.cpp"
    break;

  case 178: // ChooseExpression: "choose" AttributedVariables "in" Term "do" Term
#line 1512 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4352 "GrammarParser.cpp"
    break;

  case 179: // UniversalQuantifierExpression: "forall" AttributedVariables "in" Term "holds" Term
#line 1520 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4360 "GrammarParser.cpp"
    break;

  case 180: // ExistentialQuantifierExpression: "exists" AttributedVariables "in" Term "with" Term
#line 1528 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4368 "GrammarParser.cpp"
    break;

  case 181: // CardinalityExpression: "|" SimpleOrClaspedTerm "|"
#line 1536 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4376 "GrammarParser.cpp"
    break;

  case 182: // Literal: UndefinedLiteral
#line 1548 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 4384 "GrammarParser.cpp"
    break;

  case 183: // Literal: BooleanLiteral
#line 1552 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4392 "GrammarParser.cpp"
    break;

  case 184: // Literal: IntegerLiteral
#line 1556 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4400 "GrammarParser.cpp"
    break;

  case 185: // Literal: RationalLiteral
#line 1560 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4408 "GrammarParser.cpp"
    break;

  case 186: // Literal: DecimalLiteral
#line 1564 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4416 "GrammarParser.cpp"
    break;

  case 187: // Literal: BinaryLiteral
#line 1568 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4424 "GrammarParser.cpp"
    break;

  case 188: // Literal: StringLiteral
#line 1572 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4432 "GrammarParser.cpp"
    break;

  case 189: // Literal: ReferenceLiteral
#line 1576 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 4440 "GrammarParser.cpp"
    break;

  case 190: // Literal: ListLiteral
#line 1580 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 4448 "GrammarParser.cpp"
    break;

  case 191: // Literal: RangeLiteral
#line 1584 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 4456 "GrammarParser.cpp"
    break;

  case 192: // Literal: TupleLiteral
#line 1588 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 4464 "GrammarParser.cpp"
    break;

  case 193: // Literal: RecordLiteral
#line 1592 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 4472 "GrammarParser.cpp"
    break;

  case 194: // UndefinedLiteral: "undef"
#line 1600 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4481 "GrammarParser.cpp"
    break;

  case 195: // BooleanLiteral: "true"
#line 1609 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4491 "GrammarParser.cpp"
    break;

  case 196: // BooleanLiteral: "false"
#line 1615 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4501 "GrammarParser.cpp"
    break;

  case 197: // IntegerLiteral: "integer"
#line 1625 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4509 "GrammarParser.cpp"
    break;

  case 198: // RationalLiteral: "rational"
#line 1633 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4517 "GrammarParser.cpp"
    break;

  case 199: // DecimalLiteral: "decimal"
#line 1641 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4525 "GrammarParser.cpp"
    break;

  case 200: // BinaryLiteral: "binary"
#line 1649 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4533 "GrammarParser.cpp"
    break;

  case 201: // BinaryLiteral: "hexadecimal"
#line 1653 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4541 "GrammarParser.cpp"
    break;

  case 202: // StringLiteral: "string"
#line 1661 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4549 "GrammarParser.cpp"
    break;

  case 203: // ReferenceLiteral: "@" IdentifierPath
#line 1669 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4557 "GrammarParser.cpp"
    break;

  case 204: // ListLiteral: "[" "]"
#line 1677 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4568 "GrammarParser.cpp"
    break;

  case 205: // ListLiteral: "[" Terms "]"
#line 1684 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4578 "GrammarParser.cpp"
    break;

  case 206: // ListLiteral: "[" error "]"
#line 1690 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4586 "GrammarParser.cpp"
    break;

  case 207: // RangeLiteral: "[" Term ".." Term "]"
#line 1698 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4596 "GrammarParser.cpp"
    break;

  case 208: // TupleLiteral: "(" Terms "," Term ")"
#line 1708 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4609 "GrammarParser.cpp"
    break;

  case 209: // RecordLiteral: "{" Assignments "}"
#line 1720 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4619 "GrammarParser.cpp"
    break;

  case 210: // Assignments: Assignments "," Assignment
#line 1734 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4630 "GrammarParser.cpp"
    break;

  case 211: // Assignments: Assignment
#line 1741 "../../obj/src/GrammarParser.y"
  {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4640 "GrammarParser.cpp"
    break;

  case 212: // Assignment: Identifier ":" Term
#line 1750 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4648 "GrammarParser.cpp"
    break;

  case 213: // Types: Types "," Type
#line 1762 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4659 "GrammarParser.cpp"
    break;

  case 214: // Types: Type
#line 1769 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4669 "GrammarParser.cpp"
    break;

  case 215: // Type: BasicType
#line 1778 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4677 "GrammarParser.cpp"
    break;

  case 216: // Type: TupleType
#line 1782 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4685 "GrammarParser.cpp"
    break;

  case 217: // Type: RecordType
#line 1786 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4693 "GrammarParser.cpp"
    break;

  case 218: // Type: TemplateType
#line 1790 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4701 "GrammarParser.cpp"
    break;

  case 219: // Type: RelationType
#line 1794 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4709 "GrammarParser.cpp"
    break;

  case 220: // Type: FixedSizedType
#line 1798 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4717 "GrammarParser.cpp"
    break;

  case 221: // BasicType: IdentifierPath
#line 1806 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4725 "GrammarParser.cpp"
    break;

  case 222: // TupleType: "(" Types "," Type ")"
#line 1814 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = Ast::make< TupleType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), subTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4736 "GrammarParser.cpp"
    break;

  case 223: // RecordType: "(" TypedVariables "," TypedVariable ")"
#line 1825 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = Ast::make< RecordType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4747 "GrammarParser.cpp"
    break;

  case 224: // TemplateType: IdentifierPath "<" Types ">"
#line 1836 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4755 "GrammarParser.cpp"
    break;

  case 225: // RelationType: IdentifierPath "<" MaybeFunctionParameters "->" Type ">"
#line 1844 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4763 "GrammarParser.cpp"
    break;

  case 226: // FixedSizedType: IdentifierPath "'" Term
#line 1852 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4771 "GrammarParser.cpp"
    break;

  case 227: // FunctionParameters: FunctionParameters "*" Type
#line 1864 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4782 "GrammarParser.cpp"
    break;

  case 228: // FunctionParameters: Type
#line 1871 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4792 "GrammarParser.cpp"
    break;

  case 229: // MaybeFunctionParameters: FunctionParameters
#line 1881 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 4800 "GrammarParser.cpp"
    break;

  case 230: // MaybeFunctionParameters: %empty
#line 1885 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 4808 "GrammarParser.cpp"
    break;

  case 231: // MethodParameters: MethodParameters "," TypedAttributedVariable
#line 1893 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4819 "GrammarParser.cpp"
    break;

  case 232: // MethodParameters: "this"
#line 1900 "../../obj/src/GrammarParser.y"
  {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto identifier = Ast::make< Identifier >( yystack_[0].location, yystack_[0].value.as < Ast::Token::Ptr > ()->tokenString() );
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      auto variable = Ast::make< VariableDefinition >( yylhs.location, identifier, Token::unresolved(), unresolvedType );
      parameters->add( variable );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4832 "GrammarParser.cpp"
    break;

  case 233: // Parameters: Parameters "," TypedAttributedVariable
#line 1913 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4843 "GrammarParser.cpp"
    break;

  case 234: // Parameters: TypedAttributedVariable
#line 1920 "../../obj/src/GrammarParser.y"
  {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4853 "GrammarParser.cpp"
    break;

  case 235: // MaybeDefined: "defined" "{" Term "}"
#line 1934 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4861 "GrammarParser.cpp"
    break;

  case 236: // MaybeDefined: %empty
#line 1938 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 4869 "GrammarParser.cpp"
    break;

  case 237: // MaybeInitially: "=" "{" Initializers "}"
#line 1946 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4877 "GrammarParser.cpp"
    break;

  case 238: // MaybeInitially: %empty
#line 1950 "../../obj/src/GrammarParser.y"
  {
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 4886 "GrammarParser.cpp"
    break;

  case 239: // Initializers: Initializers "," Initializer
#line 1959 "../../obj/src/GrammarParser.y"
  {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4897 "GrammarParser.cpp"
    break;

  case 240: // Initializers: Initializer
#line 1966 "../../obj/src/GrammarParser.y"
  {
      auto initializers = Ast::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4907 "GrammarParser.cpp"
    break;

  case 241: // Initializer: Term
#line 1976 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4916 "GrammarParser.cpp"
    break;

  case 242: // Initializer: "(" Term ")" "->" Term
#line 1981 "../../obj/src/GrammarParser.y"
  {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), arguments, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4926 "GrammarParser.cpp"
    break;

  case 243: // Initializer: TupleLiteral "->" Term
#line 1987 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4937 "GrammarParser.cpp"
    break;

  case 244: // Identifier: "identifier"
#line 2002 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 4945 "GrammarParser.cpp"
    break;

  case 245: // Identifier: "in"
#line 2006 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 4954 "GrammarParser.cpp"
    break;

  case 246: // Identifier: "CASM"
#line 2011 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 4963 "GrammarParser.cpp"
    break;

  case 247: // Identifier: "enumeration"
#line 2016 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 4972 "GrammarParser.cpp"
    break;

  case 248: // IdentifierPath: IdentifierPath "::" Identifier
#line 2025 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 4983 "GrammarParser.cpp"
    break;

  case 249: // IdentifierPath: Identifier
#line 2032 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4991 "GrammarParser.cpp"
    break;

  case 250: // Variable: TypedVariable
#line 2044 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4999 "GrammarParser.cpp"
    break;

  case 251: // Variable: Identifier
#line 2048 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 5008 "GrammarParser.cpp"
    break;

  case 252: // AttributedVariables: AttributedVariables "," AttributedVariable
#line 2057 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5019 "GrammarParser.cpp"
    break;

  case 253: // AttributedVariables: AttributedVariable
#line 2064 "../../obj/src/GrammarParser.y"
  {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5029 "GrammarParser.cpp"
    break;

  case 254: // TypedVariables: TypedVariables "," TypedVariable
#line 2074 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5040 "GrammarParser.cpp"
    break;

  case 255: // TypedVariables: TypedVariable
#line 2081 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5050 "GrammarParser.cpp"
    break;

  case 256: // TypedVariable: Identifier ":" Type
#line 2091 "../../obj/src/GrammarParser.y"
  {
      auto variable = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5059 "GrammarParser.cpp"
    break;

  case 257: // AttributedVariable: Attributes Variable
#line 2100 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5069 "GrammarParser.cpp"
    break;

  case 258: // AttributedVariable: Variable
#line 2106 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5077 "GrammarParser.cpp"
    break;

  case 259: // TypedAttributedVariable: Attributes TypedVariable
#line 2114 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5087 "GrammarParser.cpp"
    break;

  case 260: // TypedAttributedVariable: TypedVariable
#line 2120 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5095 "GrammarParser.cpp"
    break;

  case 261: // TemplateVariables: TemplateVariables "," TemplateVariable
#line 2128 "../../obj/src/GrammarParser.y"
  {
      auto templateVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      templateVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = templateVariables;
  }
#line 5106 "GrammarParser.cpp"
    break;

  case 262: // TemplateVariables: TemplateVariable
#line 2135 "../../obj/src/GrammarParser.y"
  {
      auto templateVariables = Ast::make< VariableDefinitions >( yylhs.location );
      templateVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = templateVariables;
  }
#line 5116 "GrammarParser.cpp"
    break;

  case 263: // TemplateVariable: Variable
#line 2145 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5124 "GrammarParser.cpp"
    break;

  case 264: // VariableBindings: VariableBindings "," VariableBinding
#line 2158 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5135 "GrammarParser.cpp"
    break;

  case 265: // VariableBindings: VariableBinding
#line 2165 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5145 "GrammarParser.cpp"
    break;

  case 266: // VariableBinding: AttributedVariable "=" Term
#line 2174 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5153 "GrammarParser.cpp"
    break;

  case 267: // LocalFunctionDefinitions: LocalFunctionDefinitions "," AttributedLocalFunctionDefinition
#line 2186 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5164 "GrammarParser.cpp"
    break;

  case 268: // LocalFunctionDefinitions: AttributedLocalFunctionDefinition
#line 2193 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5174 "GrammarParser.cpp"
    break;

  case 269: // AttributedLocalFunctionDefinition: Attributes LocalFunctionDefinition
#line 2202 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 5184 "GrammarParser.cpp"
    break;

  case 270: // AttributedLocalFunctionDefinition: LocalFunctionDefinition
#line 2208 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 5192 "GrammarParser.cpp"
    break;

  case 271: // AttributedLocalFunctionDefinition: error
#line 2212 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 5200 "GrammarParser.cpp"
    break;

  case 272: // LocalFunctionDefinition: Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 2219 "../../obj/src/GrammarParser.y"
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
#line 5216 "GrammarParser.cpp"
    break;

  case 273: // Attributes: Attributes Attribute
#line 2239 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5226 "GrammarParser.cpp"
    break;

  case 274: // Attributes: Attribute
#line 2245 "../../obj/src/GrammarParser.y"
  {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5236 "GrammarParser.cpp"
    break;

  case 275: // Attribute: "[" BasicAttribute "]"
#line 2254 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5247 "GrammarParser.cpp"
    break;

  case 276: // Attribute: "[" ExpressionAttribute "]"
#line 2261 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5258 "GrammarParser.cpp"
    break;

  case 277: // Attribute: "[" error "]"
#line 2268 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 5266 "GrammarParser.cpp"
    break;

  case 278: // BasicAttribute: Identifier
#line 2275 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5274 "GrammarParser.cpp"
    break;

  case 279: // ExpressionAttribute: Identifier Term
#line 2282 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5282 "GrammarParser.cpp"
    break;


#line 5286 "GrammarParser.cpp"

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


  const short Parser::yypact_ninf_ = -447;

  const short Parser::yytable_ninf_ = -229;

  const short
  Parser::yypact_[] =
  {
       7,  -447,    69,    49,   509,    12,  -447,    -5,  -447,  -447,
    -447,  -447,  2244,    30,    67,  -447,  -447,    19,    70,    70,
      70,    70,    70,    70,    70,    70,    25,    25,    25,    70,
     250,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,   341,  -447,  -447,
    -447,  -447,  -447,    20,    20,    20,  2244,    20,  -447,  -447,
    -447,  2244,   691,   691,  1719,  1459,    70,   691,    70,  -447,
    -447,  -447,  -447,  -447,  -447,  3001,   -10,  -447,    76,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,   150,  -447,  -447,  2309,    99,   128,
     122,   188,   157,   117,   177,    74,   190,   198,    70,    27,
      27,    70,   233,  -447,  -447,   247,  -447,  -447,   258,    68,
    -447,    20,    72,  -447,    79,  2538,    83,  -447,  -447,  -447,
     273,   268,  2756,   278,  -447,   104,  2791,    23,  -447,   277,
     201,    99,  2244,  2244,  2244,  2244,  2244,  2244,  2244,  2244,
    2244,  2244,  2244,  2244,  2244,  2244,  2244,  2244,  2244,    27,
      53,  1524,  1589,    70,  1719,  3001,   263,   187,  -447,    34,
      27,   281,  2114,    51,    27,    27,    84,  2244,    70,   285,
     298,  -447,   225,  -447,    27,   307,  -447,  -447,  -447,  -447,
    -447,  -447,    32,  -447,   140,  -447,   -26,    27,    27,  2244,
    2244,    20,  -447,  2244,    20,  2244,  2244,  2244,  -447,  2244,
    -447,  -447,  -447,  2244,  2244,  -447,    70,  2244,  -447,   471,
     989,   918,  3036,   261,   261,   246,   303,   303,   290,   290,
     290,  -447,  3036,   246,   303,   303,  -447,  -447,   308,   309,
    -447,   -32,  3001,   311,  -447,   182,  -447,  2826,  2244,  -447,
    2309,   312,  -447,   214,   218,   247,  -447,  -447,    20,   315,
      57,  1098,  1175,  -447,    20,    65,    20,    20,  2114,  2244,
    2244,  2244,  1252,  1329,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,   295,    91,
     293,   299,   320,   226,   231,   324,  -447,  -447,  3001,  -447,
     100,   108,    70,  -447,   316,  -447,   247,   317,  -447,   322,
      27,    27,  2244,    27,  -447,   318,   326,  -447,  3001,  3001,
    -447,  2686,  -447,  2376,  2615,  2721,  2861,  3001,  2896,  -447,
    3001,  1654,  -447,  -447,  -447,  -447,   332,  3001,  -447,   334,
     335,    20,   338,    20,  -447,  2244,  -447,  -447,   236,  -447,
      20,   363,  1795,  -447,   364,  1872,   105,  -447,   330,   107,
    -447,  -447,    20,   109,   112,  -447,  2577,  2651,  2417,   356,
    1949,   277,   336,  2026,  2244,  2244,   -45,    52,    75,  2114,
    -447,   -18,  -447,   100,    70,    70,  -447,  -447,  -447,   137,
    -447,   108,  -447,    27,    70,   125,   366,   253,   197,   346,
    -447,    27,    27,  2244,  2244,  2244,  2244,  -447,  -447,   367,
    -447,   239,  2244,    27,    27,  -447,    27,  -447,  3001,  -447,
      57,  -447,  -447,  -447,  -447,  -447,  -447,  2114,    27,  2114,
      65,  -447,  2244,  2244,  2114,   333,  2114,  -447,  -447,  -447,
    -447,  3001,  3001,  2114,    27,  2114,    27,  2114,    27,  -447,
    -447,  -447,  -447,   132,   134,  -447,  -447,  -447,  -447,  -447,
     368,   369,  -447,  -447,  -447,   143,   125,   371,    27,  -447,
      27,  -447,   407,  3001,  3001,  3001,  3001,  -447,  -447,  3001,
     374,   377,   378,  -447,  -447,   357,  -447,  -447,  2335,  2458,
     400,  1394,  -447,  -447,   382,  -447,   384,  -447,   388,    27,
      27,  -447,  -447,  -447,  -447,  -447,  -447,   125,  -447,   380,
     390,   396,  2244,  2244,  2244,    27,  2114,  2244,  2114,  2114,
     391,   394,   395,  2179,  -447,  2931,  2114,  2114,  2114,   376,
     381,   149,  -447,  2244,   399,  -447,  3001,  3001,  3001,   407,
    -447,  2499,  -447,  -447,  -447,  2114,  2114,  -447,  -447,  2114,
    -447,  -447,  -447,    27,    27,  -447,  2966,  2309,   396,  2114,
    -447,  -447,  -447,  -447,  -447,  -447,   262,  -447,  -447,  -447
  };

  const short
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   274,     0,   246,   247,
     245,   244,   278,     0,     0,     1,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,    66,    66,     0,
       0,     6,     8,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,     0,     3,   273,
     277,   161,   162,     0,     0,     0,     0,     0,   194,   196,
     195,     0,     0,     0,     0,     0,     0,     0,     0,   200,
     201,   197,   198,   199,   202,   279,   124,   126,   135,   158,
     159,   136,   160,   125,   127,   128,   129,   130,   131,   132,
     137,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   249,   163,   275,   276,     0,    24,     0,
       0,     0,   249,    46,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     5,     7,   251,   258,   250,     0,     0,
     265,     0,     0,   253,     0,     0,     0,   157,   138,   139,
       0,     0,   123,     0,   204,     0,   123,     0,   211,     0,
       0,   203,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   241,   192,     0,   240,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   263,     0,   262,     0,     0,   215,   216,   217,   218,
     219,   220,   221,    75,   221,    76,     0,   230,     0,     0,
       0,     0,   257,     0,     0,     0,     0,     0,   134,     0,
     133,   206,   205,     0,     0,   209,     0,     0,   181,   154,
     152,   153,   156,   140,   141,   147,   148,   149,   142,   143,
     144,   145,   155,   146,   150,   151,   175,   171,   167,     0,
     172,     0,   123,     0,   164,     0,   248,   123,     0,    25,
       0,     0,   232,     0,     0,     0,   260,   234,     0,     0,
       0,     0,     0,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,     0,   120,
     158,   159,     0,     0,     0,     0,    45,    47,    48,    50,
       0,     0,     0,    65,     0,   214,   249,     0,   255,     0,
       0,   230,     0,   230,   228,   229,     0,   256,   266,   176,
     264,     0,   252,     0,     0,     0,   122,   122,     0,   210,
     212,     0,   174,   173,   166,   165,   133,   243,   239,     0,
       0,     0,     0,     0,   259,     0,    42,    44,     0,    40,
       0,     0,     0,    80,     0,     0,     0,   271,     0,     0,
     268,   270,     0,     0,     0,   109,     0,     0,     0,     0,
       0,   249,     0,     0,     0,     0,     0,     0,     0,     0,
      55,     0,    53,     0,     0,     0,    60,    62,    64,     0,
      58,     0,   261,     0,     0,     0,     0,     0,   214,     0,
     226,     0,     0,     0,     0,     0,     0,   208,   207,     0,
     168,     0,     0,     0,     0,   231,     0,   233,    27,    26,
       0,    41,   117,   115,    79,   113,   111,     0,   230,     0,
       0,   269,     0,     0,     0,     0,     0,   112,   110,   116,
     114,   118,   119,     0,     0,     0,     0,     0,     0,    32,
      51,    52,    54,     0,     0,    56,    63,    59,    61,    57,
     213,   254,    70,    72,    74,     0,     0,     0,     0,   224,
       0,   227,   236,   179,   178,   177,   180,   170,   169,   242,
       0,     0,     0,    43,   104,     0,   105,   267,     0,     0,
      95,     0,   121,    37,     0,    35,     0,    33,     0,   230,
     230,   222,   223,    67,    73,    69,    71,     0,   213,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   100,     0,     0,     0,     0,     0,
       0,     0,   225,     0,     0,    39,    30,    29,    28,   236,
     106,     0,   108,    96,    98,     0,     0,    97,    99,     0,
      38,    36,    34,     0,     0,    68,     0,     0,   238,     0,
     101,   102,   103,    77,    78,   235,     0,   272,   107,   237
  };

  const short
  Parser::yypgoto_[] =
  {
    -447,  -447,  -447,  -447,   429,   413,  -447,  -447,    -2,    14,
    -307,    36,  -447,  -447,  -447,  -447,  -447,  -447,  -447,    71,
    -447,    73,  -447,   171,  -447,  -446,   -53,  -447,  -447,    66,
     -37,   494,  -447,  -447,  -447,  -447,   -64,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,   -51,    62,   118,
    -447,   350,   538,   580,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,   300,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,  -102,  -447,  -447,   245,   152,   260,
    -447,  -447,  -447,  -447,   358,  -447,  -447,  -199,   302,   304,
     -68,   -86,   -81,   229,   572,   -17,  -111,   -36,  -447,  -167,
     -42,   -16,  -447,   179,   220,   284,  -447,    56,   127,    13,
      33,  -447,  -447
  };

  const short
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    30,    31,    32,    33,    34,   472,   473,
      37,   357,   358,    38,    39,    40,    41,    42,   391,   392,
      43,   398,   399,   119,    44,   474,   475,    45,    46,   400,
     362,   363,   285,   286,   287,   533,   534,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   141,   175,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   147,   148,   314,   324,
     196,   197,   198,   199,   200,   201,   325,   409,   263,   264,
     521,   545,   177,   178,   103,   104,   126,   132,   317,   127,
     133,   267,   192,   193,   129,   130,   369,   370,   371,   131,
       6,    13,    14
  };

  const short
  Parser::yytable_[] =
  {
     108,    29,    35,   390,   113,   176,   115,   191,   326,   453,
       1,   128,   266,     5,   145,    48,   266,    47,    36,   134,
     212,   136,     8,     8,   343,     9,     9,   318,    35,   514,
       8,   454,   169,     9,   223,   261,   173,     8,    49,     2,
       9,   323,   460,    47,    36,    35,   320,    10,    10,    15,
     262,   151,   302,    50,     8,    10,     8,     9,   356,     9,
       8,    36,    10,     9,     2,   170,   367,   262,     8,     2,
       7,     9,     8,     8,    75,     9,     9,     2,   107,    10,
      49,    10,   194,   225,   390,    10,   462,     8,   105,   226,
       9,     2,   118,    10,   173,   514,   210,    10,    10,   321,
     213,   354,   202,   204,   206,   322,   455,   215,     2,    11,
      11,   217,    10,   394,     2,   395,   188,    11,   135,    29,
     251,   255,     2,   137,    11,   106,   142,   146,   456,   457,
      18,   171,    20,   437,   211,   439,   173,   442,   214,    71,
     443,    11,   394,    11,   395,   214,   171,    11,    18,   214,
      20,   458,   204,   307,    18,    11,    20,     2,   176,    11,
      11,   173,   222,   204,    49,     2,  -135,   204,   204,   128,
     223,   211,   332,   440,    11,   214,   181,   204,   214,   186,
     138,   139,     2,   179,   266,   150,   266,   179,   182,   183,
     204,   204,   268,   509,     2,   510,   268,   465,   120,   121,
       2,   191,   173,   513,   180,   172,     2,   321,   180,   565,
     184,   185,   173,   322,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   187,   128,   252,   252,   365,   257,   471,   345,   495,
     373,   374,   182,   183,   189,   380,   383,   259,   223,   308,
      -2,    16,   190,   260,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,   184,   228,  -228,    27,    28,    29,
     350,   328,   329,  -228,   352,   331,   170,   333,   334,   335,
     351,   336,   387,   360,   353,   337,   338,   388,   372,   340,
     421,   312,   351,   313,   207,   488,   429,   353,   156,   157,
     298,    49,   430,   204,   204,   223,   204,     2,   208,   396,
     539,   540,   209,   159,   160,   161,   162,   163,   164,   478,
     347,   479,   579,   393,   401,   397,   167,   168,   260,   218,
     161,   162,   163,   164,   219,   425,   221,   427,   227,   258,
     270,   376,   377,   378,   310,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,   156,   157,   311,    27,    28,
      29,   319,   164,   341,   268,   342,   268,   344,   349,   355,
     170,   384,   161,   162,   163,   164,   386,   385,   389,   195,
     203,   405,   403,   404,   410,   432,   204,   411,   435,   298,
     298,   438,   501,    49,   204,   204,   298,   396,     2,   467,
     298,   298,   412,   252,   393,    49,   204,   204,   422,   204,
     423,   424,   401,   397,   426,   468,   447,   428,   476,   449,
     477,   204,   480,   487,   511,   512,    49,   520,   522,   246,
     517,   523,   524,   525,    49,   529,   536,   204,   537,   204,
     269,   204,   538,   360,   305,   306,   451,   452,   542,   543,
     544,   554,   563,   372,   315,   555,   556,   564,   567,   123,
     124,   204,   461,   204,   541,   176,   493,   469,   327,   558,
     247,   339,   466,   407,   515,   483,   484,   485,   486,   205,
     298,   568,   577,   298,   489,   303,   576,   304,   476,   348,
     516,   402,   204,   204,   366,   330,   497,     0,   298,   441,
       0,   298,     0,     0,   498,   499,     0,   298,   204,    49,
      16,     0,     0,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,   156,   157,   158,    27,    28,    29,     0,
     476,     0,   299,     0,     0,     0,     0,     0,   159,   160,
     161,   162,   163,   164,     0,     0,   204,   204,     0,     0,
     166,   167,   168,     0,   476,   298,     0,   298,     0,     0,
       0,     0,   298,   535,   298,     0,     2,     0,     0,     0,
       0,   298,     0,   298,    12,   298,     0,     0,     0,     0,
     406,   408,     0,     0,   546,   547,   548,     0,     0,   551,
     109,   110,   111,   112,   114,   535,   116,   117,     0,     0,
       0,   122,     0,     0,     0,   566,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   299,   299,     0,     0,   125,   125,   125,   299,   125,
       0,     0,   299,   299,     0,     0,     0,     0,   149,     0,
       0,     0,     0,     0,   298,     0,   298,   298,     0,     0,
       0,     0,     0,     0,   298,   298,   298,     0,     0,     0,
       0,     0,     0,   470,     0,     0,     0,     0,     0,     0,
       0,   481,   482,   298,   298,     0,   284,   298,     0,     0,
       0,     0,     0,   490,   491,     0,   492,   298,     0,     0,
     125,     0,     0,     0,     8,     0,     0,     9,     0,     0,
       0,     0,     0,   125,     0,     0,    51,    52,     0,     0,
       0,     0,   299,     0,   504,   299,   506,     0,   508,    10,
     300,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     299,     0,     0,   299,     0,    58,    59,    60,   518,   299,
     519,     0,   248,    62,    63,   256,    64,     0,    65,     0,
      66,   265,     0,     0,     0,   265,    68,     0,   256,     0,
     309,     0,   301,     0,     0,     0,   316,     0,     0,     0,
       0,     0,   375,     0,     0,    69,    70,    71,    72,    73,
      74,    11,     0,   125,     0,   549,   125,   299,     0,   299,
       0,     0,     0,     0,   299,     0,   299,     0,   149,     0,
       0,     0,     0,   299,     0,   299,     0,   299,     0,   300,
     300,     0,     0,     0,     0,     0,   300,     0,     0,     0,
     300,   300,     0,   573,   574,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     265,     0,   359,     0,     0,     0,   125,   368,   125,   125,
       0,   301,   301,     0,   381,     0,   434,     0,   301,   434,
       0,     0,   301,   301,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   434,     0,   299,   434,   299,   299,
       0,     0,     0,   459,   125,     0,   299,   299,   299,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     300,     0,     0,   300,     0,   299,   299,     0,     0,   299,
       0,     0,     0,     0,     0,     0,     0,     0,   300,   299,
       0,   300,     0,   265,     0,   265,     0,   300,     0,     0,
       0,   494,   431,   496,     0,     0,     0,     0,   500,     0,
     502,     0,   301,     0,   368,   301,     0,   503,     0,   505,
       0,   507,     0,     0,     0,     0,     0,     0,     0,     0,
     301,     0,     0,   301,     0,   152,   463,   464,     0,   301,
     156,   157,   158,     0,     0,   300,   265,   300,     0,     0,
       0,     0,   300,     0,   300,   159,   160,   161,   162,   163,
     164,   300,     0,   300,     0,   300,     0,   166,   167,   168,
       0,     0,   359,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   368,     0,     0,     0,     0,   301,     0,   301,
     550,     0,   552,   553,   301,     0,   301,     0,     0,     0,
     560,   561,   562,   301,     0,   301,   152,   301,   154,     0,
       0,   156,   157,   158,     0,     0,     0,     0,     0,   570,
     571,     0,     0,   572,     0,     0,   159,   160,   161,   162,
     163,   164,     0,   578,   300,     0,   300,   300,   166,   167,
     168,     0,     0,     0,   300,   300,   300,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   300,   300,     0,     0,   300,     0,   361,
       0,     8,     0,     0,     9,     0,   301,   300,   301,   301,
       0,     0,     0,    51,    52,     0,   301,   301,   301,   271,
       0,   272,     0,   273,   274,   275,    10,   276,   277,   278,
       0,   279,     0,     0,   280,   301,   301,     0,     0,   301,
       0,   281,    58,    59,    60,     0,     0,     0,     0,   301,
      62,    63,     0,    64,     0,    65,     0,   282,     0,     0,
       0,     0,     0,    68,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   364,     0,     8,     0,
     283,     9,    69,    70,    71,    72,    73,    74,    11,     0,
      51,    52,     0,     0,     0,     0,   271,     0,   272,     0,
     273,   274,   275,    10,   276,   277,   278,     0,   279,     0,
       0,   280,     0,     0,     0,     0,     0,     0,   281,    58,
      59,    60,     0,     0,     0,     0,     0,    62,    63,     0,
      64,     0,    65,     0,   282,     0,     0,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   379,     0,     8,     0,   283,     9,    69,
      70,    71,    72,    73,    74,    11,     0,    51,    52,     0,
       0,     0,     0,   271,     0,   272,     0,   273,   274,   275,
      10,   276,   277,   278,     0,   279,     0,     0,   280,     0,
       0,     0,     0,     0,     0,   281,    58,    59,    60,     0,
       0,     0,     0,     0,    62,    63,     0,    64,     0,    65,
       0,   282,     0,     0,     0,     0,     0,    68,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     382,     0,     8,     0,   283,     9,    69,    70,    71,    72,
      73,    74,    11,     0,    51,    52,     0,     0,     0,     0,
     271,     0,   272,     0,   273,   274,   275,    10,   276,   277,
     278,     0,   279,     0,     0,   280,     0,     0,     0,     0,
       0,     0,   281,    58,    59,    60,     0,     0,     0,     0,
       0,    62,    63,     0,    64,     0,    65,     0,   282,     0,
       0,     0,     0,     0,    68,   530,     0,     8,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,   283,     0,    69,    70,    71,    72,    73,    74,    11,
      53,     0,    10,    54,    55,     0,     0,    56,     0,     0,
       0,     0,   531,     0,    57,     0,     0,     0,    58,    59,
      60,     0,     0,     0,     0,    61,    62,    63,     0,    64,
       0,    65,     0,    66,     0,     0,     0,   532,    67,    68,
     143,     0,     8,     0,     0,     9,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,     0,     0,    69,    70,
      71,    72,    73,    74,    11,    53,     0,    10,    54,    55,
       0,     0,    56,     0,     0,     0,     0,     0,     0,    57,
       0,     0,     0,    58,    59,    60,     0,     0,     0,     0,
      61,    62,    63,     0,    64,     0,    65,   144,    66,     0,
       0,     0,     0,    67,    68,   249,     0,     8,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,     0,     0,    69,    70,    71,    72,    73,    74,    11,
      53,     0,    10,    54,    55,     0,     0,    56,     0,     0,
       0,     0,     0,     0,    57,     0,     0,     0,    58,    59,
      60,     0,     0,     0,     0,    61,    62,    63,     0,    64,
     250,    65,     0,    66,     0,     0,     0,     0,    67,    68,
     253,     0,     8,     0,     0,     9,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,     0,     0,    69,    70,
      71,    72,    73,    74,    11,    53,     0,    10,    54,    55,
       0,     0,    56,     0,     0,     0,     0,     0,     0,    57,
       0,     0,     0,    58,    59,    60,     0,     0,     0,     0,
      61,    62,    63,     0,    64,   254,    65,     0,    66,     0,
       0,     0,     0,    67,    68,   419,     0,     8,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,     0,     0,    69,    70,    71,    72,    73,    74,    11,
      53,     0,    10,    54,    55,     0,     0,    56,     0,     0,
       0,     0,     0,     0,    57,     0,     0,     0,    58,    59,
      60,     0,     0,     0,     0,    61,    62,    63,     0,    64,
     420,    65,     0,    66,     0,     0,     0,     0,    67,    68,
     140,     0,     8,     0,     0,     9,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,     0,     0,    69,    70,
      71,    72,    73,    74,    11,    53,     0,    10,    54,    55,
       0,     0,    56,     0,     0,     0,     0,     0,     0,    57,
       0,     0,     0,    58,    59,    60,     0,     0,     0,     0,
      61,    62,    63,     0,    64,     0,    65,     0,    66,     0,
       0,     0,     0,    67,    68,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       0,     9,     0,    69,    70,    71,    72,    73,    74,    11,
      51,    52,     0,     0,     0,     0,   271,   433,   272,     0,
     273,   274,   275,    10,   276,   277,   278,     0,   279,     0,
       0,   280,     0,     0,     0,     0,     0,     0,   281,    58,
      59,    60,     0,     0,     0,     0,     0,    62,    63,     0,
      64,     0,    65,     0,   282,     0,     0,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,   283,     9,    69,
      70,    71,    72,    73,    74,    11,     0,    51,    52,     0,
       0,     0,     0,   271,     0,   272,   436,   273,   274,   275,
      10,   276,   277,   278,     0,   279,     0,     0,   280,     0,
       0,     0,     0,     0,     0,   281,    58,    59,    60,     0,
       0,     0,     0,     0,    62,    63,     0,    64,     0,    65,
       0,   282,     0,     0,     0,     0,     0,    68,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,   283,     9,    69,    70,    71,    72,
      73,    74,    11,     0,    51,    52,     0,     0,     0,     0,
     271,     0,   272,     0,   273,   274,   275,    10,   276,   277,
     278,     0,   279,     0,     0,   280,     0,     0,     0,     0,
       0,     0,   281,    58,    59,    60,     0,     0,     0,     0,
       0,    62,    63,     0,    64,     0,    65,     0,   282,   448,
       0,     0,     0,     0,    68,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       0,   283,     9,    69,    70,    71,    72,    73,    74,    11,
       0,    51,    52,     0,     0,     0,     0,   271,     0,   272,
       0,   273,   274,   275,    10,   276,   277,   278,     0,   279,
       0,     0,   280,     0,     0,     0,     0,     0,     0,   281,
      58,    59,    60,     0,     0,     0,     0,     0,    62,    63,
       0,    64,     0,    65,     0,   282,     0,     0,     0,     0,
       0,    68,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   283,   450,
      69,    70,    71,    72,    73,    74,    11,     8,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,     0,     0,     0,     0,   271,     0,   272,     0,   273,
     274,   275,    10,   276,   277,   278,     0,   279,     0,     0,
     280,     0,     0,     0,     0,     0,     0,   281,    58,    59,
      60,     0,     0,     0,     0,     0,    62,    63,     0,    64,
       0,    65,     0,   282,     0,     0,     0,     0,     0,    68,
       0,     0,     8,     0,     0,     9,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,   283,     0,    69,    70,
      71,    72,    73,    74,    11,    53,     0,    10,    54,    55,
       0,     0,    56,     0,     0,     0,     0,   531,     0,    57,
       0,     0,     0,    58,    59,    60,     0,     0,     0,     0,
      61,    62,    63,     0,    64,     0,    65,     0,    66,   557,
       0,     0,   532,    67,    68,     0,     0,     8,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,     0,     0,    69,    70,    71,    72,    73,    74,    11,
      53,     0,    10,    54,    55,     0,     0,    56,     0,     0,
       0,     0,     0,     0,    57,     0,     0,     0,    58,    59,
      60,     0,     0,     0,     0,    61,    62,    63,     0,    64,
       0,    65,     0,    66,     0,     0,     0,     0,    67,    68,
       0,     0,     8,     0,     0,     9,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,     0,     0,    69,    70,
      71,    72,    73,    74,    11,    53,     0,    10,    54,    55,
       0,     0,    56,     0,     0,     0,     0,     0,     0,    57,
       0,     0,     0,    58,    59,    60,     0,     0,     0,     0,
      61,    62,    63,     0,   174,     0,    65,   526,    66,     0,
       0,     0,     0,    67,    68,     0,   527,     0,     0,     0,
       0,     0,   152,   153,   154,   155,     0,   156,   157,   158,
       0,     0,     0,    69,    70,    71,    72,    73,    74,    11,
       0,     0,   159,   160,   161,   162,   163,   164,   414,     0,
       0,     0,   165,     0,   166,   167,   168,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,     0,   156,   157,
     158,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,   160,   161,   162,   163,   164,   446,
       0,     0,     0,   165,     0,   166,   167,   168,     0,     0,
       0,     0,     0,     0,   152,   153,   154,   155,     0,   156,
     157,   158,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,   160,   161,   162,   163,   164,
     528,     0,     0,     0,   165,     0,   166,   167,   168,     0,
       0,     0,     0,     0,     0,   152,   153,   154,   155,     0,
     156,   157,   158,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   159,   160,   161,   162,   163,
     164,   569,     0,     0,     0,   165,     0,   166,   167,   168,
       0,     0,     0,     0,     0,     0,   152,   153,   154,   155,
       0,   156,   157,   158,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   159,   160,   161,   162,
     163,   164,   216,     0,     0,     0,   165,     0,   166,   167,
     168,     0,     0,     0,     0,   152,   153,   154,   155,     0,
     156,   157,   158,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   159,   160,   161,   162,   163,
     164,   444,     0,     0,     0,   165,     0,   166,   167,   168,
       0,     0,     0,     0,   152,   153,   154,   155,     0,   156,
     157,   158,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,   160,   161,   162,   163,   164,
     415,     0,     0,     0,   165,     0,   166,   167,   168,     0,
       0,     0,   152,   153,   154,   155,     0,   156,   157,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,   445,     0,
       0,     0,   165,     0,   166,   167,   168,     0,   152,   153,
     154,   155,     0,   156,   157,   158,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,   160,
     161,   162,   163,   164,     0,   413,     0,     0,   165,     0,
     166,   167,   168,   152,   153,   154,   155,     0,   156,   157,
     158,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,   160,   161,   162,   163,   164,     0,
       0,     0,   416,   165,     0,   166,   167,   168,   152,   153,
     154,   155,     0,   156,   157,   158,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,   160,
     161,   162,   163,   164,     0,     0,     0,     0,   165,     0,
     166,   167,   168,   152,   153,   154,   155,     0,   156,   157,
     158,     0,   220,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,   160,   161,   162,   163,   164,     0,
       0,     0,     0,   165,     0,   166,   167,   168,   152,   153,
     154,   155,     0,   156,   157,   158,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,   160,
     161,   162,   163,   164,     0,   224,     0,     0,   165,     0,
     166,   167,   168,   152,   153,   154,   155,     0,   156,   157,
     158,     0,   346,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,   160,   161,   162,   163,   164,     0,
       0,     0,     0,   165,     0,   166,   167,   168,   152,   153,
     154,   155,     0,   156,   157,   158,     0,   417,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,   160,
     161,   162,   163,   164,     0,     0,     0,     0,   165,     0,
     166,   167,   168,   152,   153,   154,   155,     0,   156,   157,
     158,     0,     0,     0,   418,     0,     0,     0,     0,     0,
       0,     0,     0,   159,   160,   161,   162,   163,   164,     0,
       0,     0,     0,   165,     0,   166,   167,   168,   152,   153,
     154,   155,     0,   156,   157,   158,     0,     0,     0,     0,
       0,     0,   559,     0,     0,     0,     0,     0,   159,   160,
     161,   162,   163,   164,     0,     0,     0,     0,   165,     0,
     166,   167,   168,   152,   153,   154,   155,     0,   156,   157,
     158,     0,     0,     0,     0,     0,   575,     0,     0,     0,
       0,     0,     0,   159,   160,   161,   162,   163,   164,     0,
       0,     0,     0,   165,     0,   166,   167,   168,   152,   153,
     154,   155,     0,   156,   157,   158,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,   160,
     161,   162,   163,   164,     0,     0,     0,     0,   165,     0,
     166,   167,   168,   152,   153,   154,     0,     0,   156,   157,
     158,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,   160,   161,   162,   163,   164,     0,
       0,     0,     0,     0,     0,   166,   167,   168
  };

  const short
  Parser::yycheck_[] =
  {
      17,    19,     4,   310,    21,   107,    23,   118,   207,    54,
       3,    53,   179,     0,    65,     3,   183,     4,     4,    55,
     131,    57,     3,     3,    56,     6,     6,   194,    30,   475,
       3,    76,    42,     6,    66,     1,    62,     3,     5,    57,
       6,    67,    60,    30,    30,    47,    14,    28,    28,     0,
      16,    68,     1,    58,     3,    28,     3,     6,     1,     6,
       3,    47,    28,     6,    57,    75,     1,    16,     3,    57,
       1,     6,     3,     3,    12,     6,     6,    57,    59,    28,
      47,    28,    55,    60,   391,    28,   393,     3,    58,    66,
       6,    57,    67,    28,    62,   541,    28,    28,    28,    67,
      28,   268,   119,   120,   121,    73,    54,    28,    57,    90,
      90,    28,    28,     5,    57,     7,    42,    90,    56,    19,
     171,   172,    57,    61,    90,    58,    64,    65,    76,    54,
       5,    55,     7,    28,    66,    28,    62,    28,    66,    86,
      28,    90,     5,    90,     7,    66,    55,    90,     5,    66,
       7,    76,   169,    69,     5,    90,     7,    57,   260,    90,
      90,    62,    58,   180,   131,    57,    75,   184,   185,   211,
      66,    66,   214,    66,    90,    66,    54,   194,    66,    62,
      62,    63,    57,    55,   351,    67,   353,    55,    54,    55,
     207,   208,   179,    61,    57,    61,   183,    60,    27,    28,
      57,   312,    62,    60,    76,    55,    57,    67,    76,    60,
      76,    54,    62,    73,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,    54,   274,   171,   172,   272,   174,   404,    56,   438,
     276,   277,    54,    55,    54,   282,   283,    60,    66,   187,
       0,     1,    54,    66,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    76,    64,    69,    17,    18,    19,
      56,   209,   210,    76,    56,   213,    75,   215,   216,   217,
      66,   219,    56,   270,    66,   223,   224,    56,   275,   227,
     341,    66,    66,    68,    61,    56,    60,    66,    52,    53,
     182,   268,    66,   320,   321,    66,   323,    57,    61,   311,
     509,   510,    54,    67,    68,    69,    70,    71,    72,    66,
     258,    68,    60,   310,   311,   311,    80,    81,    66,    56,
      69,    70,    71,    72,    66,   351,    58,   353,    61,    76,
      59,   279,   280,   281,    59,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    52,    53,    59,    17,    18,
      19,    54,    72,    55,   351,    56,   353,    56,    56,    54,
      75,    78,    69,    70,    71,    72,    56,    78,    54,   119,
     120,    59,    66,    66,   322,    22,   403,    69,    24,   271,
     272,    61,    59,   360,   411,   412,   278,   399,    57,   401,
     282,   283,    76,   341,   391,   372,   423,   424,    76,   426,
      76,    76,   399,   399,    76,   401,    60,   355,   405,    83,
      54,   438,    76,    56,    56,    56,   393,    20,    54,   169,
      59,    54,    54,    76,   401,    35,    54,   454,    54,   456,
     180,   458,    54,   430,   184,   185,   384,   385,    68,    59,
      54,    60,    76,   440,   194,    61,    61,    76,    59,    30,
      47,   478,   391,   480,   517,   567,   430,   401,   208,   533,
     170,   226,   399,   321,   476,   413,   414,   415,   416,   121,
     362,   549,   568,   365,   422,   183,   567,   183,   475,   260,
     476,   312,   509,   510,   274,   211,   440,    -1,   380,   372,
      -1,   383,    -1,    -1,   442,   443,    -1,   389,   525,   476,
       1,    -1,    -1,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    52,    53,    54,    17,    18,    19,    -1,
     517,    -1,   182,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,   563,   564,    -1,    -1,
      79,    80,    81,    -1,   541,   437,    -1,   439,    -1,    -1,
      -1,    -1,   444,   501,   446,    -1,    57,    -1,    -1,    -1,
      -1,   453,    -1,   455,     2,   457,    -1,    -1,    -1,    -1,
     320,   321,    -1,    -1,   522,   523,   524,    -1,    -1,   527,
      18,    19,    20,    21,    22,   533,    24,    25,    -1,    -1,
      -1,    29,    -1,    -1,    -1,   543,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   271,   272,    -1,    -1,    53,    54,    55,   278,    57,
      -1,    -1,   282,   283,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,   526,    -1,   528,   529,    -1,    -1,
      -1,    -1,    -1,    -1,   536,   537,   538,    -1,    -1,    -1,
      -1,    -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   411,   412,   555,   556,    -1,   182,   559,    -1,    -1,
      -1,    -1,    -1,   423,   424,    -1,   426,   569,    -1,    -1,
     118,    -1,    -1,    -1,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    -1,   131,    -1,    -1,    15,    16,    -1,    -1,
      -1,    -1,   362,    -1,   454,   365,   456,    -1,   458,    28,
     182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     380,    -1,    -1,   383,    -1,    44,    45,    46,   478,   389,
     480,    -1,   170,    52,    53,   173,    55,    -1,    57,    -1,
      59,   179,    -1,    -1,    -1,   183,    65,    -1,   186,    -1,
     188,    -1,   182,    -1,    -1,    -1,   194,    -1,    -1,    -1,
      -1,    -1,   278,    -1,    -1,    84,    85,    86,    87,    88,
      89,    90,    -1,   211,    -1,   525,   214,   437,    -1,   439,
      -1,    -1,    -1,    -1,   444,    -1,   446,    -1,   226,    -1,
      -1,    -1,    -1,   453,    -1,   455,    -1,   457,    -1,   271,
     272,    -1,    -1,    -1,    -1,    -1,   278,    -1,    -1,    -1,
     282,   283,    -1,   563,   564,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     268,    -1,   270,    -1,    -1,    -1,   274,   275,   276,   277,
      -1,   271,   272,    -1,   282,    -1,   362,    -1,   278,   365,
      -1,    -1,   282,   283,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   380,    -1,   526,   383,   528,   529,
      -1,    -1,    -1,   389,   312,    -1,   536,   537,   538,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     362,    -1,    -1,   365,    -1,   555,   556,    -1,    -1,   559,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   380,   569,
      -1,   383,    -1,   351,    -1,   353,    -1,   389,    -1,    -1,
      -1,   437,   360,   439,    -1,    -1,    -1,    -1,   444,    -1,
     446,    -1,   362,    -1,   372,   365,    -1,   453,    -1,   455,
      -1,   457,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     380,    -1,    -1,   383,    -1,    47,   394,   395,    -1,   389,
      52,    53,    54,    -1,    -1,   437,   404,   439,    -1,    -1,
      -1,    -1,   444,    -1,   446,    67,    68,    69,    70,    71,
      72,   453,    -1,   455,    -1,   457,    -1,    79,    80,    81,
      -1,    -1,   430,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   440,    -1,    -1,    -1,    -1,   437,    -1,   439,
     526,    -1,   528,   529,   444,    -1,   446,    -1,    -1,    -1,
     536,   537,   538,   453,    -1,   455,    47,   457,    49,    -1,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,   555,
     556,    -1,    -1,   559,    -1,    -1,    67,    68,    69,    70,
      71,    72,    -1,   569,   526,    -1,   528,   529,    79,    80,
      81,    -1,    -1,    -1,   536,   537,   538,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   555,   556,    -1,    -1,   559,    -1,     1,
      -1,     3,    -1,    -1,     6,    -1,   526,   569,   528,   529,
      -1,    -1,    -1,    15,    16,    -1,   536,   537,   538,    21,
      -1,    23,    -1,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    -1,    -1,    36,   555,   556,    -1,    -1,   559,
      -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,   569,
      52,    53,    -1,    55,    -1,    57,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,    -1,
      82,     6,    84,    85,    86,    87,    88,    89,    90,    -1,
      15,    16,    -1,    -1,    -1,    -1,    21,    -1,    23,    -1,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,
      55,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,     3,    -1,    82,     6,    84,
      85,    86,    87,    88,    89,    90,    -1,    15,    16,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    52,    53,    -1,    55,    -1,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,     3,    -1,    82,     6,    84,    85,    86,    87,
      88,    89,    90,    -1,    15,    16,    -1,    -1,    -1,    -1,
      21,    -1,    23,    -1,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    52,    53,    -1,    55,    -1,    57,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    65,     1,    -1,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    82,    -1,    84,    85,    86,    87,    88,    89,    90,
      26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    38,    -1,    40,    -1,    -1,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    55,
      -1,    57,    -1,    59,    -1,    -1,    -1,    63,    64,    65,
       1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    26,    -1,    28,    29,    30,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      51,    52,    53,    -1,    55,    -1,    57,    58,    59,    -1,
      -1,    -1,    -1,    64,    65,     1,    -1,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    -1,    -1,    84,    85,    86,    87,    88,    89,    90,
      26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    55,
      56,    57,    -1,    59,    -1,    -1,    -1,    -1,    64,    65,
       1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    26,    -1,    28,    29,    30,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      51,    52,    53,    -1,    55,    56,    57,    -1,    59,    -1,
      -1,    -1,    -1,    64,    65,     1,    -1,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    -1,    -1,    84,    85,    86,    87,    88,    89,    90,
      26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    55,
      56,    57,    -1,    59,    -1,    -1,    -1,    -1,    64,    65,
       1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    26,    -1,    28,    29,    30,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      51,    52,    53,    -1,    55,    -1,    57,    -1,    59,    -1,
      -1,    -1,    -1,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,     6,    -1,    84,    85,    86,    87,    88,    89,    90,
      15,    16,    -1,    -1,    -1,    -1,    21,    22,    23,    -1,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,
      55,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    82,     6,    84,
      85,    86,    87,    88,    89,    90,    -1,    15,    16,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    52,    53,    -1,    55,    -1,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    82,     6,    84,    85,    86,    87,
      88,    89,    90,    -1,    15,    16,    -1,    -1,    -1,    -1,
      21,    -1,    23,    -1,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    52,    53,    -1,    55,    -1,    57,    -1,    59,    60,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    82,     6,    84,    85,    86,    87,    88,    89,    90,
      -1,    15,    16,    -1,    -1,    -1,    -1,    21,    -1,    23,
      -1,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,    53,
      -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    83,
      84,    85,    86,    87,    88,    89,    90,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    -1,    -1,    -1,    -1,    21,    -1,    23,    -1,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    55,
      -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    82,    -1,    84,    85,
      86,    87,    88,    89,    90,    26,    -1,    28,    29,    30,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    38,    -1,    40,
      -1,    -1,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      51,    52,    53,    -1,    55,    -1,    57,    -1,    59,    60,
      -1,    -1,    63,    64,    65,    -1,    -1,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    -1,    -1,    84,    85,    86,    87,    88,    89,    90,
      26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    55,
      -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    64,    65,
      -1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    26,    -1,    28,    29,    30,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      51,    52,    53,    -1,    55,    -1,    57,    32,    59,    -1,
      -1,    -1,    -1,    64,    65,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    47,    48,    49,    50,    -1,    52,    53,    54,
      -1,    -1,    -1,    84,    85,    86,    87,    88,    89,    90,
      -1,    -1,    67,    68,    69,    70,    71,    72,    32,    -1,
      -1,    -1,    77,    -1,    79,    80,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    32,
      -1,    -1,    -1,    77,    -1,    79,    80,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      32,    -1,    -1,    -1,    77,    -1,    79,    80,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    32,    -1,    -1,    -1,    77,    -1,    79,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    34,    -1,    -1,    -1,    77,    -1,    79,    80,
      81,    -1,    -1,    -1,    -1,    47,    48,    49,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    34,    -1,    -1,    -1,    77,    -1,    79,    80,    81,
      -1,    -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      35,    -1,    -1,    -1,    77,    -1,    79,    80,    81,    -1,
      -1,    -1,    47,    48,    49,    50,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    37,    -1,
      -1,    -1,    77,    -1,    79,    80,    81,    -1,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    39,    -1,    -1,    77,    -1,
      79,    80,    81,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    41,    77,    -1,    79,    80,    81,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,
      79,    80,    81,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    77,    -1,    79,    80,    81,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    74,    -1,    -1,    77,    -1,
      79,    80,    81,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    77,    -1,    79,    80,    81,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,
      79,    80,    81,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    77,    -1,    79,    80,    81,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,
      79,    80,    81,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    77,    -1,    79,    80,    81,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,
      79,    80,    81,    47,    48,    49,    -1,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    80,    81
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    57,    97,    98,   205,   206,     1,     3,     6,
      28,    90,   190,   207,   208,     0,     1,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    17,    18,    19,
      99,   100,   101,   102,   103,   104,   105,   106,   109,   110,
     111,   112,   113,   116,   120,   123,   124,   205,     3,   206,
      58,    15,    16,    26,    29,    30,    33,    40,    44,    45,
      46,    51,    52,    53,    55,    57,    59,    64,    65,    84,
      85,    86,    87,    88,    89,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   190,   191,    58,    58,    59,   191,   190,
     190,   190,   190,   191,   190,   191,   190,   190,    67,   119,
     119,   119,   190,   100,   101,   190,   192,   195,   196,   200,
     201,   205,   193,   196,   193,   144,   193,   144,   145,   145,
       1,   143,   144,     1,    58,   143,   144,   172,   173,   190,
     145,   191,    47,    48,    49,    50,    52,    53,    54,    67,
      68,    69,    70,    71,    72,    77,    79,    80,    81,    42,
      75,    55,    55,    62,    55,   144,   170,   188,   189,    55,
      76,    54,    54,    55,    76,    54,    62,    54,    42,    54,
      54,   192,   198,   199,    55,   175,   176,   177,   178,   179,
     180,   181,   191,   175,   191,   180,   191,    61,    61,    54,
      28,    66,   192,    28,    66,    28,    34,    28,    56,    66,
      56,    58,    58,    66,    74,    60,    66,    61,    64,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   175,   162,   190,     1,
      56,   143,   144,     1,    56,   143,   190,   144,    76,    60,
      66,     1,    16,   184,   185,   190,   195,   197,   205,   175,
      59,    21,    23,    25,    26,    27,    29,    30,    31,    33,
      36,    43,    59,    82,   127,   128,   129,   130,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   145,   147,
     148,   149,     1,   184,   185,   175,   175,    69,   144,   190,
      59,    59,    66,    68,   174,   175,   190,   194,   195,    54,
      14,    67,    73,    67,   175,   182,   183,   175,   144,   144,
     201,   144,   196,   144,   144,   144,   144,   144,   144,   173,
     144,    55,    56,    56,    56,    56,    56,   144,   189,    56,
      56,    66,    56,    66,   195,    54,     1,   107,   108,   190,
     205,     1,   126,   127,     1,   126,   200,     1,   190,   202,
     203,   204,   205,   193,   193,   127,   144,   144,   144,     1,
     126,   190,     1,   126,    78,    78,    56,    56,    56,    54,
     106,   114,   115,   205,     5,     7,   104,   105,   117,   118,
     125,   205,   199,    66,    66,    59,   175,   174,   175,   183,
     144,    69,    76,    39,    32,    35,    41,    56,    58,     1,
      56,   143,    76,    76,    76,   197,    76,   197,   144,    60,
      66,   190,    22,    22,   127,    24,    24,    28,    61,    28,
      66,   204,    28,    28,    34,    37,    32,    60,    60,    83,
      83,   144,   144,    54,    76,    54,    76,    54,    76,   127,
      60,   115,   106,   190,   190,    60,   117,   104,   105,   125,
     175,   195,   104,   105,   121,   122,   205,    54,    66,    68,
      76,   175,   175,   144,   144,   144,   144,    56,    56,   144,
     175,   175,   175,   107,   127,   183,   127,   203,   144,   144,
     127,    59,   127,   127,   175,   127,   175,   127,   175,    61,
      61,    56,    56,    60,   121,   104,   105,    59,   175,   175,
      20,   186,    54,    54,    54,    76,    32,    41,    32,    35,
       1,    38,    63,   131,   132,   144,    54,    54,    54,   183,
     183,   122,    68,    59,    54,   187,   144,   144,   144,   175,
     127,   144,   127,   127,    60,    61,    61,    60,   132,    61,
     127,   127,   127,    76,    76,    60,   144,    59,   186,    32,
     127,   127,   127,   175,   175,    60,   188,   187,   127,    60
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    96,    97,    98,    98,    99,    99,   100,   100,   100,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   102,   102,   103,   104,   104,   104,
     104,   105,   105,   105,   105,   105,   105,   105,   105,   106,
     107,   107,   107,   108,   108,   109,   110,   110,   111,   112,
     112,   113,   114,   114,   115,   115,   116,   117,   117,   117,
     117,   117,   117,   118,   118,   119,   119,   120,   120,   121,
     121,   121,   121,   122,   122,   123,   124,   125,   125,   126,
     126,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   128,   129,   129,   130,   130,   131,
     131,   132,   132,   132,   133,   134,   135,   135,   136,   137,
     138,   138,   138,   138,   139,   139,   139,   139,   140,   140,
     141,   142,   143,   143,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   145,   145,   145,   145,   145,   145,   145,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   147,   147,
     147,   148,   148,   148,   148,   148,   148,   149,   149,   149,
     149,   150,   151,   151,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   160,   161,   161,   162,   163,   164,
     165,   165,   166,   167,   168,   168,   168,   169,   170,   171,
     172,   172,   173,   174,   174,   175,   175,   175,   175,   175,
     175,   176,   177,   178,   179,   180,   181,   182,   182,   183,
     183,   184,   184,   185,   185,   186,   186,   187,   187,   188,
     188,   189,   189,   189,   190,   190,   190,   190,   191,   191,
     192,   192,   193,   193,   194,   194,   195,   196,   196,   197,
     197,   198,   198,   199,   200,   200,   201,   202,   202,   203,
     203,   203,   204,   205,   205,   206,   206,   206,   207,   208
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     4,     6,     6,     9,     9,
       9,     4,     6,     7,     9,     7,     9,     7,     9,     8,
       1,     2,     1,     3,     1,     4,     2,     4,     4,     2,
       4,     6,     2,     1,     2,     1,     6,     2,     1,     2,
       1,     2,     1,     2,     1,     3,     0,     7,     9,     2,
       1,     2,     1,     2,     1,     3,     3,     6,     6,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     6,     6,     6,     2,
       1,     3,     3,     3,     4,     4,     6,     8,     6,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     4,     4,     3,     5,     6,
       6,     3,     3,     4,     4,     3,     4,     6,     6,     6,
       6,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     3,     3,     5,     5,     3,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     5,     4,     6,     3,     3,     1,     1,
       0,     3,     1,     3,     1,     4,     0,     4,     0,     3,
       1,     1,     5,     3,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     3,     1,     3,     2,     1,     2,
       1,     3,     1,     1,     3,     1,     3,     3,     1,     2,
       1,     1,     7,     2,     1,     3,     3,     3,     1,     2
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
  "\"implement\"", "\"for\"", "\"self\"", "\"this\"", "\"domain\"",
  "\"builtin\"", "\"function\"", "\"defined\"", "\"seq\"", "\"endseq\"",
  "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"", "\"local\"", "\"in\"",
  "\"forall\"", "\"choose\"", "\"iterate\"", "\"do\"", "\"if\"",
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
  "Definition", "InitDefinition", "EnumerationDefinition",
  "DerivedDefinition", "RuleDefinition", "FunctionDefinition",
  "EnumeratorDefinition", "Enumerators", "UsingDefinition",
  "UsingPathDefinition", "InvariantDefinition", "ImportDefinition",
  "StructureDefinition", "StructureDefinitionList",
  "StructureDefinitionElement", "FeatureDefinition",
  "FeatureDefinitionElement", "FeatureDefinitionList", "TemplateSymbols",
  "ImplementDefinition", "ImplementDefinitionElement",
  "ImplementDefinitionList", "DomainDefinition", "BuiltinDefinition",
  "Declaration", "Rules", "Rule", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabels", "CaseLabel", "LetRule", "LocalRule",
  "ForallRule", "ChooseRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", "WhileRule", "Terms", "Term",
  "SimpleOrClaspedTerm", "OperatorExpression", "CallExpression",
  "DirectCallExpression", "MethodCallExpression", "LiteralCallExpression",
  "IndirectCallExpression", "TypeCastingExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "CardinalityExpression", "Literal", "UndefinedLiteral", "BooleanLiteral",
  "IntegerLiteral", "RationalLiteral", "DecimalLiteral", "BinaryLiteral",
  "StringLiteral", "ReferenceLiteral", "ListLiteral", "RangeLiteral",
  "TupleLiteral", "RecordLiteral", "Assignments", "Assignment", "Types",
  "Type", "BasicType", "TupleType", "RecordType", "TemplateType",
  "RelationType", "FixedSizedType", "FunctionParameters",
  "MaybeFunctionParameters", "MethodParameters", "Parameters",
  "MaybeDefined", "MaybeInitially", "Initializers", "Initializer",
  "Identifier", "IdentifierPath", "Variable", "AttributedVariables",
  "TypedVariables", "TypedVariable", "AttributedVariable",
  "TypedAttributedVariable", "TemplateVariables", "TemplateVariable",
  "VariableBindings", "VariableBinding", "LocalFunctionDefinitions",
  "AttributedLocalFunctionDefinition", "LocalFunctionDefinition",
  "Attributes", "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   440,   440,   450,   456,   464,   470,   480,   486,   490,
     498,   502,   506,   510,   514,   518,   522,   526,   530,   534,
     538,   542,   546,   550,   558,   562,   570,   578,   583,   589,
     595,   603,   609,   614,   621,   627,   634,   640,   644,   652,
     660,   664,   670,   678,   685,   695,   703,   707,   715,   727,
     731,   739,   746,   752,   761,   767,   779,   787,   793,   797,
     803,   807,   813,   821,   827,   837,   842,   855,   859,   867,
     873,   877,   883,   891,   897,   911,   923,   935,   939,   951,
     957,   967,   971,   975,   979,   983,   987,   991,   995,   999,
    1003,  1007,  1011,  1015,  1023,  1031,  1035,  1043,  1047,  1055,
    1061,  1071,  1075,  1079,  1087,  1095,  1103,  1107,  1115,  1123,
    1131,  1135,  1139,  1144,  1153,  1157,  1161,  1166,  1175,  1179,
    1187,  1195,  1207,  1214,  1224,  1228,  1232,  1236,  1240,  1244,
    1248,  1252,  1256,  1264,  1268,  1272,  1276,  1280,  1284,  1288,
    1300,  1304,  1308,  1312,  1316,  1320,  1324,  1328,  1332,  1336,
    1340,  1344,  1348,  1352,  1356,  1360,  1364,  1368,  1376,  1380,
    1384,  1392,  1399,  1406,  1411,  1418,  1424,  1432,  1437,  1444,
    1450,  1458,  1466,  1473,  1479,  1487,  1495,  1503,  1511,  1519,
    1527,  1535,  1547,  1551,  1555,  1559,  1563,  1567,  1571,  1575,
    1579,  1583,  1587,  1591,  1599,  1608,  1614,  1624,  1632,  1640,
    1648,  1652,  1660,  1668,  1676,  1683,  1689,  1697,  1707,  1719,
    1733,  1740,  1749,  1761,  1768,  1777,  1781,  1785,  1789,  1793,
    1797,  1805,  1813,  1824,  1835,  1843,  1851,  1863,  1870,  1880,
    1884,  1892,  1899,  1912,  1919,  1933,  1937,  1945,  1949,  1958,
    1965,  1975,  1980,  1986,  2001,  2005,  2010,  2015,  2024,  2031,
    2043,  2047,  2056,  2063,  2073,  2080,  2090,  2099,  2105,  2113,
    2119,  2127,  2134,  2144,  2157,  2164,  2173,  2185,  2192,  2201,
    2207,  2211,  2218,  2238,  2244,  2253,  2260,  2267,  2274,  2281
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
#line 6687 "GrammarParser.cpp"

#line 2287 "../../obj/src/GrammarParser.y"


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
