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
        value.YY_MOVE_OR_COPY< AST::Token::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.YY_MOVE_OR_COPY< BehaviorDefinition::Ptr > (YY_MOVE (that.value));
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
        value.move< AST::Token::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.move< BehaviorDefinition::Ptr > (YY_MOVE (that.value));
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
        value.copy< AST::Token::Ptr > (that.value);
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

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.copy< BehaviorDefinition::Ptr > (that.value);
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
        value.move< AST::Token::Ptr > (that.value);
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

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.move< BehaviorDefinition::Ptr > (that.value);
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
        yylhs.value.emplace< AST::Token::Ptr > ();
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

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        yylhs.value.emplace< BehaviorDefinition::Ptr > ();
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
      auto definition = CST::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2911 "GrammarParser.cpp"
    break;

  case 4: // Header: "CASM"
#line 461 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = CST::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < InitDefinition::Ptr > () = CST::make< InitDefinition >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3085 "GrammarParser.cpp"
    break;

  case 25: // InitDefinition: "init" "{" MappedExpressions "}"
#line 567 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = CST::make< InitDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < MappedExpressions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3093 "GrammarParser.cpp"
    break;

  case 26: // EnumerationDefinition: "enumeration" Identifier "=" "{" Enumerators "}"
#line 575 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = CST::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3101 "GrammarParser.cpp"
    break;

  case 27: // DerivedDefinition: "derived" Identifier "->" Type "=" Term
#line 583 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3110 "GrammarParser.cpp"
    break;

  case 28: // DerivedDefinition: "derived" Identifier "(" Parameters ")" "->" Type "=" Term
#line 588 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < AST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < AST::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
  }
#line 3120 "GrammarParser.cpp"
    break;

  case 29: // DerivedDefinition: "derived" Identifier "(" MethodParameters ")" "->" Type "=" Term
#line 594 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < AST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < AST::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3148 "GrammarParser.cpp"
    break;

  case 32: // RuleDefinition: "rule" Identifier "->" Type "=" Rule
#line 614 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3157 "GrammarParser.cpp"
    break;

  case 33: // RuleDefinition: "rule" Identifier "(" Parameters ")" "=" Rule
#line 619 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < AST::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < AST::Token::Ptr > () );
  }
#line 3168 "GrammarParser.cpp"
    break;

  case 34: // RuleDefinition: "rule" Identifier "(" Parameters ")" "->" Type "=" Rule
#line 626 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < AST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
  }
#line 3178 "GrammarParser.cpp"
    break;

  case 35: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "=" Rule
#line 632 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < AST::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < AST::Token::Ptr > () );
  }
#line 3189 "GrammarParser.cpp"
    break;

  case 36: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "->" Type "=" Rule
#line 639 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < AST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < FunctionDefinition::Ptr > () = CST::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < AST::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
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
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < UsingDefinition::Ptr > () = CST::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3278 "GrammarParser.cpp"
    break;

  case 46: // UsingPathDefinition: "using" IdentifierPath
#line 708 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = CST::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3286 "GrammarParser.cpp"
    break;

  case 47: // UsingPathDefinition: "using" IdentifierPath "::" "*"
#line 712 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = CST::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3294 "GrammarParser.cpp"
    break;

  case 48: // InvariantDefinition: "invariant" Identifier "=" Term
#line 720 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = CST::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3302 "GrammarParser.cpp"
    break;

  case 49: // ImportDefinition: "import" IdentifierPath
#line 728 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = CST::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3310 "GrammarParser.cpp"
    break;

  case 50: // ImportDefinition: "import" IdentifierPath "as" Identifier
#line 732 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = CST::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3318 "GrammarParser.cpp"
    break;

  case 51: // StructureDefinition: "structure" Identifier "=" "{" StructureDefinitionList "}"
#line 744 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < StructureDefinition::Ptr > () = CST::make< StructureDefinition >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < FunctionDefinitions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < BehaviorDefinition::Ptr > () = CST::make< BehaviorDefinition >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < ImplementDefinition::Ptr > () = CST::make< ImplementDefinition >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3454 "GrammarParser.cpp"
    break;

  case 66: // ImplementDefinition: "implement" Type "for" Type "=" "{" ImplementDefinitionList "}"
#line 849 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = CST::make< ImplementDefinition >( yylhs.location, yystack_[7].value.as < AST::Token::Ptr > (), yystack_[6].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < DomainDefinition::Ptr > () = CST::make< DomainDefinition >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3524 "GrammarParser.cpp"
    break;

  case 74: // BuiltinDefinition: "builtin" RelationType
#line 912 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BuiltinDefinition::Ptr > () = CST::make< BuiltinDefinition >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < RelationType::Ptr > () );
  }
#line 3532 "GrammarParser.cpp"
    break;

  case 75: // Declaration: "derived" Identifier ":" MaybeFunctionParameters "->" Type
#line 924 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = CST::make< Declaration >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3540 "GrammarParser.cpp"
    break;

  case 76: // Declaration: "rule" Identifier ":" MaybeFunctionParameters "->" Type
#line 928 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = CST::make< Declaration >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
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
      yylhs.value.as < SkipRule::Ptr > () = CST::make< SkipRule >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3680 "GrammarParser.cpp"
    break;

  case 93: // ConditionalRule: "if" Term "then" Rule
#line 1020 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = CST::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3688 "GrammarParser.cpp"
    break;

  case 94: // ConditionalRule: "if" Term "then" Rule "else" Rule
#line 1024 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = CST::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3696 "GrammarParser.cpp"
    break;

  case 95: // CaseRule: "case" Term "of" "{" CaseLabels "}"
#line 1032 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = CST::make< CaseRule >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < Case::Ptr > () = CST::make< DefaultCase >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3740 "GrammarParser.cpp"
    break;

  case 100: // CaseLabel: "_" ":" Rule
#line 1064 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< DefaultCase >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3748 "GrammarParser.cpp"
    break;

  case 101: // CaseLabel: Term ":" Rule
#line 1068 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3756 "GrammarParser.cpp"
    break;

  case 102: // LetRule: "let" VariableBindings "in" Rule
#line 1076 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = CST::make< LetRule >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3764 "GrammarParser.cpp"
    break;

  case 103: // LocalRule: "local" LocalFunctionDefinitions "in" Rule
#line 1084 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LocalRule::Ptr > () = CST::make< LocalRule >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < FunctionDefinitions::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3772 "GrammarParser.cpp"
    break;

  case 104: // ForallRule: "forall" AttributedVariables "in" Term "do" Rule
#line 1092 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = CST::make< ForallRule >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3780 "GrammarParser.cpp"
    break;

  case 105: // ForallRule: "forall" AttributedVariables "in" Term "with" Term "do" Rule
#line 1096 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = CST::make< ForallRule >( yylhs.location, yystack_[7].value.as < AST::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3788 "GrammarParser.cpp"
    break;

  case 106: // ChooseRule: "choose" AttributedVariables "in" Term "do" Rule
#line 1104 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = CST::make< ChooseRule >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3796 "GrammarParser.cpp"
    break;

  case 107: // IterateRule: "iterate" Rule
#line 1112 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = CST::make< IterateRule >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3804 "GrammarParser.cpp"
    break;

  case 108: // BlockRule: "{" Rules "}"
#line 1120 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = CST::make< BlockRule >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3812 "GrammarParser.cpp"
    break;

  case 109: // BlockRule: "par" Rules "endpar"
#line 1124 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = CST::make< BlockRule >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < SequenceRule::Ptr > () = CST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3846 "GrammarParser.cpp"
    break;

  case 113: // SequenceRule: "seq" Rules "endseq"
#line 1146 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = CST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < UpdateRule::Ptr > () = CST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3880 "GrammarParser.cpp"
    break;

  case 117: // UpdateRule: MethodCallExpression ":=" Term
#line 1168 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = CST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < MethodCallExpression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
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
      yylhs.value.as < WhileRule::Ptr > () = CST::make< WhileRule >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3904 "GrammarParser.cpp"
    break;

  case 120: // Terms: Terms "," Term
#line 1196 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < Expression::Ptr > () = CST::make< CST::EmbracedExpression >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
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
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4045 "GrammarParser.cpp"
    break;

  case 137: // Expression: "-" Expression
#line 1277 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4053 "GrammarParser.cpp"
    break;

  case 138: // OperatorExpression: Term "+" Term
#line 1289 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4061 "GrammarParser.cpp"
    break;

  case 139: // OperatorExpression: Term "-" Term
#line 1293 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4069 "GrammarParser.cpp"
    break;

  case 140: // OperatorExpression: Term "*" Term
#line 1297 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4077 "GrammarParser.cpp"
    break;

  case 141: // OperatorExpression: Term "/" Term
#line 1301 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4085 "GrammarParser.cpp"
    break;

  case 142: // OperatorExpression: Term "%" Term
#line 1305 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4093 "GrammarParser.cpp"
    break;

  case 143: // OperatorExpression: Term "^" Term
#line 1309 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4101 "GrammarParser.cpp"
    break;

  case 144: // OperatorExpression: Term "!=" Term
#line 1313 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4109 "GrammarParser.cpp"
    break;

  case 145: // OperatorExpression: Term "=" Term
#line 1317 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4117 "GrammarParser.cpp"
    break;

  case 146: // OperatorExpression: Term "<" Term
#line 1321 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4125 "GrammarParser.cpp"
    break;

  case 147: // OperatorExpression: Term ">" Term
#line 1325 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4133 "GrammarParser.cpp"
    break;

  case 148: // OperatorExpression: Term "<=" Term
#line 1329 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4141 "GrammarParser.cpp"
    break;

  case 149: // OperatorExpression: Term ">=" Term
#line 1333 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4149 "GrammarParser.cpp"
    break;

  case 150: // OperatorExpression: Term "or" Term
#line 1337 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4157 "GrammarParser.cpp"
    break;

  case 151: // OperatorExpression: Term "xor" Term
#line 1341 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4165 "GrammarParser.cpp"
    break;

  case 152: // OperatorExpression: Term "and" Term
#line 1345 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4173 "GrammarParser.cpp"
    break;

  case 153: // OperatorExpression: Term "=>" Term
#line 1349 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4181 "GrammarParser.cpp"
    break;

  case 154: // OperatorExpression: Term "implies" Term
#line 1353 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4189 "GrammarParser.cpp"
    break;

  case 155: // OperatorExpression: "not" Term
#line 1357 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
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
      const auto identifier = CST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      const auto identifierPath = IdentifierPath::fromIdentifier( identifier );
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, identifierPath );
  }
#line 4231 "GrammarParser.cpp"
    break;

  case 160: // DirectCallExpression: IdentifierPath
#line 1387 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4239 "GrammarParser.cpp"
    break;

  case 161: // DirectCallExpression: IdentifierPath "(" ")"
#line 1391 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), arguments, yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4248 "GrammarParser.cpp"
    break;

  case 162: // DirectCallExpression: IdentifierPath "(" Terms ")"
#line 1396 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expressions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4256 "GrammarParser.cpp"
    break;

  case 163: // DirectCallExpression: IdentifierPath "(" error ")"
#line 1400 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 4264 "GrammarParser.cpp"
    break;

  case 164: // MethodCallExpression: Expression "." Identifier
#line 1408 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 4273 "GrammarParser.cpp"
    break;

  case 165: // MethodCallExpression: Expression "." Identifier "(" ")"
#line 1413 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < AST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4284 "GrammarParser.cpp"
    break;

  case 166: // MethodCallExpression: Expression "." Identifier "(" Terms ")"
#line 1420 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < AST::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < AST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4294 "GrammarParser.cpp"
    break;

  case 167: // MethodCallExpression: Expression "." Identifier "(" error ")"
#line 1426 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 4302 "GrammarParser.cpp"
    break;

  case 168: // LiteralCallExpression: Expression "." IntegerLiteral
#line 1434 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = CST::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 4310 "GrammarParser.cpp"
    break;

  case 169: // IndirectCallExpression: CallExpression "(" ")"
#line 1442 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = CST::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < AST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4321 "GrammarParser.cpp"
    break;

  case 170: // IndirectCallExpression: CallExpression "(" Terms ")"
#line 1449 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = CST::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < AST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4331 "GrammarParser.cpp"
    break;

  case 171: // IndirectCallExpression: CallExpression "(" error ")"
#line 1455 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 4339 "GrammarParser.cpp"
    break;

  case 172: // TypeCastingExpression: Expression "as" Type
#line 1463 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = CST::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 4347 "GrammarParser.cpp"
    break;

  case 173: // LetExpression: "let" VariableBindings "in" Term
#line 1471 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = CST::make< LetExpression >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4355 "GrammarParser.cpp"
    break;

  case 174: // ConditionalExpression: "if" Term "then" Term "else" Term
#line 1479 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = CST::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4363 "GrammarParser.cpp"
    break;

  case 175: // ChooseExpression: "choose" AttributedVariables "in" Term "do" Term
#line 1487 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = CST::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4371 "GrammarParser.cpp"
    break;

  case 176: // UniversalQuantifierExpression: "forall" AttributedVariables "in" Term "holds" Term
#line 1495 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = CST::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4379 "GrammarParser.cpp"
    break;

  case 177: // ExistentialQuantifierExpression: "exists" AttributedVariables "in" Term "with" Term
#line 1503 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = CST::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4387 "GrammarParser.cpp"
    break;

  case 178: // CardinalityExpression: "|" Expression "|"
#line 1511 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = CST::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4395 "GrammarParser.cpp"
    break;

  case 179: // Literal: UndefinedLiteral
#line 1523 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 4403 "GrammarParser.cpp"
    break;

  case 180: // Literal: BooleanLiteral
#line 1527 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4411 "GrammarParser.cpp"
    break;

  case 181: // Literal: IntegerLiteral
#line 1531 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4419 "GrammarParser.cpp"
    break;

  case 182: // Literal: RationalLiteral
#line 1535 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4427 "GrammarParser.cpp"
    break;

  case 183: // Literal: DecimalLiteral
#line 1539 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4435 "GrammarParser.cpp"
    break;

  case 184: // Literal: BinaryLiteral
#line 1543 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4443 "GrammarParser.cpp"
    break;

  case 185: // Literal: StringLiteral
#line 1547 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4451 "GrammarParser.cpp"
    break;

  case 186: // Literal: ReferenceLiteral
#line 1551 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 4459 "GrammarParser.cpp"
    break;

  case 187: // Literal: ListLiteral
#line 1559 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 4467 "GrammarParser.cpp"
    break;

  case 188: // Literal: RangeLiteral
#line 1563 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 4475 "GrammarParser.cpp"
    break;

  case 189: // Literal: TupleLiteral
#line 1567 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 4483 "GrammarParser.cpp"
    break;

  case 190: // Literal: RecordLiteral
#line 1571 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 4491 "GrammarParser.cpp"
    break;

  case 191: // UndefinedLiteral: "undef"
#line 1579 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = CST::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < AST::Token::Ptr > ()->spans() );
  }
#line 4500 "GrammarParser.cpp"
    break;

  case 192: // BooleanLiteral: "true"
#line 1588 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = CST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < AST::Token::Ptr > ()->spans() );
  }
#line 4510 "GrammarParser.cpp"
    break;

  case 193: // BooleanLiteral: "false"
#line 1594 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = CST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < AST::Token::Ptr > ()->spans() );
  }
#line 4520 "GrammarParser.cpp"
    break;

  case 194: // IntegerLiteral: "integer"
#line 1604 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4528 "GrammarParser.cpp"
    break;

  case 195: // RationalLiteral: "rational"
#line 1612 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4536 "GrammarParser.cpp"
    break;

  case 196: // DecimalLiteral: "decimal"
#line 1620 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4544 "GrammarParser.cpp"
    break;

  case 197: // BinaryLiteral: "binary"
#line 1628 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4552 "GrammarParser.cpp"
    break;

  case 198: // BinaryLiteral: "hexadecimal"
#line 1632 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4560 "GrammarParser.cpp"
    break;

  case 199: // StringLiteral: "string"
#line 1640 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4568 "GrammarParser.cpp"
    break;

  case 200: // ReferenceLiteral: "@" IdentifierPath
#line 1648 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = CST::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4576 "GrammarParser.cpp"
    break;

  case 201: // ListLiteral: "[" "]"
#line 1677 "../../obj/src/GrammarParser.y"
  {
      const auto& expressions = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = CST::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < AST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4587 "GrammarParser.cpp"
    break;

  case 202: // ListLiteral: "[" Terms "]"
#line 1684 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = CST::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < AST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4597 "GrammarParser.cpp"
    break;

  case 203: // ListLiteral: "[" error "]"
#line 1690 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4605 "GrammarParser.cpp"
    break;

  case 204: // RangeLiteral: "[" Term ".." Term "]"
#line 1698 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = CST::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4615 "GrammarParser.cpp"
    break;

  case 205: // TupleLiteral: "(" Terms "," Term ")"
#line 1708 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < AST::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = CST::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < AST::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4628 "GrammarParser.cpp"
    break;

  case 206: // RecordLiteral: "{" Assignments "}"
#line 1721 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = CST::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4638 "GrammarParser.cpp"
    break;

  case 207: // Assignments: Assignments "," Assignment
#line 1735 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4649 "GrammarParser.cpp"
    break;

  case 208: // Assignments: Assignment
#line 1742 "../../obj/src/GrammarParser.y"
  {
      auto assignments = CST::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4659 "GrammarParser.cpp"
    break;

  case 209: // Assignment: Identifier ":" Term
#line 1751 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = CST::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4667 "GrammarParser.cpp"
    break;

  case 210: // MappedExpressions: MappedExpressions "," MappedExpression
#line 1758 "../../obj/src/GrammarParser.y"
  {
      const auto& mappedExpressions = yystack_[2].value.as < MappedExpressions::Ptr > ();
      yystack_[0].value.as < MappedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      mappedExpressions->add( yystack_[0].value.as < MappedExpression::Ptr > () );
      yylhs.value.as < MappedExpressions::Ptr > () = mappedExpressions;
  }
#line 4678 "GrammarParser.cpp"
    break;

  case 211: // MappedExpressions: MappedExpression
#line 1765 "../../obj/src/GrammarParser.y"
  {
      auto mappedExpressions = CST::make< MappedExpressions >( yylhs.location );
      mappedExpressions->add( yystack_[0].value.as < MappedExpression::Ptr > () );
      yylhs.value.as < MappedExpressions::Ptr > () = mappedExpressions;
  }
#line 4688 "GrammarParser.cpp"
    break;

  case 212: // MappedExpression: "->" Term
#line 1774 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4697 "GrammarParser.cpp"
    break;

  case 213: // MappedExpression: "(" Term ")" "->" Term
#line 1779 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = CST::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, yystack_[4].value.as < AST::Token::Ptr > (), arguments, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4707 "GrammarParser.cpp"
    break;

  case 214: // MappedExpression: TupleLiteral "->" Term
#line 1785 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto& leftBracket = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto& rightBracket = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4718 "GrammarParser.cpp"
    break;

  case 215: // Types: Types "," Type
#line 1801 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4729 "GrammarParser.cpp"
    break;

  case 216: // Types: Type
#line 1808 "../../obj/src/GrammarParser.y"
  {
      auto types = CST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4739 "GrammarParser.cpp"
    break;

  case 217: // Type: BasicType
#line 1817 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4747 "GrammarParser.cpp"
    break;

  case 218: // Type: TupleType
#line 1821 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4755 "GrammarParser.cpp"
    break;

  case 219: // Type: RecordType
#line 1825 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4763 "GrammarParser.cpp"
    break;

  case 220: // Type: TemplateType
#line 1829 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4771 "GrammarParser.cpp"
    break;

  case 221: // Type: RelationType
#line 1833 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4779 "GrammarParser.cpp"
    break;

  case 222: // Type: FixedSizedType
#line 1837 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4787 "GrammarParser.cpp"
    break;

  case 223: // Type: MappingType
#line 1841 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < MappingType::Ptr > ();
  }
#line 4795 "GrammarParser.cpp"
    break;

  case 224: // Type: VaradicType
#line 1845 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < VaradicType::Ptr > ();
  }
#line 4803 "GrammarParser.cpp"
    break;

  case 225: // BasicType: IdentifierPath
#line 1853 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = CST::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4811 "GrammarParser.cpp"
    break;

  case 226: // TupleType: "(" Types "," Type ")"
#line 1861 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < AST::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = CST::make< TupleType >( yylhs.location, yystack_[4].value.as < AST::Token::Ptr > (), subTypes, yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4822 "GrammarParser.cpp"
    break;

  case 227: // RecordType: "{" TypedVariables "," TypedVariable "}"
#line 1872 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < AST::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = CST::make< RecordType >( yylhs.location, yystack_[4].value.as < AST::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4833 "GrammarParser.cpp"
    break;

  case 228: // TemplateType: IdentifierPath "<" Types ">"
#line 1883 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = CST::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4841 "GrammarParser.cpp"
    break;

  case 229: // RelationType: IdentifierPath "<" MaybeFunctionParameters "->" Type ">"
#line 1891 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = CST::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < AST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4849 "GrammarParser.cpp"
    break;

  case 230: // FixedSizedType: IdentifierPath "'" Term
#line 1899 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = CST::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4857 "GrammarParser.cpp"
    break;

  case 231: // MappingType: "<" FunctionParameters "->" Type ">"
#line 1907 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MappingType::Ptr > () = CST::make< MappingType >( yylhs.location, yystack_[4].value.as < AST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );      
  }
#line 4865 "GrammarParser.cpp"
    break;

  case 232: // VaradicType: Identifier "..."
#line 1915 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VaradicType::Ptr > () = CST::make< VaradicType >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4873 "GrammarParser.cpp"
    break;

  case 233: // FunctionParameters: FunctionParameters "*" Type
#line 1927 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4884 "GrammarParser.cpp"
    break;

  case 234: // FunctionParameters: Type
#line 1934 "../../obj/src/GrammarParser.y"
  {
      auto types = CST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4894 "GrammarParser.cpp"
    break;

  case 235: // MaybeFunctionParameters: FunctionParameters
#line 1944 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 4902 "GrammarParser.cpp"
    break;

  case 236: // MaybeFunctionParameters: %empty
#line 1948 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = CST::make< Types >( yylhs.location );
  }
#line 4910 "GrammarParser.cpp"
    break;

  case 237: // MethodParameters: MethodParameters "," TypedAttributedVariable
#line 1956 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4921 "GrammarParser.cpp"
    break;

  case 238: // MethodParameters: "this"
#line 1963 "../../obj/src/GrammarParser.y"
  {
      auto parameters = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto identifier = CST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      const auto unresolvedType = CST::make< UnresolvedType >( yylhs.location );
      auto variable = CST::make< VariableDefinition >( yylhs.location, identifier, Token::unresolved(), unresolvedType );
      parameters->add( variable );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4934 "GrammarParser.cpp"
    break;

  case 239: // Parameters: Parameters "," TypedAttributedVariable
#line 1976 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4945 "GrammarParser.cpp"
    break;

  case 240: // Parameters: TypedAttributedVariable
#line 1983 "../../obj/src/GrammarParser.y"
  {
      auto parameters = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4955 "GrammarParser.cpp"
    break;

  case 241: // MaybeDefined: "defined" "{" Term "}"
#line 1997 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = CST::make< Defined >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4963 "GrammarParser.cpp"
    break;

  case 242: // MaybeDefined: %empty
#line 2001 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = CST::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), CST::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 4971 "GrammarParser.cpp"
    break;

  case 243: // MaybeInitially: "=" "{" Expression "}"
#line 2009 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: drop braces and replace this rule with ::= Expression
      const auto& embracedExpression = CST::make< EmbracedExpression >( yystack_[1].location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), embracedExpression );
  }
#line 4981 "GrammarParser.cpp"
    break;

  case 244: // MaybeInitially: "=" "{" MappedExpressions "}"
#line 2015 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: replace this rule with ::= EQUAL SetLiteral
      const auto& expressions = CST::make< Expressions >( yystack_[1].location );
      for( auto const& expression : *yystack_[1].value.as < MappedExpressions::Ptr > () )
      {
          expressions->add( expression );
      }
      const auto& setLiteral = CST::make< SetLiteral >( yystack_[1].location, expressions );
      setLiteral->setLeftBracket( yystack_[2].value.as < AST::Token::Ptr > () );
      setLiteral->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), setLiteral );
  }
#line 4998 "GrammarParser.cpp"
    break;

  case 245: // MaybeInitially: %empty
#line 2028 "../../obj/src/GrammarParser.y"
  {
      const auto& expression = CST::make< CST::AbstractExpression >( yylhs.location, Token::unresolved() );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, Token::unresolved(), expression );
  }
#line 5007 "GrammarParser.cpp"
    break;

  case 246: // Identifier: "identifier"
#line 2041 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 5015 "GrammarParser.cpp"
    break;

  case 247: // Identifier: "in"
#line 2045 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5024 "GrammarParser.cpp"
    break;

  case 248: // Identifier: "CASM"
#line 2050 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5033 "GrammarParser.cpp"
    break;

  case 249: // Identifier: "self"
#line 2055 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5042 "GrammarParser.cpp"
    break;

  case 250: // Identifier: "enumeration"
#line 2060 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5051 "GrammarParser.cpp"
    break;

  case 251: // IdentifierPath: IdentifierPath "::" Identifier
#line 2069 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < AST::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 5062 "GrammarParser.cpp"
    break;

  case 252: // IdentifierPath: Identifier
#line 2076 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = CST::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5070 "GrammarParser.cpp"
    break;

  case 253: // Variable: TypedVariable
#line 2088 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5078 "GrammarParser.cpp"
    break;

  case 254: // Variable: Identifier
#line 2092 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = CST::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = CST::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 5087 "GrammarParser.cpp"
    break;

  case 255: // AttributedVariables: AttributedVariables "," AttributedVariable
#line 2101 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5098 "GrammarParser.cpp"
    break;

  case 256: // AttributedVariables: AttributedVariable
#line 2108 "../../obj/src/GrammarParser.y"
  {
      auto variables = CST::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5108 "GrammarParser.cpp"
    break;

  case 257: // TypedVariables: TypedVariables "," TypedVariable
#line 2118 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5119 "GrammarParser.cpp"
    break;

  case 258: // TypedVariables: TypedVariable
#line 2125 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = CST::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5129 "GrammarParser.cpp"
    break;

  case 259: // TypedVariable: Identifier ":" Type
#line 2135 "../../obj/src/GrammarParser.y"
  {
      auto variable = CST::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5138 "GrammarParser.cpp"
    break;

  case 260: // AttributedVariable: Attributes Variable
#line 2144 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5148 "GrammarParser.cpp"
    break;

  case 261: // AttributedVariable: Variable
#line 2150 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5156 "GrammarParser.cpp"
    break;

  case 262: // TypedAttributedVariable: Attributes TypedVariable
#line 2158 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5166 "GrammarParser.cpp"
    break;

  case 263: // TypedAttributedVariable: TypedVariable
#line 2164 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5174 "GrammarParser.cpp"
    break;

  case 264: // VariableBindings: VariableBindings "," VariableBinding
#line 2176 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5185 "GrammarParser.cpp"
    break;

  case 265: // VariableBindings: VariableBinding
#line 2183 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = CST::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5195 "GrammarParser.cpp"
    break;

  case 266: // VariableBinding: AttributedVariable "=" Term
#line 2192 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = CST::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5203 "GrammarParser.cpp"
    break;

  case 267: // LocalFunctionDefinitions: LocalFunctionDefinitions "," AttributedLocalFunctionDefinition
#line 2204 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5214 "GrammarParser.cpp"
    break;

  case 268: // LocalFunctionDefinitions: AttributedLocalFunctionDefinition
#line 2211 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5224 "GrammarParser.cpp"
    break;

  case 269: // AttributedLocalFunctionDefinition: Attributes LocalFunctionDefinition
#line 2220 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 5234 "GrammarParser.cpp"
    break;

  case 270: // AttributedLocalFunctionDefinition: LocalFunctionDefinition
#line 2226 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 5242 "GrammarParser.cpp"
    break;

  case 271: // AttributedLocalFunctionDefinition: error
#line 2230 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 5250 "GrammarParser.cpp"
    break;

  case 272: // LocalFunctionDefinition: Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 2237 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = CST::make< FunctionDefinition >( yylhs.location, Token::unresolved(), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > ()->setClassification( FunctionDefinition::Classification::LOCAL );
  }
#line 5259 "GrammarParser.cpp"
    break;

  case 273: // Attributes: Attributes Attribute
#line 2250 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5269 "GrammarParser.cpp"
    break;

  case 274: // Attributes: Attribute
#line 2256 "../../obj/src/GrammarParser.y"
  {
      auto attributes = CST::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5279 "GrammarParser.cpp"
    break;

  case 275: // Attribute: "[" BasicAttribute "]"
#line 2265 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < AST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < AST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5290 "GrammarParser.cpp"
    break;

  case 276: // Attribute: "[" SymbolAttribute "]"
#line 2272 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < SymbolAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < AST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < AST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5301 "GrammarParser.cpp"
    break;

  case 277: // Attribute: "[" ExpressionAttribute "]"
#line 2279 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < AST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < AST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5312 "GrammarParser.cpp"
    break;

  case 278: // Attribute: "[" error "]"
#line 2286 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 5320 "GrammarParser.cpp"
    break;

  case 279: // BasicAttribute: Identifier
#line 2293 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = CST::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5328 "GrammarParser.cpp"
    break;

  case 280: // SymbolAttribute: Identifier TypedVariable
#line 2300 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SymbolAttribute::Ptr > () = CST::make< SymbolAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < VariableDefinition::Ptr > () );
  }
#line 5336 "GrammarParser.cpp"
    break;

  case 281: // ExpressionAttribute: Identifier Term
#line 2307 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = CST::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5344 "GrammarParser.cpp"
    break;


#line 5348 "GrammarParser.cpp"

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


  const short Parser::yypact_ninf_ = -421;

  const short Parser::yytable_ninf_ = -235;

  const short
  Parser::yypact_[] =
  {
      38,  -421,    74,    82,   705,    48,  -421,   -48,  -421,  -421,
    -421,  -421,  -421,  2348,   -27,    53,   151,  -421,  -421,    95,
     154,   154,   154,   154,   154,   154,   154,    88,    88,    88,
     154,   154,   682,  -421,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,   879,
    -421,  -421,  -421,  -421,   123,   123,   123,  2348,   123,  -421,
    -421,  -421,  2348,   544,   544,  1816,  1552,   154,   544,   154,
    -421,  -421,  -421,  -421,  -421,  -421,  3050,   -33,  -421,   163,
    -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -421,  -421,   207,   126,  -421,  -421,  -421,  -421,
      23,  -421,   215,   119,   224,   220,   242,   245,   257,    45,
     260,    88,   154,    88,   269,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -421,   246,   231,    25,  -421,  -421,   279,   278,
    -421,  -421,   207,  -421,  -421,   286,    42,  -421,   123,    58,
    -421,    84,  2569,   105,  -421,  -421,  -421,   294,   292,  2819,
     309,  -421,   -43,  2782,   146,  -421,   307,    17,   215,  2348,
    2348,  2348,  2348,  2348,  2348,  2348,  2348,  2348,  2348,  2348,
    2348,  2348,  2348,  2348,  2348,  2348,    88,   134,  1618,    88,
    1684,   154,  2348,  2348,   297,   216,  -421,    31,    88,   313,
    2216,    57,    88,    88,   155,  2348,   154,   318,   316,  -421,
     207,   317,  -421,  -421,   280,   325,  -421,    88,  2348,    88,
     326,    88,    88,  2348,  2348,   123,  -421,  2348,   123,  2348,
    2348,  2348,  -421,  2348,  -421,  -421,  -421,  2348,  2348,  -421,
     154,  2348,  -421,  2157,   994,   936,   434,   165,   165,   266,
     361,   361,   314,   314,   314,  -421,   434,   266,   361,   361,
    -421,  -421,   333,   337,  -421,    10,  3050,  -421,   339,  -421,
      61,  -421,  2852,  3050,  2348,  -421,    23,   340,  -421,    76,
     147,  -421,  -421,   123,   343,    27,  1186,  1264,  -421,   123,
      68,   123,   123,  2216,  2348,  2348,  2348,  1342,  1420,  -421,
    -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -421,   319,   -47,   322,   324,   346,   177,   213,
     352,  -421,  -421,  3050,  -421,   115,    88,   154,    88,    88,
      43,   263,   282,   341,   335,  -421,   357,   159,   345,  3050,
    3050,  -421,  2716,  -421,  2431,  2646,  2749,  2885,  3050,  2918,
    -421,  3050,  1750,  -421,  -421,  -421,  -421,   348,  3050,  -421,
     349,   364,   123,   366,   123,  -421,  2348,  -421,  -421,   239,
    -421,   123,   413,  1893,  -421,   417,  1971,   111,  -421,   381,
     125,  -421,  -421,   123,   139,   145,  -421,  2608,  2682,  2464,
     384,  2049,   307,   365,  2127,  2348,  2348,   136,   168,   211,
    2216,  -421,    49,  -421,   115,   391,   388,  -421,   382,   154,
     154,  -421,  -421,  -421,     7,  -421,    43,    88,  -421,    88,
     390,  -421,  -421,    33,  -421,  -421,   159,    88,  2348,  2348,
    2348,  2348,  -421,  -421,   396,  -421,   214,  2348,    88,    88,
    -421,    88,  -421,  3050,  -421,    27,  -421,  -421,  -421,  -421,
    -421,  -421,  2216,    88,  2216,    68,  -421,  2348,  2348,  2216,
     395,  2216,  -421,  -421,  -421,  -421,  3050,  3050,  2216,    88,
    2216,    88,  2216,    88,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,   315,   212,  -421,  -421,  -421,  -421,  -421,  -421,   387,
     159,  -421,  -421,  -421,   438,  3050,  3050,  3050,  3050,  -421,
    -421,  3050,   406,   409,   411,  -421,  -421,   392,  -421,  -421,
    1079,  2497,   429,  1486,  -421,  -421,   416,  -421,   418,  -421,
     419,    88,    88,  -421,   187,   420,   422,  2348,  2348,  2348,
      88,  2216,  2348,  2216,  2216,   425,   428,   430,  2282,  -421,
    2951,  2216,  2216,  2216,   403,   404,  -421,  2348,   421,  -421,
    3050,  3050,  3050,   438,  -421,  2530,  -421,  -421,  -421,  2216,
    2216,  -421,  -421,  2216,  -421,  -421,  -421,    88,    88,  2984,
    2403,   422,  2216,  -421,  -421,  -421,  -421,  -421,  -421,  1816,
     116,   297,   255,  -421,  -421,  3017,  -421,  -421,   348
  };

  const short
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   274,     0,   248,   250,
     249,   247,   246,   279,     0,     0,     0,     1,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     8,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,     0,
       3,   273,   278,   159,     0,     0,     0,     0,     0,   191,
     193,   192,     0,     0,     0,     0,     0,     0,     0,     0,
     197,   198,   194,   195,   196,   199,   281,   122,   124,   133,
     156,   157,   134,   158,   123,   125,   126,   127,   128,   129,
     130,   135,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   252,   160,   280,   275,   276,   277,
       0,   252,    24,     0,     0,     0,   252,    46,     0,    49,
       0,     0,     0,     0,     0,   217,   218,   219,   220,   221,
     222,   223,   224,   252,   225,     0,    73,    74,     0,     0,
       5,     7,   254,   261,   253,     0,     0,   265,     0,     0,
     256,     0,     0,     0,   155,   136,   137,     0,     0,   121,
       0,   201,     0,   121,     0,   208,     0,     0,   200,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   211,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   216,
       0,     0,   258,   234,     0,     0,   232,   236,     0,     0,
       0,   236,   236,     0,     0,     0,   260,     0,     0,     0,
       0,     0,   132,     0,   131,   203,   202,     0,     0,   206,
       0,     0,   178,   152,   150,   151,   154,   138,   139,   145,
     146,   147,   140,   141,   142,   143,   153,   144,   148,   149,
     172,   168,   164,     0,   169,     0,   121,   259,     0,   161,
       0,   251,   121,   212,     0,    25,     0,     0,   238,     0,
       0,   263,   240,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,     0,   118,   156,   157,     0,     0,     0,
       0,    45,    47,    48,    50,     0,     0,     0,     0,     0,
       0,     0,   216,   235,     0,   230,     0,     0,     0,   266,
     173,   264,     0,   255,     0,     0,     0,   120,   120,     0,
     207,   209,     0,   171,   170,   163,   162,     0,   214,   210,
       0,     0,     0,     0,     0,   262,     0,    42,    44,     0,
      40,     0,     0,     0,    78,     0,     0,     0,   271,     0,
       0,   268,   270,     0,     0,     0,   107,     0,     0,     0,
       0,     0,   252,     0,     0,     0,     0,     0,     0,     0,
       0,    55,     0,    53,     0,   215,   257,   233,     0,     0,
       0,    60,    62,    64,     0,    58,     0,     0,   228,     0,
       0,    71,    72,     0,    68,    70,     0,     0,     0,     0,
       0,     0,   205,   204,     0,   165,     0,     0,     0,     0,
     237,     0,   239,    27,    26,     0,    41,   115,   113,    77,
     111,   109,     0,   236,     0,     0,   269,     0,     0,     0,
       0,     0,   110,   108,   114,   112,   116,   117,     0,     0,
       0,     0,     0,     0,    32,    51,    52,    54,   226,   227,
     231,     0,     0,    56,    63,    59,    61,    57,   215,     0,
       0,    65,    67,    69,   242,   176,   175,   174,   177,   167,
     166,   213,     0,     0,     0,    43,   102,     0,   103,   267,
       0,     0,    93,     0,   119,    37,     0,    35,     0,    33,
       0,   236,   236,   229,     0,     0,   245,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    98,
       0,     0,     0,     0,     0,     0,    66,     0,     0,    39,
      30,    29,    28,   242,   104,     0,   106,    94,    96,     0,
       0,    95,    97,     0,    38,    36,    34,     0,     0,     0,
       0,   245,     0,    99,   100,   101,    75,    76,   241,     0,
       0,   189,     0,   272,   105,   121,   243,   244,   131
  };

  const short
  Parser::yypgoto_[] =
  {
    -421,  -421,  -421,  -421,   458,   443,  -421,  -421,    12,    13,
    -289,    51,  -421,  -421,  -421,  -421,  -421,  -421,  -421,    92,
    -421,    83,  -421,  -421,     9,  -420,    72,  -421,  -421,    98,
     -90,   581,  -421,  -421,  -421,  -421,   -38,  -421,  -421,  -421,
    -421,  -421,  -421,  -421,  -421,  -421,  -421,   -60,    79,   284,
    -421,   410,   526,   636,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -421,  -421,  -421,  -421,   328,  -421,  -421,  -421,
    -421,  -421,  -421,  -421,  -108,  -421,  -421,   277,   -52,   247,
     304,   201,  -421,  -421,  -421,  -421,   494,  -421,  -421,  -421,
     408,  -221,   331,   334,   -13,   -45,    -2,   336,   393,   -51,
    -421,    30,   -50,    16,   253,   321,  -421,    89,   160,   131,
       8,  -421,  -421,  -421
  };

  const short
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    32,    33,    34,    35,    36,   421,   422,
      39,   368,   369,    40,    41,    42,    43,    44,   402,   403,
      45,   413,   414,    46,   423,   424,   425,    47,    48,   415,
     373,   374,   300,   301,   302,   538,   539,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   158,   266,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   164,   165,   195,   196,
     208,   213,   125,   126,   127,   128,   129,   130,   131,   132,
     333,   334,   279,   280,   526,   549,   111,   105,   143,   149,
     211,   144,   150,   282,   146,   147,   380,   381,   382,   148,
       6,    14,    15,    16
  };

  const short
  Parser::yytable_[] =
  {
      13,   338,   194,   492,   145,   151,   162,   153,   188,   186,
      52,   104,   409,    51,   410,   236,    37,    38,   113,   114,
     115,   116,   118,   237,   120,   133,   133,   133,   367,   139,
       8,   107,   277,     9,     8,  -133,   401,     9,    20,   219,
      22,     1,    10,   106,    37,    38,    10,   278,   409,   187,
     410,    50,   142,   142,   142,    11,   142,    51,   317,    11,
       8,    37,    38,     9,     2,   166,   354,   483,    31,   378,
     224,     8,    10,   278,     9,     7,   237,     8,   192,   220,
       9,   242,    17,    10,     2,    11,   227,   206,     2,    10,
       2,     8,    76,   491,     9,     2,    11,   193,     8,   187,
       2,     9,    11,    10,   492,     2,     2,   191,   225,   475,
      10,   108,   229,   401,     2,   477,    11,   356,    12,   133,
     210,   133,    12,    11,   228,     2,     8,   237,   265,     9,
     270,     5,   361,   231,    31,    49,   152,     8,    10,   452,
       9,   154,   362,   121,   159,   163,   142,   122,    12,    10,
     228,    11,   212,   454,   110,   123,    51,     8,     8,    12,
       9,     9,    11,    49,    20,    12,    22,   457,   194,    10,
      10,   228,     2,   458,   197,   145,   586,   225,   343,    12,
       2,   190,    11,    11,   133,   262,    12,   133,   191,   271,
     468,   455,    20,   198,    22,   210,   133,   376,   187,   210,
     133,   133,   271,   363,   324,   228,   239,   391,   394,   109,
     469,   228,   240,   364,    12,   133,     2,   133,   188,   133,
     133,    72,   470,   142,   322,    12,   142,   281,   124,   135,
     136,   281,   507,   398,   178,   179,   180,   181,   166,   145,
     384,   385,   471,   362,     2,    12,    12,   546,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   472,   200,   201,   189,   399,
     500,   272,   273,   522,   200,   201,   275,   191,   199,   364,
     237,   210,   276,   370,   323,   473,   202,   142,   379,   142,
     142,    51,   436,   191,   202,   392,   203,   335,   217,   444,
     544,   545,   339,   340,   218,   445,   342,   204,   344,   345,
     346,   205,   347,   365,   207,   587,   348,   349,   173,   174,
     351,   276,   209,   215,   133,   210,   133,   133,   283,   417,
     216,   418,   283,   176,   177,   178,   179,   180,   181,   222,
     223,   191,   411,   412,   184,   185,   221,   155,   156,   328,
     232,  -234,   167,   358,   329,   112,  -234,   406,   233,   117,
     210,   119,   210,   134,   134,   134,   138,   235,   241,   446,
     197,   274,   285,   387,   388,   389,   521,   325,   440,    51,
     442,   379,   326,   327,   330,   337,   181,   260,   352,   198,
     267,    51,   281,   353,   281,   355,   360,   366,   395,   284,
     396,   187,   397,   320,   321,   168,   400,   481,   482,   419,
     328,   420,    51,   173,   174,   133,   371,   133,   332,   427,
     336,   383,   437,   438,    51,   133,   411,   412,   485,   486,
     178,   179,   180,   181,    51,   447,   133,   133,   439,   133,
     441,   450,   453,   370,   462,   443,   464,   478,   479,   490,
     480,   133,   499,   379,   513,   523,   404,   134,   525,   134,
     527,   416,   581,   528,   534,   529,   530,   133,   426,   133,
     541,   133,   542,   543,   466,   467,   548,   567,   568,   547,
     570,   169,   170,   171,   313,   558,   173,   174,   175,   559,
     140,   560,   141,   283,   476,   283,   505,   484,   493,   524,
     562,   176,   177,   178,   179,   180,   181,   495,   496,   497,
     498,   183,   184,   185,   487,   261,   501,   350,   582,   133,
     133,   331,   134,   359,   137,   134,   583,   405,   133,   407,
     408,   214,   318,   404,   134,   319,   510,   511,   134,   134,
     571,   226,   377,   456,   509,   416,   341,     8,     0,     0,
       9,     0,     0,   134,   426,   134,     0,   134,   134,    10,
      53,     0,     0,     0,     0,   133,   133,     0,     0,     0,
     313,   313,    11,     0,     0,     0,   371,   313,     0,     0,
       0,   313,   313,     0,     0,     0,   383,     0,    59,    60,
      61,     0,   540,     0,     0,     0,    63,    64,     0,    65,
       0,    66,     0,    67,     0,     0,   550,   551,   552,    69,
     314,   555,     0,     0,     0,     0,     0,   540,   488,     0,
     489,   426,     0,     0,     0,     0,   569,     0,   494,    70,
      71,    72,    73,    74,    75,    12,     0,     0,     0,   502,
     503,     0,   504,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   426,     0,   313,   585,     0,
     313,     0,   134,     0,   134,   134,     0,     0,     0,     0,
     516,     0,   518,     0,   520,   313,     0,     0,   313,     0,
       0,     0,    -2,    18,   313,     0,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,   314,   314,     0,    29,
      30,    31,     0,   314,     0,     0,    18,   314,   314,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     0,
       0,     0,    29,    30,    31,     0,   315,     0,     0,     0,
       0,   553,     0,     0,     0,     0,   313,     0,   313,     2,
       0,     0,     0,   313,     0,   313,     0,     0,     0,     0,
       0,     0,   313,   134,   313,   134,   313,     0,     0,     0,
       0,     0,     2,   134,     0,     0,     0,     0,   576,   577,
       0,     0,     0,     0,   134,   134,     0,   134,     0,     0,
       0,   299,     0,   314,     0,     0,   314,     0,     0,   134,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   314,     0,     0,   314,   134,     0,   134,     0,   134,
     314,     0,   315,   315,     0,   313,     0,   313,   313,   315,
       0,     0,     0,   315,   315,   313,   313,   313,     0,     0,
       0,     0,     0,     0,     0,     0,   316,     0,     0,     0,
       0,     0,     0,   313,   313,     0,     0,   313,     0,     0,
       0,     0,     0,     0,   580,     0,   313,   134,   134,     0,
       0,     0,   314,     0,   314,     0,   134,     0,     0,   314,
       0,   314,     0,     0,   386,     0,     0,     0,   314,     0,
     314,     0,   314,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     0,     0,     0,    29,    30,    31,   315,
       0,     0,   315,   134,   134,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   315,     0,     0,
     315,     0,   316,   316,     0,     0,   315,     0,     0,   316,
       0,     0,     0,   316,   316,     0,     2,     0,     0,     0,
       0,   314,     0,   314,   314,     0,     0,     0,     0,     0,
       0,   314,   314,   314,   449,     0,     0,   449,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   314,
     314,     0,   449,   314,     0,   449,     0,     0,   315,     0,
     315,   474,   314,   169,     0,   315,     0,   315,   173,   174,
     175,     0,     0,     0,   315,     0,   315,     0,   315,     0,
       0,     0,     0,   176,   177,   178,   179,   180,   181,   316,
       0,     0,   316,   183,   184,   185,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   316,     0,     0,
     316,     0,     0,   506,     0,   508,   316,     0,     0,     0,
     512,   169,   514,   171,     0,     0,   173,   174,   175,   515,
       0,   517,     0,   519,     0,     0,     0,   315,     0,   315,
     315,   176,   177,   178,   179,   180,   181,   315,   315,   315,
       0,   183,   184,   185,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   315,   315,     0,   316,   315,
     316,     0,     0,     0,     0,   316,     0,   316,   315,     0,
       0,     0,     0,     0,   316,     0,   316,     0,   316,     0,
       0,   531,   554,     0,   556,   557,     0,     0,     0,     0,
     532,     0,   564,   565,   566,     0,   169,   170,   171,   172,
       0,   173,   174,   175,     0,     0,     0,     0,     0,     0,
     573,   574,     0,     0,   575,     0,   176,   177,   178,   179,
     180,   181,     0,   584,   182,     0,   183,   184,   185,     0,
       0,     0,     0,     0,     0,     0,     0,   316,     0,   316,
     316,     0,     0,     0,     0,     0,     0,   316,   316,   316,
       0,     0,     0,     0,     0,     0,     0,   372,     0,     8,
       0,     0,     9,     0,     0,   316,   316,     0,     0,   316,
       0,    10,    53,     0,     0,     0,     0,   286,   316,   287,
       0,   288,   289,   290,    11,   291,   292,   293,     0,   294,
       0,     0,   295,     0,     0,     0,     0,     0,     0,   296,
      59,    60,    61,     0,     0,     0,     0,     0,    63,    64,
       0,    65,     0,    66,     0,   297,     0,     0,     0,     0,
       0,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   375,   298,     8,     0,     0,
       9,    70,    71,    72,    73,    74,    75,    12,     0,    10,
      53,     0,     0,     0,     0,   286,     0,   287,     0,   288,
     289,   290,    11,   291,   292,   293,     0,   294,     0,     0,
     295,     0,     0,     0,     0,     0,     0,   296,    59,    60,
      61,     0,     0,     0,     0,     0,    63,    64,     0,    65,
       0,    66,     0,   297,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   390,   298,     8,     0,     0,     9,    70,
      71,    72,    73,    74,    75,    12,     0,    10,    53,     0,
       0,     0,     0,   286,     0,   287,     0,   288,   289,   290,
      11,   291,   292,   293,     0,   294,     0,     0,   295,     0,
       0,     0,     0,     0,     0,   296,    59,    60,    61,     0,
       0,     0,     0,     0,    63,    64,     0,    65,     0,    66,
       0,   297,     0,     0,     0,     0,     0,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   393,   298,     8,     0,     0,     9,    70,    71,    72,
      73,    74,    75,    12,     0,    10,    53,     0,     0,     0,
       0,   286,     0,   287,     0,   288,   289,   290,    11,   291,
     292,   293,     0,   294,     0,     0,   295,     0,     0,     0,
       0,     0,     0,   296,    59,    60,    61,     0,     0,     0,
       0,     0,    63,    64,     0,    65,     0,    66,     0,   297,
       0,     0,     0,     0,     0,    69,     0,   535,     0,     8,
       0,     0,     9,     0,     0,     0,     0,     0,     0,     0,
     298,    10,    53,     0,     0,    70,    71,    72,    73,    74,
      75,    12,    54,     0,    11,    55,    56,     0,     0,    57,
       0,     0,     0,     0,   536,     0,    58,     0,     0,     0,
      59,    60,    61,     0,     0,     0,     0,    62,    63,    64,
       0,    65,     0,    66,     0,    67,     0,     0,     0,   537,
      68,    69,     0,   160,     0,     8,     0,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,    10,    53,     0,
       0,    70,    71,    72,    73,    74,    75,    12,    54,     0,
      11,    55,    56,     0,     0,    57,     0,     0,     0,     0,
       0,     0,    58,     0,     0,     0,    59,    60,    61,     0,
       0,     0,     0,    62,    63,    64,     0,    65,     0,    66,
     161,    67,     0,     0,     0,     0,    68,    69,     0,   263,
       0,     8,     0,     0,     9,     0,     0,     0,     0,     0,
       0,     0,     0,    10,    53,     0,     0,    70,    71,    72,
      73,    74,    75,    12,    54,     0,    11,    55,    56,     0,
       0,    57,     0,     0,     0,     0,     0,     0,    58,     0,
       0,     0,    59,    60,    61,     0,     0,     0,     0,    62,
      63,    64,     0,    65,   264,    66,     0,    67,     0,     0,
       0,     0,    68,    69,     0,   268,     0,     8,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,    10,
      53,     0,     0,    70,    71,    72,    73,    74,    75,    12,
      54,     0,    11,    55,    56,     0,     0,    57,     0,     0,
       0,     0,     0,     0,    58,     0,     0,     0,    59,    60,
      61,     0,     0,     0,     0,    62,    63,    64,     0,    65,
     269,    66,     0,    67,     0,     0,     0,     0,    68,    69,
       0,   434,     0,     8,     0,     0,     9,     0,     0,     0,
       0,     0,     0,     0,     0,    10,    53,     0,     0,    70,
      71,    72,    73,    74,    75,    12,    54,     0,    11,    55,
      56,     0,     0,    57,     0,     0,     0,     0,     0,     0,
      58,     0,     0,     0,    59,    60,    61,     0,     0,     0,
       0,    62,    63,    64,     0,    65,   435,    66,     0,    67,
       0,     0,     0,     0,    68,    69,     0,   157,     0,     8,
       0,     0,     9,     0,     0,     0,     0,     0,     0,     0,
       0,    10,    53,     0,     0,    70,    71,    72,    73,    74,
      75,    12,    54,     0,    11,    55,    56,     0,     0,    57,
       0,     0,     0,     0,     0,     0,    58,     0,     0,     0,
      59,    60,    61,     0,     0,     0,     0,    62,    63,    64,
       0,    65,     0,    66,     0,    67,     0,     0,     0,     0,
      68,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     9,
       0,    70,    71,    72,    73,    74,    75,    12,    10,    53,
       0,     0,     0,     0,   286,   448,   287,     0,   288,   289,
     290,    11,   291,   292,   293,     0,   294,     0,     0,   295,
       0,     0,     0,     0,     0,     0,   296,    59,    60,    61,
       0,     0,     0,     0,     0,    63,    64,     0,    65,     0,
      66,     0,   297,     0,     0,     0,     0,     0,    69,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   298,     8,     0,     0,     9,    70,    71,
      72,    73,    74,    75,    12,     0,    10,    53,     0,     0,
       0,     0,   286,     0,   287,   451,   288,   289,   290,    11,
     291,   292,   293,     0,   294,     0,     0,   295,     0,     0,
       0,     0,     0,     0,   296,    59,    60,    61,     0,     0,
       0,     0,     0,    63,    64,     0,    65,     0,    66,     0,
     297,     0,     0,     0,     0,     0,    69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   298,     8,     0,     0,     9,    70,    71,    72,    73,
      74,    75,    12,     0,    10,    53,     0,     0,     0,     0,
     286,     0,   287,     0,   288,   289,   290,    11,   291,   292,
     293,     0,   294,     0,     0,   295,     0,     0,     0,     0,
       0,     0,   296,    59,    60,    61,     0,     0,     0,     0,
       0,    63,    64,     0,    65,     0,    66,     0,   297,   463,
       0,     0,     0,     0,    69,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   298,
       8,     0,     0,     9,    70,    71,    72,    73,    74,    75,
      12,     0,    10,    53,     0,     0,     0,     0,   286,     0,
     287,     0,   288,   289,   290,    11,   291,   292,   293,     0,
     294,     0,     0,   295,     0,     0,     0,     0,     0,     0,
     296,    59,    60,    61,     0,     0,     0,     0,     0,    63,
      64,     0,    65,     0,    66,     0,   297,     0,     0,     0,
       0,     0,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   298,   465,   173,
     174,   175,    70,    71,    72,    73,    74,    75,    12,     8,
       0,     0,     9,     0,   176,   177,   178,   179,   180,   181,
       0,    10,    53,     0,   183,   184,   185,   286,     0,   287,
       0,   288,   289,   290,    11,   291,   292,   293,     0,   294,
       0,     0,   295,     0,     0,     0,     0,     0,     0,   296,
      59,    60,    61,     0,     0,     0,     0,     0,    63,    64,
       0,    65,     0,    66,     0,   297,     0,     0,     0,     0,
       0,    69,     0,     0,     0,     8,     0,     0,     9,     0,
       0,     0,     0,     0,     0,     0,   298,    10,    53,     0,
       0,    70,    71,    72,    73,    74,    75,    12,    54,     0,
      11,    55,    56,     0,     0,    57,     0,     0,     0,     0,
     536,     0,    58,     0,     0,     0,    59,    60,    61,     0,
       0,     0,     0,    62,    63,    64,     0,    65,     0,    66,
       0,    67,   561,     0,     0,   537,    68,    69,     0,     0,
       0,     8,     0,     0,     9,     0,     0,     0,     0,     0,
       0,     0,     0,    10,    53,     0,     0,    70,    71,    72,
      73,    74,    75,    12,    54,     0,    11,    55,    56,     0,
       0,    57,     0,     0,     0,     0,     0,     0,    58,     0,
       0,     0,    59,    60,    61,     0,     0,     0,     0,    62,
      63,    64,     0,    65,     0,    66,     8,    67,     0,     9,
       0,     0,    68,    69,     0,     0,     0,     0,    10,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    11,     0,    70,    71,    72,    73,    74,    75,    12,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
       0,     0,     0,     0,     0,    63,    64,     0,   579,     0,
      66,     0,    67,   429,     0,     0,     0,     0,    69,     0,
       0,     0,     0,     0,     0,     0,     0,   193,   169,   170,
     171,   172,     0,   173,   174,   175,     0,     0,    70,    71,
      72,    73,    74,    75,    12,     0,   461,     0,   176,   177,
     178,   179,   180,   181,     0,     0,   182,     0,   183,   184,
     185,   169,   170,   171,   172,     0,   173,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   533,
       0,   176,   177,   178,   179,   180,   181,     0,     0,   182,
       0,   183,   184,   185,   169,   170,   171,   172,     0,   173,
     174,   175,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   572,     0,   176,   177,   178,   179,   180,   181,
       0,     0,   182,     0,   183,   184,   185,   169,   170,   171,
     172,     0,   173,   174,   175,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   176,   177,   178,
     179,   180,   181,   230,     0,   182,     0,   183,   184,   185,
       0,     0,     0,     0,     0,     0,   169,   170,   171,   172,
       0,   173,   174,   175,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   177,   178,   179,
     180,   181,   459,     0,   182,     0,   183,   184,   185,     0,
       0,     0,     0,     0,     0,   169,   170,   171,   172,     0,
     173,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   176,   177,   178,   179,   180,
     181,   430,     0,   182,     0,   183,   184,   185,     0,     0,
       0,     0,     0,   169,   170,   171,   172,     0,   173,   174,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,   178,   179,   180,   181,   460,
       0,   182,     0,   183,   184,   185,     0,     0,     0,   169,
     170,   171,   172,     0,   173,   174,   175,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,   178,   179,   180,   181,   428,     0,   182,     0,   183,
     184,   185,     0,   169,   170,   171,   172,     0,   173,   174,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,   178,   179,   180,   181,     0,
     431,   182,     0,   183,   184,   185,   169,   170,   171,   172,
       0,   173,   174,   175,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   177,   178,   179,
     180,   181,     0,     0,   182,     0,   183,   184,   185,   169,
     170,   171,   172,     0,   173,   174,   175,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,   178,   179,   180,   181,     0,     0,   182,     0,   183,
     184,   185,     0,     0,     0,   238,   169,   170,   171,   172,
       0,   173,   174,   175,     0,   234,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   177,   178,   179,
     180,   181,     0,     0,   182,     0,   183,   184,   185,   169,
     170,   171,   172,     0,   173,   174,   175,     0,   357,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,   178,   179,   180,   181,     0,     0,   182,     0,   183,
     184,   185,   169,   170,   171,   172,     0,   173,   174,   175,
       0,   432,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,   177,   178,   179,   180,   181,     0,     0,
     182,     0,   183,   184,   185,   169,   170,   171,   172,     0,
     173,   174,   175,     0,     0,     0,   433,     0,     0,     0,
       0,     0,     0,     0,     0,   176,   177,   178,   179,   180,
     181,     0,     0,   182,     0,   183,   184,   185,   169,   170,
     171,   172,     0,   173,   174,   175,     0,     0,     0,     0,
       0,     0,   563,     0,     0,     0,     0,     0,   176,   177,
     178,   179,   180,   181,     0,     0,   182,     0,   183,   184,
     185,   169,   170,   171,   172,     0,   173,   174,   175,     0,
       0,     0,     0,     0,   578,     0,     0,     0,     0,     0,
       0,   176,   177,   178,   179,   180,   181,     0,     0,   182,
       0,   183,   184,   185,   169,   170,   171,   172,     0,   173,
     174,   175,     0,   588,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,   177,   178,   179,   180,   181,
       0,     0,   182,     0,   183,   184,   185,   169,   170,   171,
     172,     0,   173,   174,   175,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   176,   177,   178,
     179,   180,   181,     0,     0,   182,     0,   183,   184,   185
  };

  const short
  Parser::yycheck_[] =
  {
       2,   222,   110,   423,    54,    56,    66,    58,    55,    42,
      58,    13,     5,     5,     7,    58,     4,     4,    20,    21,
      22,    23,    24,    66,    26,    27,    28,    29,     1,    31,
       3,    58,     1,     6,     3,    82,   325,     6,     5,    14,
       7,     3,    15,    13,    32,    32,    15,    16,     5,    82,
       7,     3,    54,    55,    56,    28,    58,    49,     1,    28,
       3,    49,    49,     6,    57,    67,    56,    60,    19,     1,
      28,     3,    15,    16,     6,     1,    66,     3,    55,    54,
       6,    64,     0,    15,    57,    28,    28,    42,    57,    15,
      57,     3,    13,    60,     6,    57,    28,    74,     3,    82,
      57,     6,    28,    15,   524,    57,    57,    62,    66,    60,
      15,    58,    28,   402,    57,   404,    28,    56,    91,   121,
     122,   123,    91,    28,    66,    57,     3,    66,   188,     6,
     190,     0,    56,    28,    19,     4,    57,     3,    15,    28,
       6,    62,    66,    55,    65,    66,   148,    59,    91,    15,
      66,    28,   122,    28,    59,    67,   148,     3,     3,    91,
       6,     6,    28,    32,     5,    91,     7,    28,   276,    15,
      15,    66,    57,    28,    55,   225,    60,    66,   228,    91,
      57,    55,    28,    28,   186,   187,    91,   189,    62,   191,
      54,    66,     5,    74,     7,   197,   198,   287,    82,   201,
     202,   203,   204,    56,   206,    66,    60,   297,   298,    58,
      74,    66,    66,    66,    91,   217,    57,   219,    55,   221,
     222,    87,    54,   225,    69,    91,   228,   197,    27,    28,
      29,   201,   453,    56,    69,    70,    71,    72,   240,   289,
     291,   292,    74,    66,    57,    91,    91,    60,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,    54,    54,    55,    61,    56,
      56,   192,   193,    61,    54,    55,    60,    62,    54,    66,
      66,   283,    66,   285,   205,    74,    74,   289,   290,   291,
     292,   283,   352,    62,    74,   297,    54,   218,    67,    60,
     521,   522,   223,   224,    73,    66,   227,    62,   229,   230,
     231,    54,   233,   283,    54,    60,   237,   238,    52,    53,
     241,    66,   121,    54,   326,   327,   328,   329,   197,    66,
      84,    68,   201,    67,    68,    69,    70,    71,    72,    61,
      54,    62,   330,   330,    78,    79,    67,    63,    64,    69,
      56,    69,    68,   274,    74,    19,    74,   327,    66,    23,
     362,    25,   364,    27,    28,    29,    30,    58,    61,   371,
      55,    74,    59,   294,   295,   296,    61,    59,   362,   371,
     364,   383,    66,    66,    59,    59,    72,   186,    55,    74,
     189,   383,   362,    56,   364,    56,    56,    54,    76,   198,
      76,    82,    56,   202,   203,    69,    54,   409,   410,    74,
      69,    54,   404,    52,    53,   417,   285,   419,   217,    74,
     219,   290,    74,    74,   416,   427,   414,   414,   416,   416,
      69,    70,    71,    72,   426,    22,   438,   439,    74,   441,
      74,    24,    61,   445,    60,   366,    81,    56,    60,    59,
      68,   453,    56,   455,    59,    68,   325,   121,    20,   123,
      54,   330,   570,    54,    35,    54,    74,   469,   337,   471,
      54,   473,    54,    54,   395,   396,    54,    74,    74,    59,
      59,    47,    48,    49,   200,    60,    52,    53,    54,    61,
      32,    61,    49,   362,   402,   364,   445,   414,   426,   490,
     538,    67,    68,    69,    70,    71,    72,   428,   429,   430,
     431,    77,    78,    79,   416,   187,   437,   240,   570,   521,
     522,   217,   186,   276,    30,   189,   571,   326,   530,   328,
     329,   123,   201,   402,   198,   201,   457,   458,   202,   203,
     553,   148,   289,   383,   455,   414,   225,     3,    -1,    -1,
       6,    -1,    -1,   217,   423,   219,    -1,   221,   222,    15,
      16,    -1,    -1,    -1,    -1,   567,   568,    -1,    -1,    -1,
     286,   287,    28,    -1,    -1,    -1,   445,   293,    -1,    -1,
      -1,   297,   298,    -1,    -1,    -1,   455,    -1,    44,    45,
      46,    -1,   513,    -1,    -1,    -1,    52,    53,    -1,    55,
      -1,    57,    -1,    59,    -1,    -1,   527,   528,   529,    65,
     200,   532,    -1,    -1,    -1,    -1,    -1,   538,   417,    -1,
     419,   490,    -1,    -1,    -1,    -1,   547,    -1,   427,    85,
      86,    87,    88,    89,    90,    91,    -1,    -1,    -1,   438,
     439,    -1,   441,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   524,    -1,   373,   579,    -1,
     376,    -1,   326,    -1,   328,   329,    -1,    -1,    -1,    -1,
     469,    -1,   471,    -1,   473,   391,    -1,    -1,   394,    -1,
      -1,    -1,     0,     1,   400,    -1,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   286,   287,    -1,    17,
      18,    19,    -1,   293,    -1,    -1,     1,   297,   298,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    17,    18,    19,    -1,   200,    -1,    -1,    -1,
      -1,   530,    -1,    -1,    -1,    -1,   452,    -1,   454,    57,
      -1,    -1,    -1,   459,    -1,   461,    -1,    -1,    -1,    -1,
      -1,    -1,   468,   417,   470,   419,   472,    -1,    -1,    -1,
      -1,    -1,    57,   427,    -1,    -1,    -1,    -1,   567,   568,
      -1,    -1,    -1,    -1,   438,   439,    -1,   441,    -1,    -1,
      -1,   200,    -1,   373,    -1,    -1,   376,    -1,    -1,   453,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   391,    -1,    -1,   394,   469,    -1,   471,    -1,   473,
     400,    -1,   286,   287,    -1,   531,    -1,   533,   534,   293,
      -1,    -1,    -1,   297,   298,   541,   542,   543,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,    -1,    -1,
      -1,    -1,    -1,   559,   560,    -1,    -1,   563,    -1,    -1,
      -1,    -1,    -1,    -1,   570,    -1,   572,   521,   522,    -1,
      -1,    -1,   452,    -1,   454,    -1,   530,    -1,    -1,   459,
      -1,   461,    -1,    -1,   293,    -1,    -1,    -1,   468,    -1,
     470,    -1,   472,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,    18,    19,   373,
      -1,    -1,   376,   567,   568,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   391,    -1,    -1,
     394,    -1,   286,   287,    -1,    -1,   400,    -1,    -1,   293,
      -1,    -1,    -1,   297,   298,    -1,    57,    -1,    -1,    -1,
      -1,   531,    -1,   533,   534,    -1,    -1,    -1,    -1,    -1,
      -1,   541,   542,   543,   373,    -1,    -1,   376,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   559,
     560,    -1,   391,   563,    -1,   394,    -1,    -1,   452,    -1,
     454,   400,   572,    47,    -1,   459,    -1,   461,    52,    53,
      54,    -1,    -1,    -1,   468,    -1,   470,    -1,   472,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,   373,
      -1,    -1,   376,    77,    78,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   391,    -1,    -1,
     394,    -1,    -1,   452,    -1,   454,   400,    -1,    -1,    -1,
     459,    47,   461,    49,    -1,    -1,    52,    53,    54,   468,
      -1,   470,    -1,   472,    -1,    -1,    -1,   531,    -1,   533,
     534,    67,    68,    69,    70,    71,    72,   541,   542,   543,
      -1,    77,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   559,   560,    -1,   452,   563,
     454,    -1,    -1,    -1,    -1,   459,    -1,   461,   572,    -1,
      -1,    -1,    -1,    -1,   468,    -1,   470,    -1,   472,    -1,
      -1,    32,   531,    -1,   533,   534,    -1,    -1,    -1,    -1,
      41,    -1,   541,   542,   543,    -1,    47,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
     559,   560,    -1,    -1,   563,    -1,    67,    68,    69,    70,
      71,    72,    -1,   572,    75,    -1,    77,    78,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   531,    -1,   533,
     534,    -1,    -1,    -1,    -1,    -1,    -1,   541,   542,   543,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,
      -1,    -1,     6,    -1,    -1,   559,   560,    -1,    -1,   563,
      -1,    15,    16,    -1,    -1,    -1,    -1,    21,   572,    23,
      -1,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,    53,
      -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    80,     3,    -1,    -1,
       6,    85,    86,    87,    88,    89,    90,    91,    -1,    15,
      16,    -1,    -1,    -1,    -1,    21,    -1,    23,    -1,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    55,
      -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    80,     3,    -1,    -1,     6,    85,
      86,    87,    88,    89,    90,    91,    -1,    15,    16,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    52,    53,    -1,    55,    -1,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    80,     3,    -1,    -1,     6,    85,    86,    87,
      88,    89,    90,    91,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    -1,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    52,    53,    -1,    55,    -1,    57,    -1,    59,
      -1,    -1,    -1,    -1,    -1,    65,    -1,     1,    -1,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    15,    16,    -1,    -1,    85,    86,    87,    88,    89,
      90,    91,    26,    -1,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    38,    -1,    40,    -1,    -1,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,    63,
      64,    65,    -1,     1,    -1,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    -1,
      -1,    85,    86,    87,    88,    89,    90,    91,    26,    -1,
      28,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    53,    -1,    55,    -1,    57,
      58,    59,    -1,    -1,    -1,    -1,    64,    65,    -1,     1,
      -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    -1,    -1,    85,    86,    87,
      88,    89,    90,    91,    26,    -1,    28,    29,    30,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    55,    56,    57,    -1,    59,    -1,    -1,
      -1,    -1,    64,    65,    -1,     1,    -1,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    -1,    -1,    85,    86,    87,    88,    89,    90,    91,
      26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    55,
      56,    57,    -1,    59,    -1,    -1,    -1,    -1,    64,    65,
      -1,     1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    85,
      86,    87,    88,    89,    90,    91,    26,    -1,    28,    29,
      30,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    51,    52,    53,    -1,    55,    56,    57,    -1,    59,
      -1,    -1,    -1,    -1,    64,    65,    -1,     1,    -1,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    16,    -1,    -1,    85,    86,    87,    88,    89,
      90,    91,    26,    -1,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,     6,
      -1,    85,    86,    87,    88,    89,    90,    91,    15,    16,
      -1,    -1,    -1,    -1,    21,    22,    23,    -1,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    55,    -1,
      57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,     3,    -1,    -1,     6,    85,    86,
      87,    88,    89,    90,    91,    -1,    15,    16,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    52,    53,    -1,    55,    -1,    57,    -1,
      59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,     3,    -1,    -1,     6,    85,    86,    87,    88,
      89,    90,    91,    -1,    15,    16,    -1,    -1,    -1,    -1,
      21,    -1,    23,    -1,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    52,    53,    -1,    55,    -1,    57,    -1,    59,    60,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
       3,    -1,    -1,     6,    85,    86,    87,    88,    89,    90,
      91,    -1,    15,    16,    -1,    -1,    -1,    -1,    21,    -1,
      23,    -1,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,
      53,    -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    52,
      53,    54,    85,    86,    87,    88,    89,    90,    91,     3,
      -1,    -1,     6,    -1,    67,    68,    69,    70,    71,    72,
      -1,    15,    16,    -1,    77,    78,    79,    21,    -1,    23,
      -1,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,    53,
      -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    15,    16,    -1,
      -1,    85,    86,    87,    88,    89,    90,    91,    26,    -1,
      28,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      38,    -1,    40,    -1,    -1,    -1,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    53,    -1,    55,    -1,    57,
      -1,    59,    60,    -1,    -1,    63,    64,    65,    -1,    -1,
      -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    -1,    -1,    85,    86,    87,
      88,    89,    90,    91,    26,    -1,    28,    29,    30,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    55,    -1,    57,     3,    59,    -1,     6,
      -1,    -1,    64,    65,    -1,    -1,    -1,    -1,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    85,    86,    87,    88,    89,    90,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    55,    -1,
      57,    -1,    59,    32,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    -1,    85,    86,
      87,    88,    89,    90,    91,    -1,    32,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,    75,    -1,    77,    78,
      79,    47,    48,    49,    50,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    67,    68,    69,    70,    71,    72,    -1,    -1,    75,
      -1,    77,    78,    79,    47,    48,    49,    50,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    67,    68,    69,    70,    71,    72,
      -1,    -1,    75,    -1,    77,    78,    79,    47,    48,    49,
      50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    34,    -1,    75,    -1,    77,    78,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    34,    -1,    75,    -1,    77,    78,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    35,    -1,    75,    -1,    77,    78,    79,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    37,
      -1,    75,    -1,    77,    78,    79,    -1,    -1,    -1,    47,
      48,    49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    72,    39,    -1,    75,    -1,    77,
      78,    79,    -1,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      41,    75,    -1,    77,    78,    79,    47,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    -1,    -1,    75,    -1,    77,    78,    79,    47,
      48,    49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    72,    -1,    -1,    75,    -1,    77,
      78,    79,    -1,    -1,    -1,    83,    47,    48,    49,    50,
      -1,    52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    -1,    -1,    75,    -1,    77,    78,    79,    47,
      48,    49,    50,    -1,    52,    53,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    72,    -1,    -1,    75,    -1,    77,
      78,    79,    47,    48,    49,    50,    -1,    52,    53,    54,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    -1,    -1,
      75,    -1,    77,    78,    79,    47,    48,    49,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    -1,    -1,    75,    -1,    77,    78,    79,    47,    48,
      49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,    75,    -1,    77,    78,
      79,    47,    48,    49,    50,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,    -1,    -1,    75,
      -1,    77,    78,    79,    47,    48,    49,    50,    -1,    52,
      53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      -1,    -1,    75,    -1,    77,    78,    79,    47,    48,    49,
      50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    -1,    -1,    75,    -1,    77,    78,    79
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    57,    98,    99,   206,   207,     1,     3,     6,
      15,    28,    91,   193,   208,   209,   210,     0,     1,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    17,
      18,    19,   100,   101,   102,   103,   104,   105,   106,   107,
     110,   111,   112,   113,   114,   117,   120,   124,   125,   206,
       3,   207,    58,    16,    26,    29,    30,    33,    40,    44,
      45,    46,    51,    52,    53,    55,    57,    59,    64,    65,
      85,    86,    87,    88,    89,    90,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   193,   194,   198,    58,    58,    58,
      59,   193,   194,   193,   193,   193,   193,   194,   193,   194,
     193,    55,    59,    67,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   193,   194,   178,   178,   183,   194,   193,
     101,   102,   193,   195,   198,   199,   201,   202,   206,   196,
     199,   196,   145,   196,   145,   146,   146,     1,   144,   145,
       1,    58,   144,   145,   173,   174,   193,   146,   194,    47,
      48,    49,    50,    52,    53,    54,    67,    68,    69,    70,
      71,    72,    75,    77,    78,    79,    42,    82,    55,    61,
      55,    62,    55,    74,   171,   175,   176,    55,    74,    54,
      54,    55,    74,    54,    62,    54,    42,    54,   177,   178,
     193,   197,   198,   178,   187,    54,    84,    67,    73,    14,
      54,    67,    61,    54,    28,    66,   195,    28,    66,    28,
      34,    28,    56,    66,    56,    58,    58,    66,    83,    60,
      66,    61,    64,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     178,   163,   193,     1,    56,   144,   145,   178,     1,    56,
     144,   193,   145,   145,    74,    60,    66,     1,    16,   189,
     190,   198,   200,   206,   178,    59,    21,    23,    25,    26,
      27,    29,    30,    31,    33,    36,    43,    59,    80,   128,
     129,   130,   131,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   146,   148,   149,   150,     1,   189,   190,
     178,   178,    69,   145,   193,    59,    66,    66,    69,    74,
      59,   177,   178,   187,   188,   145,   178,    59,   188,   145,
     145,   202,   145,   199,   145,   145,   145,   145,   145,   145,
     174,   145,    55,    56,    56,    56,    56,    56,   145,   176,
      56,    56,    66,    56,    66,   198,    54,     1,   108,   109,
     193,   206,     1,   127,   128,     1,   127,   201,     1,   193,
     203,   204,   205,   206,   196,   196,   128,   145,   145,   145,
       1,   127,   193,     1,   127,    76,    76,    56,    56,    56,
      54,   107,   115,   116,   206,   178,   198,   178,   178,     5,
       7,   105,   106,   118,   119,   126,   206,    66,    68,    74,
      54,   105,   106,   121,   122,   123,   206,    74,    39,    32,
      35,    41,    56,    58,     1,    56,   144,    74,    74,    74,
     200,    74,   200,   145,    60,    66,   193,    22,    22,   128,
      24,    24,    28,    61,    28,    66,   205,    28,    28,    34,
      37,    32,    60,    60,    81,    81,   145,   145,    54,    74,
      54,    74,    54,    74,   128,    60,   116,   107,    56,    60,
      68,   193,   193,    60,   118,   105,   106,   126,   178,   178,
      59,    60,   122,   123,   178,   145,   145,   145,   145,    56,
      56,   145,   178,   178,   178,   108,   128,   188,   128,   204,
     145,   145,   128,    59,   128,   128,   178,   128,   178,   128,
     178,    61,    61,    68,   121,    20,   191,    54,    54,    54,
      74,    32,    41,    32,    35,     1,    38,    63,   132,   133,
     145,    54,    54,    54,   188,   188,    60,    59,    54,   192,
     145,   145,   145,   178,   128,   145,   128,   128,    60,    61,
      61,    60,   133,    61,   128,   128,   128,    74,    74,   145,
      59,   191,    32,   128,   128,   128,   178,   178,    60,    55,
     146,   171,   175,   192,   128,   145,    60,    60,    56
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
     193,   194,   194,   195,   195,   196,   196,   197,   197,   198,
     199,   199,   200,   200,   201,   201,   202,   203,   203,   204,
     204,   204,   205,   206,   206,   207,   207,   207,   207,   208,
     209,   210
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
       1,     3,     1,     1,     1,     3,     1,     3,     1,     3,
       2,     1,     2,     1,     3,     1,     3,     3,     1,     2,
       1,     1,     7,     2,     1,     3,     3,     3,     3,     1,
       2,     2
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
    1386,  1390,  1395,  1399,  1407,  1412,  1419,  1425,  1433,  1441,
    1448,  1454,  1462,  1470,  1478,  1486,  1494,  1502,  1510,  1522,
    1526,  1530,  1534,  1538,  1542,  1546,  1550,  1558,  1562,  1566,
    1570,  1578,  1587,  1593,  1603,  1611,  1619,  1627,  1631,  1639,
    1647,  1676,  1683,  1689,  1697,  1707,  1720,  1734,  1741,  1750,
    1757,  1764,  1773,  1778,  1784,  1800,  1807,  1816,  1820,  1824,
    1828,  1832,  1836,  1840,  1844,  1852,  1860,  1871,  1882,  1890,
    1898,  1906,  1914,  1926,  1933,  1943,  1947,  1955,  1962,  1975,
    1982,  1996,  2000,  2008,  2014,  2027,  2040,  2044,  2049,  2054,
    2059,  2068,  2075,  2087,  2091,  2100,  2107,  2117,  2124,  2134,
    2143,  2149,  2157,  2163,  2175,  2182,  2191,  2203,  2210,  2219,
    2225,  2229,  2236,  2249,  2255,  2264,  2271,  2278,  2285,  2292,
    2299,  2306
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
#line 6758 "GrammarParser.cpp"

#line 2312 "../../obj/src/GrammarParser.y"


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
