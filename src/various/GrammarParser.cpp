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
        const auto name = CST::make< Identifier >( sourceLocation, TypeInfo::TYPE_NAME_VOID );
        const auto path = CST::make< IdentifierPath >( sourceLocation, name );
        const auto node = CST::make< BasicType >( sourceLocation, path );
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

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.YY_MOVE_OR_COPY< BehaviorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.YY_MOVE_OR_COPY< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.YY_MOVE_OR_COPY< BuiltinDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_BEHAVIOR: // "behavior"
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAINTYPE: // "domain"
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
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOTDOTDOT: // "..."
        value.YY_MOVE_OR_COPY< CST::Token::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_BehaviorDefinitionElement: // BehaviorDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
      case symbol_kind::S_ImplementDefinitionAttributedElement: // ImplementDefinitionAttributedElement
        value.YY_MOVE_OR_COPY< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_BehaviorDefinitionList: // BehaviorDefinitionList
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
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.YY_MOVE_OR_COPY< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.YY_MOVE_OR_COPY< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Terms: // Terms
        value.YY_MOVE_OR_COPY< Expressions::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_MappedExpression: // MappedExpression
        value.YY_MOVE_OR_COPY< MappedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MappedExpressions: // MappedExpressions
        value.YY_MOVE_OR_COPY< MappedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MappingType: // MappingType
        value.YY_MOVE_OR_COPY< MappingType::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_SymbolAttribute: // SymbolAttribute
        value.YY_MOVE_OR_COPY< SymbolAttribute::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_VaradicType: // VaradicType
        value.YY_MOVE_OR_COPY< VaradicType::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.YY_MOVE_OR_COPY< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.YY_MOVE_OR_COPY< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Type: // Type
        value.YY_MOVE_OR_COPY< libcasm_fe::CST::Type::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.move< BehaviorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.move< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.move< BuiltinDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_BEHAVIOR: // "behavior"
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAINTYPE: // "domain"
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
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOTDOTDOT: // "..."
        value.move< CST::Token::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_BehaviorDefinitionElement: // BehaviorDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
      case symbol_kind::S_ImplementDefinitionAttributedElement: // ImplementDefinitionAttributedElement
        value.move< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_BehaviorDefinitionList: // BehaviorDefinitionList
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
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.move< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Terms: // Terms
        value.move< Expressions::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_MappedExpression: // MappedExpression
        value.move< MappedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MappedExpressions: // MappedExpressions
        value.move< MappedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MappingType: // MappingType
        value.move< MappingType::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_SymbolAttribute: // SymbolAttribute
        value.move< SymbolAttribute::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_VaradicType: // VaradicType
        value.move< VaradicType::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.move< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.move< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Type: // Type
        value.move< libcasm_fe::CST::Type::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.copy< BehaviorDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.copy< BuiltinDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_BEHAVIOR: // "behavior"
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAINTYPE: // "domain"
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
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOTDOTDOT: // "..."
        value.copy< CST::Token::Ptr > (that.value);
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
      case symbol_kind::S_BehaviorDefinitionElement: // BehaviorDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
      case symbol_kind::S_ImplementDefinitionAttributedElement: // ImplementDefinitionAttributedElement
        value.copy< Definition::Ptr > (that.value);
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_BehaviorDefinitionList: // BehaviorDefinitionList
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
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.copy< Expression::Ptr > (that.value);
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case symbol_kind::S_Terms: // Terms
        value.copy< Expressions::Ptr > (that.value);
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

      case symbol_kind::S_MappedExpression: // MappedExpression
        value.copy< MappedExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_MappedExpressions: // MappedExpressions
        value.copy< MappedExpressions::Ptr > (that.value);
        break;

      case symbol_kind::S_MappingType: // MappingType
        value.copy< MappingType::Ptr > (that.value);
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

      case symbol_kind::S_SymbolAttribute: // SymbolAttribute
        value.copy< SymbolAttribute::Ptr > (that.value);
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

      case symbol_kind::S_VaradicType: // VaradicType
        value.copy< VaradicType::Ptr > (that.value);
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

      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.copy< WhileRule::Ptr > (that.value);
        break;

      case symbol_kind::S_Type: // Type
        value.copy< libcasm_fe::CST::Type::Ptr > (that.value);
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

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.move< BehaviorDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.move< BuiltinDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_BEHAVIOR: // "behavior"
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAINTYPE: // "domain"
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
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOTDOTDOT: // "..."
        value.move< CST::Token::Ptr > (that.value);
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
      case symbol_kind::S_BehaviorDefinitionElement: // BehaviorDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
      case symbol_kind::S_ImplementDefinitionAttributedElement: // ImplementDefinitionAttributedElement
        value.move< Definition::Ptr > (that.value);
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_BehaviorDefinitionList: // BehaviorDefinitionList
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
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.move< Expression::Ptr > (that.value);
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case symbol_kind::S_Terms: // Terms
        value.move< Expressions::Ptr > (that.value);
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

      case symbol_kind::S_MappedExpression: // MappedExpression
        value.move< MappedExpression::Ptr > (that.value);
        break;

      case symbol_kind::S_MappedExpressions: // MappedExpressions
        value.move< MappedExpressions::Ptr > (that.value);
        break;

      case symbol_kind::S_MappingType: // MappingType
        value.move< MappingType::Ptr > (that.value);
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

      case symbol_kind::S_SymbolAttribute: // SymbolAttribute
        value.move< SymbolAttribute::Ptr > (that.value);
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

      case symbol_kind::S_VaradicType: // VaradicType
        value.move< VaradicType::Ptr > (that.value);
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

      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case symbol_kind::S_Type: // Type
        value.move< libcasm_fe::CST::Type::Ptr > (that.value);
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

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        yylhs.value.emplace< BehaviorDefinition::Ptr > ();
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        yylhs.value.emplace< BlockRule::Ptr > ();
        break;

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        yylhs.value.emplace< BuiltinDefinition::Ptr > ();
        break;

      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_BEHAVIOR: // "behavior"
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAINTYPE: // "domain"
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
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOTDOTDOT: // "..."
        yylhs.value.emplace< CST::Token::Ptr > ();
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
      case symbol_kind::S_BehaviorDefinitionElement: // BehaviorDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
      case symbol_kind::S_ImplementDefinitionAttributedElement: // ImplementDefinitionAttributedElement
        yylhs.value.emplace< Definition::Ptr > ();
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_BehaviorDefinitionList: // BehaviorDefinitionList
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
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        yylhs.value.emplace< Expression::Ptr > ();
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        yylhs.value.emplace< ExpressionAttribute::Ptr > ();
        break;

      case symbol_kind::S_Terms: // Terms
        yylhs.value.emplace< Expressions::Ptr > ();
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

      case symbol_kind::S_MappedExpression: // MappedExpression
        yylhs.value.emplace< MappedExpression::Ptr > ();
        break;

      case symbol_kind::S_MappedExpressions: // MappedExpressions
        yylhs.value.emplace< MappedExpressions::Ptr > ();
        break;

      case symbol_kind::S_MappingType: // MappingType
        yylhs.value.emplace< MappingType::Ptr > ();
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

      case symbol_kind::S_SymbolAttribute: // SymbolAttribute
        yylhs.value.emplace< SymbolAttribute::Ptr > ();
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

      case symbol_kind::S_VaradicType: // VaradicType
        yylhs.value.emplace< VaradicType::Ptr > ();
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

      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        yylhs.value.emplace< VariableDefinitions::Ptr > ();
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        yylhs.value.emplace< WhileRule::Ptr > ();
        break;

      case symbol_kind::S_Type: // Type
        yylhs.value.emplace< libcasm_fe::CST::Type::Ptr > ();
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
#line 445 "../../obj/src/GrammarParser.y"
  {
      const auto& cst = CST::make< CST::Root >(
          yylhs.location, yystack_[1].value.as < HeaderDefinition::Ptr > (), yystack_[0].value.as < Definitions::Ptr > (), m_lexer.fetchSpansAndReset() );
      m_specification.setCst( cst );
  }
#line 2901 "GrammarParser.cpp"
    break;

  case 3: // Header: Attributes "CASM"
#line 455 "../../obj/src/GrammarParser.y"
  {
      auto definition = CST::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2911 "GrammarParser.cpp"
    break;

  case 4: // Header: "CASM"
#line 461 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = CST::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 2919 "GrammarParser.cpp"
    break;

  case 5: // Definitions: Definitions AttributedDefinition
#line 469 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2929 "GrammarParser.cpp"
    break;

  case 6: // Definitions: AttributedDefinition
#line 475 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2939 "GrammarParser.cpp"
    break;

  case 7: // AttributedDefinition: Attributes Definition
#line 485 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2949 "GrammarParser.cpp"
    break;

  case 8: // AttributedDefinition: Definition
#line 491 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2957 "GrammarParser.cpp"
    break;

  case 9: // AttributedDefinition: error
#line 495 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2965 "GrammarParser.cpp"
    break;

  case 10: // Definition: InitDefinition
#line 503 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2973 "GrammarParser.cpp"
    break;

  case 11: // Definition: EnumerationDefinition
#line 507 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2981 "GrammarParser.cpp"
    break;

  case 12: // Definition: DerivedDefinition
#line 511 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2989 "GrammarParser.cpp"
    break;

  case 13: // Definition: RuleDefinition
#line 515 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2997 "GrammarParser.cpp"
    break;

  case 14: // Definition: FunctionDefinition
#line 519 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 3005 "GrammarParser.cpp"
    break;

  case 15: // Definition: UsingDefinition
#line 523 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 3013 "GrammarParser.cpp"
    break;

  case 16: // Definition: UsingPathDefinition
#line 527 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 3021 "GrammarParser.cpp"
    break;

  case 17: // Definition: InvariantDefinition
#line 531 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 3029 "GrammarParser.cpp"
    break;

  case 18: // Definition: ImportDefinition
#line 535 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 3037 "GrammarParser.cpp"
    break;

  case 19: // Definition: StructureDefinition
#line 539 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < StructureDefinition::Ptr > ();
  }
#line 3045 "GrammarParser.cpp"
    break;

  case 20: // Definition: BehaviorDefinition
#line 543 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < BehaviorDefinition::Ptr > ();
  }
#line 3053 "GrammarParser.cpp"
    break;

  case 21: // Definition: ImplementDefinition
#line 547 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImplementDefinition::Ptr > ();
  }
#line 3061 "GrammarParser.cpp"
    break;

  case 22: // Definition: DomainDefinition
#line 551 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DomainDefinition::Ptr > ();
  }
#line 3069 "GrammarParser.cpp"
    break;

  case 23: // Definition: BuiltinDefinition
#line 555 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < BuiltinDefinition::Ptr > ();
  }
#line 3077 "GrammarParser.cpp"
    break;

  case 24: // InitDefinition: "init" IdentifierPath
#line 563 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = CST::make< InitDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3085 "GrammarParser.cpp"
    break;

  case 25: // InitDefinition: "init" "{" MappedExpressions "}"
#line 567 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = CST::make< InitDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < MappedExpressions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3093 "GrammarParser.cpp"
    break;

  case 26: // EnumerationDefinition: "enumeration" Identifier "=" "{" Enumerators "}"
#line 575 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = CST::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3101 "GrammarParser.cpp"
    break;

  case 27: // DerivedDefinition: "derived" Identifier "->" Type "=" Term
#line 583 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3110 "GrammarParser.cpp"
    break;

  case 28: // DerivedDefinition: "derived" Identifier "(" Parameters ")" "->" Type "=" Term
#line 588 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3120 "GrammarParser.cpp"
    break;

  case 29: // DerivedDefinition: "derived" Identifier "(" MethodParameters ")" "->" Type "=" Term
#line 594 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3130 "GrammarParser.cpp"
    break;

  case 30: // DerivedDefinition: "derived" Identifier "(" error ")" "->" Type "=" Term
#line 600 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 3138 "GrammarParser.cpp"
    break;

  case 31: // RuleDefinition: "rule" Identifier "=" Rule
#line 608 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3148 "GrammarParser.cpp"
    break;

  case 32: // RuleDefinition: "rule" Identifier "->" Type "=" Rule
#line 614 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3157 "GrammarParser.cpp"
    break;

  case 33: // RuleDefinition: "rule" Identifier "(" Parameters ")" "=" Rule
#line 619 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < CST::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
  }
#line 3168 "GrammarParser.cpp"
    break;

  case 34: // RuleDefinition: "rule" Identifier "(" Parameters ")" "->" Type "=" Rule
#line 626 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3178 "GrammarParser.cpp"
    break;

  case 35: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "=" Rule
#line 632 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < CST::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
  }
#line 3189 "GrammarParser.cpp"
    break;

  case 36: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "->" Type "=" Rule
#line 639 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3199 "GrammarParser.cpp"
    break;

  case 37: // RuleDefinition: "rule" Identifier "(" error ")" "=" Rule
#line 645 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3207 "GrammarParser.cpp"
    break;

  case 38: // RuleDefinition: "rule" Identifier "(" error ")" "->" Type "=" Rule
#line 649 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3215 "GrammarParser.cpp"
    break;

  case 39: // FunctionDefinition: "function" Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 657 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = CST::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < CST::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
  }
#line 3223 "GrammarParser.cpp"
    break;

  case 40: // EnumeratorDefinition: Identifier
#line 665 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = CST::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3231 "GrammarParser.cpp"
    break;

  case 41: // EnumeratorDefinition: Attributes Identifier
#line 669 "../../obj/src/GrammarParser.y"
  {
      auto enumerator = CST::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 3241 "GrammarParser.cpp"
    break;

  case 42: // EnumeratorDefinition: error
#line 675 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 3249 "GrammarParser.cpp"
    break;

  case 43: // Enumerators: Enumerators "," EnumeratorDefinition
#line 683 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3260 "GrammarParser.cpp"
    break;

  case 44: // Enumerators: EnumeratorDefinition
#line 690 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = CST::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3270 "GrammarParser.cpp"
    break;

  case 45: // UsingDefinition: "using" Identifier "=" Type
#line 700 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingDefinition::Ptr > () = CST::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3278 "GrammarParser.cpp"
    break;

  case 46: // UsingPathDefinition: "using" IdentifierPath
#line 708 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = CST::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3286 "GrammarParser.cpp"
    break;

  case 47: // UsingPathDefinition: "using" IdentifierPath "::" "*"
#line 712 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = CST::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3294 "GrammarParser.cpp"
    break;

  case 48: // InvariantDefinition: "invariant" Identifier "=" Term
#line 720 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = CST::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3302 "GrammarParser.cpp"
    break;

  case 49: // ImportDefinition: "import" IdentifierPath
#line 728 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = CST::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3310 "GrammarParser.cpp"
    break;

  case 50: // ImportDefinition: "import" IdentifierPath "as" Identifier
#line 732 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = CST::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3318 "GrammarParser.cpp"
    break;

  case 51: // StructureDefinition: "structure" Identifier "=" "{" StructureDefinitionList "}"
#line 744 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < StructureDefinition::Ptr > () = CST::make< StructureDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < FunctionDefinitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3326 "GrammarParser.cpp"
    break;

  case 52: // StructureDefinitionList: StructureDefinitionList StructureDefinitionElement
#line 751 "../../obj/src/GrammarParser.y"
  {
      auto functions = yystack_[1].value.as < FunctionDefinitions::Ptr > ();
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3336 "GrammarParser.cpp"
    break;

  case 53: // StructureDefinitionList: StructureDefinitionElement
#line 757 "../../obj/src/GrammarParser.y"
  {
      auto functions = CST::make< FunctionDefinitions >( yylhs.location );
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3346 "GrammarParser.cpp"
    break;

  case 54: // StructureDefinitionElement: Attributes FunctionDefinition
#line 766 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 3356 "GrammarParser.cpp"
    break;

  case 55: // StructureDefinitionElement: FunctionDefinition
#line 772 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 3364 "GrammarParser.cpp"
    break;

  case 56: // BehaviorDefinition: "behavior" Type "=" "{" BehaviorDefinitionList "}"
#line 784 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BehaviorDefinition::Ptr > () = CST::make< BehaviorDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3372 "GrammarParser.cpp"
    break;

  case 57: // BehaviorDefinitionElement: Attributes Declaration
#line 792 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Declaration::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3382 "GrammarParser.cpp"
    break;

  case 58: // BehaviorDefinitionElement: Declaration
#line 798 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Declaration::Ptr > ();
  }
#line 3390 "GrammarParser.cpp"
    break;

  case 59: // BehaviorDefinitionElement: Attributes DerivedDefinition
#line 802 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DerivedDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3400 "GrammarParser.cpp"
    break;

  case 60: // BehaviorDefinitionElement: DerivedDefinition
#line 808 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3408 "GrammarParser.cpp"
    break;

  case 61: // BehaviorDefinitionElement: Attributes RuleDefinition
#line 812 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < RuleDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3418 "GrammarParser.cpp"
    break;

  case 62: // BehaviorDefinitionElement: RuleDefinition
#line 818 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3426 "GrammarParser.cpp"
    break;

  case 63: // BehaviorDefinitionList: BehaviorDefinitionList BehaviorDefinitionElement
#line 825 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3436 "GrammarParser.cpp"
    break;

  case 64: // BehaviorDefinitionList: BehaviorDefinitionElement
#line 831 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3446 "GrammarParser.cpp"
    break;

  case 65: // ImplementDefinition: "implement" Type "=" "{" ImplementDefinitionList "}"
#line 845 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = CST::make< ImplementDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3454 "GrammarParser.cpp"
    break;

  case 66: // ImplementDefinition: "implement" Type "for" Type "=" "{" ImplementDefinitionList "}"
#line 849 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = CST::make< ImplementDefinition >( yylhs.location, yystack_[7].value.as < CST::Token::Ptr > (), yystack_[6].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3462 "GrammarParser.cpp"
    break;

  case 67: // ImplementDefinitionList: ImplementDefinitionList ImplementDefinitionElement
#line 856 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3472 "GrammarParser.cpp"
    break;

  case 68: // ImplementDefinitionList: ImplementDefinitionElement
#line 862 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3482 "GrammarParser.cpp"
    break;

  case 69: // ImplementDefinitionElement: Attributes ImplementDefinitionAttributedElement
#line 871 "../../obj/src/GrammarParser.y"
  {
      const auto& definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3492 "GrammarParser.cpp"
    break;

  case 70: // ImplementDefinitionElement: ImplementDefinitionAttributedElement
#line 877 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 3500 "GrammarParser.cpp"
    break;

  case 71: // ImplementDefinitionAttributedElement: DerivedDefinition
#line 884 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3508 "GrammarParser.cpp"
    break;

  case 72: // ImplementDefinitionAttributedElement: RuleDefinition
#line 888 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3516 "GrammarParser.cpp"
    break;

  case 73: // DomainDefinition: "domain" Type
#line 900 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DomainDefinition::Ptr > () = CST::make< DomainDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3524 "GrammarParser.cpp"
    break;

  case 74: // BuiltinDefinition: "builtin" RelationType
#line 912 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BuiltinDefinition::Ptr > () = CST::make< BuiltinDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < RelationType::Ptr > () );
  }
#line 3532 "GrammarParser.cpp"
    break;

  case 75: // Declaration: "derived" Identifier ":" MaybeFunctionParameters "->" Type
#line 924 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = CST::make< Declaration >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3540 "GrammarParser.cpp"
    break;

  case 76: // Declaration: "rule" Identifier ":" MaybeFunctionParameters "->" Type
#line 928 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = CST::make< Declaration >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3548 "GrammarParser.cpp"
    break;

  case 77: // Rules: Rules Rule
#line 940 "../../obj/src/GrammarParser.y"
  {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3558 "GrammarParser.cpp"
    break;

  case 78: // Rules: Rule
#line 946 "../../obj/src/GrammarParser.y"
  {
      auto rules = CST::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3568 "GrammarParser.cpp"
    break;

  case 79: // Rule: SkipRule
#line 956 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 3576 "GrammarParser.cpp"
    break;

  case 80: // Rule: ConditionalRule
#line 960 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 3584 "GrammarParser.cpp"
    break;

  case 81: // Rule: CaseRule
#line 964 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 3592 "GrammarParser.cpp"
    break;

  case 82: // Rule: LetRule
#line 968 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 3600 "GrammarParser.cpp"
    break;

  case 83: // Rule: LocalRule
#line 972 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LocalRule::Ptr > ();
  }
#line 3608 "GrammarParser.cpp"
    break;

  case 84: // Rule: ForallRule
#line 976 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 3616 "GrammarParser.cpp"
    break;

  case 85: // Rule: ChooseRule
#line 980 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 3624 "GrammarParser.cpp"
    break;

  case 86: // Rule: IterateRule
#line 984 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 3632 "GrammarParser.cpp"
    break;

  case 87: // Rule: BlockRule
#line 988 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 3640 "GrammarParser.cpp"
    break;

  case 88: // Rule: SequenceRule
#line 992 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 3648 "GrammarParser.cpp"
    break;

  case 89: // Rule: UpdateRule
#line 996 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 3656 "GrammarParser.cpp"
    break;

  case 90: // Rule: CallRule
#line 1000 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 3664 "GrammarParser.cpp"
    break;

  case 91: // Rule: WhileRule
#line 1004 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 3672 "GrammarParser.cpp"
    break;

  case 92: // SkipRule: "skip"
#line 1012 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SkipRule::Ptr > () = CST::make< SkipRule >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3680 "GrammarParser.cpp"
    break;

  case 93: // ConditionalRule: "if" Term "then" Rule
#line 1020 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = CST::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3688 "GrammarParser.cpp"
    break;

  case 94: // ConditionalRule: "if" Term "then" Rule "else" Rule
#line 1024 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = CST::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3696 "GrammarParser.cpp"
    break;

  case 95: // CaseRule: "case" Term "of" "{" CaseLabels "}"
#line 1032 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = CST::make< CaseRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3704 "GrammarParser.cpp"
    break;

  case 96: // CaseRule: "case" Term "of" "{" error "}"
#line 1036 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 3712 "GrammarParser.cpp"
    break;

  case 97: // CaseLabels: CaseLabels CaseLabel
#line 1044 "../../obj/src/GrammarParser.y"
  {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3722 "GrammarParser.cpp"
    break;

  case 98: // CaseLabels: CaseLabel
#line 1050 "../../obj/src/GrammarParser.y"
  {
      auto cases = CST::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3732 "GrammarParser.cpp"
    break;

  case 99: // CaseLabel: "default" ":" Rule
#line 1060 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< DefaultCase >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3740 "GrammarParser.cpp"
    break;

  case 100: // CaseLabel: "_" ":" Rule
#line 1064 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< DefaultCase >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3748 "GrammarParser.cpp"
    break;

  case 101: // CaseLabel: Term ":" Rule
#line 1068 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3756 "GrammarParser.cpp"
    break;

  case 102: // LetRule: "let" VariableBindings "in" Rule
#line 1076 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = CST::make< LetRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3764 "GrammarParser.cpp"
    break;

  case 103: // LocalRule: "local" LocalFunctionDefinitions "in" Rule
#line 1084 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LocalRule::Ptr > () = CST::make< LocalRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < FunctionDefinitions::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3772 "GrammarParser.cpp"
    break;

  case 104: // ForallRule: "forall" AttributedVariables "in" Term "do" Rule
#line 1092 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = CST::make< ForallRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3780 "GrammarParser.cpp"
    break;

  case 105: // ForallRule: "forall" AttributedVariables "in" Term "with" Term "do" Rule
#line 1096 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = CST::make< ForallRule >( yylhs.location, yystack_[7].value.as < CST::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3788 "GrammarParser.cpp"
    break;

  case 106: // ChooseRule: "choose" AttributedVariables "in" Term "do" Rule
#line 1104 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = CST::make< ChooseRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3796 "GrammarParser.cpp"
    break;

  case 107: // IterateRule: "iterate" Rule
#line 1112 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = CST::make< IterateRule >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3804 "GrammarParser.cpp"
    break;

  case 108: // BlockRule: "{" Rules "}"
#line 1120 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = CST::make< BlockRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3812 "GrammarParser.cpp"
    break;

  case 109: // BlockRule: "par" Rules "endpar"
#line 1124 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = CST::make< BlockRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3820 "GrammarParser.cpp"
    break;

  case 110: // BlockRule: "{" error "}"
#line 1128 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3829 "GrammarParser.cpp"
    break;

  case 111: // BlockRule: "par" error "endpar"
#line 1133 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3838 "GrammarParser.cpp"
    break;

  case 112: // SequenceRule: "{|" Rules "|}"
#line 1142 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = CST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3846 "GrammarParser.cpp"
    break;

  case 113: // SequenceRule: "seq" Rules "endseq"
#line 1146 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = CST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3854 "GrammarParser.cpp"
    break;

  case 114: // SequenceRule: "{|" error "|}"
#line 1150 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3863 "GrammarParser.cpp"
    break;

  case 115: // SequenceRule: "seq" error "endseq"
#line 1155 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3872 "GrammarParser.cpp"
    break;

  case 116: // UpdateRule: DirectCallExpression ":=" Term
#line 1164 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = CST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3880 "GrammarParser.cpp"
    break;

  case 117: // UpdateRule: MethodCallExpression ":=" Term
#line 1168 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = CST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < MethodCallExpression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3888 "GrammarParser.cpp"
    break;

  case 118: // CallRule: CallExpression
#line 1176 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = CST::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 3896 "GrammarParser.cpp"
    break;

  case 119: // WhileRule: "while" Term "do" Rule
#line 1184 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = CST::make< WhileRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3904 "GrammarParser.cpp"
    break;

  case 120: // Terms: Terms "," Term
#line 1196 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3915 "GrammarParser.cpp"
    break;

  case 121: // Terms: Term
#line 1203 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = CST::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3925 "GrammarParser.cpp"
    break;

  case 122: // Term: Expression
#line 1213 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3933 "GrammarParser.cpp"
    break;

  case 123: // Term: TypeCastingExpression
#line 1217 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 3941 "GrammarParser.cpp"
    break;

  case 124: // Term: OperatorExpression
#line 1221 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3949 "GrammarParser.cpp"
    break;

  case 125: // Term: LetExpression
#line 1225 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 3957 "GrammarParser.cpp"
    break;

  case 126: // Term: ConditionalExpression
#line 1229 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 3965 "GrammarParser.cpp"
    break;

  case 127: // Term: ChooseExpression
#line 1233 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 3973 "GrammarParser.cpp"
    break;

  case 128: // Term: UniversalQuantifierExpression
#line 1237 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 3981 "GrammarParser.cpp"
    break;

  case 129: // Term: ExistentialQuantifierExpression
#line 1241 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 3989 "GrammarParser.cpp"
    break;

  case 130: // Term: CardinalityExpression
#line 1245 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 3997 "GrammarParser.cpp"
    break;

  case 131: // Expression: "(" Term ")"
#line 1253 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< CST::EmbracedExpression >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4005 "GrammarParser.cpp"
    break;

  case 132: // Expression: "(" error ")"
#line 1257 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 4013 "GrammarParser.cpp"
    break;

  case 133: // Expression: CallExpression
#line 1261 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 4021 "GrammarParser.cpp"
    break;

  case 134: // Expression: LiteralCallExpression
#line 1265 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 4029 "GrammarParser.cpp"
    break;

  case 135: // Expression: Literal
#line 1269 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 4037 "GrammarParser.cpp"
    break;

  case 136: // Expression: "+" Expression
#line 1273 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4045 "GrammarParser.cpp"
    break;

  case 137: // Expression: "-" Expression
#line 1277 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4053 "GrammarParser.cpp"
    break;

  case 138: // OperatorExpression: Term "+" Term
#line 1289 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4061 "GrammarParser.cpp"
    break;

  case 139: // OperatorExpression: Term "-" Term
#line 1293 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4069 "GrammarParser.cpp"
    break;

  case 140: // OperatorExpression: Term "*" Term
#line 1297 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4077 "GrammarParser.cpp"
    break;

  case 141: // OperatorExpression: Term "/" Term
#line 1301 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4085 "GrammarParser.cpp"
    break;

  case 142: // OperatorExpression: Term "%" Term
#line 1305 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4093 "GrammarParser.cpp"
    break;

  case 143: // OperatorExpression: Term "^" Term
#line 1309 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4101 "GrammarParser.cpp"
    break;

  case 144: // OperatorExpression: Term "!=" Term
#line 1313 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4109 "GrammarParser.cpp"
    break;

  case 145: // OperatorExpression: Term "=" Term
#line 1317 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4117 "GrammarParser.cpp"
    break;

  case 146: // OperatorExpression: Term "<" Term
#line 1321 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4125 "GrammarParser.cpp"
    break;

  case 147: // OperatorExpression: Term ">" Term
#line 1325 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4133 "GrammarParser.cpp"
    break;

  case 148: // OperatorExpression: Term "<=" Term
#line 1329 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4141 "GrammarParser.cpp"
    break;

  case 149: // OperatorExpression: Term ">=" Term
#line 1333 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4149 "GrammarParser.cpp"
    break;

  case 150: // OperatorExpression: Term "or" Term
#line 1337 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4157 "GrammarParser.cpp"
    break;

  case 151: // OperatorExpression: Term "xor" Term
#line 1341 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4165 "GrammarParser.cpp"
    break;

  case 152: // OperatorExpression: Term "and" Term
#line 1345 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4173 "GrammarParser.cpp"
    break;

  case 153: // OperatorExpression: Term "=>" Term
#line 1349 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4181 "GrammarParser.cpp"
    break;

  case 154: // OperatorExpression: Term "implies" Term
#line 1353 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4189 "GrammarParser.cpp"
    break;

  case 155: // OperatorExpression: "not" Term
#line 1357 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4197 "GrammarParser.cpp"
    break;

  case 156: // CallExpression: DirectCallExpression
#line 1365 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 4205 "GrammarParser.cpp"
    break;

  case 157: // CallExpression: MethodCallExpression
#line 1369 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 4213 "GrammarParser.cpp"
    break;

  case 158: // CallExpression: IndirectCallExpression
#line 1373 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 4221 "GrammarParser.cpp"
    break;

  case 159: // DirectCallExpression: "this"
#line 1381 "../../obj/src/GrammarParser.y"
  {
      const auto identifier = CST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      identifier->setSpans( m_lexer.fetchSpansAndReset() );
      const auto identifierPath = IdentifierPath::fromIdentifier( identifier );
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, identifierPath );
  }
#line 4232 "GrammarParser.cpp"
    break;

  case 160: // DirectCallExpression: IdentifierPath
#line 1388 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4240 "GrammarParser.cpp"
    break;

  case 161: // DirectCallExpression: IdentifierPath "(" ")"
#line 1392 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), arguments, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4249 "GrammarParser.cpp"
    break;

  case 162: // DirectCallExpression: IdentifierPath "(" Terms ")"
#line 1397 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expressions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4257 "GrammarParser.cpp"
    break;

  case 163: // DirectCallExpression: IdentifierPath "(" error ")"
#line 1401 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 4265 "GrammarParser.cpp"
    break;

  case 164: // MethodCallExpression: Expression "." Identifier
#line 1409 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 4274 "GrammarParser.cpp"
    break;

  case 165: // MethodCallExpression: Expression "." Identifier "(" ")"
#line 1414 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4285 "GrammarParser.cpp"
    break;

  case 166: // MethodCallExpression: Expression "." Identifier "(" Terms ")"
#line 1421 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4295 "GrammarParser.cpp"
    break;

  case 167: // MethodCallExpression: Expression "." Identifier "(" error ")"
#line 1427 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 4303 "GrammarParser.cpp"
    break;

  case 168: // LiteralCallExpression: Expression "." IntegerLiteral
#line 1435 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = CST::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 4311 "GrammarParser.cpp"
    break;

  case 169: // IndirectCallExpression: CallExpression "(" ")"
#line 1443 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = CST::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4322 "GrammarParser.cpp"
    break;

  case 170: // IndirectCallExpression: CallExpression "(" Terms ")"
#line 1450 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = CST::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4332 "GrammarParser.cpp"
    break;

  case 171: // IndirectCallExpression: CallExpression "(" error ")"
#line 1456 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 4340 "GrammarParser.cpp"
    break;

  case 172: // TypeCastingExpression: Expression "as" Type
#line 1464 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = CST::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 4348 "GrammarParser.cpp"
    break;

  case 173: // LetExpression: "let" VariableBindings "in" Term
#line 1472 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = CST::make< LetExpression >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4356 "GrammarParser.cpp"
    break;

  case 174: // ConditionalExpression: "if" Term "then" Term "else" Term
#line 1480 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = CST::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4364 "GrammarParser.cpp"
    break;

  case 175: // ChooseExpression: "choose" AttributedVariables "in" Term "do" Term
#line 1488 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = CST::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4372 "GrammarParser.cpp"
    break;

  case 176: // UniversalQuantifierExpression: "forall" AttributedVariables "in" Term "holds" Term
#line 1496 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = CST::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4380 "GrammarParser.cpp"
    break;

  case 177: // ExistentialQuantifierExpression: "exists" AttributedVariables "in" Term "with" Term
#line 1504 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = CST::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4388 "GrammarParser.cpp"
    break;

  case 178: // CardinalityExpression: "|" Expression "|"
#line 1512 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = CST::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4396 "GrammarParser.cpp"
    break;

  case 179: // Literal: UndefinedLiteral
#line 1524 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 4404 "GrammarParser.cpp"
    break;

  case 180: // Literal: BooleanLiteral
#line 1528 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4412 "GrammarParser.cpp"
    break;

  case 181: // Literal: IntegerLiteral
#line 1532 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4420 "GrammarParser.cpp"
    break;

  case 182: // Literal: RationalLiteral
#line 1536 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4428 "GrammarParser.cpp"
    break;

  case 183: // Literal: DecimalLiteral
#line 1540 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4436 "GrammarParser.cpp"
    break;

  case 184: // Literal: BinaryLiteral
#line 1544 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4444 "GrammarParser.cpp"
    break;

  case 185: // Literal: StringLiteral
#line 1548 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4452 "GrammarParser.cpp"
    break;

  case 186: // Literal: ReferenceLiteral
#line 1552 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 4460 "GrammarParser.cpp"
    break;

  case 187: // Literal: ListLiteral
#line 1560 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 4468 "GrammarParser.cpp"
    break;

  case 188: // Literal: RangeLiteral
#line 1564 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 4476 "GrammarParser.cpp"
    break;

  case 189: // Literal: TupleLiteral
#line 1568 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 4484 "GrammarParser.cpp"
    break;

  case 190: // Literal: RecordLiteral
#line 1572 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 4492 "GrammarParser.cpp"
    break;

  case 191: // UndefinedLiteral: "undef"
#line 1580 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = CST::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4501 "GrammarParser.cpp"
    break;

  case 192: // BooleanLiteral: "true"
#line 1589 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = CST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4511 "GrammarParser.cpp"
    break;

  case 193: // BooleanLiteral: "false"
#line 1595 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = CST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4521 "GrammarParser.cpp"
    break;

  case 194: // IntegerLiteral: "integer"
#line 1605 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4529 "GrammarParser.cpp"
    break;

  case 195: // RationalLiteral: "rational"
#line 1613 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4537 "GrammarParser.cpp"
    break;

  case 196: // DecimalLiteral: "decimal"
#line 1621 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4545 "GrammarParser.cpp"
    break;

  case 197: // BinaryLiteral: "binary"
#line 1629 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4553 "GrammarParser.cpp"
    break;

  case 198: // BinaryLiteral: "hexadecimal"
#line 1633 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4561 "GrammarParser.cpp"
    break;

  case 199: // StringLiteral: "string"
#line 1641 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4569 "GrammarParser.cpp"
    break;

  case 200: // ReferenceLiteral: "@" IdentifierPath
#line 1649 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = CST::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4577 "GrammarParser.cpp"
    break;

  case 201: // ListLiteral: "[" "]"
#line 1678 "../../obj/src/GrammarParser.y"
  {
      const auto& expressions = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = CST::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4588 "GrammarParser.cpp"
    break;

  case 202: // ListLiteral: "[" Terms "]"
#line 1685 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = CST::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4598 "GrammarParser.cpp"
    break;

  case 203: // ListLiteral: "[" error "]"
#line 1691 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4606 "GrammarParser.cpp"
    break;

  case 204: // RangeLiteral: "[" Term ".." Term "]"
#line 1699 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = CST::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4616 "GrammarParser.cpp"
    break;

  case 205: // TupleLiteral: "(" Terms "," Term ")"
#line 1709 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = CST::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4629 "GrammarParser.cpp"
    break;

  case 206: // RecordLiteral: "{" Assignments "}"
#line 1722 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = CST::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4639 "GrammarParser.cpp"
    break;

  case 207: // Assignments: Assignments "," Assignment
#line 1736 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4650 "GrammarParser.cpp"
    break;

  case 208: // Assignments: Assignment
#line 1743 "../../obj/src/GrammarParser.y"
  {
      auto assignments = CST::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4660 "GrammarParser.cpp"
    break;

  case 209: // Assignment: Identifier ":" Term
#line 1752 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = CST::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4668 "GrammarParser.cpp"
    break;

  case 210: // MappedExpressions: MappedExpressions "," MappedExpression
#line 1759 "../../obj/src/GrammarParser.y"
  {
      const auto& mappedExpressions = yystack_[2].value.as < MappedExpressions::Ptr > ();
      yystack_[0].value.as < MappedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      mappedExpressions->add( yystack_[0].value.as < MappedExpression::Ptr > () );
      yylhs.value.as < MappedExpressions::Ptr > () = mappedExpressions;
  }
#line 4679 "GrammarParser.cpp"
    break;

  case 211: // MappedExpressions: MappedExpression
#line 1766 "../../obj/src/GrammarParser.y"
  {
      auto mappedExpressions = CST::make< MappedExpressions >( yylhs.location );
      mappedExpressions->add( yystack_[0].value.as < MappedExpression::Ptr > () );
      yylhs.value.as < MappedExpressions::Ptr > () = mappedExpressions;
  }
#line 4689 "GrammarParser.cpp"
    break;

  case 212: // MappedExpression: "->" Term
#line 1775 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4698 "GrammarParser.cpp"
    break;

  case 213: // MappedExpression: "(" Term ")" "->" Term
#line 1780 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = CST::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), arguments, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4708 "GrammarParser.cpp"
    break;

  case 214: // MappedExpression: TupleLiteral "->" Term
#line 1786 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto& leftBracket = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto& rightBracket = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4719 "GrammarParser.cpp"
    break;

  case 215: // Types: Types "," Type
#line 1802 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4730 "GrammarParser.cpp"
    break;

  case 216: // Types: Type
#line 1809 "../../obj/src/GrammarParser.y"
  {
      auto types = CST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4740 "GrammarParser.cpp"
    break;

  case 217: // Type: BasicType
#line 1818 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4748 "GrammarParser.cpp"
    break;

  case 218: // Type: TupleType
#line 1822 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4756 "GrammarParser.cpp"
    break;

  case 219: // Type: RecordType
#line 1826 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4764 "GrammarParser.cpp"
    break;

  case 220: // Type: TemplateType
#line 1830 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4772 "GrammarParser.cpp"
    break;

  case 221: // Type: RelationType
#line 1834 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4780 "GrammarParser.cpp"
    break;

  case 222: // Type: FixedSizedType
#line 1838 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4788 "GrammarParser.cpp"
    break;

  case 223: // Type: MappingType
#line 1842 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < MappingType::Ptr > ();
  }
#line 4796 "GrammarParser.cpp"
    break;

  case 224: // Type: VaradicType
#line 1846 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < VaradicType::Ptr > ();
  }
#line 4804 "GrammarParser.cpp"
    break;

  case 225: // BasicType: IdentifierPath
#line 1854 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = CST::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4812 "GrammarParser.cpp"
    break;

  case 226: // TupleType: "(" Types "," Type ")"
#line 1862 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = CST::make< TupleType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), subTypes, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4823 "GrammarParser.cpp"
    break;

  case 227: // RecordType: "{" TypedVariables "," TypedVariable "}"
#line 1873 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = CST::make< RecordType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4834 "GrammarParser.cpp"
    break;

  case 228: // TemplateType: IdentifierPath "<" Types ">"
#line 1884 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = CST::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4842 "GrammarParser.cpp"
    break;

  case 229: // RelationType: IdentifierPath "<" MaybeFunctionParameters "->" Type ">"
#line 1892 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = CST::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4850 "GrammarParser.cpp"
    break;

  case 230: // FixedSizedType: IdentifierPath "'" Term
#line 1900 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = CST::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4858 "GrammarParser.cpp"
    break;

  case 231: // MappingType: "<" FunctionParameters "->" Type ">"
#line 1908 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MappingType::Ptr > () = CST::make< MappingType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );      
  }
#line 4866 "GrammarParser.cpp"
    break;

  case 232: // VaradicType: Identifier "..."
#line 1916 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VaradicType::Ptr > () = CST::make< VaradicType >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4874 "GrammarParser.cpp"
    break;

  case 233: // FunctionParameters: FunctionParameters "*" Type
#line 1928 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4885 "GrammarParser.cpp"
    break;

  case 234: // FunctionParameters: Type
#line 1935 "../../obj/src/GrammarParser.y"
  {
      auto types = CST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4895 "GrammarParser.cpp"
    break;

  case 235: // MaybeFunctionParameters: FunctionParameters
#line 1945 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 4903 "GrammarParser.cpp"
    break;

  case 236: // MaybeFunctionParameters: %empty
#line 1949 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = CST::make< Types >( yylhs.location );
  }
#line 4911 "GrammarParser.cpp"
    break;

  case 237: // MethodParameters: MethodParameters "," TypedAttributedVariable
#line 1957 "../../obj/src/GrammarParser.y"
  {
      const auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4922 "GrammarParser.cpp"
    break;

  case 238: // MethodParameters: "this"
#line 1964 "../../obj/src/GrammarParser.y"
  {
      const auto parameters = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto identifier = CST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      identifier->setSpans( m_lexer.fetchSpansAndReset() );
      const auto unresolvedType = CST::make< UnresolvedType >( yylhs.location );
      const auto variable = CST::make< VariableDefinition >( yylhs.location, identifier, Token::unresolved(), unresolvedType );
      parameters->add( variable );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4936 "GrammarParser.cpp"
    break;

  case 239: // Parameters: Parameters "," TypedAttributedVariable
#line 1978 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4947 "GrammarParser.cpp"
    break;

  case 240: // Parameters: TypedAttributedVariable
#line 1985 "../../obj/src/GrammarParser.y"
  {
      auto parameters = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4957 "GrammarParser.cpp"
    break;

  case 241: // MaybeDefined: "defined" "{" Term "}"
#line 1999 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = CST::make< Defined >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4965 "GrammarParser.cpp"
    break;

  case 242: // MaybeDefined: %empty
#line 2003 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = CST::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), CST::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 4973 "GrammarParser.cpp"
    break;

  case 243: // MaybeInitially: "=" "{" Expression "}"
#line 2011 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: drop braces and replace this rule with ::= Expression
      const auto& embracedExpression = CST::make< EmbracedExpression >( yystack_[1].location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), embracedExpression );
  }
#line 4983 "GrammarParser.cpp"
    break;

  case 244: // MaybeInitially: "=" "{" MappedExpressions "}"
#line 2017 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: replace this rule with ::= EQUAL SetLiteral
      const auto& expressions = CST::make< Expressions >( yystack_[1].location );
      for( auto const& expression : *yystack_[1].value.as < MappedExpressions::Ptr > () )
      {
          expressions->add( expression );
      }
      const auto& setLiteral = CST::make< SetLiteral >( yystack_[1].location, expressions );
      setLiteral->setLeftBracket( yystack_[2].value.as < CST::Token::Ptr > () );
      setLiteral->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), setLiteral );
  }
#line 5000 "GrammarParser.cpp"
    break;

  case 245: // MaybeInitially: %empty
#line 2030 "../../obj/src/GrammarParser.y"
  {
      const auto& expression = CST::make< CST::AbstractExpression >( yylhs.location, Token::unresolved() );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, Token::unresolved(), expression );
  }
#line 5009 "GrammarParser.cpp"
    break;

  case 246: // Identifier: "identifier"
#line 2043 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 5017 "GrammarParser.cpp"
    break;

  case 247: // Identifier: "in"
#line 2047 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5026 "GrammarParser.cpp"
    break;

  case 248: // Identifier: "CASM"
#line 2052 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5035 "GrammarParser.cpp"
    break;

  case 249: // Identifier: "self"
#line 2057 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5044 "GrammarParser.cpp"
    break;

  case 250: // Identifier: "enumeration"
#line 2062 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5053 "GrammarParser.cpp"
    break;

  case 251: // Identifier: "structure"
#line 2067 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5062 "GrammarParser.cpp"
    break;

  case 252: // IdentifierPath: IdentifierPath "::" Identifier
#line 2076 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < CST::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 5073 "GrammarParser.cpp"
    break;

  case 253: // IdentifierPath: Identifier
#line 2083 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = CST::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5081 "GrammarParser.cpp"
    break;

  case 254: // Variable: TypedVariable
#line 2095 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5089 "GrammarParser.cpp"
    break;

  case 255: // Variable: Identifier
#line 2099 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = CST::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = CST::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 5098 "GrammarParser.cpp"
    break;

  case 256: // AttributedVariables: AttributedVariables "," AttributedVariable
#line 2108 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5109 "GrammarParser.cpp"
    break;

  case 257: // AttributedVariables: AttributedVariable
#line 2115 "../../obj/src/GrammarParser.y"
  {
      auto variables = CST::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5119 "GrammarParser.cpp"
    break;

  case 258: // TypedVariables: TypedVariables "," TypedVariable
#line 2125 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5130 "GrammarParser.cpp"
    break;

  case 259: // TypedVariables: TypedVariable
#line 2132 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = CST::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5140 "GrammarParser.cpp"
    break;

  case 260: // TypedVariable: Identifier ":" Type
#line 2142 "../../obj/src/GrammarParser.y"
  {
      auto variable = CST::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5149 "GrammarParser.cpp"
    break;

  case 261: // AttributedVariable: Attributes Variable
#line 2151 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5159 "GrammarParser.cpp"
    break;

  case 262: // AttributedVariable: Variable
#line 2157 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5167 "GrammarParser.cpp"
    break;

  case 263: // TypedAttributedVariable: Attributes TypedVariable
#line 2165 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5177 "GrammarParser.cpp"
    break;

  case 264: // TypedAttributedVariable: TypedVariable
#line 2171 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5185 "GrammarParser.cpp"
    break;

  case 265: // VariableBindings: VariableBindings "," VariableBinding
#line 2183 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5196 "GrammarParser.cpp"
    break;

  case 266: // VariableBindings: VariableBinding
#line 2190 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = CST::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5206 "GrammarParser.cpp"
    break;

  case 267: // VariableBinding: AttributedVariable "=" Term
#line 2199 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = CST::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5214 "GrammarParser.cpp"
    break;

  case 268: // LocalFunctionDefinitions: LocalFunctionDefinitions "," AttributedLocalFunctionDefinition
#line 2211 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5225 "GrammarParser.cpp"
    break;

  case 269: // LocalFunctionDefinitions: AttributedLocalFunctionDefinition
#line 2218 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5235 "GrammarParser.cpp"
    break;

  case 270: // AttributedLocalFunctionDefinition: Attributes LocalFunctionDefinition
#line 2227 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 5245 "GrammarParser.cpp"
    break;

  case 271: // AttributedLocalFunctionDefinition: LocalFunctionDefinition
#line 2233 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 5253 "GrammarParser.cpp"
    break;

  case 272: // AttributedLocalFunctionDefinition: error
#line 2237 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 5261 "GrammarParser.cpp"
    break;

  case 273: // LocalFunctionDefinition: Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 2244 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = CST::make< FunctionDefinition >( yylhs.location, Token::unresolved(), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > ()->setClassification( FunctionDefinition::Classification::LOCAL );
  }
#line 5270 "GrammarParser.cpp"
    break;

  case 274: // Attributes: Attributes Attribute
#line 2257 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5280 "GrammarParser.cpp"
    break;

  case 275: // Attributes: Attribute
#line 2263 "../../obj/src/GrammarParser.y"
  {
      auto attributes = CST::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5290 "GrammarParser.cpp"
    break;

  case 276: // Attribute: "[" BasicAttribute "]"
#line 2272 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5301 "GrammarParser.cpp"
    break;

  case 277: // Attribute: "[" SymbolAttribute "]"
#line 2279 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < SymbolAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5312 "GrammarParser.cpp"
    break;

  case 278: // Attribute: "[" ExpressionAttribute "]"
#line 2286 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5323 "GrammarParser.cpp"
    break;

  case 279: // Attribute: "[" error "]"
#line 2293 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 5331 "GrammarParser.cpp"
    break;

  case 280: // BasicAttribute: Identifier
#line 2300 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = CST::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5339 "GrammarParser.cpp"
    break;

  case 281: // SymbolAttribute: Identifier TypedVariable
#line 2307 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SymbolAttribute::Ptr > () = CST::make< SymbolAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < VariableDefinition::Ptr > () );
  }
#line 5347 "GrammarParser.cpp"
    break;

  case 282: // ExpressionAttribute: Identifier Term
#line 2314 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = CST::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5355 "GrammarParser.cpp"
    break;


#line 5359 "GrammarParser.cpp"

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


  const short Parser::yypact_ninf_ = -422;

  const short Parser::yytable_ninf_ = -235;

  const short
  Parser::yypact_[] =
  {
      11,  -422,   176,    36,   706,    21,  -422,   -19,  -422,  -422,
    -422,  -422,  -422,  -422,  2433,    71,   111,   137,  -422,  -422,
     178,   428,   428,   428,   428,   428,   428,   428,    85,    85,
      85,   428,   428,   683,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
     880,  -422,  -422,  -422,  -422,   375,   375,   375,  2433,   375,
    -422,  -422,  -422,  2433,  2543,  2543,  1856,  1592,   428,  2543,
     428,  -422,  -422,  -422,  -422,  -422,  -422,  3189,   -11,  -422,
      39,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,   147,   250,  -422,  -422,  -422,
    -422,   -40,  -422,    66,   160,   163,    96,   192,   231,   216,
      77,   243,    85,   428,    85,   252,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,   224,   204,    23,  -422,  -422,   -56,
     254,  -422,  -422,   147,  -422,  -422,   277,   -10,  -422,   375,
       1,  -422,    37,  2708,    48,  -422,  -422,  -422,   276,   274,
    2958,   283,  -422,   217,  2921,    67,  -422,   281,    61,    66,
    2433,  2433,  2433,  2433,  2433,  2433,  2433,  2433,  2433,  2433,
    2433,  2433,  2433,  2433,  2433,  2433,  2433,    85,   208,  1658,
      85,  1724,   428,  2433,  2433,   273,   105,  -422,    32,    85,
     291,  2301,    58,    85,    85,   396,  2433,   428,   292,   286,
    -422,   147,   289,  -422,  -422,   173,   298,  -422,    85,  2433,
      85,   300,    85,    85,  2433,  2433,   375,  -422,  2433,   375,
    2433,  2433,  2433,  -422,  2433,  -422,  -422,  -422,  2433,  2433,
    -422,   428,  2433,  -422,  2458,   995,   937,   527,   378,   378,
     267,   411,   411,   296,   296,   296,  -422,   527,   267,   411,
     411,  -422,  -422,   314,   315,  -422,    68,  3189,  -422,   316,
    -422,   107,  -422,  2991,  3189,  2433,  -422,   -40,   317,  -422,
     156,   169,  -422,  -422,   375,   323,    69,  1187,  1278,  -422,
     375,    84,   375,   375,  2301,  2433,  2433,  2433,  1369,  1460,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,   297,    56,   307,   308,   329,   182,
     212,   333,  -422,  -422,  3189,  -422,    91,    85,   428,    85,
      85,    35,   100,   205,   320,   322,  -422,   340,    44,   324,
    3189,  3189,  -422,  2855,  -422,  2569,  2785,  2888,  3024,  3189,
    3057,  -422,  3189,  1790,  -422,  -422,  -422,  -422,   327,  3189,
    -422,   338,   341,   375,   346,   375,  -422,  2433,  -422,  -422,
     256,  -422,   375,   388,  1945,  -422,   373,  2034,    70,  -422,
     353,    88,  -422,  -422,   375,    89,    90,  -422,  2747,  2821,
    2603,   363,  2123,   281,   352,  2212,  2433,  2433,   118,   120,
     124,  2301,  -422,    22,  -422,    91,   380,   381,  -422,   374,
     428,   428,  -422,  -422,  -422,    45,  -422,    35,    85,  -422,
      85,   386,  -422,  -422,   101,  -422,  -422,    44,    85,  2433,
    2433,  2433,  2433,  -422,  -422,   395,  -422,   220,  2433,    85,
      85,  -422,    85,  -422,  3189,  -422,    69,  -422,  -422,  -422,
    -422,  -422,  -422,  2301,    85,  2301,    84,  -422,  2433,  2433,
    2301,   394,  2301,  -422,  -422,  -422,  -422,  3189,  3189,  2301,
      85,  2301,    85,  2301,    85,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,   152,   226,  -422,  -422,  -422,  -422,  -422,  -422,
     387,    44,  -422,  -422,  -422,   439,  3189,  3189,  3189,  3189,
    -422,  -422,  3189,   413,   417,   419,  -422,  -422,   400,  -422,
    -422,  1080,  2636,   442,  1526,  -422,  -422,   424,  -422,   425,
    -422,   430,    85,    85,  -422,   102,   427,   434,  2433,  2433,
    2433,    85,  2301,  2433,  2301,  2301,   429,   431,   432,  2367,
    -422,  3090,  2301,  2301,  2301,   416,   421,  -422,  2433,   438,
    -422,  3189,  3189,  3189,   439,  -422,  2669,  -422,  -422,  -422,
    2301,  2301,  -422,  -422,  2301,  -422,  -422,  -422,    85,    85,
    3123,  2488,   434,  2301,  -422,  -422,  -422,  -422,  -422,  -422,
    1856,   -50,   273,   264,  -422,  -422,  3156,  -422,  -422,   327
  };

  const short
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   275,     0,   248,   250,
     251,   249,   247,   246,   280,     0,     0,     0,     1,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     8,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       0,     3,   274,   279,   159,     0,     0,     0,     0,     0,
     191,   193,   192,     0,     0,     0,     0,     0,     0,     0,
       0,   197,   198,   194,   195,   196,   199,   282,   122,   124,
     133,   156,   157,   134,   158,   123,   125,   126,   127,   128,
     129,   130,   135,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   253,   160,   281,   276,   277,
     278,     0,   253,    24,     0,     0,     0,   253,    46,     0,
      49,     0,     0,     0,     0,     0,   217,   218,   219,   220,
     221,   222,   223,   224,   253,   225,     0,    73,    74,     0,
       0,     5,     7,   255,   262,   254,     0,     0,   266,     0,
       0,   257,     0,     0,     0,   155,   136,   137,     0,     0,
     121,     0,   201,     0,   121,     0,   208,     0,     0,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   211,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     216,     0,     0,   259,   234,     0,     0,   232,   236,     0,
       0,     0,   236,   236,     0,     0,     0,   261,     0,     0,
       0,     0,     0,   132,     0,   131,   203,   202,     0,     0,
     206,     0,     0,   178,   152,   150,   151,   154,   138,   139,
     145,   146,   147,   140,   141,   142,   143,   153,   144,   148,
     149,   172,   168,   164,     0,   169,     0,   121,   260,     0,
     161,     0,   252,   121,   212,     0,    25,     0,     0,   238,
       0,     0,   264,   240,     0,     0,     0,     0,     0,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,     0,   118,   156,   157,     0,     0,
       0,     0,    45,    47,    48,    50,     0,     0,     0,     0,
       0,     0,     0,   216,   235,     0,   230,     0,     0,     0,
     267,   173,   265,     0,   256,     0,     0,     0,   120,   120,
       0,   207,   209,     0,   171,   170,   163,   162,     0,   214,
     210,     0,     0,     0,     0,     0,   263,     0,    42,    44,
       0,    40,     0,     0,     0,    78,     0,     0,     0,   272,
       0,     0,   269,   271,     0,     0,     0,   107,     0,     0,
       0,     0,     0,   253,     0,     0,     0,     0,     0,     0,
       0,     0,    55,     0,    53,     0,   215,   258,   233,     0,
       0,     0,    60,    62,    64,     0,    58,     0,     0,   228,
       0,     0,    71,    72,     0,    68,    70,     0,     0,     0,
       0,     0,     0,   205,   204,     0,   165,     0,     0,     0,
       0,   237,     0,   239,    27,    26,     0,    41,   115,   113,
      77,   111,   109,     0,   236,     0,     0,   270,     0,     0,
       0,     0,     0,   110,   108,   114,   112,   116,   117,     0,
       0,     0,     0,     0,     0,    32,    51,    52,    54,   226,
     227,   231,     0,     0,    56,    63,    59,    61,    57,   215,
       0,     0,    65,    67,    69,   242,   176,   175,   174,   177,
     167,   166,   213,     0,     0,     0,    43,   102,     0,   103,
     268,     0,     0,    93,     0,   119,    37,     0,    35,     0,
      33,     0,   236,   236,   229,     0,     0,   245,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      98,     0,     0,     0,     0,     0,     0,    66,     0,     0,
      39,    30,    29,    28,   242,   104,     0,   106,    94,    96,
       0,     0,    95,    97,     0,    38,    36,    34,     0,     0,
       0,     0,   245,     0,    99,   100,   101,    75,    76,   241,
       0,     0,   189,     0,   273,   105,   121,   243,   244,   131
  };

  const short
  Parser::yypgoto_[] =
  {
    -422,  -422,  -422,  -422,   458,   448,  -422,  -422,    12,    13,
    -322,    53,  -422,  -422,  -422,  -422,  -422,  -422,  -422,    97,
    -422,    86,  -422,  -422,    14,  -421,    75,  -422,  -422,    87,
     -89,   581,  -422,  -422,  -422,  -422,   -36,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,   -59,    79,   284,
    -422,   410,   526,   636,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,   318,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -110,  -422,  -422,   266,   -58,   235,
     304,   201,  -422,  -422,  -422,  -422,   483,  -422,  -422,  -422,
     391,  -221,   325,   330,   -38,   -54,    -2,   336,   376,   -52,
    -422,    30,   -46,  -120,   234,   310,  -422,    92,   149,   131,
       8,  -422,  -422,  -422
  };

  const short
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    33,    34,    35,    36,    37,   422,   423,
      40,   369,   370,    41,    42,    43,    44,    45,   403,   404,
      46,   414,   415,    47,   424,   425,   426,    48,    49,   416,
     374,   375,   301,   302,   303,   539,   540,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   159,   267,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   165,   166,   196,   197,
     209,   214,   126,   127,   128,   129,   130,   131,   132,   133,
     334,   335,   280,   281,   527,   550,   112,   106,   144,   150,
     212,   145,   151,   283,   147,   148,   381,   382,   383,   149,
       6,    15,    16,    17
  };

  const short
  Parser::yytable_[] =
  {
      14,   195,   339,   493,   402,   152,   192,   154,   163,   146,
     587,   222,   105,    52,     1,   193,    38,    39,   225,   114,
     115,   116,   117,   119,    51,   121,   134,   134,   134,   228,
     140,   187,   188,   278,   194,     8,    18,   220,     9,    53,
     410,    32,   411,    10,   107,    38,    39,    11,   279,    21,
     410,    23,   411,   143,   143,   143,   226,   143,    52,   318,
      12,     8,    38,    39,     9,   230,   167,   229,     2,    10,
     368,   188,     8,    11,   279,     9,   232,   221,     2,     2,
      10,   402,   476,   478,    11,   379,    12,     8,     8,     2,
       9,     9,     2,    77,   189,    10,    10,    12,   453,    11,
      11,     2,     2,   229,   493,   484,    21,    21,    23,    23,
      32,   189,    12,    12,   229,     2,   455,   458,   459,   207,
     134,   211,   134,    13,   355,   243,     2,   240,   192,   108,
     266,     5,   271,   241,   238,    50,   226,   153,  -133,   192,
     122,     2,   155,   188,   123,   160,   164,   143,     2,    13,
     201,   202,   124,   213,   456,   229,   229,    52,     2,     2,
      13,   492,   547,   357,    50,   276,   418,   195,   419,   109,
     203,   277,   469,   238,   471,    13,    13,     7,   473,     8,
     146,     8,     9,   344,     9,   134,   263,    10,   134,    10,
     272,    11,   470,    11,   472,   110,   211,   134,   474,   377,
     211,   134,   134,   272,    12,   325,    12,   198,   190,   392,
     395,     8,   362,   522,     9,   198,   134,   200,   134,    10,
     134,   134,   363,    11,   143,   364,   199,   143,   282,   125,
     136,   137,   282,   508,   199,   365,    12,   111,   399,   167,
     385,   386,   329,   441,   146,   443,   204,   330,   363,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   192,    13,   400,    13,
     206,   218,   273,   274,  -234,   237,   501,   219,   365,  -234,
     201,   202,   211,   238,   371,   324,   238,   523,   143,   380,
     143,   143,    52,   205,   437,    73,   393,   208,   336,    13,
     203,   545,   546,   340,   341,   191,   216,   343,   217,   345,
     346,   347,   192,   348,   366,   223,   445,   349,   350,   174,
     175,   352,   446,   210,   588,   134,   211,   134,   134,   284,
     277,   224,   233,   284,   177,   178,   179,   180,   181,   182,
     234,   236,   242,   412,   413,   185,   186,   275,   156,   157,
     286,   326,   327,   168,   359,   328,   113,   331,   407,   338,
     118,   211,   120,   211,   135,   135,   135,   139,   182,   353,
     447,   354,   356,   361,   388,   389,   390,   367,     8,   188,
      52,     9,   380,   396,   397,   398,    10,   401,   261,   329,
      11,   268,    52,   282,   421,   282,   420,   451,   428,     8,
     285,   438,     9,    12,   321,   322,   169,    10,   482,   483,
     448,    11,   439,    52,   454,   440,   134,   372,   134,   333,
     442,   337,   384,   463,    12,    52,   134,   412,   413,   486,
     487,     8,     2,   465,     9,    52,   479,   134,   134,    10,
     134,   480,   481,    11,   371,   491,   444,   179,   180,   181,
     182,   500,   134,   514,   380,   524,    12,   405,   135,   526,
     135,   582,   417,   174,   175,   323,    13,   528,   134,   427,
     134,   529,   134,   530,   531,   467,   468,   535,   542,   543,
     179,   180,   181,   182,   544,   314,   548,    13,   549,   559,
     568,   141,   560,   561,   284,   569,   284,   571,   142,   506,
     477,   485,   494,   563,   488,   525,   262,   351,   496,   497,
     498,   499,   360,   583,   138,   215,   572,   502,   584,    13,
     134,   134,   332,   135,   378,   227,   135,   319,   406,   134,
     408,   409,   320,   457,   405,   135,   342,   511,   512,   135,
     135,     0,     0,     0,     0,     0,   417,     0,   510,     0,
       0,     0,     0,     0,   135,   427,   135,     0,   135,   135,
       0,     0,     0,     0,     0,     0,   134,   134,     0,     0,
       0,   314,   314,     0,   170,   171,   172,   372,   314,   174,
     175,   176,   314,   314,     0,     0,     0,   384,     0,     0,
       0,     0,     0,   541,   177,   178,   179,   180,   181,   182,
       0,     0,     0,     0,   184,   185,   186,   551,   552,   553,
       0,   315,   556,     0,     0,     0,     0,     0,   541,   489,
       0,   490,   427,     0,     0,     0,     0,   570,     0,   495,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     503,   504,     0,   505,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   427,     0,   314,   586,
       0,   314,     0,   135,     0,   135,   135,     0,     0,     0,
       0,   517,     0,   519,     0,   521,   314,     0,     0,   314,
       0,     0,     0,    -2,    19,   314,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,   315,   315,     0,
      30,    31,    32,     0,   315,     0,     0,    19,   315,   315,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
       0,     0,     0,    30,    31,    32,     0,   316,     0,     0,
       0,     0,   554,     0,     0,     0,     0,   314,     0,   314,
       2,     0,     0,     0,   314,     0,   314,     0,     0,     0,
       0,     0,     0,   314,   135,   314,   135,   314,     0,     0,
       0,     0,     0,     2,   135,     0,     0,     0,     0,   577,
     578,     0,     0,     0,     0,   135,   135,     0,   135,     0,
       0,     0,   300,     0,   315,     0,     0,   315,     0,     0,
     135,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   315,     0,     0,   315,   135,     0,   135,     0,
     135,   315,     0,   316,   316,     0,   314,     0,   314,   314,
     316,     0,     0,     0,   316,   316,   314,   314,   314,     0,
       0,     0,     0,     0,     0,     0,     0,   317,     0,     0,
       0,     0,     0,     0,   314,   314,     0,     0,   314,     0,
       0,     0,     0,     0,     0,   581,     0,   314,   135,   135,
       0,     0,     0,   315,     0,   315,     0,   135,     0,     0,
     315,     0,   315,     0,     0,   387,     0,     0,     0,   315,
       0,   315,     0,   315,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     0,     0,     0,    30,    31,    32,
     316,     0,     0,   316,   135,   135,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   316,     0,
       0,   316,     0,   317,   317,     0,     0,   316,     0,     0,
     317,     0,     0,     0,   317,   317,     0,     2,     0,     0,
       0,     0,   315,     0,   315,   315,     0,     0,     0,     0,
       0,     0,   315,   315,   315,   450,     0,     0,   450,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     315,   315,     0,   450,   315,     0,   450,     0,     0,   316,
       0,   316,   475,   315,   170,     0,   316,     0,   316,   174,
     175,   176,     0,     0,     0,   316,     0,   316,     0,   316,
       0,     0,     0,     0,   177,   178,   179,   180,   181,   182,
     317,     0,     0,   317,   184,   185,   186,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   317,     0,
       0,   317,     0,     0,   507,     0,   509,   317,     0,     0,
       0,   513,   170,   515,   172,     0,     0,   174,   175,   176,
     516,     0,   518,     0,   520,     0,     0,     0,   316,     0,
     316,   316,   177,   178,   179,   180,   181,   182,   316,   316,
     316,     0,   184,   185,   186,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   316,   316,     0,   317,
     316,   317,     0,     0,     0,     0,   317,     0,   317,   316,
       0,     0,     0,     0,     0,   317,     0,   317,     0,   317,
       0,     0,   532,   555,     0,   557,   558,     0,     0,     0,
       0,   533,     0,   565,   566,   567,     0,   170,   171,   172,
     173,     0,   174,   175,   176,     0,     0,     0,     0,     0,
       0,   574,   575,     0,     0,   576,     0,   177,   178,   179,
     180,   181,   182,     0,   585,   183,     0,   184,   185,   186,
       0,     0,     0,     0,     0,     0,     0,     0,   317,     0,
     317,   317,     0,     0,     0,     0,     0,     0,   317,   317,
     317,     0,     0,     0,     0,     0,     0,     0,   373,     0,
       8,     0,     0,     9,     0,     0,   317,   317,    10,     0,
     317,     0,    11,    54,     0,     0,     0,     0,   287,   317,
     288,     0,   289,   290,   291,    12,   292,   293,   294,     0,
     295,     0,     0,   296,     0,     0,     0,     0,     0,     0,
     297,    60,    61,    62,     0,     0,     0,     0,     0,    64,
      65,     0,    66,     0,    67,     0,   298,     0,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   299,     0,     0,
       0,     0,    71,    72,    73,    74,    75,    76,    13,   376,
       0,     8,     0,     0,     9,     0,     0,     0,     0,    10,
       0,     0,     0,    11,    54,     0,     0,     0,     0,   287,
       0,   288,     0,   289,   290,   291,    12,   292,   293,   294,
       0,   295,     0,     0,   296,     0,     0,     0,     0,     0,
       0,   297,    60,    61,    62,     0,     0,     0,     0,     0,
      64,    65,     0,    66,     0,    67,     0,   298,     0,     0,
       0,     0,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   299,     0,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    13,
     391,     0,     8,     0,     0,     9,     0,     0,     0,     0,
      10,     0,     0,     0,    11,    54,     0,     0,     0,     0,
     287,     0,   288,     0,   289,   290,   291,    12,   292,   293,
     294,     0,   295,     0,     0,   296,     0,     0,     0,     0,
       0,     0,   297,    60,    61,    62,     0,     0,     0,     0,
       0,    64,    65,     0,    66,     0,    67,     0,   298,     0,
       0,     0,     0,     0,    70,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   299,
       0,     0,     0,     0,    71,    72,    73,    74,    75,    76,
      13,   394,     0,     8,     0,     0,     9,     0,     0,     0,
       0,    10,     0,     0,     0,    11,    54,     0,     0,     0,
       0,   287,     0,   288,     0,   289,   290,   291,    12,   292,
     293,   294,     0,   295,     0,     0,   296,     0,     0,     0,
       0,     0,     0,   297,    60,    61,    62,     0,     0,     0,
       0,     0,    64,    65,     0,    66,     0,    67,     0,   298,
       0,     0,     0,     0,     0,    70,     0,   536,     0,     8,
       0,     0,     9,     0,     0,     0,     0,    10,     0,     0,
     299,    11,    54,     0,     0,    71,    72,    73,    74,    75,
      76,    13,    55,     0,    12,    56,    57,     0,     0,    58,
       0,     0,     0,     0,   537,     0,    59,     0,     0,     0,
      60,    61,    62,     0,     0,     0,     0,    63,    64,    65,
       0,    66,     0,    67,     0,    68,     0,     0,     0,   538,
      69,    70,     0,   161,     0,     8,     0,     0,     9,     0,
       0,     0,     0,    10,     0,     0,     0,    11,    54,     0,
       0,    71,    72,    73,    74,    75,    76,    13,    55,     0,
      12,    56,    57,     0,     0,    58,     0,     0,     0,     0,
       0,     0,    59,     0,     0,     0,    60,    61,    62,     0,
       0,     0,     0,    63,    64,    65,     0,    66,     0,    67,
     162,    68,     0,     0,     0,     0,    69,    70,     0,   264,
       0,     8,     0,     0,     9,     0,     0,     0,     0,    10,
       0,     0,     0,    11,    54,     0,     0,    71,    72,    73,
      74,    75,    76,    13,    55,     0,    12,    56,    57,     0,
       0,    58,     0,     0,     0,     0,     0,     0,    59,     0,
       0,     0,    60,    61,    62,     0,     0,     0,     0,    63,
      64,    65,     0,    66,   265,    67,     0,    68,     0,     0,
       0,     0,    69,    70,     0,   269,     0,     8,     0,     0,
       9,     0,     0,     0,     0,    10,     0,     0,     0,    11,
      54,     0,     0,    71,    72,    73,    74,    75,    76,    13,
      55,     0,    12,    56,    57,     0,     0,    58,     0,     0,
       0,     0,     0,     0,    59,     0,     0,     0,    60,    61,
      62,     0,     0,     0,     0,    63,    64,    65,     0,    66,
     270,    67,     0,    68,     0,     0,     0,     0,    69,    70,
       0,   435,     0,     8,     0,     0,     9,     0,     0,     0,
       0,    10,     0,     0,     0,    11,    54,     0,     0,    71,
      72,    73,    74,    75,    76,    13,    55,     0,    12,    56,
      57,     0,     0,    58,     0,     0,     0,     0,     0,     0,
      59,     0,     0,     0,    60,    61,    62,     0,     0,     0,
       0,    63,    64,    65,     0,    66,   436,    67,     0,    68,
       0,     0,     0,     0,    69,    70,     0,   158,     0,     8,
       0,     0,     9,     0,     0,     0,     0,    10,     0,     0,
       0,    11,    54,     0,     0,    71,    72,    73,    74,    75,
      76,    13,    55,     0,    12,    56,    57,     0,     0,    58,
       0,     0,     0,     0,     0,     0,    59,     0,     0,     0,
      60,    61,    62,     0,     0,     0,     0,    63,    64,    65,
       0,    66,     0,    67,     0,    68,     0,     0,     0,     0,
      69,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,    72,    73,    74,    75,    76,    13,     8,     0,
       0,     9,     0,     0,     0,     0,    10,     0,     0,     0,
      11,    54,     0,     0,     0,     0,   287,   449,   288,     0,
     289,   290,   291,    12,   292,   293,   294,     0,   295,     0,
       0,   296,     0,     0,     0,     0,     0,     0,   297,    60,
      61,    62,     0,     0,     0,     0,     0,    64,    65,     0,
      66,     0,    67,     0,   298,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   299,     0,     0,     0,     0,
      71,    72,    73,    74,    75,    76,    13,     8,     0,     0,
       9,     0,     0,     0,     0,    10,     0,     0,     0,    11,
      54,     0,     0,     0,     0,   287,     0,   288,   452,   289,
     290,   291,    12,   292,   293,   294,     0,   295,     0,     0,
     296,     0,     0,     0,     0,     0,     0,   297,    60,    61,
      62,     0,     0,     0,     0,     0,    64,    65,     0,    66,
       0,    67,     0,   298,     0,     0,     0,     0,     0,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   299,     0,     0,     0,     0,    71,
      72,    73,    74,    75,    76,    13,     8,     0,     0,     9,
       0,     0,     0,     0,    10,     0,     0,     0,    11,    54,
       0,     0,     0,     0,   287,     0,   288,     0,   289,   290,
     291,    12,   292,   293,   294,     0,   295,     0,     0,   296,
       0,     0,     0,     0,     0,     0,   297,    60,    61,    62,
       0,     0,     0,     0,     0,    64,    65,     0,    66,     0,
      67,     0,   298,   464,     0,     0,     0,     0,    70,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   299,     0,     0,     0,     0,    71,    72,
      73,    74,    75,    76,    13,     8,     0,     0,     9,     0,
       0,     0,     0,    10,     0,     0,     0,    11,    54,     0,
       0,     0,     0,   287,     0,   288,     0,   289,   290,   291,
      12,   292,   293,   294,     0,   295,     0,     0,   296,     0,
       0,     0,     0,     0,     0,   297,    60,    61,    62,     0,
       0,     0,     0,     0,    64,    65,     0,    66,     0,    67,
       0,   298,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   299,   466,     0,     0,     0,    71,    72,    73,
      74,    75,    76,    13,     8,     0,     0,     9,     0,     0,
       0,     0,    10,     0,     0,     0,    11,    54,     0,     0,
       0,     0,   287,     0,   288,     0,   289,   290,   291,    12,
     292,   293,   294,     0,   295,     0,     0,   296,     0,     0,
       0,     0,     0,     0,   297,    60,    61,    62,     0,     0,
       0,     0,     0,    64,    65,     0,    66,     0,    67,     0,
     298,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       8,     0,     0,     9,     0,     0,     0,     0,    10,     0,
       0,   299,    11,    54,     0,     0,    71,    72,    73,    74,
      75,    76,    13,    55,     0,    12,    56,    57,     0,     0,
      58,     0,     0,     0,     0,   537,     0,    59,     0,     0,
       0,    60,    61,    62,     0,     0,     0,     0,    63,    64,
      65,     0,    66,     0,    67,     0,    68,   562,     0,     0,
     538,    69,    70,     0,     0,     0,     8,     0,     0,     9,
       0,     0,     0,     0,    10,     0,     0,     0,    11,    54,
       0,     0,    71,    72,    73,    74,    75,    76,    13,    55,
       0,    12,    56,    57,     0,     0,    58,     0,     0,     0,
       0,     0,     0,    59,     0,     0,     0,    60,    61,    62,
       0,     0,     0,     0,    63,    64,    65,     0,    66,     0,
      67,     8,    68,     0,     9,     0,     0,    69,    70,    10,
       0,     0,     0,    11,    54,     0,     0,     0,     0,     0,
     174,   175,   176,     0,     0,     0,    12,     0,    71,    72,
      73,    74,    75,    76,    13,   177,   178,   179,   180,   181,
     182,     0,    60,    61,    62,   184,   185,   186,     0,     0,
      64,    65,     0,   580,     0,    67,     8,    68,     0,     9,
       0,     0,     0,    70,    10,     0,     0,     0,    11,    54,
       0,     0,   194,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     0,    71,    72,    73,    74,    75,    76,    13,
       0,     0,     0,     0,     0,     0,     0,    60,    61,    62,
       0,     0,     0,     0,     0,    64,    65,     0,    66,     0,
      67,   430,    68,     0,     0,     0,     0,     0,    70,     0,
       0,     0,     0,     0,     0,     0,   170,   171,   172,   173,
       0,   174,   175,   176,     0,     0,     0,     0,    71,    72,
      73,    74,    75,    76,    13,   462,   177,   178,   179,   180,
     181,   182,     0,     0,   183,     0,   184,   185,   186,     0,
     170,   171,   172,   173,     0,   174,   175,   176,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   534,     0,
     177,   178,   179,   180,   181,   182,     0,     0,   183,     0,
     184,   185,   186,   170,   171,   172,   173,     0,   174,   175,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   573,     0,   177,   178,   179,   180,   181,   182,     0,
       0,   183,     0,   184,   185,   186,   170,   171,   172,   173,
       0,   174,   175,   176,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   177,   178,   179,   180,
     181,   182,   231,     0,   183,     0,   184,   185,   186,     0,
       0,     0,     0,     0,     0,   170,   171,   172,   173,     0,
     174,   175,   176,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   177,   178,   179,   180,   181,
     182,   460,     0,   183,     0,   184,   185,   186,     0,     0,
       0,     0,     0,     0,   170,   171,   172,   173,     0,   174,
     175,   176,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   177,   178,   179,   180,   181,   182,
     431,     0,   183,     0,   184,   185,   186,     0,     0,     0,
       0,     0,   170,   171,   172,   173,     0,   174,   175,   176,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   177,   178,   179,   180,   181,   182,   461,     0,
     183,     0,   184,   185,   186,     0,     0,     0,   170,   171,
     172,   173,     0,   174,   175,   176,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   177,   178,
     179,   180,   181,   182,   429,     0,   183,     0,   184,   185,
     186,     0,   170,   171,   172,   173,     0,   174,   175,   176,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   177,   178,   179,   180,   181,   182,     0,   432,
     183,     0,   184,   185,   186,   170,   171,   172,   173,     0,
     174,   175,   176,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   177,   178,   179,   180,   181,
     182,     0,     0,   183,     0,   184,   185,   186,   170,   171,
     172,   173,     0,   174,   175,   176,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   177,   178,
     179,   180,   181,   182,     0,     0,   183,     0,   184,   185,
     186,     0,     0,     0,   239,   170,   171,   172,   173,     0,
     174,   175,   176,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   177,   178,   179,   180,   181,
     182,     0,     0,   183,     0,   184,   185,   186,   170,   171,
     172,   173,     0,   174,   175,   176,     0,   358,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   177,   178,
     179,   180,   181,   182,     0,     0,   183,     0,   184,   185,
     186,   170,   171,   172,   173,     0,   174,   175,   176,     0,
     433,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   177,   178,   179,   180,   181,   182,     0,     0,   183,
       0,   184,   185,   186,   170,   171,   172,   173,     0,   174,
     175,   176,     0,     0,     0,   434,     0,     0,     0,     0,
       0,     0,     0,     0,   177,   178,   179,   180,   181,   182,
       0,     0,   183,     0,   184,   185,   186,   170,   171,   172,
     173,     0,   174,   175,   176,     0,     0,     0,     0,     0,
       0,   564,     0,     0,     0,     0,     0,   177,   178,   179,
     180,   181,   182,     0,     0,   183,     0,   184,   185,   186,
     170,   171,   172,   173,     0,   174,   175,   176,     0,     0,
       0,     0,     0,   579,     0,     0,     0,     0,     0,     0,
     177,   178,   179,   180,   181,   182,     0,     0,   183,     0,
     184,   185,   186,   170,   171,   172,   173,     0,   174,   175,
     176,     0,   589,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   177,   178,   179,   180,   181,   182,     0,
       0,   183,     0,   184,   185,   186,   170,   171,   172,   173,
       0,   174,   175,   176,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   177,   178,   179,   180,
     181,   182,     0,     0,   183,     0,   184,   185,   186
  };

  const short
  Parser::yycheck_[] =
  {
       2,   111,   223,   424,   326,    57,    62,    59,    67,    55,
      60,    67,    14,     5,     3,    55,     4,     4,    28,    21,
      22,    23,    24,    25,     3,    27,    28,    29,    30,    28,
      32,    42,    82,     1,    74,     3,     0,    14,     6,    58,
       5,    19,     7,    11,    14,    33,    33,    15,    16,     5,
       5,     7,     7,    55,    56,    57,    66,    59,    50,     1,
      28,     3,    50,    50,     6,    28,    68,    66,    57,    11,
       1,    82,     3,    15,    16,     6,    28,    54,    57,    57,
      11,   403,    60,   405,    15,     1,    28,     3,     3,    57,
       6,     6,    57,    14,    55,    11,    11,    28,    28,    15,
      15,    57,    57,    66,   525,    60,     5,     5,     7,     7,
      19,    55,    28,    28,    66,    57,    28,    28,    28,    42,
     122,   123,   124,    91,    56,    64,    57,    60,    62,    58,
     189,     0,   191,    66,    66,     4,    66,    58,    82,    62,
      55,    57,    63,    82,    59,    66,    67,   149,    57,    91,
      54,    55,    67,   123,    66,    66,    66,   149,    57,    57,
      91,    60,    60,    56,    33,    60,    66,   277,    68,    58,
      74,    66,    54,    66,    54,    91,    91,     1,    54,     3,
     226,     3,     6,   229,     6,   187,   188,    11,   190,    11,
     192,    15,    74,    15,    74,    58,   198,   199,    74,   288,
     202,   203,   204,   205,    28,   207,    28,    55,    61,   298,
     299,     3,    56,    61,     6,    55,   218,    54,   220,    11,
     222,   223,    66,    15,   226,    56,    74,   229,   198,    28,
      29,    30,   202,   454,    74,    66,    28,    59,    56,   241,
     292,   293,    69,   363,   290,   365,    54,    74,    66,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,    62,    91,    56,    91,
      54,    67,   193,   194,    69,    58,    56,    73,    66,    74,
      54,    55,   284,    66,   286,   206,    66,    61,   290,   291,
     292,   293,   284,    62,   353,    87,   298,    54,   219,    91,
      74,   522,   523,   224,   225,    55,    54,   228,    84,   230,
     231,   232,    62,   234,   284,    61,    60,   238,   239,    52,
      53,   242,    66,   122,    60,   327,   328,   329,   330,   198,
      66,    54,    56,   202,    67,    68,    69,    70,    71,    72,
      66,    58,    61,   331,   331,    78,    79,    74,    64,    65,
      59,    59,    66,    69,   275,    66,    20,    59,   328,    59,
      24,   363,    26,   365,    28,    29,    30,    31,    72,    55,
     372,    56,    56,    56,   295,   296,   297,    54,     3,    82,
     372,     6,   384,    76,    76,    56,    11,    54,   187,    69,
      15,   190,   384,   363,    54,   365,    74,    24,    74,     3,
     199,    74,     6,    28,   203,   204,    70,    11,   410,   411,
      22,    15,    74,   405,    61,    74,   418,   286,   420,   218,
      74,   220,   291,    60,    28,   417,   428,   415,   415,   417,
     417,     3,    57,    81,     6,   427,    56,   439,   440,    11,
     442,    60,    68,    15,   446,    59,   367,    69,    70,    71,
      72,    56,   454,    59,   456,    68,    28,   326,   122,    20,
     124,   571,   331,    52,    53,    69,    91,    54,   470,   338,
     472,    54,   474,    54,    74,   396,   397,    35,    54,    54,
      69,    70,    71,    72,    54,   201,    59,    91,    54,    60,
      74,    33,    61,    61,   363,    74,   365,    59,    50,   446,
     403,   415,   427,   539,   417,   491,   188,   241,   429,   430,
     431,   432,   277,   571,    31,   124,   554,   438,   572,    91,
     522,   523,   218,   187,   290,   149,   190,   202,   327,   531,
     329,   330,   202,   384,   403,   199,   226,   458,   459,   203,
     204,    -1,    -1,    -1,    -1,    -1,   415,    -1,   456,    -1,
      -1,    -1,    -1,    -1,   218,   424,   220,    -1,   222,   223,
      -1,    -1,    -1,    -1,    -1,    -1,   568,   569,    -1,    -1,
      -1,   287,   288,    -1,    47,    48,    49,   446,   294,    52,
      53,    54,   298,   299,    -1,    -1,    -1,   456,    -1,    -1,
      -1,    -1,    -1,   514,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    77,    78,    79,   528,   529,   530,
      -1,   201,   533,    -1,    -1,    -1,    -1,    -1,   539,   418,
      -1,   420,   491,    -1,    -1,    -1,    -1,   548,    -1,   428,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     439,   440,    -1,   442,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   525,    -1,   374,   580,
      -1,   377,    -1,   327,    -1,   329,   330,    -1,    -1,    -1,
      -1,   470,    -1,   472,    -1,   474,   392,    -1,    -1,   395,
      -1,    -1,    -1,     0,     1,   401,    -1,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   287,   288,    -1,
      17,    18,    19,    -1,   294,    -1,    -1,     1,   298,   299,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    18,    19,    -1,   201,    -1,    -1,
      -1,    -1,   531,    -1,    -1,    -1,    -1,   453,    -1,   455,
      57,    -1,    -1,    -1,   460,    -1,   462,    -1,    -1,    -1,
      -1,    -1,    -1,   469,   418,   471,   420,   473,    -1,    -1,
      -1,    -1,    -1,    57,   428,    -1,    -1,    -1,    -1,   568,
     569,    -1,    -1,    -1,    -1,   439,   440,    -1,   442,    -1,
      -1,    -1,   201,    -1,   374,    -1,    -1,   377,    -1,    -1,
     454,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   392,    -1,    -1,   395,   470,    -1,   472,    -1,
     474,   401,    -1,   287,   288,    -1,   532,    -1,   534,   535,
     294,    -1,    -1,    -1,   298,   299,   542,   543,   544,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   201,    -1,    -1,
      -1,    -1,    -1,    -1,   560,   561,    -1,    -1,   564,    -1,
      -1,    -1,    -1,    -1,    -1,   571,    -1,   573,   522,   523,
      -1,    -1,    -1,   453,    -1,   455,    -1,   531,    -1,    -1,
     460,    -1,   462,    -1,    -1,   294,    -1,    -1,    -1,   469,
      -1,   471,    -1,   473,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    17,    18,    19,
     374,    -1,    -1,   377,   568,   569,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   392,    -1,
      -1,   395,    -1,   287,   288,    -1,    -1,   401,    -1,    -1,
     294,    -1,    -1,    -1,   298,   299,    -1,    57,    -1,    -1,
      -1,    -1,   532,    -1,   534,   535,    -1,    -1,    -1,    -1,
      -1,    -1,   542,   543,   544,   374,    -1,    -1,   377,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     560,   561,    -1,   392,   564,    -1,   395,    -1,    -1,   453,
      -1,   455,   401,   573,    47,    -1,   460,    -1,   462,    52,
      53,    54,    -1,    -1,    -1,   469,    -1,   471,    -1,   473,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
     374,    -1,    -1,   377,    77,    78,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   392,    -1,
      -1,   395,    -1,    -1,   453,    -1,   455,   401,    -1,    -1,
      -1,   460,    47,   462,    49,    -1,    -1,    52,    53,    54,
     469,    -1,   471,    -1,   473,    -1,    -1,    -1,   532,    -1,
     534,   535,    67,    68,    69,    70,    71,    72,   542,   543,
     544,    -1,    77,    78,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   560,   561,    -1,   453,
     564,   455,    -1,    -1,    -1,    -1,   460,    -1,   462,   573,
      -1,    -1,    -1,    -1,    -1,   469,    -1,   471,    -1,   473,
      -1,    -1,    32,   532,    -1,   534,   535,    -1,    -1,    -1,
      -1,    41,    -1,   542,   543,   544,    -1,    47,    48,    49,
      50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,   560,   561,    -1,    -1,   564,    -1,    67,    68,    69,
      70,    71,    72,    -1,   573,    75,    -1,    77,    78,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   532,    -1,
     534,   535,    -1,    -1,    -1,    -1,    -1,    -1,   542,   543,
     544,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       3,    -1,    -1,     6,    -1,    -1,   560,   561,    11,    -1,
     564,    -1,    15,    16,    -1,    -1,    -1,    -1,    21,   573,
      23,    -1,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,
      53,    -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    89,    90,    91,     1,
      -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    21,
      -1,    23,    -1,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      52,    53,    -1,    55,    -1,    57,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    85,    86,    87,    88,    89,    90,    91,
       1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,
      21,    -1,    23,    -1,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    52,    53,    -1,    55,    -1,    57,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,    90,
      91,     1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    -1,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    52,    53,    -1,    55,    -1,    57,    -1,    59,
      -1,    -1,    -1,    -1,    -1,    65,    -1,     1,    -1,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,
      80,    15,    16,    -1,    -1,    85,    86,    87,    88,    89,
      90,    91,    26,    -1,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    38,    -1,    40,    -1,    -1,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,    63,
      64,    65,    -1,     1,    -1,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      -1,    85,    86,    87,    88,    89,    90,    91,    26,    -1,
      28,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    53,    -1,    55,    -1,    57,
      58,    59,    -1,    -1,    -1,    -1,    64,    65,    -1,     1,
      -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    15,    16,    -1,    -1,    85,    86,    87,
      88,    89,    90,    91,    26,    -1,    28,    29,    30,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    55,    56,    57,    -1,    59,    -1,    -1,
      -1,    -1,    64,    65,    -1,     1,    -1,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,
      16,    -1,    -1,    85,    86,    87,    88,    89,    90,    91,
      26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    55,
      56,    57,    -1,    59,    -1,    -1,    -1,    -1,    64,    65,
      -1,     1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    85,
      86,    87,    88,    89,    90,    91,    26,    -1,    28,    29,
      30,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    51,    52,    53,    -1,    55,    56,    57,    -1,    59,
      -1,    -1,    -1,    -1,    64,    65,    -1,     1,    -1,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    15,    16,    -1,    -1,    85,    86,    87,    88,    89,
      90,    91,    26,    -1,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    87,    88,    89,    90,    91,     3,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      15,    16,    -1,    -1,    -1,    -1,    21,    22,    23,    -1,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,
      55,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,
      85,    86,    87,    88,    89,    90,    91,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,
      16,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    55,
      -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    85,
      86,    87,    88,    89,    90,    91,     3,    -1,    -1,     6,
      -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,
      -1,    -1,    -1,    -1,    21,    -1,    23,    -1,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    55,    -1,
      57,    -1,    59,    60,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    85,    86,
      87,    88,    89,    90,    91,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    52,    53,    -1,    55,    -1,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    81,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    91,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,
      -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    52,    53,    -1,    55,    -1,    57,    -1,
      59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
       3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,
      -1,    80,    15,    16,    -1,    -1,    85,    86,    87,    88,
      89,    90,    91,    26,    -1,    28,    29,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    38,    -1,    40,    -1,    -1,
      -1,    44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,
      53,    -1,    55,    -1,    57,    -1,    59,    60,    -1,    -1,
      63,    64,    65,    -1,    -1,    -1,     3,    -1,    -1,     6,
      -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,
      -1,    -1,    85,    86,    87,    88,    89,    90,    91,    26,
      -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    44,    45,    46,
      -1,    -1,    -1,    -1,    51,    52,    53,    -1,    55,    -1,
      57,     3,    59,    -1,     6,    -1,    -1,    64,    65,    11,
      -1,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,    -1,    28,    -1,    85,    86,
      87,    88,    89,    90,    91,    67,    68,    69,    70,    71,
      72,    -1,    44,    45,    46,    77,    78,    79,    -1,    -1,
      52,    53,    -1,    55,    -1,    57,     3,    59,    -1,     6,
      -1,    -1,    -1,    65,    11,    -1,    -1,    -1,    15,    16,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    85,    86,    87,    88,    89,    90,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    55,    -1,
      57,    32,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    85,    86,
      87,    88,    89,    90,    91,    32,    67,    68,    69,    70,
      71,    72,    -1,    -1,    75,    -1,    77,    78,    79,    -1,
      47,    48,    49,    50,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      67,    68,    69,    70,    71,    72,    -1,    -1,    75,    -1,
      77,    78,    79,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,    75,    -1,    77,    78,    79,    47,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    34,    -1,    75,    -1,    77,    78,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    34,    -1,    75,    -1,    77,    78,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      35,    -1,    75,    -1,    77,    78,    79,    -1,    -1,    -1,
      -1,    -1,    47,    48,    49,    50,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    37,    -1,
      75,    -1,    77,    78,    79,    -1,    -1,    -1,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    39,    -1,    75,    -1,    77,    78,
      79,    -1,    47,    48,    49,    50,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    -1,    41,
      75,    -1,    77,    78,    79,    47,    48,    49,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    -1,    -1,    75,    -1,    77,    78,    79,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,    75,    -1,    77,    78,
      79,    -1,    -1,    -1,    83,    47,    48,    49,    50,    -1,
      52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    -1,    -1,    75,    -1,    77,    78,    79,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,    75,    -1,    77,    78,
      79,    47,    48,    49,    50,    -1,    52,    53,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,    -1,    -1,    75,
      -1,    77,    78,    79,    47,    48,    49,    50,    -1,    52,
      53,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      -1,    -1,    75,    -1,    77,    78,    79,    47,    48,    49,
      50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    -1,    -1,    75,    -1,    77,    78,    79,
      47,    48,    49,    50,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    -1,    -1,    75,    -1,
      77,    78,    79,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,    75,    -1,    77,    78,    79,    47,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    -1,    -1,    75,    -1,    77,    78,    79
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    57,    98,    99,   206,   207,     1,     3,     6,
      11,    15,    28,    91,   193,   208,   209,   210,     0,     1,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      17,    18,    19,   100,   101,   102,   103,   104,   105,   106,
     107,   110,   111,   112,   113,   114,   117,   120,   124,   125,
     206,     3,   207,    58,    16,    26,    29,    30,    33,    40,
      44,    45,    46,    51,    52,    53,    55,    57,    59,    64,
      65,    85,    86,    87,    88,    89,    90,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   193,   194,   198,    58,    58,
      58,    59,   193,   194,   193,   193,   193,   193,   194,   193,
     194,   193,    55,    59,    67,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   193,   194,   178,   178,   183,   194,
     193,   101,   102,   193,   195,   198,   199,   201,   202,   206,
     196,   199,   196,   145,   196,   145,   146,   146,     1,   144,
     145,     1,    58,   144,   145,   173,   174,   193,   146,   194,
      47,    48,    49,    50,    52,    53,    54,    67,    68,    69,
      70,    71,    72,    75,    77,    78,    79,    42,    82,    55,
      61,    55,    62,    55,    74,   171,   175,   176,    55,    74,
      54,    54,    55,    74,    54,    62,    54,    42,    54,   177,
     178,   193,   197,   198,   178,   187,    54,    84,    67,    73,
      14,    54,    67,    61,    54,    28,    66,   195,    28,    66,
      28,    34,    28,    56,    66,    56,    58,    58,    66,    83,
      60,    66,    61,    64,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   178,   163,   193,     1,    56,   144,   145,   178,     1,
      56,   144,   193,   145,   145,    74,    60,    66,     1,    16,
     189,   190,   198,   200,   206,   178,    59,    21,    23,    25,
      26,    27,    29,    30,    31,    33,    36,    43,    59,    80,
     128,   129,   130,   131,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   146,   148,   149,   150,     1,   189,
     190,   178,   178,    69,   145,   193,    59,    66,    66,    69,
      74,    59,   177,   178,   187,   188,   145,   178,    59,   188,
     145,   145,   202,   145,   199,   145,   145,   145,   145,   145,
     145,   174,   145,    55,    56,    56,    56,    56,    56,   145,
     176,    56,    56,    66,    56,    66,   198,    54,     1,   108,
     109,   193,   206,     1,   127,   128,     1,   127,   201,     1,
     193,   203,   204,   205,   206,   196,   196,   128,   145,   145,
     145,     1,   127,   193,     1,   127,    76,    76,    56,    56,
      56,    54,   107,   115,   116,   206,   178,   198,   178,   178,
       5,     7,   105,   106,   118,   119,   126,   206,    66,    68,
      74,    54,   105,   106,   121,   122,   123,   206,    74,    39,
      32,    35,    41,    56,    58,     1,    56,   144,    74,    74,
      74,   200,    74,   200,   145,    60,    66,   193,    22,    22,
     128,    24,    24,    28,    61,    28,    66,   205,    28,    28,
      34,    37,    32,    60,    60,    81,    81,   145,   145,    54,
      74,    54,    74,    54,    74,   128,    60,   116,   107,    56,
      60,    68,   193,   193,    60,   118,   105,   106,   126,   178,
     178,    59,    60,   122,   123,   178,   145,   145,   145,   145,
      56,    56,   145,   178,   178,   178,   108,   128,   188,   128,
     204,   145,   145,   128,    59,   128,   128,   178,   128,   178,
     128,   178,    61,    61,    68,   121,    20,   191,    54,    54,
      54,    74,    32,    41,    32,    35,     1,    38,    63,   132,
     133,   145,    54,    54,    54,   188,   188,    60,    59,    54,
     192,   145,   145,   145,   178,   128,   145,   128,   128,    60,
      61,    61,    60,   133,    61,   128,   128,   128,    74,    74,
     145,    59,   191,    32,   128,   128,   128,   178,   178,    60,
      55,   146,   171,   175,   192,   128,   145,    60,    60,    56
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    97,    98,    99,    99,   100,   100,   101,   101,   101,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   103,   103,   104,   105,   105,   105,
     105,   106,   106,   106,   106,   106,   106,   106,   106,   107,
     108,   108,   108,   109,   109,   110,   111,   111,   112,   113,
     113,   114,   115,   115,   116,   116,   117,   118,   118,   118,
     118,   118,   118,   119,   119,   120,   120,   121,   121,   122,
     122,   123,   123,   124,   125,   126,   126,   127,   127,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   129,   130,   130,   131,   131,   132,   132,   133,
     133,   133,   134,   135,   136,   136,   137,   138,   139,   139,
     139,   139,   140,   140,   140,   140,   141,   141,   142,   143,
     144,   144,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   146,   146,   146,   146,   146,   146,   146,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   148,   148,   148,   149,
     149,   149,   149,   149,   150,   150,   150,   150,   151,   152,
     152,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   161,   162,   162,   163,   164,   165,   166,   166,   167,
     168,   169,   169,   169,   170,   171,   172,   173,   173,   174,
     175,   175,   176,   176,   176,   177,   177,   178,   178,   178,
     178,   178,   178,   178,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   187,   188,   188,   189,   189,   190,
     190,   191,   191,   192,   192,   192,   193,   193,   193,   193,
     193,   193,   194,   194,   195,   195,   196,   196,   197,   197,
     198,   199,   199,   200,   200,   201,   201,   202,   203,   203,
     204,   204,   204,   205,   206,   206,   207,   207,   207,   207,
     208,   209,   210
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
       1,     2,     1,     2,     1,     6,     8,     2,     1,     2,
       1,     1,     1,     2,     2,     6,     6,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     6,     6,     6,     2,     1,     3,
       3,     3,     4,     4,     6,     8,     6,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     4,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     1,     1,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     3,     4,     4,     3,     5,     6,     6,     3,     3,
       4,     4,     3,     4,     6,     6,     6,     6,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     3,     5,     5,     3,     3,     1,     3,
       3,     1,     2,     5,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     5,     4,     6,
       3,     5,     2,     3,     1,     1,     0,     3,     1,     3,
       1,     4,     0,     4,     4,     0,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     3,     1,
       3,     2,     1,     2,     1,     3,     1,     3,     3,     1,
       2,     1,     1,     7,     2,     1,     3,     3,     3,     3,
       1,     2,     2
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"using\"",
  "\"invariant\"", "\"import\"", "\"structure\"", "\"behavior\"",
  "\"implement\"", "\"for\"", "\"self\"", "\"this\"", "\"domain\"",
  "\"builtin\"", "\"function\"", "\"defined\"", "\"seq\"", "\"endseq\"",
  "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"", "\"local\"", "\"in\"",
  "\"forall\"", "\"choose\"", "\"iterate\"", "\"do\"", "\"if\"",
  "\"then\"", "\"else\"", "\"case\"", "\"of\"", "\"default\"", "\"holds\"",
  "\"exists\"", "\"with\"", "\"as\"", "\"while\"", "\"undef\"",
  "\"false\"", "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"implies\"",
  "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\":\"", "\"::\"", "\"_\"", "\"|\"", "\"@\"", "\",\"",
  "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"'\"", "\"->\"",
  "\"=>\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"",
  "\".\"", "\"..\"", "\"...\"", "\"binary\"", "\"hexadecimal\"",
  "\"integer\"", "\"rational\"", "\"decimal\"", "\"string\"",
  "\"identifier\"", "BASIC_TYPE", "CALL", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header", "Definitions",
  "AttributedDefinition", "Definition", "InitDefinition",
  "EnumerationDefinition", "DerivedDefinition", "RuleDefinition",
  "FunctionDefinition", "EnumeratorDefinition", "Enumerators",
  "UsingDefinition", "UsingPathDefinition", "InvariantDefinition",
  "ImportDefinition", "StructureDefinition", "StructureDefinitionList",
  "StructureDefinitionElement", "BehaviorDefinition",
  "BehaviorDefinitionElement", "BehaviorDefinitionList",
  "ImplementDefinition", "ImplementDefinitionList",
  "ImplementDefinitionElement", "ImplementDefinitionAttributedElement",
  "DomainDefinition", "BuiltinDefinition", "Declaration", "Rules", "Rule",
  "SkipRule", "ConditionalRule", "CaseRule", "CaseLabels", "CaseLabel",
  "LetRule", "LocalRule", "ForallRule", "ChooseRule", "IterateRule",
  "BlockRule", "SequenceRule", "UpdateRule", "CallRule", "WhileRule",
  "Terms", "Term", "Expression", "OperatorExpression", "CallExpression",
  "DirectCallExpression", "MethodCallExpression", "LiteralCallExpression",
  "IndirectCallExpression", "TypeCastingExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "CardinalityExpression", "Literal", "UndefinedLiteral", "BooleanLiteral",
  "IntegerLiteral", "RationalLiteral", "DecimalLiteral", "BinaryLiteral",
  "StringLiteral", "ReferenceLiteral", "ListLiteral", "RangeLiteral",
  "TupleLiteral", "RecordLiteral", "Assignments", "Assignment",
  "MappedExpressions", "MappedExpression", "Types", "Type", "BasicType",
  "TupleType", "RecordType", "TemplateType", "RelationType",
  "FixedSizedType", "MappingType", "VaradicType", "FunctionParameters",
  "MaybeFunctionParameters", "MethodParameters", "Parameters",
  "MaybeDefined", "MaybeInitially", "Identifier", "IdentifierPath",
  "Variable", "AttributedVariables", "TypedVariables", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "VariableBindings",
  "VariableBinding", "LocalFunctionDefinitions",
  "AttributedLocalFunctionDefinition", "LocalFunctionDefinition",
  "Attributes", "Attribute", "BasicAttribute", "SymbolAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   444,   444,   454,   460,   468,   474,   484,   490,   494,
     502,   506,   510,   514,   518,   522,   526,   530,   534,   538,
     542,   546,   550,   554,   562,   566,   574,   582,   587,   593,
     599,   607,   613,   618,   625,   631,   638,   644,   648,   656,
     664,   668,   674,   682,   689,   699,   707,   711,   719,   727,
     731,   743,   750,   756,   765,   771,   783,   791,   797,   801,
     807,   811,   817,   824,   830,   844,   848,   855,   861,   870,
     876,   883,   887,   899,   911,   923,   927,   939,   945,   955,
     959,   963,   967,   971,   975,   979,   983,   987,   991,   995,
     999,  1003,  1011,  1019,  1023,  1031,  1035,  1043,  1049,  1059,
    1063,  1067,  1075,  1083,  1091,  1095,  1103,  1111,  1119,  1123,
    1127,  1132,  1141,  1145,  1149,  1154,  1163,  1167,  1175,  1183,
    1195,  1202,  1212,  1216,  1220,  1224,  1228,  1232,  1236,  1240,
    1244,  1252,  1256,  1260,  1264,  1268,  1272,  1276,  1288,  1292,
    1296,  1300,  1304,  1308,  1312,  1316,  1320,  1324,  1328,  1332,
    1336,  1340,  1344,  1348,  1352,  1356,  1364,  1368,  1372,  1380,
    1387,  1391,  1396,  1400,  1408,  1413,  1420,  1426,  1434,  1442,
    1449,  1455,  1463,  1471,  1479,  1487,  1495,  1503,  1511,  1523,
    1527,  1531,  1535,  1539,  1543,  1547,  1551,  1559,  1563,  1567,
    1571,  1579,  1588,  1594,  1604,  1612,  1620,  1628,  1632,  1640,
    1648,  1677,  1684,  1690,  1698,  1708,  1721,  1735,  1742,  1751,
    1758,  1765,  1774,  1779,  1785,  1801,  1808,  1817,  1821,  1825,
    1829,  1833,  1837,  1841,  1845,  1853,  1861,  1872,  1883,  1891,
    1899,  1907,  1915,  1927,  1934,  1944,  1948,  1956,  1963,  1977,
    1984,  1998,  2002,  2010,  2016,  2029,  2042,  2046,  2051,  2056,
    2061,  2066,  2075,  2082,  2094,  2098,  2107,  2114,  2124,  2131,
    2141,  2150,  2156,  2164,  2170,  2182,  2189,  2198,  2210,  2217,
    2226,  2232,  2236,  2243,  2256,  2262,  2271,  2278,  2285,  2292,
    2299,  2306,  2313
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
#line 6797 "GrammarParser.cpp"

#line 2319 "../../obj/src/GrammarParser.y"


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
