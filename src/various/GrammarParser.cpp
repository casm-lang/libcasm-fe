// A Bison parser, made by GNU Bison 3.8.2.

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
#line 88 "../../obj/src/GrammarParser.y"

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

#line 47 "../../obj/src/GrammarParser.y"
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

  /*---------.
  | symbol.  |
  `---------*/



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
      case symbol_kind::S_MATCH: // "match"
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

      case symbol_kind::S_MatchArm: // MatchArm
        value.YY_MOVE_OR_COPY< MatchArm::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MatchArms: // MatchArms
        value.YY_MOVE_OR_COPY< MatchArms::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MatchExpression: // MatchExpression
        value.YY_MOVE_OR_COPY< MatchExpression::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_MATCH: // "match"
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

      case symbol_kind::S_MatchArm: // MatchArm
        value.move< MatchArm::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MatchArms: // MatchArms
        value.move< MatchArms::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MatchExpression: // MatchExpression
        value.move< MatchExpression::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_MATCH: // "match"
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

      case symbol_kind::S_MatchArm: // MatchArm
        value.copy< MatchArm::Ptr > (that.value);
        break;

      case symbol_kind::S_MatchArms: // MatchArms
        value.copy< MatchArms::Ptr > (that.value);
        break;

      case symbol_kind::S_MatchExpression: // MatchExpression
        value.copy< MatchExpression::Ptr > (that.value);
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
      case symbol_kind::S_MATCH: // "match"
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

      case symbol_kind::S_MatchArm: // MatchArm
        value.move< MatchArm::Ptr > (that.value);
        break;

      case symbol_kind::S_MatchArms: // MatchArms
        value.move< MatchArms::Ptr > (that.value);
        break;

      case symbol_kind::S_MatchExpression: // MatchExpression
        value.move< MatchExpression::Ptr > (that.value);
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
  Parser::yypop_ (int n) YY_NOEXCEPT
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
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
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
      case symbol_kind::S_MATCH: // "match"
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

      case symbol_kind::S_MatchArm: // MatchArm
        yylhs.value.emplace< MatchArm::Ptr > ();
        break;

      case symbol_kind::S_MatchArms: // MatchArms
        yylhs.value.emplace< MatchArms::Ptr > ();
        break;

      case symbol_kind::S_MatchExpression: // MatchExpression
        yylhs.value.emplace< MatchExpression::Ptr > ();
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
#line 446 "../../obj/src/GrammarParser.y"
  {
      const auto& cst = CST::make< CST::Root >(
          yylhs.location, yystack_[1].value.as < HeaderDefinition::Ptr > (), yystack_[0].value.as < Definitions::Ptr > (), m_lexer.fetchSpansAndReset() );
      m_specification.setCst( cst );
  }
#line 2966 "GrammarParser.cpp"
    break;

  case 3: // Header: Attributes "CASM"
#line 456 "../../obj/src/GrammarParser.y"
  {
      auto definition = CST::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2976 "GrammarParser.cpp"
    break;

  case 4: // Header: "CASM"
#line 462 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = CST::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 2984 "GrammarParser.cpp"
    break;

  case 5: // Definitions: Definitions AttributedDefinition
#line 470 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2994 "GrammarParser.cpp"
    break;

  case 6: // Definitions: AttributedDefinition
#line 476 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3004 "GrammarParser.cpp"
    break;

  case 7: // AttributedDefinition: Attributes Definition
#line 486 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3014 "GrammarParser.cpp"
    break;

  case 8: // AttributedDefinition: Definition
#line 492 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 3022 "GrammarParser.cpp"
    break;

  case 9: // AttributedDefinition: error
#line 496 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 3030 "GrammarParser.cpp"
    break;

  case 10: // Definition: InitDefinition
#line 504 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 3038 "GrammarParser.cpp"
    break;

  case 11: // Definition: EnumerationDefinition
#line 508 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 3046 "GrammarParser.cpp"
    break;

  case 12: // Definition: DerivedDefinition
#line 512 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3054 "GrammarParser.cpp"
    break;

  case 13: // Definition: RuleDefinition
#line 516 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3062 "GrammarParser.cpp"
    break;

  case 14: // Definition: FunctionDefinition
#line 520 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 3070 "GrammarParser.cpp"
    break;

  case 15: // Definition: UsingDefinition
#line 524 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 3078 "GrammarParser.cpp"
    break;

  case 16: // Definition: UsingPathDefinition
#line 528 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 3086 "GrammarParser.cpp"
    break;

  case 17: // Definition: InvariantDefinition
#line 532 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 3094 "GrammarParser.cpp"
    break;

  case 18: // Definition: ImportDefinition
#line 536 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 3102 "GrammarParser.cpp"
    break;

  case 19: // Definition: StructureDefinition
#line 540 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < StructureDefinition::Ptr > ();
  }
#line 3110 "GrammarParser.cpp"
    break;

  case 20: // Definition: BehaviorDefinition
#line 544 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < BehaviorDefinition::Ptr > ();
  }
#line 3118 "GrammarParser.cpp"
    break;

  case 21: // Definition: ImplementDefinition
#line 548 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImplementDefinition::Ptr > ();
  }
#line 3126 "GrammarParser.cpp"
    break;

  case 22: // Definition: DomainDefinition
#line 552 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DomainDefinition::Ptr > ();
  }
#line 3134 "GrammarParser.cpp"
    break;

  case 23: // Definition: BuiltinDefinition
#line 556 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < BuiltinDefinition::Ptr > ();
  }
#line 3142 "GrammarParser.cpp"
    break;

  case 24: // InitDefinition: "init" IdentifierPath
#line 564 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = CST::make< InitDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3150 "GrammarParser.cpp"
    break;

  case 25: // InitDefinition: "init" "{" MappedExpressions "}"
#line 568 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = CST::make< InitDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < MappedExpressions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3158 "GrammarParser.cpp"
    break;

  case 26: // EnumerationDefinition: "enumeration" Identifier "=" "{" Enumerators "}"
#line 576 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = CST::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3166 "GrammarParser.cpp"
    break;

  case 27: // DerivedDefinition: "derived" Identifier "->" Type "=" Term
#line 584 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3175 "GrammarParser.cpp"
    break;

  case 28: // DerivedDefinition: "derived" Identifier "(" Parameters ")" "->" Type "=" Term
#line 589 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3185 "GrammarParser.cpp"
    break;

  case 29: // DerivedDefinition: "derived" Identifier "(" MethodParameters ")" "->" Type "=" Term
#line 595 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3195 "GrammarParser.cpp"
    break;

  case 30: // DerivedDefinition: "derived" Identifier "(" error ")" "->" Type "=" Term
#line 601 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 3203 "GrammarParser.cpp"
    break;

  case 31: // RuleDefinition: "rule" Identifier "=" Rule
#line 609 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3213 "GrammarParser.cpp"
    break;

  case 32: // RuleDefinition: "rule" Identifier "->" Type "=" Rule
#line 615 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3222 "GrammarParser.cpp"
    break;

  case 33: // RuleDefinition: "rule" Identifier "(" Parameters ")" "=" Rule
#line 620 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < CST::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
  }
#line 3233 "GrammarParser.cpp"
    break;

  case 34: // RuleDefinition: "rule" Identifier "(" Parameters ")" "->" Type "=" Rule
#line 627 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3243 "GrammarParser.cpp"
    break;

  case 35: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "=" Rule
#line 633 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < CST::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
  }
#line 3254 "GrammarParser.cpp"
    break;

  case 36: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "->" Type "=" Rule
#line 640 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3264 "GrammarParser.cpp"
    break;

  case 37: // RuleDefinition: "rule" Identifier "(" error ")" "=" Rule
#line 646 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3272 "GrammarParser.cpp"
    break;

  case 38: // RuleDefinition: "rule" Identifier "(" error ")" "->" Type "=" Rule
#line 650 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3280 "GrammarParser.cpp"
    break;

  case 39: // FunctionDefinition: "function" Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 658 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = CST::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < CST::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
  }
#line 3288 "GrammarParser.cpp"
    break;

  case 40: // EnumeratorDefinition: Identifier
#line 666 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = CST::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3296 "GrammarParser.cpp"
    break;

  case 41: // EnumeratorDefinition: Attributes Identifier
#line 670 "../../obj/src/GrammarParser.y"
  {
      auto enumerator = CST::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 3306 "GrammarParser.cpp"
    break;

  case 42: // EnumeratorDefinition: error
#line 676 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 3314 "GrammarParser.cpp"
    break;

  case 43: // Enumerators: Enumerators "," EnumeratorDefinition
#line 684 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3325 "GrammarParser.cpp"
    break;

  case 44: // Enumerators: EnumeratorDefinition
#line 691 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = CST::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3335 "GrammarParser.cpp"
    break;

  case 45: // UsingDefinition: "using" Identifier "=" Type
#line 701 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingDefinition::Ptr > () = CST::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3343 "GrammarParser.cpp"
    break;

  case 46: // UsingPathDefinition: "using" IdentifierPath
#line 709 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = CST::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3351 "GrammarParser.cpp"
    break;

  case 47: // UsingPathDefinition: "using" IdentifierPath "::" "*"
#line 713 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = CST::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3359 "GrammarParser.cpp"
    break;

  case 48: // InvariantDefinition: "invariant" Identifier "=" Term
#line 721 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = CST::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3367 "GrammarParser.cpp"
    break;

  case 49: // ImportDefinition: "import" IdentifierPath
#line 729 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = CST::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3375 "GrammarParser.cpp"
    break;

  case 50: // ImportDefinition: "import" IdentifierPath "as" Identifier
#line 733 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = CST::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3383 "GrammarParser.cpp"
    break;

  case 51: // StructureDefinition: "structure" Identifier "=" "{" StructureDefinitionList "}"
#line 745 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < StructureDefinition::Ptr > () = CST::make< StructureDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < FunctionDefinitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3391 "GrammarParser.cpp"
    break;

  case 52: // StructureDefinitionList: StructureDefinitionList StructureDefinitionElement
#line 752 "../../obj/src/GrammarParser.y"
  {
      auto functions = yystack_[1].value.as < FunctionDefinitions::Ptr > ();
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3401 "GrammarParser.cpp"
    break;

  case 53: // StructureDefinitionList: StructureDefinitionElement
#line 758 "../../obj/src/GrammarParser.y"
  {
      auto functions = CST::make< FunctionDefinitions >( yylhs.location );
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3411 "GrammarParser.cpp"
    break;

  case 54: // StructureDefinitionElement: Attributes FunctionDefinition
#line 767 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 3421 "GrammarParser.cpp"
    break;

  case 55: // StructureDefinitionElement: FunctionDefinition
#line 773 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 3429 "GrammarParser.cpp"
    break;

  case 56: // BehaviorDefinition: "behavior" Type "=" "{" BehaviorDefinitionList "}"
#line 785 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BehaviorDefinition::Ptr > () = CST::make< BehaviorDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3437 "GrammarParser.cpp"
    break;

  case 57: // BehaviorDefinitionElement: Attributes Declaration
#line 793 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Declaration::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3447 "GrammarParser.cpp"
    break;

  case 58: // BehaviorDefinitionElement: Declaration
#line 799 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Declaration::Ptr > ();
  }
#line 3455 "GrammarParser.cpp"
    break;

  case 59: // BehaviorDefinitionElement: Attributes DerivedDefinition
#line 803 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DerivedDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3465 "GrammarParser.cpp"
    break;

  case 60: // BehaviorDefinitionElement: DerivedDefinition
#line 809 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3473 "GrammarParser.cpp"
    break;

  case 61: // BehaviorDefinitionElement: Attributes RuleDefinition
#line 813 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < RuleDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3483 "GrammarParser.cpp"
    break;

  case 62: // BehaviorDefinitionElement: RuleDefinition
#line 819 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3491 "GrammarParser.cpp"
    break;

  case 63: // BehaviorDefinitionList: BehaviorDefinitionList BehaviorDefinitionElement
#line 826 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3501 "GrammarParser.cpp"
    break;

  case 64: // BehaviorDefinitionList: BehaviorDefinitionElement
#line 832 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3511 "GrammarParser.cpp"
    break;

  case 65: // ImplementDefinition: "implement" Type "=" "{" ImplementDefinitionList "}"
#line 846 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = CST::make< ImplementDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3519 "GrammarParser.cpp"
    break;

  case 66: // ImplementDefinition: "implement" Type "for" Type "=" "{" ImplementDefinitionList "}"
#line 850 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = CST::make< ImplementDefinition >( yylhs.location, yystack_[7].value.as < CST::Token::Ptr > (), yystack_[6].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3527 "GrammarParser.cpp"
    break;

  case 67: // ImplementDefinitionList: ImplementDefinitionList ImplementDefinitionElement
#line 857 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3537 "GrammarParser.cpp"
    break;

  case 68: // ImplementDefinitionList: ImplementDefinitionElement
#line 863 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3547 "GrammarParser.cpp"
    break;

  case 69: // ImplementDefinitionElement: Attributes ImplementDefinitionAttributedElement
#line 872 "../../obj/src/GrammarParser.y"
  {
      const auto& definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3557 "GrammarParser.cpp"
    break;

  case 70: // ImplementDefinitionElement: ImplementDefinitionAttributedElement
#line 878 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 3565 "GrammarParser.cpp"
    break;

  case 71: // ImplementDefinitionAttributedElement: DerivedDefinition
#line 885 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3573 "GrammarParser.cpp"
    break;

  case 72: // ImplementDefinitionAttributedElement: RuleDefinition
#line 889 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3581 "GrammarParser.cpp"
    break;

  case 73: // DomainDefinition: "domain" Type
#line 901 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DomainDefinition::Ptr > () = CST::make< DomainDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3589 "GrammarParser.cpp"
    break;

  case 74: // BuiltinDefinition: "builtin" RelationType
#line 913 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BuiltinDefinition::Ptr > () = CST::make< BuiltinDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < RelationType::Ptr > () );
  }
#line 3597 "GrammarParser.cpp"
    break;

  case 75: // Declaration: "derived" Identifier ":" MaybeFunctionParameters "->" Type
#line 925 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = CST::make< Declaration >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3605 "GrammarParser.cpp"
    break;

  case 76: // Declaration: "rule" Identifier ":" MaybeFunctionParameters "->" Type
#line 929 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = CST::make< Declaration >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3613 "GrammarParser.cpp"
    break;

  case 77: // Rules: Rules Rule
#line 941 "../../obj/src/GrammarParser.y"
  {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3623 "GrammarParser.cpp"
    break;

  case 78: // Rules: Rule
#line 947 "../../obj/src/GrammarParser.y"
  {
      auto rules = CST::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3633 "GrammarParser.cpp"
    break;

  case 79: // Rule: SkipRule
#line 957 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 3641 "GrammarParser.cpp"
    break;

  case 80: // Rule: ConditionalRule
#line 961 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 3649 "GrammarParser.cpp"
    break;

  case 81: // Rule: CaseRule
#line 965 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 3657 "GrammarParser.cpp"
    break;

  case 82: // Rule: LetRule
#line 969 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 3665 "GrammarParser.cpp"
    break;

  case 83: // Rule: LocalRule
#line 973 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LocalRule::Ptr > ();
  }
#line 3673 "GrammarParser.cpp"
    break;

  case 84: // Rule: ForallRule
#line 977 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 3681 "GrammarParser.cpp"
    break;

  case 85: // Rule: ChooseRule
#line 981 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 3689 "GrammarParser.cpp"
    break;

  case 86: // Rule: IterateRule
#line 985 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 3697 "GrammarParser.cpp"
    break;

  case 87: // Rule: BlockRule
#line 989 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 3705 "GrammarParser.cpp"
    break;

  case 88: // Rule: SequenceRule
#line 993 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 3713 "GrammarParser.cpp"
    break;

  case 89: // Rule: UpdateRule
#line 997 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 3721 "GrammarParser.cpp"
    break;

  case 90: // Rule: CallRule
#line 1001 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 3729 "GrammarParser.cpp"
    break;

  case 91: // Rule: WhileRule
#line 1005 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 3737 "GrammarParser.cpp"
    break;

  case 92: // SkipRule: "skip"
#line 1013 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SkipRule::Ptr > () = CST::make< SkipRule >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3745 "GrammarParser.cpp"
    break;

  case 93: // ConditionalRule: "if" Term "then" Rule
#line 1021 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = CST::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3753 "GrammarParser.cpp"
    break;

  case 94: // ConditionalRule: "if" Term "then" Rule "else" Rule
#line 1025 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = CST::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3761 "GrammarParser.cpp"
    break;

  case 95: // CaseRule: "case" Term "of" "{" CaseLabels "}"
#line 1033 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = CST::make< CaseRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3769 "GrammarParser.cpp"
    break;

  case 96: // CaseRule: "case" Term "of" "{" error "}"
#line 1037 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 3777 "GrammarParser.cpp"
    break;

  case 97: // CaseLabels: CaseLabels CaseLabel
#line 1045 "../../obj/src/GrammarParser.y"
  {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3787 "GrammarParser.cpp"
    break;

  case 98: // CaseLabels: CaseLabel
#line 1051 "../../obj/src/GrammarParser.y"
  {
      auto cases = CST::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3797 "GrammarParser.cpp"
    break;

  case 99: // CaseLabel: "default" ":" Rule
#line 1061 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< DefaultCase >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3805 "GrammarParser.cpp"
    break;

  case 100: // CaseLabel: "_" ":" Rule
#line 1065 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< DefaultCase >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3813 "GrammarParser.cpp"
    break;

  case 101: // CaseLabel: Term ":" Rule
#line 1069 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3821 "GrammarParser.cpp"
    break;

  case 102: // LetRule: "let" VariableBindings "in" Rule
#line 1077 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = CST::make< LetRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3829 "GrammarParser.cpp"
    break;

  case 103: // LocalRule: "local" LocalFunctionDefinitions "in" Rule
#line 1085 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LocalRule::Ptr > () = CST::make< LocalRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < FunctionDefinitions::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3837 "GrammarParser.cpp"
    break;

  case 104: // ForallRule: "forall" AttributedVariables "in" Term "do" Rule
#line 1093 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = CST::make< ForallRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3845 "GrammarParser.cpp"
    break;

  case 105: // ForallRule: "forall" AttributedVariables "in" Term "with" Term "do" Rule
#line 1097 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = CST::make< ForallRule >( yylhs.location, yystack_[7].value.as < CST::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3853 "GrammarParser.cpp"
    break;

  case 106: // ChooseRule: "choose" AttributedVariables "in" Term "do" Rule
#line 1105 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = CST::make< ChooseRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3861 "GrammarParser.cpp"
    break;

  case 107: // IterateRule: "iterate" Rule
#line 1113 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = CST::make< IterateRule >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3869 "GrammarParser.cpp"
    break;

  case 108: // BlockRule: "{" Rules "}"
#line 1121 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = CST::make< BlockRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3877 "GrammarParser.cpp"
    break;

  case 109: // BlockRule: "par" Rules "endpar"
#line 1125 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = CST::make< BlockRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3885 "GrammarParser.cpp"
    break;

  case 110: // BlockRule: "{" error "}"
#line 1129 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3894 "GrammarParser.cpp"
    break;

  case 111: // BlockRule: "par" error "endpar"
#line 1134 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3903 "GrammarParser.cpp"
    break;

  case 112: // SequenceRule: "{|" Rules "|}"
#line 1143 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = CST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3911 "GrammarParser.cpp"
    break;

  case 113: // SequenceRule: "seq" Rules "endseq"
#line 1147 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = CST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3919 "GrammarParser.cpp"
    break;

  case 114: // SequenceRule: "{|" error "|}"
#line 1151 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3928 "GrammarParser.cpp"
    break;

  case 115: // SequenceRule: "seq" error "endseq"
#line 1156 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3937 "GrammarParser.cpp"
    break;

  case 116: // UpdateRule: DirectCallExpression ":=" Term
#line 1165 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = CST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3945 "GrammarParser.cpp"
    break;

  case 117: // UpdateRule: MethodCallExpression ":=" Term
#line 1169 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = CST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < MethodCallExpression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3953 "GrammarParser.cpp"
    break;

  case 118: // CallRule: CallExpression
#line 1177 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = CST::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 3961 "GrammarParser.cpp"
    break;

  case 119: // WhileRule: "while" Term "do" Rule
#line 1185 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = CST::make< WhileRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3969 "GrammarParser.cpp"
    break;

  case 120: // Terms: Terms "," Term
#line 1197 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3980 "GrammarParser.cpp"
    break;

  case 121: // Terms: Term
#line 1204 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = CST::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3990 "GrammarParser.cpp"
    break;

  case 122: // Term: Expression
#line 1214 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3998 "GrammarParser.cpp"
    break;

  case 123: // Term: TypeCastingExpression
#line 1218 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 4006 "GrammarParser.cpp"
    break;

  case 124: // Term: OperatorExpression
#line 1222 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 4014 "GrammarParser.cpp"
    break;

  case 125: // Term: LetExpression
#line 1226 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 4022 "GrammarParser.cpp"
    break;

  case 126: // Term: ConditionalExpression
#line 1230 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 4030 "GrammarParser.cpp"
    break;

  case 127: // Term: ChooseExpression
#line 1234 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 4038 "GrammarParser.cpp"
    break;

  case 128: // Term: UniversalQuantifierExpression
#line 1238 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 4046 "GrammarParser.cpp"
    break;

  case 129: // Term: ExistentialQuantifierExpression
#line 1242 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 4054 "GrammarParser.cpp"
    break;

  case 130: // Term: CardinalityExpression
#line 1246 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 4062 "GrammarParser.cpp"
    break;

  case 131: // Term: MatchExpression
#line 1250 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < MatchExpression::Ptr > ();
  }
#line 4070 "GrammarParser.cpp"
    break;

  case 132: // Expression: "(" Term ")"
#line 1258 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< CST::EmbracedExpression >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4078 "GrammarParser.cpp"
    break;

  case 133: // Expression: "(" error ")"
#line 1262 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 4086 "GrammarParser.cpp"
    break;

  case 134: // Expression: CallExpression
#line 1266 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 4094 "GrammarParser.cpp"
    break;

  case 135: // Expression: LiteralCallExpression
#line 1270 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 4102 "GrammarParser.cpp"
    break;

  case 136: // Expression: Literal
#line 1274 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 4110 "GrammarParser.cpp"
    break;

  case 137: // Expression: "+" Expression
#line 1278 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4118 "GrammarParser.cpp"
    break;

  case 138: // Expression: "-" Expression
#line 1282 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4126 "GrammarParser.cpp"
    break;

  case 139: // OperatorExpression: Term "+" Term
#line 1294 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4134 "GrammarParser.cpp"
    break;

  case 140: // OperatorExpression: Term "-" Term
#line 1298 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4142 "GrammarParser.cpp"
    break;

  case 141: // OperatorExpression: Term "*" Term
#line 1302 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4150 "GrammarParser.cpp"
    break;

  case 142: // OperatorExpression: Term "/" Term
#line 1306 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4158 "GrammarParser.cpp"
    break;

  case 143: // OperatorExpression: Term "%" Term
#line 1310 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4166 "GrammarParser.cpp"
    break;

  case 144: // OperatorExpression: Term "^" Term
#line 1314 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4174 "GrammarParser.cpp"
    break;

  case 145: // OperatorExpression: Term "!=" Term
#line 1318 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4182 "GrammarParser.cpp"
    break;

  case 146: // OperatorExpression: Term "=" Term
#line 1322 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4190 "GrammarParser.cpp"
    break;

  case 147: // OperatorExpression: Term "<" Term
#line 1326 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4198 "GrammarParser.cpp"
    break;

  case 148: // OperatorExpression: Term ">" Term
#line 1330 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4206 "GrammarParser.cpp"
    break;

  case 149: // OperatorExpression: Term "<=" Term
#line 1334 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4214 "GrammarParser.cpp"
    break;

  case 150: // OperatorExpression: Term ">=" Term
#line 1338 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4222 "GrammarParser.cpp"
    break;

  case 151: // OperatorExpression: Term "or" Term
#line 1342 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4230 "GrammarParser.cpp"
    break;

  case 152: // OperatorExpression: Term "xor" Term
#line 1346 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4238 "GrammarParser.cpp"
    break;

  case 153: // OperatorExpression: Term "and" Term
#line 1350 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4246 "GrammarParser.cpp"
    break;

  case 154: // OperatorExpression: Term "=>" Term
#line 1354 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4254 "GrammarParser.cpp"
    break;

  case 155: // OperatorExpression: Term "implies" Term
#line 1358 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4262 "GrammarParser.cpp"
    break;

  case 156: // OperatorExpression: "not" Term
#line 1362 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4270 "GrammarParser.cpp"
    break;

  case 157: // CallExpression: DirectCallExpression
#line 1370 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 4278 "GrammarParser.cpp"
    break;

  case 158: // CallExpression: MethodCallExpression
#line 1374 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 4286 "GrammarParser.cpp"
    break;

  case 159: // CallExpression: IndirectCallExpression
#line 1378 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 4294 "GrammarParser.cpp"
    break;

  case 160: // DirectCallExpression: "this"
#line 1386 "../../obj/src/GrammarParser.y"
  {
      const auto identifier = CST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      identifier->setSpans( m_lexer.fetchSpansAndReset() );
      const auto identifierPath = IdentifierPath::fromIdentifier( identifier );
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, identifierPath );
  }
#line 4305 "GrammarParser.cpp"
    break;

  case 161: // DirectCallExpression: IdentifierPath
#line 1393 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4313 "GrammarParser.cpp"
    break;

  case 162: // DirectCallExpression: IdentifierPath "(" ")"
#line 1397 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), arguments, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4322 "GrammarParser.cpp"
    break;

  case 163: // DirectCallExpression: IdentifierPath "(" Terms ")"
#line 1402 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expressions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4330 "GrammarParser.cpp"
    break;

  case 164: // DirectCallExpression: IdentifierPath "(" error ")"
#line 1406 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 4338 "GrammarParser.cpp"
    break;

  case 165: // MethodCallExpression: Expression "." Identifier
#line 1414 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 4347 "GrammarParser.cpp"
    break;

  case 166: // MethodCallExpression: Expression "." Identifier "(" ")"
#line 1419 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4358 "GrammarParser.cpp"
    break;

  case 167: // MethodCallExpression: Expression "." Identifier "(" Terms ")"
#line 1426 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4368 "GrammarParser.cpp"
    break;

  case 168: // MethodCallExpression: Expression "." Identifier "(" error ")"
#line 1432 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 4376 "GrammarParser.cpp"
    break;

  case 169: // LiteralCallExpression: Expression "." IntegerLiteral
#line 1440 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = CST::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 4384 "GrammarParser.cpp"
    break;

  case 170: // IndirectCallExpression: CallExpression "(" ")"
#line 1448 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = CST::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4395 "GrammarParser.cpp"
    break;

  case 171: // IndirectCallExpression: CallExpression "(" Terms ")"
#line 1455 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = CST::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4405 "GrammarParser.cpp"
    break;

  case 172: // IndirectCallExpression: CallExpression "(" error ")"
#line 1461 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 4413 "GrammarParser.cpp"
    break;

  case 173: // TypeCastingExpression: Expression "as" Type
#line 1469 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = CST::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 4421 "GrammarParser.cpp"
    break;

  case 174: // LetExpression: "let" VariableBindings "in" Term
#line 1477 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = CST::make< LetExpression >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4429 "GrammarParser.cpp"
    break;

  case 175: // ConditionalExpression: "if" Term "then" Term "else" Term
#line 1485 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = CST::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4437 "GrammarParser.cpp"
    break;

  case 176: // ChooseExpression: "choose" AttributedVariables "in" Term "do" Term
#line 1493 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = CST::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4445 "GrammarParser.cpp"
    break;

  case 177: // UniversalQuantifierExpression: "forall" AttributedVariables "in" Term "holds" Term
#line 1501 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = CST::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4453 "GrammarParser.cpp"
    break;

  case 178: // ExistentialQuantifierExpression: "exists" AttributedVariables "in" Term "with" Term
#line 1509 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = CST::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4461 "GrammarParser.cpp"
    break;

  case 179: // CardinalityExpression: "|" Expression "|"
#line 1517 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = CST::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4469 "GrammarParser.cpp"
    break;

  case 180: // MatchExpression: "match" Term "with" "{" MatchArms "}"
#line 1524 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MatchExpression::Ptr > () = CST::make< MatchExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < MatchArms::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4477 "GrammarParser.cpp"
    break;

  case 181: // MatchArms: MatchArms "," MatchArm
#line 1531 "../../obj/src/GrammarParser.y"
  {
      auto arms = yystack_[2].value.as < MatchArms::Ptr > ();
      yystack_[0].value.as < MatchArm::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      arms->add( yystack_[0].value.as < MatchArm::Ptr > () );
      yylhs.value.as < MatchArms::Ptr > () = arms;
  }
#line 4488 "GrammarParser.cpp"
    break;

  case 182: // MatchArms: MatchArm
#line 1538 "../../obj/src/GrammarParser.y"
  {
      auto arms = CST::make< MatchArms >( yylhs.location );
      arms->add( yystack_[0].value.as < MatchArm::Ptr > () );
      yylhs.value.as < MatchArms::Ptr > () = arms;
  }
#line 4498 "GrammarParser.cpp"
    break;

  case 183: // MatchArm: Term "=>" Term
#line 1547 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MatchArm::Ptr > () = CST::make< MatchArm >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4506 "GrammarParser.cpp"
    break;

  case 184: // Literal: UndefinedLiteral
#line 1560 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 4514 "GrammarParser.cpp"
    break;

  case 185: // Literal: BooleanLiteral
#line 1564 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4522 "GrammarParser.cpp"
    break;

  case 186: // Literal: IntegerLiteral
#line 1568 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4530 "GrammarParser.cpp"
    break;

  case 187: // Literal: RationalLiteral
#line 1572 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4538 "GrammarParser.cpp"
    break;

  case 188: // Literal: DecimalLiteral
#line 1576 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4546 "GrammarParser.cpp"
    break;

  case 189: // Literal: BinaryLiteral
#line 1580 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4554 "GrammarParser.cpp"
    break;

  case 190: // Literal: StringLiteral
#line 1584 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4562 "GrammarParser.cpp"
    break;

  case 191: // Literal: ReferenceLiteral
#line 1588 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 4570 "GrammarParser.cpp"
    break;

  case 192: // Literal: ListLiteral
#line 1596 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 4578 "GrammarParser.cpp"
    break;

  case 193: // Literal: RangeLiteral
#line 1600 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 4586 "GrammarParser.cpp"
    break;

  case 194: // Literal: TupleLiteral
#line 1604 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 4594 "GrammarParser.cpp"
    break;

  case 195: // Literal: RecordLiteral
#line 1608 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 4602 "GrammarParser.cpp"
    break;

  case 196: // UndefinedLiteral: "undef"
#line 1616 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = CST::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4611 "GrammarParser.cpp"
    break;

  case 197: // BooleanLiteral: "true"
#line 1625 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = CST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4621 "GrammarParser.cpp"
    break;

  case 198: // BooleanLiteral: "false"
#line 1631 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = CST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4631 "GrammarParser.cpp"
    break;

  case 199: // IntegerLiteral: "integer"
#line 1641 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4639 "GrammarParser.cpp"
    break;

  case 200: // RationalLiteral: "rational"
#line 1649 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4647 "GrammarParser.cpp"
    break;

  case 201: // DecimalLiteral: "decimal"
#line 1657 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4655 "GrammarParser.cpp"
    break;

  case 202: // BinaryLiteral: "binary"
#line 1665 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4663 "GrammarParser.cpp"
    break;

  case 203: // BinaryLiteral: "hexadecimal"
#line 1669 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4671 "GrammarParser.cpp"
    break;

  case 204: // StringLiteral: "string"
#line 1677 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4679 "GrammarParser.cpp"
    break;

  case 205: // ReferenceLiteral: "@" IdentifierPath
#line 1685 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = CST::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4687 "GrammarParser.cpp"
    break;

  case 206: // ListLiteral: "[" "]"
#line 1714 "../../obj/src/GrammarParser.y"
  {
      const auto& expressions = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = CST::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4698 "GrammarParser.cpp"
    break;

  case 207: // ListLiteral: "[" Terms "]"
#line 1721 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = CST::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4708 "GrammarParser.cpp"
    break;

  case 208: // ListLiteral: "[" error "]"
#line 1727 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4716 "GrammarParser.cpp"
    break;

  case 209: // RangeLiteral: "[" Term ".." Term "]"
#line 1735 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = CST::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4726 "GrammarParser.cpp"
    break;

  case 210: // TupleLiteral: "(" Terms "," Term ")"
#line 1745 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = CST::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4739 "GrammarParser.cpp"
    break;

  case 211: // RecordLiteral: "{" Assignments "}"
#line 1758 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = CST::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4749 "GrammarParser.cpp"
    break;

  case 212: // Assignments: Assignments "," Assignment
#line 1772 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4760 "GrammarParser.cpp"
    break;

  case 213: // Assignments: Assignment
#line 1779 "../../obj/src/GrammarParser.y"
  {
      auto assignments = CST::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4770 "GrammarParser.cpp"
    break;

  case 214: // Assignment: Identifier ":" Term
#line 1788 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = CST::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4778 "GrammarParser.cpp"
    break;

  case 215: // MappedExpressions: MappedExpressions "," MappedExpression
#line 1795 "../../obj/src/GrammarParser.y"
  {
      const auto& mappedExpressions = yystack_[2].value.as < MappedExpressions::Ptr > ();
      yystack_[0].value.as < MappedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      mappedExpressions->add( yystack_[0].value.as < MappedExpression::Ptr > () );
      yylhs.value.as < MappedExpressions::Ptr > () = mappedExpressions;
  }
#line 4789 "GrammarParser.cpp"
    break;

  case 216: // MappedExpressions: MappedExpression
#line 1802 "../../obj/src/GrammarParser.y"
  {
      auto mappedExpressions = CST::make< MappedExpressions >( yylhs.location );
      mappedExpressions->add( yystack_[0].value.as < MappedExpression::Ptr > () );
      yylhs.value.as < MappedExpressions::Ptr > () = mappedExpressions;
  }
#line 4799 "GrammarParser.cpp"
    break;

  case 217: // MappedExpression: "->" Term
#line 1811 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4808 "GrammarParser.cpp"
    break;

  case 218: // MappedExpression: "(" Term ")" "->" Term
#line 1816 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = CST::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), arguments, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4818 "GrammarParser.cpp"
    break;

  case 219: // MappedExpression: TupleLiteral "->" Term
#line 1822 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto& leftBracket = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto& rightBracket = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4829 "GrammarParser.cpp"
    break;

  case 220: // Types: Types "," Type
#line 1838 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4840 "GrammarParser.cpp"
    break;

  case 221: // Types: Type
#line 1845 "../../obj/src/GrammarParser.y"
  {
      auto types = CST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4850 "GrammarParser.cpp"
    break;

  case 222: // Type: BasicType
#line 1854 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4858 "GrammarParser.cpp"
    break;

  case 223: // Type: TupleType
#line 1858 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4866 "GrammarParser.cpp"
    break;

  case 224: // Type: RecordType
#line 1862 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4874 "GrammarParser.cpp"
    break;

  case 225: // Type: TemplateType
#line 1866 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4882 "GrammarParser.cpp"
    break;

  case 226: // Type: RelationType
#line 1870 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4890 "GrammarParser.cpp"
    break;

  case 227: // Type: FixedSizedType
#line 1874 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4898 "GrammarParser.cpp"
    break;

  case 228: // Type: MappingType
#line 1878 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < MappingType::Ptr > ();
  }
#line 4906 "GrammarParser.cpp"
    break;

  case 229: // Type: VaradicType
#line 1882 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < VaradicType::Ptr > ();
  }
#line 4914 "GrammarParser.cpp"
    break;

  case 230: // BasicType: IdentifierPath
#line 1890 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = CST::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4922 "GrammarParser.cpp"
    break;

  case 231: // TupleType: "(" Types "," Type ")"
#line 1898 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = CST::make< TupleType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), subTypes, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4933 "GrammarParser.cpp"
    break;

  case 232: // RecordType: "{" TypedVariables "," TypedVariable "}"
#line 1909 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = CST::make< RecordType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4944 "GrammarParser.cpp"
    break;

  case 233: // TemplateType: IdentifierPath "<" Types ">"
#line 1920 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = CST::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4952 "GrammarParser.cpp"
    break;

  case 234: // RelationType: IdentifierPath "<" MaybeFunctionParameters "->" Type ">"
#line 1928 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = CST::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4960 "GrammarParser.cpp"
    break;

  case 235: // FixedSizedType: IdentifierPath "'" Term
#line 1936 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = CST::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4968 "GrammarParser.cpp"
    break;

  case 236: // MappingType: "<" FunctionParameters "->" Type ">"
#line 1944 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MappingType::Ptr > () = CST::make< MappingType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );      
  }
#line 4976 "GrammarParser.cpp"
    break;

  case 237: // VaradicType: Identifier "..."
#line 1952 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VaradicType::Ptr > () = CST::make< VaradicType >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4984 "GrammarParser.cpp"
    break;

  case 238: // FunctionParameters: FunctionParameters "*" Type
#line 1964 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4995 "GrammarParser.cpp"
    break;

  case 239: // FunctionParameters: Type
#line 1971 "../../obj/src/GrammarParser.y"
  {
      auto types = CST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 5005 "GrammarParser.cpp"
    break;

  case 240: // MaybeFunctionParameters: FunctionParameters
#line 1981 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 5013 "GrammarParser.cpp"
    break;

  case 241: // MaybeFunctionParameters: %empty
#line 1985 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = CST::make< Types >( yylhs.location );
  }
#line 5021 "GrammarParser.cpp"
    break;

  case 242: // MethodParameters: MethodParameters "," TypedAttributedVariable
#line 1993 "../../obj/src/GrammarParser.y"
  {
      const auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5032 "GrammarParser.cpp"
    break;

  case 243: // MethodParameters: "this"
#line 2000 "../../obj/src/GrammarParser.y"
  {
      const auto parameters = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto identifier = CST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      identifier->setSpans( m_lexer.fetchSpansAndReset() );
      const auto unresolvedType = CST::make< UnresolvedType >( yylhs.location );
      const auto variable = CST::make< VariableDefinition >( yylhs.location, identifier, Token::unresolved(), unresolvedType );
      parameters->add( variable );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5046 "GrammarParser.cpp"
    break;

  case 244: // Parameters: Parameters "," TypedAttributedVariable
#line 2014 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5057 "GrammarParser.cpp"
    break;

  case 245: // Parameters: TypedAttributedVariable
#line 2021 "../../obj/src/GrammarParser.y"
  {
      auto parameters = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5067 "GrammarParser.cpp"
    break;

  case 246: // MaybeDefined: "defined" "{" Term "}"
#line 2035 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = CST::make< Defined >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 5075 "GrammarParser.cpp"
    break;

  case 247: // MaybeDefined: %empty
#line 2039 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = CST::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), CST::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 5083 "GrammarParser.cpp"
    break;

  case 248: // MaybeInitially: "=" "{" Expression "}"
#line 2047 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: drop braces and replace this rule with ::= Expression
      const auto& embracedExpression = CST::make< EmbracedExpression >( yystack_[1].location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), embracedExpression );
  }
#line 5093 "GrammarParser.cpp"
    break;

  case 249: // MaybeInitially: "=" "{" MappedExpressions "}"
#line 2053 "../../obj/src/GrammarParser.y"
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
#line 5110 "GrammarParser.cpp"
    break;

  case 250: // MaybeInitially: %empty
#line 2066 "../../obj/src/GrammarParser.y"
  {
      const auto& expression = CST::make< CST::AbstractExpression >( yylhs.location, Token::unresolved() );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, Token::unresolved(), expression );
  }
#line 5119 "GrammarParser.cpp"
    break;

  case 251: // Identifier: "identifier"
#line 2079 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 5127 "GrammarParser.cpp"
    break;

  case 252: // Identifier: "in"
#line 2083 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5136 "GrammarParser.cpp"
    break;

  case 253: // Identifier: "CASM"
#line 2088 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5145 "GrammarParser.cpp"
    break;

  case 254: // Identifier: "self"
#line 2093 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5154 "GrammarParser.cpp"
    break;

  case 255: // Identifier: "enumeration"
#line 2098 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5163 "GrammarParser.cpp"
    break;

  case 256: // Identifier: "structure"
#line 2103 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5172 "GrammarParser.cpp"
    break;

  case 257: // IdentifierPath: IdentifierPath "::" Identifier
#line 2112 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < CST::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 5183 "GrammarParser.cpp"
    break;

  case 258: // IdentifierPath: Identifier
#line 2119 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = CST::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5191 "GrammarParser.cpp"
    break;

  case 259: // Variable: TypedVariable
#line 2131 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5199 "GrammarParser.cpp"
    break;

  case 260: // Variable: Identifier
#line 2135 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = CST::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = CST::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 5208 "GrammarParser.cpp"
    break;

  case 261: // AttributedVariables: AttributedVariables "," AttributedVariable
#line 2144 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5219 "GrammarParser.cpp"
    break;

  case 262: // AttributedVariables: AttributedVariable
#line 2151 "../../obj/src/GrammarParser.y"
  {
      auto variables = CST::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5229 "GrammarParser.cpp"
    break;

  case 263: // TypedVariables: TypedVariables "," TypedVariable
#line 2161 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5240 "GrammarParser.cpp"
    break;

  case 264: // TypedVariables: TypedVariable
#line 2168 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = CST::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5250 "GrammarParser.cpp"
    break;

  case 265: // TypedVariable: Identifier ":" Type
#line 2178 "../../obj/src/GrammarParser.y"
  {
      auto variable = CST::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5259 "GrammarParser.cpp"
    break;

  case 266: // AttributedVariable: Attributes Variable
#line 2187 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5269 "GrammarParser.cpp"
    break;

  case 267: // AttributedVariable: Variable
#line 2193 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5277 "GrammarParser.cpp"
    break;

  case 268: // TypedAttributedVariable: Attributes TypedVariable
#line 2201 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5287 "GrammarParser.cpp"
    break;

  case 269: // TypedAttributedVariable: TypedVariable
#line 2207 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5295 "GrammarParser.cpp"
    break;

  case 270: // VariableBindings: VariableBindings "," VariableBinding
#line 2219 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5306 "GrammarParser.cpp"
    break;

  case 271: // VariableBindings: VariableBinding
#line 2226 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = CST::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5316 "GrammarParser.cpp"
    break;

  case 272: // VariableBinding: AttributedVariable "=" Term
#line 2235 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = CST::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5324 "GrammarParser.cpp"
    break;

  case 273: // LocalFunctionDefinitions: LocalFunctionDefinitions "," AttributedLocalFunctionDefinition
#line 2247 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5335 "GrammarParser.cpp"
    break;

  case 274: // LocalFunctionDefinitions: AttributedLocalFunctionDefinition
#line 2254 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5345 "GrammarParser.cpp"
    break;

  case 275: // AttributedLocalFunctionDefinition: Attributes LocalFunctionDefinition
#line 2263 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 5355 "GrammarParser.cpp"
    break;

  case 276: // AttributedLocalFunctionDefinition: LocalFunctionDefinition
#line 2269 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 5363 "GrammarParser.cpp"
    break;

  case 277: // AttributedLocalFunctionDefinition: error
#line 2273 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 5371 "GrammarParser.cpp"
    break;

  case 278: // LocalFunctionDefinition: Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 2280 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = CST::make< FunctionDefinition >( yylhs.location, Token::unresolved(), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > ()->setClassification( FunctionDefinition::Classification::LOCAL );
  }
#line 5380 "GrammarParser.cpp"
    break;

  case 279: // Attributes: Attributes Attribute
#line 2293 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5390 "GrammarParser.cpp"
    break;

  case 280: // Attributes: Attribute
#line 2299 "../../obj/src/GrammarParser.y"
  {
      auto attributes = CST::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5400 "GrammarParser.cpp"
    break;

  case 281: // Attribute: "[" BasicAttribute "]"
#line 2308 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5411 "GrammarParser.cpp"
    break;

  case 282: // Attribute: "[" SymbolAttribute "]"
#line 2315 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < SymbolAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5422 "GrammarParser.cpp"
    break;

  case 283: // Attribute: "[" ExpressionAttribute "]"
#line 2322 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5433 "GrammarParser.cpp"
    break;

  case 284: // Attribute: "[" error "]"
#line 2329 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 5441 "GrammarParser.cpp"
    break;

  case 285: // BasicAttribute: Identifier
#line 2336 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = CST::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5449 "GrammarParser.cpp"
    break;

  case 286: // SymbolAttribute: Identifier TypedVariable
#line 2343 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SymbolAttribute::Ptr > () = CST::make< SymbolAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < VariableDefinition::Ptr > () );
  }
#line 5457 "GrammarParser.cpp"
    break;

  case 287: // ExpressionAttribute: Identifier Term
#line 2350 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = CST::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5465 "GrammarParser.cpp"
    break;


#line 5469 "GrammarParser.cpp"

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

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
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


  const short Parser::yypact_ninf_ = -425;

  const short Parser::yytable_ninf_ = -240;

  const short
  Parser::yypact_[] =
  {
       7,  -425,   211,    31,  1322,    21,  -425,     9,  -425,  -425,
    -425,  -425,  -425,  -425,  2426,    38,    79,    93,  -425,  -425,
     168,   561,   561,   561,   561,   561,   561,   561,   350,   350,
     350,   561,   561,  1123,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,
    1139,  -425,  -425,  -425,  -425,   226,   226,   226,  2426,   226,
    2426,  -425,  -425,  -425,  2426,  1164,  1164,  1842,  1574,   561,
    1164,   561,  -425,  -425,  -425,  -425,  -425,  -425,  3187,   -14,
    -425,   119,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,    32,   213,  -425,
    -425,  -425,  -425,   159,  -425,   146,   203,   155,   110,   198,
     202,   235,     1,   265,   350,   561,   350,   269,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,   183,   157,    -7,  -425,
    -425,    42,   245,  -425,  -425,    32,  -425,  -425,   273,     6,
    -425,   226,     8,  -425,    23,  2676,   134,  2853,  -425,  -425,
    -425,   276,   270,  2956,   277,  -425,   -51,  2919,   100,  -425,
     278,   -24,   146,  2426,  2426,  2426,  2426,  2426,  2426,  2426,
    2426,  2426,  2426,  2426,  2426,  2426,  2426,  2426,  2426,  2426,
     350,   513,  1641,   350,  1708,   561,  2426,  2426,   268,   206,
    -425,    34,   350,   286,  2292,   255,   350,   350,   507,  2426,
     561,   289,   284,  -425,    32,   285,  -425,  -425,   252,   298,
    -425,   350,  2426,   350,   300,   350,   350,  2426,  2426,   226,
    -425,  2426,   226,  2426,  2426,  2426,   303,  -425,  2426,  -425,
    -425,  -425,  2426,  2426,  -425,   561,  2426,  -425,  3307,  3286,
     881,  2452,   311,   311,   636,   209,   209,   291,   291,   291,
    -425,  2452,   636,   209,   209,  -425,  -425,   306,   310,  -425,
     115,  3187,  -425,   316,  -425,   230,  -425,  2989,  3187,  2426,
    -425,   159,   320,  -425,   234,   241,  -425,  -425,   226,   330,
      92,    55,  1256,  -425,   226,   153,   226,   226,  2292,  2426,
    2426,  2426,  1348,  1440,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,   305,   -41,
     313,   314,   332,   242,   247,   337,  -425,  -425,  3187,  -425,
      19,   350,   561,   350,   350,   122,    70,   264,   323,   319,
    -425,   340,   128,   321,  3187,  3187,  -425,  2820,  -425,  2544,
    2748,  2886,  2426,  3022,  3187,  3055,  -425,  3187,  1775,  -425,
    -425,  -425,  -425,   322,  3187,  -425,   324,   325,   226,   326,
     226,  -425,  2426,  -425,  -425,   249,  -425,   226,   376,  1932,
    -425,   378,  2022,   135,  -425,   341,   169,  -425,  -425,   226,
     185,   188,  -425,  2709,  2785,  2577,   343,  2112,   278,   327,
    2202,  2426,  2426,    76,   132,   143,  2292,  -425,    97,  -425,
      19,   348,   351,  -425,   346,   561,   561,  -425,  -425,  -425,
      67,  -425,   122,   350,  -425,   350,   356,  -425,  -425,    99,
    -425,  -425,   128,   350,  2426,  2426,  2426,  2426,  3220,   256,
    -425,  -425,  -425,   360,  -425,   248,  2426,   350,   350,  -425,
     350,  -425,  3187,  -425,    92,  -425,  -425,  -425,  -425,  -425,
    -425,  2292,   350,  2292,   153,  -425,  2426,  2426,  2292,   362,
    2292,  -425,  -425,  -425,  -425,  3187,  3187,  2292,   350,  2292,
     350,  2292,   350,  -425,  -425,  -425,  -425,  -425,  -425,  -425,
      78,   -23,  -425,  -425,  -425,  -425,  -425,  -425,   357,   128,
    -425,  -425,  -425,   407,  3187,  3187,  3187,  3187,  2426,  -425,
    2426,  -425,  -425,  3187,   373,   379,   381,  -425,  -425,   363,
    -425,  -425,  2511,  2610,   402,  1507,  -425,  -425,   385,  -425,
     392,  -425,   394,   350,   350,  -425,   112,   390,   396,  3253,
    -425,  2426,  2426,  2426,   350,  2292,  2426,  2292,  2292,   393,
     391,   395,  2359,  -425,  3088,  2292,  2292,  2292,   380,   383,
    -425,  2426,   399,  -425,  3187,  3187,  3187,   407,  -425,  2643,
    -425,  -425,  -425,  2292,  2292,  -425,  -425,  2292,  -425,  -425,
    -425,   350,   350,  3121,  2482,   396,  2292,  -425,  -425,  -425,
    -425,  -425,  -425,  1842,    35,   268,   258,  -425,  -425,  3154,
    -425,  -425,   322
  };

  const short
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   280,     0,   253,   255,
     256,   254,   252,   251,   285,     0,     0,     0,     1,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     8,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       0,     3,   279,   284,   160,     0,     0,     0,     0,     0,
       0,   196,   198,   197,     0,     0,     0,     0,     0,     0,
       0,     0,   202,   203,   199,   200,   201,   204,   287,   122,
     124,   134,   157,   158,   135,   159,   123,   125,   126,   127,
     128,   129,   130,   131,   136,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   258,   161,   286,
     281,   282,   283,     0,   258,    24,     0,     0,     0,   258,
      46,     0,    49,     0,     0,     0,     0,     0,   222,   223,
     224,   225,   226,   227,   228,   229,   258,   230,     0,    73,
      74,     0,     0,     5,     7,   260,   267,   259,     0,     0,
     271,     0,     0,   262,     0,     0,     0,     0,   156,   137,
     138,     0,     0,   121,     0,   206,     0,   121,     0,   213,
       0,     0,   205,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   221,     0,     0,   264,   239,     0,     0,
     237,   241,     0,     0,     0,   241,   241,     0,     0,     0,
     266,     0,     0,     0,     0,     0,     0,   133,     0,   132,
     208,   207,     0,     0,   211,     0,     0,   179,   153,   151,
     152,   155,   139,   140,   146,   147,   148,   141,   142,   143,
     144,   154,   145,   149,   150,   173,   169,   165,     0,   170,
       0,   121,   265,     0,   162,     0,   257,   121,   217,     0,
      25,     0,     0,   243,     0,     0,   269,   245,     0,     0,
       0,     0,     0,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,     0,   118,
     157,   158,     0,     0,     0,     0,    45,    47,    48,    50,
       0,     0,     0,     0,     0,     0,     0,   221,   240,     0,
     235,     0,     0,     0,   272,   174,   270,     0,   261,     0,
       0,     0,     0,   120,   120,     0,   212,   214,     0,   172,
     171,   164,   163,     0,   219,   215,     0,     0,     0,     0,
       0,   268,     0,    42,    44,     0,    40,     0,     0,     0,
      78,     0,     0,     0,   277,     0,     0,   274,   276,     0,
       0,     0,   107,     0,     0,     0,     0,     0,   258,     0,
       0,     0,     0,     0,     0,     0,     0,    55,     0,    53,
       0,   220,   263,   238,     0,     0,     0,    60,    62,    64,
       0,    58,     0,     0,   233,     0,     0,    71,    72,     0,
      68,    70,     0,     0,     0,     0,     0,     0,     0,     0,
     182,   210,   209,     0,   166,     0,     0,     0,     0,   242,
       0,   244,    27,    26,     0,    41,   115,   113,    77,   111,
     109,     0,   241,     0,     0,   275,     0,     0,     0,     0,
       0,   110,   108,   114,   112,   116,   117,     0,     0,     0,
       0,     0,     0,    32,    51,    52,    54,   231,   232,   236,
       0,     0,    56,    63,    59,    61,    57,   220,     0,     0,
      65,    67,    69,   247,   177,   176,   175,   178,     0,   180,
       0,   168,   167,   218,     0,     0,     0,    43,   102,     0,
     103,   273,     0,     0,    93,     0,   119,    37,     0,    35,
       0,    33,     0,   241,   241,   234,     0,     0,   250,   154,
     181,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    98,     0,     0,     0,     0,     0,     0,
      66,     0,     0,    39,    30,    29,    28,   247,   104,     0,
     106,    94,    96,     0,     0,    95,    97,     0,    38,    36,
      34,     0,     0,     0,     0,   250,     0,    99,   100,   101,
      75,    76,   246,     0,     0,   194,     0,   278,   105,   121,
     248,   249,   132
  };

  const short
  Parser::yypgoto_[] =
  {
    -425,  -425,  -425,  -425,   423,   411,  -425,  -425,    10,    13,
    -321,    11,  -425,  -425,  -425,  -425,  -425,  -425,  -425,    56,
    -425,    43,  -425,  -425,   -33,  -424,    36,  -425,  -425,    45,
     -28,   692,  -425,  -425,  -425,  -425,   -83,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,   -62,   312,   495,
    -425,   371,   436,   639,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,   -40,  -425,  -425,  -425,   280,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,  -112,  -425,  -425,
     228,  -110,   194,   262,   148,  -425,  -425,  -425,  -425,   446,
    -425,  -425,  -425,   358,  -222,   297,   299,   -61,   -80,    -2,
     218,   361,   -46,  -425,   -11,   -37,  -135,   217,   288,  -425,
      50,   126,   302,    -3,  -425,  -425,  -425
  };

  const short
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    33,    34,    35,    36,    37,   427,   428,
      40,   374,   375,    41,    42,    43,    44,    45,   408,   409,
      46,   419,   420,    47,   429,   430,   431,    48,    49,   421,
     379,   380,   305,   306,   307,   552,   553,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   162,   271,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,   439,   440,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   168,
     169,   199,   200,   212,   217,   128,   129,   130,   131,   132,
     133,   134,   135,   338,   339,   284,   285,   538,   563,   114,
     108,   146,   152,   215,   147,   153,   287,   149,   150,   386,
     387,   388,   151,     6,    15,    16,    17
  };

  const short
  Parser::yytable_[] =
  {
      14,   198,    52,   109,   343,   501,   166,   223,   241,   407,
       1,   154,   107,   156,    38,   192,   242,    39,   148,   116,
     117,   118,   119,   121,    51,   123,   136,   136,   136,   190,
     142,    18,   204,   205,   228,   282,   231,     8,    32,   534,
       9,   247,  -134,    38,   210,    10,    39,    52,   224,    11,
     283,   233,   206,   145,   145,   145,   378,   145,     8,   191,
      38,     9,    12,    39,   195,     2,    10,   170,    53,   191,
      11,    54,   415,   229,   416,   232,   291,     2,   292,     2,
     293,   294,   295,    12,   296,   297,   298,   407,   299,   486,
     232,   300,     2,   373,   193,     8,   600,   110,     9,   301,
      61,    62,    63,    10,    21,   195,    23,    11,    65,    66,
     225,    67,   501,    68,   216,   302,    32,    21,   191,    23,
      12,    71,   136,   214,   136,     2,    13,   415,   492,   416,
     270,   477,   275,    21,   201,    23,   303,   423,   111,   424,
     533,    72,    73,    74,    75,    76,    77,    13,    52,   145,
       2,   478,   112,   202,   384,     2,     8,     2,   484,     9,
     500,   244,   235,   461,    10,   204,   205,   245,    11,   198,
       2,     8,   360,   560,     9,   192,   127,   138,   139,    10,
       2,    12,   242,    11,    13,   206,     2,   479,   136,   267,
     286,   136,   148,   276,   286,   348,    12,   463,   481,   214,
     136,   232,   229,   214,   136,   136,   276,   480,   329,   195,
     203,     2,     7,   466,     8,   196,   467,     9,   482,   136,
     195,   136,    10,   136,   136,   221,    11,   145,   113,     8,
     145,   222,     9,   449,   197,   451,   464,    10,   115,    12,
     519,    11,   120,   170,   122,    13,   137,   137,   137,   141,
     390,   391,   232,   207,    12,   232,   322,   148,     8,   201,
      13,     9,   177,   178,   382,   208,    10,   280,   220,   194,
      11,   283,   213,   281,   397,   400,   195,   371,   202,   182,
     183,   184,   185,    12,     2,    52,   214,   362,   376,   172,
     209,   367,   145,   385,   145,   145,   445,   242,   369,   404,
     398,   368,     5,    13,   405,   512,    50,   226,   370,   368,
     453,   558,   559,     2,   370,   242,   454,   509,    13,   601,
     211,   412,   333,   510,   219,   281,    78,   334,   227,   136,
     214,   136,   136,   237,  -239,    50,   240,   238,   265,  -239,
     246,   272,   137,   279,   137,   417,   290,    13,   418,   330,
     289,   331,   332,     8,   325,   326,     9,   286,   335,   286,
     342,    10,   358,   352,   185,    11,   214,   359,   214,   337,
     155,   341,   157,   361,    52,   455,   158,   366,    12,   163,
     167,   182,   183,   184,   185,   372,    52,   385,   191,   403,
     401,   402,   406,   333,   425,   426,   433,   446,   456,   447,
     448,   450,   459,   462,   471,   487,   124,    52,   137,   473,
     125,   137,   488,   490,   491,   489,   499,   511,   126,    52,
     137,   136,   525,   136,   137,   137,   535,   537,   541,    52,
     417,   136,   494,   418,   542,   495,   543,   548,   544,   137,
     555,   137,    13,   137,   137,   136,   136,   556,   136,   557,
     561,   562,   376,   573,   572,   581,   143,   574,   582,   584,
     136,   144,   385,   493,   485,   517,   536,   496,   502,   576,
     540,   266,   595,   356,   596,   365,   136,   140,   136,   411,
     136,   413,   414,   336,   218,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   323,   288,   324,   597,   585,   288,   277,   278,
       8,   383,   230,     9,   521,   465,     8,   346,    10,     9,
       0,   328,    11,     0,    10,     0,     0,     0,    11,     0,
       0,   136,   136,     0,   340,    12,     0,     0,     0,   344,
     345,    12,   136,   347,     0,   349,   350,   351,     0,   137,
     353,   137,   137,     0,   354,   355,     0,     0,   357,     0,
     159,   160,     0,     0,     8,   171,     0,     9,     0,     0,
       0,   497,    10,   498,     0,   319,    11,   327,     0,   136,
     136,   503,     0,     0,     0,     0,     0,     0,     0,    12,
       0,   364,   377,     0,     0,   514,   515,   389,   516,    13,
       0,    74,     0,     0,     0,    13,     0,     0,     0,     0,
       0,   393,   394,   395,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   528,     0,   530,     0,
     532,     0,   410,     0,     0,     0,     0,   422,     0,     0,
     320,   137,     0,   137,   432,     0,     0,     0,     0,     0,
       0,   137,     0,    13,     0,     0,     0,     0,     0,     0,
       0,     0,   319,   319,   438,   137,   137,     0,   137,   319,
     288,     0,   288,   319,   319,     0,     0,     0,     0,     0,
     137,     0,     0,     0,   452,     0,     0,     0,     0,   177,
     178,     0,   567,     0,     0,     0,   137,     0,   137,   318,
     137,     0,     0,     0,   180,   181,   182,   183,   184,   185,
     410,     0,     0,   475,   476,   188,   189,     0,     0,     0,
       0,     0,   422,     0,     0,     0,     0,   320,   320,   590,
     591,   432,     0,     0,   320,     0,     0,     0,   320,   320,
       0,     0,     0,     0,     0,     0,   504,   505,   506,   507,
     319,   137,   137,   319,     0,     0,   377,     0,   513,     0,
       0,     0,   137,     0,     0,     0,   389,     0,   319,     0,
       0,   319,     0,     0,     0,     0,     0,   319,   522,   523,
       0,     0,     0,     0,     0,     0,   318,   318,     0,     0,
       0,     0,     0,   318,     0,     0,     0,   318,   318,   137,
     137,   432,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   320,     0,     0,   320,     0,
     539,     0,   438,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   319,   320,   319,     0,   320,   554,   432,   319,
       0,   319,   320,   321,     0,     0,     0,     0,   319,     0,
     319,     0,   319,   564,   565,   566,     0,     0,   569,     0,
       0,     0,     0,     0,   554,     0,     0,     0,     0,     0,
       0,     0,     0,   583,   318,     0,     0,   318,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   318,     0,     0,   318,   304,   320,     0,   320,
       0,   318,     0,     0,   320,   599,   320,     0,     0,     0,
       0,     0,     0,   320,     0,   320,   319,   320,   319,   319,
       0,     0,     0,     0,     0,     0,   319,   319,   319,   173,
     321,   321,     0,     0,   177,   178,   179,   321,     0,     0,
       0,   321,   321,     0,   319,   319,     0,     0,   319,   180,
     181,   182,   183,   184,   185,     0,   318,   319,   318,   187,
     188,   189,     0,   318,     0,   318,     0,     0,     0,     0,
       0,     0,   318,     0,   318,     0,   318,     0,     0,     0,
       0,   320,     0,   320,   320,     0,     0,     0,     0,     0,
     392,   320,   320,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   320,
     320,     0,     0,   320,     0,     0,     0,     0,   321,     0,
       0,   321,   320,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   321,     0,     0,   321,
     318,     0,   318,   318,     0,   321,     0,     0,     0,     0,
     318,   318,   318,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   318,   318,
       0,   458,   318,     0,   458,     0,     0,     0,     0,   594,
       0,   318,     0,     0,     0,     0,     0,     0,     0,   458,
       0,     0,   458,     0,     0,     0,     0,     0,   483,     0,
     321,     0,   321,     0,     0,     0,     0,   321,     0,   321,
       0,     0,     0,     0,     0,     0,   321,     0,   321,     0,
     321,     0,     0,    -2,    19,     0,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     0,     0,     0,
      30,    31,    32,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,   518,     0,   520,    30,    31,    32,     0,
     524,     0,   526,     0,     0,     0,     0,     8,     0,   527,
       9,   529,     0,   531,     0,    10,     0,     0,     0,    11,
      54,     2,     0,     0,   321,     0,   321,   321,     0,     0,
       0,     0,    12,     0,   321,   321,   321,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,   321,   321,     0,     0,   321,    65,    66,     0,
      67,     0,    68,     0,    69,   321,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,     0,   568,     0,   570,
     571,     0,     0,     0,     0,     0,     0,   578,   579,   580,
      72,    73,    74,    75,    76,    77,    13,   381,     0,     8,
       0,     0,     9,     0,     0,   587,   588,    10,     0,   589,
       0,    11,    54,     0,     0,     0,     0,   291,   598,   292,
       0,   293,   294,   295,    12,   296,   297,   298,     0,   299,
       0,     0,   300,     0,     0,     0,     0,     0,     0,     0,
     301,    61,    62,    63,     0,     0,     0,     0,     0,    65,
      66,     0,    67,     0,    68,     0,   302,     0,     0,     0,
       0,     0,    71,    19,     0,     0,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     0,   303,     0,    30,
      31,    32,    72,    73,    74,    75,    76,    77,    13,   396,
       0,     8,     0,     0,     9,     0,     0,     0,     0,    10,
       0,     0,     0,    11,    54,     0,     0,     0,     0,   291,
       0,   292,     0,   293,   294,   295,    12,   296,   297,   298,
       2,   299,     0,     0,   300,     0,     0,     0,     0,     0,
       0,     0,   301,    61,    62,    63,     0,     0,     0,     0,
       0,    65,    66,     0,    67,     0,    68,     0,   302,     0,
       0,     0,     0,     0,    71,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   303,
       0,     0,     0,     0,    72,    73,    74,    75,    76,    77,
      13,   399,     0,     8,     0,     0,     9,     0,     0,     0,
       0,    10,     0,     0,     0,    11,    54,     0,     0,     0,
       0,   291,     0,   292,     0,   293,   294,   295,    12,   296,
     297,   298,     0,   299,     0,     0,   300,     0,     0,     0,
       0,     0,     0,     0,   301,    61,    62,    63,     0,     0,
       0,     0,     0,    65,    66,     0,    67,     0,    68,     0,
     302,     0,     0,     0,     0,     0,    71,     0,   549,     0,
       8,     0,     0,     9,     0,     0,     0,     0,    10,     0,
       0,   303,    11,    54,     0,     0,    72,    73,    74,    75,
      76,    77,    13,    55,     0,    12,    56,    57,     0,     0,
      58,     0,     0,     0,     0,   550,     0,    59,    60,     0,
       0,     0,    61,    62,    63,     0,     0,     0,     0,    64,
      65,    66,     0,    67,     0,    68,     0,    69,     0,     0,
       0,   551,    70,    71,     0,   164,     0,     8,     0,     0,
       9,     0,     0,     0,     0,    10,     0,     0,     0,    11,
      54,     0,     0,    72,    73,    74,    75,    76,    77,    13,
      55,     0,    12,    56,    57,     0,     0,    58,     0,     0,
       0,     0,     0,     0,    59,    60,     0,     0,     0,    61,
      62,    63,     0,     0,     0,     0,    64,    65,    66,     0,
      67,     0,    68,   165,    69,     0,     0,     0,     0,    70,
      71,     0,   268,     0,     8,     0,     0,     9,     0,     0,
       0,     0,    10,     0,     0,     0,    11,    54,     0,     0,
      72,    73,    74,    75,    76,    77,    13,    55,     0,    12,
      56,    57,     0,     0,    58,     0,     0,     0,     0,     0,
       0,    59,    60,     0,     0,     0,    61,    62,    63,     0,
       0,     0,     0,    64,    65,    66,     0,    67,   269,    68,
       0,    69,     0,     0,     0,     0,    70,    71,     0,   273,
       0,     8,     0,     0,     9,     0,     0,     0,     0,    10,
       0,     0,     0,    11,    54,     0,     0,    72,    73,    74,
      75,    76,    77,    13,    55,     0,    12,    56,    57,     0,
       0,    58,     0,     0,     0,     0,     0,     0,    59,    60,
       0,     0,     0,    61,    62,    63,     0,     0,     0,     0,
      64,    65,    66,     0,    67,   274,    68,     0,    69,     0,
       0,     0,     0,    70,    71,     0,   443,     0,     8,     0,
       0,     9,     0,     0,     0,     0,    10,     0,     0,     0,
      11,    54,     0,     0,    72,    73,    74,    75,    76,    77,
      13,    55,     0,    12,    56,    57,     0,     0,    58,     0,
       0,     0,     0,     0,     0,    59,    60,     0,     0,     0,
      61,    62,    63,     0,     0,     0,     0,    64,    65,    66,
       0,    67,   444,    68,     0,    69,     0,     0,     0,     0,
      70,    71,     0,   161,     0,     8,     0,     0,     9,     0,
       0,     0,     0,    10,     0,     0,     0,    11,    54,     0,
       0,    72,    73,    74,    75,    76,    77,    13,    55,     0,
      12,    56,    57,     0,     0,    58,     0,     0,     0,     0,
       0,     0,    59,    60,     0,     0,     0,    61,    62,    63,
       0,     0,     0,     0,    64,    65,    66,     0,    67,     0,
      68,     0,    69,     0,     0,     0,     0,    70,    71,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    72,    73,
      74,    75,    76,    77,    13,     8,     0,     0,     9,     0,
       0,     0,     0,    10,     0,     0,     0,    11,    54,     0,
       0,     0,     0,   291,   457,   292,     0,   293,   294,   295,
      12,   296,   297,   298,     0,   299,     0,     0,   300,     0,
       0,     0,     0,     0,     0,     0,   301,    61,    62,    63,
       0,     0,     0,     0,     0,    65,    66,     0,    67,     0,
      68,     0,   302,     0,     0,     0,     0,     0,    71,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     0,     0,     0,     0,    72,    73,
      74,    75,    76,    77,    13,     8,     0,     0,     9,     0,
       0,     0,     0,    10,     0,     0,     0,    11,    54,     0,
       0,     0,     0,   291,     0,   292,   460,   293,   294,   295,
      12,   296,   297,   298,     0,   299,     0,     0,   300,     0,
       0,     0,     0,     0,     0,     0,   301,    61,    62,    63,
       0,     0,     0,     0,     0,    65,    66,     0,    67,     0,
      68,     0,   302,     0,     0,     0,     0,     0,    71,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     0,     0,     0,     0,    72,    73,
      74,    75,    76,    77,    13,     8,     0,     0,     9,     0,
       0,     0,     0,    10,     0,     0,     0,    11,    54,     0,
       0,     0,     0,   291,     0,   292,     0,   293,   294,   295,
      12,   296,   297,   298,     0,   299,     0,     0,   300,     0,
       0,     0,     0,     0,     0,     0,   301,    61,    62,    63,
       0,     0,     0,     0,     0,    65,    66,     0,    67,     0,
      68,     0,   302,   472,     0,     0,     0,     0,    71,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     0,     0,     0,     0,    72,    73,
      74,    75,    76,    77,    13,     8,     0,     0,     9,     0,
       0,     0,     0,    10,     0,     0,     0,    11,    54,     0,
       0,     0,     0,   291,     0,   292,     0,   293,   294,   295,
      12,   296,   297,   298,     0,   299,     0,     0,   300,     0,
       0,     0,     0,     0,     0,     0,   301,    61,    62,    63,
       0,     0,     0,     0,     0,    65,    66,     0,    67,     0,
      68,     0,   302,     0,     0,     0,     0,     0,    71,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,   474,     0,     0,     0,    72,    73,
      74,    75,    76,    77,    13,     8,     0,     0,     9,     0,
       0,     0,     0,    10,     0,     0,     0,    11,    54,     0,
       0,     0,     0,   291,     0,   292,     0,   293,   294,   295,
      12,   296,   297,   298,     0,   299,     0,     0,   300,     0,
       0,     0,     0,     0,     0,     0,   301,    61,    62,    63,
       0,     0,     0,     0,     0,    65,    66,     0,    67,     0,
      68,     0,   302,     0,     0,     0,     0,     0,    71,     0,
       0,     0,     8,     0,     0,     9,     0,     0,     0,     0,
      10,     0,     0,   303,    11,    54,     0,     0,    72,    73,
      74,    75,    76,    77,    13,    55,     0,    12,    56,    57,
       0,     0,    58,     0,     0,     0,     0,   550,     0,    59,
      60,     0,     0,     0,    61,    62,    63,     0,     0,     0,
       0,    64,    65,    66,     0,    67,     0,    68,     0,    69,
     575,     0,     0,   551,    70,    71,     0,     0,     0,     8,
       0,     0,     9,     0,     0,     0,     0,    10,     0,     0,
       0,    11,    54,     0,     0,    72,    73,    74,    75,    76,
      77,    13,    55,     0,    12,    56,    57,     0,     0,    58,
       0,     0,     0,     0,     0,     0,    59,    60,     0,     0,
       0,    61,    62,    63,     0,     0,     0,     0,    64,    65,
      66,     0,    67,     0,    68,     8,    69,     0,     9,     0,
       0,    70,    71,    10,     0,     0,     0,    11,    54,     0,
     173,   174,   175,     0,     0,   177,   178,   179,     0,     0,
      12,     0,    72,    73,    74,    75,    76,    77,    13,     0,
     180,   181,   182,   183,   184,   185,     0,    61,    62,    63,
     187,   188,   189,     0,     0,    65,    66,     0,   593,     0,
      68,     0,    69,   545,     0,     0,     0,     0,    71,     0,
       0,     0,     0,   546,     0,     0,     0,   197,     0,   173,
     174,   175,   176,     0,   177,   178,   179,     0,    72,    73,
      74,    75,    76,    77,    13,     0,   435,     0,     0,   180,
     181,   182,   183,   184,   185,     0,     0,   186,     0,   187,
     188,   189,   173,   174,   175,   176,     0,   177,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   470,
       0,     0,   180,   181,   182,   183,   184,   185,     0,     0,
     186,     0,   187,   188,   189,   173,   174,   175,   176,     0,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   547,     0,     0,   180,   181,   182,   183,   184,
     185,     0,     0,   186,     0,   187,   188,   189,   173,   174,
     175,   176,     0,   177,   178,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   586,     0,     0,   180,   181,
     182,   183,   184,   185,     0,     0,   186,     0,   187,   188,
     189,   173,   174,   175,   176,     0,   177,   178,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     234,   180,   181,   182,   183,   184,   185,     0,     0,   186,
       0,   187,   188,   189,   173,   174,   175,   176,     0,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   468,   180,   181,   182,   183,   184,   185,
       0,     0,   186,     0,   187,   188,   189,   173,   174,   175,
     176,     0,   177,   178,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,   436,     0,   186,     0,   187,   188,   189,
       0,     0,     0,     0,     0,     0,   173,   174,   175,   176,
       0,   177,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,   182,   183,
     184,   185,   469,     0,   186,     0,   187,   188,   189,     0,
       0,     0,     0,   173,   174,   175,   176,     0,   177,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   434,
       0,   186,     0,   187,   188,   189,     0,     0,   173,   174,
     175,   176,     0,   177,   178,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
     182,   183,   184,   185,     0,   236,   186,     0,   187,   188,
     189,   173,   174,   175,   176,     0,   177,   178,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,   182,   183,   184,   185,     0,   437,   186,
       0,   187,   188,   189,   173,   174,   175,   176,     0,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,   182,   183,   184,   185,
       0,     0,   186,     0,   187,   188,   189,   173,   174,   175,
     176,     0,   177,   178,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,     0,     0,   186,     0,   187,   188,   189,
       0,     0,     0,   243,   173,   174,   175,   176,     0,   177,
     178,   179,     0,   239,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,   182,   183,   184,   185,
       0,     0,   186,     0,   187,   188,   189,   173,   174,   175,
     176,     0,   177,   178,   179,     0,   363,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,     0,     0,   186,     0,   187,   188,   189,
     173,   174,   175,   176,     0,   177,   178,   179,     0,   441,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,   182,   183,   184,   185,     0,     0,   186,     0,
     187,   188,   189,   173,   174,   175,   176,     0,   177,   178,
     179,     0,     0,     0,   442,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,     0,
       0,   186,     0,   187,   188,   189,   173,   174,   175,   176,
       0,   177,   178,   179,     0,     0,     0,     0,     0,     0,
     577,     0,     0,     0,     0,     0,   180,   181,   182,   183,
     184,   185,     0,     0,   186,     0,   187,   188,   189,   173,
     174,   175,   176,     0,   177,   178,   179,     0,     0,     0,
       0,     0,   592,     0,     0,     0,     0,     0,     0,   180,
     181,   182,   183,   184,   185,     0,     0,   186,     0,   187,
     188,   189,   173,   174,   175,   176,     0,   177,   178,   179,
       0,   602,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,   182,   183,   184,   185,     0,     0,
     186,     0,   187,   188,   189,   173,   174,   175,   176,     0,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,     0,     0,   186,     0,   187,   188,   189,   173,   174,
     175,   176,     0,   177,   178,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
     182,   183,   184,   185,     0,     0,   508,     0,   187,   188,
     189,   173,   174,   175,     0,     0,   177,   178,   179,     0,
       0,     0,     0,     0,  -183,     0,     0,     0,     0,     0,
    -183,   180,   181,   182,   183,   184,   185,     0,     0,     0,
       0,   187,   188,   189,   173,     0,   175,     0,     0,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,   182,   183,   184,   185,
     177,   178,   179,     0,   187,   188,   189,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,     0,     0,     0,     0,   187,   188,   189
  };

  const short
  Parser::yycheck_[] =
  {
       2,   113,     5,    14,   226,   429,    68,    14,    59,   330,
       3,    57,    14,    59,     4,    56,    67,     4,    55,    21,
      22,    23,    24,    25,     3,    27,    28,    29,    30,    43,
      32,     0,    55,    56,    28,     1,    28,     3,    19,    62,
       6,    65,    83,    33,    43,    11,    33,    50,    55,    15,
      16,    28,    75,    55,    56,    57,     1,    59,     3,    83,
      50,     6,    28,    50,    63,    58,    11,    69,    59,    83,
      15,    16,     5,    67,     7,    67,    21,    58,    23,    58,
      25,    26,    27,    28,    29,    30,    31,   408,    33,   410,
      67,    36,    58,     1,    62,     3,    61,    59,     6,    44,
      45,    46,    47,    11,     5,    63,     7,    15,    53,    54,
      68,    56,   536,    58,   125,    60,    19,     5,    83,     7,
      28,    66,   124,   125,   126,    58,    92,     5,    61,     7,
     192,    55,   194,     5,    56,     7,    81,    67,    59,    69,
      62,    86,    87,    88,    89,    90,    91,    92,   151,   151,
      58,    75,    59,    75,     1,    58,     3,    58,    61,     6,
      61,    61,    28,    28,    11,    55,    56,    67,    15,   281,
      58,     3,    57,    61,     6,    56,    28,    29,    30,    11,
      58,    28,    67,    15,    92,    75,    58,    55,   190,   191,
     201,   193,   229,   195,   205,   232,    28,    28,    55,   201,
     202,    67,    67,   205,   206,   207,   208,    75,   210,    63,
      55,    58,     1,    28,     3,    56,    28,     6,    75,   221,
      63,   223,    11,   225,   226,    68,    15,   229,    60,     3,
     232,    74,     6,   368,    75,   370,    67,    11,    20,    28,
     462,    15,    24,   245,    26,    92,    28,    29,    30,    31,
     296,   297,    67,    55,    28,    67,     1,   294,     3,    56,
      92,     6,    53,    54,   292,    63,    11,    61,    85,    56,
      15,    16,   124,    67,   302,   303,    63,   288,    75,    70,
      71,    72,    73,    28,    58,   288,   288,    57,   290,    71,
      55,    57,   294,   295,   296,   297,   358,    67,    57,    57,
     302,    67,     0,    92,    57,    57,     4,    62,    67,    67,
      61,   533,   534,    58,    67,    67,    67,    61,    92,    61,
      55,   332,    70,    67,    55,    67,    14,    75,    55,   331,
     332,   333,   334,    57,    70,    33,    59,    67,   190,    75,
      62,   193,   124,    75,   126,   335,    60,    92,   335,    60,
     202,    67,    67,     3,   206,   207,     6,   368,    60,   370,
      60,    11,    56,    60,    73,    15,   368,    57,   370,   221,
      58,   223,    60,    57,   377,   377,    64,    57,    28,    67,
      68,    70,    71,    72,    73,    55,   389,   389,    83,    57,
      77,    77,    55,    70,    75,    55,    75,    75,    22,    75,
      75,    75,    24,    62,    61,    57,    56,   410,   190,    82,
      60,   193,    61,   415,   416,    69,    60,    57,    68,   422,
     202,   423,    60,   425,   206,   207,    69,    20,    55,   432,
     420,   433,   422,   420,    55,   422,    55,    35,    75,   221,
      55,   223,    92,   225,   226,   447,   448,    55,   450,    55,
      60,    55,   454,    62,    61,    75,    33,    62,    75,    60,
     462,    50,   464,   420,   408,   454,   499,   422,   432,   552,
     510,   191,   584,   245,   584,   281,   478,    31,   480,   331,
     482,   333,   334,   221,   126,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   205,   201,   205,   585,   567,   205,   196,   197,
       3,   294,   151,     6,   464,   389,     3,   229,    11,     6,
      -1,   209,    15,    -1,    11,    -1,    -1,    -1,    15,    -1,
      -1,   533,   534,    -1,   222,    28,    -1,    -1,    -1,   227,
     228,    28,   544,   231,    -1,   233,   234,   235,    -1,   331,
     238,   333,   334,    -1,   242,   243,    -1,    -1,   246,    -1,
      65,    66,    -1,    -1,     3,    70,    -1,     6,    -1,    -1,
      -1,   423,    11,   425,    -1,   204,    15,    70,    -1,   581,
     582,   433,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,   279,   290,    -1,    -1,   447,   448,   295,   450,    92,
      -1,    88,    -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,
      -1,   299,   300,   301,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   478,    -1,   480,    -1,
     482,    -1,   330,    -1,    -1,    -1,    -1,   335,    -1,    -1,
     204,   423,    -1,   425,   342,    -1,    -1,    -1,    -1,    -1,
      -1,   433,    -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   291,   292,   352,   447,   448,    -1,   450,   298,
     368,    -1,   370,   302,   303,    -1,    -1,    -1,    -1,    -1,
     462,    -1,    -1,    -1,   372,    -1,    -1,    -1,    -1,    53,
      54,    -1,   544,    -1,    -1,    -1,   478,    -1,   480,   204,
     482,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
     408,    -1,    -1,   401,   402,    79,    80,    -1,    -1,    -1,
      -1,    -1,   420,    -1,    -1,    -1,    -1,   291,   292,   581,
     582,   429,    -1,    -1,   298,    -1,    -1,    -1,   302,   303,
      -1,    -1,    -1,    -1,    -1,    -1,   434,   435,   436,   437,
     379,   533,   534,   382,    -1,    -1,   454,    -1,   446,    -1,
      -1,    -1,   544,    -1,    -1,    -1,   464,    -1,   397,    -1,
      -1,   400,    -1,    -1,    -1,    -1,    -1,   406,   466,   467,
      -1,    -1,    -1,    -1,    -1,    -1,   291,   292,    -1,    -1,
      -1,    -1,    -1,   298,    -1,    -1,    -1,   302,   303,   581,
     582,   499,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   379,    -1,    -1,   382,    -1,
     508,    -1,   510,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   461,   397,   463,    -1,   400,   525,   536,   468,
      -1,   470,   406,   204,    -1,    -1,    -1,    -1,   477,    -1,
     479,    -1,   481,   541,   542,   543,    -1,    -1,   546,    -1,
      -1,    -1,    -1,    -1,   552,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   561,   379,    -1,    -1,   382,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   397,    -1,    -1,   400,   204,   461,    -1,   463,
      -1,   406,    -1,    -1,   468,   593,   470,    -1,    -1,    -1,
      -1,    -1,    -1,   477,    -1,   479,   545,   481,   547,   548,
      -1,    -1,    -1,    -1,    -1,    -1,   555,   556,   557,    48,
     291,   292,    -1,    -1,    53,    54,    55,   298,    -1,    -1,
      -1,   302,   303,    -1,   573,   574,    -1,    -1,   577,    68,
      69,    70,    71,    72,    73,    -1,   461,   586,   463,    78,
      79,    80,    -1,   468,    -1,   470,    -1,    -1,    -1,    -1,
      -1,    -1,   477,    -1,   479,    -1,   481,    -1,    -1,    -1,
      -1,   545,    -1,   547,   548,    -1,    -1,    -1,    -1,    -1,
     298,   555,   556,   557,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   573,
     574,    -1,    -1,   577,    -1,    -1,    -1,    -1,   379,    -1,
      -1,   382,   586,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   397,    -1,    -1,   400,
     545,    -1,   547,   548,    -1,   406,    -1,    -1,    -1,    -1,
     555,   556,   557,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   573,   574,
      -1,   379,   577,    -1,   382,    -1,    -1,    -1,    -1,   584,
      -1,   586,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   397,
      -1,    -1,   400,    -1,    -1,    -1,    -1,    -1,   406,    -1,
     461,    -1,   463,    -1,    -1,    -1,    -1,   468,    -1,   470,
      -1,    -1,    -1,    -1,    -1,    -1,   477,    -1,   479,    -1,
     481,    -1,    -1,     0,     1,    -1,    -1,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      17,    18,    19,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   461,    -1,   463,    17,    18,    19,    -1,
     468,    -1,   470,    -1,    -1,    -1,    -1,     3,    -1,   477,
       6,   479,    -1,   481,    -1,    11,    -1,    -1,    -1,    15,
      16,    58,    -1,    -1,   545,    -1,   547,   548,    -1,    -1,
      -1,    -1,    28,    -1,   555,   556,   557,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,   573,   574,    -1,    -1,   577,    53,    54,    -1,
      56,    -1,    58,    -1,    60,   586,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,   545,    -1,   547,
     548,    -1,    -1,    -1,    -1,    -1,    -1,   555,   556,   557,
      86,    87,    88,    89,    90,    91,    92,     1,    -1,     3,
      -1,    -1,     6,    -1,    -1,   573,   574,    11,    -1,   577,
      -1,    15,    16,    -1,    -1,    -1,    -1,    21,   586,    23,
      -1,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,
      54,    -1,    56,    -1,    58,    -1,    60,    -1,    -1,    -1,
      -1,    -1,    66,     1,    -1,    -1,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    81,    -1,    17,
      18,    19,    86,    87,    88,    89,    90,    91,    92,     1,
      -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    21,
      -1,    23,    -1,    25,    26,    27,    28,    29,    30,    31,
      58,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    53,    54,    -1,    56,    -1,    58,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    86,    87,    88,    89,    90,    91,
      92,     1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    -1,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    66,    -1,     1,    -1,
       3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,
      -1,    81,    15,    16,    -1,    -1,    86,    87,    88,    89,
      90,    91,    92,    26,    -1,    28,    29,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    38,    -1,    40,    41,    -1,
      -1,    -1,    45,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    56,    -1,    58,    -1,    60,    -1,    -1,
      -1,    64,    65,    66,    -1,     1,    -1,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,
      16,    -1,    -1,    86,    87,    88,    89,    90,    91,    92,
      26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      56,    -1,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      66,    -1,     1,    -1,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,
      86,    87,    88,    89,    90,    91,    92,    26,    -1,    28,
      29,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    -1,    -1,    -1,    45,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    -1,    56,    57,    58,
      -1,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,     1,
      -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    15,    16,    -1,    -1,    86,    87,    88,
      89,    90,    91,    92,    26,    -1,    28,    29,    30,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    46,    47,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    56,    57,    58,    -1,    60,    -1,
      -1,    -1,    -1,    65,    66,    -1,     1,    -1,     3,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      15,    16,    -1,    -1,    86,    87,    88,    89,    90,    91,
      92,    26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    56,    57,    58,    -1,    60,    -1,    -1,    -1,    -1,
      65,    66,    -1,     1,    -1,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    26,    -1,
      28,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    -1,    -1,    -1,    45,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    54,    -1,    56,    -1,
      58,    -1,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,    92,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      -1,    -1,    -1,    21,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,
      58,    -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,    92,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,
      58,    -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,    92,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,
      58,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,    92,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,
      58,    -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,    92,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,
      58,    -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      11,    -1,    -1,    81,    15,    16,    -1,    -1,    86,    87,
      88,    89,    90,    91,    92,    26,    -1,    28,    29,    30,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    38,    -1,    40,
      41,    -1,    -1,    -1,    45,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    -1,    56,    -1,    58,    -1,    60,
      61,    -1,    -1,    64,    65,    66,    -1,    -1,    -1,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    15,    16,    -1,    -1,    86,    87,    88,    89,    90,
      91,    92,    26,    -1,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    -1,
      -1,    45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    56,    -1,    58,     3,    60,    -1,     6,    -1,
      -1,    65,    66,    11,    -1,    -1,    -1,    15,    16,    -1,
      48,    49,    50,    -1,    -1,    53,    54,    55,    -1,    -1,
      28,    -1,    86,    87,    88,    89,    90,    91,    92,    -1,
      68,    69,    70,    71,    72,    73,    -1,    45,    46,    47,
      78,    79,    80,    -1,    -1,    53,    54,    -1,    56,    -1,
      58,    -1,    60,    32,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    75,    -1,    48,
      49,    50,    51,    -1,    53,    54,    55,    -1,    86,    87,
      88,    89,    90,    91,    92,    -1,    32,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    -1,    76,    -1,    78,
      79,    80,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      76,    -1,    78,    79,    80,    48,    49,    50,    51,    -1,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    -1,    68,    69,    70,    71,    72,
      73,    -1,    -1,    76,    -1,    78,    79,    80,    48,    49,
      50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    68,    69,
      70,    71,    72,    73,    -1,    -1,    76,    -1,    78,    79,
      80,    48,    49,    50,    51,    -1,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    68,    69,    70,    71,    72,    73,    -1,    -1,    76,
      -1,    78,    79,    80,    48,    49,    50,    51,    -1,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    68,    69,    70,    71,    72,    73,
      -1,    -1,    76,    -1,    78,    79,    80,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    35,    -1,    76,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    37,    -1,    76,    -1,    78,    79,    80,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    -1,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    39,
      -1,    76,    -1,    78,    79,    80,    -1,    -1,    48,    49,
      50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    -1,    42,    76,    -1,    78,    79,
      80,    48,    49,    50,    51,    -1,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    -1,    42,    76,
      -1,    78,    79,    80,    48,    49,    50,    51,    -1,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      -1,    -1,    76,    -1,    78,    79,    80,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    -1,    76,    -1,    78,    79,    80,
      -1,    -1,    -1,    84,    48,    49,    50,    51,    -1,    53,
      54,    55,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      -1,    -1,    76,    -1,    78,    79,    80,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    -1,    76,    -1,    78,    79,    80,
      48,    49,    50,    51,    -1,    53,    54,    55,    -1,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    -1,    -1,    76,    -1,
      78,    79,    80,    48,    49,    50,    51,    -1,    53,    54,
      55,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    -1,
      -1,    76,    -1,    78,    79,    80,    48,    49,    50,    51,
      -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    -1,    -1,    76,    -1,    78,    79,    80,    48,
      49,    50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    -1,    76,    -1,    78,
      79,    80,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      76,    -1,    78,    79,    80,    48,    49,    50,    51,    -1,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    -1,    -1,    76,    -1,    78,    79,    80,    48,    49,
      50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    -1,    -1,    76,    -1,    78,    79,
      80,    48,    49,    50,    -1,    -1,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    78,    79,    80,    48,    -1,    50,    -1,    -1,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      53,    54,    55,    -1,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    78,    79,    80
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    58,    99,   100,   210,   211,     1,     3,     6,
      11,    15,    28,    92,   197,   212,   213,   214,     0,     1,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      17,    18,    19,   101,   102,   103,   104,   105,   106,   107,
     108,   111,   112,   113,   114,   115,   118,   121,   125,   126,
     210,     3,   211,    59,    16,    26,    29,    30,    33,    40,
      41,    45,    46,    47,    52,    53,    54,    56,    58,    60,
      65,    66,    86,    87,    88,    89,    90,    91,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   197,   198,   202,
      59,    59,    59,    60,   197,   198,   197,   197,   197,   197,
     198,   197,   198,   197,    56,    60,    68,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   197,   198,   182,   182,
     187,   198,   197,   102,   103,   197,   199,   202,   203,   205,
     206,   210,   200,   203,   200,   146,   200,   146,   146,   147,
     147,     1,   145,   146,     1,    59,   145,   146,   177,   178,
     197,   147,   198,    48,    49,    50,    51,    53,    54,    55,
      68,    69,    70,    71,    72,    73,    76,    78,    79,    80,
      43,    83,    56,    62,    56,    63,    56,    75,   175,   179,
     180,    56,    75,    55,    55,    56,    75,    55,    63,    55,
      43,    55,   181,   182,   197,   201,   202,   182,   191,    55,
      85,    68,    74,    14,    55,    68,    62,    55,    28,    67,
     199,    28,    67,    28,    34,    28,    42,    57,    67,    57,
      59,    59,    67,    84,    61,    67,    62,    65,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   182,   167,   197,     1,    57,
     145,   146,   182,     1,    57,   145,   197,   146,   146,    75,
      61,    67,     1,    16,   193,   194,   202,   204,   210,   182,
      60,    21,    23,    25,    26,    27,    29,    30,    31,    33,
      36,    44,    60,    81,   129,   130,   131,   132,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   147,   149,
     150,   151,     1,   193,   194,   182,   182,    70,   146,   197,
      60,    67,    67,    70,    75,    60,   181,   182,   191,   192,
     146,   182,    60,   192,   146,   146,   206,   146,   203,   146,
     146,   146,    60,   146,   146,   146,   178,   146,    56,    57,
      57,    57,    57,    57,   146,   180,    57,    57,    67,    57,
      67,   202,    55,     1,   109,   110,   197,   210,     1,   128,
     129,     1,   128,   205,     1,   197,   207,   208,   209,   210,
     200,   200,   129,   146,   146,   146,     1,   128,   197,     1,
     128,    77,    77,    57,    57,    57,    55,   108,   116,   117,
     210,   182,   202,   182,   182,     5,     7,   106,   107,   119,
     120,   127,   210,    67,    69,    75,    55,   106,   107,   122,
     123,   124,   210,    75,    39,    32,    35,    42,   146,   162,
     163,    57,    59,     1,    57,   145,    75,    75,    75,   204,
      75,   204,   146,    61,    67,   197,    22,    22,   129,    24,
      24,    28,    62,    28,    67,   209,    28,    28,    34,    37,
      32,    61,    61,    82,    82,   146,   146,    55,    75,    55,
      75,    55,    75,   129,    61,   117,   108,    57,    61,    69,
     197,   197,    61,   119,   106,   107,   127,   182,   182,    60,
      61,   123,   124,   182,   146,   146,   146,   146,    76,    61,
      67,    57,    57,   146,   182,   182,   182,   109,   129,   192,
     129,   208,   146,   146,   129,    60,   129,   129,   182,   129,
     182,   129,   182,    62,    62,    69,   122,    20,   195,   146,
     163,    55,    55,    55,    75,    32,    42,    32,    35,     1,
      38,    64,   133,   134,   146,    55,    55,    55,   192,   192,
      61,    60,    55,   196,   146,   146,   146,   182,   129,   146,
     129,   129,    61,    62,    62,    61,   134,    62,   129,   129,
     129,    75,    75,   146,    60,   195,    32,   129,   129,   129,
     182,   182,    61,    56,   147,   175,   179,   196,   129,   146,
      61,    61,    57
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    98,    99,   100,   100,   101,   101,   102,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   104,   104,   105,   106,   106,   106,
     106,   107,   107,   107,   107,   107,   107,   107,   107,   108,
     109,   109,   109,   110,   110,   111,   112,   112,   113,   114,
     114,   115,   116,   116,   117,   117,   118,   119,   119,   119,
     119,   119,   119,   120,   120,   121,   121,   122,   122,   123,
     123,   124,   124,   125,   126,   127,   127,   128,   128,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   130,   131,   131,   132,   132,   133,   133,   134,
     134,   134,   135,   136,   137,   137,   138,   139,   140,   140,
     140,   140,   141,   141,   141,   141,   142,   142,   143,   144,
     145,   145,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   147,   147,   147,   147,   147,   147,   147,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   149,   149,   149,
     150,   150,   150,   150,   150,   151,   151,   151,   151,   152,
     153,   153,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   162,   163,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   165,   166,   166,   167,
     168,   169,   170,   170,   171,   172,   173,   173,   173,   174,
     175,   176,   177,   177,   178,   179,   179,   180,   180,   180,
     181,   181,   182,   182,   182,   182,   182,   182,   182,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   191,
     192,   192,   193,   193,   194,   194,   195,   195,   196,   196,
     196,   197,   197,   197,   197,   197,   197,   198,   198,   199,
     199,   200,   200,   201,   201,   202,   203,   203,   204,   204,
     205,   205,   206,   207,   207,   208,   208,   208,   209,   210,
     210,   211,   211,   211,   211,   212,   213,   214
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
       1,     1,     3,     3,     1,     1,     1,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     1,     1,     1,
       1,     1,     3,     4,     4,     3,     5,     6,     6,     3,
       3,     4,     4,     3,     4,     6,     6,     6,     6,     3,
       6,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     3,     5,
       5,     3,     3,     1,     3,     3,     1,     2,     5,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     4,     6,     3,     5,     2,     3,     1,
       1,     0,     3,     1,     3,     1,     4,     0,     4,     4,
       0,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     3,     1,     3,     2,     1,     2,     1,
       3,     1,     3,     3,     1,     2,     1,     1,     7,     2,
       1,     3,     3,     3,     3,     1,     2,     2
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
  "\"exists\"", "\"match\"", "\"with\"", "\"as\"", "\"while\"",
  "\"undef\"", "\"false\"", "\"true\"", "\"and\"", "\"or\"", "\"xor\"",
  "\"implies\"", "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\":\"", "\"::\"", "\"_\"", "\"|\"",
  "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"", "\"^\"",
  "\"'\"", "\"->\"", "\"=>\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"",
  "\"{|\"", "\"|}\"", "\".\"", "\"..\"", "\"...\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"decimal\"",
  "\"string\"", "\"identifier\"", "BASIC_TYPE", "CALL", "UPLUS", "UMINUS",
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
  "CardinalityExpression", "MatchExpression", "MatchArms", "MatchArm",
  "Literal", "UndefinedLiteral", "BooleanLiteral", "IntegerLiteral",
  "RationalLiteral", "DecimalLiteral", "BinaryLiteral", "StringLiteral",
  "ReferenceLiteral", "ListLiteral", "RangeLiteral", "TupleLiteral",
  "RecordLiteral", "Assignments", "Assignment", "MappedExpressions",
  "MappedExpression", "Types", "Type", "BasicType", "TupleType",
  "RecordType", "TemplateType", "RelationType", "FixedSizedType",
  "MappingType", "VaradicType", "FunctionParameters",
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
       0,   445,   445,   455,   461,   469,   475,   485,   491,   495,
     503,   507,   511,   515,   519,   523,   527,   531,   535,   539,
     543,   547,   551,   555,   563,   567,   575,   583,   588,   594,
     600,   608,   614,   619,   626,   632,   639,   645,   649,   657,
     665,   669,   675,   683,   690,   700,   708,   712,   720,   728,
     732,   744,   751,   757,   766,   772,   784,   792,   798,   802,
     808,   812,   818,   825,   831,   845,   849,   856,   862,   871,
     877,   884,   888,   900,   912,   924,   928,   940,   946,   956,
     960,   964,   968,   972,   976,   980,   984,   988,   992,   996,
    1000,  1004,  1012,  1020,  1024,  1032,  1036,  1044,  1050,  1060,
    1064,  1068,  1076,  1084,  1092,  1096,  1104,  1112,  1120,  1124,
    1128,  1133,  1142,  1146,  1150,  1155,  1164,  1168,  1176,  1184,
    1196,  1203,  1213,  1217,  1221,  1225,  1229,  1233,  1237,  1241,
    1245,  1249,  1257,  1261,  1265,  1269,  1273,  1277,  1281,  1293,
    1297,  1301,  1305,  1309,  1313,  1317,  1321,  1325,  1329,  1333,
    1337,  1341,  1345,  1349,  1353,  1357,  1361,  1369,  1373,  1377,
    1385,  1392,  1396,  1401,  1405,  1413,  1418,  1425,  1431,  1439,
    1447,  1454,  1460,  1468,  1476,  1484,  1492,  1500,  1508,  1516,
    1523,  1530,  1537,  1546,  1559,  1563,  1567,  1571,  1575,  1579,
    1583,  1587,  1595,  1599,  1603,  1607,  1615,  1624,  1630,  1640,
    1648,  1656,  1664,  1668,  1676,  1684,  1713,  1720,  1726,  1734,
    1744,  1757,  1771,  1778,  1787,  1794,  1801,  1810,  1815,  1821,
    1837,  1844,  1853,  1857,  1861,  1865,  1869,  1873,  1877,  1881,
    1889,  1897,  1908,  1919,  1927,  1935,  1943,  1951,  1963,  1970,
    1980,  1984,  1992,  1999,  2013,  2020,  2034,  2038,  2046,  2052,
    2065,  2078,  2082,  2087,  2092,  2097,  2102,  2111,  2118,  2130,
    2134,  2143,  2150,  2160,  2167,  2177,  2186,  2192,  2200,  2206,
    2218,  2225,  2234,  2246,  2253,  2262,  2268,  2272,  2279,  2292,
    2298,  2307,  2314,  2321,  2328,  2335,  2342,  2349
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


#line 47 "../../obj/src/GrammarParser.y"
} // libcasm_fe
#line 6941 "GrammarParser.cpp"

#line 2355 "../../obj/src/GrammarParser.y"


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
